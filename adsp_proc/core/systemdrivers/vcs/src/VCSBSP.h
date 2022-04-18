#ifndef __VCSBSP_H__
#define __VCSBSP_H__
/*
===========================================================================
*/
/**
  @file VCSBSP.h

  BSP interface definitions for the DAL VCS device driver.
*/
/*
  ====================================================================

  Copyright (c) 2010-2014 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/src/VCSBSP.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  01/22/14   lil     Created.
 
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


#include "comdef.h"
#include "VCSDefs.h"
#include "ClockDefs.h"
#include "DDIChipInfo.h"
#include "HALldo.h"
#include "npa_resource.h"


/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * VCSLogType
 *
 * Default configuration for the VCS log.
 *
 *  nLogSize        - Log size in bytes.  Must be a power of 2.
 */
typedef struct
{
  uint32 nLogSize;
} VCSLogType;


/*
 * VCSPropertyValueType
 *
 * Generic VCS property data.  Actual data type will depend on the property
 * and will not even necessarily be a pointer (i.e. could be straight uint32).
 */
typedef const void *VCSPropertyValueType;


/*
 * VCSHWVersionType;
 *
 * HW version information.
 *
 *  Min             - Minimum supported HW Major/Minor revision
 *  Max             - Maximum supported HW Major/Minor revision
 *                    '0xFF' indicates all versions.
 *  eChipInfoFamily - Chip this configuration is for. '0' indicates all chips.
 *  aeChipInfoId    - Array of chip id's that the configuration supports.
 *                    NULL indicates all chips.
 */
typedef struct
{
  struct
  {
    uint8 nMajor;
    uint8 nMinor;
  } Min;

  struct
  {
    uint8 nMajor;
    uint8 nMinor;
  } Max;

  DalChipInfoFamilyType    eChipInfoFamily;
  const DalChipInfoIdType *aeChipInfoId;

} VCSHWVersionType;


/*
 * VCSRegMaskType
 *
 * BSP data structure for describing a HW register and bit mask value that can
 * be used to interpret the bits of interest in the register value.
 *
 * nAddr - Address of the register (32-bit).
 * nMask - 32-bit mask.
 */
typedef struct
{
  uint32 nAddr;
  uint32 nMask;
} VCSRegMaskType;


/*
 * VCSCornerVoltageType
 *
 * BSP data structure for describing the voltage for each corner.
 *
 *  eCorner     - The voltage corner
 *  nVoltageUV  - The voltage in uV for this corner
 */
typedef struct
{
  VCSCornerType eCorner;
  uint32        nVoltageUV;
} VCSCornerVoltageType;


/*
 * VCSRailCornerConfigType
 *
 * BSP Data structure for describing the rail configuration data.
 *
 *  eCornerMin         - The minimum corner at which the rail is allowed to operate
 *  eCornerMax         - The max corner at which the rail is allowed to operate
 *  eCornerInit        - The initial corner at boot-up
 *  eCornerInitThermal - The initial thermal corner restriction at boot-up
 *  HWVersion          - Supported hardware version info
 */
typedef struct
{
  VCSCornerType              eCornerMin;
  VCSCornerType              eCornerMax;
  VCSCornerType              eCornerInit;
  VCSCornerType              eCornerInitThermal;
  VCSHWVersionType           HWVersion;
} VCSRailCornerConfigType;


/*
 * VCSLDOCornerType
 *
 * BSP data structure for describing a corner that the LDO supports as well
 * as how to interpret the fuse info to determine whether a corner should be
 * used on a specific target instance.
 *
 * eCorner     - The corner supported by this LDO.
 * mEnableFuse - Register/mask for corner fuse enablement data.
 */
typedef struct
{
  VCSCornerType  eCorner;
  VCSRegMaskType mEnableFuse;
} VCSLDOCornerType;


/*
 * VCSLDOConfigType
 *
 * BSP data structure for describing the LDO configuration.
 *
 *  eLDO        - LDO enum
 *  szName      - Name of NPA resource for this LDO
 *  pCorners    - Corners used by LDO as well as their fuse enablement data.
 *  nNumCorners - Number of corners
 *  bEnable     - Enable switch for this LDO.
 *  bAutoBypass - use LDO auto bypass mode
 */
typedef struct
{ 
  HAL_ldo_LDOType   eLDO;
  const char       *szName;
  VCSLDOCornerType *pCorners;
  uint32            nNumCorners;
  boolean           bEnable;
  boolean           bAutoBypass;
  VCSCornerType     eMinRailCorner;
  VCSHWVersionType  HWVersion;
} VCSLDOConfigType;


/*
 * VCSCPUConfigType
 *
 * BSP data structure for describing the LDO configuration.
 *
 *  eLDO        - LDO enum
 *  szName      - Name of the NPA client handle for this CPU to vote on the rail
 *  eRail       - Rail enum for this CPU's power source.
 *  pLDODConfig - Pointer to LDO configuration (if applicable, otherwise NULL).
 *
 */
typedef struct
{
  ClockCPUType      eCPU;
  const char       *szName;
  VCSRailType       eRail;
  VCSLDOConfigType *pLDOConfig;
  uint32            nNumLDOConfigs;
} VCSCPUConfigType;


/*
 * VCSNPARemoteDefinitionType
 *
 * BSP Data structure for describing a VCS NPA remote resource.
 *
 *  szName  - Name of remote resource.
 *  szUnits - Name of the resource units or vector resource key.
 */
typedef struct
{
  const char *szName;
  const char *szUnits;
} VCSNPARemoteDefinitionType;


/*
 * VCSNPADefinitionType
 *
 * BSP Data structure for describing a VCS NPA resource.
 *
 *  szName              - Name of local resource.
 *  NPARemoteDefinition - Remote definition for this resource.
 */
typedef struct
{
  const char                 *szName;
  VCSNPARemoteDefinitionType  NPARemoteDefinition;
} VCSNPADefinitionType;


/*
 * VCSRailConfigType
 *
 * BSP Data structure for describing the rail configuration.
 *
 *  eRail             - Rail enum.
 *  szNameLocal       - Name of local rail resource.
 *  pNPAActiveFloor   - Pointer to definition for the active floor resource.
 *  pNPADependency    - Pointer to definition for the dependency resource.
 *  pCornerConfig     - The rail's configuration data.
 *  nNumCornerConfigs - Total number of configurations.
 *  bEnableDVS        - Enable switch for dynamic voltage scaling.
 *  bIsLocal          - Binary state indicator whether the rail is controlled locally.
 */
typedef struct
{
  VCSRailType              eRail;
  const char              *szNameLocal;
  VCSNPADefinitionType    *pNPAActiveFloor;
  VCSNPADefinitionType    *pNPADependency;
  VCSRailCornerConfigType *pCornerConfig;
  uint32                   nNumCornerConfigs;
  boolean                  bEnableDVS;
  boolean                  bIsLocal;
} VCSRailConfigType;


/*
 * VCSBSPConfigType
 *
 * BSP Data structure for list of the rail and CPU configurations.
 *
 *  pRailConfig     - Pointer to array of rail configurations
 *  nNumRailConfigs - Number of rails
 *  pCPUConfig      - Pointer to array of CPU configurations
 *  nNumCPUConfigs  - Number of CPUs
 */
typedef struct
{
  VCSRailConfigType *pRailConfig;
  uint32             nNumRailConfigs;
  VCSCPUConfigType  *pCPUConfig;
  uint32             nNumCPUConfigs;
} VCSBSPConfigType;


#endif  /* __VCSBSP_H__ */ 

