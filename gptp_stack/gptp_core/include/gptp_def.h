/*
 * Copyright 2019-2025 NXP
 *
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifndef GPTP_DEF
    #define GPTP_DEF

#include <stddef.h>
#include <stdbool.h>
#include "BasicTypes.h"
#include "gptp_component_cfg.h"
#include "gptp_port_def.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*
 * Memory Analysis Assumptions:
 * - Worst case scenario assumed: compiling for 64-bit architecture.
 * - Implications:
 *   - Single boolean inside a structure has 7 bytes of padding.
 *   - Pointers take 8 bytes instead of the typical 4 bytes.
 *   - All elements need to be divisible by 8 for smooth array indexing over
 *     structures.
 * - Memory Layout:
 *   - Structures are aligned to 8-byte boundaries to optimize memory access.
 *     This alignment ensures efficient use of the CPU's memory cache.
 * - Enum Representation:
 *   - Enum members still take only 4 bytes despite being compiled for 64-bit
 *     architecture. This is due to the representation of enums, which
 *     is typically of int type.
 */

/*!
 * @name Product detail string lengths
 * @{
 */
/*! Manufacturer identity string length */
#define GPTP_DEF_MAN_IDENTITY_LENGTH    3u
/*! Product description string length */
#define GPTP_DEF_PROD_DESC_LENGTH       64u
/*! Product revision string length */
#define GPTP_DEF_PROD_REV_LENGTH        32u
/*! @} */

/*!
 * @name PTP message parts length
 * @{
 */
/*! ETH II length */
#define GPTP_DEF_ETH_II_LEN             14u
/*! gPTP Sync message length */
#define GPTP_DEF_SYNC_MSG_LEN           44u
/*! gPTP Pdelay request message length */
#define GPTP_DEF_PDELAY_REQ_MSG_LEN     54u
/*! gPTP Pdelay response message length */
#define GPTP_DEF_PDELAY_RESP_MSG_LEN    54u
/*! gPTP Follow up message length */
#define GPTP_DEF_FOLLOW_UP_MSG_LEN      76u
/*! gPTP Pdelay follow up message length */
#define GPTP_DEF_PDELAY_FUP_MSG_LEN     54u
/*! gPTP Signaling message interval length */
#define GPTP_DEF_SIGNALING_MSG_LEN      60u
/*! @} */

/*!
 * @name Flags values for specific messages
 * @{
 */
/*! 'flags' value for Sync message */
#define GPTP_DEF_SYNC_FLAGS             0x0208
/*! 'flags' value for Follow-up message */
#define GPTP_DEF_FUP_FLAGS              0x0008
/*! 'flags' value for Pdelay request message */
#define GPTP_DEF_PDELAY_REQ_FLAGS       0x0008
/*! 'flags' value for Pdelay response message */
#define GPTP_DEF_PDELAY_RESP_FLAGS      0x0208
/*! 'flags' value for Pdelay response follow-up message */
#define GPTP_DEF_PDELAY_RESP_FUP_FLAGS  0x0008
/*! 'flags' value for Signaling message */
#define GPTP_DEF_SIGNALING_FLAGS        0x0008
/*! 'flags' value for Signaling message TLV */
#define GPTP_DEF_SIG_TLV_FLAGS          0x03
/*! @} */

/*!
 * @name Input sizes for buffer length calculations
 * @{
 */
/*! VLAN tag length including Ethtype */
#define GPTP_DEF_ETH_VLAN_LEN           4u
/*! VLAN tag length excluding Ethtype */
#define GPTP_DEF_ETH_TPID_LEN           2u
/*! Number of cascaded switches (depth of the cascade) */
#define GPTP_DEF_NUM_CASCADE_SW         2u
/*! Header for the switch length */
#define GPTP_DEF_HEADER_LEN             4u
/*! Trailed for the switch length */
#define GPTP_DEF_TRAILER_LEN            (1u + (GPTP_DEF_NUM_CASCADE_SW * 3u))
/*! Header + Trailer length */
#define GPTP_DEF_HEAD_TRAIL_LEN         (GPTP_DEF_HEADER_LEN + GPTP_DEF_TRAILER_LEN)
/*! @} */

/*!
 * @name Size of buffers for PTP messages
 * @{
 */
/*! Length of TX buffer for Sync message */
#define GPTP_DEF_TX_BUF_LEN_SYNC        (((GPTP_DEF_SYNC_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! Length of TX buffer for Pdelay request message */
#define GPTP_DEF_TX_BUF_LEN_PD_RQ       (((GPTP_DEF_PDELAY_REQ_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! Length of TX buffer for Pdelay response message */
#define GPTP_DEF_TX_BUF_LEN_PD_RSP      (((GPTP_DEF_PDELAY_RESP_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! Length of TX buffer for Follow-up message */
#define GPTP_DEF_TX_BUF_LEN_FUP         (((GPTP_DEF_FOLLOW_UP_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! Length of TX buffer for Pdelay follow-up message */
#define GPTP_DEF_TX_BUF_LEN_PD_FUP      (((GPTP_DEF_PDELAY_FUP_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! Length of TX buffer for Signaling message */
#define GPTP_DEF_TX_BUF_LEN_SIGNL       (((GPTP_DEF_SIGNALING_MSG_LEN + GPTP_DEF_ETH_II_LEN) + GPTP_DEF_HEAD_TRAIL_LEN) + GPTP_DEF_ETH_VLAN_LEN)
/*! @} */

/*!
 * @name Various bit masks (count of low bits "L", count of high bits "H")
 * @{
 */
/*! Bit mask, upper 16 bits low, lower 48 bits high */
#define GPTP_DEF_BIT_MASK_16L_48H       (0x0000FFFFFFFFFFFFu)
/*! Bit mask, upper 32 bits low, lower 32 bits high */
#define GPTP_DEF_BIT_MASK_32L_32H       (0x00000000FFFFFFFFu)
/*! Bit mask, upper 48 bits low, lower 16 bits high */
#define GPTP_DEF_BIT_MASK_48L_16H       (0x000000000000FFFFu)
/*! Bit mask, upper 56 bits low, lower 8 bits high */
#define GPTP_DEF_BIT_MASK_56L_8H        (0x00000000000000FFu)
/*! Bit mask, upper 32 bits high, lower 32 bits low */
#define GPTP_DEF_BIT_MASK_32H_32L       (0xFFFFFFFF00000000u)
/*! Bit mask, upper 8 bits low, lower 24 bits high */
#define GPTP_DEF_BIT_MASK_8L_24H        0x00FFFFFFu
/*! Bit mask, upper 16 bits low, lower 16 bits high */
#define GPTP_DEF_BIT_MASK_16L_16H       0x0000FFFFu
/*! Bit mask, upper 24 bits low, lower 8 bits high */
#define GPTP_DEF_BIT_MASK_24L_8H        0x000000FFu
/*! @} */

/*!
 * @name Various limits of integer types
 * @{
 */
/*! INT32 min value */
#define GPTP_DEF_INT32_MIN              (-2147483647 -1)
/*! INT32 max value */
#define GPTP_DEF_INT32_MAX              (2147483647)
/*! @} */

/*!
 * @name Pre-calculated float constants
 * @{
 */
/*! 2^(-41) */
#define GPTP_DEF_POW_2_M41              (4.5474735e-13)
/*! 2^(41) */
#define GPTP_DEF_POW_2_41               (2.1990233e+12)
/*! @} */

/*!
 * @name Sync machine roles
 * @{
 */
/*! Sync state machine master */
#define GPTP_DEF_PTP_MASTER             (true)
/*! Sync state machine slave */
#define GPTP_DEF_PTP_SLAVE              (false)
/*! @} */

/*!
 * @name PTP Messaging interval limits
 * @{
 */
/*! Minimum Pdelay interval limit - 31.25ms */
#define GPTP_DEF_LOG_PDEL_INT_MIN       (-5)
/*! Maximum Pdelay interval limit - 8s*/
#define GPTP_DEF_LOG_PDEL_INT_MAX       3
/*! Minimum Sync interval limit - 31.25ms */
#define GPTP_DEF_LOG_SYNC_INT_MIN       (-5)
/*! Maximum Sync interval limit - 1s*/
#define GPTP_DEF_LOG_SYNC_INT_MAX       0
/*! @} */

/*!
 * @name Frame ID start and maximum ranges for messages
 * @{
 */
/*! Sync frame ID start position */
#define GPTP_DEF_FID_SYNC_START         0u
/*! Sync frame ID end position */
#define GPTP_DEF_FID_SYNC_MAX           150u
/*! Pdelay request start position */
#define GPTP_DEF_FID_PDREQ_START        150u
/*! Pdelay request end position */
#define GPTP_DEF_FID_PDREQ_MAX          200u
/*! Pdelay response start position */
#define GPTP_DEF_FID_PDRESP_START       200u
/*! Pdelay response end position */
#define GPTP_DEF_FID_PDRESP_MAX         250u
/*! @} */

/*!
 * @name Debug messages verbosity levels
 * @{
 */
/*! Highest verbosity, containing the synchronization status messages */
#define GPTP_DEBUG_MSGTYPE_SYNC         3
/*! High verbosity, containing informative messages */
#define GPTP_DEBUG_MSGTYPE_INFO         2
/*! Medium verbosity, containing state messages */
#define GPTP_DEBUG_MSGTYPE_STATE        1
/*! Low verbosity, Error messages only */
#define GPTP_DEBUG_MSGTYPE_ERROR        0
/*! @} */

/*!
 * @name Misc gPTP constants
 * @{
 */

/*! Period of Offset estimation calculation */
#define GPTP_DEF_CALC_PERIOD_100_MS     100000000u

/*! Transport specific value for the check */
#define GPTP_DEF_TRANSPORT_SPEC_1       0x10

/*! Maximum start-up timeout [s] */
#define GPTP_DEF_STARTUP_TIMEOUT_MAX    20

