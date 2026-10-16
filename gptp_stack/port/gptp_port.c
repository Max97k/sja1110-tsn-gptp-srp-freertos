/*
*   Copyright 2024-2025 NXP
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
 * @file gptp_port.c
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "EthSwt_43_SJA11XX.h"
#include "StandardTypes.h"
#include "Switch_Ip_Mgmt.h"
#include "Eth.h"
#include "EthSwt_43_SJA11XX.h"
#include "EthSwt_43_SJA11XX_Ipw.h"
#include "gptp_def.h"
#include "gptp_port.h"
#include "gptp_port_platform.h"
#include "gptp.h"
#include "gptp_err.h"
#include "gptp_pi.h"
#include "gptp_internal.h"

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
static void GPTP_PORT_MsgCopy(uint8_t *pu8Dest, const uint8_t *cpu8Src, uint16_t u16Length);
static uint32_t GPTP_PORT_PPBToPtpClockRatio(int32_t i32PPBAdjustment);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static gptp_def_map_info_t                  srPortMap;
static int32_t                              si32PPBadjustmentAverage = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief The function copies messages ptp frame into the transmit buffer.
 *
 * The function copies messages ptp frame into the transmit buffer.
 *
 */
static void GPTP_PORT_MsgCopy(uint8_t *pu8Dest, const uint8_t *cpu8Src, uint16_t u16Length)
{
    uint16_t u16Index;

    for(u16Index = 0; u16Index < u16Length; u16Index++)
    {
        pu8Dest[u16Index] = cpu8Src[u16Index];
    }
}


/*!
 * @brief           Convert PPB to clock ratio to uint32 representation
 *                  in range (0:2).
 *
 * @details         Converts PPB to clock ratio representation as uint32
 *                  in range (0:2) as needed by the RTD API.
 *                  The most significat bit of the integer is 0 or 1. The reset
 *                  of the bits are the fractional part.
 *
 * @param[in]       i32PPBAdjustment Parts per billion adjustment.
 *
 * @return          uint32 representating fractional numbers in range (0:2).
 * 
 * @ requirements 2081146
 * @ requirements 2081313
*/
static uint32_t GPTP_PORT_PPBToPtpClockRatio(int32_t i32PPBAdjustment)
{
    uint32_t  u32PtpClkRate;
    uint64_t  u64PtpClkRate;
    float64_t f64TempCorrectedRateRatio;
    float64_t f64correctedRateRatio;

    /* Compute correction ratio from the PPB adjustement. */
    if (i32PPBAdjustment > 0)
    {
        f64correctedRateRatio = 1.0 - (((float64)i32PPBAdjustment)/((float64)1000000000));
    }
    else
    {
        f64correctedRateRatio = 1.0 + (((float64)(-i32PPBAdjustment))/((float64)1000000000));
    }

    /* Convert from float to representation expect by RTD
       (most significat bit 0/1 rest of the bits fractional part). */
    f64TempCorrectedRateRatio = f64correctedRateRatio * (float64_t)0x80000000U;
    u64PtpClkRate = (uint64_t)f64TempCorrectedRateRatio;
    u32PtpClkRate = (uint32_t)(u64PtpClkRate & 0xFFFFFFFFUL);

    return u32PtpClkRate;
}

/*!
 *
 * @brief   This function finds gPTP port number in the port map.
 *
 * @details The function finds the gPTP port number in the port map by the
 *          Switch index and Switch port index.
 *
 * @param[out] pu8GptpPort  Pointer to gPTP port number
 * @param[in] u8PortOnSw    Number of the respective port on switch.
 * @param[in] u8Sw          Number of the respective switch.
 *
 * @return GPTP_ERR_OK in case the gPTP port is found
 *
 * @ requirements 2081146
 * @ requirements 2081314
 */
gptp_err_type_t GPTP_PORT_PortLookup(uint8_t *pu8GptpPort, uint8_t u8PortOnSw,
                                     uint8_t u8Sw)
{
    gptp_err_type_t   eStatus;
    uint8_t           u8PortLookUp;
    bool              bFound;

    if (NULL != pu8GptpPort)
    {
        eStatus = GPTP_ERR_OK;

        bFound = false;
        for (u8PortLookUp = 0u; u8PortLookUp < srPortMap.u8NumOfGptpPorts; u8PortLookUp++)
        {
            if ((srPortMap.prMapTable[u8PortLookUp].u8SwitchPort == u8PortOnSw) && 
                (srPortMap.prMapTable[u8PortLookUp].u8Switch == u8Sw))
            {
                *pu8GptpPort = u8PortLookUp;
                bFound = true;
            }
        }

        if (false == bFound)
        {
            eStatus = GPTP_ERR_API_ILLEGAL_PORT_NUM;;
        }
    }
    else
    {
        eStatus = GPTP_ERR_V_NULL_PTR;
    }

    return eStatus;
}

/*!
 *
 * @brief   This function registers multicast MAC.
 *
 * @details This function provides interface to register MAC in the Ethernet
 *          module so the multicast MAC is forwarded.
 *
 * @param[in] cpu8MacAddr Pointer to multicast MAC address.
 * 
 * @ requirements 2081146
 * @ requirements 2081315
 */
void GPTP_PORT_MulticastForward(const uint8_t *cpu8MacAddr)
{
    (void)Eth_UpdatePhysAddrFilter(EthConf_EthCtrlConfig_EthCtrlConfig_0, cpu8MacAddr, ETH_ADD_TO_FILTER);
}

/*!
 *
 * @brief   This function initializes port module
 *
 * @details This function initializes port module with providing port map table to the module.
 *
 * @param[in] cprPortTable Pointer to the Port Map Table.
 * @param[in] u8NumOfPorts Count of gPTP ports.
 *
 * @ requirements 2081146
 * @ requirements 2081316
 */
