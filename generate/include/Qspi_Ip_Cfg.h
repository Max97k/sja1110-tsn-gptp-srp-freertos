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

#ifndef QSPI_IP_CFG_H
#define QSPI_IP_CFG_H

/**
*   @file Qspi_Ip_Cfg.h
*
*   @addtogroup FLS
*   @implements Qspi_Ip_Cfg.h_Artifact
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
#include "Qspi_Ip_BOARD_InitPeripherals_PBcfg.h"
#include "Devassert.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_VENDOR_ID_CFG                    43
#define QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG     4
#define QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG     4
#define QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG  0
#define QSPI_IP_SW_MAJOR_VERSION_CFG             1
#define QSPI_IP_SW_MINOR_VERSION_CFG             0
#define QSPI_IP_SW_PATCH_VERSION_CFG             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_CFG != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Qspi_Ip_Cfg.h and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG    != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG    != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Qspi_Ip_Cfg.h and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_CFG != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     (QSPI_IP_SW_MINOR_VERSION_CFG != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     (QSPI_IP_SW_PATCH_VERSION_CFG != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_Cfg.h and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Devassert.h header file are of the same Autosar version */
    #if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG != DEVASSERT_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Qspi_Ip_Cfg.h and Devassert.h are different"
    #endif
#endif

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* Maximum number of retries for Write Enable command */
#define QSPI_IP_MAX_RETRY                 (3U)

/* Pre-processor switch to enable/disable development error detection for QSPI Ip API */
#define DEV_ASSERT_QSPI(x)                DevAssert((x))

/* Number of serial flash devices */
#define QSPI_IP_MEM_INSTANCE_COUNT        (1U)


/* Timeout for QSPI command completion */
#define QSPI_IP_CMD_COMPLETE_TIMEOUT      (10000U)


/* Timeout for external flash software reset completion */
#define QSPI_IP_RESET_TIMEOUT             (10000U)

/* Timeout for external flash startup initialization sequence completion */
#define QSPI_IP_FLS_INIT_TIMEOUT          (100000U)

/* Timeout for a complete read operation */
#define QSPI_IP_READ_TIMEOUT              (2147483647U)

/* OsIf counter type used in timeout detection for QSPI IP operations  */
#define QSPI_IP_TIMEOUT_TYPE              (OSIF_COUNTER_DUMMY)

/* Delay after changing the value of the QSPI software reset bits */
#define QSPI_IP_SOFTWARE_RESET_DELAY      (0U)

/*! @brief Minimum delay in CPU cycles between Tx FIFO reset and Tx FIFO push */
#define QSPI_IP_TX_BUFFER_RESET_DELAY     (0U)


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_CFG_H */

