#include "devcfg_ClockChipset.h"
/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.

==============================================================================

            Copyright (c) 2014-2015 QUALCOMM Technologies Inc.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR

==============================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/config/sdm660/ClockBSP.c#5 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
03/17/16   dai     Updated BSP data for 8998
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
 * Clock source configuration data.
 */
const ClockSourceConfigType SourceConfig[] =
{

  /*-----------------------------------------------------------------------*/
  /* XO                                                                    */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource      = HAL_CLK_SOURCE_XO,
    .HALConfig    = { HAL_CLK_SOURCE_NULL },
    .nConfigMask  = 0,
    .nFreqHz      = 19200000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL0 - General purpose PLL                                           */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource     = HAL_CLK_SOURCE_GPLL0,
    .HALConfig   =  {
        .eSource   =   HAL_CLK_SOURCE_XO,
        .eVCO      =   HAL_CLK_PLL_VCO3,
        .nPreDiv   =   1,
        .nPostDiv  =   1,
        .nL        =   31,
        .nAlpha    =   0,
        .nAlphaU   =   0x40,
                    },
    .nConfigMask = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz     = 600000000,
    .eVRegLevel  = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL0_DIV2 - Branch of GPLL0                                          */
  /*-----------------------------------------------------------------------*/

  {
    .eSource      = HAL_CLK_SOURCE_GPLL0_DIV2,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_GPLL0,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   0,
        .nPostDiv =   0,
        .nL       =   0x0,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x0,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 300000000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL1 - General purpose PLL                                           */
  /*-----------------------------------------------------------------------*/

  {
    .eSource      = HAL_CLK_SOURCE_GPLL1,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   41,
        .nAlpha   =   0x55000000,
        .nAlphaU  =   0xC5,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 802000000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL2 -                                                               */
  /*-----------------------------------------------------------------------*/

  {
    .eSource      = HAL_CLK_SOURCE_GPLL2,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   43,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x0,
                     },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 825600000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL3                                                                 */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource      = HAL_CLK_SOURCE_GPLL3,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   43,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x0,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 825600000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },
  /*-----------------------------------------------------------------------*/
  /* GPLL4                                                                 */
  /*-----------------------------------------------------------------------*/  
  {
    .eSource      = HAL_CLK_SOURCE_GPLL4,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO1,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   80,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x0,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 1536000000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  /*-----------------------------------------------------------------------*/
  /* GPLL5                                                                 */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource      = HAL_CLK_SOURCE_GPLL5,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO1,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   89,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x0,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 1708800000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW_MINUS,
  },

  
  /*-----------------------------------------------------------------------*/
  /* MMPLL0                                                                */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource      = HAL_CLK_SOURCE_MMPLL0,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   42,
        .nAlpha   =   0x55000000,
        .nAlphaU  =   0x15,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 808000 * 1000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW,
  },
  
  /*-----------------------------------------------------------------------*/
  /* MMPLL1                                                                */
  /*-----------------------------------------------------------------------*/  

  {
        .eSource  =   HAL_CLK_SOURCE_MMPLL1,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO3,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   42,
        .nAlpha   =   0xAA000000,
        .nAlphaU  =   0x4A,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 812000*1000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW,
  },
  /*-----------------------------------------------------------------------*/
  /* MMPLL6                                                                */
  /*-----------------------------------------------------------------------*/  

  {
    .eSource      = HAL_CLK_SOURCE_MMPLL6,
    .HALConfig    = {
        .eSource  =   HAL_CLK_SOURCE_XO,
        .eVCO     =   HAL_CLK_PLL_VCO1,
        .nPreDiv  =   1,
        .nPostDiv =   1,
        .nL       =   56,
        .nAlpha   =   0x0,
        .nAlphaU  =   0x40,
                    },
    .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
    .nFreqHz      = 1080000*1000,
    .eVRegLevel   = CLOCK_VREG_LEVEL_LOW,
  },

  { HAL_CLK_SOURCE_NULL }
  
};


