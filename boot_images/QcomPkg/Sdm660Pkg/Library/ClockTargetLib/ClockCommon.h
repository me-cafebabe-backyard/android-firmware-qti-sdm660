#ifndef CLOCKCOMMON_H
#define CLOCKCOMMON_H

/**
==============================================================================

  @file ClockCommon.h

  Common functions for PLL and clock management

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

#include <HALcomdef.h>

/*=========================================================================
      Definitions
==========================================================================*/
#define CLK_ELEM_SIZE(array)      sizeof((array)[0])
#define CLK_NUM_ELEM(array)       (sizeof(array) / CLK_ELEM_SIZE(array))

#define CLK_64B_ALPHA(a_u, a_l)   ((((uint64)(a_u)) << 32) | (a_l))

#define CLK_ENABLE_MSK 0x00000001
#define CLK_OFF_MSK    0x80000000
#define CLK_GDSCR_SW_COLLAPSE_MSK 0x00000001
#define CLK_GDSCR_PWR_ON_MSK      0x80000000
#define CLK_GDSCR_TIMEOUT_US      150

/*
 * RCGR update timeout. In practice this should be very short (less than 1us),
 * but it depends on the clock frequency being fed into the RCG. Choosing
 * a very conservative value.
 */
#define CLOCK_UPDATE_TIMEOUT_US 1000

/*=========================================================================
      Type Definitions
==========================================================================*/
/*
 * HAL_clk_SourceType : Adopted from RPM for shared data compatibility
 *
 */
typedef enum
{
  HAL_CLK_SOURCE_NULL             = 0,

  /*
   * XO
   */
  HAL_CLK_SOURCE_XO               = 1,

  /*
   * GCC PLL
   */
  HAL_CLK_SOURCE_GPLL0,
  HAL_CLK_SOURCE_GPLL1,
  HAL_CLK_SOURCE_GPLL2,
  HAL_CLK_SOURCE_GPLL3,
  HAL_CLK_SOURCE_GPLL4,
  HAL_CLK_SOURCE_GPLL5,

  /*
   * MMSS PLL
   */
  HAL_CLK_SOURCE_MMPLL0,
  HAL_CLK_SOURCE_MMPLL1,
  HAL_CLK_SOURCE_MMPLL2,
  HAL_CLK_SOURCE_MMPLL3,
  HAL_CLK_SOURCE_MMPLL4,
  HAL_CLK_SOURCE_MMPLL5,
  HAL_CLK_SOURCE_MMPLL10,

  /*
   * External source
   */
  HAL_CLK_SOURCE_EXTERNAL,
  HAL_CLK_NUM_OF_EXTERNAL_SOURCES,

  /*
   * Raw
   */
  HAL_CLK_SOURCE_RAW0,
  HAL_CLK_SOURCE_RAW1,
  HAL_CLK_SOURCE_RAW2,

  /*
   * Misc
   */
  HAL_CLK_SOURCE_SLEEPCLK,
  HAL_CLK_SOURCE_GROUND,
  HAL_CLK_SOURCE_GPLL0_DIV2,

  HAL_CLK_NUM_OF_SOURCES,

  HAL_ENUM_32BITS(CLK_SOURCE)
} HAL_clk_SourceType;

/*
 * ClockSourceType
 *
 * A type to be used for clock sources in the configuration data and functions.
 */

typedef enum {

  SRC_CXO = HAL_CLK_SOURCE_XO,
  SRC_GPLL0 = HAL_CLK_SOURCE_GPLL0,
  SRC_GPLL0_DIV2 = HAL_CLK_SOURCE_GPLL0_DIV2,
  SRC_GPLL1 = HAL_CLK_SOURCE_GPLL1,
  SRC_GPLL2 = HAL_CLK_SOURCE_GPLL2,
  SRC_GPLL3 = HAL_CLK_SOURCE_GPLL3,
  SRC_GPLL4 = HAL_CLK_SOURCE_GPLL4,
  SRC_GPLL5 = HAL_CLK_SOURCE_GPLL5,
  SRC_MMPLL0 = HAL_CLK_SOURCE_MMPLL0,
  SRC_MMPLL1 = HAL_CLK_SOURCE_MMPLL1,
  SRC_MMPLL2 = HAL_CLK_SOURCE_MMPLL2,
  SRC_MMPLL3 = HAL_CLK_SOURCE_MMPLL3,
  SRC_MMPLL4 = HAL_CLK_SOURCE_MMPLL4,
  SRC_MMPLL5 = HAL_CLK_SOURCE_MMPLL5,
  SRC_MMPLL10 = HAL_CLK_SOURCE_MMPLL10,
  SRC_GPLL6, /* No HAL definition for GPLL6 */
  SRC_EXT1,
  SRC_EXT2,
  SRC_GPLL1_DIV2
} ClockSourceType;

/*
 * ClockSourceMuxType
 *
 * A type to choose the mapping for the mux.
 */
typedef enum {
  MUX_GCC,
  MUX_MMSS,
  MUX_SDCC2,
  MUX_QSPI,
  NUM_MUX_TYPES
} ClockSourceMuxType;

