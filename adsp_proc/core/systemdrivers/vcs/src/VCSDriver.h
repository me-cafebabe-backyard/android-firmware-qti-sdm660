#ifndef __VCSDRIVER_H__
#define __VCSDRIVER_H__
/*
===========================================================================
*/
/**
  @file VCSDriver.h 
  
  Internal header file for the VCS device driver.
*/
/*  
  ====================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/src/VCSDriver.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  10/11/16   shm     First version for core.qdsp6.1.0
  01/22/14   lil     Created.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/


#include "com_dtypes.h"
#include "comdef.h"
#include "DALSys.h"
#include "ULogFront.h"
#include "VCSDefs.h"
#include "VCSBSP.h"
#include "npa.h"
#include "npa_remote.h"    // npa_remote_resource_definition
#include "voltage_level.h" // rail_voltage_level


/*=========================================================================
      Macro Definitions
==========================================================================*/


/*
 * Definition for remote VLVL resources that VCS will vote to after
 * aggregating all the local requests. These resources accept VLVL corners.
 */
#define VCS_NPA_RESOURCE_VDD_CX_VLVL     "/vdd/cx/vlvl"
#define VCS_NPA_RESOURCE_VDD_SSCCX_VLVL  "/vdd/ssccx/vlvl"
#define VCS_NPA_RESOURCE_VDD_MX_VLVL     "/vdd/mx/vlvl"
#define VCS_NPA_RESOURCE_VDD_LPICX_VLVL  "/vdd/lpicx/vlvl"
#define VCS_NPA_RESOURCE_VDD_LPIMX_VLVL  "/vdd/lpimx/vlvl"

/**
 * Macros for checking, setting and clearing the global flag bits in the
 * driver context.  Note these work only on the "nGlobalFlags" field
 * within the driver context structure.
 */
#define VCS_GLOBAL_FLAG_IS_SET(flag) ((pDrvCtxt->nGlobalFlags & VCS_GLOBAL_FLAG_##flag) ? TRUE : FALSE)
#define VCS_GLOBAL_FLAG_SET(flag)    (pDrvCtxt->nGlobalFlags |= VCS_GLOBAL_FLAG_##flag)
#define VCS_GLOBAL_FLAG_CLEAR(flag)  (pDrvCtxt->nGlobalFlags &= ~VCS_GLOBAL_FLAG_##flag)


/*
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define VCS_ENUM_32BITS(name) VCS_##name##_32BITS = 0x7FFFFFFF


/*
 * Macro to define the number of resources for each rail NPA node.
 */
#define VCS_NPA_RAIL_NUM_RESOURCES 2


/*
 * Macros to define the index for each rail NPA node resource.
 */
#define VCS_NPA_RAIL_RES_IDX_RAIL          0
#define VCS_NPA_RAIL_RES_IDX_ACTIVE_FLOOR  1


/*
 * Macro to define the number of remote resources for each rail NPA node.
 */
#define VCS_NPA_RAIL_NUM_REMOTE_RESOURCES 2


/*
 * Macros to define the index for each rail NPA remote resource.
 */
#define VCS_NPA_RAIL_REM_RES_IDX_ACTIVE_FLOOR 0
#define VCS_NPA_RAIL_REM_RES_IDX_DEPENDENCY   1


/*
 * Macro to define the number of dependencies for each rail NPA node.
 */
#define VCS_NPA_RAIL_NUM_DEPENDENCIES 3


/*
 * Macros to define the index for each rail NPA node dependency.
 */
#define VCS_NPA_RAIL_DEP_IDX_REQ  0
#define VCS_NPA_RAIL_DEP_IDX_SUP  1
#define VCS_NPA_RAIL_DEP_IDX_SUP2 2

/*
 * Global flag bits
 *  STUB_API - Stubs out entire API (DAL and NPA nodes expected).
 */
#define VCS_GLOBAL_FLAG_STUB_API 0x00000001


/*
 * Flags used to enable/disable various features.
 */
