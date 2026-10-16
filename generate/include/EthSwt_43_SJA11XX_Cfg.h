/*==================================================================================================
*   Project            : RTD AUTOSAR 4.4
*   Platform           : N/A
*   Peripheral         : SJA11XX
*   Dependencies       : none
*
*   AutosarVersion     : 4.4.0
*   AutosarRevision    : ASR_REL_4_4_REV_0000
*   AutosarConfVariant :
*   SW Version         : 1.0.2
*   BuildVersion       : SJA11XX_RTD_1_0_2_D2604_ASR_REL_4_4_REV_0000_20260421
*
*   Copyright 2026 NXP Semiconductors
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef ETHSWT_43_SJA11XX_CFG_H
#define ETHSWT_43_SJA11XX_CFG_H

/**
*   @file    EthSwt_43_SJA11XX_Cfg.h
*   @implements EthSwt_Cfg.h_Artifact
*   @version 1.0.2
*
*   @brief   AUTOSAR EthSwt_43_SJA11XX - Configuration header of EthSwt driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
*
*   @addtogroup ethswt_driver_cfg
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETHSWT_43_SJA11XX_VENDOR_ID_CFG                    43
#define ETHSWT_43_SJA11XX_MODULE_ID_CFG                    89
#define ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION_CFG     4
#define ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION_CFG     4
#define ETHSWT_43_SJA11XX_AR_RELEASE_REVISION_VERSION_CFG  0
#define ETHSWT_43_SJA11XX_SW_MAJOR_VERSION_CFG             1
#define ETHSWT_43_SJA11XX_SW_MINOR_VERSION_CFG             0
#define ETHSWT_43_SJA11XX_SW_PATCH_VERSION_CFG             2

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h header file are of the same Autosar version */
#if ((ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AutoSar Version Numbers of EthSwt_Cfg.h and Mcal.h are different"
#endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief  Development Error Types for EthSwt. */

/** @brief  Invalid switch index. */
#define ETHSWT_43_SJA11XX_E_INV_SWITCH_IDX         ((uint8)0x01U)
/** @brief  EthSwt module was not initialized. */
#define ETHSWT_43_SJA11XX_E_UNINIT                 ((uint8)0x02U)
/** @brief  Invalid pointer in parameter list. */
#define ETHSWT_43_SJA11XX_E_PARAM_POINTER          ((uint8)0x03U)
/** @brief  Invalid API which is not available by another module. */
#define ETHSWT_43_SJA11XX_E_INV_API                ((uint8)0x05U)
/** @brief  Invalid switch port index. */
#define ETHSWT_43_SJA11XX_E_INV_SWITCHPORT_IDX     ((uint8)0x06U)
/** @brief  Invalid Controller Index. */
#define ETHSWT_43_SJA11XX_E_INV_CTRL_IDX           ((uint8)0x07U)
/** @brief  Invalid input parameter. */
#define ETHSWT_43_SJA11XX_E_INV_PARAM              ((uint8)0x08U)
/** @brief  Invalid configuration. */
#define ETHSWT_43_SJA11XX_E_INIT_FAILED            ((uint8)0x09U)

/** @brief  Invalid API call. */
#define ETHSWT_43_SJA11XX_E_INVALID_CALL           ((uint8)0xC0U)
/** @brief  Invalid learning mode. */
#define ETHSWT_43_SJA11XX_E_UNSUPPORTED_MODE       ((uint8)0xC1U)
/** @brief  Invalid Gate Index. */
#define ETHSWT_43_SJA11XX_E_INV_GATE_IDX           ((uint8)0xC2U)
/** @brief  EthSwt module was already initialized. */
#define ETHSWT_43_SJA11XX_E_ALREADY_INITIALIZED    ((uint8)0xC3U)

/** @brief  Port mirroring configuration is not supported by Ethernet switch driver or by the Ethernet switch hardware. */
#define ETHSWT_43_SJA11XX_PORT_MIRRORING_CONFIGURATION_NOT_SUPPORTED   ((uint8)0x02U)
/**
* @brief      Specifies the InstanceId of this module instance.
*/
#define ETHSWT_43_SJA11XX_INSTANCE_ID          ((uint8)0U)

