/*
==============================================================================

FILE:         ClockBSP.c 

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/msm8998/adsp/ClockBSP.c#1 $

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
 *  SourceFreqConfig_AUDREF
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_AUDREF[] =
{
  {
    /* .nFreqHz    = */  9600 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_NULL },
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .nFreqHz    = */  282240 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL0 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL0_DIV5
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL0_DIV5[] =
{
  {
    /* .nFreqHz    = */  112896 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL0 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .nFreqHz    = */  307200 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL2 },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
  },
  /* last entry */
  { 0 }
};


/*
 *  SourceFreqConfig_LPAPLL2_ODD
 *
 *  Set of source frequency configurations.
 */
static ClockSourceFreqConfigType SourceFreqConfig_LPAPLL2_ODD[] =
{
  {
    /* .nFreqHz    = */  122880 * 1000,
    /* .HALConfig  = */  { HAL_CLK_SOURCE_LPAPLL2 },
    /* .eVRegLevel = */  VCS_CORNER_OFF,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  31,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00004000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .nFreqHz    = */  564480 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  2,
      /* .nL             = */  58,
      /* .nM             = */  4,
      /* .nN             = */  5,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .nFreqHz    = */  614400 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
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
    /* .HWVersion  = */  { {0x00, 0x00}, {0x00, 0x00} },
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
    /* .nFreqHz    = */  288000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  15,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x02, 0x00} },
  },
  {
    /* .nFreqHz    = */  307200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  16,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x02, 0x00} },
  },
  {
    /* .nFreqHz    = */  384000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  20,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x02, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  499200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  26,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x02, 0x00} },
  },
  {
    /* .nFreqHz    = */  595200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
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
    /* .HWVersion  = */  { {0x02, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  672000 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  35,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x02, 0x00} },
  },
  {
    /* .nFreqHz    = */  787200 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  41,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW,
    /* .HWVersion  = */  { {0x02, 0x00}, {0xFF, 0xFF} },
  },
  {
    /* .nFreqHz    = */  844800 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  44,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW,
    /* .HWVersion  = */  { {0x00, 0x00}, {0x02, 0x00} },
  },
  {
    /* .nFreqHz    = */  998400 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  52,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW,
    /* .HWVersion  = */  { {0x02, 0x00}, {0xFF, 0xFF} },
  },
  /* last entry */
  { 0 }
};



static ClockSourceFreqConfigType ClockCalibrationFreq_LPAPLL1[] =
{
  {
    /* .nFreqHz    = */  556800 * 1000,
    /* .HALConfig  = */
    {
      /* .eSource        = */  HAL_CLK_SOURCE_XO,
      /* .eVCO           = */  HAL_CLK_PLL_VCO1,
      /* .nPreDiv        = */  1,
      /* .nPostDiv       = */  1,
      /* .nL             = */  29,
      /* .nM             = */  0,
      /* .nN             = */  0,
      /* .nVCOMultiplier = */  0,
      /* .nAlpha         = */  0x00000000,
      /* .nAlphaU        = */  0x00,
    },
    /* .eVRegLevel = */  VCS_CORNER_LOW_MINUS,
    /* .HWVersion  = */  { {0x00, 0x00}, {0xFF, 0xFF} },
  },
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
    SOURCE_NAME(GPLL0_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_GPLL0_DIV2,
  },
  {
    SOURCE_NAME(LPAPLL0_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL0_DIV2,
  },
  {
    SOURCE_NAME(LPAPLL0_DIV5),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL0_DIV5,
  },
  {
    SOURCE_NAME(LPAPLL2_DIV2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL2_DIV2,
  },
  {
    SOURCE_NAME(LPAPLL2_ODD),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL2_ODD,
  },
  {
    SOURCE_NAME(GPLL0),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_GPLL0,
  },
  {
    SOURCE_NAME(LPAPLL0),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL0,
  },
  {
    SOURCE_NAME(LPAPLL2),

    /* .nConfigMask       = */  0,
    /* .pSourceFreqConfig = */  SourceFreqConfig_LPAPLL2,
  },
  {
    SOURCE_NAME(LPAPLL1),

    /* .nConfigMask       = */      0,
    /* .pSourceFreqConfig = */      SourceFreqConfig_LPAPLL1,
    /* .pCalibrationFreqConfig = */ ClockCalibrationFreq_LPAPLL1,
    /* .eDisableMode           = */ HAL_CLK_SOURCE_DISABLE_MODE_FREEZE
  },
  { 0 }
};


/*----------------------------------------------------------------------*/
/* GCC   Clock Configurations                                           */
/*----------------------------------------------------------------------*/


/*
 * BLSP1QUP1I2CAPPS clock configurations
 */
const ClockMuxConfigType BLSP1QUP1I2CAPPSClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,   },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, VCS_CORNER_LOW,         },
  { 0 }
};


