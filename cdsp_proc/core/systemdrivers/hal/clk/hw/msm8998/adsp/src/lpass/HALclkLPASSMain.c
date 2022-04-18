/*
==============================================================================

FILE:         HALclkLPASSMain.c

DESCRIPTION:
   The main auto-generated file for LPASS.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkLPASSMain.c#1 $

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_BusConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
);

void HAL_clk_AudioClksInvert
(
  HAL_clk_ClockDescType  *pmClockDesc,
  boolean                 bInvert
);


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSBusClockDomainControl;

/* ============================================================================
**    Data
** ==========================================================================*/

#define HAL_CLK_MEM_CORE_ON_BMSK               0x00004000
#define HAL_CLK_MEM_PERIPH_ON_BMSK             0x00002000
#define HAL_CLK_HW_CTL_ON_BMSK                 0x00000002
#define HAL_CLK_CONFIG_LPASS_CORE_CLK_OFF_BMSK 0x80000000

/*
 * HAL_clk_mLpassClockControl_1
 *
 * Functions for controlling common clock functions.
 * Specialization for CORE/PERIH MEM configurations.
 */
HAL_clk_ClockControlType HAL_clk_mLpassClockControl_1 =
{
  /* .Enable           = */ HAL_clk_GenericEnable,
  /* .Disable          = */ HAL_clk_GenericDisable,
  /* .IsEnabled        = */ HAL_clk_GenericIsEnabled,
  /* .IsOn             = */ HAL_clk_GenericIsOn,
  /* .Reset            = */ HAL_clk_GenericReset,
  /* .IsReset          = */ HAL_clk_GenericIsReset,
  /* .Config           = */ HAL_clk_BusConfig,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ HAL_clk_GenericConfigDivider,
  /* .DetectDivider    = */ HAL_clk_GenericDetectDivider,
  /* .ConfigFootswitch = */ HAL_clk_GenericConfigFootswitch,
  /* .Invert           = */ NULL,
};


/*
 * HAL_clk_mLpass_ClockControl_2
 *
 * Functions for controlling common clock functions.
 * Specialization for PRI/SEC/TER/QUA PCM clock inversion.
 */

HAL_clk_ClockControlType HAL_clk_mLpass_ClockControl_2 =
{
  /* .Enable           = */ HAL_clk_GenericEnable,
  /* .Disable          = */ HAL_clk_GenericDisable,
  /* .IsEnabled        = */ HAL_clk_GenericIsEnabled,
  /* .IsOn             = */ HAL_clk_GenericIsOn,
  /* .Reset            = */ HAL_clk_GenericReset,
  /* .IsReset          = */ HAL_clk_GenericIsReset,
  /* .Config           = */ NULL,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ HAL_clk_GenericConfigDivider,
  /* .DetectDivider    = */ HAL_clk_GenericDetectDivider,
  /* .ConfigFootswitch = */ HAL_clk_GenericConfigFootswitch,
  /* .Invert           = */ HAL_clk_AudioClksInvert,
};


/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6COREIMAGEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAONClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSATIMEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSAUDSLIMBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCCLPASSQ6SMMUCFGCNOCCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCCLPASSQ6SMMUCLIENTCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCCLPASSSNOCSWAYCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSEXTMCLK2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSICAMSSDSPSTREAMING0CLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSICAMSSDSPSTREAMING1CLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPCMOEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPRIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFQUADClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSECClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSPKRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSPRIMI2SCLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQCASLIMBUSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQOSFIXEDLATCOUNTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSQUAMI2SCLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSRESAMPLERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSECMI2SCLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSPKRI2SCLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSSTANDALONEBCRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSTERMI2SCLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mLPASSXOClkDomain;

/*
 * Power domains
 */
extern HAL_clk_PowerDomainDescType HAL_clk_mLPASSAUDIOCOREPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mLPASSQ6SMMUPowerDomain;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aLPASSSourceMap
 *
 * LPASS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aLPASSSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_AUDREF,             1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_LPAPLL2_ODD,        5 },
  { HAL_CLK_SOURCE_LPAPLL0_DIV5,       6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}  
};


