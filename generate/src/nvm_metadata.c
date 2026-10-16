/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
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

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "SJA1110.h"
#include "nvm_metadata.h"

/*! nvm_metadata1 configuration structure */
#define VALIDATION_MARKER    (0xA66AA66AA66AA66AU)
#define CLOCK_SETTING        (CGU_IDIV_4_C_IDIV(9u) | CGU_IDIV_4_C_X(2u))
#define PIN_SETTING_QSPI_SS  (ACU_PIN_CFG_QSPI_S_SSN_ODS(2u) | ACU_PIN_CFG_QSPI_S_SSN_PUPD(2u))
#define PIN_SETTING_QSPI     (ACU_PIN_CFG_QSPI_IO_ODS(2u) | ACU_PIN_CFG_QSPI_IO_PUPD(2u) | ACU_PIN_CFG_QSPI_SCLK_ODS(2u) | ACU_PIN_CFG_QSPI_SCLK_PUPD(2u))

typedef struct {
    uint64 marker;
    uint64 clk_set;
    uint64 pin_set;
#if (defined(__ICCARM__))
    uint32 fw_length;
#else
    uint32* fw_length;
#endif
    uint32* fw_exec_addr;
} nvm_metadata_header_t;

    /* Workaround: The table address will be minus 1 in Thumb mode */
#if (defined(__ICCARM__))
    #pragma section = ".nvmImageHeaderSection"
    #define NVMHEADER_SECTION_START     __section_begin(".nvmImageHeaderSection")
#else
    extern uint32 __FW_LENGTH[];
#endif
extern uint32 Reset_Handler[];

const nvm_metadata_header_t fw_header __attribute__((section(".nvmImageHeaderSection"))) =
{
    VALIDATION_MARKER,
    CLOCK_SETTING,
    (uint64)((uint64)PIN_SETTING_QSPI_SS << 32U) | (uint64)PIN_SETTING_QSPI,
#if (defined(__ICCARM__))
    (uint32)NVMHEADER_SECTION_START,
#else
    __FW_LENGTH,
#endif
    Reset_Handler
};

#ifdef __cplusplus
}
#endif

