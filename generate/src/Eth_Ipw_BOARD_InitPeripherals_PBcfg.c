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
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Eth_Ipw_Cfg.h"
#include "Enet_Ip_Cfg.h"

#if (STD_ON == ETH_DEM_EVENT_DETECT)
    #include "Dem.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                     43
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C      4
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C      4
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C   0
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C              1
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C              0
#define ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_Ipw_Cfg.h */
#if (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ETH_IPW_CFG_VENDOR_ID)
    #error "Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h have different vendor ids"
#endif
#if ((ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ETH_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ETH_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ETH_IPW_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h are different"
#endif
#if ((ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ETH_IPW_CFG_SW_MAJOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ETH_IPW_CFG_SW_MINOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ETH_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h are different"
#endif

/* Checks against Enet_Ip_Cfg.h */
#if (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ENET_IP_CFG_VENDOR_ID)
    #error "Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h have different vendor ids"
#endif
#if ((ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ENET_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h are different"
#endif
#if ((ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ENET_IP_CFG_SW_MAJOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ENET_IP_CFG_SW_MINOR_VERSION) || \
     (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ENET_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if STD_ON == ETH_DEM_EVENT_DETECT
    /* Checks against Dem.h */
    #if ((ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_IPW_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Eth_Ipw_BOARD_INITPERIPHERALS_PBcfg.c and Dem.h are different"
    #endif
  #endif
#endif

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/**
* @brief   Export ENET configurations.
*/
ENET_CONFIG_EXT

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

const Eth_Ipw_CtrlConfigType Eth_Ipw_aCtrlConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Eth_Ipw_aCtrlConfig[0U] */
    {
        &Enet_aCtrlConfigPB_BOARD_INITPERIPHERALS[0U]
#if (STD_ON == ETH_DEM_EVENT_DETECT)
       ,{
            { (uint32)STD_OFF, 0 }
        }
#endif
#if STD_ON == ETH_GLOBAL_TIME_API
       ,0U
#endif
    }
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif
/** @} */

