/*
 *  Copyright 2025 NXP
 *
 *  NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only
 *  be used strictly in accordance with the applicable license terms. By
 *  expressly accepting such terms or by downloading, installing, activating
 *  and/or otherwise using the software, you are agreeing that you have read,
 *  and that you agree to comply with and are bound by, such license terms. If
 *  you do not agree to be bound by the applicable license terms, then you may
 *  not retain, install, activate or otherwise use the software.
 *
 *  This file contains sample code only. It is not part of the production code deliverables.
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

#include "example_init.h"
#include "pcal/pcal9722.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define MMD30_VS1                              30U
#define DEVICE_CONTROL_ADDRESS                 0x0040U
#define DEVICE_RESET                           0x8000U

#define SJA_TJA1121B_ADDRESS                   1U
#define SJA_TJA1121A_ADDRESS                   2U

/* SJA1110 Ethernet Controller ID */
#define ETH_CTRL_ID                            0U

/* SJA1110-MGS Switch ID */
#define SJA1110_SWT_ID                         0U

#define IRQ_TJA1104B                           2U
#define IRQ_TJA1121A                           3U
#define IRQ_TJA1121B                           4U
#define IRQ_TJA1230                            5U
#define IRQ_PMIC                               6U
#define IRQ_PCAL9722                           7U
#define IRQ_SFP_ABSENT                         9U
#define IRQ_SWT_BUTTON1                        11U
#define IRQ_SWT_BUTTON2                        12U

#define PHY_SGMII_P4                           1U
#define PHY_TJA1121B                           6U
#define PHY_TJA1121A                           5U
#define PHY_100BASET1_P5                       2U
#define PHY_100BASET1_P6                       3U
#define PHY_100BASET1_P7                       4U

#define SW0_P1                                 0U
#define SW0_P2                                 1U
#define SW0_P4                                 3U
#define SW0_P5                                 4U
#define SW0_P6                                 5U
#define SW0_P7                                 6U

#define PCAL9722_CFG0                          0x6U
#define PCAL9722_CFG1                          0x00
#define PCAL9722_CFG2                          0xFF

#define SJA_FW_TJA1121_PMA_MMD                 1U
#define SJA_FW_TJA1121_PMA_STATUS_ADDR         0x0008U
#define SJA_FW_TJA1121_PMA_STATUS_PRESENT_MASK 0xC000U
#define SJA_FW_TJA1121_PMA_STATUS_PRESENT_FLAG 0x8000U

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

extern const gptp_def_init_params_t rGptpCfgParams;
extern const EthSwt_43_SJA11XX_ConfigType EthSwt_43_SJA11XX_PBCfgVariantPredefined;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void TJA1121_Reset(uint8 phyAddress);
static void TJA1121_Wait(uint8 phyAddress);
static void StartPtpClk(void);
static void SJA1110_WritePin(uint8 pin, uint16 value);
static Std_ReturnType SJA1110_EthSwt_Init(void);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

static void StartPtpClk(void)
{
    Std_ReturnType rStatus;
    static EthSwt_43_SJA11XX_PtpTimeType srStartTime;
    static bool bStartPtpClk = true;

    if (true == bStartPtpClk)
    {
        rStatus = EthSwt_43_SJA11XX_GetPtpClk(0u, &srStartTime);
        if ((Std_ReturnType)E_OK == rStatus)
        {
            srStartTime.seconds    += 1u;
            srStartTime.nanoSeconds = 0u;

            EthSwt_43_SJA11XX_StartPtpMediaClk(SJA1110_SWT_ID, &srStartTime);

            bStartPtpClk = false;
        }
    }
}

void HandlePhyInterrupts(uint32 gpioFlags)
{
    if (gpioFlags & (1U << IRQ_TJA1104B))
    {
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_BLUE);
    }
    if (gpioFlags & (1U << IRQ_TJA1121B))
    {
        Phy_Ip_MainFunction(PHY_TJA1121B);
    }
    if (gpioFlags & (1U << IRQ_TJA1121A))
    {
        Phy_Ip_MainFunction(PHY_TJA1121A);
    }
    if (gpioFlags & (1U << IRQ_TJA1230))
    {
    }
}

void HandlePeripheralInterrupts(uint32 gpioFlags)
{
    static volatile boolean sgmiiPhySuspended = FALSE;

    if (gpioFlags & (1U << IRQ_PMIC))
    {
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_YELLOW);
    }

    if (gpioFlags & (1U << IRQ_PCAL9722))
    {
    }

    if (gpioFlags & (1U << IRQ_SFP_ABSENT))
    {
        Phy_Ip_Suspend(PHY_SGMII_P4);
        sgmiiPhySuspended = TRUE;
    }
    else
    {
        /* Resume the PHY only if it was suspended to avoid
         * unnecessary Phy_Ip_Resume calls. */
        if (TRUE == sgmiiPhySuspended)
        {
            Phy_Ip_Resume(PHY_SGMII_P4);
            sgmiiPhySuspended = FALSE;
        }
    }
}

extern void SRP_PORT_RunSelfTest(void);

