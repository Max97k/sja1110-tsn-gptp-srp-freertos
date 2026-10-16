/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : LPit
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

#ifndef LPIT_GPT_IP_CFG_H
#define LPIT_GPT_IP_CFG_H

/**
*   @file           LPit_Gpt_Ip_Cfg.h
*
*   @addtogroup     lpit_ip LPit IPL
*
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
#include "LPit_Gpt_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPIT_GPT_IP_VENDOR_ID_CFG                       43
#define LPIT_GPT_IP_AR_RELEASE_MAJOR_VERSION_CFG        4
#define LPIT_GPT_IP_AR_RELEASE_MINOR_VERSION_CFG        4
#define LPIT_GPT_IP_AR_RELEASE_REVISION_VERSION_CFG     0
#define LPIT_GPT_IP_SW_MAJOR_VERSION_CFG                1
#define LPIT_GPT_IP_SW_MINOR_VERSION_CFG                0
#define LPIT_GPT_IP_SW_PATCH_VERSION_CFG                1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (LPIT_GPT_IP_VENDOR_ID_CFG != LPIT_GPT_IP_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_H)
    #error "LPit_Gpt_Ip_Cfg.h and LPit_Gpt_Ip_BOARD_INITPERIPHERALS_PBcfg.h have different vendor ids"
#endif
/* Check if this header file and header file are of the same Autosar version */
#if ((LPIT_GPT_IP_AR_RELEASE_MAJOR_VERSION_CFG != LPIT_GPT_IP_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (LPIT_GPT_IP_AR_RELEASE_MINOR_VERSION_CFG != LPIT_GPT_IP_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (LPIT_GPT_IP_AR_RELEASE_REVISION_VERSION_CFG != LPIT_GPT_IP_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of LPit_Gpt_Ip_Cfg.h and LPit_Gpt_Ip_BOARD_INITPERIPHERALS_PBcfg.h are different"
#endif
/* Check if this header file and header file are of the same Software version */
#if ((LPIT_GPT_IP_SW_MAJOR_VERSION_CFG != LPIT_GPT_IP_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (LPIT_GPT_IP_SW_MINOR_VERSION_CFG != LPIT_GPT_IP_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (LPIT_GPT_IP_SW_PATCH_VERSION_CFG != LPIT_GPT_IP_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) \
    )
    #error "Software Version Numbers of LPit_Gpt_Ip_Cfg.h and LPit_Gpt_Ip_BOARD_INITPERIPHERALS_PBcfg.h are different"
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Dev error detect switch
*/
#define LPIT_GPT_IP_DEV_ERROR_DETECT     (STD_OFF)
/*==================================================================================================*/
/**
* @brief    LPIT_GPT_IP_CHAIN_MODE switch
* @details  Enable/disable API for Chain Mode.
*/
#define LPIT_GPT_IP_CHAIN_MODE     (STD_OFF)

/*================================================================================================*/
/**
* @brief    LPIT_GPT_IP_ENABLE_USER_MODE_SUPPORT switch
* @details  Enable/disable support usermode.If this parameter has been configured to TRUE the GPT driver code can be executed from both supervisor and user mode.
*/
#define LPIT_GPT_IP_ENABLE_USER_MODE_SUPPORT     (STD_OFF)

/*================================================================================================*/
/**
* @brief    LPIT_GPT_IP_CHANGE_NEXT_TIMEOUT_VALUE switch
* @details  Enable/disable support for changing timeout value during timer running
*/
#define LPIT_GPT_IP_CHANGE_NEXT_TIMEOUT_VALUE     (STD_OFF)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
#endif  /* LPIT_GPT_IP_CFG_H */

