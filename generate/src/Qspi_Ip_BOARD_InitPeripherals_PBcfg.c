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
*   @file Qspi_Ip_BOARD_InitPeripherals_PBcfg.c
*
*   @addtogroup FLS
*   @implements Qspi_Ip_PBcfg.c_Artifact
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
#include "Qspi_Ip_BOARD_InitPeripherals_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C                      43
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C       4
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C       4
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C    0
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C               1
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C               0
#define QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same vendor */
#if (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID_C != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_VENDOR_ID)
    #error "Qspi_Ip_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same Autosar version */
#if ((QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
#error "AutoSar Version Numbers of Qspi_Ip_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif
/* Check if current file and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h header file are of the same software version */
#if ((QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION_C != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MAJOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION_C != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_MINOR_VERSION) || \
     (QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION_C != QSPI_IP_BOARD_INITPERIPHERALS_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_BOARD_InitPeripherals_PBcfg.c and Qspi_Ip_BOARD_InitPeripherals_PBcfg.h are different"
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/



#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/* External QSPI flash parameters. */
/* paFlashConnectionCfg */
const Qspi_Ip_MemoryConnectionType FlsConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg[1U] =
{
    {
        0U,  /* qspiInstance */
        QSPI_IP_SIDE_A1,  /* connectionType */
        1U  /* memAlignment */
    }
};

/* paQspiUnitCfg */
const Qspi_Ip_ControllerConfigType FlsConfigSet_BOARD_InitPeripherals_paQspiUnitCfg[1U] =
{
    /* ControllerCfg_0 */
    {
        8388608U,  /* memSizeA1 */
        0U,  /* memSizeA2 */
        3U,  /* csHoldTime */
        3U,  /* csSetupTime */
        0U,  /* columnAddr */
        (boolean)FALSE,   /* wordAddresable */
        QSPI_IP_READ_MODE_LOOPBACK,  /* readModeA */
        QSPI_IP_SAMPLE_DELAY_SAME_DQS,  /* sampleDelay */
        QSPI_IP_SAMPLE_PHASE_INVERTED,  /* samplePhase */
        1U,  /* io2IdleValueA */
        1U,  /* io3IdleValueA */
        {
            /* AHBConfig */
            {
                /* masters */
                0U,  /* buffer 0 master ID */
                1U,  /* buffer 1 master ID */
                2U,  /* buffer 2 master ID */
                3U   /* buffer 3 master ID */
            },
            {
                /* sizes */
                32U,  /* buffer 0 size */
                32U,  /* buffer 1 size */
                32U,  /* buffer 2 size */
                32U   /* buffer 3 size */
            },
            (boolean)TRUE  /* allMasters */
        }
    }
};

/* paInitOperations */
static Qspi_Ip_InitOperationType MemCfg_0_BOARD_InitPeripherals_paInitOperations_0[4U] =
{
    {
        QSPI_IP_OP_TYPE_RMW_REG,  /* opType */
        QSPI_IP_LUT_INVALID,  /* command1Lut */
        QSPI_IP_LUT_INVALID,  /* command2Lut */
        QSPI_IP_LUT_INVALID,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        2U,  /* shift */
        4U,  /* width */
        0U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    },
    {
        QSPI_IP_OP_TYPE_READ_REG,  /* opType */
        QSPI_IP_LUT_INVALID,  /* command1Lut */
        QSPI_IP_LUT_INVALID,  /* command2Lut */
        QSPI_IP_LUT_INVALID,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        2U,  /* shift */
        4U,  /* width */
        0U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    },
    {
        QSPI_IP_OP_TYPE_RMW_REG,  /* opType */
        QSPI_IP_LUT_INVALID,  /* command1Lut */
        QSPI_IP_LUT_INVALID,  /* command2Lut */
        QSPI_IP_LUT_INVALID,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        6U,  /* shift */
        1U,  /* width */
        1U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    },
    {
        QSPI_IP_OP_TYPE_READ_REG,  /* opType */
        QSPI_IP_LUT_INVALID,  /* command1Lut */
        QSPI_IP_LUT_INVALID,  /* command2Lut */
        QSPI_IP_LUT_INVALID,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        6U,  /* shift */
        1U,  /* width */
        1U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    }
};


/* paLutOperations */
static Qspi_Ip_InstrOpType MemCfg_0_BOARD_InitPeripherals_paLutOperations_0[48U] =
{
    /* 0: FastRead */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)235U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_MODE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)2U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_DUMMY | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)4U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)16U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 6: FastWrite */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)56U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)16U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 10: ReadStatus */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)5U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 13: EraseSector */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)32U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 16: SoftReset */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)102U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_STOP | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)153U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_STOP | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)102U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_STOP | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)153U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 24: WriteEnable */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)6U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 26: WriteStatus */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 29: ReadID */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)159U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)4U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 32: Read */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)3U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)128U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 36: Write */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)2U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)16U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 40: ReadCR */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)21U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 43: DRead */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)59U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_DUMMY | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)8U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_2 | (Qspi_Ip_InstrOpType)128U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP)
};



