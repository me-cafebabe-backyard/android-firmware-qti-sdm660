/*
===========================================================================

FILE:         teetest_HALqgic.c

DESCRIPTION:
  This is the hardware abstraction layer implementation for the Qualcomm
  Generic Interrupt Controller.

===========================================================================

                             Edit History

$Header: //components/rel/core.tz/1.0.7.1/securemsm/trustzone/qsapps/teetest/teetest/src/teetest_hal_qgic.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
07/22/09   gfr     Fixed GICD_ICFGRn indexing.
04/08/09   gfr     Renamed GICD_IDR to GICD_IIDR.
12/11/08   gfr     Created.

===========================================================================
           Copyright (c) 2011 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "teetest.h"
#include "teetest_hal_qgic.h"
#include "teetest_hal_hwio.h"
/*
 * QGIC Distributor section base address definitions
 */
uintnt nHalGICDBaseAddress;

/*
 * QGIC CPU Interface section base address definitions
 */
uintnt nHalGICCBaseAddress;

/*
 * QGIC Hypervisor section base address definitions
 */
uintnt nHalGICHBaseAddress;

/*
 * QGIC Virtualization section base address definitions
 */
uintnt nHalGICVBaseAddress;

/*
 * QGIC Redistributor section base address definitions.
 */
uintnt nHalGICRBaseAddress;

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */


/*
 * Identifier string for this HAL.
 */
#define HAL_QGIC_VERSION_STRING "HAL_QGIC_V1"

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */


/* ===========================================================================
**  HAL_qgic_Init
**
** ======================================================================== */

void HAL_qgic_Init
(
  HAL_qgic_BaseAddressType *pBaseAddr
)
{
  uint32 nCPUCount, nIdx;

  /*
   * Validate input pointer
   */
  if (pBaseAddr == NULL)
  {
    return;
  }

  /*
   * Assign register base
   */
  nHalGICDBaseAddress = pBaseAddr->nGICDBaseAddress;
  nHalGICCBaseAddress = pBaseAddr->nGICCBaseAddress;
  nHalGICHBaseAddress = pBaseAddr->nGICHBaseAddress;
  nHalGICVBaseAddress = pBaseAddr->nGICVBaseAddress;
  nHalGICRBaseAddress = pBaseAddr->nGICRBaseAddress;

} /* END HAL_qgic_Init */


/* ===========================================================================
**  HAL_qgic_SetSecurity
**
** ======================================================================== */

void HAL_qgic_SetSecurity
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_SecureType    eSecure
)
{
  uintnt nAddr;
  uint32 nMask;
  uint32 nVal;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ISRn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  nVal = inpdw(nAddr);

  if (eSecure == HAL_QGIC_SECURE)
  {
    nVal &= ~nMask;
  }
  else
  {
    nVal |= nMask;
  }

  outpdw(nAddr, nVal);

} /* END HAL_qgic_SetSecurity */

/* ===========================================================================
**  HAL_qgic_GetSecurity
**
** ======================================================================== */

void HAL_qgic_GetSecurity
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_SecureType    *peSecure
)
{
  uintnt nAddr;
  uint32 nMask;
  uint32 nVal;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ISRn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  nVal = inpdw(nAddr);

  if (nVal & nMask)
  {
    *peSecure = HAL_QGIC_NON_SECURE;
  }
  else
  {
    *peSecure = HAL_QGIC_SECURE;
  }


} /* END HAL_qgic_GetSecurity */



/* ===========================================================================
**  HAL_qgic_Enable
**
** ======================================================================== */

void HAL_qgic_Enable
(
  HAL_qgic_InterruptType nInterrupt
)
{
  uintnt nAddr;
  uint32 nMask;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ISENABLERn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  outpdw(nAddr, nMask);

} /* END HAL_qgic_Enable */


/* ===========================================================================
**  HAL_qgic_Disable
**
** ======================================================================== */

void HAL_qgic_Disable
(
  HAL_qgic_InterruptType nInterrupt
)
{
  uintnt nAddr;
  uint32 nMask;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ICENABLERn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  outpdw(nAddr, nMask);

} /* END HAL_qgic_Disable */




/* ===========================================================================
**  HAL_qgic_IsPending
**
** ======================================================================== */

boolean HAL_qgic_IsPending
(
  HAL_qgic_InterruptType nInterrupt
)
{
  uintnt nAddr;
  uint32 nMask;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ISPENDRn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  if (inpdw(nAddr) & nMask)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }

} /* END HAL_qgic_IsPending */


/* ===========================================================================
**  HAL_qgic_IsActive
**
** ======================================================================== */

boolean HAL_qgic_IsActive
(
  HAL_qgic_InterruptType nInterrupt
)
{
  uintnt nAddr;
  uint32 nMask;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr = HAL_QGIC_INT2ADDR(GICD_IACTIVERn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  /*
   * Check the active bit.
   */
  if (inpdw(nAddr) & nMask)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }

} /* END HAL_qgic_IsActive */


/* ===========================================================================
**  HAL_qgic_SetPriority
**
** ======================================================================== */

void HAL_qgic_SetPriority
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_PriorityType  nPriority
)
{
  uintnt nAddr;
  uint8 nVal;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr  = HWIO_ADDRI(GICD_IPRIORITYRn, nInterrupt / 4) + (nInterrupt % 4);
  nVal = nPriority;

  /*
   * Program the new priority.
   */
  outp(nAddr, nVal);

} /* END HAL_qgic_SetPriority */

/* ===========================================================================
**  HAL_qgic_GetPriority
**
** ======================================================================== */

