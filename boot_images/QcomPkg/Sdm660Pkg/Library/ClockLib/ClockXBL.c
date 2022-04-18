/** @file ClockUEFI.c

  This file implements specialized image specific functions such
  as init image, enable DCVS, etc. In case of UEFI, we have few
  place holders for now.

  Copyright (c) 2010-2016, Qualcomm Technologies, Inc.
                   All rights reserved.
                 QUALCOMM Proprietary/GTDR

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/30/14   sj      Fixed 64 bit compilation errors
 05/08/14   sr      Ported to 8994.
 08/09/12   sr      Ported to 8974.
 12/23/10   vs      Created.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DDIClock.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include "ClockApps.h"
#include "ClockAVS.h"
#include <Protocol/EFIPlatformInfoTypes.h>

#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>
#include "DDIChipInfo.h"
/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Externals
==========================================================================*/

extern void HAL_clk_MemCoreSave (void);
extern void HAL_clk_MemCoreRestore (void);
extern void HAL_clk_NocDcdEnable (void);
extern void HAL_clk_NocDcdDisable (void);


/*=========================================================================
      Prototypes
==========================================================================*/

void Clock_VDDCXNodeReadyCallback(void *pContext, unsigned int nEventType, void *pNodeName, unsigned int  nNodeNameSize);
void Clock_VDDMXNodeReadyCallback(void *pContext, unsigned int nEventType, void *pNodeName, unsigned int  nNodeNameSize);


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * UEFI Clock Driver local context.
 */
typedef struct
{
  boolean        bLowPowerMode;
  boolean        bClusterGoldInReset;
  ClockNodeType *ClusterSilverId;
  ClockNodeType *ClusterGoldId;
  ClockNodeType *MDSSMDPClockId;
} ClockLocalCtxtType;


/**
 * UEFI Clock Driver NPA context.
 */
typedef struct
{
  boolean                         bDefineResource;
  npa_remote_resource_definition  Clock_NPARemoteResource;
  npa_callback                    fpCallBack;
  npa_client_handle               hClient;
  uint32                          nLowPowerValue;
  ClockDrvCtxt                   *pDrvCtxt;
} ClockNPACtxtType;


/*=========================================================================
      Data
==========================================================================*/

/*
 * Defined in DalClockFwk.c
 */
extern DALREG_DriverInfo DALClock_DriverInfo;

/*
 * gDALModDriverInfoList needs to be created for WM and UEFI - dynamic
 * loading of DAL drivers. This will not work for AMSS image (static loading
 * via DAL based XML files at compile time) so the following can't go in
 * DalClockFwk.c which is common across images
 *
 */
static DALREG_DriverInfo* DALDriverInfoArr[1] = { &DALClock_DriverInfo};
DALREG_DriverInfoList gDALModDriverInfoList= {1, DALDriverInfoArr};
npa_client_handle   hMmssNocAxiHandle = NULL;

/*-----------------------------------------------------------------------*/
/* Remote node definitions.                                              */
/*-----------------------------------------------------------------------*/

static ClockNPACtxtType Clock_aNPACtxt[] =
{
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/qdss",
      /* .remote_resource_name  = */ "clk0\x01\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "STATE",
      /* .max                   = */ 4,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL
    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/dcvs.ena",
      /* .remote_resource_name  = */ "clk0\x02\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_binary_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "Enable",
      /* .max                   = */ 1,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL
    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 1,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/cnoc_periph",
      /* .remote_resource_name  = */ "clk1\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 19200,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/snoc",
      /* .remote_resource_name  = */ "clk1\x01\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL
    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 19200,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/cnoc",
      /* .remote_resource_name  = */ "clk1\x02\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 19200,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/bimc",
      /* .remote_resource_name  = */ "clk2\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 37500,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/ipa",
      /* .remote_resource_name  = */ "ipa\x00\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/ce1",
      /* .remote_resource_name  = */ "ce\x00\x00\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/agr2",
      /* .remote_resource_name  = */ "aggr\x02\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/pmem",
      /* .remote_resource_name  = */ "pmem\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ TRUE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/clk/mmnoc_axi",
      /* .remote_resource_name  = */ "mmxi\x00\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "KHz",
      /* .max                   = */ NPA_MAX_STATE,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ NULL,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ 0,
    /* .pDrvCtxt                = */ NULL,
  },
