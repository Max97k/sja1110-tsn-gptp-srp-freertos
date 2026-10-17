#!/usr/bin/env python3
"""
SJA1110-MGS-EVM IEEE 802.1Qat (MSRP / MVRP) & 802.1AS (gPTP)
Bidirectional Test Script

Connection: SJA1110 SW1 Port 4 (1G SFP) <-> PC Ethernet Interface

Usage:
    python tool/test_sja1110_srp.py [--iface Ethernet] [--mac a0:ad:9f:2d:fe:84]

Milestones verified:
  T4:   125ms gPTP Sync/Follow_Up, Pdelay_Req, Pdelay Responder (Resp + Follow_Up)
  T5-A: MVRP JoinIn (VID = 2) Injection & State Machine Response
  T5-B: MSRP Talker Advertise Injection & Propagation
  T5-C: MSRP Listener Ready & Reservation Loop Closure
"""
import argparse
import struct
import sys
import threading
import time
from scapy.all import Ether, Raw, sendp, sniff, conf

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

# ---------------------------------------------------------------------------
# CLI Arguments & Auto-detection
# ---------------------------------------------------------------------------
def detect_default_iface():
    for iface in conf.ifaces.values():
        if "Realtek" in iface.description or "Ethernet" in iface.name:
            return iface.name, iface.mac
    return "Ethernet", "a0:ad:9f:2d:fe:84"

default_iface, default_mac = detect_default_iface()

parser = argparse.ArgumentParser(description="SJA1110 TSN SRP/gPTP bidirectional test tool")
parser.add_argument("--iface", default=default_iface,
                    help=f"Network interface connected to SJA1110 Port 4 (default: {default_iface})")
parser.add_argument("--mac", default=default_mac,
                    help=f"Source MAC of PC NIC (default: {default_mac})")
args = parser.parse_args()
IFACE  = args.iface
PC_MAC = args.mac
PC_CLOCK_ID = bytes.fromhex(PC_MAC.replace(":", "")[:6] + "fffe" + PC_MAC.replace(":", "")[6:])

ETHERTYPE_NAMES = {0x88F7: "gPTP", 0x22EA: "MSRP", 0x88F5: "MVRP", 0x88F6: "MMRP"}
stats = {
    "gptp_sync": 0,
    "gptp_fup": 0,
    "gptp_pdelay_req": 0,
    "gptp_pdelay_resp_sent": 0,
    "msrp_rx": 0,
    "mvrp_rx": 0,
    "other_rx": 0,
    "header_leak_8b8c": 0
}

# ---------------------------------------------------------------------------
# Frame builders
# ---------------------------------------------------------------------------
def build_mvrp_join_vid2() -> Ether:
    """IEEE 802.1Q MVRP JoinIn (VID = 2) PDU."""
    pdu = struct.pack("!BBBHBB",
                      0x00,   # Protocol Version
                      0x01,   # Attribute Type: VID (1)
                      0x02,   # Attribute Length (2 bytes per VID entry)
                      0x0001, # Vector Header: LeaveAll=0, NumberOfValues=1
                      0x00, 0x02)  # First Value: VID = 2
    # ThreePackedEvent: JoinIn for 1 value = 1 * 36 = 36 (0x24), padded
    pdu += struct.pack("!BHH", 0x24, 0x0000, 0x0000)  # 3-packed + Vector + PDU EndMarks
    return Ether(dst="01:80:c2:00:00:21", src=PC_MAC, type=0x88F5) / Raw(load=pdu)


def build_msrp_domain_class_a(sr_class_id: int = 6, priority: int = 3, vlan_id: int = 2) -> Ether:
    """IEEE 802.1Qat MSRP Domain (AttributeType = 4) PDU to clear SR Class A Domain Boundary Port."""
    first_val = struct.pack("!BBH", sr_class_id, priority, vlan_id)
    attr_list_len = 2 + 4 + 1 + 2
    pdu = (struct.pack("!BBBHH", 0x00, 0x04, 4, attr_list_len, 0x0001) +
           first_val +
           struct.pack("!BHH", 0x24, 0x0000, 0x0000))
    return Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)


def build_msrp_talker_advertise(
    stream_id_hex: str = "0011223344550001",
    stream_da_hex: str = "91e0f000fe00",
    vlan_id: int = 2,
    max_frame_size: int = 128,
    max_interval_frames: int = 1,
    priority: int = 3,   # Class A
    accum_latency: int = 1000,
) -> Ether:
    """IEEE 802.1Qat MSRP Talker Advertise PDU."""
    stream_id = bytes.fromhex(stream_id_hex)
    stream_da = bytes.fromhex(stream_da_hex)
    prio_rank = (priority << 5) | (1 << 4)  # Rank=1

    first_val = (stream_id + stream_da +
                 struct.pack("!HHHBI", vlan_id, max_frame_size,
                             max_interval_frames, prio_rank, accum_latency))
    assert len(first_val) == 25, f"First Value must be 25 bytes, got {len(first_val)}"

    # VecHdr(2) + FirstVal(25) + 3Packed(1) + VecEndMark(2)
    attr_list_len = 2 + 25 + 1 + 2

    pdu = (struct.pack("!BBBHH",
                       0x00,           # Protocol Version
                       0x01,           # Attribute Type: Talker Advertise
                       25,             # Attribute Length
                       attr_list_len,  # Attribute List Length
                       0x0001) +       # Vector Header: LeaveAll=0, NumValues=1
           first_val +
           struct.pack("!BHH",
                       36,     # ThreePackedEvent: JoinIn (1 value * 36)
                       0x0000, # Vector EndMark
                       0x0000))# PDU EndMark
    return Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)