void HAL_qgic_GetPriority
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_PriorityType  *pnPriority
)
{
  uintnt nAddr;
  uint32 nShift;
  uint32 nVal;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr  = HWIO_ADDRI(GICD_IPRIORITYRn, nInterrupt / 4);
  nShift = (nInterrupt & 0x3) * 8;

  /*
   * Read the priority.
   */
  nVal = inpdw(nAddr);
  *pnPriority = nVal >> nShift;
  *pnPriority &= 0xFF;

} /* END HAL_qgic_GetPriority */


/* ===========================================================================
**  HAL_qgic_SetTargets
**
** ======================================================================== */

void HAL_qgic_SetTargets
(
  HAL_qgic_InterruptType nInterrupt,
  uint32                 nTargets
)
{
  uintnt nAddr;
  uint8 nVal;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr  = HWIO_ADDRI(GICD_ITARGETSRn, nInterrupt / 4) + (nInterrupt % 4);
  nVal = nTargets;

  /*
   * Program the new target CPU.
   */
  outp(nAddr, nVal);

} /* END HAL_qgic_SetTargets */


/* ===========================================================================
**  HAL_qgic_GetTargets
**
** ======================================================================== */

void HAL_qgic_GetTargets
(
  HAL_qgic_InterruptType nInterrupt,
  uint32                 *pnTargets
)
{
  uintnt nAddr;
  uint32 nMask;
  uint32 nShift;
  uint32 nVal;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr  = HWIO_ADDRI(GICD_ITARGETSRn, nInterrupt / 4);
  nShift = (nInterrupt & 0x3) * 8;
  nMask  = 0xFF << nShift;

  /*
   * Mask existing target.
   */
  nVal = inpdw(nAddr);
  nVal &= nMask;
  *pnTargets = (nVal >> nShift) & 0xFF;

} /* END HAL_qgic_GetTargets */


/* ===========================================================================
**  HAL_qgic_IsEnabled
**
** ======================================================================== */

boolean HAL_qgic_IsEnabled
(
  HAL_qgic_InterruptType nInterrupt
)
{
  uintnt nAddr;
  uint32 nMask;

  nAddr = HAL_QGIC_INT2ADDR(GICD_ISENABLERn, nInterrupt);
  nMask = HAL_QGIC_INT2MASK(nInterrupt);

  if (inpdw(nAddr) & nMask)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }

} /* END HAL_qgic_IsEnabled */

/* ===========================================================================
**  HAL_qgic_SetTrigger
**
** ======================================================================== */

void HAL_qgic_SetTrigger
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_TriggerType   eTrigger
)
{
  uintnt nAddr;
  uint32 nMask;
  uint32 nVal;
  boolean bIsEnabled;

  /*
   * Get the address and mask for this interrupt.
   */
  nAddr = HWIO_ADDRI(GICD_ICFGRn, nInterrupt >> 4);
  nMask = (0x1 << ((nInterrupt & 0xF) * 2 + 1));

  /*
   * Get current configuration
   */
  nVal = inpdw(nAddr);

  /*
   * Determine new configuration based on interrupt type and trigger.
   */
  if (eTrigger == HAL_QGIC_TRIGGER_EDGE)
  {
    nVal |= nMask;
  }
  else
  {
    nVal &= ~nMask;
  }

  /*
   * Disable the interrupt while programming the type.
   */
  bIsEnabled = HAL_qgic_IsEnabled(nInterrupt);
  if (bIsEnabled)
  {
    HAL_qgic_Disable(nInterrupt);
  }

  /*
   * Program the new trigger.
   */
  outpdw(nAddr, nVal);

  /*
   * Re-enable the interrupt if necessary.
   */
  if (bIsEnabled)
  {
    HAL_qgic_Enable(nInterrupt);
  }

} /* END HAL_qgic_SetTrigger */




/* ===========================================================================
**  HAL_qgic_Generate
**
** ======================================================================== */

void HAL_qgic_Generate
(
  HAL_qgic_InterruptType nInterrupt,
  HAL_qgic_SecureType    eSecure,
  uint32                 nTargets
)
{
  uint32 nCmd;

  /*
   * Only send SGIs or the command may do bad things.
   */
  if (!HAL_QGIC_IS_SGI(nInterrupt))
  {
    return;
  }

  /*
   * Fill in the command value.
   */
  nCmd = nInterrupt;

  /*
   * Set the security attribute.
   */
  if (eSecure == HAL_QGIC_NON_SECURE)
  {
    nCmd |= HWIO_FMSK(GICD_SGIR, SATT);
  }

  /*
   * Fill in the targets.
   */
  if ((nTargets & HAL_QGIC_TARGET_OTHERS) &&
      (nTargets & HAL_QGIC_TARGET_SELF))
  {
    nCmd |= HWIO_FMSK(GICD_SGIR, T_LIST);
  }
  else if (nTargets & HAL_QGIC_TARGET_OTHERS)
  {
    nCmd |= HWIO_FVAL(GICD_SGIR, T_FILTER, 0x1);
  }
  else if (nTargets & HAL_QGIC_TARGET_SELF)
  {
    nCmd |= HWIO_FVAL(GICD_SGIR, T_FILTER, 0x2);
  }
  else
  {
    nCmd |= HWIO_FVAL(GICD_SGIR, T_LIST, nTargets);
  }

  /*
   * Trigger the interrupt.
   */
  HWIO_OUT(GICD_SGIR, nCmd);

} /* END HAL_qgic_Generate */






