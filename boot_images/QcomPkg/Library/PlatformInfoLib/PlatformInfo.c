
#include "PlatformInfo.h"

/* =========================================================================
**  Function : PlatformInfo_GetPlatform
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_GetPlatform
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  DalPlatformInfoPlatformType *pType
)
{
  if (pType != NULL)
  {
    *pType = pDrvCtxt->PlatformInfo.platform;
    return DAL_SUCCESS;
  }

  return DAL_ERROR;

} /* END PlatformInfo_GetPlatform */


/* =========================================================================
**  Function : PlatformInfo_GetPlatformInfo
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_GetPlatformInfo
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  DalPlatformInfoPlatformInfoType *pInfo
)
{
  if (pInfo != NULL)
  {
    *pInfo = pDrvCtxt->PlatformInfo;
    return DAL_SUCCESS;
  }

  return DAL_ERROR;

} /* END PlatformInfo_GetPlatformInfo */


/* =========================================================================
**  Function : PlatformInfo_GetKeyValue
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_GetKeyValue
(
  PlatformInfoDrvCtxt     *pDrvCtxt,
  DalPlatformInfoKeyType   eKey,
  uint32                  *nValue
)
{
  uint32 i;

  if (eKey > DALPLATFORMINFO_NUM_KEYS || nValue == NULL)
  {
    return DAL_ERROR;
  }

  for (i = 0; i < pDrvCtxt->nNumKVPS; i++)
  {
    if (eKey == pDrvCtxt->aKVPS[i].nKey)
    {
      *nValue = pDrvCtxt->aKVPS[i].nValue;
      return DAL_SUCCESS;
    }
  }

  return DAL_ERROR;

} /* END PlatformInfo_GetKeyValue */

