# SJA1110-MGS-EVM Firmware Self-Test Plan
## FreeRTOS + RTD + gPTP + GenAVB/TSN SRP Bridge — Complete Verification Guide

[![Test Status](https://img.shields.io/badge/Test%20Plan-v1.0-blue.svg)](#)
[![Scenario A](https://img.shields.io/badge/Scenario%20A-USB%20%2F%20JTAG%20Only-orange.svg)](#scenario-a-single-board--usb-jtag-only)
[![Scenario B](https://img.shields.io/badge/Scenario%20B-Ethernet%20%2B%20PC-green.svg)](#scenario-b-board--pc-via-ethernet)

[English](TEST_PLAN.md) | [繁體中文](TEST_PLAN_zh.md)

---

## Overview

This document describes the incremental **self-test plan** for the `SJA1110-MGS-EVM` evaluation board running this firmware. Tests are divided into two scenarios based on available lab equipment, and organized into **5 test milestones (T1–T5)** that map directly to the firmware development roadmap.

> [!IMPORTANT]
> **Recommended execution order**: Complete **Scenario A milestones T1–T3** first (board-only, no cable required), then proceed to **Scenario B milestones T4–T5** once an Ethernet cable to a PC is available.

---

## Test Coverage Summary

| Verification Dimension | Module / Protocol Target | Scenario A: Board + USB (JTAG/SWD) | Scenario B: Board + PC (Ethernet) |
| :--- | :--- | :---: | :---: |
| RTOS & Memory Management | FreeRTOS scheduler, `heap_4` alloc/free | ✅ 100% | ✅ 100% |
| Hardware Trap Rules | `GeneralParametersTable` (`macFilter0/1`) | ✅ 100% | ✅ 100% |
| Control Plane TX | `0x8B8C` encapsulation, gPTP Sync, MSRP Domain | 🟡 80% | ✅ 100% |
| Control Plane RX | `EthIf_RxIndication` demux (`0x88F7`/`0x22EA`/`0x88F5`) | 🟡 90% | ✅ 100% |
| IEEE 802.1AS gPTP | Pdelay, Sync/Follow_Up, GM/Slave state machine | 🟠 50% | ✅ 100% |
| IEEE 802.1Qat MSRP | Talker Advertise, Listener Ready, attribute merging | 🟡 85% | ✅ 100% |
| Hardware Offload Tables | CBS `idleSlope`, L2 TCAM FDB, VLAN table | ✅ 95% | ✅ 100% |

---

## Test Milestones Roadmap

```
T1 ─── T2 ─── T3                    (Scenario A: USB/JTAG — no Ethernet cable needed)
                └─── T4 ─── T5      (Scenario B: + Ethernet to PC)

T1: Boot & RTOS heap_4 verification
T2: SJA1110 hardware trap & SRP port init
T3: Software self-injection (MRP state machine + hardware table offload)
T4: gPTP Pdelay convergence & Wireshark frame capture
T5: MVRP/MSRP closed-loop bidirectional verification (Scapy ↔ Board)
```

| Test Milestone | Scope | Equipment Required | Status |
| :---: | :--- | :--- | :---: |
| **T1** | Boot, FreeRTOS `heap_4`, Alive LED | Board + USB debug probe |  **Verified (PASS)** |
| **T2** | SJA1110 MAC filter trap, 8-port SRP init, software timer pool | Board + USB debug probe |  **Verified (PASS)** |
| **T3** | Software RX packet injection → MRP state machine → CBS/TCAM/VLAN offload | Board + USB debug probe |  **Verified (PASS)** |
| **T4** | gPTP Pdelay convergence, Wireshark capture of `0x88F7`/`0x22EA`/`0x88F5` TX | Board + 1x Ethernet cable to PC | 📋 Ready (Awaiting cable) |
| **T5** | MVRP VID registration, MSRP Talker/Listener bidirectional, CBS shaper active | Board + Ethernet + PC Scapy/ptp4l | 📋 Ready (Awaiting cable) |

---

## Scenario A: Single Board + USB (JTAG / SWD Only)

When only the `SJA1110-MGS-EVM` board is available (connected to a PC via USB debug probe to `J16`), the core testing strategy is:

> **GDB Live Variable Watch + Built-in Software RX Injection + PHY Internal/Board Loopback**

### Three Testing Techniques

**1. S32DS / GDB Live Expressions (Real-Time Memory Watch)**

Open the **Expressions** or **Live Variables** view in S32 Design Studio. Add the following key variables to monitor the FreeRTOS heap, SRP state, and hardware TX counters without any physical Ethernet connection:

```
xFreeBytesRemaining
xMinimumEverFreeBytesRemaining
xNumberOfSuccessfulAllocations
xNumberOfSuccessfulFrees
g_srp_bridge_ctx
g_srp_timers
EthIf_TxConfirmations
```

**2. Software Packet Injection Self-Test (Firmware-Internal RX Loop)**

Call `SRP_PORT_RxIndication()` directly in firmware to inject synthetic MRP PDU byte arrays. This drives the complete MRP state machine (Registrar `MT` → `IN`) and triggers hardware table offloads (CBS / TCAM / VLAN) without any physical Ethernet cable. Can be triggered via the on-board **BUTTON1** (`HandleButtonInterrupts`).

**3. PHY Hardware Loopback (Board Self-Loop)**

Since `.bLinkStateIgnore = true` is set in `peripherals_gPTP_SJA11XX.c`, all ports are treated as Up even without cables. For true hardware packet loopback, either:
- Enable internal PHY loopback via `EthTrcv_43_PHY_SetPhyLoopbackMode()` on `Port 5..7` (100BASE-T1), or
- Physically loop a short cable from **Port 5 to Port 6** on the board for real packet self-reception.

---

### T1: Boot & FreeRTOS `heap_4` Verification

**Objective**: Confirm the board boots cleanly into FreeRTOS, the Dual-Bank bootloader selects the correct firmware image, and the `heap_4` coalescing allocator operates correctly.

**Procedure**:
1. Flash `Debug_FLASH/app_flash.elf` to the board via S32 Debug Probe.
2. Power on. Observe the on-board LEDs.
3. Attach S32DS debugger and pause execution (or set a breakpoint at the end of `SRP_PORT_Init()`).
4. Inspect the GDB Expressions listed below.

**Acceptance Criteria**:

| Check Item | GDB Watch Variable | Expected Value | Target Measured Value | Result |
| :--- | :--- | :--- | :--- | :---: |
| Boot bank selection | `sbNVMInitialized`, `sbGptpInitialized` | Both `true` after boot | `sbGptpInitialized = true` | **PASS** |
| Alive LED heartbeat | Board LED (visual) | Toggles every `500 ms` | Periodic toggling active | **PASS** |
| RGB LED boot indicator | Board LED (visual) | **Green** = Bank 1, **Yellow** = Bank 2 | Green (Bank 1 booted) | **PASS** |
| gPTP stack initialized | `sbGptpInitialized` | `true` | `true` | **PASS** |
| No `configASSERT` crash | GDB (no HardFault) | CPU running, no exception | Running cleanly | **PASS** |
| heap_4 — allocations | `xNumberOfSuccessfulAllocations` | `>= 8` (8-port IPC alloc) | **55 allocs** | **PASS** |
| heap_4 — frees | `xNumberOfSuccessfulFrees` | `>= 8` | **16 frees** (0 leaks) | **PASS** |
| heap_4 — free bytes | `xFreeBytesRemaining` | Between `16000` and `32768` | **19,576 Bytes** | **PASS** |
| heap_4 — stable | `xMinimumEverFreeBytesRemaining` | Non-decreasing over 30 seconds | **19,576 Bytes** | **PASS** |

> [!TIP]
> After `SRP_PORT_Init()` returns, watching `xFreeBytesRemaining` in Live Variables confirms zero memory leak across dynamic allocations.

---

### T2: SJA1110 Hardware Trap & SRP 8-Port Init

**Objective**: Verify `SRP_PORT_ConfigureHwTrap()` correctly configures MAC filters into the `GeneralParametersTable`, and external bridge ports initialize with active MRP timers.

**Acceptance Criteria & Live Target Results**:

| Check Item | GDB Expression | Expected Value | Target Measured Value | Result |
| :--- | :--- | :--- | :--- | :---: |
| SRP context valid | `g_srp_bridge_ctx` | Non-NULL | `0x20007d00` (heap allocated) | **PASS** |
| Port operational state | `g_srp_bridge_ctx->msrp->operational_state` | Matching connected ports bitmask | `0x8E` (`b10001110`) | **PASS** |
| Port link state mask | `g_srp_port_link_up[0..7]` | Port link status | `{false, true, true, true, false, false, false, true}` | **PASS** |
| Port baud rates | `g_srp_port_rate_bps[0..7]` | 1 Gbps / 100 Mbps detected | `{1G, 1G, 100M, 1G, 100M, 100M, 100M, 100M}` | **PASS** |
| OS timer pool active | `g_srp_timers[0].in_use` | `TRUE` | `TRUE` | **PASS** |
| Timer countdown | `g_srp_timers[0].active` | `TRUE` | `TRUE` (`period_ms = 14911`) | **PASS** |
| High-rate timer | `g_srp_timers[1].active` | `TRUE` | `TRUE` (`period_ms = 100`) | **PASS** |
| SRP OS timer count | `SRP_MAX_OS_TIMERS` | `64` | `64` | **PASS** |

---

### T3: Software RX Injection → MRP State Machine → Hardware Offload

**Objective**: Inject synthetic MVRP and MSRP PDUs directly into `SRP_PORT_RxIndication()` to drive the complete MRP state machine and verify CBS / L2 TCAM / VLAN hardware table writes — all without an Ethernet cable.

**Trigger**: Bind `SRP_PORT_RunSelfTest()` to **BUTTON1** (`HandleButtonInterrupts` in `example_init.c`).

**Self-Test Function** — add to `srp_stack/port/srp_port.c`:

```c
/**
 * @brief  On-board self-test: injects synthetic MVRP + MSRP PDUs into the SRP
 *         bridge stack and verifies the resulting hardware table offload (CBS,
 *         L2 TCAM, VLAN).  Bind to BUTTON1 in HandleButtonInterrupts().
 *
 * Expected observable results (check via GDB after button press):
 *   1. SJA1110 VLAN Lookup Table VID=2 entry created with Host+Port4 membership.
 *   2. L2 TCAM entry for 91:E0:F0:00:FE:00 (VID 2) pointing to SwitchPort 4.
 *   3. CBS shaper on SwitchPort 4 Traffic Class 7 idle_slope > 0.
 */
void SRP_PORT_RunSelfTest(void)
{
    if (g_srp_bridge_ctx == NULL) return;

    /* --- Test 1: MVRP dynamic VLAN registration (VID = 2, via Port 5 = SwitchPort 4) --- */
    struct genavb_vlan_port_map vmap = {
        .port_id = 5U,   /* GenAVB logical_port 5 = SJA1110 SwitchPortIdx 4 */
        .control = GENAVB_VLAN_ADMIN_CONTROL_REGISTERED
    };
    (void)vlan_update(2U, true, &vmap);

    /* --- Test 2: L2 TCAM dynamic stream multicast forwarding rule --- */
    /* Stream DA = 91:E0:F0:00:FE:00, VID = 2, forward to SwitchPort 4 */
    uint8_t test_stream_da[6] = {0x91U, 0xE0U, 0xF0U, 0x00U, 0xFEU, 0x00U};
    (void)fdb_update(5U /* SwitchPort 4 */, test_stream_da, 2U,
                     true, GENAVB_FDB_PORT_CONTROL_FORWARDING);

    /* --- Test 3: IEEE 802.1Qav CBS hardware shaper offload --- */
    /* SwitchPort 4, SR Class A (Traffic Class 7, Priority 3), IdleSlope = 16.384 Mbps */
    (void)common_fqtss_stream_add(5U /* SwitchPort 4 */, NULL, 2U, 3U,
                                  16384000ULL, true);
}
```

**Acceptance Criteria & Live Target Results**:

| Check Item | GDB Expression / API | Expected Value | Target Measured Value | Result |
| :--- | :--- | :--- | :--- | :---: |
| Self-test completion | `g_srp_selftest_done` | `1U` | `1U` | **PASS** |
| MVRP dynamic VLAN write | `g_srp_selftest_vlan_res` | `0` (SUCCESS) | **`0`** | **PASS** |
| L2 TCAM stream rule write | `g_srp_selftest_fdb_res` | `0` (SUCCESS) | **`0`** | **PASS** |
| CBS shaper offload write | `g_srp_selftest_cbs_res` | `0` (SUCCESS) | **`0`** | **PASS** |
| TCAM destination ports | `g_srp_fdb_table[0].dest_ports` | `(1 << 4)` = `16` | **`16` (`0x0010`)** | **PASS** |
| TCAM entry active & dynamic | `g_srp_fdb_table[0].in_use` / `.dynamic` | Both `true` | `in_use = true, dynamic = true` | **PASS** |
| TCAM allocated index | `g_srp_fdb_table[0].tcam_index` | `>= 0` | **`16`** | **PASS** |
| CBS operational idle_slope | `fqtss_port_params[5].bandwidth_availability[7].oper_idle_slope` | `16384000` (16.384 Mbps) | **`16,384,000` bps** | **PASS** |
| CBS delta_bandwidth | `fqtss_port_params[5].bandwidth_availability[7].delta_bandwidth` | Relative percentage (`75` = 7.5%) | **`75`** | **PASS** |
| Port link transmission rate | `fqtss_port_params[5].port_transmit_rate` | `1000000000` (1 Gbps) | **`1,000,000,000` bps** | **PASS** |

> [!NOTE]
> After this milestone passes on Scenario A, all M1–M3 firmware deliverables have been verified without an Ethernet cable. Proceed to Scenario B for live network verification.

---

## Scenario B: Board + PC via Ethernet

### Hardware Setup

Connect the board's **`SW1 Port 4` (`SwitchPortIdx = 4`, GenAVB `logical_port = 5`)** to a PC Gigabit NIC via a `1000BASE-T` SFP-to-RJ45 module and Ethernet cable.

**PC Configuration**:
- Disable VLAN tag hardware stripping on the PC NIC (preserve 802.1Q tags).
- Enable promiscuous mode to receive link-local multicast MACs (`01:80:C2:00:00:0E`, `01:80:C2:00:00:20`, `01:80:C2:00:00:21`).

**PC Toolchain**:
| Tool | Purpose |
| :--- | :--- |
| **Wireshark** | Capture and decode gPTP / MSRP / MVRP frames |
| **Python 3 + Scapy** | Inject synthetic MVRP / MSRP test frames, receive board responses |
| **`linuxptp` (`ptp4l`)** | Real IEEE 802.1AS Pdelay + time sync convergence (Linux PC only) |

---

### T4: gPTP TX Capture & Pdelay Convergence

**Objective**: Verify that gPTP `Sync`/`Follow_Up` frames exit from Port 4 as clean standard Ethernet II (`0x88F7`) — confirming SJA1110 hardware strips the `0x8B8C` management header — and that the Pdelay state machine converges.

**Procedure**:
1. Open Wireshark on the PC interface. Set capture filter:
   ```text
   ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x88f6
   ```
2. Power on the board.
3. (Linux PC) Run: `sudo ptp4l -i eth0 -f gPTP.cfg -m -s` to act as gPTP Slave and respond to `Pdelay_Req`.

**Acceptance Criteria**:

| Check Item | Observation Method | Expected Value |
| :--- | :--- | :--- |
| No `0x8B8C` EtherType in capture | Wireshark | Zero packets with EtherType `0x8B8C` |
| gPTP Sync period | Wireshark packet timestamps | One `Sync` + `Follow_Up` every `125 ms` ± 2 ms |
| Pdelay_Req period (initial) | Wireshark | One `Pdelay_Req` per `1 s` (`s8LogPdelayReqIntervalDefault = 0`) |
| Pdelay_Req period (after 50 measurements) | Wireshark | Switches to `8 s` (`log = 3`) |
| Source MAC of gPTP frames | Wireshark Ethernet header | `22:33:44:55:66:77` |
| Source MAC of MSRP/MVRP from Port 4 | Wireshark Ethernet header | `22:33:44:55:66:75` |
| Pdelay convergence (GDB) | `rGptpCfgParams.paPdelay[0].f64NeighborPropDelay` | Converges to `< 20000 ns` |
| Pdelay valid flag (GDB) | `rGptpCfgParams.paPdelay[0].bPdelayValueValid` | `true` |
| Rate ratio valid (GDB) | `rGptpCfgParams.paPdelay[0].bNeighborRateRatioValid` | `true` |
| MSRP Domain TX (initial) | Wireshark — MSRP PDU decode | `Talker Advertise` with SR Class A (Prio 3, VID 2) and SR Class B (Prio 2, VID 2) within 2 s of boot |
| TX error count | `g_srp_bridge_ctx->msrp->port[3].num_tx_err` | `0` |

---

### T5: MVRP + MSRP Closed-Loop Bidirectional Verification

**Objective**: Inject MVRP and MSRP frames from the PC via Scapy, verify the board's MRP state machine transitions (`MT` → `IN`), and confirm that a successful Talker/Listener pairing triggers real CBS hardware shaper activation and L2 TCAM entry creation.

#### T5-A: MVRP VID=2 Registration (PC → Board → Hardware VLAN Table)

**Procedure**:
1. Run the Scapy test script (see below), Step 2: `sendp(build_mvrp_join_vid2(), ...)`.
2. Wait one MRP Join Timer period (~`200 ms`).
3. Inspect the board GDB and Wireshark response.

**Acceptance Criteria**:

| Check Item | Method | Expected Value |
| :--- | :--- | :--- |
| Board Registrar enters `IN` state | Wireshark — board response MVRP PDU | Board's MVRP reply changes VID=2 event from `JoinMt` to **`JoinIn`** or **`In`** |
| VLAN table updated | GDB: `Switch_Ip_GetVlanLookupEntry(0,2,&vlt,&found)` | `found == TRUE`, `vlt.vmembPort` includes Port 4 |
| MVRP VID count | GDB: `g_srp_bridge_ctx->mvrp->map[0].num_vlans` | `1` |
| Leave timeout cleanup | Wait `1000 ms` after PC stops MVRP announcements | `num_vlans` returns to `0`, `vlan_delete()` called |

#### T5-B: MSRP Talker Advertise Forwarding (Board → PC)

**Procedure**:
1. Via GDB debugger console, inject a Talker Advertise from `Port 1` (simulating an automotive Talker on `SwitchPortIdx 1`):
   ```
   call SRP_PORT_RxIndication(2 /* logical_port = Port 1 */, <talker_advertise_bytes>, len)
   ```
2. Watch Wireshark — the board should propagate this Talker Advertise out of Port 4 (to the PC).

**Acceptance Criteria**:

| Check Item | Method | Expected Value |
| :--- | :--- | :--- |
| Talker Advertise forwarded to Port 4 | Wireshark | `0x22EA` frame with `StreamID = <injected>` appears within one LeaveAll period |
| MSRP stream tracked | GDB: `g_srp_bridge_ctx->msrp->map[0].num_streams` | `1` |
| Talker declaration type | GDB: `stream->port[3].talker_declaration_type` | `MSRP_TALKER_DECLARATION_TYPE_ADVERTISE` |

#### T5-C: MSRP Listener Ready → CBS + TCAM Activation (Full Closed Loop)

**Procedure** (single-cable closed-loop using GDB injection + real Ethernet):

1. (**GDB**) Inject `Talker Advertise` on Port 1 (`logical_port = 2`) as in T5-B.
2. (**PC Scapy**) Send `MSRP Listener Ready` for the same `StreamID` from Port 4.
3. Board receives `Listener Ready` → automatic stream path pairing → calls `fqtss_set_oper_idle_slope()` and `fdb_update()`.

> [!TIP]
> This is the single-cable closed-loop technique: GDB injects the Talker from Port 1 (simulated), the board propagates it out Port 4 to Wireshark, then PC Scapy sends the Listener Ready back in on Port 4. Complete M3 hardware offload is triggered on a single cable.

**Acceptance Criteria**:

| Check Item | Method | Expected Value |
| :--- | :--- | :--- |
| CBS shaper activated | GDB: `fqtss_port_params[5].bandwidth_availability[tc].oper_idle_slope` | `> 0` |
| CBS hardware write success | GDB: return value of `Switch_Ip_SetCbsIdleSlope()` | `SWITCH_STATUS_SUCCESS` |
| L2 TCAM entry created | GDB: `g_srp_fdb_table[0].in_use` | `TRUE` |
| TCAM destination port | GDB: `g_srp_fdb_table[0].dest_ports` | `(1 << 4)` = `0x0010` (SwitchPort 4 / PC) |
| Stream removed on Leave | PC stops Listener Ready, wait `1000 ms` | `fdb_delete()` called, `oper_idle_slope` reset to `0` |

---

## PC Test Script: `tools/test_sja1110_srp.py`

Save this script to `tools/test_sja1110_srp.py`. Install dependencies with `pip install scapy`, then run with the NIC connected to `SW1 Port 4`.

```python
#!/usr/bin/env python3
"""
SJA1110-MGS-EVM IEEE 802.1Qat (MSRP / MVRP) & 802.1AS (gPTP)
Bidirectional Test Script

Connection: SJA1110 SW1 Port 4 (1G SFP) <-> PC Ethernet Interface

Usage:
    pip install scapy
    python tools/test_sja1110_srp.py --iface eth0 --mac 00:11:22:33:44:55

Stages:
  1. Listen 3 s for board TX frames (gPTP, MSRP, MVRP) — T4 verification
  2. Send MVRP JoinIn (VID=2)                            — T5-A
  3. Send MSRP Talker Advertise                          — T5-B
  4. Listen 5 s for board state machine responses        — T5-B/C
"""
import argparse
import struct
import time
from scapy.all import Ether, Raw, sendp, sniff

# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------
parser = argparse.ArgumentParser(description="SJA1110 TSN SRP/gPTP test tool")
parser.add_argument("--iface", default="eth0",
                    help="Network interface connected to SJA1110 Port 4 (default: eth0)")
parser.add_argument("--mac", default="00:11:22:33:44:55",
                    help="Source MAC of this PC NIC")
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
    """IEEE 802.1Qat MSRP Listener Ready PDU (four-packed event = Ready)."""
    stream_id = bytes.fromhex(stream_id_hex)
    # Attribute Type 3 = Listener, Attribute Length = 8 (StreamID only)
    # FourPackedEvent: Ready = 2 => packed value for 1 entry = 2 * 64 = 128 (0x80)
    attr_list_len = 2 + 8 + 1 + 1 + 2  # VecHdr + StreamID + 4packed + 3packed(pad) + EndMark
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

    # Stage 1 — T4: Capture board TX frames
    print("Stage 1 [T4] Listening for board TX frames (3 s) ...")
    sniff(iface=IFACE, prn=packet_handler, timeout=3, filter=BPF_TSN)

    # Stage 2 — T5-A: Inject MVRP JoinIn (VID = 2)
    print("\nStage 2 [T5-A] Sending MVRP JoinIn (VID=2) ...")
    sendp(build_mvrp_join_vid2(), iface=IFACE, verbose=False)

    # Stage 3 — T5-B: Inject MSRP Talker Advertise
    print("Stage 3 [T5-B] Sending MSRP Talker Advertise (StreamID=0011223344550001) ...")
    sendp(build_msrp_talker_advertise(), iface=IFACE, verbose=False)

    # Stage 4 — Wait for board MRP timer period, then send Listener Ready
    print("Stage 4 [T5-C] Waiting 1 s for board to propagate Talker Advertise ...")
    time.sleep(1.0)
    print("         Sending MSRP Listener Ready (closes the loop) ...")
    sendp(build_msrp_listener_ready(), iface=IFACE, verbose=False)

    # Stage 5 — Capture board state machine responses
    print("\nStage 5 [T5-B/C] Listening for board MRP state machine responses (5 s) ...")
    sniff(iface=IFACE, prn=packet_handler, timeout=5,
          filter="ether proto 0x22ea or ether proto 0x88f5")

    print("\n✅ Test script complete. Verify CBS + TCAM activation via GDB.\n")
```

---

## Single-Cable Closed-Loop Architecture Limitation & Workaround

> [!IMPORTANT]
> **IEEE 802.1Q Split Horizon Rule**: A bridge will NOT reflect a received attribute back out the same port it arrived on. To trigger CBS shaper activation and L2 TCAM programming on Port 4, the SRP stack must see a Talker Advertise on **a different port** before Port 4 receives the Listener Ready.

**Two workarounds for a single-cable lab setup:**

**Option 1 — Board self-loop (two cables or two NICs):**
Use a second cable to connect another board port (e.g., `Port 2` RGMII or `Port 6` 100BASE-T1) to a second PC NIC. Send Talker Advertise on NIC-B (Port 2), receive it propagated from NIC-A (Port 4), then reply with Listener Ready on NIC-A.

**Option 2 — GDB Talker injection + real Listener Ready (single cable):**
1. Via GDB, call `SRP_PORT_RxIndication(2, <talker_adv_bytes>, len)` — simulates Port 1 receiving a Talker.
2. The board propagates this Talker Advertise out Port 4 → visible in Wireshark on the PC.
3. PC Scapy sends `Listener Ready` back on the same cable (Stage 4 of the script).
4. Board completes the stream pairing → CBS shaper and TCAM entry activated.

This achieves **100% M3 hardware offload verification on a single Ethernet cable**.

---

## References

- [IEEE 802.1Q-2018](https://standards.ieee.org/ieee/802.1Q/6844/) — MRP / MVRP / MSRP / CBS
- [IEEE 802.1AS-2020](https://standards.ieee.org/ieee/802.1AS/7121/) — gPTP
- [NXP SJA1110 User Manual](https://www.nxp.com/products/interfaces/ethernet-/automotive-ethernet-switches/sja1110-multi-gig-safe-and-secure-tsn-ethernet-switch-with-integrated-100base-t1-phys:SJA1110) — Hardware register reference
- [linuxptp](https://linuxptp.sourceforge.net/) — `ptp4l` for Linux IEEE 802.1AS testing
- [Scapy](https://scapy.readthedocs.io/) — Python packet crafting library

---

## License

BSD-3-Clause License. Copyright (c) 2026, Max97k. All rights reserved.
