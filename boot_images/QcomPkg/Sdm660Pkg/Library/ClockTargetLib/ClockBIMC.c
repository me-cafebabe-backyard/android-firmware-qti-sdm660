/**
==============================================================================

  @file ClockBIMC.c

  This file provides clock initialization for the Apps.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
10/07/15  plc           Comment out railway calls until railway is delivered
08/11/15  jcuddihy      Initial SDM660 revision, branched from MSM8996.

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockBoot.h"
#include "ClockBIMC.h"
#include "ClockHWIO.h"
#include "ClockBSP.h"
#include "ddr_drivers.h"
#include "ddr_common.h"
#include "railway.h"
#include "smem.h"
#include "boot_util.h"

/*=========================================================================
      Macro Definitions
==========================================================================*/
/*
 * HALF_DIVIDER
 *
 * Macro to return the normalized half divider for a given mux structure.
 * NOTE: Expecting (2 * divider) value as input.
 */
#define HALF_DIVIDER(mux)  ((mux)->nDiv2x ? (((mux)->nDiv2x) - 1) : 0)

/*
 * Common root clock command fields/masks (*_CMD_RCGR)
 */
#define HAL_CLK_CMD_RCGR_ROOT_OFF_FMSK                                0x80000000
#define HAL_CLK_CMD_RCGR_ROOT_EN_FMSK                                 0x00000002
#define HAL_CLK_CMD_CFG_UPDATE_FMSK                                   0x00000001
#define HAL_CLK_CMD_CFG_UPDATE_SHFT                                   0

/*
 * Common root clock config fields/masks (*_CFG_RCGR)
 */
#define HAL_CLK_CFG_RCGR_MODE_FMSK                                    0x00003000
#define HAL_CLK_CFG_RCGR_MODE_SHFT                                    0xc
#define HAL_CLK_CFG_RCGR_SRC_SEL_FMSK                                 0x00000700
#define HAL_CLK_CFG_RCGR_SRC_SEL_SHFT                                 0x8
#define HAL_CLK_CFG_RCGR_SRC_DIV_FMSK                                 0x0000001F
#define HAL_CLK_CFG_RCGR_SRC_DIV_SHFT                                 0

#define HAL_CLK_CFG_REG_OFFSET                                        0x4

/*
 * Supported PLL pre/post dividers.
 */
#define CLK_PLL_PREDIV_1      1
#define CLK_PLL_PREDIV_2      2
#define CLK_PLL_POSTDIV_1     1
#define CLK_PLL_POSTDIV_2     2
#define CLK_PLL_POSTDIV_4     4

#define MAX_BIMC_DDR_ASYNC_CLK 6
/*
 * 'ClockDDRCPLLConfigType' accessors used for repurposed bit-fields in
 * 'HAL_clk_ClockMuxConfigType'. Provides RPM HAL compatibility.
 */

#define HAL_CLK_BIMC_DIV2X_VAL(ddrcc_mode, ddr_gpll0_sel, ddr_div2x, cdsp_gpll0_sel, cdsp_div2x) \
  ((((ddrcc_mode) & 0x1) << 15) | (((ddr_gpll0_sel) & 0x3) << 13) | (((ddr_div2x) & 0x1F) << 8) | (((cdsp_gpll0_sel) & 0x7) << 5) | ((cdsp_div2x) & 0x1F))
 
#define HAL_CLK_BIMC_DIV2X_DDRCC_MODE_EN(div2x) (((div2x) & 0x8000) >> 15)
#define HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(div2x) (((div2x) & 0x6000) >> 13)
#define HAL_CLK_BIMC_DIV2X_DDR_DIV2X(div2x)     (((div2x) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(div2x)(((div2x) & 0xE0) >> 5)
#define HAL_CLK_BIMC_DIV2X_CDSP_DIV2X(div2x)    ((div2x) & 0x1F)



#define HAL_CLK_BIMC_M_VAL(bimc_gpll0_sel, bimc_div2x, hmss_gpll0_sel, hmss_div2x) \
  ((((bimc_gpll0_sel) & 0x7) << 13) | (((bimc_div2x) & 0x1F) << 8) | (((hmss_gpll0_sel) & 0x7) << 5) | ((hmss_div2x) & 0x1F))

#define HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(m)    (((m) & 0xE000) >> 13)
#define HAL_CLK_BIMC_M_BIMC_DIV2X(m)        (((m) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(m)    (((m) & 0xE0) >> 5)
#define HAL_CLK_BIMC_M_HMSS_DIV2X(m)        ((m) & 0x1F)



#define HAL_CLK_BIMC_N_VAL(gfx_gpll0_sel, gfx_div2x, mpss_gpll0_sel, mpss_div2x) \
  ((((gfx_gpll0_sel) & 0x7) << 13) | (((gfx_div2x) & 0x1F) << 8) | (((mpss_gpll0_sel) & 0x7) << 5) | ((mpss_div2x) & 0x1F))

#define HAL_CLK_BIMC_N_GFX_GPLL0_SEL(n)     (((n) & 0xE000) >> 13)
#define HAL_CLK_BIMC_N_GFX_DIV2X(n)         (((n) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(n)    (((n) & 0xE0) >> 5)
#define HAL_CLK_BIMC_N_MPSS_DIV2X(n)        ((n) & 0x1F)



#define HAL_CLK_BIMC_N2D_VAL(gpll23_idx, VDDA_EBI_vote) \
  ((((gpll23_idx) & 0xF) << 12) | ((VDDA_EBI_vote) & 0xFFF))

#define HAL_CLK_BIMC_N2D_GPLL23_IDX(n2d)                (((n2d) & 0xF000) >> 12)
#define HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(n2d)             ((n2d) & 0xFFF)


 

#define CLOCK_TABLE(table) {table, sizeof(table), sizeof(table[0]), sizeof(table)/sizeof(table[0]) }

#define FREQ_1296000K                   1296000000
#define FREQ_1353600K                   1353600000


/* This ClockPLLTableType captures the table, and necessary sizeof parameters so that we
 * can swap in tables for different versions. */
