/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : SJA11XX
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

#ifndef ACU_IP_BOARD_INITPERIPHERALS_PBCFG_H
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_H

/*
*   @file
*
*   @addtogroup switch_driver_configuration PORT Driver Configuration
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
#include "Acu_Ip_Types.h"
#include "StandardTypes.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID                     43
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION      4
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION      4
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION   0
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION              1
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION              0
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Acu_Ip_Types.h */
#if (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID != ACU_IP_TYPES_VENDOR_ID)
    #error "Acu_Ip_BOARD_InitPeripherals_PBcfg.h and Acu_Ip_Types.h have different vendor ids"
#endif
#if (( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION    != ACU_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     ( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION    != ACU_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     ( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION != ACU_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Acu_Ip_BOARD_InitPeripherals_PBcfg.h and Acu_Ip_Types.h are different"
#endif
#if (( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION != ACU_IP_TYPES_SW_MAJOR_VERSION) || \
     ( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION != ACU_IP_TYPES_SW_MINOR_VERSION) || \
     ( ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION != ACU_IP_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Acu_Ip_BOARD_InitPeripherals_PBcfg.h and Acu_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against StandardTypes.h */
    #if ((ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Acu_Ip_BOARD_InitPeripherals_PBcfg.h and StandardTypes.h are different"
    #endif
#endif

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
extern const Acu_Ip_SettingConfigType Acu_Ip_PinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals;

extern const Acu_Ip_UnusedPortSettingType Acu_Ip_UnusedPinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals;

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

#endif /* ACU_IP_BOARD_INITPERIPHERALS_PBCFG_H */


