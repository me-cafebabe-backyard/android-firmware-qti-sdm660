/*
===========================================================================
*/
/**
  @file VCSCPU.c 
  
  LDO-related functions for the VCS driver.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated. All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/src/VCSCPU.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/


#include <DALSys.h>
#include "VCSDriver.h"
#include "HALldo.h"
#include "DALDeviceId.h"
#include <npa_resource.h>
#include "VCSSWEVT.h"
#include "HALhwio.h"

/*=========================================================================
      Externs
==========================================================================*/


/*=========================================================================
      Prototypes
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : VCS_InitLDOVoltageTable
** =========================================================================*/
/**
  Initializes the voltage table for this HW version.

  @param pLDO [in]         -- Pointer rail node.
  @param pCornerConfig [in] -- Pointer rail corner config for this HW version.
  @return
  DAL_ERROR if a voltage table not initialized, other DAL_SUCCESS.

  @dependencies
  None.
*/

static DALResult VCS_InitLDOVoltageTable
(
  VCSLDONodeType   *pLDO,
  VCSLDOConfigType *pLDOConfig

)
{
  DALResult               eResult;
  uint32                  i, nSize;
  VCSCornerType           eCorner;
  VCSRegMaskType         *pRegMask;
  VCSLDOVoltageTableType *pVoltageTable;
  VCSCornerVoltageType   *pCornerVoltage;
  boolean                 bIsCornerSupported[VCS_CORNER_NUM_OF_CORNERS];

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pLDO == NULL || pLDOConfig == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }


  /*-----------------------------------------------------------------------*/
  /* Validate the BSP config.                                              */
  /*-----------------------------------------------------------------------*/

  if (pLDOConfig->nNumCorners == 0 ||
      pLDOConfig->nNumCorners >= VCS_CORNER_NUM_OF_CORNERS ||
      pLDOConfig->pCorners == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Short circuit if the LDO is not enabled.                              */
  /*-----------------------------------------------------------------------*/

  if (pLDO->nDisable)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Allocate storage for LDO voltage table.                               */
  /*-----------------------------------------------------------------------*/

  nSize = sizeof(*pLDO->pVoltageTable);

  eResult = DALSYS_Malloc(nSize, (void **)&pLDO->pVoltageTable);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to allocate %lu bytes for LDO[%s].",
      nSize,
      pLDO->pBSPConfig->szName);

    return eResult;
  }

  memset((void *)pLDO->pVoltageTable, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Init supported corner flag for each entry before usage.               */
  /*-----------------------------------------------------------------------*/

  memset((void *)bIsCornerSupported, 0x0, sizeof(bIsCornerSupported));

  /*-----------------------------------------------------------------------*/
  /* Count how many corner voltage entries must be allocated for this LDO. */
  /*-----------------------------------------------------------------------*/

  pVoltageTable = pLDO->pVoltageTable;
  for (i = 0; i < pLDOConfig->nNumCorners; i++)
  {
    eCorner = pLDOConfig->pCorners[i].eCorner;
    if (eCorner >= VCS_CORNER_NUM_OF_CORNERS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid corner[%lu] for LDO[%s] specified in BSP",
        eCorner,
        pLDO->pBSPConfig->szName);

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Only read the efuse register if it is non-zero.
     * Enable support for the corner for either of the below cases:
     *  - Fuse register is zero (i.e. no assigned fuse).
     *  - Fuse register is non-zero and the enablement field is non-zero
     *    after a bitwise AND operation with the assigned bit mask.
     */
    pRegMask = &pLDOConfig->pCorners[i].mEnableFuse;
    if (pRegMask->nAddr == 0 ||
        in_dword_masked(pRegMask->nAddr, pRegMask->nMask))
    {
      pVoltageTable->nNumCornerVoltages++;
      bIsCornerSupported[eCorner] = TRUE;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Allocate storage for corner voltages.                                 */
  /*-----------------------------------------------------------------------*/

  nSize =
    pVoltageTable->nNumCornerVoltages * sizeof (*pVoltageTable->pCornerVoltage);

  eResult = DALSYS_Malloc(nSize, (void **)&pVoltageTable->pCornerVoltage);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to allocate %lu bytes for LDO[%s].",
      nSize,
      pLDO->pBSPConfig->szName);

    return eResult;
  }

  memset((void *)pVoltageTable->pCornerVoltage, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Populate allocated memory with supported corner data.                 */
  /*-----------------------------------------------------------------------*/

  pCornerVoltage = pVoltageTable->pCornerVoltage;
  for (i = 0; i < VCS_CORNER_NUM_OF_CORNERS; i++)
  {
    if (bIsCornerSupported[i] == TRUE)
    {
      pCornerVoltage->eCorner = i;

      /*
       * Update map to point to the voltage list entry.
       */
      pVoltageTable->apCornerMap[i] = pCornerVoltage;

      /*
       * Increment pointer to next entry in allocated array of supported corners.
       */
      pCornerVoltage++;
    }
  }

  return DAL_SUCCESS;

} /* END VCS_InitLDOVoltageTable */


/* =========================================================================
**  Function : VCS_InitLDO
** =========================================================================*/
/**
  Initializes the LDO structures for the specified CPU.

  @param pCPU [in] -- Pointer to CPU node.
  @return
  DAL_ERROR if LDO couldn't be initialized, other DAL_SUCCESS.

  @dependencies
  None.
*/
static DALResult VCS_InitLDO
(
  VCSCPUNodeType *pCPU
)
{
  DALResult         eResult;
  uint32            nSize;
  VCSLDONodeType   *pLDO;
  VCSLDOConfigType *pLDOConfig;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pCPU == NULL ||
      pCPU->pBSPConfig == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Nothing to do if no LDO present.                                      */
  /*-----------------------------------------------------------------------*/

  if (pCPU->pBSPConfig->nNumLDOConfigs == 0)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Choose the LDO config which supports this HW version.                 */
  /*-----------------------------------------------------------------------*/

  eResult = VCS_DetectLDOConfigBSPVersion(pCPU, &pLDOConfig);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Failed to detect a valid BSP version for LDO configurations.");

    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate the LDO identifier defined in the BSP.                       */
  /*-----------------------------------------------------------------------*/

  if (pLDOConfig->eLDO >= HAL_LDO_NUM_OF_LDOS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Invalid LDO [%lu] for CPU[%s] in BSP.",
      pLDOConfig->eLDO,
      pCPU->pBSPConfig->szName);

    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Allocate memory for LDO node.                                         */
  /*-----------------------------------------------------------------------*/

  nSize = sizeof (*pCPU->pLDO);

  eResult = DALSYS_Malloc(nSize, (void **)&pCPU->pLDO);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to allocate %lu bytes for LDO[%s]",
      nSize,
      pLDOConfig->szName);

    return eResult;
  }

  memset((void *)pCPU->pLDO, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Store LDO properties.                                                 */
  /*-----------------------------------------------------------------------*/

  pLDO = pCPU->pLDO;
  pLDO->eLDO             = pLDOConfig->eLDO;
  pLDO->eCorner          = VCS_CORNER_OFF;
  pLDO->nVoltageUV       = 0;
  pLDO->nNumRestrictions = 0;
  pLDO->pBSPConfig       = pLDOConfig;

  /*-----------------------------------------------------------------------*/
  /* Explicitly disable per the BSP configuration.                         */
  /*-----------------------------------------------------------------------*/

  if (!pLDOConfig->bEnable)
  {
    pLDO->nDisable |= VCS_FLAG_DISABLED_BY_BSP;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the LDO voltage table.                                     */
  /*-----------------------------------------------------------------------*/

  eResult = VCS_InitLDOVoltageTable(pLDO, pLDOConfig);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Failed to initialize voltage table for LDO[%s]",
      pLDO->pBSPConfig->szName);

    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Make sure that the LDO is disabled (in BHS mode) by default.          */
  /*-----------------------------------------------------------------------*/

  HAL_ldo_DisableLDO(pLDO->eLDO);

  /*-----------------------------------------------------------------------*/
  /* Set the LDO autobypass mode according to its BSP flag.                */
  /*-----------------------------------------------------------------------*/

  HAL_ldo_SetLDOAutoBypass(pLDO->eLDO, pLDO->pBSPConfig->bAutoBypass);

  return DAL_SUCCESS;

} /* END VCS_InitLDO */


