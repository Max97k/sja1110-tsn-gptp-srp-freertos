#!/usr/bin/env python3
"""
SJA1110 TSN & gPTP FreeRTOS - Hardware Telemetry & Live Wireshark Bridge
Connects SJA1110 Port 4 (1GbE SFP) <-> PC Ethernet NIC
Streams real-time Wireshark packet dissection and MCU telemetry over WebSocket to Web Dashboard.
"""
import asyncio
import json
import os
import struct
import sys
import threading
import time
from aiohttp import web
import websockets
from scapy.all import Ether, Raw, conf, sendp, sniff

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

# ---------------------------------------------------------------------------
# Network Interface Auto-Detection
# ---------------------------------------------------------------------------
def detect_interface():
    for iface in conf.ifaces.values():
        if "Realtek" in iface.description or "Ethernet" in iface.name:
            return iface.name, iface.mac
    return "Ethernet", "a0:ad:9f:2d:fe:84"

IFACE, PC_MAC = detect_interface()
PC_CLOCK_ID = bytes.fromhex(PC_MAC.replace(":", "")[:6] + "fffe" + PC_MAC.replace(":", "")[6:])

print(f"[*] SJA1110 Telemetry Bridge initialized")
print(f"    - Sniffing interface: {IFACE}")
print(f"    - PC Source MAC:      {PC_MAC}")

# ---------------------------------------------------------------------------
# Global Telemetry & Statistics State
# ---------------------------------------------------------------------------
start_time = time.time()
packet_counter = 0
connected_ws_clients = set()
packet_history = []
MAX_HISTORY = 100

stats = {
    "uptime_sec": 0,
    "total_packets": 0,
    "gptp_sync": 0,
    "gptp_fup": 0,
    "gptp_pdelay_req": 0,
    "gptp_pdelay_resp": 0,
    "msrp_count": 0,
    "mvrp_count": 0,
    "leak_8b8c": 0,
    "probe_connected": False,
    "telemetry_source": "Wire-Derived Only (No MCU Probe Connected)",
    "pdelay_ns": None,
    "free_heap_bytes": None,
    "min_free_heap_bytes": None,
    "gptp_initialized": False,
    "vlan_offload": "UNVERIFIED (Connect Probe / Awaiting MVRP)",
    "tcam_offload": "UNVERIFIED (Connect Probe / Awaiting MSRP)",
    "cbs_slope_bps": None,
    "port_links": [False, False, False, True, False, False, False, False],
    "port_rates": ["1G SGMII", "1G RGMII", "100M SGMII", "1G SFP (PC)", "100BASE-T1", "100BASE-T1", "100BASE-T1", "100M MII"]
}

FREEMASTER_RPC_URL = os.environ.get("FREEMASTER_RPC_URL", "ws://127.0.0.1:8090")


