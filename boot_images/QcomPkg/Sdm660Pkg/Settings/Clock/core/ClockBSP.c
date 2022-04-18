/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.


==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/Clock/core/ClockBSP.c#7 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockBSP.h"

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
    /* .nFreqHz    = */  9600 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};

#if 0
/*
 *  SourceFreqConfig_GPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL0[] =
{
  {
    /* .nFreqHz    = */  600000 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_XO },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
  },
  /* last entry */
  { 0 }
};
#endif

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
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
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
    /* .nFreqHz    = */  19200 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL0_DIV2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL0_DIV2[] =
{
  {
    /* .nFreqHz    = */  300000 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_GPLL0 },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL1_DIV2
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL1_DIV2[] =
{
  {
    /* .nFreqHz    = */  401000 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_GPLL1 },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL0[] =
{
  {
    /* .nFreqHz    = */  600000 * 1000,
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
      /* .nAlphaU        = */  0x40,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL1
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL1[] =
{
  {
    /* .nFreqHz    = */  802000 * 1000,
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
      /* .nAlpha         = */  0x55000000,
      /* .nAlphaU        = */  0xC5,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPLL4
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL4[] =
{
  {
    /* .nFreqHz    = */  1536000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  80,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_GPLL5
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPLL5[] =
{
{
    /* .nFreqHz    = */  1708800 * 1000,
    /* .HALConfig  = */
{
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  89,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};

/*
 *  SourceFreqConfig_GPUPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPUPLL0[] =
{
  {
    /* .nFreqHz    = */  1176000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1, //VCO1
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  61,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x40,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_GPUPLL1
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_GPUPLL1[] =
{
  {
    /* .nFreqHz    = */  320000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,//VCO4
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  2,
      /* .nL             = */  33,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x55000000,
      /* .nAlphaU        = */  0x55,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  532000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  27,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x55000000,
      /* .nAlphaU        = */  0xB5,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  740000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  38,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0xAA000000,
      /* .nAlphaU        = */  0x8A,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  930000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  48,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x70,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1176000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2,//VCO1
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  61,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x40,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1294000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2, //VCO1
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  67,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x55000000,
      /* .nAlphaU        = */  0x65,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1400000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  72,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0xAA000000,
      /* .nAlphaU        = */  0xEA,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1500000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2, //VCO1
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  78,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x20,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL0
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL0[] =
{
  {
    /* .nFreqHz    = */  808000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  42,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x55000000,
      /* .nAlphaU        = */  0x15,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL1
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL1[] =
{
  {
    /* .nFreqHz    = */  812000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  42,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0xAA000000,
      /* .nAlphaU        = */  0x4A,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL3
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL3[] =
{
  {
    /* .nFreqHz    = */  883200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  46,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1036800 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2,//VCO1
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  54,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  {
    /* .nFreqHz    = */  1125000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO2,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  58,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x98,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL4
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL4[] =
{
  {
    /* .nFreqHz    = */  768000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  40,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL5
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL5[] =
{
  {
    /* .nFreqHz    = */  825000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  42,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0xF8,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL6
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL6[] =
{
  {
    /* .nFreqHz    = */  1080000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  56,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x40,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL7
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL7[] =
{
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
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL8
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL8[] =
{
  {
    /* .nFreqHz    = */  930000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO3,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  48,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x70,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0

  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_MMPLL10
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_MMPLL10[] =
{
  {
    /* .nFreqHz    = */  576000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  30,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_APCSPLL0_PLL
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_APCSPLL0_PLL[] =
{
  {
    /* .nFreqHz    = */  1497600 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  78,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_APCSPLL1_PLL
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_APCSPLL1_PLL[] =
{
  {
    /* .nFreqHz    = */  1555200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  81,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
    /* .bLastEntry = */  0
  },
  /* last entry */
  { 0 }
};


/*
 * SourceConfig
 *
 * Clock source configuration data.
 */
static ClockSourceConfigType SourceConfig[] =
{
  {
    SOURCE_NAME(AUDREF),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_AUDREF,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(SLEEPCLK),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_SLEEPCLK,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(XO),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_XO,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL0_DIV2),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPLL0_DIV2,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL1_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_GPLL1_DIV2,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL0),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPLL0,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL1),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPLL1,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL4),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPLL4,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPLL5),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPLL5,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPUPLL0),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPUPLL0,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(GPUPLL1),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_GPUPLL1,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL0),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL0,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL1),

    /* .nConfigMask             = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE ,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL1,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL3),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL3,
    /* .pCalibrationFreqConfig  = */  &SourceFreqConfig_MMPLL3[2],
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL4),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL4,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL5),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL5,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  
  {
    SOURCE_NAME(MMPLL6),

    /* .nConfigMask       = */  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL6,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL7),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL7,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL8),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_MMPLL8,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(MMPLL10),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_MMPLL10,
    /* .pCalibrationFreqConfig  = */  NULL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(APCSPLL0),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_APCSPLL0_PLL,
    /* .pCalibrationFreqConfig  = */  SourceFreqConfig_APCSPLL0_PLL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  {
    SOURCE_NAME(APCSPLL1),

    /* .nConfigMask             = */  0,
    /* .pSourceFreqConfig       = */  SourceFreqConfig_APCSPLL1_PLL,
    /* .pCalibrationFreqConfig  = */  SourceFreqConfig_APCSPLL1_PLL,
    /* .eDisableMode            = */  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL
  },
  /* last entry */
  { HAL_CLK_SOURCE_NULL }
};


/*----------------------------------------------------------------------*/
/* GCC   Clock Configurations                                           */
/*----------------------------------------------------------------------*/

/*
 * BLSP1QUP1I2CAPPS clock configurations
 */
const ClockMuxConfigType BLSP1QUP1I2CAPPSClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * BLSP1QUP1SPIAPPS clock configurations
 */
const ClockMuxConfigType BLSP1QUP1SPIAPPSClockConfig[] =
{
  {     960000, { HAL_CLK_SOURCE_XO,             20,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    4800000, { HAL_CLK_SOURCE_XO,             8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   15000000, { HAL_CLK_SOURCE_GPLL0,          20,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW,         },
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   25000000, { HAL_CLK_SOURCE_GPLL0,          24,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW,         },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * BLSP1UART1APPS clock configurations
 */
const ClockMuxConfigType BLSP1UART1APPSClockConfig[] =
{
  {    3686400, { HAL_CLK_SOURCE_GPLL0,          2,      96,     15625,  15625   }, CLOCK_VREG_LEVEL_LOW,         },
  {    7372800, { HAL_CLK_SOURCE_GPLL0,          2,      192,    15625,  15625   }, CLOCK_VREG_LEVEL_LOW,         },
  {   14745600, { HAL_CLK_SOURCE_GPLL0,          2,      384,    15625,  15625   }, CLOCK_VREG_LEVEL_LOW,         },
  {   16000000, { HAL_CLK_SOURCE_GPLL0,          10,     2,      15,     15      }, CLOCK_VREG_LEVEL_LOW,         },
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   24000000, { HAL_CLK_SOURCE_GPLL0,          10,     1,      5,      5       }, CLOCK_VREG_LEVEL_LOW,         },
  {   32000000, { HAL_CLK_SOURCE_GPLL0,          2,      4,      75,     75      }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   40000000, { HAL_CLK_SOURCE_GPLL0,          30,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   46400000, { HAL_CLK_SOURCE_GPLL0,          2,      29,     375,    375     }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   48000000, { HAL_CLK_SOURCE_GPLL0,          25,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   51200000, { HAL_CLK_SOURCE_GPLL0,          2,      32,     375,    375     }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   56000000, { HAL_CLK_SOURCE_GPLL0,          2,      7,      75,     75      }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   58982400, { HAL_CLK_SOURCE_GPLL0,          2,      1536,   15625,  15625   }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {   63157895, { HAL_CLK_SOURCE_GPLL0,          19,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * GP1 clock configurations
 */
const ClockMuxConfigType GP1ClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * HMSSAHB clock configurations
 */
const ClockMuxConfigType HMSSAHBClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   37500000, { HAL_CLK_SOURCE_GPLL0,          32,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * HMSSRBCPR clock configurations
 */
const ClockMuxConfigType HMSSRBCPRClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * MMSSQMCORE clock configurations
 */
const ClockMuxConfigType MMSSQMCOREClockConfig[] =
{
  {  150000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     4,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * PDM2 clock configurations
 */
const ClockMuxConfigType PDM2ClockConfig[] =
{
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * QSPISER clock configurations
 */
const ClockMuxConfigType QSPISERClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   80200000, { HAL_CLK_SOURCE_GPLL1_DIV2,     10,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  160400000, { HAL_CLK_SOURCE_GPLL1,          10,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  267333333, { HAL_CLK_SOURCE_GPLL1,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * SDCC1APPS clock configurations
 */
const ClockMuxConfigType SDCC1APPSClockConfig[] =
{
  {     144000, { HAL_CLK_SOURCE_XO,             32,     3,      25,     25      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {     400000, { HAL_CLK_SOURCE_XO,             24,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   20000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     10,     1,      3,      3       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   25000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  192000000, { HAL_CLK_SOURCE_GPLL4,          16,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  384000000, { HAL_CLK_SOURCE_GPLL4,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * SDCC1ICECORE clock configurations
 */
const ClockMuxConfigType SDCC1ICECOREClockConfig[] =
{
  {   75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  150000000, { HAL_CLK_SOURCE_GPLL0,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * SDCC2APPS clock configurations
 */
const ClockMuxConfigType SDCC2APPSClockConfig[] =
{
  {     144000, { HAL_CLK_SOURCE_XO,             32,     3,      25,     25      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {     400000, { HAL_CLK_SOURCE_XO,             24,     1,      4,      4       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   20000000, { HAL_CLK_SOURCE_GPLL0,          30,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW,         },
  {   25000000, { HAL_CLK_SOURCE_GPLL0,          24,     1,      2,      2       }, CLOCK_VREG_LEVEL_LOW,         },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  192000000, { HAL_CLK_SOURCE_GPLL4,          16,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * UFSAXI clock configurations
 */
const ClockMuxConfigType UFSAXIClockConfig[] =
{
  {   50000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  150000000, { HAL_CLK_SOURCE_GPLL0,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  240000000, { HAL_CLK_SOURCE_GPLL0,          5,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * UFSICECORE clock configurations
 */
const ClockMuxConfigType UFSICECOREClockConfig[] =
{
  {   75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  150000000, { HAL_CLK_SOURCE_GPLL0,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * UFSPHYAUX clock configurations
 */
const ClockMuxConfigType UFSPHYAUXClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * UFSUNIPROCORE clock configurations
 */
const ClockMuxConfigType UFSUNIPROCOREClockConfig[] =
{
  {   37500000, { HAL_CLK_SOURCE_GPLL0_DIV2,     16,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   75000000, { HAL_CLK_SOURCE_GPLL0,          16,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  150000000, { HAL_CLK_SOURCE_GPLL0,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * USB20MASTER clock configurations
 */
const ClockMuxConfigType USB20MASTERClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  120000000, { HAL_CLK_SOURCE_GPLL0,          10,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * USB20MOCKUTMI clock configurations
 */
const ClockMuxConfigType USB20MOCKUTMIClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};
/*
 * USB3PHYPIPE clock configurations
 */
const ClockMuxConfigType USB3PHYPIPEClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS, },
  {   62500000, { HAL_CLK_SOURCE_EXTERNAL,       2,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS, },
  {  125000000, { HAL_CLK_SOURCE_EXTERNAL,       2,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,       },
  { 0 }
};

/*
 * USB30MASTER clock configurations
 */
const ClockMuxConfigType USB30MASTERClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   66666667, { HAL_CLK_SOURCE_GPLL0_DIV2,     9,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  120000000, { HAL_CLK_SOURCE_GPLL0,          10,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  133333333, { HAL_CLK_SOURCE_GPLL0,          9,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  150000000, { HAL_CLK_SOURCE_GPLL0,          8,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  240000000, { HAL_CLK_SOURCE_GPLL0,          5,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * USB30MOCKUTMI clock configurations
 */
const ClockMuxConfigType USB30MOCKUTMIClockConfig[] =
{
  {   40000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     15,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * USB3PHYAUX clock configurations
 */
const ClockMuxConfigType USB3PHYAUXClockConfig[] =
{
  {    1200000, { HAL_CLK_SOURCE_XO,             32,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};



/*----------------------------------------------------------------------*/
/* GPU   Clock Configurations                                           */
/*----------------------------------------------------------------------*/


/*
 * GFX3D clock configurations
 */
const ClockMuxConfigType GFX3DClockConfig[] =
{
 
 {  588000000, { HAL_CLK_SOURCE_GPUPLL0,        4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     { { 0 }                      }, NULL},

  { 0 }
};


/*
 * RBBMTIMER clock configurations
 */
const ClockMuxConfigType RBBMTIMERClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * RBCPR clock configurations
 */
const ClockMuxConfigType RBCPRClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};



/*----------------------------------------------------------------------*/
/* MMSS  Clock Configurations                                           */
/*----------------------------------------------------------------------*/


/*
 * AHB clock configurations
 */
const ClockMuxConfigType AHBClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   40000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     15,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {   80800000, { HAL_CLK_SOURCE_MMPLL0,         20,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * BYTE0 clock configurations
 */
const ClockMuxConfigType BYTE0ClockConfig[] =
{
  {	  19200000, { HAL_CLK_SOURCE_XO,			 2,	     0,	     0,	     0	     }, CLOCK_VREG_LEVEL_LOW_MINUS,	  },
  {  131250000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  210000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  262500000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * CAMSSGP0 clock configurations
 */
const ClockMuxConfigType CAMSSGP0ClockConfig[] =
{
  {      10000, { HAL_CLK_SOURCE_XO,             32,     1,      120,    120     }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {      24000, { HAL_CLK_SOURCE_XO,             32,     1,      50,     50      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    6000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     20,     1,      5,      5       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   12000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     20,     2,      5,      5       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   13043478, { HAL_CLK_SOURCE_GPLL0_DIV2,     2,      1,      23,     23      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   24000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     2,      2,      25,     25      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  100000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * CCI clock configurations
 */
const ClockMuxConfigType CCIClockConfig[] =
{
  {   37500000, { HAL_CLK_SOURCE_GPLL0_DIV2,     16,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     12,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  100000000, { HAL_CLK_SOURCE_GPLL0,          12,     0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * CPP clock configurations
 */
const ClockMuxConfigType CPPClockConfig[] =
{
  {  120000000, { HAL_CLK_SOURCE_GPLL0,          10,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  256000000, { HAL_CLK_SOURCE_MMPLL4,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  384000000, { HAL_CLK_SOURCE_MMPLL4,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  480000000, { HAL_CLK_SOURCE_MMPLL7,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  540000000, { HAL_CLK_SOURCE_MMPLL6,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,},
  {  576000000, { HAL_CLK_SOURCE_MMPLL10,        2,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * CSI0 clock configurations
 */
const ClockMuxConfigType CSI0ClockConfig[] =
{
  {  100000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  310000000, { HAL_CLK_SOURCE_MMPLL8,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  404000000, { HAL_CLK_SOURCE_MMPLL0,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  465000000, { HAL_CLK_SOURCE_MMPLL8,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,},
  { 0 }
};


/*
 * CSI0PHYTIMER clock configurations
 */
const ClockMuxConfigType CSI0PHYTIMERClockConfig[] =
{
  {  100000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  269333333, { HAL_CLK_SOURCE_MMPLL0,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * CSIPHY clock configurations
 */
const ClockMuxConfigType CSIPHYClockConfig[] =
{
  {  100000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  269333333, { HAL_CLK_SOURCE_MMPLL0,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  320000000, { HAL_CLK_SOURCE_MMPLL7,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * DPAUX clock configurations
 */
const ClockMuxConfigType DPAUXClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * DPCRYPTO clock configurations
 */
const ClockMuxConfigType DPCRYPTOClockConfig[] =
{
  {  101250000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  168750000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  337500000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * DPGTC clock configurations
 */
const ClockMuxConfigType DPGTCClockConfig[] =
{
  {   40000000, { HAL_CLK_SOURCE_GPLL0_DIV2,          15,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * DPLINK clock configurations
 */
const ClockMuxConfigType DPLINKClockConfig[] =
{
  {	 19200000,  { HAL_CLK_SOURCE_XO,			 2,	     0,	     0,	     0	     }, CLOCK_VREG_LEVEL_LOW_MINUS,	  },
  {  162000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  270000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  540000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * DPPIXEL clock configurations
 */
const ClockMuxConfigType DPPIXELClockConfig[] =
{
  {  148380000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  296740000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  593470000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * ESC0 clock configurations
 */
const ClockMuxConfigType ESC0ClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   19200000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * JPEG0 clock configurations
 */
const ClockMuxConfigType JPEG0ClockConfig[] =
{
  {   66666667, { HAL_CLK_SOURCE_GPLL0_DIV2,     9,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  133333333, { HAL_CLK_SOURCE_GPLL0,          9,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  219428571, { HAL_CLK_SOURCE_MMPLL4,         7,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  320000000, { HAL_CLK_SOURCE_MMPLL7,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  480000000, { HAL_CLK_SOURCE_MMPLL7,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,},
  { 0 }
};


/*
 * MCLK0 clock configurations
 */
const ClockMuxConfigType MCLK0ClockConfig[] =
{
  {    4800000, { HAL_CLK_SOURCE_XO,             8,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    6000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     20,     1,      5,      5       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    8000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     2,      2,      75,     75      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   16666667, { HAL_CLK_SOURCE_GPLL0_DIV2,     4,      1,      9,      9       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   24000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     2,      2,      25,     25      }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   33333333, { HAL_CLK_SOURCE_GPLL0_DIV2,     2,      1,      9,      9       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   48000000, { HAL_CLK_SOURCE_GPLL0,          2,      2,      25,     25      }, CLOCK_VREG_LEVEL_LOW,         },
  {   66666667, { HAL_CLK_SOURCE_GPLL0,          2,      1,      9,      9       }, CLOCK_VREG_LEVEL_LOW,         },
  { 0 }
};


/*
 * MDP clock configurations
 */
const ClockMuxConfigType MDPClockConfig[] =
{
  {  100000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  150000000, { HAL_CLK_SOURCE_GPLL0_DIV2,     4,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  171428571, { HAL_CLK_SOURCE_GPLL0,          7,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  275000000, { HAL_CLK_SOURCE_MMPLL5,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  330000000, { HAL_CLK_SOURCE_MMPLL5,         5,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  412500000, { HAL_CLK_SOURCE_MMPLL5,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * PCLK0 clock configurations
 */
const ClockMuxConfigType PCLK0ClockConfig[] =
{
  {  175000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  280000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  350000000, { HAL_CLK_SOURCE_EXTERNAL,       2,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  { 0 }
};


/*
 * ROT clock configurations
 */
const ClockMuxConfigType ROTClockConfig[] =
{
  {  171428571, { HAL_CLK_SOURCE_GPLL0,          7,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  275000000, { HAL_CLK_SOURCE_MMPLL5,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  330000000, { HAL_CLK_SOURCE_MMPLL5,         5,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  412500000, { HAL_CLK_SOURCE_MMPLL5,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * VFE0 clock configurations
 */
const ClockMuxConfigType VFE0ClockConfig[] =
{
  {  120000000, { HAL_CLK_SOURCE_GPLL0,          10,     0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  200000000, { HAL_CLK_SOURCE_GPLL0,          6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  256000000, { HAL_CLK_SOURCE_MMPLL4,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  300000000, { HAL_CLK_SOURCE_GPLL0,          4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  404000000, { HAL_CLK_SOURCE_MMPLL0,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  480000000, { HAL_CLK_SOURCE_MMPLL7,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  540000000, { HAL_CLK_SOURCE_MMPLL6,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,},
  {  576000000, { HAL_CLK_SOURCE_MMPLL10,        2,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        },
  { 0 }
};


/*
 * VIDEOCORE clock configurations
 */
const ClockMuxConfigType VIDEOCOREClockConfig[] =
{
  {  133333333, { HAL_CLK_SOURCE_GPLL0,          9,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  269333333, { HAL_CLK_SOURCE_MMPLL0,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW,         },
  {  320000000, { HAL_CLK_SOURCE_MMPLL7,         6,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  404000000, { HAL_CLK_SOURCE_MMPLL0,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  441600000, { HAL_CLK_SOURCE_MMPLL3,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,{ { 0 }                      }, &SourceFreqConfig_MMPLL3[0] /* 883.2 MHz */ },
  {  518400000, { HAL_CLK_SOURCE_MMPLL3,         4,      0,      0,      0       }, CLOCK_VREG_LEVEL_HIGH,        { { 0 }                      }, &SourceFreqConfig_MMPLL3[1] /* 1036.8 MHz */ },
  { 0 }
};


/*
 * VSYNC clock configurations
 */
const ClockMuxConfigType VSYNCClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  { 0 }
};


/*
 * Clock Log Default Configuration.
 *
 */
const ClockLogType ClockLogDefaultConfig[] =
{
  {
    /* .nLogSize        = */ 4096,
    /* .nGlobalLogFlags = */ 0x90ff
  }
};

/*
 * Clock Flag Init Config.
 */
const ClockFlagInitType ClockFlagInitConfig[] =
{
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"MMPLL3",
    CLOCK_FLAG_SUPPORTS_SLEWING
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"AUDREF",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"GPLL0",
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
    (void *)"GPLL0_DIV2",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_SOURCE,
    (void *)"GPLL1_DIV2",
    CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void *)"apcs_cluster0_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN,
    (void *)"apcs_cluster1_clk",
    CLOCK_FLAG_SUPPRESSIBLE
  },
  {
    CLOCK_FLAG_NODE_TYPE_NONE,
    (void *)0,
    0
  }
};



const ClockAVSCoreConfigType ClockAVSData[] =
{
  {
    /* .nPhysicalBase    = */ 0x17912000,             /* Base address: 0x17912000  - 0x3FF */
    /* .eCore            = */ HAL_AVS_CORE_APC0_L2,   /* Cluster0 L2: APCLUS0_L2_SAW4_1_1_SPM */
    /* .ePMIC            = */ HAL_AVS_PMSdm660_SUPPORT,
    /* .eStepSize        = */ HAL_AVS_STEP_SIZE_25MV,
    /* .nVddRequestDelay = */ 300,
    /* .nClockDiv        = */ 1,
    /* .HWVersion        = */ { {0, 0}, {0xFF, 0xFF}, DALCHIPINFO_FAMILY_UNKNOWN, NULL },
  },
  {
    /* .nPhysicalBase    = */ 0x17812000,             /* Base address: 0x17812000 - 0x3FF */
    /* .eCore            = */ HAL_AVS_CORE_APC1_L2,   /* Cluster1 L2: APCLUS1_L2_SAW4_1_1_SPM */
    /* .ePMIC            = */ HAL_AVS_PMSdm660_SUPPORT,
    /* .eStepSize        = */ HAL_AVS_STEP_SIZE_25MV,
    /* .nVddRequestDelay = */ 300,
    /* .nClockDiv        = */ 1,
    /* .HWVersion        = */ { {0, 0}, {0xFF, 0xFF}, DALCHIPINFO_FAMILY_UNKNOWN, NULL },
  },

  { 0 }
};

/*
 * List of clocks allowed to be suppressible.
 */
ClockNameListType ClockSuppressibleList[] =
{
  // Serial Debugger:
  { "gcc_blsp1_uart2_apps_clk"   },
  { "gcc_blsp1_ahb_clk"          },
  { "gcc_blsp2_uart2_apps_clk"   },
  { "gcc_blsp2_ahb_clk"          },

  // USB 2.0 Debugger:
  { "gcc_usb20_master_clk"       },
  { "gcc_usb20_mock_utmi_clk"    },
  { "gcc_usb_phy_cfg_ahb2phy_clk"},
  { "gcc_usb20_sleep_clk"        },

  // USB 3.0 Debugger:
  { "gcc_usb30_master_clk"       },
  { "gcc_usb30_mock_utmi_clk"    },
  { "gcc_sys_noc_usb3_axi_clk"   },
  { "gcc_usb30_sleep_clk"        },
  { "gcc_usb3_phy_pipe_clk"      },
  { "gcc_usb3_phy_aux_clk"       },

  { NULL }
};

/*
 * List of clocks allowed to be always on.
 */
ClockNameListType ClockAlwaysOnList[] =
{
  { "gcc_usb20_sleep_clk"        },
  { "gcc_usb30_sleep_clk"        },
  { "gcc_usb3_phy_aux_clk"       },
  { NULL }
};

/*
 * List of clocks allowed to be reference counter disabled.
 */
ClockNameListType ClockRefCountSuspendedList[] =
{
  // USB 2.0
  { "gcc_usb20_mock_utmi_clk"    },

  // USB 3.0
  { "gcc_usb30_master_clk"       },
  { "gcc_usb30_mock_utmi_clk"    },
  { "gcc_sys_noc_usb3_axi_clk"   },
  { "gcc_usb3_phy_aux_clk"       },

  { NULL }
};

/*
 * List of clocks allowed to be configured with the
 * FORCE_MEM_CORE and FORCE_MEM_PERIPH parameters.
 */
ClockNameListType ClockForceMemCoreAndPeriphList[] =
{
  { NULL }
};

/*
 * List of clocks anticipated to fail the BIST.
 */
ClockNameListType ClockBistExceptions[] =
{
  { "mmss_spdm_vfe1_clk"    },
  { "mmss_spdm_vfe0_clk"    },
  { "mmss_spdm_rot_clk"    },
  { "mmss_spdm_mdp_clk"    },
  { "mmss_spdm_jpeg0_clk"    },
  { "mmss_spdm_csi0_clk"    },
  { "mmss_spdm_cpp_clk"    },
  { "gpucc_gpu_cx_bcr"    },
  { "gcc_cnoc_bus_timeout_extref_bcr"    },
  { "gcc_pnoc_bus_timeout0_bcr"    },
  { "gcc_qusb2phy_prim_bcr"    },
  { "gcc_qusb2phy_sec_bcr"    },
  { "gcc_snoc_bus_timeout_extref_bcr"    },
  { "gcc_usb3_phy_bcr"    },
  { "gpucc_spdm_gfx3d_clk"  },
  { "mmss_spdm_video_core_clk" },
  { NULL }
};

/*
 * List of clocks excluded from the BIST.
 */
ClockNameListType ClockExcludeFromBist[] =
{
  { NULL }
};


