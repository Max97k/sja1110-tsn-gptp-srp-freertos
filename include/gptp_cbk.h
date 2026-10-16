/*
 *  Copyright 2025 NXP
 *
 *  NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only
 *  be used strictly in accordance with the applicable license terms. By
 *  expressly accepting such terms or by downloading, installing, activating
 *  and/or otherwise using the software, you are agreeing that you have read,
 *  and that you agree to comply with and are bound by, such license terms. If
 *  you do not agree to be bound by the applicable license terms, then you may
 *  not retain, install, activate or otherwise use the software.
 *
 *  This file contains sample code only. It is not part of the production code deliverables.
 */

#ifndef GPTP_CBK_H
#define GPTP_CBK_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "gptp.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

Std_ReturnType GPTP_StartPtpClk(void);

Std_ReturnType GPTP_StopPtpClk(void);

boolean GPTP_DomainSelectionCB(uint8 u8DomainNumber,
                               float64 *pf64RateRatio,
                               gptp_def_timestamp_sig_t *prTime,
                               boolean *pbNegativeOfst,
                               int8_t *pi8SyncIntervalLog);

uint8 GPTP_NVMWriteCB(uint8 u8PdelayMachine,
                      gptp_def_nvm_data_t eNvmDataType,
                      float64 f64Value,
                      gptp_def_mem_write_stat *peWriteStat);

uint8 GPTP_NVMReadCB(uint8 u8PdelayMachine,
                     gptp_def_nvm_data_t eNvmDataType,
                     float64 *pf64Value);

void GPTP_ErrorNotifyCB(void);

void GPTP_SyncNotifyCB(gptp_def_syn_lock_state_type_t eSyncLockState);

void GPTP_ClkUpdateNotifyStartCB(void);

void GPTP_ClkUpdateNotifyFinishCB(void);

#ifdef __cplusplus
}
#endif

#endif
