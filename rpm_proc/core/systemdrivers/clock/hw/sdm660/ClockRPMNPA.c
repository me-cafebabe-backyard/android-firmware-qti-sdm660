/*
===========================================================================
*/
/**
  @file ClockRPMNPA.c 
  
  NPA node definitions for the MSM8996 RPM clock driver.
*/
/*  
  ====================================================================

  Copyright (c) 2013-2016 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/hw/sdm660/ClockRPMNPA.c#12 $
  $DateTime: 2017/08/21 09:17:04 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  07/07/15   vph     Support rate matching in MMSS AXI and Sys NOC.
  05/21/15   vph     Fixed IPA power collapse does not trigger.
  11/27/13   vph     Initial version
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "mpm.h"
#include "swevent.h"
#include "QDSSLite.h"
#include "ClockRPMNPA.h"
#include "ClockRPMBIMC.h"
#include "ClockCommon.h"
#include "CoreVerify.h"
#include "icb_rpm.h"


/*=========================================================================
      Macros
==========================================================================*/
#define DCVS_ENABLE

#define DDR_MAX_KHZ         4000000
#define SNOC_MAX_KHZ        4000000
#define XO_FREQ_HZ          19200000
#define XO_FREQ_KHZ         (XO_FREQ_HZ / 1000)

#define CLK_RPM_NPA_ENABLE_MAX                      1

// markers for npa clients, marked in client resource data
#define CLK_NPA_NODE_RES_DATA_INTERNAL_CLIENT_FLAG  0x00010000

#define CLK_NPA_NODE_RES_DATA_CLIENT_ID_MASK        0x0000FFFF
#define CLK_NPA_NODE_CLIENT_ID_EQ(hClient, id)      (((uint32)((hClient)->resource_data) & CLK_NPA_NODE_RES_DATA_CLIENT_ID_MASK) == (id))

#define CLK_NPA_NODE_RES_DATA_MPSS_REQ              0x504D
#define CLK_NPA_NODE_RES_DATA_APSS_REQ              0x5041


/*=========================================================================
      Prototypes
==========================================================================*/
extern unsigned int qdss_fuse_trace_access(void);
extern void sleep_update_xo_stats(const npa_client *xo_clients, const npa_client *changed_client); 

uint32 Clock_SNOCHSSetFrequency
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeCXOFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeDCVSEnaFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeGenericFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeBIMCFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeIPAFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
);


static npa_resource_state Clock_NPANodeSPMFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
);


static npa_resource_state Clock_NPANodeQDSSFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
);


static npa_resource_state Clock_NPANodeMMSSAXIFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
);

static npa_resource_state Clock_NPANodeAggrFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
);


static npa_query_status Clock_NPAResourceQuery
(
  npa_resource   *pResource,
  unsigned int   nId,
  npa_query_type *pResult
);


static void Clock_CXRailPreChangedCB
(
  const railway_settings *settings,
  void                   *cookie
);


static void Clock_CXRailPostChangedCB
(
  const railway_settings *settings,
  void                   *cookie
);

static void Clock_SetVSenseFrequency
(
  ClockVRegLevelType eVReg 
);

static void Clock_NPACreateMarkedClient
(
  npa_client *hClient
);

npa_resource_state Clock_NPASuppressibleMaxUpdate
(
 npa_resource      *resource,
 npa_client_handle  client 
);

void Clock_SNOCVoteMatchSpeed( uint32 nSNOCFreqKHz, uint32 nSNOCHSFreqKHz, uint32 *nNewSNOCFreqKHz, uint32 *nNewSNOCHSFreqKHz );

uint32 gDDRFreqIndex;
/*=========================================================================
      Data
==========================================================================*/

Clock_TargCtxtType Clock_Resources;

/* Rate matching data */
static npa_client_handle SNOCHandle = NULL;
static npa_client_handle MMXIHandle = NULL;
static npa_client_handle SNOCHSHandle = NULL;
static npa_client_handle CNOCPeriphHandle = NULL;
static npa_client_handle CNOCHandle = NULL;

typedef enum {
  SNOC_RMFREQ_ID,
  SNOC_HS_RMFREQ_ID,
  SNOC_PIMEM_RMFREQ_ID,
  MAXSNOC_RMFREQ_ID
} SNOC_RMFREQ_ARRAY_ID;


typedef enum {
  FMAX_VREG_LEVEL_LOW_MINUS,
  FMAX_VREG_LEVEL_LOW,
  FMAX_VREG_LEVEL_LOW_PLUS,
  FMAX_VREG_LEVEL_NOMINAL,
  FMAX_VREG_LEVEL_NOMINAL_PLUS,
  FMAX_VREG_LEVEL_HIGH,
  FMAX_VREG_LEVEL_NUM_CORNERS
} FMAX_VREG_LEVEL;

uint32 SNOCRMFreqKHz[FMAX_VREG_LEVEL_NUM_CORNERS + 1][MAXSNOC_RMFREQ_ID]; /*Single entry for each corner, one extra for  last NULL entry*/



uint32 RMFreqKHz[][5] =
{
  // DDR frequency to be filled at run-time
  //                       SNOC, MMSS_AXI,  SNOC_HS, CNOC
  { DDR_MAX_KHZ,  75000,  75000,  75000, 33330},    // SVS2
  { DDR_MAX_KHZ, 120000, 171430, 150000, 37500},    // SVS
  { DDR_MAX_KHZ, 160400, 240000, 200000, 37500},    // SVS_L1
  { DDR_MAX_KHZ, 200000, 323200, 240000, 75000},    // NOM
  { DDR_MAX_KHZ, 236310, 406000, 300000, 75000},    // TUR
  { 0 },  // End of frequency table
};

/*
 * Clock driver NPA unit strings.
 */
static const char szClockNPAUnitEnable[] = "Enable";
static const char szClockNPAUnitKHz[] = "KHz";
static const char szClockNPAUnitState[] = "STATE";

const npa_resource_plugin Clock_NPANodeMaxPlugin = 
{
  Clock_NPASuppressibleMaxUpdate,
  /* Supported client types */
  NPA_CLIENT_INTERNAL | NPA_CLIENT_REQUIRED | NPA_CLIENT_SUPPRESSIBLE | 
  NPA_CLIENT_LIMIT_MAX | NPA_CLIENT_IMPULSE, 
  Clock_NPACreateMarkedClient,  /* Create client function */
  NULL                          /* Destroy client function */
};

const npa_resource_plugin Clock_NPANodeIPAPlugin = 
{
  npa_max_update_fcn,
  /* Supported client types */
  NPA_CLIENT_INTERNAL | NPA_CLIENT_REQUIRED | NPA_CLIENT_SUPPRESSIBLE | 
  NPA_CLIENT_LIMIT_MAX | NPA_CLIENT_IMPULSE, 
  Clock_NPACreateMarkedClient,  /* Create client function */
  NULL                          /* Destroy client function */
};

const npa_resource_plugin Clock_NPANodeSPMPlugin = 
{
  npa_identity_update_fcn,
  /* Supported client types */
  0xffffffff,                   /* All client types supported */
  Clock_NPACreateMarkedClient,  /* Create client function */
  NULL                          /* Destroy client function */
};

/*
 * RPM Clock Driver NPA resource names.
 */
const char* const aszClockNPAResNames[] =
{
  [CLK_NPA_RES_CXO_IDX]         = "/xo/cxo",
  [CLK_NPA_RES_DCVS_IDX]        = "/clk/dcvs.ena",
  [CLK_NPA_RES_CPU_IDX]         = "/clk/cpu",
  [CLK_NPA_RES_SNOC_IDX]        = "/clk/snoc",
  [CLK_NPA_RES_SNOC_PIMEM_IDX]  = "/clk/pmem",
  [CLK_NPA_RES_CNOC_IDX]        = "/clk/cnoc",
  [CLK_NPA_RES_CNOC_PERIPH_IDX] = "/clk/cnoc_periph",
  [CLK_NPA_RES_BIMC_IDX]        = "/clk/bimc",
  [CLK_NPA_RES_IPA_IDX]         = "/clk/ipa",
  [CLK_NPA_RES_CE1_IDX]         = "/clk/ce1",
  [CLK_NPA_RES_AGGRE2_IDX]      = "/clk/agr2",
  [CLK_NPA_RES_SPM_IDX]         = "/clk/spm",
  [CLK_NPA_RES_MMAXI_IDX]       = "/clk/mmnoc_axi",
  [CLK_NPA_RES_QDSS_IDX]        = "/clk/qdss",
  [CLK_NPA_RES_SNOC_HS_IDX]     = "/clk/snoc_hs"
};
CORE_STATIC_VERIFY( CLK_NUM_ELEM(aszClockNPAResNames) == CLK_NPA_NUM_RESOURCES );

/*
 * Array of NPA resource definitions plus resource user data.
 *
 * See Clock_NPANodeGenericFunc() for relevant usage information.
 */
