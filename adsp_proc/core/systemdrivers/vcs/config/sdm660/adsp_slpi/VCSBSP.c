/*
==============================================================================

FILE:         VCSBSP.c

DESCRIPTION:
  This file contains VCS BSP data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/config/sdm660/adsp_slpi/VCSBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/06/16   lil     First version for SDM660.

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/


#include "comdef.h"
#include "VCSBSP.h"
#include "VCSDriver.h"
#include "pmapp_npa.h"


/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Data Declarations
==========================================================================*/


/*
 *  VCS_RailCornerConfigsLPICX
 *
 *  Set of rail corner configurations.
 */
static VCSRailCornerConfigType VCS_CornerConfigLPICX[] =
{
  {
    .eCornerMin         = VCS_CORNER_OFF,
    .eCornerMax         = VCS_CORNER_MAX,
    .eCornerInit        = VCS_CORNER_NOMINAL,
    .eCornerInitThermal = VCS_CORNER_OFF,
    .HWVersion          = { {0x0, 0x0}, {0xFF, 0xFF} },
  }
};

/*
 *  VCS_RailCornerConfigsCX
 *
 *  Set of rail corner configurations.
 */
static VCSRailCornerConfigType VCS_CornerConfigCX[] =
{
  {
    .eCornerMin         = VCS_CORNER_OFF,
    .eCornerMax         = VCS_CORNER_MAX,
    .eCornerInit        = VCS_CORNER_NOMINAL,
    .eCornerInitThermal = VCS_CORNER_OFF,
    .HWVersion          = { {0x0, 0x0}, {0xFF, 0xFF} },
  }
};


/*
 *  VCS_RailCornerConfigsMX
 *
 *  Set of rail corner configurations.
 */
static VCSRailCornerConfigType VCS_CornerConfigMX[] =
{
  {
    .eCornerMin         = VCS_CORNER_OFF,
    .eCornerMax         = VCS_CORNER_MAX,
    .eCornerInit        = VCS_CORNER_NOMINAL,
    .eCornerInitThermal = VCS_CORNER_OFF,
    .HWVersion          = { {0x0, 0x0}, {0xFF, 0xFF} },
  }
};


/*
 * VCS_NPADefinitionDependencyLPICX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionDependencyLPICX =
{
  .szName = VCS_NPA_RESOURCE_VDD_LPICX_VLVL,
  {
    .szName  = "rwlc\x00\x00\x00\x00",
    .szUnits = "vlvl"
  },
};


/*
 * VCS_NPADefinitionDependencyCX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionDependencyCX =
{
  .szName = VCS_NPA_RESOURCE_VDD_CX_VLVL,
  {
    .szName  = "rwcx\x00\x00\x00\x00",
    .szUnits = "vlvl"
  },
};


/*
 * VCS_NPADefinitionActiveFloorLPICX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionActiveFloorLPICX =
{
  .szName = VCS_NPA_RESOURCE_VDD_LPI_CX_ACTIVE_FLOOR,
  {
    .szName  = "rwlc\x00\x00\x00\x00",
    .szUnits = "vfl"
  },
};

/*
 *
 * VCS_NPADefinitionActiveFloorCX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionActiveFloorCX =
{
  .szName = VCS_NPA_RESOURCE_VDD_CX_ACTIVE_FLOOR,
  {
    .szName  = "rwcx\x00\x00\x00\x00",
    .szUnits = "vfl"
  },
};


/*
 * VCS_NPADefinitionDependencyLPIMX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionDependencyLPIMX =
{
  .szName = VCS_NPA_RESOURCE_VDD_LPIMX_VLVL,
  {
    .szName  = "rwlm\x00\x00\x00\x00",
    .szUnits = "vlvl"
  },
};


/*
 * VCS_NPADefinitionActiveFloorLPIMX;
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionActiveFloorLPIMX =
{
  .szName = VCS_NPA_RESOURCE_VDD_LPI_MX_ACTIVE_FLOOR,
  {
    .szName  = "rwlm\x00\x00\x00\x00",
    .szUnits = "vfl"
  },
};


/*
 * VCS_NPADefinitionDependencyMX
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionDependencyMX =
{
  .szName = VCS_NPA_RESOURCE_VDD_MX_VLVL,
  {
    .szName  = "rwmx\x00\x00\x00\x00",
    .szUnits = "vlvl"
  },
};


/*
 * VCS_NPADefinitionActiveFloorMX;
 *
 * Data required to define a an NPA resource in VCS.
 */
static VCSNPADefinitionType VCS_NPADefinitionActiveFloorMX =
{
  .szName = VCS_NPA_RESOURCE_VDD_MX_ACTIVE_FLOOR,
  {
    .szName  = "rwmx\x00\x00\x00\x00",
    .szUnits = "vfl"
  },
};