/*! Signaling message value for stop sending */
#define GPTP_DEF_SIG_TLV_STOP_SENDING   127
/*! Signaling message value for setting to initial value */
#define GPTP_DEF_SIG_TLV_SET_TO_INIT    126
/*! Signaling message value for not changing interval */
#define GPTP_DEF_SIG_TLV_NOT_CHANGE     (-128)

/*! Count of nanoseconds in 1.5 seconds */
#define GPTP_DEF_1S5_IN_NS              1500000000u
/*! Count of nanoseconds in 1 second */
#define GPTP_DEF_NS_IN_SECONDS          1000000000u
/*! Count of nanoseconds in 10 miliseconds */
#define GPTP_DEF_10_MS_IN_NS            10000000u

/*! First sequence ID for Pdelay messages */
#define GPTP_DEF_PDELAY_FIRST_SEQ_ID    0x0100u
/*! First sequence ID for Sync messages */
#define GPTP_DEF_SYNC_FIRST_SEQ_ID      0x0400u

/*! PTP Multicast MAC Address - each PTP message is transmitted to this address */
#define GPTP_DEF_ETH_PTP_MAC_MULTICAST  (0x0180C200000Eu)

/*! Buffer index not used - map entry closed */
#define GPTP_DEF_BUFF_INDEX_CLOSED      0xFFFFFFFFU
#define GPTP_DEF_FRAME_INDEX_CLOSED     0xFFU

#if (GPTP_COUNTERS == STD_ON)
/*! Count of port counters */
#define GPTP_COUNTERS_PORT_CNT          13u
/*! Count of domain counters */
#define GPTP_COUNTERS_DOM_CNT           6u
/*! Count of counters defined by IEEE */
#define GPTP_IEEE_COUNTERS_CNT          18u
/*! @} */

/*!
 * @name gPTP Counter enum
 * @{
 */

/*!
 * @brief gPTP Counters
 */
typedef enum
{   /*! Count of valid Sync messages received on the gPTP port */
    ieee8021AsPortStatRxSyncCount = 1,
    /*! This counter is not used, no One Step Syncs */
    ieee8021AsPortStatRxOneStepSyncCount,
    /*! Count of valid Follow-Up messages received on the gPTP port */
    ieee8021AsPortStatRxFollowUpCount,
    /*! Count of valid Pdelay Request messages received on the gPTP port */
    ieee8021AsPortStatRxPdelayRequest,
    /*! Count of valid Pdelay Response messages received on the gPTP port */
    ieee8021AsPortStatRxPdelayResponse,
    /*! Count of valid Pdelay Request Follow-Up messages received on the gPTP port */
    ieee8021AsPortStatRxPdelayResponseFollowUp,
    /*! This counter is not used, no Announce messages allowed */
    ieee8021AsPortStatRxAnnounce,
    /*! Count of discarded PTP packets */
    ieee8021AsPortStatRxPTPPacketDiscard,
    /*! Count of Sync Receipt Timeout events */
    ieee8021AsPortStatRxSyncReceiptTimeouts,
    /*! This counter is not used, no Announce messages allowed */
    ieee8021AsPortStatAnnounceReceiptTimeouts,
    /*! Count of exceeded Alowed Lost Pdelay Responses (Too many lost responses) events */
    ieee8021AsPortStatPdelayAllowedLostResponsesExceeded,
    /*! Count of Sync messages transmitted on the gPTP port */
    ieee8021AsPortStatTxSyncCount,
    /*! This counter is not used, no One Step Syncs */
    ieee8021AsPortStatTxOneStepSyncCount,
    /*! Count of Follow-Up messages transmitted on the gPTP port */
    ieee8021AsPortStatTxFollowUpCount,
    /*! Count of Pdelay Request messages transmitted on the gPTP port */
    ieee8021AsPortStatTxPdelayRequest,
    /*! Count of Pdelay Response messages transmitted on the gPTP port */
    ieee8021AsPortStatTxPdelayResponse,
    /*! Count of Pdelay Request Follow-Up messages transmitted on the gPTP port */
    ieee8021AsPortStatTxPdelayResponseFollowUp,
    /*! This counter is not used, no Announce messages allowed */
    ieee8021AsPortStatTxAnnounce,
}gptp_def_counters_t;
#endif /* (GPTP_COUNTERS == STD_ON) */
/*! @} */

/*!
 * @name gPTP stack INTERNAL enums
 * @{
 */

/*!
 * @brief Platform timebases
 */
typedef enum
{
    /*! Timestamp from the freerunning timebase */
    GPTP_DEF_TS_FREERUNNING,
    /*! Timestamp from the corrected (synchronized to Grand Master) timebase */
    GPTP_DEF_TS_CORRECTED
}gptp_def_ts_type_t;

/*!
 * @brief State machines API call types
 */
typedef enum
{
    /*! Not used */
    GPTP_DEF_CALL_BY_MISTAKE = 0,
    /*! Initiate the State machine operation */
    GPTP_DEF_CALL_INITIATE,
    /*! State machine action upon the ptp message reception */
    GPTP_DEF_CALL_PTP_RECEIVED,
    /*! State machine action upon the timestamp reception */
    GPTP_DEF_CALL_ON_TIMESTAMP
}gptp_def_sm_call_type_t;

/*!
 * @brief Timestamp vs. buffer index map entry status  
 */
typedef enum
{
    /*! Entry not used */
    GPTP_DEF_TS_MAP_ENTRY_UNUSED = 0,
    /*! Entry enqueued */ 
    GPTP_DEF_TS_MAP_ENTRY_ENQUEUED,
    /*! Entry confirmed */ 
    GPTP_DEF_TS_MAP_ENTRY_CNFRMD
}gptp_def_ts_map_status_type_t;

/*!
 * @brief PTP message types carried in the PTP message
 */
typedef enum
{
    /*! Sync message type */
    GPTP_DEF_MSG_TYPE_SYNC = 0x00,
    /*! Pdelay request message type */
    GPTP_DEF_MSG_TYPE_PD_REQ = 0x02,
    /*! Pdelay response message type */
    GPTP_DEF_MSG_TYPE_PD_RESP = 0x03,
    /*! Sync followup message type */
    GPTP_DEF_MSG_TYPE_FOLLOW_UP = 0x08,
    /*! Pdelay response folloup message type */
    GPTP_DEF_MSG_TYPE_PD_RESP_FUP = 0x0a,
    /*! Announce message type */
    GPTP_DEF_MSG_TYPE_ANNOUNCE = 0x0b,
    /*! Signaling message type */
    GPTP_DEF_MSG_TYPE_SIGNALING = 0x0c,
    /*! Unknown message type */
    GPTP_DEF_MSG_TYPE_UNKNOWN = 0xff
}gptp_def_msg_type_t;

/*!
 * @brief Pdelay inititator state machine states
 */
typedef enum
{
    /*! Pdelay initiator not enabled */
    GPTP_DEF_INITIATOR_NOT_ENABLED = 0,
    /*! Initiation of the Pdelay request transmission */
    GPTP_DEF_INIIAL_SEND_PD_REQ,
    /*! Waiting for pdelay data - responses and local timestamp */
    GPTP_DEF_WAITING_FOR_DATA,
    /*! Waiting for pdelay interval */
    GPTP_DEF_WAITING_FOR_PD_INTERV,
    /*! Transmit pdelay request */
    GPTP_DEF_SEND_PDELAY_REQ,
    /*! Pdelay state machine reset */
    GPTP_DEF_PDELAY_RESET
}gptp_def_pdel_init_state_t;

/*!
 * @brief Pdelay responder state machine states
 */
typedef enum
{
    /*! Pdelay responder not enabled */
    GPTP_DEF_RESPONDER_NOT_ENABLED = 0,
    /*! Machine waiting for Pdelay request */
    GPTP_DEF_INIT_WAITING_FOR_PD_R,
    /*! Pdelay response sent, waiting for timestamp */
    GPTP_DEF_SENT_PD_RESP_WTING_4_T,
    /*! Waiting for Pdelay request */
    GPTP_DEF_WAITING_FOR_PDELAY_REQ
}gptp_def_pdel_resp_state_t;

/*!
 * @brief Sync state machine states - master
 */
typedef enum
{
    /*! Sync master not enabled */
    GPTP_DEF_SYNC_MASTER_NOT_EN = 0,
    /*! Sync master initialization */
    GPTP_DEF_SYNC_MASTER_INITING,
    /*! Sync master sync message sent */
    GPTP_DEF_SYNC_MASTER_SEND_SYNC,
    /*! Sync master followup message sent */
    GPTP_DEF_SYNC_MASTER_SEND_FUP
}gptp_def_sync_master_state_t;

/*!
 * @brief Sync state machine states - slave
 */
typedef enum
{
    /*! Sync slave not enabled */
    GPTP_DEF_SYNC_SLAVE_NOT_EN = 0,
    /*! Sync slave waiting for sync message */
    GPTP_DEF_SYNC_SLAVE_WT_4_FUP,
    /*! Sync slave waiting for followup message */
    GPTP_DEF_SYNC_SLAVE_WT_4_SYNC
}gptp_def_sync_slave_state_t;

/*!
 * @brief Synchronization lock states.
 */
typedef enum
{
    /*! Unlocked. */
    GPTP_SYN_UNLOCK,
    /*! Locked. */
    GPTP_SYN_LOCK
}gptp_def_syn_lock_state_type_t;
/*! @} */

/*!
 * @name gPTP stack data structures visible in the API
 * @{
 */
 /*!
 * @brief NVM writer machine states
 */
typedef enum
{
    /*! NVM writing stopped */
    GPTP_DEF_MEM_WRITE_STOP,
    /*! NVM writing initialized */
    GPTP_DEF_MEM_WRITE_INIT,
    /*! NVM writing finish */
    GPTP_DEF_MEM_WRITE_FINISH
}gptp_def_mem_write_stat;

 /*!
 * @brief NVM Data type
 */