typedef struct 
{
  const RPMClockSourceConfigType *table;  /* Pointer to data */
  const uint32 size;                      /* sizeof(table) */
  const uint32 item_size;                 /* size of one array element */
  const uint32 count;                     /* The sizeof(array) / sizeof(array[0]) */
} ClockPLLTableType;

/* This RPMClockMuxConfigType captures the table, and necessary sizeof parameters so that we
 * can swap in tables for different versions. */
typedef struct 
{
  RPMClockMuxConfigType *table;  /* Pointer to data */
  const uint32 size;             /* sizeof(table) */
  const uint32 item_size;        /* size of one array element */
  const uint32 count;            /* The sizeof(array) / sizeof(array[0]) */
} ClockRPMTableType;

/*=========================================================================
     Externs
==========================================================================*/

/*=========================================================================
      Function Prototypes
==========================================================================*/

boolean Clock_SourceMapToGCC(ClockSourceType eSource, uint32 *nMuxValue);

/*=========================================================================
      Data
==========================================================================*/
#define MAX_DDR_LEVELS 12

/* Min and Max support DDR Index */
static uint8 nDDRMinIndex = 0;
static uint8 nDDRMaxIndex = MAX_DDR_LEVELS;
static uint8 nDDRActiveIndex = 2; /*Pre- DDR init happens at 200Mhz*/
/*
 * PLL settings used for reprogramming GPLL2 or GPLL3 for the GCC clock roots
 */
const RPMClockSourceConfigType BIMCPLLConfig_V1[] =
{
  /* ==============================================================================================================================================================================
  **  { eSource,          { eSource,                    nPreDiv,          nPostDiv,   nL, nM, nN, nAlphau, nAlpha, eVCO},                      nConfigMask,   nFreqHz }
  ** =============================================================================================================================================================================*/
    { HAL_CLK_SOURCE_GPLL2, { HAL_CLK_SOURCE_XO, CLK_PLL_PREDIV_1, CLK_PLL_POSTDIV_1, 0x2B, 0, 0, 0x0, 0x0, HAL_CLK_PLL_VCO_MODE_2}, CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,  825600000}, 
    { HAL_CLK_SOURCE_GPLL2, { HAL_CLK_SOURCE_XO, CLK_PLL_PREDIV_1, CLK_PLL_POSTDIV_1, 0x21, 0, 0, 0x0, 0x0, HAL_CLK_PLL_VCO_MODE_2}, CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,  633600000}, 
    { HAL_CLK_SOURCE_GPLL2, { HAL_CLK_SOURCE_XO, CLK_PLL_PREDIV_1, CLK_PLL_POSTDIV_1, 0x4C, 0, 0, 0x0, 0x0, HAL_CLK_PLL_VCO_MODE_0}, CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,  1459200000}, 
    { HAL_CLK_SOURCE_GPLL2, { HAL_CLK_SOURCE_XO, CLK_PLL_PREDIV_1, CLK_PLL_POSTDIV_1, 0x5E, 0, 0, 0x0, 0x0, HAL_CLK_PLL_VCO_MODE_0}, CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,  1804800000},

};
const ClockPLLTableType BIMCPLLConfigTbl_V1 = CLOCK_TABLE(BIMCPLLConfig_V1);

ClockPLLTableType const *BIMCPLLConfigTbl = &BIMCPLLConfigTbl_V1;

/*
 * DDR CPLL Clock configurations.
 *
** =========================================================================
**
** 'HAL_clk_ClockMuxConfigType' repurposing (allows RPM-HAL compatibilty):
**    nDiv2x[15]    - 0 for GCC, and 1 for DDRCC mode
**    nDiv2x[15:8]  - index to DDRCC config (zeroed out for RPM)
**    nDiv2x[7:0]   - DDR nDiv2x (placed here for RPM detect mux config)
**
**    nM[15:12]     - index to GPLL23 config
**    nM[11:6]      - BIMC nDiv2x
**    nM[5:0]       - HMSS nDiv2x
**
**    nN[15:8]      - GFX nDiv2x
**    nN[7:0]       - MPSS nDiv2x
**
**    n2D[15:0]     - VDDA EBI vote
**
** =========================================================================*/
RPMClockMuxConfigType DDRClockConfig_V1[] =
{
  /* ======================================================================================================================================================================================
  ** {freq_Hz,  {source,                  (ddrcc_mode, ddr_gpll0_sel, ddr_div2x, cdsp_gpll0_sel, cdsp_div2x),
                                                                               ( bimc_gpll0_sel, bimc_div2x, hmss_gpll0_sel, hmss_div2x)
                                                                                                                     (gfx_gpll0_sel, gfx_div2x, mpss_gpll0_sel, mpss_div2x), 
                                                                                                                                                       {gpll23_idx, VDDA_EBI_vote}},               VDDCX_vote }
  ** =====================================================================================================================================================================================*/
  {  100000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0,12, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  150000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 8, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  200000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 6, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  300000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 1, 4, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  412800000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 4, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},

  {  547200000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 16, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  681600000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 18, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  768000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 20, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  { 1017600000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 22, 0, 4), HAL_CLK_BIMC_M_VAL(0, 2, 1, 2), HAL_CLK_BIMC_N_VAL(0, 4, 0, 3), HAL_CLK_BIMC_N2D_VAL(1, RAILWAY_SVS_HIGH)}, RAILWAY_SVS_HIGH},
  { FREQ_1296000K, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 24, 2, 4), HAL_CLK_BIMC_M_VAL(2, 2, 0, 4), HAL_CLK_BIMC_N_VAL(2, 4, 1, 2), HAL_CLK_BIMC_N2D_VAL(2, RAILWAY_NOMINAL)}, RAILWAY_NOMINAL},
 // { FREQ_1353600K, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 26, 2, 4), HAL_CLK_BIMC_M_VAL(2, 2, 0, 4), HAL_CLK_BIMC_N_VAL(2, 4, 1, 2), HAL_CLK_BIMC_N2D_VAL(2, RAILWAY_NOMINAL)}, RAILWAY_NOMINAL},
  { 1555200000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 28, 2, 4), HAL_CLK_BIMC_M_VAL(2, 2, 0, 4), HAL_CLK_BIMC_N_VAL(2, 4, 1, 2), HAL_CLK_BIMC_N2D_VAL(2, RAILWAY_NOMINAL)}, RAILWAY_NOMINAL},
  { 1804800000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 30, 0, 8), HAL_CLK_BIMC_M_VAL(0, 4, 4, 4), HAL_CLK_BIMC_N_VAL(0, 8, 1, 2), HAL_CLK_BIMC_N2D_VAL(3, RAILWAY_TURBO)}, RAILWAY_TURBO},
  {0},
};
const ClockRPMTableType DDRClockConfigTbl_V1 = CLOCK_TABLE(DDRClockConfig_V1);

