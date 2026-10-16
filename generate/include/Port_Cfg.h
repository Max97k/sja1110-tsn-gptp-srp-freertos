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

#ifndef PORT_CFG_H
#define PORT_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Port_BOARD_InitPeripherals_PBcfg.h"


#include "Acu_Ip_Types.h"
#include "Mcal.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PORT_CFG_VENDOR_ID_H                     43
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION_H      4
#define PORT_CFG_AR_RELEASE_MINOR_VERSION_H      4
#define PORT_CFG_AR_RELEASE_REVISION_VERSION_H   0
#define PORT_CFG_SW_MAJOR_VERSION_H              1
#define PORT_CFG_SW_MINOR_VERSION_H              0
#define PORT_CFG_SW_PATCH_VERSION_H              1

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Port_BOARD_InitPeripherals_PBcfg header file are of the same vendor */
#if (PORT_CFG_VENDOR_ID_H != PORT_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG_H)
    #error "Port_Cfg.h and Port_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Port_BOARD_InitPeripherals_PBcfg header file are of the same Autosar version */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION_H    != PORT_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (PORT_CFG_AR_RELEASE_MINOR_VERSION_H    != PORT_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (PORT_CFG_AR_RELEASE_REVISION_VERSION_H != PORT_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) \
    )
     #error "AUTOSAR Version Numbers of Port_Cfg.h and Port_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if current file and Port_BOARD_InitPeripherals_PBcfg header file are of the same Software version */
#if ((PORT_CFG_SW_MAJOR_VERSION_H != PORT_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (PORT_CFG_SW_MINOR_VERSION_H != PORT_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG_H) || \
     (PORT_CFG_SW_PATCH_VERSION_H != PORT_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG_H)    \
    )
    #error "Software Version Numbers of Port_Cfg.h and Port_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Checks against Acu_Ip_Types.h */
#if (PORT_CFG_VENDOR_ID_H != ACU_IP_TYPES_VENDOR_ID)
    #error "Port_Cfg.h and Acu_Ip_Types.h have different vendor ids"