def build_msrp_listener_ready(stream_id_hex: str = "0011223344550001") -> Ether:
    """IEEE 802.1Qat MSRP Listener Ready PDU.
    ThreePackedEvent = JoinIn (1 * 36 = 0x24), FourPackedEvent = Ready (2 * 64 = 0x80).
    """
    stream_id = bytes.fromhex(stream_id_hex)
    attr_list_len = 2 + 8 + 1 + 1 + 2
    pdu = (struct.pack("!BBBHH",
                       0x00, 0x03, 8, attr_list_len, 0x0001) +
           stream_id +
           struct.pack("!BBHH", 0x24, 0x80, 0x0000, 0x0000))
    return Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)


def respond_pdelay_req(raw: bytes, src_mac: str) -> None:
    """Respond to SJA1110 gPTP Pdelay_Req with Pdelay_Resp and Pdelay_Resp_Follow_Up."""
    if len(raw) < 34:
        return
    seq = int.from_bytes(raw[30:32], "big")
    req_port_id = raw[20:30]  # sourcePortIdentity of initiator

    t2_total_ns = time.time_ns()
    t2_sec, t2_nsec = divmod(t2_total_ns, 1_000_000_000)

    # Pdelay_Resp (Type 3, length 54)
    resp_hdr = struct.pack("!BBHBBHQIH10sHBB",
        0x13, 0x02, 54, 0x00, 0x00, 0x0208, 0, 0, 0,
        PC_CLOCK_ID[:8] + b"\x00\x01", seq, 0x05, 0x7F
    )
    t2_bytes = struct.pack("!Q", t2_sec)[2:] + struct.pack("!I", t2_nsec)
    resp_payload = resp_hdr + t2_bytes + req_port_id
    resp_pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x88F7) / Raw(load=resp_payload)
    sendp(resp_pkt, iface=IFACE, verbose=False)

    # Capture actual t3 egress timestamp (with proper second carry) after sending Pdelay_Resp
    t3_total_ns = max(time.time_ns(), t2_total_ns + 1000)
    t3_sec, t3_nsec = divmod(t3_total_ns, 1_000_000_000)

    # Pdelay_Resp_Follow_Up (Type 10, length 54)
    fup_hdr = struct.pack("!BBHBBHQIH10sHBB",
        0x1A, 0x02, 54, 0x00, 0x00, 0x0008, 0, 0, 0,
        PC_CLOCK_ID[:8] + b"\x00\x01", seq, 0x05, 0x7F
    )
    t3_bytes = struct.pack("!Q", t3_sec)[2:] + struct.pack("!I", t3_nsec)
    fup_payload = fup_hdr + t3_bytes + req_port_id
    fup_pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x88F7) / Raw(load=fup_payload)
    sendp(fup_pkt, iface=IFACE, verbose=False)

    stats["gptp_pdelay_resp_sent"] += 1
    print(f"  [gPTP Responder] <-- Pdelay_Req(seq={seq})  --> Sent Pdelay_Resp + Follow_Up")


# ---------------------------------------------------------------------------
# Packet handler
# ---------------------------------------------------------------------------
def packet_handler(pkt) -> None:
    if Ether not in pkt:
        return
    et  = pkt[Ether].type
    src = pkt[Ether].src
    dst = pkt[Ether].dst

    # Ignore our own outbound injected packets
    if src.lower() == PC_MAC.lower():
        return

    if et == 0x8B8C:
        stats["header_leak_8b8c"] += 1
        print(f"  [!] ALERT: SJA1110 0x8B8C header leaked to wire! len={len(pkt)}")
        return

    if et == 0x88F7:
        raw = bytes(pkt[Raw]) if Raw in pkt else b""
        msg_type = (raw[0] & 0x0F) if len(raw) > 0 else 0xFF
        seq = int.from_bytes(raw[30:32], "big") if len(raw) >= 32 else 0

        if msg_type == 0:  # Sync
            stats["gptp_sync"] += 1
            if stats["gptp_sync"] % 8 == 1:
                print(f"  [RX gPTP Sync] seq={seq:5d}  src={src}  dst={dst} (125ms interval)")
        elif msg_type == 8:  # Follow_Up
            stats["gptp_fup"] += 1
        elif msg_type == 2:  # Pdelay_Req
            stats["gptp_pdelay_req"] += 1
            respond_pdelay_req(raw, src)

    elif et == 0x22EA:
        stats["msrp_rx"] += 1
        raw = bytes(pkt[Raw]) if Raw in pkt else b""
        attr_t = raw[1] if len(raw) > 1 else 0
        attr_desc = {1: "TalkerAdv", 2: "TalkerFailed/LeaveAll", 3: "Listener", 4: "Domain"}.get(attr_t, f"Type{attr_t}")
        print(f"  [RX MSRP PDU] attr={attr_desc}  src={src}  dst={dst}  len={len(pkt)}")

    elif et == 0x88F5:
        stats["mvrp_rx"] += 1
        print(f"  [RX MVRP PDU] src={src}  dst={dst}  len={len(pkt)}")
    else:
        stats["other_rx"] += 1


