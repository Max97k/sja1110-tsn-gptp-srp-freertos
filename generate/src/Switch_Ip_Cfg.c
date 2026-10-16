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

/*
*   @file Switch_Ip_Cfg.c
*
*   @addtogroup switch_driver_configuration SWITCH Driver Configuration
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
#include "Switch_Ip_Types.h"
#include "Switch_Ip_Cfg.h"
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWITCH_IP_CFG_VENDOR_ID_C                     43
#define SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION_C      4
#define SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION_C      4
#define SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION_C   0
#define SWITCH_IP_CFG_SW_MAJOR_VERSION_C              1
#define SWITCH_IP_CFG_SW_MINOR_VERSION_C              0
#define SWITCH_IP_CFG_SW_PATCH_VERSION_C              2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Switch_Ip_Types.h */
#if (SWITCH_IP_CFG_VENDOR_ID_C != SWITCH_IP_TYPES_VENDOR_ID)
    #error "Switch_Ip_Cfg.c and Switch_Ip_Types.h have different vendor ids"
#endif
#if ((SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and Switch_Ip_Types.h are different"
#endif
#if ((SWITCH_IP_CFG_SW_MAJOR_VERSION_C != SWITCH_IP_TYPES_SW_MAJOR_VERSION) || \
     (SWITCH_IP_CFG_SW_MINOR_VERSION_C != SWITCH_IP_TYPES_SW_MINOR_VERSION) || \
     (SWITCH_IP_CFG_SW_PATCH_VERSION_C != SWITCH_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_Cfg.c and Switch_Ip_Types.h are different"
#endif

/* Checks against Switch_Ip_Cfg.h */
#if (SWITCH_IP_CFG_VENDOR_ID_C != SWITCH_IP_CFG_VENDOR_ID)
    #error "Switch_Ip_Cfg.c and Switch_Ip_Cfg.h have different vendor ids"
#endif
#if ((SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and Switch_Ip_Cfg.h are different"
#endif
#if ((SWITCH_IP_CFG_SW_MAJOR_VERSION_C != SWITCH_IP_CFG_SW_MAJOR_VERSION) || \
     (SWITCH_IP_CFG_SW_MINOR_VERSION_C != SWITCH_IP_CFG_SW_MINOR_VERSION) || \
     (SWITCH_IP_CFG_SW_PATCH_VERSION_C != SWITCH_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_Cfg.c and Switch_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
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
