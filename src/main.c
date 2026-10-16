/*
 *   Copyright 2025 NXP
 *
 *   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly
 *   in accordance with the applicable license terms.  By expressly accepting
 *   such terms or by downloading, installing, activating and/or otherwise using
 *   the software, you are agreeing that you have read, and that you agree to
 *   comply with and are bound by, such license terms.  If you do not agree to
 *   be bound by the applicable license terms, then you may not retain,
 *   install, activate or otherwise use the software.
 *
 *   This file contains sample code only. It is not part of the production code deliverables.
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
#include "timers.h"
#include "srp_port.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define PDELAY_IDX_OFFSET            (0x0)
#define RRATIO_IDX_OFFSET            (0x1)

#define PORT_COUNT                   (16u)
#define PORT_DATA_ENTRY_SIZE         (8u)
/* In our case pdelay & rratio are written per port. */
#define PORT_DATA_ENTRY_COUNT        (2u)

/* NVM */
#define NVM_SECTOR_SIZE              (4096u)
#define NVM_START_ADDR               (0u)
#define NVM_NUMBER_OF_SECTORS        (1u)
#define NVM_SIZE                     (NVM_SECTOR_SIZE * NVM_NUMBER_OF_SECTORS)

#define gPTPTask_TASK_PRIORITY       (3U)
#define gpioHandleTask_TASK_PRIORITY (3U)

#define gPTPTask_SLEEP_TIME          (2U)
#define ALIVE_LED_TIMER_PERIOD        500U

#define BOOT_LOGGING_ADDRESS         0x2003FFF8
#define PRIMARY_IMAGE_BOOTED_FLAG    0xAA
#define SECONDARY_IMAGE_BOOTED_FLAG  0xBB
#define IMAGE_BOOTED_OFFSET          24U

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef enum
{
    WRITE_PENDING,
    WRITE_ERASE_WAIT,
    WRITE_IN_PROGRESS,
    WRITE_COMPLETE
} write_state_t;

typedef struct
{
    uint8 au8Data[PORT_DATA_ENTRY_SIZE];
    uint8 u16Offset;
    write_state_t eState;
} gptp_nvm_data_t;

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

extern gptp_def_init_params_t rGptpCfgParams;
extern const EthSwt_43_SJA11XX_ConfigType EthSwt_43_SJA11XX_PBCfgVariantPredefined;

static gptp_nvm_data_t sarPerPortData[PORT_COUNT * PORT_DATA_ENTRY_COUNT];
static uint8 sau8NVMBuffer[NVM_SECTOR_SIZE * NVM_NUMBER_OF_SECTORS];
static volatile MemIf_StatusType sveMemStatus  = MEMIF_IDLE;
static volatile write_state_t sveNVMWriteState = WRITE_COMPLETE;
static boolean sbNVMInitialized;
static boolean sbGptpInitialized;

TaskHandle_t gPTPTaskTaskHandle       = NULL;
TaskHandle_t gpioHandleTaskTaskHandle = NULL;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void Eth_Main(void);
static void Eth_Poll(void);
static boolean FLASH_Init(void);
static gptp_err_type_t FLASH_Enqueue_Write(const uint8 cu8Port, const uint8 cu8Offset, const uint32 cu32Length, const uint8 *cpu8Data);
static void FLASH_Write_Poll(void);
static void FLASH_Poll(void);
static void toggleAliveLED(TimerHandle_t xTimer);
static void getImageBooted(void);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/* Check which image booted from the dual banking functionality */
static void getImageBooted(void)
{
    uint64 *boot_log  = (uint64 *)BOOT_LOGGING_ADDRESS;
    uint32 img_booted = *boot_log;

    if ((img_booted >> IMAGE_BOOTED_OFFSET) == PRIMARY_IMAGE_BOOTED_FLAG)
    {
        /* Primary Image booted */
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_GREEN);
    }
    else if ((img_booted >> IMAGE_BOOTED_OFFSET) == SECONDARY_IMAGE_BOOTED_FLAG)
    {
        /* Secondary Image booted */
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_YELLOW);
    }
    else
    {
        /* Boot Error */
        SJA1110_SetRGBLed(SJA1110_LEDCOLOR_RED);
    }
}