async def poll_mcu_probe_once():
    """Attempt to read live MCU SRAM telemetry (`g_srp_telemetry` & `rGptpCfgParams`)
    from FreeMASTER Lite JSON-RPC server (default ws://127.0.0.1:8090).
    Leaves telemetry fields as None/UNVERIFIED if no probe is connected.
    """
    try:
        async with websockets.connect(FREEMASTER_RPC_URL, open_timeout=0.4, close_timeout=0.2) as rpc:
            req = {"jsonrpc": "2.0", "id": 1, "method": "ReadVariable", "params": {"name": "g_srp_telemetry.free_heap_bytes"}}
            await rpc.send(json.dumps(req))
            resp = json.loads(await asyncio.wait_for(rpc.recv(), timeout=0.4))
            if "result" in resp and resp["result"].get("success"):
                stats["probe_connected"] = True
                stats["telemetry_source"] = "Live MCU Probe (FreeMASTER JSON-RPC)"
                stats["free_heap_bytes"] = int(resp["result"]["data"])
                for var_name, key in [
                    ("g_srp_telemetry.min_free_heap_bytes", "min_free_heap_bytes"),
                    ("g_srp_telemetry.port4_cbs_slope_bps", "cbs_slope_bps"),
                ]:
                    await rpc.send(json.dumps({"jsonrpc": "2.0", "id": 2, "method": "ReadVariable", "params": {"name": var_name}}))
                    r2 = json.loads(await asyncio.wait_for(rpc.recv(), timeout=0.4))
                    if "result" in r2 and r2["result"].get("success"):
                        stats[key] = int(r2["result"]["data"])

                # Read active_vlan_id, active_tcam_dest_ports, and port_link_mask
                await rpc.send(json.dumps({"jsonrpc": "2.0", "id": 3, "method": "ReadVariable", "params": {"name": "g_srp_telemetry.active_vlan_id"}}))
                rv = json.loads(await asyncio.wait_for(rpc.recv(), timeout=0.4))
                if "result" in rv and rv["result"].get("success"):
                    vid = int(rv["result"]["data"])
                    stats["vlan_offload"] = f"VID={vid} ACTIVE (Switch_Ip VLAN Table)" if vid > 0 else "IDLE (No Dynamic MVRP VID)"

                await rpc.send(json.dumps({"jsonrpc": "2.0", "id": 4, "method": "ReadVariable", "params": {"name": "g_srp_telemetry.active_tcam_dest_ports"}}))
                rt = json.loads(await asyncio.wait_for(rpc.recv(), timeout=0.4))
                if "result" in rt and rt["result"].get("success"):
                    dports = int(rt["result"]["data"])
                    stats["tcam_offload"] = f"ACTIVE (DestMask=0x{dports:04X})" if dports > 0 else "IDLE (No Active Stream FDB)"

                await rpc.send(json.dumps({"jsonrpc": "2.0", "id": 5, "method": "ReadVariable", "params": {"name": "g_srp_telemetry.port_link_mask"}}))
                rl = json.loads(await asyncio.wait_for(rpc.recv(), timeout=0.4))
                if "result" in rl and rl["result"].get("success"):
                    lmask = int(rl["result"]["data"])
                    stats["port_links"] = [bool(lmask & (1 << i)) for i in range(8)]
                return True
    except Exception:
        stats["probe_connected"] = False
        stats["telemetry_source"] = "Wire-Derived Only (No MCU Probe Connected)"
    return False

# ---------------------------------------------------------------------------
# Frame Dissectors & Builders
# ---------------------------------------------------------------------------
def dissect_gptp(raw: bytes):
    if len(raw) < 34:
        return "Malformed gPTP", "gptp-other", {}
    msg_type = raw[0] & 0x0F
    seq = int.from_bytes(raw[30:32], "big")
    log_int = struct.unpack("!b", raw[33:34])[0]
    sec = int.from_bytes(raw[34:40], "big") if len(raw) >= 40 else 0
    nsec = int.from_bytes(raw[40:44], "big") if len(raw) >= 44 else 0

    types = {
        0: ("Sync", "gptp-sync", f"SequenceID={seq}, LogInterval={log_int} (125ms)"),
        8: ("Follow_Up", "gptp-fup", f"SequenceID={seq}, PreciseOriginTimestamp={sec}s+{nsec}ns"),
        2: ("Pdelay_Req", "gptp-pdelay", f"SequenceID={seq}, RequestingPort=Port 4"),
        3: ("Pdelay_Resp", "gptp-pdelay", f"SequenceID={seq}, ReceiptTimestamp={sec}s+{nsec}ns"),
        10: ("Pdelay_Resp_Follow_Up", "gptp-pdelay", f"SequenceID={seq}, EgressTimestamp={sec}s+{nsec}ns")
    }
    proto, tag, info = types.get(msg_type, (f"gPTP (Type {msg_type})", "gptp-other", f"Seq={seq}"))
    fields = {
        "MessageType": proto,
        "VersionPTP": raw[1] & 0x0F,
        "MessageLength": int.from_bytes(raw[2:4], "big"),
        "DomainNumber": raw[4],
        "Flags": f"0x{int.from_bytes(raw[6:8], 'big'):04X}",
        "SourcePortIdentity": raw[20:30].hex(),
        "SequenceID": seq,
        "LogMessageInterval": log_int,
        "Timestamp": f"{sec}.{nsec:09d} s" if len(raw) >= 44 else "N/A"
    }
    return proto, tag, info, fields


def dissect_msrp(raw: bytes):
    if len(raw) < 4:
        return "MSRP", "msrp", "PDU", {}
    attr_type = raw[1]
    attr_len = raw[2]
    type_names = {1: "Talker Advertise", 2: "Talker Failed / LeaveAll", 3: "Listener Ready", 4: "Domain"}
    proto = f"MSRP {type_names.get(attr_type, f'Type {attr_type}')}"
    info = f"AttributeType={attr_type}, Length={attr_len}"
    if attr_type == 2:
        info += " (Periodic LeaveAll Event Triggered)"
    fields = {
        "ProtocolVersion": raw[0],
        "AttributeType": attr_type,
        "AttributeLength": attr_len,
        "AttributeListLength": int.from_bytes(raw[3:5], "big") if len(raw) >= 5 else 0
    }
    return proto, "msrp", info, fields