#if 0 // move these nodes from PMIC to vcs-> rpm
  {
    /* .bDefineResource         = */ FALSE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/pmic/client/rail_cx",
      /* .remote_resource_name  = */ "smpa\x01\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "ModeID",
      /* .max                   = */ CLOCK_VREG_LEVEL_HIGH,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL

    },
    /* .fpCallBack              = */ Clock_VDDCXNodeReadyCallback,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ CLOCK_VREG_LEVEL_LOW_MINUS,
    /* .pDrvCtxt                = */ NULL,
  },
  {
    /* .bDefineResource         = */ FALSE,
    { /* .Clock_NPARemoteResource */
      /* .local_resource_name   = */ "/pmic/client/rail_mx",
      /* .remote_resource_name  = */ "smpa\x02\x00\x00\x00",
      /* .protocol_type         = */ "/protocol/rpm/rpm",
      /* .plugin                = */ &npa_max_plugin,
      /* .driver_fcn            = */ npa_remote_resource_local_aggregation_driver_fcn,
      /* .units                 = */ "ModeID",
      /* .max                   = */ CLOCK_VREG_LEVEL_HIGH,
      /* .attributes            = */ 0,
      /* .data                  = */ NULL,
      /* .handle                = */ NULL
    },
    /* .fpCallBack              = */ Clock_VDDMXNodeReadyCallback,
    /* .hClient                 = */ NULL,
    /* .nLowPowerValue          = */ CLOCK_VREG_LEVEL_LOW,
    /* .pDrvCtxt                = */ NULL,
  },
#endif
};

#define   CLOCK_CLUSTER0_FREQUENCY_HZ      1382400 * 1000UL
#define   CLOCK_CLUSTER1_FREQUENCY_HZ      1670400 * 1000UL
#define   CLOCK_CLUSTER0_VOLTAGE_MV        896
#define   CLOCK_CLUSTER1_VOLTAGE_MV        896


#define   CLOCK_CLUSTER0_FREQUENCY_HZ_BU   600000  * 1000UL
#define   CLOCK_CLUSTER1_FREQUENCY_HZ_BU   600000  * 1000UL
#define   CLOCK_CLUSTER0_VOLTAGE_MV_BU     896
#define   CLOCK_CLUSTER1_VOLTAGE_MV_BU     896



static ClockSourceFreqConfigType HFPLLCfgCPU0 =
{
  /*                |-.HALConfig------------------------------------------------------------------------------|                             |-.HWVersion----------------------------------------------------------------------------------|              */
  /* .nFreqHz,      {.eSource, .eVCO, .nPreDiv, .nPostDiv, .nL,  .nM, .nN, .nVCOMultiplier, .nAlpha, .nAlphaU } .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .bLastEntry */
  CLOCK_CLUSTER0_FREQUENCY_HZ, { HAL_CLK_SOURCE_XO, HAL_CLK_PLL_VCO1, 1, 1,  72, 0, 0, 0, 0x00000000, 0x00 },              CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   0
};

static ClockSourceFreqConfigType HFPLLCfgCPU1 =
{
  /*                |-.HALConfig------------------------------------------------------------------------------|                             |-.HWVersion----------------------------------------------------------------------------------|              */
  /* .nFreqHz,      {.eSource, .eVCO, .nPreDiv, .nPostDiv, .nL,  .nM, .nN, .nVCOMultiplier, .nAlpha, .nAlphaU } .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .bLastEntry */
  CLOCK_CLUSTER1_FREQUENCY_HZ, { HAL_CLK_SOURCE_XO, HAL_CLK_PLL_VCO1, 1, 1,  87, 0, 0, 0, 0x00000000, 0x00 },              CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   0
};