void HandleButtonInterrupts(uint32 gpioFlags)
{
    if (gpioFlags & (1U << IRQ_SWT_BUTTON1))
    {
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_MAGENTA);
        SRP_PORT_RunSelfTest();
    }

    if (gpioFlags & (1U << IRQ_SWT_BUTTON2))
    {
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_CYAN);
    }
}

static void TJA1121_Reset(uint8 phyAddress)
{

    uint32 timeOut = 0xFFFF;
    uint16 reg     = 0U;

    /* Reset the PHY */
    Eth_ReadMmd(ETH_CTRL_ID, phyAddress, MMD30_VS1, DEVICE_CONTROL_ADDRESS, &reg);
    Eth_WriteMmd(ETH_CTRL_ID, phyAddress, MMD30_VS1, DEVICE_CONTROL_ADDRESS, (reg | DEVICE_RESET));
    /* Delay added in order to reset the PHY */
    do
    {
        Eth_ReadMmd(ETH_CTRL_ID, phyAddress, MMD30_VS1, DEVICE_CONTROL_ADDRESS, &reg);
        timeOut--;
    } while ((DEVICE_RESET == (reg & DEVICE_RESET)) && (0U < timeOut));

    return;
}

static void TJA1121_Wait(uint8 phyAddress)
{
    uint32 timeOut = 0xFFFF;
    uint16 reg     = 0U;

    do
    {
        Eth_ReadMmd(ETH_CTRL_ID, phyAddress, SJA_FW_TJA1121_PMA_MMD, SJA_FW_TJA1121_PMA_STATUS_ADDR, &reg);
        timeOut--;
    } while (((reg & SJA_FW_TJA1121_PMA_STATUS_PRESENT_MASK) != SJA_FW_TJA1121_PMA_STATUS_PRESENT_FLAG) && (0U < timeOut));
}

static void SJA1110_WritePin(uint8 pin, uint16 value)
{
    uint32 regVal;

    Switch_Ip_Read(SJA1110_SWT_ID, 1U, (GPIO_REG_ADDR), &regVal);

    regVal &= (uint32)(~(1UL << pin));
    regVal |= (uint32)(value << pin);

    Switch_Ip_Write(SJA1110_SWT_ID, 1U, (GPIO_REG_ADDR), &regVal);
}

Phy_Ip_StatusType linkUpEventCallback(uint8 phy, Phy_Ip_IrqSourceType irqSrc, Phy_Ip_IrqDefaultActionType alreadyExecutedAction)
{
    (void)irqSrc;
    (void)alreadyExecutedAction;
    PCAL9722_StatusType status = PCAL9722_OK;

    if (phy == PHY_TJA1121B)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P1, TRUE);
    }
    else if (phy == PHY_TJA1121A)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P2, TRUE);
    }
    else if (phy == PHY_SGMII_P4)
    {
        /* SW1_P4_LED has swapped polarity. */
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P4, FALSE);
    }
    else if (phy == PHY_100BASET1_P5)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P5, TRUE);
    }
    else if (phy == PHY_100BASET1_P6)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P6, TRUE);
    }
    else if (phy == PHY_100BASET1_P7)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P7, TRUE);
    }

    return (Phy_Ip_StatusType)status;
}

Phy_Ip_StatusType linkDownEventCallback(uint8 phy, Phy_Ip_IrqSourceType irqSrc, Phy_Ip_IrqDefaultActionType alreadyExecutedAction)
{
    (void)irqSrc;
    (void)alreadyExecutedAction;
    PCAL9722_StatusType status = PCAL9722_OK;

    if (phy == PHY_TJA1121B)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P1, FALSE);
    }
    else if (phy == PHY_TJA1121A)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P2, FALSE);
    }
    else if (phy == PHY_SGMII_P4)
    {
        /* SW1_P4_LED has swapped polarity. */
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P4, TRUE);
    }
    else if (phy == PHY_100BASET1_P5)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P5, FALSE);
    }
    else if (phy == PHY_100BASET1_P6)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P6, FALSE);
    }
    else if (phy == PHY_100BASET1_P7)
    {
        status = pcal9722_setPin(PCA9722_PORT1, SW0_P7, FALSE);
    }

    return (Phy_Ip_StatusType)status;
}

/*!
 * @brief   Initialize SJA1110 Ethernet Switch with pre-compile mode support
 *
 * @details This function performs SJA1110 switch initialization in a special
 *          sequence required for pre-compile mode.
 *
 *          Initialization sequence:
 *          1. First EthSwt_43_SJA11XX_Init() call sets the internal
 *             EthSwt_43_SJA11XX_pConfigPtr to allow Deinit to work properly
 *          2. EthSwt_43_SJA11XX_Deinit() resets the switch hardware
 *          3. Second EthSwt_43_SJA11XX_Init() call reinitializes the
 *             configuration pointer for final initialization
 *          4. EthSwt_43_SJA11XX_SwitchInit() fully configures the switch
 *
 * @return  Std_ReturnType
 * @retval  E_OK        Switch initialized successfully
 * @retval  E_NOT_OK    Error during deinit or init
 */