def dissect_mvrp(raw: bytes):
    proto = "MVRP"
    if len(raw) < 7:
        return proto, "mvrp", f"Short/LeaveAll MVRP PDU ({len(raw)}B)", {"RawBytes": raw.hex()}
    proto_ver = raw[0]
    attr_type = raw[1]
    attr_len = raw[2]
    vec_hdr = int.from_bytes(raw[3:5], "big")
    lva = (vec_hdr >> 13) & 0x07
    num_vals = vec_hdr & 0x1FFF
    vid = int.from_bytes(raw[5:7], "big") if attr_len == 2 and len(raw) >= 7 else 0
    ev_byte = raw[7] if len(raw) >= 8 else 0
    ev0 = ev_byte // 36
    ev_names = {0: "New", 1: "JoinIn", 2: "In", 3: "JoinMt", 4: "Mt", 5: "Lv"}
    ev_str = f"{ev_names.get(ev0, f'Evt({ev0})')} (0x{ev_byte:02X})"
    info = f"VID={vid}, Event={ev_str}, NumValues={num_vals}, LeaveAll={lva}"
    fields = {
        "ProtocolVersion": proto_ver,
        "AttributeType": f"VID ({attr_type})",
        "AttributeLength": attr_len,
        "LeaveAllEvent": lva,
        "NumberOfValues": num_vals,
        "FirstValue_VID": vid,
        "ThreePackedEvent": ev_str,
    }
    return proto, "mvrp", info, fields


def format_hex_dump(data: bytes) -> str:
    lines = []
    for i in range(0, min(len(data), 64), 16):
        chunk = data[i:i+16]
        hex_str = " ".join(f"{b:02x}" for b in chunk)
        ascii_str = "".join(chr(b) if 32 <= b <= 126 else "." for b in chunk)
        lines.append(f"{i:04x}  {hex_str:<48}  |{ascii_str}|")
    return "\n".join(lines)


# ---------------------------------------------------------------------------
# gPTP Active Pdelay Responder
# ---------------------------------------------------------------------------
def respond_pdelay_req(raw: bytes):
    if len(raw) < 34:
        return
    seq = int.from_bytes(raw[30:32], "big")
    req_port_id = raw[20:30]

    t2_total_ns = time.time_ns()
    t2_sec, t2_nsec = divmod(t2_total_ns, 1_000_000_000)

    resp_hdr = struct.pack("!BBHBBHQIH10sHBB",
        0x13, 0x02, 54, 0x00, 0x00, 0x0208, 0, 0, 0,
        PC_CLOCK_ID[:8] + b"\x00\x01", seq, 0x05, 0x7F
    )
    t2_bytes = struct.pack("!Q", t2_sec)[2:] + struct.pack("!I", t2_nsec)
    resp_payload = resp_hdr + t2_bytes + req_port_id
    resp_pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x88F7) / Raw(load=resp_payload)
    sendp(resp_pkt, iface=IFACE, verbose=False)

    t3_total_ns = max(time.time_ns(), t2_total_ns + 1000)
    t3_sec, t3_nsec = divmod(t3_total_ns, 1_000_000_000)

    fup_hdr = struct.pack("!BBHBBHQIH10sHBB",
        0x1A, 0x02, 54, 0x00, 0x00, 0x0008, 0, 0, 0,
        PC_CLOCK_ID[:8] + b"\x00\x01", seq, 0x05, 0x7F
    )
    t3_bytes = struct.pack("!Q", t3_sec)[2:] + struct.pack("!I", t3_nsec)
    fup_payload = fup_hdr + t3_bytes + req_port_id
    fup_pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x88F7) / Raw(load=fup_payload)
    sendp(fup_pkt, iface=IFACE, verbose=False)

    stats["gptp_pdelay_resp"] += 1


# ---------------------------------------------------------------------------
# Packet Processing Callback
# ---------------------------------------------------------------------------
loop = None

def broadcast_packet(pkt_info):
    if loop and connected_ws_clients:
        msg = json.dumps({"type": "packet", "data": pkt_info})
        for ws in list(connected_ws_clients):
            asyncio.run_coroutine_threadsafe(ws.send_str(msg), loop)