ClockRPMTableType const *DDRClockConfigTbl = &DDRClockConfigTbl_V1;


/* Starhawks DDR clock plan */
RPMClockMuxConfigType DDRClockConfig_SDM630[] =
{
  /* ======================================================================================================================================================================================
  ** {freq_Hz,  {source,                  (ddrcc_mode, ddr_gpll0_sel, ddr_div2x, cdsp_gpll0_sel, cdsp_div2x),
                                                                               ( bimc_gpll0_sel, bimc_div2x, hmss_gpll0_sel, hmss_div2x)
                                                                                                                     (gfx_gpll0_sel, gfx_div2x, mpss_gpll0_sel, mpss_div2x), 
                                                                                                                                                       {gpll23_idx, VDDA_EBI_vote}},               VDDCX_vote }
  ** =====================================================================================================================================================================================*/
  {  100000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0,12, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  150000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 8, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  200000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 6, 0,10), HAL_CLK_BIMC_M_VAL(0, 6, 0, 6), HAL_CLK_BIMC_N_VAL(0,10, 0, 6), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS_LOW)}, RAILWAY_SVS_LOW},
  {  300000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(0, 1, 4, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  412800000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(0, 0, 4, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},

  {  547200000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 16, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  681600000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 18, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  {  768000000, {HAL_CLK_SOURCE_GPLL0,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 20, 1, 6), HAL_CLK_BIMC_M_VAL(2, 4, 2, 4), HAL_CLK_BIMC_N_VAL(1, 6, 2, 4), HAL_CLK_BIMC_N2D_VAL(0, RAILWAY_SVS)}, RAILWAY_SVS},
  { 1017600000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 22, 0, 4), HAL_CLK_BIMC_M_VAL(0, 2, 1, 2), HAL_CLK_BIMC_N_VAL(0, 4, 0, 3), HAL_CLK_BIMC_N2D_VAL(1, RAILWAY_SVS_HIGH)}, RAILWAY_SVS_HIGH},
  { 1296000000, {HAL_CLK_SOURCE_GPLL2,       HAL_CLK_BIMC_DIV2X_VAL(1, 0, 24, 2, 4), HAL_CLK_BIMC_M_VAL(2, 2, 0, 4), HAL_CLK_BIMC_N_VAL(3, 6, 1, 2), HAL_CLK_BIMC_N2D_VAL(2, RAILWAY_NOMINAL)}, RAILWAY_NOMINAL},
  {0},
};
const ClockRPMTableType DDRClockConfigTbl_SDM630 = CLOCK_TABLE(DDRClockConfig_SDM630);

/* The current rate of the DRR clock in kHz */
static uint32 ddr_speed_khz = 200000;

/*=========================================================================
      Function Definitions
=========================================================================*/

/* =========================================================
**  Function : Clock_InitBIMCPlan()
** =======================================================*/
/* Choose between the V1 and V2 clock plans based on chip revision.
 *
 * @param None
 * @return None
 */
void Clock_InitBIMCPlan( void )
{
  uint32 nIdx;
  uint16 part_num = HWIO_INF(TLMM_HW_REVISION_NUMBER, PRODUCT_DEVICE_ID);
  
  if(HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_NUMBER) == DEVICE_ID_SDM630)
   {
      DDRClockConfigTbl = &DDRClockConfigTbl_SDM630;
   }
  else if(HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_NUMBER) == DEVICE_ID_SDM660 && (part_num == PART_NUM_SDM636 || part_num == PART_NUM_SDA636))
   {
      for ( nIdx = 0; (DDRClockConfigTbl->table[nIdx].nFreqHz != 0); nIdx++ )
      {
        if(DDRClockConfigTbl->table[nIdx].nFreqHz == FREQ_1296000K)
        {
          DDRClockConfigTbl->table[nIdx].nFreqHz = FREQ_1353600K;
          break;
        }
      }
   }
}


/* =========================================================
**  Function : Clock_SetDDRMinMax()
** =======================================================*/
/* 
 * Function is used for setting minimum and maximum DDR speed.
 *
 * @param 
 *   nDDRMin - Minimum DDR speed index.
 *   nDDRMax - Maximum DDR speed index.
 * @return 
 *   TRUE  - Min and Max are in supporting range
 *   FALSE - Min and Max are NOT in supporting range.  No setting effective.
 */
boolean Clock_SetDDRMinMax( uint8 nDDRMin, uint8 nDDRMax )
{
  /* Check if Min and Max are in supportive range */
  if ( (nDDRMin > nDDRMax) || (nDDRMin > MAX_DDR_LEVELS) )
  {
    return FALSE;
  }

  /* Over-write Max if it is higher than supportive levels */
  if ( nDDRMax > MAX_DDR_LEVELS )
  {
    nDDRMax = MAX_DDR_LEVELS;
  }

  nDDRMinIndex = nDDRMin;
  nDDRMaxIndex = nDDRMax;

  return TRUE;
}


/* =========================================================
**  Function : Clock_GetDDRMinMax()
** =======================================================*/
/* 
 * Function is used for getting minimum and maximum DDR level index.
 *
 * @param 
 *   pDDRMin - Pointer to Minimum DDR speed index.
 *   pDDRMax - Pointer to Maximum DDR speed index.
 * @return 
 *   None
 */
void Clock_GetDDRMinMax( uint8 *pDDRMin, uint8 *pDDRMax )
{
  *pDDRMin = nDDRMinIndex;
  *pDDRMax = nDDRMaxIndex;
}


