#ifndef __CLOCK_BIMC_H__
#define __CLOCK_BIMC_H__

/**
==============================================================================

FILE:         ClockBIMC.h

DESCRIPTION:  Initial revision of types borrowed from the RPM so that the shared
memory transfer will be correctly understood when recieved by the RPM.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
08/11/15  jcuddihy      Initial SDM660 revision, branched from MSM8996.

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================
                     INCLUDE FILES FOR MODULE
============================================================================*/

#include "ClockBoot.h"
#include "ClockCommon.h"

/*============================================================================
                     Type Definitions
============================================================================*/

/*
 * Macros for consolidating PLL configuration in a single mask.
 */
#define CLOCK_CONFIG_PLL_FSM_MODE_ENABLE        (1 << 0)
#define CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE      (1 << 1)
#define CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE     (1 << 2)
#define CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE    (1 << 3)

#define BSP_SUPPORTED     0
#define BSP_NOT_SUPPORTED 0xFFFF0000

/*
 * HAL_clk_PLLVCOType
 */
typedef enum
{
  HAL_CLK_PLL_VCO_MODE_0,
  HAL_CLK_PLL_VCO_MODE_1,
  HAL_CLK_PLL_VCO_MODE_2,
  HAL_CLK_PLL_VCO_MODE_3,

  HAL_CLK_NUM_PLL_VCO_MODES,

  HAL_ENUM_32BITS(CLK_PLL_VCO)
} HAL_clk_PLLVCOType;

/*
 * HAL_clk_PLLConfigType
 */
typedef struct
{
  HAL_clk_SourceType  eSource;
  uint8               nPreDiv;
  uint8               nPostDiv;
  uint16              nL;
  uint8               nM;
  uint8               nN;
  uint16              nAlphaU;
  uint32              nAlpha;
  HAL_clk_PLLVCOType  eVCO;
} HAL_clk_PLLConfigType;

/*
 * HAL_clk_ClockMuxConfigType
 */
typedef struct
{
  HAL_clk_SourceType eSource;
  uint16             nDiv2x;
  uint16             nM;
  uint16             nN;
  uint16             n2D;
} HAL_clk_ClockMuxConfigType;

/*
 * RPMClockSourceConfigType
 */
typedef struct
{
  HAL_clk_SourceType      eSource;
  HAL_clk_PLLConfigType   HALConfig;
  uint32                  nConfigMask;
  uint32                  nFreqHz;
  railway_corner          eVRegLevel;
} RPMClockSourceConfigType;

typedef struct
{
  uint32                      nFreqHz;
  HAL_clk_ClockMuxConfigType  HALConfig;
  railway_corner              eVRegLevel;
  uint32                      nChipVersion;
  uint32                      nFamily;
  //RPMClockSourceConfigType    *pSourceConfig;  Removed, for 32-bit compatiblity
  uint32                      pSourceConfig; 
} RPMClockMuxConfigType;

#define CLOCK_BIMC_SMEM_VERSION 0x0003
/*
 * ClockBIMCTableType
 */
typedef enum
{
  CLOCK_BIMC_PLL,
  CLOCK_BIMC_DDR,

  CLOCK_BIMC_NUM_TABLES
} ClockBIMCTableType;

typedef struct
{
  uint16 nVersion;     /* A version number to verify matching XBL and RPM data structures */
  uint8  nNumConfig;   /* A count of how many data tables are provided */
  uint8  nHALNumSrc;   /* HAL_CLK_NUM_OF_SOURCES */
  uint8  nMinLevel;    /* Min DDR level index */
  uint8  nMaxLevel;    /* Max DDR level index */
  uint8  nActiveLevel; /* The level in use at the time of RPM handoff */
  uint8  nReserved;    /* Reserved */
  uint32 nConfigData;  /* An offset from the start of the shared memory to the first table header */
} ClockBIMCConfigInfo;

typedef struct
{
  uint16 nNodeSize;   /* Size of each struct (row) in the table */
  uint8  nNumNodes;   /* The total number of structs */
  uint8  eBIMCTable;  /* The type of table, actual type should be ClockBIMCTableType but need to force it to 8-bit */
  uint32 nNodeOffset; /* Offset from shared memory to the first struct of the table */
} ClockBIMCTableHeaderType;

#endif /* __CLOCK_BIMC_H__ */
