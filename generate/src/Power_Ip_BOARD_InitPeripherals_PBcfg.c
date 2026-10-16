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
*   @file       Power_Ip_PBcfg.c
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
#include "Power_Ip_BOARD_InitPeripherals_PBcfg.h"
#include "Power_Ip.h"
#include "StandardTypes.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_PBCFG_VENDOR_ID_C                      43
#define POWER_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C       4
#define POWER_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_PBCFG_SW_MAJOR_VERSION_C               1
#define POWER_IP_PBCFG_SW_MINOR_VERSION_C               0
#define POWER_IP_PBCFG_SW_PATCH_VERSION_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if source file and Power_Ip_PBcfg.h file are of the same vendor */
#if (POWER_IP_PBCFG_VENDOR_ID_C != POWER_IP_PBCFG_VENDOR_ID)
    #error "Power_Ip_PBcfg.c and Power_Ip_PBcfg.h have different vendor ids"
#endif
/* Check if source file and Power_Ip_PBcfg.h file are of the same Autosar version */
#if ((POWER_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PBcfg.c and Power_Ip_PBcfg.h are different"
#endif
/* Check if source file and Power_Ip_PBcfg.h file are of the same Software version */
#if ((POWER_IP_PBCFG_SW_MAJOR_VERSION_C != POWER_IP_PBCFG_SW_MAJOR_VERSION) || \
     (POWER_IP_PBCFG_SW_MINOR_VERSION_C != POWER_IP_PBCFG_SW_MINOR_VERSION) || \
     (POWER_IP_PBCFG_SW_PATCH_VERSION_C != POWER_IP_PBCFG_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of Power_Ip_PBcfg.c and Power_Ip_PBcfg.h are different"
#endif

/* Check if source file and Power_Ip.h file are of the same vendor */
#if (POWER_IP_PBCFG_VENDOR_ID_C != POWER_IP_VENDOR_ID)
    #error "Power_Ip_PBcfg.c and Power_Ip.h have different vendor ids"
#endif
/* Check if source file and Power_Ip.h file are of the same Autosar version */
#if ((POWER_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != POWER_IP_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != POWER_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PBcfg.c and Power_Ip.h are different"
#endif
/* Check if source file and Power_Ip.h file are of the same Software version */
#if ((POWER_IP_PBCFG_SW_MAJOR_VERSION_C != POWER_IP_SW_MAJOR_VERSION) || \
     (POWER_IP_PBCFG_SW_MINOR_VERSION_C != POWER_IP_SW_MINOR_VERSION) || \
     (POWER_IP_PBCFG_SW_PATCH_VERSION_C != POWER_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PBcfg.c and Power_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and StandardTypes.h file are of the same Autosar version */
#if ((POWER_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PBcfg.c and StandardTypes.h are different"
#endif

#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

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
#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"

/**
* @brief          Definition of a MCU mode section in the configuration structure.
* @details        Specifies the system behaviour during the selected target mode.
*                 Data set and configured by Mcu_SetMode call.
*/
const Power_Ip_ModeConfigType Power_Ip_aModeConfigPB[1U] =
{

    /* Start of Mcu_aModeConfig[0] */
    {

        /* Mode Configuration ID. */
        (Power_Ip_ModeType)0U,

        /* The Power Mode name (code). */
        POWER_IP_ACTIVE_MODE,

        /* The Sleep On Exit configuration. */
        (boolean)FALSE,
    } /* End of Mcu_aModeConfig[0] */
};


#if (POWER_IP_PERFORM_RESET_API == STD_ON)
/**
* @brief          Initialization data for RGU hardware IP.
* @details        Static configuration assigned at startup by calling Mcu_PerformReset() API.n*
*/
static const Power_Ip_RGU_ConfigType Power_Ip_RGU_ConfigPB =
{
    /* MC_ResetType. */
    (MCU_HW_INP_RESET),
};
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */


/**
* @brief          Initialization data for PMU hw IP.
* @details        Static configuration realized at startup by calling Mcu_Init() API.
*
*/
static const Power_Ip_PMU_ConfigType Power_Ip_PMU_ConfigPB =
{
    (uint32)0U,     /* Bandgap power-down */
    (uint32)1U,     /* LDO2V5 enable */
    (uint32)0U,     /* Interrupt enable set register */
    (uint32)1U,     /* Interrupt enable clear register */
    (Power_Ip_PMU_LDOType)PMU_LDO_VOUT_1V7,                    /* LDO1V8 output voltage level adjust. */
    (Power_Ip_PMU_LDOType)PMU_LDO_VOUT_1V7                     /* LDO2V5 output voltage level adjust */
};


/**
* @brief          Initialization data for different hw IPs.
* @details        Static configuration realized at startup by calling Mcu_Init() API.
*
*/
const Power_Ip_HwIPsConfigType Power_Ip_HwIPsConfigPB =
{
#if (POWER_IP_PERFORM_RESET_API == STD_ON)
    /* Configuration for RGU (Reset Generation Module) hardware IP. */
    &Power_Ip_RGU_ConfigPB,
#endif

    /* Configuration for PMU (Power Management Unit) hardware IP, part of PCU. */
    &Power_Ip_PMU_ConfigPB,
};



#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"

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