/*
 * HAL_clk_mLPASSClockDomainControl
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap
};


/*
 * HAL_clk_mLPASSClockDomainControlRO
 *
 * Read-only functions for LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap
};


/*
 * aLPASSSourceMap_1
 *
 * LPASS HW source mapping
 *
 */
static HAL_clk_SourceMapType aLPASSSourceMap_1[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_LPAPLL2,            1 },
  { HAL_CLK_SOURCE_LPAPLL2_DIV2,       2 },
  { HAL_CLK_SOURCE_LPAPLL0,            3 },
  { HAL_CLK_SOURCE_LPAPLL0_DIV2,       4 },
  { HAL_CLK_SOURCE_AUDREF,             5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mLPASSClockDomainControl_1
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControl_1 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_1
};


/*
 * HAL_clk_mLPASSClockDomainControlRO_1
 *
 * Read-only functions for LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControlRO_1 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_1
};


/*
 * aLPASSSourceMap_2
 *
 * LPASS HW source mapping.  Keeping XO for source 0 for now.  Needs pre-sil verification.
 *
 */
static HAL_clk_SourceMapType aLPASSSourceMap_2[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_SLEEPCLK,           1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GROUND,             5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mLPASSClockDomainControl_2
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControl_2 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_2
};


/*
 * HAL_clk_mLPASSClockDomainControlRO_2
 *
 * Read-only functions for LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControlRO_2 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_2
};


/*
 * aLPASSSourceMap_3
 *
 * LPASS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aLPASSSourceMap_3[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_LPAPLL1,            1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GROUND,             5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mLPASSClockDomainControl_3
 *
 * Functions for controlling LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControl_3 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_3
};


/*
 * HAL_clk_mLPASSClockDomainControlRO_3
 *
 * Read-only functions for LPASS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mLPASSClockDomainControlRO_3 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aLPASSSourceMap_3
};


/*
 * HAL_clk_aLPASSClockDomainDesc
 *
 * List of LPASS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aLPASSClockDomainDesc [] =
{
  &HAL_clk_mLPASSQ6COREIMAGEClkDomain,
  &HAL_clk_mLPASSAONClkDomain,
  &HAL_clk_mLPASSATIMEClkDomain,
  &HAL_clk_mLPASSAUDSLIMBUSClkDomain,
  &HAL_clk_mLPASSCCLPASSQ6SMMUCFGCNOCCLKClkDomain,
  &HAL_clk_mLPASSCCLPASSQ6SMMUCLIENTCLKClkDomain,
  &HAL_clk_mLPASSCCLPASSSNOCSWAYCLKClkDomain,
  &HAL_clk_mLPASSCOREClkDomain,
  &HAL_clk_mLPASSEXTMCLK0ClkDomain,
  &HAL_clk_mLPASSEXTMCLK1ClkDomain,
  &HAL_clk_mLPASSEXTMCLK2ClkDomain,
  &HAL_clk_mLPASSICAMSSDSPSTREAMING0CLKClkDomain,
  &HAL_clk_mLPASSICAMSSDSPSTREAMING1CLKClkDomain,
  &HAL_clk_mLPASSLPAIFPCMOEClkDomain,
  &HAL_clk_mLPASSLPAIFPRIClkDomain,
  &HAL_clk_mLPASSLPAIFQUADClkDomain,
  &HAL_clk_mLPASSLPAIFSECClkDomain,
  &HAL_clk_mLPASSLPAIFSPKRClkDomain,
  &HAL_clk_mLPASSLPAIFTERClkDomain,
  &HAL_clk_mLPASSPRIMI2SCLKINClkDomain,
  &HAL_clk_mLPASSQCASLIMBUSClkDomain,
  &HAL_clk_mLPASSQOSFIXEDLATCOUNTERClkDomain,
  &HAL_clk_mLPASSQUAMI2SCLKINClkDomain,
  &HAL_clk_mLPASSRESAMPLERClkDomain,
  &HAL_clk_mLPASSSECMI2SCLKINClkDomain,
  &HAL_clk_mLPASSSLEEPClkDomain,
  &HAL_clk_mLPASSSPKRI2SCLKINClkDomain,
  &HAL_clk_mLPASSSTANDALONEBCRClkDomain,
  &HAL_clk_mLPASSTERMI2SCLKINClkDomain,
  &HAL_clk_mLPASSXOClkDomain,
  NULL
};


/*
 * HAL_clk_aLPASSPowerDomainDesc
 *
 * List of LPASS power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aLPASSPowerDomainDesc [] =
{
  &HAL_clk_mLPASSAUDIOCOREPowerDomain,
  &HAL_clk_mLPASSQ6SMMUPowerDomain,
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

void HAL_clk_BusConfig
(
  HAL_clk_ClockDescType  *pmClockDesc,
  HAL_clk_ClockConfigType eConfig
)
{
  uint32 nAddr = 0;
  uint32 nValue = 0;

  if(NULL != pmClockDesc)
  {
    nAddr = pmClockDesc->mRegisters.nBranchAddr;

    if(nAddr != 0)
    {
      nValue = inpdw(nAddr);

      switch(eConfig)
      {
        case HAL_CLK_CONFIG_LPASS_CORE_MEM_ON:
          nValue |= HAL_CLK_MEM_CORE_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_PERIPH_MEM_ON:
          nValue |= HAL_CLK_MEM_PERIPH_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_CORE_MEM_OFF:
          nValue &= ~HAL_CLK_MEM_CORE_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_PERIPH_MEM_OFF:
          nValue &= ~HAL_CLK_MEM_PERIPH_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_HW_CTL_ON:
          nValue |= HAL_CLK_HW_CTL_ON_BMSK;
          outpdw(nAddr, nValue);
          break;

        case HAL_CLK_CONFIG_LPASS_HW_CTL_OFF:
          nValue &= ~HAL_CLK_HW_CTL_ON_BMSK;
          outpdw(nAddr, nValue);
          break;
 
        default:
          break;
      }
    }
  }

} /* HAL_clk_BusConfig */