void GPTP_PORT_PortMapInit(const gptp_def_map_table_t *cprPortTable, uint8_t u8NumOfPorts)
{
    srPortMap.u8NumOfGptpPorts = u8NumOfPorts;
    srPortMap.prMapTable = cprPortTable;
}

/*!
 *
 * @brief   This function gets Time Base Information from the switch driver
 *
 * @details This function gets Time Base Information from the switch driver and provides
 *          it to the gPTP stack.
 *
 * @param[out] pu16GmTimeBaseIndicator Pointer to the GM Time Base Indicator variable which is updated by calling of this function.
 * @param[out] pu32LastGmPhaseChangeH Pointer to the Last GM Phase Change (High) variable which is updated by calling of this function.
 * @param[out] pu64LastGmPhaseChangeL Pointer to the Last GM Phase Change (Low) variable which is updated by calling of this function.
 * @param[out] pu32ScaledLastGmFreqChange Pointer to the Scaled Last GM Frequency Change variable which is updated by calling of this function.
 *
 * @ requirements 2081146
 * @ requirements 2081317
 */
void GPTP_PORT_TimeBaseInfoGet(uint16_t *pu16GmTimeBaseIndicator,
                               uint32_t *pu32LastGmPhaseChangeH,
                               uint64_t *pu64LastGmPhaseChangeL,
                               uint32_t *pu32ScaledLastGmFreqChange)
{
    static EthSwt_43_SJA11XX_PtpTimeBaseInfoType rTimeBaseInfo;
    float64_t                                    f64Temp;
    uint64_t                                     u64Seconds;
    uint64_t                                     au64Input[TIME_BASE_REORG_SIZE];
    uint64_t                                     au64Output[TIME_BASE_REORG_SIZE];
    uint16_t                                     u16Cycle;

    (void)EthSwt_43_SJA11XX_GetPtpTimeBaseInformation(&rTimeBaseInfo);

    *pu16GmTimeBaseIndicator = rTimeBaseInfo.timeBaseIndicator;

    u64Seconds = ((uint64_t)rTimeBaseInfo.lastPhaseChange.seconds) | \
                 ((uint64_t)rTimeBaseInfo.lastPhaseChange.secondsHi << 32u);

    for (u16Cycle = 0u; u16Cycle < TIME_BASE_REORG_SIZE; u16Cycle++)
    {
        au64Input[u16Cycle] = u64Seconds & GPTP_DEF_BIT_MASK_48L_16H;
        u64Seconds = u64Seconds >> 16u;
        au64Input[u16Cycle] = au64Input[u16Cycle] * GPTP_DEF_NS_IN_SECONDS;
        if (0u == u16Cycle)
        {
            au64Input[u16Cycle] = au64Input[u16Cycle] + (uint64_t)rTimeBaseInfo.lastPhaseChange.nanoSeconds;
        }
        else
        {
            au64Input[u16Cycle] = au64Input[u16Cycle] + au64Input[(u16Cycle - 1u)];
        }
        au64Output[u16Cycle] = au64Input[u16Cycle] & GPTP_DEF_BIT_MASK_48L_16H;
        au64Input[u16Cycle] = au64Input[u16Cycle] >> 16u;
    }

    *pu64LastGmPhaseChangeL = 0u | ((((uint64_t)au64Output[0] & (uint64_t)GPTP_DEF_BIT_MASK_48L_16H) << 16u) | \
                                   (((uint64_t)au64Output[1] & (uint64_t)GPTP_DEF_BIT_MASK_48L_16H) << 32u) | \
                                   (((uint64_t)au64Output[2] & (uint64_t)GPTP_DEF_BIT_MASK_48L_16H) << 48u));


    *pu32LastGmPhaseChangeH = (((uint32_t)au64Output[3] & (uint32_t)GPTP_DEF_BIT_MASK_48L_16H) | \
                             (((uint32_t)au64Output[4] & (uint32_t)GPTP_DEF_BIT_MASK_48L_16H) << 16u));

    if (true == rTimeBaseInfo.negativePhase)
    {
        /* *pu64LastGmPhaseChangeL * (-1) */
        *pu64LastGmPhaseChangeL = (~(*pu64LastGmPhaseChangeL)) + 1u;
        /* *pu32LastGmPhaseChangeH * (-1) */
        *pu32LastGmPhaseChangeH = (~(*pu32LastGmPhaseChangeH)) + 1u;
    }

    f64Temp = (rTimeBaseInfo.lastFreqChange * (float64_t)GPTP_DEF_POW_2_41);
    *pu32ScaledLastGmFreqChange = (uint32_t)((int32_t)f64Temp);
}

/*!
 *
 * @brief   This function sends PTP message.
 *
 * @details This function sends PTP message using the ENET driver.
 *
 * @param[in] u8Port gPTP port on which the PTP message is transmitted.
 * @param[in] u8FramePrio Eth frame priority.
 * @param[in] cprTxData Pointer to the structure containing data to send.
 * @param[in] u8FrameId Frame ID of the transmitted message.
 *
 * @return GPTP_ERR_OK in case the frame is successfully transmitted.
 *
 * @ requirements 2081146
 * @ requirements 2081320
 */
