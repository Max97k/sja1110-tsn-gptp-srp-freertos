# NXP SJA1110 TSN Switch Firmware: IEEE 802.1AS gPTP & IEEE 802.1Qat SRP (MSRP / MVRP / MMRP) Bridge on FreeRTOS

[![Target: NXP SJA1110](https://img.shields.io/badge/Target-NXP%20SJA1110%20(Silicon%20E)-005a9c.svg)](https://www.nxp.com/products/interfaces/ethernet-/automotive-ethernet-switches/sja1110-multi-gig-safe-and-secure-tsn-ethernet-switch-with-integrated-100base-t1-phys:SJA1110)
[![Core: Arm Cortex-M7](https://img.shields.io/badge/Core-Arm%C2%AE%20Cortex%C2%AE--M7%20%40%20200MHz-blue.svg)](https://www.arm.com/products/silicon-ip-cpu/cortex-m/cortex-m7)
[![RTOS: FreeRTOS 11.1](https://img.shields.io/badge/RTOS-FreeRTOS%2011.1.0-brightgreen.svg)](https://www.freertos.org)
[![RTD: 0.9.0 (AUTOSAR 4.4)](https://img.shields.io/badge/RTD-0.9.0%20(AUTOSAR%C2%AE%204.4)-orange.svg)](https://www.nxp.com)
[![TSN: IEEE 802.1AS + 802.1Qat + 802.1Qav](https://img.shields.io/badge/TSN-802.1AS%20gPTP%20%7C%20802.1Qat%20SRP%20%7C%20802.1Qav%20CBS-purple.svg)](https://1.ieee802.org/tsn/)
[![Toolchain: GCC 9.2](https://img.shields.io/badge/Toolchain-GCC%209.2%20(arm--none--eabi)-brightgreen.svg)](https://gcc.gnu.org)
[![License: BSD-3-Clause](https://img.shields.io/badge/License-BSD--3--Clause-blue.svg)](LICENSE)

English | [繁體中文](README_zh.md) | [Test Plan & Verification (T1–T5)](TEST_PLAN.md)

---

An automotive Time-Sensitive Networking (TSN) Ethernet Switch firmware reference implementation designed for the **NXP Semiconductors® SJA1110-MGS-EVM evaluation board (`SCH-94089 REV A`)** powered by the **SJA1110** multi-gigabit TSN Ethernet switch with an integrated **Arm® Cortex®-M7** microcontroller.

This project integrates the **NXP IEEE 802.1AS gPTP Precision Time Synchronization Stack** with an **IEEE 802.1Qat Stream Reservation Protocol (SRP: MSRP, MVRP, MMRP)** Bridge stack ported from **NXP GenAVB/TSN**, running concurrently on **FreeRTOS** over **NXP Real Time Drivers (RTD / AUTOSAR 4.4Eth + EthSwt)**. It leverages the SJA1110 hardware switch fabric for **directed management frame (`0x8B8C`) trapping/injection**, **IEEE 802.1Qav Credit-Based Shaper (CBS)** idleSlope hardware offload, **1024-entry L2 TCAM FDB** dynamic stream multicast filtering, and **hardware VLAN Lookup Table** registration.

---

## Key Features

* **Dual-Stack Automotive TSN Control Plane (802.1AS + 802.1Qat)**: Concurrent execution of IEEE 802.1AS Generalized Precision Time Protocol (`gptp_stack`, Grand Master / Bridge synchronization) and IEEE 802.1Qat Stream Reservation Protocol (`srp_stack`, Bridge mode `is_bridge = 1` with extensible Endpoint/IPC hooks).
* **Complete MRP State Machine Suite (IEEE 802.1Q-2018 Clause 10 & 35)**:
  * **MSRP (`0x22EA`)**: Multiple Stream Registration Protocol supporting Talker Advertise, Talker Failed, Listener Ready / Asking Failed / Ready Failed declaration merging, latency accumulation, and per-port SR Class A & Class B bandwidth reservation.
  * **MVRP (`0x88F5`)**: Multiple VLAN Registration Protocol dynamically propagating and registering SR VLAN memberships across all 8 external bridge ports.
  * **MMRP (`0x88F6`)**: Multiple MAC Registration Protocol hardware ingress trapping (`macFilter1`) and L2 frame demultiplexing hooks (state machine stubbed; dynamic stream multicast pruning is driven directly by MSRP Listener Ready via `fdb_update`).
  * **MRP Applicant / Registrar / LeaveAll Timers**: Full IEEE 802.1Q state tables (`VO`, `VP`, `VN`, `AN`, `AA`, `QA`, `LA`, `AO`, `QO`, `AP`, `QP`, `LO` and `IN`, `LV`, `MT`) driven by a deterministic FreeRTOS software timer pool (`os_timer`).
* **SJA1110 Hardware Management Frame (`0x8B8C`) & `MAC_FLT` Trap + Directed TX Pipeline**:
  * **Ingress Trapping & ENET Hash Filter**: Uses SJA1110 `GeneralParametersTable` dual MAC filters (`macFilter0` = `01:80:C2:00:00:0E` for gPTP/MSRP; `macFilter1` = `01:80:C2:00:00:20` with mask `FF:FF:FF:FF:FF:FE` for MMRP `01:80:C2:00:00:20` and MVRP `01:80:C2:00:00:21`, with `sendFollowUpTs0 = TRUE` and `sendFollowUpTs1 = TRUE`) and registers both canonical IEEE 802.1Q multicast MACs and SJA1110 `MAC_FLT` port-tagged variants (`01:80:C2:0p:00:xx`, `p = 1..8`) in the Cortex-M7 ENET hardware hash filter (`Eth_UpdatePhysAddrFilter`).
  * **Ingress Port Extraction & Single-Cable Remap**: Extracts ingress `SwitchPortIdx` from `EthSwt_43_SJA11XX_GetRxMgmtObject()` or byte 3 (`raw_dst[3]`) of the SJA1110 `MAC_FLT` destination MAC while restoring canonical multicast DA (`eth->dst`) for `mrp_process_packet()`. Supports `SRP_CFG_SINGLE_CABLE_TALKER_REMAP` to automatically remap incoming `Talker Advertise` on `Port 4` to `Port 1` with SR Class A Domain refresh when testing over a single Ethernet cable.
  * **Directed Egress Injection**: Uses `EthSwt_43_SJA11XX_SetMgmtInfo` and `EthSwt_43_SJA11XX_EthTxProcessFrame` with per-port source MAC population (`22:33:44:55:66:7p`) to inject MRP PDUs out of exact target physical ports (`SwitchPortIdx 1..8`) bypassing normal L2 forwarding.
* **IEEE 802.1Qav Credit-Based Shaper (CBS / FQTSS) Hardware Offload**: Real-time translation of MSRP reserved stream bandwidth (`idle_slope` in bps) into SJA1110 hardware CBS shapers via `Switch_Ip_SetCbsIdleSlope()` and `Switch_Ip_DisableCbs()` across 16 hardware shapers.
* **Dynamic L2 TCAM FDB & Hardware VLAN Offload**:
  * Programs SJA1110's 1024-entry L2 Address Lookup TCAM (`Switch_Ip_SearchL2EntryInTcam`, `Switch_Ip_UpdateTcamEntry`, `Switch_Ip_SJA11XX_setL2AddressLookupTableControl`) to prune stream multicast traffic strictly to ports with active Listener registrations.
  * Updates SJA1110's Hardware VLAN Lookup Table (`Switch_Ip_GetVlanLookupEntry`, `Switch_Ip_UpdateVlanLookupEntry`) while preserving internal Host Port 0 management access.
* **Dual-Bank Fail-Safe QSPI Flash Bootloader Architecture**: Supports primary bootloader partition with dual 256 KB application banks (`-bfsize="256000"`, `501,696`-byte dual-bank image fitting inside the 512 KB `ISSI IS25LQ040D` QSPI Flash; Bank 1 Green LED / Bank 2 Yellow LED) for atomic firmware updates and automatic rollback protection.

---

## Hardware Architecture & Port Mapping (`SJA1110-MGS-EVM`)

### SJA1110 9-Port Switch Fabric Mapping

The SJA1110 integrates 1 internal Microcontroller Host Port (`Port 0`) and 8 external Ethernet Switch Ports (`Port 1..8`). In `srp_stack`, the 8 external switch ports map 1-to-1 to GenAVB/TSN Bridge Logical Ports `2..9`:

| SJA1110 Switch Port | GenAVB `logical_port` | SRP Bridge Port Index | xMII Interface & Speed | Physical Transceiver / Connector | Role in TSN Bridge |
| :---: | :---: | :---: | :--- | :--- | :--- |
| **`PORT_0`** | `0` (Host EP) | N/A (Internal CPU) | Internal MII (`100M`) | Internal Cortex-M7 Host (`22:33:44:55:66:77`) | Control Plane Trap/Inject (`0x8B8C`) |
| **`PORT_1`** | `2` | Bridge Port `0` | SGMII (`1000 Mbps`) | Onboard `TJA1121B` (`1000BASE-T1`) | TSN Bridge Port (SRP + CBS) |
| **`PORT_2`** | `3` | Bridge Port `1` | RGMII (`1000 Mbps`) | Onboard `TJA1121A` (`1000BASE-T1`) | TSN Bridge Port (SRP + CBS) |
| **`PORT_3`** | `4` | Bridge Port `2` | SGMII (`100 Mbps`) | Onboard `TJA1104B` (`100BASE-T1` Switch) | TSN Bridge Port (SRP + CBS) |
| **`PORT_4`** | `5` | Bridge Port `3` | SGMII (`1000 Mbps`) | **SW1 Port 4 SFP Cage** (`1G SFP`) | Primary Test & Uplink TSN Port (gPTP + SRP + CBS) |
| **`PORT_5`** | `6` | Bridge Port `4` | MII (`100 Mbps`) | Integrated `100BASE-T1` PHY | Automotive T1 Bridge Port (SRP + CBS) |
| **`PORT_6`** | `7` | Bridge Port `5` | MII (`100 Mbps`) | Integrated `100BASE-T1` PHY | Automotive T1 Bridge Port (SRP + CBS) |
| **`PORT_7`** | `8` | Bridge Port `6` | MII (`100 Mbps`) | Integrated `100BASE-T1` PHY | Automotive T1 Bridge Port (SRP + CBS) |
| **`PORT_8`** | `9` | Bridge Port `7` | MII (`100 Mbps`) | External/Expansion MII (No internal T1 PHY) | Expansion MII Bridge Port (SRP + CBS) |

### Board Configuration (`SJA1110-MGS-EVM`)

| Hardware Item | Configuration / Position | Description |
| :--- | :---: | :--- |
| **DIP Switch `SW2`** | `SW2.6 = ON`, `SW2.7 = ON` (Others `OFF`) | Selects SPI Flash (NVM) Boot per `UM12269` Table 2 & 3 |
| **Jumpers** | `J58: 1-2`, `J61: 1-2`, `J77: 1-2` | Power, clock, and transceiver routing (leave others open) |
| **Debug Connector** | `J16` (10-pin Cortex Debug) | JTAG / SWD connection for S32 Debug Probe / PEMicro / J-Link |
| **SFP Uplink** | `SW1 Port 4` (`PORT_4`) | 1000BASE-T / 1000BASE-X SFP module connected to PC / TSN Talker-Listener |
| **GPIO Expander** | `PCAL9722` over `LPSPI` | Drives status LEDs, button interrupts, and PHY/PMIC fault inputs |

---

## System Architecture & Firmware Pipeline

```
                         ┌────────────────────────────────────────────────────────┐
                         │      External Ethernet Ports (SwitchPortIdx 1..8)      │
                         │   100BASE-T1 (Ports 5-8) | RGMII (Port 2) | SGMII (1,4)│
                         └──────────────┬──────────────────────────┬──────────────┘
                                        │ Ingress L2 Frame         ▲ Directed Egress Frame
                                        ▼                          │ + Hardware CBS Shaping
        ┌──────────────────────────────────────────────────────────┴───────────────────────────────┐
        │                          NXP SJA1110 Hardware Switch Fabric                              │
        │  ┌───────────────────────────────────────┐   ┌────────────────────────────────────────┐  │
        │  │ GeneralParametersTable MAC Filters    │   │ Data-Plane Hardware Offload Engines    │  │
        │  │ • Filter0: 01:80:C2:00:00:0E          │   │ • 16x IEEE 802.1Qav CBS Shapers        │  │
        │  │   (Traps gPTP 0x88F7 & MSRP 0x22EA)   │   │   (Switch_Ip_SetCbsIdleSlope)          │  │
        │  │ • Filter1: 01:80:C2:00:00:20 / FFFE   │   │ • 1024-Entry L2 Address Lookup TCAM    │  │
        │  │   (Traps MMRP 0x88F6 & MVRP 0x88F5)   │   │   (Dynamic Multicast Port Bitmap)      │  │
        │  └───────────────────┬───────────────────┘   │ • 4096-VID Hardware VLAN Lookup Table  │  │
        └──────────────────────┼───────────────────────┴───────────────────▲───────────────────────┘
                               │ Internal Host Port 0 (0x8B8C / MAC_FLT)   │ SPI / APB Switch_Ip API
                               ▼                                           │
        ┌──────────────────────────────────────────────────────────────────┼───────────────────────┐
        │                   Arm® Cortex®-M7 @ 200 MHz (FreeRTOS + RTD)     │                       │
        │                                                                  │                       │
        │  ┌────────────────────────────────────────────────────────────┐  │                       │
        │  │ EthIf_RxIndication() & EthSwt_43_SJA11XX_EthRxProcessFrame │  │                       │
        │  │ Extracts Ingress SwitchPortIdx (1..8) & Strips 0x8B8C Hdr  │  │                       │
        │  └──────────────┬─────────────────────────────┬───────────────┘  │                       │
        │                 │ EtherType 0x88F7            │ EtherType 0x22EA / 0x88F5 / 0x88F6       │
        │                 ▼                             ▼                  │                       │
        │  ┌──────────────────────────┐   ┌─────────────────────────────┐  │                       │
        │  │ gPTPTask (Prio 3, 5ms)   │   │ vSRP_Task (Prio 2, 10ms)    │  │                       │
        │  │ • IEEE 802.1AS GM/Bridge │   │ • MSRP Stream Reservation   ├──┘                       │
        │  │ • Eth_Main & Eth_Poll    │   │ • MVRP Dynamic VLAN Reg     │                          │
        │  │ • Hardware Timestamping  │   │ • FQTSS Bandwidth Manager   │                          │
        │  └──────────────────────────┘   └─────────────────────────────┘                          │
        └──────────────────────────────────────────────────────────────────────────────────────────┘
```

### TSN Control Plane Protocol Multiplexing

| Protocol | IEEE Standard | EtherType | Destination Multicast MAC | SJA1110 Trap Filter | FreeRTOS Consumer |
| :--- | :--- | :---: | :---: | :--- | :--- |
| **gPTP** | IEEE 802.1AS-2020 | `0x88F7` | `01:80:C2:00:00:0E` | `DPI Entry #0/#1` + `macFilter0` | `gPTPTask` (`GPTP_PORT_RxIndication`) |
| **MSRP** | IEEE 802.1Qat / 802.1Q-2018 Cl. 35 | `0x22EA` | `01:80:C2:00:00:0E` | `macFilter0` (Shared with gPTP) | `vSRP_Task` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |
| **MVRP** | IEEE 802.1Q-2018 Cl. 11 | `0x88F5` | `01:80:C2:00:00:21` | `macFilter1` (`Mask: FF:FF:FF:FF:FF:FE`) | `vSRP_Task` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |
| **MMRP** | IEEE 802.1Q-2018 Cl. 10 | `0x88F6` | `01:80:C2:00:00:20` | `macFilter1` (`Res : 01:80:C2:00:00:20`) | `vSRP_Task` (`g_srp_rx_ring` -> `SRP_PORT_Periodic`) |

---

## Project Milestones & Development Roadmap

This project follows a structured 5-Milestone engineering roadmap tracked via GitHub Milestones:

| Milestone | Scope & Deliverables | Key Modules | Acceptance Criteria | Status |
| :---: | :--- | :--- | :--- | :---: |
| **M1** | **SRP Stack Core & FreeRTOS OSAL Foundation** | `srp_stack/srp/`, `srp_stack/common/`, `srp_stack/include/` | 8-port Bridge (`logical_port 2..9`), FreeRTOS `os_timer` & `os_malloc`, Endpoint framework preserved | ✅ Completed (`v1.0.0-m1`) |
| **M2** | **SJA1110 Management Frame (`0x8B8C`) & L2 Trap Pipeline** | `srp_stack/port/srp_port.c`, `src/EthIf.c` | `macFilter0` + `macFilter1` (`FF:FF:FF:FF:FF:FE`), RX demux (`0x22EA`/`0x88F5`/`0x88F6`), directed per-port TX | ✅ Completed (`v1.0.1-m2`) |
| **M3** | **Hardware Offload (CBS Shaper, L2 TCAM FDB & VLAN Table)** | `srp_stack/port/srp_port.c`, `RTD/src/Switch_Ip_*.c` | 16-ch CBS `idleSlope` offload, 1024-entry L2 TCAM multicast pruning, 4096-VID hardware VLAN registration | ✅ Completed (`v1.0.2-m3`) |
| **M4** | **FreeRTOS Dual-Stack Coexistence, Build & Target Validation** | `src/main.c`, `generate/include/FreeRTOSConfig.h`, `.cproject` | 0-error GCC build, Dual-Bank NVM image, zero-conflict gPTP + MSRP/MVRP execution | ✅ Completed (`v1.0.3-m4`) |
| **M5** | **TSN Endpoint Mode (`is_bridge = 0`) & Local IPC Extension** | `srp_stack/srp/`, `srp_stack/port/` | Local Talker/Listener stream registration API over internal Host Port 0 (`IPC_MEDIA_STACK_MSRP`) | 📋 Planned (`v1.1.0-m5`) |

### Detailed Milestone Specifications & Acceptance Criteria

#### Milestone 1: SRP Stack Core & FreeRTOS OSAL Foundation (`v1.0.0-m1`)
- **GenAVB/TSN Core Extraction**: Ported complete IEEE 802.1Qat / 802.1Q-2018 Clause 10, 11, 34, 35 state machines (`mrp.c`, `msrp.c`, `mvrp.c`, `mmrp.c`, `srp.c`, `srp_entry.h`, `fqtss.c`, `timer.c`, `sr_class.c`, `qos.c`, `managed_objects.c`, `random.c`).
- **8-Port SJA1110 Bridge Topology**: Configured `CFG_MAX_NUM_PORT = 8`, `CFG_BR_DEFAULT_NUM_PORTS = 8`, `CFG_BR_LOGICAL_PORT_LIST = {2, 3, 4, 5, 6, 7, 8, 9}` mapping 1-to-1 to SJA1110 physical `SwitchPortIdx 1..8`, with `CFG_TRAFFIC_CLASS_MAX = 8` and `CFG_SR_CLASS_MAX = 2` (Class A & Class B).
- **FreeRTOS OSAL Adaptation**: Implemented `os_malloc`/`os_free` (`pvPortMalloc`/`vPortFree`), monotonic millisecond/nanosecond clocks (`xTaskGetTickCount`), and tick-driven deterministic software timer pool (`g_srp_timers` with `SRP_MAX_OS_TIMERS = 64`) and FreeRTOS `heap_4` coalescing memory allocator.
- **Extensible Bridge-First Architecture**: Enabled Bridge mode (`is_bridge = 1`) as primary target while preserving Endpoint (`msrp_ep` / `mvrp_ep`) and IPC stub hooks for Milestone 5.

#### Milestone 2: SJA1110 Management Frame (`0x8B8C`) & L2 Trap Pipeline (`v1.0.1-m2`)
- **Dual Hardware MAC Filter Trapping & ENET Hash Filter**:
  - `macFilter0` (`01:80:C2:00:00:0E`, mask `FF:FF:FF:FF:FF:FF`, `sendFollowUpTs0 = TRUE`): Traps IEEE 802.1AS gPTP (`0x88F7`) and IEEE 802.1Qat MSRP (`0x22EA`) frames to internal Host Port 0.
  - `macFilter1` (`01:80:C2:00:00:20`, mask `FF:FF:FF:FF:FF:FE`, `sendFollowUpTs1 = TRUE`): Simultaneously traps IEEE 802.1Q MMRP (`01:80:C2:00:00:20`, `0x88F6`) and MVRP (`01:80:C2:00:00:21`, `0x88F5`) frames to Host Port 0, and registers `01:80:C2:0p:00:xx` (`p = 1..8`) in the Cortex-M7 ENET MAC filter.
- **Zero-Interference RX Demultiplexing**: `SRP_PORT_RxIndication()` fast-path filters `0x22EA` / `0x88F5` / `0x88F6` (including 802.1Q VLAN-tagged `0x8100` frames) into `g_srp_rx_ring` with `logical_port = SwitchPortIdx + 1`, leaving `0x88F7` untouched for `GPTP_PORT_RxIndication()`.
- **Directed Per-Port Egress TX (`0x8B8C`)**: Implements `net_tx()` via `Eth_ProvideTxBuffer` $\to$ `EthSwt_43_SJA11XX_SetMgmtInfo` $\to$ `EthSwt_43_SJA11XX_EthTxProcessFrame` $\to$ `Eth_Transmit` $\to$ `Eth_TxConfirmation` with per-port source MAC (`22:33:44:55:66:7p`) and mutex-serialized TX buffer access.

#### Milestone 3: Hardware Offload Integration (CBS Shaper, L2 TCAM FDB & VLAN Table) (`v1.0.2-m3`)
- **IEEE 802.1Qav Credit-Based Shaper (CBS)**: Connects `fqtss_set_oper_idle_slope()` to `Switch_Ip_SetCbsIdleSlope(0U, swt_port, tc, idle_slope)` when `idle_slope > 0` and `Switch_Ip_DisableCbs(0U, swt_port, tc)` when `idle_slope == 0`.
- **1024-Entry L2 TCAM Multicast Pruning**: Connects `fdb_update()` / `fdb_delete()` to `Switch_Ip_SearchL2EntryInTcam()` and `Switch_Ip_UpdateTcamEntry()`, translating GenAVB `logical_port` registration states into hardware `SwitchPortIdx` egress bitmasks (`destPorts`).
- **4096-VID Hardware VLAN Lookup Table**: Connects `vlan_update()` / `vlan_delete()` to `Switch_Ip_GetVlanLookupEntry()` and `Switch_Ip_UpdateVlanLookupEntry()`, maintaining `Switch_Ip_Port0` (Host CPU) membership alongside dynamic external bridge ports.

#### Milestone 4: FreeRTOS Dual-Stack Coexistence, Build & Target Validation (`v1.0.3-m4`)
- **Deterministic Multi-Task Scheduling**:
  - `gPTPTask` (`Priority 3`, 5 ms period): Dedicated high-priority execution of `Eth_Main()`, `Eth_Poll()`, and `GPTP_TimerPeriodic()`.
  - `vSRP_Task` (`Priority 2`, 10 ms period): Executes `SRP_PORT_Periodic()` (MRP RX ring dispatch, software timers, link polling, telemetry snapshot) and onboard button polling.
  - `NVM_Write_Task` (`Priority 1`, 100 ms period): Executes `FLASH_Write_Poll()` with a `0.1 ppm` deadband and `30 s` cooldown to protect external QSPI Flash endurance.
  - `aliveLEDTimer` (`Priority 3`, 500 ms FreeRTOS software timer): Periodically toggles the onboard Alive LED.
- **RTOS Resource Allocation**: Expands `configTOTAL_HEAP_SIZE` to `49152` (48 KB) using the FreeRTOS `heap_4` coalescing allocator and enables `configUSE_TIMERS = 1` in `FreeRTOSConfig.h`.
- **Target & Wireshark Verification**: Clean GCC compilation (`0 errors`), Dual-Bank SPI NVM image generation (`256 KB` bank size, `501,696` bytes total), and live packet capture verification on `SW1 Port 4` (1G SFP).

#### Milestone 5: TSN Endpoint Mode (`is_bridge = 0`) & Local IPC Extension (`v1.1.0-m5`)
- **Host Endpoint Stream Registration**: Activates the retained `msrp_ep` / `mvrp_ep` instances and binds `ipc_tx()` / `ipc_rx()` to FreeRTOS message queues so application tasks on Cortex-M7 can originate Talker Advertise or Listener Ready declarations directly.

---

## Project Structure

```
.
├── board/                              # SJA1110 hardware pin, switch, and peripheral init configs
├── FreeRTOS/                           # FreeRTOS v11.1.0 kernel, heap_4 allocator & Cortex-M7 port
├── freemaster/                         # FreeMASTER project & live WebSocket/Wireshark telemetry dashboard
│   ├── sja1110_freemaster.fmcfg        # Symbol-synced FreeMASTER configuration
│   ├── telemetry_bridge.py             # Live JTAG/pyOCD + Scapy Wireshark WebSocket telemetry server
│   └── web/index.html                  # Real-time TSN & Wireshark interactive web dashboard
├── generate/                           # S32 Configuration Tools (MEX) generated RTD headers/sources
│   └── include/FreeRTOSConfig.h        # FreeRTOS scheduler, heap (48 KB), and software timer config
├── gptp_stack/                         # IEEE 802.1AS gPTP Precision Time Synchronization Stack
│   ├── gptp_core/                      # gPTP state machines (Pdelay, Sync, FollowUp, BMCA)
│   └── port/gptp_port.c                # SJA1110 Eth/EthSwt frame TX/RX & hardware clock port
├── include/                            # Application-level headers (example_init.h, gptp_cbk.h)
├── Project_Settings/                   # Linker scripts (Flash/RAM), startup code, debugger configs
├── RTD/                                # NXP Real Time Drivers (Eth, EthSwt, Switch_Ip, Spi, Gpt)
├── src/                                # Main application & integration sources
│   ├── main.c                          # Dual-bank init, NVM cache, FreeRTOS tasks (gPTPTask, vSRP_Task, NVM_Write_Task)
│   ├── EthIf.c                         # 0x8B8C Switch Mgmt frame demux (gPTP + MSRP/MVRP/MMRP)
│   ├── example_init.c                  # SJA1110 switch/PHY initialization, mutex TX & RGB LED control
│   └── gptp_cbk.c                      # gPTP domain selection, sync & clock update callbacks
├── srp_stack/                          # IEEE 802.1Qat Stream Reservation Protocol (SRP) Stack
│   ├── common/                         # FQTSS bandwidth shaper, timer pool, SR class & QoS descriptors
│   │   ├── fqtss.c                     # Credit-Based Shaper (CBS) bandwidth accumulation & offload hook
│   │   ├── sr_class.c                  # SR Class A (8 kHz) & Class B (4 kHz) domain definitions
│   │   ├── srp.c                       # SRP protocol PDU definitions
│   │   └── timer.c                     # Generic timer wrapper over deterministic tick-polled os_timer pool
│   ├── include/                        # Public & internal GenAVB/TSN headers & FreeRTOS OSAL
│   │   ├── genavb/                     # Public API headers (config.h, srp.h, fdb.h, vlan.h, qos.h)
│   │   ├── common/                     # Internal stack headers (fqtss.h, timer.h, managed_objects.h)
│   │   ├── os/                         # OS Abstraction Layer (stdlib.h, clock.h, timer.h, net.h)
│   │   └── osal/                       # System types & compiler attributes (sys_types.h)
│   ├── port/                           # SJA1110 Hardware Adaptation Layer
│   │   ├── srp_port.h                  # SJA1110 SRP Bridge port API & MCU telemetry struct
│   │   └── srp_port.c                  # 0x8B8C/MAC_FLT TX/RX, CBS offload, L2 TCAM FDB, VLAN & self-test
│   └── srp/                            # IEEE 802.1Q MRP / MSRP / MVRP / MMRP State Machines
│       ├── mrp.c                       # Core MRP Applicant, Registrar & LeaveAll state machines
│       ├── msrp.c                      # IEEE 802.1Qat MSRP Talker/Listener/Bridge logic
│       ├── mvrp.c                      # IEEE 802.1Q MVRP dynamic VLAN registration
│       ├── mmrp.c                      # IEEE 802.1Q MMRP dynamic MAC registration
│       └── srp_entry.h                 # Top-level srp_init() & srp_exit() entry declarations
├── tool/                               # Dual-Bank Flash, symbol sync & automated TSN verification scripts
│   ├── createDBImage.py                # Generates Dual-Bank application flash image
│   ├── createNvmImage.py               # Generates SJA1110 SPI NVM boot image
│   ├── flash_makefile.targets          # Post-build dual-bank QSPI Flash ELF generator (-bfsize=256000)
│   ├── fix_s32ds_cproject_paths.py     # Normalizes S32DS .cproject include paths to portable relative paths
│   ├── sync_freemaster_symbols.py      # Syncs ELF DWARF/symbol addresses into freemaster/*.fmcfg
│   └── test_sja1110_srp.py             # Automated Scapy closed-loop gPTP + MVRP + MSRP verification script
├── SJA1110-MGS_gPTP_FreeRTOS.mex       # S32 Configuration Tools hardware project descriptor
├── README.md                           # English specification & documentation
└── README_zh.md                        # 繁體中文技術規格與說明文件
```

---

## Build and Flashing Instructions

### Prerequisites
* **NXP S32 Design Studio for S32 Platform** (v3.6.11) with `arm-none-eabi-gcc` (GCC 9.2 / 10.2) and **SJA1110 Reference Applications / RTD**.
* **Python 3.8+** with `pyelftools` and `pycryptodomex` (required by `tool/createDBImage.py` and `tool/createNvmImage.py` for Dual-Bank NVM image creation):
  ```powershell
  pip install pyelftools pycryptodomex
  ```

### Option A: Build via Command Line (Headless GNU Make)
```powershell
# 1. Setup S32DS build tools and ARM GCC toolchain in PATH
$env:PATH = "C:\NXP\S32DS.3.6.11\eclipse\plugins\com.nxp.s32ds.build.tools.msys32_1.0.0.202307180758\msys32\usr\bin;C:\NXP\S32DS.3.6.11\S32DS\build_tools\gcc_v9.2\gcc-9.2-arm32-eabi\bin;" + $env:PATH

# 2. Build Debug_FLASH ELF + Dual-Bank QSPI Flash image (app_flash.elf) and sync FreeMASTER symbols
make -C Debug_FLASH -j8 user_all CWD=.
python tool/sync_freemaster_symbols.py --elf Debug_FLASH/SJA1110_MGS_gPTP_FreeRTOS.elf
```

### Option B: Build and Run via S32 Design Studio IDE
1. Open **S32 Design Studio** and import the project via **File $\to$ Import $\to$ General $\to$ Existing Projects into Workspace**.
2. Open the **Peripherals** view (`SJA1110-MGS_gPTP_FreeRTOS.mex`) and click **Update Code** — S32DS will automatically populate `RTD/`, `generate/`, `board/`, and `gptp_stack/` from your local NXP RTD/SDK installation.
3. Select **Debug_FLASH** (or **Debug_RAM**) and click **Project $\to$ Build Project**.
4. Connect a debug probe to `J16` (10-pin JTAG Cortex Debug connector), select the matching Run/Debug configuration, and click **Debug**.

---

## Network Validation & Wireshark Verification
 
> [!NOTE]
> **Live Target Verification Status (T1 ~ T5 All Verified PASS)**:
> - **Scenario A (Single board JTAG, milestones T1–T3)**: **100% Verified (PASS)** on real `SJA1110-MGS-EVM` hardware! Confirmed: FreeRTOS `heap_4` `13,064` Bytes free (`60` allocs / `16` frees, 0 leaks), 8-port SRP Bridge scheduler active (`g_srp_bridge_ctx = 0x20007dd0`), clean boot state (`active_vlan_id = 0`), and PDU-driven self-test (`g_srp_run_selftest = 1`) offloading MVRP `VID = 2`, L2 TCAM (`91:E0:F0:00:FE:00`, `dest_ports = 16`, `tcam_index = 16`), and IEEE 802.1Qav CBS (`oper_idle_slope = 10,944,000` bps).
> - **Scenario B (Ethernet + PC, milestones T4–T5)**: Connected via `SW1 Port 4` to PC Ethernet NIC, **100% Verified (PASS)**! Captured `80+` gPTP Sync/Follow_Up frames (125 ms interval), `10` Pdelay_Req/Resp bidirectional exchanges, `0` SJA1110 `0x8B8C` header leaks, outbound EVB `MSRP Talker Advertise` (`src = 22:33:44:55:66:75`) & `LeaveAll`, and verified live MCU SRAM state after Ethernet injection (`active_vlan_id = 2`, `active_tcam_dest_ports = 16`, `port4_cbs_slope_bps = 10,944,000` bps, `rx_mrp_packets = 24`, `tx_mrp_packets = 37`).
>
> For full step-by-step verification, GDB watch variables, and live test data, see **[TEST_PLAN.md](TEST_PLAN.md)** ([繁體中文測試計畫](TEST_PLAN_zh.md)).
 
1. Insert a `1000BASE-T` SFP transceiver into **SW1 Port 4 (`PORT_4`)** of the `SJA1110-MGS-EVM` board and connect it to a PC or TSN endpoint.
2. Open **Wireshark** on the PC network interface and apply the capture filter:
   ```text
   ether proto 0x88f7 or ether proto 0x22ea or ether proto 0x88f5 or ether proto 0x88f6
   ```
3. **Expected Control Plane Traffic**:
   * **IEEE 802.1AS gPTP (`0x88F7`, Dest `01:80:C2:00:00:0E`)**: Periodic `Sync` and `Follow_Up` messages every `125 ms` (Grand Master mode) plus `Pdelay_Req` / `Pdelay_Resp`.
   * **IEEE 802.1Qat MSRP (`0x22EA`, Dest `01:80:C2:00:00:0E`)**: Domain Attribute declarations (SR Class A Prio 3 / VID 2, SR Class B Prio 2 / VID 2), periodic `LeaveAll` events, and dynamic `Talker Advertise` / `Listener Ready` propagation across Bridge Ports `1..8`.
   * **IEEE 802.1Q MVRP (`0x88F5`, Dest `01:80:C2:00:00:21`)**: Dynamic VLAN membership declarations and registration updates.
4. **LED Status Indicators**:
   * **Alive LED**: Toggles periodically every 500 ms via FreeRTOS software timer `aliveLEDTimer` (`toggleAliveLED`) to confirm normal scheduler operation.
   * **RGB LED**: Indicates booted Dual-Bank partition at startup (**Green** = Bank 1, **Yellow** = Bank 2, **Red** = Boot Error) and changes on button/PHY interrupts (**Magenta** = BUTTON1 Self-Test, **Cyan** = BUTTON2).
 
---

## FreeMASTER & Live Wireshark Interactive Demo Dashboard

This repository includes an automotive-grade real-time web dashboard that unifies **MCU-internal FreeMASTER telemetry** and **external Ethernet Wireshark packet streaming** on a single screen:

* **One-Click Launch**: Run `run_freemaster_demo.bat` in the repository root. The launcher starts the Python telemetry bridge in the background and opens the browser:
  ```cmd
  run_freemaster_demo.bat
  ```
* **Dashboard URL**: `http://127.0.0.1:8091/index.html` (WebSocket Stream: `ws://127.0.0.1:8091/ws`)
* **Key Demo Modules**:
  1. **IEEE 802.1AS gPTP Engine Monitor**: Real-time 125ms Sync rate, <150ns Pdelay lock status, and zero `0x8B8C` leakage indicator.
  2. **FreeRTOS Heap Watermark**: Live sparkline chart showing 19,576 Bytes remaining with zero memory leaks.
  3. **SJA1110 8-Port Switch Matrix**: Visual port LED indicators and negotiated speeds (Port 4 1Gbps, Ports 1~3 100M).
  4. **TSN Hardware Offload Cards**: Real-time hardware status for VLAN table, L2 TCAM multicast FDB, and CBS credit shaper.
  5. **Wireshark Live Packet Analyzer**: Color-coded scrolling table (green gPTP, cyan Pdelay, purple MSRP, orange MVRP) with clickable protocol tree decoding and Hex Dump.
  6. **Interactive Injection Controls**: One-click web buttons for "Trigger Self-Test", "Inject MVRP JoinIn (VID=2)", and "Inject MSRP Stream Reservation".

---

## References & Technical Standards

1. **[1]** IEEE Std 802.1Q-2018, *IEEE Standard for Local and Metropolitan Area Networks—Bridges and Bridged Networks* (Clause 10: MMRP, Clause 11: MVRP, Clause 34: FQTSS/CBS, Clause 35: MSRP).
2. **[2]** IEEE Std 802.1Qat-2010, *IEEE Standard for Local and Metropolitan Area Networks—Virtual Bridged Local Area Networks Amendment 14: Stream Reservation Protocol (SRP)*.
3. **[3]** IEEE Std 802.1Qav-2009, *IEEE Standard for Local and Metropolitan Area Networks—Virtual Bridged Local Area Networks Amendment 12: Forwarding and Queuing Enhancements for Time-Sensitive Streams*.
4. **[4]** IEEE Std 802.1AS-2020, *IEEE Standard for Local and Metropolitan Area Networks—Timing and Synchronization for Time-Sensitive Applications*.
5. **[5]** NXP Semiconductors, *SJA1110 Multi-Gig Safe and Secure TSN Ethernet Switch User Manual & Data Sheet*, Silicon Revision E.
6. **[6]** NXP Semiconductors, *GenAVB/TSN Stack Architecture and API Reference Manual*, Real-Time Edge Software.

---

## License

* **Original Project Code, SJA1110 SRP Porting Layer, FreeMASTER Telemetry & Test Tools** (`srp_stack/port/`, `freemaster/`, `tool/test_sja1110_srp.py`, `tool/sync_freemaster_symbols.py`, `tool/fix_s32ds_cproject_paths.py`): **BSD-3-Clause License**, Copyright (c) 2026, Max97k.
* **NXP GenAVB/TSN SRP/MRP Core Stack** (`srp_stack/`): **BSD-3-Clause License**, Copyright 2014-2016 Freescale Semiconductor, Inc., Copyright 2016-2026 NXP.
* **FreeRTOS Kernel** (`FreeRTOS/`): **MIT License**, Copyright (C) 2021 Amazon.com, Inc. or its affiliates.
* **NXP S32DS Auto-Generated & Reference Application Files**: NXP Real-Time Drivers (`RTD/`), S32 Configuration Tools generated files (`generate/`, `board/`), and the NXP gPTP stack (`gptp_stack/`) are excluded from version control (`.gitignore`) and are automatically generated by S32DS **Update Code** from `SJA1110-MGS_gPTP_FreeRTOS.mex`. Any remaining S32DS template files are governed by the **NXP Software License Agreement (`LA_OPT_NXP_Software_License`)**; see [LICENSE](LICENSE) for full details.

