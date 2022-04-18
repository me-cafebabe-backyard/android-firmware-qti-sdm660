/*
===========================================================================
*/
/**
  @file ClockVoltage.c 
  
  Digital voltage management interface implementation for the clock
  device driver.
*/
/*  
  ====================================================================

  Copyright (c) 2010-2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header $
  $DateTime $
  $Author $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  09/29/16   bc      Add selectable VDDA_EBI rail
  04/18/14   vph     Add support for VDDA_EBI rail
  07/31/11   vph     Add support for GFX rail
  10/27/11   vph     Initial version
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include "swevent.h"
#include "railway.h"
#include "CoreVerify.h"

/*=========================================================================
      Constants and Macros 
==========================================================================*/

#define CX_RAILWAY   "vddcx"
#define GFX_RAILWAY  "vddgfx"

/*=========================================================================
      Data
==========================================================================*/

/*
 * Define local state variable to track vdd_dig voltage suspension
 */
static ClockVoltReqSuspStateType  eVoltageRequestSuspendState = CLOCK_VOLT_REQ_OPEN;
static int32                      nEBIRailID;
static railway_voter_t            sEBIVoter   = NULL;
static ClockVRegLevelType         eEBILevel   = CLOCK_VREG_LEVEL_OFF; 

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_VoteRailway
**    This function is used for voting the railway.  Depending on the 
** bSetTransition flag, it will call railway transition or not.
** =========================================================================*/
static void Clock_VoteRailway
( 
  ClockDrvCtxt        *pDrvCtxt,
  ClockVRegConfigType *pVReg,
  railway_corner      eMinLevel,
  boolean             bSetTransition
)
{
  if ( pVReg == &pDrvCtxt->CX_VRegConfig )
  {
    SWEVENT(CLOCK_EVENT_CX, eMinLevel);
  }
  else
  {
    SWEVENT(CLOCK_EVENT_GFX, eMinLevel);
  }

  // Now setup the vote.
  railway_corner_vote(pVReg->sVoter, eMinLevel);

  // Check if need to transition the rail yet, since CPR may not be ready yet
  if ( bSetTransition )
  {
    railway_transition_rail(pVReg->nRailID);
  }

  pVReg->eRailVoteLevel = (ClockVRegLevelType)eMinLevel;
}