gptp_err_type_t GPTP_PORT_MsgSend(uint8_t u8Port,
                                  uint8_t u8FramePrio,
                                  const gptp_def_tx_data_t *cprTxData,
                                  uint8_t u8FrameId)
{
    Std_ReturnType                  eStatus = E_OK;
    gptp_err_type_t                 eError;
    const  gptp_def_map_table_t     *cprMapTablePort;
    EthSwt_MgmtInfoType             rMgmtInfo;
    uint16_t                        u16PayloadLength;
    uint16_t                        u16BufLengthNeeded;
    static uint8_t                  *spu8PayloadBuffer;
    static Eth_BufIdxType           srBufferIndex;
    static uint8_t                  sauMcMac[6u];
    uint8_t                         u8Idx;
    (void)u8FramePrio;

    eError = GPTP_ERR_OK;

    cprMapTablePort = &srPortMap.prMapTable[u8Port];

    /* Check input arguments. */
    if ((NULL != cprTxData) && (cprTxData->u8FrameLength > GPTP_DEF_ETH_II_LEN))
    {
        for (u8Idx = 0u; u8Idx < 6u; u8Idx++)
        {
            sauMcMac[u8Idx] = cprTxData->pau8TxBuffPtr[u8Idx];
        }

        u16BufLengthNeeded = (((uint16_t)cprTxData->u8FrameLength) + GPTP_DEF_HEAD_TRAIL_LEN);
        u16PayloadLength = u16BufLengthNeeded;

        if (BUFREQ_OK == Eth_ProvideTxBuffer(EthConf_EthCtrlConfig_EthCtrlConfig_0, 
                                             0U, 
                                             &srBufferIndex, &spu8PayloadBuffer, 
                                             &u16PayloadLength))
        {
            GPTP_PORT_MsgCopy(spu8PayloadBuffer, &(cprTxData->pau8TxBuffPtr)[12], 
                              u16BufLengthNeeded);

            u16PayloadLength = (uint16_t)cprTxData->u8FrameLength - (uint16_t)GPTP_DEF_ETH_II_LEN;

            rMgmtInfo.SwitchIdx = cprMapTablePort->u8Switch;
            rMgmtInfo.SwitchPortIdx = cprMapTablePort->u8SwitchPort;

            eStatus = EthSwt_43_SJA11XX_SetMgmtInfo(EthConf_EthCtrlConfig_EthCtrlConfig_0, 
                                                    srBufferIndex, &rMgmtInfo);

            if ((Std_ReturnType)E_OK == eStatus)
            {
                if (true == cprTxData->bTsRequested)
                {
                    eStatus = EthSwt_43_SJA11XX_EnableEgressTimeStamp(EthConf_EthCtrlConfig_EthCtrlConfig_0,
                                                                      srBufferIndex, &rMgmtInfo);
                }

                if ((Std_ReturnType)E_OK != eStatus)
                {
                    /* Could not enable timestamping. */
                    eError = GPTP_ERR_T_TS_NOT_REGISTERED;
                }
                else
                {
                    eStatus = EthSwt_43_SJA11XX_EthTxProcessFrame(EthConf_EthCtrlConfig_EthCtrlConfig_0, 
                                                                  srBufferIndex, &spu8PayloadBuffer, 
                                                                  &u16PayloadLength);

                    if ((Std_ReturnType)E_OK != eStatus)
                    {
                        /* Could not process frame. */
                        eError = GPTP_ERR_T_TS_NOT_REGISTERED;
                    }
                    else 
                    {
                        GPTP_PORT_MsgCopy(spu8PayloadBuffer, &spu8PayloadBuffer[2], u16BufLengthNeeded);

                        /* Set MAC address from destination address in packet. */
                        Eth_SetPhysAddr(EthConf_EthCtrlConfig_EthCtrlConfig_0,
                                        &(cprTxData->pau8TxBuffPtr[MAC_LENGTH]));
                        
                        eStatus = Eth_Transmit(EthConf_EthCtrlConfig_EthCtrlConfig_0, 
                                               srBufferIndex, 
                                               (Eth_FrameType)0x8B8C, true, 
                                               u16PayloadLength, sauMcMac);

                        if ((Std_ReturnType)E_OK == eStatus)
                        {
                            if (NULL != cprTxData->prFrameMap)
                            {
                                cprTxData->prFrameMap->u8PtpFrameId = u8FrameId;
                                cprTxData->prFrameMap->u32BufferIndex = srBufferIndex;
                            }
                        }
                        else
                        {
                            /* Transmission failed. */
                            eError = GPTP_ERR_F_FRAME_SEND;
                        }
                    }
                }
            }
            else
            {
                /* Could not set as management frame. */
                eError = GPTP_ERR_T_TS_NOT_REGISTERED;
            }
        }
        else
        {
            /* No Tx buffer. */
            eError = GPTP_ERR_M_MSG_BUFF_PTR_NULL;
        }
    }
    else
    {
        /* Invalid input arguments. */
        eError = GPTP_ERR_V_NULL_PTR;
    }

    return eError;
}

/*!
 *
 * @brief   This function reads current link status of the gPTP port.
 *
 * @details This function reads current link status of the gPTP port using Switch driver.
 *
 * @param[in] u8Port gPTP port number.
 * @param[out] pbStat Pointer to the status variable, updated in the function.
 *
 * @return GPTP_ERR_OK in case the link status is successfully provided.
 *
 * @ requirements 2081146
 * @ requirements 2081321
 */
gptp_err_type_t GPTP_PORT_GetLinkStatus(uint8_t u8Port, bool *pbStat)
{
    Std_ReturnType                  eStatus;
    gptp_err_type_t                 eError;
    static EthTrcv_LinkStateType    pLinkState;
    const gptp_def_map_table_t      *cprMapTablePort;

    /* Init variables. */
    eError = GPTP_ERR_V_NULL_PTR;

    if (NULL != pbStat)
    {
        if (srPortMap.prMapTable[u8Port].bLinkStateIgnore)
        {
            *pbStat = true;
            eError = GPTP_ERR_OK;
        }
        else
        {
            if (u8Port < srPortMap.u8NumOfGptpPorts)
            {
                cprMapTablePort = &srPortMap.prMapTable[u8Port];

                eStatus = EthSwt_43_SJA11XX_GetLinkState(cprMapTablePort->u8Switch, cprMapTablePort->u8SwitchPort, &pLinkState);
                if ((Std_ReturnType)E_OK != eStatus)
                {
                    eError = GPTP_ERR_I_NO_LINK_STATUS;
                }
                else
                {
                    eError = GPTP_ERR_OK;

                    if (ETHTRCV_LINK_STATE_DOWN == pLinkState)
                    {
                        *pbStat = false;
                    }
                    else
                    {
                        *pbStat = true;
                    }
                }
            }
            else
            {
                eError = GPTP_ERR_API_ILLEGAL_PORT_NUM;
            }
        }
    }

    return eError;
}

