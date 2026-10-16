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

#ifndef FLS_CFG_DEFINES_H
#define FLS_CFG_DEFINES_H

/**
*   @file Fls_Cfg_Defines.h
*
*   @addtogroup FLS
*   @implements Fls_Cfg_Defines.h_Artifact
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


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_CFG_DEFINES                    43
#define FLS_AR_RELEASE_MAJOR_VERSION_CFG_DEFINES     4
#define FLS_AR_RELEASE_MINOR_VERSION_CFG_DEFINES     4
#define FLS_AR_RELEASE_REVISION_VERSION_CFG_DEFINES  0
#define FLS_SW_MAJOR_VERSION_CFG_DEFINES             1
#define FLS_SW_MINOR_VERSION_CFG_DEFINES             0
#define FLS_SW_PATCH_VERSION_CFG_DEFINES             1

/*==================================================================================================
*                                    FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/* Enable calculates CRC for items of Fls Configuration */
#define FLS_CHECK_CFG_CRC                    (STD_OFF)

/* Compile switch to enable and disable the Fls_Cancel function */
#define FLS_CANCEL_API                       (STD_ON)

/* Compile switch to enable and disable the Fls_Compare function */
#define FLS_COMPARE_API                      (STD_ON)

/* Compile switch to enable and disable the Fls_BlankCheck function */
#define FLS_BLANK_CHECK_API                  (STD_ON)

/* Pre-processor switch to enable and disable development error detection */
#define FLS_DEV_ERROR_DETECT                 (STD_ON)

/* Compile switch to enable and disable the Fls_GetJobResult function */
#define FLS_GET_JOB_RESULT_API               (STD_ON)

/* Compile switch to enable and disable the Fls_GetStatus function */
#define FLS_GET_STATUS_API                   (STD_ON)

/* Compile switch to enable and disable the Fls_SetMode function */
#define FLS_SET_MODE_API                     (STD_ON)

/* Pre-processor switch to enable / disable the API to read out the modules version information */
#define FLS_VERSION_INFO_API                 (STD_ON)

/* Pre-processor switch to enable / disable the erase blank check */
#define FLS_ERASE_VERIFICATION_ENABLED       (STD_ON)

/* Pre-processor switch to enable / disable the write verify check */
#define FLS_WRITE_VERIFICATION_ENABLED       (STD_ON)

#if (FLS_ERASE_VERIFICATION_ENABLED == STD_ON)
    /* The maximum number of bytes to blank check in one cycle of the flash driver job processing function */
    #define FLS_MAX_ERASE_BLANK_CHECK        (256U)
#endif

/* Timeout handling enabled */
#define FLS_TIMEOUT_SUPERVISION_ENABLED      (STD_ON)

/* Timeout value for Erase and Write operation - QSPI flash operations. */
#define FLS_QSPI_SYNC_WRITE_TIMEOUT          (2147483647U)
#define FLS_QSPI_SYNC_ERASE_TIMEOUT          (2147483647U)
#define FLS_QSPI_ASYNC_WRITE_TIMEOUT         (2147483647U)
#define FLS_QSPI_ASYNC_ERASE_TIMEOUT         (2147483647U)




/* External QSPI sectors are present or not in the current configuration. */
#define FLS_QSPI_SECTORS_CONFIGURED          (STD_ON)

/* Enable the hang recovery feature for the external QuadSPI controller. */
#define FLS_QSPI_HANG_RECOVERY               (STD_OFF)


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL CONSTANT DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif    /* FLS_CFG_DEFINES_H */


