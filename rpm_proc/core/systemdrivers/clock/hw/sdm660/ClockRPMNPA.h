#ifndef CLOCKRPMNPA_H
#define CLOCKRPMNPA_H
/*
===========================================================================
*/
/**
  @file ClockRPMNPA.h
  
  NPA node definitions for the MSM8996 RPM clock driver.
*/
/*  
  ====================================================================

  Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/hw/sdm660/ClockRPMNPA.h#4 $
  $DateTime: 2017/01/23 23:42:49 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  05/07/14   vph     Initial version for 8996
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include <DALSys.h>
#include <railway.h>
#include <npa.h>
#include <npa_resource.h>

#include "ClockDriver.h"

/*=========================================================================
      Macros
==========================================================================*/

/*
 * Invalid NPA resource max state (clock frequency in KHz). Marks that a 
 * resource's max state should be detected from its associated ClockBSP
 * data during RPM NPA init.
 */
#define CLK_INV_MAX_FREQ_KHZ            0

/*
 * Clock resource performance level indices (valid levels: [0--126]).
 */
#define CLK_XO_LEVEL                    0
#define CLK_MAX_LEVEL                   0x7E
#define CLK_INV_LEVEL                   0x7F

/*
 * Macro that returns true if the resource has been previously voted upon.
 */
#define CLK_NPA_RES_VOTED_UPON(pNpaRes) \
      ((pNpaRes)->handle->sequence > 0)

/*
 * Clock driver NPA resource config flags:
 *
 *  CLK_NPA_FLAG_DATA_CLK_RES:
 *    Resource data points to a 'ClockResourceType'. Only used for initial
 *    sanity checks.
 *
 *  CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE:
 *    Initial active and max states are detected from the NPA resoure's clock
 *    resource during clock driver NPA init.
 *
 *  CLK_NPA_FLAG_CLK_SWITCH_EN:
 *    Resource uses generic clock *scaling* option.
 *
 *  CLK_NPA_FLAG_CLK_GATE_EN:
 *    Resource uses generic clock *gating* option.
 *
 *  CLK_NPA_FLAG_DCVS_GATE_EN:
 *    Resource scaling is gated by "dcvs.ena".
 *
 *  CLK_NPA_FLAG_PC_GATE_EN:
 *    Resource collapse is gated by *pc_gate* option.
 */
#define CLK_NPA_FLAG_DATA_CLK_RES               (1 << 0)
#define CLK_NPA_FLAG_GEN_INIT_MAX_AND_ACTIVE    (1 << 1)
#define CLK_NPA_FLAG_CLK_SWITCH_EN              (1 << 2)
#define CLK_NPA_FLAG_CLK_GATE_EN                (1 << 3)
#define CLK_NPA_FLAG_DCVS_GATE_EN               (1 << 4)
#define CLK_NPA_FLAG_PC_GATE_EN                 (1 << 5)

/*
 * Declares a clock resource with default initial values and a variable length
 * compound literal clock array.
 */
#define CLK_RESOURCE_DECL(nClockCount)                      \
  { .apClocks       = (ClockNodeType*[nClockCount]){NULL},  \
    .nNumClocks     = nClockCount,                          \
    .bClkGrpEnabled = FALSE,                                \
    .nMinLevel      = CLK_XO_LEVEL,                         \
    .nMaxLevel      = CLK_MAX_LEVEL,                        \
    .nCurLevel      = CLK_XO_LEVEL,                         \
    .nSavLevel      = CLK_INV_LEVEL,                        \
    .nPrevLevel     = CLK_INV_LEVEL }

/*
 * Returns the clock object delegate used to switch an entire clock domain.
 */
#define CLK_RES_DELEGATE_IDX        0
#define CLK_DELEGATE(pClockRes)     ((pClockRes)->apClocks[CLK_RES_DELEGATE_IDX])

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Clock driver pre/post-clock switch function.
 *
 *  PARAMETERS    pResource [in]  - Clock Resource.
 *                hClient   [in]  - NPA client handle.
 *                nState    [in]  - Aggregated request state.
 *                pNewState [out] - Optional modified resource state.
 *
 *  RETURN VALUE  TRUE - 'pNewState' was assigned a new state for generic
 *                       clock switches to use.
 *                FALSE - 'pNewState' wasn't assigned a new state.
 */
