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

#ifndef SMPU_IP_CFG_H
#define SMPU_IP_CFG_H

/**
*   @file Smpu_Ip_Cfg.h
*
*   @addtogroup Smpu_Ip Smpu IPV Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Smpu_Ip_Types.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_SMPU_IP_CFG_VENDOR_ID                    43
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MAJOR_VERSION     4
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MINOR_VERSION     4
#define CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_REVISION_VERSION  0
#define CDD_PLATFORM_SMPU_IP_CFG_SW_MAJOR_VERSION             1
#define CDD_PLATFORM_SMPU_IP_CFG_SW_MINOR_VERSION             0
#define CDD_PLATFORM_SMPU_IP_CFG_SW_PATCH_VERSION             1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Smpu_Ip_Types.h */
#if (CDD_PLATFORM_SMPU_IP_CFG_VENDOR_ID != CDD_PLATFORM_SMPU_IP_TYPES_VENDOR_ID)
    #error "Smpu_Ip_Cfg.h and Smpu_Ip_Types.h have different vendor ids"
#endif
#if (( CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_SMPU_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     ( CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_SMPU_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     ( CDD_PLATFORM_SMPU_IP_CFG_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_SMPU_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Smpu_Ip_Cfg.h and Smpu_Ip_Types.h are different"
#endif
#if (( CDD_PLATFORM_SMPU_IP_CFG_SW_MAJOR_VERSION != CDD_PLATFORM_SMPU_IP_TYPES_SW_MAJOR_VERSION) || \
     ( CDD_PLATFORM_SMPU_IP_CFG_SW_MINOR_VERSION != CDD_PLATFORM_SMPU_IP_TYPES_SW_MINOR_VERSION) || \
     ( CDD_PLATFORM_SMPU_IP_CFG_SW_PATCH_VERSION != CDD_PLATFORM_SMPU_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Smpu_Ip_Cfg.h and Smpu_Ip_Types.h are different"
#endif


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define PLATFORM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Platform_MemMap.h"

/**
* @brief   Collection of all configuration structures declarations.
*/
extern const Smpu_Ip_ConfigType Smpu_Config;
#define PLATFORM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Platform_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SMPU_IP_CFG_H */

