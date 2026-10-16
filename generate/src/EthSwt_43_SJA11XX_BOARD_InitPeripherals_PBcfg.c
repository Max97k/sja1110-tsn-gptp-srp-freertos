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

/**
*   @file   EthSwt_43_SJA11XX_PBcfg.c
*   @implements EthSwt_PBcfg.c_Artifact
*   @version 1.0.2
*
*   @brief   AUTOSAR EthSwt_43_SJA11XX - Data structures for the EthSwt driver.
*   @details Postbuild structure configurations for the driver initalization.
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
#include "EthSwt_43_SJA11XX.h"

#if (ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif

#include "EthTrcv_43_PHY.h"
                        #if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
#include "Eth.h"
#include "Eth_43_ENET.h"
#endif

#include "Switch_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETHSWT_43_SJA11XX_PBCFG_VENDOR_ID_C                     43
#define ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define ETHSWT_43_SJA11XX_PBCFG_SW_MAJOR_VERSION_C              1
#define ETHSWT_43_SJA11XX_PBCFG_SW_MINOR_VERSION_C              0
#define ETHSWT_43_SJA11XX_PBCFG_SW_PATCH_VERSION_C              2

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The Eth Switch module's implementer shall avoid the integration of incompatible files.
*/

/* Check if current file and Eth Switch header file are of the same vendor */
#if (ETHSWT_43_SJA11XX_PBCFG_VENDOR_ID_C != ETHSWT_43_SJA11XX_VENDOR_ID)
#error "EthSwt_PBcfg.c and EthSwt.h have different vendor ids"
#endif

/* Check if current file and Eth Switch header file are of the same Autosar version */
#if ((ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C    != ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_REVISION_VERSION_C != ETHSWT_43_SJA11XX_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of EthSwt_PBcfg.c and EthSwt.h are different"
#endif

/* Check if current file and Eth Switch header file are of the same Software version */
#if ((ETHSWT_43_SJA11XX_PBCFG_SW_MAJOR_VERSION_C != ETHSWT_43_SJA11XX_SW_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_SW_MINOR_VERSION_C != ETHSWT_43_SJA11XX_SW_MINOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_SW_PATCH_VERSION_C != ETHSWT_43_SJA11XX_SW_PATCH_VERSION) \
    )
#error "Software Version Numbers of EthSwt_PBcfg.c and EthSwt.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and DEM header file are of the same version */
#if (ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#if ((ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthSwt_PBcfg.c and Dem.h are different"
#endif
#endif

/* Check if current file and EthTrcv header file are of the same version */
#if ((ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C != ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C != ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthSwt_PBcfg.c and EthTrcv.h are different"
#endif
                    #if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))

/* Check if current file and EthTrcv header file are of the same version */
#if ((ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C != ETH_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C != ETH_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthSwt_PBcfg.c and Eth.h are different"
#endif
/* Check if current file and EthTrcv header file are of the same version */
#if ((ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C != ETH_43_ENET_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C != ETH_43_ENET_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthSwt_PBcfg.c and Eth.h are different"
#endif

#endif
#endif
/* Checks against Switch_Ip_Cfg.h */
#if (ETHSWT_43_SJA11XX_PBCFG_VENDOR_ID_C != SWITCH_IP_CFG_VENDOR_ID)
    #error "EthSwt_PBcfg.c and Switch_Ip_Cfg.h have different vendor ids"
