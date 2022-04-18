/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock BSP data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/sdm660/adsp_slpi/ClockBSP.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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
 *  SourceFreqConfig_AUDREF
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_AUDREF[] =
{
  {
    /* .nFreqHz    = */  9600000,
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
 *  SourceFreqConfig_XO
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_XO[] =
{
  {
    /* .nFreqHz    = */  19200000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL0[] =
{
  {
    /* .nFreqHz    = */  564480000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  2,
      /* .nL             = */  58,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0xCCCCCCCC,
      /* .nAlphaU        = */  0x000000CC,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL0_DIV2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL0_DIV2[] =
{
  {
    /* .nFreqHz    = */  282240000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL0 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL2[] =
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
    /* .eVRegLevel = */  VCS_CORNER_LOW_MIN,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL2_DIV2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL2_DIV2[] =
{
  {
    /* .nFreqHz    = */  307700000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL2 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MIN,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL1
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL1[] =
{
  {
    /* .nFreqHz    = */  614400000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
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
  {
    /* .nFreqHz    = */  652800000,
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
    /* .nFreqHz    = */  748800000,
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
    /* .nFreqHz    = */  844800000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  44,
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
    /* .nFreqHz    = */  864000000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  45,
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
    /* .nFreqHz    = */  998400000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  52,
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
 *  SourceFreqConfig_SCCPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_SCCPLL0[] =
{
  {
    /* .nFreqHz    = */  249593856,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_SLEEPCLK,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  7617,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MIN,
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
    SOURCE_NAME(AUDREF),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_AUDREF,
  },
  {
    SOURCE_NAME(SLEEPCLK),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_SLEEPCLK,
  },
  {
    SOURCE_NAME(XO),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_XO,
  },
  {
    SOURCE_NAME(LPAPLL0),

    /* .nConfigMask       = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL0,
  },
  {
    SOURCE_NAME(LPAPLL0_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL0_DIV2,
  },
  {
    SOURCE_NAME(LPAPLL1),

    /* .nConfigMask            = */ 0,
    /* .pSourceFreqConfig      = */ SourceFreqConfig_LPAPLL1,
    /* .pCalibrationFreqConfig = */ &SourceFreqConfig_LPAPLL1[2],
  },
  {
    SOURCE_NAME(LPAPLL2),

    /* .nConfigMask       = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE     |
                                CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE |
                                CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL2,
  },
  {
    SOURCE_NAME(LPAPLL2_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL2_DIV2,
  },
  {
    SOURCE_NAME(SCCPLL0),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_SCCPLL0,
  },
  { 0 }
};


/*----------------------------------------------------------------------*/
/* LPASS clock configurations                                           */
/*----------------------------------------------------------------------*/

/*
 * AON clock configurations
 */
const ClockMuxConfigType AONClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,           2,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   49918771, { HAL_CLK_SOURCE_SCCPLL0,     10,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   99837542, { HAL_CLK_SOURCE_SCCPLL0,      5,    0,    0,    0 }, VCS_CORNER_LOW       },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2, 4,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {  204800000, { HAL_CLK_SOURCE_LPAPLL2,      6,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * CORE clock configurations
 */
const ClockMuxConfigType COREClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,            2,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   49918771, { HAL_CLK_SOURCE_SCCPLL0,      10,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   99837542, { HAL_CLK_SOURCE_SCCPLL0,       5,    0,    0,    0 }, VCS_CORNER_LOW       },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,  4,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {  204800000, { HAL_CLK_SOURCE_LPAPLL2,       6,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * ATIME clock configurations
 */
const ClockMuxConfigType ATIMEClockConfig[] =
{
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   30720000, { HAL_CLK_SOURCE_LPAPLL2,       8,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {   61440000, { HAL_CLK_SOURCE_LPAPLL2,       4,    0,    0,    0 }, VCS_CORNER_LOW       },
  {  122880000, { HAL_CLK_SOURCE_LPAPLL2,       2,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * SLIMBUS clock configurations
 */
/*
SLIMBUS uses LOW and NOM corners also,but we are not voting since voltage requirements
are taken care by BUSES team
*/
const ClockMuxConfigType SLIMBUSClockConfig[] =
{
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};


/*
 * MCLK clock configurations
 */
const ClockMuxConfigType MCLKClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MINUS },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW       },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 10,    1,    5,    5 }, VCS_CORNER_LOW       },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};

/*
 * INTMCLK0 clock configurations
 */
const ClockMuxConfigType INTMCLK0ClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 10,    1,    5,    5 }, VCS_CORNER_LOW_MINUS },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};

/*
 * INTMCLK1 clock configurations
 */
const ClockMuxConfigType INTMCLK1ClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};

/*
 * INTI2S01 clock configurations
 */
const ClockMuxConfigType INTI2S01ClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MINUS },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW       },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 10,    1,    5,    5 }, VCS_CORNER_LOW       },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * LPAIFPCMOE clock configurations
 */
const ClockMuxConfigType LPAIFPCMOEClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MIN   },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 10,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  { 0 }
};

/*
 * LPAIF clock configurations
 */
const ClockMuxConfigType LPAIFClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,      30,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 20,    1,    5,    5 }, VCS_CORNER_LOW_MINUS },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,      20,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,      30,    0,    0,    0 }, VCS_CORNER_LOW       },
  {    9600000, { HAL_CLK_SOURCE_XO,            4,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2, 10,    1,    5,    5 }, VCS_CORNER_LOW       },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,      20,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   15360000, { HAL_CLK_SOURCE_LPAPLL2,      16,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2,      10,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};

/*
 * LPAIF clock configurations
 */
const ClockMuxConfigType LPAIFEBITClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   30,   30 }, VCS_CORNER_LOW_MIN   },
  {     352800, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   50,   50 }, VCS_CORNER_LOW_MIN   },
  {     384000, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {     512000, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   15,   15 }, VCS_CORNER_LOW_MIN   },
  {     705600, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   25,   25 }, VCS_CORNER_LOW_MIN   },
  {     768000, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    1024000, { HAL_CLK_SOURCE_EXTERNAL,      30,    1,    8,    8 }, VCS_CORNER_LOW_MIN   },
  {    1411200, { HAL_CLK_SOURCE_EXTERNAL,      20,    1,   20,   20 }, VCS_CORNER_LOW_MIN   },
  {    1536000, { HAL_CLK_SOURCE_EXTERNAL,      32,    1,    5,    5 }, VCS_CORNER_LOW_MIN   },
  {    2048000, { HAL_CLK_SOURCE_EXTERNAL,      30,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    2822400, { HAL_CLK_SOURCE_EXTERNAL,      20,    1,   10,   10 }, VCS_CORNER_LOW_MIN   },
  {    3072000, { HAL_CLK_SOURCE_EXTERNAL,      20,    1,    4,    4 }, VCS_CORNER_LOW_MIN   },
  {    4096000, { HAL_CLK_SOURCE_EXTERNAL,      30,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    5644800, { HAL_CLK_SOURCE_EXTERNAL,      20,    1,    5,    5 }, VCS_CORNER_LOW_MINUS },
  {    6144000, { HAL_CLK_SOURCE_EXTERNAL,      20,    1,    2,    2 }, VCS_CORNER_LOW_MINUS },
  {    8192000, { HAL_CLK_SOURCE_EXTERNAL,      30,    0,    0,    0 }, VCS_CORNER_LOW       },
  {    9600000, { HAL_CLK_SOURCE_EXTERNAL,      4,     0,    0,    0 }, VCS_CORNER_LOW       },
  {   11289600, { HAL_CLK_SOURCE_EXTERNAL,      10,    1,    5,    5 }, VCS_CORNER_LOW       },
  {   12288000, { HAL_CLK_SOURCE_EXTERNAL,      20,    0,    0,    0 }, VCS_CORNER_LOW       },
  {   15360000, { HAL_CLK_SOURCE_EXTERNAL,      16,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  {   24576000, { HAL_CLK_SOURCE_EXTERNAL,      10,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};

/*
 * LPAIFQUAD clock configurations
 */
const ClockMuxConfigType LPAIFQUADClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_LPAPLL2,        32,     1,      30,     30      }, VCS_CORNER_LOW_MIN,   },
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   32,     1,      50,     50      }, VCS_CORNER_LOW_MIN,   },
  {     384000, { HAL_CLK_SOURCE_LPAPLL2,        32,     1,      20,     20      }, VCS_CORNER_LOW_MIN,   },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2,        32,     1,      15,     15      }, VCS_CORNER_LOW_MIN,   },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   32,     1,      25,     25      }, VCS_CORNER_LOW_MIN,   },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2,        32,     1,      10,     10      }, VCS_CORNER_LOW_MIN,   },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2,        30,     1,      8,      8       }, VCS_CORNER_LOW_MIN,   },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   20,     1,      20,     20      }, VCS_CORNER_LOW_MIN,   },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2,        32,     1,      5,      5       }, VCS_CORNER_LOW_MIN,   },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2,        30,     1,      4,      4       }, VCS_CORNER_LOW_MIN,   },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   20,     1,      10,     10      }, VCS_CORNER_LOW_MIN,   },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2,        20,     1,      4,      4       }, VCS_CORNER_LOW_MIN,   },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2,        30,     1,      2,      2       }, VCS_CORNER_LOW_MINUS, },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   20,     1,      5,      5       }, VCS_CORNER_LOW_MINUS, },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2,        20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS, },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2,        30,     0,      0,      0       }, VCS_CORNER_LOW,       },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, VCS_CORNER_LOW,       },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV2,   10,     1,      5,      5       }, VCS_CORNER_LOW,       },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2,        20,     0,      0,      0       }, VCS_CORNER_LOW,       },
  { 0 }
};