static ClockMuxConfigType MuxCfgHFCPU0 =
{
  /*                |-.HALConfig--------------------------|                              |-.HWVersion----------------------------------------------------------------------------------|                     */
  /* .nFreqHz,      { .eSource, .nDiv2x, .nM, .nN, .n2D   }  .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .pSourceFreqConfig */
  CLOCK_CLUSTER0_FREQUENCY_HZ, { HAL_CLK_SOURCE_APCSPLL0, 2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   &HFPLLCfgCPU0
};

static ClockMuxConfigType MuxCfgHFCPU1 =
{
  /*                |-.HALConfig--------------------------|                              |-.HWVersion----------------------------------------------------------------------------------|                     */
  /* .nFreqHz,      { .eSource, .nDiv2x, .nM, .nN, .n2D   }  .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .pSourceFreqConfig */
  CLOCK_CLUSTER1_FREQUENCY_HZ, { HAL_CLK_SOURCE_APCSPLL1, 2, 0, 0, 0 }, CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   &HFPLLCfgCPU1
};


// work around for HW bringup Issue
static ClockMuxConfigType MuxCfgHFCPU0_BU =
{
  /*                |-.HALConfig--------------------------|                              |-.HWVersion----------------------------------------------------------------------------------|                     */
  /* .nFreqHz,      { .eSource, .nDiv2x, .nM, .nN, .n2D   }  .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .pSourceFreqConfig */
  CLOCK_CLUSTER0_FREQUENCY_HZ_BU,  { HAL_CLK_SOURCE_GPLL0, 2, 0, 0, 0 },    CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   NULL
};

static ClockMuxConfigType MuxCfgHFCPU1_BU =
{
  /*                |-.HALConfig--------------------------|                              |-.HWVersion----------------------------------------------------------------------------------|                     */
  /* .nFreqHz,      { .eSource, .nDiv2x, .nM, .nN, .n2D   }  .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .pSourceFreqConfig */
  CLOCK_CLUSTER1_FREQUENCY_HZ_BU,  { HAL_CLK_SOURCE_GPLL0, 2, 0, 0, 0 },    CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   NULL
};

static ClockMuxConfigType MuxCfgLowPower =
{
  /*                |-.HALConfig--------------------------|                              |-.HWVersion----------------------------------------------------------------------------------|                     */
  /* .nFreqHz,      { .eSource, .nDiv2x, .nM, .nN, .n2D   }  .eVRegLevel,                { { .Min.nMajor, .Min.nMinor }, { .Max.nMajor, .Max.nMinor }, .eChipInfoFamily, .aeChipInfoId }, .pSourceFreqConfig */
  600000 * 1000UL,  { HAL_CLK_SOURCE_GPLL0, 2, 0, 0, 0 },    CLOCK_VREG_LEVEL_LOW_MINUS, { { 0, 0 }, { 0xFF, 0xFF }, DALCHIPINFO_FAMILY_UNKNOWN, NULL},                                   NULL
};

ClockLocalCtxtType  ClockLocalCtxt;

#define MMNOCAXI_LOW_POWER_FREQUENCY  19200   // KHz
#define MMNOCAXI_DEFAULT_FREQUENCY    323200  // KHz

#define MDSSMDP_LOW_POWER_FREQUENCY   171428  // KHz
#define MDSSMDP_DEFAULT_FREQUENCY     330000  // KHz

/*
 * The voltage levels specified below were chosen to accommodate all parts of
 * every version. These values come from the characterized silicone and are
 * based on the Slow bin parts.
 */
#define CORE_LOWEST_VOLTAGE           644000  // @ 300 MHz - 0.644 V

#define CORE_NOMINAL_VOLTAGE          868000  // @ varies MHz - 0.868 V


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_VDDCXNodeReadyCallback
** =========================================================================*/

void Clock_VDDCXNodeReadyCallback(void *pContext, unsigned int nEventType, void *pNodeName, unsigned int nNodeNameSize)
{
  ClockNPACtxtType  *pClockNPACtxtType = (ClockNPACtxtType *)pContext;

  /*-----------------------------------------------------------------------*/
  /* Create NPA client handle for VDD CX                                   */
  /*-----------------------------------------------------------------------*/

  pClockNPACtxtType->hClient = npa_create_sync_client(
    pClockNPACtxtType->Clock_NPARemoteResource.local_resource_name,
    "UEFI_client", NPA_CLIENT_REQUIRED);

} /* END Clock_VDDCXNodeReadyCallback */


/* =========================================================================
**  Function : Clock_VDDMXNodeReadyCallback
** =========================================================================*/

void Clock_VDDMXNodeReadyCallback(void *pContext, unsigned int nEventType, void *pNodeName, unsigned int nNodeNameSize)
{
  ClockNPACtxtType  *pClockNPACtxtType = (ClockNPACtxtType *)pContext;

  /*-----------------------------------------------------------------------*/
  /* Create NPA client handle for VDD MX                                   */
  /*-----------------------------------------------------------------------*/

  pClockNPACtxtType->hClient = npa_create_sync_client(
    pClockNPACtxtType->Clock_NPARemoteResource.local_resource_name,
    "UEFI_client", NPA_CLIENT_REQUIRED);

  /*-----------------------------------------------------------------------*/
  /* Test only.                                                            */
  /*-----------------------------------------------------------------------*/

  #if 0
  {
    DALResult eResult;

    eResult = Clock_EnterLowPowerMode(pClockNPACtxtType->pDrvCtxt);
    eResult = Clock_ExitLowPowerMode(pClockNPACtxtType->pDrvCtxt);
    eResult = eResult;
  }
  #endif

} /* END Clock_VDDMXNodeReadyCallback */


/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/*
  See DalClock.h
*/

DALResult Clock_InitImage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult                     eResult;
  uint32                        i;
  uint32                        nResultFreq;
  uint32 nChipFamily;

  /*-----------------------------------------------------------------------*/
  /* Initialze local UEFI Clock Driver context.                            */
  /*-----------------------------------------------------------------------*/

  memset(&ClockLocalCtxt, 0, sizeof(ClockLocalCtxtType));

  /*-----------------------------------------------------------------------*/
  /* Initialize the PLLs                                                   */
  /*-----------------------------------------------------------------------*/
  #if 0
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPLL0,  0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPLL1,  0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPLL4,  0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPLL5,  0);
  #endif
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPUPLL0, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_GPUPLL1, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL0, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL1, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL3, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL4, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL5, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL6, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL7, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL8, 0);
  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL10, 0);
  /*-----------------------------------------------------------------------*/
  /* Initialize the CPU PLLs.                                              */
  /*-----------------------------------------------------------------------*/
  HAL_clk_ConfigSource(HAL_CLK_SOURCE_APCSPLL0, HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE);
  HAL_clk_ConfigSource(HAL_CLK_SOURCE_APCSPLL1, HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE);

  HAL_clk_ConfigSource(HAL_CLK_SOURCE_APCSPLL0, HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE);
  HAL_clk_ConfigSource(HAL_CLK_SOURCE_APCSPLL1, HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE);

  /*-----------------------------------------------------------------------*/
  /* Get clock IDs for the two clusters.                                   */
  /*-----------------------------------------------------------------------*/
  eResult = Clock_GetClockId(pDrvCtxt, "apcs_cluster0_clk", (ClockIdType *)&ClockLocalCtxt.ClusterSilverId);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  eResult = Clock_GetClockId(pDrvCtxt, "apcs_cluster1_clk", (ClockIdType *)&ClockLocalCtxt.ClusterGoldId);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }
#if 0
  // work around for HW bringup Issue
  if ((pDrvCtxt->nGlobalPlatformInfo == EFI_PLATFORMINFO_TYPE_RUMI) ||
      (pDrvCtxt->nGlobalPlatformInfo == EFI_PLATFORMINFO_TYPE_VIRTIO))
  {
    /*-----------------------------------------------------------------------*/
    /* Ramp up the cluster 0 clock.                                          */
    /*-----------------------------------------------------------------------*/
    Clock_EnableClock(pDrvCtxt, (ClockIdType)ClockLocalCtxt.ClusterSilverId);
    Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterSilverId->pDomain, &MuxCfgHFCPU0);

    /*-----------------------------------------------------------------------*/
    /* Ramp up the cluster 1 clock. Cluster 1 won't actually be switched to  */
    /* the HF PLL because this code runs on core 0 of cluster 0. The rest of */
    /* the cores will switch to run from the corresponding HF PLLs inside    */
    /* MP_PARK when they are brought out of reset.                           */
    /*-----------------------------------------------------------------------*/
    Clock_EnableClock(pDrvCtxt, (ClockIdType)ClockLocalCtxt.ClusterGoldId);
    Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterGoldId->pDomain, &MuxCfgHFCPU1);
  }
  else
 #endif
  nChipFamily = DalChipInfo_ChipFamily();
  { // Bringup Target
    /*-----------------------------------------------------------------------*/
    /* Ramp up the cluster 0 clock.                                          */
    /*-----------------------------------------------------------------------*/
    Clock_EnableClock(pDrvCtxt, (ClockIdType)ClockLocalCtxt.ClusterSilverId);
    if(nChipFamily == DALCHIPINFO_FAMILY_SDM630)
    {
      Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterSilverId->pDomain, &MuxCfgHFCPU0_BU);
    }

    /*-----------------------------------------------------------------------*/
    /* Ramp up the cluster 1 clock. Cluster 1 won't actually be switched to  */
    /* the HF PLL because this code runs on core 0 of cluster 0. The rest of */
    /* the cores will switch to run from the corresponding HF PLLs inside    */
    /* MP_PARK when they are brought out of reset.                           */
    /*-----------------------------------------------------------------------*/
    Clock_EnableClock(pDrvCtxt, (ClockIdType)ClockLocalCtxt.ClusterGoldId);
    if(nChipFamily == DALCHIPINFO_FAMILY_SDM660)
    {
      Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterGoldId->pDomain, &MuxCfgHFCPU1_BU);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get the MDSS MDP clock ID.                                            */
  /*-----------------------------------------------------------------------*/
  eResult = Clock_GetClockId(pDrvCtxt, "mmss_mdss_mdp_clk",
    (ClockIdType *)&ClockLocalCtxt.MDSSMDPClockId);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

 // #if 0
  /*-----------------------------------------------------------------------*/
  /* Set the MDSS MDP clock's frequency.                                   */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetClockFrequency(pDrvCtxt,
                                    (ClockIdType)ClockLocalCtxt.MDSSMDPClockId,
                                    MDSSMDP_DEFAULT_FREQUENCY,
                                    CLOCK_FREQUENCY_KHZ_CLOSEST,
                                    &nResultFreq);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }
//  #endif

  /*-----------------------------------------------------------------------*/
  /* Initialize the NPA context.                                           */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < SIZEOF_ARRAY(Clock_aNPACtxt); i++)
  {
    if (Clock_aNPACtxt[i].bDefineResource)
    {
      /*-----------------------------------------------------------------------*/
      /* Define the resource and initialize the handle.                        */
      /*-----------------------------------------------------------------------*/
      npa_remote_define_resource(&Clock_aNPACtxt[i].Clock_NPARemoteResource, 0, NULL);
      Clock_aNPACtxt[i].hClient = npa_create_sync_client(
        Clock_aNPACtxt[i].Clock_NPARemoteResource.local_resource_name,
        "UEFI_client", NPA_CLIENT_REQUIRED);
    }
    else
    {
      /*-----------------------------------------------------------------------*/
      /* Create callback events.                                               */
      /*-----------------------------------------------------------------------*/
      npa_resource_available_cb(Clock_aNPACtxt[i].Clock_NPARemoteResource.local_resource_name,
        Clock_aNPACtxt[i].fpCallBack, &Clock_aNPACtxt[i]);
    }
    Clock_aNPACtxt[i].pDrvCtxt = pDrvCtxt;
  }

  pDrvCtxt->pImageCtxt = &ClockLocalCtxt;
 //#if 0
  /*-----------------------------------------------------------------------*/
  /* Process MMNOCAXI_DEFAULT_FREQUENCY frequest.                          */
  /*-----------------------------------------------------------------------*/
  hMmssNocAxiHandle = npa_create_sync_client("/clk/mmnoc_axi",    /* resource name */
                                             "UEFI_CLOCK_DRIVER", /* client name   */
                                             NPA_CLIENT_REQUIRED  /* work model    */
                                            );

  npa_issue_required_request(hMmssNocAxiHandle, MMNOCAXI_DEFAULT_FREQUENCY);
  /*-----------------------------------------------------------------------*/
  /* Initialize AVS.                                                       */
  /*-----------------------------------------------------------------------*/
 
  eResult = Clock_InitAVS(pDrvCtxt, NULL);

  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }
 

  /*-----------------------------------------------------------------------*/
  /* Test only.                                                            */
  /*-----------------------------------------------------------------------*/

  #if 0
  eResult = Clock_EnterLowPowerMode(pDrvCtxt);
  eResult = Clock_ExitLowPowerMode(pDrvCtxt);
  #endif

  return DAL_SUCCESS;

} /* END Clock_InitImage */