/* =========================================================
**  Function : Clock_DDRSpeed()
** =======================================================*/
/* 
 * @param None
 * @return The clock rate of DDR in kHz
 */
uint32 Clock_DDRSpeed()
{
  return ddr_speed_khz;
}

void Clock_StoreDDRFreqKHz ( uint32 nFreqKHz )
{
  ddr_speed_khz = nFreqKHz;
}


/* ============================================================================
**  Function : Clock_BIMCQuery
** ============================================================================
*/
/*!
 
  This function lets the client query the BIMC frequency plan and the number 
  of supported frequencies.
  @return
  NONE
  @dependencies
  None.

*/
void Clock_BIMCQuery(ClockQueryType nQuery, void* pResource)
{
  uint32 nIdx;
  uint32 eDDRCCModeEn;
  uint32 *pnData;
  ClockPlanType *pBimcClkPlan;

  /* Return early if no output buffer is given. */
  if ( pResource == NULL )
  {
    return;
  }

  switch ( nQuery )
  {
    case CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS:
      pnData = (uint32 *)pResource;
      for ( nIdx = 0; (DDRClockConfigTbl->table[nIdx].nFreqHz != 0); nIdx++ );

      *pnData = nIdx;
      break;

    case CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ:
      pBimcClkPlan = (ClockPlanType*)pResource;

      for ( nIdx = 0; (DDRClockConfigTbl->table[nIdx].nFreqHz != 0); nIdx++ )
      {
        eDDRCCModeEn = HAL_CLK_BIMC_DIV2X_DDRCC_MODE_EN(DDRClockConfigTbl->table[nIdx].HALConfig.nDiv2x);

        pBimcClkPlan[nIdx].nFreqKHz   = (DDRClockConfigTbl->table[nIdx].nFreqHz / 1000);
        pBimcClkPlan[nIdx].eVRegLevel = DDRClockConfigTbl->table[nIdx].eVRegLevel;
        pBimcClkPlan[nIdx].eMode      = eDDRCCModeEn;
      }
      break;

    default:
      return;
  }
}

/* ============================================================================
**  Function : Clock_EnableBIMCSource
** ============================================================================
*/
/**
  Configures and enables a BIMC PLL. Handles GPLL2/GPLL3 ping-pong.

  @params
    pNewCfg           [in]  - BIMC config to prepare.
    pOrigCfg          [in]  - Previous BIMC config.
    peSourceToDisable [out] - BIMC source that might require disabling after
                              the clock switch via Clock_DisableBIMCSources().

  @return
    True upon success.

  @dependencies
    None.

  @sa
    None
*/
static boolean Clock_EnableBIMCSource
(
  RPMClockMuxConfigType *pNewCfg,
  RPMClockMuxConfigType *pOrigCfg,
  HAL_clk_SourceType    *peSourceToDisable
)
{
  uint32               nPLLCfgIdx;
  Clock_ConfigType    *pClockCfg;
  ClockConfigPLLType  *pPLLCfg;
  ClockSourceType     ePLL;
  HAL_clk_SourceType  eNewSource = pNewCfg->HALConfig.eSource;
  RPMClockSourceConfigType const *pSource;  /* cache the PLL */

  /* Nothing to do for GPLL0/XO (enabled in PBL). */
  if ( (eNewSource == HAL_CLK_SOURCE_XO) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL0) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL0_DIV2))
  {
    *peSourceToDisable = pOrigCfg->HALConfig.eSource;
    return TRUE;
  }

  /* Else PLL must be GPLL2 or GPLL3. */
  if ( (eNewSource != HAL_CLK_SOURCE_GPLL2) &&
       (eNewSource != HAL_CLK_SOURCE_GPLL3) )
  {
    return FALSE;
  }

  pClockCfg = Clock_Config();

  /* Switch to whichever of GPLL2/GPLL3 is currently inactive. */
  if ( HWIO_INF(GCC_GPLL2_MODE, PLL_ACTIVE_FLAG) == 0 )
  {
    pNewCfg->HALConfig.eSource = HAL_CLK_SOURCE_GPLL2;
    *peSourceToDisable = HAL_CLK_SOURCE_GPLL3;

    pPLLCfg = &pClockCfg->PLL2_Cfg;
    ePLL = SRC_GPLL2;
  }
  else if ( HWIO_INF(GCC_GPLL3_MODE, PLL_ACTIVE_FLAG) == 0 )
  {
    pNewCfg->HALConfig.eSource = HAL_CLK_SOURCE_GPLL3;
    *peSourceToDisable = HAL_CLK_SOURCE_GPLL2;

    pPLLCfg = &pClockCfg->PLL3_Cfg;
    ePLL = SRC_GPLL3;
  }
  else
  {
    /* Both GPLL2 and GPLL3 are active => bug. */
    return FALSE;
  }

  /* Set new configuration for selected PLL. */
  nPLLCfgIdx = HAL_CLK_BIMC_N2D_GPLL23_IDX(pNewCfg->HALConfig.n2D);

  if(nPLLCfgIdx > BIMCPLLConfigTbl->count) return FALSE;
  pSource = &BIMCPLLConfigTbl->table[nPLLCfgIdx];
  pPLLCfg->nVCO     = pSource->HALConfig.eVCO;
  pPLLCfg->nL       = pSource->HALConfig.nL;
  //pPLLCfg->nM       = 0;
  //pPLLCfg->nN       = 0;
  pPLLCfg->nAlpha   = CLK_64B_ALPHA(pSource->HALConfig.nAlphaU,
                                    pSource->HALConfig.nAlpha);
  pPLLCfg->nPostDiv = pSource->HALConfig.nPostDiv;

  if ( !Clock_ConfigureSource(ePLL) ) return FALSE;

  return Clock_EnableSource( (ClockSourceType)pNewCfg->HALConfig.eSource );
}
/* ============================================================================
**  Function : Clock_EnableBIMCAsyncSource
** ============================================================================
*/
/**
  Configures and enables a BIMC Async PLL. 
*/
static boolean Clock_EnableBIMCAsyncSource
(
  HAL_clk_SourceType eNewSource
)
{
  boolean rtrn = FALSE;
  ClockConfigPLLType NewConfig;
  Clock_ConfigType    *pClockCfg;
  pClockCfg = Clock_Config();

  /* Nothing to do there PLLs are already enabled along with BIMC Source*/
  if ( (eNewSource == HAL_CLK_SOURCE_XO) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL0) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL0_DIV2) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL2) ||
       (eNewSource == HAL_CLK_SOURCE_GPLL3))
  {
    return TRUE;
  }

  switch(eNewSource)
  {
    case SRC_GPLL1:
     NewConfig = pClockCfg->PLL1_Cfg;
     NewConfig.nVoteAddr = HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE);
     NewConfig.nVoteMask = HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL1);
     rtrn = Clock_EnablePLL(&NewConfig);
     HWIO_OUTF(GCC_GPLL1_USER_CTL, PLLOUT_LV_EARLY, 1);
     break;


    case SRC_GPLL4:
     NewConfig = pClockCfg->PLL4_Cfg;
     NewConfig.nVoteAddr = HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE);
     NewConfig.nVoteMask = HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL4);
     rtrn = Clock_EnablePLL(&NewConfig);
     break;

    case SRC_GPLL5:
     NewConfig = pClockCfg->PLL5_Cfg;
     NewConfig.nVoteAddr = HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE);
     NewConfig.nVoteMask = HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL5);
     rtrn = Clock_EnablePLL(&NewConfig);
     break;
    default:
      break;
  }
  return rtrn;
}