npa_resource_definition Clock_NPAResources[] =
{
  /* CXO */
  [CLK_NPA_RES_CXO_IDX] =
  {
    .units      = szClockNPAUnitEnable,
    .max        = CLK_RPM_NPA_ENABLE_MAX,
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED|NPA_RESOURCE_DRIVER_UNCONDITIONAL,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = 0,
        .pData            = NULL,
        .pmResDriverFunc  = Clock_NPANodeCXOFunc,
      }
    }
  },

  /* DCVS */
  [CLK_NPA_RES_DCVS_IDX] =
  {
    .units      = szClockNPAUnitEnable,
    .max        = CLK_RPM_NPA_ENABLE_MAX,
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = 0,
        .pData            = NULL,
        .pmResDriverFunc  = Clock_NPANodeDCVSEnaFunc,
      }
    }
  },

  /* RPM CPU */
  [CLK_NPA_RES_CPU_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_DEFAULT,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_CLK_SWITCH_EN),

        .pData            = &Clock_Resources.CPUClockResource,
        .pmResDriverFunc  = NULL,
      }
    }
  },

  /* SNOC */
  [CLK_NPA_RES_SNOC_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &Clock_NPANodeMaxPlugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.SNOCClockResource,
        .pmResDriverFunc  = Clock_SNOCHSSetFrequency,
      }
    }
  },

    /* SNOC-HS */
  [CLK_NPA_RES_SNOC_HS_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &Clock_NPANodeMaxPlugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.SNOCHSClockResource,
        .pmResDriverFunc  = Clock_SNOCHSSetFrequency,
      }
    }
  },

  
  /* SNOC PIMEM */
  [CLK_NPA_RES_SNOC_PIMEM_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_CLK_SWITCH_EN |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.SNOCPIMEMClockResource,
        .pmResDriverFunc  = NULL,
      }
    }
  },

  /* CNOC */
  [CLK_NPA_RES_CNOC_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_CLK_SWITCH_EN |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.CNOCClockResource,
        .pmResDriverFunc  = NULL,
      }
    }
  },
  
  /* CNOC_PERIPH */
  [CLK_NPA_RES_CNOC_PERIPH_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags               = (CLK_NPA_FLAG_DATA_CLK_RES |
                                  CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                                  CLK_NPA_FLAG_CLK_SWITCH_EN |
                             	  CLK_NPA_FLAG_CLK_GATE_EN |
                                  CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData                = &Clock_Resources.CNOCPeriphClockResource,
        .pmResDriverFunc      = NULL,
      }
    }
  },


  /* BIMC */
  [CLK_NPA_RES_BIMC_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &Clock_NPANodeMaxPlugin,
    .attributes = (NPA_RESOURCE_REMOTE_ACCESS_ALLOWED |
                    NPA_RESOURCE_DRIVER_UNCONDITIONAL),
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.BIMCResource,
        .pmResDriverFunc  = Clock_NPANodeBIMCFunc,
      }
    }
  },

  /* IPA */
  [CLK_NPA_RES_IPA_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &Clock_NPANodeIPAPlugin,    
    .attributes = (NPA_RESOURCE_REMOTE_ACCESS_ALLOWED |
                    NPA_RESOURCE_DRIVER_UNCONDITIONAL),
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData            = &Clock_Resources.IPAResource,
        .pmResDriverFunc  = Clock_NPANodeIPAFunc,
      }
    }
  },

  /* CE1 */
  [CLK_NPA_RES_CE1_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_CLK_SWITCH_EN |
                              CLK_NPA_FLAG_CLK_GATE_EN),

        .pData            = &Clock_Resources.CE1ClockResource,
        .pmResDriverFunc  = NULL,
      }
    }
  },

  /* Aggre2 */
  [CLK_NPA_RES_AGGRE2_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE |
                              CLK_NPA_FLAG_DCVS_GATE_EN),

        .pData                = &Clock_Resources.Aggre2Resource,
        .pmResDriverFunc      = Clock_NPANodeAggrFunc,
      }
    }
  },
  /* SPM */
  [CLK_NPA_RES_SPM_IDX] =
  {
    .units      = szClockNPAUnitEnable,
    .max        = CLK_RPM_NPA_ENABLE_MAX,
    .plugin     = &Clock_NPANodeSPMPlugin,
    .attributes = NPA_RESOURCE_DRIVER_UNCONDITIONAL,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags               = CLK_NPA_FLAG_DATA_CLK_RES,
        .pData                = &Clock_Resources.SPMClockResource,
        .pmResDriverFunc      = Clock_NPANodeSPMFunc,
      }
    }
  },

  /* MM AXI */
  [CLK_NPA_RES_MMAXI_IDX] =
  {
    .units      = szClockNPAUnitKHz,
    .max        = CLK_INV_MAX_FREQ_KHZ,   /* Fill in the max during init. */
    .plugin     = &Clock_NPANodeMaxPlugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = (CLK_NPA_FLAG_DATA_CLK_RES |
                              CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE ),

        .pData            = &Clock_Resources.MMAXIClockResource,
        .pmResDriverFunc  = Clock_NPANodeMMSSAXIFunc,
      }
    }
  },

  /* QDSS */
  [CLK_NPA_RES_QDSS_IDX] =
  {
    .units      = szClockNPAUnitState,
    .max        = CLOCK_QDSS_LEVEL_MAX_LEVEL,
    .plugin     = &npa_max_plugin,
    .attributes = NPA_RESOURCE_REMOTE_ACCESS_ALLOWED,
    .query_fcn  = Clock_NPAResourceQuery,

    /* Single-entry compound literal array for ease of declaration. */
    .data = (ClockNPAResDataType[])
    {
      {
        .nFlags           = CLK_NPA_FLAG_DATA_CLK_RES,
        .pData            = &Clock_Resources.QDSSResource,
        .pmResDriverFunc  = Clock_NPANodeQDSSFunc,
      }
    }
  }
};
CORE_STATIC_VERIFY( CLK_NUM_ELEM(Clock_NPAResources) == CLK_NPA_NUM_RESOURCES );


/*
 * Structure that holds RPM Clock Driver target context.
 */
Clock_TargCtxtType Clock_Resources =
{
  /*
   * Common clock driver NPA node.
   */
  .sNPAClkNode =
  {
    .name             = "/node/clk",
    .driver_fcn       = Clock_NPANodeGenericFunc,
    .attributes       = NPA_NODE_DEFAULT,
    .data             = NULL,

    .dependency_count = 0,
    .dependencies     = NULL,
    .resource_count   = CLK_NPA_NUM_RESOURCES,
    .resources        = Clock_NPAResources
  },

  /*
   * Clock resource declarations (variable-length clock arrays).
   */
  .CPUClockResource         = CLK_RESOURCE_DECL(1),
  .SNOCClockResource        = CLK_RESOURCE_DECL(1),
  .SNOCPIMEMClockResource   = CLK_RESOURCE_DECL(1),
  .CNOCClockResource        = CLK_RESOURCE_DECL(1),
  .CNOCPeriphClockResource  = CLK_RESOURCE_DECL(CLK_RES_CNOC_PERIPH_NUM_CLKS),
  .CE1ClockResource         = CLK_RESOURCE_DECL(CLK_RES_CE_NUM_CLKS),
  .HMSSAHBClockResource     = CLK_RESOURCE_DECL(1),
  .SNOCHSClockResource      = CLK_RESOURCE_DECL(1),
  .VSenseClockResource      = CLK_RESOURCE_DECL(CLK_RES_VSENSE_NUM_CLKS),

  .BIMCResource =
  {
    .sClockRes            = CLK_RESOURCE_DECL(1),
    .eBIMCState           = BIMC_ON,
    .bPCModeEn            = TRUE,
    .bPCDDRPHYModeEn      = TRUE,
    .bBIMCModemEnabled    = FALSE,
    .bBIMCAppsEnabled     = FALSE,
  },

  .IPAResource =
  {
    .sClockRes            = CLK_RESOURCE_DECL(1),
  },

  .Aggre2Resource =
  {
    .sClockRes            = CLK_RESOURCE_DECL(CLK_RES_AGGRE2_NUM_CLKS),
  },

  .MMAXIClockResource     =
  {
    .sClockRes            = CLK_RESOURCE_DECL(CLK_RES_MMSS_NUM_CLKS),
  },

  .QDSSResource =
  {
    .sClockRes            = CLK_RESOURCE_DECL(CLK_RES_QDSS_NUM_CLKS),
  }
};


/*=========================================================================
      Functions
==========================================================================*/
/*===========================================================================

  FUNCTION      Clock_WaitForClockGroupOn

  DESCRIPTION   Waits for an entire group of clocks to turn on.

  PARAMETERS    pClockResource  [in] - Clock resource to wait on.

  DEPENDENCIES  None.

  RETURN VALUE  Returns DAL_SUCCESS (aborts upon failure).

  SIDE EFFECTS  Sets clock resource's 'bClkGrpEnabled' to TRUE upon success.

===========================================================================*/
DALResult Clock_WaitForClockGroupOn
(
    ClockResourceType   *pClockResource
)
{
  uint32    nIdx;

  for ( nIdx = 0; nIdx < pClockResource->nNumClocks; nIdx++ )
  {
    CORE_DAL_VERIFY( Clock_WaitForClockOn(
          pClockResource->apClocks[nIdx], CLK_ON_WAIT_USEC ) );
  }

  pClockResource->bClkGrpEnabled = TRUE;
  return DAL_SUCCESS;
}


/*===========================================================================

  FUNCTION      Clock_EnableClockGroup

  DESCRIPTION   Enables an entire group of clocks.

  PARAMETERS    pClockResource  [in] - Clock resource to enable.
                bWaitForClockOn [in] - Set to TRUE to wait for clock ONs.

  DEPENDENCIES  None.

  RETURN VALUE  Returns DAL_SUCCESS (aborts upon failure).

  SIDE EFFECTS  If called with 'bWaitForClockOn' = TRUE, sets the clock 
                resource's 'bClkGrpEnabled' to TRUE upon success. Otherwise
                'bClkGrpEnabled' is left unmodified.

===========================================================================*/
DALResult Clock_EnableClockGroup
(
  ClockResourceType   *pClockResource,
  boolean              bWaitForClockOn
)
{
  uint32    nIdx;

  for ( nIdx = 0; nIdx < pClockResource->nNumClocks; nIdx++ )
  {
    CORE_DAL_VERIFY( Clock_EnableClockEx(
            (ClockIdType)pClockResource->apClocks[nIdx], FALSE ) );
  }

  if ( bWaitForClockOn )
  {
    Clock_WaitForClockGroupOn( pClockResource );
  }

  return DAL_SUCCESS;
}


/*===========================================================================

  FUNCTION      Clock_DisableClockGroup

  DESCRIPTION   Disables an entire group of clocks.

  PARAMETERS    pClockResource  [in] - Clock resource to disable.

  DEPENDENCIES  None.

  RETURN VALUE  Returns DAL_SUCCESS (aborts upon failure).

  SIDE EFFECTS  Sets clock resource's 'bClkGrpEnabled' to FALSE if the clock
                delegate's reference count is zero after the disable.

===========================================================================*/
DALResult Clock_DisableClockGroup
(
  ClockResourceType   *pClockResource
)
{
  uint32    nIdx;

  for ( nIdx = 0; nIdx < pClockResource->nNumClocks; nIdx++ )
  {
    CORE_DAL_VERIFY( Clock_DisableClock(
            (ClockIdType)pClockResource->apClocks[nIdx] ) );
  }

  pClockResource->bClkGrpEnabled =
      ( pClockResource->apClocks[CLK_RES_DELEGATE_IDX]->nReferenceCount > 0 );

  return DAL_SUCCESS;
}



