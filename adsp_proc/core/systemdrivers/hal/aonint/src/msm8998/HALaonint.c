/*
===========================================================================

FILE:         HALaonint.c

DESCRIPTION:  
  This is the generic hardware abstraction layer implementation for the
  AON interrupt controller.

===========================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/aonint/src/msm8998/HALaonint.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
09/29/14   cpaulo  Added retention enter and exit APIs.
08/20/14   cpaulo  Created.

===========================================================================
             Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */


#include <HALhwio.h>
#include "HALaonintHWIO.h"
#include "HALaonintcsrHWIO.h"
#include "HALaonint.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */


/*
 * Identifier string for this HAL.
 */
#define HAL_AONINT_VERSION_STRING "HAL_AONINT_V1"

/*
 * 
 */
#define HAL_AONINT_REG_MASK 0x1F
#define HAL_AONINT_REG_BITS 5


/* -----------------------------------------------------------------------
**                           MACROS
** ----------------------------------------------------------------------- */

/*
 * Gets the bit position for the interrupt
 */
#define HAL_AONINT_IDX(index) ( index >> HAL_AONINT_REG_BITS )

/*
 * Gets the bit position for the interrupt
 */
#define HAL_AONINT_GET_BITPOS(idx) ( idx & HAL_AONINT_REG_MASK )

/*
 * Sets a register with the bitmask given
 */
#define HAL_AONINT_GET_N_SET_REG(reg,mask,val) \
          val = inpdw(reg); \
          val |= mask; \
          outpdw(reg, val)

/*
 * Gets a register
 */
#define HAL_AONINT_GET_REG(reg) \
          inpdw(reg)

/*
 * Sets a command register with the bitmask given
 */
#define HAL_AONINT_SET_REG(reg,mask) \
          outpdw(reg, mask)

/*
 * Clears a register at the given bitmask
 */
#define HAL_AONINT_CLR_REG(reg,mask,val) \
          val = inpdw(reg); \
          val &= ~mask; \
          outpdw(reg, val)


/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

static HAL_aonint_PlatformInfo gPlatform;

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* =========================================================================
**  Function : HAL_aonint_Init
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_Init ( void )
{
  /* Initialize platform specific registers */
  HAL_aonint_PlatformInitEarly(&gPlatform);

  /* Initialize Wakeup Interrupts to SSC AON */
  HWIO_OUT(SSC_SSC_WAKEUP_PRIMARY_IE, HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_WAKEUP_IE_BMSK);
  HWIO_OUT(SSC_SSC_WAKEUP_SECONDARY_IE, HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_WAKEUP_IE_BMSK);
}


/* =========================================================================
**  Function : HAL_aonint_Enable
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_Enable ( uint32 nAonIdx )
{
  uint32 nMask, nReg, nVal;

  nMask = 0x1 << HAL_AONINT_GET_BITPOS(nAonIdx);
  nReg = gPlatform.nEnableRegs[HAL_AONINT_IDX(nAonIdx)];

  /* Set */
  HAL_AONINT_GET_N_SET_REG(nReg,nMask,nVal);
}


/* =========================================================================
**  Function : HAL_aonint_Disable
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_Disable ( uint32 nAonIdx )
{
  uint32 nMask, nReg, nVal;

  nMask = 0x1 << HAL_AONINT_GET_BITPOS(nAonIdx);
  nReg  = gPlatform.nEnableRegs[HAL_AONINT_IDX(nAonIdx)];

  /* Clear */
  HAL_AONINT_CLR_REG(nReg,nMask,nVal);
}


