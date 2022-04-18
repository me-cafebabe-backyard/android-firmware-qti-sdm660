#ifndef __HALCLKGENERICPLL_H__
#define __HALCLKGENERICPLL_H__
/*
==============================================================================

FILE:         HALclkGenericPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/v1/HALclkGenericPLL.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
05/30/13   frv     Created.

==============================================================================
Copyright (c) 2016 Qualcomm Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALclkInternal.h"



/* ============================================================================
**    Definitions
** ==========================================================================*/


/* ============================================================================
**    External Definitions
** ==========================================================================*/

#define HAL_CLK_PLL_HWIO_ADDR(reg, ctxt)  (ctxt->nAddr + HWIO_OFFS(reg))

#define HAL_CLK_PLL_HWIO_IN(reg, ctxt)       \
  inpdw(HAL_CLK_PLL_HWIO_ADDR(reg, ctxt))

#define HAL_CLK_PLL_HWIO_INF(reg, ctxt, fld) \
  ((inpdw(HAL_CLK_PLL_HWIO_ADDR(reg, ctxt)) & HWIO_FMSK(reg, fld)) >> HWIO_SHFT(reg, fld))

#define HAL_CLK_PLL_HWIO_INFV(reg, ctxt, fld, var) \
  ((var & HWIO_FMSK(reg, fld)) >> HWIO_SHFT(reg, fld))

#define HAL_CLK_PLL_HWIO_OUT(reg, ctxt, val) \
  outpdw(HAL_CLK_PLL_HWIO_ADDR(reg, ctxt), val)

#define HAL_CLK_PLL_HWIO_OUTF(reg, ctxt, fld, val)           \
  outpdw(HAL_CLK_PLL_HWIO_ADDR(reg, ctxt),                   \
   (HAL_CLK_PLL_HWIO_IN(reg, ctxt) & ~HWIO_FMSK(reg, fld))   \
   | (((val) << HWIO_SHFT(reg, fld)) & HWIO_FMSK(reg, fld)))

#define HAL_CLK_PLL_HWIO_OUTFV(reg, ctxt, fld, val, var)           \
   ((var & ~HWIO_FMSK(reg, fld))   \
   | (((val) << HWIO_SHFT(reg, fld)) & HWIO_FMSK(reg, fld)))


/* ============================================================================
**    Functions
** ==========================================================================*/

/*
 * Install a PLL handler.
 */
void HAL_clk_InstallPLL( HAL_clk_SourceType eSource, HAL_clk_PLLContextType *pCtxt, uint32 nBaseAddress);


#endif  /* __HALCLKGENERICPLL_H__ */