/*
 * BLSP1QUP1SPIAPPS clock configurations
 */
const ClockMuxConfigType BLSP1QUP1SPIAPPSClockConfig[] =
{
  {     960000, { HAL_CLK_SOURCE_XO,             20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,   },
  {    4800000, { HAL_CLK_SOURCE_XO,             8,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,   },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,   },
  {   15000000, { HAL_CLK_SOURCE_GPLL0,          20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         { {0x00, 0x00}, {0x02, 0x00} }},
  {   15000000, { HAL_CLK_SOURCE_GPLL0,          20,     1,      4,      4       }, VCS_CORNER_LOW,               { {0x02, 0x00}, {0xFF, 0xFF} }},
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,   },
  {   25000000, { HAL_CLK_SOURCE_GPLL0,          24,     1,      2,      2       }, VCS_CORNER_LOW,         },
  {   50000000, { HAL_CLK_SOURCE_GPLL0,          24,     0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  { 0 }
};


/*
 * BLSP1UART1APPS clock configurations
 */
const ClockMuxConfigType BLSP1UART1APPSClockConfig[] =
{
  {    3686400, { HAL_CLK_SOURCE_GPLL0,          2,      96,     15625,  15625   }, VCS_CORNER_LOW_MINUS,         { {0x00, 0x00}, {0x02, 0x00} }},
  {    3686400, { HAL_CLK_SOURCE_GPLL0,          2,      96,     15625,  15625   }, VCS_CORNER_LOW,               { {0x02, 0x00}, {0xFF, 0xFF} }},
  {    7372800, { HAL_CLK_SOURCE_GPLL0,          2,      192,    15625,  15625   }, VCS_CORNER_LOW_MINUS,         { {0x00, 0x00}, {0x02, 0x00} }},
  {    7372800, { HAL_CLK_SOURCE_GPLL0,          2,      192,    15625,  15625   }, VCS_CORNER_LOW,               { {0x02, 0x00}, {0xFF, 0xFF} }},
  {   14745600, { HAL_CLK_SOURCE_GPLL0,          2,      384,    15625,  15625   }, VCS_CORNER_LOW_MINUS,         { {0x00, 0x00}, {0x02, 0x00} }},
  {   14745600, { HAL_CLK_SOURCE_GPLL0,          2,      384,    15625,  15625   }, VCS_CORNER_LOW,               { {0x02, 0x00}, {0xFF, 0xFF} }},
  {   16000000, { HAL_CLK_SOURCE_GPLL0,          10,     2,      15,     15      }, VCS_CORNER_LOW_MINUS,         { {0x00, 0x00}, {0x02, 0x00} }},
  {   16000000, { HAL_CLK_SOURCE_GPLL0,          10,     2,      15,     15      }, VCS_CORNER_LOW,               { {0x02, 0x00}, {0xFF, 0xFF} }},
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,   },
  {   24000000, { HAL_CLK_SOURCE_GPLL0,          10,     1,      5,      5       }, VCS_CORNER_LOW,         },
  {   32000000, { HAL_CLK_SOURCE_GPLL0,          2,      4,      75,     75      }, VCS_CORNER_NOMINAL,     },
  {   40000000, { HAL_CLK_SOURCE_GPLL0,          30,     0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  {   46400000, { HAL_CLK_SOURCE_GPLL0,          2,      29,     375,    375     }, VCS_CORNER_NOMINAL,     },
  {   48000000, { HAL_CLK_SOURCE_GPLL0,          25,     0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  {   51200000, { HAL_CLK_SOURCE_GPLL0,          2,      32,     375,    375     }, VCS_CORNER_NOMINAL,     },
  {   56000000, { HAL_CLK_SOURCE_GPLL0,          2,      7,      75,     75      }, VCS_CORNER_NOMINAL,     },
  {   58982400, { HAL_CLK_SOURCE_GPLL0,          2,      1536,   15625,  15625   }, VCS_CORNER_NOMINAL,     },
  {   60000000, { HAL_CLK_SOURCE_GPLL0,          20,     0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  {   63157895, { HAL_CLK_SOURCE_GPLL0,          19,     0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  { 0 }
};



/*----------------------------------------------------------------------*/
/* LPASS Clock Configurations                                           */
/*----------------------------------------------------------------------*/


/*
 * AON clock configurations
 */
const ClockMuxConfigType AONClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   38400000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   16,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   76800000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   8,      0,      0,      0       }, VCS_CORNER_LOW,         },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   4,      0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  { 0 }
};


/*
 * ATIME clock configurations
 */
const ClockMuxConfigType ATIMEClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   30720000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    8,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   61440000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    4,      0,      0,      0       }, VCS_CORNER_LOW,         },
  {  122880000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    2,      0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  { 0 }
};


/*
 * AUDSLIMBUS clock configurations
 */
const ClockMuxConfigType AUDSLIMBUSClockConfig[] =
{
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    10,     0,      0,      0       }, VCS_CORNER_LOW,         },
  { 0 }
};


/*
 * CORE clock configurations
 */
const ClockMuxConfigType COREClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   38400000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   16,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   76800000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   8,      0,      0,      0       }, VCS_CORNER_LOW,         },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   4,      0,      0,      0       }, VCS_CORNER_NOMINAL,     },
  { 0 }
};


