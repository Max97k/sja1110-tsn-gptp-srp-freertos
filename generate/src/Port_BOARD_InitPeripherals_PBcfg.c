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

/*
*   @file   Port_BOARD_InitPeripherals_PBcfg.c
*   @implements Port_PBcfg.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - Data structures for the Port driver.
*   @details Postbuild structure configurations for the driver initalization.
*
*   @addtogroup Port
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

#include "Port_Cfg.h"
#include "Acu_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PORT_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                     43
#define PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C      4
#define PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C      4
#define PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C   0
#define PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C              1
#define PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C              0
#define PORT_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C              1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Port_Cfg.h are of the same version */
#if (PORT_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PORT_CFG_VENDOR_ID_H)
    #error "Port_BOARD_InitPeripherals_PBcfg.c and Port_Cfg.h have different vendor ids"
#endif
#if ((PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PORT_CFG_AR_RELEASE_MAJOR_VERSION_H) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PORT_CFG_AR_RELEASE_MINOR_VERSION_H) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PORT_CFG_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Port_BOARD_InitPeripherals_PBcfg.c and Port_Cfg.h are different"
#endif
#if ((PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PORT_CFG_SW_MAJOR_VERSION_H) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PORT_CFG_SW_MINOR_VERSION_H) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PORT_CFG_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_BOARD_InitPeripherals_PBcfg.c and Port_Cfg.h are different"
#endif

/* Check if current file and Acu_Ip_Cfg.h are of the same version */
#if (PORT_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ACU_IP_CFG_VENDOR_ID)
    #error "Port_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_Cfg.h have different vendor ids"
#endif
#if ((PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ACU_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ACU_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ACU_IP_CFG_AR_RELEASE_REVISION_VERSION)   \
    )
    #error "AutoSar Version Numbers of Port_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_Cfg.h are different"
#endif
#if ((PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ACU_IP_CFG_SW_MAJOR_VERSION) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ACU_IP_CFG_SW_MINOR_VERSION) || \
     (PORT_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ACU_IP_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                          LOCAL S (STRUCTURES, UNIONS, ENUMS)
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
#define PORT_NUM_OF_SWITCHES        1

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
/**
* @brief Array containing list of partition which used in driver
*/
const uint8 au8Port_PartitionList_BOARD_InitPeripherals[PORT_MAX_PARTITION] =
{
    1
};

/**
* @brief Array containing list of mapping information for mappable elements
*/
static const uint32 au32Port_PinToPartitionMap_BOARD_InitPeripherals[PORT_MAX_CONFIGURED_PADS_U16] =
{
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001,
    (uint32)0x00000001
};

/**
* @brief        Definition of a Switch Port structure.
* @details      Configures the pins of a switch.
*               Port_SwitchConfigType
*/

static const Port_SwitchConfigType Port_aConfigOfSwitchPort_BOARD_InitPeripherals[PORT_NUM_OF_SWITCHES] =
{
    {
        .pPortSettingConfig = &Acu_Ip_PinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals,
        .pPortUnusedSettingConfig = &Acu_Ip_UnusedPinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals,
    },
};

/**
* @brief        Definition of Port structure.
* @details      Configures the pins.
*               Configuration set by calling Port_Init API.
*/

const Port_ConfigType Port_Config =
{
    .pau8Port_PartitionList = au8Port_PartitionList_BOARD_InitPeripherals,
    .pau32Port_PinToPartitionMap = au32Port_PinToPartitionMap_BOARD_InitPeripherals,
    .u8NumSwitches = PORT_NUM_OF_SWITCHES,
    .pPortSwitchSettingConfig = Port_aConfigOfSwitchPort_BOARD_InitPeripherals,
};

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

