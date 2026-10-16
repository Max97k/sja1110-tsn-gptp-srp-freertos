/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : ENET
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : SJA11XX_RTD_1_0_1_P02_HF01_D2510_ASR_REL_4_4_REV_0000_20251021
*
*   Copyright 2021-2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be  used strictly in accordance with the applicable license terms.  By expressly  accepting such terms or by downloading, installing, activating and/or otherwise  using the software, you are agreeing that you have read, and that you agree to  comply with and are bound by, such license terms.  If you do not agree to be  bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
==================================================================================================*/

#ifndef ENET_IP_BOARD_INITPERIPHERALS_PBCFG_H
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_H

/**
*   @file
*
*   @addtogroup ENET_DRIVER_CONFIGURATION ENET Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID                     43
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION      4
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION      4
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION   0
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION              1
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION              0
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION              1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
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
#define ENET_CONFIG_BOARD_INITPERIPHERALS_PB \
    extern const Enet_CtrlConfigType Enet_aCtrlConfigPB_BOARD_INITPERIPHERALS[];

/*! @brief Device instance number */
#ifndef INST_ENET_0
    #define INST_ENET_0        (0U)
#elif (INST_ENET_0 != 0)
    #error "[TPS_ECUC_06074] Invalid configuration due to symbolic name values"
#endif

/* Used for allocation of TX buffers */
#ifndef ENET_0_TXRING_0_DESCR
    #define ENET_0_TXRING_0_DESCR
#endif
#ifndef ENET_0_TXRING_0_DATA
    #define ENET_0_TXRING_0_DATA
#endif

/* Used for allocation of RX buffers */
#ifndef ENET_0_RXRING_0_DESCR
    #define ENET_0_RXRING_0_DESCR
#endif
#ifndef ENET_0_RXRING_0_DATA
    #define ENET_0_RXRING_0_DATA
#endif


/* Maximum number of configured buffers for a Tx Ring */
#ifndef ENET_0_MAX_TXBUFF_SUPPORTED
    #define ENET_0_MAX_TXBUFF_SUPPORTED    (1U)
#elif (ENET_0_MAX_TXBUFF_SUPPORTED < 1)
    #undef ENET_0_MAX_TXBUFF_SUPPORTED
    #define ENET_0_MAX_TXBUFF_SUPPORTED    (1U) 
#endif

/* Maximum number of configured buffers for an Rx Ring */
#ifndef ENET_0_MAX_RXBUFF_SUPPORTED
    #define ENET_0_MAX_RXBUFF_SUPPORTED    (1U)
#elif (ENET_0_MAX_RXBUFF_SUPPORTED < 1)
    #undef ENET_0_MAX_RXBUFF_SUPPORTED
    #define ENET_0_MAX_RXBUFF_SUPPORTED    (1U) 
#endif

/* Maximum length of a single buffer across all Tx Rings */
#ifndef ENET_0_MAX_TXBUFFLEN_SUPPORTED
    #define ENET_0_MAX_TXBUFFLEN_SUPPORTED    (1536U)
#elif (ENET_0_MAX_TXBUFFLEN_SUPPORTED < 1536)
    #undef ENET_0_MAX_TXBUFFLEN_SUPPORTED
    #define ENET_0_MAX_TXBUFFLEN_SUPPORTED    (1536U) 
#endif

/* Maximum length of a single buffer across all Rx Rings */
#ifndef ENET_0_MAX_RXBUFFLEN_SUPPORTED
    #define ENET_0_MAX_RXBUFFLEN_SUPPORTED    (1536U)
#elif (ENET_0_MAX_RXBUFFLEN_SUPPORTED < 1536)
    #undef ENET_0_MAX_RXBUFFLEN_SUPPORTED
    #define ENET_0_MAX_RXBUFFLEN_SUPPORTED    (1536U) 
#endif

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

#endif /* ENET_IP_BOARD_INITPERIPHERALS_PBCFG_H */

