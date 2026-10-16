/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : 
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



#ifndef DEM_INTERRID_H
#define DEM_INTERRID_H

/**
*   @file Dem_IntErrId.h
*
*   @addtogroup DEM_MODULE
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define DEM_INTERRID_VENDOR_ID 43
#define DEM_INTERRID_MODULE_ID 54

#define DEM_INTERRID_AR_RELEASE_MAJOR_VERSION       4
#define DEM_INTERRID_AR_RELEASE_MINOR_VERSION       4
#define DEM_INTERRID_AR_RELEASE_REVISION_VERSION    0
#define DEM_INTERRID_SW_MAJOR_VERSION               1
#define DEM_INTERRID_SW_MINOR_VERSION               0
#define DEM_INTERRID_SW_PATCH_VERSION               1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#include "Dem_Types.h"
#include "Rte_Dem_Type.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** @brief Identifier for DEM error ETH_E_ACCESS */
#define DemConf_DemEventParameter_ETH_E_ACCESS   ((Dem_EventIdType) 0x1)
/** @brief Identifier for DEM error ETH_E_ALIGNMENT */
#define DemConf_DemEventParameter_ETH_E_ALIGNMENT   ((Dem_EventIdType) 0x2)
/** @brief Identifier for DEM error ETH_E_CRC */
#define DemConf_DemEventParameter_ETH_E_CRC   ((Dem_EventIdType) 0x3)
/** @brief Identifier for DEM error ETH_E_ERR */
#define DemConf_DemEventParameter_ETH_E_ERR   ((Dem_EventIdType) 0xB)
/** @brief Identifier for DEM error ETH_E_LATECOLLISION */
#define DemConf_DemEventParameter_ETH_E_LATECOLLISION   ((Dem_EventIdType) 0x4)
/** @brief Identifier for DEM error ETH_E_MULTIPLECOLLISION */
#define DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION   ((Dem_EventIdType) 0x5)
/** @brief Identifier for DEM error ETH_E_OVERSIZEFRAME */
#define DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME   ((Dem_EventIdType) 0x6)
/** @brief Identifier for DEM error ETH_E_RX_FRAMES_LOST */
#define DemConf_DemEventParameter_ETH_E_RX_FRAMES_LOST   ((Dem_EventIdType) 0x7)
/** @brief Identifier for DEM error ETH_E_SAFETY */
#define DemConf_DemEventParameter_ETH_E_SAFETY   ((Dem_EventIdType) 0xA)
/** @brief Identifier for DEM error ETH_E_SINGLECOLLISION */
#define DemConf_DemEventParameter_ETH_E_SINGLECOLLISION   ((Dem_EventIdType) 0x8)
/** @brief Identifier for DEM error ETH_E_UNDERSIZEFRAME */
#define DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME   ((Dem_EventIdType) 0x9)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DEM_INTERRID_H */