/*!
 *
 * @brief   This function gets current Time Stamp time.
 *
 * @details This function gets current Time Stamp time from the Switch driver.
 *
 * @param[in] eTsType Type of the Time Stamp (free-running of corrected).
 *
 * @return gptp_def_timestamp_t with the current Time Stamp time.
 *
 * @ requirements 2081146
 * @ requirements 2081322
 */
gptp_def_timestamp_t GPTP_PORT_CurrentTimeGet(gptp_def_ts_type_t eTsType)
{

    Std_ReturnType                          rStatus;
    gptp_def_timestamp_t                    rTimeStamp;
    static EthSwt_43_SJA11XX_PtpTimeType    srEthTimestamp;

    rTimeStamp.u64TimeStampS = 0u;
    rTimeStamp.u32TimeStampNs = 0u;

    switch (eTsType)
    {
        case GPTP_DEF_TS_FREERUNNING:
            rStatus = EthSwt_43_SJA11XX_GetPtpTSClk(0u, &srEthTimestamp);
            if ((Std_ReturnType)E_OK == rStatus)
            {
                rTimeStamp.u64TimeStampS = (((uint64_t)srEthTimestamp.secondsHi & (uint64_t)GPTP_DEF_BIT_MASK_16L_16H) << 32u) | (uint64_t) srEthTimestamp.seconds;
                rTimeStamp.u32TimeStampNs = srEthTimestamp.nanoSeconds;
            }
            break;

        case GPTP_DEF_TS_CORRECTED:
            rStatus = EthSwt_43_SJA11XX_GetPtpClk(0u, &srEthTimestamp);
            if ((Std_ReturnType)E_OK == rStatus)
            {
                rTimeStamp.u64TimeStampS = (((uint64_t)srEthTimestamp.secondsHi & (uint64_t)GPTP_DEF_BIT_MASK_16L_16H) << 32u) | (uint64_t) srEthTimestamp.seconds;
                rTimeStamp.u32TimeStampNs = srEthTimestamp.nanoSeconds;
            }
            break;

        default:
            rTimeStamp.u64TimeStampS = 0u;
            rTimeStamp.u32TimeStampNs = 0u;
            break;
    }

    return rTimeStamp;
}

/*!
 * @brief           This function reads MAC Address of the gPTP port.
 *
 * @details         This function reads MAC Address of the gPTP port using
 *                  the Switch driver.
 *
 * @param[in]       u8Port gPTP port number.
 * @param[out]      pu64Mac Pointer to the MAC Address variable, updated in
 *                  the function.
 *
 * @return          Error status.
 * @retval          GPTP_ERR_OK: The MAC Address was successfully read.
 * @retval          GPTP_ERR_V_NULL_PTR: Empty or invalid input arguments.
 *
 * @ requirements 2081146
 * @ requirements 2081324
*/
gptp_err_type_t GPTP_PORT_ObtainPortMac(uint8_t u8Port,
                                        uint64_t *pu64Mac)
{
    const gptp_def_map_table_t  *cprMapTablePort;
    gptp_err_type_t             eError;
    static const uint8          *scpu8MacAddr;

    if (NULL != pu64Mac)
    {
        if (u8Port < srPortMap.u8NumOfGptpPorts)
        {
            cprMapTablePort = &srPortMap.prMapTable[u8Port];

            /* There is now no high level interface - using Ip interface. */
            Switch_Ip_GetMacAddr(cprMapTablePort->u8Switch, cprMapTablePort->u8SwitchPort, &scpu8MacAddr);

            *pu64Mac = GPTP_PORT_MacAddrAsUInt64(scpu8MacAddr);

            eError = GPTP_ERR_OK;
        }
        else
        {
            eError = GPTP_ERR_API_ILLEGAL_PORT_NUM;
        }
    }
    else
    {
        eError = GPTP_ERR_V_NULL_PTR;
    }

    return eError;
}