/* =========================================================================
**  Function : VCS_InitCPUs
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCS_InitCPUs
(
  VCSDrvCtxt       *pDrvCtxt,
  VCSBSPConfigType *pBSPConfig
)
{
  DALResult         eResult;
  uint32            i, j, k, nSize;
  VCSCPUNodeType   *pCPU;
  VCSRailNodeType  *pRail;

  /*-----------------------------------------------------------------------*/
  /* Nothing to do if no CPUs present.                                     */
  /*-----------------------------------------------------------------------*/

  if (pBSPConfig->nNumCPUConfigs == 0)
  {
    return DAL_SUCCESS;
  }

  pDrvCtxt->nNumCPUs = pBSPConfig->nNumCPUConfigs;

  /*-----------------------------------------------------------------------*/
  /* Allocate memory for the CPU nodes.                                    */
  /*-----------------------------------------------------------------------*/

  nSize = pDrvCtxt->nNumCPUs * sizeof (*pDrvCtxt->aCPUs);

  eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aCPUs);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to allocate %lu bytes for %lu CPUs.",
      nSize,
      pDrvCtxt->nNumCPUs);

    return eResult;
  }

  memset((void *)pDrvCtxt->aCPUs, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Initialize the CPU nodes.                                             */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumCPUs; i++)
  {
    pCPU = &pDrvCtxt->aCPUs[i];

    /*
     * Link the BSP data.`
     */
    pCPU->pBSPConfig = &pBSPConfig->pCPUConfig[i];

    /*
     * Validate the CPU defined in the BSP.
     */
    if (pCPU->pBSPConfig->eCPU >= CLOCK_CPU_NUM_OF_CPUS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid CPU [%lu] in BSP.",
        pCPU->pBSPConfig->eCPU);

      return DAL_ERROR_INTERNAL;
    }

    pCPU->eCPU = pCPU->pBSPConfig->eCPU;

    /*
     * Create entry in CPU enum to node map.
     */
    pDrvCtxt->apCPUMap[pCPU->eCPU] = pCPU;

    /*
     * Validate the rail defined for this CPU in the BSP.
     */
    if (pCPU->pBSPConfig->eRail >= VCS_RAIL_NUM_OF_RAILS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid rail[%lu] in BSP for CPU [%lu].",
        pCPU->pBSPConfig->eRail,
        pCPU->pBSPConfig->eCPU);

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Increment the count for the rail powering this CPU.
     */
    pRail = pDrvCtxt->apRailMap[pCPU->pBSPConfig->eRail];
    if (pRail == NULL)
    {
      return DAL_ERROR_INTERNAL;
    }

    pRail->nNumCPUs++;

    /*
     * Init the LDO if present for this CPU
     */
    eResult = VCS_InitLDO(pCPU);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Unable to initialize LDO for CPU[%lu].",
        pCPU->eCPU);

      return eResult;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Connect the Rails to each of the CPUs which it powers.                */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumRails; i++)
  {
    pRail = &pDrvCtxt->aRails[i];

    /*
     * Skip this rail if there are no CPU's to map.
     */
    if (pRail->nNumCPUs == 0)
    {
      continue;
    }

    /*
     * Allocate storage for pointers to CPU nodes.
     */
    nSize = pRail->nNumCPUs * sizeof (*pRail->apCPU);

    eResult = DALSYS_Malloc(nSize, (void **)&pRail->apCPU);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Unable to allocate %lu bytes for %lu CPUs.",
        nSize,
        pDrvCtxt->nNumCPUs);

      return eResult;
    }

    memset((void *)pRail->apCPU, 0x0, nSize);

    /*
     * Iterate through CPU list and store pointers to those on this rail.
     */
    for (j = 0, k = 0; j < pRail->nNumCPUs; j++, k++)
    {
      for ( ; k < pDrvCtxt->nNumCPUs; k++)
      {
        pCPU = &pDrvCtxt->aCPUs[j];
        if (pCPU->pBSPConfig->eRail == pRail->eRail)
        {
          pRail->apCPU[j] = pCPU;
          break;
        }
      }
    }
  }

  return DAL_SUCCESS;

} /* END VCS_InitCPUs */


