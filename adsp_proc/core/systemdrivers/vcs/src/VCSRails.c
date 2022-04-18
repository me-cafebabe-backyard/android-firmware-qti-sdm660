/*
===========================================================================
*/
/**
  @file VCSRails.c 
  
  Rail-related functions for the VCS driver.
*/
/*  
  ====================================================================

  Copyright (c) 2014 QUALCOMM Technologies Incorporated. All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/src/VCSRails.c#1 $
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

#include "VCSDriver.h"
#include "DALDeviceId.h"
#include <DALSys.h>


/*=========================================================================
      Prototypes
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : VCS_DetectRailBSPVersion
** =========================================================================*/
/**
 *
  See VCSDriver.h
*/

DALResult VCS_DetectRailBSPVersion
(
  VCSRailNodeType          *pRail,
  VCSRailCornerConfigType **pCornerConfig
)
{
  uint32                   i;
  VCSRailCornerConfigType *pIteratorCornerConfig;

  /*-----------------------------------------------------------------------*/
  /* Sanity.                                                               */
  /*-----------------------------------------------------------------------*/

  if (pRail == NULL || pCornerConfig == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize return parameter.                                          */
  /*-----------------------------------------------------------------------*/

  *pCornerConfig = NULL;

  /*-----------------------------------------------------------------------*/
  /* Detect which BSP data to use for this HW version.                     */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pRail->pBSPConfig->nNumCornerConfigs; i++)
  {
    pIteratorCornerConfig = &pRail->pBSPConfig->pCornerConfig[i];
    if (VCS_IsBSPSupported(&pIteratorCornerConfig->HWVersion))
    {
      *pCornerConfig = pIteratorCornerConfig;
      break;
    }
  }

  if (*pCornerConfig == NULL)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : VCS_InitRails
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCS_InitRails
(
  VCSDrvCtxt       *pDrvCtxt,
  VCSBSPConfigType *pBSPConfig
)
{
  uint32                   i, nSize;
  DALResult                eResult;
  VCSRailNodeType         *pRail;
  VCSRailCornerConfigType *pCornerConfig;

  /*-----------------------------------------------------------------------*/
  /* Make sure we found at least one rail.                                 */
  /*-----------------------------------------------------------------------*/

  if (pBSPConfig->nNumRailConfigs == 0)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: VCS_InitRails found 0 rails.");

    return DAL_ERROR;
  }

  pDrvCtxt->nNumRails = pBSPConfig->nNumRailConfigs;

  /*-----------------------------------------------------------------------*/
  /* Allocate memory for the rail nodes.                                   */
  /*-----------------------------------------------------------------------*/

  nSize = pDrvCtxt->nNumRails * sizeof (*pDrvCtxt->aRails);

  eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aRails);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      0,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "DALLOG Device VCS: Unable to allocate %lu bytes for %lu rails.",
      nSize,
      pDrvCtxt->nNumRails);

    return eResult;
  }

  memset((void *)pDrvCtxt->aRails, 0x0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Initialize the rail nodes.                                            */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumRails; i++)
  {
    pRail = &pDrvCtxt->aRails[i];

    /*
     * Link the rail node to its BSP config data.
     */
    pRail->pBSPConfig = &pBSPConfig->pRailConfig[i];

    /*
     * Validate the rail defined in the BSP is supported.
     */
    if (pRail->pBSPConfig->eRail >= VCS_RAIL_NUM_OF_RAILS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid rail enum [%lu] defined in BSP",
        pRail->pBSPConfig->eRail);

      return DAL_ERROR_INTERNAL;
    }

    pRail->eRail = pRail->pBSPConfig->eRail;

    /*
     * Store entry in Rail enum to node map
     */
    pDrvCtxt->apRailMap[pRail->eRail] = pRail;

    /*
     * Detect the corner config for this HW version.
     */
    eResult = VCS_DetectRailBSPVersion(pRail, &pCornerConfig);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Failed to detect a valid BSP version.");

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Validate the min corner defined in the BSP.
     */
    if (pCornerConfig->eCornerMin >= VCS_CORNER_NUM_OF_CORNERS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid min corner [%lu] on rail[%s]",
        pCornerConfig->eCornerMin,
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    pRail->eCornerMin = pCornerConfig->eCornerMin;

    /*
     * Validate the max corner defined in the BSP.
     */
    if (pCornerConfig->eCornerMax >= VCS_CORNER_NUM_OF_CORNERS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid max corner [%lu] on rail[%s]",
        pCornerConfig->eCornerMax,
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    pRail->eCornerMax  = pCornerConfig->eCornerMax;

    /*
     * Validate the init corner defined in the BSP.
     */
    if (pCornerConfig->eCornerInit >= VCS_CORNER_NUM_OF_CORNERS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid init corner [%lu] on rail[%s]",
        pCornerConfig->eCornerInit,
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    pRail->eCornerInit = pCornerConfig->eCornerInit;

    /*
     * Validate the thermal init corner defined in the BSP.
     */
    if (pCornerConfig->eCornerInitThermal >= VCS_CORNER_NUM_OF_CORNERS)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid init thermal corner [%lu] on rail[%s]",
        pCornerConfig->eCornerInitThermal,
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    pRail->eCornerInitThermal = pCornerConfig->eCornerInitThermal;

    /*
     * All rails init to default mode.
     */
    pRail->eMode = VCS_RAIL_MODE_DEFAULT;

    /*
     * Explicitly disable per the BSP configuration
     */
    if (!pRail->pBSPConfig->bEnableDVS)
    {
      pRail->nDisableDVS |= VCS_FLAG_DISABLED_BY_BSP;
    }

    /*
     * Validate the active floor definition.
     */
    if (pRail->pBSPConfig->pNPAActiveFloor == NULL)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid active floor defined on rail[%s]",
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Validate the dependency definition.
     */
    if (pRail->pBSPConfig->pNPADependency == NULL)
    {
      DALSYS_LogEvent(
        0,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "DALLOG Device VCS: Invalid dependency defined on rail[%s]",
        pRail->pBSPConfig->szNameLocal);

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Set current rail corner to initial corner.
     */
    pRail->eCorner = pRail->eCornerInit;

    /*
     * Init the raw voltage.
     */
    pRail->nVoltageUV = 0;
  }

  return DAL_SUCCESS;

} /* END VCS_InitRails */

