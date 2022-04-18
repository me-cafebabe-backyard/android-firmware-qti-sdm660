/*
==============================================================================

FILE:         HALclkIPA.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   IPA clocks.

   List of clock domains:
     - HAL_clk_mGCCIPA2XClkDomain


   List of power domains:
     - HAL_clk_mGCCIPAPowerDomain



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkIPA.c#1 $

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
#include "assert.h"

/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_IPAEnable
(
  HAL_clk_ClockDescType *pmClockDesc
);

void HAL_clk_IPADisable
(
  HAL_clk_ClockDescType *pmClockDesc
);

#if 0
void HAL_clk_IPAPowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc, 
  boolean                     bAsync
);

void HAL_clk_IPAPowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
);
#endif
/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern void HAL_clk_GenericPowerDomainEnable( HAL_clk_PowerDomainDescType *pmPowerDomainDesc, boolean bAsync );
extern void HAL_clk_GenericPowerDomainDisable( HAL_clk_PowerDomainDescType *pmPowerDomainDesc );
extern boolean HAL_clk_GenericPowerDomainIsEnabled( HAL_clk_PowerDomainDescType *pmPowerDomainDesc );


/* ============================================================================
**    Data
** ==========================================================================*/

#if 0
#define OFFSET_ADDR         0x60000000
   
#define NUM_WAITS           25
#define WAIT_TIME           20
#define DELAY_TIME          100
#define IPA_SAVE_SUCCESS    0xFADEFADE
#define IPA_SAVE_FAIL       0x0BADFADE
#define IPA_RESTORE_SUCCESS 0xCAFECAFE
#define IPA_RESTORE_FAIL    0x0BADCAFE

static uint32 nIPASave = 0;
static uint32 nIPARestore = 0;
static uint32 nIPASaveTimes = 0;
static uint32 nIPARestoreTimes = 0;

typedef enum
{
  IPA_SAVE_ENTER = 0,
  IPA_SAVE_COMPLETE,
  IPA_RESTORE_ENTER,
  IPA_RESTORE_COMPLETE,
  IPA_RESTORE_PW_ENABLED,
  IPA_RESTORE_IN_LOOP,
  IPA_RESTORE_OUT_LOOP,
  IPA_RESTORE_BEFORE_WAIT
}ipa_pc_state_e;

ipa_pc_state_e pc_state;
#endif
/*
 * HAL_clk_mIPAClockControl
 *
 * Functions for controlling IPA clock functions.
 */
HAL_clk_ClockControlType HAL_clk_mIPAClockControl =
{
  /* .Enable           = */ HAL_clk_IPAEnable,
  /* .Disable          = */ HAL_clk_IPADisable,
  /* .IsEnabled        = */ HAL_clk_GenericIsEnabled,
  /* .IsOn             = */ HAL_clk_GenericIsOn,
  /* .Reset            = */ HAL_clk_GenericReset,
  /* .Config           = */ NULL,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ HAL_clk_GenericConfigDivider,
  /* .DetectDivider    = */ HAL_clk_GenericDetectDivider,
  /* .ConfigFootswitch = */ HAL_clk_GenericConfigFootswitch,
};

#if 0
/*
 * HAL_clk_mIPAPowerDomainControl
 *
 * Functions for controlling IPA power domain functions.
 */
HAL_clk_PowerDomainControlType HAL_clk_mIPAPowerDomainControl =
{
   /* .Enable     = */ HAL_clk_IPAPowerDomainEnable,
   /* .Disable    = */ HAL_clk_IPAPowerDomainDisable,
   /* .IsEnabled  = */ HAL_clk_GenericPowerDomainIsEnabled
};
#endif

/*                           
 *  HAL_clk_mIPA2XClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mIPA2XClkDomainClks[] =
{
#if 0
  {
    /* .szClockName      = */ "gcc_aggre2_noc_ipa_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_AGGRE2_NOC_IPA_CBCR), HWIO_OFFS(GCC_AGGRE2_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_AGGRE2_NOC_IPA_CLK
  },
  {
    /* .szClockName      = */ "gcc_ipa_2x_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IPA_2X_CBCR), HWIO_OFFS(GCC_IPA_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IPA_2X_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_ipa_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_IPA_CBCR), HWIO_OFFS(GCC_IPA_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mIPAClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_IPA_CLK
  },
};


/*
 * HAL_clk_mGCCIPA2XClkDomain
 *
 * IPA2X clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCIPA2XClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_IPA_2X_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mIPA2XClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mIPA2XClkDomainClks)/sizeof(HAL_clk_mIPA2XClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


#if 0
/*
 * HAL_clk_mGCCIPAPowerDomain
 *
 * IPA power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCIPAPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_IPA",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_IPA_GDSCR),
  /* .pmControl               = */ &HAL_clk_mIPAPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};
#endif

#define CLK_ON_WAIT_USEC    150

