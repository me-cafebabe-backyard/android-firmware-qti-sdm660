/*
==============================================================================

FILE:         ClockBSP.c 

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/sdm660/cdsp/ClockBSP.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"


/*=========================================================================
      Data Declarations
==========================================================================*/


/*
 *  SourceFreqConfig_XO
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_XO[] =
{
  {
    /* .nFreqHz    = */  19200 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_SLEEPCLK
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_SLEEPCLK[] =
{
  {
    /* .nFreqHz    = */  32768,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_TURINGPLL0_DIV2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_TURINGPLL0_DIV2[] =
{
  {
    /* .nFreqHz    = */  307200 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_TURINGPLL0 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};



/*
 *  SourceFreqConfig_TURINGPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_TURINGPLL0[] =
{
  {
    /* .nFreqHz    = */  307200000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  2,
      /* .nL             = */  32,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_TURINGPLL1
 *
 *  Set of source frequency configurations.
 */
ClockSourceFreqConfigType SourceFreqConfig_TURINGPLL1[] =
{
  {
    /* .nFreqHz    = */  576000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  30,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  595200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  31,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  652800 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  34,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  748800 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  39,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  787200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  41,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  960000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  50,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 * SourceConfig
 *
 * Clock source configuration data.
 */
const ClockSourceConfigType SourceConfig[] =
{
  {
    SOURCE_NAME(XO),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_XO,
  },
  {
    SOURCE_NAME(SLEEPCLK),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_SLEEPCLK,
  },
  {
    SOURCE_NAME(TURINGPLL0_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_TURINGPLL0_DIV2,
  },
  {
    SOURCE_NAME(TURINGPLL0),

    /* .nConfigMask       = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                                CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE |
                                CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE,
    /* .pSourceFreqConfig = */  SourceFreqConfig_TURINGPLL0,

  },
  {
    SOURCE_NAME(TURINGPLL1),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_TURINGPLL1,
    /* .pCalibrationFreqConfig = */ &SourceFreqConfig_TURINGPLL1[3],
  },
  { 0 }
};



/*----------------------------------------------------------------------*/
/* TURING Clock Configurations                                           */
/*----------------------------------------------------------------------*/


/*
 * AON clock configurations
 */
const ClockMuxConfigType AONClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,               2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   38400000, { HAL_CLK_SOURCE_TURINGPLL0_DIV2, 16,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   51200000, { HAL_CLK_SOURCE_TURINGPLL0_DIV2, 12,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   76800000, { HAL_CLK_SOURCE_TURINGPLL0_DIV2,  8,      0,      0,      0       }, VCS_CORNER_LOW,               },
  {  102400000, { HAL_CLK_SOURCE_TURINGPLL0_DIV2,  6,      0,      0,      0       }, VCS_CORNER_LOW,               },
  {  153600000, { HAL_CLK_SOURCE_TURINGPLL0,       8,      0,      0,      0       }, VCS_CORNER_NOMINAL,           },
  {  204800000, { HAL_CLK_SOURCE_TURINGPLL0,       6,      0,      0,      0       }, VCS_CORNER_NOMINAL,           },
  { 0 }
};


/*
 * QOSFIXEDLATCOUNTERSRC clock configurations
 */
const ClockMuxConfigType QOSFIXEDLATCOUNTERSRCClockConfig[] =
{
  {  122880000, { HAL_CLK_SOURCE_TURINGPLL0, 2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  { 0 }
};


/*
 * Clock Log Default Configuration.
 *
 * NOTE: An .nGlobalLogFlags value of 0x12 will log only clock frequency
 *       changes and source state changes by default.
 */
const ClockLogType ClockLogDefaultConfig[] =
{
  {
    /* .nLogSize        = */ 4096,
    /* .nGlobalLogFlags = */ 0x12
  }
};


/*
 * Clock Flag Init Config.
 */
const ClockFlagInitType ClockFlagInitConfig[] =
{
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"XO",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"TURINGPLL0_DIV2",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void*)"TURINGPLL1",
    CLOCK_FLAG_SUPPORTS_SLEWING | CLOCK_FLAG_SOURCE_CALIBRATED
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"turing_q6core",
    CLOCK_FLAG_SUPPRESSIBLE | CLOCK_FLAG_DOMAIN_HOLD_VREG_REQUEST
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"q6ss_ahbm_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"q6ss_ahbs_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_bus_timeout_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_mpu_cfg_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_q6_ahbm_mpu_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_qos_ahbs_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"turing_wrapper_sysnoc_sway_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_NONE,
    (void *)0,
    0
  }
};

