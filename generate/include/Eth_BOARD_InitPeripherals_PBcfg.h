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

#ifndef ETH_PBCFG_BOARD_INITPERIPHERALS_H
#define ETH_PBCFG_BOARD_INITPERIPHERALS_H

/**
*   @file
*
*   @addtogroup ETH_DRIVER_CONFIGURATION Ethernet Driver Configuration
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
#define ETH_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID                     43
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION      4
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION      4
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION   0
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION              1
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION              0
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION              1

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
*                                      DEFINES AND MACROS
==================================================================================================*/


#ifndef ETH_MDIO_CLAUSE22_API
    #define ETH_MDIO_CLAUSE22_API    (STD_ON)
#endif

#ifndef ETH_MDIO_CLAUSE45_API
    #define ETH_MDIO_CLAUSE45_API    (STD_ON)
#endif



#ifndef EthConf_EthCtrlConfig_EthCtrlConfig_0
    /*! @brief Controller symbolic name to be passed to API functions that require CtrlIdx */
    #define EthConf_EthCtrlConfig_EthCtrlConfig_0    (0U)
#elif (EthConf_EthCtrlConfig_EthCtrlConfig_0 != 0)
    #error "[TPS_ECUC_06074] Invalid configuration due to symbolic name values"
#endif

#ifndef EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0
    /*! @brief Controller symbolic name to be passed to API functions that require FifoIdx */
    #define EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0        (0U)
#elif (EthConf_EthCtrlConfigIngressFifo_EthCtrlConfigIngressFifo_0 != 0)
    #error "[TPS_ECUC_06074] Invalid configuration due to symbolic name values"
#endif

/* Maximum number of configured Tx FIFOs */
#ifndef ETH_MAX_TXFIFO_SUPPORTED
    /*! @brief Maximum number of configured Tx FIFOs */
    #define ETH_MAX_TXFIFO_SUPPORTED        (1U)
#elif (ETH_MAX_TXFIFO_SUPPORTED < 1)
    #undef ETH_MAX_TXFIFO_SUPPORTED
    #define ETH_MAX_TXFIFO_SUPPORTED        (1U) 
#endif

/* Maximum number of configured Rx FIFOs */
#ifndef ETH_MAX_RXFIFO_SUPPORTED
    #define ETH_MAX_RXFIFO_SUPPORTED        (1U)
#elif (ETH_MAX_RXFIFO_SUPPORTED < 1)
    #undef ETH_MAX_RXFIFO_SUPPORTED
    #define ETH_MAX_RXFIFO_SUPPORTED        (1U) 
#endif

/* Maximum number of configured buffers per Tx FIFO */
#ifndef ETH_MAX_TXBUFF_SUPPORTED
    #define ETH_MAX_TXBUFF_SUPPORTED        (1U)
#elif (ETH_MAX_TXBUFF_SUPPORTED < 1)
    #undef ETH_MAX_TXBUFF_SUPPORTED
    #define ETH_MAX_TXBUFF_SUPPORTED        (1U) 
#endif

/* Maximum number of configured buffers per Rx FIFO */
#ifndef ETH_MAX_RXBUFF_SUPPORTED
    #define ETH_MAX_RXBUFF_SUPPORTED        (1U)
#elif (ETH_MAX_RXBUFF_SUPPORTED < 1)
    #undef ETH_MAX_RXBUFF_SUPPORTED
    #define ETH_MAX_RXBUFF_SUPPORTED        (1U) 
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

#endif /* ETH_PBCFG_BOARD_INITPERIPHERALS_H */

