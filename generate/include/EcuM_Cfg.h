/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : 
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



#ifndef ECUM_CFG_H
#define ECUM_CFG_H

/**
*   @file
*
*   @addtogroup ECUM_MODULE EcuM Module
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_CFG_VENDOR_ID                      43
#define ECUM_CFG_MODULE_ID                      10
#define ECUM_CFG_AR_RELEASE_MAJOR_VERSION       4
#define ECUM_CFG_AR_RELEASE_MINOR_VERSION       4
#define ECUM_CFG_AR_RELEASE_REVISION_VERSION    0
#define ECUM_CFG_SW_MAJOR_VERSION               1
#define ECUM_CFG_SW_MINOR_VERSION               0
#define ECUM_CFG_SW_PATCH_VERSION               1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
 *                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/* ========= user defined wakeup sources ========= */
#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource_0) /* to prevent double declaration */
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource_0 already defined
#endif
/** @brief Identifier for wakeup source EcuMWakeupSource_0*/
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource_0    ((uint32)((uint32)1U<<0))
#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource_1) /* to prevent double declaration */
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource_1 already defined
#endif
/** @brief Identifier for wakeup source EcuMWakeupSource_1*/
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource_1    ((uint32)((uint32)1U<<1))
#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource_2) /* to prevent double declaration */
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource_2 already defined
#endif
/** @brief Identifier for wakeup source EcuMWakeupSource_2*/
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource_2    ((uint32)((uint32)1U<<2))
#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource_3) /* to prevent double declaration */
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource_3 already defined
#endif
/** @brief Identifier for wakeup source EcuMWakeupSource_3*/
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource_3    ((uint32)((uint32)1U<<3))
#if (defined EcuMConf_EcuMWakeupSource_EcuMWakeupSource_4) /* to prevent double declaration */
#error EcuMConf_EcuMWakeupSource_EcuMWakeupSource_4 already defined
#endif
/** @brief Identifier for wakeup source EcuMWakeupSource_4*/
#define EcuMConf_EcuMWakeupSource_EcuMWakeupSource_4    ((uint32)((uint32)1U<<4))

/* ======== Sleep modes ======== */
#if (defined EcuMConf_EcuMSleepMode_EcuMSleepMode_0) /* to prevent double declaration */
#error EcuMConf_EcuMSleepMode_EcuMSleepMode_0 already defined
#endif
/** @brief Identifier for wakeup source EcuMSleepMode_0*/
#define EcuMConf_EcuMSleepMode_EcuMSleepMode_0  0x0U
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef uint32 EcuM_WakeupSourceType; /**< @brief variable type for ECU Manager wakeup sources*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ECUM_CFG_H */


