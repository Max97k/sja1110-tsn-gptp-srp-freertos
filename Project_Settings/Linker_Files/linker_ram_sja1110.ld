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
/*
* GCC Linker Command File:
* Target device: This linker is demo and it is using for device SJA11XX only
* Target core: ARM cortex M7
* Linker support for application running on M7_0 core0 only. It need to align with MPU default setup in core_specific.h and system.c as well.
* Memory setting: Local ram of M7_0 (sram)
*/

/*
* GCC Linker Command File:
* 0x00000000    0x00080000  524288  ITCM (512K)
* 0x20000000    0x20040000  262144  DTCM (256K)
*/
HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00002000;

ENTRY(Reset_Handler)

MEMORY
{
    int_flash               : ORIGIN = 0x00000000, LENGTH = 0
    int_itcm                : ORIGIN = 0x00000000, LENGTH = 0x00080000
    int_dtcm                : ORIGIN = 0x20000000, LENGTH = 0x00040000
    int_sram                : ORIGIN = 0x20000000, LENGTH = 0x00035F00    /* 192KB */
    int_sram_stack_c0       : ORIGIN = 0x20035F00, LENGTH = 0x00002000
    int_sram_results        : ORIGIN = 0x20037F00, LENGTH = 0x00000100
    int_sram_shareable      : ORIGIN = 0x20038000, LENGTH = 0x00008000    /* 32KB */
    ram_rsvd2               : ORIGIN = 0x20040000, LENGTH = 0             /* End of SRAM */
}


