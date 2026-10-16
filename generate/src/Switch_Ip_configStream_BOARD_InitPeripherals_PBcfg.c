/*==================================================================================================
*   Project            : RTD AUTOSAR 4.4
*   Platform           : N/A
*   Peripheral         : SJA11XX
*   Dependencies       : none
*
*   AutosarVersion     : 4.4.0
*   AutosarRevision    : ASR_REL_4_4_REV_0000
*   AutosarConfVariant :
*   SW Version         : 1.0.2
*   BuildVersion       : SJA11XX_RTD_1_0_2_D2604_ASR_REL_4_4_REV_0000_20260421
*
*   Copyright 2026 NXP Semiconductors
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
*   @file Switch_Ip_configStream_PBcfg.c
*
*   @addtogroup switch_driver_configuration SWITCH Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Switch_Ip_Types.h"
#include "Switch_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWITCH_IP_CONFIGSTREAM_PBCFG_VENDOR_ID_C                     43
#define SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define SWITCH_IP_CONFIGSTREAM_PBCFG_SW_MAJOR_VERSION_C              1
#define SWITCH_IP_CONFIGSTREAM_PBCFG_SW_MINOR_VERSION_C              0
#define SWITCH_IP_CONFIGSTREAM_PBCFG_SW_PATCH_VERSION_C              2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Switch_Ip_Types.h */
#if (SWITCH_IP_CONFIGSTREAM_PBCFG_VENDOR_ID_C != SWITCH_IP_TYPES_VENDOR_ID)
    #error "Switch_Ip_configStream_PBcfg.c and Switch_Ip_Types.h have different vendor ids"
