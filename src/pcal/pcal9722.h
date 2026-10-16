/*
 * Copyright 2025 NXP
 *
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 *
 * This file contains sample code only. It is not part of the production code deliverables.
 */

#ifndef PCAL9722_H
#define PCAL9722_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include <stdint.h>

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef enum
{
    PCAL9722_OK,
    PCAL9722_NOT_OK,
    PCAL9722_ERROR_PORT,
    PCAL9722_ERROR_PIN
} PCAL9722_StatusType;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/* Register Addresses */
#define PCAL9722_REG_INPUT_PORT0    0x00
#define PCAL9722_REG_INPUT_PORT1    0x01
#define PCAL9722_REG_INPUT_PORT2    0x02
#define PCAL9722_REG_OUTPUT_PORT0   0x04
#define PCAL9722_REG_OUTPUT_PORT1   0x05
#define PCAL9722_REG_OUTPUT_PORT2   0x06
#define PCAL9722_REG_CONFIG_PORT0   0x0C
#define PCAL9722_REG_CONFIG_PORT1   0x0D
#define PCAL9722_REG_CONFIG_PORT2   0x0E

/* PCAL9722 Slave Address */
#define PCAL9722_SLAVE_ADDRESS      0x42U

/* SPI Command bits */
#define PCAL9722_READ_CMD           0x01U
#define PCAL9722_WRITE_CMD          0x00U

#define PCA9722_PORT0               0U
#define PCA9722_PORT1               1U
#define PCA9722_PORT2               2U

#define INIT_PORT_MASK              (1 << 3U)
/* Constants */
#define PCAL9722_MAX_PORT_NUM       2
/* Ports 0 and 1 have pins 0-7 */
#define PCAL9722_MAX_PIN_NUM_PORT01 7
/* Port 2 has pins 0-5 */
#define PCAL9722_MAX_PIN_NUM_PORT2  5

/* Ports 0 and 1 have 8 pins */
#define PCAL9722_PINS_PER_PORT01    8
/* Port 2 has 2 pins */
#define PCAL9722_PINS_PER_PORT2     6

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

/**
 * @brief Initialize GPIO configuration for all ports
 * @param cfg_port0 Configuration value for port 0
 * @param cfg_port1 Configuration value for port 1
 * @param cfg_port2 Configuration value for port 2
 */
PCAL9722_StatusType pcal9722_initGPIO(uint8 cfg_port0, uint8 cfg_port1, uint8 cfg_port2);

/**
 * @brief Write a value to a single register
 * @param reg Register address
 * @param value Value to write
 */
PCAL9722_StatusType pcal9722_writeRegister(uint8 reg, uint8 value);

/**
 * @brief Read a value from a single register
 * @param reg Register address
 * @return Register value
 */
uint8 pcal9722_readRegister(uint8 reg);

/**
 * @brief Write values to multiple consecutive registers
 * @param start_reg Starting register address
 * @param values Pointer to array of values to write
 * @param count Number of registers to write (max 3)
 */
PCAL9722_StatusType pcal9722_writePorts(uint8 start_reg, uint8 *values, uint8 count);

/**
 * @brief Read values from multiple consecutive registers
 * @param start_reg Starting register address
 * @param values Pointer to array to store read values
 * @param count Number of registers to read (max 3)
 */
PCAL9722_StatusType pcal9722_readPorts(uint8 start_reg, uint8 *values, uint8 count);

/**
 * @brief Set a specific pin on a port
 * @param port Port number (0-2)
 * @param pin Pin number (0-7 for ports 0&1, 0-5 for port 2)
 * @param value Pin value (0 or 1)
 * @return PCAL9722_OK on success, error code on failure
 */
PCAL9722_StatusType pcal9722_setPin(uint8 port, uint8 pin, uint8 value);

/**
 * @brief Read a specific pin from a port
 * @param port Port number (0-2)
 * @param pin Pin number (0-7 for ports 0&1, 0-5 for port 2)
 * @return Pin value (0 or 1), 0 if invalid parameters
 */
uint8 pcal9722_readPin(uint8 port, uint8 pin);

/**
 * @brief Set all pins of a port at once
 * @param port Port number (0-2)
 * @param value 8-bit value to set (automatically masked for port 2)
 * @return PCAL9722_OK on success, error code on failure
 */
PCAL9722_StatusType pcal9722_setPins(uint8 port, uint8 value);

/**
 * @brief Get all pins of a port at once
 * @param port Port number (0-2)
 * @return 8-bit port value, 0 if invalid port
 */
uint8 pcal9722_getPins(uint8 port);

#ifdef __cplusplus
}
#endif

#endif