typedef boolean (*Clock_NPAPostPreFcnType)
(
  struct npa_resource *pResource,
  npa_client_handle    hClient,
  npa_resource_state   nState,
  npa_resource_state   *pNewState
);


/*
 * ClockNPAResIdxType
 *
 * Indices for 'Clock_NPAResources'. Must be kept in sync with this array.
 */
typedef enum
{
  // V1+
  CLK_NPA_RES_CXO_IDX = 0,
  CLK_NPA_RES_DCVS_IDX,
  CLK_NPA_RES_CPU_IDX,
  CLK_NPA_RES_SNOC_IDX,
  CLK_NPA_RES_SNOC_PIMEM_IDX,
  CLK_NPA_RES_CNOC_IDX,
  CLK_NPA_RES_CNOC_PERIPH_IDX,
  CLK_NPA_RES_BIMC_IDX,
  CLK_NPA_RES_IPA_IDX,
  CLK_NPA_RES_CE1_IDX,
  CLK_NPA_RES_AGGRE2_IDX,
  CLK_NPA_RES_SPM_IDX,
  CLK_NPA_RES_MMAXI_IDX,
  CLK_NPA_RES_QDSS_IDX,
  CLK_NPA_RES_SNOC_HS_IDX,
  CLK_NPA_NUM_RESOURCES,
  CLOCK_BSP_ENUM_32BITS(CLK_NPA_RES_IDX)
} ClockNPAResIdxType;


/*
 *
 * Indices for "Aggre2" clocks.
 * Used for enable/disable only (these clocks don't share a domain).
 * Must be kept in sync with the "Aggre" clock resource arrays.
 */
typedef enum
{
  CLK_RES_AGGRE2_SNOC_IDX = 0,   // "gcc_aggreN_snoc_axi_clk"
  CLK_RES_AGGRE2_SNOC_SOUTH_IDX,  // "gcc_aggreN_snoc_east_axi_clk"
  CLK_RES_AGGRE2_SNOC_NORTH_IDX, // "gcc_aggreN_snoc_north_axi_clk"
  CLK_RES_AGGRE2_CNOC_IDX,       // "gcc_aggreN_cnoc_ahb_clk"
  CLK_RES_AGGRE2_SMMU_AXI_IDX,   // "gcc_smmu_aggreN_axi_clk"
  CLK_RES_AGGRE2_SMMU_AHB_IDX,   // "gcc_smmu_aggreN_ahb_clk"

  CLK_RES_AGGRE2_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_AGGRE2_IDX)
} ClockResAggre2IdxType;


/*
 * ClockResCeIdxType
 *
 * Indices for CE clocks.
 * Must be kept in sync with the CE clock resource array.
 */
typedef enum
{
  CLK_RES_CE_CLK_IDX = 0,   // "gcc_ceN_clk"
  CLK_RES_CE_CLK_AXI_IDX,   // "gcc_ceN_axi_clk" (SNOC domain)
  CLK_RES_CE_CLK_AHB_IDX,   // "gcc_ceN_ahb_clk" (CNOC domain)

  CLK_RES_CE_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_CE_IDX)
} ClockResCeIdxType;

/*
 * ClockResCnocPeriphIdxType
 *
 * Indices for CNOC Periph clocks.
 * Must be kept in sync with the PNOC clock resource array.
 */
typedef enum
{
  CLK_RES_CNOC_PERIPH_NORTH_AHB_IDX = 0, //"gcc_cnoc_periph_west_ahb_clk",
  CLK_RES_CNOC_PERIPH_SOUTH_AHB_IDX,     //"gcc_cnoc_periph_east_ahb_clk",
  CLK_RES_CNOC_PERIPH_AHB_IDX,         //"gcc_cnoc_periph_ahb_clk"
  CLK_RES_CNOC_PERIPH_AGGRE2_AHB_IDX,   //"gcc_aggre2_cnoc_periph_ahb_clk",
  CLK_RES_CNOC_NORTH_PERIPH_AGGRE2_AHB_IDX,   //"gcc_aggre2_north_cnoc_periph_ahb_clk",
  CLK_RES_CNOC_SOUTH_PERIPH_AGGRE2_AHB_IDX,   //"gcc_aggre2_south_cnoc_periph_ahb_clk",
  CLK_RES_CNOC_PERIPH_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_CNOC_PERIPH_IDX)
} ClockResPnocIdxType;