static boolean FLASH_Init(void)
{
    uint32 u32PortCacheEntry;
    uint32 u32PortDataEntry;
    boolean bRet = true;
    uint16 u16Offset;
    Std_ReturnType eRetStatus = E_NOT_OK;

    /* Initialize Fls driver. */
    Fls_Init(NULL_PTR);

    /* Read data from external sector. */
    eRetStatus = Fls_Read((Fls_AddressType)NVM_START_ADDR, sau8NVMBuffer, (Fls_LengthType)NVM_SIZE);
    /* Check return status. */
    if (E_OK == eRetStatus)
    {
        /* Wait for job to be processed. */
        do
        {
            FLASH_Poll();
        } while (MEMIF_IDLE != sveMemStatus);
        /* Check job result. */
        if (MEMIF_JOB_OK != Fls_GetJobResult())
        {
            bRet = false;
        }
    }
    else
    {
        bRet = false;
    }

    if (bRet && ((PORT_COUNT * PORT_DATA_ENTRY_COUNT * PORT_DATA_ENTRY_SIZE) <= NVM_SIZE))
    {
        /* Prepare cache default values and cache data. */
        for (u32PortCacheEntry = 0u; u32PortCacheEntry < (PORT_COUNT * PORT_DATA_ENTRY_COUNT); u32PortCacheEntry++)
        {
            u16Offset = (uint16)(PORT_DATA_ENTRY_SIZE * u32PortCacheEntry);

            sarPerPortData[u32PortCacheEntry].eState    = WRITE_COMPLETE;
            sarPerPortData[u32PortCacheEntry].u16Offset = u16Offset;

            for (u32PortDataEntry = 0u; u32PortDataEntry < PORT_DATA_ENTRY_SIZE; u32PortDataEntry++)
            {
                sarPerPortData[u32PortCacheEntry].au8Data[u32PortDataEntry] = sau8NVMBuffer[u16Offset + u32PortDataEntry];
            }
        }
    }
    else
    {
        bRet = false;
    }

    return bRet;
}

static gptp_err_type_t FLASH_Enqueue_Write(const uint8 cu8Port, const uint8 cu8Offset, const uint32 cu32Length, const uint8 *cpu8Data)
{
    const uint32 cu32Idx = ((uint32)PORT_DATA_ENTRY_COUNT * cu8Port) + (uint32)cu8Offset;
    uint32 u32Entry;
    gptp_err_type_t eError = GPTP_ERR_N_UNABLE_NVM_WRITE;

    if ((NVM_SIZE >= (cu32Length + sarPerPortData[cu32Idx].u16Offset)) && (cu32Length <= PORT_DATA_ENTRY_SIZE) && (cu32Idx < (PORT_COUNT * PORT_DATA_ENTRY_COUNT)))
    {
        if (WRITE_COMPLETE == sarPerPortData[cu32Idx].eState)
        {
            /* Entry is ready for new value. */
            for (u32Entry = 0; u32Entry < cu32Length; u32Entry++)
            {
                sarPerPortData[cu32Idx].au8Data[u32Entry]                   = cpu8Data[u32Entry];
                sau8NVMBuffer[sarPerPortData[cu32Idx].u16Offset + u32Entry] = cpu8Data[u32Entry];
            }
            /* Write pending. */
            sarPerPortData[cu32Idx].eState = WRITE_PENDING;
            /* Status is OK. */
            eError = GPTP_ERR_OK;
        }
    }

    return eError;
}

static void FLASH_Write_Poll(void)
{
    boolean bIsWriteInProgress = false;
    uint32 u32PortCacheEntry;

    FLASH_Poll();
    if (MEMIF_IDLE == sveMemStatus)
    {
        if (WRITE_IN_PROGRESS == sveNVMWriteState)
        {
            sveNVMWriteState = WRITE_COMPLETE;
        }

        if (WRITE_ERASE_WAIT == sveNVMWriteState)
        {
            /* Check job result. */
            if (MEMIF_JOB_OK == Fls_GetJobResult())
            {
                /* Write data to external sector. */
                Fls_Write((Fls_AddressType)NVM_START_ADDR, sau8NVMBuffer, (Fls_LengthType)NVM_SIZE);

                sveNVMWriteState = WRITE_IN_PROGRESS;
            }
            else
            {
                /* If block was not erased, do not perform write. */
                sveNVMWriteState = WRITE_COMPLETE;
            }
        }

        if (WRITE_COMPLETE == sveNVMWriteState)
        {
            /* Clear status of previous write. */
            for (u32PortCacheEntry = 0u; u32PortCacheEntry < (PORT_COUNT * PORT_DATA_ENTRY_COUNT); u32PortCacheEntry++)
            {
                if (WRITE_IN_PROGRESS == sarPerPortData[u32PortCacheEntry].eState)
                {
                    sarPerPortData[u32PortCacheEntry].eState = WRITE_COMPLETE;
                }
            }
            /* Write data from cache entry. */
            for (u32PortCacheEntry = 0u; u32PortCacheEntry < (PORT_COUNT * PORT_DATA_ENTRY_COUNT); u32PortCacheEntry++)
            {
                if ((WRITE_PENDING == sarPerPortData[u32PortCacheEntry].eState))
                {
                    bIsWriteInProgress                       = true;
                    sarPerPortData[u32PortCacheEntry].eState = WRITE_IN_PROGRESS;
                }
            }
            if (bIsWriteInProgress)
            {
                sveNVMWriteState = WRITE_PENDING;
            }
        }

        if (WRITE_PENDING == sveNVMWriteState)
        {
            /* Erase all configured sectors.  */
            Fls_Erase(NVM_START_ADDR, NVM_SIZE);

            sveNVMWriteState = WRITE_ERASE_WAIT;
        }
    }
}

