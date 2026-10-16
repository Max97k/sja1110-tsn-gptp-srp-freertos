/*
 * Copyright 2025-2026 NXP
 * Copyright (c) 2026, Max97k
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file srp_port.c
 * @brief SJA1110 FreeRTOS Porting & Hardware Offload Layer for GenAVB/TSN SRP
 *        (IEEE 802.1Qat: MSRP, MVRP, MMRP Bridge & Extensible Endpoint Framework)
 */

#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "StandardTypes.h"
#include "Eth.h"
#include "EthSwt_43_SJA11XX.h"
#include "EthSwt_43_SJA11XX_Ipw.h"
#include "Switch_Ip.h"
#include "Switch_Ip_SJA1110_Tables.h"
#include "Switch_Ip_Cbs.h"

#include "../srp/config.h"
#include "common/ipc.h"
#include "os/stdlib.h"
#include "os/clock.h"
#include "os/timer.h"
#include "os/net.h"
#include "os/ipc.h"
#include "os/fdb.h"
#include "os/vlan.h"
#include "os/fqtss.h"

#include "common/log.h"
#include "common/ether.h"
#include "common/fqtss.h"
#include "common/srp.h"
#include "genavb/qos.h"
#include "genavb/sr_class.h"

#include "../srp/srp_entry.h"
#include "../srp/srp.h"
#include "srp_port.h"

/*==================================================================================================
 *                                       LOCAL MACROS
 *==================================================================================================*/

#define SRP_RX_QUEUE_DEPTH              (32U)
#define SRP_IPC_QUEUE_DEPTH             (16U)
#define SRP_MAX_OS_TIMERS               (32U)
#define SRP_MAX_FDB_ENTRIES             (32U)
#define SRP_TCAM_BASE_INDEX             (16U)
#define SRP_ETH_HEAD_TRAIL_LEN          (8U)
#define SRP_ETH_II_HEADER_LEN           (14U)
#define SRP_VLAN_TAG_LEN                (4U)
#define SRP_MGMT_FRAME_ETHERTYPE        ((Eth_FrameType)0x8B8CU)
#define SRP_LINK_POLL_PERIOD_MS         (200U)

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *==================================================================================================*/

typedef struct {
    struct os_timer *timer;
    uint32_t         period_ms;
    TickType_t       last_tick;
    boolean          active;
    boolean          periodic;
    boolean          in_use;
} srp_os_timer_slot_t;

typedef struct {
    ipc_id_t         id;
    struct ipc_rx   *rx;
    struct ipc_tx   *tx;
    struct ipc_desc *queue[SRP_IPC_QUEUE_DEPTH];
    uint8_t          head;
    uint8_t          tail;
    uint8_t          count;
    boolean          registered;
} srp_ipc_channel_t;

typedef struct {
    uint8_t          mac[6];
    uint16_t         vid;
    uint16_t         dest_ports;
    uint16_t         tcam_index;
    boolean          in_use;
    boolean          dynamic;
} srp_fdb_shadow_t;

/*==================================================================================================
 *                                      LOCAL VARIABLES
 *==================================================================================================*/

static struct srp_ctx *g_srp_bridge_ctx = NULL;
static struct srp_config g_srp_bridge_cfg;

/* Registered net_rx per logical_port (0..CFG_MAX_LOGICAL_PORTS-1) */
static struct net_rx *g_srp_net_rx_by_port[CFG_MAX_LOGICAL_PORTS];

/* RX ring buffer for MRP PDUs trapped via SJA1110 0x8B8C management header */
static struct net_rx_desc *g_srp_rx_ring[SRP_RX_QUEUE_DEPTH];
static volatile uint8_t g_srp_rx_head = 0U;
static volatile uint8_t g_srp_rx_tail = 0U;
static volatile uint8_t g_srp_rx_count = 0U;

/* Deterministic tick-based software timer table */
static srp_os_timer_slot_t g_srp_timers[SRP_MAX_OS_TIMERS];

/* Lightweight in-memory IPC channels for Bridge & Endpoint extensibility */
static srp_ipc_channel_t g_srp_ipc_channels[IPC_ID_MAX];

/* Shadow FDB table mapped to SJA1110 L2 Address Lookup TCAM */
static srp_fdb_shadow_t g_srp_fdb_table[SRP_MAX_FDB_ENTRIES];

/* Cached link state per external bridge port (port_idx 0..7 -> SwitchPortIdx 1..8) */
static boolean g_srp_port_link_up[SRP_SJA1110_NUM_BR_PORTS];
static uint64_t g_srp_port_rate_bps[SRP_SJA1110_NUM_BR_PORTS];
static TickType_t g_srp_last_link_poll_tick = 0U;

/* Galois LFSR seed for os_random() */
static uint32_t g_srp_lfsr_state = 0xACE12468UL;

/* Local Switch Host MAC address */
static const uint8_t g_srp_local_mac[6] = {0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U};

/* IEEE 802.1Q MRP Multicast MAC addresses */
static const uint8_t g_msrp_mc_mac[6] = MC_ADDR_MSRP; /* 01:80:C2:00:00:0E */
static const uint8_t g_mmrp_mc_mac[6] = MC_ADDR_MMRP; /* 01:80:C2:00:00:20 */
static const uint8_t g_mvrp_mc_mac[6] = MC_ADDR_MVRP; /* 01:80:C2:00:00:21 */

/*==================================================================================================
 *                                   LOCAL HELPER FUNCTIONS
 *==================================================================================================*/

/**
 * @brief Convert GenAVB logical_port (2..9) to SJA1110 physical SwitchPortIdx (1..8)
 */
static int srp_logical_to_swt_port(unsigned int logical_port, uint8 *swt_port)
{
    if ((logical_port >= SRP_SJA1110_FIRST_LOGICAL_PORT) &&
        (logical_port < (SRP_SJA1110_FIRST_LOGICAL_PORT + SRP_SJA1110_NUM_BR_PORTS)))
    {
        if (swt_port != NULL)
        {
            *swt_port = (uint8)(logical_port - 1U);
        }
        return 0;
    }
    return -1;
}

/**
 * @brief Query SJA1110 physical port link state and speed in bps
 */
static void srp_query_swt_port_link(uint8 swt_port, boolean *up, uint64_t *rate_bps)
{
    Switch_Ip_SJA1110_macCfgTableEntryType macCfg;
    uint32_t portStatusReg = 0U;

    *up = TRUE;
    *rate_bps = 100000000ULL; /* Default 100 Mbps */

    /* SJA1110 Port 1, 2, 4 are 1 Gbps capable; Ports 3, 5..8 are 100 Mbps */
    if ((swt_port == 1U) || (swt_port == 2U) || (swt_port == 4U))
    {
        *rate_bps = 1000000000ULL;
    }

    if (SWITCH_STATUS_SUCCESS == Switch_Ip_GetMacConfigTable(SRP_SJA1110_SWT_ID, swt_port, &macCfg))
    {
        if (macCfg.speed == Switch_Ip_SJA11XX_switchSpeed_1_GBPS)
        {
            *rate_bps = 1000000000ULL;
        }
        else if (macCfg.speed == Switch_Ip_SJA11XX_switchSpeed_100_MBPS)
        {
            *rate_bps = 100000000ULL;
        }
        else if (macCfg.speed == Switch_Ip_SJA11XX_switchSpeed_10_MBPS)
        {
            *rate_bps = 10000000ULL;
        }
        else
        {
            /* Keep default speed based on port role */
        }
    }
    (void)portStatusReg;
}