/*
 * LPAIFQUADEBIT clock configurations
 */
const ClockMuxConfigType LPAIFQUADEBITClockConfig[] =
{
  {     256000, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      30,     30      }, VCS_CORNER_LOW_MIN,   },
  {     352800, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      50,     50      }, VCS_CORNER_LOW_MIN,   },
  {     384000, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      20,     20      }, VCS_CORNER_LOW_MIN,   },
  {     512000, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      15,     15      }, VCS_CORNER_LOW_MIN,   },
  {     705600, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      25,     25      }, VCS_CORNER_LOW_MIN,   },
  {     768000, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      10,     10      }, VCS_CORNER_LOW_MIN,   },
  {    1024000, { HAL_CLK_SOURCE_EXTERNAL,        30,     1,      8,      8       }, VCS_CORNER_LOW_MIN,   },
  {    1411200, { HAL_CLK_SOURCE_EXTERNAL,        20,     1,      20,     20      }, VCS_CORNER_LOW_MIN,   },
  {    1536000, { HAL_CLK_SOURCE_EXTERNAL,        32,     1,      5,      5       }, VCS_CORNER_LOW_MIN,   },
  {    2048000, { HAL_CLK_SOURCE_EXTERNAL,        30,     1,      4,      4       }, VCS_CORNER_LOW_MIN,   },
  {    2822400, { HAL_CLK_SOURCE_EXTERNAL,        20,     1,      10,     10      }, VCS_CORNER_LOW_MIN,   },
  {    3072000, { HAL_CLK_SOURCE_EXTERNAL,        20,     1,      4,      4       }, VCS_CORNER_LOW_MIN,   },
  {    4096000, { HAL_CLK_SOURCE_EXTERNAL,        30,     1,      2,      2       }, VCS_CORNER_LOW_MINUS, },
  {    5644800, { HAL_CLK_SOURCE_EXTERNAL,        20,     1,      5,      5       }, VCS_CORNER_LOW_MINUS, },
  {    6144000, { HAL_CLK_SOURCE_EXTERNAL,        20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS, },
  {    8192000, { HAL_CLK_SOURCE_EXTERNAL,        30,     0,      0,      0       }, VCS_CORNER_LOW,       },
  {    9600000, { HAL_CLK_SOURCE_EXTERNAL,        4,      0,      0,      0       }, VCS_CORNER_LOW,       },
  {   11289600, { HAL_CLK_SOURCE_EXTERNAL,        10,     1,      5,      5       }, VCS_CORNER_LOW,       },
  {   12288000, { HAL_CLK_SOURCE_EXTERNAL,        20,     0,      0,      0       }, VCS_CORNER_LOW,       },
  { 0 }
};
/*
 * Q6SPM clock configurations
 */