/*
 * ClockResQdssIdxType
 *
 * Indices for (toggle-able) QDSS clocks.
 * Must be kept in sync with the QDSS clock resource array.
 */
typedef enum
{
  CLK_RES_QDSS_CFG_AHB_IDX = 0,     // "gcc_qdss_cfg_ahb_clk"
  CLK_RES_QDSS_DAP_AHB_IDX,         // "gcc_qdss_dap_ahb_clk"
  CLK_RES_QDSS_ETR_USB_IDX,         // "gcc_qdss_etr_usb_clk"
  CLK_RES_QDSS_TRACE_IDX,           // "gcc_qdss_traceclkin_clk"
  CLK_RES_QDSS_STM_IDX,             // "gcc_qdss_stm_clk"
  CLK_RES_QDSS_SNOC_STM_AXI_IDX,    // "gcc_sys_noc_qdss_stm_axi_clk"
  CLK_RES_QDSS_DAP_IDX,             // "gcc_qdss_dap_clk"
  CLK_RES_QDSS_TCSTR_DIV2_IDX,      // "gcc_qdss_tsctr_div2_clk"
  CLK_RES_QDSS_TCSTR_DIV3_IDX,      // "gcc_qdss_tsctr_div3_clk"
  CLK_RES_QDSS_TCSTR_DIV4_IDX,      // "gcc_qdss_tsctr_div4_clk"
  CLK_RES_QDSS_TCSTR_DIV8_IDX,      // "gcc_qdss_tsctr_div8_clk"
  CLK_RES_QDSS_TCSTR_DIV16_IDX,     // "gcc_qdss_tsctr_div16_clk"
  CLK_RES_QDSS_APB2JTAG_IDX,        // "gcc_qdss_apb2jtag_clk"
  CLK_RES_WCSS_TSCTR_DIV2_IDX,      // "gcc_wcss_tsctr_div2_clk",
  CLK_RES_MMSS_TRIG_IDX,            // "gcc_mmss_trig_clk",
  CLK_RES_QDSS_TRIG_IDX,            // "gcc_qdss_trig_clk",
  CLK_RES_LPASS_TRIG_IDX,           // "gcc_lpass_trig_clk",
  CLK_RES_HMSS_TRIG_IDX,            // "gcc_hmss_trig_clk",
  CLK_RES_MSS_TRIG_IDX,             // "gcc_mss_trig_clk",
  CLK_RES_GPU_TRIG_IDX,             // "gcc_gpu_trig_clk"
  CLK_RES_TURING_TRIG_IDX,          // "gcc_turing_trig_clk"
  CLK_RES_APSS_QDSS_TCSTR_DIV2_IDX, // "gcc_apss_qdss_tsctr_div2_clk"
  CLK_RES_APSS_QDSS_TCSTR_DIV8_IDX, // "gcc_apss_qdss_tsctr_div8_clk"
  
  CLK_RES_QDSS_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_QDSS_IDX)
} ClockResQdssIdxType;

/*
 * ClockResQdssATIdxType
 *
 * Indices for (non toggle-able) QDSS clocks.
 * Must be kept in sync with the QDSS clock resource array.
 */
typedef enum
{

  CLK_RES_QDSS_SYS_NOC_AT_IDX = 0,  // "gcc_sys_noc_at_clk",
  CLK_RES_QDSS_MMSS_NOC_AT_IDX,     // "gcc_mmss_noc_at_clk",
  CLK_RES_QDSS_CENTER_AT_IDX,       // "gcc_qdss_center_at_clk",
  CLK_RES_QDSS_SOUTH_AT_IDX,        // "gcc_south_at_clk",
  CLK_RES_QDSS_NORTH_AT_IDX,        // "gcc_north_at_clk",
  CLK_RES_QDSS_AGGRE2_AT_IDX,       // "gcc_aggre2_noc_at_clk",
  CLK_RES_QDSS_BIMC_AT_IDX,         // "gcc_bimc_at_clk",
  CLK_RES_QDSS_MSS_AT_IDX,          // "gcc_mss_at_clk"
  CLK_RES_QDSS_HMSS_AT_IDX,         // "gcc_hmss_at_clk"
  CLK_RES_NORTH_APB_IDX,            // "gcc_north_apb_clk"
  CLK_RES_WCSS_AT_IDX,              // "gcc_wcss_at_clk",
  CLK_RES_TURING_AT_IDX,            // "gcc_turing_at_clk"
  CLK_RES_QDSS_GPU_AT_IDX,          // "gcc_gpu_at_clk"
  CLK_RES_QDSS_LPASS_AT_IDX,        // "gcc_lpass_at_clk"
 
  CLK_RES_QDSS_AT_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_QDSS_AT_IDX)
} ClockResQdssATIdxType;


