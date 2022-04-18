/*
==============================================================================

FILE:         HALclkGenericPLL.c

DESCRIPTION:
  This file contains the generic clock HAL code for the PLL control.
  These PLLs are of the Prius and Tesla PLL variety.

==============================================================================

                             Edit History


when       who     what, where, why
--------   ---     -----------------------------------------------------------
05/30/13   frv     Created
04/08/14   sr      Added support for the Veyron PLL.

==============================================================================
   Copyright (c) 2013-2014 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
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


extern HAL_clk_SourceControlType HAL_clk_BrammoPLLControl;
extern HAL_clk_SourceControlType HAL_clk_SRPLLControl;
extern HAL_clk_SourceControlType HAL_clk_PriusPLLControl;
extern HAL_clk_SourceControlType HAL_clk_VeyronPLLControl;
extern HAL_clk_SourceControlType HAL_clk_HuayraPLLControl;
extern HAL_clk_SourceControlType HAL_clk_HuayraCBFPLLControl;
extern HAL_clk_SourceControlType HAL_clk_SparkPLLControl;
extern HAL_clk_SourceControlType HAL_clk_BrammoBearPLLControl;
extern HAL_clk_SourceControlType HAL_clk_FabiaPLLControl;
extern HAL_clk_SourceControlType HAL_clk_AgeraPLLControl;

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
  size_t                  nBaseAddress
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
  if ((pCtxt->ePLLType == HAL_CLK_PLL_SR) ||
      (pCtxt->ePLLType == HAL_CLK_PLL_SR2))
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_SRPLLControl, pCtxt);
  }
  else if ((pCtxt->ePLLType == HAL_CLK_PLL_PRIUS)   ||
           (pCtxt->ePLLType == HAL_CLK_PLL_TESLA)   ||
           (pCtxt->ePLLType == HAL_CLK_PLL_STROMER))
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_PriusPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_BRAMMO)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_BrammoPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_BRAMMO_BEAR)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_BrammoBearPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_VEYRON)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_VeyronPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_HUAYRA)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_HuayraPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_HUAYRA_CBF)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_HuayraCBFPLLControl, pCtxt);
  }
  else if ((pCtxt->ePLLType == HAL_CLK_PLL_SPARK) ||
           (pCtxt->ePLLType == HAL_CLK_PLL_SPARK_HMSS))
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_SparkPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_FABIA)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_FabiaPLLControl, pCtxt);
  }
  else if (pCtxt->ePLLType == HAL_CLK_PLL_AGERA)
  {
    HAL_clk_InstallSource(eSource, &HAL_clk_AgeraPLLControl, pCtxt);
  }
  else
  {
    // error but no return parameter to provide!
    die_here: goto die_here;
  }

} /* END HAL_clk_InstallPLL */