/**
 * @brief Configure SJA1110 GeneralParametersTable MAC Filters to trap MSRP, MVRP, and MMRP
 */
static Std_ReturnType SRP_PORT_ConfigureHwTrap(void)
{
    Switch_Ip_SJA1110_generalParametersEntryType genParams;
    Switch_Ip_StatusType swtStatus;
    uint8 idx;

    /* Register multicast addresses in internal Cortex-M7 Ethernet MAC filter */
    (void)Eth_UpdatePhysAddrFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, g_msrp_mc_mac, ETH_ADD_TO_FILTER);
    (void)Eth_UpdatePhysAddrFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, g_mmrp_mc_mac, ETH_ADD_TO_FILTER);
    (void)Eth_UpdatePhysAddrFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, g_mvrp_mc_mac, ETH_ADD_TO_FILTER);

    /* Update SJA1110 GeneralParametersTable macFilter1 to trap 01:80:C2:00:00:20 (MMRP) & 01:80:C2:00:00:21 (MVRP)
     * while preserving macFilter0 (01:80:C2:00:00:0E for gPTP 0x88F7 and MSRP 0x22EA).
     */
    swtStatus = Switch_Ip_GetGeneralParamsTable(SRP_SJA1110_SWT_ID, &genParams);
    if (SWITCH_STATUS_SUCCESS != swtStatus)
    {
        return E_NOT_OK;
    }

    for (idx = 0U; idx < 5U; idx++)
    {
        genParams.macFilter1[idx]       = 0xFFU;
        genParams.macFilterResult1[idx] = g_mmrp_mc_mac[idx];
    }
    /* Ignore LSB bit 0 so both 0x20 (MMRP) and 0x21 (MVRP) match macFilter1 */
    genParams.macFilter1[5]       = 0xFEU;
    genParams.macFilterResult1[5] = 0x20U;
    genParams.sendFollowUpTs1     = FALSE;

    swtStatus = Switch_Ip_UpdateGeneralParamsTable(SRP_SJA1110_SWT_ID, &genParams);
    return (SWITCH_STATUS_SUCCESS == swtStatus) ? E_OK : E_NOT_OK;
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: STDLIB & MATH (os/stdlib.h)
 *==================================================================================================*/

void *os_malloc(size_t size)
{
    if (size == 0U)
    {
        return NULL;
    }
    return pvPortMalloc(size);
}

void os_free(void *p)
{
    if (p != NULL)
    {
        vPortFree(p);
    }
}

long int os_random(void)
{
    uint32_t lsb = g_srp_lfsr_state & 1UL;
    g_srp_lfsr_state >>= 1U;
    if (lsb != 0UL)
    {
        g_srp_lfsr_state ^= 0xB4000000UL;
    }
    return (long int)(g_srp_lfsr_state & 0x7FFFFFFFUL);
}

int os_abs(int j)
{
    return (j < 0) ? -j : j;
}

double os_fabs(double j)
{
    return (j < 0.0) ? -j : j;
}