uint32 Clock_SNOCHSSetClockSpeed
(
  ClockResourceType   *pClockResource,
  uint32              nFreqHz
)
{
  uint32  nFreqKHz  = 0, nSNOCHSState, nSNOCState, nNewSNOCState, nNewSNOCHSState;
  if(pClockResource == &Clock_Resources.SNOCClockResource)
  {
     nNewSNOCHSState = Clock_NPAResources[CLK_NPA_RES_SNOC_HS_IDX].handle->request_state;
     nNewSNOCState = nFreqHz/1000;
  }
  else
  {
     nNewSNOCState   = Clock_NPAResources[CLK_NPA_RES_SNOC_IDX].handle->request_state;
     nNewSNOCHSState = nFreqHz/1000;
  }

  Clock_SNOCVoteMatchSpeed(nNewSNOCState, nNewSNOCHSState, &nSNOCState, &nSNOCHSState);

  if(pClockResource == &Clock_Resources.SNOCClockResource)
  {
     nFreqKHz = nSNOCState;
     npa_assign_resource_state( Clock_NPAResources[CLK_NPA_RES_SNOC_HS_IDX].handle, nSNOCHSState );
  }
  else
  {
     nFreqKHz = nSNOCHSState;
     npa_assign_resource_state( Clock_NPAResources[CLK_NPA_RES_SNOC_IDX].handle, nSNOCState );
  }
 
   return nFreqKHz;
}




uint32 Clock_SNOCHSSetFrequency
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{

  ClockResourceType     *pClockResource;
  ClockNPAResDataType   *pResData;
  uint32  nFreqKHz;
  
  pResData = (ClockNPAResDataType *)pResource->definition->data;
  pClockResource = (ClockResourceType *)pResData->pData;
 
  nFreqKHz = Clock_SNOCHSSetClockSpeed(pClockResource, nState*1000);
  return nFreqKHz;
}


void Clock_MatchCnocPeriph(uint32 nNewFreqKHz)
{

  /* Match CNOC_Periph Domain Performance with CNOC */

  if ( CNOCPeriphHandle == NULL )
  {
    CNOCPeriphHandle = npa_create_sync_client("/clk/cnoc_periph", "ClockRPM", NPA_CLIENT_REQUIRED );
    CORE_VERIFY_PTR( CNOCPeriphHandle );
  } 
  if(nNewFreqKHz == 75*1000)
  {
     nNewFreqKHz = 100*1000;
  }
  npa_issue_required_request( CNOCPeriphHandle, nNewFreqKHz );

}


/*===========================================================================

  FUNCTION      Clock_SetClockSpeed

  DESCRIPTION   Sets the clock frequency for a clock resource's clock domain
                and updates the clock resource state.

                Note that BIMC frequency switches should performed via
                Clock_BIMCSetFrequency().

  PARAMETERS    pClockResource [in] - Clock resource to switch.
                nFreqHz        [in] - New clock speed (in Hz).

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in Hz).

  SIDE EFFECTS  None.

===========================================================================*/
uint32 Clock_SetClockSpeed
(
  ClockResourceType   *pClockResource,
  uint32              nFreqHz
)
{
  uint32              nLvl;
  uint32              nNewFreqHz;
  ClockMuxConfigType  *pNewConfig;
  ClockNodeType       *pClock     = CLK_DELEGATE(pClockResource);

  /* If SNOC below 19.2MHz, set it to 19.2MHz for SYS_NOC_HS_AXI to be at 37.5MHz */
  /*it is not required as the HS_SNOC is corner matched to SNOC*/
  
#if 0
  if ( (pClockResource == &Clock_Resources.SNOCClockResource) &&
       (nFreqHz < XO_FREQ_HZ) )
  {
    nFreqHz = XO_FREQ_HZ;
  }
#endif

  /* Find new clock config that match to setting frequency */
  pNewConfig = &pClock->pDomain->pBSPConfig[pClockResource->nMinLevel];
  for ( nLvl = pClockResource->nMinLevel; nLvl < pClockResource->nMaxLevel; nLvl++ )
  {
    // Check frequency that supported in this HW version only
    if ( Clock_IsBSPSupported(pNewConfig) &&
         (nFreqHz <= pNewConfig->nFreqHz) )
    {
      break;
    }

    pNewConfig++;
  }
  nNewFreqHz = pNewConfig->nFreqHz;

  /* Do nothing if clock is already in the same as active config */
  if ( pNewConfig == pClock->pDomain->pActiveMuxConfig )
  {
    return nNewFreqHz;
  }


  /*
   * If BIMC clock, need to call special BIMC set frequency for set voltage before call
   * pre_ddr_clock_switch 
   */
  if ( pClockResource == &Clock_Resources.BIMCResource.sClockRes )
  {
    Clock_BIMCSetClockConfig( pClock, pNewConfig );
  }
  else
  {
    Clock_SetClockConfig( pClock, pNewConfig );
  }

  pClockResource->nPrevLevel  = pClockResource->nCurLevel;
  pClockResource->nCurLevel   = nLvl;

    
  /* Match CNOC_Periph Domain Performance with CNOC */
  if ( pClockResource == &Clock_Resources.CNOCClockResource )
  {
    Clock_MatchCnocPeriph(nNewFreqHz/1000);
  }

  return nNewFreqHz;
}


/*===========================================================================

  FUNCTION      Clock_InitNPA

  DESCRIPTION   This function is used setup NPA node to all the clock
                resource
                  
  PARAMETERS    None.

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
__attribute__((section("clk_cram_reclaim_pool")))
DALResult Clock_InitNPA
(
  void
)
{
  uint32  nIdx, nFlags, nMaxFreqKHz;
  boolean bClockResData, bGenericInitMaxAct, bDcvsGateEn;
  boolean bResQueryFunc, bResDriverFunc;
  boolean bGenericClkAction, bResClkPostPreFunc;

  npa_resource_definition *pNPARes;
  ClockNPAResDataType     *pResData;
  ClockResourceType       *pClkRes;
  ClockNodeType           *pClock;
  npa_resource_state      naInitReqs[CLK_NPA_NUM_RESOURCES];
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Perform sanity checks on NPA target context and get initial/max       */
  /* states for each resource.                                             */
  /*-----------------------------------------------------------------------*/
  pNPARes = &Clock_NPAResources[0];
  for ( nIdx = 0; nIdx < Clock_Resources.sNPAClkNode.resource_count; nIdx++ )
  {
    /* The compiler doesn't allow this linkage at run-time... */
    pNPARes->name = aszClockNPAResNames[nIdx];

    /* Check for holes in the NPA resource array. */
    if ( pNPARes->data == NULL )
    {
      return DAL_ERROR;
    }

    /* Perform sanity checks on the resource's configuration. */
    pResData = (ClockNPAResDataType *)pNPARes->data;
    nFlags = pResData->nFlags;

    bClockResData         = CLK_FLAG_ON(nFlags, CLK_NPA_FLAG_DATA_CLK_RES);
    bGenericInitMaxAct    = CLK_FLAG_ON(nFlags, CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE);
    bDcvsGateEn           = CLK_FLAG_ON(nFlags, CLK_NPA_FLAG_DCVS_GATE_EN);

    bGenericClkAction     = (CLK_FLAG_ON(nFlags, CLK_NPA_FLAG_CLK_SWITCH_EN) |
                              CLK_FLAG_ON(nFlags, CLK_NPA_FLAG_CLK_GATE_EN));

    bResQueryFunc         = (pNPARes->query_fcn != NULL);
    bResDriverFunc        = (pResData->pmResDriverFunc != NULL);

    bResClkPostPreFunc    = ((pResData->pmPreClkSwitchFunc != NULL) |
                              (pResData->pmPostClkSwitchFunc != NULL));

    /* If an NPA resource has a clock resource, its pData can't be NULL. */
    if ( bClockResData && (pResData->pData == NULL) )
    {
      return DAL_ERROR;
    }

    /*
     * Generic NPA active/max state initialization, DCVS gating, generic clock
     * operations, and NPA clock queries all require a clock resource.
     */
    if ( bGenericInitMaxAct || bDcvsGateEn || (!bResDriverFunc) || bResQueryFunc )
    {
      assert( bClockResData );
    }

    /* 
     * Clock NPA resource's must use a resource-specific driver function or use
     * at least one generic clock action.
     */
    assert( bGenericClkAction != bResDriverFunc );

    /*
     * If an NPA resource has a resource-specific driver function, it won't
     * call any pre/post generic switch functions. 
     */
    if ( bResDriverFunc )
    {
      assert( !bResClkPostPreFunc );
    }

    /*
     * Get the initial/max state from the clock resource if it exists.
     */
    if ( bGenericInitMaxAct )
    {
      pClkRes = (ClockResourceType *)pResData->pData;
      pClock  = CLK_DELEGATE(pClkRes);

      nMaxFreqKHz = (pClock->pDomain->pBSPConfig[pClkRes->nMaxLevel].nFreqHz / 1000);
      if ( pNPARes->max == CLK_INV_MAX_FREQ_KHZ )
      {
        pNPARes->max = nMaxFreqKHz;
      }
      else
      {
        /* Cap the max within the original resource max. */
        pNPARes->max = MIN(pNPARes->max, nMaxFreqKHz);
      }

      if ( pClock->nReferenceCount )
      {
        naInitReqs[nIdx] =
            (pClock->pDomain->pBSPConfig[pClkRes->nCurLevel].nFreqHz / 1000);
      }
      else
      {
        naInitReqs[nIdx] = 0;
      }
    }

    pNPARes++;
  }

  /* Set initial request states for non-generic-init NPA resources. */
  naInitReqs[CLK_NPA_RES_CXO_IDX]     = 1;
  naInitReqs[CLK_NPA_RES_DCVS_IDX]    = (pDrvCtxt->bDCVSEnabled) ? 1 : 0;
  naInitReqs[CLK_NPA_RES_SPM_IDX]     = 0;
  naInitReqs[CLK_NPA_RES_QDSS_IDX]    = CLOCK_QDSS_LEVEL_OFF;

  pClock = CLK_DELEGATE(&Clock_Resources.BIMCResource.sClockRes);
  naInitReqs[CLK_NPA_RES_BIMC_IDX]    = pClock->pDomain->pBSPConfig[Clock_Resources.BIMCResource.sClockRes.nCurLevel].nFreqHz / 1000;
  

  pClock = CLK_DELEGATE(&Clock_Resources.Aggre2Resource.sClockRes);
  naInitReqs[CLK_NPA_RES_AGGRE2_IDX]  = (pClock->nReferenceCount > 0);

  /*-----------------------------------------------------------------------*/
  /* Define the common clock driver NPA node.                              */
  /*-----------------------------------------------------------------------*/
  npa_define_node(&Clock_Resources.sNPAClkNode, naInitReqs, NULL);

  /*-----------------------------------------------------------------------*/
  /* Set call back function for tracking CX rail changes.                  */
  /*-----------------------------------------------------------------------*/
  Clock_Resources.nCXRailID = rail_id("vddcx");
  railway_set_callback(Clock_Resources.nCXRailID, RAILWAY_PRECHANGE_CB,  Clock_CXRailPreChangedCB,  NULL);
  railway_set_callback(Clock_Resources.nCXRailID, RAILWAY_POSTCHANGE_CB, Clock_CXRailPostChangedCB, NULL);

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/
  return DAL_SUCCESS;

} /* END Clock_InitNPA */


