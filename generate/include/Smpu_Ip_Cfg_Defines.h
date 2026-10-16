/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
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

#ifndef SMPU_IP_CFG_DEFINES_H
#define SMPU_IP_CFG_DEFINES_H

/**
*   @file Smpu_Ip_Cfg_Defines.h
*
*   @addtogroup Smpu_Ip Smpu IPV Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "StandardTypes.h"
#include "SJA1110.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_VENDOR_ID                    43
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     4
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_SW_MAJOR_VERSION             1
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_SW_MINOR_VERSION             0
#define CDD_PLATFORM_SMPU_IP_CFG_DEFINES_SW_PATCH_VERSION             1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /*  Check if current file and StandardTypes.h header file are of the same Autosar version */
    #if ((CDD_PLATFORM_SMPU_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_SMPU_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Autosar Version Numbers of Smpu_Ip_CfgDefines.h and StandardTypes.h are different"
    #endif
#endif

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/** @brief    Smpu Instances */
#define SMPU_INSTANCE0                      (0U)
#define SMPU_INSTANCE1                      (1U)

/** @brief    Define enable/disable Smpu */
#define PLATFORM_IP_ENABLE_SMPU                   (STD_ON)
/** @brief    Development error checking */
#define SMPU_IP_DEV_ERROR_DETECT            (STD_ON)

/** @brief    All Master Number in SMPU instance 0 */
#define SMPU_IP_INSTANCE0_MASTER_COUNT      (5U)

/** @brief    All Master Number in SMPU instance 1 */
#define SMPU_IP_INSTANCE1_MASTER_COUNT      (7U)

/** @brief    Enumeration listing specifies total number of bus master in SMPU instance 0 and SMPU instance 1 bus master */
#define SMPU_IP_INSTANCE_MASTER_COUNT       {SMPU_IP_INSTANCE0_MASTER_COUNT, SMPU_IP_INSTANCE1_MASTER_COUNT}

/** @brief    All Master Count Support */
#define SMPU_IP_MASTER_COUNT_SUPPORT_MAX    (7U)

/** @brief    List Master support */
#define SMPU_IP_MASTER_SUPPORT              {                                      \
                                                SMPU_MASTER_CORE,     /* CORE   */ \
                                                SMPU_MASTER_DEBUG,    /* DEBUG  */ \
                                                SMPU_MASTER_DMA,      /* DMA    */ \
                                                SMPU_MASTER_ENET,     /* ENET   */ \
                                                SMPU_MASTER_CAAM,     /* CAAM   */ \
                                                SMPU_MASTER_SPIHAP,   /* SPIHAP */ \
                                                SMPU_MASTER_CCC       /* CCC    */ \
                                            }

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SMPU_IP_CFG_DEFINES_H */

