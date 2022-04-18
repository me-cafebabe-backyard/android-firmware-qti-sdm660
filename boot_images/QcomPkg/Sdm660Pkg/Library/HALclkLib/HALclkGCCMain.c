/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGCCMain.c#4 $

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



/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCHMSSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCLOCKDRIVERGENNODOMAINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCNOCPERIPHClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGP3ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGPUBIMCGFXClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSRBCPRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCMMSSQMCOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCMSSQ6BIMCAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCPDM2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSAPBTRIGClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBAClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQSPISERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC1ICECOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMIAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMISERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSTANDALONEBCRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSNOCHSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSICECOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSPHYAUXClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSRXSYMBOL0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSRXSYMBOL1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSTXSYMBOL0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUFSUNIPROCOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB20MASTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB20MOCKUTMIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB30MASTERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB30MOCKUTMIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB3PHYAUXClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCUSB3PHYPIPEClkDomain;

/*
 * Power domains
 */
#if 0 /* not present on apcs */
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCMMSSPowerDomain;
#endif
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCUFSPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCUSB30PowerDomain;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGCCSourceMap
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL5,              2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_SLEEPCLK,           5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap
};


/*
 * HAL_clk_mGCCClockDomainControlRO
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap
};


/*
 * aGCCSourceMap_1
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_1[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_1
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_1 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_1
};


/*
 * HAL_clk_mGCCClockDomainControlRO_1
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_1 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_1
};


/*
 * aGCCSourceMap_2
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_2[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_2
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_2 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_2
};


/*
 * HAL_clk_mGCCClockDomainControlRO_2
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_2 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_2
};


/*
 * aGCCSourceMap_3
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_3[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GPLL1_DIV2,         3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_3
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_3 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_3
};


/*
 * HAL_clk_mGCCClockDomainControlRO_3
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_3 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_3
};


/*
 * aGCCSourceMap_4
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_4[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL5,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_4
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_4 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_4
};


/*
 * HAL_clk_mGCCClockDomainControlRO_4
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_4 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_4
};


/*
 * aGCCSourceMap_5
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_5[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL1_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_5
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_5 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_5
};


/*
 * HAL_clk_mGCCClockDomainControlRO_5
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_5 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSourceMap_5
};


/*
 * HAL_clk_aGCCClockDomainDesc
 *
 * List of GCC clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aGCCClockDomainDesc [] =
{
  &HAL_clk_mGCCBIMCHMSSAXIClkDomain,
  &HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART2APPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART2APPSClkDomain,
  &HAL_clk_mGCCCE1ClkDomain,
  &HAL_clk_mGCCCLOCKDRIVERGENNODOMAINClkDomain,
  &HAL_clk_mGCCCNOCPERIPHClkDomain,
  &HAL_clk_mGCCCONFIGNOCClkDomain,
  &HAL_clk_mGCCGCCSLEEPClkDomain,
  &HAL_clk_mGCCGCCXOClkDomain,
  &HAL_clk_mGCCGP1ClkDomain,
  &HAL_clk_mGCCGP2ClkDomain,
  &HAL_clk_mGCCGP3ClkDomain,
  &HAL_clk_mGCCGPUBIMCGFXClkDomain,
  &HAL_clk_mGCCHMSSAHBClkDomain,
  &HAL_clk_mGCCHMSSRBCPRClkDomain,
  &HAL_clk_mGCCMMSSQMCOREClkDomain,
  &HAL_clk_mGCCMSSQ6BIMCAXIClkDomain,
  &HAL_clk_mGCCPDM2ClkDomain,
  &HAL_clk_mGCCQDSSAPBTRIGClkDomain,
  &HAL_clk_mGCCQDSSATBAClkDomain,
  &HAL_clk_mGCCQDSSATBBClkDomain,
  &HAL_clk_mGCCQDSSATBCClkDomain,
  &HAL_clk_mGCCQSPISERClkDomain,
  &HAL_clk_mGCCSDCC1APPSClkDomain,
  &HAL_clk_mGCCSDCC1ICECOREClkDomain,
  &HAL_clk_mGCCSDCC2APPSClkDomain,
  &HAL_clk_mGCCSPMIAHBClkDomain,
  &HAL_clk_mGCCSPMISERClkDomain,
  &HAL_clk_mGCCSTANDALONEBCRClkDomain,
  &HAL_clk_mGCCSYSNOCHSAXIClkDomain,
  &HAL_clk_mGCCSYSTEMNOCClkDomain,
  &HAL_clk_mGCCUFSAXIClkDomain,
  &HAL_clk_mGCCUFSICECOREClkDomain,
  &HAL_clk_mGCCUFSPHYAUXClkDomain,
  &HAL_clk_mGCCUFSRXSYMBOL0ClkDomain,
  &HAL_clk_mGCCUFSRXSYMBOL1ClkDomain,
  &HAL_clk_mGCCUFSTXSYMBOL0ClkDomain,
  &HAL_clk_mGCCUFSUNIPROCOREClkDomain,
  &HAL_clk_mGCCUSB20MASTERClkDomain,
  &HAL_clk_mGCCUSB20MOCKUTMIClkDomain,
  &HAL_clk_mGCCUSB30MASTERClkDomain,
  &HAL_clk_mGCCUSB30MOCKUTMIClkDomain,
  &HAL_clk_mGCCUSB3PHYAUXClkDomain,
  &HAL_clk_mGCCUSB3PHYPIPEClkDomain,
  NULL
};


/*
 * HAL_clk_aGCCPowerDomainDesc
 *
 * List of GCC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGCCPowerDomainDesc [] =
{
#if 0 /* not present on apcs */
  &HAL_clk_mGCCMMSSPowerDomain,
#endif
  &HAL_clk_mGCCUFSPowerDomain,
  &HAL_clk_mGCCUSB30PowerDomain,
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitGCCMain
**
** ======================================================================== */

void HAL_clk_PlatformInitGCCMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aGCCClockDomainDesc, CLK_CTL_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aGCCPowerDomainDesc, CLK_CTL_BASE);

} /* END HAL_clk_PlatformInitGCCMain */