SECTIONS
{
    .itcm :
    {
        . = ALIGN(8);
        __user_app_start = .;
        KEEP(*(.core_loop))
        . = ALIGN(8);
        *(.startup)
        . = ALIGN(8);
        *(.text.startup)
        . = ALIGN(8);
        *(.text)
        *(.text*)
        . = ALIGN(8);
        *(.mcal_text)

        . = ALIGN(8);
        KEEP(*(.init))
        . = ALIGN(8);
        KEEP(*(.fini))
        . = ALIGN(8);
        __init_table = .;
        KEEP(*(.init_table))
        . = ALIGN(8);
        __zero_table = .;
        KEEP(*(.zero_table))
    } > int_itcm

    /* Section used by the libgcc.a library for fvp4 */
    .ARM :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > int_itcm

    .acfls_code_rom :
    {
        . = ALIGN(8);
        acfls_code_rom_start = .;
        *(.acfls_code_rom)
        . = ALIGN(8);
        acfls_code_rom_end = .;
    } > int_itcm

    .acfls_code_ram :
    {
        . = ALIGN(8);
        . += (acfls_code_rom_end - acfls_code_rom_start );
    } > int_itcm

    .ramcode :
    {
        . = ALIGN(8);
        *(.aceep_code_rom)
        . = ALIGN(8);
        *(.acmcu_code_rom)
        . = ALIGN(8);
        *(.ramcode)
    } > int_itcm

    . = ALIGN(8);
    __rom_intc_vector_start = .;
    .intc_vector : AT(__rom_intc_vector_start)
    {
        . = ALIGN(2048);
        __interrupts_ram_start = .;
        KEEP(*(.intc_vector))
        . = ALIGN(8);
        __interrupts_ram_end = .;
    } > int_sram
    __rom_intc_vector_end = __rom_intc_vector_start + (__interrupts_ram_end - __interrupts_ram_start);

    __rom_rodata_start = __rom_intc_vector_end;
    .rodata : AT(__rom_rodata_start)
    {
        . = ALIGN(8);
        __sram_rodata_start = .;
        *(.rodata)
        *(.rodata*)
        . = ALIGN(8);
        *(.mcal_const_cfg)
        . = ALIGN(8);
        *(.mcal_const)
        . = ALIGN(8);
        __sram_rodata_end = .;
    } > int_sram
    __rom_rodata_end = __rom_rodata_start + (__sram_rodata_end - __sram_rodata_start);

    __rom_data_start = __rom_rodata_end;
    .sram_data : AT(__rom_data_start)
    {
        . = ALIGN(8);
        __sram_data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(8);
        *(.mcal_data)
        . = ALIGN(8);
        __sram_data_end = .;
    } > int_sram
    __rom_data_end = __rom_data_start + (__sram_data_end - __sram_data_start);

    .sram_bss (NOLOAD):
    {
        . = ALIGN(16);
        __sram_bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(16);
        *(.mcal_bss)
        . = ALIGN(8);
        __sram_bss_end = .;
    } > int_sram

    /* heap section */
    .heap (NOLOAD):
    {
        . += ALIGN(8);
        _end = .;
        end = .;
        _heap_start = .;
        . += HEAP_SIZE;
        _heap_end = .;
    } > int_sram

    .non_cacheable_bss (NOLOAD):
    {
        . = ALIGN(16);
        __non_cacheable_bss_start = .;
        *(.mcal_bss_no_cacheable)
        . = ALIGN(8);
        __non_cacheable_bss_end = .;
    } > int_sram

    __rom_non_cacheable_data_start = __rom_data_end;
    .non_cacheable_data : AT(__rom_non_cacheable_data_start)
    {
        . = ALIGN(8);
        __sram_non_cacheable_data_start = .;
        *(.mcal_data_no_cacheable)
        . = ALIGN(8);
        *(.mcal_const_no_cacheable)
        . = ALIGN(8);
        __sram_non_cacheable_data_end = .;
    } > int_sram
    __rom_non_cacheable_data_end = __rom_non_cacheable_data_start + (__sram_non_cacheable_data_end - __sram_non_cacheable_data_start);

    int_results (NOLOAD):
    {
        . = ALIGN(8);
        KEEP(*(.int_results))
        . += 0x100;
    } > int_sram_results

    .shareable_ram_bss (NOLOAD):
    {
        . = ALIGN(16);
        __shareable_bss_start = .;
        KEEP(*(.mcal_shared_bss))
        . = ALIGN(8);
        __shareable_bss_end = .;
    } > int_sram_shareable

    __rom_shareable_ram_data_start = __rom_non_cacheable_data_end;
    .shareable_ram_data : AT(__rom_shareable_ram_data_start)
    {
        . = ALIGN(16);
        __sram_shareable_ram_data_start = .;
        KEEP(*(.mcal_shared_data))
        . = ALIGN(8);
        __sram_shareable_ram_data_end = .;
    } > int_sram_shareable
    __rom_shareable_ram_data_end = __rom_shareable_ram_data_start + (__sram_shareable_ram_data_end - __sram_shareable_ram_data_start);

    __user_app_end = __rom_shareable_ram_data_end;   /* Define a global symbol for initialized data end for external flash boot configuration */
    /* Boot Image Header*/
    .nvmImageHeaderSectionBlock __user_app_end :
    {
        . = ALIGN(8);
        KEEP(*(.nvmImageHeaderSection))
        . = ALIGN(8);
        __nvmImageHeaderSection_end__ = .;
    } > int_itcm

    __FW_LENGTH = __user_app_end - __user_app_start;

    __Stack_end_c0           = ORIGIN(int_sram_stack_c0);
    __Stack_start_c0         = ORIGIN(int_sram_stack_c0) + LENGTH(int_sram_stack_c0);

    __INT_SRAM_START         = ORIGIN(int_sram);
    __INT_SRAM_END           = ORIGIN(ram_rsvd2);

    __INT_ITCM_START         = ORIGIN(int_itcm);
    __INT_ITCM_END           = ORIGIN(int_itcm) + LENGTH(int_itcm);

    __INT_DTCM_START         = ORIGIN(int_dtcm);
    __INT_DTCM_END           = ORIGIN(int_dtcm) + LENGTH(int_dtcm);

    __RAM_SHAREABLE_START    = ORIGIN(int_sram_shareable);
    __RAM_SHAREABLE_END      = ORIGIN(int_sram_shareable) + LENGTH(int_sram_shareable) - 1;
    __RAM_SHAREABLE_SIZE     = 0xF; /*32 kbyte*/
    __ROM_SHAREABLE_START    = 0;
    __ROM_SHAREABLE_END      = 0;
    __RAM_NO_CACHEABLE_START = 0;
    __RAM_NO_CACHEABLE_END   = 0;
    __RAM_NO_CACHEABLE_SIZE  = 0;
    __ROM_NO_CACHEABLE_START = 0;
    __ROM_NO_CACHEABLE_END   = 0;
    __RAM_CACHEABLE_START    = 0;
    __RAM_CACHEABLE_END      = 0;
    __RAM_CACHEABLE_SIZE     = 0;
    __ROM_CACHEABLE_START    = 0;
    __ROM_CACHEABLE_END      = 0;
    __ROM_CODE_START         = 0;
    __ROM_DATA_START         = 0;

    __BSS_SRAM_START         = __sram_bss_start;
    __BSS_SRAM_END           = __sram_bss_end;
    __BSS_SRAM_SIZE          = __sram_bss_end - __sram_bss_start;

    __BSS_SRAM_NC_START      = __non_cacheable_bss_start;
    __BSS_SRAM_NC_SIZE       = __non_cacheable_bss_end - __non_cacheable_bss_start;
    __BSS_SRAM_NC_END        = __non_cacheable_bss_end;

    __BSS_SRAM_SH_START       = __shareable_bss_start;
    __BSS_SRAM_SH_SIZE        = __shareable_bss_end - __shareable_bss_start;
    __BSS_SRAM_SH_END         = __shareable_bss_end;

    __RAM_INTERRUPT_START    = __interrupts_ram_start;
    __ROM_INTERRUPT_START    = __rom_intc_vector_start;
    __ROM_INTERRUPT_END      = __rom_intc_vector_end;

    __INIT_TABLE             = __init_table;
    __ZERO_TABLE             = __zero_table;

    __RAM_INIT               = 0;
    __ITCM_INIT              = 0;
    __DTCM_INIT              = 0;

    /* Fls module access code support */
    Fls_ACEraseRomStart         = ADDR(.acfls_code_rom);
    Fls_ACEraseRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACEraseSize             = (SIZEOF(.acfls_code_rom)+3) / 4; /* Copy 4 bytes at a time*/

    Fls_ACWriteRomStart         = ADDR(.acfls_code_rom);
    Fls_ACWriteRomEnd           = ADDR(.acfls_code_rom) + SIZEOF(.acfls_code_rom);
    Fls_ACWriteSize             = (SIZEOF(.acfls_code_rom)+3) / 4; /* Copy 4 bytes at a time*/

    _ERASE_FUNC_ADDRESS_        = ADDR(.acfls_code_ram);
    _WRITE_FUNC_ADDRESS_        = ADDR(.acfls_code_ram);

    __ENTRY_VTABLE              = __RAM_INTERRUPT_START;
}