void HAL_clk_AudioClksInvert
(
  HAL_clk_ClockDescType  *pmClockDesc,
  boolean                 bInvert
)
{
  if (pmClockDesc->mRegisters.nBranchAddr != 0)
  {
    /*
     * Check if inversion is for primary ibit/ebit.
     */
    if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV, INV_EXT_CLK, (uint32)bInvert);
    }
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV, INV_INT_CLK, (uint32)bInvert);
    }

    /*
     * Check if inversion is for secondary ibit/ebit.
     */
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV, INV_EXT_CLK, (uint32)bInvert);
    }
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV, INV_INT_CLK, (uint32)bInvert);
    }

    /*
     * Check if inversion is for ternary ibit/ebit.
     */
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV, INV_EXT_CLK, (uint32)bInvert);
    }
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV, INV_INT_CLK, (uint32)bInvert);
    }

    /*
     * Check if inversion is for quaternary ibit/ebit.
     */
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV, INV_EXT_CLK, (uint32)bInvert);
    }
    else if(pmClockDesc->mRegisters.nBranchAddr == 
        (HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR) + LPASS_BASE))
    {
      HWIO_OUTF(LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV, INV_INT_CLK, (uint32)bInvert);
    }
  }
}


/* ===========================================================================
**  HAL_clk_AudioCorePowerDomainEnable
**
** ======================================================================== */

void HAL_clk_AudioCorePowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr,nVal;
  nAddr = pmPowerDomainDesc->nGDSCRAddr;

  /*
   * Sanity check
   */
  if(nAddr != 0)
  {
    nVal  = inpdw(nAddr);
   
    /*
     * Clear the SW PD collapse bit
     */
    nVal &= ~HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);

    /*
     * Busywait for some time to allow propagation of the signal.
     * HW requirement is 48 XO clock cycles.  We wait a bit longer
     * here to ensure state is ready.
     */
    HAL_clk_BusyWait(10);

    /*
     * Wait for PD ON
     */
    if(HWIO_INF(LPASS_AUDIO_CORE_GDS_HW_CTRL, SW_OVERRIDE) == 0)
    {
      while(!(HWIO_INF(LPASS_AUDIO_CORE_GDS_HW_CTRL, POWER_ON_STATUS)));
    }
    else
    {
      while(!(inpdw(nAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));
    }
  }

} /* HAL_clk_AudioCorePowerDomainEnable */