/* ============================================================================
**  Function : Clock_DisableBIMCSource
** ============================================================================
*/
/**
  Disables a BIMC PLL if necessary.

  @params
    eSource [in]  - BIMC source to disable.

  @return
    True upon success.

  @dependencies
    None.

  @sa
    None
*/
static boolean Clock_DisableBIMCSource
(
  HAL_clk_SourceType    eSource
)
{
  /* Never disable GPLL0/XO. */
  if ( (eSource == HAL_CLK_SOURCE_XO) ||
       (eSource == HAL_CLK_SOURCE_GPLL0) ||
       (eSource == HAL_CLK_SOURCE_GPLL0_DIV2))
  {
    return TRUE;
  }

  /* Else PLL must be GPLL2 or GPLL3. */
  if ( (eSource != HAL_CLK_SOURCE_GPLL2) &&
       (eSource != HAL_CLK_SOURCE_GPLL3) )
  {
    return FALSE;
  }

  return Clock_DisableSource( (ClockSourceType)eSource );
}

/* =========================================================================
**  Function : HAL_clk_DDRSetConfigMux
** =========================================================================*/
/*!
    Configure BIMC clock domain.

    @param 
      nCmdRCGRAddr     - Clock CMD_RCGR address
      nSourceIndex    - Source Index
      nDiv2x          - Divider

    @return
      None.

    @dependencies

    @sa None
*/

static void HAL_clk_DDRSetConfigMux
(
  uintnt nCmdRCGRAddr,
  uint32 nSourceIndex,
  uint32 nDiv2x
)
{
  uintnt nCmdRCGRVal;
  uintnt nCfgRCGRAddr = (nCmdRCGRAddr + HAL_CLK_CFG_REG_OFFSET);
  uintnt nCfgRCGRVal  = inp32(nCfgRCGRAddr);

  /*
   * Clear the CFG_RCGR fields.
   */
  nCfgRCGRVal &= ~(HAL_CLK_CFG_RCGR_SRC_SEL_FMSK |
                  HAL_CLK_CFG_RCGR_SRC_DIV_FMSK |
                  HAL_CLK_CFG_RCGR_MODE_FMSK);

  /* Convert divider to HAL format. */
  if ( nDiv2x > 0 )
    nDiv2x--;

  /* Enforce max half-integer divider of 16 (31 in HAL format). */
  if ( nDiv2x > 31 )
    nDiv2x = 31;

  /*
   * Program the source and divider values.
   */
  nCfgRCGRVal |= ((nSourceIndex << HAL_CLK_CFG_RCGR_SRC_SEL_SHFT) & HAL_CLK_CFG_RCGR_SRC_SEL_FMSK);
  nCfgRCGRVal |= ((nDiv2x << HAL_CLK_CFG_RCGR_SRC_DIV_SHFT) & HAL_CLK_CFG_RCGR_SRC_DIV_FMSK);

  /*
   * Write the final CFG register value.
   */
  outp32(nCfgRCGRAddr, nCfgRCGRVal);

  /*
   * Trigger the update.
   */
  nCmdRCGRVal = inp32(nCmdRCGRAddr);
  nCmdRCGRVal |= HAL_CLK_CMD_CFG_UPDATE_FMSK;
  outp32(nCmdRCGRAddr, nCmdRCGRVal);

  /*
   * Wait until update finishes.
   */
  while(inp32(nCmdRCGRAddr) & HAL_CLK_CMD_CFG_UPDATE_FMSK);
}

/* =========================================================================
**  Function : HAL_clk_DDRConfigMux
** =========================================================================*/
/*!
    Programs 

    @param
      pmConfig -  [IN] Clock mux config structure

    @return
      None.

    @dependencies
      None.

    @sa
      None.
*/

enum {
  GPLL23_GPLL0_BIMC_DDR_RCG_PLL_ID,
  GPLL0_ASYNC_CLK_PLL_ID,
  GPLL1_ASYNC_CLK_PLL_ID,
  GPLL4_ASYNC_CLK_PLL_ID,
  GPLL5_ASYNC_CLK_PLL_ID,
  NUM_GPLLx_ASYNC_CLK_PLL_ID
}GPLLx_BIMC_DDR_RCG_ID;

static uint32 nAsyncPllSel[NUM_GPLLx_ASYNC_CLK_PLL_ID] = 
{ 0,
  HAL_CLK_SOURCE_GPLL0,
  HAL_CLK_SOURCE_GPLL1,
  HAL_CLK_SOURCE_GPLL4,
  HAL_CLK_SOURCE_GPLL5,
 };