typedef enum
{
    /*! NVM data Path delay */
    GPTP_DEF_NVM_PDELAY,
    /*! NVM data Rate ratio */
    GPTP_DEF_NVM_RRATIO,
    /*! NVM data check */
    GPTP_DEF_NVM_CHECK
}gptp_def_nvm_data_t;

/*!
 * @brief Clock and port ID structure.
 */
typedef struct
{
    /*! Clock ID information. */
    uint64_t                            u64ClockId; /* 8 bytes */
    /*! Port ID information. */
    uint16_t                            u16PortId; /* 2 bytes */
    /* 6 bytes padding */
    /* 16 bytes total */
} gptp_def_clock_port_id_t;

/*!
 * @brief Time information data structure - unsigned.
 */
typedef struct
{
    /*! Seconds part of the time information. */
    uint64_t                            u64TimeStampS; /* 8 bytes */
    /*! Nanoseconds part of the time information. */
    uint32_t                            u32TimeStampNs; /* 4 bytes */
    /* 4 bytes padding */
    /* 16 bytes total */
} gptp_def_timestamp_t;

/*!
 * @brief Time information data structure - signed.
 */
typedef struct
{
    /*! Seconds part of the time information. */
    int64_t                             s64TimeStampS; /* 8 bytes */
    /*! Nanoseconds part of the time information. */
    int32_t                             s32TimeStampNs; /* 4 bytes */
    /* 4 bytes padding */
    /* 16 bytes total */
} gptp_def_timestamp_sig_t;

/*!
 * @brief The structure gathering RX data.
 */
typedef struct
{
    /* Source MAC address. */
    uint64_t                            u64SourceMac; /* 8 bytes */
    /*! Pointer to the received gPTP data. */
    const uint8_t                       *cpu8RxData; /* 8 bytes */
    /*! Ingress timestamp - seconds. */
    uint32_t                            u32TsSec; /* 4 bytes */
    /*! Ingress timestamp - nano seconds. */
    uint32_t                            u32TsNsec; /* 4 bytes */
    /*! Ethertype. */
    uint16_t                            u16EthType; /* 2 bytes */
    /*! gPTP port received the message. */
    uint8_t                             u8PtpPort; /* 1 byte */
    /* 5 bytes padding */
    /* 32 bytes total */
} gptp_def_rx_data_t;
/*! @} */

/*!
 * @name gPTP Time Validation structures
 * @{
 */
#if (GPTP_TIME_VALIDATION == STD_ON)
/*!
 * @brief Time Validation Sync Slave measuremetn data structure.
 */
typedef struct
{
    /*! sourcePortId from received Sync frame. */
    gptp_def_clock_port_id_t            rSourcePortId; /* 16 bytes */
    /*! Ingress timestamp of Sync frame converted to Virtual Local Time. */
    gptp_def_timestamp_t                rSyncIngressTimestamp; /* 16 bytes */
    /*! preciseOriginTimestamp taken from the received Follow_Up frame. */
    gptp_def_timestamp_t                rPreciseOriginTimestamp; /* 16 bytes */
    /*! SyncLocal Time Tuple (Virtual Local Time part). */
    gptp_def_timestamp_t                rReferenceLocalTimestamp; /* 16 bytes */
    /*! SyncLocal Time Tuple (Global Time part). */
    gptp_def_timestamp_t                rReferenceGlobalTimestamp; /* 16 bytes*/
    /*! correctionField taken from the received Follow_Up frame. */
    int64_t                             s64CorrectionField; /* 8 bytes */
    /*! Currently valid pDelay value. */
    uint32_t                            u32Pdelay; /* 4 bytes */
    /*! Sequence Id of received Sync frame. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /* 2 bytes padding */
    /* 96 bytes total */
} gptp_def_time_slave_measure_t;

/*!
 * @brief Time Validation Sync Master measurement data structure.
 */
typedef struct
{
    /*! sourcePortId of sending Ethernet port. */
    gptp_def_clock_port_id_t            rSourcePortId; /* 16 bytes */
    /*! Egress timestamp of Sync frame. */
    gptp_def_timestamp_t                rSyncEgressTimestamp; /* 16 bytes */
    /*! The preciseOriginTime as copied to the Follow_Up frame. */
    gptp_def_timestamp_t                rPreciseOriginTimestamp; /* 16 bytes */
    /*! The correctionField as copied to the Follow_Up frame. */
    int64_t                             s64CorrectionField; /* 8 bytes */
    /*! sequenceId of sent Ethernet frame. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /* 6 bytes padding */
    /* 64 bytes total */
} gptp_def_time_master_measure_t;

/*!
 * @brief Time Validation Pdelay initiator measurement data structure.
 */
typedef struct
{
    /*! sourcePortId of sent Pdelay_Req frame. */
    gptp_def_clock_port_id_t            rRequestPortId; /* 16 bytes */
    /*! sourcePortId of received Pdelay_Resp frame. */
    gptp_def_clock_port_id_t            rResponsePortId; /* 16 bytes */
    /*! Egress timestamp of Pdelay_Req in Virtual Local Time. */
    gptp_def_timestamp_t                rRequestOriginTimestamp; /* 16 bytes */
    /*! Ingress timestamp of Pdelay_Resp in Virtual Local Time. */
    gptp_def_timestamp_t                rResponseReceiptTimestamp; /* 16 bytes */
    /*! Ingress timestamp of Pdelay_Req in Global Time taken from the received
        Pdelay_Resp. */
    gptp_def_timestamp_t                rRequestReceiptTimestamp; /* 16 bytes */
    /*! Egress timestamp of Pdelay_Resp in Global Time taken from the received
        Pdelay_Resp_Follow_Up. */
    gptp_def_timestamp_t                rResponseOriginTimestamp; /* 16 bytes */
    /*! Value of the Virtual Local Time of the reference Global Time Tuple. */
    gptp_def_timestamp_t                rReferenceLocalTimestampInit; /* 16 bytes */
    /*! Value of the local instance of the Global Time of the reference
        Global Time Tuple. */
    gptp_def_timestamp_t                rReferenceGlobalTimestampInit; /* 16 bytes */
    /*! Currently valid Pdelay value. */
    uint32_t                            u32Pdelay; /* 4 bytes */
    /*! Sequence Id of sent Pdelay_Req frame. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /* 2 bytes padding */
    /* 136 bytes total */
} gptp_def_pdelay_init_meas_t;

/*!
 * @brief Time Validation Pdelay responder measurement data structure.
 */
typedef struct
{
    /*! sourcePortId of received Pdelay_Req frame. */
    gptp_def_clock_port_id_t            rRequestPortId; /* 16 bytes */
    /*! sourcePortId of sent Pdelay_Resp frame. */
    gptp_def_clock_port_id_t            rResponsePortId; /* 16 bytes */
    /*! Ingress timestamp of Pdelay_Req converted to Virtual Local Time. */
    gptp_def_timestamp_t                rRequestReceiptTimestamp; /* 16 bytes */
    /*! Egress timestamp of Pdelay_Resp converted to Virtual Local Time. */
    gptp_def_timestamp_t                rResponseOriginTimestamp; /* 16 bytes */
    /*! Value of the Virtual Local Time of the reference Global Time Tuple used
        to convert requestReceiptTimestamp and responseOriginTimestamp into
        Global Time. */
    gptp_def_timestamp_t                rReferenceLocalTimestampInit; /* 16 bytes */
    /*! Value of the local instance of the Global Time of the reference
        Global Time Tuple used to convert requestReceiptTimestamp and
        responseOriginTimestamp into Global Time. */
    gptp_def_timestamp_t                rReferenceGlobalTimestampInit; /* 16 bytes */
    /*! sequenceId of received Pdelay_Req frame. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /* 6 bytes padding */
    /* 104 bytes total */
} gptp_def_pdelay_resp_meas_t;
#endif /* (GPTP_TIME_VALIDATION == STD_ON) */
/*! @} */

/*!
 * @name Callback function typedefs
 * @{
 */
/*!
 * @brief Domain selection callback function
 */
typedef bool (*gptp_domain_sel_callback_t)(uint8_t u8DomainNumber, float64_t *pf64RateRatio, gptp_def_timestamp_sig_t *prTime, bool *pbNegativeOfst, int8_t *ps8SyncIntervalLog);
/*!
 * @brief Callback function for NVM write access
 */
typedef uint8_t (*gptp_nvm_write_callback_t)(uint8_t u8PdelayMachine, gptp_def_nvm_data_t eNvmDataType, float64_t f64Value, gptp_def_mem_write_stat *peWriteStat);
/*!
 * @brief Callback function for NVM read access
 */
typedef uint8_t (*gptp_nvm_read_callback_t)(uint8_t u8PdelayMachine, gptp_def_nvm_data_t eNvmDataType, float64_t *pf64Value);
/*!
 * @brief Callback function for error event notification
 */
typedef void (*gptp_err_notify_t)(void);
/*!
 * @brief Callback function for synchronization notification.
 */
typedef void (*gptp_syn_notify_t)(gptp_def_syn_lock_state_type_t eSyncLockState);
/*!
 * @brief Callback function to notify 1588 time users of a hard clock update starting.
 */
typedef void (*gptp_clk_update_notify_start_t)(void);
/*!
 * @brief Callback function to notify 1588 time users of a hard clock update finishing.
 */
typedef void (*gptp_clk_update_notify_finish_t)(void);

#if (GPTP_TIME_VALIDATION == STD_ON)
/*!
 * @brief Time Validation callback function, reporting Sync Slave data
 */
typedef void (*gptp_def_t_b_notif_slave)(uint8_t u8DomainNumber, gptp_def_time_slave_measure_t rTimeSlaveData);
/*!
 * @brief Time Validation callback function, reporting Sync Master data
 */
typedef void (*gptp_def_t_b_notif_master)(uint8_t u8DomainNumber, gptp_def_time_master_measure_t rTimeMasterData);
/*!
 * @brief Time Validation callback function, reporting Pdelay initiator data
 */