#define VCS_FLAG_DISABLED_BY_USER                       (0x1UL << 0)
#define VCS_FLAG_DISABLED_BY_EFS                        (0x1UL << 1)
#define VCS_FLAG_DISABLED_BY_BSP                        (0x1UL << 2)
#define VCS_FLAG_DISABLED_BY_SWCLIENT                   (0x1UL << 3)
#define VCS_FLAG_DISABLED_BY_CPR                        (0x1UL << 4)
//#define VCS_FLAG_DISABLED__x                          (0x1UL << 5)
#define VCS_FLAG_DISABLED_HW_LOGIC                      (0x1UL << 31)


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Forward declarations.
 */
typedef struct VCSRailNodeType VCSRailNodeType;


/*
 * Pointer to function that sets rail corner.
 */
typedef DALResult (*VCS_SetRailCornerFuncPtr)(VCSRailNodeType *pRail, VCSCornerType eCorner, boolean bIsNASRequest);
typedef npa_query_status (*VCS_RailQueryFuncPtr)(npa_resource *pResource, unsigned int nID, npa_query_type *pResult);


/*
 * VCS Rail Voltage Table type.
 *
 *  pCorner     - Pointer to corner voltage array.
 *  nNumCorners - Number of voltage corners supported.
 *  anCornerMap - Map of corner enum to index in voltage table.
 */
typedef struct VCSLDOVoltageTableType
{
  VCSCornerVoltageType *pCornerVoltage;
  uint32                nNumCornerVoltages;
  VCSCornerVoltageType *apCornerMap[VCS_CORNER_NUM_OF_CORNERS];
} VCSLDOVoltageTableType;


/*
 * VCS LDO node type.
 *
 *  eLDO             - LDO enum.
 *  bIsOn            - Indicates if the LDO is turned ON.
 *  nVoltageUV       - LDO voltage in uV.
 *  nNumRestrictions - Number of restrictions on the LDO. The LDO will be
 *                     disabled if this number is greater than 0.
 *  nDisable         - LDO disable flag.
 *  pVoltageTable    - Voltage table for this LDO.
 *  pBSPConfig       - Pointer to BSP data.
 */
typedef struct VCSLDONodeType
{
  HAL_ldo_LDOType         eLDO;
  VCSCornerType           eCorner;
  uint32                  nVoltageUV;
  uint32                  nNumRestrictions;
  uint32                  nDisable;
  VCSLDOVoltageTableType *pVoltageTable;
  VCSLDOConfigType       *pBSPConfig;
} VCSLDONodeType;


/*
 * VCS CPU node type.
 *
 *  eCPU             - CPU enum.
 *  eCorner          - CPU's voltage corner request.
 *  resource         - NPA resource for this CPU.
 *  dependency       - NPA dependencies for this CPU.
 *  node             - NPA node for this CPU.
 *  pLDO             - Pointer to the LDO node, if any.
 *  pBSPConfig       - Pointer to BSP data.
 */
typedef struct VCSCPUNodeType
{
  ClockCPUType             eCPU;
  VCSCornerType            eCorner;
  npa_resource_definition  resource;
  npa_node_dependency      dependency;
  npa_node_definition      node;
  VCSLDONodeType          *pLDO;
  VCSCPUConfigType        *pBSPConfig;
} VCSCPUNodeType;


/*
 * VCS Corner List type.
 *
 * aCorners            - Array of supported corners.
 * nNumCorners         - Number of supported corners in aCorners array.
 * abIsCornerSupported - Array of boolean flags indicating whether each corner is supported.
 */
typedef struct VCSCornerListType
{
  VCSCornerType *aCorners;
  uint32         nNumCorners;
  boolean        abIsCornerSupported[VCS_CORNER_NUM_OF_CORNERS];
} VCSCornerListType;