#endif
#if (( ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     ( ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     ( ETHSWT_43_SJA11XX_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of EthSwt_PBcfg.c and Switch_Ip_Cfg.h are different"
#endif
#if (( ETHSWT_43_SJA11XX_PBCFG_SW_MAJOR_VERSION_C != SWITCH_IP_CFG_SW_MAJOR_VERSION) || \
     ( ETHSWT_43_SJA11XX_PBCFG_SW_MINOR_VERSION_C != SWITCH_IP_CFG_SW_MINOR_VERSION) || \
     ( ETHSWT_43_SJA11XX_PBCFG_SW_PATCH_VERSION_C != SWITCH_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of EthSwt_PBcfg.c and Switch_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                          LOCAL S (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define ETHSWT_43_SJA11XX_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"


#if (ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthSwt_43_SJA11XX_DemConfigType EthSwt_DemConfig0 =
{

    /* DEM error reporting ETHSWT_E_ACCESS */
    {(uint32)STD_OFF, 0U},

    /* DEM error reporting ETHSWT_E_SYNCPORT2PHY */
    {(uint32)STD_OFF, 0U},

    /* DEM error reporting ETHSWT_E_TIMEOUT */
    {(uint32)STD_OFF, 0U}

};
#endif /* (ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */


/**
* @brief        Definition of Ethernet switch port structures.
* @details      Configures the switch ports.
*               Configuration set by calling EthSwt_SwitchInit() API.
*/
static const EthSwt_43_SJA11XX_SwitchPortConfigType EthSwt_PortConfigOfSwt0[9] =
{
    {
        /* Time stamp support */
        (boolean)FALSE,
        /* Port Transceiver Reference */
        (uint8)ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            NULL_PTR,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)0U,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            &EthTrcv_43_PHY_TransceiverLinkStateRequest,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            &EthTrcv_43_PHY_GetLinkState,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            &EthTrcv_43_PHY_GetBaudRate,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetDuplexMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            &EthTrcv_43_PHY_GetPhySignalQuality,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            &EthTrcv_43_PHY_GetPhyIdentifier,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTestMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyLoopbackMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTxMode,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            &EthTrcv_43_PHY_RunCableDiagnostic,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            &EthTrcv_43_PHY_GetCableDiagnosticsResult,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_43_ENET_ReadMii,
            &Eth_43_ENET_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            NULL_PTR,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)1U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            NULL_PTR,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            NULL_PTR,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)2U,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            &EthTrcv_43_PHY_TransceiverLinkStateRequest,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            &EthTrcv_43_PHY_GetLinkState,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            &EthTrcv_43_PHY_GetBaudRate,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetDuplexMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            &EthTrcv_43_PHY_GetPhySignalQuality,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            &EthTrcv_43_PHY_GetPhyIdentifier,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTestMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyLoopbackMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTxMode,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            &EthTrcv_43_PHY_RunCableDiagnostic,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            &EthTrcv_43_PHY_GetCableDiagnosticsResult,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)3U,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            &EthTrcv_43_PHY_TransceiverLinkStateRequest,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            &EthTrcv_43_PHY_GetLinkState,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            &EthTrcv_43_PHY_GetBaudRate,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetDuplexMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            &EthTrcv_43_PHY_GetPhySignalQuality,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            &EthTrcv_43_PHY_GetPhyIdentifier,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTestMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyLoopbackMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTxMode,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            &EthTrcv_43_PHY_RunCableDiagnostic,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            &EthTrcv_43_PHY_GetCableDiagnosticsResult,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)4U,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetTransceiverMode,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            &EthTrcv_43_PHY_TransceiverLinkStateRequest,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            &EthTrcv_43_PHY_GetLinkState,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            &EthTrcv_43_PHY_GetBaudRate,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_GetDuplexMode,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            &EthTrcv_43_PHY_GetPhySignalQuality,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            &EthTrcv_43_PHY_GetPhyIdentifier,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTestMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyLoopbackMode,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            &EthTrcv_43_PHY_SetPhyTxMode,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            &EthTrcv_43_PHY_RunCableDiagnostic,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            &EthTrcv_43_PHY_GetCableDiagnosticsResult,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    },
    {
        /* Time stamp support */
        (boolean)TRUE,
        /* Port Transceiver Reference */
        (uint8)ETHSWT_43_SJA11XX_INVALID_TRCV_INDEX,

        {
#if (ETHSWT_43_SJA11XX_SET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_SWITCH_PORT_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_START_SWITCH_PORT_AUTO_NEGOTIATION_API == STD_ON)
            NULL_PTR,
#endif
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_LINK_STATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_BAUD_RATE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_DUPLEX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_SIGNAL_QUALITY_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_GET_PORT_IDENTIFIER_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TEST_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_LOOPBACK_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_SET_PORT_TX_MODE_API == STD_ON)
            NULL_PTR,
#endif
#if (ETHSWT_43_SJA11XX_ENABLE_CABLE_DIAGNOSTIC_API == STD_ON)
            NULL_PTR,
#if (ETHSWT_43_SJA11XX_GET_PORT_CABLE_DIAGNOSTICS_RESULT_API == STD_ON)
            NULL_PTR,
#endif
#endif
        },
#if ((ETHSWT_43_SJA11XX_WRITE_TRCV_REGISTER_API == STD_ON) || (ETHSWT_43_SJA11XX_READ_TRCV_REGISTER_API == STD_ON))
        255U,
        255U,
        {
            &Eth_ReadMii,
            &Eth_WriteMii
        },
#endif
        {
            (uint8)0U,
            (uint8)1U,
            (uint8)0U,
            (uint8)1U,
            (uint8)0U
        }
    }

};


/**
* @brief        Definition of Ethernet switch structures.
* @details      Configures the switches.
*               Configuration set by calling EthSwt_SwitchInit() API.
*/
static const EthSwt_43_SJA11XX_SwitchConfigType EthSwt_SwitchConfigs[1] =
{
    {
        /* Switch Management Ethernet Controller Reference */
        (uint8)0U,
        (uint8)ETHSWT_43_SJA11XX_INVALID_PORT_INDEX,
#if (ETHSWT_43_SJA11XX_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthSwt_DemConfig0,
#endif
#if (ETHSWT_43_SJA11XX_NVM_API == STD_OFF)
        /* NVM configuration */
        (uint8)0U,
#endif
        (uint8)ETHSWT_43_SJA11XX_INVALID_PORT_INDEX,
        &EthSwt_PortConfigOfSwt0,
    }

};

/**
* @brief          Initialization data for the EthSwt driver.
* @details        A pointer to such a structure is provided to the EthSwt initialization routines for configuration.
*
*/
const EthSwt_43_SJA11XX_ConfigType EthSwt_43_SJA11XX_PBCfgVariantPredefined =
{
    /* Pointer to the switch configuration array. */
    &EthSwt_SwitchConfigs,
    &switchDriverConfig,
    switchState
};

#define ETHSWT_43_SJA11XX_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