static void FLASH_Poll(void)
{
    /* Perform the job.  */
    Fls_MainFunction();

    sveMemStatus = Fls_GetStatus();
}

static void Eth_Main(void)
{
    EthSwt_43_SJA11XX_MainFunction();
    Eth_TxConfirmation(EthConf_EthCtrlConfig_EthCtrlConfig_0);
}

static void Eth_Poll(void)
{
    uint8 u8FifoIdx = 0u;
    Eth_RxStatusType rRxStatus;

    for (u8FifoIdx = 0u; u8FifoIdx < ETH_MAX_RXFIFO_SUPPORTED; u8FifoIdx++)
    {
        /* Receive Rx frames and TX writebacks
                (eg. egress timestamps). */
        Eth_Receive(EthConf_EthCtrlConfig_EthCtrlConfig_0, u8FifoIdx, &rRxStatus);
    }
}

uint8 GPTP_NVMWriteCB(uint8 u8PdelayMachine, gptp_def_nvm_data_t eNvmDataType, float64 f64Value, gptp_def_mem_write_stat *peWriteStat)
{
    uint8 u8Offset;
    uint8 au8Data[PORT_DATA_ENTRY_SIZE];
    uint8 u8Idx;
    uint8 *pu8Value;
    gptp_err_type_t eError = GPTP_ERR_N_UNABLE_NVM_WRITE;

    u8Offset = (uint8)(((gptp_def_nvm_data_t)GPTP_DEF_NVM_PDELAY == eNvmDataType) ? PDELAY_IDX_OFFSET : RRATIO_IDX_OFFSET);

    if (sbNVMInitialized && (NULL != peWriteStat))
    {
        if (GPTP_DEF_MEM_WRITE_INIT == *peWriteStat)
        {
            /* Write should be done. */
            pu8Value = (uint8 *)&f64Value;
            for (u8Idx = 0u; u8Idx < PORT_DATA_ENTRY_SIZE; u8Idx++)
            {
                au8Data[u8Idx] = pu8Value[u8Idx];
            }

            /* Inserting data to FLASH pool. */
            eError = FLASH_Enqueue_Write(u8PdelayMachine, u8Offset, PORT_DATA_ENTRY_SIZE, au8Data);
            if (GPTP_ERR_OK == eError)
            {
                /* Data was inserting for write, changing status to finish. */
                *peWriteStat = GPTP_DEF_MEM_WRITE_FINISH;
            }
        }
        else
        {
            eError = GPTP_ERR_OK;
        }
    }

    return (uint8)eError;
}

uint8 GPTP_NVMReadCB(uint8 u8PdelayMachine, gptp_def_nvm_data_t eNvmDataType, float64_t *pf64Value)
{
    uint8 u8Offset                      = (uint8)(((gptp_def_nvm_data_t)GPTP_DEF_NVM_PDELAY == eNvmDataType) ? PDELAY_IDX_OFFSET : RRATIO_IDX_OFFSET);
    const uint32 cu32Entry              = ((uint32)PORT_DATA_ENTRY_COUNT * u8PdelayMachine) + (uint32)u8Offset;
    uint8 au8Data[PORT_DATA_ENTRY_SIZE] = {0};
    uint8 *pu8Value;
    uint8 u8Idx;
    gptp_err_type_t eError = GPTP_ERR_N_UNABLE_NVM_READ;

    if (sbNVMInitialized && ((PORT_COUNT * PORT_DATA_ENTRY_COUNT) > cu32Entry))
    {
        /* Take data from cache as they are read during initialization and updated. */
        for (u8Idx = 0; u8Idx < PORT_DATA_ENTRY_SIZE; u8Idx++)
        {
            au8Data[u8Idx] = sarPerPortData[cu32Entry].au8Data[u8Idx];
        }

        /* Read was successful. */
        pu8Value = (uint8 *)pf64Value;
        for (u8Idx = 0; u8Idx < PORT_DATA_ENTRY_SIZE; u8Idx++)
        {
            pu8Value[u8Idx] = au8Data[u8Idx];
        }
        eError = GPTP_ERR_OK;
    }

    return (uint8)eError;
}

