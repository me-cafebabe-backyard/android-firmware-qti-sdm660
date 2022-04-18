/*
===========================================================================
*/
/**
  @file VCSNPA.c

  NPA-related functions for the VCS driver.
*/
/*
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated. All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/src/VCSNPA.c#1 $
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
#include "DDIPlatformInfo.h"
#include "VCSDriver.h"
#include "pmapp_npa.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "npa.h"
#include "npa_scheduler.h"
#include "npa_remote_resource.h"
#include "VCSSWEVT.h"

/*=========================================================================
      Macros
==========================================================================*/


#define VCS_NPA_UNITS_RAIL              "VReg Corner"
#define VCS_NPA_UNITS_LDO               "0/1"
#define VCS_NPA_NAS_TRIGGER_EVENT_NAME  "VCS NAS Event"


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Prototypes
==========================================================================*/


static unsigned int VCS_NPARailResourceCreateClientCallback(npa_client *, unsigned int, void *);

static npa_resource_state VCS_NPAMaxUpdateFunction(npa_resource *, npa_client_handle);

static npa_resource_state VCS_NPAEmptyDriverFunc(npa_resource *, npa_client_handle, npa_resource_state);


/*=========================================================================
      Data
==========================================================================*/


/*
 * VCS customer wrapper for the NPA provided max plugin.
 * This is needed to intercept client votes and take additional measures
 * when the vote is being placed to satisfy a CPU's voltage requirement.
 */
static npa_resource_plugin VCS_NPAMaxPlugin;


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : VCS_NPARailResourceCreateClientCallback
** =========================================================================*/
/**
  Callback to take action when specific clients of voltage rail resources
  are being created. This function looks to identify CPU clients so that
  VCS can take the appropriate action when future votes are made by these
  clients that require additional checks to be made when satisfying the
  voltage requirement.

  @param *hClient     [in] -- Pointer to the client being created.
  @param  nClientValue[in] -- Non-zero indicates this client is a CPU.
  @param *pClientData [in] -- Integer value representing the CPU identifier.

  @return
  unsigned in - 0 if the client is valid and should be created.
                1 if the client is not valid and should not be created.

  @dependencies
  None.
*/

static unsigned int VCS_NPARailResourceCreateClientCallback
(
  npa_client   *hClient,
  unsigned int  nClientValue,
  void         *pClientData
)
{
  VCSDrvCtxt     *pDrvCtxt;
  VCSCPUNodeType *pCPU;
  ClockCPUType   *pCPUID;
  boolean         bIsCPUClient;

  /*-----------------------------------------------------------------------*/
  /* Return success for all non-CPU clients.                               */
  /*-----------------------------------------------------------------------*/

  bIsCPUClient = (boolean)nClientValue;
  if (bIsCPUClient != TRUE)
  {
    return 0;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify the CPU ID encoded in the nClientValue field.                  */
  /*-----------------------------------------------------------------------*/

  pCPUID = (ClockCPUType *)pClientData;
  if (pCPUID == NULL || *pCPUID >= CLOCK_CPU_NUM_OF_CPUS)
  {
    return 1;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the driver context.                                               */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Find the CPU node and store it in the client user data.               */
  /*-----------------------------------------------------------------------*/

  pCPU = pDrvCtxt->apCPUMap[*pCPUID];
  if (pCPU != NULL)
  {
    hClient->resource_data = (npa_user_data)pCPU;
    return 0;
  }

  return 1;

} /* END VCS_NPARailResourceCreateClientCallback */


/* =========================================================================
**  Function : VCS_NPAEmptyDriverFunc
** =========================================================================*/
/**
  Empty resource driver function

  This is a dummy function to satisfy NPA node requirement of a
  driver function for every resource.

  @param *pResource [in] -- Pointer to rail resource.
  @param  hClient [in] -- Client handle.
  @param  nState [in] -- New request state.

  @return
  New resource state.

  @dependencies
  None.
*/
npa_resource_state VCS_NPAEmptyDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  if(hClient->type == NPA_CLIENT_INITIALIZE)
  {
    return nState;
  }
  else
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Voting on resource[%s] not supported.",
      pResource->definition->name);

    return (npa_resource_state)0;
  }
} /* END VCS_NPAEmptyDriverFunc */


/* =========================================================================
**  Function : VCS_NPAMaxUpdateFunction
** =========================================================================*/
/**
  Update function for the VCS wrapper around the NPA provided max plugin.
  The need for this wrapper is to take special action when the voter is a
  CPU client.  The UNCONDITIONAL_NEXT attribute is set on the rail resource
  to force the driver function to execute so that the CPU's LDO state can
  get updated if applicable.

  @param *pResource[in] -- Pointer to the resource being voted on.
  @param  hClient  [in] -- Client who submitted the vote.

  @return
  npa_resource_state - Result of aggregation and new active state.

  @dependencies
  None.
*/

static npa_resource_state VCS_NPAMaxUpdateFunction
(
  npa_resource      *pResource,
  npa_client_handle  hClient
)
{
  npa_resource_state nUpdatedState;

  /*-----------------------------------------------------------------------*/
  /* Invoke NPA provided max update function.                              */
  /*-----------------------------------------------------------------------*/

  nUpdatedState = npa_max_plugin.update_fcn(pResource, hClient);

  /*-----------------------------------------------------------------------*/
  /* Set UNCONDITIONAL_NEXT for CPU clients.                               */
  /*-----------------------------------------------------------------------*/

  if (hClient->resource_data != NULL)
  {
    npa_set_resource_attribute(
      pResource,
      NPA_RESOURCE_DRIVER_UNCONDITIONAL_NEXT);
  }

  return nUpdatedState;

} /* END VCS_NPAMaxUpdateFunction */

/* =========================================================================
**  Function : VCS_NPACPUResourceQuery
** =========================================================================*/
/**
  NPA CPU resource query function.

  This function is called to get the following CPU information:
    -- Current corner (id / table index).
    -- Current voltage

  @param *pResource  [in]  -- Pointer to the resource in question
  @param  nID        [in]  -- ID of the query.
  @param *pResult    [out] -- Pointer to the data to be filled by this function.

  @return
  npa_query_status - NPA_QUERY_SUCCESS, if query supported.
                   - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  @dependencies
  None.
*/

