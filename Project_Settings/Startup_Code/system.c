/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : SJA11XX_RTD_1_0_0_D2306_ASR_REL_4_4_REV_0000_20230616
*
*   Copyright 2021 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/



#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "Mcal.h"
#include "system.h"
#include "core_specific.h"
#include "SJA1110.h"
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

extern  uint32 __INT_ITCM_START[];
extern  uint32 __ROM_CODE_START[];
extern  uint32 __ROM_DATA_START[];
extern  uint32 __INT_DTCM_START[];
extern  uint32 __INT_SRAM_START[];
extern  uint32 __RAM_NO_CACHEABLE_START[];
extern  uint32 __RAM_SHAREABLE_START[];
extern  uint32 __RAM_CACHEABLE_SIZE[];
extern  uint32 __RAM_NO_CACHEABLE_SIZE[];
extern  uint32 __RAM_SHAREABLE_SIZE[];
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define CM7_0  (0UL)
#define CM7_1  (1UL)

#define SVC_GoToSupervisor()      ASM_KEYWORD("svc 0x0")
#define SVC_GoToUser()            ASM_KEYWORD("svc 0x1")

#define S32_FPU_CPACR_CPx_MASK(CpNum)             (0x3U << S32_FPU_CPACR_CPx_SHIFT(CpNum))
#define S32_FPU_CPACR_CPx_SHIFT(CpNum)            (2U*((uint32)CpNum))
#define S32_FPU_CPACR_CPx(CpNum, x)               (((uint32)(((uint32)(x))<<S32_FPU_CPACR_CPx_SHIFT((CpNum))))&S32_FPU_CPACR_CPx_MASK((CpNum)))

/* MPU setting */

/* Single ELF for one or all cores */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (15U)
 volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
 volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================-
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define PLATFORM_START_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"

/* Allocate a global variable which will be overwritten by the debugger if attached(in CMM), to catch the core after reset. */
uint32 RESET_CATCH_CORE;

#define PLATFORM_STOP_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
static void sys_m7_cache_init(void);
static void sys_m7_cache_disable(void);
static void sys_m7_cache_clean(void);
#endif

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void);
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void)
{
    ASM_KEYWORD("push {r0}");
    ASM_KEYWORD("ldr r0, =0x1");
    ASM_KEYWORD("msr CONTROL, r0");
    ASM_KEYWORD("pop {r0}");
}
#endif
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    extern uint32 startup_getControlRegisterValue(void);
    extern uint32 startup_getAipsRegisterValue(void);
    extern void Suspend_Interrupts(void);
    extern void Resume_Interrupts(void);
#endif /*MCAL_ENABLE_USER_MODE_SUPPORT*/


/*================================================================================================*/
/**
* @brief    startup_go_to_user_mode
* @details  Function called from startup.s to switch to user mode if MCAL_ENABLE_USER_MODE_SUPPORT
*           is defined
*/
/*================================================================================================*/
void startup_go_to_user_mode(void);
void startup_go_to_user_mode(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    ASM_KEYWORD("svc 0x1");
#endif
}

/*================================================================================================*/
/**
* @brief   Default IRQ handler
* @details Infinite Loop
*/
/*================================================================================================*/
void default_interrupt_routine(void)
{
    while(TRUE){};
}

/*================================================================================================*/
/**
* @brief Sys_GoToSupervisor
* @details function used to enter to supervisor mode.
*           check if it's needed to switch to supervisor mode and make the switch.
*           Return 1 if switch was done
*/
/*================================================================================================*/

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
uint32 Sys_GoToSupervisor(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;
    uint32 u32SwitchToSupervisor;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        u32SwitchToSupervisor = 0U;
    }
    else
    {
        u32SwitchToSupervisor = 1U;
        SVC_GoToSupervisor();
    }

    return u32SwitchToSupervisor;
}

/*================================================================================================*/
/**
* @brief Sys_GoToUser_Return
* @details function used to switch back to user mode for Thread mode, return a uint32 value passed as parameter
*/
/*================================================================================================*/
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue)
{
    if (1UL == u32SwitchToSupervisor)
    {
        Direct_GoToUser();
    }

    return u32returnValue;
}

uint32 Sys_GoToUser(void)
{
    Direct_GoToUser();
    return 0UL;
}
/*================================================================================================*/
/**
* @brief Sys_SuspendInterrupts
* @details Suspend Interrupts
*/
/*================================================================================================*/
void Sys_SuspendInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Suspend_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x3");
    }
}
/*================================================================================================*/
/**
* @brief Sys_ResumeInterrupts
* @details Resume Interrupts
*/
/*================================================================================================*/
void Sys_ResumeInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Resume_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x2");
    }
}
#endif
/*================================================================================================*/
/**
* @brief Sys_GetCoreID
* @details Function used to get the ID of the currently executing thread
*/
/*================================================================================================*/
#if !defined(USING_OS_AUTOSAROS)
uint8 Sys_GetCoreID(void)
{
    return 0;
}
#endif

/*================================================================================================*/
/*
 * system initialization : system clock, interrupt router ...
 */