#endif
#if ((SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_CONFIGSTREAM_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_configStream_PBcfg.c and Switch_Ip_Types.h are different"
#endif
#if ((SWITCH_IP_CONFIGSTREAM_PBCFG_SW_MAJOR_VERSION_C != SWITCH_IP_TYPES_SW_MAJOR_VERSION) || \
     (SWITCH_IP_CONFIGSTREAM_PBCFG_SW_MINOR_VERSION_C != SWITCH_IP_TYPES_SW_MINOR_VERSION) || \
     (SWITCH_IP_CONFIGSTREAM_PBCFG_SW_PATCH_VERSION_C != SWITCH_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_configStream_PBcfg.c and Switch_Ip_Types.h are different"
#endif


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/
#define ETHSWT_43_SJA11XX_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"

uint32 switchConfigData0[506U];

uint32 switchConfigData0[506U] = {
	0xb700030fU,0x06000000U,0x000000dcU,0x86e02ce8U,0xffffec00U,
	0x007fffffU,0xffffec00U,0x027fffffU,0xffffec00U,0x047fffffU,
	0xffffec00U,0x067fffffU,0xffffec00U,0x087fffffU,0xffffec00U,
	0x0a7fffffU,0xffffec00U,0x0c7fffffU,0xffffec00U,0x0e7fffffU,
	0xffffec00U,0x107fffffU,0xffffec00U,0x127fffffU,0xffffec00U,
	0x147fffffU,0xffffec00U,0x167fffffU,0xffffec00U,0x187fffffU,
	0xffffec00U,0x1a7fffffU,0xffffec00U,0x1c7fffffU,0xffffec00U,
	0x1e7fffffU,0xffffec00U,0x207fffffU,0xffffec00U,0x227fffffU,
	0xffffec00U,0x247fffffU,0xffffec00U,0x267fffffU,0xffffec00U,
	0x287fffffU,0xffffec00U,0x2a7fffffU,0xffffec00U,0x2c7fffffU,
	0xffffec00U,0x2e7fffffU,0xffffec00U,0x307fffffU,0xffffec00U,
	0x327fffffU,0xffffec00U,0x347fffffU,0xffffec00U,0x367fffffU,
	0xffffec00U,0x387fffffU,0xffffec00U,0x3a7fffffU,0xffffec00U,
	0x3c7fffffU,0xffffec00U,0x3e7fffffU,0xffffec00U,0x407fffffU,
	0xffffec00U,0x427fffffU,0xffffec00U,0x447fffffU,0xffffec00U,
	0x467fffffU,0xffffec00U,0x487fffffU,0xffffec00U,0x4a7fffffU,
	0xffffec00U,0x4c7fffffU,0xffffec00U,0x4e7fffffU,0xffffec00U,
	0x507fffffU,0xffffec00U,0x527fffffU,0xffffec00U,0x547fffffU,
	0xffffec00U,0x567fffffU,0xffffec00U,0x587fffffU,0xffffec00U,
	0x5a7fffffU,0xffffec00U,0x5c7fffffU,0xffffec00U,0x5e7fffffU,
	0xffffec00U,0x607fffffU,0xffffec00U,0x627fffffU,0xffffec00U,
	0x647fffffU,0xffffec00U,0x667fffffU,0xffffec00U,0x687fffffU,
	0xffffec00U,0x6a7fffffU,0xffffec00U,0x6c7fffffU,0xffffec00U,
	0x6e7fffffU,0xffffec00U,0x707fffffU,0xffffec00U,0x727fffffU,
	0xffffec00U,0x747fffffU,0xffffec00U,0x767fffffU,0xffffec00U,
	0x787fffffU,0xffffec00U,0x7a7fffffU,0xffffec00U,0x7c7fffffU,
	0xffffec00U,0x7e7fffffU,0xffffec00U,0x807fffffU,0xffffec00U,
	0x827fffffU,0xffffec00U,0x847fffffU,0xffffec00U,0x867fffffU,
	0xffffec00U,0x887fffffU,0xffffec00U,0x8a7fffffU,0xffffec00U,
	0x8c7fffffU,0xffffec00U,0x8e7fffffU,0xffffec00U,0x907fffffU,
	0xffffec00U,0x927fffffU,0xffffec00U,0x947fffffU,0xffffec00U,
	0x967fffffU,0xffffec00U,0x987fffffU,0xffffec00U,0x9a7fffffU,
	0xffffec00U,0x9c7fffffU,0xffffec00U,0x9e7fffffU,0xffffec00U,
	0xa07fffffU,0xffffec00U,0xa27fffffU,0xffffec00U,0xa47fffffU,
	0xffffec00U,0xa67fffffU,0xffffec00U,0xa87fffffU,0xffffec00U,
	0xaa7fffffU,0xffffec00U,0xac7fffffU,0xffffec00U,0xae7fffffU,
	0xffffec00U,0xb07fffffU,0xffffec00U,0xb27fffffU,0xffffec00U,
	0xb47fffffU,0xffffec00U,0xb67fffffU,0xffffec00U,0xb87fffffU,
	0xffffec00U,0xba7fffffU,0xffffec00U,0xbc7fffffU,0xffffec00U,
	0xbe7fffffU,0xffffec00U,0xc07fffffU,0xffffec00U,0xc27fffffU,
	0xffffec00U,0xc47fffffU,0xffffec00U,0xc67fffffU,0xffffec00U,
	0xc87fffffU,0xffffec00U,0xca7fffffU,0xffffec00U,0xcc7fffffU,
	0xffffec00U,0xce7fffffU,0xffffec00U,0xd07fffffU,0xffffec00U,
	0xd27fffffU,0xffffec00U,0xd47fffffU,0xffffec00U,0xd67fffffU,
	0xffffec00U,0xd87fffffU,0xffffec00U,0xda7fffffU,0xbda25ad8U,
	0x08000000U,0x00000026U,0xd00b644aU,0x00000000U,0xffdffbffU,
	0x80000000U,0xffbff7feU,0x80000000U,0xff7feffdU,0x80000000U,
	0xfeffdffbU,0x80000000U,0xfdffbff7U,0x80000000U,0xfbff7fefU,
	0x80000000U,0xf7feffdfU,0x80000000U,0xeffdffbfU,0x80000000U,
	0xdffbff7fU,0x80000000U,0xbff7feffU,0x80000000U,0x7feffdffU,
	0x40000000U,0x00000000U,0xc0000000U,0x24924924U,0x40000000U,
	0x49249249U,0xc0000000U,0x6db6db6dU,0x40000000U,0x92492492U,
	0xc0000000U,0xb6db6db6U,0x40000000U,0xdb6db6dbU,0xc0000000U,
	0xffffffffU,0x5be6e94cU,0x09000000U,0x00000058U,0x668b9a55U,
	0xc0000000U,0xff000000U,0x00000000U,0x08fc0103U,0xbf404fe4U,
	0xe017fb02U,0x06ff40cfU,0xfff03bfcU,0xc0000000U,0xff000001U,
	0x00000000U,0x08fc0102U,0xbf404fe4U,0xe017fb02U,0x06ff40cfU,
	0xfff03bfcU,0xc0000000U,0xff000000U,0x00000000U,0x08fc0102U,
	0xbf404fe4U,0xe017fb02U,0x06ff40cfU,0xfff03bfcU,0xc0000000U,
	0xff000000U,0x00000000U,0x08fc0103U,0xbf404fe4U,0xe017fb02U,
	0x06ff40cfU,0xfff03bfcU,0xc0000000U,0xff000000U,0x00000000U,
	0x08fc0102U,0xbf404fe4U,0xe017fb02U,0x06ff40cfU,0xfff03bfcU,
	0xc0000000U,0xff000000U,0x00000000U,0x08fc0103U,0xbf404fe4U,
	0xe017fb02U,0x06ff40cfU,0xfff03bfcU,0xc0000000U,0xff000000U,
	0x00000000U,0x08fc0103U,0xbf404fe4U,0xe017fb02U,0x06ff40cfU,
	0xfff03bfcU,0xc0000000U,0xff000000U,0x00000000U,0x08fc0103U,
	0xbf404fe4U,0xe017fb02U,0x06ff40cfU,0xfff03bfcU,0xc0000000U,
	0xff000000U,0x00000000U,0x08fc0103U,0xbf404fe4U,0xe017fb02U,
	0x06ff40cfU,0xfff03bfcU,0xc0000000U,0xff000000U,0x00000000U,
	0x08fc0103U,0xbf404fe4U,0xe017fb02U,0x06ff40cfU,0xfff03bfcU,
	0xc0000000U,0xff000000U,0x00000000U,0x08fc0103U,0xbf404fe4U,
	0xe017fb02U,0x06ff40cfU,0xfff03bfcU,0xf1fda1b8U,0x0d000000U,
	0x00000007U,0x00652361U,0x00000000U,0x00000000U,0x08010000U,
	0x10020040U,0x20040080U,0x40080100U,0x00000000U,0x0b2f86b2U,
	0x0e000000U,0x00000003U,0xc8a7cee6U,0x0000e380U,0x00000000U,
	0xe0000000U,0x05cf8e51U,0x10000000U,0x00000004U,0x8aa0dfbcU,
	0x00000000U,0x00000000U,0x00038000U,0x40603080U,0x382aaa95U,
	0x11000000U,0x0000000eU,0xd87d1668U,0x78090000U,0x17181000U,
	0x82000013U,0x000001e3U,0x88a84080U,0xffffffffU,0x00000000U,
	0x00000002U,0x00000000U,0x00000000U,0xff800000U,0xffffffffU,
	0xffffffffU,0xc3ffffffU,0x63af416eU,0x1a000000U,0x00000001U,
	0xf7ce372fU,0xb0000000U,0xea256c90U,0x1b000000U,0x00000046U,
	0xcc6d7e1bU,0x00000000U,0x01000c00U,0x00fc0000U,0x00000000U,
	0x00000000U,0xfff10000U,0xfe7f3dffU,0x00000000U,0x00000000U,
	0x000e0000U,0x0180c200U,0x00000000U,0x00000000U,0x77080c00U,
	0x00000000U,0x00000000U,0x00000000U,0x88f70000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000c00U,0x00fc0100U,0x00000000U,
	0x00000000U,0xfff10000U,0xfe7f3dffU,0x00000000U,0x00000000U,
	0x000e0000U,0x0180c200U,0x00000000U,0x00000000U,0x77080000U,
	0x00000000U,0x00000000U,0x00000000U,0x88f70000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0x00000000U,0x00000000U,0x00000000U,0x00000000U,
	0x00000000U,0xab09f2afU,0x1c000000U,0x0000000bU,0x173322ebU,
	0xfac68800U,0xfac68800U,0xfac68800U,0xfac68800U,0xfac68800U,
	0xfac68800U,0xfac68800U,0xfac68800U,0xfac68800U,0xfac68800U,
	0xfac68800U,0xf23e954cU,0x4e000000U,0x00000002U,0x28e8f1caU,
	0x2b400000U,0x000000bbU,0x1618028bU,0x00000000U,0x00000000U,
	0x8d6bab3cU

};

Switch_Ip_BinaryConfigType switchConfig0 = {
    switchConfigData0,
    506U
};

#define ETHSWT_43_SJA11XX_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
