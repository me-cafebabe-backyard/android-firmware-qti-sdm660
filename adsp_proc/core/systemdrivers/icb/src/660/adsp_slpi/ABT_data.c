/*==============================================================================

FILE:      ABT_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/icb/src/660/adsp_slpi/ABT_data.c#1 $ 
$DateTime: 2020/02/10 01:57:30 $
$Author: pwbldsvc $
$Change: 22511909 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2016/09/26  bc     Added support for 660
2016/02/08  bc     Added support for 8998
2013/11/14  tb     Added support for multiple enable/status registers and
                   ported for 8994
2013/04/16  pm     Added interrupt priority  
2012/10/04  av     Support for disabling ABT 
2012/05/31  av     Created
 
        Copyright (c) 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "ABTimeout.h"
#include "ABTimeout_HWIO.h"

/*============================================================================
                      TARGET AND PLATFORM SPECIFIC DATA
============================================================================*/

/* Base address for devices */
#define ABT_LPASS0_BASE_ADDR  LPASS_AHBE_TIME_REG_BASE
#define ABT_LPASS1_BASE_ADDR  LPASS_AHBI_TIME_REG_BASE 
#define ABT_LPASS2_BASE_ADDR  LPASS_AHBL_TIME_REG_BASE
#define ABT_LPASS3_BASE_ADDR  LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT_REG_BASE

/* Bit Mask for ABT Slaves */
#define ABT_LPASS0_BMSK   HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBE_TIMEOUT0_SHFT
#define ABT_LPASS1_BMSK   HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBI_TIMEOUT1_SHFT
#define ABT_LPASS2_BMSK   (HWIO_TCSR_TIMEOUT_INTR_STATUS1_LPASS_IRQ_OUT_AHBL_TIMEOUT_SHFT + 32) // status-1 register
#define ABT_LPASS3_BMSK   HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHBS_TIMEOUT_1_SHFT

/* ABT Slave CLK Name */
#define ABT_LPASS0_CLK   NULL
#define ABT_LPASS1_CLK   "audio_core_core_clk"
#define ABT_LPASS2_CLK   "audio_core_qdsp_sway_aon_clk"
#define ABT_LPASS3_CLK   "island_scc_sensor_core_core_clk"

/* ABT Slave PWR domain Name */
#define ABT_LPASS0_PD   "VDD_AUDIO_CORE"
#define ABT_LPASS1_PD   NULL
#define ABT_LPASS2_PD   NULL
#define ABT_LPASS3_PD   NULL


/* Timeout Interrupt Register Address */
#define ABT_TIMEOUT_INTR_LPASS_ENABLE  HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR
#define ABT_TIMEOUT_INTR_LPASS_ENABLE1 HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR
#define ABT_TIMEOUT_INTR_STATUS        HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR
#define ABT_TIMEOUT_INTR_STATUS1       HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR
#define ABT_TIMEOUT_SLAVE_GLB_EN       HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR

/* TCSR Summary Interrupt Vectors */
#define ABT_TCSR_LPASS_INTR_VECTOR     90

/* LPASS Interrupt Priority (Note:  This varies with the processor, as DAL    */
/*                                  passes this through to the underlying     */
/*                                  kernel/OS                                 */
#define ABT_LPASS_INTR_PRIORITY     1


/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/*---------------------------------------------------------------------------*/
/*          Properties data for device ID  = "/dev/ABTimeout"                */
/*---------------------------------------------------------------------------*/

/* ABT Configuration Data*/
static ABT_slave_info_type ABT_cfgdata[] = 
{ 
//ABT_SLAVE_INFO(  name, sl_en, int_en, to_val)
  ABT_SLAVE_INFO(LPASS0,  TRUE,   TRUE,   0xFF),//  LPASS AHBE
  ABT_SLAVE_INFO(LPASS1,  TRUE,   TRUE,   0xFF), //  LPASS AHBI
  ABT_SLAVE_INFO(LPASS2,  TRUE,   TRUE,   0xFF),//  LPASS AHBL
  ABT_SLAVE_INFO(LPASS3,  TRUE,   TRUE,   0xFF) //  LPASS AHBS
};

/* ABT interrupt enable array */
static void *intrEnable[] =
{
  (void*)ABT_TIMEOUT_INTR_LPASS_ENABLE,
  (void*)ABT_TIMEOUT_INTR_LPASS_ENABLE1,
};

/* ABT interrupt status array */
static void *intrStatus[] =
{
  (void*)ABT_TIMEOUT_INTR_STATUS,
  (void*)ABT_TIMEOUT_INTR_STATUS1,
};

/* ABT Platform Data type */
static ABT_platform_info_type ABT_platform_info =
{
    "LPASS",                               /* Image name */
    intrEnable,                               /* INTR Enable address */
    intrStatus,                               /* INTR Status Register address */
    (void*)ABT_TIMEOUT_SLAVE_GLB_EN,       /* ABT Slave global en address */
    ABT_TCSR_LPASS_INTR_VECTOR,            /* ABT TCSR Summary interrupt vector */
    ABT_LPASS_INTR_PRIORITY,               /* ABT LPASS Interrupt priority */
    sizeof(intrEnable)/sizeof(intrEnable[0]), /* Number of interrupt enable/status registers */
};


/* ABT Configuration Property Data*/
ABT_propdata_type ABT_propdata = 
{
    /* Length of the config  data array */
    sizeof(ABT_cfgdata)/sizeof(ABT_slave_info_type), 
    /* Pointer to config data array */ 
    ABT_cfgdata,
    /* Pointer to platform info data */ 
    &ABT_platform_info                                    
};