/*
 * VCS rail node type.
 *
 *  eRail              - Rail enum ID.
 *  eCorner            - Current rail corner.
 *  eCornerNAS         - NAS rail corner.
 *  nVoltageUV         - Current rail voltage, in uV.
 *  eMode              - Rail mode. Examples: default, CPR.
 *  eCornerInit        - The corner the rail boots up at.
 *  eCornerInitThermal - The initial thermal corner restriction at boot-up
 *  eCornerMin         - The minimum corner the rail can operate at (while active).
 *  eCornerMinSaved    - Used to store original active corner when overriding eCornerMin.
 *  eCornerMax         - The maximum corner the rail can operate at.
 *  pCornerList        - List of corners supported on this rail.
 *  nNumCornerVoltages - Number of corners the rail can operate at on this target.
 *  anCornerMap        - Voltage corner to index map.
 *  nDisableDVS        - Bitfield flag to disable dynamic voltage scaling.
 *  fpSetRailCorner    - Pointer to function that configures rail to requested voltage.
 *  fpRailQuery        - Pointer to function that performs NPA query on rail.
 *  pCPUs              - Array of pointers to CPU nodes powered by this rail.
 *  nNumCPUs           - Number of CPUs in pCPUs.
 *  aResource          - NPA resources for this rail.
 *  aRemoteResources   - NPA remote resources for this rail.
 *  hNode              - NPA node for this rail.
 *  aDependency        - Array of NPA dependencies for this rail.
 *  hClientImpluse     - Impulse NPA client to re-sync the rail state.
 *  hClientThermalInit - NPA client to vote temp init corner for thermal.
 *  nNASRequestCount   - Counter to track the number of NAS requests on rail entering sleep.
 *  bNASCleanup        - Dirty flag indicating that a NAS request(s) occurred for which we need to clean up.
 *  pBSPConfig         - Pointer to BSP data.
 */
struct VCSRailNodeType
{
  VCSRailType                      eRail;
  VCSCornerType                    eCorner;
  VCSCornerType                    eCornerNAS;
  uint32                           nVoltageUV;
  VCSRailModeType                  eMode;

  VCSCornerType                    eCornerInit;
  VCSCornerType                    eCornerInitThermal;
  VCSCornerType                    eCornerMin;
  VCSCornerType                    eCornerMinSaved;
  VCSCornerType                    eCornerMax;

  VCSCornerListType               *pCornerList;

  uint32                           nDisableDVS;

  VCS_SetRailCornerFuncPtr         fpSetRailCorner;
  VCS_RailQueryFuncPtr             fpRailQuery;

  VCSCPUNodeType                 **apCPU;
  uint32                           nNumCPUs;

  npa_resource_definition          aResources[VCS_NPA_RAIL_NUM_RESOURCES];
  npa_remote_resource_definition   aRemoteResources[VCS_NPA_RAIL_NUM_REMOTE_RESOURCES];
  npa_node_definition              hNode;
  npa_node_dependency              aDependencies[VCS_NPA_RAIL_NUM_DEPENDENCIES];
  npa_client_handle                hClientImpulse;
  npa_client_handle                hClientThermalInit;

  uint32                           nNASRequestCount;
  boolean                          bNASCleanup;

  VCSRailConfigType               *pBSPConfig;
};


/*
 * VCS corner description type
 *
 *  eCorner     - VCS corner enum.
 *  eCornerVLVL - VLVL corner enum.
 *  szName      - String name of corner.
 */
typedef struct VCSCornerDescriptionType
{
  VCSCornerType       eCorner;
  rail_voltage_level  eCornerVLVL;
  char               *szName;
} VCSCornerDescriptionType;


/*
 * VCS driver context.
 * 
 *  hVCSLog            - ULOG handle.
 *  nGlobalFlags       - Global flags bit-field.
 *  aRails             - List of rails.
 *  nNumRails          - Number of rails.
 *  aCPUs              - List of CPUs.
 *  nNumCPUs           - Number of CPUs.
 *  apRailUMap         - Map of Rail enum to node pointers.
 *  apCPUMap           - Map of CPU enum to node pointers.
 *  pCornerDescription - Map of VCS corners to VLVL and string names.
 *
 *  pImageCtxt         - Pointer to the image context.
 */
typedef struct VCSDrvCtxt
{
  ULogHandle                      hVCSLog;
  uint32                          nGlobalFlags;

  VCSRailNodeType                *aRails;
  uint32                          nNumRails;

  VCSCPUNodeType                 *aCPUs;
  uint32                          nNumCPUs;

  VCSRailNodeType                *apRailMap[VCS_RAIL_NUM_OF_RAILS];
  VCSCPUNodeType                 *apCPUMap[CLOCK_CPU_NUM_OF_CPUS];

  const VCSCornerDescriptionType *pCornerDescription;

  void                           *pImageCtxt;
} VCSDrvCtxt;


