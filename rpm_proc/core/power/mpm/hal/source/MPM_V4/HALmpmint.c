/*
===========================================================================

FILE:         HALmpmint.c

DESCRIPTION:  
  This is the generic hardware abstraction layer implementation for the
  MPM interrupt controller.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/source/MPM_V4/HALmpmint.c#3 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright © 2008-2011 Qualcomm Technologies Incorporated.
                        All Rights Reserved.
                QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include <string.h>
#include <HALmpmint.h>
#include "CoreVerify.h"

#include "../common/HALmpmintInternal.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/*
 * Identifier string for this HAL.
 */
#define HAL_MPMINT_VERSION_STRING "HAL_MPMINT_V1"

#define MAKE_MASK(bit_pos) (1 << ((bit_pos) % 32))

#define POL_FROM_IDX(idx) (idx&4)
#define DET_B_FROM_IDX(idx) (idx&2)
#define DET_A_FROM_IDX(idx) (idx&1)

const HAL_mpmint_TriggerType mpmint_trigger_lookup[8] = {HAL_MPMINT_TRIGGER_LOW,       //pol = 0, det_b = 0, det_a = 0
                                                         HAL_MPMINT_TRIGGER_FALLING,   //pol = 0, det_b = 0, det_a = 1 
                                                         HAL_MPMINT_TRIGGER_RISING,    //pol = 0, det_b = 1, det_a = 0 
                                                         HAL_MPMINT_TRIGGER_DUAL,      //pol = 0, det_b = 1, det_a = 1 
                                                         HAL_MPMINT_TRIGGER_HIGH,      //pol = 1, det_b = 0, det_a = 0 
                                                         HAL_MPMINT_TRIGGER_RISING,    //pol = 1, det_b = 0, det_a = 1 
                                                         HAL_MPMINT_TRIGGER_FALLING,   //pol = 1, det_b = 1, det_a = 0 
                                                         HAL_MPMINT_TRIGGER_DUAL};     //pol = 1, det_b = 1, det_a = 1

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */
static uint32 inline get_en_reg(uint32 nMPM)
{
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);
  return registerLayout.nEnableReg[nMPM / 32];
}

static uint32 inline get_en_reg_pad(uint32 nMPM)
{
  CORE_VERIFY(nMPM < HAL_MPMINT_PHYS_INTS);
  return registerLayout.nEnableRegPad[nMPM / 32];
}

static uint32 inline get_status_reg(uint32 nMPM)
{
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);
  return registerLayout.nStatusReg[nMPM / 32];
}

static uint32 inline get_clear_reg(uint32 nMPM)
{
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);
  return registerLayout.nClearReg[nMPM / 32];
}

static uint32 inline get_pol_reg(uint32 nMPM)
{
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);
  return registerLayout.nPolarityReg[nMPM / 32];
}

static uint32 inline get_det_reg_low(uint32 nMPM)
{
  uint32 index = nMPM / 32;
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);

  // For the lower order bit:
  //     interrupts 0-31 are index 0 (detect1)
  //     interrupts 31-63 are index 1 (detect2)
  //     interrupts 64-95 are index 4 (detect5)
  if(index == 2)
  {
    index = 4;
  } 

  return registerLayout.nDetectReg[index];
}

static uint32 inline get_det_reg_high(uint32 nMPM)
{
  uint32 index = (nMPM / 32) + 3; //adding 3 for higher order bit indices
  CORE_VERIFY(nMPM < HAL_MPMINT_NUM);

  // For the higher order bit:
  //     interrupts 0-31 are index 2 (detect3)
  //     interrupts 31-63 are index 3 (detect4)
  //     interrupts 64-95 are index 6 (detect6)
  if(index == 3)
  {
    index = 2;
  } 
  else if(index == 4)
  {
    index = 3;
  }

  return registerLayout.nDetectReg[index];
}

/* ===========================================================================
**  HAL_mpmint_Init
**
** ======================================================================== */

__attribute__((section("mpm_cram_reclaim_pool")))
void HAL_mpmint_Init
(
  char **ppszVersion
)
{
  uint32 nMPM;

  /*
   * Populate MPM interrupt controller with initial guesses from BSP data.
   * Also, initialize the back-lookup table while we're at it.
   */
  for (nMPM = 0; nMPM < HAL_MPMINT_NUM; nMPM++)
  {
    HAL_mpmint_SetTrigger( nMPM, aInterruptTable[nMPM].eTrigger );
  }

  /*
   * Disable and clear all interrupts
   */
  HAL_mpmint_All_Disable();
  HAL_mpmint_All_Clear();

  /*
   * Fill in return value
   */
  if (ppszVersion != NULL)
  {
    *ppszVersion = (char*)HAL_MPMINT_VERSION_STRING;
  }

} /* END HAL_mpmint_Init */