/*===========================================================================

  FUNCTION      Clock_NPANodeCXOFunc

  DESCRIPTION   This function is used for enable/disable CXO.
                Currently, sleep code will handle CXO enable/disable
  
  PARAMETERS    pResource [in] - CXO Resource
                nState [in]    - Request state.

  DEPENDENCIES  Requires max state of 1.

  RETURN VALUE  New CXO state

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeCXOFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  extern void HAL_clk_CLKREF_restore ( boolean bEnable );
  sleep_update_xo_stats(pResource->clients, hClient); 

  if(hClient->type == NPA_CLIENT_REQUIRED)
  {
    /* Handle CLKREF based on Modem's XO Vote. */
    if(strcmp(hClient->name, "MPSS") == 0)
    {
      /* Get the modem's xo request */
      if (NPA_PENDING_REQUEST(hClient).state == 0)
      {
        HAL_clk_CLKREF_restore ( FALSE );
      }
      else
      {
        HAL_clk_CLKREF_restore ( TRUE );
      }
    }
  }
 
  /* Sleep code will handle CXO enable/disable */
  return nState;
}


#ifdef DCVS_ENABLE
/*===========================================================================

  FUNCTION      Clock_DcvsEnaSetClockSpeed

  DESCRIPTION   Helper function that sets clock speed for an NPA resource for
                DCVS enable/disable.
  
  PARAMETERS    nIdx        [in] - NPA resource index.
                pNPARes     [in] - NPA resource.
                pClkRes     [in] - NPA resource's clock resource.
                nNewFreqHz  [in] - New clock frequency (in Hz).

  DEPENDENCIES  The NPA group must have a clock resource.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static inline void Clock_DcvsEnaSetClockSpeed
(
  uint32                    nIdx,
  npa_resource_definition   *pNPARes,
  ClockResourceType         *pClkRes,
  uint32                    nNewFreqHz
)
{
  uint32                   nFreqKHz;

  /* Set clock speed. */
  if ( nIdx == CLK_NPA_RES_BIMC_IDX )
  {
    nFreqKHz = Clock_BIMCSetFrequency( &Clock_Resources.BIMCResource,
                                      (nNewFreqHz / 1000) );
  }
  else if(nIdx == CLK_NPA_RES_SNOC_IDX || nIdx == CLK_NPA_RES_SNOC_HS_IDX )
  {
    nFreqKHz =  Clock_SNOCHSSetClockSpeed( pClkRes, nNewFreqHz );
  }
  else
  {
    nFreqKHz = ( Clock_SetClockSpeed( pClkRes, nNewFreqHz ) / 1000 );
  }

  /* Inform NPA new clock speed has been updated */
  npa_assign_resource_state( pNPARes->handle, nFreqKHz );
}


/*===========================================================================

  FUNCTION      Clock_EnableDCVS

  DESCRIPTION   Helper function used to enable/disable RPM DCVS. When DCVS is
                enabled, all DCVS-gated resources which have already been 
                voted upon are set to their requested state. When DCVS is
                disabled, all DCVS-gated resources are set to their max
                frequency (not intended for POR usage).
  
  PARAMETERS    bEnable [in]  - New enable state for RPM DCVS.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
static inline void Clock_EnableDCVS( boolean bEnable )
{
  uint32                    nIdx, nFreqHz;
  npa_resource_definition   *pNPARes;
  ClockNPAResDataType       *pResData;
  ClockResourceType         *pClkRes;
  ClockNodeType             *pClock;

  /* Scale all appropriate unscaled nodes. */
  pNPARes = &Clock_NPAResources[0];
  for ( nIdx = 0; nIdx < Clock_Resources.sNPAClkNode.resource_count; nIdx++ )
  {

    if(nIdx == CLK_NPA_RES_AGGRE2_IDX)
    {
      pNPARes++;
      continue;
    }

    pResData = (ClockNPAResDataType *)pNPARes->data;

    /* Check if node is DCVS-gated and already voted upon. */
    if ( (pResData->nFlags & CLK_NPA_FLAG_DCVS_GATE_EN) &&
          CLK_NPA_RES_VOTED_UPON(pNPARes) )
    {
      pClkRes = (ClockResourceType *)pResData->pData;

      if ( bEnable )
      {
        /*
         * Get requested frequency in Hz. Protect against 32-bit overflow since
         * a client might request max-int to get highest supported frequency.
         */
        nFreqHz = CLK_KHZ_TO_HZ_UINT32(pNPARes->handle->request_state);
      }
      else
      {
        /* Get max frequency in Hz. */
        pClock = CLK_DELEGATE(pClkRes);
        nFreqHz = pClock->pDomain->pBSPConfig[pClkRes->nMaxLevel].nFreqHz;
      }

      /* Switch clock and update NPA active state. */
      Clock_DcvsEnaSetClockSpeed( nIdx, pNPARes, pClkRes, nFreqHz );
    }

    pNPARes++;
  }
}
#endif /* DCVS_ENABLE */


/*===========================================================================

  FUNCTION      Clock_NPANodeDCVSEnaFunc

  DESCRIPTION   This function is used for enable or disable bus scaling.
                Disable - Bus clocks will be run at max
                Enable - Bus clocks will be set at the previous state request
  
  PARAMETERS    pResource [in] - NPA resource
                hClient [in]   - NPA client handle
                nState [in]    - Request frequency.

  DEPENDENCIES  Requires max state of 1.

  RETURN VALUE  DCVS enable state (bool).

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeDCVSEnaFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
#ifdef DCVS_ENABLE
  ClockDrvCtxt      *pDrvCtxt = Clock_GetDrvCtxt();

  pDrvCtxt->bDCVSEnabled = nState;
  Clock_EnableDCVS( nState );
#endif

  return nState;
}


/*===========================================================================

  FUNCTION      Clock_NPANodeGenericFunc

  DESCRIPTION   Clock driver function for clock operations. General flow:

    (1) Performs initial operations common to all clock driver NPA resources.
    (2) If a resource-specific clock switch function is present it is called
        and its return value is returned.
              -ELSE-
    (3) Performs generic clock switch actions:
        (a) Calls a pre-switch function if present.
        (b) Disables the resource's clocks if the resource is configured
            to do so, the clock delegate has a reference count of one, and
            the new aggregated resource state is zero.
        (c) Performs a generic clock domain switch if the resource is
            configured to do so.
        (d) Enables the resource's clocks if the resource is configured
            to do so, the clock delegate has a reference count of zero, and
            the new aggregated resource state is non-zero.
        (e) Calls a post-switch function if present.

  PARAMETERS    pResource [in] - NPA resource.
                hClient   [in] - NPA client handle.
                nState    [in] - Aggregated request state.

  DEPENDENCIES  None.

  RETURN VALUE  New NPA resource state.

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeGenericFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  ClockNPAResDataType   *pResData;
  ClockResourceType     *pClockRes;
  boolean               bClkGateEn;
  ClockDrvCtxt          *pDrvCtxt;
  npa_resource_state    nNewState;
  npa_resource_state    nRet;
  uint32                nNewFreqHz;
  boolean               bDisabledClockGroup = FALSE;
  uint32                nRefCount = 0; // initialized to appease the compiler

  /* (1) Short-circuit init driver function invocations. */
  if ( hClient->type == NPA_CLIENT_INITIALIZE )
  {
    return nState;
  }

  pResData = (ClockNPAResDataType *)pResource->definition->data;

  /* Don't scale if DCVS is disabled. */
  if ( pResData->nFlags & CLK_NPA_FLAG_DCVS_GATE_EN )
  {
    pDrvCtxt = Clock_GetDrvCtxt();
    if ( !pDrvCtxt->bDCVSEnabled )
    {
      /* Just return the active NPA state. */
      return pResource->active_state;
    }
  }

  /* (2) Branch into resource-specific clock switch if available. */
  if ( pResData->pmResDriverFunc != NULL )
  {
    return pResData->pmResDriverFunc(pResource, hClient, nState);
  }

  /* (3a) Otherwise perform any resource-specific pre-switch operations. */
  if ( pResData->pmPreClkSwitchFunc != NULL )
  {
    if ( pResData->pmPreClkSwitchFunc(pResource, hClient, nState, &nNewState) )
    {
      /* Allow pre-switch operation to optionally return a modified state. */
      nState = nNewState;
    }
  }

  /* (3b) Disable the clocks if required. */
  pClockRes = (ClockResourceType *)pResData->pData;
  bClkGateEn = CLK_FLAG_ON(pResData->nFlags, CLK_NPA_FLAG_CLK_GATE_EN);
  if ( bClkGateEn )
  {
    nRefCount = CLK_DELEGATE(pClockRes)->nReferenceCount;

    if ( (nState == 0) && (nRefCount == 1) )
    {
      Clock_DisableClockGroup( pClockRes );
      bDisabledClockGroup = TRUE;
    }
  }

  /* (3c) Switch the clock domain frequency if required. */
  if ( pResData->nFlags & CLK_NPA_FLAG_CLK_SWITCH_EN )
  {
    nNewFreqHz = Clock_SetClockSpeed( pClockRes, (nState * 1000) );

    if ( bDisabledClockGroup )
    {
      nRet = 0;
    }
    else
    {
      nRet = (nNewFreqHz / 1000);
    }
  }
  else
  {
    /* No clock frequency switch occurred. */
    nRet = nState;
  }

  /* (3d) Enable the clocks if required. */
  if ( bClkGateEn )
  {
    if ( (nState != 0) && (nRefCount == 0) )
    {
      Clock_EnableClockGroup( pClockRes, TRUE );
    }
  }

  /* (3e) Perform any resource-specific post-switch operations. */
  if ( pResData->pmPostClkSwitchFunc != NULL )
  {
    if ( pResData->pmPostClkSwitchFunc(pResource, hClient, nState, &nNewState) )
    {
      /* Allow post-switch operation to optionally return a modified state. */
      nRet = nNewState;
    }
  }

  return nRet;
}