static boolean HAL_clk_DDRConfigMux
(
  HAL_clk_ClockMuxConfigType *pmConfig,
  int nNextCPLL
)
{

  uint8  nDDRCCModeEn;
  uint32 nPllSel[NUM_GPLLx_ASYNC_CLK_PLL_ID] = {0};
  HAL_clk_SourceType   nNewPLL[MAX_BIMC_DDR_ASYNC_CLK];
  uint32 id;

  if ( pmConfig == NULL )
    return FALSE;

  /* Get source index from source enum. */
  if ( !Clock_SourceMapToGCC((ClockSourceType)pmConfig->eSource, &nPllSel[GPLL23_GPLL0_BIMC_DDR_RCG_PLL_ID]) )
    return FALSE;
  if ( !Clock_SourceMapToGCC((ClockSourceType)HAL_CLK_SOURCE_GPLL0, &nPllSel[GPLL0_ASYNC_CLK_PLL_ID]) )
    return FALSE;

  if ( !Clock_SourceMapToGCC((ClockSourceType)HAL_CLK_SOURCE_GPLL1, &nPllSel[GPLL1_ASYNC_CLK_PLL_ID]) )
    return FALSE;

  if ( !Clock_SourceMapToGCC((ClockSourceType)HAL_CLK_SOURCE_GPLL4, &nPllSel[GPLL4_ASYNC_CLK_PLL_ID]) )
    return FALSE;

  if ( !Clock_SourceMapToGCC((ClockSourceType)HAL_CLK_SOURCE_GPLL5, &nPllSel[GPLL5_ASYNC_CLK_PLL_ID]) )
    return FALSE;

  /*
   * Set GCC_BIMC_DDR_CPLL config.
   * Ping-pong between CPLL0 and CPLL1, starting from CPLL0.
   * On switches from DDRCC to GCC, we must start over from CPLL0.
   *
   */
  

  nDDRCCModeEn = HAL_CLK_BIMC_DIV2X_DDRCC_MODE_EN(pmConfig->nDiv2x);

  if( nNextCPLL == 0)
  {
    if(nDDRCCModeEn == 0)
    {
      HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL0_ROOT_CMD_RCGR),
                              nPllSel[HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x)],
                              HAL_CLK_BIMC_DIV2X_DDR_DIV2X(pmConfig->nDiv2x));
      Clock_ToggleClock(HWIO_GCC_BIMC_DDR_CPLL0_CBCR_ADDR, CLK_TOGGLE_ENABLE); // GCC Mode needs CPLL clock
    } else {
      HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL0_ROOT_CMD_RCGR), 0, 0);
    }
  } else {
    if(nDDRCCModeEn == 0)
    {
      HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL1_ROOT_CMD_RCGR),
                              nPllSel[HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x)],
                              HAL_CLK_BIMC_DIV2X_DDR_DIV2X(pmConfig->nDiv2x));
      Clock_ToggleClock(HWIO_GCC_BIMC_DDR_CPLL1_CBCR_ADDR, CLK_TOGGLE_ENABLE); // GCC Mode needs CPLL clock
    } else {
      HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL1_ROOT_CMD_RCGR), 0, 0);
    }
  }

  if((HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(pmConfig->nM) >= NUM_GPLLx_ASYNC_CLK_PLL_ID) || 
     (HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(pmConfig->nM) >= NUM_GPLLx_ASYNC_CLK_PLL_ID) || 
     (HAL_CLK_BIMC_N_GFX_GPLL0_SEL(pmConfig->nN)  >= NUM_GPLLx_ASYNC_CLK_PLL_ID) || 
     (HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(pmConfig->nN) >= NUM_GPLLx_ASYNC_CLK_PLL_ID) || 
     (HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x)  >= NUM_GPLLx_ASYNC_CLK_PLL_ID) || 
     (HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(pmConfig->nDiv2x) >= NUM_GPLLx_ASYNC_CLK_PLL_ID))
    {
      return FALSE;
    }
  
  /*Enable BIMC Async clock sources*/
  nAsyncPllSel[0] = pmConfig->eSource;
  nNewPLL[0] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(pmConfig->nDiv2x)]);
  nNewPLL[1] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(pmConfig->nDiv2x)]); 
  nNewPLL[2] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(pmConfig->nM)]);
  nNewPLL[3] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(pmConfig->nM)]);
  nNewPLL[4] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_N_GFX_GPLL0_SEL(pmConfig->nN)]);
  nNewPLL[5] = (HAL_clk_SourceType)(nAsyncPllSel[HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(pmConfig->nN)]);
 
 id =0;
 while(id < MAX_BIMC_DDR_ASYNC_CLK)
 {  
   if (!Clock_EnableBIMCAsyncSource(nNewPLL[id])) return FALSE;
   id++;
 }

  /* Set GCC_BIMC config. */
  HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_CMD_RCGR),
                          nPllSel[HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(pmConfig->nM)],
                          HAL_CLK_BIMC_M_BIMC_DIV2X(pmConfig->nM));

  /* Set BIMC_HMSS_AXI config. */
  HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_HMSS_AXI_CMD_RCGR),
                          nPllSel[HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(pmConfig->nM)],
                          HAL_CLK_BIMC_M_HMSS_DIV2X(pmConfig->nM));

  /* Set GCC_GPU_BIMC_GFX config. */
  HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_GPU_BIMC_GFX_CMD_RCGR),
                          nPllSel[HAL_CLK_BIMC_N_GFX_GPLL0_SEL(pmConfig->nN)],
                          HAL_CLK_BIMC_N_GFX_DIV2X(pmConfig->nN));

  /* Set GCC_MSS_Q6_BIMC_AXI config. */
  HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_MSS_Q6_BIMC_AXI_CMD_RCGR),
                          nPllSel[HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(pmConfig->nN)],
                          HAL_CLK_BIMC_N_MPSS_DIV2X(pmConfig->nN));

 /* Set GCC_cDSP config. */
 HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_CDSP_BIMC_CMD_RCGR),
                         nPllSel[HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(pmConfig->nDiv2x)],
                         HAL_CLK_BIMC_DIV2X_CDSP_DIV2X(pmConfig->nDiv2x));

  return TRUE;
} /* HAL_clk_DDRConfigMux */