/* ===========================================================================
**  HAL_mpmint_Reset
**
** ======================================================================== */

void HAL_mpmint_Reset (void)
{
  /* TODO */

} /* END HAL_mpmint_Reset */


/* ===========================================================================
**  HAL_mpmint_Save
**
** ======================================================================== */

void HAL_mpmint_Save (void)
{
  /* MPM hardware is always on. */
} /* END HAL_mpmint_Save */


/* ===========================================================================
**  HAL_mpmint_Restore
**
** ======================================================================== */

void HAL_mpmint_Restore (void)
{
  /* MPM hardware is always on. */
} /* END HAL_mpmint_Restore */


/* ===========================================================================
**  HAL_mpmint_Enable
**
** ======================================================================== */

void HAL_mpmint_Enable
(
  uint32 nMPM
)
{
  uint32 nPadPos, nPadMask, nRegPad;
  uint32 nBitPos, nMask, nReg, nVal;

  /* 
   * Enable the interrupt at the pad 
   */
  nPadPos  = aInterruptTable[nMPM].padBitPos;

  if ( HAL_MPMINT_INVALID_BIT_POS != nPadPos )
  {
    nRegPad  = get_en_reg_pad(nPadPos);
    nPadMask = MAKE_MASK(nPadPos);

    nVal = inpdw(nRegPad);
    nVal |= nPadMask;
    outpdw(nRegPad, nVal);
  }

  /* 
   * Clear the interrupt 
   */
  HAL_mpmint_Clear( nMPM );

  /* 
   * Enable the interrupt in the MPM register 
   */
  nBitPos = nMPM;
  nReg    = get_en_reg(nBitPos);
  nMask   = MAKE_MASK(nBitPos);

  nVal = inpdw(nReg);
  nVal |= nMask;
  outpdw(nReg, nVal);

} /* END HAL_mpmint_Enable */


/* ===========================================================================
**  HAL_mpmint_Disable
**
** ======================================================================== */

void HAL_mpmint_Disable
(
  uint32 nMPM
)
{
  uint32 nPadPos, nPadMask, nRegPad;
  uint32 nBitPos, nMask, nReg, nVal;

  /* 
   * Disable the interrupt at the pad 
   */
  nPadPos  = aInterruptTable[nMPM].padBitPos;

  if ( HAL_MPMINT_INVALID_BIT_POS != nPadPos )
  {
    nRegPad  = get_en_reg_pad(nPadPos);
    nPadMask = MAKE_MASK(nPadPos);

    nVal = inpdw(nRegPad);
    nVal &= ~nPadMask;
    outpdw(nRegPad, nVal);
  }

  /*
   * Disable the interrupt in MPM
   */
  nBitPos = nMPM;
  nReg    = get_en_reg(nBitPos);
  nMask   = MAKE_MASK(nBitPos);

  nVal = inpdw(nReg);
  nVal &= ~nMask;
  outpdw(nReg, nVal);

} /* END HAL_mpmint_Disable */


/* ===========================================================================
**  HAL_mpmint_Clear
**
** ======================================================================== */

void HAL_mpmint_Clear
(
  uint32 nMPM
)
{
  uint32 nBitPos, nMask, nReg;

  nBitPos = nMPM;
  nMask   = MAKE_MASK(nBitPos);
  nReg    = get_clear_reg(nBitPos);

  outpdw(nReg, nMask);

} /* END HAL_mpmint_Clear */


/* ===========================================================================
**  HAL_mpmint_All_Enable
**
** ======================================================================== */

void HAL_mpmint_All_Enable( void )
{
  uint32 nNumRegs, nReg, nRegPad, nClearReg, i, nNumRegpad;

  /* enable at pad first */
  nNumRegpad = HAL_MPMINT_PHYS_INTS / 32;
  for(i = 0; i < nNumRegpad; i++)
  {
	nRegPad   = registerLayout.nEnableRegPad[i];
	//memset((void*)nRegPad, 0xFFFFFFFF, sizeof(uint32));
	*((int*)nRegPad) = 0xFFFFFFFF;
  }

  HAL_mpmint_GetNumberMasks(&nNumRegs);
  
  for(i = 0; i < nNumRegs; i++)
  {
    nReg      = registerLayout.nEnableReg[i];
    nClearReg = registerLayout.nClearReg[i];
	
    /* then clear the interrupts */
    //memset((void*)nClearReg, 0xFFFFFFFF, sizeof(uint32));
	*((int*)nClearReg) = 0xFFFFFFFF;

    /* finally, enable the interrupts */
    //memset((void*)nReg, 0xFFFFFFFF, sizeof(uint32));
	*((int*)nReg) = 0xFFFFFFFF;
  }
} /* END HAL_mpmint_All_Enable */