const ClockMuxConfigType Q6SPMClockConfig[] =
{
  {   19199527, { HAL_CLK_SOURCE_SCCPLL0,      26,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};


/*
 * QOSFIXEDLATCOUNTER clock configurations
 */
const ClockMuxConfigType QOSFIXEDLATCOUNTERClockConfig[] =
{
  {  122880000, { HAL_CLK_SOURCE_LPAPLL2,       2,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};


/*
 * RESAMPLER clock configurations
 */
const ClockMuxConfigType RESAMPLERClockConfig[] =
{
  {   38400000, { HAL_CLK_SOURCE_LPAPLL2_DIV2, 16,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   76800000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,  8,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,  4,    0,    0,    0 }, VCS_CORNER_LOW       },
  {  307200000, { HAL_CLK_SOURCE_LPAPLL2,       4,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * SCC100M clock configurations
 */
const ClockMuxConfigType SCC100MClockConfig[] =
{
  {   99837542, { HAL_CLK_SOURCE_SCCPLL0,       5,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};


/*
 * SCCAONDBG clock configurations
 */
const ClockMuxConfigType SCCAONDBGClockConfig[] =
{
  {   62398464, { HAL_CLK_SOURCE_SCCPLL0,       8,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {  124796928, { HAL_CLK_SOURCE_SCCPLL0,       4,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {  249593856, { HAL_CLK_SOURCE_SCCPLL0,       2,    0,    0,    0 }, VCS_CORNER_LOW,      },
  { 0 }
};


/*
 * SCCAONDBGTSCTR clock configurations
 */
const ClockMuxConfigType SCCAONDBGTSCTRClockConfig[] =
{
  {   31199232, { HAL_CLK_SOURCE_SCCPLL0,      16,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   62398464, { HAL_CLK_SOURCE_SCCPLL0,       8,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {  124796928, { HAL_CLK_SOURCE_SCCPLL0,       4,    0,    0,    0 }, VCS_CORNER_LOW       },
  { 0 }
};


/*
 * SCCUART clock configurations
 */
const ClockMuxConfigType SCCUARTClockConfig[] =
{
  {   14745600, { HAL_CLK_SOURCE_SCCPLL0,       2,  150, 2539, 2539 }, VCS_CORNER_LOW_MIN   },
  {   49918771, { HAL_CLK_SOURCE_SCCPLL0,      10,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {   62398464, { HAL_CLK_SOURCE_SCCPLL0,       8,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  { 0 }
};


/*
 * SCCVSVDDCX clock configurations
 */
const ClockMuxConfigType SCCVSVDDCXClockConfig[] =
{
  {  249593856, { HAL_CLK_SOURCE_SCCPLL0,       2,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {  307200000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,  2,    0,    0,    0 }, VCS_CORNER_LOW_MINUS },
  {  614400000, { HAL_CLK_SOURCE_LPAPLL2,       2,    0,    0,    0 }, VCS_CORNER_NOMINAL   },
  { 0 }
};


/*
 * SWNPL clock configurations
 */
const ClockMuxConfigType SWNPLClockConfig[] =
{
  {   76800000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,  8,    0,    0,    0 }, VCS_CORNER_LOW_MIN   },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2,       8,    0,    0,    0 }, VCS_CORNER_LOW       },
  { 0 }
};


/*
 * Clock log default configuration.
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
    (void *)"AUDREF",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"SLEEPCLK",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"XO",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"LPAPLL0_DIV2",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"LPAPLL2_DIV2",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void*)"LPAPLL1",
    CLOCK_FLAG_SUPPORTS_SLEWING | CLOCK_FLAG_SOURCE_CALIBRATED
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"lpass_q6core",
    CLOCK_FLAG_SUPPRESSIBLE | CLOCK_FLAG_DOMAIN_HOLD_VREG_REQUEST
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_core_qdsp_sway_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_bus_timeout_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_mpu_cfg_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_q6_ahbm_mpu_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_qos_ahbs_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_wrapper_sysnoc_sway_aon_clk",
    CLOCK_FLAG_SUPPRESSIBLE
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
    (void*)"audio_core_core_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_core_aud_slimbus_core_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_core_qca_slimbus_core_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_core_lpm_core_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void*)"audio_core_sysnoc_mport_core_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_pcm_data_oe_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_wrapper_ext_mclk0_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_wrapper_ext_mclk1_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_wrapper_ext_mclk2_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_wrapper_ext_mclk3_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_mclk0_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_mclk1_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_pri_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_pri_ebit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_sec_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_sec_ebit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_ter_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_ter_ebit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_quad_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_lpaif_quad_ebit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_i2s0_1_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_i2s2_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_i2s3_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_i2s4_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"audio_core_int_i2s5_6_ibit_clk",
    CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void *)"lpass_audio_core_bcr",
    CLOCK_FLAG_BIST_FAILURE_ANTICIPATED
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK,
    (void *)"lpass_sensor_core_bcr",
    CLOCK_FLAG_BIST_FAILURE_ANTICIPATED
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"island_scc_qup_i2c1_clk",
    CLOCK_FLAG_DOMAIN_NON_MND_SWITCH
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"island_scc_vs_vddcx_clk",
    CLOCK_FLAG_DOMAIN_NON_MND_SWITCH
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void*)"island_scc_vs_vddmx_clk",
    CLOCK_FLAG_DOMAIN_NON_MND_SWITCH
  },
  {
    CLOCK_FLAG_NODE_TYPE_NONE,
    (void*)0,
    0
  }
};