/* =========================================================================
**  Function : Clock_FindBIMCLevel
** =========================================================================*/
/*!
    Find the table line that meets or exceeds the request.

    @param -  nFreqHz [in] Frequency to search for in the table
    @param -  pConfigTable [in] Table to search
    @param -  nTableLimit [in] Length of table 
    @return - index to the table row to be used.

    @dependencies
    None.

    @sa None
*/
static uint32 Clock_FindBIMCLevel
( 
  uint32 nFreqHz,
  ClockRPMTableType const *pRPMTable
)
{
  uint32 index = 0, nSupCfg = 0;
  RPMClockMuxConfigType const *pConfigTable;
  uint32 nTableLimit;

  if(pRPMTable == NULL) return 0;
  pConfigTable = pRPMTable->table;
  nTableLimit = pRPMTable->count;

  for(index = 0; (index < nTableLimit) && (pConfigTable[index].nFreqHz != 0); index++)
  {
    if( pConfigTable[index].nChipVersion == 0 )
    {
      nSupCfg = index;
    }
    if( (nSupCfg == index) && pConfigTable[index].nFreqHz >= nFreqHz )
    {
      return nSupCfg;
    }
  }

  if(pConfigTable[nSupCfg].nFreqHz == 0) 
  {
    /* End of the table is reached, use the last line, or line 0 if the table is empty */
    nSupCfg = (nSupCfg > 0 ? nSupCfg-1 : 0);
  }
  return nSupCfg;
}

/* =========================================================================
**  Function : Clock_SetBIMCSpeed
** =========================================================================*/
/*!
    Switch DDR and the related BIMC roots to the requested frequency

    @param -  nFreqHz [in] Frequency to search for in the table
    @return - FALSE on fail, TRUE on success

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetBIMCSpeed(uint32 nFreqKHz )
{
  uint32                   nNewLvlIdx, nCurrHz, nCurrKHz, nCurrLvlIdx;
  HAL_clk_SourceType       ePrevSource;
  RPMClockMuxConfigType   *pNewDDRCfg;
  RPMClockMuxConfigType   *pCurrDDRCfg;
  uint32                   nFreqHz;
  Clock_RailwayType       *pClockRailway = Clock_RailwayConfig();
  int                      nNextCPLL, nPrevCPLL;
  railway_corner          CurrEBIVolLvl, NewEBIVolLvl;

  if ( RAIL_NOT_SUPPORTED_BY_RAILWAY == pClockRailway->nCxRailId )
    return TRUE;

  /* Find current level */
  nCurrKHz = Clock_DDRSpeed();
  nCurrHz = (1000 * nCurrKHz);
  nCurrLvlIdx = Clock_FindBIMCLevel ( nCurrHz, DDRClockConfigTbl );

  pCurrDDRCfg = &DDRClockConfigTbl->table[nCurrLvlIdx];
  if (nCurrHz != pCurrDDRCfg->nFreqHz) return FALSE;

  /* Find new level */
  nFreqHz = (nFreqKHz * 1000);
  nNewLvlIdx = Clock_FindBIMCLevel ( nFreqHz, DDRClockConfigTbl );
  pNewDDRCfg = &DDRClockConfigTbl->table[nNewLvlIdx];
  nFreqKHz = (pNewDDRCfg->nFreqHz / 1000);

  CurrEBIVolLvl = HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(DDRClockConfigTbl->table[nCurrLvlIdx].HALConfig.n2D);
  NewEBIVolLvl = HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(DDRClockConfigTbl->table[nNewLvlIdx].HALConfig.n2D);

  // Change VDDA_EBI rail if increase
  if ( (RAIL_NOT_SUPPORTED_BY_RAILWAY != pClockRailway->nEBIRailId) &&
       (nCurrKHz < nFreqKHz) )
  {
    if ( NewEBIVolLvl >= RAILWAY_NOMINAL )
  {
      railway_corner_vote( pClockRailway->EBIVoter, (railway_corner)NewEBIVolLvl);
    railway_transition_rails();
  }
  }

  /* 
   * Vote for higher voltage before the switch if the new frequency is more
   * than the current frequency.
   */
  if ( (RAIL_NOT_SUPPORTED_BY_RAILWAY != pClockRailway->nCxRailId) &&
       (nCurrKHz < nFreqKHz) )
  {
    /* CPU and Buses are running at NOMINAL or higher.  Do not scale voltage below NOMINAL */
    if ( pNewDDRCfg->eVRegLevel >= RAILWAY_NOMINAL )
    {
      // Change VDD_CX rail, VDDA_EBI1 will follow
      railway_corner_vote(pClockRailway->CxVoter, (railway_corner)pNewDDRCfg->eVRegLevel);
      railway_transition_rails();
    }
  }

  /* Enable the next source before switch */
  if( !Clock_EnableBIMCSource(pNewDDRCfg,
                              pCurrDDRCfg,
                              &ePrevSource) )
  {
    return FALSE;
  }

  nNextCPLL = 0;   /* This default covers the GCC -> DDRCC mode change */
  nPrevCPLL = -1;  /* -1 means no previous CPLL, such as DDRCC mode */
  if( HWIO_INF(GCC_BIMC_DDR_CPLL0_CBCR, CLK_ENABLE) == 1 )
  {
    nPrevCPLL = 0;
    nNextCPLL = 1;
  }
  if( HWIO_INF(GCC_BIMC_DDR_CPLL1_CBCR, CLK_ENABLE) == 1 )
  {
    if(nPrevCPLL == 0) return FALSE; /* Both CPLLs are On.  That is bad */
    nPrevCPLL = 1;
    nNextCPLL = 0;
  }
  
  if( !HAL_clk_DDRConfigMux( &pNewDDRCfg->HALConfig, nNextCPLL ) )
  {
    return FALSE;
  }


  ddr_pre_clock_switch( nCurrKHz, nFreqKHz, SDRAM_INTERFACE_BOTH );
  ddr_clock_switch( nCurrKHz, nFreqKHz, SDRAM_INTERFACE_BOTH );
  ddr_post_clock_switch( nCurrKHz, nFreqKHz, SDRAM_INTERFACE_BOTH );

  /* Park previous CPLL at CXO/1 and turn it off. */
  if( nPrevCPLL == 0)
  {
    HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL0_ROOT_CMD_RCGR), 0, 0);
    Clock_ToggleClock(HWIO_GCC_BIMC_DDR_CPLL0_CBCR_ADDR, CLK_TOGGLE_DISABLE);
  }
  if( nPrevCPLL == 1)
  {
    HAL_clk_DDRSetConfigMux((uintnt)HWIO_ADDR(GCC_BIMC_DDR_CPLL1_ROOT_CMD_RCGR), 0, 0);
    Clock_ToggleClock(HWIO_GCC_BIMC_DDR_CPLL1_CBCR_ADDR, CLK_TOGGLE_DISABLE);
  }

  /* Disable previous DDR-dedicated sources after the switch */
  Clock_DisableBIMCSource(ePrevSource);

  /* 
   * Vote for lower voltage after the switch if the new frequency is less
   * than the current frequency.
   */
  if ( (RAIL_NOT_SUPPORTED_BY_RAILWAY != pClockRailway->nCxRailId) && 
       (nCurrKHz > nFreqKHz) )
  {
    /* CPU and Buses are running at NOMINAL or higher.  Do not scale voltage below NOMINAL */
    if ( pNewDDRCfg->eVRegLevel >= RAILWAY_NOMINAL )
    {
      // Change VDD_CX rail, VDDA_EBI1 will follow
      railway_corner_vote(pClockRailway->CxVoter, (railway_corner)pNewDDRCfg->eVRegLevel);
      railway_transition_rails();
    }
  }

  // Change VDDA_EBI rail if decrease
  if ( (RAIL_NOT_SUPPORTED_BY_RAILWAY != pClockRailway->nEBIRailId) && 
        (nCurrKHz > nFreqKHz))
  {
  
    /* CPU and Buses are running at NOMINAL or higher.  Do not scale voltage below NOMINAL */
    if ( NewEBIVolLvl >= RAILWAY_NOMINAL )
  {
      railway_corner_vote( pClockRailway->EBIVoter, (railway_corner)NewEBIVolLvl);
    railway_transition_rails();
  }
  }

  nDDRActiveIndex = nNewLvlIdx;
  Clock_StoreDDRFreqKHz( nFreqKHz );

  return TRUE;
}