/*
 * ClockResVsenseIdxType
 *
 * Indices for Vsense clocks.
 * Must be kept in sync with the Vsense clock resource array.
 */
typedef enum
{
  // V1+
  CLK_RES_VSENSE_VDDA_IDX = 0,  // "gcc_vdda_vs_clk"
  CLK_RES_VSENSE_VDDCX_IDX,     // "gcc_vddcx_vs_clk"
  CLK_RES_VSENSE_VDDMX_IDX,     // "gcc_vddmx_vs_clk"
  CLK_RES_VSENSE_CTRL_IDX,      // "gcc_vs_ctrl_clk"
  CLK_RES_VSENSE_MAX_IDX_V1 = CLK_RES_VSENSE_CTRL_IDX,
  CLK_RES_VSENSE_NUM_CLOCKS_V1,

  // V2+
  CLK_RES_VSENSE_MSS_IDX = CLK_RES_VSENSE_NUM_CLOCKS_V1, // "gcc_mss_vs_clk"

  CLK_RES_VSENSE_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_VSENSE_IDX)
} ClockResVsenseIdxType;

/*
 * ClockResMMAXIIdxType
 *
 * Indices for MMAXI clocks
 *
 */
typedef enum
{
  CLK_RES_MMSS_MNOC_AXI_IDX = 0,    // "mmss_mnoc_axi_clk"

  CLK_RES_MMSS_NUM_CLKS,
  CLOCK_BSP_ENUM_32BITS(CLK_RES_MMSS_IDX)
} ClockResMMAXIIdxType;


/*
 * BIMCStateType
 *
 * BIMC enum state type
 */
typedef enum
{
  BIMC_ON,           /* BIMC is on */
  BIMC_SAVING,       /* BIMC is in power collapsed, save DEHR */
  BIMC_COLLAPSED,    /* BIMC is in power collapsed */
  BIMC_RESTORING,    /* BIMC is in restoring state */
} BIMCStateType;


/*
 * ClockQDSSSpeedType
 *
 * QDSS enum speed type
 */
typedef enum
{
  CLOCK_QDSS_SPEED_XO,
  CLOCK_QDSS_SPEED_LOW_MINUS,
  CLOCK_QDSS_SPEED_LOW,
  CLOCK_QDSS_SPEED_NOMINAL,
  CLOCK_QDSS_NUM_SPEEDS,
} ClockQDSSSpeedType;


/*
 * ClockResourceType
 *
 * Structure containing the clocks resource info
 */
typedef struct
{
  /*
   * Array of clock nodes. The first clock is used for generic clock domain
   * frequency switches. Each clock is disabled/enabled for generic clock
   * gating operations.
   */
  ClockNodeType           **apClocks;
  uint8                   nNumClocks;

  /*
   * Holds the enable state from the last group enable/disable operation
   * (see Clock_Enable/DisableClockGroup()).
   */
  boolean                 bClkGrpEnabled;

  uint8                   nMinLevel;    // Minimum level index.
  uint8                   nMaxLevel;    // Max level index.
  uint8                   nCurLevel;    // Current level index.
  uint8                   nSavLevel;    // Saved level index (for restores).
  uint8                   nPrevLevel;   // Previous level index.
} ClockResourceType;

typedef struct  
{
  HAL_clk_SourceType nCurrPLL;
 // HAL_clk_SourceType nPrevPLL;
}Clock_BIMCAsyncClkState;

#define MAX_BIMC_DDR_ASYNC_CLK 6