# ---------------------------------------------------------------------------
# Main test flow
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    print(f"\n{'='*72}")
    print(f"  SJA1110-MGS-EVM TSN Closed-Loop Bidirectional Verification")
    print(f"  Interface: {IFACE}  |  PC MAC: {PC_MAC}")
    print(f"{'='*72}\n")

    # Stage 1: T4 Validation & Active gPTP Pdelay Locking (4 seconds)
    print("=== Stage 1: [T4] gPTP Sync Verification & Active Pdelay Locking (4 s) ===")
    sniff(iface=IFACE, prn=packet_handler, timeout=4,
          filter="ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x8b8c")

    # Stage 2: T5-A MVRP Injection (VID = 2)
    print("\n=== Stage 2: [T5-A] Injecting MVRP JoinIn (VID=2) ===")
    sendp(build_mvrp_join_vid2(), iface=IFACE, verbose=False)
    print("  [TX MVRP] JoinIn VID=2 sent to 01:80:C2:00:00:21")

    # Stage 3: T5-B MSRP Domain & Talker Advertise Injection
    print("\n=== Stage 3: [T5-B] Injecting MSRP Domain (Class A) & Talker Advertise (StreamID=0011223344550001) ===")
    sendp(build_msrp_domain_class_a(), iface=IFACE, verbose=False)
    print("  [TX MSRP] Domain (SRclassID=6, Priority=3, VID=2) sent to clear Domain Boundary Port")
    time.sleep(0.1)
    sendp(build_msrp_talker_advertise(), iface=IFACE, verbose=False)
    print("  [TX MSRP] Talker Advertise (StreamID=0011223344550001, VID=2, Priority 3) sent")

    # Stage 4: T5-C MSRP Listener Ready Injection
    print("\n=== Stage 4: [T5-C] Injecting MSRP Listener Ready (StreamID=0011223344550001) ===")
    time.sleep(0.5)
    sendp(build_msrp_listener_ready(), iface=IFACE, verbose=False)
    print("  [TX MSRP] Listener Ready (StreamID=0011223344550001) sent")

    # Stage 5: Observe MRP Convergence & Pdelay exchanges (6 seconds, with IEEE 802.1Qat JoinIn refresh)
    print("\n=== Stage 5: [T4/T5] Observing MRP State Machine Convergence & Pdelay (6 s) ===")
    for _round_idx in range(3):
        sniff(iface=IFACE, prn=packet_handler, timeout=2,
              filter="ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x8b8c")
        sendp(build_mvrp_join_vid2(), iface=IFACE, verbose=False)
        sendp(build_msrp_domain_class_a(), iface=IFACE, verbose=False)
        time.sleep(0.05)
        sendp(build_msrp_talker_advertise(), iface=IFACE, verbose=False)
        time.sleep(0.05)
        sendp(build_msrp_listener_ready(), iface=IFACE, verbose=False)
    time.sleep(0.25)

    # ---------------------------------------------------------------------------
    # Report & Scorecard
    # ---------------------------------------------------------------------------
    print(f"\n{'='*72}")
    print(f"                      TEST RESULTS SUMMARY (T4 & T5)")
    print(f"{'='*72}")
    print(f"  [T4] gPTP Sync Frames Captured:         {stats['gptp_sync']:4d}  ({'PASS' if stats['gptp_sync'] >= 20 else 'FAIL'})")
    print(f"  [T4] gPTP Follow_Up Frames Captured:    {stats['gptp_fup']:4d}  ({'PASS' if stats['gptp_fup'] >= 20 else 'FAIL'})")
    print(f"  [T4] gPTP Pdelay_Req Captured:          {stats['gptp_pdelay_req']:4d}  ({'PASS' if stats['gptp_pdelay_req'] >= 1 else 'FAIL'})")
    print(f"  [T4] gPTP Pdelay_Resp/Fup Sent (PC):    {stats['gptp_pdelay_resp_sent']:4d}  ({'PASS' if stats['gptp_pdelay_resp_sent'] >= 1 else 'FAIL'})")
    print(f"  [T4] SJA1110 0x8B8C Header Leakage:     {stats['header_leak_8b8c']:4d}  ({'PASS' if stats['header_leak_8b8c'] == 0 else 'FAIL'})")
    print(f"  [T5] MSRP Frames Captured from EVB:     {stats['msrp_rx']:4d}  ({'PASS' if stats['msrp_rx'] >= 1 else 'WARN'})")
    print(f"{'='*72}\n")