/*!
 * @brief           This function provides time synchronization information.
 *
 * @details         This function provides time synchronization information
 *                  received from the Grand Master to the Switch driver.
 *
 * @param[in]       prGptp Pointer to global gPTP structure.
 * @param[in]       cu8DomainNumber Domain number of the received Follow Up
 *                  message.
 * @param[in]       cpf64RateRatio Rate Ratio.
 * @param[in]       crOffset Current time offset between local (corrected) clock
 *                  and the Grand Master.
 * @param[in]       cbNegative Positive/negative offset.
 * @param[in]       ci8SyncIntervalLog Current Sync interval.
 * @param[out]      pbUpdated Pointer to flag signalizing stack the clock is
 *                  updated.
 *
 * @return          Error status.
 * @retval          GPTP_ERR_OK: The local clock is successfully updated.
 * @retval          GPTP_ERR_F_UPDATE_PTP: The local clock cannot be updated.
 *
 * @ requirements 2081146
 * @ requirements 2081325
*/
gptp_err_type_t GPTP_PORT_UpdateLocalClock(gptp_def_data_t *prGptp,
                                           const uint8_t cu8DomainNumber,
                                           const float64_t *cpf64RateRatio,
                                           const gptp_def_timestamp_sig_t crOffset,
                                           const bool cbNegative,
                                           const int8_t ci8SyncIntervalLog,
                                           bool *pbUpdated)
{
    gptp_err_type_t                         eError;
    Std_ReturnType                          eStatus;
    static gptp_def_timestamp_sig_t         srOffsetTmp;
    /* Placeholder for gPTP stack computed rate ratio. */
    static float64_t                        sf64sRateRatio;
    static bool                             sbNegativeOfst;
    static int8_t                           si8SyncIntLog;
    bool                                    bUpdateClock;
    bool                                    bClkUpdateNotify;
    uint64_t                                u64Offset;
    int32_t                                 i32PPBAdjustment;
    int32_t                                 i32timeErrorNs;
    int64_t                                 i64PtpOffsetNs;
    uint32_t                                u32PtpClkRate;
    uint8_t                                 u8SwtIdx;
    static EthSwt_43_SJA11XX_PtpTimeType    srPtpTimeOffset;
    static uint8_t                          su8NumberOfSwitches;
    
    /* Local variable initialization with default value. */
    sf64sRateRatio = *cpf64RateRatio;
    sbNegativeOfst = cbNegative;
    bUpdateClock = false;
    bClkUpdateNotify = false;
    si8SyncIntLog = ci8SyncIntervalLog;
    srOffsetTmp = crOffset;
    eError = GPTP_ERR_OK;
    eStatus = (Std_ReturnType)E_NOT_OK;
    su8NumberOfSwitches = prGptp->rPerDeviceParams.u8NumberOfClkInstances;

    /* Call domain selection callback if configured. */
    if (NULL != prGptp->rPtpStackCallBacks.pfDomSelectionCB)
    {
        bUpdateClock =
            prGptp->rPtpStackCallBacks.pfDomSelectionCB(cu8DomainNumber,
                                                        &sf64sRateRatio,
                                                        &srOffsetTmp,
                                                        &sbNegativeOfst,
                                                        &si8SyncIntLog);
    }
    else
    {
        if (0u == cu8DomainNumber)
        {
            bUpdateClock = true;
        }
    }

    /* Clock update if requested. */
    if (TRUE == bUpdateClock)
    {
        /* Store the reported offset to device params. */
        prGptp->rPerDeviceParams.rReportedOffset = srOffsetTmp;
        prGptp->rPerDeviceParams.bReportedOffsetNeg = cbNegative;
        prGptp->rPerDeviceParams.f64CorrClockRateRatio = sf64sRateRatio;

        u64Offset = GPTP_INTERNAL_AbsInt64ToUint64(srOffsetTmp.s64TimeStampS * (int64_t)GPTP_DEF_NS_IN_SECONDS);
        u64Offset += GPTP_INTERNAL_AbsInt64ToUint64(srOffsetTmp.s32TimeStampNs);

        /* Time offset correction. */
        if (u64Offset > prGptp->rPerDeviceParams.u64PIControllerMaxThreshold)
        {
            /* Convert to signed offset. */
            if (sbNegativeOfst == false)
            {
                i64PtpOffsetNs = (int64_t)u64Offset;
            }
            else
            {
                i64PtpOffsetNs = (int64_t)u64Offset * (-1);
            }

            /* Calculate relative PPB correction from rateRatio reported by
               gPTP stack. */
            i32PPBAdjustment = GPTP_INTERNAL_Float64ToInt32((1.0 - sf64sRateRatio) * (float64_t)GPTP_DEF_NS_IN_SECONDS);

            /* Origin of average calculation. */
            si32PPBadjustmentAverage = i32PPBAdjustment;

            GPTP_PI_Clear();

            /* Set clock update notify flag. */
            bClkUpdateNotify = true;
        }
        /* PI controller mode adjusting oscilator PPM in range +-50 PPM from
           reference frequency. */
        else
        {
            /* No offset adjustment to be done in this case. */
            i64PtpOffsetNs = 0;

            /* Convert srOffsetTmp to signed integer. */
            i32timeErrorNs = cbNegative ? srOffsetTmp.s32TimeStampNs : -srOffsetTmp.s32TimeStampNs;

            /* Calculate the PI Controller output for this control loop cycle. */
            i32PPBAdjustment = GPTP_PI_Update(ci8SyncIntervalLog, i32timeErrorNs);

            /* Calculate weighted average. */
            si32PPBadjustmentAverage = GPTP_INTERNAL_Float64ToInt32(((1.0 - GPTP_PORT_NEW_PPB_WEIGHT) *
                                                                    (float64_t)si32PPBadjustmentAverage) +
                                                                    (GPTP_PORT_NEW_PPB_WEIGHT *
                                                                    (float64_t)i32PPBAdjustment));
        }

        /* Covert PPB to clock ratio in expected RTD format. */
        u32PtpClkRate = GPTP_PORT_PPBToPtpClockRatio(i32PPBAdjustment);

        /* Call "clock update start" callback, if configured,
           to allow 1588 time users to prepare for abrupt change. */
        if ((true == bClkUpdateNotify) &&
            (NULL != prGptp->rPtpStackCallBacks.pfClkUpdateNotifyStart))
        {
            prGptp->rPtpStackCallBacks.pfClkUpdateNotifyStart();
        }

        /* Apply offset correction if it is not zero. */
        if (0 != i64PtpOffsetNs)
        {
            srPtpTimeOffset.nanoSeconds = (uint32)srOffsetTmp.s32TimeStampNs;
            srPtpTimeOffset.seconds = (uint32)srOffsetTmp.s64TimeStampS;
            srPtpTimeOffset.secondsHi = (uint16)((uint64_t)srOffsetTmp.s64TimeStampS >> 32);

            for (u8SwtIdx = 0u; u8SwtIdx < su8NumberOfSwitches; u8SwtIdx++)
            {
                if (i64PtpOffsetNs > 0)
                {
                    eStatus = EthSwt_43_SJA11XX_AddOffsetToPtpClk(u8SwtIdx, &srPtpTimeOffset);
                }
                else
                {
                    eStatus = EthSwt_43_SJA11XX_SubtractOffsetFromPtpClk(u8SwtIdx, &srPtpTimeOffset);
                }
            }
        }

        /* Call "clock update finish" callback, if configured,
           to allow 1588 time users to resume after abrupt change. */
        if ((true == bClkUpdateNotify) &&
            (NULL != prGptp->rPtpStackCallBacks.pfClkUpdateNotifyFinish))
        {
            prGptp->rPtpStackCallBacks.pfClkUpdateNotifyFinish();
        }

        for (u8SwtIdx = 0u; u8SwtIdx < su8NumberOfSwitches; u8SwtIdx++)
        {
            eStatus = EthSwt_43_SJA11XX_SetPtpClkRatio(u8SwtIdx, u32PtpClkRate);
        }

        if ((Std_ReturnType)E_OK == eStatus)
        {
            /* Notification to gPTP stack, clock was successfully updated. */
            *pbUpdated = true;
            prGptp->rPerDeviceParams.bEverUpdated = true;
        }
        else
        {
            /* Notification to gPTP stack, clock was not successfully updated. */
            *pbUpdated = false;
            prGptp->rPerDeviceParams.bEverUpdated = false;
            eError = GPTP_ERR_F_UPDATE_PTP;
        }
    }

    return eError;
}