/*
 * EXTMCLK0 clock configurations
 */
const ClockMuxConfigType EXTMCLK0ClockConfig[] =
{
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      32,     32      }, VCS_CORNER_LOW_MINUS,         },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    10,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  { 0 }
};


/*
 * LPAIFPCMOE clock configurations
 */
const ClockMuxConfigType LPAIFPCMOEClockConfig[] =
{
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      32,     32      }, VCS_CORNER_LOW_MINUS,         },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    10,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  { 0 }
};



/*
 * LPAIFSPKR clock configurations
 */
const ClockMuxConfigType LPAIFSPKRClockConfig[] =
{
  {     352800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      32,     32      }, VCS_CORNER_LOW_MINUS,         },
  {     512000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     705600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {     768000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      16,     16      }, VCS_CORNER_LOW_MINUS,         },
  {    1024000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1411200, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    1536000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      8,      8       }, VCS_CORNER_LOW_MINUS,         },
  {    2048000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    2822400, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    3072000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      4,      4       }, VCS_CORNER_LOW_MINUS,         },
  {    4096000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    5644800, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    6144000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     1,      2,      2       }, VCS_CORNER_LOW_MINUS,         },
  {    8192000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    30,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {    9600000, { HAL_CLK_SOURCE_XO,             4,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   11289600, { HAL_CLK_SOURCE_LPAPLL0_DIV5,   20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   12288000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    20,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  {   24576000, { HAL_CLK_SOURCE_LPAPLL2_ODD,    10,     0,      0,      0       }, VCS_CORNER_LOW_MINUS,         },
  { 0 }
};

/*
 * RESAMPLER clock configurations
 */
const ClockMuxConfigType RESAMPLERClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {   76800000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   8,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
  {  153600000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   4,      0,      0,      0       }, VCS_CORNER_LOW,               },
  {  307200000, { HAL_CLK_SOURCE_LPAPLL2_DIV2,   2,      0,      0,      0       }, VCS_CORNER_NOMINAL,           },
  { 0 }
};


/*
 * XO clock configurations
 */
const ClockMuxConfigType XOClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,             2,      0,      0,      0       }, VCS_CORNER_LOW_MINUS,                       },
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
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"AUDREF",                                            CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"SLEEPCLK",                                          CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"XO",                                                CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"GPLL0_DIV2",                                        CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"LPAPLL0_DIV2",                                      CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"LPAPLL0_DIV5",                                      CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"LPAPLL2_DIV2",                                      CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"LPAPLL2_ODD",                                       CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE },
  { CLOCK_FLAG_NODE_TYPE_SOURCE,       (void*)"LPAPLL1",                                           CLOCK_FLAG_SUPPORTS_SLEWING },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_q6core",                                      CLOCK_FLAG_SUPPRESSIBLE | CLOCK_FLAG_DOMAIN_HOLD_VREG_REQUEST },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_qdsp_sway_aon_clk",                CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_aon_clk",                       CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_bus_timeout_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_mpu_cfg_aon_clk",               CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_q6_ahbm_mpu_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_qos_ahbs_aon_clk",              CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_wrapper_sysnoc_sway_aon_clk",           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_q6ss_ahbm_aon_clk",                           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_q6ss_ahbs_aon_clk",                           CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_peripheral_smmu_client_core_clk",  CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_core_clk",                         CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_aud_slimbus_core_clk",             CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_qca_slimbus_core_clk",             CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_lpm_core_clk",                     CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK,        (void*)"lpass_audio_core_sysnoc_mport_core_clk",            CLOCK_FLAG_SUPPRESSIBLE },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_pcm_data_oe_clk",            CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_wrapper_ext_mclk0_clk",                 CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_wrapper_ext_mclk1_clk",                 CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_wrapper_ext_mclk2_clk",                 CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_pri_ibit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_pri_ebit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_sec_ibit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_sec_ebit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_ter_ibit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_ter_ebit_clk",               CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_quad_ibit_clk",              CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_quad_ebit_clk",              CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_codec_spkr_ibit_clk",        CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_codec_spkr_osr_clk",         CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  { CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN, (void*)"lpass_audio_core_lpaif_codec_spkr_ebit_clk",        CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF },
  {
    CLOCK_FLAG_NODE_TYPE_NONE,
    (void *)0,
    0
  }
};