/*=========================================================================
      Externs
==========================================================================*/


extern VCSDrvCtxt *VCS_GetDrvCtxt(void);


/*=========================================================================
      Function Definitions
==========================================================================*/


/* =========================================================================
**  Function : VCS_DriverInit
** =========================================================================*/
/**
  Initialize the VCS driver.

  This function initializes the VCS driver, it is the main init entry
  point.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult VCS_DriverInit
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCSStub_DriverInit
** =========================================================================*/
/**
  Initialize the VCS driver stub.

  This function initializes the VCS driver, it is the main init entry
  point.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.

  @dependencies
  None.
*/

DALResult VCSStub_DriverInit
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCS_DriverDeInit
** =========================================================================*/
/**
  De-initialize the VCS driver.

  This function shuts-down the VCS driver.  It is not expected to ever
  be called.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- De-init was successful.
  DAL_ERROR -- De-init failed.

  @dependencies
  None.
*/

DALResult VCS_DriverDeInit
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCSStub_DriverDeInit
** =========================================================================*/
/**
  De-initialize the VCS driver stub.

  This function shuts-down the VCS driver.  It is not expected to ever
  be called.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- De-init was successful.

  @dependencies
  None.
*/

DALResult VCSStub_DriverDeInit
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCS_InitImage
** =========================================================================*/
/**
  Initialize the image specific portion of the VCS driver.

  This function initializes the portion of the VCS driver that is specific
  to the image we are running on.  This generally corresponds to a particular
  processor on a particular chipset, but also includes the various boot
  images.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult VCS_InitImage
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCSStub_InitImage
** =========================================================================*/
/**
  Initialize the image specific portion of the VCS driver stub.

  This function initializes the portion of the VCS driver that is specific
  to the image we are running on.  This generally corresponds to a particular
  processor on a particular chipset, but also includes the various boot
  images.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.

  @dependencies
  None.
*/