/* =========================================================================
**  Function : Clock_VoltageRequest
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_VoltageRequest
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockVRegLevelType  *peCurrentLevel,
  ClockVRegLevelType  eNewLevel,
  boolean             bGFXVoltage
)
{
  ClockVRegLevelType  eMinLevel;
  ClockVRegConfigType *pVReg;
  ClockVRegLevelType  eRailwayVoteLevel;
  boolean             bTransitionRails;

  /* For non-gfx rail (CX), the minimun clock voltage is LOW */
  if ( !bGFXVoltage )
  {
    if ( *peCurrentLevel < CLOCK_VREG_LEVEL_LOW_MINUS )
      *peCurrentLevel = CLOCK_VREG_LEVEL_LOW_MINUS;

    if ( eNewLevel < CLOCK_VREG_LEVEL_LOW_MINUS )
      eNewLevel = CLOCK_VREG_LEVEL_LOW_MINUS;
  }

  /*-----------------------------------------------------------------------*/
  /* Find new minimum level.                                               */
  /*-----------------------------------------------------------------------*/

  if (*peCurrentLevel == eNewLevel)
  {
    return DAL_SUCCESS;
  }

  if ( (*peCurrentLevel >= CLOCK_VREG_NUM_LEVELS) || (eNewLevel >= CLOCK_VREG_NUM_LEVELS) )
  {
    return DAL_ERROR;
  }

  if ( bGFXVoltage == FALSE )           // CX Voltage
  {
    pVReg = &pDrvCtxt->CX_VRegConfig;
  }
  else
  {
    pVReg = &pDrvCtxt->GFX_VRegConfig;
  }

  /*------------------------------------------------------------------------------*/
  /* All domains default to LOW_MINUS at init, but the ClientCount for            */
  /* LOW_MINUS will not reflect this.  So we cannot track clients for the         */
  /* LOW_MINUS voltage level, but this is ok since it is the "do not care" level. */
  /*------------------------------------------------------------------------------*/

  if (*peCurrentLevel != CLOCK_VREG_LEVEL_LOW_MINUS &&
      pVReg->nClientCount[*peCurrentLevel] > 0)
  {
    pVReg->nClientCount[*peCurrentLevel]--;
  }

  if (eNewLevel != CLOCK_VREG_LEVEL_LOW_MINUS)
  {
    pVReg->nClientCount[eNewLevel]++;
  }

  *peCurrentLevel = eNewLevel;

  /*-----------------------------------------------------------------------*/
  /* Check if new min has changed.                                         */
  /*-----------------------------------------------------------------------*/

  if (eNewLevel > pVReg->eMinLevel)
  {
    eMinLevel = eNewLevel;
  }
  else
  {
    for (eMinLevel = pVReg->eMinLevel; 
         eMinLevel > eNewLevel; eMinLevel--)
    {
      if (pVReg->nClientCount[eMinLevel] > 0)
      {
        break;
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update request if minimum level is different.                         */
  /*-----------------------------------------------------------------------*/

  if (eMinLevel != pVReg->eMinLevel)
  {
    /*
     * Vote for new voltage. If voltage changes are suspended, then this new
     * voltage is known to be within the current ceiling and the railway
     * transition process can be (and is) skipped. Otherwise the railway
     * transition is done now.
     */
    if ( eVoltageRequestSuspendState == CLOCK_VOLT_REQ_OPEN )
    {
      /* Forward the request to railway and transition rails. */
      bTransitionRails = TRUE;
      eRailwayVoteLevel = eMinLevel;
    }
    else
    {
      /* Clock voltage requests are suspended--don't transition rails. */
      bTransitionRails = FALSE;

      if ( eMinLevel > pVReg->eSuspRailVoteLevel )
      {
        /* Record our new highest "suspend mode" voltage request. */
        pVReg->eSuspRailVoteLevel = eMinLevel;
        eRailwayVoteLevel = eMinLevel;
      }
      else
      {
        eRailwayVoteLevel = pVReg->eSuspRailVoteLevel;
      }
    }
    Clock_VoteRailway( pDrvCtxt, pVReg, (railway_corner)eRailwayVoteLevel, bTransitionRails );
    pVReg->eMinLevel = eMinLevel;
  }

  /*-----------------------------------------------------------------------*/
  /* Success.                                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_VoltageRequest */


/* =========================================================================
**  Function : Clock_VoltageRequestSuspend
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

void Clock_VoltageRequestSuspend
(
  ClockDrvCtxt                *pDrvCtxt,
  ClockVoltReqSuspStateType   eNewVoltReqSuspendState,
  boolean                     bUpdateRailway
)
{
  static boolean bInit = TRUE;
  boolean bSetTransition = TRUE;

  /* Record current clock driver railway requests upon request suspension. */
  if ( (eVoltageRequestSuspendState == CLOCK_VOLT_REQ_OPEN) &&
        (eNewVoltReqSuspendState != CLOCK_VOLT_REQ_OPEN) )
  {
    pDrvCtxt->CX_VRegConfig.eSuspRailVoteLevel = pDrvCtxt->CX_VRegConfig.eRailVoteLevel;

    if ( pDrvCtxt->GFX_VRegConfig.nRailID != RAIL_NOT_SUPPORTED_BY_RAILWAY )
    {
      pDrvCtxt->GFX_VRegConfig.eSuspRailVoteLevel = pDrvCtxt->GFX_VRegConfig.eRailVoteLevel;
    }
  }

  eVoltageRequestSuspendState = eNewVoltReqSuspendState;

  /*
   * Prevent railway transition on first voltage request resume,
   * since CPR is not initialized yet.
   */
  if ( bInit && (eNewVoltReqSuspendState == CLOCK_VOLT_REQ_OPEN) )
  {
    bSetTransition = FALSE;
    bInit = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Make a voltage request when resuming from suspension.                 */
  /*-----------------------------------------------------------------------*/

  if ( bUpdateRailway )
  {
    Clock_VoteRailway(  pDrvCtxt, 
                        &pDrvCtxt->CX_VRegConfig, 
                        (railway_corner)pDrvCtxt->CX_VRegConfig.eMinLevel,
                        bSetTransition );

    if ( pDrvCtxt->GFX_VRegConfig.nRailID != RAIL_NOT_SUPPORTED_BY_RAILWAY )
    {
      Clock_VoteRailway(  pDrvCtxt, 
                          &pDrvCtxt->GFX_VRegConfig, 
                          (railway_corner)pDrvCtxt->GFX_VRegConfig.eMinLevel,
                          bSetTransition );
    }
  }

} /* END Clock_VoltageRequestSuspend */


/* =========================================================================
**  Function : Clock_InitVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

__attribute__((section("clk_cram_reclaim_pool")))
DALResult Clock_InitVoltage
(
  ClockDrvCtxt *pDrvCtxt
)
{

  /* Default level is highest level */
  pDrvCtxt->CX_VRegConfig.eRailVoteLevel = CLOCK_VREG_LEVEL_HIGH_NO_CPR;

  /* Initialize CX Rail ID */
  pDrvCtxt->CX_VRegConfig.nRailID = rail_id(CX_RAILWAY);
  CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY != pDrvCtxt->CX_VRegConfig.nRailID);
  
  /* Now create a voter for Clock Driver to vote on */
  pDrvCtxt->CX_VRegConfig.sVoter = railway_create_voter(pDrvCtxt->CX_VRegConfig.nRailID, 
                                                        TRUE, 
                                                        RAILWAY_CLOCK_DRIVER_VOTER_ID);

  /* Common driver.  Default with no GFX rail. */
  pDrvCtxt->GFX_VRegConfig.nRailID = RAIL_NOT_SUPPORTED_BY_RAILWAY;

  return DAL_SUCCESS;

} /* END Clock_InitVoltage */


/* =========================================================================
**  Function : Clock_InitGFXVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

__attribute__((section("clk_cram_reclaim_pool")))
DALResult Clock_InitGFXVoltage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  /* Default level is highest level */
  pDrvCtxt->GFX_VRegConfig.eRailVoteLevel = CLOCK_VREG_LEVEL_HIGH_NO_CPR;

  /* Initialize GFX Rail ID */
  pDrvCtxt->GFX_VRegConfig.nRailID = rail_id(GFX_RAILWAY);
  CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY != pDrvCtxt->GFX_VRegConfig.nRailID);

  /* Now create a voter for Clock Driver to vote on */
  pDrvCtxt->GFX_VRegConfig.sVoter = railway_create_voter(pDrvCtxt->GFX_VRegConfig.nRailID, 
                                                         TRUE, 
                                                         RAILWAY_CLOCK_DRIVER_VOTER_ID);
  
  return DAL_SUCCESS;

}