def on_packet_received(pkt):
    global packet_counter
    if Ether not in pkt:
        return

    et  = pkt[Ether].type
    src = pkt[Ether].src
    dst = pkt[Ether].dst
    is_outbound = (src.lower() == PC_MAC.lower())

    if et not in (0x88F7, 0x22EA, 0x88F5, 0x8B8C):
        return

    packet_counter += 1
    stats["total_packets"] = packet_counter
    rel_time = round(time.time() - start_time, 3)

    raw_bytes = bytes(pkt[Raw]) if Raw in pkt else b""
    proto = f"0x{et:04X}"
    tag = "other"
    info = ""
    fields = {}

    if et == 0x88F7:
        proto, tag, info, fields = dissect_gptp(raw_bytes)
        if not is_outbound:
            stats["gptp_initialized"] = True
        if "Sync" in proto:
            stats["gptp_sync"] += 1
        elif "Follow_Up" in proto:
            stats["gptp_fup"] += 1
        elif "Pdelay_Req" in proto:
            stats["gptp_pdelay_req"] += 1
            if not is_outbound:
                respond_pdelay_req(raw_bytes)

    elif et == 0x22EA:
        proto, tag, info, fields = dissect_msrp(raw_bytes)
        stats["msrp_count"] += 1

    elif et == 0x88F5:
        proto, tag, info, fields = dissect_mvrp(raw_bytes)
        stats["mvrp_count"] += 1

    elif et == 0x8B8C:
        stats["leak_8b8c"] += 1
        proto = "0x8B8C LEAK"
        tag = "leak"
        info = "ALERT: Switch management header exposed on external port!"

    pkt_obj = {
        "no": packet_counter,
        "time": f"{rel_time:.3f}",
        "protocol": proto,
        "tag": tag,
        "src": src,
        "dst": dst,
        "len": len(pkt),
        "info": info,
        "is_outbound": is_outbound,
        "fields": fields,
        "hex_dump": format_hex_dump(raw_bytes if raw_bytes else bytes(pkt))
    }

    packet_history.append(pkt_obj)
    if len(packet_history) > MAX_HISTORY:
        packet_history.pop(0)

    broadcast_packet(pkt_obj)


def sniffer_thread_func():
    print("[*] Background Scapy sniffer thread started...")
    sniff(iface=IFACE, prn=on_packet_received, store=False,
          filter="ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x8b8c")


# ---------------------------------------------------------------------------
# Action Injections (REST Endpoints)
# ---------------------------------------------------------------------------
def inject_mvrp_join():
    pdu = struct.pack("!BBBHBB", 0x00, 0x01, 0x02, 0x0001, 0x00, 0x02) + struct.pack("!BHH", 0x24, 0x0000, 0x0000)
    pkt = Ether(dst="01:80:c2:00:00:21", src=PC_MAC, type=0x88F5) / Raw(load=pdu)
    sendp(pkt, iface=IFACE, verbose=False)
    return {"status": "ok", "msg": "MVRP JoinIn (VID=2) injected"}


def inject_msrp_talker():
    # First send MSRP Domain (Class A: SRclassID=6, Priority=3, VID=2) to clear Domain Boundary Port on Port 4
    dom_pdu = struct.pack("!BBBHHBBHBHH", 0x00, 0x04, 4, 9, 0x0001, 6, 3, 2, 0x24, 0, 0)
    dom_pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=dom_pdu)
    sendp(dom_pkt, iface=IFACE, verbose=False)

    stream_id = bytes.fromhex("0011223344550001")
    stream_da = bytes.fromhex("91e0f000fe00")
    first_val = stream_id + stream_da + struct.pack("!HHHBI", 2, 128, 1, (3 << 5) | (1 << 4), 1000)
    attr_list_len = 2 + 25 + 1 + 2
    pdu = struct.pack("!BBBHH", 0x00, 0x01, 25, attr_list_len, 0x0001) + first_val + struct.pack("!BHH", 36, 0, 0)
    pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)
    sendp(pkt, iface=IFACE, verbose=False)
    return {"status": "ok", "msg": "MSRP Domain (Class A) + Talker Advertise (StreamID=0011223344550001, DA=91:E0:F0:00:FE:00) injected"}


