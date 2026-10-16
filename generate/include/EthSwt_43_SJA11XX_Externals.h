/*==================================================================================================
*   Project            : RTD AUTOSAR 4.4
*   Platform           : N/A
*   Peripheral         : SJA11XX
*   Dependencies       : none
*
*   AutosarVersion     : 4.4.0
*   AutosarRevision    : ASR_REL_4_4_REV_0000
*   AutosarConfVariant :
*   SW Version         : 1.0.2
*   BuildVersion       : SJA11XX_RTD_1_0_2_D2604_ASR_REL_4_4_REV_0000_20260421
*
*   Copyright 2026 NXP Semiconductors
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef ETHSWT_43_SJA11XX_EXTERNALS_H
#define ETHSWT_43_SJA11XX_EXTERNALS_H

/**
*   @file    EthSwt_43_SJA11XX_Externals.h
*   @version 1.0.2
*
*   @brief   AUTOSAR EthSwt_43_SJA11XX - Header for exporting callbacks and callouts of EthSwt driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
*
*   @addtogroup ethswt_driver_cfg
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
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETHSWT_43_SJA11XX_VENDOR_ID_EXTERNALS                    43
#define ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION_EXTERNALS     4
#define ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION_EXTERNALS     4
#define ETHSWT_43_SJA11XX_AR_RELEASE_REVISION_VERSION_EXTERNALS  0
#define ETHSWT_43_SJA11XX_SW_MAJOR_VERSION_EXTERNALS             1
#define ETHSWT_43_SJA11XX_SW_MINOR_VERSION_EXTERNALS             0
#define ETHSWT_43_SJA11XX_SW_PATCH_VERSION_EXTERNALS             2

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Mcal.h header file are of the same Autosar version */
#if ((ETHSWT_43_SJA11XX_AR_RELEASE_MAJOR_VERSION_EXTERNALS != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (ETHSWT_43_SJA11XX_AR_RELEASE_MINOR_VERSION_EXTERNALS != MCAL_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AutoSar Version Numbers of EthSwt_Externals.h and Mcal.h are different"
#endif
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
*                                STRUCTURES AND OTHER TYPES
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

/** @} */

#endif /* ETHSWT_EXTERNALS_H */
