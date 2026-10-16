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

#ifndef PHY_IP_CFG_H
#define PHY_IP_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Phy_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PHY_IP_CFG_VENDOR_ID                     43
#define PHY_IP_CFG_AR_RELEASE_MAJOR_VERSION      4
#define PHY_IP_CFG_AR_RELEASE_MINOR_VERSION      4
#define PHY_IP_CFG_AR_RELEASE_REVISION_VERSION   0
#define PHY_IP_CFG_SW_MAJOR_VERSION              1
#define PHY_IP_CFG_SW_MINOR_VERSION              0
#define PHY_IP_CFG_SW_PATCH_VERSION              8

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same vendor */
#if (PHY_IP_CFG_VENDOR_ID != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Phy_Ip_Cfg.h and Phy_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same Autosar version */
#if (( PHY_IP_CFG_AR_RELEASE_MAJOR_VERSION    != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     ( PHY_IP_CFG_AR_RELEASE_MINOR_VERSION    != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     ( PHY_IP_CFG_AR_RELEASE_REVISION_VERSION != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Phy_Ip_Cfg.h and Phy_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if current file and Phy_Ip_BOARD_InitPeripherals_PBcfg header file are of the same Software version */
#if (( PHY_IP_CFG_SW_MAJOR_VERSION != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     ( PHY_IP_CFG_SW_MINOR_VERSION != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     ( PHY_IP_CFG_SW_PATCH_VERSION != PHY_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Phy_Ip_Cfg.h and Phy_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif


/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define PHY_IP_DEV_ERROR_DETECT  (STD_OFF)
#define PHY_TIMEOUT_LOOPS        ((uint32)65535U)
#define PHY_TIMEOUT_METHOD       ((OsIf_CounterType)OSIF_COUNTER_DUMMY)
#define PHY_SANITY_READ_ENABLE   (STD_OFF)

#if (STD_ON == PHY_SANITY_READ_ENABLE)
#define PHY_RETRY_WRITE_ENABLE   (STD_OFF)
#endif

#define PHY_CHECK_ACCESS         (STD_OFF)
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
/*FUNCTION**********************************************************************
 *
 * Function Name : User-defined callback name
 * Description   : User-defined callback functions for interrupts
 * Parameters:
 *   phy The device number, representing the index in the array of PHY configurations.
 *   irqSrc The indicator for the source of interrupt.
 *   alreadyExecutedAction The default action executed(for the events which have dafault action).
 * Return: Returned value is not used in the driver, it is kept to match the prototype of other interrupt callbacks.
 *
 *END**************************************************************************/

extern Phy_Ip_StatusType linkUpEventCallback(uint8 phy, Phy_Ip_IrqSourceType irqSrc, Phy_Ip_IrqDefaultActionType alreadyExecutedAction);
extern Phy_Ip_StatusType linkDownEventCallback(uint8 phy, Phy_Ip_IrqSourceType irqSrc, Phy_Ip_IrqDefaultActionType alreadyExecutedAction);
#ifdef __cplusplus
}
#endif


/** @} */

#endif /* PHY_IP_CFG_H */