static npa_query_status VCS_NPACPUResourceQuery
(
  npa_resource   *pResource,
  unsigned int    nID,
  npa_query_type *pResult
)
{
  VCSCPUNodeType       *pCPU;
  VCSLDONodeType       *pLDO;
  VCSCornerVoltageType *pCornerVoltage;
  uint32                nCorner;

  /*-----------------------------------------------------------------------*/
  /* Validate parameters.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pResource == NULL || pResult == NULL)
  {
    return NPA_QUERY_NULL_POINTER;
  }

  pCPU = (VCSCPUNodeType *)pResource->node->data;

  /*-----------------------------------------------------------------------*/
  /* Validate CPU pointer.                                                 */
  /*-----------------------------------------------------------------------*/

  if (pCPU == NULL)
  {
    return NPA_QUERY_NO_VALUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for the current corner.                                         */
  /*-----------------------------------------------------------------------*/

  if (nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_LEVEL_ID)
  {
    /*
     * Store current corner request.
     */
    pResult->data.value = pCPU->eCorner;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate LDO pointer.                                                 */
  /*-----------------------------------------------------------------------*/

  pLDO = (VCSLDONodeType *)pCPU->pLDO;
  if (pLDO == NULL)
  {
    return NPA_QUERY_NO_VALUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for the current voltage.                                        */
  /*-----------------------------------------------------------------------*/

  if (nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_VOLTAGE_UV)
  {
    /*
     * Store current voltage request.
     */
    pResult->data.value = pLDO->nVoltageUV;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Only process voltage related queries if we have a voltage table.      */
  /*-----------------------------------------------------------------------*/

  if (pLDO->pVoltageTable == NULL)
  {
    return NPA_QUERY_NO_VALUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Store the number of entries in the corner voltage table.              */
  /*-----------------------------------------------------------------------*/

  if (nID == VCS_NPA_QUERY_VOLTAGE_NUM_ENTRIES)
  {
    pResult->data.value = pLDO->pVoltageTable->nNumCornerVoltages;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Store the number of entries in the corner voltage table.              */
  /*-----------------------------------------------------------------------*/

  if(nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_VOLTAGE_UV)
  {
    pResult->data.value = pLDO->nVoltageUV;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Store the corner enum for the requested level.                        */
  /*-----------------------------------------------------------------------*/

  if (nID >= VCS_NPA_QUERY_VOLTAGE_LEVEL_ID &&
      nID < VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR)
  {
    nCorner = nID - VCS_NPA_QUERY_VOLTAGE_LEVEL_ID;
    if (nCorner >= pLDO->pVoltageTable->nNumCornerVoltages)
    {
      return NPA_QUERY_UNSUPPORTED_QUERY_ID;
    }
    else
    {
      pCornerVoltage = &pLDO->pVoltageTable->pCornerVoltage[nCorner];
      pResult->data.value = pCornerVoltage->eCorner;
      pResult->type = NPA_QUERY_TYPE_VALUE;

      return NPA_QUERY_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Store the voltage for the requested level.                            */
  /*-----------------------------------------------------------------------*/

  if (nID >= VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR &&
      nID < VCS_NPA_QUERY_VOLTAGE_LEVEL_CEILING)
  {
    nCorner = nID - VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR;
    if (nCorner >= pLDO->pVoltageTable->nNumCornerVoltages)
    {
      return NPA_QUERY_UNSUPPORTED_QUERY_ID;
    }
    else
    {
      pCornerVoltage = &pLDO->pVoltageTable->pCornerVoltage[nCorner];
      pResult->data.value = pCornerVoltage->nVoltageUV;
      pResult->type = NPA_QUERY_TYPE_VALUE;

      return NPA_QUERY_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Store the voltage for the requested level.                            */
  /*-----------------------------------------------------------------------*/

  else if (nID >= VCS_NPA_QUERY_VOLTAGE_LEVEL_CEILING &&
           nID < VCS_NPA_QUERY_VOLTAGE_LEVEL_MVC_SAFE)
  {
    nCorner = nID - VCS_NPA_QUERY_VOLTAGE_LEVEL_CEILING;
    if (nCorner >= pLDO->pVoltageTable->nNumCornerVoltages)
    {
      return NPA_QUERY_UNSUPPORTED_QUERY_ID;
    }
    else
    {
      pCornerVoltage = &pLDO->pVoltageTable->pCornerVoltage[nCorner];
      pResult->data.value = pCornerVoltage->nVoltageUV;
      pResult->type = NPA_QUERY_TYPE_VALUE;

      return NPA_QUERY_SUCCESS;
    }
  }

  return NPA_QUERY_UNSUPPORTED_QUERY_ID;

} /* END VCS_NPACPUResourceQuery */


/* =========================================================================
**  Function : VCS_NPASetLDOVoltages
** =========================================================================*/
/**
  Set's the voltage for each LDO on the specified rail and switches the CPU

  This function makes NPA requests on the rail's resource dependencies.

  @param *pRail [in] -- Pointer to rail node.
  @param *eCorner [in] -- Corner of the rail.

  @dependencies
  None.
*/

static void VCS_NPASetLDOVoltages
(
  VCSRailNodeType *pRail,
  VCSCornerType    eCorner
)
{
  uint32          i;
  DALResult       eResult;
  VCSCPUNodeType *pCPU;
  VCSLDONodeType *pLDO;

  /*-----------------------------------------------------------------------*/
  /* Verify arguments.                                                     */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Invalid NULL pointer passed to SetLDOVoltages");

    return;
  }

  for (i = 0; i < pRail->nNumCPUs; i++)
  {
    pCPU = pRail->apCPU[i];
    pLDO = pCPU->pLDO;

    /*
     * Check if the LDO can now be enabled.
     */
    if (pLDO && !pLDO->nDisable)
    {
      eResult = VCS_SetLDOCorner(pCPU, pCPU->eCorner, eCorner);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          0,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "DALLOG Device VCS: Unable to set LDO[%s] to voltage[%lu]",
          pLDO->pBSPConfig->szName,
          eCorner);

        return;
      }
    }
  }

} /* END of VCS_NPASetLDOVoltages */


/* =========================================================================
**  Function : VCS_NPAVoteDependency
** =========================================================================*/
/**
  Issue an NPA request on the rail resource dependency.

  This function makes an NPA request on a specific rail dependency resource.

  @param *pRail [in] -- Pointer to rail node.
  @param  hClientFrom [in] -- Client handle used by client to send the initial request.
  @param  hClientTo [in] -- Client handle used by VCS to satisfy the dependency.
  @param  eCorner [in] -- Corner vote.

  @dependencies
  None.
*/

static void VCS_NPAVoteDependency
(
  VCSRailNodeType   *pRail,
  npa_client_handle  hClientFrom,
  npa_client_handle  hClientTo,
  VCSCornerType      eCorner
)
{
  VCSDrvCtxt    *pDrvCtxt;
  VCSCornerType  eCornerAdjusted;
  uint32         nCornerVote;

  eCornerAdjusted = eCorner;

  /*-----------------------------------------------------------------------*/
  /* Bring votes up to within the supported range if vote is not OFF.      */
  /*-----------------------------------------------------------------------*/

  if (eCornerAdjusted != VCS_CORNER_OFF)
  {
    eCornerAdjusted = MAX(eCornerAdjusted, pRail->eCornerMin);

    if (pRail->pCornerList)
    {
      for ( ;
           eCornerAdjusted < VCS_CORNER_NUM_OF_CORNERS &&
           eCornerAdjusted <= pRail->eCornerMax;
           eCornerAdjusted++)
      {
        if (pRail->pCornerList->abIsCornerSupported[eCornerAdjusted] != FALSE)
        {
          break;
        }
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Validate eCornerAdjusted <= max supported corner.                     */
  /*-----------------------------------------------------------------------*/

  if (eCornerAdjusted > pRail->eCornerMax)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Request[%lu] on rail[%s] above max corner[%lu]",
      eCornerAdjusted,
      pRail->pBSPConfig->szNameLocal,
      pRail->eCornerMax);

    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Set request attribute to fire-and-forget if we are setting a lower    */
  /* voltage corner.                                                       */
  /*-----------------------------------------------------------------------*/

  if (eCornerAdjusted < pRail->eCorner)
  {
    npa_set_request_attribute(hClientTo, NPA_REQUEST_FIRE_AND_FORGET);
  }

  /*-----------------------------------------------------------------------*/
  /* Propagate the NAS attribute if it was used in the original request.   */
  /*-----------------------------------------------------------------------*/

  npa_pass_request_attributes(hClientFrom, hClientTo);

  /*-----------------------------------------------------------------------*/
  /* Get the driver context.                                               */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Issue the request to satisfy the dependency.                          */
  /* Map the vote to VLVL if the vote is going to RPM (not local).         */
  /*-----------------------------------------------------------------------*/

  if (pRail->pBSPConfig->pNPADependency->NPARemoteDefinition.szName != NULL)
  {
    nCornerVote = pDrvCtxt->pCornerDescription[eCornerAdjusted].eCornerVLVL;
  }
  else
  {
    nCornerVote = eCornerAdjusted;
  }

  npa_issue_scalar_request(hClientTo, nCornerVote);

} /* END of VCS_NPAVoteDependency */


/* =========================================================================
**  Function : VCS_NPASatisfyRailDependencies
** =========================================================================*/
/**
  Issue NPA requests on the rail's resource dependencies.

  This function makes NPA requests on the rail's resource dependencies.

  @param *pRail [in] -- Pointer to rail node.
  @param *pResource [in] -- Pointer to rail resource.
  @param  hClient [in] -- Client handle.

  @dependencies
  None.
*/

static void VCS_NPASatisfyRailDependencies
(
  VCSRailNodeType   *pRail,
  npa_resource      *pResource,
  npa_client_handle  hClient
)
{
  /*-----------------------------------------------------------------------*/
  /* Determine which client handle to use and which value to send.         */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_SUPPRESSIBLE ||
      hClient->type == NPA_CLIENT_IMPULSE)
  {
    VCS_NPAVoteDependency(
      pRail,
      hClient,
      pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_SUP].handle,
      (VCSCornerType)NPA_RESOURCE_SUPPRESSIBLE_REQUEST(pResource));
  }

  if (hClient->type == NPA_CLIENT_SUPPRESSIBLE2 ||
      hClient->type == NPA_CLIENT_IMPULSE)
  {
    VCS_NPAVoteDependency(
      pRail,
      hClient,
      pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_SUP2].handle,
      (VCSCornerType)NPA_RESOURCE_SUPPRESSIBLE2_REQUEST(pResource));
  }

  if (hClient->type == NPA_CLIENT_REQUIRED ||
      hClient->type == NPA_CLIENT_IMPULSE)
  {
    VCS_NPAVoteDependency(
      pRail,
      hClient,
      pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_REQ].handle,
      (VCSCornerType)NPA_RESOURCE_REQUIRED_REQUEST(pResource));
  }

} /* END of VCS_NPASatisfyRailDependencies */


/* =========================================================================
**  Function : VCS_NPARailResourceQuery
** =========================================================================*/
/**
  NPA rail resource query function.

  This function is called to get the following rail information:
    -- Number of corners.
    -- Voltage table for each corner.
    -- Current corner (id / table index).

  @param *pResource  [in]  -- Pointer to the resource in question
  @param  nID        [in]  -- ID of the query.
  @param *pResult    [out] -- Pointer to the data to be filled by this function.

  @return
  npa_query_status - NPA_QUERY_SUCCESS, if query supported.
                   - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  @dependencies
  None.
*/

static npa_query_status VCS_NPARailResourceQuery
(
  npa_resource   *pResource,
  unsigned int    nID,
  npa_query_type *pResult
)
{
  npa_query_status nStatus = NPA_QUERY_SUCCESS;
  uint32           nCorner;
  VCSRailNodeType *pRail = (VCSRailNodeType *)pResource->node->data;

  /*-----------------------------------------------------------------------*/
  /* Validate parameters.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pResource == NULL || pResult == NULL || pRail == NULL)
  {
    return NPA_QUERY_NULL_POINTER;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for the current corner.                                         */
  /*-----------------------------------------------------------------------*/

  if(nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_LEVEL_ID)
  {
    /*
     * Store current corner request.
     */
    pResult->data.value = pRail->eCorner;
    pResult->type = NPA_QUERY_TYPE_VALUE;

    return NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Only process voltage related queries if we have a corner list.        */
  /*-----------------------------------------------------------------------*/

  if (pRail->pCornerList == NULL)
  {
    return NPA_QUERY_UNSUPPORTED_QUERY_ID;
  }

  if (nID == VCS_NPA_QUERY_VOLTAGE_NUM_ENTRIES)
  {
    /*
     * Store the number of entries in the corner voltage table.
     */
    pResult->data.value = pRail->pCornerList->nNumCorners;
    pResult->type = NPA_QUERY_TYPE_VALUE;
  }
  else if(nID == VCS_NPA_QUERY_VOLTAGE_CURRENT_VOLTAGE_UV)
  {
    /*
     * Store current voltage request.
     */
    pResult->data.value = pRail->nVoltageUV;
    pResult->type = NPA_QUERY_TYPE_VALUE;
  }
  else if (nID >= VCS_NPA_QUERY_VOLTAGE_LEVEL_ID &&
           nID < VCS_NPA_QUERY_VOLTAGE_LEVEL_FLOOR)
  {
    nCorner = nID - VCS_NPA_QUERY_VOLTAGE_LEVEL_ID;
    if (nCorner >= pRail->pCornerList->nNumCorners)
    {
      nStatus = NPA_QUERY_UNSUPPORTED_QUERY_ID;
    }
    else
    {
      pResult->data.value = pRail->pCornerList->aCorners[nCorner];
      pResult->type = NPA_QUERY_TYPE_VALUE;
    }
  }
  else
  {
    /*
     * Call the rail specific query function if available.
     */
    if (pRail->fpRailQuery != NULL)
    {
      nStatus = pRail->fpRailQuery(pResource, nID, pResult);
    }
  }

  return nStatus;

} /* END VCS_NPARailResourceQuery */


/* =========================================================================
**  Function : VCS_NPARailNASEventCallback
** =========================================================================*/
/**
  Callback on wake-up for NAS requests submitted to the rail.

  This function is called by the NPA framework upon wake-up for a NAS
  request that was submitted to the rail prior to sleep.

  @param *pData [in] -- Event data.

  @return
  None.

  @dependencies
  None.
*/

static void VCS_NPARailNASEventCallback
(
  void *pData
)
{
  VCSDrvCtxt              *pDrvCtxt;
  VCSRailNodeType         *pRail;
  VCSNPARailEventDataType  RailEventData;
  npa_resource            *pRailResource;
  npa_client_handle        hClient;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  hClient = (npa_client_handle)pData;
  if (hClient == NULL)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Missing required data argument to NPA rail NAS event callback on wake up.");
  }

  /*-----------------------------------------------------------------------*/
  /* Get the rail resource from the client.                                */
  /*-----------------------------------------------------------------------*/

  pRailResource = hClient->resource;

  /*-----------------------------------------------------------------------*/
  /* Get the rail node from the resource.                                  */
  /*-----------------------------------------------------------------------*/

  pRail = (VCSRailNodeType *)pRailResource->node->data;

  /*-----------------------------------------------------------------------*/
  /* Get the driver context.                                               */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Log the NAS Callback                                                  */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_4(
    pDrvCtxt->hVCSLog,
    "Rail[%s] NAS event callback for Client[0x%x] Vote[%s] Stored NAS Corner[%s]",
    pRail->pBSPConfig->szNameLocal,
    hClient,
    pDrvCtxt->pCornerDescription[NPA_ACTIVE_REQUEST(hClient).state].szName,
    pDrvCtxt->pCornerDescription[pRail->eCornerNAS].szName);

  /*-----------------------------------------------------------------------*/
  /* NPA will potentially invoke this event trigger callback once for each */
  /* NAS request that was made.  We only take action on the first event    */
  /* notification because that was the final NAS state of the resource.    */
  /*-----------------------------------------------------------------------*/

  if (pRail->nNASRequestCount == 0)
  {
    return;
  }

  pRail->nNASRequestCount = 0;

  /*-----------------------------------------------------------------------*/
  /* If there is no pending NAS request it means that an immediate request */
  /* was already satisfied before the NPA scheduler dispatched this        */
  /* callback and thus we must ignore it.                                  */
  /*-----------------------------------------------------------------------*/

  if (pRail->eCornerNAS == VCS_CORNER_OFF)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* The active state does not get updated on NAS wake up events for rails */
  /* that are locally managed because the rail could still be settling.    */
  /* Instead, a dirty flag is set and the onus is on the requesting client */
  /* to resubmit the voltage request (or trigger IMPULSE on the resource)  */
  /* to indicate that it wishes to block the call path until the rail has  */
  /* finished settling.                                                    */
  /*-----------------------------------------------------------------------*/

  pRailResource = pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL].handle;

  if (pRail->pBSPConfig->bIsLocal)
  {
    /*
     * Keep track of inconsistent state.
     */
    pRail->bNASCleanup = TRUE;

    /*
     * Set the UNCONDITIONAL flag to bypass short-circuiting on the next
     * request to support NPA cleanup when a rude wake up is detected.
     */
    npa_set_resource_attribute(
      pRailResource,
      NPA_RESOURCE_DRIVER_UNCONDITIONAL_NEXT);

    /*
     * Make it clear in log that the state is inconsistent.
     */
    ULOG_RT_PRINTF_1(
      pDrvCtxt->hVCSLog,
      "Rail[%s] potentially still settling - waiting for client to reconcile NAS state.",
      pRail->pBSPConfig->szNameLocal);

    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Fill out event data for rail state change.                            */
  /*-----------------------------------------------------------------------*/

  RailEventData.PreChange.eCorner = pRail->eCorner;
  RailEventData.PostChange.eCorner = pRail->eCornerNAS;

  /*-----------------------------------------------------------------------*/
  /* Notify NPA clients of post-switch event.                              */
  /*-----------------------------------------------------------------------*/

  npa_dispatch_custom_events(
    pRailResource,
    (npa_event_type)VCS_NPA_RAIL_EVENT_POST_CHANGE,
    &RailEventData);

  /*-----------------------------------------------------------------------*/
  /* Update rail context.                                                  */
  /*-----------------------------------------------------------------------*/

  pRail->eCorner = pRail->eCornerNAS;

  /*-----------------------------------------------------------------------*/
  /* Clear NAS corner state.                                               */
  /*-----------------------------------------------------------------------*/

  pRail->eCornerNAS = VCS_CORNER_OFF;

  /*-----------------------------------------------------------------------*/
  /* Log the state update.                                                 */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_3(
    pDrvCtxt->hVCSLog,
    "Rail[%s] switch end - Vote[%s] NAS[1] End State[%s]",
    pRail->pBSPConfig->szNameLocal,
    pDrvCtxt->pCornerDescription[NPA_ACTIVE_REQUEST(hClient).state].szName,
    pDrvCtxt->pCornerDescription[pRail->eCorner].szName);

  /*-----------------------------------------------------------------------*/
  /* Log the NAS Callback                                                  */
  /*-----------------------------------------------------------------------*/

  VCS_SWEvent(VCS_EVENT_RAIL_NAS_WAKEUP, 2, pRail->eRail, pRail->eCorner);

  /*-----------------------------------------------------------------------*/
  /* Switch CPU's to LDO mode if possible.                                 */
  /*-----------------------------------------------------------------------*/

  VCS_NPASetLDOVoltages(pRail, pRail->eCorner);

  /*-----------------------------------------------------------------------*/
  /* A future implementation may include support for defining a timer      */
  /* callback to guarantee that we wait for the rail to settle and         */
  /* re-enable CPR to put the SW/HW in a consistent state.                 */
  /*-----------------------------------------------------------------------*/

} /* END of VCS_NPARailNASEventCallback */


/* =========================================================================
**  Function : VCS_NPARailDriverFunc
** =========================================================================*/
/**
  Handle request state changes on a rail's NPA resource.

  This is a generic NPA driver function applicable to all rail resources.
  This function does some common record keeping, and makes use of function
  pointers to invoke rail-specific functions to actually set the voltage.

  @param *pResource [in] -- Pointer to rail resource.
  @param  hClient [in] -- Client handle.
  @param  nState [in] -- New request state.

  @return
  New resource state.

  @dependencies
  None.
*/

static npa_resource_state VCS_NPARailResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  uint32                   nUpdatedState = 0;
  boolean                  bIsNASRequest;
  DALResult                eResult;
  VCSRailNodeType         *pRail;
  VCSCPUNodeType          *pCPU;
  VCSCornerType            eCornerAggregated;
  VCSNPARailEventDataType  RailEventData;
  VCSDrvCtxt              *pDrvCtxt;

  pRail = (VCSRailNodeType *)pResource->node->data;
  eCornerAggregated = (VCSCornerType)nState;

  /*-----------------------------------------------------------------------*/
  /* Do nothing for init.                                                  */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    return pRail->eCornerInit;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for NAS attribute.                                              */
  /*-----------------------------------------------------------------------*/

  if (npa_request_has_attribute(hClient, NPA_REQUEST_NEXT_AWAKE))
  {
    bIsNASRequest = TRUE;
  }
  else
  {
    bIsNASRequest = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Check if client is a CPU.                                             */
  /*-----------------------------------------------------------------------*/

  pCPU = (VCSCPUNodeType *)hClient->resource_data;
  if (pCPU != NULL)
  {
    /*
     * Update the CPU corner context.
     */
    pCPU->eCorner = (VCSCornerType)NPA_PENDING_REQUEST(hClient).state;

    /*
     * Log the CPU corner request.
     */
    VCS_SWEvent(
      VCS_EVENT_RAIL_CPU_CORNER_VOTE_RECEIVED,
      3,
      pCPU->eCPU,
      pCPU->eCorner,
      pRail->eRail);
  }

  /*-----------------------------------------------------------------------*/
  /* Log the corner vote received                                          */
  /*-----------------------------------------------------------------------*/

  VCS_SWEvent(
    VCS_EVENT_RAIL_CORNER_VOTE_RECEIVED,
    3,
    pRail->eRail,
    pRail->eCorner,
    bIsNASRequest);

  /*-----------------------------------------------------------------------*/
  /* If any non-HW disable DVS bit is set then set the rail to max.        */
  /*-----------------------------------------------------------------------*/

  if (pRail->nDisableDVS & ~VCS_FLAG_DISABLED_HW_LOGIC)
  {
    eCornerAggregated = pRail->eCornerMax;
  }

  /*-----------------------------------------------------------------------*/
  /* Round the request up within the supported range.                      */
  /*-----------------------------------------------------------------------*/

  if (eCornerAggregated != VCS_CORNER_OFF)
  {
    eCornerAggregated = MAX(eCornerAggregated, pRail->eCornerMin);

    /*
     * If a voltage table is present then find the min supported corner that
     * is greater than a equal to the request state.
     */
    if (pRail->pCornerList)
    {
      for ( ;
           eCornerAggregated < VCS_CORNER_NUM_OF_CORNERS &&
           eCornerAggregated <= pRail->eCornerMax;
           eCornerAggregated++)
      {
        if (pRail->pCornerList->abIsCornerSupported[eCornerAggregated] != FALSE)
        {
          break;
        }
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Error if the voltage corner exceeds the current max corner.           */
  /*-----------------------------------------------------------------------*/

  if (eCornerAggregated > pRail->eCornerMax)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Request[%lu] on rail[%s] above max corner[%lu]",
      nState,
      pRail->pBSPConfig->szNameLocal,
      pRail->eCornerMax);

    return (npa_resource_state)pRail->eCorner;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the driver context.                                               */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Log the corner request.                                               */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_5(
    pDrvCtxt->hVCSLog,
    "Rail[%s] switch start - Vote[%s] NAS[%lu] CPU[%s] State[%s]",
    pRail->pBSPConfig->szNameLocal,
    pDrvCtxt->pCornerDescription[NPA_PENDING_REQUEST(hClient).state].szName,
    bIsNASRequest > 0 ? 1 : 0,
    pCPU != NULL ? pCPU->pBSPConfig->szName : "-",
    pDrvCtxt->pCornerDescription[pResource->active_state].szName);

  /*-----------------------------------------------------------------------*/
  /* Clear the FIRE_AND_FORGET attribute because this resource makes no    */
  /* use of that resource and the NPA framework makes decisions if that    */
  /* attribute is set that are unfriendly for local NAS aware resources.   */
  /*-----------------------------------------------------------------------*/

  hClient->request_attr &= ~NPA_REQUEST_FIRE_AND_FORGET;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if not in default mode.                                 */
  /*-----------------------------------------------------------------------*/

  if (pRail->eMode != VCS_RAIL_MODE_DEFAULT)
  {
    ULOG_RT_PRINTF_1(
      pDrvCtxt->hVCSLog,
      "Rail[%s] not in default mode - short circuiting",
      pRail->pBSPConfig->szNameLocal);

    pRail->eCorner = eCornerAggregated;

    return (npa_resource_state)pRail->eCorner;
  }

  /*-----------------------------------------------------------------------*/
  /* Check whether NAS request requires additional NPA interaction.        */
  /*-----------------------------------------------------------------------*/

  if (bIsNASRequest)
  {
    /*
     * Process NAS requests that result in a change to the active state.
     */
    if (pResource->request_state != pResource->active_state)
    {
      /*
       * Store the new max NAS request
       */
      pRail->eCornerNAS = eCornerAggregated;

      /*
       * Increment the NAS request counter while entering sleep.
       * This is used to match the number of NAS event callbacks invoked.
       */
      pRail->nNASRequestCount++;

      /*
       * Register w/NPA for NAS wake up events.
       */
      npa_notify_next_awake(VCS_NPARailNASEventCallback, (void *)hClient);
    }

    /*
     * If the request is not resulting in an update to the active state then
     * let the flow continue so that all dependencies can get satisfied.
     */
  }

  /*-----------------------------------------------------------------------*/
  /* This is an immediate request.                                         */
  /*                                                                       */
  /* The NPA framework doesn't support immediate requests that occur after */
  /* NAS requests but before going through a sleep transition.  Raise an   */
  /* error here if that case is detected.                                  */
  /*-----------------------------------------------------------------------*/

  else if (pRail->eCornerNAS != VCS_CORNER_OFF &&
           npa_is_next_wakeup_after_nas() != TRUE)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Rail[%s] Invalid CAS request for corner[%s] when pending NAS request for corner[%s].",
      pRail->pBSPConfig->szNameLocal,
      pDrvCtxt->pCornerDescription[NPA_PENDING_REQUEST(hClient).state].szName,
      pDrvCtxt->pCornerDescription[pRail->eCornerNAS].szName);

    return pResource->active_state;
  }

  /*-----------------------------------------------------------------------*/
  /* Handle the case where request on rail increased.                      */
  /*-----------------------------------------------------------------------*/

  if (eCornerAggregated > pResource->active_state ||
      (pRail->bNASCleanup == TRUE && eCornerAggregated > pRail->eCorner))
  {
    /*
     * Fill out event data for rail state change.
     */
    RailEventData.bIsNAS = bIsNASRequest;
    RailEventData.PreChange.eCorner = pRail->eCorner;
    RailEventData.PostChange.eCorner = eCornerAggregated;

    /*
     * Notify NPA clients of pre-switch event.
     */
    npa_dispatch_custom_events(
      pResource,
      (npa_event_type)VCS_NPA_RAIL_EVENT_PRE_CHANGE,
      &RailEventData);

    /*
     * Satisfy rail dependency.
     */
    VCS_NPASatisfyRailDependencies(pRail, pResource, hClient);

    /*
     * Increase the rail voltage to requested corner.
     */
    if (pRail->fpSetRailCorner)
    {
      eResult = pRail->fpSetRailCorner(pRail, eCornerAggregated, bIsNASRequest);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          0,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "DALLOG Device VCS: Unable to set rail[%s] to corner[%s]",
          pRail->pBSPConfig->szNameLocal,
          pDrvCtxt->pCornerDescription[eCornerAggregated].szName);
      }
    }

    /*
     * The rail would not have settled yet for NAS requests.
     * Skip the following steps for NAS requests:
     *  - Broadcast corner change complete event.
     *  - Enable LDO if possible.
     */
    if (bIsNASRequest)
    {
      return (npa_resource_state)eCornerAggregated;
    }

    /*
     * Notify NPA clients of post-switch event.
     */
    npa_dispatch_custom_events(
      pResource,
      (npa_event_type)VCS_NPA_RAIL_EVENT_POST_CHANGE,
      &RailEventData);

    /*
     * Switch CPU's to LDO mode if possible.
     */
    VCS_NPASetLDOVoltages(pRail, eCornerAggregated);
  }

  /*-----------------------------------------------------------------------*/
  /* Handle the case where request on rail decreased.                      */
  /*-----------------------------------------------------------------------*/

  else if (eCornerAggregated < pResource->active_state ||
           (pRail->bNASCleanup == TRUE && eCornerAggregated < pRail->eCorner))
  {
    /*
     * Switch CPU's to BHS mode if required.
     */
    VCS_NPASetLDOVoltages(pRail, eCornerAggregated);

    /*
     * Fill out event data for rail state change.
     */
    RailEventData.bIsNAS = bIsNASRequest;
    RailEventData.PreChange.eCorner = pRail->eCorner;
    RailEventData.PostChange.eCorner = eCornerAggregated;

    /*
     * Notify NPA clients of pre-switch event.
     */
    npa_dispatch_custom_events(
      pResource,
      (npa_event_type)VCS_NPA_RAIL_EVENT_PRE_CHANGE,
      &RailEventData);

    /*
     * Decrease the rail voltage to requested corner.
     */
    if (pRail->fpSetRailCorner)
    {
      eResult = pRail->fpSetRailCorner(pRail, eCornerAggregated, bIsNASRequest);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          0,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "DALLOG Device VCS: Unable to set rail[%s] to corner[%s]",
          pRail->pBSPConfig->szNameLocal,
          pDrvCtxt->pCornerDescription[eCornerAggregated].szName);
      }
    }

    /*
     * Satisfy rail dependency.
     */
    VCS_NPASatisfyRailDependencies(pRail, pResource, hClient);

    /*
     * The rail would not have settled yet for NAS requests.
     * Skip the following steps for NAS requests:
     *  - Broadcast corner change complete event.
     */
    if (bIsNASRequest)
    {
      return (npa_resource_state)eCornerAggregated;
    }

    /*
     * Notify NPA clients of post-switch event.
     */
    npa_dispatch_custom_events(
      pResource,
      (npa_event_type)VCS_NPA_RAIL_EVENT_POST_CHANGE,
      &RailEventData);
  }

  /*-----------------------------------------------------------------------*/
  /* Handle the case where the aggregated request state hasn't changed.    */
  /* Potential reasons for the driver function being invoked here:         */
  /*                                                                       */
  /* - CPU voltage requirement changed but the resulting aggregation did   */
  /*   not cause the rail to change.  It's possible that the CPU's eLDO    */
  /*   state might need to be updated.                                     */
  /*                                                                       */
  /* - Change in voltage table from EFS settlings require a voltage change */
  /*   for the current corner. The EFS logic in VCSMSS.c will trigger an   */
  /*   impulse to the resource that will poke this driver function but     */
  /*   with the same request state so the image specific code in VCSMSS.c  */
  /*   must be invoked in order to adjust the current corner voltage.      */
  /*                                                                       */
  /* - Exiting from MVC mode requires a re-sync process for the rail to    */
  /*   get VCS, PMIC, and CPR all back in control and consistent state.    */
  /*                                                                       */
  /* - No change in the overall request state but a change in the          */
  /*   aggregated request state for a particular client type. This is      */
  /*   needed to adjust dependency votes without changing the active state.*/
  /*-----------------------------------------------------------------------*/

  else
  {
    ULOG_RT_PRINTF_1(
      pDrvCtxt->hVCSLog,
      "Rail[%s] no change in corner.",
      pRail->pBSPConfig->szNameLocal);

    /*
     * Handle the case where the CPU voltage vote changed and now the LDO
     * state needs to be updated accordingly.
     */
    if (pCPU != NULL &&
        pCPU->pLDO != NULL &&
        !pCPU->pLDO->nDisable)
    {
      eResult = VCS_SetLDOCorner(pCPU, pCPU->eCorner, pRail->eCorner);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          0,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "DALLOG Device VCS: Unable to set LDO[%s] to corner[%s]",
          pCPU->pLDO->pBSPConfig->szName,
          pDrvCtxt->pCornerDescription[pCPU->eCorner].szName);
      }
    }

    /*
     * Handle the case when the request was made by an impulse client.
     * The dependencies may need to get adjusted due to a change
     * in the active floor. We force the dependency vote to go through
     * and let NPA perform the short-circuiting.
     */
    if (hClient->type == NPA_CLIENT_IMPULSE)
    {
      ULOG_RT_PRINTF_2(
        pDrvCtxt->hVCSLog,
        "Rail[%s] impulse client forced voltage update on corner[%s].",
        pRail->pBSPConfig->szNameLocal,
        pDrvCtxt->pCornerDescription[eCornerAggregated].szName);

      /*
       * Invoke the rail specific voltage update function.
       */
      if (pRail->fpSetRailCorner)
      {
        eResult = pRail->fpSetRailCorner(pRail, eCornerAggregated, FALSE);
        if (eResult != DAL_SUCCESS)
        {
          DALSYS_LogEvent(
            0,
            DALSYS_LOGEVENT_FATAL_ERROR,
            "DALLOG Device VCS: Unable to set rail[%s] to corner[%s]",
            pRail->pBSPConfig->szNameLocal,
            pDrvCtxt->pCornerDescription[eCornerAggregated].szName);
        }
      }

      VCS_NPASatisfyRailDependencies(pRail, pResource, hClient);
    }

    /*
     * Handle the case where the overall aggregated state didn't change but
     * the aggregated votes for either required or suppressible alone have
     * changed and thus we must update the dependency accordingly.
     */
    else
    {
      if (hClient->type == NPA_CLIENT_SUPPRESSIBLE)
      {
        nUpdatedState = NPA_RESOURCE_SUPPRESSIBLE_REQUEST(pResource);
      }
      else if (hClient->type == NPA_CLIENT_SUPPRESSIBLE2)
      {
        nUpdatedState = NPA_RESOURCE_SUPPRESSIBLE2_REQUEST(pResource);
      }
      else if (hClient->type == NPA_CLIENT_REQUIRED)
      {
        nUpdatedState = NPA_RESOURCE_REQUIRED_REQUEST(pResource);
      }

      if ((NPA_PENDING_REQUEST(hClient).state <
             NPA_ACTIVE_REQUEST(hClient).state &&
           nUpdatedState < NPA_ACTIVE_REQUEST(hClient).state) ||
          (NPA_PENDING_REQUEST(hClient).state >
             NPA_ACTIVE_REQUEST(hClient).state &&
           nUpdatedState > NPA_ACTIVE_REQUEST(hClient).state))
      {
        ULOG_RT_PRINTF_2(
          pDrvCtxt->hVCSLog,
          "Rail[%s] change in dependency.",
          pRail->pBSPConfig->szNameLocal,
          pDrvCtxt->pCornerDescription[eCornerAggregated].szName);

        VCS_NPASatisfyRailDependencies(pRail, pResource, hClient);
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Log the voltage corner switch.                                        */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_4(
    pDrvCtxt->hVCSLog,
    "Rail[%s] switch end - Vote[%s] Post-NAS-Sync[%lu] State[%s]",
    pRail->pBSPConfig->szNameLocal,
    pDrvCtxt->pCornerDescription[NPA_PENDING_REQUEST(hClient).state].szName,
    pRail->eCornerNAS != VCS_CORNER_OFF ? 1 : 0,
    pDrvCtxt->pCornerDescription[eCornerAggregated].szName);

  VCS_SWEvent(
    VCS_EVENT_RAIL_CORNER_VOTE_COMPLETE,
    3,
    pRail->eRail,
    eCornerAggregated,
    bIsNASRequest);

  /*
   * Update the context.
   */
  pRail->eCorner = eCornerAggregated;

  /*
   * Perform NAS post rail change events now that rail has settled.
   */
  if (pRail->eCornerNAS != VCS_CORNER_OFF)
  {
    pRail->bNASCleanup = FALSE;
    pRail->eCornerNAS = VCS_CORNER_OFF;

    /*
     * Log NAS cleanup complete
     */
    VCS_SWEvent(VCS_EVENT_RAIL_NAS_COMPLETE, 2, pRail->eRail, pRail->eCorner);
  }

  /*-----------------------------------------------------------------------*/
  /* Return the current rail corner.                                       */
  /*-----------------------------------------------------------------------*/

  return (npa_resource_state)pRail->eCorner;

} /* END VCS_NPARailResourceDriverFunc */


/* =========================================================================
**  Function : VCS_NPARailActiveFloorResourceDriverFunc
** =========================================================================*/
/**
  Handle request state changes on a rail's active floor NPA resource.

  This is a generic NPA driver function applicable to all rail resources.
  This function will update the active floor for the requested rail and
  send an IMPULSE request to the rail driver function if necessary.

  @param *pResource [in] -- Pointer to rail resource.
  @param  hClient [in] -- Client handle.
  @param  nState [in] -- New request state.

  @return
  New resource state.

  @dependencies
  None.
*/

static npa_resource_state VCS_NPARailActiveFloorResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{

  VCSRailNodeType *pRail;

  pRail = (VCSRailNodeType *)pResource->node->data;

  /*-----------------------------------------------------------------------*/
  /* Do nothing for init.                                                  */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    /*
     * Save the initial min corner.
     */
    pRail->eCornerMinSaved = pRail->eCornerMin;

    return pRail->eCornerMin;
  }

  /*-----------------------------------------------------------------------*/
  /* Error if the voltage corner exceeds the current max corner.           */
  /*-----------------------------------------------------------------------*/

  if (nState > pRail->eCornerMax)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Active floor request[%lu] on rail[%s] above max corner[%lu]",
      nState,
      pRail->pBSPConfig->szNameLocal,
      pRail->eCornerMax);

    return (npa_resource_state)pRail->eCornerMin;
  }

  /*-----------------------------------------------------------------------*/
  /* The new active floor corner is the greater between the resource vote  */
  /* and the original active floor.                                        */
  /*-----------------------------------------------------------------------*/

  pRail->eCornerMin = (VCSCornerType)MAX(pRail->eCornerMinSaved, nState);

  /*-----------------------------------------------------------------------*/
  /* Trigger impulse on rail to account for new active floor.              */
  /*-----------------------------------------------------------------------*/

  npa_issue_impulse_request(pRail->hClientImpulse);

  return (npa_resource_state)pRail->eCornerMin;

} /* END VCS_NPARailActiveFloorResourceDriverFunc */


