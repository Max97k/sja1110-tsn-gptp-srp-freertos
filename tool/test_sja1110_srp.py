#!/usr/bin/env python3
"""
SJA1110-MGS-EVM IEEE 802.1Qat (MSRP / MVRP) & 802.1AS (gPTP)
Bidirectional Test Script

Connection: SJA1110 SW1 Port 4 (1G SFP) <-> PC Ethernet Interface

Usage:
    pip install scapy
    python tool/test_sja1110_srp.py --iface eth0 --mac 00:11:22:33:44:55

Stages:
  1. Listen 3 s for board TX frames (gPTP, MSRP, MVRP) - T4 verification
  2. Send MVRP JoinIn (VID=2)                           - T5-A
  3. Send MSRP Talker Advertise                         - T5-B
  4. Send MSRP Listener Ready                           - T5-C
  5. Listen 5 s for board state machine responses       - T5-B/C
"""
import argparse
import struct
import time
from scapy.all import Ether, Raw, sendp, sniff

# ---------------------------------------------------------------------------
# CLI Arguments
# ---------------------------------------------------------------------------
parser = argparse.ArgumentParser(description="SJA1110 TSN SRP/gPTP test tool")
parser.add_argument("--iface", default="eth0",
                    help="Network interface connected to SJA1110 Port 4 (default: eth0)")
parser.add_argument("--mac", default="00:11:22:33:44:55",
                    help="Source MAC of this PC NIC (default: 00:11:22:33:44:55)")
args = parser.parse_args()
IFACE  = args.iface
PC_MAC = args.mac

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


def build_msrp_talker_advertise(
    stream_id_hex: str = "0011223344550001",
    stream_da_hex: str = "91e0f000fe01",
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
    """IEEE 802.1Qat MSRP Listener Ready PDU."""
    stream_id = bytes.fromhex(stream_id_hex)
    # Attribute Type 3 = Listener, Attribute Length = 8 (StreamID only)
    # FourPackedEvent: Ready = 2 => packed value for 1 entry = 2 * 64 = 128 (0x80)
    attr_list_len = 2 + 8 + 1 + 1 + 2
    pdu = (struct.pack("!BBBHH",
                       0x00, 0x03, 8, attr_list_len, 0x0001) +
           stream_id +
           struct.pack("!BBHH", 0x80, 0x00, 0x0000, 0x0000))
    return Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)


# ---------------------------------------------------------------------------
# Packet handler
# ---------------------------------------------------------------------------
ETHERTYPE_NAMES = {0x88F7: "gPTP", 0x22EA: "MSRP", 0x88F5: "MVRP", 0x88F6: "MMRP"}

def packet_handler(pkt) -> None:
    if Ether not in pkt:
        return
    et  = pkt[Ether].type
    src = pkt[Ether].src
    name = ETHERTYPE_NAMES.get(et, f"0x{et:04X}")
    raw_hex = bytes(pkt[Raw]).hex()[:48] + "..." if Raw in pkt else ""
    print(f"[RX {name:4s}] src={src}  len={len(pkt):4d}  {raw_hex}")


BPF_TSN = "ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x88f6"

# ---------------------------------------------------------------------------
# Main test sequence
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    print(f"\n{'='*60}")
    print(f"  SJA1110-MGS-EVM TSN Self-Test  |  iface={IFACE}  src={PC_MAC}")
    print(f"{'='*60}\n")

    # Stage 1 - T4: Capture board TX frames
    print("Stage 1 [T4] Listening for board TX frames (3 s) ...")
    sniff(iface=IFACE, prn=packet_handler, timeout=3, filter=BPF_TSN)

    # Stage 2 - T5-A: Inject MVRP JoinIn (VID = 2)
    print("\nStage 2 [T5-A] Sending MVRP JoinIn (VID=2) ...")
    sendp(build_mvrp_join_vid2(), iface=IFACE, verbose=False)

    # Stage 3 - T5-B: Inject MSRP Talker Advertise
    print("Stage 3 [T5-B] Sending MSRP Talker Advertise (StreamID=0011223344550001) ...")
    sendp(build_msrp_talker_advertise(), iface=IFACE, verbose=False)

    # Stage 4 - Wait for board MRP timer period, then send Listener Ready
    print("Stage 4 [T5-C] Waiting 1 s for board to propagate Talker Advertise ...")
    time.sleep(1.0)
    print("         Sending MSRP Listener Ready (closes the loop) ...")
    sendp(build_msrp_listener_ready(), iface=IFACE, verbose=False)

    # Stage 5 - Capture board state machine responses
    print("\nStage 5 [T5-B/C] Listening for board MRP state machine responses (5 s) ...")
    sniff(iface=IFACE, prn=packet_handler, timeout=5,
          filter="ether proto 0x22ea or ether proto 0x88f5")

    print("\n[+] Test script complete. Verify CBS + TCAM activation via GDB.\n")
