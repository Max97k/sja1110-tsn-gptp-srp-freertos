/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : SJA11XX
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

/*
*   @file
*
*   @addtogroup switch_driver_configuration PORT Driver Configuration
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

#include "Acu_Ip_Register_Access.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ACU_IP_CFG_VENDOR_ID_C                     43
#define ACU_IP_CFG_AR_RELEASE_MAJOR_VERSION_C      4
#define ACU_IP_CFG_AR_RELEASE_MINOR_VERSION_C      4
#define ACU_IP_CFG_AR_RELEASE_REVISION_VERSION_C   0
#define ACU_IP_CFG_SW_MAJOR_VERSION_C              1
#define ACU_IP_CFG_SW_MINOR_VERSION_C              0
#define ACU_IP_CFG_SW_PATCH_VERSION_C              1

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/

/* Check if current file and Acu_Ip_Register_Access header file are of the same vendor */
#if (ACU_IP_CFG_VENDOR_ID_C != ACU_IP_REGISTER_ACCESS_VENDOR_ID)
    #error "Acu_Ip_Cfg.c and Acu_Ip_Register_Access.h have different vendor ids"
#endif
/* Check if current file and Acu_Ip_Register_Access header file are of the same Autosar version */
#if (( ACU_IP_CFG_AR_RELEASE_MAJOR_VERSION_C    != ACU_IP_REGISTER_ACCESS_AR_RELEASE_MAJOR_VERSION) || \
     ( ACU_IP_CFG_AR_RELEASE_MINOR_VERSION_C    != ACU_IP_REGISTER_ACCESS_AR_RELEASE_MINOR_VERSION) || \
     ( ACU_IP_CFG_AR_RELEASE_REVISION_VERSION_C != ACU_IP_REGISTER_ACCESS_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Acu_Ip_Cfg.c and Acu_Ip_Register_Access.h are different"
#endif
/* Check if current file and Acu_Ip_Register_Access header file are of the same Software version */
#if (( ACU_IP_CFG_SW_MAJOR_VERSION_C != ACU_IP_REGISTER_ACCESS_SW_MAJOR_VERSION) || \
     ( ACU_IP_CFG_SW_MINOR_VERSION_C != ACU_IP_REGISTER_ACCESS_SW_MINOR_VERSION) || \
     ( ACU_IP_CFG_SW_PATCH_VERSION_C != ACU_IP_REGISTER_ACCESS_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Acu_Ip_Cfg.c and Acu_Ip_Register_Access.h are different"
#endif

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
                                       GLOBAL CONSTANTS
==================================================================================================*/
const Acu_Ip_HwAccessType g_acuHwConfig[1] =
{
    {
        Acu_Ip_InternalWrite,
        Acu_Ip_InternalRead,
    },
};
/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