/* =========================================================================
**  Function : VCS_NPARailNodeDriverFunc
** =========================================================================*/
/**
  Handle request for a state change on a rail's resource.

  This is a generic NPA driver function applicable to all rail resources.
  This function will update the requested rail's resource and
  send an IMPULSE request to the rail driver function if necessary.

  @param *pResource [in] -- Pointer to rail resource.
  @param  hClient [in] -- Client handle.
  @param  nState [in] -- New request state.

  @return
  New resource state.

  @dependencies
  None.
*/

static npa_resource_state VCS_NPARailNodeDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  VCSRailNodeType    *pRail;
  npa_resource_state  nActiveState;
  npa_resource       *pRailResource;
  npa_resource       *pRailActiveFloorResource;

  pRail = (VCSRailNodeType *)pResource->node->data;
  pRailResource =
    pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL].handle;
  pRailActiveFloorResource =
    pRail->aResources[VCS_NPA_RAIL_RES_IDX_ACTIVE_FLOOR].handle;
  nActiveState = 0;

  if (pResource == pRailResource)
  {
    nActiveState =
      VCS_NPARailResourceDriverFunc(
        pResource,
        hClient,
        nState);
  }
  else if (pResource == pRailActiveFloorResource)
  {
    nActiveState =
      VCS_NPARailActiveFloorResourceDriverFunc(
        pResource,
        hClient,
        nState);
  }
  else
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to process NPA request for rail[%s]",
	  pRail->pBSPConfig->szNameLocal);
  }

  return nActiveState;

} /* END VCS_NPARailNodeDriverFunc */