/* =========================================================================
**    nFreqHz       { eSource, nDiv2x, nM, nN, n2D },      eVRegLevel         
** =========================================================================*/

/*
 * RPM clock configurations.
 */
const ClockMuxConfigType RPMClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 300000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 401000000, { HAL_CLK_SOURCE_GPLL1,      4, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 600000000, { HAL_CLK_SOURCE_GPLL0,      1, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * System NOC clock configurations
 */
const ClockMuxConfigType SystemNOCClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 120000000, { HAL_CLK_SOURCE_GPLL0,      10, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 160400000, { HAL_CLK_SOURCE_GPLL1,      10, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_PLUS  },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 236310000, { HAL_CLK_SOURCE_GPLL4,      13, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH      },
  { 0 }
};

/*
 * SYSNOCHSAXI clock configurations
 */
const ClockMuxConfigType SYSNOCHSAXIClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 150000000, { HAL_CLK_SOURCE_GPLL0,       8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_PLUS  },
  { 240000000, { HAL_CLK_SOURCE_GPLL0,       5, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 267330000, { HAL_CLK_SOURCE_GPLL1,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL_PLUS   },
  { 300000000, { HAL_CLK_SOURCE_GPLL0,       4, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH      },
  { 0 }
};


/*
 * Config NOC clock configurations
 */
const ClockMuxConfigType ConfigNOCClockConfig[] =
{
  { 19200000, { HAL_CLK_SOURCE_XO,     1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 33330000, { HAL_CLK_SOURCE_GPLL0_DIV2, 18, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 37500000, { HAL_CLK_SOURCE_GPLL0, 32, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 75000000, { HAL_CLK_SOURCE_GPLL0, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * Peripheral NOC clock configurations.
 */
const ClockMuxConfigType PeriphNOCClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,     1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  33330000, { HAL_CLK_SOURCE_GPLL0_DIV2, 18, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  50000000, { HAL_CLK_SOURCE_GPLL0, 24, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  {  75000000, { HAL_CLK_SOURCE_GPLL0,      16, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_PLUS  },
  { 100000000, { HAL_CLK_SOURCE_GPLL0, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },  
  { 0 }
};

/*
 * QDSS AT Group A clock configurations
 */
const ClockMuxConfigType QDSSATBAClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  60000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 10, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 120000000, { HAL_CLK_SOURCE_GPLL0,      10, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 240000000, { HAL_CLK_SOURCE_GPLL0,       5, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * QDSS AT Group B clock configurations
 */
const ClockMuxConfigType QDSSATBBClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  {  50000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  { 100000000, { HAL_CLK_SOURCE_GPLL0,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW        },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL    },
  { 0 }
};

/*
 * QDSS AT Group C clock configurations
 */
const ClockMuxConfigType QDSSATBCClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  {  50000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  { 100000000, { HAL_CLK_SOURCE_GPLL0,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW        },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL    },
  { 0 }
};

/*
 * QDSS Trace clock configurations.
 */
const ClockMuxConfigType QDSSTraceClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 150000000, { HAL_CLK_SOURCE_GPLL0,      8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 267330000, { HAL_CLK_SOURCE_GPLL1,      6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * QDSS STM clock configurations.
 */
const ClockMuxConfigType QDSSSTMClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  {  50000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS  },
  { 100000000, { HAL_CLK_SOURCE_GPLL0,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW        },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL    },
  { 0 }
};

/*
 * QDSS TSCTR Div-2 clock configurations for V2 or higher
 */
const ClockMuxConfigType QDSSTSCTRDiv2ClockConfig[] =
{
  {   9600000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {   9600000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {   9600000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {   9600000, { HAL_CLK_SOURCE_XO,         1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 0 }
};

/*
 * QDSSAPBTRIG clock configurations
 */
const ClockMuxConfigType QDSSAPBTRIGClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  37500000, { HAL_CLK_SOURCE_GPLL0_DIV2, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0,      16, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 150000000, { HAL_CLK_SOURCE_GPLL0,       8, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};


/*
 * PIMEM clock configurations
 */
const ClockMuxConfigType PIMEMClockConfig[] =
{
  {   9600000, { HAL_CLK_SOURCE_XO,          4, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  50000000, { HAL_CLK_SOURCE_GPLL0_DIV2, 12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 100000000, { HAL_CLK_SOURCE_GPLL0,      12, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 150000000, { HAL_CLK_SOURCE_GPLL0,       8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 200000000, { HAL_CLK_SOURCE_GPLL0,       6, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_PLUS  },
  { 240000000, { HAL_CLK_SOURCE_GPLL0,       5, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 300000000, { HAL_CLK_SOURCE_GPLL0,       4, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 341760000, { HAL_CLK_SOURCE_GPLL5,      10, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH      },
  { 0 }
};

#if 0

/*
 * RBCPR clock configurations.
 */
const ClockMuxConfigType RBCPRClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,     1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 0 }
};

#endif

/*
 * IPA clock configurations. RCGR Div reflect IPA 2x Clock Domain. 
 */
const ClockMuxConfigType IPAClockConfig[] =
{
  {  9600000, { HAL_CLK_SOURCE_XO,     1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  37500000, { HAL_CLK_SOURCE_GPLL0_DIV2, 8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  75000000, { HAL_CLK_SOURCE_GPLL0,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 150000000, { HAL_CLK_SOURCE_GPLL0,  4, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * CE (Crypto Engine) clock configurations.
 */
const ClockMuxConfigType CEClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,          1, 0,  0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  {  85710000, { HAL_CLK_SOURCE_GPLL0,      14, 0,  0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 171430000, { HAL_CLK_SOURCE_GPLL0,       7, 0,  0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 },
};

/*
 * SPMI AHB clock configurations.
 */
const ClockMuxConfigType SPMIAHBClockConfig[] =
{
  { 19200000, { HAL_CLK_SOURCE_XO,     1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 37500000, { HAL_CLK_SOURCE_GPLL0, 32, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 75000000, { HAL_CLK_SOURCE_GPLL0, 16, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * SPMI SER clock configurations.
 */
const ClockMuxConfigType SPMISERClockConfig[] =
{
  { 19200000, { HAL_CLK_SOURCE_XO,  1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS       },
  { 0 }
};

/*
 * HMSS AHB clock configurations. Only two custom configs for now.
 */
const ClockMuxConfigType HMSSAHBClockConfig[] =
{
  {  1200000, { HAL_CLK_SOURCE_XO, 32, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 19200000, { HAL_CLK_SOURCE_XO,  1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 0 }
};

/*
 * Voltage Sense clock configurations.
 */
const ClockMuxConfigType VSenseClockConfig[] =
{
  {  19200000, { HAL_CLK_SOURCE_XO,    1, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS },
  { 300000000, { HAL_CLK_SOURCE_GPLL0, 4, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW       },
  { 600000000, { HAL_CLK_SOURCE_GPLL0, 1, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL   },
  { 0 }
};

/*
 * MMSS NOC AXI clock configurations.
 */
const ClockMuxConfigType MMSSAXIClockConfig[] =
{
  {   19200000, { HAL_CLK_SOURCE_XO,          2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {   75000000, { HAL_CLK_SOURCE_GPLL0_DIV2,  8, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS,   },
  {  171430000, { HAL_CLK_SOURCE_GPLL0,       7, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW,         },
  {  240000000, { HAL_CLK_SOURCE_GPLL0,       5, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_PLUS,    },
  {  323200000, { HAL_CLK_SOURCE_MMPLL0,      5, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL,     },
  {  360000000, { HAL_CLK_SOURCE_MMPLL6,      6, 0, 0, 0 }, CLOCK_VREG_LEVEL_NOMINAL_PLUS,},
  {  406000000, { HAL_CLK_SOURCE_MMPLL1,      4, 0, 0, 0 }, CLOCK_VREG_LEVEL_HIGH,        },

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