/*
 * BIMCResourceType
 * Structure containing the BIMC resource info
 */
typedef struct
{
  // Clock resource must be first member (see 'CLK_NPA_FLAG_DATA_CLK_RES').
  ClockResourceType       sClockRes;
    
  boolean                 bPCModeEn;          // BIMC power collapse is allowed
  boolean                 bPCDDRPHYModeEn;          // DDRPHY power collapse is allowed
  boolean                 bBIMCModemEnabled;  // last BIMC vote from MSS
  boolean                 bBIMCAppsEnabled;   // last BIMC vote from APSS
  uint32                  nChannelDDR;
  ClockVRegLevelType      nVDDA;
  BIMCStateType           eXOBIMCState;       // BIMC state in XO shutdown
  BIMCStateType           eBIMCState;
  ClockPowerDomainIdType  nBIMCPowerID;
  ClockPowerDomainIdType  nDDRPHYPowerID;
  Clock_BIMCAsyncClkState sAsyncClockState[MAX_BIMC_DDR_ASYNC_CLK];
} BIMCResourceType;


/*
 * MMXIResourceType
 * Structure containing the MMSS NOC AXI resource info
 */
typedef struct
{
  // Clock resource must be first member (see 'CLK_NPA_FLAG_DATA_CLK_RES').
  ClockResourceType       sClockRes;
  
  boolean                 bEnabled;         // MMSS AXI NOC enable state
  ClockPowerDomainIdType  nMMSSAXIPowerID;
} MMXIResourceType;


/*
 * IPAResourceType
 * Structure containing the IPA resource info
 */
typedef struct
{
  // Clock resource must be first member (see 'CLK_NPA_FLAG_DATA_CLK_RES').
  ClockResourceType       sClockRes;

  boolean                 bEnabled;         // IPA enable state
  npa_client_handle       BIMCHandle;
  npa_client_handle       Aggre2Handle;
} IPAResourceType;


/*
 * QDSSResourceType
 *
 * QDSS resource info.
 */
typedef struct
{
  // Clock resource must be first member (see 'CLK_NPA_FLAG_DATA_CLK_RES').
  ClockResourceType       sClockRes;

  ClockVRegLevelType      nQDSSVoltageLevel;
  ClockQDSSLevelType      nQDSSCurrLevel;

  /* Clocks that aren't enabled/disabled for QDSS clock toggles. */
  ClockNodeType           *pQDSSATClkGroup[CLK_RES_QDSS_AT_NUM_CLKS];
} QDSSResourceType;


/*
 * AggreResourceType
 *
 * Aggre resource information.
 */
typedef struct
{
  // Clock resource must be first member (see 'CLK_NPA_FLAG_DATA_CLK_RES').
  ClockResourceType       sClockRes;
  npa_client_handle       SNOCHandle;

  ClockPowerDomainIdType  nAggrePowerID;
} AggreResourceType;


/*
 * ClockNPANodeDataType
 *
 * Structure containing the NPA resources's user data.
 */
typedef struct
{
  /* Resource data flags. */
  uint32                  nFlags;

  /*
   * Additional resource data. To utilize generic clock switches, this must
   * point to a 'ClockResourceType'.
   */
  void                    *pData;

  /* Resource driver function. Set to NULL to use generic clock switch. */
  npa_resource_driver_fcn pmResDriverFunc;

  /* Resource pre-generic-clock-switch function. Set to NULL to bypass. */
  Clock_NPAPostPreFcnType pmPreClkSwitchFunc;

  /* Resource post-generic-clock-switch function. Set to NULL to bypass. */
  Clock_NPAPostPreFcnType pmPostClkSwitchFunc;

} ClockNPAResDataType;


/*
 * Clock_TargCtxtType
 *
 * Structure containing target specific clock driver context (for RPM).
 */
