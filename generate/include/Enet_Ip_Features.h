/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : ENET
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : SJA11XX_RTD_1_0_1_P02_HF01_D2510_ASR_REL_4_4_REV_0000_20251021
*
*   Copyright 2021-2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be  used strictly in accordance with the applicable license terms.  By expressly  accepting such terms or by downloading, installing, activating and/or otherwise  using the software, you are agreeing that you have read, and that you agree to  comply with and are bound by, such license terms.  If you do not agree to be  bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.
==================================================================================================*/

#ifndef ENET_IP_FEATURES_H
#define ENET_IP_FEATURES_H

/**
*   @file
*
*   @addtogroup ENET_DRIVER_CONFIGURATION ENET Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*
* @page misra_violations MISRA-C:2012 violations
* 
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ENET_IP_FEATURES_VENDOR_ID                    43
#define ENET_IP_FEATURES_AR_RELEASE_MAJOR_VERSION     4
#define ENET_IP_FEATURES_AR_RELEASE_MINOR_VERSION     4
#define ENET_IP_FEATURES_AR_RELEASE_REVISION_VERSION  0
#define ENET_IP_FEATURES_SW_MAJOR_VERSION             1
#define ENET_IP_FEATURES_SW_MINOR_VERSION             0
#define ENET_IP_FEATURES_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
    /*! @brief Number of instances */
    #define FEATURE_ENET_NUM_INSTANCES                      (1U)
    
    /*! @brief Number of channels */
    #define FEATURE_ENET_NUM_RINGS                          (1U)
    
    /*! @brief Tx Fifo memory */
    #define FEATURE_ENET_TX_POOL_SIZE                       (4096U)
    
    /*! @brief Rx Fifo memory */
    #define FEATURE_ENET_RX_POOL_SIZE                       (4096U)
    
    /*! @brief Number of channels for timer */
    #define FEATURE_ENET_CHANNEL_COUNT                      (4U)
    
    /*! @brief Size of each block in Fifo */
    #define FEATURE_ENET_MTL_FIFO_BLOCK_SIZE                (8U)
    
    /*! @brief Sleep Wakeup Mode is supported */
    #define FEATURE_ENET_HAS_SLEEP_WAKEUP                   (0U)
    
    /*! @brief Input Capture is supported */
    #define FEATURE_ENET_HAS_INPUT_CAPTURE                  (0U)
    
    /*! @brief The transmission interrupts */
    #define FEATURE_ENET_TX_IRQS                            { { {ENET_TX_BUFFER_IRQn, ENET_TX_FRAME_IRQn} } }
    
    /*! @brief The reception interrupts */
    #define FEATURE_ENET_RX_IRQS                            { { {ENET_RX_BUFFER_IRQn, ENET_RX_FRAME_IRQn} } }
    
    /*! @brief ENET error IRQ number for each instance. */
    #define FEATURE_ENET_ERR_IRQS                           { {ENET_RX_ERR_IRQn, ENET_TX_UNDER_IRQn, ENET_BUS_ERR_IRQn, ENET_TX_BABB_IRQn, ENET_RX_BABB_IRQn} }
    
    /*! @brief ENET timer IRQ number for each instance. */
    #define FEATURE_ENET_TIMESTAMP_IRQS                     { {ENET_TS_TIMER_IRQn} }
    
    /*! @brief The transmit interrupt handlers */
    #define FEATURE_ENET_TX_IRQ_HDLRS                       { {ENET0_RING0_TX_IRQHandler} }
    
    /*! @brief The receive interrupt handlers */
    #define FEATURE_ENET_RX_IRQ_HDLRS                       { {ENET0_RING0_RX_IRQHandler} }
    
    /*! @brief The error interrupt handlers */
    #define FEATURE_ENET_ERR_IRQ_HDLRS                      { {ENET0_ERR_IRQHandler} }
    
    /*! @brief The timestamp interrupt handlers */
    #define FEATURE_ENET_TIMESTAMP_IRQ_HDLRS                { {ENET0_TIMESTAMP_IRQHandler} }
    
    /*! @brief Definition used for aligning the buffer descriptors */
    #define FEATURE_ENET_BUFFDESCR_ALIGNMENT_BYTES          (16U)
    
    /*! @brief Definition used for aligning the buffer data */
    #define FEATURE_ENET_BUFFDATA_ALIGNMENT_BYTES           (64U) 
    
    /*! @brief Definition used for aligning the buffer length */
    #define FEATURE_ENET_BUFFLEN_ALIGNMENT_BYTES            (16U)

    /*! @brief Definition used for number of interrupt vectors for error */
    #define FEATURE_ENET_NUM_INT_ERR                        (5U) 
    /*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ENET_IP_FEATURES_H */