/*===========================================================================

  FUNCTION      Clock_NPANodeBIMCFunc

  DESCRIPTION   Function for switching BIMC clock.
  
  PARAMETERS    pResource [in] - NPA resource
                hClient [in]   - NPA client handle
                nState [in]    - Request frequency (KHz).

  DEPENDENCIES  Requires 'Clock_NPANodeBIMCPlugin' NPA plugin.

  RETURN VALUE  New clock speed (in KHz).

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeBIMCFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  BIMCResourceType  *pBimcRes     = &Clock_Resources.BIMCResource;

  /* Do not modify all BIMC clock frequencies if requested max state is not new */
  if ( nState == pResource->active_state )
  {
    return nState;
  }

  return Clock_BIMCSetFrequency( pBimcRes, nState );
}


/*===========================================================================

  FUNCTION      Clock_NPANodeIPAFunc

  DESCRIPTION   This NPA call-back function is using for scaling IPA clocks.
  
  PARAMETERS    pResource [in] - NPA resource
                hClient [in]   - NPA client handle
                nState [in]    - Request frequency.

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in KHz).

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeIPAFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  static boolean     bMpssPlacedNonZeroVote = FALSE;
  IPAResourceType   *pIpaRes    = &Clock_Resources.IPAResource;
  ClockResourceType *pIpaClkRes = &pIpaRes->sClockRes;
  ClockNodeType     *pIpaClock  = pIpaClkRes->apClocks[0];
  uint32             nNewFreqKHz;

  if ( nState == 0 )
  {
    if ( pIpaRes->bEnabled )
    {
      if ( bMpssPlacedNonZeroVote )
      {
        /* Set IPA clock to LOW SVS  rate if at XO for improving speed */
        #if 1
         if(pIpaClkRes->nCurLevel == 0) /*XO Level*/
         {
            Clock_SetClockSpeed( pIpaClkRes, 375 * 100 * 1000);
         }
         #endif
         //Clock_SetClockSpeed( pIpaClkRes, 150000000);
         HAL_clk_IPAGating(TRUE);
#if 0
        Clock_DisablePowerDomain( Clock_Resources.IPAResource.nIPAPowerID );
#endif
      }

      Clock_DisableClock( (ClockIdType)pIpaClock );
      pIpaRes->bEnabled = FALSE;

      /* Release BIMC and Aggre2 NOC vote */
      npa_complete_request( Clock_Resources.IPAResource.BIMCHandle ); 
      npa_complete_request( Clock_Resources.IPAResource.Aggre2Handle ); 
    }

    nNewFreqKHz = 0;
  }
  else
  {
    if ( !pIpaRes->bEnabled )
    {
      /* Vote for BIMC and Aggre2 NOC before turning IPA clocks ON */ 
      npa_issue_required_request( Clock_Resources.IPAResource.BIMCHandle, 1 );  
      npa_issue_required_request( Clock_Resources.IPAResource.Aggre2Handle, 1 );  

      Clock_EnableClockEx( (ClockIdType)pIpaClock, FALSE );
      if ( bMpssPlacedNonZeroVote )
      {
        /* Set IPA clock to requested  rate to improve restoring IPA speed */
        //Clock_SetClockSpeed( pIpaClkRes, 150000000);
        Clock_SetClockSpeed( pIpaClkRes, nState * 1000);
        HAL_clk_IPAGating(FALSE);
        //Clock_EnablePowerDomain( Clock_Resources.IPAResource.nIPAPowerID, TRUE );
      }
      pIpaRes->bEnabled = TRUE;
    }

    nNewFreqKHz = Clock_SetClockSpeed( pIpaClkRes, nState * 1000) / 1000;
  }

  /* Check for first non-zero vote from MPSS. */
  if ( (!bMpssPlacedNonZeroVote) &&
       CLK_NPA_NODE_CLIENT_ID_EQ(hClient, CLK_NPA_NODE_RES_DATA_MPSS_REQ) &&
      (NPA_PENDING_REQUEST(hClient).state != 0) )
  {
    /* Enable the full IPA power domain save/restore sequence. Do this after
     * fulfilling the first non-zero MPSS IPA request, since save/restore
     * requires handshake from IPA uC (which is booted by Modem).
     */
    bMpssPlacedNonZeroVote = TRUE;
  }

  return nNewFreqKHz;
}


/*===========================================================================

  FUNCTION      Clock_SetQDSSDebugSpeed

  DESCRIPTION   This function is used for setting QDSS speed according to 
                CX level.

  PARAMETERS    settings      [in] - Current CX rail setting.
                pQDSSResource [in] - QDSS resource.
                bForceSwitch  [in] - Set to TRUE to prevent short-circuit.

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_SetQDSSDebugSpeed
(
  const railway_settings  *settings,
  QDSSResourceType        *pQDSSResource,
  boolean                 bForceSwitch
)
{
  ClockQDSSSpeedType  eNewLevel;
  ClockResourceType   *pClockRes = &pQDSSResource->sClockRes;

  /* Find the new QDSS level to switch to. */
  if ( settings->mode >= CLOCK_VREG_LEVEL_NOMINAL )
  {
    eNewLevel = CLOCK_QDSS_SPEED_NOMINAL;
  }
  else if ( settings->mode >= CLOCK_VREG_LEVEL_LOW )
  {
    eNewLevel = CLOCK_QDSS_SPEED_LOW;
  }
  else
  {
    eNewLevel = CLOCK_QDSS_SPEED_LOW_MINUS;
  }

  if ( bForceSwitch || (pClockRes->nCurLevel != eNewLevel) )
  {
    Clock_SetQDSSClocks(pQDSSResource, eNewLevel);
  }
}


/*===========================================================================

  FUNCTION      Clock_CXRailPreChangedCB

  DESCRIPTION   This callback function is invoked before CX voltage changed.
                Use this function for reducing QDSS clock speed before CX 
                voltage drop.

  PARAMETERS    settings [in] - Current CX rail setting
                cookie   [in] - Not used

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_CXRailPreChangedCB(const railway_settings *settings, void *cookie)
{
  QDSSResourceType    *pQDSSResource = &Clock_Resources.QDSSResource;

  if ( Clock_Resources.nCXVReg > settings->mode )
  {
    /* Only allow VDDCX level tracking in "DEBUG" mode */
    if( pQDSSResource->nQDSSCurrLevel == CLOCK_QDSS_LEVEL_DEBUG)
    {
      Clock_SetQDSSDebugSpeed( settings, pQDSSResource, FALSE );
    }
    
    /* If VSense clocks are enable, track and drop frequency before the voltage is about to drop */
    if ( Clock_Resources.VSenseClockResource.bClkGrpEnabled )
    {
      Clock_SetVSenseFrequency( (ClockVRegLevelType)settings->mode);
    }
  }
}


/*===========================================================================

  FUNCTION      Clock_CXRailPostChangedCB

  DESCRIPTION   This callback function is invoked after CX voltage changed.
                Use this function for increasing QDSS clock speed after CX 
                voltage increased.

  PARAMETERS    settings [in] - Current CX rail setting
                cookie   [in] - Not used

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_CXRailPostChangedCB(const railway_settings *settings, void *cookie)
{
  QDSSResourceType    *pQDSSResource = &Clock_Resources.QDSSResource;

  if ( Clock_Resources.nCXVReg < settings->mode )
  {
    /* Only allow VDDCX level tracking in "DEBUG" mode */
    if( pQDSSResource->nQDSSCurrLevel == CLOCK_QDSS_LEVEL_DEBUG)
    {
      Clock_SetQDSSDebugSpeed( settings, pQDSSResource, FALSE );
    }
    
    /* If VSense clocks are enable, track and drop frequency before the voltage is about to drop */
    if ( Clock_Resources.VSenseClockResource.bClkGrpEnabled )
    {
      Clock_SetVSenseFrequency( (ClockVRegLevelType)settings->mode);
    }
  }

  /* Record the new CX level. */
  Clock_Resources.nCXVReg = (ClockVRegLevelType)settings->mode;
}


/*===========================================================================

  FUNCTION      Clock_ToggleQDSSClocks

  DESCRIPTION   Toggles the QDSS clocks which are toggle-able.

  PARAMETERS    pQdssClkRes   [in] - QDSS clock resource.
                bQdssOn       [in] - ON/OFF selection.

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_ToggleQDSSClocks
(
  ClockResourceType     *pQdssClkRes,
  boolean               bQdssOn
)
{
  /* Do nothing if QDSS clocks are already at requested state */
  if ( pQdssClkRes->bClkGrpEnabled == bQdssOn )
  {
    return;
  }

  /* Toggle the QDSS clocks that are toggle-able. */
  if ( bQdssOn )
  {
    /*
     * Enable each QDSS clock, but don't wait for clocks to turn on since the
     * SSC clocks may not turn on until other dependencies are fulfilled.
     */
    Clock_EnableClockGroup(pQdssClkRes, FALSE);

    /* Manually record that the QDSS clock group was enabled. */
    pQdssClkRes->bClkGrpEnabled = TRUE;
  }
  else
  {
    Clock_DisableClockGroup(pQdssClkRes);
  }
}