/* =========================================================================
**  Function : VCS_NPARailNodeAvailableCallback
** =========================================================================*/
/**
  Callback after a rail node is created.

  This function is called by the NPA framework after a rail node
  is created.  The creation is delayed until all dependencies are also
  created.

  @param *pContext     [in] -- Context passed in npa_define_node_cb
  @param nEventType    [in] -- Zero.
  @param *pNodeName    [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/

static void VCS_NPARailNodeAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pNodeName,
  unsigned int  nNodeNameSize
)
{
  VCSRailNodeType         *pRail;
  npa_resource_definition *pRailResourceDef;
  npa_resource_definition *pRailActiveFloorResourceDef;

  pRail = (VCSRailNodeType *)pContext;
  pRailResourceDef =
    &pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL];
  pRailActiveFloorResourceDef =
    &pRail->aResources[VCS_NPA_RAIL_RES_IDX_ACTIVE_FLOOR];

  /*-----------------------------------------------------------------------*/
  /* Create an impulse client for this rail node.                          */
  /*-----------------------------------------------------------------------*/

  pRail->hClientImpulse =
    npa_create_sync_client(
      pRailResourceDef->name,
      pRailResourceDef->name,
      NPA_CLIENT_IMPULSE);
  if (pRail->hClientImpulse == NULL)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Failed to create impulse client for rail[%s]",
      pRailResourceDef->name);
  }

  /*-----------------------------------------------------------------------*/
  /* Create a temp thermal init client and vote based on the BSP setting.  */
  /*-----------------------------------------------------------------------*/

  if (pRail->eCornerInitThermal != VCS_CORNER_OFF)
  {
    pRail->hClientThermalInit =
      npa_create_sync_client(
        pRailActiveFloorResourceDef->name,
        "VCS Thermal Init",
        NPA_CLIENT_REQUIRED);
    if (pRail->hClientThermalInit == NULL)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to create required client for temporary thermal init on rail[%s].",
        pRailActiveFloorResourceDef->name);
    }

    /*
     * Issue temporary thermal vote.
     */
    npa_issue_required_request(
      pRail->hClientThermalInit,
      pRail->eCornerInitThermal);
  }

} /* END of VCS_NPARailNodeAvailableCallback */


