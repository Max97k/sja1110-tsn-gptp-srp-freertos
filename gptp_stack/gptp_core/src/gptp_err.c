/*
 * Copyright 2019-2025 NXP
 *
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

/**
 * @file gptp_err.c
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "gptp_def.h"
#include "gptp_err.h"
#include "gptp_port.h"
#include "gptp_internal.h"

#if (GPTP_USE_PRINTF == STD_ON)
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define GPTP_ERR_DBG_MSG_MAX_LEN         80u

#endif /* (GPTP_USE_PRINTF == STD_ON) */

/*******************************************************************************
 * Data types
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static gptp_err_error_t         rErrorLog[GPTP_ERR_LOG_LENGTH];
static gptp_err_notify_t        pfErrorNotify = NULL;

#if (GPTP_USE_PRINTF == STD_ON)
static const char *scap8GptpErrDescription[GPTP_ERR_NUMBER_OF_ERRS] =
{
    "No error", 
    "gPTP stack not initialized", 
    "Count of initialized gPTP ports is zero", 
    "Count of initialized Domains is zero", 
    "Too many Sync slaves under one domain", 
    "Too many Sync state machines under the domain (not enough gPTP ports)", 
    "No Slave machine for non Grand Master domain", 
    "Slave Sync state machine initialized for Grand Master domain", 
    "Pdelay initiator not enabled for the slave sync machine", 
    "Start-up time-out for Bridge is too long", 
    "Source port MAC address not available", 
    "Unable to get link status", 
    "Pointer to gPTP counters is NULL", 
    "Pointer to port mapping structure is NULL", 
    "Port initialization contains duplicate port assignment", 
    "Pointer to port structure is NULL", 
    "Pointer to Domain structure is NULL", 
    "Pointer to Pdelay structure is NULL", 
    "Pointer to Sync structure under the Domain is NULL", 
    "Pdelay interval out of range", 
    "Sync interval out of range", 
    "Initialized Synchronized Grand Master on non Grand Master domain", 
    "The same domain number used twice", 
    "Reference domain for synced GM is not initialized", 
    "Number of clock instances is zero", 
    "Division by zero attempt", 
    "Times stamp is incorrect to perform the calculation", 
    "The time stamp is not registered", 
    "Unexpected time stamp received on the port", 
    "Incorrect Sync domain index (out of range)", 
    "Incorrect Sync machine index (out of range)", 
    "Incorrect Pdelay machine index (out of range)", 
    "Incorrect frame id received for time-stamp handler", 
    "Double reception of the Pdelay response", 
    "Unknown message type received", 
    "The time stamp doesn't match with send message", 
    "Transport specific byte is not 1", 
    "Sync message received on master sync machine", 
    "Follow Up message received on master sync machine", 
    "Sync message received on Grand Master domain", 
    "Follow Up message received on Grand Master domain", 
    "Sync message received for unknown domain", 
    "Sync message received for unknown Sync machine", 
    "Pdelay message received for unknown Pdelay machine", 
    "Pointer to TX buffer is null", 
    "No ETH type PTP in the incoming frame", 
    "No ETH type VLAN in the incoming frame", 
    "Unable to read data from NVM", 
    "Unable to write data to the NVM", 
    "Lost Pdelay responses exceeded count of allowed lost responses", 
    "Path delay exceed threshold value", 
    "Rate ratio exceed threshold value", 
    "Missing or incorrect configuration for PI Controller", 
    "Lost GM, no incoming Sync messages", 
    "State machine state error", 
    "Incorrect Time stamp for the follow-up message", 
    "Sync receipt time-out exceeded", 
    "Residence time is too long", 
    "Turnaround time is too long on the Pdelay initiator - other side responds late", 
    "Turnaround time is too long on the Pdelay responder - the stack responds late", 
    "Pointer to function is null", 
    "Function for reading time error", 
    "Function for sending ptp frame error", 
    "Function for updating ptp results error", 
    "Unknown domain number used in API call", 
    "Illegal machine ID used in API call", 
    "Illegal port number used in API call", 
    "Illegal counter used in API call", 
    "Pointer to variable is null", 
    "Array index out of range",
    "Grand Master failure", 
    "Reading of the error log with illegal index"
};
#endif /* (GPTP_USE_PRINTF == STD_ON) */
        
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void GPTP_ERR_LogMessage(uint8_t u8Port,
                                uint8_t u8Domain,
                                gptp_err_type_t eError,
                                uint16_t u16SeqId);

/*******************************************************************************
 * Local Functions
 ******************************************************************************/
/*!
 * @brief The function sweep and write error into log.
 * 
 * @ requirements 2081146
 * @ requirements 2081276
 */
static void GPTP_ERR_LogMessage(uint8_t u8Port,
                                uint8_t u8Domain,
                                gptp_err_type_t eError,
                                uint16_t u16SeqId)
{
    uint16_t    u16Sweep;

    for (u16Sweep = GPTP_ERR_LOG_LENGTH - 1u; u16Sweep >= 1u; u16Sweep--)
    {
        rErrorLog[u16Sweep] = rErrorLog[(u16Sweep - 1u)];
    }
    rErrorLog[0u].eErrorType = eError;
    rErrorLog[0u].u8RespGptpPortIndex = u8Port;
    rErrorLog[0u].u8RespGptpDomainIndex = u8Domain;
    rErrorLog[0u].rLogTime = GPTP_PORT_CurrentTimeGet(GPTP_DEF_TS_CORRECTED);
    rErrorLog[0u].u16RespMsgSeqId = u16SeqId;
    rErrorLog[0u].bFreshLog = true;
}

