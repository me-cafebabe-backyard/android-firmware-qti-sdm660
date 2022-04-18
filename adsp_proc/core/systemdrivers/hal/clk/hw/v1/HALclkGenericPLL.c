/*
==============================================================================

FILE:         HALclkGenericPLL.c

DESCRIPTION:
  This file contains the generic clock HAL code for the PLL control.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/v1/HALclkGenericPLL.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/11/16   shm     First version for core.qdsp6.1.0
09/04/12   dcf     Merged enabling sequence for SR and SR2 PLLs
02/24/11   gfr     Created

==============================================================================
Copyright (c) 2016 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkGenericPLL.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/


/* ============================================================================
**    Data Declarations
** ==========================================================================*/


/* ============================================================================
**    External Definitions
** ==========================================================================*/


extern HAL_clk_SourceControlType HAL_clk_SparkPLLControl;
extern HAL_clk_SourceControlType HAL_clk_FabiaPLLControl;
extern HAL_clk_SourceControlType HAL_clk_AgeraPLLControl;
extern HAL_clk_SourceControlType HAL_clk_PeelPLLControl;

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_InstallPLL
**
** ======================================================================== */

void HAL_clk_InstallPLL
(
  HAL_clk_SourceType      eSource,
  HAL_clk_PLLContextType *pCtxt,
  uint32                  nBaseAddress
)
{
  /*
   * Add base address
   */
  pCtxt->nAddr += nBaseAddress;

  if (pCtxt->VoterRegister.nAddr != 0)
  {
    pCtxt->VoterRegister.nAddr += nBaseAddress;
  }

  /*
   * Install PLL handler
   */
  if ((pCtxt->ePLLType == HAL_CLK_PLL_SPARK) ||
      (pCtxt->ePLLType == HAL_CLK_PLL_BRAMMO))
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_SparkPLLControl, pCtxt);
  }
  else if(pCtxt->ePLLType == HAL_CLK_PLL_FABIA)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_FabiaPLLControl, pCtxt);
  }
  else if(pCtxt->ePLLType == HAL_CLK_PLL_AGERA)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_AgeraPLLControl, pCtxt);
  }
  else if(pCtxt->ePLLType == HAL_CLK_PLL_PEEL)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_PeelPLLControl, pCtxt);
  }
  else
  {
    // error but no return parameter to provide!
  }

} /* END HAL_clk_InstallPLL */
