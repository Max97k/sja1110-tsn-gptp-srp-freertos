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

#ifndef ETH_IPW_CFG_H
#define ETH_IPW_CFG_H

/**
*   @file
*
*   @addtogroup ETH_DRIVER_CONFIGURATION Ethernet Driver Configurations
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
#include "Eth_Ipw_BOARD_InitPeripherals_PBcfg.h"

#include "Eth_Cfg.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_IPW_CFG_VENDOR_ID                    43
#define ETH_IPW_CFG_AR_RELEASE_MAJOR_VERSION     4
#define ETH_IPW_CFG_AR_RELEASE_MINOR_VERSION     4
#define ETH_IPW_CFG_AR_RELEASE_REVISION_VERSION  0
#define ETH_IPW_CFG_SW_MAJOR_VERSION             1
#define ETH_IPW_CFG_SW_MINOR_VERSION             0
#define ETH_IPW_CFG_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_Ipw_BOARD_InitPeripherals_PBcfg.h */
#if (ETH_IPW_CFG_VENDOR_ID != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID)
    #error "Eth_Ipw_Cfg.h and Eth_Ipw_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
#if ((ETH_IPW_CFG_AR_RELEASE_MAJOR_VERSION    != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_IPW_CFG_AR_RELEASE_MINOR_VERSION    != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION) || \
     (ETH_IPW_CFG_AR_RELEASE_REVISION_VERSION != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Eth_Ipw_Cfg.h and Eth_Ipw_BOARD_InitPeripherals_PBcfg.h are different"
#endif
#if ((ETH_IPW_CFG_SW_MAJOR_VERSION != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION) || \
     (ETH_IPW_CFG_SW_MINOR_VERSION != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION) || \
     (ETH_IPW_CFG_SW_PATCH_VERSION != ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Eth_Ipw_Cfg.h and Eth_Ipw_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/* Checks against Eth_Cfg.h */
#if (ETH_IPW_CFG_VENDOR_ID != ETH_CFG_VENDOR_ID)
    #error "Eth_Ipw_Cfg.h and Eth_Cfg.h have different vendor ids"
#endif
#if ((ETH_IPW_CFG_AR_RELEASE_MAJOR_VERSION    != ETH_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_IPW_CFG_AR_RELEASE_MINOR_VERSION    != ETH_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_IPW_CFG_AR_RELEASE_REVISION_VERSION != ETH_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_Ipw_Cfg.h and Eth_Cfg.h are different"
#endif
#if ((ETH_IPW_CFG_SW_MAJOR_VERSION != ETH_CFG_SW_MAJOR_VERSION) || \
     (ETH_IPW_CFG_SW_MINOR_VERSION != ETH_CFG_SW_MINOR_VERSION) || \
     (ETH_IPW_CFG_SW_PATCH_VERSION != ETH_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_Ipw_Cfg.h and Eth_Cfg.h are different"
#endif
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ETH_IPW_CONFIG_EXT \
    ETH_IPW_CONFIG_BOARD_INITPERIPHERALS_PB \

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#if (STD_ON == ETH_DEM_EVENT_DETECT)
/**
 * @brief    Type for holding DEM events
 * @details  It contains the necessary events to report to the DEM module
 */
typedef struct
{
    Mcal_DemErrorType ETH_IPW_ETH_E_ERR_Cfg;

} Eth_Ipw_DemEventsType;
#endif

/* Forward IPW structure declarations */
struct sEnet_CtrlConfigType;

/**
* @brief   The structure contains the hardware controller configuration type.
*/
typedef struct sEth_Ipw_CtrlConfigType
{
    const struct sEnet_CtrlConfigType *Eth_Ipw_pEnetCtrlConfig;
#if (STD_ON == ETH_DEM_EVENT_DETECT)
    const Eth_Ipw_DemEventsType Eth_Ipw_DemEventsList;
#endif
#if (STD_ON == ETH_GLOBAL_TIME_API)
    uint32 CorectionCounter;
#endif
} Eth_Ipw_CtrlConfigType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETH_IPW_CFG_H */