/*
 * VCS_RailConfigs
 *
 * Set of rail configurations.
 */
static VCSRailConfigType VCS_RailConfigs[] =
{
  {
    .eRail             = VCS_RAIL_LPI_CX,
    .szNameLocal       = VCS_NPA_RESOURCE_VDD_LPI_CX,
    .pNPAActiveFloor   = &VCS_NPADefinitionActiveFloorLPICX,
    .pNPADependency    = &VCS_NPADefinitionDependencyLPICX,
    .pCornerConfig     = VCS_CornerConfigLPICX,
    .nNumCornerConfigs = ARR_SIZE(VCS_CornerConfigLPICX),
    .bEnableDVS        = TRUE,
    .bIsLocal          = FALSE,
  },
  {
    .eRail             = VCS_RAIL_CX,
    .szNameLocal       = VCS_NPA_RESOURCE_VDD_CX,
    .pNPAActiveFloor   = &VCS_NPADefinitionActiveFloorCX,
    .pNPADependency    = &VCS_NPADefinitionDependencyCX,
    .pCornerConfig     = VCS_CornerConfigCX,
    .nNumCornerConfigs = ARR_SIZE(VCS_CornerConfigCX),
    .bEnableDVS        = TRUE,
    .bIsLocal          = FALSE,
  },
  {
    .eRail             = VCS_RAIL_LPI_MX,
    .szNameLocal       = VCS_NPA_RESOURCE_VDD_LPI_MX,
    .pNPAActiveFloor   = &VCS_NPADefinitionActiveFloorLPIMX,
    .pNPADependency    = &VCS_NPADefinitionDependencyLPIMX,
    .pCornerConfig     = VCS_CornerConfigMX,
    .nNumCornerConfigs = ARR_SIZE(VCS_CornerConfigMX),
    .bEnableDVS        = TRUE,
    .bIsLocal          = FALSE,
  },
  {
    .eRail             = VCS_RAIL_MX,
    .szNameLocal       = VCS_NPA_RESOURCE_VDD_MX,
    .pNPAActiveFloor   = &VCS_NPADefinitionActiveFloorMX,
    .pNPADependency    = &VCS_NPADefinitionDependencyMX,
    .pCornerConfig     = VCS_CornerConfigMX,
    .nNumCornerConfigs = ARR_SIZE(VCS_CornerConfigMX),
    .bEnableDVS        = TRUE,
    .bIsLocal          = FALSE,
  },
};


/*
 * Set of LDO_Q6 corner voltages.
 */
static VCSLDOCornerType VCS_LDOCornerLPASSQ6[] =
{
  { VCS_CORNER_LOW_MINUS, {0,0}}, // fill in fuse data when available from PTE
};


/*
 * LDO_Q6 configuration data.
 *
 * Note: This structure is a starting point for what we think the LDO
 * usage should be. This may change in the future.
 */
static VCSLDOConfigType VCS_LDOConfigLPASSQ6[] =
{
  {
    .eLDO               = HAL_LDO_CPU_0,
    .pCorners           = VCS_LDOCornerLPASSQ6,
    .nNumCorners        = ARR_SIZE(VCS_LDOCornerLPASSQ6),
    .bEnable            = FALSE,
    .bAutoBypass        = FALSE,
    .eMinRailCorner     = VCS_CORNER_LOW_MINUS,
    .HWVersion          = { {0x00, 0x00}, {0xFF, 0xFF} }
  },
};


/*
 * List of CPUs.
 */
static VCSCPUConfigType VCS_CPUConfigs[] =
{
  {
    .eCPU             = CLOCK_CPU_LPASS_Q6,
    .szName           = VCS_NPA_RESOURCE_CPU_0,
    .eRail            = VCS_RAIL_LPI_CX,
    .pLDOConfig       = VCS_LDOConfigLPASSQ6,
    .nNumLDOConfigs   = ARR_SIZE(VCS_LDOConfigLPASSQ6),
  },
};


/*
 * VCS Log Default Configuration.
 */
const VCSLogType VCS_LogDefaultConfig[] =
{
  {
    /* .nLogSize = */ 4096,
  }
};


/*
 *  VCS_BSPConfig
 *
 *  List and length of Rail and CPU configurations.
 */
const VCSBSPConfigType VCS_BSPConfig =
{
  .pRailConfig     = VCS_RailConfigs,
  .nNumRailConfigs = ARR_SIZE(VCS_RailConfigs),
  .pCPUConfig      = VCS_CPUConfigs,
  .nNumCPUConfigs  = ARR_SIZE(VCS_CPUConfigs),
};
