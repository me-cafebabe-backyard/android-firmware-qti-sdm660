#ifndef CLOCKAPPS_H
#define CLOCKAPPS_H
/*
===========================================================================
*/
/**
  @file ClockApps.h

  Internal header file for the clock device driver on the apps image.
*/
/*
  ====================================================================

  Copyright (c) 2010-2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockAppsCPR.h"
#include "ClockAppsBSP.h"
#include "../HALclkLib/HALclkAPCS.h"
#include <npa_resource.h>


/*=========================================================================
      Macro Definitions
==========================================================================*/

#define CLOCK_NOT(a)  (a == TRUE) ? FALSE : TRUE


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of PVS levels.
 */
typedef enum
{
  CLOCK_APPS_PVS0,
  CLOCK_APPS_PVS1,
  CLOCK_APPS_PVS2,
  CLOCK_APPS_PVS3,
  CLOCK_APPS_PVS4,
  CLOCK_APPS_PVS5,
  CLOCK_APPS_PVS6,
  CLOCK_APPS_PVS7,
  CLOCK_APPS_PVS8,
  CLOCK_APPS_PVS9,
  CLOCK_APPS_PVS10,
  CLOCK_APPS_PVS11,
  CLOCK_APPS_PVS12,
  CLOCK_APPS_PVS13,
  CLOCK_APPS_PVS14,
  CLOCK_APPS_PVS15,
  CLOCK_APPS_PVS16,
  CLOCK_APPS_PVS17,
  CLOCK_APPS_PVS18,
  CLOCK_APPS_PVS19,
  CLOCK_APPS_PVS20,
  CLOCK_APPS_PVS21,
  CLOCK_APPS_PVS22,
  CLOCK_APPS_PVS23,
  CLOCK_APPS_PVS24,
  CLOCK_APPS_PVS25,
  CLOCK_APPS_PVS26,
  CLOCK_APPS_PVS27,
  CLOCK_APPS_PVS28,
  CLOCK_APPS_PVS29,
  CLOCK_APPS_PVS30,
  CLOCK_APPS_PVS31,
  CLOCK_APPS_PVS32,
  CLOCK_APPS_PVS33,
  CLOCK_APPS_PVS34,
  CLOCK_APPS_PVS35,
  CLOCK_APPS_PVS36,
  CLOCK_APPS_PVS37,
  CLOCK_APPS_PVS38,
  CLOCK_APPS_PVS39,
  CLOCK_APPS_PVS40,
  CLOCK_APPS_PVS41,
  CLOCK_APPS_PVS42,
  CLOCK_APPS_PVS43,
  CLOCK_APPS_PVS44,
  CLOCK_APPS_PVS45,
  CLOCK_APPS_PVS46,
  CLOCK_APPS_PVS47,
  CLOCK_APPS_PVS48,
  CLOCK_APPS_PVS49,
  CLOCK_APPS_PVS50,
  CLOCK_APPS_PVS51,
  CLOCK_APPS_PVS52,
  CLOCK_APPS_PVS53,
  CLOCK_APPS_PVS54,
  CLOCK_APPS_PVS55,
  CLOCK_APPS_PVS56,
  CLOCK_APPS_PVS57,
  CLOCK_APPS_PVS58,
  CLOCK_APPS_PVS59,
  CLOCK_APPS_PVS60,
  CLOCK_APPS_PVS61,
  CLOCK_APPS_PVS62,
  CLOCK_APPS_PVS63,
  CLOCK_APPS_PVS_TOTAL,
} ClockAppsPVSType;

/**
 * CPU context.
 */
typedef struct
{
  ClockNodeType                 *pClock;
  ClockAppsBSPCPUType           *pBSPConfig;
  ClockAppsPerfLevelConfigType  *pActiveConfig;
  ClockAppsPerfLevelConfigType  *pPreviousConfig;
  uint32                         nMinPerfLevel;
  uint32                         nMaxPerfLevel;
} ClockAppsCPUCtxt;

/**
 * Apps clock driver context.
 */
typedef struct
{
  ClockAppsCPUCtxt    aCPU[CLOCK_APPS_CPU_TOTAL];
  uint32              nVDDCoreMinLevel;
  uint32              nVDDMemMinLevel;
  npa_client_handle   NPAMemHandle;
  uint32              nAccL1Register;
  uint32              nUpliftFuse;
  uint32              nMetalRev;
  ClockAppsPVSType    ePVSBin;
  ClockAppsPVSType    ePVSBinSecondary;
  uint32              nSpeedBinStatus;
  uint32              nSpeedBinRaw;
  uint32              nSpeedBin;
  uint32              nSpeedBinSecondary;
  boolean             bUseExternalBuck;
  ClockVDDAPCCtxtType VDDAPCCtxt[CLOCK_VREG_TOTAL];
  ClockCPRCtxtType    CPRCtxt;
} ClockAppsCtxtType;