typedef void (*gptp_def_s_p_notif_init)(gptp_def_pdelay_init_meas_t rPdelayInitData);
/*!
 * @brief Time Validation callback function, reporting Pdelay responder data
 */
typedef void (*gptp_def_s_p_notif_resp)(gptp_def_pdelay_resp_meas_t rPdelayRespData);
#endif /* (GPTP_TIME_VALIDATION == STD_ON) */

/*!
 * @brief Data structure concentrates all gPTP stack callback function pointers.
 */
typedef struct
{
    /*! Callback function for multidomain operation. The function allows
        to select domain to clock update. */
    gptp_domain_sel_callback_t          pfDomSelectionCB; /* 8 bytes */
    /*! Callback function for NVM write access. */
    gptp_nvm_write_callback_t           pfNvmWriteCB; /* 8 bytes */
    /*! Callback function for NVM read access. */
    gptp_nvm_read_callback_t            pfNvmReadCB; /* 8 bytes */
    /*! Callback function for Error notification. */
    gptp_err_notify_t                   pfErrNotify; /* 8 bytes */
    /*! Callback function for synchronization notification. */
    gptp_syn_notify_t                   pfSynNotify; /* 8 bytes */
    /*! Callback function to notify 1588 time users of a hard clock
        update starting. */
    gptp_clk_update_notify_start_t      pfClkUpdateNotifyStart; /* 8 bytes */
    /*! Callback function to notify 1588 time users of a hard clock
        update finishing. */
    gptp_clk_update_notify_finish_t     pfClkUpdateNotifyFinish; /* 8 bytes */
#if (GPTP_TIME_VALIDATION == STD_ON)
    /*! Callback function for Time Validation notification - Time Receiver. */
    gptp_def_t_b_notif_slave            pfTimeBaseProvideNotifSlave; /* 8 bytes */
    /*! Callback function for Time Validation notification - Time Transmitter. */
    gptp_def_t_b_notif_master           pfTimeBaseProvideNotifMaster; /* 8 bytes */
    /*! Callback function for Pdelay Initiator notification. */
    gptp_def_s_p_notif_init             pfSetPdelayInitiatorData; /* 8 bytes */
    /*! Callback function for Pdelay Responder notification. */
    gptp_def_s_p_notif_resp             pfSetPdelayResponderData; /* 8 bytes */
#endif /* (GPTP_TIME_VALIDATION == STD_ON) */
    /* 0 bytes padding */
    /* 56/88 bytes total */
} gptp_def_cb_funcs_t;
/*! @} */

/*!
 * @name gPTP stack INTERNAL structs
 * @{
 */
#if (GPTP_COUNTERS == STD_ON)
/*!
 * @brief gPTP INTERNAL stucture - gPTP port mapping to the ports on switch.
 */
typedef struct
{
    /*! Array of uint32_t - port counters. */
    uint32_t                            u32CountersPort[GPTP_COUNTERS_PORT_CNT]; /* 52 bytes */
    /* 4 bytes padding */
    /* 56 bytes total */
} gptp_def_countes_port_t;
/*!
 * @brief gPTP INTERNAL stucture - gPTP port mapping to the ports on switch.
 */
typedef struct
{
    /*! Array of uint32_t - domain counters. */
    uint32_t                            u32CountersDom[GPTP_COUNTERS_DOM_CNT]; /* 24 bytes */
    /* 0 bytes padding */
    /* 24 bytes total */
} gptp_def_countes_dom_t;
#endif /* (GPTP_COUNTERS == STD_ON) */

/*!
 * @brief gPTP INTERNAL stucture - port mapping to the ports on switch.
 */
typedef struct
{
    /*! Port number on the switch */
    uint8_t                             u8SwitchPort; /* 1 byte */
    /*! Switch number */
    uint8_t                             u8Switch; /* 1 byte */
    /*! Ignore link status */
    bool                                bLinkStateIgnore; /* 1 byte */
    /* 5 bytes padding */
    /* 8 bytes total */
} gptp_def_map_table_t;

/*!
 * @brief gPTP INTERNAL stucture - frame ID mapping to the buffer index.
 */
typedef struct
{
    /*! Pointer to management object used in Autosar EthSwt switch management. */
    void                                *MgmtObjectPtr; /* 8 bytes */
    /*! Timestamp map entry status. */
    gptp_def_ts_map_status_type_t       eTsEntryStatus; /* 4 bytes */
    /*! TX mechanism buffer index. */
    uint32_t                            u32BufferIndex; /* 4 bytes */
    /*! Egress timestamp placeholder. */
    uint32_t                            u32EgressTimeStampSeconds; /* 4 bytes */
    /*! Egress timestamp placeholder. */
    uint32_t                            u32EgressTimeStampNanoseconds; /* 4 bytes */
    /*! gPTP frame ID. */
    uint8_t                             u8PtpFrameId; /* 1 byte */
    /*! Egress port. */
    uint8_t                             u8EgressPort; /* 1 byte */
    /* 6 bytes padding */
    /* 32 bytes total */
} gptp_def_tx_frame_map_t;

/*!
 * @brief gPTP INTERNAL stucture - product details.
 */
typedef struct
{
    /*! Pointer to manufacturer ID string. */
    const uint8_t                       *cpu8ManId; /* 8 bytes */
    /*! Pointer to product revision string. */
    const uint8_t                       *cpu8ProdRev; /* 8 bytes */
    /*! Array of product description. */
    uint8_t                             au8ProdDesc[GPTP_DEF_PROD_DESC_LENGTH]; /* 64 bytes */
    /* 0 bytes padding */
    /* 80 bytes total */
} gptp_def_prod_detail_t;

/*!
 * @brief gPTP INTERNAL stucture - port map information.
 */
typedef struct
{
    /*! Pointer to port map table. */
    const gptp_def_map_table_t          *prMapTable; /* 8 bytes */
    /*! Number of gPTP ports. */
    uint8_t                             u8NumOfGptpPorts; /* 1 byte */
    /* 7 bytes padding */
    /* 16 bytes total */
} gptp_def_map_info_t;

/*!
 * @brief gPTP INTERNAL stucture - frame ID details.
 */
typedef struct
{
    /*! Message type. */
    gptp_def_msg_type_t                 eMsgType; /* 4 bytes */
    /*! Sequence ID. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /*! Port number. */
    uint8_t                             u8Port; /* 1 byte */
    /*! Machine ID. */
    uint8_t                             u8MachineId; /* 1 byte */
    /*! Domain ID. */
    uint8_t                             u8DomainId; /* 1 byte */
    /*! Sync machine acting as GM flag. */
    bool                                bSyncActingGm; /* 1 byte */
    /* 6 bytes padding */
    /* 16 bytes total */
} gptp_def_frame_id_element_t;

/*!
 * @brief gPTP INTERNAL stucture - MAC address.
 */
typedef struct
{
    /*! Dummy bits. */
    uint64_t                            u16Dummy:16; /* 2 bytes */
    /*! MAC address. */
    uint64_t                            u48Mac:48; /* 6 bytes */
    /* 0 bytes padding */
    /* 8 bytes total */
} gptp_def_eth_mac_t;

/*!
 * @brief gPTP INTERNAL stucture - PTP message header data.
 */
typedef struct
{
    /*! Correction time in sub ns. */
    uint64_t                            u64CorrectionSubNs; /* 8 bytes */
    /*! Source clock ID. */
    uint64_t                            u64SourceClockId; /* 8 bytes */
    /*! Message ID. */
    gptp_def_msg_type_t                 eMsgId; /* 4 bytes */
    /*! Source port ID. */
    uint16_t                            u16SourcePortId; /* 2 bytes */
    /*! Sequence ID. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /*! Message period in log format. */
    int8_t                              s8MessagePeriodLog; /* 1 byte */
    /* 7 bytes padding */
    /* 32 bytes total */
} gptp_def_msg_header_t;

/*!
 * @brief gPTP INTERNAL stucture - Sync message content.
 */
typedef struct
{
    /*! Structure containing message header information. */
    gptp_def_msg_header_t               rHeader; /* 32 bytes */
    /*! Sync RX timestamp. */
    gptp_def_timestamp_t                rSyncRxTs; /* 16 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /* 6 bytes padding */
    /* 56 bytes total */
} gptp_def_sync_data_t;

/*!
 * @brief gPTP INTERNAL stucture - Pdelay request message content.
 */
typedef struct
{
    /*! Structure containing message header information. */
    gptp_def_msg_header_t               rHeader; /* 32 bytes */
    /*! T2 timestamp. */
    gptp_def_timestamp_t                rT2Ts; /* 16 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Major SDO ID. */
    uint8_t                             u8MajorSdoId; /* 1 byte */
    /*! Subdomain number. */
    uint8_t                             u8SubdomainNum; /* 1 byte */
    /* 4 bytes padding */
    /* 56 bytes total */
} gptp_def_pdel_req_data_t;

/*!
 * @brief gPTP INTERNAL stucture - Pdelay response message content.
 */
typedef struct
{
    /*! Structure containing message header information. */
    gptp_def_msg_header_t               rHeader; /* 32 bytes */
    /*! T2 timestamp. */
    gptp_def_timestamp_t                rT2Ts; /* 16 bytes */
    /*! T4 timestamp. */
    gptp_def_timestamp_t                rT4Ts; /* 16 bytes */
    /*! Requesting port ID. */
    gptp_def_clock_port_id_t            rRequestingId; /* 16 bytes */
    /* 0 bytes padding */
    /* 80 bytes total */
} gptp_def_pdel_resp_data_t;

/*!
 * @brief gPTP INTERNAL stucture - Pdelay response follow-up message content.
 */
typedef struct
{
    /*! Structure containing message header information. */
    gptp_def_msg_header_t               rHeader; /* 32 bytes */
    /*! T3 timestamp. */
    gptp_def_timestamp_t                rT3Ts; /* 16 bytes */
    /*! Requesting port ID. */
    gptp_def_clock_port_id_t            rRequestingId; /* 16 bytes */
    /* 0 bytes padding */
    /* 64 bytes total */
} gptp_def_pdel_resp_fup_data_t;

