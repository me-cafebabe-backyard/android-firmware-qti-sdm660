/*
==============================================================================

FILE:         HALclkUSB20.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   USB20 clocks.

   List of clock domains:
     - HAL_clk_mGCCUSB20MASTERClkDomain
     - HAL_clk_mGCCUSB20MOCKUTMIClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkUSB20.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mUSB20MASTERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB20MASTERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_cfg_noc_usb2_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_USB2_AXI_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_USB2_AXI_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout12_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT12_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT12_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT12_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_usb20_master_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB20_MASTER_CBCR), HWIO_OFFS(GCC_USB_20_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB20_MASTER_CLK
  },
};


/*
 * HAL_clk_mGCCUSB20MASTERClkDomain
 *
 * USB20MASTER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB20MASTERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB20_MASTER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUSB20MASTERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB20MASTERClkDomainClks)/sizeof(HAL_clk_mUSB20MASTERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mUSB20MOCKUTMIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mUSB20MOCKUTMIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_usb20_mock_utmi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB20_MOCK_UTMI_CBCR), HWIO_OFFS(GCC_USB_20_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_USB20_MOCK_UTMI_CLK
  },
};


/*
 * HAL_clk_mGCCUSB20MOCKUTMIClkDomain
 *
 * USB20MOCKUTMI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB20MOCKUTMIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_USB20_MOCK_UTMI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mUSB20MOCKUTMIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mUSB20MOCKUTMIClkDomainClks)/sizeof(HAL_clk_mUSB20MOCKUTMIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

