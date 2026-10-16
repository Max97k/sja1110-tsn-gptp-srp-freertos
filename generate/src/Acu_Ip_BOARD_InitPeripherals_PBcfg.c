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
*   @file
*
*   @addtogroup PORT_DRIVER_CONFIGURATION PORT Driver Configuration
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
#include "Acu_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C                     43
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C              1
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C              0
#define ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Acu_Ip_BOARD_InitPeripherals_PBcfg.h */
#if (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Acu_Ip_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
#if ((ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C    != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Acu_Ip_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
#if ((ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     (ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != ACU_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Acu_Ip_BOARD_InitPeripherals_PBcfg.c and Acu_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
const Acu_Ip_SettingConfigType Acu_Ip_PinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals =
{
    .cfgPinMii2Tx =
    {
        .clkIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .clkOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .clkSrc                    = Acu_Ip_SJA11XX_xmiiClkSrc_AUTO,
        .clkPolInv                 = FALSE,
        .ctrlIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ctrlOs                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .d10Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d10Os                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .d32Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d32Os                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
    },
    .cfgPinMii2Rx =
    {
        .clkIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .clkOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .clkSrc                    = Acu_Ip_SJA11XX_xmiiClkSrc_AUTO,
        .clkPolInv                 = FALSE,
        .ctrlIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ctrlOs                    = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .d10Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d10Os                     = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .d32Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d32Os                     = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
    },
    .cfgPinMii2Id =
    {
        .rxcStableOverwrite        = FALSE,
        .rxcPhase                  = 8U,
        .rxcRange                  = Acu_Ip_SJA11XX_freqRange_AUTO,
        .rxcBypass                 = FALSE,
        .rxcPd                     = TRUE,
        .txcStableOverwrite        = FALSE,
        .txcPhase                  = 8U,
        .txcRange                  = Acu_Ip_SJA11XX_freqRange_AUTO,
        .txcBypass                 = TRUE,
        .txcPd                     = FALSE,
    },
    .cfgPinMii3Tx =
    {
        .clkIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .clkOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .clkSrc                    = Acu_Ip_SJA11XX_xmiiClkSrc_AUTO,
        .clkPolInv                 = FALSE,
        .ctrlIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ctrlOs                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .d10Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d10Os                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .d32Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d32Os                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
    },
    .cfgPinMii3Rx =
    {
        .clkIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .clkOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .clkSrc                    = Acu_Ip_SJA11XX_xmiiClkSrc_AUTO,
        .clkPolInv                 = FALSE,
        .ctrlIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ctrlOs                    = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .d10Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d10Os                     = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .d32Ipud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .d32Os                     = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
    },
    .cfgPinMii3Id =
    {
        .rxcStableOverwrite        = FALSE,
        .rxcPhase                  = 8U,
        .rxcRange                  = Acu_Ip_SJA11XX_freqRange_AUTO,
        .rxcBypass                 = FALSE,
        .rxcPd                     = TRUE,
        .txcStableOverwrite        = FALSE,
        .txcPhase                  = 8U,
        .txcRange                  = Acu_Ip_SJA11XX_freqRange_AUTO,
        .txcBypass                 = FALSE,
        .txcPd                     = TRUE,
    },
    .cfgPinRefclk =
    {
        .out4PolInv                = FALSE,
        .out4Mode                  = Acu_Ip_SJA11XX_pinOutputMode_ACTIVE,
        .out4Os                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .out4Ipud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .out3PolInv                = FALSE,
        .out3Mode                  = Acu_Ip_SJA11XX_pinOutputMode_ACTIVE,
        .out3Os                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .out3Ipud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .out2PolInv                = FALSE,
        .out2Mode                  = Acu_Ip_SJA11XX_pinOutputMode_ACTIVE,
        .out2Os                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .out2Ipud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .out1PolInv                = FALSE,
        .out1Mode                  = Acu_Ip_SJA11XX_pinOutputMode_ACTIVE,
        .out1Os                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .out1Ipud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSync =
    {
        .devicesyncOs              = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .devicesyncIpud            = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ptpclkOs                  = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .ptpclkIpud                = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSpiHap =
    {
        .sdoOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .sdoIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .sdiIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .sckIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSpiHapSs =
    {
        .ss1nIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ss0nIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSpiPer =
    {
        .sdoOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .sdoIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .sdiOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .sdiIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .sckOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .sckIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSpiPerSs =
    {
        .ss1nOs                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .ss1nIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .ss0nOs                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .ss0nIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinQspi =
    {
        .ioOs                      = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .ioIpud                    = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .sckOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .sckIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinQspiSs =
    {
        .ssnOs                     = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .ssnIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinSmi =
    {
        .mdioOutOs                 = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .mdioOutIpud               = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .mdcOutOs                  = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .mdcOutIpud                = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .mdioApOs                  = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .mdioApIpud                = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .mdcApIpud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinDebug =
    {
        .tdoswoOs                  = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .tdoswoIpud                = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .tdiIpud                   = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .tmsswdioOs                = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .tmsswdioIpud              = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .tckswclkIpud              = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
    },
    .cfgPinMisc =
    {
        .devicecfgnOmActiveHigh    = TRUE,
        .devicecfgnOs              = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .devicecfgnIpud            = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .intnOmActiveHigh          = TRUE,
        .intnOs                    = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .intnIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .rstnIpud                  = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .trstnIpud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinGpio1 =
    {
        .gpio3Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio3Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .gpio2Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio2Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio1Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio1Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio0Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio0Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinGpio2 =
    {
        .gpio3Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio3Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio2Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio2Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio1Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio1Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .gpio0Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio0Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
    },
    .cfgPinGpio3 =
    {
        .gpio3Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio3Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio2Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio2Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio1Os                   = Acu_Ip_SJA11XX_outputStageSpeed_MEDIUM_SPEED,
        .gpio1Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PULL_UP,
        .gpio0Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio0Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .cfgPinGpio4 =
    {
        .gpio3Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio3Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio2Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio2Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio1Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio1Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .gpio0Os                   = Acu_Ip_SJA11XX_outputStageSpeed_FAST_SPEED,
        .gpio0Ipud                 = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
    },
    .settingGpio[0] =
    {
        .gpioPin                   = 0,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_TRISTATE,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[1] =
    {
        .gpioPin                   = 1,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_TRISTATE,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[2] =
    {
        .gpioPin                   = 2,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 0U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[3] =
    {
        .gpioPin                   = 3,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_TRISTATE,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[4] =
    {
        .gpioPin                   = 4,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_TRISTATE,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[5] =
    {
        .gpioPin                   = 5,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_TRISTATE,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[6] =
    {
        .gpioPin                   = 6,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[7] =
    {
        .gpioPin                   = 7,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[8] =
    {
        .gpioPin                   = 8,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[9] =
    {
        .gpioPin                   = 9,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_RISING_EDGE,
        .initValue                 = 1U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[10] =
    {
        .gpioPin                   = 10,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_DISABLE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[11] =
    {
        .gpioPin                   = 11,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 0U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[12] =
    {
        .gpioPin                   = 12,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_FALLING_EDGE,
        .initValue                 = 0U,
        .bDirChangeable            = TRUE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[13] =
    {
        .gpioPin                   = 13,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_DISABLE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[14] =
    {
        .gpioPin                   = 14,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_DISABLE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
    .settingGpio[15] =
    {
        .gpioPin                   = 15,
        .outputBuffer              = PORT_SJA11XX_OUTPUT_BUFFER_ENABLED,
        .inputBuffer               = PORT_SJA11XX_INPUT_BUFFER_DISABLED,
        .activeState               = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                   = PORT_SJA11XX_INTERRUPT_DISABLE,
        .initValue                 = 0U,
        .bDirChangeable            = FALSE,
        .bModeChangeable           = FALSE,
    },
};
const Acu_Ip_UnusedPortSettingType Acu_Ip_UnusedPinConfigurationOfSwitch_PortContainer_0_BOARD_InitPeripherals =
{
        .outputSpeed              = Acu_Ip_SJA11XX_outputStageSpeed_LOW_SPEED,
        .inputPullSelection       = Acu_Ip_SJA11XX_pinInputStageSelection_PLAIN_INPUT,
        .outputBuffer             = PORT_SJA11XX_OUTPUT_BUFFER_DISABLED,
        .inputBuffer              = PORT_SJA11XX_INPUT_BUFFER_ENABLED,
        .activeState              = PORT_SJA11XX_ACTIVE_STATE_HIGH,
        .intType                  = PORT_SJA11XX_INTERRUPT_DISABLE,
        .initValue                = 0U,
};
/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