/**
* @brief   Switches the EthSwt_DeletePortMirrorConfiguration() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_DELETE_PORT_MIRROR_CONFIGURATION_API         (STD_OFF)

/**
* @brief   Switches the EthSwt_EnableCableDiagnostic() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API         (STD_OFF)

/**
* @brief          Support for enable VLAN API.
* @details        Switches the EthSwt_EnableVlan() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_ENABLE_VLAN_API          (STD_ON)

/**
* @brief          Support for get ARL table API.
* @details        Switches the EthSwt_GetArlTable() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_ARL_TABLE_API        (STD_ON)

/**
* @brief          Support to get the baud rate of a port.
* @details        Switches the EthSwt_GetBaudRate() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_BAUD_RATE_API     (STD_ON)

/**
* @brief          Support for get drop count values API.
* @details        Switches the EthSwt_GetCounterValues() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_COUNTER_VALUES_API   (STD_ON)

/**
* @brief          Support for get duplex mode API.
* @details        Switches the EthSwt_GetDuplexMode() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API    (STD_OFF)

/**
* @brief          Support for get link state API.
* @details        Switches the EthSwt_GetLinkState() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_LINK_STATE_API    (STD_ON)

/**
* @brief          Support for get MAC learning mode API.
* @details        Switches the EthSwt_GetMacLearningMode() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_MAC_LEARNING_MODE_API    (STD_ON)

/**
* @brief          Support for get MAC learning mode API.
* @details        Switches the EthSwt_GetMaxFIFOBufferFillLevel() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_MAX_FIFO_BUFFER_FILL_LEVEL_API    (STD_OFF)

/**
* @brief          Support for get port cable diagnostics result API.
* @details        Switches the EthSwt_GetPortCableDiagnosticsResult() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API    (STD_OFF)

/**
* @brief          Support for get port identifier API.
* @details        Switches the EthSwt_GetPortIdentifier() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API  (STD_OFF)

/**
* @brief          Support for get port MAC addr API.
* @details        Switches the  EthSwt_GetPortMacAddr() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_MAC_ADDR_API    (STD_ON)

/**
* @brief          Support for get port mirror state API.
* @details        Switches the  EthSwt_GetPortMirrorState() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_MIRROR_STATE_API    (STD_ON)

/**
* @brief          Support for get port signal quality API.
* @details        Switches the  EthSwt_GetPortSignalQuality() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API  (STD_OFF)

/**
* @brief          Support for get RX stats API.
* @details        Switches the  EthSwt_GetRxtats() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_RX_STATS_API             (STD_ON)

/**
* @brief          Support for get switch identifier API.
* @details        Switches the   EthSwt_GetSwitchIdentifier() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_SWITCH_IDENTIFIER_API    (STD_ON)

/**
* @brief          Support for get switch port mode API.
* @details        Switches the   EthSwt_GetSwitchPortMode() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API    (STD_OFF)

/**
* @brief          Support for get switch register API.
* @details        Switches the EthSwt_GetSwitchReg() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_SWITCH_REG_API           (STD_ON)

/**
* @brief          Support for get TX Error counter values API.
* @details        Switches the Eth_GetTxErrorCounterValues() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_TX_ERROR_COUNTER_VALUES_API      (STD_ON)

/**
* @brief          Support for get TX stats API.
* @details        Switches the Eth_GetTxStats() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_TX_STATS_API      (STD_ON)

/**
* @brief          Support for global time support API.
* @details        Switches the Global Time APIs used amongst others by Global Time Synchronization over Ethernet.
*
* @api
*/
#define ETHSWT_43_SJA11XX_GLOBAL_TIME_SUPPORT_API      (STD_ON)