/*===========================================================================

  FUNCTION      Clock_SetQDSSClocks

  DESCRIPTION   Sets the QDSS clock frequencies. Railway requests are placed
                manually here in order to support 'CLOCK_QDSS_LEVEL_DEBUG'
                mode, where QDSS frequency follows CX railway level.

  PARAMETERS    pQDSSResource [in] - QDSS resource.
                eSpeed        [in] - New QDSS speed.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
void Clock_SetQDSSClocks
(
  QDSSResourceType    *pQDSSResource,
  ClockQDSSSpeedType  eSpeed
)
{
  ClockDrvCtxt        *pDrvCtxt   = Clock_GetDrvCtxt();
  ClockResourceType   *pClockRes  = &pQDSSResource->sClockRes;
  ClockNodeType       **apClocks  = pClockRes->apClocks;

  /* Get QDSS clock/config handles. */
  ClockNodeType       *pTraceClk  = apClocks[CLK_RES_QDSS_TRACE_IDX];
  ClockMuxConfigType  *pTraceCfg  = &pTraceClk->pDomain->pBSPConfig[eSpeed];

  ClockNodeType       *pTsctrDiv2Clk  = apClocks[CLK_RES_QDSS_TCSTR_DIV2_IDX];
  ClockMuxConfigType  *pTsctrDiv2Cfg  = &pTsctrDiv2Clk->pDomain->pBSPConfig[eSpeed];

  ClockNodeType       *pStmClk  = apClocks[CLK_RES_QDSS_STM_IDX];
  ClockMuxConfigType  *pStmCfg  = &pStmClk->pDomain->pBSPConfig[eSpeed];

  ClockNodeType       *pTrigClk  = apClocks[CLK_RES_QDSS_TRIG_IDX];
  ClockMuxConfigType  *pTrigCfg  = &pTrigClk->pDomain->pBSPConfig[eSpeed];

  /* Manually set QDSS voltage based on the QDSS mode and CX railway level. */
  if ( pQDSSResource->nQDSSCurrLevel == CLOCK_QDSS_LEVEL_DEBUG )
  {
    /* QDSS will stay within CX limits--relinquish its current request. */
    Clock_VoltageTerminateRequest(
        pDrvCtxt,
        &pQDSSResource->nQDSSVoltageLevel,
        FALSE ); 
  }
  else
  {
    Clock_VoltageRequest(
        pDrvCtxt,
        &pQDSSResource->nQDSSVoltageLevel,
        pTraceCfg->eVRegLevel,
        FALSE );
  }

  /* Set QDSS Trace Speed */
  Clock_SetClockConfig( pTraceClk,
                        pTraceCfg );

  /* Set QDSS AT Speed (untoggle-able clock) */
  Clock_SetClockConfig( pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_SYS_NOC_AT_IDX],
                        &pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_SYS_NOC_AT_IDX]->pDomain->pBSPConfig[eSpeed] );
  
  Clock_SetClockConfig( pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_BIMC_AT_IDX],
                        &pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_BIMC_AT_IDX]->pDomain->pBSPConfig[eSpeed] );
  
  Clock_SetClockConfig( pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_LPASS_AT_IDX],
                        &pQDSSResource->pQDSSATClkGroup[CLK_RES_QDSS_LPASS_AT_IDX]->pDomain->pBSPConfig[eSpeed] );
    
  /* Set QDSS TSCTR Speed */
  Clock_SetClockConfig( pTsctrDiv2Clk,
                        pTsctrDiv2Cfg );

  /* Set QDSS STM Speed */
  Clock_SetClockConfig( pStmClk,
                        pStmCfg );

  /* Set QDSS Trig Speed */
  Clock_SetClockConfig( pTrigClk,
                        pTrigCfg );
    
  QDSSSTMSetTimestampFreq( pTsctrDiv2Cfg->nFreqHz );

  pClockRes->nCurLevel = eSpeed;
}


/*===========================================================================

  FUNCTION      Clock_ChangeQDSSLevel

  DESCRIPTION   Switches QDSS clocks to a new level.

  PARAMETERS    pQDSSResource [in] - QDSS resource.
                eCurLevel     [in] - (0=Off, 1=Debug, 2=High Speed)
                eNewLevel     [in] - (0=Off, 1=Debug, 2=High Speed)

  DEPENDENCIES  None.

  RETURN VALUE  New Level.

  SIDE EFFECTS  None.

===========================================================================*/
ClockQDSSLevelType Clock_ChangeQDSSLevel
(
  QDSSResourceType      *pQDSSResource,
  ClockQDSSLevelType    eCurLevel,
  ClockQDSSLevelType    eNewLevel
)
{
  ClockResourceType   *pClockRes = &pQDSSResource->sClockRes;

  /* Do nothing if it is already at the same level */
  if ( eCurLevel == eNewLevel )
    return eNewLevel;

  pQDSSResource->nQDSSCurrLevel = eNewLevel;

  /* Because V1 is using TRACECLKIN as the source to AT_CLK, it must be enabled
   * before clock switch and disabled after clock switch.  This is why Toggle
   * is now mixed into the cases */
  switch (eNewLevel)
  {
    case CLOCK_QDSS_LEVEL_OFF:
      Clock_SetQDSSClocks(pQDSSResource, CLOCK_QDSS_SPEED_XO);
      Clock_ToggleQDSSClocks (pClockRes, FALSE);
      break;

    case CLOCK_QDSS_LEVEL_DEBUG:
      Clock_ToggleQDSSClocks (pClockRes, TRUE);

      /* Set the QDSS clocks to match the VDDCX mode */
      railway_settings  settings;
      railway_get_current_settings(Clock_Resources.nCXRailID, &settings);
      Clock_SetQDSSDebugSpeed( &settings, pQDSSResource, TRUE );
      break;

    case CLOCK_QDSS_LEVEL_HSDEBUG:
      Clock_ToggleQDSSClocks (pClockRes, TRUE);
      Clock_SetQDSSClocks(pQDSSResource, CLOCK_QDSS_SPEED_NOMINAL);
      break;

    case CLOCK_QDSS_LEVEL_LOW:
      Clock_ToggleQDSSClocks (pClockRes, TRUE);
      Clock_SetQDSSClocks(pQDSSResource, CLOCK_QDSS_SPEED_LOW);
      break;

    case CLOCK_QDSS_LEVEL_LOW_MINUS:
      Clock_ToggleQDSSClocks (pClockRes, TRUE);
      Clock_SetQDSSClocks(pQDSSResource, CLOCK_QDSS_SPEED_LOW_MINUS);
      break;

    default:
      break;
  }

  return eNewLevel;
}


/*===========================================================================

  FUNCTION      Clock_NPANodeAggrFunc

  DESCRIPTION   Function for Aggre NOCs operations, which ignores the client vote
                and always keeps AS-IS

  PARAMETERS    pResource [in]  - NPA resource.
                hClient   [in]  - NPA client handle.
                nState    [in]  - Request state.

  DEPENDENCIES  Requires max state of 1.

  RETURN VALUE  Aggre NOC current state.

  SIDE EFFECTS  None.
===========================================================================*/
static npa_resource_state Clock_NPANodeAggrFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
)
{
  ClockNPAResDataType *pResData;
  AggreResourceType   *pAggreRes;
  ClockResourceType   *pAggreClkRes;
  boolean              bPCGateEn;
  
  pResData = (ClockNPAResDataType *)pResource->definition->data;
  pAggreRes = (AggreResourceType *)pResData->pData;
  pAggreClkRes = &pAggreRes->sClockRes;
  bPCGateEn = CLK_FLAG_ON(pResData->nFlags, CLK_NPA_FLAG_PC_GATE_EN);

  if ( nState == 0 )
  {
    if ( pAggreClkRes->bClkGrpEnabled )
    {
      if(bPCGateEn )
      {
        Clock_DisableClockGroup( pAggreClkRes );
        Clock_DisablePowerDomain( pAggreRes->nAggrePowerID );
      }

      /* Release SNOC vote */
      npa_complete_request( pAggreRes->SNOCHandle ); 
    }
  }
  else
  {
    if ( !pAggreClkRes->bClkGrpEnabled )
    {
      Clock_EnablePowerDomain( pAggreRes->nAggrePowerID, TRUE );
      Clock_EnableClockGroup( pAggreClkRes, TRUE );
    }
    /* Vote for SNOC */ 
    npa_issue_required_request( pAggreRes->SNOCHandle, nState );  
  }
  
  return nState;
}


/*===========================================================================

  FUNCTION      Clock_NPANodeQDSSFunc

  DESCRIPTION   This NPA node is for QDSS

  PARAMETERS    nState -(0=Off, 1=Debug, 2=High Speed)

  DEPENDENCIES  None.

  RETURN VALUE  The new active state for the resource.

  SIDE EFFECTS  None.

===========================================================================*/
npa_resource_state Clock_NPANodeQDSSFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState
)
{
  QDSSResourceType *pQDSSResource = &Clock_Resources.QDSSResource;

  /* Change QDSS clock to new level */
  pQDSSResource->nQDSSCurrLevel = 
      Clock_ChangeQDSSLevel (pQDSSResource, pQDSSResource->nQDSSCurrLevel, (ClockQDSSLevelType)nState);

  return nState;
}

/*===========================================================================

  FUNCTION      Clock_NPAResourceQuery

  DESCRIPTION   This function is called to get a list of supported clock frequencies.

  PARAMETERS    *pResource [in]  -- Pointer to the resource in question
                nId        [in]  -- ID of the query.  
                *pResult   [out] -- Pointer to the data to be filled by this function.  

  DEPENDENCIES  None.

  RETURN VALUE  npa_query_status 
                      - NPA_QUERY_SUCCESS, if query supported.
                      - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  SIDE EFFECTS  None.

===========================================================================*/
static npa_query_status Clock_NPAResourceQuery
(
  npa_resource   *pResource,
  unsigned int   nId,
  npa_query_type *pResult
)
{
  npa_query_status nStatus = NPA_QUERY_UNSUPPORTED_QUERY_ID;
  ClockResourceType   *pClockResource;
  ClockNodeType       *pClock;
  ClockPlanType       *pClockPlan;
  ClockMuxConfigType  *pNewConfig;
  uint32              index, nCfg;

  pClockResource = (ClockResourceType *)pResource->definition->data;
  pClock = CLK_DELEGATE(pClockResource);

  switch ( nId )
  {
  case CLOCK_NPA_QUERY_NUM_PERF_LEVELS:
    pNewConfig = pClock->pDomain->pBSPConfig;

    pResult->type = NPA_QUERY_TYPE_VALUE;
    
    // Loop to all BSP to find all supported BSP for this HW version
    nCfg = 0;
    for ( index = pClockResource->nMinLevel; index <= pClockResource->nMaxLevel; index++ )
    {
      if ( Clock_IsBSPSupported(&pNewConfig[index]) )
      {
        nCfg++;
      }
    }
    pResult->data.value = nCfg;
    nStatus = NPA_QUERY_SUCCESS;
    break;
    
  case CLOCK_NPA_QUERY_MIN_FREQ_KHZ:
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = pClock->pDomain->pBSPConfig[pClockResource->nMinLevel].nFreqHz / 1000;
    nStatus = NPA_QUERY_SUCCESS;
    break;
    
  case CLOCK_NPA_QUERY_ALL_FREQ_KHZ:
    pNewConfig = pClock->pDomain->pBSPConfig;

    pResult->type = NPA_QUERY_TYPE_REFERENCE;

    if ( pResult->data.reference == NULL )
    {
      nStatus = NPA_QUERY_UNKNOWN_RESOURCE;
    }
    else
    {
      pClockPlan = pResult->data.reference;
          
      // Loop to all BSP to find all supported BSP for this HW version
      nCfg = 0;
      for ( index = pClockResource->nMinLevel; index <= pClockResource->nMaxLevel; index++ )
      {
        if ( Clock_IsBSPSupported(&pNewConfig[index]) )
        {
          pClockPlan[nCfg].nFreqKHz   = (pNewConfig[index].nFreqHz / 1000); /* In KHz */
          pClockPlan[nCfg].eVRegLevel = pNewConfig[index].eVRegLevel;
          pClockPlan[nCfg].eMode      = (ClockDDRMode)pNewConfig[index].HALConfig.nM;
          nCfg++;
        }
      }
    
      nStatus = NPA_QUERY_SUCCESS;
    }
    break;
  
  case CLOCK_NPA_QUERY_SETTLING_TIME:
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = 0;
    nStatus = NPA_QUERY_SUCCESS;
    break;
  }

  return nStatus;
}
/*===========================================================================

  FUNCTION      Clock_NPASuppressibleMaxUpdate

  DESCRIPTION   Performs a modified MAX to ignore suppressible votes when
   they are the only votes present.
  
  PARAMETERS    resource [in] - The NPA resource being aggregated
                client [in] - The client that has changed state

  DEPENDENCIES  None.

  RETURN VALUE  Resource state

  SIDE EFFECTS  None.

===========================================================================*/
npa_resource_state Clock_NPASuppressibleMaxUpdate
( 
  npa_resource      *resource, 
  npa_client_handle  client
)
{
  npa_resource_state state;

  state = npa_max_update_fcn(resource, client);

  /* The standard npa_max_upate_fcn returns the max of suppressible and required:
   * The behavior we want is that suppressible votes are ignored if there are no
   * required votes.  So if required is 0, the state is 0.  If required is non-zero, 
   * then the standard MAX(suppressible, required) state is returned. */

  if( NPA_RESOURCE_REQUIRED_REQUEST(resource) == 0 ) return 0;
  return state;
}