/*!
 * @brief gPTP INTERNAL stucture - Follow-up message content.
 */
typedef struct
{
    /*! Structure containing message header information. */
    gptp_def_msg_header_t               rHeader; /* 32 bytes */
    /*! Sync TX timestamp. */
    gptp_def_timestamp_t                rSyncTxTs; /* 16 bytes */
    /*! Cumulative rate ratio. */
    float64_t                           f64RateRatio; /* 8 bytes */
    /* 0 bytes padding */
    /* 56 bytes total */
} gptp_def_fup_data_t;

/*!
 * @brief gPTP INTERNAL stucture - TX data.
 */
typedef struct
{
    /*! Tx timestamp. */
    gptp_def_timestamp_t                rTs; /* 16 bytes */
    /*! Requesting port ID. */
    gptp_def_clock_port_id_t            rRequesting; /* 16 bytes */
    /*! Source port ID. */
    gptp_def_clock_port_id_t            rSrcPortID; /* 16 bytes */
    /*! Rate Ratio. */
    float64_t                           f64RateRatio; /* 8 bytes */
    /*! Correction time in sub ns. */
    uint64_t                            u64CorrectionSubNs; /* 8 bytes */
    /* Destination MAC address. */
    uint64_t                            u64DestMac; /* 8 bytes */
    /*! Pointer to array of TX buffer. */
    uint8_t                             *pau8TxBuffPtr; /* 8 bytes */
    /*! Pointer to TX Cmd structure. */
    void                                *pvTxCmd; /* 8 bytes */
    /*! Pointer to Buffer index map for corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMap; /* 8 bytes */
    /*! Message ID. */
    gptp_def_msg_type_t                 eMsgId; /* 4 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Sequence ID. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /*! Subdomain number. */
    uint8_t                             u8SubdomainNumber; /* 1 byte */
    /*! Frame Length. */
    uint8_t                             u8FrameLength; /* 1 byte */
    /*! Message period in log format. */
    int8_t                              s8LogMessagePeriod; /* 1 byte */
    /*! Flag if the TS is requested upon transmission. */
    bool                                bTsRequested; /* 1 byte */
    /*! Flag of the Brifge acting GM. */
    bool                                bSyncActingGm; /* 1 byte */
    /* 3 bytes padding */
    /* 112 bytes total */
} gptp_def_tx_data_t;

/*!
 * @brief gPTP INTERNAL stucture - Pdelay machine.
 */
typedef struct
{
    /*! Structure containing Pdelay response follow-up TX data. */
    gptp_def_tx_data_t                  rTxDataReFu; /* 112 bytes */
    /*! Structure containing Pdelay response TX data. */
    gptp_def_tx_data_t                  rTxDataResp; /* 112 bytes */
    /*! Structure containing Pdelay request TX data. */
    gptp_def_tx_data_t                  rTxDataReq; /* 112 bytes */
    /*! Structure containing Pdelay response message RX data. */
    gptp_def_pdel_resp_data_t           rPdRespMsgRx; /* 80 bytes */
    /*! Structure containing Pdelay response followup message RX data. */
    gptp_def_pdel_resp_fup_data_t       rPdRespFupMsgRx; /* 64 bytes */
    /*! Structure containing Pdelay request message RX data. */
    gptp_def_pdel_req_data_t            rPdReqMsgRx; /* 56 bytes */
    /*! T1 timestamp value. */
    gptp_def_timestamp_t                rT1Ts; /* 16 bytes */
    /*! T3 timestamp value. */
    gptp_def_timestamp_t                rT3Ts; /* 16 bytes */
    /*! Previous T1 timestamp. */
    gptp_def_timestamp_t                rNeighborCalcPrevT1; /* 16 bytes */
    /*! Previous T2 timestamp. */
    gptp_def_timestamp_t                rNeighborCalcPrevT2; /* 16 bytes */
#if (GPTP_TIME_VALIDATION == STD_ON)
    /*! Local timestamp of Time validation on initiator side. */
    gptp_def_timestamp_t                rReferenceLocalTimestampInit; /* 16 bytes */
    /*! Global timestamp of Time validation on initiator side. */
    gptp_def_timestamp_t                rReferenceGlobalTimestampInit; /* 16 bytes */
    /*! Local timestamp of Time validation on responder side. */
    gptp_def_timestamp_t                rReferenceLocalTimestampResp; /* 16 bytes */
    /*! Global timestamp of Time validation on responder side. */
    gptp_def_timestamp_t                rReferenceGlobalTimestampResp; /* 16 bytes */
#endif /* (GPTP_TIME_VALIDATION == STD_ON) */
    /*! Neighbor rate ratio - filtered. */
    float64_t                           f64NeighborRateRatio; /* 8 bytes */
    /*! Current result of Neighbor rate ratio. */
    float64_t                           f64NeighborRateRatioCurrent; /* 8 bytes */
    /*! Temporary Rate ratio - current. */
    float64_t                           f64TempRateRatioCurrent; /* 8 bytes */
    /*! Neighbor propagation delay - filtered. */
    float64_t                           f64NeighborPropDelay; /* 8 bytes */
    /*! Current result of Neighbor propagation delay. */
    float64_t                           f64NeighborPropDelayCurrent; /* 8 bytes */
    /*! Pdelay value to write into the NVM. */
    float64_t                           f64PdelayToWrite; /* 8 bytes */
    /*! Rate ratio value to write into the NVM. */
    float64_t                           f64RratioToWrite; /* 8 bytes */
    /*! Check data for NVM. */
    float64_t                           f64NeighborCheck; /* 8 bytes */
    /*! Pdelay timer Pdelay request send due. */
    uint64_t                            u64TimerPdelaySendDue; /* 8 bytes */
    /*! Neighbor propagation delay threshold. */
    uint64_t                            u64NeighborPropDelayThreshNs; /* 8 bytes */
    /*! Start time of turnaround measurement on the initiator side. */
    uint64_t                            u64TurnaroundMeasStartPtpNsInit; /* 8 bytes */
    /*! Start time of turnaround measurement on the responder side. */
    uint64_t                            u64TurnaroundMeasStartPtpNsResp; /* 8 bytes */
    /* Source MAC address. */
    uint64_t                            u64SourceMac; /* 8 bytes */
    /*! Pointer to clock ID. */
    uint64_t                            *pu64ClockId; /* 8 bytes */
    /*! Pointer to port enabled flag. */
    bool                                *pbPortEnabled; /* 8 bytes */
    /*! NVM storage physical address for Pdelay value. */
    uint32_t                            u32NvmAddressPdelay; /* 4 bytes */
    /*! NVM storage physical address for Rate ratio. */
    uint32_t                            u32NvmAddressRratio; /* 4 bytes */
    /*! Pdelay initiator state machine state. */
    gptp_def_pdel_init_state_t          ePdelayInitiatorState; /* 4 bytes */
    /*! Pdelay initiator state machine state. */
    gptp_def_pdel_resp_state_t          ePdelayResponderState; /* 4 bytes */
    /*! State machine for NVM writing Pdelay. */
    gptp_def_mem_write_stat             rPdelayNvmWriteStat; /* 4 bytes */
    /*! State machine for NVM writing Rate Ratio. */
    gptp_def_mem_write_stat             rRratioNvmWriteStat; /* 4 bytes */
    /*! State machine for NVM writing check data. */
    gptp_def_mem_write_stat             rCheckNvmWriteStat; /* 4 bytes */
    /*! Squence ID of T1 timestamp. */
    uint16_t                            u16T1TsSeqId; /* 2 bytes */
    /*! Sequence ID of T3 timestamp. */
    uint16_t                            u16T3TsSeqId; /* 2 bytes */
    /*! Pdelay response sequence ID. */
    uint16_t                            u16RespSeqId; /* 2 bytes */
    /*! Count of lost responses. */
    uint16_t                            u16LostResponses; /* 2 bytes */
    /*! Maximum allowed lost responses. */
    uint16_t                            u16PdelLostReponsesAllowedCnt; /* 2 bytes */
    /*! Count of pdelay measurements till slow down. */
    uint16_t                            u16MsmtsTillSlowDown; /* 2 bytes */
    /*! Pdelay responses count. */
    uint16_t                            u16PdelayResponsesCnt; /* 2 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Sequence ID. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /*! Delay asymmetry for corresponding port [ns]. */
    int16_t                             s16DelayAsymmetry; /* 2 bytes */
    /*! gPTP port number. */
    uint8_t                             u8GptpPort; /* 1 byte */
    /*! Current pdelay interval in log format. */
    int8_t                              s8PdelayIntervalLog; /* 1 byte */
    /*! Initial pdelay interval in log format. */
    int8_t                              s8InitPdelayIntervalLog; /* 1 byte */
    /*! Operational pdelay interval in log format. */
    int8_t                              s8OperPdelayIntervalLog; /* 1 byte */
    /*! Array Pdelay request message buffer. */
    uint8_t                             au8SendBuffPdelReq[GPTP_DEF_TX_BUF_LEN_PD_RQ]; /* 83 bytes */
    /*! Array Pdelay response message buffer. */
    uint8_t                             au8SendBuffPdelResp[GPTP_DEF_TX_BUF_LEN_PD_RSP]; /* 83 bytes */
    /*! Array Pdelay response follow-up message buffer. */
    uint8_t                             au8SendBuffPdelRespFup[GPTP_DEF_TX_BUF_LEN_PD_FUP]; /* 83 bytes */
    /*! flag if to compute Neighbor Rate Ratio. */
    bool                                bComputeNeighborRateRatio; /* 1 byte */
    /*! flag if to compute Neighbor Rate Ratio .*/
    bool                                bComputeNeighborPropDelay; /* 1 byte */
    /*! Pdelay request received flag. */
    bool                                bPdelayReqReceived; /* 1 byte */
    /*! Pdelay response received flag. */
    bool                                bPdelayRespReceived; /* 1 byte */
    /*! Pdelay response follow-up received flag. */
    bool                                bPdelayRespFupReceived; /* 1 byte */
    /*! T1 timestamp registered flag. */
    bool                                bT1TsRegistred; /* 1 byte */
    /*! T3 timestamp registered flag. */
    bool                                bT3TsRegistred; /* 1 byte */
    /*! Neighbor rate ratio valid flag. */
    bool                                bNeighborRateRatioValid; /* 1 byte */
    /*! Current neighbor rate ratio valid flag. */
    bool                                bNeighborRateRatioValidCurrent; /* 1 byte */
    /*! Rate ratio averager initialized flag. */
    bool                                bRatioAveragerInitialized; /* 1 byte */
    /*! Pdelay value is valid flag. */
    bool                                bPdelayValueValid; /* 1 byte */
    /*! Current pldelay value is valid flag. */
    bool                                bPdelayValueValidCurrent; /* 1 byte */
    /*! Prelay aferager initialized flag. */
    bool                                bPdelAveragerInitialized; /* 1 byte */
    /*! Pdelay initiator enabled flag. */
    bool                                bPdelayInitiatorEnabled; /* 1 byte */
    /*! Pdelay initiator enabled previous state flag. */
    bool                                bPdelayInitiatorEnabledPrev; /* 1 byte */
    /*! Respond to a Pdelay request with responder's (unicast) instead of
        multicast MAC address. */
    bool                                bPdelayUnicastResp; /* 1 byte */
    /*! Pdelay responder enabled flag. */
    bool                                bPdelayResponderEnabled; /* 1 byte */
    /*! Pdelay timer enabled. */
    bool                                bTimerPdelayTimerEnabled;  /* 1 byte */
    /* 1 byte padding */
    /* 1040/1104 bytes total */
} gptp_def_pdelay_t;