uint32 gIPAwaitTimeUsec;
void HAL_ClkIsOn(uint32 nAddr)
{
  uint32 nVal;

  gIPAwaitTimeUsec = 0;
  nVal  = inpdw(nAddr);
  while((nVal & HAL_CLK_BRANCH_CTRL_REG_CLK_OFF_FMSK) && (gIPAwaitTimeUsec <= CLK_ON_WAIT_USEC) )
  {
    HAL_clk_BusyWait(1);
    nVal  = inpdw(nAddr);
    gIPAwaitTimeUsec++;
  }

}

/* ===========================================================================
**  HAL_clk_IPAEnable
**
** ======================================================================== */
void HAL_clk_IPAEnable
(
  HAL_clk_ClockDescType *pmClockDesc
)
{
/*   There is no GDSCR in Starlord for IPA, hence we need to wait till all the clocks are ON.
   */
  HWIO_OUTF( GCC_AGGRE2_NOC_IPA_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF( GCC_IPA_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF( GCC_IPA_2X_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF( GCC_IPA_SLEEP_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF( GCC_IPA_AHB_CBCR, CLK_ENABLE, 1);

  HAL_ClkIsOn(HWIO_ADDR(GCC_AGGRE2_NOC_IPA_CBCR));
  HAL_ClkIsOn(HWIO_ADDR(GCC_IPA_CBCR));
  HAL_ClkIsOn(HWIO_ADDR(GCC_IPA_2X_CBCR));
  HAL_ClkIsOn(HWIO_ADDR(GCC_IPA_AHB_CBCR));
  HAL_ClkIsOn(HWIO_ADDR(GCC_IPA_SLEEP_CBCR));
  
//  HAL_clk_BusyWait( 10 );

} /* HAL_clk_IPAEnable */


/* ===========================================================================
**  HAL_clk_IPADisable
**
** ======================================================================== */
void HAL_clk_IPADisable
(
  HAL_clk_ClockDescType *pmClockDesc
)
{
  /* Disable IPA clocks
   */
  HWIO_OUTF( GCC_AGGRE2_NOC_IPA_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF( GCC_IPA_2X_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF( GCC_IPA_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF( GCC_IPA_SLEEP_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF( GCC_IPA_AHB_CBCR, CLK_ENABLE, 0);

} /* HAL_clk_IPADisable */


#if 0
/* ===========================================================================
**  HAL_clk_IPAPowerDomainEnable
**
** ======================================================================== */

void HAL_clk_IPAPowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc, 
  boolean                     bAsync
)
{
  nIPARestoreTimes = NUM_WAITS;
  pc_state = IPA_RESTORE_ENTER;

  HAL_clk_GenericPowerDomainEnable( pmPowerDomainDesc, bAsync );
  pc_state = IPA_RESTORE_PW_ENABLED;
    
  HAL_clk_BusyWait( DELAY_TIME );

  while ( (HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) != IPA_RESTORE_SUCCESS) && nIPARestoreTimes--  )
  {
    pc_state = IPA_RESTORE_BEFORE_WAIT;
    HAL_clk_BusyWait( WAIT_TIME );
    pc_state = IPA_RESTORE_IN_LOOP;
  }
  pc_state = IPA_RESTORE_OUT_LOOP;
  
  // Assert if IPA restored is not success
  assert( HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) == IPA_RESTORE_SUCCESS );

  // Keep track number of IPA Restore for debug purpose
  nIPARestore++;
  pc_state = IPA_RESTORE_COMPLETE;
} /* END HAL_clk_IPAPowerDomainEnable */

/* ===========================================================================
**  HAL_clk_IPAPowerDomainDisable
**
** ======================================================================== */

void HAL_clk_IPAPowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  nIPASaveTimes = NUM_WAITS;
  pc_state = IPA_SAVE_ENTER;

  HWIO_OUT( TCSR_TCSR_IPA_WARMBOOT_EN, 1);
  
  // Invalidate mailbox 17 before polling
  HWIO_OUTI2( IPA_0_IPA_UC_MAILBOX_m_n, 0, 17, 0 );

  // Write to MBOX for trigger interrupt to uC
  HWIO_OUTI2( IPA_0_IPA_UC_MAILBOX_m_n, 0, 16, HWIO_ADDRI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) - OFFSET_ADDR );
  
  while ( (HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) != IPA_SAVE_SUCCESS) && nIPASaveTimes--  )
  {
    HAL_clk_BusyWait( WAIT_TIME );
  }
  
  // Assert if IPA save is not success
  assert( HWIO_INI2(IPA_0_IPA_UC_MAILBOX_m_n, 0, 17) == IPA_SAVE_SUCCESS );

  /* Retent all registers before power down */
  HWIO_OUTF( GCC_IPA_GDSCR, RETAIN_FF_ENABLE, 1 );
 
  HAL_clk_GenericPowerDomainDisable (pmPowerDomainDesc);

  // Keep track number of IPA Save for debug purpose
  nIPASave++;
  pc_state = IPA_SAVE_COMPLETE;
} /* END HAL_clk_IPAPowerDomainDisable */
#endif