/* ===========================================================================
**  HAL_mpmint_All_Disable
**
** ======================================================================== */

void HAL_mpmint_All_Disable( void )
{
  uint32 nNumRegs, nReg, nRegPad, i, nNumRegpad;

  HAL_mpmint_GetNumberMasks(&nNumRegs);
/* disable both at pad AND in MPM */
  for(i = 0; i < nNumRegs; i++)
  {
    nReg    = registerLayout.nEnableReg[i];
    //memset((void*)nReg, 0, sizeof(uint32));
	*((int*)nReg) = 0;
  }
  
  nNumRegpad = HAL_MPMINT_PHYS_INTS / 32;

  for(i = 0; i < nNumRegpad; i++)
  {
    nRegPad = registerLayout.nEnableRegPad[i];
    //memset((void*)nRegPad, 0, sizeof(uint32));
	*((int*)nRegPad) = 0;
  } 
} /* END HAL_mpmint_Disable */


/* ===========================================================================
**  HAL_mpmint_All_Clear
**
** ======================================================================== */

void HAL_mpmint_All_Clear( void )
{
  uint32 nNumRegs, nReg, i;

  HAL_mpmint_GetNumberMasks(&nNumRegs);
  for(i = 0; i < nNumRegs; i++)
  {
    nReg     = registerLayout.nClearReg[i];
    //memset((void*)nReg, 0xFFFFFFFF, sizeof(uint32));
	*((int*)nReg) = 0xFFFFFFFF;
  }

} /* END HAL_mpmint_Clear */


/* ===========================================================================
**  HAL_mpmint_GetNumberMasks
**
** ======================================================================== */

void HAL_mpmint_GetNumberMasks
(
  uint32 *pnNumber
)
{

  *pnNumber = ( HAL_MPMINT_NUM / 32);

} /* END HAL_mpmint_GetNumberMasks */


/* ===========================================================================
**  HAL_mpmint_Mask_Enable
**
** ======================================================================== */

void HAL_mpmint_Mask_Enable
(
  uint32 nMaskIndex,
  uint32 nMask
)
{
  uint32 nNumRegs, nWorkingMask, i;

  HAL_mpmint_GetNumberMasks(&nNumRegs);

  if(nMaskIndex > nNumRegs)
    return;

  // This is a simplified implementation; if blazing speed is necessary this
  // can likely be made faster by unrolling the multiple Enable calls into:
  //   - a write per pad enable register
  //   - a Mask_Clear call
  //   - a write to the enable register
  nWorkingMask = 1;
  for(i = 0; i < 32 && nMask; i++)
  {
    if(nMask & nWorkingMask)
    {
      HAL_mpmint_Enable(32 * nMaskIndex + i);
    }
    nWorkingMask = (nWorkingMask << 1) | (nWorkingMask >> 31);
  }

} /* END HAL_mpmint_Mask_Enable */


/* ===========================================================================
**  HAL_mpmint_Mask_Disable
**
** ======================================================================== */

void HAL_mpmint_Mask_Disable
(
  uint32 nMaskIndex,
  uint32 nMask
)
{
  uint32 nNumRegs, nWorkingMask, i;

  HAL_mpmint_GetNumberMasks(&nNumRegs);

  if(nMaskIndex > nNumRegs)
    return;

  // This is a simplified implementation; if blazing speed is necessary this
  // can likely be made faster by unrolling the multiple Disable calls into:
  //   - a write per pad enable register
  //   - a write to the enable register
  nWorkingMask = 1;
  for(i = 0; i < 32 && nMask; i++)
  {
    if(nMask & nWorkingMask)
    {
      HAL_mpmint_Disable(32 * nMaskIndex + i);
    }
    nWorkingMask = (nWorkingMask << 1) | (nWorkingMask >> 31);
  }

} /* END HAL_mpmint_Mask_Disable */


