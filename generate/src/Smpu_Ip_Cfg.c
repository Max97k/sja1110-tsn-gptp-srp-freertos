/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
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
*   @file Smpu_Ip_cfg.c
*
*   @addtogroup Smpu_Ip Smpu IPV Driver
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
#include "Smpu_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_SMPU_IP_CFG_VENDOR_ID_C                     43
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MAJOR_VERSION_C      4
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MINOR_VERSION_C      4
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_REVISION_VERSION_C   0
#define CDD_PLATFORM_SMPU_IP_CFG_SW_MAJOR_VERSION_C              1
#define CDD_PLATFORM_SMPU_IP_CFG_SW_MINOR_VERSION_C              0
#define CDD_PLATFORM_SMPU_IP_CFG_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Smpu_Ip_Cfg.h */
#if (CDD_PLATFORM_SMPU_IP_CFG_VENDOR_ID_C != CDD_PLATFORM_SMPU_IP_CFG_VENDOR_ID)
    #error "Smpu_Ip_Cfg.c and Smpu_Ip_Cfg.h have different vendor ids"
#endif
#if ((CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_REVISION_VERSION_C != CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Smpu_Ip_Cfg.h and Smpu_Ip_Cfg.h are different"
#endif
#if ((CDD_PLATFORM_SMPU_IP_CFG_SW_MAJOR_VERSION_C != CDD_PLATFORM_SMPU_IP_CFG_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_SMPU_IP_CFG_SW_MINOR_VERSION_C != CDD_PLATFORM_SMPU_IP_CFG_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_SMPU_IP_CFG_SW_PATCH_VERSION_C != CDD_PLATFORM_SMPU_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Smpu_Ip_Cfg.c and Smpu_Ip_Cfg.h are different"
#endif

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
#define PLATFORM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Platform_MemMap.h"

/**
 * @brief       Configure Access Rights for Master in Region 0, Instance 0
 */
const Smpu_Ip_MasterAccessType SmpuInstance0_MasterAccessConfig_Region0[SMPU_IP_INSTANCE0_MASTER_COUNT] =
{
    /* CORE Access Right */
    {
        SMPU_MASTER_CORE,
        SMPU_FULL_ACCESS
    },
    /* DEBUG Access Right */
    {
        SMPU_MASTER_DEBUG,
        SMPU_FULL_ACCESS
    },
    /* DMA Access Right   */
    {
        SMPU_MASTER_DMA,
        SMPU_FULL_ACCESS
    },
    /* ENET Access Right  */
    {
        SMPU_MASTER_ENET,
        SMPU_FULL_ACCESS
    },
    /* CAAM Access Right  */
    {
        SMPU_MASTER_CAAM,
        SMPU_FULL_ACCESS
    }
};

/**
 * @brief       Smpu Regions Configuration for Instance 0
 */
const Smpu_Ip_RegionConfigType SmpuInstance0_AllRegionsConfig[1U] =
{
    /* Region Configuration 0 */
    {
        /* u8RegionNumber       */ 0U,
        /* u32StartAddr         */ 0U,
        /* u32EndAddr           */ 4294967295U,
        /* masterAccess         */ SmpuInstance0_MasterAccessConfig_Region0,
        /* bCacheInhibitEnable  */ FALSE,
        /* lockConfig           */ SMPU_REGION_UNLOCK
    }
};

/**
 * @brief       Smpu Configuration for Instance 0
 */
const Smpu_Ip_InstanceConfigType SmpuInstance0_Config =
{
    /* u32Instance      */ SMPU_INSTANCE0,
    /* u8RegionCnt      */ 1U,
    /* pRegionConfigArr */ SmpuInstance0_AllRegionsConfig
};


/**
 * @brief       Smpu Instances Configuration Array
 */
const Smpu_Ip_InstanceConfigType *const SmpuInstanceConfigArr[1U] =
{
    &SmpuInstance0_Config
};

/**
 * @brief       Smpu Configure Initialization
 */
const Smpu_Ip_ConfigType Smpu_Config =
{
    /* u8InstanceCnt      */ 1U,
    /* pInstanceConfigArr */ SmpuInstanceConfigArr
};

#define PLATFORM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Platform_MemMap.h"

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

