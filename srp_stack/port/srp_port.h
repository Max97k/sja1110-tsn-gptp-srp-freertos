/*
 * Copyright 2025-2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file srp_port.h
 * @brief SJA1110 FreeRTOS Porting Layer for GenAVB/TSN SRP (IEEE 802.1Qat: MSRP, MVRP, MMRP)
 */

#ifndef SRP_PORT_H
#define SRP_PORT_H

#include "StandardTypes.h"
#include "Eth_GeneralTypes.h"
#include "genavb/init.h"
#include "genavb/srp.h"
#include "common/ipc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Number of external Bridge ports on SJA1110-MGS (SwitchPortIdx 1..8) */
#define SRP_SJA1110_SWT_ID              (0U)
#define SRP_SJA1110_HOST_PORT           (0U)
#define SRP_SJA1110_NUM_BR_PORTS        (8U)
#define SRP_SJA1110_FIRST_SW_PORT       (1U)
#define SRP_SJA1110_FIRST_LOGICAL_PORT  (2U)

/**
 * Bitmask (indexed by SwitchPortIdx 1..8) of Phyless / fixed-link ports
 * that should be treated as Link Up when no EthTrcv GetLinkState callback is bound.
 * Default: (1U << 4U) for SW1 Port 4 (1G SFP uplink).
 * Set additional bits (e.g. (1U << 2U) | (1U << 3U) | (1U << 8U)) only if external
 * xMII links on Ports 2, 3, or 8 are physically wired in your hardware setup.
 */
#ifndef SRP_PHYLESS_PORT_FORCE_UP_MASK
#define SRP_PHYLESS_PORT_FORCE_UP_MASK  (1U << 4U)
#endif

/**
 * @brief Initialize the IEEE 802.1Qat (SRP: MSRP, MVRP, MMRP) stack on SJA1110.
 *
 * Initializes hardware multicast trapping for MRP protocols (01:80:C2:00:00:0E,
 * 01:80:C2:00:00:20, 01:80:C2:00:00:21), FQTSS/CBS, IPC channels, and the
 * SRP Bridge state machines (leaving Endpoint hooks extensible).
 *
 * @return E_OK on success, E_NOT_OK on failure.
 */
Std_ReturnType SRP_PORT_Init(void);

/**
 * @brief Periodic processing function for the SRP stack.
 *
 * Processes pending SRP timer events, received MRP frames, IPC messages, and
 * polls SJA1110 switch port link states (notifying MSRP/MVRP/MMRP on link changes).
 * Call periodically from the Ethernet/gPTP task context.
 */
void SRP_PORT_Periodic(void);

/**
 * @brief Ethernet RX Indication hook for MRP frames (MSRP 0x22EA, MVRP 0x88F5, MMRP 0x88F6).
 *
 * Inspects incoming frames from EthIf_RxIndication. If the frame (untagged or
 * 802.1Q VLAN-tagged) is an MRP frame, extracts the SJA1110 source SwitchPortIdx
 * via EthSwt_43_SJA11XX_GetRxMgmtObject and queues it for SRP processing.
 *
 * @param[in] u8CtrlIdx     Ethernet controller index
 * @param[in] u16FrameType  Outer EtherType (host byte order)
 * @param[in] bIsBroadcast  Broadcast indicator
 * @param[in] cpu8PhysAddr  Pointer to Source MAC address (6 bytes)
 * @param[in] cpu8Data      Pointer to Ethernet payload (after 14-byte Ethernet header)
 * @param[in] u16LenByte    Payload length in bytes
 * @return TRUE if frame was consumed by SRP, FALSE if frame should be passed to other stacks (e.g. gPTP).
 */
boolean SRP_PORT_RxIndication(uint8 u8CtrlIdx,
                              Eth_FrameType u16FrameType,
                              boolean bIsBroadcast,
                              const uint8 *cpu8PhysAddr,
                              const Eth_DataType *cpu8Data,
                              uint16 u16LenByte);

/**
 * @brief Send an IPC command to the SRP stack (extensible framework hook for Endpoint Talker/Listener & Managed Objects).
 *
 * @param[in] ipc_id   Target IPC channel ID (e.g. IPC_SRP_BRIDGE, IPC_MSRP, IPC_MVRP)
 * @param[in] type     IPC message type (enum genavb_ipc_msg_type)
 * @param[in] payload  Pointer to IPC message payload structure
 * @param[in] len      Length of payload in bytes
 * @return 0 on success, negative error code on failure.
 */
int SRP_PORT_SendIpcMessage(unsigned int ipc_id, uint32_t type, const void *payload, unsigned int len);

/**
 * @brief Run the built-in self-test (T3 milestone verification).
 *
 * Simulates MVRP VID 2 registration, L2 TCAM stream multicast forwarding,
 * and CBS hardware shaper configuration on SwitchPort 4.
 */
void SRP_PORT_RunSelfTest(void);

/** Set to 1U only for Scenario A standalone JTAG boot self-test; keep 0U for clean network boot */
#ifndef SRP_CFG_RUN_SELFTEST_ON_BOOT
#define SRP_CFG_RUN_SELFTEST_ON_BOOT            (0U)
#endif

/**
 * Enable single-cable closed-loop MSRP Talker Advertise ingress remap on SwitchPort 4:
 * When only one Ethernet cable is connected to Port 4 and Port 1 is unplugged, an incoming
 * MSRP Talker Advertise on Port 4 is logically mapped to Port 1 so IEEE 802.1Qat Split Horizon
 * allows propagating the Talker Advertise out Port 4 and pairing with Listener Ready on Port 4.
 */
#ifndef SRP_CFG_SINGLE_CABLE_TALKER_REMAP
#define SRP_CFG_SINGLE_CABLE_TALKER_REMAP       (1U)
#endif

/** Contiguous MCU telemetry snapshot readable via FreeMASTER / GDB / pyOCD */
typedef struct {
    uint32_t magic;                  /* 0x534A4131 ('SJA1') */
    uint32_t uptime_ticks;           /* FreeRTOS xTaskGetTickCount() */
    uint32_t free_heap_bytes;        /* xPortGetFreeHeapSize() */
    uint32_t min_free_heap_bytes;    /* xPortGetMinimumEverFreeHeapSize() */
    uint8_t  port_link_mask;         /* Bitmask of SwitchPort 1..8 link state (bit 0 = Port 1) */
    uint8_t  selftest_done;          /* 1 if SRP_PORT_RunSelfTest completed */
    uint16_t active_vlan_id;         /* Dynamically registered VID (e.g. 2) or 0 */
    uint16_t active_tcam_dest_ports; /* Destination port mask of first active FDB entry */
    uint8_t  active_tcam_mac[6];     /* Destination MAC of first active FDB entry */
    uint32_t port4_cbs_slope_bps;    /* Active CBS idleSlope (bps) on SwitchPort 4 */
    uint32_t rx_mrp_packets;         /* Total MRP PDUs received by SRP_PORT */
    uint32_t tx_mrp_packets;         /* Total MRP PDUs transmitted by SRP_PORT */
} srp_mcu_telemetry_t;

extern volatile srp_mcu_telemetry_t g_srp_telemetry;

/** Global trigger and status flags for FreeMASTER / Debugger / Self-Test */
extern volatile uint8_t g_srp_run_selftest;
extern volatile uint8_t g_srp_selftest_done;
extern volatile int g_srp_selftest_vlan_res;
extern volatile int g_srp_selftest_fdb_res;
extern volatile int g_srp_selftest_cbs_res;

#ifdef __cplusplus
}
#endif

#endif /* SRP_PORT_H */