/*!
 * @brief gPTP INTERNAL stucture - Sync machine.
 */
typedef struct
{
    /*! Structure containing data for follow-up transmission. */
    gptp_def_tx_data_t                  rTxDataFup; /* 112 bytes */
    /*! Structure containing data for sync transmission. */
    gptp_def_tx_data_t                  rTxDataSyn; /* 112 bytes */
    /*! Follow-up message RX data. */
    gptp_def_fup_data_t                 rFupMsgRx; /* 56 bytes */
    /*! Sync message RX data. */
    gptp_def_sync_data_t                rSyncMsgRx; /* 56 bytes */
    /*! Store correctly received timestamp. */
    gptp_def_timestamp_t                rPrecOrigTsRcvd; /* 16 bytes */
    /*! TS timestamp value. */
    gptp_def_timestamp_t                rTsTs; /* 16 bytes */
    /*! TR timestamp value. */
    gptp_def_timestamp_t                rTrTs; /* 16 bytes */
    /*! Upstream TX time in timestamp format. */
    gptp_def_timestamp_t                rUpstreamTxTime; /* 16 bytes */
    /*! Destination MAC address. */
    gptp_def_eth_mac_t                  rDestMac; /* 8 bytes */
    /*! Correction value in sub ns. */
    uint64_t                            u64CorrectionSubNs; /* 8 bytes */
    /*! Upstream TX time - local time of GM timestamp transmission. */
    uint64_t                            u64UpstreamTxTime; /* 8 bytes */
    /*! Log of last sync transmission time. */
    uint64_t                            u64TimerLastSyncSent; /* 8 bytes */
    /*! Sync transmission due. */
    uint64_t                            u64TimerSyncSendDue; /* 8 bytes */
    /*! Residence measurement start time. */
    uint64_t                            u64ResidenceMeasStartPtpNs; /* 8 bytes */
    /*! Rate ratio. */
    float64_t                           f64RateRatio; /* 8 bytes */
    /*! Pointer to neighbor propagation delay for corresponding port. */
    float64_t                           *pf64NeighborPropDelay; /* 8 bytes */
    /*! Pointer to neighbor rate ratio for corresponding port. */
    float64_t                           *pf64NeighborRateRatio; /* 8 bytes */
    /*! Pointer to delay asymmetry for corresponding port [ns]. */
    int16_t                             *ps16DelayAsymmetry; /* 8 bytes */
    /*! Pointer to port enabled flag. */
    bool                                *pbPortEnabled; /* 8 bytes */
    /*! Mean propagation delay in ns. */
    uint32_t                            u32MeanPropDelay; /* 4 bytes */
    /*! Sync machine Master state. */
    gptp_def_sync_master_state_t        eSyncMasterState; /* 4 bytes */
    /*! Sync machine Slave state. */
    gptp_def_sync_slave_state_t         eSyncSlaveState; /* 4 bytes */
    /*! TR timestamp sequence ID. */
    uint16_t                            u16TsTsSeqId; /* 2 bytes */
    /*! Sequence ID. */
    uint16_t                            u16SequenceId; /* 2 bytes */
    /*! Sync send buffer. */
    uint8_t                             au8SendBuffSync[GPTP_DEF_TX_BUF_LEN_SYNC]; /* 73 bytes */
    /*! Follow-up send buffer. */
    uint8_t                             au8SendBuffFup[GPTP_DEF_TX_BUF_LEN_FUP]; /* 105 bytes */
    /*! gPTP port number. */
    uint8_t                             u8GptpPort; /* 1 byte */
    /*! Initial sync interval in log format. */
    int8_t                              s8InitSyncIntervalLog; /* 1 byte */
    /*! Operating sync interval in log format. */
    int8_t                              s8OperSyncIntervalLog; /* 1 byte */
    /*! Sync message received flag. */
    bool                                bSyncMsgReceived; /* 1 byte */
    /*! Follow-up message received flag. */
    bool                                bFupMsgReceived; /* 1 byte */
    /*! TS timestamp registered flag. */
    bool                                bTsTsRegistred; /* 1 byte */
    /*! Sync role flag - Timer Receiver or Time Transmitter. */
    bool                                bSyncRole; /* 1 byte */
    /*! Sync machine is acting GM flag. */
    bool                                bSyncActingGm; /* 1 byte */
    /*! TR timestamp registered flag. */
    bool                                bTrTsRegistred; /* 1 byte */
    /*! Timer for Sync tranmission enabled flag. */
    bool                                bTimerSyncEnabled; /* 1 byte */
    /*! Count of currently skipped syncs if the transmission is slower
        than reception. */
    uint8_t                             u8SkippedSyncs; /* 1 byte */
    /*! Current sync interval in log format. */
    int8_t                              s8SyncIntervalLog; /* 1 byte */
    /* 2 bytes padding */
    /* 696 bytes total */
} gptp_def_sync_t;

/*!
 * @brief gPTP INTERNAL stucture - PI Controller configuration structure.
 */
typedef struct
{
    /*! The system dumping ratio is dimensionless quantity describing the loop
        attenuation. */
    float64_t                           f64DampingRatio; /* 8 bytes */
    /*! The natural frequency ratio defines ration between
        system natural frequency and sampling frequency. */
    float64_t                           f64NatFreqRatio; /* 8 bytes */
    /*! Integral windup limit
        (max positive/negative output value of the I term) [PPB]. */
    uint32_t                            u32IntegralWindupLimit; /* 4 bytes */
    /* 4 bytes padding */
    /* 24 bytes total */
} gptp_def_pi_controller_conf_t;

/*!
 * @brief gPTP INTERNAL stucture - Synchronization notification parameters.
 */
typedef struct
{
    /*! Synchronization offset threshold. */
    int64_t                             i64SynTrigOfst; /* 8 bytes */
    /*! Unsynchronization offset threshold. */
    int64_t                             i64UnsTrigOfst; /* 8 bytes */
    /*! Synchronization consecutive occurrence limit. */
    uint16_t                            u16SynTrigCnt; /* 2 bytes */
    /*! Unsynchronization consecutive occurrence limit. */
    uint16_t                            u16UnsTrigCnt; /* 2 bytes */
    /* 4 bytes padding */
    /* 24 bytes total */
} gptp_def_params_syn_lock_t;

/*!
 * @brief gPTP INTERNAL stucture - Time base information.
 */
typedef struct
{
    /*! Change of phase during the last time base indicator increment (i.e.,
        current time offset between local (corrected) clock
        and the Grand Master). */
    gptp_def_timestamp_sig_t            rLastPhaseChange; /* 16 bytes */
    /*! Fractional frequency change (i.e., frequency change expressed as a pure
        fraction) during the last time base indicator increment. */
    float64_t                           f64LastFreqChange; /* 8 bytes */
    /*! Time base is incremented evertime the PTP CLK slave changes its phase
        or frequency. */
    uint16_t                            u16TimeBaseIndicator; /* 2 bytes */
    /*! The last phase change had positive/negative offset. */
    bool                                bNegativePhase; /* 1 byte */
    /* 5 bytes padding */
    /* 32 bytes total */
} gptp_port_ptp_timebase_info_t;

/*!
 * @brief gPTP INTERNAL stucture - Per device parameters.
 */
