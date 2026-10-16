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

#ifndef INTCTRL_IP_CFG_DEFINES_H_
#define INTCTRL_IP_CFG_DEFINES_H_

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "StandardTypes.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MAJOR_VERSION                   1
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_PATCH_VERSION                   1
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


    #include "SJA1110.h"
    
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Development error detection */
    #define INT_CTRL_MCAL_ARM_MARCH_SMU      STD_OFF
    #define INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER  (STD_OFF)
#define INT_CTRL_IP_DEV_ERROR_DETECT              (STD_ON)
/* IP standalone APIs  */
#define INT_CTRL_IP_STANDALONE_APIS               (STD_OFF)


/* VTOR address configuration enable */
#define INT_CTRL_IP_ENABLE_VTOR_CONFIG             (STD_OFF)

/* Number of nvic priority bits implemented */
#define INT_CTRL_IP_NVIC_PRIO_BITS                (3U)
/* User mode support */
#define INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT (STD_OFF)

/*Interrupt Router Shared Peripheral Routing Control Register*/
#define INT_CTRL_IP_ROUTING_CONTROL_REGISTER      (STD_OFF)
/* This instruction invalidates the entire instruction cache or caches */
#define INT_CTRL_IP_INVALIDATE_CACHE              (STD_OFF)

/* First implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MIN                       (ETHSW_TTESWITCH0_IRQn)
/* Last implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MAX                       (CREG_Infra_ERR_IRQn)
/* The interrupt counter value*/
#define INT_CTRL_IP_IRQ_COUNT                     (75)
/* Arm Cortex R */
#define INT_CTRL_IP_CORTEXR                       (STD_OFF)
/* Arm Cortex M */
#define INT_CTRL_IP_CORTEXM                       (STD_ON)
#define INT_CTRL_IP_CORTEXM0PLUS                  (STD_OFF)
/* Arm Cortex A */
#define INT_CTRL_IP_CORTEXA                       (STD_OFF)

#endif /* INTCTRL_IP_CFG_DEFINES_H_ */