/* =========================================================================
**  Function : HAL_aonint_Config
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_Config ( uint32 nAonIdx, HAL_aonint_TriggerType eTrigger )
{
  uint32 nMask, nRegPOL, nRegPOS, nRegNEG, nVal;

  nMask = 0x1 << HAL_AONINT_GET_BITPOS(nAonIdx);
  nRegPOL  = gPlatform.nPolarityRegs[HAL_AONINT_IDX(nAonIdx)];
  nRegPOS  = gPlatform.nPositiveEdgeRegs[HAL_AONINT_IDX(nAonIdx)];
  nRegNEG  = gPlatform.nNegativeEdgeRegs[HAL_AONINT_IDX(nAonIdx)];

  switch (eTrigger)
  {
    case HAL_AONINT_TRIGGER_HIGH:
      HAL_AONINT_GET_N_SET_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegNEG,nMask,nVal);
      break;
    case HAL_AONINT_TRIGGER_LOW:
      HAL_AONINT_CLR_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegNEG,nMask,nVal);
      break;
    case HAL_AONINT_TRIGGER_RISING:
      HAL_AONINT_GET_N_SET_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_GET_N_SET_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegNEG,nMask,nVal);
      break;
    case HAL_AONINT_TRIGGER_FALLING:
      HAL_AONINT_GET_N_SET_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_GET_N_SET_REG(nRegNEG,nMask,nVal);
      break;
    case HAL_AONINT_TRIGGER_DUAL_EDGE:
      HAL_AONINT_CLR_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_GET_N_SET_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_GET_N_SET_REG(nRegNEG,nMask,nVal);
      break;
    default:
      /* Default level High */
      HAL_AONINT_GET_N_SET_REG(nRegPOL,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegPOS,nMask,nVal);
      HAL_AONINT_CLR_REG(nRegNEG,nMask,nVal);
      break;
  }
}


/* =========================================================================
**  Function : HAL_aonint_Get_Config
** =========================================================================*/
/*
  See HALaonint.h
*/

HAL_aonint_TriggerType HAL_aonint_Get_Config ( uint32 nAonIdx )
{
  uint32 nMask, nRegPOL, nRegPOS, nRegNEG, nValPOL, nValPOS, nValNEG;

  nMask = 0x1 << HAL_AONINT_GET_BITPOS(nAonIdx);
  nRegPOL  = gPlatform.nPolarityRegs[HAL_AONINT_IDX(nAonIdx)];
  nRegPOS  = gPlatform.nPositiveEdgeRegs[HAL_AONINT_IDX(nAonIdx)];
  nRegNEG  = gPlatform.nNegativeEdgeRegs[HAL_AONINT_IDX(nAonIdx)];

  nValPOL = HAL_AONINT_GET_REG(nRegPOL);
  nValPOS = HAL_AONINT_GET_REG(nRegPOS);
  nValNEG = HAL_AONINT_GET_REG(nRegNEG);

  if ( !( nValPOL & nMask ) && !( nValPOS & nMask ) && !( nValNEG & nMask ) )
  {
    return HAL_AONINT_TRIGGER_LOW;
  }
  else if ( !( nValPOL & nMask ) && !( nValPOS & nMask ) && ( nValNEG & nMask ) )
  {
    return HAL_AONINT_TRIGGER_FALLING;
  }
  else if ( !( nValPOL & nMask ) && ( nValPOS & nMask ) && !( nValNEG & nMask ) )
  {
    return HAL_AONINT_TRIGGER_RISING;
  }
  else if ( !( nValPOL & nMask ) && ( nValPOS & nMask ) && ( nValNEG & nMask ) )
  {
    return HAL_AONINT_TRIGGER_DUAL_EDGE;
  }
  else if ( ( nValPOL & nMask ) && !( nValPOS & nMask ) && !( nValNEG & nMask ) )
  {
    return HAL_AONINT_TRIGGER_HIGH;
  }
  else
  {
    return HAL_AONINT_TRIGGER_DEFAULT;
  }
}


/* =========================================================================
**  Function : HAL_aonint_Clear
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_Clear ( uint32 nAonIdx )
{
  uint32 nMask, nReg;

  nMask = 0x1 << HAL_AONINT_GET_BITPOS(nAonIdx);
  nReg  = gPlatform.nClearRegs[HAL_AONINT_IDX(nAonIdx)];
  HAL_AONINT_SET_REG(nReg,nMask);
}


/* =========================================================================
**  Function : HAL_aonint_RetentionEnter
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_RetentionEnter ( void )
{
  HWIO_OUT(SSC_QDSP6SS_WAKEUP_CTL, 0x0);
  HWIO_OUTF(SSC_QDSP6SS_SPMCTL_EN_EXT, SHUTDOWN_REQ, 0x1);  
}


/* =========================================================================
**  Function : HAL_aonint_RetentionExit
** =========================================================================*/
/*
  See HALaonint.h
*/

void HAL_aonint_RetentionExit ( void )
{
  HWIO_OUTF(SSC_QDSP6SS_SPMCTL_EN_EXT, SHUTDOWN_REQ, 0x0);  
  HWIO_OUT(SSC_QDSP6SS_WAKEUP_CTL, 0x1);
}