typedef struct
{
    /*! Data structure containing time base information. */
    gptp_port_ptp_timebase_info_t       rTimeBaseInfo; /* 32 bytes */
    /*! PI Controller configuration structure. */
    gptp_def_pi_controller_conf_t       rPIControllerConfig; /* 24 bytes */
    /*! Data structure containing all synchronization notification parameters. */
    gptp_def_params_syn_lock_t          rSynLockParam; /* 24 bytes */
    /*! Frame ID table carrying transmitted frames details. */
    gptp_def_frame_id_element_t         arFrameIdTable[256]; /* 4096 bytes */
    /*! Last reported GM offset to the synchronization mechanism. */
    gptp_def_timestamp_sig_t            rReportedOffset; /* 16 bytes */
    /*! Estimated offset of local clock to the GM clock. */
    gptp_def_timestamp_sig_t            rEstimGmOffset; /* 16 bytes */
    /*! Last free running clock reference for offset estimation calculation. */
    gptp_def_timestamp_t                rLastFreeRunRef; /* 16 bytes */
    /*! Pdelay filter weight. */
    float64_t                           f64PdelAvgWeight; /* 8 bytes */
    /*! Rate ratio filter weight. */
    float64_t                           f64RratioAvgWeight; /* 8 bytes */
    /*! Rate ratio maximum allowed deviation. */
    float64_t                           f64RratioMaxDev; /* 8 bytes */
    /*! Threshold for Pdelay writing into the NVM. */
    float64_t                           f64PdelayNvmWriteThr; /* 8 bytes */
    /*! Threshold for Rate ratio writing into the NVM. */
    float64_t                           f64RratioNvmWriteThr; /* 8 bytes */
    /*! Corrected clock rate ratio. */
    float64_t                           f64CorrClockRateRatio; /* 8 bytes */
    /*! PI Controller maximum threshold - creates PI Controller action band. */
    uint64_t                            u64PIControllerMaxThreshold; /* 8 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Number of consecutive synchronizations. */
    uint16_t                            u16SynCnt; /* 2 bytes */
    /*! Number of consecutive unsynchronizations. */
    uint16_t                            u16UnsCnt; /* 2 bytes */
    /*! Eth frame priority. */
    uint8_t                             u8EthFramePrio; /* 1 byte */
    /*! Count of gPTP ports. */
    uint8_t                             u8PortsCount; /* 1 byte */
    /*! Next Sync frame ID. */
    uint8_t                             u8NextFrameIdSync; /* 1 byte */
    /*! Next Pdelay request frame ID. */
    uint8_t                             u8NextFrameIdPdReq; /* 1 byte */
    /*! Next Pdelay response frame ID. */
    uint8_t                             u8NextFrameIdPdResp; /* 1 byte */
    /*! Count of initialized domains. */
    uint8_t                             u8NumberOfDomains; /* 1 byte */
    /*! Count of Pdelay machines. */
    uint8_t                             u8NumberOfPdelayMachines; /* 1 byte */
    /*! Number of clock instances which should be updated/corrected. */
    uint8_t                             u8NumberOfClkInstances; /* 1 byte */
    /*! SDO ID compatibility mode flag. */
    bool                                bSdoIdCompatibilityMode; /* 1 byte */
    /*! Vlan enabled flag. */
    bool                                bVlanEnabled; /* 1 byte */
    /*! Last reported GM offset to the synchronization mechanism negative flag. */
    bool                                bReportedOffsetNeg; /* 1 byte */
    /*! Local clock ever updated to the GM time flag. */
    bool                                bEverUpdated; /* 1 byte */
    /*! Estimated offset of local clock to the GM clock calculated. */
    bool                                bEstimGmOffsetCalculated; /* 1 byte */
    /*! Signaling mechanism enabled flag. */
    bool                                bSignalingEnabled; /* 1 byte */
    /*! Synchronized state flag. */
    bool                                bSynced; /* 1 byte */
    /*! Use both clock - free running and corrected. */
    bool                                bDoubleClock; /* 1 byte */
    /* 2 bytes padding */
    /* 4304 bytes total */
} gptp_def_device_t;

/*!
 * @brief gPTP INTERNAL stucture -  Per port parameters.
 */
typedef struct
{
    /*! Source port MAC address. */
    gptp_def_eth_mac_t                  rSourceMac; /* 8 bytes */
    /*! Clock ID. */
    uint64_t                            u64ClockId; /* 8 bytes */
    /*! gPTP port number. */
    uint8_t                             u8PortId; /* 1 byte */
    /*! Port enabled (link up/down) flag. */
    bool                                bPortEnabled; /* 1 byte */
    /*! Ignore link status. */
    bool                                bLinkStateIgnore; /* 1 byte */
    /* 5 bytes padding */
    /* 24 bytes total */
} gptp_def_port_t;

/*!
 * @brief gPTP INTERNAL stucture -  Per domain parameters.
 */
typedef struct
{
    /*! Structure containing data for signaling transmission. */
    gptp_def_tx_data_t                  rTxDataSig; /* 112 bytes */
    /*! Last valid GM time plus correction. */
    gptp_def_timestamp_t                rLastValidGmPlusCor; /* 16 bytes */
    /*! Last valid Timestamp from GM plus correction. */
    gptp_def_timestamp_t                rLastValidTsOfGmPlusCor; /* 16 bytes */
    /*! Previously received precision origin timestamp. */
    gptp_def_timestamp_t                rPrevPrecOrigTs; /* 16 bytes */
    /*! Time of last Sync reception. */
    uint64_t                            u64TimerLastSyncRcvd; /* 8 bytes */
    /*! Last GM phase change - low. */
    uint64_t                            u64LastGmPhaseChangeL; /* 8 bytes */
    /*! Sync status check due. */
    uint64_t                            u64TimerSyncCheckDue; /* 8 bytes */
    /*! Sync receipt timeout due. */
    uint64_t                            u64TimerSyncReceiptTimeoutDue; /* 8 bytes */
    /*! Pointer to array od Sync machine structures. */
    gptp_def_sync_t                     *prSyncMachines; /* 8 bytes */
#if (GPTP_COUNTERS == STD_ON)
    /*! Pointer to array of domain specific counters. */
    gptp_def_countes_dom_t              *prCntrsDom; /* 8 bytes */
#endif /* (GPTP_COUNTERS == STD_ON) */
    /*! Last GM phase change - high. */
    uint32_t                            u32LastGmPhaseChangeH; /* 4 bytes */
    /*! Scaled last GM frequency change. */
    uint32_t                            u32ScaledLastGmFreqChange; /* 4 bytes */
    /*! Threshold for the Sync outlier reception. */
    uint32_t                            u32SyncOutlierThrNs; /* 4 bytes */
    /*! Signaling message sequence ID counter. */
    uint16_t                            u16SigSequenceId; /* 2 bytes */
    /*! GM timebase indicator. */
    uint16_t                            u16GmTimeBaseIndicator; /* 2 bytes */
    /*! Vlan information. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Signaling send buffer. */
    uint8_t                             au8SendBuffSig[GPTP_DEF_TX_BUF_LEN_SIGNL]; /* 89 bytes */
    /*! Domain index - configuration order. */
    uint8_t                             u8DomainIndex; /* 1 byte */
    /*! Domain number - number on wire (0-255). */
    uint8_t                             u8DomainNumber; /* 1 byte */
    /*! Count of sync machines per domain. */
    uint8_t                             u8NumberOfSyncsPerDom; /* 1 byte */
    /*! Slave machine ID - which sync machine is the slave one. */
    uint8_t                             u8SlaveMachineId; /* 1 byte */
    /*! Reference domain for the Synced GM. */
    uint8_t                             u8RefDomForSyncedGIndex; /* 1 byte */
    /*! Startup timeout in seconds. */
    uint8_t                             u8StartupTimeoutS; /* 1 byte */
    /*! Count of missing Sync messages till the Sync receipt timeout. */
    uint8_t                             u8SyncReceiptTimeoutCnt; /* 1 byte */
    /*! Count of allowed outliers received. */
    uint8_t                             u8OutlierIgnoreCnt; /* 1 byte */
    /*! Coutliers received. */
    uint8_t                             u8OutlierCnt; /* 1 byte */
    /*! Sync interval of incoming Sync messages. */
    int8_t                              s8SyncIntervalLogRcvd; /* 1 byte */
    /*! Received request for Sync interval update. */
    bool                                bSignalingIntervalRcvd; /* 1 byte */
    /*! Valid sync message received flag. */
    bool                                bValidSyncReceived; /* 1 byte */
    /*! Domain role flag. */
    bool                                bDomainIsGm; /* 1 byte */
    /*! If the sync is acting. */
    bool                                bSyncActingGm; /* 1 byte */
    /*! Synced GM flag. */
    bool                                bSyncedGm; /* 1 byte */
    /*! GM failure already reported flag. */
    bool                                bGmFailureReported; /* 1 byte */
    /*! Received sync has been used for local clock update flag. */
    bool                                bRcvdSyncUsedForLocalClk; /* 1 byte */
    /*! Valid sync message received since start flag. */
    bool                                bSyncValidEverReceived; /* 1 byte */
    /* 3 bytes padding */
    /* 328/336 bytes total */
} gptp_def_domain_t;

/*!
 * @brief gPTP INTERNAL stucture - Main data structure containing all the instance data.
 */
typedef struct
{
    /*! Structure containing all device specific parameters. */
    gptp_def_device_t                   rPerDeviceParams; /* 4304 bytes */
    /*! Data structure containing pointers to all callback functions. */
    gptp_def_cb_funcs_t                 rPtpStackCallBacks; /* 56/88 bytes */
    /*! Structure containing all product detail information. */
    gptp_def_prod_detail_t              rProductDetails; /* 80 bytes */
    /*! Sync status calculation due. */
    uint64_t                            u64SyncStatCalcDue; /* 8 bytes */
    /*! Pointer to structure containing all per port parameters. */
    gptp_def_port_t                     *prPerPortParams; /* 8 bytes */
    /*! Pointer to structure containing all per domain parameters. */
    gptp_def_domain_t                   *prPerDomainParams; /* 8 bytes */
    /*! Pointer to structure containing all Pdelay machine parameters. */
    gptp_def_pdelay_t                   *prPdelayMachines; /* 8 bytes */
#if (GPTP_COUNTERS == STD_ON)
    /*! Pointer to port specific counters. */
    gptp_def_countes_port_t             *prCntrsPort; /* 8 bytes */
#endif /* (GPTP_COUNTERS == STD_ON) */
    /*! Local clock is to be updated flag. */
    bool                                bLocClkToUpdate; /* 1 byte */
    /*! gPTP stack initialized flag. */
    bool                                bGptpInitialized; /* 1 byte */
    /* 6 bytes padding */
    /* 4480/4520 bytes total */
} gptp_def_data_t;
/*! @} */