static Std_ReturnType SJA1110_EthSwt_Init(void)
{
    Std_ReturnType status;

    /* First Init call: Set EthSwt_43_SJA11XX_pConfigPtr != NULL_PTR
     * This is necessary so that EthSwt_43_SJA11XX_Deinit() will reset the switch.
     * In pre-compile mode, without this call, the pointer could be invalid. */
    EthSwt_43_SJA11XX_Init(NULL_PTR);

    /* Reset the Switch. */
    status = EthSwt_43_SJA11XX_Deinit();

    if (E_OK == status)
    {
        /* Second Init call: Re-initialize EthSwt_43_SJA11XX_pConfigPtr
         * After Deinit, the configuration pointer must be reset for
         * final initialization. This call prepares the driver for
         * complete switch configuration. */
        EthSwt_43_SJA11XX_Init(NULL_PTR);

        /* Initialize the Switch. */
        status = EthSwt_43_SJA11XX_SwitchInit(SJA1110_SWT_ID);
    }

    return status;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void SJA1110_SetRGBLed(sja1110_ledColor ledColor)
{
    SJA1110_WritePin(SWT0_LEDRGB_RED, ((uint8)ledColor) & 0x1U);
    SJA1110_WritePin(SWT0_LEDRGB_GREEN, (((uint8)ledColor) & 0x2U) >> 1U);
    SJA1110_WritePin(SWT0_LEDRGB_BLUE, (((uint8)ledColor) & 0x4U) >> 2U);
}

Std_ReturnType SJA1110_DeviceInit(void)
{
    Std_ReturnType status;

    OsIf_Init(NULL_PTR);

    /* Initialize the Mcu driver. */
    Mcu_Init(NULL);
    /* Initialize the clock tree and apply PLL as system clock. */
    Mcu_InitClock(McuClockSettingConfig_0);
    while (MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
        /* Busy wait until the System PLL is locked. */
        ;
    }
    Mcu_DistributePllClock();
    Mcu_SetMode(McuModeSettingConf_0);

    /* Initialize all pins using the Port driver */
    Port_Init(NULL_PTR);

    /* Initialize Spi driver. */
    Spi_Init(NULL);

    /* Initialize Eth driver */
    Eth_Init(NULL_PTR);

    /* Enable the Eth controller */
    status = Eth_SetControllerMode(EthConf_EthCtrlConfig_EthCtrlConfig_0, ETH_MODE_ACTIVE);

    if (E_OK == status)
    {
        status = SJA1110_EthSwt_Init();
    }

    if (E_OK == status)
    {
        Switch_Ip_InitMgmt();

        status = Switch_Ip_InitPtp();
    }

    if (E_OK == status)
    {
        /* Initialize Gpt. */
        Gpt_Init(&Gpt_Config_BOARD_InitPeripherals);

        /* Reset the TJA1121 PHYs because if they are initialized without it, check_fusa fails. */
        TJA1121_Reset(SJA_TJA1121B_ADDRESS);
        TJA1121_Reset(SJA_TJA1121A_ADDRESS);

        /* Wait for the TJA1121 PHYs to be operational. */
        TJA1121_Wait(SJA_TJA1121B_ADDRESS);
        TJA1121_Wait(SJA_TJA1121A_ADDRESS);

        /* Initialize the PHYs. */
        EthTrcv_43_PHY_Init(NULL_PTR);

        /* Initialize Platform driver. */
        Platform_Init(NULL_PTR);
    }

    if (true == rGptpCfgParams.pcrDomainsSyncsParam->bDomainIsGm)
    {
        StartPtpClk();
    }

    return status;
}

Std_ReturnType SJA1110_PinsInit(void)
{
    Std_ReturnType status;

    /* Init PCAL9722
     * Link LEDs are OFF
     * Port0 and Port2 PINS use default configuration */
    status = pcal9722_setPins(PCA9722_PORT1, INIT_PORT_MASK);

    if (status == E_OK)
    {
        status = pcal9722_initGPIO(PCAL9722_CFG0, PCAL9722_CFG1, PCAL9722_CFG2);
    }

    return status;
}

Std_ReturnType GPTP_StartPtpClk(void)
{
    static EthSwt_43_SJA11XX_PtpTimeType srStartTime;
    Std_ReturnType                       status;

    status = EthSwt_43_SJA11XX_GetPtpClk(0u, &srStartTime);

    if ((Std_ReturnType)E_OK == status)
    {
        srStartTime.seconds += 1u;
        srStartTime.nanoSeconds = 0u;

        status = EthSwt_43_SJA11XX_StartPtpMediaClk(SJA1110_SWT_ID, &srStartTime);
    }

    return status;
}

/*!
 * @brief           This function stops PTP CLK.
 *
 * @details         Stops PTP CLK on all configured switches.
*/
Std_ReturnType GPTP_StopPtpClk(void)
{
    Std_ReturnType status;

    status = EthSwt_43_SJA11XX_StopPtpMediaClk(SJA1110_SWT_ID);

    return status;
}

#ifdef __cplusplus
}
#endif
