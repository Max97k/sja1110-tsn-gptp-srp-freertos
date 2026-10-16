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

/**
*   @file Fls_BOARD_InitPeripherals_PBcfg.c
*
*   @addtogroup FLS
*   @implements Fls_PBcfg.c_Artifact
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
#include "Fls.h"
#include "Qspi_Ip_Features.h"
#include "Qspi_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_CFG_C                      43
#define FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C       4
#define FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C    0
#define FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_CFG_C               1
#define FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_CFG_C               0
#define FLS_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_CFG_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls header file are of the same vendor */
#if (FLS_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_CFG_C != FLS_VENDOR_ID)
    #error "Fls_BOARD_InitPeripherals_PBcfg.c and Fls.h have different vendor ids"
#endif
/* Check if current file and Fls header file are of the same Autosar version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != FLS_AR_RELEASE_MINOR_VERSION) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != FLS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Fls.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_CFG_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_CFG_C != FLS_SW_MINOR_VERSION) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_CFG_C != FLS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Fls.h are different"
#endif

/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (FLS_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_CFG_C != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_CFG_C != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Features.h are different"
#endif

/* Check if current file and Qspi_Ip_Cfg header file are of the same vendor */
#if (FLS_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_CFG_C != QSPI_IP_VENDOR_ID_CFG)
    #error "Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Autosar version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_CFG_C    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_CFG_C    != QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_CFG_C != QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Cfg.h are different"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Software version */