/*===========================================================================

  FUNCTION      Clock_SetVSenseFrequency

  DESCRIPTION   Performs changing voltage sensing clock frequencies
  
  PARAMETERS    eVReg - Voltage level for setting frequencies

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_SetVSenseFrequency( ClockVRegLevelType eVReg )
{
  uint32              nLvl;
  ClockMuxConfigType  *pCfg;
  ClockResourceType   *pClockRes = &Clock_Resources.VSenseClockResource;
  ClockNodeType       **apClocks = pClockRes->apClocks;

  /* Map the voltage level to a VSense BSP config level. */
  if ( eVReg >= CLOCK_VREG_LEVEL_NOMINAL )
    nLvl = 2;
  else if ( eVReg >= CLOCK_VREG_LEVEL_LOW )
    nLvl = 1;
  else 
    nLvl = 0;

  /* Get the new clock config (shared among these non-ctrl VS clocks). */
  pCfg = &apClocks[CLK_RES_VSENSE_VDDA_IDX]->pDomain->pBSPConfig[nLvl];

  Clock_SetClockConfig( apClocks[CLK_RES_VSENSE_VDDA_IDX],  pCfg );
  Clock_SetClockConfig( apClocks[CLK_RES_VSENSE_VDDCX_IDX], pCfg );
  Clock_SetClockConfig( apClocks[CLK_RES_VSENSE_VDDMX_IDX], pCfg );
  Clock_SetClockConfig( apClocks[CLK_RES_VSENSE_MSS_IDX], pCfg );
}


/*===========================================================================

  FUNCTION      Clock_EnableVSenseClocks

  DESCRIPTION   This function is used for setting VSense clocks to enable
                or disable

  PARAMETERS    bEnable - TRUE  - Enable
                        - FALSE - Disable
  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
void Clock_EnableVSenseClocks( boolean bEnable )
{
  ClockResourceType   *pClockRes = &Clock_Resources.VSenseClockResource;

  /* Do nothing if the state is already the same */
  if ( bEnable == pClockRes->bClkGrpEnabled )
  {
    return;
  }

  if ( bEnable )
  {
    Clock_EnableClockGroup(pClockRes, TRUE);
    Clock_SetVSenseFrequency( Clock_Resources.nCXVReg );
  }
  else
  {
    Clock_SetVSenseFrequency( CLOCK_VREG_LEVEL_LOW_MINUS );
    Clock_DisableClockGroup(pClockRes);
  }
}


/*===========================================================================

  FUNCTION      Clock_NPACreateMarkedClient

  DESCRIPTION   Creates NPA node client with conditional markers.
  
  PARAMETERS    hClient [in] - handle to npa client

  DEPENDENCIES  Requires an unused client 'resource_data'.
                Requires that internal client names do not intersect with
                external "master" client names (e.g. "APSS").

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_NPACreateMarkedClient
(
  npa_client *hClient
)
{
  /* init resource data as marked as an "internal" client */
  uint32 nResData = CLK_NPA_NODE_RES_DATA_INTERNAL_CLIENT_FLAG;

  /* mark client based on client name */
  if(strcmp(hClient->name, "MPSS") == 0)
  {
    /* clear "internal" client flag for external MPSS master */
    nResData &= (~CLK_NPA_NODE_RES_DATA_INTERNAL_CLIENT_FLAG);

    if(hClient->type == NPA_CLIENT_REQUIRED)
    {
      /* set modem "required client" marker */
      nResData |= CLK_NPA_NODE_RES_DATA_MPSS_REQ;
    }
  }
  else if(strcmp(hClient->name, "APSS") == 0)
  {
    /* clear "internal" client flag for external APSS master */
    nResData &= (~CLK_NPA_NODE_RES_DATA_INTERNAL_CLIENT_FLAG);

    if(hClient->type == NPA_CLIENT_REQUIRED)
    {
      /* set APSS "required client" marker */
      nResData |= CLK_NPA_NODE_RES_DATA_APSS_REQ;
    }
  }
  else if((strcmp(hClient->name, "LPASS") == 0) ||
          (strcmp(hClient->name, "WCSS") == 0) ||
          (strcmp(hClient->name, "TZ") == 0) ||
          (strcmp(hClient->name, "ADSP") == 0) ||
          (strcmp(hClient->name, "CDSP") == 0))
  {
    /* clear "internal" client flag for all other external masters */
    nResData &= (~CLK_NPA_NODE_RES_DATA_INTERNAL_CLIENT_FLAG);
  }

  hClient->resource_data = (npa_user_data)nResData;
}


/*===========================================================================

  FUNCTION      Clock_NPANodeSPMFunc

  DESCRIPTION   This function is used for any activites necessary when a master
                changes between the active and sleep sets.
  
  PARAMETERS    pResource [in] - SPM Resource.
                nState [in]    - Request state.

  DEPENDENCIES  Requires 'npa_identity_update_fcn' update plugin.

  RETURN VALUE  The most recent SPM state.

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeSPMFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  BIMCResourceType  *pBimcRes     = &Clock_Resources.BIMCResource;
  extern void HAL_clk_SPMAPPSEnableBIMCPorts( boolean bEnable );
  extern void HAL_clk_EnableQ6BIMCPorts( boolean bEnable );
  extern void HAL_clk_ReduceQ6BIMCPorts( boolean bReduce );

  /* Handle APSS active/sleep state transition. */
  if ( CLK_NPA_NODE_CLIENT_ID_EQ(hClient, CLK_NPA_NODE_RES_DATA_APSS_REQ) )
  {
    /* Get the APSS client's pending BIMC frequency request */
    if ( nState == 0 )
    {
      if ( pBimcRes->bBIMCAppsEnabled )
      {
        Clock_SetClockSpeed(&Clock_Resources.HMSSAHBClockResource, 1200000);
        HAL_clk_SPMAPPSEnableBIMCPorts( FALSE );
        pBimcRes->bBIMCAppsEnabled = FALSE;
      }
    }
    else
    {
      if ( !pBimcRes->bBIMCAppsEnabled )
      {
        Clock_SetClockSpeed(&Clock_Resources.HMSSAHBClockResource, 19200000);
        HAL_clk_SPMAPPSEnableBIMCPorts( TRUE );
        pBimcRes->bBIMCAppsEnabled = TRUE;
      }
    }
  }

  /* Handle Modem active/sleep state transition. */
  if ( CLK_NPA_NODE_CLIENT_ID_EQ(hClient, CLK_NPA_NODE_RES_DATA_MPSS_REQ) )
  {
    /* Get the modem client's pending BIMC frequency request */
    if ( nState == 0 )
    {
      if ( pBimcRes->bBIMCModemEnabled )
      {
        HAL_clk_ReduceQ6BIMCPorts( TRUE );
        //HAL_clk_EnableQ6BIMCPorts( FALSE );
        pBimcRes->bBIMCModemEnabled = FALSE;
        npa_issue_required_request(CNOCHandle, 0);
      }
    }
    else
    {
      if ( !pBimcRes->bBIMCModemEnabled )
      {
        npa_issue_required_request(CNOCHandle, RMFreqKHz[gDDRFreqIndex][4]);
        HAL_clk_ReduceQ6BIMCPorts( FALSE );
        //HAL_clk_EnableQ6BIMCPorts( TRUE );
        pBimcRes->bBIMCModemEnabled = TRUE;
      }
    }
  }
  return nState;
}

    
/*===========================================================================

  FUNCTION      Clock_NPANodeMMSSAXIFunc

  DESCRIPTION   This function is setting MMSS AXI clock and its power domain
  
  PARAMETERS    pResource [in] - MMSS AXI Resource.
                nState [in]    - Request state.

  DEPENDENCIES  None

  RETURN VALUE  

  SIDE EFFECTS  None.

===========================================================================*/
static npa_resource_state Clock_NPANodeMMSSAXIFunc
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState 
)
{
  uint32 nFreqKHz = 0;
  MMXIResourceType* pMMXIRes = &Clock_Resources.MMAXIClockResource;

  if ( nState == 0 )
  {
    Clock_SetClockSpeed( &pMMXIRes->sClockRes, 0 );
    if ( pMMXIRes->bEnabled )
    {
      Clock_DisableClockGroup( &pMMXIRes->sClockRes);
      Clock_DisablePowerDomain( pMMXIRes->nMMSSAXIPowerID);
      pMMXIRes->bEnabled = FALSE;
    }
  }
  else
  {
    if ( !pMMXIRes->bEnabled )
    {
      Clock_EnablePowerDomain( pMMXIRes->nMMSSAXIPowerID, TRUE);
      Clock_EnableClockGroup( &pMMXIRes->sClockRes, TRUE);
      pMMXIRes->bEnabled = TRUE;
    }
    nFreqKHz = Clock_SetClockSpeed( &pMMXIRes->sClockRes, nState * 1000 ) / 1000;
  }

  return nFreqKHz;
}