long long int os_llabs(long long int j)
{
    return (j < 0LL) ? -j : j;
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: STRING (os/string.h)
 *==================================================================================================*/

void *os_memset(void *s, int c, size_t n)              { return memset(s, c, n); }
void *os_memcpy(void *d, const void *s, size_t n)      { return memcpy(d, s, n); }
void *os_memmove(void *d, const void *s, size_t n)     { return memmove(d, s, n); }
int   os_memcmp(const void *s1, const void *s2, size_t n) { return memcmp(s1, s2, n); }
int   os_strnlen(const char *s, size_t maxlen)         { size_t i = 0U; while ((i < maxlen) && (s[i] != '\0')) { i++; } return (int)i; }

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: LOG (os/log.h)
 *==================================================================================================*/

/* Project links newlib-nano "noio" (no console). Log calls are counted only;
 * inspect g_srp_log_count in the debugger. Hook a UART here if needed. */
volatile uint32_t g_srp_log_count = 0U;

void _os_log(const char *level, const char *func, const char *component, const char *format, ...)
{
    (void)level; (void)func; (void)component; (void)format;
    g_srp_log_count++;
}

void _os_log_raw(const char *format, ...)
{
    (void)format;
    g_srp_log_count++;
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: NET PORT MTU (os/net.h)
 *==================================================================================================*/

unsigned int net_port_mtu_get(struct net_tx *tx, unsigned int port_id)
{
    (void)tx;
    (void)port_id;
    return 1500U; /* SJA1110 standard Ethernet MTU */
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: CLOCK (os/clock.h)
 *==================================================================================================*/

int os_clock_setfreq(os_clock_id_t id, s32 ppb)
{
    (void)id;
    (void)ppb;
    return 0;
}

int os_clock_setoffset(os_clock_id_t id, s64 offset)
{
    (void)id;
    (void)offset;
    return 0;
}

int os_clock_gettime32(os_clock_id_t id, u32 *ns)
{
    u64 ns64 = 0ULL;
    (void)id;

    if (ns == NULL)
    {
        return -1;
    }
    (void)os_clock_gettime64(id, &ns64);
    *ns = (u32)(ns64 & 0xFFFFFFFFULL);
    return 0;
}

int os_clock_gettime64(os_clock_id_t id, u64 *ns)
{
    TickType_t ticks;
    (void)id;

    if (ns == NULL)
    {
        return -1;
    }
    ticks = xTaskGetTickCount();
    *ns = ((u64)ticks * (u64)NSECS_PER_SEC) / (u64)configTICK_RATE_HZ;
    return 0;
}

int os_clock_convert_multi(os_clock_id_t clk_id_src, u64 *ns_src, unsigned int num_ts, os_clock_id_t clk_id_dst, u64 *ns_dst)
{
    unsigned int i;
    (void)clk_id_src;
    (void)clk_id_dst;

    if ((ns_src == NULL) || (ns_dst == NULL))
    {
        return -1;
    }
    for (i = 0U; i < num_ts; i++)
    {
        ns_dst[i] = ns_src[i];
    }
    return 0;
}

os_clock_id_t logical_port_to_local_clock(unsigned int port_id)
{
    (void)port_id;
    return OS_CLOCK_LOCAL_BR_0;
}

os_clock_id_t logical_port_to_gptp_clock(unsigned int port_id, unsigned int domain)
{
    (void)port_id;
    return (domain == 0U) ? OS_CLOCK_GPTP_BR_0_0 : OS_CLOCK_GPTP_BR_0_1;
}

os_clock_id_t logical_port_to_avtp_clock(unsigned int port_id)
{
    (void)port_id;
    return OS_CLOCK_AVTP_MEDIA_0;
}

unsigned int os_clock_adjust_mode(os_clock_id_t id)
{
    (void)id;
    return 0U;
}

bool os_clock_is_match(os_clock_id_t clk_id_0, os_clock_id_t clk_id_1)
{
    return (clk_id_0 == clk_id_1);
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: TIMER (os/timer.h)
 *==================================================================================================*/

int os_timer_create(struct os_timer *t, os_clock_id_t id, unsigned int flags,
                    void (*func)(struct os_timer *t, int count), unsigned long priv)
{
    uint32_t i;
    (void)flags;
    (void)priv;

    if ((t == NULL) || (func == NULL))
    {
        return -1;
    }

    for (i = 0U; i < SRP_MAX_OS_TIMERS; i++)
    {
        if (!g_srp_timers[i].in_use)
        {
            g_srp_timers[i].in_use    = TRUE;
            g_srp_timers[i].active    = FALSE;
            g_srp_timers[i].periodic  = FALSE;
            g_srp_timers[i].period_ms = 0U;
            g_srp_timers[i].last_tick = 0U;
            g_srp_timers[i].timer     = t;

            t->clk_id    = (int)id;
            t->handle    = (void *)&g_srp_timers[i];
            t->q_handle  = NULL;
            t->event_err = 0U;
            t->func      = func;
            t->start     = NULL;
            t->stop      = NULL;
            t->destroy   = NULL;
            return 0;
        }
    }

    return -1;
}

int os_timer_start(struct os_timer *t, u64 value, u64 interval_p, u64 interval_q, unsigned int flags)
{
    srp_os_timer_slot_t *slot;
    u64 period_ns;
    uint32_t period_ms;
    (void)flags;

    if ((t == NULL) || (t->handle == NULL))
    {
        return -1;
    }

    slot = (srp_os_timer_slot_t *)t->handle;
    if (!slot->in_use)
    {
        return -1;
    }

    if (interval_p > 0ULL)
    {
        u64 div_q = (interval_q > 0ULL) ? interval_q : 1ULL;
        period_ns = interval_p / div_q;
        slot->periodic = TRUE;
    }
    else
    {
        period_ns = value;
        slot->periodic = FALSE;
    }

    period_ms = (uint32_t)(period_ns / (u64)NSECS_PER_MS);
    if (period_ms == 0U)
    {
        period_ms = 1U;
    }

    slot->period_ms = period_ms;
    slot->last_tick = xTaskGetTickCount();
    slot->active    = TRUE;

    return 0;
}

void os_timer_stop(struct os_timer *t)
{
    srp_os_timer_slot_t *slot;

    if ((t != NULL) && (t->handle != NULL))
    {
        slot = (srp_os_timer_slot_t *)t->handle;
        slot->active = FALSE;
    }
}

void os_timer_destroy(struct os_timer *t)
{
    srp_os_timer_slot_t *slot;

    if ((t != NULL) && (t->handle != NULL))
    {
        slot = (srp_os_timer_slot_t *)t->handle;
        slot->active = FALSE;
        slot->in_use = FALSE;
        slot->timer  = NULL;
        t->handle    = NULL;
    }
}

void os_timer_process(struct os_timer *t)
{
    if ((t != NULL) && (t->func != NULL))
    {
        t->func(t, 1);
    }
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: IPC (os/ipc.h)
 *==================================================================================================*/

struct ipc_desc *ipc_alloc(struct ipc_tx const *tx, unsigned int size)
{
    struct ipc_desc *desc;
    unsigned int alloc_bytes;
    (void)tx;

    alloc_bytes = sizeof(struct ipc_desc) + ((size > sizeof(union { uint8_t d[1]; })) ? size : 0U);
    desc = (struct ipc_desc *)os_malloc(alloc_bytes);
    if (desc != NULL)
    {
        os_memset(desc, 0, alloc_bytes);
    }
    return desc;
}

void ipc_free(void const *ipc, struct ipc_desc *desc)
{
    (void)ipc;
    if (desc != NULL)
    {
        os_free(desc);
    }
}

int ipc_rx_init(struct ipc_rx *rx, ipc_id_t id, void (*func)(struct ipc_rx const *, struct ipc_desc *), unsigned long priv)
{
    if ((rx == NULL) || (id >= IPC_ID_MAX))
    {
        return -1;
    }

    rx->func     = func;
    rx->priv     = priv;
    rx->ipc_slot = (void *)&g_srp_ipc_channels[id];

    g_srp_ipc_channels[id].id         = id;
    g_srp_ipc_channels[id].rx         = rx;
    g_srp_ipc_channels[id].registered = TRUE;

    return 0;
}

int ipc_rx_init_no_notify(struct ipc_rx *rx, ipc_id_t id)
{
    return ipc_rx_init(rx, id, NULL, 0UL);
}

void ipc_rx_exit(struct ipc_rx *rx)
{
    srp_ipc_channel_t *ch;

    if ((rx != NULL) && (rx->ipc_slot != NULL))
    {
        ch = (srp_ipc_channel_t *)rx->ipc_slot;
        while (ch->count > 0U)
        {
            struct ipc_desc *d = ch->queue[ch->tail];
            ch->tail = (uint8_t)((ch->tail + 1U) % SRP_IPC_QUEUE_DEPTH);
            ch->count--;
            os_free(d);
        }
        ch->rx = NULL;
        rx->ipc_slot = NULL;
    }
}

int ipc_tx_init(struct ipc_tx *tx, ipc_id_t id)
{
    if ((tx == NULL) || (id >= IPC_ID_MAX))
    {
        return -1;
    }

    tx->ipc_slot = (void *)&g_srp_ipc_channels[id];
    g_srp_ipc_channels[id].id         = id;
    g_srp_ipc_channels[id].tx         = tx;
    g_srp_ipc_channels[id].registered = TRUE;

    return 0;
}

void ipc_tx_exit(struct ipc_tx *tx)
{
    if (tx != NULL)
    {
        tx->ipc_slot = NULL;
    }
}

int ipc_tx_connect(struct ipc_tx *tx, struct ipc_rx *rx)
{
    (void)tx;
    (void)rx;
    return 0;
}

int ipc_tx(struct ipc_tx const *tx, struct ipc_desc *desc)
{
    srp_ipc_channel_t *ch;

    if ((tx == NULL) || (desc == NULL) || (tx->ipc_slot == NULL))
    {
        return -IPC_TX_ERR_UNKNOWN;
    }

    ch = (srp_ipc_channel_t *)tx->ipc_slot;

    /* Intercept IPC_MAC_SERVICE_GET_STATUS sent by srp_port_init() and reply with live SJA1110 port status */
    if ((ch->id == IPC_MEDIA_STACK_MAC_SERVICE_BRIDGE) && (desc->type == IPC_MAC_SERVICE_GET_STATUS))
    {
        unsigned int logical_port = desc->u.mac_service_get_status.port_id;
        uint8 swt_port = 0U;

        if (srp_logical_to_swt_port(logical_port, &swt_port) == 0)
        {
            srp_ipc_channel_t *rx_ch = &g_srp_ipc_channels[IPC_MAC_SERVICE_BRIDGE_MEDIA_STACK];
            if ((rx_ch->rx != NULL) && (rx_ch->count < SRP_IPC_QUEUE_DEPTH))
            {
                struct ipc_desc *resp = ipc_alloc(NULL, sizeof(struct ipc_mac_service_status));
                if (resp != NULL)
                {
                    boolean link_up = TRUE;
                    uint64_t rate_bps = 100000000ULL;
                    srp_query_swt_port_link(swt_port, &link_up, &rate_bps);

                    g_srp_port_link_up[swt_port - 1U]  = link_up;
                    g_srp_port_rate_bps[swt_port - 1U] = rate_bps;

                    resp->type = IPC_MAC_SERVICE_STATUS;
                    resp->len  = sizeof(struct ipc_mac_service_status);
                    resp->u.mac_service_status.port_id        = (u16)logical_port;
                    resp->u.mac_service_status.operational    = link_up ? 1U : 0U;
                    resp->u.mac_service_status.point_to_point = 1U;
                    resp->u.mac_service_status.rate           = (u32)rate_bps;

                    rx_ch->queue[rx_ch->head] = resp;
                    rx_ch->head = (uint8_t)((rx_ch->head + 1U) % SRP_IPC_QUEUE_DEPTH);
                    rx_ch->count++;
                }
            }
        }
        ipc_free(tx, desc);
        return 0;
    }

    if (ch->rx == NULL)
    {
        return -IPC_TX_ERR_NO_READER;
    }

    if (ch->count >= SRP_IPC_QUEUE_DEPTH)
    {
        return -IPC_TX_ERR_QUEUE_FULL;
    }

    ch->queue[ch->head] = desc;
    ch->head = (uint8_t)((ch->head + 1U) % SRP_IPC_QUEUE_DEPTH);
    ch->count++;

    return 0;
}

struct ipc_desc *__ipc_rx(struct ipc_rx const *rx)
{
    srp_ipc_channel_t *ch;
    struct ipc_desc *desc = NULL;

    if ((rx == NULL) || (rx->ipc_slot == NULL))
    {
        return NULL;
    }

    ch = (srp_ipc_channel_t *)rx->ipc_slot;
    if (ch->count > 0U)
    {
        desc = ch->queue[ch->tail];
        ch->tail = (uint8_t)((ch->tail + 1U) % SRP_IPC_QUEUE_DEPTH);
        ch->count--;
    }

    return desc;
}

void ipc_rx(struct ipc_rx const *rx)
{
    struct ipc_desc *desc;

    if ((rx == NULL) || (rx->func == NULL))
    {
        return;
    }

    while ((desc = __ipc_rx(rx)) != NULL)
    {
        rx->func(rx, desc);
    }
}

/*==================================================================================================
 *                          OSAL IMPLEMENTATION: NETWORK TX/RX (os/net.h)
 *==================================================================================================*/

int net_rx_init(struct net_rx *rx, struct net_address *addr,
                void (*func)(struct net_rx *, struct net_rx_desc *), unsigned long priv)
{
    (void)priv;

    if ((rx == NULL) || (addr == NULL))
    {
        return -1;
    }

    rx->func       = func;
    rx->func_multi = NULL;
    rx->socket     = (void *)(uintptr_t)addr->port;
    rx->batch      = 1U;

    if (addr->port < CFG_MAX_LOGICAL_PORTS)
    {
        g_srp_net_rx_by_port[addr->port] = rx;
    }

    return 0;
}

void net_rx_exit(struct net_rx *rx)
{
    unsigned int port_id;

    if (rx != NULL)
    {
        port_id = (unsigned int)(uintptr_t)rx->socket;
        if (port_id < CFG_MAX_LOGICAL_PORTS)
        {
            g_srp_net_rx_by_port[port_id] = NULL;
        }
        rx->func = NULL;
    }
}

int net_tx_init(struct net_tx *tx, struct net_address *addr)
{
    if ((tx == NULL) || (addr == NULL))
    {
        return -1;
    }

    tx->func_tx_ts = NULL;
    tx->socket     = (void *)(uintptr_t)addr->port;
    tx->port_id    = addr->port;

    return 0;
}

void net_tx_exit(struct net_tx *tx)
{
    if (tx != NULL)
    {
        tx->socket = NULL;
    }
}

struct net_tx_desc *net_tx_alloc(struct net_tx *tx, unsigned int size)
{
    struct net_tx_desc *desc;
    unsigned int total_size;
    (void)tx;

    total_size = sizeof(struct net_tx_desc) + size + 16U;
    desc = (struct net_tx_desc *)os_malloc(total_size);
    if (desc != NULL)
    {
        os_memset(desc, 0, total_size);
        desc->l2_offset = (uint16_t)sizeof(struct net_tx_desc);
        desc->len       = 0U;
    }
    return desc;
}

struct net_tx_desc *net_tx_clone(struct net_tx *tx, struct net_tx_desc *src)
{
    struct net_tx_desc *dst;
    unsigned int copy_len;
    (void)tx;

    if (src == NULL)
    {
        return NULL;
    }

    copy_len = src->len + 16U;
    dst = net_tx_alloc(tx, copy_len);
    if (dst != NULL)
    {
        dst->len       = src->len;
        dst->l2_offset = src->l2_offset;
        dst->port      = src->port;
        dst->flags     = src->flags;
        os_memcpy((uint8_t *)dst + dst->l2_offset, (const uint8_t *)src + src->l2_offset, src->len);
    }
    return dst;
}

void net_tx_free(struct net_tx_desc *desc)
{
    if (desc != NULL)
    {
        os_free(desc);
    }
}

void net_rx_free(struct net_rx_desc *desc)
{
    if (desc != NULL)
    {
        os_free(desc);
    }
}

/**
 * @brief Directed SJA1110 Management Frame (0x8B8C) transmission for MRP PDUs
 */
int net_tx(struct net_tx *tx, struct net_tx_desc *desc)
{
    uint8 swt_port = 0U;
    uint8 *frame_ptr;
    uint16 frame_len;
    uint16 buf_len_needed;
    uint16 payload_len;
    uint8 *payload_buf = NULL;
    Eth_BufIdxType buf_idx = 0U;
    EthSwt_MgmtInfoType mgmt_info;
    uint8 dst_mac[6];
    Std_ReturnType status;

    if ((tx == NULL) || (desc == NULL) || (desc->len <= SRP_ETH_II_HEADER_LEN))
    {
        return -1;
    }

    if (srp_logical_to_swt_port(tx->port_id, &swt_port) < 0)
    {
        return -1;
    }

    frame_ptr = (uint8 *)desc + desc->l2_offset;
    frame_len = (uint16)desc->len;

    os_memcpy(dst_mac, frame_ptr, 6U);

    buf_len_needed = (uint16)(frame_len + SRP_ETH_HEAD_TRAIL_LEN);
    payload_len    = buf_len_needed;

    if (BUFREQ_OK != Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0,
                                         0U,
                                         &buf_idx,
                                         &payload_buf,
                                         &payload_len))
    {
        return -1;
    }

    /* Copy EtherType + MRP PDU payload starting at offset 12 of Ethernet frame */
    os_memcpy(payload_buf, &frame_ptr[12], (size_t)(frame_len - 12U));
    payload_len = (uint16)(frame_len - SRP_ETH_II_HEADER_LEN);

    mgmt_info.SwitchIdx     = SRP_SJA1110_SWT_ID;
    mgmt_info.SwitchPortIdx = swt_port;

    status = EthSwt_43_SJA11XX_SetMgmtInfo(EthConf_EthCtrlConfig_EthCtrlConfig_0, buf_idx, &mgmt_info);
    if (E_OK != status)
    {
        return -1;
    }

    status = EthSwt_43_SJA11XX_EthTxProcessFrame(EthConf_EthCtrlConfig_EthCtrlConfig_0,
                                                 buf_idx,
                                                 &payload_buf,
                                                 &payload_len);
    if (E_OK != status)
    {
        return -1;
    }

    /* Align payload buffer after SJA1110 management header insertion (matches GPTP_PORT_MsgSend) */
    os_memmove(payload_buf, &payload_buf[2], (size_t)(frame_len - 12U));

    Eth_SetPhysAddr(EthConf_EthCtrlConfig_EthCtrlConfig_0, &frame_ptr[6]);

    status = Eth_Transmit(EthConf_EthCtrlConfig_EthCtrlConfig_0,
                          buf_idx,
                          SRP_MGMT_FRAME_ETHERTYPE,
                          TRUE,
                          payload_len,
                          dst_mac);
    if (E_OK != status)
    {
        return -1;
    }

    /* Immediately confirm and release the single TX buffer descriptor (BufferCount = 1U) */
    Eth_TxConfirmation(EthConf_EthCtrlConfig_EthCtrlConfig_0);

    /* Free descriptor on successful transmission (GenAVB net_tx contract) */
    net_tx_free(desc);

    return 1;
}

int net_get_local_addr(unsigned int port_id, unsigned char *addr)
{
    if (addr == NULL)
    {
        return -1;
    }
    os_memcpy(addr, g_srp_local_mac, 6U);
    /* Embed logical port index in LSB so each Bridge port has a unique source MAC */
    addr[5] = (unsigned char)((g_srp_local_mac[5] & 0xF0U) | (port_id & 0x0FU));
    return 0;
}

int net_add_multi(struct net_rx *rx, unsigned int port_id, const unsigned char *hw_addr)
{
    (void)rx;
    (void)port_id;

    if (hw_addr != NULL)
    {
        (void)Eth_UpdatePhysAddrFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, hw_addr, ETH_ADD_TO_FILTER);
    }
    return 0;
}

int net_del_multi(struct net_rx *rx, unsigned int port_id, const unsigned char *hw_addr)
{
    (void)rx;
    (void)port_id;
    (void)hw_addr;
    return 0;
}

unsigned int net_port_priority_to_traffic_class(unsigned int port_id, uint8_t priority)
{
    const uint8_t *map;
    (void)port_id;

    if (priority >= QOS_PRIORITY_MAX)
    {
        return 0U;
    }

    map = priority_to_traffic_class_map(CFG_TRAFFIC_CLASS_MAX, CFG_SR_CLASS_MAX);
    if (map != NULL)
    {
        return (unsigned int)map[priority];
    }

    return (unsigned int)priority;
}

/*==================================================================================================
 *                 HARDWARE OFFLOAD: IEEE 802.1Qav CBS SHAPER (os/fqtss.h)
 *==================================================================================================*/

int fqtss_set_oper_idle_slope(unsigned int port_id, uint8_t traffic_class, uint64_t idle_slope)
{
    uint8 swt_port = 0U;
    Switch_Ip_StatusType status;

    if (srp_logical_to_swt_port(port_id, &swt_port) < 0)
    {
        return -1;
    }

    if (idle_slope > 0ULL)
    {
        uint32 hw_idle_slope = (idle_slope < 8ULL) ? 8UL : (uint32)idle_slope;
        status = Switch_Ip_SetCbsIdleSlope(SRP_SJA1110_SWT_ID, swt_port, traffic_class, hw_idle_slope);
    }
    else
    {
        status = Switch_Ip_DisableCbs(SRP_SJA1110_SWT_ID, swt_port, traffic_class);
    }

    return (SWITCH_STATUS_SUCCESS == status) ? 0 : -1;
}

int fqtss_stream_add(unsigned int port_id, void *stream_id, uint16_t vlan_id, uint8_t priority, uint64_t idle_slope)
{
    uint8_t tc = (uint8_t)net_port_priority_to_traffic_class(port_id, priority);
    (void)stream_id;
    (void)vlan_id;
    return fqtss_set_oper_idle_slope(port_id, tc, idle_slope);
}

int fqtss_stream_remove(unsigned int port_id, void *stream_id, uint16_t vlan_id, uint8_t priority, uint64_t idle_slope)
{
    uint8_t tc = (uint8_t)net_port_priority_to_traffic_class(port_id, priority);
    (void)stream_id;
    (void)vlan_id;
    (void)idle_slope;
    return fqtss_set_oper_idle_slope(port_id, tc, 0ULL);
}

/*==================================================================================================
 *                 HARDWARE OFFLOAD: SJA1110 L2 TCAM FDB (os/fdb.h)
 *==================================================================================================*/

static srp_fdb_shadow_t *srp_fdb_find_or_alloc(const uint8_t *address, uint16_t vid, boolean alloc_if_missing)
{
    uint32_t i;
    srp_fdb_shadow_t *free_slot = NULL;

    for (i = 0U; i < SRP_MAX_FDB_ENTRIES; i++)
    {
        if (g_srp_fdb_table[i].in_use)
        {
            if ((g_srp_fdb_table[i].vid == vid) && (os_memcmp(g_srp_fdb_table[i].mac, address, 6U) == 0))
            {
                return &g_srp_fdb_table[i];
            }
        }
        else if (free_slot == NULL)
        {
            free_slot = &g_srp_fdb_table[i];
            free_slot->tcam_index = (uint16_t)(SRP_TCAM_BASE_INDEX + i);
        }
    }

    if (alloc_if_missing && (free_slot != NULL))
    {
        os_memcpy(free_slot->mac, address, 6U);
        free_slot->vid        = vid;
        free_slot->dest_ports = 0U;
        free_slot->in_use     = TRUE;
        return free_slot;
    }

    return NULL;
}

static int srp_fdb_commit_to_hw(const srp_fdb_shadow_t *entry)
{
    Switch_Ip_SJA1110_l2ArtLockedEntryType tcamEntry;
    boolean found = FALSE;
    uint8 i;
    Switch_Ip_StatusType status;

    os_memset(&tcamEntry, 0, sizeof(tcamEntry));
    for (i = 0U; i < 6U; i++)
    {
        tcamEntry.macaddr[i]     = entry->mac[i];
        tcamEntry.macaddrMask[i] = 0xFFU;
    }
    tcamEntry.vlanid     = entry->vid;
    tcamEntry.vlanidMask = 0x0FFFU;
    tcamEntry.srcPortMask = 0U;

    (void)Switch_Ip_SearchL2EntryInTcam(SRP_SJA1110_SWT_ID, &tcamEntry, &found);
    if (!found)
    {
        tcamEntry.index = entry->tcam_index;
    }

    tcamEntry.destports = entry->dest_ports;
    tcamEntry.enfport   = FALSE;

    status = Switch_Ip_UpdateTcamEntry(SRP_SJA1110_SWT_ID, &tcamEntry);
    return (SWITCH_STATUS_SUCCESS == status) ? 0 : -1;
}

int fdb_update(unsigned int port_id, uint8_t *address, uint16_t vid, bool dynamic, genavb_fdb_port_control_t control)
{
    uint8 swt_port = 0U;
    srp_fdb_shadow_t *entry;

    if ((address == NULL) || (srp_logical_to_swt_port(port_id, &swt_port) < 0))
    {
        return -1;
    }

    entry = srp_fdb_find_or_alloc(address, vid, TRUE);
    if (entry == NULL)
    {
        return -1;
    }

    entry->dynamic = dynamic ? TRUE : FALSE;
    if (control == GENAVB_FDB_PORT_CONTROL_FORWARDING)
    {
        entry->dest_ports |= (uint16_t)(1U << swt_port);
    }
    else
    {
        entry->dest_ports &= (uint16_t)~(1U << swt_port);
    }

    return srp_fdb_commit_to_hw(entry);
}

int fdb_delete(uint8_t *address, uint16_t vid, bool dynamic)
{
    srp_fdb_shadow_t *entry;
    (void)dynamic;

    if (address == NULL)
    {
        return -1;
    }

    entry = srp_fdb_find_or_alloc(address, vid, FALSE);
    if (entry == NULL)
    {
        return 0;
    }

    entry->dest_ports = 0U;
    (void)srp_fdb_commit_to_hw(entry);
    entry->in_use = FALSE;

    return 0;
}

int fdb_read(uint8_t *address, uint16_t vid, bool *dynamic, struct genavb_fdb_port_map *map, genavb_fdb_status_t *status)
{
    srp_fdb_shadow_t *entry;
    unsigned int i;

    if ((address == NULL) || (map == NULL) || (status == NULL))
    {
        return -1;
    }

    entry = srp_fdb_find_or_alloc(address, vid, FALSE);
    if (entry == NULL)
    {
        return -1;
    }

    if (dynamic != NULL)
    {
        *dynamic = entry->dynamic ? true : false;
    }

    for (i = 0U; i < SRP_SJA1110_NUM_BR_PORTS; i++)
    {
        uint8 swt_port = (uint8)(i + 1U);
        map[i].port_id = i + SRP_SJA1110_FIRST_LOGICAL_PORT;
        map[i].control = ((entry->dest_ports & (1U << swt_port)) != 0U) ? GENAVB_FDB_PORT_CONTROL_FORWARDING : GENAVB_FDB_PORT_CONTROL_FILTERING;
    }

    *status = GENAVB_FDB_STATUS_OTHER;
    return 0;
}

int fdb_dump(uint32_t *token, uint8_t *address, uint16_t *vid, bool *dynamic, struct genavb_fdb_port_map *map, genavb_fdb_status_t *status)
{
    (void)token;
    (void)address;
    (void)vid;
    (void)dynamic;
    (void)map;
    (void)status;
    return -1;
}

/*==================================================================================================
 *                 HARDWARE OFFLOAD: SJA1110 VLAN LOOKUP TABLE (os/vlan.h)
 *==================================================================================================*/

int vlan_update(uint16_t vid, bool dynamic, struct genavb_vlan_port_map *map)
{
    Switch_Ip_SJA1110_vlanLookupTableEntryType vltEntry;
    boolean found = FALSE;
    uint16_t port_mask = (1U << SRP_SJA1110_HOST_PORT); /* Always preserve Host Port 0 */
    unsigned int i;
    Switch_Ip_StatusType status;
    (void)dynamic;

    if (map == NULL)
    {
        return -1;
    }

    os_memset(&vltEntry, 0, sizeof(vltEntry));
    (void)Switch_Ip_GetVlanLookupEntry(SRP_SJA1110_SWT_ID, vid, &vltEntry, &found);

    for (i = 0U; i < SRP_SJA1110_NUM_BR_PORTS; i++)
    {
        uint8 swt_port = 0U;
        if (srp_logical_to_swt_port(map[i].port_id, &swt_port) == 0)
        {
            if ((map[i].control == GENAVB_VLAN_ADMIN_CONTROL_REGISTERED) ||
                (map[i].control == GENAVB_VLAN_ADMIN_CONTROL_FIXED))
            {
                port_mask |= (uint16_t)(1U << swt_port);
            }
        }
    }

    vltEntry.vlanid    = vid;
    vltEntry.entryType = Switch_Ip_SJA11XX_vlanEntryType_SINGLE_INNER_TAG;
    vltEntry.vmembPort = port_mask;
    vltEntry.vlanBc    = port_mask;
    vltEntry.tagPort   = (uint16_t)(port_mask & ~(1U << SRP_SJA1110_HOST_PORT));
    vltEntry.vegrMirr  = 0U;
    vltEntry.vingMirr  = 0U;

    status = Switch_Ip_UpdateVlanLookupEntry(SRP_SJA1110_SWT_ID, &vltEntry);
    return (SWITCH_STATUS_SUCCESS == status) ? 0 : -1;
}

int vlan_delete(uint16_t vid, bool dynamic)
{
    Switch_Ip_SJA1110_vlanLookupTableEntryType vltEntry;
    Switch_Ip_StatusType status;
    (void)dynamic;

    os_memset(&vltEntry, 0, sizeof(vltEntry));
    vltEntry.vlanid    = vid;
    vltEntry.entryType = Switch_Ip_SJA11XX_vlanEntryType_INVALID;
    vltEntry.vmembPort = (1U << SRP_SJA1110_HOST_PORT);
    vltEntry.vlanBc    = (1U << SRP_SJA1110_HOST_PORT);
    vltEntry.tagPort   = 0U;

    status = Switch_Ip_UpdateVlanLookupEntry(SRP_SJA1110_SWT_ID, &vltEntry);
    return (SWITCH_STATUS_SUCCESS == status) ? 0 : -1;
}

int vlan_read(uint16_t vid, bool *dynamic, struct genavb_vlan_port_map *map)
{
    Switch_Ip_SJA1110_vlanLookupTableEntryType vltEntry;
    boolean found = FALSE;
    unsigned int i;

    if (map == NULL)
    {
        return -1;
    }

    os_memset(&vltEntry, 0, sizeof(vltEntry));
    if (SWITCH_STATUS_SUCCESS != Switch_Ip_GetVlanLookupEntry(SRP_SJA1110_SWT_ID, vid, &vltEntry, &found) || !found)
    {
        return -1;
    }

    if (dynamic != NULL)
    {
        *dynamic = true;
    }

    for (i = 0U; i < SRP_SJA1110_NUM_BR_PORTS; i++)
    {
        uint8 swt_port = (uint8)(i + 1U);
        map[i].port_id = i + SRP_SJA1110_FIRST_LOGICAL_PORT;
        map[i].control = ((vltEntry.vmembPort & (1U << swt_port)) != 0U) ? GENAVB_VLAN_ADMIN_CONTROL_REGISTERED : GENAVB_VLAN_ADMIN_CONTROL_FORBIDDEN;
    }

    return 0;
}

int vlan_dump(uint32_t *token, uint16_t *vid, bool *dynamic, struct genavb_vlan_port_map *map)
{
    (void)token;
    (void)vid;
    (void)dynamic;
    (void)map;
    return -1;
}

int vlan_port_set_default(unsigned int port_id, uint16_t vid)
{
    (void)port_id;
    (void)vid;
    return 0;
}

int vlan_port_get_default(unsigned int port_id, uint16_t *vid)
{
    (void)port_id;
    if (vid != NULL)
    {
        *vid = CFG_MVRP_VID;
    }
    return 0;
}

/*==================================================================================================
 *                          PUBLIC SJA1110 SRP PORTING API IMPLEMENTATION
 *==================================================================================================*/

Std_ReturnType SRP_PORT_Init(void)
{
    unsigned int i;
    static const unsigned int br_logical_ports[SRP_SJA1110_NUM_BR_PORTS] = CFG_BR_LOGICAL_PORT_LIST;

    os_memset(g_srp_net_rx_by_port, 0, sizeof(g_srp_net_rx_by_port));
    os_memset(g_srp_timers, 0, sizeof(g_srp_timers));
    os_memset(g_srp_ipc_channels, 0, sizeof(g_srp_ipc_channels));
    os_memset(g_srp_fdb_table, 0, sizeof(g_srp_fdb_table));

    /* 1. Initialize SJA1110 hardware multicast traps for MSRP, MVRP, and MMRP */
    (void)SRP_PORT_ConfigureHwTrap();

    /* 2. Initialize common FQTSS bandwidth tracking tables */
    (void)common_fqtss_init();

    /* 3. Build 8-port SJA1110 Bridge SRP configuration (is_bridge = 1) */
    os_memset(&g_srp_bridge_cfg, 0, sizeof(g_srp_bridge_cfg));
    g_srp_bridge_cfg.log_level          = srp_CFG_LOG;
    g_srp_bridge_cfg.is_bridge          = 1U;
    g_srp_bridge_cfg.port_max           = SRP_SJA1110_NUM_BR_PORTS;
    g_srp_bridge_cfg.management_enabled = 1U;

    g_srp_bridge_cfg.mrp_cfg.leave_timeout = CFG_MRP_LVTIMER_VAL_802_1Q_DEFAULT;

    g_srp_bridge_cfg.msrp_cfg.is_bridge  = 1U;
    g_srp_bridge_cfg.msrp_cfg.port_max   = SRP_SJA1110_NUM_BR_PORTS;
    g_srp_bridge_cfg.msrp_cfg.flags      = 0U;
    g_srp_bridge_cfg.msrp_cfg.enabled    = true;

    g_srp_bridge_cfg.mvrp_cfg.is_bridge  = 1U;
    g_srp_bridge_cfg.mvrp_cfg.port_max   = SRP_SJA1110_NUM_BR_PORTS;

    for (i = 0U; i < SRP_SJA1110_NUM_BR_PORTS; i++)
    {
        g_srp_bridge_cfg.logical_port_list[i]          = br_logical_ports[i];
        g_srp_bridge_cfg.msrp_cfg.logical_port_list[i] = br_logical_ports[i];
        g_srp_bridge_cfg.mvrp_cfg.logical_port_list[i] = br_logical_ports[i];
    }

    /* 4. Initialize SRP Bridge instance (MSRP + MVRP + MMRP + Timer Pool) */
    g_srp_bridge_ctx = (struct srp_ctx *)srp_init(&g_srp_bridge_cfg, 0UL);
    if (g_srp_bridge_ctx == NULL)
    {
        return E_NOT_OK;
    }

    /* 5. Process initial IPC_MAC_SERVICE_STATUS notifications queued during srp_init() */
    SRP_PORT_Periodic();

    return E_OK;
}

boolean SRP_PORT_RxIndication(uint8 u8CtrlIdx,
                              Eth_FrameType u16FrameType,
                              boolean bIsBroadcast,
                              const uint8 *cpu8PhysAddr,
                              const Eth_DataType *cpu8Data,
                              uint16 u16LenByte)
{
    uint16 inner_ethertype = (uint16)u16FrameType;
    const uint8 *pdu_ptr   = (const uint8 *)cpu8Data;
    uint16 pdu_len         = u16LenByte;
    EthSwt_MgmtObjectType *prRxMgmt = NULL;
    uint8 swt_port = 0U;
    unsigned int logical_port;
    struct net_rx_desc *desc;
    struct eth_hdr *eth;
    const uint8 *dst_mac;
    (void)bIsBroadcast;

    if ((cpu8PhysAddr == NULL) || (cpu8Data == NULL) || (u16LenByte == 0U))
    {
        return FALSE;
    }

    /* Support both untagged and 802.1Q VLAN-tagged (0x8100) MRP frames */
    if (inner_ethertype == 0x8100U)
    {
        if (u16LenByte <= SRP_VLAN_TAG_LEN)
        {
            return FALSE;
        }
        inner_ethertype = (uint16)(((uint16)pdu_ptr[2] << 8U) | (uint16)pdu_ptr[3]);
        pdu_ptr += SRP_VLAN_TAG_LEN;
        pdu_len = (uint16)(u16LenByte - SRP_VLAN_TAG_LEN);
    }

    /* Fast-path filter: only consume MSRP (0x22EA), MVRP (0x88F5), and MMRP (0x88F6).
     * Leave gPTP (0x88F7) untouched so GPTP_PORT_RxIndication can read its RxMgmtObject!
     */
    if (inner_ethertype == ETHERTYPE_MSRP)
    {
        dst_mac = g_msrp_mc_mac;
    }
    else if (inner_ethertype == ETHERTYPE_MVRP)
    {
        dst_mac = g_mvrp_mc_mac;
    }
    else if (inner_ethertype == ETHERTYPE_MMRP)
    {
        dst_mac = g_mmrp_mc_mac;
    }
    else
    {
        return FALSE;
    }

    /* Retrieve ingress SwitchPortIdx from SJA1110 0x8B8C Management Object */
    if ((Std_ReturnType)E_OK == EthSwt_43_SJA11XX_GetRxMgmtObject(u8CtrlIdx, (Eth_DataType *)cpu8Data, &prRxMgmt))
    {
        if ((prRxMgmt != NULL) && ((Std_ReturnType)E_OK == prRxMgmt->Validation.MgmtInfoValid))
        {
            swt_port = prRxMgmt->MgmtInfo.SwitchPortIdx;
        }
        if (prRxMgmt != NULL)
        {
            prRxMgmt->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        }
    }

    if ((swt_port < SRP_SJA1110_FIRST_SW_PORT) || (swt_port > SRP_SJA1110_NUM_BR_PORTS))
    {
        return TRUE;
    }

    if (g_srp_rx_count >= SRP_RX_QUEUE_DEPTH)
    {
        return TRUE;
    }

    logical_port = (unsigned int)swt_port + 1U;

    desc = (struct net_rx_desc *)os_malloc(sizeof(struct net_rx_desc) + sizeof(struct eth_hdr) + pdu_len);
    if (desc != NULL)
    {
        os_memset(desc, 0, sizeof(struct net_rx_desc));
        desc->l2_offset = (uint16_t)sizeof(struct net_rx_desc);
        desc->l3_offset = (uint16_t)(desc->l2_offset + sizeof(struct eth_hdr));
        desc->len       = (uint16_t)(sizeof(struct eth_hdr) + pdu_len);
        desc->ethertype = inner_ethertype;
        desc->port      = logical_port;

        eth = (struct eth_hdr *)((uint8_t *)desc + desc->l2_offset);
        os_memcpy(eth->dst, dst_mac, 6U);
        os_memcpy(eth->src, cpu8PhysAddr, 6U);
        eth->type = htons(inner_ethertype);

        os_memcpy((uint8_t *)desc + desc->l3_offset, pdu_ptr, pdu_len);

        taskENTER_CRITICAL();
        if (g_srp_rx_count < SRP_RX_QUEUE_DEPTH)
        {
            g_srp_rx_ring[g_srp_rx_head] = desc;
            g_srp_rx_head = (uint8_t)((g_srp_rx_head + 1U) % SRP_RX_QUEUE_DEPTH);
            g_srp_rx_count++;
            desc = NULL;
        }
        taskEXIT_CRITICAL();

        if (desc != NULL)
        {
            os_free(desc);
        }
    }

    return TRUE;
}

void SRP_PORT_Periodic(void)
{
    uint32_t i;
    TickType_t now_tick;

    if (g_srp_bridge_ctx == NULL)
    {
        return;
    }

    now_tick = xTaskGetTickCount();

    /* 1. Dispatch queued MRP RX frames to srp_net_rx */
    while (g_srp_rx_count > 0U)
    {
        struct net_rx_desc *desc = NULL;
        struct net_rx *rx = NULL;

        taskENTER_CRITICAL();
        if (g_srp_rx_count > 0U)
        {
            desc = g_srp_rx_ring[g_srp_rx_tail];
            g_srp_rx_tail = (uint8_t)((g_srp_rx_tail + 1U) % SRP_RX_QUEUE_DEPTH);
            g_srp_rx_count--;
        }
        taskEXIT_CRITICAL();

        if (desc != NULL)
        {
            if (desc->port < CFG_MAX_LOGICAL_PORTS)
            {
                rx = g_srp_net_rx_by_port[desc->port];
            }

            if ((rx != NULL) && (rx->func != NULL))
            {
                rx->func(rx, desc);
            }
            else
            {
                net_rx_free(desc);
            }
        }
    }

    /* 2. Dispatch pending IPC messages (MAC status, MSRP/MVRP control, Managed Objects) */
    for (i = 0U; i < (uint32_t)IPC_ID_MAX; i++)
    {
        if (g_srp_ipc_channels[i].registered &&
            (g_srp_ipc_channels[i].rx != NULL) &&
            (g_srp_ipc_channels[i].count > 0U))
        {
            ipc_rx(g_srp_ipc_channels[i].rx);
        }
    }

    /* 3. Process deterministic software timers (MRP Join / Leave / LeaveAll / Periodic timers) */
    for (i = 0U; i < SRP_MAX_OS_TIMERS; i++)
    {
        srp_os_timer_slot_t *slot = &g_srp_timers[i];
        if (slot->in_use && slot->active && (slot->timer != NULL) && (slot->timer->func != NULL))
        {
            TickType_t elapsed_ms = now_tick - slot->last_tick;
            if (elapsed_ms >= (TickType_t)slot->period_ms)
            {
                int count = (int)(elapsed_ms / (TickType_t)slot->period_ms);
                if (count < 1)
                {
                    count = 1;
                }

                if (slot->periodic)
                {
                    slot->last_tick += (TickType_t)((uint32_t)count * slot->period_ms);
                }
                else
                {
                    slot->active = FALSE;
                }

                slot->timer->func(slot->timer, count);
            }
        }
    }

    /* 4. Periodically poll SJA1110 port link/speed changes and notify SRP if changed */
    if ((now_tick - g_srp_last_link_poll_tick) >= pdMS_TO_TICKS(SRP_LINK_POLL_PERIOD_MS))
    {
        g_srp_last_link_poll_tick = now_tick;
        for (i = 0U; i < SRP_SJA1110_NUM_BR_PORTS; i++)
        {
            uint8 swt_port = (uint8)(i + 1U);
            boolean link_up = TRUE;
            uint64_t rate_bps = 100000000ULL;

            srp_query_swt_port_link(swt_port, &link_up, &rate_bps);
            if ((link_up != g_srp_port_link_up[i]) || (rate_bps != g_srp_port_rate_bps[i]))
            {
                srp_ipc_channel_t *rx_ch = &g_srp_ipc_channels[IPC_MAC_SERVICE_BRIDGE_MEDIA_STACK];
                g_srp_port_link_up[i]  = link_up;
                g_srp_port_rate_bps[i] = rate_bps;

                if ((rx_ch->rx != NULL) && (rx_ch->count < SRP_IPC_QUEUE_DEPTH))
                {
                    struct ipc_desc *resp = ipc_alloc(NULL, sizeof(struct ipc_mac_service_status));
                    if (resp != NULL)
                    {
                        resp->type = IPC_MAC_SERVICE_STATUS;
                        resp->len  = sizeof(struct ipc_mac_service_status);
                        resp->u.mac_service_status.port_id        = (u16)(i + SRP_SJA1110_FIRST_LOGICAL_PORT);
                        resp->u.mac_service_status.operational    = link_up ? 1U : 0U;
                        resp->u.mac_service_status.point_to_point = 1U;
                        resp->u.mac_service_status.rate           = (u32)rate_bps;

                        rx_ch->queue[rx_ch->head] = resp;
                        rx_ch->head = (uint8_t)((rx_ch->head + 1U) % SRP_IPC_QUEUE_DEPTH);
                        rx_ch->count++;
                    }
                }
            }
        }
    }
}

int SRP_PORT_SendIpcMessage(unsigned int ipc_id, uint32_t type, const void *payload, unsigned int len)
{
    srp_ipc_channel_t *ch;
    struct ipc_desc *desc;

    if (ipc_id >= (unsigned int)IPC_ID_MAX)
    {
        return -1;
    }

    ch = &g_srp_ipc_channels[ipc_id];
    if ((ch->rx == NULL) || (ch->count >= SRP_IPC_QUEUE_DEPTH))
    {
        return -1;
    }

    desc = ipc_alloc(NULL, len);
    if (desc == NULL)
    {
        return -1;
    }

    desc->type  = type;
    desc->len   = len;
    desc->flags = 0U;
    if ((payload != NULL) && (len > 0U))
    {
        os_memcpy(desc->u.data, payload, len);
    }

    ch->queue[ch->head] = desc;
    ch->head = (uint8_t)((ch->head + 1U) % SRP_IPC_QUEUE_DEPTH);
    ch->count++;

    return 0;
}
