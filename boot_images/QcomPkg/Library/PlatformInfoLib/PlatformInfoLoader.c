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

#include "Library/BaseLib.h"
#include "com_dtypes.h"
#include "pm_version.h"
#include "mobile.h"
#include "smem.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * PlatformInfoRPMType
 *
 */
typedef struct
{
  DalPlatformInfoPlatformInfoType   PlatformInfo;
  uint32                            nNumKVPS;
  PlatformInfoKVPSType              aKVPS[];
} PlatformInfoRPMType;

/*
 * PlatformInfoKVPSCDTType
 *
 *
 */
typedef struct PACK(PlatformInfoKVPSCDTType)
{
  uint8 nKey;
  uint8 nValue;
} PlatformInfoKVPSCDTType;

/*
 * PlatformInfoCDTType
 *
 * Storage structure which mimics the format of the EEPROM platform ID section.
 */
typedef struct PACK(PlatformInfoCDTType)
{
  uint8                 nVersion;
  uint8                 nPlatform;
  uint8                 nHWVersionMajor;
  uint8                 nHWVersionMinor;
  uint8                 nSubtype;
  uint8                 nNumKVPS;
  PlatformInfoKVPSCDTType  aKVPS[];
} PlatformInfoCDTType;

/*
 * PlatformInfoPmicFamilyType
 *
 * An enum to define Chip Family type.
 */
typedef enum
{
  PLATFORMINFO_PMIC_FAMILY_A     = 0,
  PLATFORMINFO_PMIC_FAMILY_B     = 1,
}PlatformInfoPmicFamilyType;


/*=========================================================================
      Function Prototypes
==========================================================================*/

static DALResult PlatformInfo_InitGlblCtxt (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_InitSMem     (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_CDTInit (PlatformInfoDrvCtxt *pDrvCtxt, PlatformInfoCDTType *pPlatformInfo);


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

  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : PlatformInfo_InitGlblCtxt
** =========================================================================*/
/**
  This function allocates and fills in the global context.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  None.
*/

static DALResult PlatformInfo_InitGlblCtxt
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  uint32 nSize, nKVPSSize;

  /*-----------------------------------------------------------------------*/
  /* Ensure global context has been initialized.                           */
  /*-----------------------------------------------------------------------*/

  DALGLBCTXT_Init();

  /*-----------------------------------------------------------------------*/
  /* Allocate the context.                                                 */
  /*-----------------------------------------------------------------------*/

  nKVPSSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
  nSize = sizeof(PlatformInfoGlbCtxType) + nKVPSSize;

  /* TODO: lock type? */
  eResult = DALGLBCTXT_AllocCtxt("DAL_PLATFORM_INFO", nSize,
    0, (void **)&pDrvCtxt->pGlbCtxt);

  /*-----------------------------------------------------------------------*/
  /* Fill it in if possible.                                               */
  /*-----------------------------------------------------------------------*/

  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pDrvCtxt->pGlbCtxt->PlatformInfo = pDrvCtxt->PlatformInfo;
  pDrvCtxt->pGlbCtxt->nNumKVPS = pDrvCtxt->nNumKVPS;
  DALSYS_memscpy(pDrvCtxt->pGlbCtxt->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);

  return DAL_SUCCESS;

} /* PlatformInfo_InitGlblCtxt */


/* =========================================================================
**  Function : PlatformInfo_InitSmem
** =========================================================================*/
/*
  Initializes and populates the SMEM (socinfo) location in which to store
  chip, platform, and build information.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitSMem
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DalPlatformInfoSMemType     *pSMem;
  DalPlatformInfoSMemPMICType *aPMICInfo;
  DalDeviceHandle             *phChipInfo;
  pm_device_info_type          PmicDeviceInfo;
  DALResult                    eResult;
  pm_err_flag_type             ePMICErr;
  uint32                       i, nPMICIndex, nNumPMICs;
  uint32                       nSize, nPMICArraySize;
  DalChipInfoSerialNumType     nChipSerial;

  /*-----------------------------------------------------------------------*/
  /* Calculate array sizes and allocate SMEM.                              */
  /*-----------------------------------------------------------------------*/

  for (i = 0, nNumPMICs = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG__FEATURE_NOT_SUPPORTED)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      nNumPMICs++;
    }
  }

  nPMICArraySize = sizeof(DalPlatformInfoSMemPMICType) * nNumPMICs;
  nSize = sizeof(DalPlatformInfoSMemType) + nPMICArraySize;

  pSMem = (DalPlatformInfoSMemType *) smem_alloc(SMEM_HW_SW_BUILD_ID, nSize);
  if (pSMem == NULL)
  {
    return DAL_ERROR;
  }

  DALSYS_memset(pSMem, 0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Get misc information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nFormat = DALPLATFORMINFO_SMEM_FORMAT;
//  AsciiStrnCpy(pSMem->aBuildId, mob_sw_rev, DALPLATFORMINFO_SMEM_BUILD_ID_LENGTH);

  /*-----------------------------------------------------------------------*/
  /* Get chip information.                                                 */
  /*-----------------------------------------------------------------------*/

  eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
  if (eResult == DAL_SUCCESS)
  {
    DalChipInfo_GetChipId(phChipInfo, (DalChipInfoIdType *)&pSMem->eChipId);
    DalChipInfo_GetChipVersion(phChipInfo, &pSMem->nChipVersion);
    DalChipInfo_GetRawChipId(phChipInfo, &pSMem->nRawChipId);
    DalChipInfo_GetRawChipVersion(phChipInfo, &pSMem->nRawChipVersion);
    DalChipInfo_GetFoundryId(phChipInfo,
      (DalChipInfoFoundryIdType *)&pSMem->nFoundryId);

    /* TODO: Does the chip serial really need to be 64-bit now? */
    DalChipInfo_GetSerialNumber(phChipInfo, &nChipSerial);
    pSMem->nChipSerial = (uint32)nChipSerial;
  }

  /*-----------------------------------------------------------------------*/
  /* Get platform information.                                             */
  /*-----------------------------------------------------------------------*/

  pSMem->ePlatformType = pDrvCtxt->PlatformInfo.platform;
  pSMem->nPlatformVersion = pDrvCtxt->PlatformInfo.version;
  pSMem->nPlatformSubtype = pDrvCtxt->PlatformInfo.subtype;
  pSMem->bFusion = pDrvCtxt->PlatformInfo.fusion;

  /*-----------------------------------------------------------------------*/
  /* Get PMIC information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nNumPMICs = nNumPMICs;
  pSMem->nPMICArrayOffset = sizeof(DalPlatformInfoSMemType);
  aPMICInfo =
    (DalPlatformInfoSMemPMICType *)((uintnt)pSMem + pSMem->nPMICArrayOffset);

  for (i = 0, nPMICIndex = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG__FEATURE_NOT_SUPPORTED || nPMICIndex >= nNumPMICs)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      aPMICInfo[nPMICIndex].nPMICModel =
        ((PLATFORMINFO_PMIC_FAMILY_B << 16) | (PmicDeviceInfo.ePmicModel));

      aPMICInfo[nPMICIndex].nPMICVersion =
        DALPLATFORMINFO_VERSION(PmicDeviceInfo.nPmicAllLayerRevision,
                                PmicDeviceInfo.nPmicMetalRevision);

      nPMICIndex++;
    }
  }

  /*
   * Copy up to three PMICs from main array into legacy array.
   */
  DALSYS_memscpy(pSMem->aPMICInfo, sizeof(pSMem->aPMICInfo),
    aPMICInfo, nPMICArraySize);

  return DAL_SUCCESS;

} /* END PlatformInfo_InitSMem */