/* =========================================================================
**  Function : VCS_SetLDOCorner
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCS_SetLDOCorner
(
  VCSCPUNodeType *pCPU,
  VCSCornerType   eLDOCorner,
  VCSCornerType   eRailCorner
)
{
  VCSLDONodeType         *pLDO;
  VCSCornerVoltageType   *pCornerVoltage;
  VCSNPALDOEventDataType  LDOEventData;
  VCSDrvCtxt             *pDrvCtxt;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (pCPU == NULL ||
      pCPU->pLDO == NULL ||
      eLDOCorner >= VCS_CORNER_NUM_OF_CORNERS ||
      eRailCorner >= VCS_CORNER_NUM_OF_CORNERS)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  pLDO = pCPU->pLDO;

  /*-----------------------------------------------------------------------*/
  /* Short circuit if no change in LDO corner.                             */
  /*-----------------------------------------------------------------------*/

  if (pLDO->eCorner == eLDOCorner)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pLDO->pVoltageTable == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the driver context.                                               */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = VCS_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Switch to LDO if                                                      */
  /* - the corner is supported, not in autobypass mode, LDO corner is less */
  /*   than rail which is at least at subsystem's required minimum corner. */
  /*        OR                                                             */
  /* - the corner is supported and in autobypass mode and rail is at least */
  /*   at subsystem's required minimum corner.                             */
  /*-----------------------------------------------------------------------*/

  pCornerVoltage = pLDO->pVoltageTable->apCornerMap[eLDOCorner];
  if (pCornerVoltage != NULL &&
      ((pLDO->pBSPConfig->bAutoBypass == FALSE &&
        eLDOCorner < eRailCorner &&
        eRailCorner >= pLDO->pBSPConfig->eMinRailCorner) ||
       (pLDO->pBSPConfig->bAutoBypass == TRUE &&
        eRailCorner >= pLDO->pBSPConfig->eMinRailCorner)))
  {
    /*
     * Fill out event data for LDO state change.
     */
    LDOEventData.PreChange.eCorner  = pLDO->eCorner;
    LDOEventData.PreChange.nVoltageUV = pLDO->nVoltageUV;
    LDOEventData.PostChange.eCorner = eLDOCorner;
    LDOEventData.PostChange.nVoltageUV = pCornerVoltage->nVoltageUV;

    /*
     * Notify NPA clients of pre-switch event.
     */
    npa_dispatch_custom_events(
      pCPU->resource.handle,
      (npa_event_type)VCS_NPA_LDO_EVENT_PRE_CHANGE,
      &LDOEventData);

    /*
     * Update the LDO voltage.
     */
    HAL_ldo_SetLDOVoltage(pLDO->eLDO, pCornerVoltage->nVoltageUV);

    ULOG_RT_PRINTF_3(
      pDrvCtxt->hVCSLog,
      "LDO[%s] - setting voltage corner[%s] uV[%d].",
      pCPU->pBSPConfig->szName,
      pDrvCtxt->pCornerDescription[eLDOCorner].szName,
      pCornerVoltage->nVoltageUV);

    /*
     * Update the LDO Voltage SW Event
     */
    VCS_SWEvent(
      VCS_EVENT_LDO_VOLTAGE_SET,
      3,
      pLDO->eLDO,
      eLDOCorner,
      pCornerVoltage->nVoltageUV);

    /*
     * Enable the LDO if it's not already on.
     */
    if (pLDO->eCorner == VCS_CORNER_OFF)
    {
      HAL_ldo_EnableLDO(pLDO->eLDO);

      ULOG_RT_PRINTF_1(
        pDrvCtxt->hVCSLog,
        "LDO[%s] - enabled.",
        pCPU->pBSPConfig->szName);

      VCS_SWEvent(VCS_EVENT_LDO_STATE_SET, 2, pLDO->eLDO, 1);
    }

    /*
     * Update the context.
     */
    pLDO->nVoltageUV = pCornerVoltage->nVoltageUV;
    pLDO->eCorner    = eLDOCorner;

    /*
     * Notify NPA clients of post-switch event.
     */
    npa_dispatch_custom_events(
      pCPU->resource.handle,
      (npa_event_type)VCS_NPA_LDO_EVENT_POST_CHANGE,
      &LDOEventData);
  }

  /*-----------------------------------------------------------------------*/
  /* Otherwise disable the LDO if it's not already off.                    */
  /*-----------------------------------------------------------------------*/

  else if (pLDO->eCorner != VCS_CORNER_OFF)
  {
    /*
     * Fill out event data for LDO state change.
     */
    LDOEventData.PreChange.eCorner  = pLDO->eCorner;
    LDOEventData.PreChange.nVoltageUV = pLDO->nVoltageUV;
    LDOEventData.PostChange.eCorner = VCS_CORNER_OFF;
    LDOEventData.PostChange.nVoltageUV = 0;

    /*
     * Notify NPA clients of pre-switch event.
     */
    npa_dispatch_custom_events(
      pCPU->resource.handle,
      (npa_event_type)VCS_NPA_LDO_EVENT_PRE_CHANGE,
      &LDOEventData);

    HAL_ldo_DisableLDO(pLDO->eLDO);

    ULOG_RT_PRINTF_1(
      pDrvCtxt->hVCSLog,
      "LDO[%s] - disabled.",
      pCPU->pBSPConfig->szName);

    /*
     * Update the LDO Disable SW Event
     */
    VCS_SWEvent(VCS_EVENT_LDO_STATE_SET, 2, pLDO->eLDO, 0);

    /*
     * Update the context.
     */
    pLDO->eCorner = VCS_CORNER_OFF;
    pLDO->nVoltageUV = 0;

    /*
     * Notify NPA clients of post-switch event.
     */
    npa_dispatch_custom_events(
      pCPU->resource.handle,
      (npa_event_type)VCS_NPA_LDO_EVENT_POST_CHANGE,
      &LDOEventData);
  }

  return DAL_SUCCESS;

} /* END VCS_SetLDOCorner */