/**
* @brief          Support for the EthSwt_EnableEgressTimeStamp API.
* @details        Switches the EthSwt_EnableEgressTimeStamp APIs ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_ENABLE_EGRESS_TIME_STAMP_API      (STD_ON)

/**
* @brief          Support for management support API.
* @details        Switches the Switch management APIs to support a Switch-port specific communication attribute access.
*
* @api
*/
#define ETHSWT_43_SJA11XX_MANAGEMENT_SUPPORT_API      (STD_ON)

/**
* @brief          Support for read port mirror configuration API.
* @details        Switches the EthSwt_ReadPortMirrorConfiguration() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_READ_PORT_MIRROR_CONFIGURATION_API      (STD_ON)

/**
* @brief          Support for read port mirror configuration API.
* @details        Switches the EthSwt_ReadTrcvRegister() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API      (STD_OFF)

/**
* @brief          Support for reset configuration API.
* @details        Switches the EthSwt_ResetConfiguration() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_RESET_CONFIGURATION_API      (STD_ON)

/**
* @brief          Support for set forwarding mode API.
* @details        Switches the EthSwt_SetForwardingMode() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_FORWARDING_MODE_API      (STD_ON)

/**
* @brief          Support for set MAC learning mode API.
* @details        Switches the EthSwt_SetMacLearningMode() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_MAC_LEARNING_MODE_API      (STD_ON)

/**
* @brief          Support for set port loopback mode API.
* @details        Switches the EthSwt_SetPortLoopbackModeApi() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API      (STD_OFF)

/**
* @brief          Support for set port mirror state API.
* @details        Switches the EthSwt_SetPortMirrorState() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_PORT_MIRROR_STATE_API      (STD_ON)

/**
* @brief          Support for set port test mode API.
* @details        Switches the EthSwt_SetPortTestMode() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API      (STD_OFF)

/**
* @brief          Support for set port TX mode API.
* @details        Switches the EthSwt_SetPortTxMode() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API      (STD_ON)

/**
* @brief          Support for set switch port mode API.
* @details        Switches the EthSwt_SetSwitchPortMode() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API      (STD_OFF)

/**
* @brief          Support for set switch register API.
* @details        Switches the EthSwt_SetSwitchReg() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_SET_SWITCH_REG_API      (STD_ON)

/**
* @brief          Support for starting switch port auto negotiation API.
* @details        Switches the EthSwt_StartSwitchPortAutoNegotiation() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API      (STD_OFF)

/**
* @brief          Support for store configuration API.
* @details        Switches the EthSwt_StoreConfiguration() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_STORE_CONFIGURATION_API      (STD_OFF)

/**
* @brief          Support for verify configuration API.
* @details        Switches the  EthSwt_VerifyConfig() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_VERIFY_CONFIG_API      (STD_ON)

/**
* @brief          Support for version info API.
* @details        Switches the EthSwt_GetVersionInfo() API ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_VERSION_INFO_API      (STD_ON)

/**
* @brief          Support for write port mirror configuration API.
* @details        Switches the  EthSwt_WritePortMirrorConfiguration() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_WRITE_PORT_MIRROR_CONFIGURATION_API      (STD_ON)

/**
* @brief          Support for write transceiver register API.
* @details        Switches the  EthSwt_WriteTrcvRegister() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API      (STD_OFF)

/**
* @brief          Support for get ARL entry API.
* @details        Switches the  EthSwtGetArlEntryApi() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_ARL_ENTRY_API      (STD_OFF)

/**
* @brief          Support for update ARL entry API.
* @details        Switches the  EthSwtUpdateArlEntryApi() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_UPDATE_ARL_ENTRY_API      (STD_OFF)

/**
* @brief          Support for getting port fw parameters API.
* @details        Switches the  EthSwt_GetPortForwardingRules() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_GET_PORT_FORWARDING_RULES_API      (STD_OFF)

/**
* @brief          Support for updating port fw parameters API.
* @details        Switches the  EthSwt_UpdatePortForwardingRules() API
*
* @api
*/
#define ETHSWT_43_SJA11XX_UPDATE_PORT_FORWARDING_RULES_API      (STD_OFF)

