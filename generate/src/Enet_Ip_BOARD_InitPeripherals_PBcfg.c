/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : ENET
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
*   @file
*
*   @addtogroup ENET_DRIVER_CONFIGURATION ENET Driver Configuration
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
#include "Enet_Ip_Types.h"
#include "Enet_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C                     43
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C              1
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C              0
#define ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Enet_Ip_Types.h */
#if (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != ENET_IP_TYPES_VENDOR_ID)
    #error "Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Types.h have different vendor ids"
#endif
#if ((ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != ENET_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C    != ENET_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != ENET_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Types.h are different"
#endif
#if ((ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != ENET_IP_TYPES_SW_MAJOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != ENET_IP_TYPES_SW_MINOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != ENET_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Types.h are different"
#endif

/* Checks against Enet_Ip_Cfg.h */
#if (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != ENET_IP_CFG_VENDOR_ID)
    #error "Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h have different vendor ids"
#endif
#if ((ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != ENET_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h are different"
#endif
#if ((ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != ENET_IP_CFG_SW_MAJOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != ENET_IP_CFG_SW_MINOR_VERSION) || \
     (ENET_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != ENET_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Enet_Ip_BOARD_INITPERIPHERALS_PBcfg.c and Enet_Ip_Cfg.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define ENET_ADDR_LENGTH        (6U)

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ETH_START_SEC_CODE
#include "Eth_MemMap.h"

/*! @brief Channel callbacks external declarations */

#define ETH_STOP_SEC_CODE
#include "Eth_MemMap.h"

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

extern Enet_Ip_BufferDescriptorType ENET_0_RxRing_0_DescBuffer[];
extern uint8 ENET_0_RxRing_0_DataBuffer[];
extern Enet_Ip_BufferDescriptorType ENET_0_TxRing_0_DescBuffer[];
extern uint8 ENET_0_TxRing_0_DataBuffer[];

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_MemMap.h"

extern Enet_Ip_StateType ENET_0_StateStructure;

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_MemMap.h"

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"


/*! @brief The MAC address(es) of the configured controller(s) */
static const uint8 ENET_0_au8MacAddrPB_BOARD_INITPERIPHERALS[ENET_ADDR_LENGTH] = { 0x10U, 0x11U, 0x12U, 0x66U, 0x66U, 0x66U };

/*! @brief Reception ring configuration structures */
static const Enet_Ip_BufferConfigType ENET_0_aRxRingConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Rx Ring 0 */
    {
        /*.ringDesc = */ENET_0_RxRing_0_DescBuffer,
        /*.callback = */NULL_PTR,
        /*.buffer = */ENET_0_RxRing_0_DataBuffer,
        /*.interrupts = */(uint32)0U,
        /*.bufferLen = */1536U,
        /*.ringSize = */1U
    }
};

/*! @brief Transmission ring configuration structures */
static const Enet_Ip_BufferConfigType ENET_0_aTxRingConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Tx Ring 0 */
    {
        /*.ringDesc = */ENET_0_TxRing_0_DescBuffer,
        /*.callback = */NULL_PTR,
        /*.buffer = */ENET_0_TxRing_0_DataBuffer,
        /*.interrupts = */(uint32)0U,
        /*.bufferLen = */1536U,
        /*.ringSize = */1U
    }
};

/*! @brief Module configuration structures */
static const Enet_Ip_ConfigType ENET_0_InitConfigPB_BOARD_INITPERIPHERALS =
{
    /*.rxRingCount = */1U,
    /*.txRingCount = */1U,
    /*.callback = */NULL_PTR,
    /*.interrupts = */0U,
    /*.callback = */NULL_PTR,
    /*.maxFrameLen = */1518U,
    /*.miiMode = */ENET_MII_MODE,
    /*.speed = */ENET_MII_SPEED_100M,
    /*.duplex = */ENET_MII_FULL_DUPLEX,
    /*.rxConfig = */0U | (uint32)ENET_RX_CONFIG_ENABLE_PROMISCUOUS_MODE,
    /*.txConfig = */0U,
    /*.rxAccelerConfig = */0U,
    /*.txAccelerConfig = */0U,
    /*.enableCtrl = */(boolean)FALSE
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

const Enet_CtrlConfigType Enet_aCtrlConfigPB_BOARD_INITPERIPHERALS[1U] =
{
    /* The configuration structure for Enet_aCtrlConfig[0U] */
    {
        &ENET_0_StateStructure,
        &ENET_0_InitConfigPB_BOARD_INITPERIPHERALS,
        &ENET_0_aRxRingConfigPB_BOARD_INITPERIPHERALS[0U],
        &ENET_0_aTxRingConfigPB_BOARD_INITPERIPHERALS[0U],
        &ENET_0_au8MacAddrPB_BOARD_INITPERIPHERALS[0U]
    }
};

#define ETH_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_MemMap.h"

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