def inject_msrp_listener():
    stream_id = bytes.fromhex("0011223344550001")
    attr_list_len = 2 + 8 + 1 + 1 + 2
    # ThreePackedEvent = JoinIn (0x24), FourPackedEvent = Ready (0x80)
    pdu = struct.pack("!BBBHH", 0x00, 0x03, 8, attr_list_len, 0x0001) + stream_id + struct.pack("!BBHH", 0x24, 0x80, 0, 0)
    pkt = Ether(dst="01:80:c2:00:00:0e", src=PC_MAC, type=0x22EA) / Raw(load=pdu)
    sendp(pkt, iface=IFACE, verbose=False)
    return {"status": "ok", "msg": "MSRP Listener Ready (StreamID=0011223344550001) injected"}


# ---------------------------------------------------------------------------
# HTTP & WebSocket Server Handlers (aiohttp)
# ---------------------------------------------------------------------------
async def ws_handler(request):
    ws = web.WebSocketResponse()
    await ws.prepare(request)
    connected_ws_clients.add(ws)
    print(f"[*] Dashboard client connected via WebSocket ({len(connected_ws_clients)} active)")

    # Send initial snapshot & recent packet history
    await ws.send_str(json.dumps({"type": "init", "stats": stats, "history": packet_history}))

    try:
        async for msg in ws:
            pass
    finally:
        connected_ws_clients.remove(ws)
        print(f"[*] Dashboard client disconnected ({len(connected_ws_clients)} active)")
    return ws


async def api_stats(request):
    stats["uptime_sec"] = int(time.time() - start_time)
    return web.json_response(stats)


async def api_inject_mvrp(request):
    res = inject_mvrp_join()
    return web.json_response(res)


async def api_inject_talker(request):
    res = inject_msrp_talker()
    return web.json_response(res)


async def api_inject_listener(request):
    res = inject_msrp_listener()
    return web.json_response(res)


async def api_selftest(request):
    inject_mvrp_join()
    await asyncio.sleep(0.1)
    inject_msrp_talker()
    await asyncio.sleep(0.1)
    inject_msrp_listener()
    # If FreeMASTER JSON-RPC probe is connected, trigger MCU g_srp_run_selftest = 1
    try:
        async with websockets.connect(FREEMASTER_RPC_URL, open_timeout=0.4, close_timeout=0.2) as rpc:
            await rpc.send(json.dumps({"jsonrpc": "2.0", "id": 99, "method": "WriteVariable", "params": {"name": "g_srp_run_selftest", "value": 1}}))
            await asyncio.wait_for(rpc.recv(), timeout=0.4)
    except Exception:
        pass
    await poll_mcu_probe_once()
    return web.json_response({"status": "ok", "probe_connected": stats["probe_connected"], "msg": "Test frames injected on wire (and MCU selftest triggered if probe attached)"})


async def telemetry_broadcast_loop():
    while True:
        await asyncio.sleep(1.0)
        stats["uptime_sec"] = int(time.time() - start_time)
        await poll_mcu_probe_once()
        if connected_ws_clients:
            msg = json.dumps({"type": "stats", "data": stats})
            for ws in list(connected_ws_clients):
                try:
                    await ws.send_str(msg)
                except Exception:
                    pass


# ---------------------------------------------------------------------------
# Main Application Entrypoint
# ---------------------------------------------------------------------------
def main():
    global loop
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)

    sniff_thread = threading.Thread(target=sniffer_thread_func, daemon=True)
    sniff_thread.start()

    app = web.Application()
    app.router.add_get("/ws", ws_handler)
    app.router.add_get("/api/stats", api_stats)
    app.router.add_post("/api/inject_mvrp", api_inject_mvrp)
    app.router.add_post("/api/inject_talker", api_inject_talker)
    app.router.add_post("/api/inject_listener", api_inject_listener)
    app.router.add_post("/api/selftest", api_selftest)

    # Also serve static web dashboard directly on port 8091
    web_dir = os.path.join(os.path.dirname(__file__), "web")
    if os.path.exists(web_dir):
        app.router.add_static("/", web_dir, show_index=True)

    asyncio.ensure_future(telemetry_broadcast_loop(), loop=loop)

    print("[+] Telemetry & Wireshark Bridge Server running on http://127.0.0.1:8091")
    print("    - WebSocket: ws://127.0.0.1:8091/ws")
    print("    - Web Dashboard: http://127.0.0.1:8091/index.html")

    web.run_app(app, host="127.0.0.1", port=8091, loop=loop)


if __name__ == "__main__":
    main()