/* =========================================================================
**  Function : VCS_InitNPAResourceCPU
** =========================================================================*/
/*
  Initialize the NPA structures for this CPU.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pCPU [in] -- Pointer to CPU being initialized.

  @return
  DAL_SUCCESS -- Successfully initialized the NPA structures for this CPU.
  DAL_ERROR_INVALID_PARAMETER -- Invalid pointer.

  @dependencies
  None.
*/

DALResult VCS_InitNPAResourceCPU
(
  VCSDrvCtxt     *pDrvCtxt,
  VCSCPUNodeType *pCPU
)
{
  VCSRailNodeType    *pRail;
  npa_resource_state  nInitialState;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pCPU == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Identify rail dependency.                                             */
  /*-----------------------------------------------------------------------*/

  pRail = pDrvCtxt->apRailMap[pCPU->pBSPConfig->eRail];
  if (pRail == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Populate resource.                                                    */
  /*-----------------------------------------------------------------------*/

  pCPU->resource.name       = pCPU->pBSPConfig->szName;
  pCPU->resource.units      = VCS_NPA_UNITS_RAIL;
  pCPU->resource.max        = 0;
  pCPU->resource.plugin     = &npa_no_client_plugin;
  pCPU->resource.attributes = NPA_RESOURCE_DEFAULT;
  pCPU->resource.data       = (npa_user_data)pCPU;
  pCPU->resource.query_fcn  = VCS_NPACPUResourceQuery;

  /*-----------------------------------------------------------------------*/
  /* Populate node information.                                            */
  /*-----------------------------------------------------------------------*/

  pCPU->node.name             = pCPU->pBSPConfig->szName;
  pCPU->node.driver_fcn       = VCS_NPAEmptyDriverFunc;
  pCPU->node.attributes       = NPA_NODE_DEFAULT;
  pCPU->node.data             = (npa_user_data)pCPU;
  pCPU->node.resource_count   = 1;
  pCPU->node.resources        = &pCPU->resource;

  /*-----------------------------------------------------------------------*/
  /* Get the resource's initial state.                                     */
  /*-----------------------------------------------------------------------*/

  nInitialState = (npa_resource_state)0;

  /*-----------------------------------------------------------------------*/
  /* Define the rail NPA node.                                             */
  /*-----------------------------------------------------------------------*/

  npa_define_node(&pCPU->node, &nInitialState, NULL);

  /*-----------------------------------------------------------------------*/
  /* Done.                                                                 */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END VCS_InitNPAResourceCPU */


/* =========================================================================
**  Function : VCS_InitNPAResourceRail
** =========================================================================*/
/**
  Initialize the NPA structures for this voltage rail.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pRail [in] -- Pointer to voltage rail being initialized.

  @return
  DAL_SUCCESS -- Successfully initialized the NPA structures for this rail.
  DAL_ERROR_INVALID_PARAMETER -- Invalid pointer.

  @dependencies
  None.
*/

DALResult VCS_InitNPAResourceRail
(
  VCSDrvCtxt      *pDrvCtxt,
  VCSRailNodeType *pRail
)
{
  npa_resource_state              anInitialState[VCS_NPA_RAIL_NUM_RESOURCES];
  npa_node_dependency            *pDependency;
  npa_remote_resource_definition *pRemoteResource;
  npa_resource_definition        *pRailResource;
  uint32                          nNumResources;

  /*-----------------------------------------------------------------------*/
  /* Validate pointers.                                                    */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Populate rail resource.                                               */
  /*-----------------------------------------------------------------------*/

  nNumResources = 0;

  pRailResource = &pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL];
  pRailResource->name       = pRail->pBSPConfig->szNameLocal;
  pRailResource->units      = VCS_NPA_UNITS_RAIL;
  pRailResource->max        = VCS_CORNER_MAX;
  pRailResource->plugin     = &VCS_NPAMaxPlugin;
  pRailResource->attributes = NPA_RESOURCE_DEFAULT |
                              NPA_RESOURCE_IMPULSE_UNCONDITIONAL;
  pRailResource->data       = (npa_user_data)pRail;
  pRailResource->query_fcn  = VCS_NPARailResourceQuery;

  anInitialState[VCS_NPA_RAIL_RES_IDX_RAIL] =
    (npa_resource_state)pRail->eCorner;

  nNumResources++;

  /*-----------------------------------------------------------------------*/
  /* Populate local rail active floor resource.                            */
  /*-----------------------------------------------------------------------*/

  if (pRail->pBSPConfig->pNPAActiveFloor->NPARemoteDefinition.szName == NULL)
  {
    pRailResource = &pRail->aResources[VCS_NPA_RAIL_RES_IDX_ACTIVE_FLOOR];
    pRailResource->name       = pRail->pBSPConfig->pNPAActiveFloor->szName;
    pRailResource->units      = VCS_NPA_UNITS_RAIL;
    pRailResource->max        = VCS_CORNER_MAX;
    pRailResource->plugin     = &npa_max_plugin;
    pRailResource->attributes = NPA_RESOURCE_DEFAULT |
                                NPA_RESOURCE_IMPULSE_UNCONDITIONAL;
    pRailResource->data       = (npa_user_data)pRail;
    pRailResource->query_fcn  = NULL;

    anInitialState[VCS_NPA_RAIL_RES_IDX_ACTIVE_FLOOR] =
      (npa_resource_state)pRail->eCornerMin;

    nNumResources++;
  }

  /*-----------------------------------------------------------------------*/
  /* Create the remote active floor resource.                              */
  /*-----------------------------------------------------------------------*/

  else
  {
    pRemoteResource =
      &pRail->aRemoteResources[VCS_NPA_RAIL_REM_RES_IDX_ACTIVE_FLOOR];
    pRemoteResource->local_resource_name =
      (char *)pRail->pBSPConfig->pNPAActiveFloor->szName;
    pRemoteResource->remote_resource_name =
      (char *)pRail->pBSPConfig->pNPAActiveFloor->NPARemoteDefinition.szName;
    pRemoteResource->protocol_type = "/protocol/rpm/rpm";
    pRemoteResource->plugin = &npa_max_plugin,
    pRemoteResource->driver_fcn =
      npa_remote_resource_local_aggregation_driver_fcn;
    pRemoteResource->units =
      pRail->pBSPConfig->pNPAActiveFloor->NPARemoteDefinition.szUnits;
    pRemoteResource->max = NPA_MAX_STATE;
    pRemoteResource->attributes = NPA_RESOURCE_REMOTE_NO_INIT;

    npa_remote_define_resource(pRemoteResource, 0, NULL);
  }

  /*-----------------------------------------------------------------------*/
  /* Create remote dependency resource.                                    */
  /*-----------------------------------------------------------------------*/

  if (pRail->pBSPConfig->pNPADependency->NPARemoteDefinition.szName != NULL)
  {
    pRemoteResource =
      &pRail->aRemoteResources[VCS_NPA_RAIL_REM_RES_IDX_DEPENDENCY];
    pRemoteResource->local_resource_name =
      (char *)pRail->pBSPConfig->pNPADependency->szName;
    pRemoteResource->remote_resource_name =
      (char *)pRail->pBSPConfig->pNPADependency->NPARemoteDefinition.szName;
    pRemoteResource->protocol_type = "/protocol/rpm/rpm";
    pRemoteResource->plugin = &npa_max_plugin,
    pRemoteResource->driver_fcn =
      npa_remote_resource_local_aggregation_driver_fcn;
    pRemoteResource->units =
      pRail->pBSPConfig->pNPADependency->NPARemoteDefinition.szUnits;
    pRemoteResource->max = NPA_MAX_STATE;
    pRemoteResource->attributes = NPA_RESOURCE_REMOTE_NO_INIT;

    npa_remote_define_resource(pRemoteResource, 0, NULL);
  }

  /*-----------------------------------------------------------------------*/
  /* Create a dependency client for each type supported by NPA.            */
  /*-----------------------------------------------------------------------*/

  pDependency = &pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_REQ];
  pDependency->name = pRail->pBSPConfig->pNPADependency->szName;
  pDependency->client_type = NPA_CLIENT_REQUIRED;

  pDependency = &pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_SUP];
  pDependency->name = pRail->pBSPConfig->pNPADependency->szName;
  pDependency->client_type = NPA_CLIENT_SUPPRESSIBLE;

  pDependency = &pRail->aDependencies[VCS_NPA_RAIL_DEP_IDX_SUP2];
  pDependency->name = pRail->pBSPConfig->pNPADependency->szName;
  pDependency->client_type = NPA_CLIENT_SUPPRESSIBLE2;

  /*-----------------------------------------------------------------------*/
  /* Populate node information.                                            */
  /*-----------------------------------------------------------------------*/

  pRail->hNode.name             = pRail->pBSPConfig->szNameLocal;
  pRail->hNode.driver_fcn       = VCS_NPARailNodeDriverFunc;
  pRail->hNode.attributes       = NPA_NODE_DEFAULT;
  pRail->hNode.data             = (npa_user_data)pRail;
  pRail->hNode.dependency_count = VCS_NPA_RAIL_NUM_DEPENDENCIES;
  pRail->hNode.dependencies     = pRail->aDependencies;
  pRail->hNode.resource_count   = nNumResources;
  pRail->hNode.resources        = pRail->aResources;

  /*-----------------------------------------------------------------------*/
  /* Define the rail NPA node.                                             */
  /*-----------------------------------------------------------------------*/

  npa_define_node_cb(
    &pRail->hNode,
    anInitialState,
    VCS_NPARailNodeAvailableCallback,
    pRail);

  /*-----------------------------------------------------------------------*/
  /* Done.                                                                 */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END VCS_InitNPAResourceRail */


