/**
  @file PlatformInfo.c

  Interface implementation file for the PlatformInfo driver.
*/
/*
  ====================================================================

  Copyright (c) 2011 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================


  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "PlatformInfo.h"
#include "LoaderUtils.h"


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : PlatformInfo_DriverInit
** =========================================================================*/
/**
  Initialize the PlatformInfo driver.

  This function initializes the PlatformInfo driver, it is the main init entry
  point.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Initialization was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult PlatformInfo_DriverInit
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  uint32 nSize;

  DALGLBCTXT_Init();
  DALGLBCTXT_FindCtxt("DAL_PLATFORM_INFO", (void **)&pDrvCtxt->pGlbCtxt);

  if (pDrvCtxt->pGlbCtxt == NULL)
  {
    return DAL_SUCCESS;
  }

  pDrvCtxt->PlatformInfo = pDrvCtxt->pGlbCtxt->PlatformInfo;
  pDrvCtxt->nNumKVPS = pDrvCtxt->pGlbCtxt->nNumKVPS;

  if (pDrvCtxt->nNumKVPS > 0)
  {
    nSize = sizeof(PlatformInfoKVPSType) * pDrvCtxt->nNumKVPS;
    eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aKVPS);
    if (eResult != DAL_SUCCESS)
    {
      return DAL_ERROR;
    }

    memscpy(pDrvCtxt->aKVPS, nSize, pDrvCtxt->pGlbCtxt->aKVPS, nSize);
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_DriverInit */


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPreDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPreDDR
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  void                *pPlatformInfo
)
{
  /*
   * Nothing to do for XBL Core.
   */
  return DAL_SUCCESS;

} /* END PlatformInfo_CDTConfigPreDDR*/


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPostDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPostDDR
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  void                *pPlatformInfo
)
{
  /*
   * Nothing to do for XBL Core.
   */
  return DAL_SUCCESS;

} /* END PlatformInfo_CDTConfigPostDDR */