/*
 * ClockConfigPLLType
 *
 * Parameters used for configuring a source that is a PLL.
 *
 *  nPLLModeAddr  - The address of the PLL MODE register.
 *  nVoteAddr     - The address of the PLL voting register. Set to NULL for
 *                  non-FSM mode.
 *  nVoteMask     - The mask of the voting bit.
 *  eVCO          - The internal VCO to use.
 *  nPreDiv       - The pre-divider value (generally 1 or 2).
 *  nPostDiv      - The post-divider value 
 *  nL            - The L value for the PLL.  The PLL output frequency is derived
 *                  as out_freq = ((in_freq / nPreDiv) * (L + M/N)) / nPostDiv.
 *  nM            - The M value (see above).
 *  nN            - The N value (see above).
 *  nAlpha        - The Alpha(prog) value. For the 20nm PLLs, the output frequency is
 *                  derived as :
 *                  out_freq = ((in_freq / nPreDiv) * (L + ALPHAfrac)) / nPostDiv.
 *                  ALPHAprog = 2^b x ALPHAfrac where 'b' is 40 for Prius and 40 for Tesla.
 */
typedef struct ClockConfigPLL
{
  size_t nPLLModeAddr;
  size_t nVoteAddr;
  size_t nVoteMask;
  size_t nVCO;
  uint8  nPreDiv;
  uint8  nPostDiv;
  uint16 nL;
  uint16  nM;
  uint16  nN;
  uint64 nConfigCtl;
  uint64 nTestCtl;
  uint64 nAlpha;
} ClockConfigPLLType;

/*
 * ClockConfigMuxType
 *
 * Parameters used for configuring a standard clock multiplexer.
 *
 *  nCMDRCGRAddr - The address of the CMD RCGR register.
 *  eMux        - The mux type for mapping eSource to register source values.
 *  eSource     - The source to use.
 *  nDiv2x      - The integer (2 * divider) value to use.
 *  nM          - The M value for any M/N counter, or 0 to bypass.
 *  nN          - The N value for any M/N counter.
 *  n2D         - Twice the D value for any M/N counter.
 */
typedef struct ClockConfigMux
{
  uintnt nCMDRCGRAddr;
  ClockSourceMuxType eMux;
  ClockSourceType eSource;
  uint32 nDiv2x;
  uint32 nM;
  uint32 nN;
  uint32 n2D;
} ClockConfigMuxType;

/*
 * Clock_CBCRtoggleType
 *
 * A type to choose the the operation on clocks(enable/disable).
 */
typedef enum{
  CLK_TOGGLE_DISABLE    = 0,
  CLK_TOGGLE_ENABLE     = 1,
  NUM_CLK_TOGGLE_TYPES
} Clock_CBCRtoggleType;

typedef struct
{
  ClockSourceType   ePLL;
  ClockConfigPLLType PLLCfg;
} ClockSourceConfigType;



typedef struct
{
  uint32                nFrequency;
  ClockConfigMuxType    Cfg;
} ClockFreqMuxCfgType;

/* ============================================================================
**  Function : Clock_EnablePLL
** ============================================================================
*/
/*!
    Configure and enable a PLL.  If it is voteable, it will be set for FSM mode
    and voted for using the vote register.

    @param pConfig -  [IN] PLL configuration structure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_EnablePLL(const ClockConfigPLLType *pConfig);

/* ============================================================================
**  Function : Clock_DisablePLL
** ============================================================================
*/
/*!
    Disable a PLL.

    @param pConfig -  [IN] PLL configuration structure
    @return
    TRUE -- The PLL was succesfully disabled.
    FALSE -- Disable failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_DisablePLL(const ClockConfigPLLType *pConfig);

/* =========================================================================
**  Function : Clock_ConfigurePLL
** =========================================================================*/
/**
  Configures a PLL but do not enable it.  If the PLL is already enabled or
  set to FSM mode, this will fail.

  @param *pConfig [in] -- PLL configuration
  @return
  TRUE -- Configuration was successful
  FALSE -- The PLL was already enabled or in FSM mode.

*/
boolean Clock_ConfigurePLL(const ClockConfigPLLType *pConfig);

/* =========================================================================
**  Function : Clock_ConfigMux
** =========================================================================*/
/*!
    Configure a clock mux.

    @param pConfig -  [IN] Clock mux config structure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_ConfigMux (const ClockConfigMuxType *pConfig);

/* =========================================================================
**  Function : Clock_DetectMuxCfg
** =========================================================================*/
/*!
    Detect a clock mux configuration.

    @param pMuxCfg -  [IN] Clock mux config structure.
    @param CurrentCfg -  [IN] Current hardware Clock mux config structure.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_DetectMuxCfg(const ClockConfigMuxType *pMuxCfg,ClockConfigMuxType *CurrentCfg);

/* =========================================================================
**  Function : Clock_TriggerUpdate
** =========================================================================*/
/*!
    Trigger a clock switch, and wait for a timeout.

    @param cmdReg : HWIO_ADDR(*_CMD_CBCR)
    @return
    TRUE -- Clock switch completed.
    FALSE -- Clock switch timed out.

    @dependencies
    None.

    @sa None
*/
boolean Clock_TriggerUpdate(uintnt cmdReg, uintnt nMask);

/* =========================================================================
**  Function : Clock_ToggleClock
** =========================================================================*/
/*!
    Enable/Disable a Clock.

    @param CBCR_addr - Address of the CBCR register
           enable :-  enable/disable the CBCR
    TRUE -- CBCR programming successful.
    FALSE -- CBCR programming failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_ToggleClock(uintnt CBCR_addr, Clock_CBCRtoggleType clk_enable);


/* ===========================================================================
**  Clock_PowerDomainEnable
** ======================================================================== */
boolean Clock_PowerDomainEnable ( uintnt nGDSCRAddr );

/* ===========================================================================
**  Clock_PowerDomainDisable
** ======================================================================== */
boolean Clock_PowerDomainDisable ( uintnt nGDSCRAddr );

#endif /* CLOCKSBLCOMMON_H */