/* =========================================================================
**  Function : Clock_CopyBIMCPlanToRPM()
** =========================================================================*/
/*!
    Copy the BIMC clock plan into shared memory for the RPM to use.

    @param -  
    @return - FALSE on fail, TRUE on success

    @dependencies
    None.

    @sa None
*/
boolean Clock_CopyBIMCPlanToRPM()
{
  uint32 smem_size = 
    (sizeof(ClockBIMCConfigInfo) + 
    (sizeof(ClockBIMCTableHeaderType) * CLOCK_BIMC_NUM_TABLES) +
    BIMCPLLConfigTbl->size +
    DDRClockConfigTbl->size);

  uint32 tip;
  ClockBIMCConfigInfo *pBIMCConfigInfo;
  ClockBIMCTableHeaderType *pBIMCTableHeaders;
  void *pSMEM = smem_alloc(SMEM_CLOCK_INFO, smem_size);

  if(pSMEM == NULL) return FALSE;

  pBIMCConfigInfo = pSMEM;
  pBIMCConfigInfo->nVersion = CLOCK_BIMC_SMEM_VERSION;
  pBIMCConfigInfo->nNumConfig = CLOCK_BIMC_NUM_TABLES;
  pBIMCConfigInfo->nHALNumSrc = HAL_CLK_NUM_OF_SOURCES;
  pBIMCConfigInfo->nMinLevel = nDDRMinIndex;
  pBIMCConfigInfo->nMaxLevel = nDDRMaxIndex;
  pBIMCConfigInfo->nActiveLevel = nDDRActiveIndex;
  pBIMCConfigInfo->nConfigData = sizeof(ClockBIMCConfigInfo);

  pBIMCTableHeaders = (pSMEM + sizeof(ClockBIMCConfigInfo));

  /* The dynamic tip of the smem copy sequence */
  tip = (sizeof(ClockBIMCConfigInfo) +
        (sizeof(ClockBIMCTableHeaderType) * CLOCK_BIMC_NUM_TABLES));

  pBIMCTableHeaders[0].nNodeSize = BIMCPLLConfigTbl->item_size;
  pBIMCTableHeaders[0].nNumNodes = BIMCPLLConfigTbl->count;
  pBIMCTableHeaders[0].eBIMCTable = CLOCK_BIMC_PLL;
  pBIMCTableHeaders[0].nNodeOffset = tip;
  qmemscpy((pSMEM + tip), (smem_size - tip), BIMCPLLConfigTbl->table, BIMCPLLConfigTbl->size);
  tip += BIMCPLLConfigTbl->size;

  pBIMCTableHeaders[1].nNodeSize = DDRClockConfigTbl->item_size;
  pBIMCTableHeaders[1].nNumNodes = DDRClockConfigTbl->count;
  pBIMCTableHeaders[1].eBIMCTable = CLOCK_BIMC_DDR;
  pBIMCTableHeaders[1].nNodeOffset = tip;
  qmemscpy((pSMEM + tip), (smem_size - tip), DDRClockConfigTbl->table, DDRClockConfigTbl->size);
  tip += DDRClockConfigTbl->size;

  if(tip == smem_size)
    return TRUE;
  else
    return FALSE;
}

//
// XBL Loader Clock Driver BIMC switch test.
//

#ifdef CLOCK_BIMC_TEST
boolean Clock_BIMCTest()
{
  uint32 nNumLevel;
  ClockPlanType aClockPlan[15];
  int i;

  /* Call BIMCQuery to get the Num Perf Levels */
  Clock_BIMCQuery(CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS,&nNumLevel);

  /* Call BIMCQuery to get the Clock Plan */
  Clock_BIMCQuery(CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ, aClockPlan);

  for(i=0; i<nNumLevel; i++)
  {
    if(Clock_SetBIMCSpeed( aClockPlan[i].nFreqKHz ) == FALSE) return FALSE;
  }
  return TRUE;
}
#endif
