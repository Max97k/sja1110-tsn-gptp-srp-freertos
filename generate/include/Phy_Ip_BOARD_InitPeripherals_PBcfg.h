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
#ifndef PHY_IP_BOARD_INITPERIPHERALS_PBCFG_H
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID                     43
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION      4
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION      4
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION   0
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION              1
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION              0
#define PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION              8
/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

#include "Phy_Ip_Types.h"

#ifndef SJA1110_REV_C
#define SJA1110_REV_C
#endif
#ifndef PHY_IP_SJA1110_100BASE_T1_ENABLE
#define PHY_IP_SJA1110_100BASE_T1_ENABLE
#endif
#ifndef PHY_IP_SJA1110_SGMII_ENABLE
#define PHY_IP_SJA1110_SGMII_ENABLE
#endif
#ifndef PHY_IP_TJA1121_ENABLE
#define PHY_IP_TJA1121_ENABLE
#endif
#ifndef PHY_IP_TJA1121A_ENABLE
#define PHY_IP_TJA1121A_ENABLE
#endif
#ifndef PHY_IP_TJA1121B_ENABLE
#define PHY_IP_TJA1121B_ENABLE
#endif
/* PTP and BIST features are supported only by TJA1104, TJA1120 and TJA1121. */
#ifndef PHY_IP_PTP_SUPPORTED
#define PHY_IP_PTP_SUPPORTED
#endif
#ifndef PHY_IP_BIST_SUPPORTED
#define PHY_IP_BIST_SUPPORTED
#endif
/* Macsec feature is supported by TJA1104(A/B) and TJA1121. */
#ifndef PHY_IP_MACSEC_SUPPORTED
#define PHY_IP_MACSEC_SUPPORTED
#endif

/* Definitions of names for the PHY instances */
#define SGMII_PHY_P1  (0U)
#define SGMII_PHY_P4  (1U)
#define P5_100BASE_T1  (2U)
#define P6_100BASE_T1  (3U)
#define P7_100BASE_T1  (4U)
#define P2_TJA1121A  (5U)
#define P1_TJA1121B  (6U)

#define N_PHY_DEVS_BOARD_InitPeripherals     (7U)

#define ETHTRCV_43_PHY_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

extern Phy_Ip_DriverConfigType  EthTrcv_PhyDriverConfig_BOARD_InitPeripherals;

#define ETHTRCV_43_PHY_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


/** @} */

#endif /* PHY_IP_BOARD_INITPERIPHERALS_PBCFG_H */
