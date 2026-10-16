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

#ifndef SWITCH_IP_CFG_H
#define SWITCH_IP_CFG_H

/*
*   @file Switch_Ip_Cfg.h
*
*   @addtogroup switch_driver_configuration SWITCH Driver Configuration
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
#include "Switch_Ip_Types.h"
#include "StandardTypes.h"
#include "Reg_eSys.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWITCH_IP_CFG_VENDOR_ID                     43
#define SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION      4
#define SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION      4
#define SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION   0
#define SWITCH_IP_CFG_SW_MAJOR_VERSION              1
#define SWITCH_IP_CFG_SW_MINOR_VERSION              0
#define SWITCH_IP_CFG_SW_PATCH_VERSION              2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Switch_Ip_Types.h */
#if (SWITCH_IP_CFG_VENDOR_ID != SWITCH_IP_TYPES_VENDOR_ID)
    #error "Switch_Ip_Cfg.h and Switch_Ip_Types.h have different vendor ids"
#endif
#if (( SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION    != SWITCH_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     ( SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION    != SWITCH_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     ( SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION != SWITCH_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and Switch_Ip_Types.h are different"
#endif
#if (( SWITCH_IP_CFG_SW_MAJOR_VERSION != SWITCH_IP_TYPES_SW_MAJOR_VERSION) || \
     ( SWITCH_IP_CFG_SW_MINOR_VERSION != SWITCH_IP_TYPES_SW_MINOR_VERSION) || \
     ( SWITCH_IP_CFG_SW_PATCH_VERSION != SWITCH_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Switch_Ip_Cfg.h and Switch_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against StandardTypes.h */
    #if ((SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and StandardTypes.h are different"
    #endif
    /* Checks against Reg_eSys.h */
    #if ((SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Switch_Ip_Cfg.h and Reg_eSys.h are different"
    #endif
#endif

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#define SWITCH_IP_DEV_ERROR_DETECT     (STD_OFF)

#define SWITCH_TIMEOUT_LOOPS        ((uint32)65535U)

#define SJA1110_REV_C


#define SWITCH_USE_INTERNAL_RW
#define SWITCH_IP_USE_EXTERNAL_RW    (STD_OFF)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ETHSWT_43_SJA11XX_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "EthSwt_43_SJA11XX_MemMap.h"
/**
* @brief    Structure containing binary static configuration for switch 0.
*/
extern Switch_Ip_BinaryConfigType switchConfig0;

/**
* @brief    Pre-Compile structure from Switch_Ip_Cfg.c file.
*/
        extern const Switch_Ip_ConfigType switchConfig[1U];
        extern const Switch_Ip_DriverConfigType switchDriverConfig;
        extern Switch_Ip_StateType switchState[1U];

#define ETHSWT_43_SJA11XX_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#include "EthSwt_43_SJA11XX_MemMap.h"

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

#endif /* SWITCH_IP_CFG_H */
