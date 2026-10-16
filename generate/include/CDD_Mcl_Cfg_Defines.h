/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : DMA
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
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef CDD_MCL_CFG_DEFINES_H_
#define CDD_MCL_CFG_DEFINES_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Dma_Ip_Cfg_Defines.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_MCL_CFG_DEFINES_VENDOR_ID                       43
#define CDD_MCL_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define CDD_MCL_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        4
#define CDD_MCL_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define CDD_MCL_CFG_DEFINES_SW_MAJOR_VERSION                1
#define CDD_MCL_CFG_DEFINES_SW_MINOR_VERSION                0
#define CDD_MCL_CFG_DEFINES_SW_PATCH_VERSION                1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if header file and Dma_Ip_Cfg_Defines.h file are of the same vendor */
#if (CDD_MCL_CFG_DEFINES_VENDOR_ID != DMA_IP_CFG_DEFINES_VENDOR_ID)
    #error "CDD_Mcl_Cfg_Defines.h and Dma_Ip_Cfg_Defines.h have different vendor ids"
#endif

/* Check if header file and Dma_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((CDD_MCL_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION != DMA_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_MCL_CFG_DEFINES_AR_RELEASE_MINOR_VERSION != DMA_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_MCL_CFG_DEFINES_AR_RELEASE_REVISION_VERSION != DMA_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of CDD_Mcl_Cfg_Defines.h and Dma_Ip_Cfg_Defines.h are different"
#endif

/* Check if header file and Dma_Ip_Cfg_Defines.h file are of the same Software version */
#if ((CDD_MCL_CFG_DEFINES_SW_MAJOR_VERSION != DMA_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_MCL_CFG_DEFINES_SW_MINOR_VERSION != DMA_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_MCL_CFG_DEFINES_SW_PATCH_VERSION != DMA_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Mcl_Cfg_Defines.h and Dma_Ip_Cfg_Defines.h are different"
#endif

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/*-----------------------------------------------/
/  DMA                                           /
/-----------------------------------------------*/
#define MCL_DMA_IS_AVAILABLE                       DMA_IP_IS_AVAILABLE

/*-----------------------------------------------/
/  CACHE                                         /
/-----------------------------------------------*/
#define MCL_CACHE_IS_AVAILABLE                     STD_OFF

/*-----------------------------------------------/
/  TRGMUX                                        /
/-----------------------------------------------*/
#define MCL_TRGMUX_IS_AVAILABLE                    STD_OFF

/*-----------------------------------------------/
/  EMIOS                                         /
/-----------------------------------------------*/
#define MCL_EMIOS_IS_AVAILABLE                     STD_OFF

/*-----------------------------------------------/
/  ETIMER                                        /
/-----------------------------------------------*/
#define MCL_ETIMER_IS_AVAILABLE                    STD_OFF

/*-----------------------------------------------/
/  LCU                                           /
/-----------------------------------------------*/
#define MCL_LCU_IS_AVAILABLE                       STD_OFF

/*-----------------------------------------------/
/  FLEXIO                                        /
/-----------------------------------------------*/
#define MCL_FLEXIO_IS_AVAILABLE                    STD_OFF

/*-----------------------------------------------/
/  FTM                                           /
/-----------------------------------------------*/
#define MCL_COMMON_TIMEBASE_IS_AVAILABLE           STD_OFF

/*-----------------------------------------------/
/  LLC                                           /
/-----------------------------------------------*/
#define MCL_LLC_IS_AVAILABLE                       STD_OFF

/*-----------------------------------------------/
/  SPFU                                          /
/-----------------------------------------------*/
#define MCL_SPFU_IS_AVAILABLE                      STD_OFF

/*-----------------------------------------------/
/  MULTICORE                                     /
/-----------------------------------------------*/
#define MCL_MULTICORE_IS_AVAILABLE                 STD_OFF

/*-----------------------------------------------/
/  VERSION INFO API                              /
/-----------------------------------------------*/
#define MCL_VERSION_INFO_API_IS_AVAILABLE          STD_OFF

#ifdef __cplusplus
}
#endif

#endif /* CDD_MCL_CFG_DEFINES_H */

