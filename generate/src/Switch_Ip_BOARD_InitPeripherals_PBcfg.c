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
*   @file Switch_Ip_PBcfg.c
*
*   @addtogroup switch_driver_configuration SWITCH Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Switch_Ip_Cfg.h"
#include "Switch_Ip_SJA1110.h"
#include "Switch_Ip_Register_Access.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWITCH_IP_PBCFG_VENDOR_ID_C                     43
#define SWITCH_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define SWITCH_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C      4
#define SWITCH_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define SWITCH_IP_PBCFG_SW_MAJOR_VERSION_C              1
#define SWITCH_IP_PBCFG_SW_MINOR_VERSION_C              0
#define SWITCH_IP_PBCFG_SW_PATCH_VERSION_C              2

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Switch_Ip_Cfg.h */
#if (SWITCH_IP_PBCFG_VENDOR_ID_C != SWITCH_IP_CFG_VENDOR_ID)
    #error "Switch_Ip_PBcfg.c and Switch_Ip_Cfg.h have different vendor ids"
#endif
#if ((SWITCH_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_Cfg.h are different"
#endif
#if ((SWITCH_IP_PBCFG_SW_MAJOR_VERSION_C != SWITCH_IP_CFG_SW_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_MINOR_VERSION_C != SWITCH_IP_CFG_SW_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_PATCH_VERSION_C != SWITCH_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_Cfg.h are different"
#endif

/* Checks against Switch_Ip_SJA1110.h */
#if (SWITCH_IP_PBCFG_VENDOR_ID_C != SWITCH_IP_SJA1110_VENDOR_ID)
    #error "Switch_Ip_PBcfg.c and Switch_Ip_SJA1110.h have different vendor ids"
#endif
#if ((SWITCH_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_SJA1110_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_SJA1110_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_SJA1110_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_SJA1110.h are different"
#endif
#if ((SWITCH_IP_PBCFG_SW_MAJOR_VERSION_C != SWITCH_IP_SJA1110_SW_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_MINOR_VERSION_C != SWITCH_IP_SJA1110_SW_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_PATCH_VERSION_C != SWITCH_IP_SJA1110_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_SJA1110.h are different"
#endif

/* Checks against Switch_Ip_Register_Access.h */
#if (SWITCH_IP_PBCFG_VENDOR_ID_C != SWITCH_IP_REGISTER_ACCESS_VENDOR_ID)
    #error "Switch_Ip_PBcfg.c and Switch_Ip_Register_Access.h have different vendor ids"