/* =========================================================================
**  Function : PlatformInfo_InitRPM
** =========================================================================*/
/*
  Initialize and populate the IMEM location used to communicate to RPM.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitRPM
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  PlatformInfoRPMType *pRPM;
  uint32 nKVPSSize;
  DALResult eResult;
  
  eResult = PlatformInfo_GetPropertyValue("rpm_buffer_addr", (void **)&pRPM);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pRPM->PlatformInfo = pDrvCtxt->PlatformInfo;
  pRPM->nNumKVPS = pDrvCtxt->nNumKVPS;
  if (pRPM->nNumKVPS > 0)
  {
    nKVPSSize = pRPM->nNumKVPS * sizeof(PlatformInfoKVPSType);
    DALSYS_memscpy(pRPM->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_InitRPM */


/* =========================================================================
**  Function : PlatformInfo_CDTInit
** =========================================================================*/
/*
  Populate the platform information based on data from the CDT.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pPlatformInfo [in] -- Pointer to the CDT data.
*/

static DALResult PlatformInfo_CDTInit
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  PlatformInfoCDTType *pPlatformInfo
)
{
  static boolean bCDTInitialized = FALSE;
  DALResult eResult;
  uint32 nSize, i, nVal;

  if (bCDTInitialized == TRUE)
  {
    return DAL_SUCCESS;
  }

  if (pPlatformInfo == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Get platform type.                                                    */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->PlatformInfo.platform =
    (DalPlatformInfoPlatformType)pPlatformInfo->nPlatform;

  /*-----------------------------------------------------------------------*/
  /* Get platform version.                                                 */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->PlatformInfo.version =
    DALPLATFORMINFO_VERSION(pPlatformInfo->nHWVersionMajor,
                            pPlatformInfo->nHWVersionMinor);

  /*-----------------------------------------------------------------------*/
  /* Get platform sub-type.                                                */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 2)
  {
    pDrvCtxt->PlatformInfo.subtype = pPlatformInfo->nSubtype;
  }

  /*-----------------------------------------------------------------------*/
  /* Get key-value pairs.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 3)
  {
    pDrvCtxt->nNumKVPS = pPlatformInfo->nNumKVPS;
    if (pDrvCtxt->nNumKVPS > 0)
    {
      nSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
      eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aKVPS);
      if (eResult != DAL_SUCCESS)
      {
        return DAL_ERROR;
      }

      for (i = 0; i < pDrvCtxt->nNumKVPS; i++)
      {
        pDrvCtxt->aKVPS[i].nKey = pPlatformInfo->aKVPS[i].nKey;
        pDrvCtxt->aKVPS[i].nValue = pPlatformInfo->aKVPS[i].nValue;
      }
    }

    /*-----------------------------------------------------------------------*/
    /* Get Fusion.                                                           */
    /*-----------------------------------------------------------------------*/

    eResult =
      PlatformInfo_GetKeyValue(pDrvCtxt, DALPLATFORMINFO_KEY_FUSION, &nVal);
    if (eResult == DAL_SUCCESS)
    {
      pDrvCtxt->PlatformInfo.fusion = nVal;
    }
  }

  bCDTInitialized = TRUE;
  return DAL_SUCCESS;

} /* END PlatformInfo_CDTInit */


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
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, (PlatformInfoCDTType *)pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the location for communication to RPM.
   */
  PlatformInfo_InitRPM(pDrvCtxt);

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
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, (PlatformInfoCDTType *)pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the DAL global context.
   */
  PlatformInfo_InitGlblCtxt(pDrvCtxt);

  /*
   * Initialize the SMEM (socinfo) location.
   */
  eResult = PlatformInfo_InitSMem(pDrvCtxt);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;
}