/**
* @brief          Support for CBS features.
* @details        Switches the CBS support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_CBS_SUPPORT_API      (STD_OFF)

/**
* @brief          Support for DPI features.
* @details        Switches the DPI support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_DPI_SUPPORT_API      (STD_ON)

/**
* @brief          Support for FRER features.
* @details        Switches the FRER support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_FRER_SUPPORT_API      (STD_ON)

/**
* @brief          Support for PSFP features.
* @details        Switches the PSFP support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_PSFP_SUPPORT_API      (STD_ON)

/**
* @brief          Support for PTP features.
* @details        Switches the PTP support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_PTP_SUPPORT_API      (STD_ON)

#if (ETHSWT_43_SJA11XX_PTP_SUPPORT_API == STD_ON)
/**
* @brief          Support for TAS features.
* @details        Switches the TAS support API
*
* @api
*/
#define ETHSWT_43_SJA11XX_TAS_SUPPORT_API      (STD_OFF)
#endif /* ETHSWT_43_SJA11XX_PTP_SUPPORT_API == STD_ON */

/**
* @brief          Support for NVM API.
* @details        Switches the NVM APIs
*
* @api
*/
#define ETHSWT_43_SJA11XX_NVM_API      (STD_OFF)

/**
* @brief      Specifies the cycle time of the periodic main function of EthSwt. Defined in seconds
*/
#define ETHSWT_43_SJA11XX_MAIN_FUNCTION_PERIOD         ((float)0)

/**
* @brief            Timeout representing the number of loops for preventing to lock inside am infinite while/for.
*/
#define ETHSWT_43_SJA11XX_TIMEOUT_LOOPS   ((uint32)65535U)

/**
* @brief      Specifies specifies the timeout while the Switch driver is waiting for management information out of the Switch for reception.
*/
#define ETHSWT_43_SJA11XX_MGMT_INFO_INDICATION_TIMEOUT ((float)0)

/**
* @brief      The number of MainFunction calls to wait for a timestamp. If timestamps are not available, the NULL_PTR will be passed as paramter to EthIf.
*/
#define ETHSWT_43_SJA11XX_TIMESTAMP_TIMEOUT ((uint32)0xFFFFFFFFUL)

/**
* @brief   Switches the Development Error Detection and Notification ON or OFF.
*
* @api
*/
#define ETHSWT_43_SJA11XX_DEV_ERROR_DETECT         (STD_OFF)

/**
* @brief            Enable/Disable reporting the Dem Error.
*/
#define ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS (STD_OFF)

#define ETHSWT_43_SJA11XX_SPI_LEVEL_DELIVERED (0U)
#define ETHSWT_43_SJA11XX_SYNC_TRANSMIT

/**
* @brief            Use SPI read/write for external switches.
*/
#define ETHSWT_43_SJA11XX_USE_EXTERNAL_RW    (STD_OFF)

/**
* @brief            Maximum number of ports for each switch.
*/
#define ETHSWT_43_SJA11XX_MAX_SWITCH_PORTS         ((uint8)11U)

/**
* @brief            Maximum number of switches (based on the maximum index that can be configured in the hw device).
*/
#define ETHSWT_43_SJA11XX_MAX_SWITCHES             ((uint8)16U)

/**
* @brief            Maximum number of switches (based on the maximum index that can be configured in the hw device).
*/
#define ETHSWT_43_SJA11XX_MAX_GATES                ((uint8)8U)

/**
* @brief            Maximum number of FIFOs in the switch
*/
#define ETHSWT_43_SJA11XX_MAX_FIFO                ((uint8)8U)

/**
* @brief            Maximum number of buffers, used for management and time stamping APIs.
*/
#define ETHSWT_43_SJA11XX_MAX_BUFFERS              ((uint8)11U)

/**
* @brief            The number of configured switches for each variant.
*/
#define ETHSWT_43_SJA11XX_SWITCHES                 ((uint8)1U)

/**
* @brief            Invalid switch index.
*/
#define ETHSWT_43_SJA11XX_INVALID_SWITCH_INDEX     ((uint8)255U)

