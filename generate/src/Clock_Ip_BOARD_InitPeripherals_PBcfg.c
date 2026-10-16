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
*   @file       Clock_Ip_BOARD_InitPeripherals_PBcfg.c
*   @version    1.0.1
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
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
#include "Clock_Ip_BOARD_InitPeripherals_PBcfg.h"
#include "StandardTypes.h"
#include "Clock_Ip.h"
#include "Clock_Ip_Private.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C                      43
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C       4
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C               1
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C               0
#define CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Clock_Ip_BOARD_InitPeripherals_PBcfg.h file are of the same vendor */
#if (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif

/* Check if source file and Clock_Ip_BOARD_InitPeripherals_PBcfg.h file are of the same Autosar version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/* Check if source file and Clock_Ip_BOARD_InitPeripherals_PBcfg.h file are of the same Software version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and StandardTypes.h file are of the same Autosar version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and StandardTypes.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/* Check if source file and Clock_Ip.h file are of the same vendor */
#if (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != CLOCK_IP_VENDOR_ID)
    #error "Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip.h have different vendor ids"
#endif

/* Check if source file and Clock_Ip.h file are of the same Autosar version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip.h are different"
#endif

/* Check if source file and Clock_Ip.h file are of the same Software version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != CLOCK_IP_SW_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != CLOCK_IP_SW_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != CLOCK_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip.h are different"
#endif

/* Check if source file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if source file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_Private.h are different"
#endif

/* Check if source file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_BOARD_InitPeripherals_PBcfg.c and Clock_Ip_Private.h are different"
#endif

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


/* *************************************************************************
 * Configuration structure for Clock Configuration 
 * ************************************************************************* */