static void toggleAliveLED(TimerHandle_t xTimer)
{
    uint32 regVal;

    (void) xTimer;

    /* Toggle ALIVE LED */
    regVal = (uint32)(1U << GPIO_PIN_10);

    Switch_Ip_Write(SJA1110_SWT_ID, 1U, (GPIO_TGL_ADDR), &regVal);
}

static void gPTPTask(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        GPTP_TimerPeriodic();
        Eth_Main();
        Eth_Poll();
        SRP_PORT_Periodic();

        /* Poll FLASH write function. */
        FLASH_Write_Poll();

        vTaskDelay(pdMS_TO_TICKS(gPTPTask_SLEEP_TIME));
    }
}

static void gpioHandleTask(void *pvParameters)
{
    uint32 gpioFlags;

    (void)pvParameters;

    while (1)
    {
        /* Read PHY GPIO interrupt flags */
        Switch_Ip_Read(SJA1110_SWT_ID, 1U, (GPIO_REG_IRQ_ADDR), &gpioFlags);

        /* Handle PHY Interrupts */
        HandlePhyInterrupts(gpioFlags);

        /* Handle PCAL9722, PMIC and SFP interrupts */
        HandlePeripheralInterrupts(gpioFlags);

        /* Handle SWT button interrupts */
        HandleButtonInterrupts(gpioFlags);

        if (gpioFlags != 0U)
        {
            /* Clear all interrupt flags */
            Switch_Ip_Write(SJA1110_SWT_ID, 1U, (GPIO_REG_IRQ_ADDR), &gpioFlags);
        }
    }
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

int main(void)
{
    gptp_err_type_t eError;
    Std_ReturnType status;
    TimerHandle_t aliveLEDTimer;

    /* Initialize all the peripherals, PHYs and Switch */
    status = SJA1110_DeviceInit();

    if (status == E_OK)
    {
        /* Initialize the PCAL9722 driver */
        status = SJA1110_PinsInit();
    }

    if (status == E_OK)
    {
        /* Init Done, check which image booted. */
        getImageBooted();

        /* Initialize FLASH cache and FLS. */
        sbNVMInitialized = FLASH_Init();
    }

    /* Set number of clock instances from DS configuration */
    rGptpCfgParams.u8NumberOfClkInstances = EthSwt_43_SJA11XX_PBCfgVariantPredefined.switchDriverConfig->nSwitches;
    rGptpCfgParams.bDoubleClock           = !EthSwt_43_SJA11XX_PBCfgVariantPredefined.switchDriverConfig->ptpConfig->useCorrectedClkforTS;

    /* Initialize gPTP Stack. */
    eError = GPTP_GptpInit(&rGptpCfgParams);
    if (GPTP_ERR_OK == eError)
    {
        sbGptpInitialized = true;
    }

    /* Initialize IEEE 802.1Qat SRP Stack (Bridge Mode: MSRP, MVRP, MMRP + FQTSS/CBS). */
    (void)SRP_PORT_Init();

    if (sbGptpInitialized)
    {
        xTaskCreate(gPTPTask, "gPTPTask", configMINIMAL_STACK_SIZE, NULL, gPTPTask_TASK_PRIORITY, &gPTPTaskTaskHandle);
    }

    xTaskCreate(gpioHandleTask, "gpioHandleTask", configMINIMAL_STACK_SIZE, NULL, gpioHandleTask_TASK_PRIORITY, &gpioHandleTaskTaskHandle);

    aliveLEDTimer = xTimerCreate("toggleAliveLED", ALIVE_LED_TIMER_PERIOD, pdTRUE, NULL, toggleAliveLED);

    xTimerStart(aliveLEDTimer, 0);

    vTaskStartScheduler();

    /* Should never reach here. */
    while (1)
    {
        ;
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