#endif
#if ((SWITCH_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != SWITCH_IP_REGISTER_ACCESS_AR_RELEASE_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C    != SWITCH_IP_REGISTER_ACCESS_AR_RELEASE_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != SWITCH_IP_REGISTER_ACCESS_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_Register_Access.h are different"
#endif
#if ((SWITCH_IP_PBCFG_SW_MAJOR_VERSION_C != SWITCH_IP_REGISTER_ACCESS_SW_MAJOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_MINOR_VERSION_C != SWITCH_IP_REGISTER_ACCESS_SW_MINOR_VERSION) || \
     (SWITCH_IP_PBCFG_SW_PATCH_VERSION_C != SWITCH_IP_REGISTER_ACCESS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Switch_Ip_PBcfg.c and Switch_Ip_Register_Access.h are different"
#endif


/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*! @brief Switch driver types */
#define SWITCH_TYPE_SJA1110            (0U)

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define ETHSWT_43_SJA11XX_START_SEC_VAR_INIT_8
#include "EthSwt_43_SJA11XX_MemMap.h"

/**
* @brief    Switch Ethernet type for management frames
*/
uint8 mgmtEthType[2U] = { 0x8B, 0x8C };

#define ETHSWT_43_SJA11XX_STOP_SEC_VAR_INIT_8
#include "EthSwt_43_SJA11XX_MemMap.h"

#define ETHSWT_43_SJA11XX_START_SEC_VAR_INIT_32
#include "EthSwt_43_SJA11XX_MemMap.h"

/**
* @brief    Spi sequences used for switch external access.
*/
#define ETHSWT_43_SJA11XX_STOP_SEC_VAR_INIT_32
#include "EthSwt_43_SJA11XX_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETHSWT_43_SJA11XX_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"

/**
* @brief    Switch driver state structure which holds driver runtime data.
*
*/
Switch_Ip_StateType switchState[1U];

/**
* @brief        Ports configuration structure.
*/
static const Switch_Ip_PortType switchPortConfigOfSwt0[9U] =
{
    {
        /* Index PHY instance connected to the port */
        (uint8)255U,
        /* No PHY connected */
        (boolean)TRUE,
        /* Physical Number of port */
        (uint8)0U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        MII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)0U,
        /* No PHY connected */
        (boolean)FALSE,
        /* Physical Number of port */
        (uint8)1U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_1_GBPS,
        (boolean)FALSE,
        SGMII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)255U,
        /* No PHY connected */
        (boolean)TRUE,
        /* Physical Number of port */
        (uint8)2U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_1_GBPS,
        (boolean)FALSE,
        RGMII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)255U,
        /* No PHY connected */
        (boolean)TRUE,
        /* Physical Number of port */
        (uint8)3U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        SGMII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)255U,
        /* No PHY connected */
        (boolean)TRUE,
        /* Physical Number of port */
        (uint8)4U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_1_GBPS,
        (boolean)FALSE,
        SGMII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)2U,
        /* No PHY connected */
        (boolean)FALSE,
        /* Physical Number of port */
        (uint8)5U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        MII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)3U,
        /* No PHY connected */
        (boolean)FALSE,
        /* Physical Number of port */
        (uint8)6U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        MII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)4U,
        /* No PHY connected */
        (boolean)FALSE,
        /* Physical Number of port */
        (uint8)7U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        MII_MODE
    },
    {
        /* Index PHY instance connected to the port */
        (uint8)255U,
        /* No PHY connected */
        (boolean)TRUE,
        /* Physical Number of port */
        (uint8)8U,
        /* Array containing the MAC addresses of the port */
        { 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 },
        SWITCH_PORT_SPEED_100_MBPS,
        (boolean)FALSE,
        MII_MODE
    }
};

/**
* @brief    Hardware access structure for switch 0
*/
static const Switch_Ip_HwAccessType switchHwAccess0 =
{
    SWITCH_CONTROL_INTERNAL,
    Switch_Ip_InternalWrite,
    Switch_Ip_InternalRead
};


/**
* @brief    Switch configuration structure
*/
const Switch_Ip_ConfigType switchConfig[1U] =
{
    {
        &Switch_Ip_driver_SJA1110,
        SJA1110A,
        &switchHwAccess0,
        NULL_PTR,
        &switchConfig0,
        switchPortConfigOfSwt0,
        (uint8)9U,
        (uint8)0U,
        (uint8)255U,
        (uint8)255U,
        (uint8)255U,
        (uint8)0U
    }
};

/**
* @brief    Switch port mirroring configuration
*/
const Switch_Ip_VlanTagType switch0IngressMirrCfg[9U] =
{
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    },
    {
        (uint16)0U,
        (uint8)0U,
        (boolean)FALSE
    }
};
const Switch_Ip_PortMirrVlanConfigType switchPortMirrCfg[1U] =
{
    {
        {
            (uint16)0U,
            (uint8)0U,
            (boolean)FALSE
        },
        switch0IngressMirrCfg
    }
};

/**
* @brief    Switch Management configuration
*/
Switch_Ip_MgmtConfigType switchMgmtConfig =
{
    mgmtEthType
};

/**
* @brief    Switch PTP configuration
*/
const Switch_Ip_PtpConfigType switchPtpConfig =
{
    (uint8)0U,
    (uint64)0U,
    (float64)0U,
    (float64)0U,
    (boolean)TRUE,
    (uint32)62500000U
};

/**
* @brief    Switch driver configuration structure
*/
const Switch_Ip_DriverConfigType switchDriverConfig =
{
    (uint8)1U,
    switchConfig,
    switchPortMirrCfg,
    &switchMgmtConfig,
    &switchPtpConfig
};

#define ETHSWT_43_SJA11XX_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "EthSwt_43_SJA11XX_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
