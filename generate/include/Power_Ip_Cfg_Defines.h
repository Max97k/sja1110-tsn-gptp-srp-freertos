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

#ifndef POWER_IP_CFG_DEFINES_H
#define POWER_IP_CFG_DEFINES_H

/**
*   @file       Power_Ip_Cfg_Defines.h
*   @version    1.0.1
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup POWER_DRIVER_CONFIGURATION Power Ip Driver
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
#include "StandardTypes.h"
#include "SJA1110.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_CFG_DEFINES_VENDOR_ID                       43
#define POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        4
#define POWER_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_CFG_DEFINES_SW_MAJOR_VERSION                1
#define POWER_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define POWER_IP_CFG_DEFINES_SW_PATCH_VERSION                1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Power_Ip_Cfg_Defines.h file and StandardTypes.h file are of the same Autosar version */
#if ((POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION    != STD_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION    != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_Cfg_Defines.h and StandardTypes.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/

/**
* @brief            If this parameter is set to TRUE, all Reset Generation Unit (RGU) registers are disabled accessing.
*/
#define POWER_IP_DISABLE_RGU_ACCESS                   (STD_OFF)

/**
* @brief            If this parameter is set to TRUE, the Power Management Controller (PMU) initialization has to be disabled from the MCU driver.
*/
#define POWER_IP_DISABLE_PMU_INIT                   (STD_OFF)

/**
* @brief            Support for Low Power mode.
*/
#define POWER_IP_ENTER_LOW_POWER_MODE                    (STD_OFF)

/**
* @brief
*/
#define POWER_IP_PERFORM_RESET_API                       (STD_OFF)

/**
* @brief            ISR Mcu_PMU_UnderOverVoltage_ISR is/is not available (STD_ON/STD_OFF)
*/
#define POWER_IP_VOLTAGE_ERROR_ISR_USED                  (STD_OFF)

/**
* @brief            Create defines with the values assigned to Mcu Reset Reason configurations.
*                   These values can be  retrieved from Mcu_GetResetReason Api.
*/

#define McuConf_McuResetReasonConf_MCU_COLD_INP_EXTERNAL_RESET   ((uint8)4U)

#define McuConf_McuResetReasonConf_MCU_COLD_INP_SW_RESET   ((uint8)6U)

#define McuConf_McuResetReasonConf_MCU_COLD_INP_WATCHDOG_RESET   ((uint8)5U)

#define McuConf_McuResetReasonConf_MCU_HW_INP_EXTERNAL_RESET   ((uint8)1U)

#define McuConf_McuResetReasonConf_MCU_HW_INP_SW_RESET   ((uint8)3U)

#define McuConf_McuResetReasonConf_MCU_HW_INP_WATCHDOG_RESET   ((uint8)2U)

#define McuConf_McuResetReasonConf_MCU_MULTIPLE_RESET_REASON   ((uint8)11U)

#define McuConf_McuResetReasonConf_MCU_NO_RESET_REASON   ((uint8)10U)

#define McuConf_McuResetReasonConf_MCU_POWER_ON_RESET   ((uint8)0U)

#define McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED   ((uint8)12U)

#define McuConf_McuResetReasonConf_MCU_WARM_EXTERNAL_RESET   ((uint8)7U)

#define McuConf_McuResetReasonConf_MCU_WARM_SW_RESET   ((uint8)9U)

#define McuConf_McuResetReasonConf_MCU_WARM_WATCHDOG_RESET   ((uint8)8U)

/**
* @brief           This define controls the availability of function Mcu_SleepOnExit
*/
#define POWER_IP_SLEEPONEXIT_SUPPORT    (STD_ON)

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef POWER_IP_CFG_DEFINES_H */