/* ===========================================================================
**  HAL_mpmint_Mask_Clear
**
** ======================================================================== */

void HAL_mpmint_Mask_Clear
(
  uint32 nMaskIndex,
  uint32 nMask
)
{
  uint32 nNumRegs, nReg;

  HAL_mpmint_GetNumberMasks(&nNumRegs);

  if(nMaskIndex >= nNumRegs)
    return;

  nReg = registerLayout.nClearReg[nMaskIndex];
  outpdw(nReg, nMask);

} /* END HAL_mpmint_Mask_Clear */


/* ===========================================================================
**  HAL_mpmint_GetPending
**
** ======================================================================== */

void HAL_mpmint_GetPending
(
  uint32 nMaskIndex,
  uint32 *pnMask
)
{
  uint32 nNumRegs, nReg, nEnable;

  HAL_mpmint_GetNumberMasks(&nNumRegs);

  if((nMaskIndex >= nNumRegs) || (!pnMask))
    return;

  nReg = registerLayout.nStatusReg[nMaskIndex];
  nEnable = registerLayout.nEnableReg[nMaskIndex];
  *pnMask = ( inpdw(nReg) & inpdw(nEnable) );

} /* HAL_mpmint_GetPending */

void HAL_mpmint_GetIndex(uint32 nDetect, uint32 nDetect3, uint32 nPolarity, uint32 nMask, HAL_mpmint_TriggerType *trigger)
{
  uint32 index = 0;
  if (nDetect & nMask)
    index |= 1;
  if (nDetect3 & nMask)
    index |= 2;
  if (nPolarity & nMask)
    index |= 4;

  *trigger = mpmint_trigger_lookup[index];
}


/* ===========================================================================
**  HAL_mpmint_GetTrigger
**
** ======================================================================== */

void HAL_mpmint_GetTrigger
(
  uint32                   nMPM,
  HAL_mpmint_TriggerType *peTrigger
)
{
  uint32 nBitPos, nMask, nRegDetLow, nRegDetHigh, nRegPol;
  uint32 index = 0;

  nBitPos  = nMPM;
  nMask    = MAKE_MASK(nBitPos);
  nRegDetLow  = get_det_reg_low(nBitPos);
  nRegDetHigh  = get_det_reg_high(nBitPos);
  nRegPol  = get_pol_reg(nBitPos);

  HAL_mpmint_GetIndex(inpdw(nRegDetLow), inpdw(nRegDetHigh), inpdw(nRegPol), nMask, peTrigger);
  
  *peTrigger = mpmint_trigger_lookup[index];

  /*
   * Update the shadow in case it was incorrect
   */
  aInterruptTable[nMPM].eTrigger = *peTrigger;

} /* HAL_mpmint_GetTrigger */


/* ===========================================================================
**  HAL_mpmint_SetTrigger
**
** ======================================================================== */

void HAL_mpmint_SetTrigger
(
  uint32                   nMPM,
  HAL_mpmint_TriggerType  eTrigger
)
{
  uint32 nBitPos, nMask, nReg, nVal;
  uint32 index = (uint32)mpmint_trigger_lookup[eTrigger];

  /*
   * Configure edge bit 1
   */
  nBitPos = nMPM;
  nMask   = MAKE_MASK(nBitPos);
  nReg    = get_det_reg_low(nBitPos);
  nVal    = inpdw(nReg);
  if (DET_A_FROM_IDX(index))
  {
    nVal |= nMask;
  }
  else
  {
    nVal &= ~nMask;
  }
  outpdw(nReg, nVal);

  /*
   *  Configure edge bit 2
   */
  nReg    = get_det_reg_high(nBitPos);
  nVal    = inpdw(nReg);
  if (DET_B_FROM_IDX(index))
  {
    nVal |= nMask;
  }
  else
  {
    nVal &= ~nMask;
  }
  outpdw(nReg, nVal);

  /*
   * Configure the polarity
   */
  nReg = get_pol_reg(nBitPos);
  nVal = inpdw(nReg);
  if (POL_FROM_IDX(index))
  {
    nVal |= nMask;
  }
  else
  {
    nVal &= ~nMask;
  }
  outpdw(nReg, nVal);

  /*
   * Save the new value
   */
  aInterruptTable[nMPM].eTrigger = eTrigger;

} /* END HAL_mpmint_SetTrigger */


/* ===========================================================================
**  HAL_mpmint_GetNumber
**
** ======================================================================== */

