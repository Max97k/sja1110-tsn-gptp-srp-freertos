/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : IPV_QSPI
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

#ifndef QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_H
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_H

/**
*   @file Qspi_Ip_BOARD_InitPeripherals_PBcfg.h
*
*   @addtogroup FLS
*   @implements Qspi_Ip_PBcfg.h_Artifact
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
#include "Qspi_Ip_Types.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID                    43

#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION     4
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION  0

#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION             1
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION             0
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION             1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Types.h header file are of the same vendor */
#if (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID != FLS_QSPI_TYPES_VENDOR_ID)
    #error "Qspi_Ip_BOARD_InitPeripherals_PBcfg.h and Qspi_Ip_Types.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Types.h header file are of the same Autosar version */
#if ((QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION    != FLS_QSPI_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION    != FLS_QSPI_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION != FLS_QSPI_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Qspi_Ip_BOARD_InitPeripherals_PBcfg.h and Qspi_Ip_Types.h are different"
#endif
/* Check if current file and Qspi_Ip_Types.h header file are of the same software version */
#if ((QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION != FLS_QSPI_TYPES_SW_MAJOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION != FLS_QSPI_TYPES_SW_MINOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION != FLS_QSPI_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_BOARD_InitPeripherals_PBcfg.h and Qspi_Ip_Types.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/* Defines for direct access to the virtual LUT table */
/* Configuration: MemCfg_0 */
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_FASTREAD                  0U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_FASTWRITE                 6U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_READSTATUS               10U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_ERASESECTOR              13U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_SOFTRESET                16U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_WRITEENABLE              24U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_WRITESTATUS              26U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_READID                   29U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_READ                     32U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_WRITE                    36U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_READCR                   40U
#define MEMCFG_0_BOARD_INITPERIPHERALS_LUT_SEQUENCE_DREAD                    43U


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"


/* Controller connections */
extern const Qspi_Ip_ControllerConfigType FlsConfigSet_BOARD_InitPeripherals_paQspiUnitCfg[1U];

/* Memory configurations */
extern const Qspi_Ip_MemoryConfigType FlsConfigSet_BOARD_InitPeripherals_paFlashCfg[1U];

/* Memory-controller connections */
extern const Qspi_Ip_MemoryConnectionType FlsConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg[1U];


#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif    /* #ifndef QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_H */