/*!
 *
 * @brief           This function stabilizes the local clock.
 *
 * @details         This function stabilizes the local clock running.
 *                  The stabilized clock runs at the current rate ratio.
 *                  It prevents clock from drifting, in case of Grand Master
 *                  loss.
 *
 * @param[in]       cpf64RateRatio Rate Ratio.
 * @param[in]       cu8NumberOfClkInstances Number of clock instances.
 *
 * @return          Error status
 * @retval          GPTP_ERR_OK: The Local clock is successfully stabilized.
 * @retval          GPTP_ERR_F_UPDATE_PTP: The Local clock cannot be stabilized.
 * 
 * @ requirements 2081146
 * @ requirements 2081326
 */
gptp_err_type_t GPTP_PORT_FixLocalClock(const float64_t *cpf64RateRatio,
                                        const uint8_t cu8NumberOfClkInstances)
{
    (void)*cpf64RateRatio;

    gptp_err_type_t         eError;
    Std_ReturnType          eStatus = E_OK;
    uint32                  u32PtpClkRate;
    uint8_t                 u8SwtIdx;
    
    eError = GPTP_ERR_OK;

    /* Use current average value of PI Controller instead of RateRatio. */
    u32PtpClkRate = GPTP_PORT_PPBToPtpClockRatio(si32PPBadjustmentAverage);

    for (u8SwtIdx = 0u; u8SwtIdx < cu8NumberOfClkInstances; u8SwtIdx++)
    {
        eStatus = EthSwt_43_SJA11XX_SetPtpClkRatio(u8SwtIdx, u32PtpClkRate);
        if ((Std_ReturnType)E_OK != eStatus)
        {
            eError = GPTP_ERR_F_UPDATE_PTP;
        }
    }

    return eError;
}

/*!
 * @brief           This function gets current time.
 *
 * @details         This function gets current Time Stamp(free running) clock
 *                  time and current PTP(corrected) clock time.
 *                  These Time Stamps are taken at once.
 *
 * @param[out]      prFreeRunClk Pointer to the free running clock variable,
 *                  updated in the function.
 * @param[out]      prCorrectedClk Pointer to the corrected clock variable,
 *                  updated in the function.
 * @param[out]      bDoubleClock If true return both clock - corrected and free running.
 * 
 * @return          Error status
 * @retval          GPTP_ERR_OK: In case the time is successfully read.
 * @retval          GPTP_ERR_I_COUNTERS_NULL_PTR: The input parameters NULL.
 * @retval          GPTP_ERR_F_TIME_READ: The time read error.
 *
 * @ requirements 2081146
 * @ requirements 2081327
 */
gptp_err_type_t GPTP_PORT_GetSwitchTimes(gptp_def_timestamp_t *prFreeRunClk,
                                         gptp_def_timestamp_t *prCorrectedClk,
                                         bool bDoubleClock)
{

    static EthSwt_43_SJA11XX_PtpTimeType    srFreeRunTime;
    static EthSwt_43_SJA11XX_PtpTimeType    srCorrectedTime;
    gptp_err_type_t                         eError;
    Std_ReturnType                          eStatus;

    eStatus = EthSwt_43_SJA11XX_GetPtpTimes(GPTP_PORT_PRIMARY_SWITCH, &srFreeRunTime, &srCorrectedTime);

    if ((Std_ReturnType)E_OK == eStatus)
    {
        /* Check address of destination buffers. */
        if ((NULL != prFreeRunClk) && (NULL != prCorrectedClk))
        {
            prCorrectedClk->u64TimeStampS = srCorrectedTime.seconds | (((uint64_t)srCorrectedTime.secondsHi) << 32u);
            prCorrectedClk->u32TimeStampNs = srCorrectedTime.nanoSeconds;
            if (true == bDoubleClock)
            {
                prFreeRunClk->u64TimeStampS = srFreeRunTime.seconds | (((uint64_t)srFreeRunTime.secondsHi) << 32u);
                prFreeRunClk->u32TimeStampNs = srFreeRunTime.nanoSeconds;
            }
            else
            {
                prFreeRunClk->u64TimeStampS = prCorrectedClk->u64TimeStampS;
                prFreeRunClk->u32TimeStampNs = prCorrectedClk->u32TimeStampNs;
            }

            eError = GPTP_ERR_OK;
        }
        else
        {
            eError = GPTP_ERR_I_COUNTERS_NULL_PTR;
        }
        
    }
    else
    {
        eError = GPTP_ERR_F_TIME_READ;
        GPTP_ERR_Register(GPTP_ERR_PORT_NOT_SPECIF, GPTP_ERR_DOMAIN_NOT_SPECIF,
                          GPTP_ERR_F_TIME_READ, GPTP_ERR_SEQ_ID_NOT_SPECIF);
    }

    return eError;
}