/*******************************************************************************
 * Code
 ******************************************************************************/
 /*!
 * @brief The function initializes error management.
 *
 * The function initializes error detail text for console print (if preprocessor 
 * enabled) and initializes error notification callback function pointer.
 *
 * @ requirements 2081146
 * @ requirements 2081273
 */
void GPTP_ERR_MgmtInit(const gptp_def_data_t *prGptp)
{
    pfErrorNotify = prGptp->rPtpStackCallBacks.pfErrNotify;
}

/*!
 * @brief The function clears error log.
 *
 * The function clears error log of the gPTP stack
 *
 * @ requirements 2081146
 * @ requirements 2081274
 */
void GPTP_ERR_LogClear(void)
{
    uint16_t u16Sweep;

    for (u16Sweep = 0u; u16Sweep < GPTP_ERR_LOG_LENGTH; u16Sweep++)
    {
        rErrorLog[u16Sweep].eErrorType = GPTP_ERR_OK;
        rErrorLog[u16Sweep].u8RespGptpPortIndex = (uint8_t)0xFFu;
        rErrorLog[u16Sweep].u8RespGptpDomainIndex = (uint8_t)0xFFu;
        rErrorLog[u16Sweep].rLogTime.u64TimeStampS = 0u;
        rErrorLog[u16Sweep].rLogTime.u32TimeStampNs = 0u;
        rErrorLog[u16Sweep].u16RespMsgSeqId = 0u;
        rErrorLog[u16Sweep].bFreshLog = false;
    }
}

/*!
 * @brief The function writes error log.
 *
 * The function writes error into the error log. The fresh log is written to the index 0.
 * Previous logs are shifted towards the end of the log.
 *
 * @param[in] Port information - on which port the error occurred (if applicable).
 * @param[in] Domain information - on which domain the error occured (if applicable).
 * @param[in] Error type to be logged.
 * @param[in] Sequence ID of PTP message which caused error (if applicable).
 *
 * @ requirements 2081146
 * @ requirements 2081275
 */
void GPTP_ERR_Register(uint8_t u8Port,
                       uint8_t u8Domain,
                       gptp_err_type_t eError,
                       uint16_t u16SeqId)
{
    GPTP_ERR_LogMessage(u8Port, u8Domain, eError, u16SeqId);

#if (GPTP_USE_PRINTF == STD_ON)
    if ((uint16_t)GPTP_ERR_NUMBER_OF_ERRS > (uint16_t)eError)
    {
        GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, ("gptp: Error ID %d: %s", eError, scap8GptpErrDescription[(uint16_t)eError]));
        if ((u8Port != GPTP_ERR_PORT_NOT_SPECIF) || (u8Domain != GPTP_ERR_DOMAIN_NOT_SPECIF))
        {
            GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, (" on"));
            if (u8Port != GPTP_ERR_PORT_NOT_SPECIF)
            {
                GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, (" port index %u", u8Port));
            }
            if (u8Domain != GPTP_ERR_DOMAIN_NOT_SPECIF)
            {
                GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, (" domain index: %u", u8Domain));
            }
        }

        if (u16SeqId != GPTP_ERR_SEQ_ID_NOT_SPECIF)
        {
            GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, (", Sequence ID: %u", u16SeqId));
        }
        GPTP_PRINTF(GPTP_DEBUG_MSGTYPE_ERROR, (", Time:"));
        GPTP_PRINTF_TIME_UNSIG(GPTP_DEBUG_MSGTYPE_ERROR, rErrorLog[0u].rLogTime);
    }
    else
    {
        GPTP_ERR_LogMessage(GPTP_ERR_PORT_NOT_SPECIF, GPTP_ERR_DOMAIN_NOT_SPECIF, GPTP_ERR_V_OUT_OF_RANGE, GPTP_ERR_SEQ_ID_NOT_SPECIF);
    }
#endif /* (GPTP_USE_PRINTF == STD_ON) */

    if (NULL != pfErrorNotify)
    {
        pfErrorNotify();
    }
}

/*!
 * @brief The function reads error log.
 *
 * The function reads error from the error log on the specified index.
 *
 * @param[in] Error log index which will be read.
 * @return  Error details read from the log.
 *
 * @ requirements 2081146
 * @ requirements 2081276
 */
gptp_err_error_t GPTP_ERR_ReadIndex(uint16_t u16ErrIndex)
{
    gptp_err_error_t eError;

    if (GPTP_ERR_LOG_LENGTH > u16ErrIndex)
    {
        eError = rErrorLog[u16ErrIndex];
        rErrorLog[u16ErrIndex].bFreshLog = false;
    }

    else
    {
        eError.eErrorType = GPTP_ERR_E_READ_INDEX_TOO_HIGH;
        eError.u8RespGptpPortIndex = (uint8_t)0xFFu;
        eError.u8RespGptpDomainIndex = (uint8_t)0xFFu;
        eError.rLogTime.u64TimeStampS = 0u;
        eError.rLogTime.u32TimeStampNs = 0u;
        eError.u16RespMsgSeqId = 0u;
        eError.bFreshLog = false;
    }

    return eError;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
