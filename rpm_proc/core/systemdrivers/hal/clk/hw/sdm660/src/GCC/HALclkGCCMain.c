/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkGCCMain.c#2 $

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
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCDDRCPLL0ROOTClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCNOCPERIPHClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGPUVSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCIPA2XClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCMSSVSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCPIMEMAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSAPBTRIGClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBAClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSATBCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSSTMClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSTRACECLKINClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCQDSSTSCTRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMBIMCCY4XClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMDEBUGCY4XClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMFFClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMPNOCCYClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMRPMCYClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPDMSNOCCY2XClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCRPMClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMIAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSPMISERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSNOCHSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDAVSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDCXVSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCVDDMXVSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCVSCTRLClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCDDRXOClkDomain;
/*
 * Power domains
 */

extern HAL_clk_PowerDomainDescType HAL_clk_mGCCAGGRE2NOCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCBIMCPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCDDRDIMWRAPPERPowerDomain;
#if 0
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCIPAPowerDomain;
#endif
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCMMSSPowerDomain;


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
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL5,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


static HAL_clk_SourceMapType aGCCSystemNocSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
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
 * HAL_clk_mGCCClockDomainControl
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCSystemNocClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGCCSystemNocSourceMap
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
 * HAL_clk_aGCCClockDomainDesc
 *
 * List of GCC clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aGCCClockDomainDesc [] =
{
  &HAL_clk_mGCCBIMCDDRCPLL0ROOTClkDomain,
  &HAL_clk_mGCCCE1ClkDomain,
  &HAL_clk_mGCCCNOCPERIPHClkDomain,
  &HAL_clk_mGCCCONFIGNOCClkDomain,
  &HAL_clk_mGCCIPA2XClkDomain,
  &HAL_clk_mGCCMSSVSClkDomain,
  &HAL_clk_mGCCPIMEMAXIClkDomain,
  &HAL_clk_mGCCQDSSAPBTRIGClkDomain,
  &HAL_clk_mGCCQDSSATBAClkDomain,
  &HAL_clk_mGCCQDSSATBBClkDomain,
  &HAL_clk_mGCCQDSSATBCClkDomain,
  &HAL_clk_mGCCQDSSSTMClkDomain,
  &HAL_clk_mGCCQDSSTRACECLKINClkDomain,
  &HAL_clk_mGCCQDSSTSCTRClkDomain,
  &HAL_clk_mGCCRPMClkDomain,
  &HAL_clk_mGCCSPDMBIMCCY4XClkDomain,
  &HAL_clk_mGCCSPDMDEBUGCY4XClkDomain,
  &HAL_clk_mGCCSPDMFFClkDomain,
  &HAL_clk_mGCCSPDMPNOCCYClkDomain,
  &HAL_clk_mGCCSPDMRPMCYClkDomain,
  &HAL_clk_mGCCSPDMSNOCCY2XClkDomain,
  &HAL_clk_mGCCSPMIAHBClkDomain,
  &HAL_clk_mGCCSPMISERClkDomain,
  &HAL_clk_mGCCSYSNOCHSAXIClkDomain,
  &HAL_clk_mGCCSYSTEMNOCClkDomain,
  &HAL_clk_mGCCVDDAVSClkDomain,
  &HAL_clk_mGCCVDDCXVSClkDomain,
  &HAL_clk_mGCCVDDMXVSClkDomain,
  &HAL_clk_mGCCVSCTRLClkDomain,
  &HAL_clk_mGCCHMSSAHBClkDomain,
  &HAL_clk_mGCCBIMCDDRXOClkDomain,
  NULL
};


/*
 * HAL_clk_aGCCPowerDomainDesc
 *
 * List of GCC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGCCPowerDomainDesc [] =
{
  &HAL_clk_mGCCAGGRE2NOCPowerDomain,
  &HAL_clk_mGCCBIMCPowerDomain,
  &HAL_clk_mGCCDDRDIMWRAPPERPowerDomain,
#if 0
  &HAL_clk_mGCCIPAPowerDomain,
  &HAL_clk_mGCCMMSSPowerDomain,
#endif
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

