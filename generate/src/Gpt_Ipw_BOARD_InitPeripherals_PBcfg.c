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
/**
 *   @file           Gpt_Ipw__PBcfg.c
 *
 *   @internal
 *   @addtogroup     gpt gpt_ipw
 *
 *   @{
 */
/*==================================================================================================
 *                              GENERATION MACRO DEFINTION
 *================================================================================================*/

/*==================================================================================================*/
#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Gpt_Ipw_BOARD_InitPeripherals_PBcfg.h"
#include "LPit_Gpt_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define GPT_IPW_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_C                    43
#define GPT_IPW_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C     4
#define GPT_IPW_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C     4
#define GPT_IPW_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_C  0
#define GPT_IPW_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C             1
#define GPT_IPW_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C             0
#define GPT_IPW_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_C             1

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
#if (GPT_IPW_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_C)
    #error "Gpt_Ipw_BOARD_InitPeripherals_PBcfg.h and Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) \
    )
    #error "AutoSar Version Numbers of Gpt_Ipw_BOARD_InitPeripherals_PBcfg.h and Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_IPW_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) || \
     (GPT_IPW_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) || \
     (GPT_IPW_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_H != GPT_IPW_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_C) \
    )
    #error "Software Version Numbers of Gpt_Ipw_BOARD_InitPeripherals_PBcfg.h and Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c are different"
#endif

#if (GPT_IPW_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_H)
    #error "Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c and LPit_Gpt_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c and LPit_Gpt_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_IPW_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (GPT_IPW_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (GPT_IPW_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_C != LPIT_GPT_IP_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) \
    )
    #error "Software Version Numbers of Gpt_Ipw_BOARD_InitPeripherals_PBcfg.c and LPit_Gpt_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/

 /*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/
#define GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"

/** 
 * @brief   GPT instances related configuration array
 */

Gpt_Ipw_HwInstanceConfigType Gpt_Ipw_HwInstanceConfig_PB_BOARD_InitPeripherals[1U] =
{
    {
        /** @brief IP type  */
/** @brief GptChannelConfiguration_0 */        GPT_LPIT_MODULE,
        /** @brief IP instance */
        0U,
        /** @brief IP instance pointer */
        {
            &LPIT_0_InitConfig_PB_BOARD_InitPeripherals
        }
    }
};

/** 
 * @brief   GPT channels IP related configuration array
 */
Gpt_Ipw_HwChannelConfigType Gpt_Ipw_ChannelConfig_PB_BOARD_InitPeripherals[1U] =
{

    {
        /** @brief IP type  */
        GPT_LPIT_MODULE,
        /** @brief IP instance */
        0U,
        /**@brief IP channel */
        0U,
        /** @brief IP channel pointer */
        {
            &LPIT_0_ChannelConfig_PB_BOARD_InitPeripherals[0U]
        }
    }
};
#define GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"
/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/


/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/


/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

#ifdef __cplusplus
}
#endif/*GPT_IPW_PBCFG_C*/

