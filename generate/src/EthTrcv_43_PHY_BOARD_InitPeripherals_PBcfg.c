/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : N/A
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.8
*   Build Version        : SJA11XX_RTD_1_0_8_D2601_ASR_REL_4_4_REV_0000_20260112
*
*   Copyright 2020-2026 NXP Semiconductors
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file    EthTrcv_43_PHY_PBcfg_BOARD_InitPeripherals.c
*   @version 1.0.8
*
*   @brief   AUTOSAR EthTrcv_43_PHY - Data structures for the EthTrcv driver.
*   @details Postbuild structure configurations for the driver initalization.
*
*   @addtogroup ETHTRCV
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "EthTrcv_43_PHY.h"

#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
#include "EcuM.h"
#include "Icu.h"
#endif

#include "Phy_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                     43
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C      4
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C      4
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C   0
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C              1
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C              0
#define ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C              8


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The Eth Trcv module's implementer shall avoid the integration of incompatible files.
*/

/* Check if current file and Eth Trcv header file are of the same vendor */
#if (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != ETHTRCV_43_PHY_VENDOR_ID)
#error "EthTrcv_PBcfg_BOARD_InitPeripherals.c and EthTrcv.h have different vendor ids"
#endif

/* Check if current file and Eth Trcv header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != ETHTRCV_43_PHY_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of EthTrcv_PBcfg_BOARD_InitPeripherals.c and EthTrcv.h are different"
#endif

/* Check if current file and Eth Trcv header file are of the same Software version */
#if ((ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != ETHTRCV_43_PHY_SW_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != ETHTRCV_43_PHY_SW_MINOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != ETHTRCV_43_PHY_SW_PATCH_VERSION) \
    )
#error "Software Version Numbers of EthTrcv_PBcfg_BOARD_InitPeripherals.c and EthTrcv.h are different"
#endif

/* Check if current file and DEM header file are of the same Autosar version */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if ((ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthTrcv_PBcfg_BOARD_InitPeripherals.c and Dem.h are different"
#endif
#endif
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and EcuM header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != ECUM_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != ECUM_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthTrcv_PBcfg_BOARD_InitPeripherals.c and EcuM.h are different"
#endif
/* Check if current file and Icu header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C != ICU_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C != ICU_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of EthTrcv_PBcfg_BOARD_InitPeripherals.c and Icu.h are different"
#endif
#endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                        LOCAL MACROS
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
#define ETHTRCV_43_PHY_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig0_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig1_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig2_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig3_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig4_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig5_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_DemConfigType EthTrcv_DemConfig6_BOARD_InitPeripherals =
{
    /* DEM error reporting ETHTRCV_E_ACCESS */
    {(uint32)STD_OFF, 0}
};
#endif /* (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig0_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig1_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig2_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig3_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig4_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig5_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif

#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static const EthTrcv_43_PHY_EcuMSourcesConfigType EthTrcv_EcuMConfig6_BOARD_InitPeripherals =
{
    /* Wakeup source for ETHTRCV_WUR_GENERAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_BUS */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_INTERNAL */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_RESET */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_POWER_ON */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE,
    /* Wakeup source for ETHTRCV_WUR_PIN */
    (EcuM_WakeupSourceType)ETHTRCV_43_PHY_INVALID_WAKEUP_SOURCE
};
#endif


#if ((ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON) || (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF))
/**
* @brief        Definition of Ethernet transceiver structures.
* @details      Configures the transceivers.
*               Configuration set by calling EthTrcv_Init() API.
*/
static const EthTrcv_43_PHY_TrcvConfigType EthTrcv_TrcvConfigs_BOARD_InitPeripherals[7] =
{
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig0_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig0_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig1_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig1_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig2_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig2_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig3_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig3_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig4_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig4_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig5_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig5_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    },
    {
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        /* Icu channel used for wake-up */
        (Icu_ChannelType)ETHTRCV_43_PHY_INVALID_ICU_CHANNEL,
#endif
#if (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* DEM error reporting configuration. */
        &EthTrcv_DemConfig6_BOARD_InitPeripherals,
#endif
#if (ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON)
        &EthTrcv_EcuMConfig6_BOARD_InitPeripherals,
        NULL_PTR,
        FALSE
#endif
    }
};
#endif


/**
* @brief          Initialization data for the EthTrcv driver.
* @details        A pointer to such a structure is provided to the EthTrcv initialization routines for configuration.
*
*/
const EthTrcv_43_PHY_ConfigType EthTrcv_43_PHY_PBCfgVariantPredefined =
{
    /* Number of transceivers configured */
    (uint8)7U,
    /* Wake-Up type */
    ETHTRCV_43_PHY_WAKEUP_UP_NOT_SUPPORTED,
#if ((ETHTRCV_43_PHY_WAKEUP_SUPPORT == STD_ON) || (ETHTRCV_43_PHY_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF))
    /* Pointer to the transceiver configuration array. */
    &EthTrcv_TrcvConfigs_BOARD_InitPeripherals,
#endif
    &EthTrcv_PhyDriverConfig_BOARD_InitPeripherals
};

#define ETHTRCV_43_PHY_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


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


