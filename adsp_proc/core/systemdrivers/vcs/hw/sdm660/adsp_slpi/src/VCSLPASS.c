/*
===========================================================================
*/
/**
  @file VCSLPASS.c 
  
  Main entry point for the LPASS VCS driver.
*/
/*  
  ====================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/vcs/hw/sdm660/adsp_slpi/src/VCSLPASS.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  08/26/16   shm     First version, with stub nodes for SDM660.
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "VCSDriver.h"
#include <npa_resource.h>

/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Extern Definitions
==========================================================================*/


/*=========================================================================
      Function prototypes
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/
static const char *VCSNPANodeName[] =
{
  VCS_NPA_RESOURCE_VDD_CX,
  VCS_NPA_RESOURCE_VDD_CX_ACTIVE_FLOOR,
  VCS_NPA_RESOURCE_VDD_LPI_CX,
  VCS_NPA_RESOURCE_VDD_LPI_CX_ACTIVE_FLOOR,
  VCS_NPA_RESOURCE_VDD_MX,
  VCS_NPA_RESOURCE_VDD_MX_ACTIVE_FLOOR,
  VCS_NPA_RESOURCE_VDD_LPI_MX,
  VCS_NPA_RESOURCE_VDD_LPI_MX_ACTIVE_FLOOR
};

/* =========================================================================
      Prototypes
==========================================================================*/


/* =========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : VCS_SetRailMode
** =========================================================================*/
/*
  See DDIVCS.h
*/

DALResult VCS_SetRailMode
(
  VCSDrvCtxt     *pDrvCtxt,
  VCSRailType     eRail,
  VCSRailModeType eMode,
  const void     *pModeData
)
{
  /*
   * No locally managed rail on LPASS.
   */
  return DAL_ERROR_NOT_SUPPORTED;

} /* END VCS_SetRailMode */


/* =========================================================================
**  Function : VCS_SetRailVoltage
** =========================================================================*/
/*
  See DDIVCS.h
*/

DALResult VCS_SetRailVoltage
(
  VCSDrvCtxt  *pDrvCtxt,
  VCSRailType  eRail,
  uint32       nVoltageUV
)
{
  /*
   * No locally managed rail on LPASS.
   */
  return DAL_ERROR_NOT_SUPPORTED;

} /* END VCS_SetRailMode */


/* =========================================================================
**  Function : VCS_LoadNV
** =========================================================================*/
/*
  See VCSLPASS.h
*/

void VCS_LoadNV
(
  void
)
{

} /* END VCS_LoadNV */


/* =========================================================================
**  Function : VCS_InitImage
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCS_InitImage
(
  VCSDrvCtxt *pDrvCtxt
)
{
  return DAL_SUCCESS;

} /* END VCS_InitImage */


/* =========================================================================
**  Function : VCSStub_InitImage
** =========================================================================*/
/*
  See VCSDriver.h
*/

DALResult VCSStub_InitImage
(
  VCSDrvCtxt *pDrvCtxt
)
{
  uint32 i;
  
  /*-----------------------------------------------------------------------*/
  /* Create stubs for each NPA node.                                       */
  /*-----------------------------------------------------------------------*/
  
  for (i = 0; i < ARR_SIZE(VCSNPANodeName); i++)
  {
    npa_stub_resource(VCSNPANodeName[i]);
  }
  
  return DAL_SUCCESS;

} /* END VCSStub_InitImage */