/* =========================================================================
**  Function : VCS_AddLDORestriction
** =========================================================================*/
/*
  See DDIVCS.h
*/

DALResult VCS_AddLDORestriction
(
  VCSDrvCtxt   *pDrvCtxt,
  ClockCPUType  eCPU
)
{
  VCSCPUNodeType  *pCPU;
  VCSRailNodeType *pRail;
  VCSLDONodeType  *pLDO;
  npa_resource    *pRailResource;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  pCPU = pDrvCtxt->apCPUMap[eCPU];
  if (pCPU == NULL || pCPU->pLDO == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  pLDO = pCPU->pLDO;

  /*-----------------------------------------------------------------------*/
  /* Get pointer to the rail node.                                         */
  /*-----------------------------------------------------------------------*/

  pRail = pDrvCtxt->apRailMap[pCPU->pBSPConfig->eRail];
  if (pRail == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Protect operation on rail/LDO with a critical section.                */
  /*-----------------------------------------------------------------------*/

  pRailResource = pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL].handle;
  npa_resource_lock(pRailResource);

  /*-----------------------------------------------------------------------*/
  /* Increment the number of restrictions on the LDO.                      */
  /*-----------------------------------------------------------------------*/

  pLDO->nNumRestrictions += 1;

  /*-----------------------------------------------------------------------*/
  /* Log the SW Event LDO restrictions                                     */
  /*-----------------------------------------------------------------------*/

  VCS_SWEvent(VCS_EVENT_LDO_RESTRICTION, 2, pLDO->eLDO, pLDO->nNumRestrictions);

  /*-----------------------------------------------------------------------*/
  /* Disable the LDO if not already done.                                  */
  /*-----------------------------------------------------------------------*/

  if (!(pLDO->nDisable & VCS_FLAG_DISABLED_BY_SWCLIENT))
  {
    /*
     * Disable the LDO.
     */
    VCS_SetLDOCorner(pCPU, VCS_CORNER_OFF, pRail->eCorner);

    /*
     * Update the disable flag.
     */
    pLDO->nDisable |= VCS_FLAG_DISABLED_BY_SWCLIENT;
  }

  /*-----------------------------------------------------------------------*/
  /* Release lock.                                                         */
  /*-----------------------------------------------------------------------*/

  npa_resource_unlock(pRailResource);

  return DAL_SUCCESS;

} /* END VCS_AddLDORestriction */


/* =========================================================================
**  Function : VCS_RemoveLDORestriction
** =========================================================================*/
/*
  See DDIVCS.h
*/

DALResult VCS_RemoveLDORestriction
(
  VCSDrvCtxt   *pDrvCtxt,
  ClockCPUType  eCPU
)
{
  DALResult        eResult;
  VCSCPUNodeType  *pCPU;
  VCSRailNodeType *pRail;
  VCSLDONodeType  *pLDO;
  npa_resource    *pRailResource;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  pCPU = pDrvCtxt->apCPUMap[eCPU];
  if (pCPU == NULL || pCPU->pLDO == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  pLDO = pCPU->pLDO;

  /*-----------------------------------------------------------------------*/
  /* Get pointer to the rail node.                                         */
  /*-----------------------------------------------------------------------*/

  pRail = pDrvCtxt->apRailMap[pCPU->pBSPConfig->eRail];
  if (pRail == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Protect operation on rail/ldo with a critical section.                */
  /*-----------------------------------------------------------------------*/

  pRailResource = pRail->aResources[VCS_NPA_RAIL_RES_IDX_RAIL].handle;
  npa_resource_lock(pRailResource);

  /*-----------------------------------------------------------------------*/
  /* Decrement the number of restrictions on the LDO.                      */
  /*-----------------------------------------------------------------------*/

  if (pLDO->nNumRestrictions > 0)
  {
    pLDO->nNumRestrictions -= 1;
  }

  /*-----------------------------------------------------------------------*/
  /* Log the SW Event LDO restrictions                                     */
  /*-----------------------------------------------------------------------*/

  VCS_SWEvent(VCS_EVENT_LDO_RESTRICTION, 2, pLDO->eLDO, pLDO->nNumRestrictions);

  /*-----------------------------------------------------------------------*/
  /* If the number of restrictions on the LDO has gone down to zero, clear */
  /* the relevant bit in the disable flag.                                 */
  /*-----------------------------------------------------------------------*/

  if (pLDO->nDisable == 0)
  {
    pLDO->nDisable &= ~VCS_FLAG_DISABLED_BY_SWCLIENT;
  }

  /*-----------------------------------------------------------------------*/
  /* Re-vote the CPU's vote for the LDO if there are no disable flags set. */
  /*-----------------------------------------------------------------------*/

  if (!pLDO->nDisable)
  {
    eResult = VCS_SetLDOCorner(pCPU, pCPU->eCorner, pRail->eCorner);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to update LDO corner.");
    }

    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Release lock.                                                         */
  /*-----------------------------------------------------------------------*/

  npa_resource_unlock(pRailResource);

  return DAL_SUCCESS;

} /* END VCS_RemoveLDORestriction */


/* =========================================================================
**  Function : VCS_DetectLDOConfigBSPVersion
** =========================================================================*/
/**
 *
  See VCSDriver.h
*/

DALResult VCS_DetectLDOConfigBSPVersion
(
  VCSCPUNodeType    *pCPU,
  VCSLDOConfigType **pLDOConfig
)
{
  uint32             i;
  VCSLDOConfigType  *pIteratorLDOConfig;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pCPU == NULL || pLDOConfig == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize return parameter.                                          */
  /*-----------------------------------------------------------------------*/

  *pLDOConfig = NULL;

  /*-----------------------------------------------------------------------*/
  /* Detect which BSP data to use for this HW version.                     */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pCPU->pBSPConfig->nNumLDOConfigs; i++)
  {
    pIteratorLDOConfig = &pCPU->pBSPConfig->pLDOConfig[i];
    if (VCS_IsBSPSupported(&pIteratorLDOConfig->HWVersion))
    {
      *pLDOConfig = pIteratorLDOConfig;
      break;
    }
  }

  if (*pLDOConfig == NULL)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

}  /*  END VCS_DetectLDOConfigBSPVersion */