void SystemInit(void)
{
#ifndef DISABLE_MPU
    uint8 regionNum = 0U;
    uint8 index = 0U;
#endif /* DISABLE_MPU */

/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
#ifdef ENABLE_FPU
    /* Enable CP10 and CP11 coprocessors */
    S32_FPU->CPACR |= (S32_FPU_CPACR_CPx(10U, 3U) | S32_FPU_CPACR_CPx(11U, 3U));

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /* ENABLE_FPU */

#ifndef DISABLE_MPU
/**************************************************************************/
                      /* DEFAULT MEMORY ENABLE*/
/**************************************************************************/
    /* Init MPU table for memory layout*/
    /* Cover all memory on device as background set all memory as strong-order and no access*/
    rbar[0]=0x00000000UL;
    rasr[0]=0x1004003FUL;

    /* ITCM for cortex M7 if no set it as zero */
    rbar[1]=(uint32)__INT_ITCM_START;
    rasr[1]=0x03040001UL|(((uint32)19 - 1) << 1); /* Strongly-Ordered */
    /*Program flash which would extract from linker symbol*/
    rbar[2]=(uint32)__ROM_CODE_START;
    rasr[2]=0x0; /*Disable rom code section due to code store on ITCM only*/

    /*Data flash which would extract from linker symbol*/
    rbar[3]=(uint32)__ROM_DATA_START;
    rasr[3]=0x0;  /*disable rom data section due to code store on DTCM only*/

    /*DTCM for cortex m7 if no set it as zero*/
    rbar[4]=(uint32)__INT_DTCM_START;
    rasr[4]=0x030C0001UL|(((uint32)18 - 1) << 1); /* Normal, Non-cacheable, Shareable, XN */

    /*Ram unified section  + stack*/
    rbar[5]=(uint32)__INT_SRAM_START;
    rasr[5]=0; /*disable int_sram_start section due to use TCM only*/

    /*Ram non-cache section plus int result which is using for test report*/
    rbar[6]=(uint32)__RAM_NO_CACHEABLE_START;
    rasr[6]=0; /*disable ram non cache section due to SJA1110 does not support cache*/

    /*Ram shareable section*/
    rbar[7]=(uint32)__RAM_SHAREABLE_START;
    rasr[7]=((uint32)0x030C0001UL)|(((uint32)__RAM_SHAREABLE_SIZE - 1) << 1); /* Normal, Non-cacheable, Shareable, XN */
    /* Additional configuration for peripheral device*/

    /*AIPS_0*/
    rbar[8]=0x40000000UL;
    rasr[8]=0x13050029UL; /* Shared Device, XN */

    /*QuadSPI_device AHB*/
    rbar[9]=0x40100000UL;
    rasr[9]=0x13050035UL;  /* Shared Device, XN */

    /*Private memory space*/
    rbar[10]=0xE0000000UL;
    rasr[10]=0x13040027UL; /* Strongly-Ordered, XN */

    /*sytem region*/
    rbar[11]=0xFF700000UL;
    rasr[11]=0x13050035UL;  /* Shared Device, XN */

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");

#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
    /*Checking if cache is enable before*/
    if (((((uint32)1U << (uint32)17U) & S32_SCB->CCR) != (uint32)0) || ((((uint32)1U << (uint32)16U) & S32_SCB->CCR) != (uint32)0))
    {
 /*synchronize cache before update mpu */
        sys_m7_cache_clean();
        sys_m7_cache_disable();
    }
#endif

    /* Disable MPU before configuring regions */
    S32_MPU->CTRL &= ~S32_MPU_CTRL_ENABLE_MASK;

    /* Set default memory regions */
    for (index = 0U; index < 15; index++)
    {
        if ((rasr[index]&(uint32)0x1) == (uint32)0x1)
        {
            S32_MPU->RNR  = regionNum;
            S32_MPU->RBAR = rbar[index];
            S32_MPU->RASR = rasr[index];
            regionNum++;
        }
    }

    /* Enable MPU */
    S32_MPU->CTRL |= S32_MPU_CTRL_ENABLE_MASK;

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /* DISABLE_MPU */

/**************************************************************************/
            /* ENABLE CACHE */
/**************************************************************************/
#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
    sys_m7_cache_init();
#endif
}


#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
static void sys_m7_cache_init(void)
{
#ifdef D_CACHE_ENABLE
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;

    /*init Data caches*/
    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    ASM_KEYWORD("dsb");
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do
    {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
        do
        {
            S32_SCB->DCISW = (((sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk) |
                              ((ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk)  );
            ASM_KEYWORD("dsb");
        } while (ways-- != 0U);
    } while(sets-- != 0U);
    ASM_KEYWORD("dsb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_DC_Msk;  /* enable D-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif

#ifdef I_CACHE_ENABLE
    /*init Code caches*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_IC_Msk;  /* enable I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif
    sys_m7_cache_clean();
}

static void sys_m7_cache_disable(void)
{
    sys_m7_cache_clean();
    S32_SCB->CCR &= ~((uint32)1U << 17U);
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->CCR &= ~((uint32)1U << 16U);
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
}

static void sys_m7_cache_clean(void)
{
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;

    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    ASM_KEYWORD("dsb");
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do
    {
        ways = (uint32)(CCSIDR_WAYS(ccsidr));
        do
        {
            S32_SCB->DCCISW = (((sets << 5) & (uint32)0x3FE0U) |
                               ((ways << 30) & (uint32)0xC0000000U));
            ASM_KEYWORD("dsb");
        } while (ways-- != 0U);
    } while(sets-- != 0U);

    S32_SCB->CSSELR = (uint32)((S32_SCB->CSSELR) | 1U);
    S32_SCB->ICIALLU = 0UL;
    ASM_KEYWORD("dsb");
}
#endif

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#ifdef __cplusplus
}
#endif