/**
* @brief            Invalid port index.
*/
#define ETHSWT_43_SJA11XX_INVALID_PORT_INDEX       ((uint8)255U)

/**
* @brief            Invalid transceiver index.
*/
#define ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX       ((uint8)255U)

#if ((ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON))
/**
* @brief            Invalid transceiver address.
*/
#define ETHSWT_43_SJA11XX_INVALID_TRCV_ADDRESS     ((uint8)255U)
#endif

/**
* @brief            Invalid controller index.
*/
#define ETHSWT_43_SJA11XX_INVALID_CTRL_INDEX       ((uint8)255U)

/**
* @brief            Invalid gate index.
*/
#define ETHSWT_43_SJA11XX_INVALID_GATE_INDEX       ((uint8)255U)

/**
* @brief            Pre-compile Support.
*/
#define ETHSWT_43_SJA11XX_PRECOMPILE_SUPPORT   (STD_ON)



/**
* @brief            Check if some Api are enable
*/
#if ((ETHSWT_43_SJA11XX_PRECOMPILE_SUPPORT == STD_OFF) || (ETHSWT_43_SJA11XX_GET_ARL_ENTRY_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_PORT_FORWARDING_RULES_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON) || (ETHSWT_43_SJA11XX_UPDATE_PORT_FORWARDING_RULES_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_COUNTER_VALUES_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_RX_STATS_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_TX_STATS_API == STD_ON) || (ETHSWT_43_SJA11XX_WRITE_PORT_MIRROR_CONFIGURATION_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_SWITCH_REG_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_MANAGEMENT_SUPPORT_API == STD_ON) || (ETHSWT_43_SJA11XX_GLOBAL_TIME_SUPPORT_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_VERIFY_CONFIG_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_SWITCH_IDENTIFIER_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_MAC_LEARNING_MODE_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_PORT_MIRROR_STATE_API == STD_ON) || (ETHSWT_43_SJA11XX_PSFP_SUPPORT_API == STD_ON) \
    || ((ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON) && (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON))\
    || (ETHSWT_43_SJA11XX_PTP_SUPPORT_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_PORT_MIRROR_CONFIGURATION_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_GET_MAX_FIFO_BUFFER_FILL_LEVEL_API == STD_ON) || (ETHSWT_43_SJA11XX_CBS_SUPPORT_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_DPI_SUPPORT_API == STD_ON) || (ETHSWT_43_SJA11XX_FRER_SUPPORT_API == STD_ON) \
    || (ETHSWT_43_SJA11XX_UPDATE_ARL_ENTRY_API == STD_ON) || (ETHSWT_43_SJA11XX_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON))

#define ETHSWT_43_SJA11XX_CHECK_API_USED
#endif

/**
* @brief            Create defines with the IDs assigned to Switch configurations.
*                   These IDs will be transmitted as input parameters for EthSwt APIs.
*/

#define EthSwtConfig_0   ((uint8)0U)
#define EthSwtConf_EthSwtConfig_EthSwtConfig_0   ((uint8)0U)


/**
* @brief            Create defines with the IDs assigned to Switch Port configurations.
*                   These IDs will be transmitted as input parameters for EthSwt APIs.
*/

#define EthSwtPort_0   ((uint8)0U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_0   ((uint8)0U)


#define EthSwtPort_1   ((uint8)1U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_1   ((uint8)1U)


#define EthSwtPort_2   ((uint8)2U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_2   ((uint8)2U)


#define EthSwtPort_3   ((uint8)3U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_3   ((uint8)3U)


#define EthSwtPort_4   ((uint8)4U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_4   ((uint8)4U)


#define EthSwtPort_5   ((uint8)5U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_5   ((uint8)5U)


#define EthSwtPort_6   ((uint8)6U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_6   ((uint8)6U)


#define EthSwtPort_7   ((uint8)7U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_7   ((uint8)7U)


#define EthSwtPort_8   ((uint8)8U)
#define EthSwtConf_EthSwtConfig_EthSwtPort_8   ((uint8)8U)


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPES
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETHSWT_CFG_H */