/*!
 *
 * @brief   This function reads TX management object to obtain TX timestamp.
 *
 * @details This function reads TX management object which have been identified as open. If the object is
 *          owned by UPPER LAYER and contains valid egress timestamp, the timestamp is provided to the
 *          timestamp handler.
 *
 * @param[in] prFrameMap pointer to the frame map with open buffer index
 *
 */
void GPTP_PORT_ProcessMapEntry(gptp_def_tx_frame_map_t *prFrameMap)
{
    static EthSwt_MgmtObjectType    srTxMgmt;
    static EthSwt_MgmtObjectType    *sprTxMgmt;
    static uint8_t                  u8PtpPort;
    
    sprTxMgmt = &srTxMgmt;

    if ((Std_ReturnType)E_OK == EthSwt_43_SJA11XX_GetTxMgmtObject(EthConf_EthCtrlConfig_EthCtrlConfig_0, 
                                                                  prFrameMap->u32BufferIndex, &sprTxMgmt))
    {
        if ((sprTxMgmt->Ownership == ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER) && 
            ((Std_ReturnType)E_OK == sprTxMgmt->Validation.EgressTimestampValid))
        {
            if (GPTP_ERR_OK == GPTP_PORT_PortLookup(&u8PtpPort, sprTxMgmt->MgmtInfo.SwitchPortIdx, sprTxMgmt->MgmtInfo.SwitchIdx))
            {
                GPTP_TimeStampHandler(u8PtpPort, sprTxMgmt->EgressTimestamp.seconds, 
                                      sprTxMgmt->EgressTimestamp.nanoseconds, 
                                      prFrameMap->u8PtpFrameId);
            }
            prFrameMap->u32BufferIndex = GPTP_DEF_BUFF_INDEX_CLOSED;
            sprTxMgmt->Ownership = ETHSWT_MGMT_OBJ_UNUSED;
        }
    }
}

/*!
 *
 * @brief     This function executes platform specific functionality of the Periodic function.
 *
 * @details   This function executes platform specific functionality of the Periodic function.
 *            This function may be left empty or it can perform the time stamp polling
 *            by the frame buffer and frame table index.
 *
 * @param[in] prGptp Pointer to global gPTP structure.
 *
 * @ requirements 2081146
 * @ requirements 2081329
 */
void GPTP_PORT_TimerPeriodic(gptp_def_data_t *prGptp)
{
    uint8_t                  u8Port;
    uint8_t                  u8Machine;
    uint8_t                  u8Domain;
    gptp_def_pdelay_t        *prPdelay;
    gptp_def_domain_t        *prDomain;
    gptp_def_sync_t          *prSync;

    /* TS polling */
    for (u8Port = 0u; u8Port < prGptp->rPerDeviceParams.u8NumberOfPdelayMachines; u8Port++)
    {
        prPdelay = &prGptp->prPdelayMachines[u8Port];

        /* Those Pdelay machines that are initiator enabled */
        if (true == prPdelay->bPdelayInitiatorEnabled)
        {
            /* If a buffer index is assigned */
            if (GPTP_DEF_BUFF_INDEX_CLOSED != prPdelay->rTxDataReq.prFrameMap->u32BufferIndex)
            {
                /* Check if TS is available and call TS handler */
                GPTP_PORT_ProcessMapEntry(prPdelay->rTxDataReq.prFrameMap);
            }
        }
        /* Those Pdelay machines that are responder enabled */
        if (true == prPdelay->bPdelayResponderEnabled)
        {
            /* If a buffer index is assigned */
            if (GPTP_DEF_BUFF_INDEX_CLOSED != prPdelay->rTxDataResp.prFrameMap->u32BufferIndex)
            {
                /* Check if TS is available and call TS handler */
                GPTP_PORT_ProcessMapEntry(prPdelay->rTxDataResp.prFrameMap);
            }
        }
    }
    /* For each domain */
    for (u8Domain = 0u; u8Domain < prGptp->rPerDeviceParams.u8NumberOfDomains; u8Domain++)
    {
        prDomain = &prGptp->prPerDomainParams[u8Domain];

        /* For each sync machine on domain */
        for (u8Machine = 0u; u8Machine < prDomain->u8NumberOfSyncsPerDom; u8Machine++)
        {
            prSync = &prDomain->prSyncMachines[u8Machine];
            /* If a buffer index is assigned */
            if (GPTP_DEF_BUFF_INDEX_CLOSED != prSync->rTxDataSyn.prFrameMap->u32BufferIndex)
            {
                /* Check if TS is available and call TS handler */
                GPTP_PORT_ProcessMapEntry(prSync->rTxDataSyn.prFrameMap);
            }
        }
    }
}

/*!
 *
 * @brief           This function initializes platform part.
 *
 * @details         This function executes platform specific parts of 
 *                  the generic initialization.
 *
 * @return          GPTP_ERR_OK in case platform part is initialized successfully.
 *
 * @ requirements 2573707
 */
gptp_err_type_t GPTP_PORT_Init(void)
{
    gptp_err_type_t eError;

    /* Error initial value. */
    eError = GPTP_ERR_OK;

    return eError;
}

