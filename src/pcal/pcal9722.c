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

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "../pcal/pcal9722.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define PCAL9722_AUTO_INCREMENT 0x80

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

static uint8 pcal9722_get_max_pin_for_port(uint8 port);
static Std_ReturnType ext_SpiWrite(uint8 channel, uint8 *txData, uint8 len);
static Std_ReturnType ext_SpiRead(uint8 channel, uint8 *txData, uint8 *rxData, uint8 len);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

static Std_ReturnType ext_SpiWrite(uint8 channel, uint8 *txData, uint8 len)
{
    Std_ReturnType spiStatus;

    /* Set up external buffer to transmission and reception */
    spiStatus = Spi_SetupEB(channel, txData, NULL, len);

    if (spiStatus == E_OK)
    {
        spiStatus = Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
    }

    if (spiStatus == E_OK)
    {
        while (SPI_SEQ_OK != Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0))
        {
            ;
        }
    }

    return spiStatus;
}

static Std_ReturnType ext_SpiRead(uint8 channel, uint8 *txData, uint8 *rxData, uint8 len)
{
    Std_ReturnType spiStatus;

    /* Set up external buffer to transmission and reception */
    spiStatus = Spi_SetupEB(channel, txData, rxData, len);

    if (spiStatus == E_OK)
    {
        spiStatus = Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
    }

    if (spiStatus == E_OK)
    {
        while (SPI_SEQ_OK != Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0))
        {
            ;
        }
    }

    return spiStatus;
}

/* Get maximum pin number from a given port. */
static uint8 pcal9722_get_max_pin_for_port(uint8 port)
{
    if (port <= 1)
    {
        return PCAL9722_MAX_PIN_NUM_PORT01;
    }
    else if (port == 2)
    {
        return PCAL9722_MAX_PIN_NUM_PORT2;
    }
    return 0;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

PCAL9722_StatusType pcal9722_writeRegister(uint8 reg, uint8 value)
{
    uint8 tx_data[3];

    tx_data[0] = PCAL9722_SLAVE_ADDRESS;
    tx_data[1] = reg;
    tx_data[2] = value;

    return (PCAL9722_StatusType)ext_SpiWrite(0U, tx_data, sizeof(tx_data));
}

uint8 pcal9722_readRegister(uint8 reg)
{
    Std_ReturnType readStatus;
    uint8 tx_data[3];
    uint8 rx_data[3];
    tx_data[0] = PCAL9722_SLAVE_ADDRESS | 0x01U;
    tx_data[1] = reg;
    tx_data[2] = 0x00U;

    readStatus = ext_SpiRead(0U, tx_data, rx_data, sizeof(tx_data));

    if (readStatus != E_OK)
    {
        /* Return 0 if read didn't complete succesfully */
        rx_data[0] = 0U;
        rx_data[1] = 0U;
        rx_data[2] = 0U;
    }

    return rx_data[2];
}

PCAL9722_StatusType pcal9722_writePorts(uint8 start_reg, uint8 *values, uint8 count)
{
    uint8 tx_data[5];
    tx_data[0] = PCAL9722_SLAVE_ADDRESS;
    tx_data[1] = PCAL9722_AUTO_INCREMENT | start_reg;

    if ((values == NULL) || (count == 0U) || (count > 3U))
    {
        return PCAL9722_NOT_OK;
    }

    for (uint8 i = 0U; i < count; i++)
    {
        tx_data[i + 2U] = values[i];
    }

    return (PCAL9722_StatusType)ext_SpiWrite(0U, tx_data, count + 2U);
}

PCAL9722_StatusType pcal9722_readPorts(uint8 start_reg, uint8 *values, uint8 count)
{
    Std_ReturnType readStatus;
    uint8 tx_data[5];
    uint8 rx_data[5];

    if ((values == NULL) || (count == 0U) || (count > 3U))
    {
        return PCAL9722_NOT_OK;
    }

    tx_data[0] = PCAL9722_SLAVE_ADDRESS | 0x01U;
    tx_data[1] = PCAL9722_AUTO_INCREMENT | start_reg;
    for (uint8 i = 0U; i < count; i++)
    {
        tx_data[i + 2U] = 0x00U;
    }

    readStatus = ext_SpiRead(0U, tx_data, rx_data, count + 2U);

    if (readStatus == E_OK)
    {
        for (uint8 i = 0U; i < count; i++)
        {
            values[i] = rx_data[i + 2U];
        }
    }

    return (PCAL9722_StatusType)readStatus;
}

PCAL9722_StatusType pcal9722_setPin(uint8 port, uint8 pin, uint8 value)
{
    uint8 reg                       = PCAL9722_REG_OUTPUT_PORT0 + port;
    uint8 port_value                = pcal9722_readRegister(reg);
    PCAL9722_StatusType checkStatus = PCAL9722_OK;

    if (port > PCAL9722_MAX_PORT_NUM)
    {
        checkStatus = PCAL9722_ERROR_PORT;
    }

    if (pin > pcal9722_get_max_pin_for_port(port))
    {
        checkStatus = PCAL9722_ERROR_PIN;
    }

    if (checkStatus == PCAL9722_OK)
    {
        if (value != 0U)
        {
            port_value |= (1U << pin);
        }
        else
        {
            port_value &= ~(1U << pin);
        }
    }

    checkStatus = pcal9722_writeRegister(reg, port_value);

    return checkStatus;
}

uint8 pcal9722_readPin(uint8 port, uint8 pin)
{
    if ((port > PCAL9722_MAX_PORT_NUM) || (pin > pcal9722_get_max_pin_for_port(port)))
    {
        return 0U;
    }

    uint8 reg        = PCAL9722_REG_INPUT_PORT0 + port;
    uint8 port_value = pcal9722_readRegister(reg);

    return (port_value >> pin) & 0x01U;
}

PCAL9722_StatusType pcal9722_initGPIO(uint8 cfg_port0, uint8 cfg_port1, uint8 cfg_port2)
{
    PCAL9722_StatusType writeStatus;

    writeStatus = pcal9722_writeRegister(PCAL9722_REG_CONFIG_PORT0, cfg_port0);

    if (writeStatus == PCAL9722_OK)
    {
        writeStatus = pcal9722_writeRegister(PCAL9722_REG_CONFIG_PORT1, cfg_port1);
    }

    if (writeStatus == PCAL9722_OK)
    {
        writeStatus = pcal9722_writeRegister(PCAL9722_REG_CONFIG_PORT2, cfg_port2);
    }

    return writeStatus;
}

PCAL9722_StatusType pcal9722_setPins(uint8 port, uint8 value)
{
    uint8 reg                       = PCAL9722_REG_OUTPUT_PORT0 + port;
    PCAL9722_StatusType checkStatus = PCAL9722_OK;

    if (port > PCAL9722_MAX_PORT_NUM)
    {
        checkStatus = PCAL9722_ERROR_PORT;
    }

    if (checkStatus == PCAL9722_OK)
    {
        /* Mask the value to ensure only valid pins are set for port 2 */
        if (port == 2U)
        {
            /* Mask to 6 bits (0b00111111) for port 2 (pins 0-5) */
            value &= 0x3FU;
        }

        checkStatus = pcal9722_writeRegister(reg, value);
    }

    return checkStatus;
}

uint8 pcal9722_getPins(uint8 port)
{
    uint8 reg = PCAL9722_REG_INPUT_PORT0 + port;

    if (port > PCAL9722_MAX_PORT_NUM)
    {
        return 0U;
    }

    return pcal9722_readRegister(reg);
}

#ifdef __cplusplus
}
#endif