void HAL_mpmint_GetNumber
(
  uint32 *pnNumber
)
{

  /* MPM interrupt controller supports HAL_MPMINT_NUM interrupts */
  *pnNumber = HAL_MPMINT_NUM;

} /* END HAL_mpmint_GetNumber */


/* ===========================================================================
**  HAL_mpmint_GetNumberPhysical
**
** ======================================================================== */
void HAL_mpmint_GetNumberPhysical
(
  uint32 *pnNumber
)
{
  /* the correct number is defined by the platform */
  *pnNumber = HAL_MPMINT_NUM;
} /* HAL_mpmint_GetNumberPhysical */


/* ===========================================================================
**  HAL_mpmint_GetPhysNumber
**
** ======================================================================== */
bool32 HAL_mpmint_GetPhysNumber
(
  uint32 nMPM,
  uint32 *pnPhys
)
{

  if(HAL_mpmint_IsSupported(nMPM))
  {
    *pnPhys = nMPM;
    return TRUE;
  }

  return FALSE;
} /* HAL_mpmint_GetPhysNumber */


/* ===========================================================================
**  HAL_mpmint_GetEnumNumber
**
** ======================================================================== */
bool32 HAL_mpmint_GetEnumNumber
(
  uint32 nPhys,
  uint32 *pnMPM
)
{
  /* current HAL uses a 1:1 mapping between phys and enum */
  uint32 nMPM = nPhys;

  if(HAL_mpmint_IsSupported(nMPM))
  {
    *pnMPM = nMPM;
    return TRUE;
  }

  return FALSE;
} /* HAL_mpmint_GetEnumNumber */


/* ===========================================================================
**  HAL_mpmint_IsSupported
**
** ======================================================================== */

bool32 HAL_mpmint_IsSupported
(
  uint32 nMPM
)
{
  return ( nMPM < HAL_MPMINT_NUM );
} /* END HAL_mpmint_IsSupported */


/* ===========================================================================
**  HAL_mpmint_IsGpioSupported
**
** ======================================================================== */

bool32 HAL_mpmint_IsGpioSupported
(
  uint32 nGPIO,
  uint32 *pnMPM
)
{
  uint32 nMPM;

  /*
   * Check to see if this GPIO is supported as a wakeup, and if so, 
   * return the MPM interrupt that it corresponds to.
   */ 
  for ( nMPM = 0; nMPM < HAL_MPMINT_NUM; nMPM++ )
  {
    if ( aInterruptTable[nMPM].gpio == nGPIO )
    {
      break;
    }
  }

  if ( nMPM < HAL_MPMINT_NUM )
  {
    *pnMPM = nMPM;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


/* ===========================================================================
**  HAL_mpmint_IsGpio
**
** ======================================================================== */

bool32 HAL_mpmint_IsGpio
(
  uint32 nMPM,
  uint32 *pnGPIO
)
{
  bool32 retval = FALSE;

  if ( aInterruptTable[nMPM].gpio != HAL_MPMINT_INVALID_GPIO )
  {
    *pnGPIO = aInterruptTable[nMPM].gpio;
    retval = TRUE;
  }

  return retval;
} /* HAL_mpmint_IsGpio */


/* ===========================================================================
**  HAL_mpmint_IsPending
**
** ======================================================================== */

bool32 HAL_mpmint_IsPending
(
  uint32 nMPM
)
{
  uint32 nBitPos, nMask, nStatusReg, nEnableReg;
  bool32 bPending = FALSE;

  nBitPos    = nMPM;
  nMask      = MAKE_MASK(nBitPos);
  nStatusReg = get_status_reg(nBitPos);
  nEnableReg = get_en_reg(nBitPos);

  if (inpdw(nStatusReg) & inpdw(nEnableReg) & nMask)
  {
    bPending = TRUE;
  }

  /*
   * Return if we are set
   */
  return bPending;

} /* END HAL_mpmint_IsPending */


/* ===========================================================================
**  HAL_mpmint_IsEnabled
**
** ======================================================================== */

bool32 HAL_mpmint_IsEnabled
(
  uint32 nMPM
)
{
  uint32 nBitPos, nMask, nReg;
  bool32 bEnabled = FALSE;

  nBitPos = nMPM;
  nMask   = MAKE_MASK(nBitPos);
  nReg    = get_en_reg(nBitPos);

  if (inpdw(nReg) & nMask)
  {
    bEnabled = TRUE;
  }

  /*
   * Return if we are set
   */
  return bEnabled;

} /* END HAL_mpmint_IsEnabled */

