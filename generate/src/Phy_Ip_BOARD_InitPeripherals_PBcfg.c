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

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Phy_Ip.h"
#include "Phy_Ip_BOARD_InitPeripherals_PBcfg.h"

#include "Phy_Ip_SJA1110_SGMII.h"
#include "Phy_Ip_SJA1110_100BASE-T1.h"
#include "Phy_Ip_TJA1121.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                      43
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C       4
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C       4
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C    0
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C               1
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C               0
#define PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C               8

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Phy_Ip header file are of the same vendor */
#if (PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PHY_IP_VENDOR_ID)
    #error "Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip header file are of the same Autosar version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PHY_IP_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PHY_IP_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PHY_IP_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip.h are different"
#endif
/* Check if current file and Phy_Ip header file are of the same Software version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PHY_IP_SW_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PHY_IP_SW_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PHY_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip.h are different"
#endif

/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same vendor */
#if (PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same Autosar version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same Software version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/* Check if current file and Phy_Ip_SJA1110_SGMII header file are of the same vendor */
#if (PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PHY_IP_SJA1110_SGMII_VENDOR_ID)
    #error "Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_SGMII.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip_SJA1110_SGMII header file are of the same Autosar version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PHY_IP_SJA1110_SGMII_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PHY_IP_SJA1110_SGMII_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PHY_IP_SJA1110_SGMII_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_SGMII.h are different"
#endif
/* Check if current file and Phy_Ip_SJA1110_SGMII header file are of the same Software version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PHY_IP_SJA1110_SGMII_SW_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PHY_IP_SJA1110_SGMII_SW_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PHY_IP_SJA1110_SGMII_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_SGMII.h are different"
#endif
/* Check if current file and Phy_Ip_SJA1110_100BASE-T1 header file are of the same vendor */
#if (PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PHY_IP_SJA1110_100BASE_T1_VENDOR_ID)
    #error "Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_100BASE-T1.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip_SJA1110_100BASE-T1 header file are of the same Autosar version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PHY_IP_SJA1110_100BASE_T1_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PHY_IP_SJA1110_100BASE_T1_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PHY_IP_SJA1110_100BASE_T1_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_100BASE-T1.h are different"
#endif
/* Check if current file and Phy_Ip_SJA1110_100BASE-T1 header file are of the same Software version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PHY_IP_SJA1110_100BASE_T1_SW_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PHY_IP_SJA1110_100BASE_T1_SW_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PHY_IP_SJA1110_100BASE_T1_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_SJA1110_100BASE-T1.h are different"
#endif
/* Check if current file and Phy_Ip_TJA1121 header file are of the same vendor */
#if (PHY_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != PHY_IP_TJA1121_VENDOR_ID)
    #error "Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_TJA1121.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip_TJA1121 header file are of the same Autosar version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != PHY_IP_TJA1121_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != PHY_IP_TJA1121_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != PHY_IP_TJA1121_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_TJA1121.h are different"