/*===========================================================================

  FUNCTION      Clock_SetDDRFmax

  DESCRIPTION   Fill Fmax DDR frequency for all corners for rate matching support
  
  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  

  SIDE EFFECTS  None.

===========================================================================*/
void Clock_SetDDRFmax( void )
{
  uint32              nIndex;
  ClockMuxConfigType  *pCfg;
  ClockNodeType       *pBimcClk = Clock_Resources.BIMCResource.sClockRes.apClocks[0];

  for ( nIndex = Clock_Resources.BIMCResource.sClockRes.nMinLevel;
        nIndex <= Clock_Resources.BIMCResource.sClockRes.nMaxLevel;
        nIndex++ )
  {
    pCfg = &pBimcClk->pDomain->pBSPConfig[nIndex];
    
    // Check frequency that supported in this HW version only
    if ( Clock_IsBSPSupported(pCfg) )
    {
      if ( pCfg->eVRegLevel == CLOCK_VREG_LEVEL_LOW_MINUS )
        RMFreqKHz[0][0] = pCfg->nFreqHz / 1000;
      else if( pCfg->eVRegLevel == CLOCK_VREG_LEVEL_LOW )
        RMFreqKHz[1][0] = pCfg->nFreqHz / 1000;
      else if( pCfg->eVRegLevel == CLOCK_VREG_LEVEL_LOW_PLUS )
        RMFreqKHz[2][0] = pCfg->nFreqHz / 1000;
      else if( pCfg->eVRegLevel == CLOCK_VREG_LEVEL_NOMINAL )
        RMFreqKHz[3][0] = pCfg->nFreqHz / 1000;
      else if( pCfg->eVRegLevel == CLOCK_VREG_LEVEL_HIGH )
        RMFreqKHz[4][0] = pCfg->nFreqHz / 1000;
    }
  }
}


/*===========================================================================

  FUNCTION      Clock_GetFmax

  DESCRIPTION   Fill Fmax DDR frequency for all corners for rate matching support
  
  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  

  SIDE EFFECTS  None.

===========================================================================*/
void Clock_GetFmax(uint32 id, ClockMuxConfigType *pCfg, uint32 min, uint32 max )
{
  uint32              nIndex;

  if(id >= MAXSNOC_RMFREQ_ID)
  {
    return;
  }
  
  for ( nIndex = min; nIndex <= max; nIndex++ )
  {
    
    // Check frequency that supported in this HW version only
    if ( Clock_IsBSPSupported(pCfg) )
    {
      if ( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_LOW_MINUS )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_LOW_MINUS][id] = pCfg->nFreqHz / 1000;

      if( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_LOW )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_LOW][id] = pCfg->nFreqHz / 1000;

      if( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_LOW_PLUS )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_LOW_PLUS][id] = pCfg->nFreqHz / 1000;

      if( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_NOMINAL )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_NOMINAL][id] = pCfg->nFreqHz / 1000;

      if( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_NOMINAL_PLUS )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_NOMINAL_PLUS][id] = pCfg->nFreqHz / 1000;

      if( pCfg->eVRegLevel <= CLOCK_VREG_LEVEL_HIGH )
        SNOCRMFreqKHz[FMAX_VREG_LEVEL_HIGH][id] = pCfg->nFreqHz / 1000;

      pCfg++;
    }
  }
}


void Clock_SetSNOCFmax( void )
{
  ClockMuxConfigType *pCfg;
  uint32  nMaxLevel;
  ClockNodeType       *pClk;
  
  nMaxLevel = Clock_Resources.SNOCClockResource.nMaxLevel;
  pClk      = Clock_Resources.SNOCClockResource.apClocks[0];
  pCfg      = &pClk->pDomain->pBSPConfig[0];
  Clock_GetFmax(SNOC_RMFREQ_ID, pCfg, 0, nMaxLevel );
  
  nMaxLevel = Clock_Resources.SNOCHSClockResource.nMaxLevel;
  pClk      = Clock_Resources.SNOCHSClockResource.apClocks[0];
  pCfg      = &pClk->pDomain->pBSPConfig[0];
  Clock_GetFmax(SNOC_HS_RMFREQ_ID, pCfg, 0, nMaxLevel );

  nMaxLevel = Clock_Resources.SNOCPIMEMClockResource.nMaxLevel;
  pClk      = Clock_Resources.SNOCPIMEMClockResource.apClocks[0];
  pCfg      = &pClk->pDomain->pBSPConfig[0];
  Clock_GetFmax(SNOC_PIMEM_RMFREQ_ID, pCfg, 0, nMaxLevel );

}



/*===========================================================================

  FUNCTION      Clock_SNOCVoteMatchSpeed

  DESCRIPTION   Match MMSS AXI and System NOC with DDR speed for improve performance level
  
  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  

  SIDE EFFECTS  None.

===========================================================================*/

#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

static boolean nSNOCInit = FALSE;

void Clock_SNOCVoteMatchSpeed( uint32 nSNOCFreqKHz, uint32 nSNOCHSFreqKHz, uint32 *nNewSNOCFreqKHz, uint32 *nNewSNOCHSFreqKHz )
{
  uint32 nIndex, nIndexHS, nIdxNew, nSnocFreq, nSnocHSFreq, nPimeFreq;
  
  ClockDrvCtxt   *pDrvCtxt = Clock_GetDrvCtxt();

  if ( nSNOCInit == FALSE )
  {
    Clock_SetSNOCFmax();
    nSNOCInit = TRUE;
  }

  // Get the index for voting HSSNOC and PIMEM
  nIndex = 0;
  while ( SNOCRMFreqKHz[nIndex][SNOC_RMFREQ_ID] != 0 )
  {
    if ( nSNOCFreqKHz <= SNOCRMFreqKHz[nIndex][SNOC_RMFREQ_ID] )
    {
      break;
    }
    nIndex++;
  }
  if(nIndex == FMAX_VREG_LEVEL_NUM_CORNERS)
  {
    nIndex = FMAX_VREG_LEVEL_HIGH;
  }

  // Get the index for voting HSSNOC and PIMEM
  nIndexHS = 0;
  while ( SNOCRMFreqKHz[nIndexHS][SNOC_HS_RMFREQ_ID] != 0 )
  {
   if ( nSNOCHSFreqKHz <= SNOCRMFreqKHz[nIndexHS][SNOC_HS_RMFREQ_ID] )
   {
     break;
   }
   nIndexHS++;
  }
  if(nIndexHS == FMAX_VREG_LEVEL_NUM_CORNERS)
  {
    nIndexHS = FMAX_VREG_LEVEL_HIGH;
  }

  nIdxNew = MAX(nIndexHS, nIndex);

  if(nSNOCFreqKHz == 0 && nSNOCHSFreqKHz == 0)
  {
    nSnocFreq = SNOCRMFreqKHz[nIdxNew][SNOC_RMFREQ_ID]*1000;
    nSnocHSFreq = SNOCRMFreqKHz[nIdxNew][SNOC_HS_RMFREQ_ID]*1000;
    nPimeFreq = SNOCRMFreqKHz[nIdxNew][SNOC_PIMEM_RMFREQ_ID];
  }
  else
  {
    nSnocFreq = SNOCRMFreqKHz[nIdxNew][SNOC_RMFREQ_ID]*1000;
    nSnocHSFreq = SNOCRMFreqKHz[nIdxNew][SNOC_HS_RMFREQ_ID]*1000;
    nPimeFreq = SNOCRMFreqKHz[nIdxNew][SNOC_PIMEM_RMFREQ_ID];

  }
  *nNewSNOCFreqKHz = Clock_SetClockSpeed(&Clock_Resources.SNOCClockResource, nSnocFreq)/1000;
  *nNewSNOCHSFreqKHz = Clock_SetClockSpeed(&Clock_Resources.SNOCHSClockResource, nSnocHSFreq)/1000;

  if(Clock_Resources.PIMEMHandle == NULL)  
  {
    Clock_Resources.PIMEMHandle = npa_create_sync_client("/clk/pmem", "ClockRPM-SNOC", NPA_CLIENT_REQUIRED ); 
    CORE_VERIFY_PTR(Clock_Resources.PIMEMHandle);  
  }
  
  
  /* Vote for PIMEM as sync with SysNoc */
  npa_issue_required_request( Clock_Resources.PIMEMHandle, nPimeFreq );

}






/*===========================================================================

  FUNCTION      Clock_VoteMatchSpeed

  DESCRIPTION   Match MMSS AXI and System NOC with DDR speed for improve performance level
  
  PARAMETERS    None

  DEPENDENCIES  None

  RETURN VALUE  

  SIDE EFFECTS  None.

===========================================================================*/
void Clock_VoteMatchSpeed( uint32 nDDRFreqKHz )
{
  uint32 nIndex;
  static boolean nInit = FALSE;
  extern Clock_TargCtxtType Clock_Resources;  
  BIMCResourceType  *pBimcRes     = &Clock_Resources.BIMCResource;
  

  if ( nInit == FALSE )
  {
    Clock_SetDDRFmax();
    nInit = TRUE;
  }

  // Get the index for voting SNOC and MMNOC AXI
  nIndex = 0;
  while ( RMFreqKHz[nIndex][0] != 0 )
  {
    if ( nDDRFreqKHz <= RMFreqKHz[nIndex][0] )
    {
      break;
    }
    nIndex++;
  }

  if ( SNOCHandle == NULL )
  {
    SNOCHandle = npa_create_sync_client("/clk/snoc", "ClockRPM-BIMC", NPA_CLIENT_SUPPRESSIBLE );
    CORE_VERIFY_PTR( SNOCHandle );
  }
  if ( MMXIHandle == NULL )
  {
    MMXIHandle = npa_create_sync_client("/clk/mmnoc_axi", "ClockRPM", NPA_CLIENT_SUPPRESSIBLE );
    CORE_VERIFY_PTR( MMXIHandle );
  } 

  if ( SNOCHSHandle == NULL )
  {
    SNOCHSHandle = npa_create_sync_client("/clk/snoc_hs", "ClockRPM-BIMC", NPA_CLIENT_SUPPRESSIBLE );
    CORE_VERIFY_PTR( SNOCHSHandle );
  } 

  if ( CNOCHandle == NULL )
  {
    CNOCHandle = npa_create_sync_client("/clk/cnoc", "ClockRPM-BIMC", NPA_CLIENT_REQUIRED );
    CORE_VERIFY_PTR( CNOCHandle );
  } 


  npa_issue_required_request(SNOCHandle, RMFreqKHz[nIndex][1]);
  npa_issue_required_request(MMXIHandle, RMFreqKHz[nIndex][2]);
  npa_issue_required_request(SNOCHSHandle, RMFreqKHz[nIndex][3]);
  if ( pBimcRes->bBIMCModemEnabled )
  {
    npa_issue_required_request(CNOCHandle, RMFreqKHz[nIndex][4]);
  }
  gDDRFreqIndex = nIndex;
}