typedef struct
{
  npa_node_definition     sNPAClkNode;

  int                     nCXRailID;
  ClockVRegLevelType      nCXVReg;
  npa_client_handle       PIMEMHandle;
  npa_client_handle       SNOCHSHandle;
  npa_client_handle       SNOCHandle;

  /*
   * Containers for clock resources plus extra resource-specific data.
   * The first member of these structs must be a 'ClockResourceType' to support
   * generic operations (C standard gaurentees that a struct's first member
   * is placed at the base address of the struct).
   */
  BIMCResourceType        BIMCResource;
  IPAResourceType         IPAResource;
  AggreResourceType       Aggre2Resource;
  QDSSResourceType        QDSSResource;

  /*
   * Bare clock resources.
   */
  ClockResourceType       CPUClockResource;
  ClockResourceType       SNOCClockResource;
  ClockResourceType       SNOCPIMEMClockResource;
  ClockResourceType       CNOCClockResource;
  ClockResourceType       CNOCPeriphClockResource;
  ClockResourceType       CE1ClockResource;
  ClockResourceType       HMSSAHBClockResource;
  ClockResourceType       SNOCHSClockResource;
  ClockResourceType       SPMClockResource;
  MMXIResourceType        MMAXIClockResource;
  ClockResourceType       VSenseClockResource;
} Clock_TargCtxtType;


/*=========================================================================
      Externs
==========================================================================*/

extern const char* const aszClockNPAResNames[];


/*=========================================================================
      Prototypes
==========================================================================*/

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
);


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
);


/*===========================================================================

  FUNCTION      Clock_InitNPA

  DESCRIPTION   This function is used setup NPA node to all the clock
                resource
                  
  PARAMETERS    None.

  DEPENDENCIES  None.

  RETURN VALUE  None

  SIDE EFFECTS  None.

===========================================================================*/
DALResult Clock_InitNPA
(
  void
);


/*===========================================================================

  FUNCTION      Clock_GetTargCtxt

  DESCRIPTION   Returns target-specific RPM clock driver context.

  PARAMETERS    None

  DEPENDENCIES  None.

  RETURN VALUE  Pointer target-specific RPM clock driver context.

  SIDE EFFECTS  None.

===========================================================================*/
static inline Clock_TargCtxtType* Clock_GetTargCtxt
(
  void
)
{
  extern Clock_TargCtxtType Clock_Resources;
  return &Clock_Resources;
}


/*===========================================================================

  FUNCTION      Clock_WaitForClockGroupOn

  DESCRIPTION   Waits for an entire group of clocks to turn on.

  PARAMETERS    pClockResource  [in] - Clock resource to wait on.

  DEPENDENCIES  None.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  Sets clock resource's 'bClkGrpEnabled' to TRUE upon success.

===========================================================================*/
DALResult Clock_WaitForClockGroupOn
(
  ClockResourceType   *pClockResource
);


/*===========================================================================

  FUNCTION      Clock_EnableClockGroup

  DESCRIPTION   Enables an entire group of clocks.

  PARAMETERS    pClockResource  [in] - Clock resource to enable.
                bWaitForClockOn [in] - Set to TRUE to wait for clock ONs.

  DEPENDENCIES  None.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  If called with 'bWaitForClockOn' = TRUE, sets the clock 
                resource's 'bClkGrpEnabled' to TRUE upon success. Otherwise
                'bClkGrpEnabled' is left unmodified.

===========================================================================*/
DALResult Clock_EnableClockGroup
(
  ClockResourceType   *pClockResource,
  boolean              bWaitForClockOn
);


/*===========================================================================

  FUNCTION      Clock_DisableClockGroup

  DESCRIPTION   Disables an entire group of clocks.

  PARAMETERS    pClockResource  [in] - Clock resource to disable.

  DEPENDENCIES  None.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  Sets clock resource's 'bClkGrpEnabled' to FALSE if the clock
                delegate's reference count is zero after the disable.

===========================================================================*/
DALResult Clock_DisableClockGroup
(
  ClockResourceType   *pClockResource
);


/*===========================================================================

  FUNCTION      Clock_SetClockSpeed

  DESCRIPTION   This function is for setting the clock speed
                  
  PARAMETERS    pClockResource [in] - Clock to switch.
                nFreqHz        [in] - New clock speed (in Hz).

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in Hz).

  SIDE EFFECTS  None.

===========================================================================*/
npa_resource_state Clock_SetClockSpeed
(
  ClockResourceType   *pClockResource,
  uint32              nFreqHz
);



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
void Clock_EnableVSenseClocks( boolean bEnable );

#endif /* #ifndef CLOCKRPMNPA_H */