const Clock_Ip_ClockConfigType Mcu_aClockConfigPB[1U] = {

    /*! @brief User Configuration structure clock_Cfg_0 */

    {
        0U,                          /* clkConfigId */
        (NULL_PTR),               /* Register data if register value optimization is enabled */

        0U,                       /* ircoscsCount */
        0U,                       /* xoscsCount */
        2U,                       /* pllsCount */
        13U,                       /* selectorsCount */
        6U,                       /* dividersCount */
        0U,                       /* dividerTriggersCount */
        0U,                       /* fracDivsCount */
        0U,                       /* extClksCount */
        13U,                       /* gatesCount */
        0U,                       /* pcfsCount */
        3U,                       /* detectCount */
        0U,                       /* configureFrequenciesCount */


        /* IRCOSC initialization. */
        {
            {
                RESERVED_CLK,           /* name */
                0U,                     /* enable */
                0U,                     /* Enable regulator */
                0U,                     /* Ircosc range */
                0U,                     /* Ircosc enable in VLP mode */
                0U,                     /* Ircosc enable in STOP mode */
            },
        },

        /* XOSC initialization. */

        {
            {
                RESERVED_CLK,           /* Clock name associated to xosc */
                0U,                     /* External oscillator frequency. */ 
                0U,                     /* Enable xosc. */
                0U,                     /* Startup stabilization time. */
                0U,                     /* bypassOption: Xosc use crystal */ 
                0U,                     /* Comparator is not enabled */ 
                0U,                     /* Crystal overdrive protection */
                0U,                     /* Gain value */
                0U,                     /* Monitor type */
                0U,                     /* Automatic level controller */
            },
        },


        /* PLL initialization. */
        {

            #if CLOCK_IP_PLLS_NO > 0U
            {
                PLL0_CLK,                /* name */
                1U,                     /* enable */
                XOSC_CLK,                     /* inputReference */
                CLOCK_IP_HAS_PLL_NORMAL_MODE_1B,                           /* Bypass */
                0U,                           /* Predivider */
                0U,                           /* Multiplier */
                0U,                           /* Postdivider */
                0U,                           /* numeratorFracLoopDiv */
                0U,                           /* mulFactorDiv */
                0U,                     /* modulation */
                0U,                     /* Modulaton type */ 
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
                0U,                     /* Monitor type */
                {                       /* Dividers */
                    20U,                     /* M */
                    1U,                     /* N */
                    1U,                     /* P */
                },
            },
            #endif

            #if CLOCK_IP_PLLS_NO > 1U
            {
                PLL1_CLK,                /* name */
                1U,                     /* enable */
                XOSC_CLK,                     /* inputReference */
                CLOCK_IP_HAS_PLL_NORMAL_MODE_1B,                           /* Bypass */
                0U,                           /* Predivider */
                0U,                           /* Multiplier */
                0U,                           /* Postdivider */
                0U,                           /* numeratorFracLoopDiv */
                0U,                           /* mulFactorDiv */
                0U,                     /* modulation */
                0U,                     /* Modulaton type */ 
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
                0U,                     /* Monitor type */
                {                       /* Dividers */
                    16U,                     /* M */
                    1U,                     /* N */
                    1U,                     /* P */
                },
            },
            #endif
        },



        /* SELECTOR initialization. */
        {

            #if CLOCK_IP_SELECTORS_NO > 0U
            {
                SAFE_CLK,                    /* Clock name associated to selector */
                FRO_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 1U
            {
                SYSTEM_CLK,                    /* Clock name associated to selector */
                IDIV2_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 2U
            {
                XMII_CLK_2M5HZ,                    /* Clock name associated to selector */
                IDIV0_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 3U
            {
                XMII_CLK_25MHZ,                    /* Clock name associated to selector */
                IDIV1_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 4U
            {
                XMII_CLK_125MHZ,                    /* Clock name associated to selector */
                IDIV2_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 5U
            {
                XMII_CLK_50MHZ,                    /* Clock name associated to selector */
                IDIV3_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 6U
            {
                MCSS_CLK,                    /* Clock name associated to selector */
                PLL1_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 7U
            {
                TIMER_CLK,                    /* Clock name associated to selector */
                IDIV0_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 8U
            {
                QSPI_CLK,                    /* Clock name associated to selector */
                IDIV4_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 9U
            {
                LPSPI_CLK,                    /* Clock name associated to selector */
                IDIV3_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 10U
            {
                ISO_CLK,                    /* Clock name associated to selector */
                XOSC_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 11U
            {
                TPR_CLK,                    /* Clock name associated to selector */
                XOSC_CLK,                    /* Name of the selected input source */
            },
            #endif

            #if CLOCK_IP_SELECTORS_NO > 12U
            {
                TEST_CLK,                    /* Clock name associated to selector */
                XOSC_CLK,                    /* Name of the selected input source */
            },
            #endif
        },


        /* DIVIDER initialization. */
        {

            #if CLOCK_IP_DIVIDERS_NO > 0U
            {
                FDIV0_CLK,                    /* name */
                1U,                              /* value */
                {
                    1U,                              /* Options */
                }
            },
            #endif

            #if CLOCK_IP_DIVIDERS_NO > 1U
            {
                IDIV0_CLK,                    /* name */
                99U,                              /* value */
                {
                    0U,                              /* Options */
                }
            },
            #endif

            #if CLOCK_IP_DIVIDERS_NO > 2U
            {
                IDIV1_CLK,                    /* name */
                9U,                              /* value */
                {
                    0U,                              /* Options */
                }
            },
            #endif

            #if CLOCK_IP_DIVIDERS_NO > 3U
            {
                IDIV2_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,                              /* Options */
                }
            },
            #endif

            #if CLOCK_IP_DIVIDERS_NO > 4U
            {
                IDIV3_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,                              /* Options */
                }
            },
            #endif

            #if CLOCK_IP_DIVIDERS_NO > 5U
            {
                IDIV4_CLK,                    /* name */
                49U,                              /* value */
                {
                    0U,                              /* Options */
                }
            },
            #endif
        },


        /* DIVIDER TRIGGER Initialization. */
        {
            #if CLOCK_IP_DIVIDER_TRIGGERS_NO > 0U
            {
                RESERVED_CLK,             /* divider name */
                COMMON_TRIGGER_DIVIDER_UPDATE, /* trigger value */
                RESERVED_CLK,             /* input source name */
            },
            #endif
        },



        /* FRACTIONAL DIVIDER initialization. */
        {
            {
                RESERVED_CLK,
                0U,
                {
                    0U,
                    0U,
                },
            },
        },


        /* EXTERNAL CLOCKS initialization. */
        {
            {
                RESERVED_CLK,                    /* name */
                0U,                              /* value */
            },
        },



        /* CLOCK GATES initialization. */
        {
            #if CLOCK_IP_GATES_NO > 0U
            {
                SAFE_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 1U
            {
                SYSTEM_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 2U
            {
                XMII_CLK_2M5HZ,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 3U
            {
                XMII_CLK_25MHZ,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 4U
            {
                XMII_CLK_125MHZ,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 5U
            {
                XMII_CLK_50MHZ,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 6U
            {
                MCSS_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 7U
            {
                TIMER_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 8U
            {
                QSPI_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 9U
            {
                LPSPI_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 10U
            {
                ISO_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 11U
            {
                TPR_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

            #if CLOCK_IP_GATES_NO > 12U
            {
                TEST_CLK,                    /* name */
                1U,                           /* enable */
            },
            #endif

        },
        /* Progressive clock switching */ 
        {
            {
                RESERVED_CLK,
                0U,
                0U,
                RESERVED_CLK,
                0U,
            },
        },
        /* Clock monitor */ 
        {
            #if CLOCK_IP_CMUS_NO > 0U
            {
                XOSC_CLK,       /* Clock name associated to clock Detection. */
                0U,
                (                     /* IER for XOSC_CLK */
                CGU_INT_SET_ENABLE_XO66M_0_ACT(0U) |
                CGU_INT_SET_ENABLE_XO66M_0_INACT(0U)
                ),
                0U,
                {
                    0U,          /* Start index in register values array */
                    0U,          /* End index in register values array */
                },
            },
            #endif
            #if CLOCK_IP_CMUS_NO > 1U
            {
                PLL0_CLK,       /* Clock name associated to clock Detection. */
                0U,
                (                     /* IER for PLL0_CLK */
                CGU_INT_SET_ENABLE_PL550M_0_ACT(0U) |
                CGU_INT_SET_ENABLE_PL550M_0_INACT(0U)
                ),
                0U,
                {
                    0U,          /* Start index in register values array */
                    0U,          /* End index in register values array */
                },
            },
            #endif
            #if CLOCK_IP_CMUS_NO > 2U
            {
                PLL1_CLK,       /* Clock name associated to clock Detection. */
                0U,
                (                     /* IER for PLL1_CLK */
                CGU_INT_SET_ENABLE_PL550M_1_ACT(0U) |
                CGU_INT_SET_ENABLE_PL550M_1_INACT(0U)
                ),
                0U,
                {
                    0U,          /* Start index in register values array */
                    0U,          /* End index in register values array */
                },
            },
            #endif
        },
        /* Specific peripheral initialization. */
        {
            0U,
            {
                {
                    RESERVED_VALUE,
                    0U,
                },
            },
        },
        /* Configured frequency values. */
        {
            {
                RESERVED_CLK,
                0U,
            },
        },
    },

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