/* paFlashCfg */
const Qspi_Ip_MemoryConfigType FlsConfigSet_BOARD_InitPeripherals_paFlashCfg[1U] =
{
    {
        /* MemCfg_0 */
        QSPI_IP_SERIAL_FLASH,  /* memType */
        1048576U,  /* memSize */
        256U,  /* pageSize */
        0U,  /* readLut */
        6U,  /* writeLut */
        QSPI_IP_LUT_INVALID,  /* read0xxLut */
        QSPI_IP_LUT_INVALID,  /* read0xxLutAHB */
        /* readIdSettings */
        {
            29U,  /* readIdLut */
            3U,  /* readIdSize */
            /* readIdExpected */
            {
                0xC2U,  /* byte 1 */
                0x81U,  /* byte 2 */
                0x3AU,  /* byte 3 */
                0xFFU   /* byte 4 */
            }
        },
        {
            /* eraseSettings */
            {
                {
                    /* eraseTypes[0] */
                    13U,  /* eraseLut */
                    12U  /* size */
                },
                {
                    /* eraseTypes[1] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    12U  /* size */
                },
                {
                    /* eraseTypes[2] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    12U  /* size */
                },
                {
                    /* eraseTypes[3] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    12U  /* size */
                }
            },
            QSPI_IP_LUT_INVALID  /* chipEraseLut */
        },
        {
            /* statusConfig */
            10U,  /* statusRegInitReadLut */
            10U,  /* statusRegReadLut */
            QSPI_IP_LUT_INVALID,  /* statusRegWriteLut */
            24U,  /* writeEnableSRLut */
            24U,  /* writeEnableLut */
            1U,  /* regSize */
            0U,  /* busyOffset */
            1U,  /* busyValue */
            1U,  /* writeEnableOffset */
            2U,  /* blockProtectionOffset */
            4U,  /* blockProtectionWidth */
            0U  /* blockProtectionValue */
        },
        {
            /* suspendSettings */
            QSPI_IP_LUT_INVALID,  /* eraseSuspendLut */
            QSPI_IP_LUT_INVALID,  /* eraseResumeLut */
            QSPI_IP_LUT_INVALID,  /* programSuspendLut */
            QSPI_IP_LUT_INVALID  /* programResumeLut */
        },
        {
            /* resetSettings */
            16U,  /* resetCmdLut */
            4U  /* resetCmdCount */
        },
        {
            /* initResetSettings */
            QSPI_IP_LUT_INVALID,  /* resetCmdLut */
            4U  /* resetCmdCount */
        },
        {
            /* initConfiguration */
            4U,  /* opCount */
            (Qspi_Ip_InitOperationType *)MemCfg_0_BOARD_InitPeripherals_paInitOperations_0  /* operations */
        },
        {
            /* lutSequences */
            48U,  /* opCount */
            MemCfg_0_BOARD_InitPeripherals_paLutOperations_0  /* lutOps */
        },
        NULL_PTR,  /* initCallout */
        NULL_PTR,  /* resetCallout */
        NULL_PTR,  /* errorCheckCallout */
        NULL_PTR,  /* eccCheckCallout */
        NULL_PTR  /* ctrlAutoCfgPtr */
    }
};

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @}*/

