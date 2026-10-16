/**
*   @file    EthTrcv_43_PHY_Cfg.h
*   @implements EthTrcv_Cfg.h_Artifact
*   @version 1.0.8
*
*   @brief   AUTOSAR EthTrcv_43_PHY - Configuration header of EthTrcv driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
*
*   @addtogroup EthTrcv
*   @{
*/
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : N/A
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.8
*   Build Version        : SJA11XX_RTD_1_0_8_D2601_ASR_REL_4_4_REV_0000_20260112
*
*   Copyright 2020-2026 NXP Semiconductors
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef ETHTRCV_43_PHY_CFG_H
#define ETHTRCV_43_PHY_CFG_H

#ifdef __cplusplus
extern "C"
{
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
/* Inclusion of incompatible header files shall be avoided */

#define ETHTRCV_43_PHY_VENDOR_ID_CFG                    43

#define ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_CFG     4
#define ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_CFG     4
#define ETHTRCV_43_PHY_AR_RELEASE_REVISION_VERSION_CFG  0

#define ETHTRCV_43_PHY_SW_MAJOR_VERSION_CFG             1
#define ETHTRCV_43_PHY_SW_MINOR_VERSION_CFG             0
#define ETHTRCV_43_PHY_SW_PATCH_VERSION_CFG             8
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AutoSar Version Numbers of EthTrcv_Cfg.h and Mcal.h are different"
#endif
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief  Development Error Types for EthTrcv. */

/** @brief  Invalid transceiver index. */
#define ETHTRCV_43_PHY_E_INV_TRCV_IDX          ((uint8)0x01U)
/** @brief  EthTrcv module was not initialized. */
#define ETHTRCV_43_PHY_E_UNINIT                ((uint8)0x02U)
/** @brief  Invalid pointer in parameter list. */
#define ETHTRCV_43_PHY_E_PARAM_POINTER         ((uint8)0x03U)
/** @brief  Invalid value in parameter list. */
#define ETHTRCV_43_PHY_E_NOT_SUPPORTED         ((uint8)0x04U)
/** @brief  EthTrcv module was already initialized. */
#define ETHTRCV_43_PHY_E_ALREADY_INITIALIZED       ((uint8)0x05U)
/** @brief  Invalid argument passed to init function. */
#define ETHTRCV_43_PHY_E_INIT_FAILED               ((uint8)0x06U)


/**
* @brief      Specifies the InstanceId of this module instance.
*/
#define ETHTRCV_43_PHY_INSTANCE_ID          ((uint8)0U)

/**
* @brief   Switches the Development Error Detection and Notification ON or OFF.
*
* @api
*/
#define ETHTRCV_43_PHY_DEV_ERROR_DETECT         (STD_ON)

/**
* @brief          Support for get baud rate API.
* @details        Enables / Disables EthTrcv_GetBaudRate API
*
* @api
*/
#define ETHTRCV_43_PHY_GET_BAUD_RATE_API        (STD_ON)

/**
* @brief          Support for get duplex mode API.
* @details        Enables / Disables EthTrcv_GetDuplexMode API
*
* @api
*/
#define ETHTRCV_43_PHY_GET_DUPLEX_MODE_API      (STD_ON)

/**
* @brief          Support for get link state API.
* @details        Enables / Disables EthTrcv_GetLinkState API
*
* @api
*/
#define ETHTRCV_43_PHY_GET_LINK_STATE_API       (STD_ON)

/**
* @brief          Support for get transceiver mode API.
* @details        Enables / Disables EthTrcv_GetTransceiverMode API
*
* @api
*/
#define ETHTRCV_43_PHY_GET_TRANSCEIVER_MODE_API        (STD_ON)

/**
* @brief          Support for get transceiver wakeup mode API.
* @details        Enables / Disables EthTrcv_GetTransceiverWakeupMode API
*
* @api
*/
#define ETHTRCV_43_PHY_GET_TRANSCEIVER_WAKEUP_MODE_API (STD_OFF)

/**
* @brief          Support for set transceiver mode API.
* @details        Enables / Disables EthTrcv_SetTransceiverMode API
*
* @api
*/
#define ETHTRCV_43_PHY_SET_TRANSCEIVER_MODE_API  (STD_ON)

/**
* @brief          Support for start auto negotiation API.
* @details        Enables / Disables EthTrcv_StartAutoNegotiation API
*
* @api
*/
#define ETHTRCV_43_PHY_START_AUTO_NEGOTIATION_API (STD_OFF)

/**
* @brief          Support for Get Phy Signal Quality API.
* @details        Enables / Disables EthTrcv_GetPhySignalQuality API.
*
* @api
*/
#define ETHTRCV_43_PHY_GET_PHY_SIGNAL_QUALITY_API (STD_ON)

/**
* @brief          Support for Get Phy Identifier API.
* @details        Enables / Disables EthTrcv_GetPhyIdentifier API.
*
* @api
*/
#define ETHTRCV_43_PHY_GET_PHY_IDENTIFIER_API (STD_ON)

/**
* @brief          Support for Set Phy Test Mode API.
* @details        Enables / Disables EthTrcv_SetPhyTestMode API.
*
* @api
*/
#define ETHTRCV_43_PHY_SET_PHY_TEST_MODE_API  (STD_ON)

/**
* @brief          Support for Set Phy Tx Mode API.
* @details        Enables / Disables EthTrcv_SetPhyTxMode API.
*
* @api
*/
#define ETHTRCV_43_PHY_SET_PHY_TX_MODE_API    (STD_ON)

/**
* @brief          Support for Get Cable Diagnostics Result API.
* @details        Enables / Disables EthTrcv_GetCableDiagnosticsResult API.
*
* @api
*/
#define ETHTRCV_43_PHY_GET_CABLE_DIAGNOSTICS_RESULT_API (STD_ON)

/**
* @brief          Support for Run Cable Diagnostic and Get Cable Diagnostics Result APIs.
* @details        Enable/disable the APIs for cable diagnostic: EthTrcv_RunCableDiagnostic, EthTrcv_GetCableDiagnosticsResult.
*
* @api
*/
#define ETHTRCV_43_PHY_ENABLE_CABLE_DIAGNOSTIC_API      (STD_ON)

/**
* @brief      If wakeup mode is set to ETHTRCV_WAKEUP_NOT_SUPPORTED this will be STD_OFF, else STD_ON
*/
#define ETHTRCV_43_PHY_WAKEUP_SUPPORT                   (STD_OFF)

/**
* @brief      Specifies the cycle time of the periodic main function of EthTrcv. Defined in seconds
*/

/**
* @brief      Timeout representing the number of loops for preventing to lock inside am infinite while/for.
*/
#define ETHTRCV_43_PHY_TIMEOUT_LOOPS   ((uint32)65535U)

/**
* @brief      Enables/disables dem reporting
*/
#define ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS (STD_OFF)

/**
* @brief      Support for MacSec APIs.
* @details    Enable/disable the APIs for MacSec.
*
* @api
*/
#define ETHTRCV_43_PHY_MACSEC_SUPPORT                   (STD_OFF)

/**
* @brief      Enables/disables PHY drivers MKA header overriding.
*/
#if (STD_ON == ETHTRCV_43_PHY_MACSEC_SUPPORT)
#define ETHTRCV_43_PHY_MACSEC_MKA_HEADER_OVERRIDE       (STD_OFF)
#endif

/**
* @brief      Maximum number of transceivers
*/
#define ETHTRCV_43_PHY_MAX_TRANSCEIVERS             ((uint8)7)

/**
* @brief     Invalid transceiver index
*/
#define ETHTRCV_43_PHY_INVALID_TRCV_INDEX           ((uint8)255U)

/**
* @brief     Invalid wakeup source
*/
#define ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE       ((uint32)255U)

/**
* @brief     Invalid Icu channel ID
*/
#define ETHTRCV_43_PHY_INVALID_ICU_CHANNEL       ((uint32)255U)

/**
* @brief            Pre-compile Support.
*/
#define ETHTRCV_43_PHY_PRECOMPILE_SUPPORT (STD_ON)

/**
* @brief            Pre-Compile structure from EthTrcv_Cfg.c file.
*/


/**
* @brief            Create defines with the IDs assigned to Transceiver configurations.
*                   These IDs will be transmitted as input parameters for EthTrcv APIs.
*/







/** @brief   Check if the APIs with pointer parameters are enable */
#if ((ETHTRCV_43_PHY_GET_TRANSCEIVER_MODE_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_LINK_STATE_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_BAUD_RATE_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_DUPLEX_MODE_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_PHY_SIGNAL_QUALITY_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_CABLE_DIAGNOSTICS_RESULT_API == STD_ON) \
    || (ETHTRCV_43_PHY_GET_PHY_IDENTIFIER_API == STD_ON) \
    || (ETHTRCV_43_PHY_MACSEC_SUPPORT == STD_ON) \
    || (ETHTRCV_43_PHY_GET_TRANSCEIVER_WAKEUP_MODE_API == STD_ON))
#define ETHTRCV_43_PHY_CHECK_POINTER_PARAMETER_API_USED
#endif
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/* The WakeUp callout functions */
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
#endif

#ifdef __cplusplus
}
#endif

#endif /* ETHTRCV_CFG_H */

