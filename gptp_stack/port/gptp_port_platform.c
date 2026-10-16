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

/**
 * @file gptp_port_platform.c
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "StandardTypes.h"
#include "Switch_Ip_Mgmt.h"
#include "Eth.h"
#include "EthSwt_43_SJA11XX.h"
#include "gptp_def.h"
#include "gptp_port_platform.h"
#include "gptp_port.h"
#include "gptp.h"
#include "gptp_err.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* None */

/*******************************************************************************
 * Data types
 ******************************************************************************/
/* None */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* None */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* None */

/*******************************************************************************
 * Code
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
uint64_t GPTP_PORT_MacAddrAsUInt64(const uint8 *cpu8Mac)
{
    return (uint64_t)((((uint64_t)cpu8Mac[0]) << 40u) | \
                      (((uint64_t)cpu8Mac[1]) << 32u) | \
                      (((uint64_t)cpu8Mac[2]) << 24u) | \
                      (((uint64_t)cpu8Mac[3]) << 16u) | \
                      (((uint64_t)cpu8Mac[4]) << 8u)  | \
                      ((uint64_t)cpu8Mac[5]));
}

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
 * 
 * @ requirements 2081146
 * @ requirements 2081335
*/
void GPTP_PORT_TxConfirmation(uint8_t u8CtrlIdx,
                              Eth_BufIdxType u32BufferIndex,
                              Std_ReturnType eStatus)
{
    (void)u8CtrlIdx;
    (void)u32BufferIndex;
    (void)eStatus;

    /* Nothing to be done here.
       Timestamp handling done in GPTP_PORT_ProcessMapEntry, because egress
       timestamp is received in Rx part. */
}

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
 *
 * @ requirements 2081146
 * @ requirements 2081334
*/
void GPTP_PORT_RxIndication(uint8 u8CtrlIdx,
                            Eth_FrameType u16FrameType,
                            boolean bIsBroadcast,
                            const uint8 *cpu8PhysAddr,
                            const Eth_DataType *cpu8Data,
                            uint16 u16LenByte)
{
    (void)cpu8PhysAddr;
    (void)bIsBroadcast;
    (void)u16LenByte;
    
    static uint8_t          su8PtpPort;
    gptp_def_rx_data_t      rRxData;
    EthSwt_MgmtObjectType   *prRxMgmt;
    uint64_t                u64MacAddress;
    Eth_DataType            *pu8Data;

    su8PtpPort = 0u;
    prRxMgmt = NULL;

    pu8Data = (Eth_DataType *)cpu8Data;

    if ((Std_ReturnType)E_OK == EthSwt_43_SJA11XX_GetRxMgmtObject(u8CtrlIdx, 
                                                                  pu8Data, 
                                                                  &prRxMgmt))
    {
        if ((Std_ReturnType)E_OK == prRxMgmt->Validation.IngressTimestampValid)
        {
            rRxData.u32TsSec = (uint32_t)prRxMgmt->IngressTimestamp.seconds;
            rRxData.u32TsNsec = (uint32_t)prRxMgmt->IngressTimestamp.nanoseconds;
        }
        else
        {
            /* No timestamp available, or error occured during the timestamp
               query. */
            rRxData.u32TsSec = 0u;
            rRxData.u32TsNsec = 0u;
        }
        if ((Std_ReturnType)E_OK == prRxMgmt->Validation.MgmtInfoValid)
        {
            if (GPTP_ERR_OK == GPTP_PORT_PortLookup(&su8PtpPort, 
                                                   prRxMgmt->MgmtInfo.SwitchPortIdx,
                                                   prRxMgmt->MgmtInfo.SwitchIdx))
            {
                rRxData.u8PtpPort = su8PtpPort;
                rRxData.cpu8RxData = cpu8Data;
                rRxData.u16EthType = (uint16_t)u16FrameType;

                u64MacAddress = GPTP_PORT_MacAddrAsUInt64(cpu8PhysAddr);
                rRxData.u64SourceMac = u64MacAddress;

                GPTP_MsgReceive(rRxData);
            }
        }
        prRxMgmt->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
