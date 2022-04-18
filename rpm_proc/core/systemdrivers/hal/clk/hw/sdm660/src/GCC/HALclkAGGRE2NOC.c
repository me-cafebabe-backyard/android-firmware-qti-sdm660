/*
==============================================================================

FILE:         HALclkAGGRE2NOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AGGRE2NOC clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mGCCAGGRE2NOCPowerDomain



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkAGGRE2NOC.c#3 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
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


/* ============================================================================
**    Externs
** ==========================================================================*/



/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_mGCCAGGRE2NOCPowerDomain
 *
 * AGGRE2_NOC power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCAGGRE2NOCPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_AGGRE2_NOC",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_AGGRE2_NOC_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

typedef enum
{
    DEBUG_AGGR_IMEM_CLK_ON=0,
    DEBUG_AGGR_AGGR_CLK_ON,
    DEBUG_AGGR_IMEM_CLK_OFF,
    DEBUG_AGGR_AGGR_CLK_OFF,
    DEBUG_AGGR_QDSS_AT_CLK_OFF,
    DEBUG_AGGR_AGGR_GDSC_OFF,
    DEBUG_AGGR_INVALID = 0x7FFFFFF
}HAL_AGGR_DEBUG_MARKER;

volatile HAL_AGGR_DEBUG_MARKER hal_aggr_debug_marker = DEBUG_AGGR_INVALID;

void HAL_clk_AGGRE2NOCRestore 
(
  boolean bRestore
)
{
  if(bRestore)
  {
    /*Polling for the clock on after GDSCR power on. This is to save time.*/
    HWIO_OUTF(GCC_SMMU_AGGRE2_AXI_SRC_CBCR, CLK_ENABLE, 1);
    HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE,IMEM_AXI_CLK_ENA,1);
    HWIO_OUTF(GCC_QDSS_CENTER_AT_CBCR, CLK_ENABLE, 1 );
  }

  /* Toggle Aggre 2 NOCs Domain on/off */
  HWIO_OUTF( GCC_AGGRE2_NOC_GDSCR, SW_COLLAPSE, !bRestore );

  if( bRestore )
  {
    while( HWIO_INF( GCC_AGGRE2_NOC_GDSCR, PWR_ON ) == 0 )
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_AGGR_GDSC_OFF);
    }
  }

  if(!bRestore)
  {
    /* PSCBCs renabled before wakeup. */
    HWIO_OUTF( GCC_QDSS_CENTER_AT_CBCR, CLK_ENABLE, 0 );
    HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE,IMEM_AXI_CLK_ENA,0);
    HWIO_OUTF( GCC_SMMU_AGGRE2_AXI_SRC_CBCR, CLK_ENABLE, 0);
    while( HWIO_INF( GCC_IMEM_AXI_CBCR, CLK_OFF ) == 0 )
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_IMEM_CLK_ON);
    }
    while(HWIO_INF(GCC_SMMU_AGGRE2_AXI_SRC_CBCR,CLK_OFF) == 0)
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_AGGR_CLK_ON);
    }
  }
  else
  {
    /*Poll for the clock on before wake up*/
    while(HWIO_INF(GCC_SMMU_AGGRE2_AXI_SRC_CBCR,CLK_OFF) == 1)
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_AGGR_CLK_OFF);
    }
    while( HWIO_INF( GCC_IMEM_AXI_CBCR, CLK_OFF ) == 1 )
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_IMEM_CLK_OFF);
    }
    while(HWIO_INF(GCC_QDSS_CENTER_AT_CBCR,CLK_OFF) == 1)
    {
      debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_QDSS_AT_CLK_OFF);
    }
  }
  debug_marker(hal_aggr_debug_marker, DEBUG_AGGR_INVALID);
}