/* =========================================================================
**  Function : Clock_VoltageRequest
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_VoltageRequest
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockVRegRequestType  *pCurrentRequest,
  ClockVRegRequestType  *pNewRequest
)
{

  /*-----------------------------------------------------------------------*/
  /* Nothing to do for UEFI just yet.                                      */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_VoltageRequest */


/* =========================================================================
**  Function : Clock_InitVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_InitVoltage
(
  ClockDrvCtxt *pDrvCtxt
)
{

  /*-----------------------------------------------------------------------*/
  /* Nothing to do for UEFI just yet.                                      */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitVoltage */


/* =========================================================================
**  Function : Clock_EnterLowPowerMode
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnterLowPowerMode
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult           eResult, eReturnedResult = DAL_SUCCESS;
  ClockLocalCtxtType  *pClockLocalCtxt = (ClockLocalCtxtType *)pDrvCtxt->pImageCtxt;
  uint32              i;
  uint32              nResultFreq;

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Do not allow nested entries of the Low Power Mode.                    */
  /*-----------------------------------------------------------------------*/

  if (pClockLocalCtxt->bLowPowerMode == TRUE)
  {
    DALCLOCK_FREE(pDrvCtxt);
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Lower the MDSS MDP clock's frequency.                                 */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetClockFrequency(pDrvCtxt,
                                    (ClockIdType)ClockLocalCtxt.MDSSMDPClockId,
                                    MDSSMDP_LOW_POWER_FREQUENCY,
                                    CLOCK_FREQUENCY_KHZ_CLOSEST,
                                    &nResultFreq);
  if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
  {
    eReturnedResult = eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Lower the mmnoc_ax clock's frequency.                                 */
  /*-----------------------------------------------------------------------*/
  npa_issue_required_request(hMmssNocAxiHandle, MMNOCAXI_LOW_POWER_FREQUENCY);

  /*-----------------------------------------------------------------------*/
  /* Reduce each core's frequency to the lowest possible.                  */
  /*-----------------------------------------------------------------------*/

  Clock_SetClockConfig(pDrvCtxt, pClockLocalCtxt->ClusterSilverId->pDomain, &MuxCfgLowPower);
  Clock_SetClockConfig(pDrvCtxt, pClockLocalCtxt->ClusterGoldId->pDomain, &MuxCfgLowPower);

  /*-----------------------------------------------------------------------*/
  /* Reduce voltage of both clusters to the lowest possible.               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetVoltageLevel(HAL_AVS_CORE_APC0_L2, CORE_LOWEST_VOLTAGE);
  if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
  {
    eReturnedResult = eResult;
  }
  eResult = Clock_SetVoltageLevel(HAL_AVS_CORE_APC1_L2, CORE_LOWEST_VOLTAGE);
  if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
  {
    /*
     * If the H1 Cluster is not accepting a voltage change, then assume it is
     * being held in reset. Remember this fact.
     */
    pClockLocalCtxt->bClusterGoldInReset = TRUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Reduce every bus frequency to the lowest possible.                    */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < SIZEOF_ARRAY(Clock_aNPACtxt); i++)
  {
    if (Clock_aNPACtxt[i].hClient != NULL)
    {
      npa_issue_required_request(Clock_aNPACtxt[i].hClient, Clock_aNPACtxt[i].nLowPowerValue);
    }
  }

  pClockLocalCtxt->bLowPowerMode = TRUE;

  DALCLOCK_FREE(pDrvCtxt);

  return eReturnedResult;

} /* END Clock_EnterLowPowerMode */


