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

/*******************************************************************************
 * Guard Begin
 ******************************************************************************/

#ifndef GPTP_CFG_H
#define GPTP_CFG_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef GPTP_MAKEFILE_APP
/* Example is not a Makefile application - use generated header file. */
/* Design Studio gPTP component generated header. */
#include "peripherals_gPTP_SJA11xx.h"
#else
/* Example is a Makefile application - use following values. */
#include "StandardTypes.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define GPTP_USE_PRINTF                 (STD_OFF)
#define GPTP_DEBUG_VERBOSITY            (3)

#define GPTP_COUNTERS                   (STD_OFF)
#define GPTP_TIME_VALIDATION            (STD_OFF)

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
/* None */

/*******************************************************************************
 * Guard End
 ******************************************************************************/

#endif /* GPTP_MAKEFILE_APP */
#endif /* GPTP_CFG_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