/* =========================================================================
**  Function : Clock_InitEBIVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

__attribute__((section("clk_cram_reclaim_pool")))
DALResult Clock_InitEBIVoltage
(
  ClockVRegLevelType eInitLevel,
  char *VddaEBIRail
)
{
  /* Initialize VDDA_EBI Rail ID */
  nEBIRailID = rail_id(VddaEBIRail);
  CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY != nEBIRailID);

  /* Now create a voter for Clock Driver to vote on */
  sEBIVoter = railway_create_voter( nEBIRailID, 
                                    TRUE, 
                                    RAILWAY_CLOCK_DRIVER_VOTER_ID);
    
  /* Set default VDDA_EBI active */
  eEBILevel = eInitLevel;
  railway_corner_vote( sEBIVoter, (railway_corner)eEBILevel );

  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : Clock_SetVDDAVoltage()
** =========================================================================*/
/**
  This function is used for setting VDDA_EBI voltage

  @param 
      eNewLevel - New voltage level

  @return
      None
*/
void Clock_SetVDDAVoltage
( 
  ClockVRegLevelType eNewLevel 
)
{
  if ( eNewLevel == eEBILevel )
    return;

  eEBILevel = eNewLevel;

  railway_corner_vote(sEBIVoter, (railway_corner)eEBILevel);
  railway_transition_rail( nEBIRailID );
}
