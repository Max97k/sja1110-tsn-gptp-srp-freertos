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

#if !defined(QSPI_IP_FEATURES_H)
#define QSPI_IP_FEATURES_H

/**
*   @file Qspi_Ip_Features.h
*
*   @addtogroup FLS
*   @implements Qspi_Ip_Features.h_Artifact
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
#include "SJA1110.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_FEATURES_VENDOR_ID_CFG                      43
#define QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG       4
#define QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG       4
#define QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG    0
#define QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG               1
#define QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG               0
#define QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG               1

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/* QuadSPI module features */

/*! @brief First address of the serial flash device on the AHB bus for QuadSPI instances */
#define FEATURE_QSPI_AMBA_BASE                        {0x41000000UL}
/*! @brief Size of AHB buffer. */
#define FEATURE_QSPI_AHB_BUF_SIZE                     128U
/*! @brief Size of Tx FIFO. */
#define FEATURE_QSPI_TX_BUF_SIZE                      64U
/*! @brief Size of Rx FIFO. */
#define FEATURE_QSPI_RX_BUF_SIZE                      128U
/*! @brief Number of LUT registers that make up a LUT sequence */
#define FEATURE_QSPI_LUT_SEQUENCE_SIZE                4U
/* Minimum entries of 4 bytes fill needed to allow Tx operation to start */
#define FEATURE_QSPI_TX_MIN_BUF_FILL                  4U

/*! @brief Supports Double Data Rate operation */
#define FEATURE_QSPI_DDR                              0
/*! @brief QSPI side B is available */
#define FEATURE_QSPI_HAS_SIDE_B                       0
/*! @brief Configurable Idle Signal Drive */
#define FEATURE_QSPI_CONFIGURABLE_ISD                 1

/*! @brief Supports addr. config options (column address, word addressable) */
#define FEATURE_QSPI_ADDR_CFG                         1
/*! @brief Supports byte swap */
#define FEATURE_QSPI_BYTES_SWAP_ADDR                  0

/*! @brief Supports center-aligned read strobe */
#define FEATURE_QSPI_CENTER_ALIGNED_READ_STROBE       0
/*! @brief Supports differential clock */
#define FEATURE_QSPI_DIFFERENTIAL_CLOCK               0

/*! @brief Supports internal DQS sampling mode */
#define FEATURE_QSPI_INTERNAL_DQS                     0
/*! @brief Supports loopback sampling mode */
#define FEATURE_QSPI_LOOPBACK                         1
/*! @brief Supports DQS loopback sampling mode */
#define FEATURE_QSPI_LOOPBACK_DQS                     0
/*! @brief Supports external DQS sampling mode */
#define FEATURE_QSPI_EXTERNAL_DQS                     0
/*! @brief Supports DQS_FA_SEL/DQS_FB_SEL field in MCR register for DQS selection */
#define FEATURE_QSPI_SELECT_DQS                       0

/*! @brief Supports Dll feature */
#define FEATURE_QSPI_HAS_DLL                          0
/*! @brief Supports full DLL features (as opposed to bypass mode only) */
#define FEATURE_QSPI_EXTERNAL_DLL_FULL                0
/*! @brief Supports DLL reference counter and DLL resolution */
#define FEATURE_QSPI_DLL_LOOPCONTROL                  0



/*! @brief The maximum size of manufacturer & device ID that flash memories can have */
#define FEATURE_QSPI_FLASH_MDID_SIZE                  4U

/*! @brief AHB base pointers initializer for all QSPI units */
#define QuadSPI_AHB_PTRS      FEATURE_QSPI_AMBA_BASE


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_FEATURES_H */