/* =========================================================================
**  Function : Clock_ExitLowPowerMode
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ExitLowPowerMode
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult           eResult = DAL_SUCCESS;
  DALResult           eReturnedResult = DAL_SUCCESS;
  ClockLocalCtxtType  *pClockLocalCtxt = (ClockLocalCtxtType *)pDrvCtxt->pImageCtxt;
  uint32              i;
  uint32              nResultFreq;

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Make sure the Low Power Mode is active before exiting it.             */
  /*-----------------------------------------------------------------------*/

  if (pClockLocalCtxt->bLowPowerMode == FALSE)
  {
    DALCLOCK_FREE(pDrvCtxt);
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Restore every bus frequency to its nominal.                           */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < SIZEOF_ARRAY(Clock_aNPACtxt); i++)
  {
    if (Clock_aNPACtxt[i].hClient != NULL)
    {
      npa_complete_request(Clock_aNPACtxt[i].hClient);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Restore voltage of both clusters to the nominal level.                */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetVoltageLevel(HAL_AVS_CORE_APC0_L2, CORE_NOMINAL_VOLTAGE);
  if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
  {
    eReturnedResult = eResult;
  }
  eResult = Clock_SetVoltageLevel(HAL_AVS_CORE_APC1_L2, CORE_NOMINAL_VOLTAGE);
  if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
  {
    /*
     * If the H1 Cluster is being held in reset, ignore the voltage setting failure.
     */
    if (pClockLocalCtxt->bClusterGoldInReset)
    {
      eResult = DAL_SUCCESS;
    }
    else
    {
      eReturnedResult = eResult;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Restore each core's frequency to the nominal.                         */
  /*-----------------------------------------------------------------------*/

  if (eResult != DAL_ERROR)
  {
    MuxCfgHFCPU0.HALConfig.eSource = HAL_CLK_SOURCE_APCSPLL0;
    Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterSilverId->pDomain, &MuxCfgHFCPU0);

    MuxCfgHFCPU1.HALConfig.eSource = HAL_CLK_SOURCE_APCSPLL1;
    Clock_SetClockConfig(pDrvCtxt, ClockLocalCtxt.ClusterGoldId->pDomain, &MuxCfgHFCPU1);

    /*-----------------------------------------------------------------------*/
    /* Restore the MDSS MDP clock's frequency.                               */
    /*-----------------------------------------------------------------------*/

    eResult = Clock_SetClockFrequency(pDrvCtxt,
                                      (ClockIdType)ClockLocalCtxt.MDSSMDPClockId,
                                      MDSSMDP_DEFAULT_FREQUENCY,
                                      CLOCK_FREQUENCY_KHZ_CLOSEST,
                                      &nResultFreq);
    if (eReturnedResult == DAL_SUCCESS && eResult != DAL_SUCCESS)
    {
      eReturnedResult = eResult;
    }

    /*-----------------------------------------------------------------------*/
    /* Restore the mmnoc_ax clock's frequency.                               */
    /*-----------------------------------------------------------------------*/

    npa_issue_required_request(hMmssNocAxiHandle, MMNOCAXI_DEFAULT_FREQUENCY);

    pClockLocalCtxt->bLowPowerMode = FALSE;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eReturnedResult;

} /* END Clock_ExitLowPowerMode */


/*=========================================================================
**  Function : Clock_NormalizeChipInfo
** =========================================================================*/
/*
  See ClockDriver.h
*/

void Clock_NormalizeChipInfo
(
  HAL_clk_ContextType *HALClkCtxt
)
{
}

/* =========================================================================
**  Function : Clock_GetCpuFrequencyHz
** =========================================================================*/
DALResult Clock_GetCpuFrequencyHz
(
  ClockDrvCtxt *pDrvCtxt,
  uint32 *pnFrequencyHz
)
{
  if (pnFrequencyHz == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize output parameter                                           */
  /*-----------------------------------------------------------------------*/
#if 0
  // work around for HW bringup Issue
  if ((pDrvCtxt->nGlobalPlatformInfo == EFI_PLATFORMINFO_TYPE_RUMI) ||
      (pDrvCtxt->nGlobalPlatformInfo == EFI_PLATFORMINFO_TYPE_VIRTIO))
  {
    *pnFrequencyHz = CLOCK_CLUSTER0_FREQUENCY_HZ;
  }
  else
  {
    *pnFrequencyHz = CLOCK_CLUSTER0_FREQUENCY_HZ_BU;
  }
#endif
    switch(DalChipInfo_ChipFamily()){
        case DALCHIPINFO_FAMILY_SDM660 :
            *pnFrequencyHz = 1382400000;
            break;
        case DALCHIPINFO_FAMILY_SDM630 :
            *pnFrequencyHz = 1670400000;
            break;
        default:
            *pnFrequencyHz = 0x0;
            break;
    }
  return DAL_SUCCESS;
}