/* ===========================================================================
**  HAL_clk_AudioCorePowerDomainDisable
**
** ======================================================================== */

void HAL_clk_AudioCorePowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr = pmPowerDomainDesc->nGDSCRAddr;
  uint32 nVal;

  if(nAddr != 0)
  {
    nVal = inpdw(nAddr);

    /*
     * Set the SW PD collapse bit
     */
    nVal |= HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);
  }

} /* HAL_clk_AudioCorePowerDomainDisable */


/* ===========================================================================
**  HAL_clk_Q6SMMUCorePowerDomainEnable
**
** ======================================================================== */

void HAL_clk_Q6SMMUCorePowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr,nVal;
  nAddr = pmPowerDomainDesc->nGDSCRAddr;

  /*
   * Sanity check
   */
  if(nAddr != 0)
  {
    nVal  = inpdw(nAddr);
   
    /*
     * Clear the SW PD collapse bit
     */
    nVal &= ~HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);

    /*
     * Busywait for some time to allow propagation of the signal.
     * HW requirement is 48 XO clock cycles.  We wait a bit longer
     * here to ensure state is ready.
     */
    HAL_clk_BusyWait(10);

    /*
     * Wait for PD ON
     */
    if(HWIO_INF(LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL, SW_OVERRIDE) == 0)
    {
      while(!(HWIO_INF(LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL, POWER_ON_STATUS)));
    }
    else
    {
      while(!(inpdw(nAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));
    }
  }

} /* HAL_clk_Q6SMMUCorePowerDomainEnable */


/* ===========================================================================
**  HAL_clk_Q6SMMUCorePowerDomainDisable
**
** ======================================================================== */

void HAL_clk_Q6SMMUCorePowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uint32 nAddr = pmPowerDomainDesc->nGDSCRAddr;
  uint32 nVal;

  if(nAddr != 0)
  {
    nVal = inpdw(nAddr);

    /*
     * Set the SW PD collapse bit
     */
    nVal |= HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
    outpdw(nAddr, nVal);
  }

} /* HAL_clk_Q6SMMUCorePowerDomainDisable */


/* ===========================================================================
**  HAL_clk_PlatformInitLPASSMain
**
** ======================================================================== */

void HAL_clk_PlatformInitLPASSMain (void)
{
  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aLPASSClockDomainDesc, LPASS_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aLPASSPowerDomainDesc, LPASS_BASE);

  /*
   * Program all the PSCBC's SLEEP field to 0x1 in order to meet the minimum 
   * requirements for PERIPH_ON deassertion after clock disable and to meet the
   * requirements to deassert before the core goes into power collapse.
   */
  HWIO_OUTF(LPASS_AUDIO_CORE_LPM_CORE_CBCR, SLEEP, 0x1);
  HWIO_OUTF(LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR, SLEEP, 0x1);
  HWIO_OUTF(LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR, SLEEP, 0x1);
  HWIO_OUTF(LPASS_AUDIO_CORE_RESAMPLER_CBCR, SLEEP, 0x1);

  /*
   * Program the GDSCR's CLK_DIS_WAIT field to 0x5 so that it will have enough time 
   * for all the PERIPH_ON to deassert before collapsing the core.
   */
  HWIO_OUTF(LPASS_AUDIO_CORE_GDSCR, CLK_DIS_WAIT, 0x5);
  HWIO_OUTF(LPASS_Q6_SMMU_GDSCR, CLK_DIS_WAIT, 0x5);

} /* END HAL_clk_PlatformInitLPASSMain */

