/**
*   @file    EthTrcv_43_PHY_Externals.h
*   @version 1.0.8
*
*   @brief   AUTOSAR EthTrcv_43_PHY - Header for exporting callbacks and callouts of EthTrcv driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
*
*   @addtogroup EthTrcv
*   @{
*/
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

#ifndef ETHTRCV_43_PHY_EXTERNALS_H
#define ETHTRCV_43_PHY_EXTERNALS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "EthTrcv_43_PHY_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* Inclusion of incompatible header files shall be avoided */

#define ETHTRCV_43_PHY_VENDOR_ID_EXTERNALS                    43

#define ETHTRCV_43_PHY_MODULE_ID_EXTERNALS                    73
#define ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_EXTERNALS     4
#define ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_EXTERNALS     4
#define ETHTRCV_43_PHY_AR_RELEASE_REVISION_VERSION_EXTERNALS  0

#define ETHTRCV_43_PHY_SW_MAJOR_VERSION_EXTERNALS             1
#define ETHTRCV_43_PHY_SW_MINOR_VERSION_EXTERNALS             0
#define ETHTRCV_43_PHY_SW_PATCH_VERSION_EXTERNALS             8
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_EXTERNALS != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_EXTERNALS != MCAL_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AutoSar Version Numbers of EthTrcv_Externals.h and Mcal.h are different"
#endif
#endif

/* Check if current file and EthTrcv_Cfg header file are of the same vendor */
#if (ETHTRCV_43_PHY_VENDOR_ID_EXTERNALS != ETHTRCV_43_PHY_VENDOR_ID_CFG)
    #error "EthTrcv.h and EthTrcv_Cfg.h have different vendor ids"
#endif
/* Check if current file and EthTrcv_Cfg header file are of the same Autosar version */
#if ((ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_EXTERNALS    != ETHTRCV_43_PHY_AR_RELEASE_MAJOR_VERSION_CFG) ||    \
     (ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_EXTERNALS    != ETHTRCV_43_PHY_AR_RELEASE_MINOR_VERSION_CFG) ||    \
     (ETHTRCV_43_PHY_AR_RELEASE_REVISION_VERSION_EXTERNALS != ETHTRCV_43_PHY_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of EthTrcv.h and EthTrcv_Cfg.h are different"
#endif
/* Check if current file and EthTrcv_Cfg header file are of the same Software version */
#if ((ETHTRCV_43_PHY_SW_MAJOR_VERSION_EXTERNALS != ETHTRCV_43_PHY_SW_MAJOR_VERSION_CFG) || \
     (ETHTRCV_43_PHY_SW_MINOR_VERSION_EXTERNALS != ETHTRCV_43_PHY_SW_MINOR_VERSION_CFG) || \
     (ETHTRCV_43_PHY_SW_PATCH_VERSION_EXTERNALS != ETHTRCV_43_PHY_SW_PATCH_VERSION_CFG)    \
    )
    #error "Software Version Numbers of EthTrcv.h and EthTrcv_Cfg.h are different"
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* ETHTRCV_EXTERNALS_H */