/* =========================================================================
**  Function : VCS_InitNPAResources
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCS_InitNPAResources
(
  VCSDrvCtxt *pDrvCtxt
)
{
  uint32    i;
  DALResult eResult;

  /*-----------------------------------------------------------------------*/
  /* Initialize the custom VCS max plugin used for all the rails.          */
  /*-----------------------------------------------------------------------*/

  VCS_NPAMaxPlugin.update_fcn =
    VCS_NPAMaxUpdateFunction;

  VCS_NPAMaxPlugin.supported_clients =
    npa_max_plugin.supported_clients;

  VCS_NPAMaxPlugin.create_client_ex_fcn =
    VCS_NPARailResourceCreateClientCallback;

  /*-----------------------------------------------------------------------*/
  /* Iterate through all the rails to define rail resources.               */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumRails; i++)
  {
    eResult = VCS_InitNPAResourceRail(pDrvCtxt, &pDrvCtxt->aRails[i]);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to create NPA resource for rail.");

      return eResult;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Iterate through all the CPUs to define LDO resources.                 */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumCPUs; i++)
  {
    eResult = VCS_InitNPAResourceCPU(pDrvCtxt, &pDrvCtxt->aCPUs[i]);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to create NPA resource for CPU.");

      return eResult;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Done.                                                                 */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END VCS_InitNPAResources */

/* =========================================================================
**  Function : VCS_InitThermal
** =========================================================================*/
/*
  Clear out the initial thermal restriction vote on each rail.

  This function gets invoked by the RCINIT framework when the thermal SW
  component has completed initializing.  The agreement with themal SW is that
  by this time it will have issued a voltage vote against all rails to establish
  a voltage corner floor if necessary.

  @param
  None.

  @return
  None.

  @dependencies
  None.
*/

void VCS_InitThermal
(
  void
)
{
  VCSDrvCtxt      *pDrvCtxt;
  VCSRailNodeType *pRail;
  uint32           nCount;

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Remove temporary thermal vote on each rail.                           */
  /*-----------------------------------------------------------------------*/

  for (nCount = 0; nCount < pDrvCtxt->nNumRails; nCount++)
  {
    pRail = &pDrvCtxt->aRails[nCount];
    if (pRail->hClientThermalInit)
    {
      npa_complete_request(pRail->hClientThermalInit);
    }
  }

} /* END VCS_InitThermal */