#endif
/* Check if current file and Phy_Ip_TJA1121 header file are of the same Software version */
#if (( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != PHY_IP_TJA1121_SW_MAJOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != PHY_IP_TJA1121_SW_MINOR_VERSION) || \
     ( PHY_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != PHY_IP_TJA1121_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_BOARD_InitPeripherals_PBcfg.c and Phy_Ip_TJA1121.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

#define PHY_TYPE_SJA1110_SGMII (0U)
#define PHY_TYPE_SJA1110_100BASE_T1 (1U)
#define PHY_TYPE_TJA1121 (2U)

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*! @brief HW access functions */
extern Std_ReturnType Phy_Ip_SJA1110_100BASE_T1_Read(uint8 ctrlIdx, uint8 phyAddr, uint8 registerAddr, uint16 *value);
extern Std_ReturnType Eth_ReadMii(uint8 ctrlIdx, uint8 phyAddr, uint8 registerAddr, uint16 *value);
extern Std_ReturnType Phy_Ip_SJA1110_100BASE_T1_Write(uint8 ctrlIdx, uint8 phyAddr, uint8 registerAddr, uint16 value);
extern Std_ReturnType Eth_WriteMii(uint8 ctrlIdx, uint8 phyAddr, uint8 registerAddr, uint16 value);
extern Std_ReturnType Phy_Ip_SJA1110_100BASE_T1_ReadMMD(uint8 ctrlIdx, uint8 phyAddr, uint8 mmd, uint16 registerAddr, uint16 *value);
extern Std_ReturnType Eth_ReadMmd(uint8 ctrlIdx, uint8 phyAddr, uint8 mmd, uint16 registerAddr, uint16 *value);
extern Std_ReturnType Phy_Ip_SJA1110_100BASE_T1_WriteMMD(uint8 ctrlIdx, uint8 phyAddr, uint8 mmd, uint16 registerAddr, uint16 value);
extern Std_ReturnType Eth_WriteMmd(uint8 ctrlIdx, uint8 phyAddr, uint8 mmd, uint16 registerAddr, uint16 value);
/*FUNCTION**********************************************************************
 *
 * Function Name : User-defined callback name
 * Description   : User-defined callback functions for specific events
 * Parameters:
 *   phy The device number, representing the index in the array of PHY configurations.
 *   irqSrc The indicator for the source of the event.
 *   alreadyExecutedAction The default action executed(for the events which have dafault action).
 * Return: Returned value is not used in the driver, it is kept to match the prototype of other interrupt callbacks.
 *
 *END**************************************************************************/

#define ETHTRCV_43_PHY_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

/*! @brief MacSec State Machine for PHY  5 */
static Phy_Ip_MacSec_StateType macSecState5_BOARD_InitPeripherals;
/*! @brief MacSec State Machine for PHY  6 */
static Phy_Ip_MacSec_StateType macSecState6_BOARD_InitPeripherals;

static Phy_Ip_StateMachineType EthTrcv_PhyState_BOARD_InitPeripherals[7] = {
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        NULL_PTR,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        NULL_PTR,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        NULL_PTR,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        NULL_PTR,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        NULL_PTR,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        &macSecState5_BOARD_InitPeripherals,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
    {
        PHY_REVISION_UNKNOWN,
        PHY_ROLE_AUTO,
        {PHY_TIMEOUT_IDLE, 0UL, 0UL},
        {0UL, 0UL, 0UL, 0UL},
        0UL,
        0U,
        &macSecState6_BOARD_InitPeripherals,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
        FALSE,
    },
};

#define ETHTRCV_43_PHY_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

#define ETHTRCV_43_PHY_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

/*! @brief HW configuration for PHY 0 */
static const Phy_Ip_HwAccessType phyHwAccess0_BOARD_InitPeripherals = {
    1U,
    PHY_LOCATION_INTERNAL,
    0U,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};

/*! @brief HW configuration for PHY 1 */
static const Phy_Ip_HwAccessType phyHwAccess1_BOARD_InitPeripherals = {
    4U,
    PHY_LOCATION_INTERNAL,
    0U,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};

/*! @brief HW configuration for PHY 2 */
static const Phy_Ip_HwAccessType phyHwAccess2_BOARD_InitPeripherals = {
    1U,
    PHY_LOCATION_INTERNAL,
    0U,
    Phy_Ip_SJA1110_100BASE_T1_Write,
    Phy_Ip_SJA1110_100BASE_T1_Read,
    NULL_PTR,
    Phy_Ip_SJA1110_100BASE_T1_WriteMMD,
    Phy_Ip_SJA1110_100BASE_T1_ReadMMD,
    NULL_PTR
};

/*! @brief HW configuration for PHY 3 */
static const Phy_Ip_HwAccessType phyHwAccess3_BOARD_InitPeripherals = {
    1U,
    PHY_LOCATION_INTERNAL,
    0U,
    Phy_Ip_SJA1110_100BASE_T1_Write,
    Phy_Ip_SJA1110_100BASE_T1_Read,
    NULL_PTR,
    Phy_Ip_SJA1110_100BASE_T1_WriteMMD,
    Phy_Ip_SJA1110_100BASE_T1_ReadMMD,
    NULL_PTR
};

/*! @brief HW configuration for PHY 4 */
static const Phy_Ip_HwAccessType phyHwAccess4_BOARD_InitPeripherals = {
    1U,
    PHY_LOCATION_INTERNAL,
    0U,
    Phy_Ip_SJA1110_100BASE_T1_Write,
    Phy_Ip_SJA1110_100BASE_T1_Read,
    NULL_PTR,
    Phy_Ip_SJA1110_100BASE_T1_WriteMMD,
    Phy_Ip_SJA1110_100BASE_T1_ReadMMD,
    NULL_PTR
};

/*! @brief HW configuration for PHY 5 */
static const Phy_Ip_HwAccessType phyHwAccess5_BOARD_InitPeripherals = {
    2U,
    PHY_LOCATION_EXTERNAL,
    0U,
    &Eth_WriteMii,
    &Eth_ReadMii,
    NULL_PTR,
    &Eth_WriteMmd,
    &Eth_ReadMmd,
    NULL_PTR
};

/*! @brief MacSec configuration for PHY 5 */
static const Phy_Ip_MacSec_CfgType macSecCfg5_BOARD_InitPeripherals = {
  FALSE,
  FALSE,
  {
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    0,
    FALSE,
    0
  }
};
/*! @brief Ptp configuration for PHY 5 */
static const Phy_Ip_Ptp_ConfigType ptpCfg5_BOARD_InitPeripherals = {
  FALSE, /* PTP feature is set to FALSE for this PHY */
  FALSE, /* Software tracking is set to FALSE for this PHY */
  {
    FALSE, /* Controls if VLAN tagged PTP frame is considered for timestamp. */
    FALSE, /* Controls if domainNumber needs to be checked. */
    0U,    /* Domain number value. */
    FALSE, /* Controls if versionFilter needs to be checked. */
    0U,    /* Version number value. */
    FALSE, /* Controls whether fixed DA (01:80:C2:00:00:0E) can be used for honoring PTP message. */
    FALSE, /* Controls whether fixed DA (01:1B:19:00:00:00) can be used for honoring PTP message. */
    FALSE  /* Controls whether user DA can be used for honoring PTP message. */
  },
  0x0U,    /* MAC Destination Address. */
  0x0U,    /* MASK Address. */
  {
    FALSE, /* Controls whether Pdelay_Resp event should be considered for timestamping or not. */
    FALSE, /* Controls whether Pdelay_Request event should be considered for timestamping or not. */
    FALSE, /* Controls whether Delay_Request event should be considered for timestamping or not. */
    FALSE  /* Controls whether sync event should be considered for timestamping or not. */
  },
  {
    FALSE, /* Controls whether rising edge should be used for PTP trigger timestamping or not. */
    FALSE, /* Controls whether falling edge should be used for PTP trigger timestamping or not. */
    FALSE, /* Controls whether rising edge should be used for PTP sync timestamping or not. */
    FALSE  /* Controls whether falling edge should be used for PTP sync timestamping or not. */
  }
};
/*! @brief HW configuration for PHY 6 */
static const Phy_Ip_HwAccessType phyHwAccess6_BOARD_InitPeripherals = {
    1U,
    PHY_LOCATION_EXTERNAL,
    0U,
    &Eth_WriteMii,
    &Eth_ReadMii,
    NULL_PTR,
    &Eth_WriteMmd,
    &Eth_ReadMmd,
    NULL_PTR
};

/*! @brief MacSec configuration for PHY 6 */
static const Phy_Ip_MacSec_CfgType macSecCfg6_BOARD_InitPeripherals = {
  FALSE,
  FALSE,
  {
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    0,
    FALSE,
    0
  }
};
/*! @brief Ptp configuration for PHY 6 */
static const Phy_Ip_Ptp_ConfigType ptpCfg6_BOARD_InitPeripherals = {
  FALSE, /* PTP feature is set to FALSE for this PHY */
  FALSE, /* Software tracking is set to FALSE for this PHY */
  {
    FALSE, /* Controls if VLAN tagged PTP frame is considered for timestamp. */
    FALSE, /* Controls if domainNumber needs to be checked. */
    0U,    /* Domain number value. */
    FALSE, /* Controls if versionFilter needs to be checked. */
    0U,    /* Version number value. */
    FALSE, /* Controls whether fixed DA (01:80:C2:00:00:0E) can be used for honoring PTP message. */
    FALSE, /* Controls whether fixed DA (01:1B:19:00:00:00) can be used for honoring PTP message. */
    FALSE  /* Controls whether user DA can be used for honoring PTP message. */
  },
  0x0U,    /* MAC Destination Address. */
  0x0U,    /* MASK Address. */
  {
    FALSE, /* Controls whether Pdelay_Resp event should be considered for timestamping or not. */
    FALSE, /* Controls whether Pdelay_Request event should be considered for timestamping or not. */
    FALSE, /* Controls whether Delay_Request event should be considered for timestamping or not. */
    FALSE  /* Controls whether sync event should be considered for timestamping or not. */
  },
  {
    FALSE, /* Controls whether rising edge should be used for PTP trigger timestamping or not. */
    FALSE, /* Controls whether falling edge should be used for PTP trigger timestamping or not. */
    FALSE, /* Controls whether rising edge should be used for PTP sync timestamping or not. */
    FALSE  /* Controls whether falling edge should be used for PTP sync timestamping or not. */
  }
};

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

static const Phy_Ip_ConfigType EthTrcv_PhyConfig_BOARD_InitPeripherals[7] = {
    {
        &PHY_driver_SJA1110_SGMII,
        TRUE,
        PHY_SPEED_1_GBPS,
        FALSE,
        PHY_ROLE_SLAVE,
        PHY_FULL_DUPLEX,
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkUpEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        FALSE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess0_BOARD_InitPeripherals,
        NULL_PTR,
        NULL_PTR,
        PHY_DEVICE_TYPE_SJA1110_SGMII, /* The actual device type name. */
        PHY_TYPE_NO_VARIANT,
        NULL_PTR, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_SJA1110_SGMII,
        TRUE,
        PHY_SPEED_AUTONEG,
        FALSE,
        PHY_ROLE_MASTER,
        PHY_FULL_DUPLEX,
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkUpEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        FALSE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess1_BOARD_InitPeripherals,
        NULL_PTR,
        NULL_PTR,
        PHY_DEVICE_TYPE_SJA1110_SGMII, /* The actual device type name. */
        PHY_TYPE_NO_VARIANT,
        NULL_PTR, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_SJA1110_100BASE_T1,
        FALSE,
        PHY_SPEED_100_MBPS,
        FALSE,
        PHY_ROLE_AUTO,
        PHY_FULL_DUPLEX,
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkUpEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        TRUE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess2_BOARD_InitPeripherals,
        NULL_PTR,
        NULL_PTR,
        PHY_DEVICE_TYPE_SJA1110_100BASE_T1, /* The actual device type name. */
        PHY_TYPE_NO_VARIANT,
        NULL_PTR, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_SJA1110_100BASE_T1,
        FALSE,
        PHY_SPEED_100_MBPS,
        FALSE,
        PHY_ROLE_AUTO,
        PHY_FULL_DUPLEX,
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkUpEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        TRUE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess3_BOARD_InitPeripherals,
        NULL_PTR,
        NULL_PTR,
        PHY_DEVICE_TYPE_SJA1110_100BASE_T1, /* The actual device type name. */
        PHY_TYPE_NO_VARIANT,
        NULL_PTR, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_SJA1110_100BASE_T1,
        FALSE,
        PHY_SPEED_100_MBPS,
        FALSE,
        PHY_ROLE_AUTO,
        PHY_FULL_DUPLEX,
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkUpEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        TRUE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess4_BOARD_InitPeripherals,
        NULL_PTR,
        NULL_PTR,
        PHY_DEVICE_TYPE_SJA1110_100BASE_T1, /* The actual device type name. */
        PHY_TYPE_NO_VARIANT,
        NULL_PTR, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_TJA1121,
        FALSE,
        PHY_SPEED_1_GBPS,
        FALSE,
        PHY_ROLE_MASTER,
        PHY_FULL_DUPLEX,
            {TRUE, PHY_IRQ_DEFAULT_ACTION_NONE, linkUpEventCallback}, /* linkUpEvent */
            {TRUE, PHY_IRQ_DEFAULT_ACTION_NONE, linkDownEventCallback}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        TRUE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess5_BOARD_InitPeripherals,
        NULL_PTR,
        &macSecCfg5_BOARD_InitPeripherals,
        PHY_DEVICE_TYPE_TJA1121, /* The actual device type name, independent of the variant. (A/B) */
        PHY_TYPE_TJA1121A,
        &ptpCfg5_BOARD_InitPeripherals, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
    {
        &PHY_driver_TJA1121,
        FALSE,
        PHY_SPEED_1_GBPS,
        FALSE,
        PHY_ROLE_MASTER,
        PHY_FULL_DUPLEX,
            {TRUE, PHY_IRQ_DEFAULT_ACTION_NONE, linkUpEventCallback}, /* linkUpEvent */
            {TRUE, PHY_IRQ_DEFAULT_ACTION_NONE, linkDownEventCallback}, /* linkDownEvent */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* sleepRequest */
            {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* coldReset */
        NULL_PTR, 
        NULL_PTR, 
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFusaFailed */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqCoreSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddaTrxWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregaSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVregdSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTempWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqOscWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTxcClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEphyClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiLfWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiClkWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqVddioSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqAoSysSupplyWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSqiWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTreeWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqLimitedAccessWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiAutoneg */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoOverflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiFifoUnderflow */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSgmiiSgmiiLinkStatus */
        {
            {
                FALSE,                       /* Not used in current configuration: linkRecoveryTimeout.eventEnabled */
                PHY_IRQ_DEFAULT_ACTION_NONE, /* Not used in current configuration: linkRecoveryTimeout.defaultAction */
                NULL_PTR                     /* Not used in current configuration: linkRecoveryTimeout.eventCB */
            },
            0                            /* Not used in current configuration: linkRecoveryTimeout.timeoutDuration */
        },
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecAdptrErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqMacSecErr */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGlobalWarning */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFramingError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqFcsError */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqIngressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqEgressTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpTopDownReset */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqGptpLtcErrorWarn */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTsLost */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqTrigTs */
        {FALSE, PHY_IRQ_DEFAULT_ACTION_NONE, NULL_PTR}, /* Not used in current configuration: irqSyncTs */
        FALSE,
        TRUE,
        PHY_XMII_MODE_DEFAULT,
        &phyHwAccess6_BOARD_InitPeripherals,
        NULL_PTR,
        &macSecCfg6_BOARD_InitPeripherals,
        PHY_DEVICE_TYPE_TJA1121, /* The actual device type name, independent of the variant. (A/B) */
        PHY_TYPE_TJA1121B,
        &ptpCfg6_BOARD_InitPeripherals, /* Reference to PTP config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        {NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG, NO_CONFIG},
        INVALID_MODE,  /* This feature is not supported for this type of device. */
        NULL_PTR, /* Reference to BIST generator config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
        NULL_PTR, /* Reference to BIST checker config structure for the current PHY. If the value is NULL_PTR, the PTP feature is not supported for this PHY. */
    },
};

Phy_Ip_DriverConfigType EthTrcv_PhyDriverConfig_BOARD_InitPeripherals =
{
  N_PHY_DEVS_BOARD_InitPeripherals,
  EthTrcv_PhyConfig_BOARD_InitPeripherals,
  EthTrcv_PhyState_BOARD_InitPeripherals,
};

#define ETHTRCV_43_PHY_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthTrcv_43_PHY_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

