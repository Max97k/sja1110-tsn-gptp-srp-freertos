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
*   @file       Clock_Ip_Cfg_Defines.h
*   @version    1.0.1
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/

#ifndef CLOCK_IP_CFG_DEFINES_H
#define CLOCK_IP_CFG_DEFINES_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "SJA1110.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_CFG_DEFINES_VENDOR_ID                       43
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        4
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_CFG_DEFINES_SW_MAJOR_VERSION                1
#define CLOCK_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define CLOCK_IP_CFG_DEFINES_SW_PATCH_VERSION                1

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Derivative used.
*/
#define CLOCK_IP_DERIVATIVE_NOT_SUPPORT_USER_MODE
/**
* @brief            Max number of internal oscillators
*/
#define CLOCK_IP_IRCOSCS_COUNT       (0U)

/**
* @brief            Max number of external oscillators
*/
#define CLOCK_IP_XOSCS_COUNT       (1U)

/**
* @brief            Max number of pll devices
*/
#define CLOCK_IP_PLLS_COUNT       (2U)

/**
* @brief            Max number of selectors
*/
#define CLOCK_IP_SELECTORS_COUNT       (13U)

/**
* @brief            Max number of dividers
*/
#define CLOCK_IP_DIVIDERS_COUNT       (6U)

/**
* @brief            Max number of divider triggers
*/
#define CLOCK_IP_DIVIDER_TRIGGERS_COUNT       (0U)

/**
* @brief            Max number of fractional dividers
*/
#define CLOCK_IP_FRACTIONAL_DIVIDERS_COUNT       (0U)

/**
* @brief            Max number of external clocks
*/
#define CLOCK_IP_EXT_CLKS_COUNT       (0U)

/**
* @brief            Max number of pcfs
*/
#define CLOCK_IP_PCFS_COUNT       (0U)

/**
* @brief            Max number of clock gates
*/
#define CLOCK_IP_GATES_COUNT       (13U)

/**
* @brief            Max number of clock monitoring units
*/
#define CLOCK_IP_CMUS_COUNT       (3U)

/**
* @brief            Max number of configured frequencies values
*/
#define CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT       (0U)

/**
* @brief             Max number of specific peripheral (eMIOS) units
*/
#define CLOCK_IP_SPECIFIC_PERIPH_COUNT       (0U)

/**
* @brief            Clock ip supports PLL clock mode
*/
#define CLOCK_IP_HAS_PLL_BYPASS_MODE        0U
#define CLOCK_IP_HAS_PLL_NORMAL_MODE_1A     1U
#define CLOCK_IP_HAS_PLL_NORMAL_MODE_1B     2U
#define CLOCK_IP_HAS_PLL_NORMAL_MODE_1C     3U
#define CLOCK_IP_HAS_PLL_NORMAL_MODE_1D     4U

/**
* @brief            Clock ip supports divider M/N/P
*/
#define CLOCK_IP_HAS_DIVIDER_M          0U
#define CLOCK_IP_HAS_DIVIDER_N          1U
#define CLOCK_IP_HAS_DIVIDER_P          2U

#define CLOCK_IP_DEFAULT_XOSC_FREQUENCY     25000000U

/**
* @brief            Default Free-running Oscillator frequency
*/
#define CLOCK_IP_FRO_FREQUENCY          10000000U

/**
* @brief            Clock ip supports clock frequency.
*/
#define CLOCK_IP_GET_FREQUENCY_API                (STD_OFF)

/**
* @brief            Supported clocks.
*/
#define CLOCK_IP_HAS_FRO_CLK         0U
#define CLOCK_IP_HAS_XOSC_CLK         1U
#define CLOCK_IP_HAS_PLL0_CLK         2U
#define CLOCK_IP_HAS_PLL1_CLK         3U
#define CLOCK_IP_HAS_FDIV0_CLK         4U
#define CLOCK_IP_HAS_IDIV0_CLK         5U
#define CLOCK_IP_HAS_IDIV1_CLK         6U
#define CLOCK_IP_HAS_IDIV2_CLK         7U
#define CLOCK_IP_HAS_IDIV3_CLK         8U
#define CLOCK_IP_HAS_IDIV4_CLK         9U
#define CLOCK_IP_FEATURE_PRODUCERS_NO         10U
#define CLOCK_IP_HAS_SAFE_CLK         11U
#define CLOCK_IP_HAS_SYSTEM_CLK         12U
#define CLOCK_IP_HAS_XMII_CLK_2M5HZ         13U
#define CLOCK_IP_HAS_XMII_CLK_25MHZ         14U
#define CLOCK_IP_HAS_XMII_CLK_125MHZ         15U
#define CLOCK_IP_HAS_XMII_CLK_50MHZ         16U
#define CLOCK_IP_HAS_MCSS_CLK         17U
#define CLOCK_IP_HAS_DMA0_CLK         18U
#define CLOCK_IP_HAS_ENET0_CLK         19U
#define CLOCK_IP_HAS_TIMER_CLK         20U
#define CLOCK_IP_HAS_ENET0_TIME_CLK         21U
#define CLOCK_IP_HAS_QSPI_CLK         22U
#define CLOCK_IP_HAS_QSPI0_CLK         23U
#define CLOCK_IP_HAS_LPSPI_CLK         24U
#define CLOCK_IP_HAS_LPSPI0_CLK         25U
#define CLOCK_IP_HAS_LPSPI1_CLK         26U
#define CLOCK_IP_HAS_ISO_CLK         27U
#define CLOCK_IP_HAS_TPR_CLK         28U
#define CLOCK_IP_HAS_TEST_CLK         29U
#define CLOCK_IP_FEATURE_NAMES_NO         30U

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif /* #ifndef CLOCK_IP_CFG_DEFINES_H */

/** @} */