/*!
 * @name gPTP Initialization parameters structs.
 * @{
 */
/*!
 * @brief gPTP Initialization - Pdelay state machine.
 */
typedef struct
{
    /*! Neighbor propagation delay threshold [ns]. */
    uint64_t                            u64NeighborPropDelayThreshNs; /* 8 bytes */
    /*! Clock ID of gPTP port. */
    uint64_t                            u64ClockId; /* 8 bytes */
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdReq; /* 8 bytes */
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdResp; /* 8 bytes */
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdReFu; /* 8 bytes */
    /*! Pointer to Buffer index map for Pdelay Request on corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMapReq; /* 8 bytes */
    /*! Pointer to Buffer index map for Pdelay Response on corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMapResp; /* 8 bytes */
    /*! Pointer to Buffer index map for Pdelay Response FUP on corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMapReFu; /* 8 bytes */
    /*! Address of Pdelay record in the Non Volatile Memory. */
    uint32_t                            u32NvmAddressPdelay; /* 4 bytes*/
    /*! Address of Rate Ratio record in the Non Volatile Memory. */
    uint32_t                            u32NvmAddressRratio; /* 4 bytes */
    /*! Count of Pdelay measurement, till the interval is switched from initial to operational. */
    uint16_t                            u16MeasurementsTillSlowDown; /* 2 bytes */
    /*! Count of allowed lost Pdelay responses. */
    uint16_t                            u16PdelLostReponsesAllowedCnt; /* 2 bytes */
    /*! Delay asymmetry for corresponding port [ns]. */
    int16_t                             s16DelayAsymmetry; /* 2 bytes */
    /*! Pdelay initial interval, in log. format. E.g., value -2 represents 250ms. */
    int8_t                              s8PdelIntervalLogInit; /* 1 byte */
    /*! Pdelay operational interval in log format. E.g., value 0 represents 1s. */
    int8_t                              s8PdelIntervalLogOper; /* 1 byte */
    /*! Pdelay initiator enabled = true / disabled = false. */
    bool                                bPdelayInitiatorEnabled; /* 1 byte */
    /*! Respond to a Pdelay request with responder's (unicast) instead of
        multicast MAC address. */
    bool                                bPdelayUnicastResp; /* 1 byte */
    /* 6 bytes padding */
    /* 88 bytes total */
} gptp_def_init_params_pdel_t;

/*!
 * @brief gPTP Initialization - Sync state machine.
 */
typedef struct
{
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdSyn; /* 8 bytes */
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdFup; /* 8 bytes */
    /*! Pointer to Buffer index map for Sync message on corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMapSync; /* 8 bytes */
    /*! Pointer to Buffer index map for FUP message on corresponding machine. */
    gptp_def_tx_frame_map_t             *prFrameMapFup; /* 8 bytes */
    /*! Index of gPTP port on which the state machine operates. */
    uint8_t                             u8GptpPort; /* 1 byte */
    /*! Sync interval, in log. format. E.g., value -3 represents 125ms. */
    int8_t                              s8SyncIntervalLog; /* 1 byte */
    /*! The state machine role master = true / slave = false. */
    bool                                bMachineRole; /* 1 byte */
    /* 5 bytes padding */
    /* 40 bytes total */
} gptp_def_init_params_sync_t;

/*!
 * @brief gPTP Initialization - Domain parameters.
 */
typedef struct
{
    /*! Pointer to array of structure, containing initial parameters of
        the sync machines which belong to this domain. */
    const gptp_def_init_params_sync_t   *pcrDomainSyncMachinesPtr; /* 8 bytes */
    /*! Pointer to array of structure, containing all operational parameters of
        the sync machines, which belong to this domain. */
    gptp_def_sync_t                     *prSync; /* 8 bytes */
    /*! Pointer to the cmd structure for sending ETH frames. */
    void                                *pvTxCmdSig; /* 8 bytes */
    /*! Pointer to Buffer index map for Signal message. */
    gptp_def_tx_frame_map_t             *prFrameMapSign; /* 8 bytes */
#if (GPTP_COUNTERS == STD_ON)
    /*! Pointer to domain counters array. */
    gptp_def_countes_dom_t              *prCntrsDom; /* 8 bytes */
#endif /* (GPTP_COUNTERS == STD_ON) */
    /*! Threshold for the outlier time value received. */
    uint32_t                            u32SyncOutlierThrNs; /* 4 bytes */
    /*! VLAN TCI. */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Domain number. */
    uint8_t                             u8DomainNumber; /* 1 byte */
    /*! Count of Sync machines operating under the domain. */
    uint8_t                             u8NumberOfSyncMachines; /* 1 byte */
    /*! Reference domain number for synced GM. The domain from which the synced
        GM takes Rate Ratio to the Grand Master. If reference to itself,
        the Rate Ratio is 1.0. */
    uint8_t                             u8RefDomForSynced; /* 1 byte */
    /*! Start-up time-out - time-out for non Grand Master, after which
        the domain starts acting as Grand Master, if not received sync message
        on slave port. */
    uint8_t                             u8StartupTimeoutS; /* 1 byte */
    /*! Sync receipt time-out [count of missed syncs] - count of missed sync
        messages on the slave port after which the Error is raised. */
    uint8_t                             u8SyncReceiptTimeoutCnt; /* 1 byte */
    /*! Count of consecutive outliers to drop. */
    uint8_t                             u8OutlierIgnoreCnt; /* 1 byte */
    /*! Synchronized Grand Master transmits Corrected time, instead of free running. */
    bool                                bSyncedGm; /* 1 byte */
    /*! Domain is Grand Master = true / domain is not Grand Master = false. */
    bool                                bDomainIsGm; /* 1 byte */
    /* 2 bytes padding */
    /* 48/56 bytes total */
} gptp_def_init_params_domain_t;

/*!
 * @brief gPTP Initialization - gPTP Stack parameters.
 */
typedef struct
{
    /*! Data structure containing pointers to all callback functions. */
    gptp_def_cb_funcs_t                 rPtpStackCallBacks; /* 56/88 bytes */
    /*! Structure containing synchronization notification parameters. */
    gptp_def_params_syn_lock_t          rSynLockParam; /* 24 bytes */
    /*! PI Controller configuration structure. */
    gptp_def_pi_controller_conf_t       rPIControllerConfig; /* 24 bytes */
    /*! Pdelay averaging filter weight. */
    float64_t                           f64PdelAvgWeight; /* 8 bytes */
    /*! Rate ratio averaging filter weight. */
    float64_t                           f64RratioAvgWeight; /* 8 bytes */
    /*! Rate ratio maximum deviation. */
    float64_t                           f64RratioMaxDev; /* 8 bytes */
    /*! Pdelay NVM threshold - if current pdelay is different of the threshold,
        the value in the NVM is updated. */
    float64_t                           f64PdelayNvmWriteThr; /* 8 bytes */
    /*! Neighbor rate ratio NVM threshold - if current neighbor rate ration
        is different of the threshold, the value in the NVM is updated. */
    float64_t                           f64RratioNvmWriteThr; /* 8 bytes */
    /*! PI Controller maximum threshold - creates PI Controller action band. */
    uint64_t                            u64PIControllerMaxThreshold; /* 8 bytes */
    /*! Pointer to array of structure - mapping of gPTP ports to the ports on
        switch. */
    const gptp_def_map_table_t          *pcrPortMapTable; /* 8 bytes */
    /*! Pointer to array of structure containing Pdelay initial parameters of
        Pdelay machines. */
    const gptp_def_init_params_pdel_t   *pcrPdelayMachinesParam; /* 8 bytes */
    /*! Pointer to array of structure containing Domain initial parameters of
        all domains. */
    const gptp_def_init_params_domain_t *pcrDomainsSyncsParam; /* 8 bytes */
    /*! Pointer to array of structure - map of gPTP ports to switch ports. */
    gptp_def_port_t                     *paPort; /* 8 bytes */
    /*! Pointer to array of structure - internal gPTP Domain data. */
    gptp_def_domain_t                   *paDomain; /* 8 bytes */
    /*! Pointer to array of structure - internal gPTP Pdelay data. */
    gptp_def_pdelay_t                   *paPdelay; /* 8 bytes */
#if (GPTP_COUNTERS == STD_ON)
    /*! Pointer to port counters array. */
    gptp_def_countes_port_t             *prCntrsPort; /* 8 bytes */
#endif /* (GPTP_COUNTERS == STD_ON) */
    /*! VLAN TCI */
    uint16_t                            u16VlanTci; /* 2 bytes */
    /*! Priority of transmitted ETH Frame. */
    uint8_t                             u8EthFramePrio; /* 1 byte */
    /*! Count of domains used in the application. */
    uint8_t                             u8GptpDomainsCount; /* 1 byte */
    /*! Count of gPTP ports which corresponds to the count of Pdelay machines. */
    uint8_t                             u8GptpPortsCount; /* 1 byte */
    /*! Number of clock instances which should be updated/corrected. */
    uint8_t                             u8NumberOfClkInstances; /* 1 byte */
    /*! Compatibility with SdoID - if disabled, other "transport specific"
        than 0x1 is ignored. For the AVNU compliance must be disabled. */
    bool                                bSdoIdCompatibilityMode; /* 1 byte */
    /*! Flag indicating, if the Signaling mechanism is enabled. */
    bool                                bSignalingEnabled; /* 1 byte */
    /*! VLAN enabled. */
    bool                                bVlanEnabled; /* 1 byte */
    /*! Use both clock - free running and corrected. */
    bool                                bDoubleClock; /* 1 byte */
    /* 6 bytes padding */
    /* 216/256 bytes total */
} gptp_def_init_params_t;
/*! @} */

#endif /* GPTP_DEF */
/*******************************************************************************
 * EOF
 ******************************************************************************/
