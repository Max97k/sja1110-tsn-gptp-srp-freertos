/*
 * Copyright 2024-2025 NXP
 *
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

/*******************************************************************************
 * Guard Begin
 ******************************************************************************/

#ifndef GPTP_PORT_VERSION_H
#define GPTP_PORT_VERSION_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "gptp_component_cfg.h"

#if (GPTP_USE_PRINTF == STD_ON)
    #include <stdio.h>
    #define GPTP_PORT_PRINTF(x) (void)printf x
#endif /* (GPTP_USE_PRINTF == STD_ON) */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Integer to string converter. */
#define GPTP_DEF_STR_HELPER(x)          #x
/* Integer to string converter. */
#define GPTP_DEF_STR(x)                 GPTP_DEF_STR_HELPER(x)

/* Manufacturer name. */
#define GPTP_DEF_MANUFACTURER_NAME      "NXP"
/* Manufacturer identity. */
#define GPTP_DEF_MANUFACTURER_IDENTITY  {0x00,0x60,0x37}

/* Product details. */
#ifndef GPTP_PORT_MODEL_NUMBER
#define GPTP_PORT_MODEL_NUMBER          "SJA1110"
#endif /* GPTP_PORT_MODEL_NUMBER */

#ifndef GPTP_PORT_HW_VERSION
#define GPTP_PORT_HW_VERSION            "SJA1110"
#endif /* GPTP_PORT_HW_VERSION */

#ifndef GPTP_PORT_FW_VERSION
#define GPTP_PORT_FW_VERSION            "Undefined"
#endif /* GPTP_PORT_FW_VERSION */

#define GPTP_PORT_PRODUCT_DESCRIPTION   GPTP_DEF_MANUFACTURER_NAME";"GPTP_PORT_MODEL_NUMBER" gPTP SW Stack;"

/* Major. */
#define GPTP_DEF_REV_MAJOR              0
/* Minor. */
#define GPTP_DEF_REV_MINOR              8
/* Patch. */
#define GPTP_DEF_REV_PATCH              0
/* gPTP revision string. */
#define GPTP_DEF_GPTP_REV               GPTP_DEF_STR(GPTP_DEF_REV_MAJOR)"."GPTP_DEF_STR(GPTP_DEF_REV_MINOR)"."GPTP_DEF_STR(GPTP_DEF_REV_PATCH)

/* gPTP product version string. */
#define GPTP_PORT_PRODUCT_REVISION      GPTP_PORT_HW_VERSION";"GPTP_PORT_FW_VERSION";"GPTP_DEF_GPTP_REV

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

#endif /* GPTP_PORT_VERSION_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