#if ((FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_CFG_C != QSPI_IP_SW_MAJOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_CFG_C != QSPI_IP_SW_MINOR_VERSION_CFG) || \
     (FLS_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_CFG_C != QSPI_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Fls_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_Cfg.h are different"
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


#define FLS_START_SEC_CONFIG_DATA_8
#include "Fls_MemMap.h"

/* aFlsSectorFlags */
static const uint8 FlsConfigSet_BOARD_InitPeripherals_aFlsSectorFlags[2U] =
{
    0U,  /* FlsSector_0 */
    0U   /* FlsSector_1 */
};

#define FLS_STOP_SEC_CONFIG_DATA_8
#include "Fls_MemMap.h"



#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/* aFlsSectorEndAddr */
static const Fls_AddressType FlsConfigSet_BOARD_InitPeripherals_aFlsSectorEndAddr[2U] =
{
    (Fls_AddressType)4095U,  /* FlsSector_0 */
    (Fls_AddressType)8191U   /* FlsSector_1 */
};

/* paSectorSize */
static const Fls_LengthType FlsConfigSet_BOARD_InitPeripherals_aFlsSectorSize[2U] =
{
    (Fls_LengthType)4096U,  /* FlsSector_0 */
    (Fls_LengthType)4096U   /* FlsSector_1 */
};

/* paSectorPageSize */
static const Fls_LengthType FlsConfigSet_BOARD_InitPeripherals_aFlsSectorPageSize[2U] =
{
    (Fls_LengthType)16U,  /* FlsSector_0 */
    (Fls_LengthType)16U   /* FlsSector_1 */
};


/* paHwCh */
static const Fls_HwChType FlsConfigSet_BOARD_InitPeripherals_paHwCh[2U] =
{
    FLS_CH_QSPI,  /* FlsSector_0 */
    FLS_CH_QSPI   /* FlsSector_1 */
};

/* paSectorHwAddress */
static const Fls_AddressType FlsConfigSet_BOARD_InitPeripherals_paSectorHwAddress[2U] =
{
    (Fls_AddressType)1028096U,  /* FlsSector_0 */
    (Fls_AddressType)1032192U   /* FlsSector_1 */
};

/* External QSPI flash parameters. */

/* u8SectFlashUnit */
static const uint8 FlsConfigSet_BOARD_InitPeripherals_u8SectFlashUnit[2U] =
{
    (uint8)0U,                                                       /* FlsSector_0 */
    (uint8)0U                                                        /* FlsSector_1 */
};

/* u8QspiInstance */
static const uint8 FlsConfigSet_BOARD_InitPeripherals_u8QspiInstance[1U] =
{
    0U
};

/* u8QspiConfig */
static const uint8 FlsConfigSet_BOARD_InitPeripherals_u8QspiConfig[1U] =
{
    0U
};

/* u8FlashConfig */
static const uint8 FlsConfigSet_BOARD_InitPeripherals_u8FlashConfig[1U] =
{
    0xFFU   /* uses SFDP */
};

/* paAHBReadCfg */
static const boolean FlsConfigSet_BOARD_InitPeripherals_paAHBReadCfg[1U] =
{
    (boolean)TRUE
};

/* pFlsQspiCfgConfig */
static const Fls_QspiCfgConfigType Fls_QspiConfigSet_BOARD_InitPeripherals =
{
    &FlsConfigSet_BOARD_InitPeripherals_u8SectFlashUnit,             /* (*u8SectFlashUnit)[] */
    1U,                                                              /* u8FlashUnitsCount */
    &FlsConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg,        /* (*paFlashConnectionCfg)[] */
    &FlsConfigSet_BOARD_InitPeripherals_u8FlashConfig,               /* (*u8FlashConfig)[] */
    &FlsConfigSet_BOARD_InitPeripherals_paAHBReadCfg,                /* (*paAHBReadCfg)[] */
    1U,                                                              /* u8FlashConfigCount */
    &FlsConfigSet_BOARD_InitPeripherals_paFlashCfg,                  /* (*paFlashCfg)[] */
    1U,                                                              /* u8QspiUnitsCount */
    &FlsConfigSet_BOARD_InitPeripherals_u8QspiInstance,              /* (*u8QspiInstance)[] */
    &FlsConfigSet_BOARD_InitPeripherals_u8QspiConfig,                /* (*u8QspiConfig)[] */
    1U,                                                              /* u8QspiConfigCount */
    &FlsConfigSet_BOARD_InitPeripherals_paQspiUnitCfg                /* (*paQspiUnitCfg)[] */
};


/**
* @brief        Structure used to set function pointers notification, working mode
*/
/* Fls module initialization data (FlsConfigSet)*/
const Fls_ConfigType Fls_Config_BOARD_InitPeripherals =
{
    NULL_PTR,                                                        /* FlsJobEndNotification */
    NULL_PTR,                                                        /* FlsJobErrorNotification */
    MEMIF_MODE_SLOW,                                                 /* FlsDefaultMode */
    1024U,                                                           /* FlsMaxReadFastMode */
    512U,                                                            /* FlsMaxReadNormalMode */
    1024U,                                                           /* FlsMaxWriteFastMode */
    320U,                                                            /* FlsMaxWriteNormalMode */
    2U,                                                              /* FlsSectorCount */
    &FlsConfigSet_BOARD_InitPeripherals_aFlsSectorEndAddr,           /* (*paSectorEndAddr)[] */
    &FlsConfigSet_BOARD_InitPeripherals_aFlsSectorSize,              /* (*paSectorSize)[] */
    &FlsConfigSet_BOARD_InitPeripherals_aFlsSectorFlags,             /* (*paSectorFlags)[] */
    &FlsConfigSet_BOARD_InitPeripherals_aFlsSectorPageSize,          /* (*paSectorPageSize)[] */
    &FlsConfigSet_BOARD_InitPeripherals_paHwCh,                      /* (*paHwCh)[] */
    &FlsConfigSet_BOARD_InitPeripherals_paSectorHwAddress,           /* (*paSectorHwAddress)[] */
    &Fls_QspiConfigSet_BOARD_InitPeripherals,                        /* FlsQspiConfig */
#if (STD_ON == FLS_CHECK_CFG_CRC)
    61850U                                                           /* configCrc */
#endif
};


#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @}*/

