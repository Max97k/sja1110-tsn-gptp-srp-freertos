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
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ENET_IP_CFG_VENDOR_ID_C                     43
#define ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION_C      4
#define ENET_IP_CFG_AR_RELEASE_MINOR_VERSION_C      4
#define ENET_IP_CFG_AR_RELEASE_REVISION_VERSION_C   0
#define ENET_IP_CFG_SW_MAJOR_VERSION_C              1
#define ENET_IP_CFG_SW_MINOR_VERSION_C              0
#define ENET_IP_CFG_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Enet_Ip_Types.h */
#if (ENET_IP_CFG_VENDOR_ID_C != ENET_IP_TYPES_VENDOR_ID)
    #error "Enet_Ip_Cfg.c and Enet_Ip_Types.h have different vendor ids"
#endif
#if ((ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != ENET_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (ENET_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != ENET_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (ENET_IP_CFG_AR_RELEASE_REVISION_VERSION_C != ENET_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Enet_Ip_Cfg.h and Enet_Ip_Types.h are different"
#endif
#if ((ENET_IP_CFG_SW_MAJOR_VERSION_C != ENET_IP_TYPES_SW_MAJOR_VERSION) || \
     (ENET_IP_CFG_SW_MINOR_VERSION_C != ENET_IP_TYPES_SW_MINOR_VERSION) || \
     (ENET_IP_CFG_SW_PATCH_VERSION_C != ENET_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Enet_Ip_Cfg.c and Enet_Ip_Types.h are different"
#endif

/* Checks against Enet_Ip_Cfg.h */
#if (ENET_IP_CFG_VENDOR_ID_C != ENET_IP_CFG_VENDOR_ID)
    #error "Enet_Ip_Cfg.c and Enet_Ip_Cfg.h have different vendor ids"
#endif
#if ((ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ENET_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != ENET_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ENET_IP_CFG_AR_RELEASE_REVISION_VERSION_C != ENET_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Enet_Ip_Cfg.h and Enet_Ip_Cfg.h are different"
#endif
#if ((ENET_IP_CFG_SW_MAJOR_VERSION_C != ENET_IP_CFG_SW_MAJOR_VERSION) || \
     (ENET_IP_CFG_SW_MINOR_VERSION_C != ENET_IP_CFG_SW_MINOR_VERSION) || \
     (ENET_IP_CFG_SW_PATCH_VERSION_C != ENET_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Enet_Ip_Cfg.c and Enet_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((ENET_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (ENET_IP_CFG_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Enet_Ip_Cfg.h and Mcal.h are different"
    #endif
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
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

#ifdef ENET_0_RXRING_0_DESCR
    /*! @brief Reception buffer descriptors for Rx Ring 0 */
    VAR_ALIGN(Enet_Ip_BufferDescriptorType ENET_0_RxRing_0_DescBuffer[ENET_0_MAX_RXBUFF_SUPPORTED], FEATURE_ENET_BUFFDESCR_ALIGNMENT_BYTES)
#endif
#ifdef ENET_0_RXRING_0_DATA
    /*! @brief Reception data buffers for Rx Ring 0 */
    VAR_ALIGN(uint8 ENET_0_RxRing_0_DataBuffer[ENET_0_MAX_RXBUFF_SUPPORTED * ENET_0_MAX_RXBUFFLEN_SUPPORTED], FEATURE_ENET_BUFFDATA_ALIGNMENT_BYTES)
#endif
#ifdef ENET_0_TXRING_0_DESCR
    /*! @brief Transmission buffer descriptors for Tx Ring 0 */
    VAR_ALIGN(Enet_Ip_BufferDescriptorType ENET_0_TxRing_0_DescBuffer[ENET_0_MAX_TXBUFF_SUPPORTED], FEATURE_ENET_BUFFDESCR_ALIGNMENT_BYTES)
#endif
#ifdef ENET_0_TXRING_0_DATA
    /*! @brief Transmission data buffers for Tx Ring 0 */
    VAR_ALIGN(uint8 ENET_0_TxRing_0_DataBuffer[ENET_0_MAX_TXBUFF_SUPPORTED * ENET_0_MAX_TXBUFFLEN_SUPPORTED], FEATURE_ENET_BUFFDATA_ALIGNMENT_BYTES)
#endif

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"


#define ETH_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_MemMap.h"

/* Instance state structures used to hold driver runtime data */
#ifdef INST_ENET_0
    Enet_Ip_StateType ENET_0_StateStructure;
#endif

#define ETH_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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