#endif
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION_H    != ACU_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_CFG_AR_RELEASE_MINOR_VERSION_H    != ACU_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (PORT_CFG_AR_RELEASE_REVISION_VERSION_H != ACU_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Port_Cfg.h and Acu_Ip_Types.h are different"
#endif
#if ((PORT_CFG_SW_MAJOR_VERSION_H != ACU_IP_TYPES_SW_MAJOR_VERSION) || \
     (PORT_CFG_SW_MINOR_VERSION_H != ACU_IP_TYPES_SW_MINOR_VERSION) || \
     (PORT_CFG_SW_PATCH_VERSION_H != ACU_IP_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_Cfg.h and Acu_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Checks against Mcal.h */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION_H != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_CFG_AR_RELEASE_MINOR_VERSION_H != MCAL_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AUTOSAR Version Numbers of Acu_Ip_Types.h and Mcal.h are different"
#endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/**
* @brief Enable/Disable multicore function from the driver
*/
#define PORT_MULTICORE_ENABLED              (STD_OFF)

/**
* @brief The number of configured partition on the platform
*/
#define PORT_MAX_PARTITION              (1U)

/**
* @brief Port code size optimization macro define.
*
*/
#define PORT_CODE_SIZE_OPTIMIZATION           (STD_OFF)

/**
* @brief The maximum number of configured pins
*/
#define PORT_MAX_CONFIGURED_PADS_U16                              ((uint16)72)
/**
* @brief   Switches the Port_SetPinDirection() API ON or OFF.
*
* @api
*/
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/**
* @brief   Switches the Port_SetPinMode() API ON or OFF.
*
* @api
*/
#define PORT_SET_PIN_MODE_API                (STD_OFF)

/**
* @brief   Switches the Port_GetVersionInfo() API ON or OFF.
*
* @api
*/
#define PORT_VERSION_INFO_API                (STD_ON)

/**
* @brief   Switches the Port_SetAsUnusedPin() and Port_SetAsUsedPin() API ON or OFF.
*
* @api
*/
#define PORT_SET_AS_UNUSED_PIN_API           (STD_OFF)

/**
* @brief   Switches the Development Error Detection and Notification ON or OFF.
*
* @api
*/
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/**
* @brief            Pre-compile Support.
*/
#define PORT_PRECOMPILE_SUPPORT   (STD_ON)

/**
* @brief            User-mode Support.
*
* @api
*/
#define PORT_ENABLE_USER_MODE_SUPPORT                (STD_OFF)

#define PORT_PORT_PINS       (72UL)

#define PORT_DEDICATED_PINS  (56UL)

/**
* @brief Port Pin symbolic names
* @details Get All Symbolic Names from configuration tool
*
*/
#define PortConf_PortPin_PortPin_0 0
#define PortConf_PortPin_PortPin_1 1
#define PortConf_PortPin_PortPin_2 2
#define PortConf_PortPin_PortPin_3 3
#define PortConf_PortPin_PortPin_4 4
#define PortConf_PortPin_PortPin_5 5
#define PortConf_PortPin_PortPin_6 6
#define PortConf_PortPin_PortPin_7 7
#define PortConf_PortPin_PortPin_8 8
#define PortConf_PortPin_PortPin_9 9
#define PortConf_PortPin_PortPin_10 10
#define PortConf_PortPin_PortPin_11 11
#define PortConf_PortPin_PortPin_12 12
#define PortConf_PortPin_PortPin_13 13
#define PortConf_PortPin_PortPin_14 14
#define PortConf_PortPin_PortPin_15 15
#define PortConf_PortPin_PortPin_16 16
#define PortConf_PortPin_PortPin_17 17
#define PortConf_PortPin_PortPin_18 18
#define PortConf_PortPin_PortPin_19 19
#define PortConf_PortPin_PortPin_20 20
#define PortConf_PortPin_PortPin_21 21
#define PortConf_PortPin_PortPin_22 22
#define PortConf_PortPin_PortPin_23 23
#define PortConf_PortPin_PortPin_24 24
#define PortConf_PortPin_PortPin_25 25
#define PortConf_PortPin_PortPin_26 26
#define PortConf_PortPin_PortPin_27 27
#define PortConf_PortPin_PortPin_28 28
#define PortConf_PortPin_PortPin_29 29
#define PortConf_PortPin_PortPin_30 30
#define PortConf_PortPin_PortPin_31 31
#define PortConf_PortPin_PortPin_32 32
#define PortConf_PortPin_PortPin_33 33
#define PortConf_PortPin_PortPin_34 34
#define PortConf_PortPin_PortPin_35 35
#define PortConf_PortPin_PortPin_36 36
#define PortConf_PortPin_PortPin_37 37
#define PortConf_PortPin_PortPin_38 38
#define PortConf_PortPin_PortPin_39 39
#define PortConf_PortPin_PortPin_40 40
#define PortConf_PortPin_PortPin_41 41
#define PortConf_PortPin_PortPin_42 42
#define PortConf_PortPin_PortPin_43 43
#define PortConf_PortPin_PortPin_44 44
#define PortConf_PortPin_PortPin_45 45
#define PortConf_PortPin_PortPin_46 46
#define PortConf_PortPin_PortPin_47 47
#define PortConf_PortPin_PortPin_48 48
#define PortConf_PortPin_PortPin_49 49
#define PortConf_PortPin_PortPin_50 50
#define PortConf_PortPin_PortPin_51 51
#define PortConf_PortPin_PortPin_52 52
#define PortConf_PortPin_PortPin_53 53
#define PortConf_PortPin_PortPin_54 54
#define PortConf_PortPin_PortPin_55 55
#define PortConf_PortPin_I2C_SCL 56
#define PortConf_PortPin_I2C_SDA 57
#define PortConf_PortPin_IRQ_TJA1104B 58
#define PortConf_PortPin_IRQ_TJA1121A 59
#define PortConf_PortPin_IRQ_TJA1121B 59
#define PortConf_PortPin_IRQ_TJA1230 59
#define PortConf_PortPin_IRQ_PMIC 62
#define PortConf_PortPin_IRQ_PCAL9722 63
#define PortConf_PortPin_SWT0_GPIO8 64
#define PortConf_PortPin_SFP_MOD_ABS 65
#define PortConf_PortPin_ALIVE_LED 66
#define PortConf_PortPin_SWT0_BUTTON1 67
#define PortConf_PortPin_SWT0_BUTTON2 68
#define PortConf_PortPin_SWT0_LEDRGB_RED 69
#define PortConf_PortPin_SWT0_LEDRGB_GREEN 70
#define PortConf_PortPin_SWT0_LEDRGB_BLUE 71

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

typedef uint32 Port_PinType;

typedef struct
{
    const Acu_Ip_SettingConfigType * pPortSettingConfig;
    const Acu_Ip_UnusedPortSettingType * pPortUnusedSettingConfig;
}Port_SwitchConfigType;

typedef struct
{
    uint8 u8NumSwitches;
    const uint8 *pau8Port_PartitionList;
    const uint32 *pau32Port_PinToPartitionMap;
    const Port_SwitchConfigType * pPortSwitchSettingConfig;
}Port_ConfigType;


typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT,
    PORT_PIN_INOUT,
    PORT_PIN_HIGH_Z
}Port_PinDirectionType;


typedef uint8 Port_PinModeType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


/** @} */

#endif /* Port_CFG_H */

