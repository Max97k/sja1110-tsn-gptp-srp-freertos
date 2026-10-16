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

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "gptp_cbk.h"
#include "gptp_err.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
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

bool GPTP_DomainSelectionCB(uint8_t u8DomainNumber, float64_t *pf64RateRatio, gptp_def_timestamp_sig_t *prTime, bool *pbNegativeOfst, int8_t *pi8SyncIntervalLog)
{
    bool bUpdateClock;

    (void)u8DomainNumber;
    (void)*pf64RateRatio;
    (void)*prTime;
    (void)*pbNegativeOfst;
    (void)*pi8SyncIntervalLog;

    bUpdateClock = true;

    /* Place for custom implementation of domain selection */

    return bUpdateClock;
}

void GPTP_ErrorNotifyCB(void) { /* Place for custom implementation of reaction on error notification */ }

void GPTP_SyncNotifyCB(gptp_def_syn_lock_state_type_t eSyncLockState)
{
    /* Place for custom implementation of reaction on error notification. */
    (void)eSyncLockState;
}

/*!
 * @brief           gPTP notification before hard clock adjustment.
 *
 * @details         This function is called before the gPTP stack performs
 *                  a hard 1588 clock adjustment. Any components relying
 *                  on precise synchronized time should prepare for
 *                  the abrupt time change, using this callback.
*/
void GPTP_ClkUpdateNotifyStartCB(void)
{
    GPTP_StopPtpClk();
}

/*!
 * @brief           gPTP notification after hard clock adjustment.
 *
 * @details         This function is called after the gPTP stack has
 *                  performed a hard 1588 clock adjustment.
 *                  Any components relying on precise synchronized
 *                  time should resume normal operation, using
 *                  this callback.
*/
void GPTP_ClkUpdateNotifyFinishCB(void)
{
    GPTP_StartPtpClk();
}

#ifdef __cplusplus
}
#endif