/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitXO
** =========================================================================*/
/**
  Initialize the XO management subsystem.

  This function initializes the XO LPR nodes required for communicating
  resource requests to the RPM.

  @param *pDrvCtxt [in] -- The driver context.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/

DALResult Clock_InitXO
(
  ClockDrvCtxt *pDrvCtxt
);

/* =========================================================================
**  Function : Clock_InitAppsVDD
** =========================================================================*/
/**
  Initialize /vdd/apc NPA node.

  This function initializes /vdd/apc NPA node.

  @param *pDrvCtxt   [in] -- The driver context.
  @param eVRegId     [in] -- Voltage regulator identifier.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/

DALResult Clock_InitAppsVDD
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockVRegIdType   eVRegId
);


/* =========================================================================
**  Function : Clock_SetVDDAPCCorner
** =========================================================================*/
/**
  Updates the /vdd/apc voltage.

  This function updates the voltage on the given /vdd/apc rail.

  @param pDrvCtxt    [in] -- Pointer to the driver context.
  @param eCPU        [in] -- CPU core, or Cluster Identifier.
  @param eVRegId     [in] -- Voltage regulator identifier.
  @param pPerfConfig [in] -- New Perf Level.
  @param bCPURequest [in] -- CPU vs. Non-CPU request being made.

  @return
  DAL_SUCCESS -- The voltage corner was successfully applied.
  DAL_ERROR -- The voltage corner was not applied.

  @dependencies
  None.
*/

DALResult Clock_SetVDDAPCCorner
(
  ClockDrvCtxt                  *pDrvCtxt,
  ClockAppsCPUType               eCPU,
  ClockVRegIdType                eVRegId,
  ClockAppsPerfLevelConfigType  *pPerfConfig,
  boolean                        bCPURequest
);


/* =========================================================================
**  Function : Clock_MapVDDAPCCornerToVoltage
** =========================================================================*/
/**
  Maps an APC rail corner index to a raw voltage.

  This function takes in an APC voltage rail corner index and returns a raw voltage.

  @param pDrvCtxt          [in] -- Pointer to the driver context.
  @param eCPU              [in] -- CPU/Cluster identifier.
  @param nCornerTableIndex [in] -- Index into the Corner table for /vdd/apc.

  @return
  Raw voltage in uV.

  @dependencies
  None.
*/

uint32 Clock_MapVDDAPCCornerToVoltage
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockAppsCPUType  eCPU,
  uint32            nCornerTableIndex
);


/* =========================================================================
**  Function : Clock_DetectCPUConfig
** =========================================================================*/
/**
  Detects current CPU configuration

  This function is invoked at driver initialization to detect the current
  CPU configuration.

  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param eCPU [in] -- Which CPU to perform detection on.

  @return
  DAL_ERROR if configuration was not valid, other DAL_SUCCESS.

  @dependencies
  None.
*/

DALResult Clock_DetectCPUConfig
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockAppsCPUType  eCPU
);


/* =========================================================================
**  Function : Clock_GetClusterID
** =========================================================================*/
/**
  Returns the ID of the cluster we are running on.

  This function is used internally to determine the ID of the cluster (0-n)
  that we are currently running on.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pnCluster [in/out] -- Location to store the result.

  @return
  DAL_SUCCESS -- ID returned successfully.
  DAL_ERROR -- NULL parameter.

  @dependencies
  None.
*/

DALResult Clock_GetClusterID
(
  ClockDrvCtxt *pDrvCtxt,
  uint32       *pnCluster
);


/* =========================================================================
**  Function : Clock_GetCoreID
** =========================================================================*/
/**
  Returns the ID of the core we are running on.

  This function is used internally to determine the ID of the core (0-n)
  that we are currently running on.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pnCore [in/out] -- Location to store the result.

  @return
  DAL_SUCCESS -- ID returned successfully.
  DAL_ERROR -- NULL parameter.

  @dependencies
  None.
*/

DALResult Clock_GetCoreID
(
  ClockDrvCtxt *pDrvCtxt,
  uint32       *pnCore
);


/* =========================================================================
**  Function : Clock_SetCoreAffinity
** =========================================================================*/
/**
  Returns the ID of the core we are running on.

  This function is used internally to determine the ID of the core (0-n)
  that we are currently running on.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pnCore [in/out] -- Location to store the result.

  @return
  DAL_SUCCESS -- ID returned successfully.
  DAL_ERROR -- NULL parameter.

  @dependencies
  None.
*/

DALResult Clock_SetCoreAffinity
(
  ClockDrvCtxt *pDrvCtxt,
  uint32        nNew,
  uint32       *pnPrev
);

#if 0
/* =========================================================================
**  Function : Clock_GetLocalNPAResourceClocks
** =========================================================================*/
/**
    Returns a list of clock names that are associated with the given local NPA
    Resource.

    This function takes a name of a local NPA resource and returns the corresponding
    list of clock names.

    @param szResourceName [in]  -- Name of a local NPA resource.
    @param pClockNameList [out] -- Pointer to a list of clock names.

    @return
    DAL_SUCCESS -- A valid clock name list is returned.\n
    DAL_ERROR -- Unable to return a valid clock name list.

    @dependencies
    None.
--*/

DALResult
Clock_GetLocalNPAResourceClocks
(
  char                        *szResourceName,
  LocalNPAResourceClocksList  *pClockNameList
);

#endif 
#endif /* !CLOCKAPPS_H */