/*!
 * @brief           This function initializes platform part of
 *                  gptp_def_pdelay_t struct.
 *
 * @details         This function executes platform specific parts of
 *                  the initialization for each Path delay machine.
 *
 * @param[in]       cu8Port gPTP port on which the PTP message is transmitted.
 * @param[in]       cprPdelayInit Pointer to gPTP Pdelay Initialization.
 * @param[in]       prPdelay Pointer to gPTP INTERNAL stucture - Pdelay machine.
 *
 * @return          GPTP_ERR_OK in case the structure has been set.
 *
 * @ requirements 2081146
 * @ requirements 2081330
*/
gptp_err_type_t GPTP_PORT_InitPDelayStruct(const uint8_t cu8Port,
                                           const gptp_def_init_params_pdel_t *cprPdelayInit,
                                           gptp_def_pdelay_t *prPdelay)
{
    gptp_err_type_t eError;

    /* Error initial value. */
    eError = GPTP_ERR_OK;

    /* Check if prFrameMapReq and prFrameMapResp are not null. */
    if ((NULL != cprPdelayInit->prFrameMapReq) &&
        (NULL != cprPdelayInit->prFrameMapResp))
    {
        prPdelay->rTxDataReq.prFrameMap = cprPdelayInit->prFrameMapReq;
        prPdelay->rTxDataResp.prFrameMap = cprPdelayInit->prFrameMapResp;
        prPdelay->rTxDataReFu.prFrameMap = NULL;
    }
    else
    {
        if (NULL == cprPdelayInit->prFrameMapReq)
        {
            eError = GPTP_ERR_I_PD_STRCT_NULL_PTR;
            GPTP_ERR_Register(cu8Port, GPTP_ERR_DOMAIN_NOT_SPECIF,
                              GPTP_ERR_I_PD_STRCT_NULL_PTR,
                              GPTP_ERR_SEQ_ID_NOT_SPECIF);
        }

        if (NULL == cprPdelayInit->prFrameMapResp)
        {
            eError = GPTP_ERR_I_PD_STRCT_NULL_PTR;
            GPTP_ERR_Register(cu8Port, GPTP_ERR_DOMAIN_NOT_SPECIF,
                              GPTP_ERR_I_PD_STRCT_NULL_PTR,
                              GPTP_ERR_SEQ_ID_NOT_SPECIF);
        }
    }

    prPdelay->rTxDataReq.prFrameMap->u32BufferIndex = GPTP_DEF_BUFF_INDEX_CLOSED;
    prPdelay->rTxDataReq.prFrameMap->u8PtpFrameId = GPTP_DEF_FRAME_INDEX_CLOSED;
    prPdelay->rTxDataResp.prFrameMap->u32BufferIndex = GPTP_DEF_BUFF_INDEX_CLOSED;
    prPdelay->rTxDataResp.prFrameMap->u8PtpFrameId = GPTP_DEF_FRAME_INDEX_CLOSED;

    return eError;
}

/*!
 * @brief           This function initializes platform part of
 *                  gptp_def_domain_t struct.
 *
 * @details         This function executes platform specific parts of
 *                  the initialization for each Domain.
 *
 * @param[in]       cu8Domain Respective Domain number.
 * @param[in]       cprDomainInit Pointer to gPTP Domain parameters
 *                  initialization.
 * @param[in]       prDomain Pointer to gPTP INTERNAL stucture - Per domain
 *                  parameters.
 *
 * @return          GPTP_ERR_OK in case the structure has been set.
 *
 * @ requirements 2081146
 * @ requirements 2081331
*/
gptp_err_type_t GPTP_PORT_InitDomainStruct(const uint8_t cu8Domain,
                                           const gptp_def_init_params_domain_t *cprDomainInit,
                                           gptp_def_domain_t *prDomain)
{
    (void)cu8Domain;
    (void)cprDomainInit;

    prDomain->rTxDataSig.prFrameMap = NULL;

    return GPTP_ERR_OK;
}

/*!
 * @brief           This function initializes platform part of gptp_def_sync_t
 *                  struct.
 *
 * @details         This function executes platform specific parts of
 *                  the initialization for each Sync machine.
 *
 * @param[in]       cu8Machine Sync machine index for the domain
 * @param[in]       cu8Domain Respective Domain number
 * @param[in]       cprSyncInit Pointer to Sync initialization parameters
 * @param[in]       prSync Pointer to respective Sync machine structure
 *
 * @return          GPTP_ERR_OK in case the structure has been set.
*/
gptp_err_type_t GPTP_PORT_InitSyncStruct(const uint8_t cu8Machine,
                                         const uint8_t cu8Domain,
                                         const gptp_def_init_params_sync_t *cprSyncInit,
                                         gptp_def_sync_t *prSync)
{
    gptp_err_type_t eError;

    /* Error initial value. */
    eError = GPTP_ERR_OK;

    /* Check if prFrameMapSync is not null. */
    if (NULL != cprSyncInit->prFrameMapSync)
    {
        prSync->rTxDataSyn.prFrameMap = cprSyncInit->prFrameMapSync;
        prSync->rTxDataFup.prFrameMap = NULL;
    }
    else
    {
        eError = GPTP_ERR_I_SYNC_STRCT_NULL_PTR;
        GPTP_ERR_Register(cu8Machine, cu8Domain, GPTP_ERR_I_SYNC_STRCT_NULL_PTR,
                          GPTP_ERR_SEQ_ID_NOT_SPECIF);
    }

    prSync->rTxDataSyn.prFrameMap->u32BufferIndex = GPTP_DEF_BUFF_INDEX_CLOSED;
    prSync->rTxDataSyn.prFrameMap->u8PtpFrameId = GPTP_DEF_FRAME_INDEX_CLOSED;

    return eError;
}

/*!
 *
 * @brief This function returns Ethernet II offset
 *
 * @return Ethernet II offset
 */
uint8_t GPTP_PORT_FrameRxGetOffset(void)
{
    /* No offset, because porting layer operates on the 2nd network layer,
       so ethernet header always starts on the first byte. */
    return (uint8_t)GPTP_PORT_ETH_II_OFST;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
