/*
*   Copyright 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly
*   in accordance with the applicable license terms.  By expressly accepting
*   such terms or by downloading, installing, activating and/or otherwise using
*   the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms.  If you do not agree to
*   be bound by the applicable license terms, then you may not retain,
*   install, activate or otherwise use the software.
*
 */

/*******************************************************************************
 * Guard Begin
 ******************************************************************************/

#ifndef GPTP_PORT_PLATFORM_H
#define GPTP_PORT_PLATFORM_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifdef GPTP_USE_PRINTF
    #include <stdio.h>
    #define GPTP_PORT_PRINTF(x) (void)printf x
#endif

#include "StandardTypes.h"
#include "gptp_def.h"
#include "gptp_err.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Driver instances. */
#define GPTP_PORT_PRIMARY_SWITCH        (0u)

/*******************************************************************************
 * Data Types
 ******************************************************************************/
/* None */

/*******************************************************************************
 * Externs
 ******************************************************************************/
/* None */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief           This function converts a MAC address to uint64.
 *
 * @details         This function converts a MAC address from bytes array to
 *                  an unsigned 64 bit integer.
 *
 *
 * @param[in]       cau8Mac Bytes array containing a MAC address.
 *
 * @return          cau8Mac as unsigned 64 bit integer.
*/
uint64_t GPTP_PORT_MacAddrAsUInt64(const uint8 *cpu8Mac);

/*!
 * @brief           This function processes egress timestamp.
 *
 * @details         This function processes captured egress timestamp.
 *                  Only call this function from EthIf_TxConfirmation.
 *
 * @param[in]       u8CtrlIdx Index of the controller which transmitted
 *                  the frame.
 * @param[in]       u32BufferIndex Index of the transmitted data buffer.
 * @param[in]       eStatus Result.
*/
void GPTP_PORT_TxConfirmation(uint8_t u8CtrlIdx,
                              Eth_BufIdxType u32BufferIndex,
                              Std_ReturnType eStatus);

/*!
 * @brief           This function processes the timestamp of a received frames.
 *
 * @details         This function processes the timestamp of a received frames
 *                  and passes the frame to the stack for furthure processing
 *                  to the upper layer of gPTP stack.
 *
 * @note            The passed data buffer is no longer valid after the function
 *                  is exited.
 *
 * @warning         This is an example implementation of function passing
 *                  received frames with timestamp to the gPTP stack.
 *
 * @param[in]       u8CtrlIdx Index of the controller which received the frame.
 * @param[in]       u16FrameType The received frame Ethertype
 *                  (from the frame header).
 * @param[in]       bIsBroadcast The value TRUE indicates that the received
 *                  frame was sent to broadcast address (ff-ff-ff-ff-ff-ff).
 * @param[in]       cpu8PhysAddr Pointer to received frame source MAC address
 *                  (6 bytes).
 * @param[in]       cpu8Data Data buffer containing the received Ethernet frame
 *                  payload.
 * @param[in]       u16LenByte Length of the data in the buffer cpu8Data.
*/
void GPTP_PORT_RxIndication(uint8 u8CtrlIdx,
                            Eth_FrameType u16FrameType,
                            boolean bIsBroadcast,
                            const uint8 *cpu8PhysAddr,
                            const Eth_DataType *cpu8Data,
                            uint16 u16LenByte);

/*******************************************************************************
 * Guard End
 ******************************************************************************/

#endif /* GPTP_PORT_PLATFORM_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