DALResult VCSStub_InitImage
(
  VCSDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : VCS_InitRails
** =========================================================================*/
/**
  Initialize the rail data structures.

  This function initializes the data structures used to control voltage
  rails.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pBSPConfig [in] -- Pointer to the rail BSP config.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult VCS_InitRails
(
  VCSDrvCtxt       *pDrvCtxt,
  VCSBSPConfigType *pBSPConfig
);


/* =========================================================================
**  Function : VCS_SetLDOCorner
** =========================================================================*/
/**
  Process a request to run the LDO at a given corner.

  This function determines if it's possbile to run the LDO at the CPU requested
  corner. If so, enable the LDO. If not, turn it off. Factors that determine
  this include the current rail voltage and whether or not there will be
  enough headroom should the LDO be set to the requested corner.

  @param *pCPU [in]        -- Handle to the CPU node.
  @param  eLDOCorner [in]  -- LDO corner.
  @param  eRailCorner [in] -- Rail corner.

  @return
  DAL_SUCCESS -- Successfully set or disabled the LDD.
  DAL_ERROR_INVALID_PARAMETER -- Invalid handle to the CPU node passed in.

  @dependencies
  The rail must be locked by a parent function prior to invoking this
  function.
*/

DALResult VCS_SetLDOCorner
(
  VCSCPUNodeType *pCPU,
  VCSCornerType   eLDOCorner,
  VCSCornerType   eRailCorner
);


/* =========================================================================
**  Function : VCS_GetPropertyValue
** =========================================================================*/
/**
  Retrieve a VCS driver property from the environment store.

  This function retrieves the given VCS property from the relevant
  storage location (may be DAL properties DB or another source).

  @param *szName [in] -- Name of the property to look up
  @param *pValue [out] -- Location to store the result

  @return
  DAL_SUCCESS -- Property was found and retrieved
  DAL_ERROR -- Otherwise.

  @dependencies
  None.
*/

DALResult VCS_GetPropertyValue
(
  const char            *szName,
  VCSPropertyValueType  *pValue
);


/*=========================================================================
**  Function : VCS_IsBSPSupported
** =========================================================================*/
/**

  This function validates the specified BSP config is supported on the
  executing target chip and version.

  @param pHWVersion [in] - HW Version

  @return
  TRUE - HW version is supported.
  FALSE - HW version is not supported.

  @dependencies
  None.
*/

boolean VCS_IsBSPSupported
(
  VCSHWVersionType *pHWVersion
);


/* =========================================================================
**  Function : VCS_DetectRailBSPVersion
** =========================================================================*/
/**
  Detects which rail BSP configuration to use for the current HW.

  @param pRail [in]          -- Pointer rail node.
  @param pCornerConfig [out] -- Pointer to rail corner config pointer.
  @return
  DAL_ERROR if a valid configuration was not found, other DAL_SUCCESS.

  @dependencies
  None.
*/

DALResult VCS_DetectRailBSPVersion
(
  VCSRailNodeType          *pRail,
  VCSRailCornerConfigType **pCornerConfig
);


/* =========================================================================
**  Function : VCS_DetectLDOConfigBSPVersion
** =========================================================================*/
/**
  Detects which LDO BSP configuration to use for the current HW.

  @param pCPU [in]          -- Pointer CPU node.
  @param pLDOConfig [out]   -- Pointer to LDO config pointer.
  @return
  DAL_ERROR if a valid configuration was not found, other DAL_SUCCESS.

  @dependencies
*/

DALResult VCS_DetectLDOConfigBSPVersion
(
  VCSCPUNodeType    *pCPU,
  VCSLDOConfigType **pLDOConfig
);


/* =========================================================================
**  Function : VCS_MapHWIORegion
** =========================================================================*/
/**
  Map a HWIO region into memory for the VCS driver.

  This function maps a physical HWIO region into memory for the VCS driver
  using environment appropriate APIs.  If the mapping is not available
  the virtual address will be set to the provided physical address.

  @param nPhysAddr [in] -- Physical address.
  @param nSizeBytes [in] -- Size of the region in bytes.
  @param *pnVirtAddr [out] -- Location to store the mapped address.

  @return
  DAL_SUCCESS -- Mapping was OK
  DAL_ERROR -- Error code based on failure.

  @dependencies
  None.
*/

DALResult VCS_MapHWIORegion
(
  uint32  nPhysAddr,
  uint32  nSizeBytes,
  uint32 *pnVirtAddr
);


/* =========================================================================
**  Function : VCS_InitCPUs
** =========================================================================*/
/**
  Initialize the CPU / LDO data structures for a given rail.

  This function initializes the data structures used to service CPU requests.

  @param *pRail [in] -- Pointer to the rail node.
  @param *pBSPConfig [in] -- Pointer to the CPU BSP config.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult VCS_InitCPUs
(
  VCSDrvCtxt       *pDrvCtxt,
  VCSBSPConfigType *pBSPConfig
);


/* =========================================================================
**  Function : VCS_InitNPAResources
** =========================================================================*/
/**
  Create an NPA resource node for each rail and LDO.

  This function creates an NPA resource based on BSP data.

  @param pDrvCtxt[in] -- Pointer to the driver context.

  @return
  DAL_SUCCESS -- Sucessfully created NPA resources.
  DAL_ERROR -- Failed to create NPA resources.

  @dependencies
  None.
*/

DALResult VCS_InitNPAResources
(
  VCSDrvCtxt *pDrvCtxt
);


/*=========================================================================
      Function Definitions From DDIVCS.h
==========================================================================*/


DALResult VCS_SetRailMode(VCSDrvCtxt *pDrvCtxt, VCSRailType eRail, VCSRailModeType eMode, const void *pModeData);

DALResult VCS_SetRailVoltage(VCSDrvCtxt *pDrvCtxt, VCSRailType eRail, uint32 nVoltageUV);

DALResult VCS_AddLDORestriction(VCSDrvCtxt *pDrvCtxt, ClockCPUType eCPU);

DALResult VCS_RemoveLDORestriction(VCSDrvCtxt *pDrvCtxt, ClockCPUType eCPU);

void VCS_LoadNV(void);

#endif /* !__VCS_DRIVER_H__ */

