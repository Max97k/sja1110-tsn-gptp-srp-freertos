/*
 *   Copyright 2025 NXP
 *
 *   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
 *   used strictly in accordance with the applicable license terms. By expressly
 *   accepting such terms or by downloading, installing, activating and/or otherwise
 *   using the software, you are agreeing that you have read, and that you agree to
 *   comply with and are bound by, such license terms. If you do not agree to be
 *   bound by the applicable license terms, then you may not retain, install,
 *   activate or otherwise use the software.
 *
 *   This file contains sample code only. It is not part of the production code deliverables.
 */

#ifndef EXAMPLE_INIT_H
#define EXAMPLE_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Eth.h"
#include "EthSwt_43_SJA11XX.h"
#include "EthSwt_43_SJA11XX_Ipw.h"
#include "EthTrcv_43_PHY.h"
#include "Fls.h"
#include "FreeRTOS.h"
#include "Gpt.h"
#include "Mcu.h"
#include "OsIf.h"
#include "Platform.h"
#include "Port.h"
#include "SchM_EthSwt_43_SJA11XX.h"
#include "SchM_Fls.h"
#include "Spi.h"
#include "StandardTypes.h"
#include "Switch_Ip.h"
#include "Switch_Ip_Mgmt.h"
#include "Switch_Ip_Ptp.h"
#include "Switch_Ip_Register_Access.h"
#include "gptp.h"
#include "gptp_cbk.h"
#include "gptp_port.h"
#include "gptp_port_platform.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef enum
{
    SJA1110_LEDCOLOR_OFF,
    SJA1110_LEDCOLOR_BLUE,
    SJA1110_LEDCOLOR_GREEN,
    SJA1110_LEDCOLOR_CYAN,
    SJA1110_LEDCOLOR_RED,
    SJA1110_LEDCOLOR_MAGENTA,
    SJA1110_LEDCOLOR_YELLOW,
    SJA1110_LEDCOLOR_WHITE
} sja1110_ledColor;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/* SJA1110-MGS RGB LED pins */
#define SWT0_LEDRGB_RED   13U
#define SWT0_LEDRGB_GREEN 14U
#define SWT0_LEDRGB_BLUE  15U

/* SJA1110-MGS Switch ID */
#define SJA1110_SWT_ID    0U

/* SJA1110-MGS Switch GPIO Register Address */
#define GPIO_REG_ADDR     0x3FDC4800U
#define GPIO_TGL_ADDR     0x3FDC4803U
#define GPIO_REG_IRQ_ADDR 0x3FDC4BF8u
#define GPIO_PIN_10       10U

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

Std_ReturnType SJA1110_DeviceInit(void);
Std_ReturnType SJA1110_PinsInit(void);
void SJA1110_SetRGBLed(sja1110_ledColor ledColor);
void SJA1110_LockSwitch(void);
void SJA1110_UnlockSwitch(void);
void HandlePhyInterrupts(uint32 gpioFlags);
void HandlePeripheralInterrupts(uint32 gpioFlags);
void HandleButtonInterrupts(uint32 gpioFlags);

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_INIT_H */
