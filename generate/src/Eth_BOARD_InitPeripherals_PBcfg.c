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
*   @implements Eth_PBcfg.c_Artifact
*   @addtogroup Eth_DRIVER_CONFIGURATION Ethernet Driver Configuration
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
#include "Eth_Cfg.h"
#include "Eth_Ipw_Cfg.h"

#if STD_ON == ETH_DEM_EVENT_DETECT
    #include "Dem.h"
#endif

#if (STD_ON == ETH_MDIO_CLAUSE22_API) || (STD_ON == ETH_MDIO_CLAUSE45_API)
    #include "EthTrcv_43_PHY.h"
#endif

#if STD_ON == ETH_SWT_MANAGEMENT_SUPPORT_API
    #include "EthSwt_43_SJA11XX.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                     43
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C      4
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C      4
#define ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C   0
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C              1
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C              0
#define ETH_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_Cfg.h */
#if (ETH_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ETH_CFG_VENDOR_ID)
    #error "Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Cfg.h have different vendor ids"
#endif
#if ((ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ETH_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ETH_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ETH_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Cfg.h are different"
#endif
#if ((ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ETH_CFG_SW_MAJOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ETH_CFG_SW_MINOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ETH_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Cfg.h are different"
#endif

/* Checks against Eth_Ipw_Cfg.h */
#if (ETH_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ETH_IPW_CFG_VENDOR_ID)
    #error "Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h have different vendor ids"
#endif
#if ((ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ETH_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ETH_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ETH_IPW_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h are different"
#endif
#if ((ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ETH_IPW_CFG_SW_MAJOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ETH_IPW_CFG_SW_MINOR_VERSION) || \
     (ETH_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ETH_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and Eth_Ipw_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if STD_ON == ETH_DEM_EVENT_DETECT
    /* Checks against Dem.h */
    #if ((ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and Dem.h are different"
    #endif
  #endif

  #if (STD_ON == ETH_MDIO_CLAUSE22_API) || (STD_ON == ETH_MDIO_CLAUSE45_API)
    /* Checks against EthTrcv_43_PHY.h */
    #if ((ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and EthTrcv_43_PHY.h are different"
    #endif
  #endif

  #if STD_ON == ETH_SWT_MANAGEMENT_SUPPORT_API
    /* Checks against EthSwt_43_SJA11XX.h */
    #if ((ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Eth_BOARD_INITPERIPHERALS_PBcfg.c and EthSwt_43_SJA11XX.h are different"
    #endif
  #endif
#endif

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/**
* @brief   Export IPW configurations.
*/
ETH_IPW_CONFIG_EXT

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

static const Eth_EgressCfgType Eth_aEgressConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Eth_aEgressConfigPB_[0U] - IP_0 */
    {
        1U,  /* Total number of buffers across all Tx FIFOs */
        1U, /* Total number of configured Tx FIFOs */
        { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U } /* Map between VLAN PCPs and Tx FIFOs */
    }
};

static const Eth_IngressCfgType Eth_aIngressConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Eth_aIngressConfigPB_[0U] - IP_0 */
    {
        1U,  /* Total number of buffers across all Rx FIFOs */
        1U /* Total number of configured Rx FIFOs */
    }
};

static const Eth_ClockCfgType Eth_aClockConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Eth_aClockConfigPB_[0U] - IP_0 */
    {
        200000000U, /* Frequency of the application interface (in Hz) */
        0U, /* Number of picoseconds in a PTP clock period */
        0U /* Number of nanoseconds in a PTP clock period for the required accuracy */
    }
};

static const Eth_CtrlCfgType Eth_aCtrlConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Eth_aCtrlConfigPB[0U] - IP_0 */
    {
        &Eth_Ipw_aCtrlConfigPB_BOARD_INITPERIPHERALS[0U],
        &Eth_aEgressConfigPB_BOARD_INITPERIPHERALS[0U],
        &Eth_aIngressConfigPB_BOARD_INITPERIPHERALS[0U],
        &Eth_aClockConfigPB_BOARD_INITPERIPHERALS[0U],
        (uint8)0U
#if (STD_ON == ETH_DEM_EVENT_DETECT)
       ,{
            { (uint32)STD_ON, DemConf_DemEventParameter_ETH_E_ACCESS },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 },
            { (uint32)STD_OFF, 0 }
        }
#endif
#if (STD_ON == ETH_MDIO_CLAUSE22_API) || (STD_ON == ETH_MDIO_CLAUSE45_API)
       ,{
            &EthTrcv_43_PHY_ReadMiiIndication,
            &EthTrcv_43_PHY_WriteMiiIndication
        }
#endif
#if STD_ON == ETH_SWT_MANAGEMENT_SUPPORT_API
       ,{
            &EthSwt_43_SJA11XX_EthTxAdaptBufferLength,
            &EthSwt_43_SJA11XX_EthTxPrepareFrame,
            &EthSwt_43_SJA11XX_EthTxProcessFrame,
            &EthSwt_43_SJA11XX_EthTxFinishedIndication,
            &EthSwt_43_SJA11XX_EthRxProcessFrame,
            &EthSwt_43_SJA11XX_EthRxFinishedIndication
        }
#endif
    }
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

const Eth_ConfigType Eth_xPredefinedConfig =
{
    {
        &Eth_aCtrlConfigPB_BOARD_INITPERIPHERALS[0U]  /* IP_0 */
    }
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

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
