/*
===========================================================================
*/
/**
  @file Clock.c

  Interface implementation file for the clock device driver.
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

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "HALclk.h"
#include "HALclkInternal.h"
#include "DALSys.h"
#include "DDIChipInfo.h"
#include "QdssSWEvent.h"
#include "tracer_event_ids.h"
#include "DDIPlatformInfo.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIPlatformInfoTypes.h>
#include <Protocol/EFIPlatformInfo.h>

#ifdef WIN8EA
#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Clock_DriverInit)
#endif
#pragma warning(disable: 6385)
#endif

/*=========================================================================
      Definitions
==========================================================================*/

/*
 * This is the maximum number of delay attempts that will be made when
 * waiting for a clock change (config, enable, disable, etc) to propagate
 * to the status register.
 */
#define CLOCK_CONFIG_DELAY_ATTEMPTS 250    /* Expressed in iterations */

/*=========================================================================
      Function Prototypes
==========================================================================*/

static boolean Clock_CheckNameList
(
  const char  *szListName,
  const char  *szClockName
);

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_DriverInit
** =========================================================================*/
/**
  Initialize the clock driver.

  This function initializes the clock driver, it is the main init entry
  point.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Initialization was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

#ifdef WIN8EA
_IRQL_requires_max_(PASSIVE_LEVEL)
#endif
DALResult Clock_DriverInit
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  HAL_clk_ContextType HALClkCtxt = {0};
  ClockPropertyValueType PropVal;
  HAL_clk_HWIOBaseType *pBases = NULL;
  EFI_PLATFORMINFO_PROTOCOL           *pPlatformInfoProtocol;
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE  platformInfo;

  #ifdef WIN8EA
  PAGED_CODE();
  #endif

  /*-----------------------------------------------------------------------*/
  /* Create the driver synchronization object.                             */
  /*-----------------------------------------------------------------------*/

  eResult = DALSYS_SyncCreate (DALSYS_SYNC_ATTR_RESOURCE,
                               &pDrvCtxt->hLock, &pDrvCtxt->LockObj);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "DALSYS_SyncCreate failed.");
    return eResult;
  }

  QDSS_SWEVENT(CLOCK_EVENT_INIT);

  /*-----------------------------------------------------------------------*/
  /* Initialize the log.                                                   */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockLogDefaults", &PropVal);

  if (eResult == DAL_SUCCESS)
  {
    ULogFront_RealTimeInit (&pDrvCtxt->hClockLog, "Clock Log",
                            ((ClockLogType *)PropVal)->nLogSize,
                            ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);

    pDrvCtxt->nGlobalFlags |= ((ClockLogType *)PropVal)->nGlobalLogFlags;
  }


#ifdef WIN8EA
  else
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
      "Missing clock log defaults. Logging is disabled.");

    ULogFront_RealTimeInit (&pDrvCtxt->hClockLog, "Clock Log",
                            0,
                            ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
  }
#endif
  ULogCore_HeaderSet (pDrvCtxt->hClockLog,
                      "Content-Type: text/tagged-log-1.0;");

  /*-----------------------------------------------------------------------*/
  /* Get the platform type info.                                           */
  /*-----------------------------------------------------------------------*/
  //pDrvCtxt->nGlobalPlatformInfo = DalPlatformInfo_Platform();
  eResult = gBS->LocateProtocol(&gEfiPlatformInfoProtocolGuid, NULL,
                                (VOID **) &pPlatformInfoProtocol);

  if ((eResult != EFI_SUCCESS)|| (pPlatformInfoProtocol==NULL))
  {
    return  DAL_ERROR;
  }

  if(pPlatformInfoProtocol->GetPlatformInfo(pPlatformInfoProtocol, &platformInfo)!= EFI_SUCCESS)
  {
    return  DAL_ERROR;
  }
  pDrvCtxt->nGlobalPlatformInfo = platformInfo.platform;

  /*-----------------------------------------------------------------------*/
  /* Initialize the clock HAL.                                             */
  /*-----------------------------------------------------------------------*/

  /*
   * Map HAL regions.
   */
  HAL_clk_GetHWIOBases(&pBases);

  if (pBases != NULL)
  {
    while (pBases->pnBaseAddr != NULL)
    {
      Clock_MapHWIORegion(
        pBases->nPhysAddr, pBases->nSize, pBases->pnBaseAddr);
      pBases++;
    }
  }

  /*
   * Use DALSys busy wait function for HAL modules.
   */
  HALClkCtxt.BusyWait = DALSYS_BusyWait;

  /*
   * Get chip version to send to the HAL.
   */
  HALClkCtxt.nChipVersion = DalChipInfo_ChipVersion();
  HALClkCtxt.nChipId = DalChipInfo_ChipId();
  HALClkCtxt.nChipFamily = DalChipInfo_ChipFamily();

  /* Normalize Chip Info if necessary */
  Clock_NormalizeChipInfo(&HALClkCtxt);

  HAL_clk_Init(&HALClkCtxt);

  /*-----------------------------------------------------------------------*/
  /* Initialize the core driver.                                           */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitCore (pDrvCtxt);

  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the image specific driver.                                 */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitImage (pDrvCtxt);

  if (eResult != DAL_SUCCESS)
  {
    /* TODO: Remove this log once Clock_InitImage has proper logging */
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitImage failed.");
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Run the BIST if enabled.                                              */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->nBISTLogSize == 0)
  {
    pDrvCtxt->nBISTLogSize = CLOCK_BIST_DEFAULT_LOG_SIZE;
  }

  if (pDrvCtxt->bBISTEnabled)
  {
    Clock_BIST (pDrvCtxt);
  }

  /*-----------------------------------------------------------------------*/
  /* Initialization complete.                                              */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_DriverInit */


/* =========================================================================
**  Function : Clock_InitCore
** =========================================================================*/
/**
  Initialize the core portion of the clock driver.

  This function initializes the common portion of the clock driver that is
  shared with all images.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Initialization was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitCore
(
  ClockDrvCtxt *pDrvCtxt
)
{
  uint32                         nClockDomainIndex;
  uint32                         nClockIndex;
  uint32                         nPowerDomainIndex;
  HAL_clk_ClockDomainHandleType  HALClockDomainHandle = NULL;
  HAL_clk_ClockHandleType        pHALClock = NULL;
  HAL_clk_PowerDomainHandleType  HALPowerDomainHandle = NULL;
  HAL_clk_ClockMuxConfigType     ClockMuxConfig;
  ClockPropertyValueType         PropVal;
  DALResult                      eResult;
  uint32                         nSize;
  uint32                         nClockCountDomain;

  /*-----------------------------------------------------------------------*/
  /* Request the number of clock domains from the HAL and allocate memory  */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->nNumClockDomains = HAL_clk_GetNumberOfClockDomains();

  if (pDrvCtxt->nNumClockDomains > 0)
  {
    nSize = pDrvCtxt->nNumClockDomains * sizeof(*pDrvCtxt->aClockDomains);

    eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aClockDomains);

    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for %lu clock domains.",
        nSize, pDrvCtxt->nNumClockDomains);
      return eResult;
    }

    memset((void *)pDrvCtxt->aClockDomains, 0x0, nSize);
  }

  /*-----------------------------------------------------------------------*/
  /* Request the number of clocks from the HAL and allocate memory         */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->nNumClockDomains == 0)
  {
    pDrvCtxt->nNumClocks = 0;
  }
  else
  {
    pDrvCtxt->nNumClocks = HAL_clk_GetNumberOfClocks();

    if (pDrvCtxt->nNumClocks == 0)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "HAL_clk_GetNumberOfClocks returned 0.");
      return DAL_ERROR;
    }

    nSize = pDrvCtxt->nNumClocks * sizeof(*pDrvCtxt->aClocks);

    eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aClocks);

    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for %lu clocks.",
        nSize, pDrvCtxt->nNumClocks);
      return eResult;
    }

    memset((void *)pDrvCtxt->aClocks, 0x0, nSize);
  }

  /*-----------------------------------------------------------------------*/
  /* Request the number of power domains from the HAL and allocate memory  */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->nNumPowerDomains = HAL_clk_GetNumberOfPowerDomains();

  if (pDrvCtxt->nNumPowerDomains > 0)
  {
    nSize = pDrvCtxt->nNumPowerDomains * sizeof (*pDrvCtxt->aPowerDomains);

    eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aPowerDomains);

    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for %lu power domains.",
        nSize, pDrvCtxt->nNumPowerDomains);
      return eResult;
    }

    memset((void *)pDrvCtxt->aPowerDomains, 0x0, nSize);
  }

  /*-----------------------------------------------------------------------*/
  /* Allocate memory for sources and initialize source nodes               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitSources (pDrvCtxt);

  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize clock domain and clock nodes                               */
  /*-----------------------------------------------------------------------*/

  /* Request the first clock domain from the HAL */
  HAL_clk_GetNextClockDomain (NULL, &HALClockDomainHandle);

  /* Loop over all clock domains, making sure we don't overflow memory */
  nClockDomainIndex = 0;
  nClockIndex = 0;
  while ((HALClockDomainHandle != NULL) &&
         (nClockDomainIndex < pDrvCtxt->nNumClockDomains))
  {

    /* Bypass empty domains. */
    if (0 == HAL_clk_GetNumberOfClocksInDomain(HALClockDomainHandle))
    {
      /* Request the next clock domain from the HAL */
      HAL_clk_GetNextClockDomain (HALClockDomainHandle, &HALClockDomainHandle);
      pDrvCtxt->nNumClockDomains--;
      continue;
    }

    /* Store the HAL clock domain handle in the driver clock domain node */
    pDrvCtxt->aClockDomains[nClockDomainIndex].HALHandle =
      HALClockDomainHandle;

    /* Get the current source for this domain from the HAL */
    HAL_clk_DetectClockMuxConfig(
      pDrvCtxt->aClockDomains[nClockDomainIndex].HALHandle, &ClockMuxConfig);

    /*
     * If the source is valid, controllable, and present in the BSP, link the
     * domain node to a source node
     */
    if ((ClockMuxConfig.eSource != HAL_CLK_SOURCE_NULL) &&
        (pDrvCtxt->anSourceIndex[ClockMuxConfig.eSource] != 0xFF))
    {
      pDrvCtxt->aClockDomains[nClockDomainIndex].pSource =
        &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[ClockMuxConfig.eSource]];
    }
    /*
     * HAL_clk_DetectClockMuxConfig will return a NULL source for the domains that are
     * controlled by another processor, i.e., buses. These domains are now connected to
     * XO for accurate source voting.  This change also assumes a single XO per target and/or
     * for the domains that are implemented in this image.
     */
    else if((ClockMuxConfig.eSource == HAL_CLK_SOURCE_NULL) &&
            (pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO] != 0xFF))
    {
      pDrvCtxt->aClockDomains[nClockDomainIndex].pSource =
        &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO]];
    }

    /*
     * This domain node is almost complete, now work on its clock nodes
     */

    /* Get the first clock for this domain from the HAL */
    nClockCountDomain = 0;
    pHALClock = HAL_clk_GetNextClockInDomain (pDrvCtxt->aClockDomains[nClockDomainIndex].HALHandle,
                                              nClockCountDomain);

    if (pHALClock == NULL)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
        "HAL_clk_GetNextClockInDomain returned 0 (ClockDomain Index: %lu).", nClockDomainIndex);
    }

    /* Loop over all clocks, making sure we don't overflow memory */
    while ((pHALClock != NULL) && (nClockIndex < pDrvCtxt->nNumClocks))
    {
      /* Store the HAL clock handle in the driver clock node */
      pDrvCtxt->aClocks[nClockIndex].HALHandle = pHALClock;

      /* Get the clock name from the HAL */
      HAL_clk_GetClockName (pDrvCtxt->aClocks[nClockIndex].HALHandle,
                            &pDrvCtxt->aClocks[nClockIndex].szName);

      /* Link the domain node to the first set of BSP/XML configuration data */
      if (pDrvCtxt->aClockDomains[nClockDomainIndex].pBSPConfig == NULL)
      {
        eResult = Clock_GetPropertyValue(
          pDrvCtxt->aClocks[nClockIndex].szName, &PropVal);

        if (eResult == DAL_SUCCESS)
        {
          pDrvCtxt->aClockDomains[nClockDomainIndex].pBSPConfig =
            (ClockMuxConfigType *)PropVal;
        }
      }

      /* Link the clock node to its domain node */
      pDrvCtxt->aClocks[nClockIndex].pDomain =
        &pDrvCtxt->aClockDomains[nClockDomainIndex];

      /*
       *  Identify all the clocks that require explicit XO votes
       *  when enabled and mark them as such.
       */
      eResult = Clock_GetPropertyValue("XOVoteClocks", &PropVal);
      if (eResult == DAL_SUCCESS)
      {
        while (((ClockNameListType *)PropVal)->szName != NULL)
        {
          if (!strcmp(pDrvCtxt->aClocks[nClockIndex].szName, ((ClockNameListType *)PropVal)->szName))
          {
            CLOCK_FLAG_SET(&pDrvCtxt->aClocks[nClockIndex], XO_VOTE);
          }

          PropVal = (ClockNameListType *)PropVal + 1;
        }
      }

      /*
       * All reference counts for clocks, domains, and sources are initialized
       * to zero after we allocate memory for the corresponding data structures.
       * This happens regardless of the actual state of the associated hardware
       * following boot-up and it allows us to insist that the client drivers
       * make symmetrical calls to enable/disable clocks and power domains.
       */

      /*
       * This clock node is complete
       */
      nClockIndex++;
      nClockCountDomain++;

      /* Get the next clock for this domain from the HAL */
      pHALClock = HAL_clk_GetNextClockInDomain (pDrvCtxt->aClockDomains[nClockDomainIndex].HALHandle,
                                                nClockCountDomain);
    } /* End of clock loop */

    /*
     * If the clock list isn't NULL at this point, it means we exhausted the
     * memory allocated to the clock array, i.e. the HAL has more clocks defined
     * than the total number it reported to us.  This error would likely present
     * itself on the last domain, but the root cause could be in the HAL file
     * for an earlier domain.
     */
    if (pHALClock != NULL)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Clock_InitCore exceeded its memory allocation for clocks.");
      return DAL_ERROR;
    }

    /*
     * This domain node and its clock nodes are complete
     */

    /* Request the next clock domain from the HAL */
    HAL_clk_GetNextClockDomain (HALClockDomainHandle, &HALClockDomainHandle);
    nClockDomainIndex++;
  } /* End of clock domain loop */

  /*
   * If the clock domain handle isn't NULL at this point, it means we exhausted
   * the memory allocated to the clock domain array, i.e. the HAL has more
   * domains defined than the total number it reported to us.
   */
  if (HALClockDomainHandle != NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitCore exceeded its memory allocation for clock domains.");
    return DAL_ERROR;
  }

  /*
   * If the clock domain index isn't equal to the total number of domains
   * reported to us by the HAL, it means the HAL has less domains defined
   * than the total number it reported to us.
   */
  if (nClockDomainIndex != pDrvCtxt->nNumClockDomains)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitCore received too few clock domains from the HAL.");
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Init clock flags.                                                     */
  /*-----------------------------------------------------------------------*/

  Clock_InitFlags(pDrvCtxt, CLOCK_FLAG_NODE_TYPE_CLOCK);

  /*-----------------------------------------------------------------------*/
  /* Init clock domain flags.                                              */
  /*-----------------------------------------------------------------------*/

  Clock_InitFlags(pDrvCtxt, CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN);

  /*-----------------------------------------------------------------------*/
  /* Initialize power domain nodes                                         */
  /*-----------------------------------------------------------------------*/

  /* Request the first power domain from the HAL */
  HAL_clk_GetNextPowerDomain (NULL, &HALPowerDomainHandle);

  /* Loop over all power domains, making sure we don't overflow memory */
  nPowerDomainIndex = 0;
  while ((HALPowerDomainHandle != NULL) &&
         (nPowerDomainIndex < pDrvCtxt->nNumPowerDomains))
  {
    /* Store the HAL power domain handle in the driver power domain node */
    pDrvCtxt->aPowerDomains[nPowerDomainIndex].HALHandle =
      HALPowerDomainHandle;

    /* Get the power domain name from the HAL */
    HAL_clk_GetPowerDomainName (pDrvCtxt->aPowerDomains[nPowerDomainIndex].HALHandle,
                                &pDrvCtxt->aPowerDomains[nPowerDomainIndex].szName);

    /* Check if the domain is enabled */
    pDrvCtxt->aPowerDomains[nPowerDomainIndex].bEnabled =
      HAL_clk_IsPowerDomainEnabled (pDrvCtxt->aPowerDomains[nPowerDomainIndex].HALHandle);

    /* Request the next power domain from the HAL */
    HAL_clk_GetNextPowerDomain (HALPowerDomainHandle, &HALPowerDomainHandle);
    nPowerDomainIndex++;
  }

  /*
   * If the power domain handle isn't NULL at this point, it means we exhausted
   * the memory allocated to the power domain array, i.e. the HAL has more
   * domains defined than the total number it reported to us.
   */
  if (HALPowerDomainHandle != NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitCore exceeded its memory allocation for power domains.");
    return DAL_ERROR;
  }

  /*
   * If the power domain index isn't equal to the total number of domains
   * reported to us by the HAL, it means the HAL has less domains defined
   * than the total number it reported to us.
   */
  if (nPowerDomainIndex != pDrvCtxt->nNumPowerDomains)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitCore received too few power domains from the HAL.");
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Init power domain flags.                                              */
  /*-----------------------------------------------------------------------*/

  Clock_InitFlags(pDrvCtxt, CLOCK_FLAG_NODE_TYPE_POWER_DOMAIN);

  /*-----------------------------------------------------------------------*/
  /* Init voltage module.                                                  */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitVoltage(pDrvCtxt);

  if (eResult != DAL_SUCCESS)
  {
    /* TODO: Remove this log once Clock_InitVoltage has proper logging */
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitVoltage failed.");
    return eResult;
  }


  /*-----------------------------------------------------------------------*/
  /* Core initialization complete                                          */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitCore */


/* =========================================================================
**  Function : Clock_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @param *pdrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Deinititialization was successful.
  DAL_ERROR -- Deinitialization failed.

  @dependencies
  None.
*/

DALResult Clock_DriverDeInit
(
  ClockDrvCtxt *pDrvCtxt
)
{
  /*-----------------------------------------------------------------------*/
  /* Free memory.                                                          */
  /*-----------------------------------------------------------------------*/

  DALSYS_Free (pDrvCtxt->aClocks);
  pDrvCtxt->aClocks = NULL;

  DALSYS_Free (pDrvCtxt->aClockDomains);
  pDrvCtxt->aClockDomains = NULL;

  DALSYS_Free (pDrvCtxt->aSources);
  pDrvCtxt->aSources = NULL;

  DALSYS_Free (pDrvCtxt->aPowerDomains);
  pDrvCtxt->aPowerDomains = NULL;

  /*-----------------------------------------------------------------------*/
  /* Destroy the mutex object.                                             */
  /*-----------------------------------------------------------------------*/

  DALSYS_DestroyObject(pDrvCtxt->hLock);

  /*-----------------------------------------------------------------------*/
  /* Shut-down complete.                                                   */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_DriverDeInit */


/* =========================================================================
**  Function : Clock_GetClockId
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_GetClockId
(
  ClockDrvCtxt *pDrvCtxt,
  const char   *szClock,
  ClockIdType  *pnId
)
{
  uint32   nClockIndex;
  boolean  bFound;

  /*-----------------------------------------------------------------------*/
  /* Validate pointers are usable.                                         */
  /*-----------------------------------------------------------------------*/

  if (!szClock || !pnId)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize output parameter                                           */
  /*-----------------------------------------------------------------------*/

  *pnId = (ClockIdType)NULL;

  /*-----------------------------------------------------------------------*/
  /* Search the array of clock nodes, break if we find a match             */
  /*-----------------------------------------------------------------------*/

  bFound = FALSE;

  for (nClockIndex = 0; nClockIndex < pDrvCtxt->nNumClocks; nClockIndex++)
  {
    if (strcmp (szClock, pDrvCtxt->aClocks[nClockIndex].szName) == 0)
    {
      bFound = TRUE;
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the clock node if found, otherwise return NULL    */
  /*-----------------------------------------------------------------------*/

  if (bFound)
  {
    *pnId = (ClockIdType)&pDrvCtxt->aClocks[nClockIndex];
    return DAL_SUCCESS;
  }
  else
  {
    return DAL_ERROR_NOT_FOUND;
  }

} /* END Clock_GetClockId */


/* =========================================================================
**  Function : Clock_SetExternalSourceDiv
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetExternalSourceDiv
(
  ClockDrvCtxt *pDrvCtxt,
  const char   *szClock,
  uint32        nExtDivider
)
{
  extern void HAL_clk_SetExternalSourceDiv( const char *szClock, uint32 nExtDivider);

  HAL_clk_SetExternalSourceDiv(szClock, nExtDivider);
  return DAL_SUCCESS;

} /* END Clock_SetExternalSourceDiv */


/* =========================================================================
**  Function : Clock_EnableClockDomain
** =========================================================================*/
/**
  Enables a clock domain.

  This function enables a clock domain, generally as a result of a call to
  Clock_EnableClock().

  @param *pDrvCtxt [in] -- Pointer to the driver context.
  @param *pClockDomain [in] -- Pointer to a clock domain node.
  @param  nClockFlags  [in] -- Flags for any clock attributes.

  @return
  DAL_SUCCESS -- The domain was successfully enabled.
  DAL_ERROR -- The domain was not enabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

DALResult Clock_EnableClockDomain
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockDomainNodeType *pClockDomain,
  uint32               nClockFlags
)
{
  DALResult             eResult;
  boolean               bSuppressibleRequest;
  ClockVRegRequestType  VRegRequest;

  /* Make sure the domain handle is valid */
  if (pClockDomain == NULL)
  {
    return DAL_ERROR;
  }

  /* Check if the clock or domain are suppressible */
  if ((nClockFlags & CLOCK_FLAG_SUPPRESSIBLE) != 0 ||
      CLOCK_FLAG_IS_SET(pClockDomain, SUPPRESSIBLE))
  {
    bSuppressibleRequest = TRUE;
  }
  else
  {
    bSuppressibleRequest = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Process insuppressible requests.                                      */
  /*-----------------------------------------------------------------------*/

  if (!bSuppressibleRequest)
  {
    /*
     * We enable the source for the first insuppressible clock even if
     * another suppressible clock has already enabled the clock domain
     * because we need to keep reference counting within the source.
     */
    if (pClockDomain->nReferenceCount == 0)
    {
      /* If this domain has a controllable source, enable it first */
      if (pClockDomain->pSource != NULL)
      {
        eResult = Clock_EnableSourceInternal(pDrvCtxt, pClockDomain->pSource, FALSE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * When there is no suppressible reference count, make the initial voltage
       * request. When there is already a suppressible reference count, change
       * the request to suppressible.
       */
      if (!CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST) &&
          pClockDomain->pActiveMuxConfig != NULL)
      {
        VRegRequest.eVRegLevel = pClockDomain->pActiveMuxConfig->eVRegLevel;
        VRegRequest.bSuppressible = FALSE;
        Clock_VoltageRequest(pDrvCtxt, &pClockDomain->VRegRequest, &VRegRequest);

        if (CLOCK_FLAG_IS_SET(pClockDomain, REPORT_CX_RAIL_UPDATES))
        {
          /*-----------------------------------------------------------------------*/
          /* Call the Limits Management callback function if one was specified.    */
          /*-----------------------------------------------------------------------*/

          if (pDrvCtxt->fpGpuUpdate != NULL)
          {
            LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

            fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
          }
        }
      }
    }

    /*
     * Increment the insuppressible reference count.
     */
    pClockDomain->nReferenceCount++;
  }

  /*-----------------------------------------------------------------------*/
  /* Process suppressible request.                                         */
  /*-----------------------------------------------------------------------*/

  else
  {
    /*
     * We enable the source for the first suppressible clock even if
     * another insuppressible clock has already enabled the clock domain
     * because we need to keep reference counting within the source.
     */
    if (pClockDomain->nReferenceCountSuppressible == 0)
    {
      /* If this domain has a controllable source, enable it first */
      if (pClockDomain->pSource != NULL)
      {
        eResult = Clock_EnableSourceInternal(pDrvCtxt, pClockDomain->pSource, TRUE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * Only make the voltage request if there is no insuppressible reference
       * count, since the insuppressible voltage requests take priority.
       */
      if (pClockDomain->nReferenceCount == 0 &&
          !CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST) &&
          pClockDomain->pActiveMuxConfig != NULL)
      {
        VRegRequest.eVRegLevel = pClockDomain->pActiveMuxConfig->eVRegLevel;
        VRegRequest.bSuppressible = TRUE;
        Clock_VoltageRequest(pDrvCtxt, &pClockDomain->VRegRequest, &VRegRequest);

        if (CLOCK_FLAG_IS_SET(pClockDomain, REPORT_CX_RAIL_UPDATES))
        {
          /*-----------------------------------------------------------------------*/
          /* Call the Limits Management callback function if one was specified.    */
          /*-----------------------------------------------------------------------*/

          if (pDrvCtxt->fpGpuUpdate != NULL)
          {
            LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

            fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
          }
        }
      }
    }

    /*
     * Increment the reference count.
     */
    pClockDomain->nReferenceCountSuppressible++;
  }

  return DAL_SUCCESS;

} /* END Clock_EnableClockDomain */


/* =========================================================================
**  Function : Clock_DisableClockDomain
** =========================================================================*/
/**
  Disables a clock domain.

  This function disables a clock domain, generally as a result of a call to
  Clock_DisableClock().

  @param *pDrvCtxt     [in] -- Pointer to the driver context.
  @param *pClockDomain [in] -- Pointer to a clock domain node.
  @param  nClockFlags  [in] -- Flags for any clock attributes.

  @return
  DAL_SUCCESS -- The domain was successfully disabled.
  DAL_ERROR -- The domain was not disabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

DALResult Clock_DisableClockDomain
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockDomainNodeType *pClockDomain,
  uint32               nClockFlags
)
{
  DALResult             eResult;
  boolean               bSuppressibleRequest;
  ClockVRegRequestType  VRegRequest;

  /* Make sure the domain handle is valid */
  if (pClockDomain == NULL)
  {
    return DAL_ERROR;
  }

  /* Check if the clock or domain are suppressible */
  if ((nClockFlags & CLOCK_FLAG_SUPPRESSIBLE) != 0 ||
      CLOCK_FLAG_IS_SET(pClockDomain, SUPPRESSIBLE))
  {
    bSuppressibleRequest = TRUE;
  }
  else
  {
    bSuppressibleRequest = FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Process insuppressible requests.                                      */
  /*-----------------------------------------------------------------------*/

  if (!bSuppressibleRequest)
  {
    /*
     * We disable the source for the last insuppressible clock even if
     * another suppressible clock is still enabled because we need to keep
     * reference counting within the source.
     */
    if (pClockDomain->nReferenceCount == 1)
    {
      if (pClockDomain->pSource != NULL)
      {
        eResult = Clock_DisableSourceInternal(pDrvCtxt, pClockDomain->pSource, FALSE, FALSE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * If there is no suppressible reference count, just remove the voltage
       * request. If there is a suppressible reference count, then update the
       * voltage request to be suppressible.
       */
      if (!CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST) &&
          pClockDomain->pActiveMuxConfig != NULL)
      {
        if (pClockDomain->nReferenceCountSuppressible == 0)
        {
          VRegRequest.eVRegLevel = CLOCK_VREG_LEVEL_OFF;
          VRegRequest.bSuppressible = FALSE;
        }
        else
        {
          VRegRequest.eVRegLevel = pClockDomain->pActiveMuxConfig->eVRegLevel;
          VRegRequest.bSuppressible = TRUE;
        }

        Clock_VoltageRequest(pDrvCtxt, &pClockDomain->VRegRequest, &VRegRequest);

        if (CLOCK_FLAG_IS_SET(pClockDomain, REPORT_CX_RAIL_UPDATES))
        {
          /*-----------------------------------------------------------------------*/
          /* Call the Limits Management callback function if one was specified.    */
          /*-----------------------------------------------------------------------*/

          if (pDrvCtxt->fpGpuUpdate != NULL)
          {
            LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

            fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
          }
        }
      }
    }

    /*
     * Decrement insuppressible reference count.
     */
    if (pClockDomain->nReferenceCount > 0)
    {
      pClockDomain->nReferenceCount--;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Process suppressible request.                                         */
  /*-----------------------------------------------------------------------*/

  else
  {
    /*
     * We disable the source for the last suppressible clock even if
     * another insuppressible clock is still enabled because we need to
     * keep reference counting within the source.
     */
    if (pClockDomain->nReferenceCountSuppressible == 1)
    {
      if (pClockDomain->pSource != NULL)
      {
        eResult = Clock_DisableSourceInternal(pDrvCtxt, pClockDomain->pSource, TRUE, FALSE);
        if (eResult != DAL_SUCCESS)
        {
          return eResult;
        }
      }

      /*
       * Only remove the voltage request if there are no insuppressible
       * reference counts.
       */
      if (pClockDomain->nReferenceCount == 0 &&
          !CLOCK_FLAG_IS_SET(pClockDomain, DOMAIN_HOLD_VREG_REQUEST))
      {
        VRegRequest.eVRegLevel = CLOCK_VREG_LEVEL_OFF;
        VRegRequest.bSuppressible = TRUE;
        Clock_VoltageRequest(pDrvCtxt, &pClockDomain->VRegRequest, &VRegRequest);

        if (CLOCK_FLAG_IS_SET(pClockDomain, REPORT_CX_RAIL_UPDATES))
        {
          /*-----------------------------------------------------------------------*/
          /* Call the Limits Management callback function if one was specified.    */
          /*-----------------------------------------------------------------------*/

          if (pDrvCtxt->fpGpuUpdate != NULL)
          {
            LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

            fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
          }
        }
      }
    }

    /*
     * Decrement suppressible reference count.
     */
    if (pClockDomain->nReferenceCountSuppressible > 0)
    {
      pClockDomain->nReferenceCountSuppressible--;
    }
  }

  return DAL_SUCCESS;

} /* END Clock_DisableClockDomain */


/* =========================================================================
**  Function : Clock_EnableClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnableClock
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock
)
{
  ClockNodeType   *pClock = NULL;
  DALResult        eResult;
  boolean          bIsOn;
  uint32           nTimeout = 0;

  /* Cast nClock to a proper pointer */
  pClock = (ClockNodeType*)nClock;

  /* Make sure the clock handle is valid */
  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /* If the reference count is zero, we need to enable the clock */
  if (pClock->nReferenceCount == 0)
  {
    /*
     * If the BRANCH_ONLY_CONTROL is set for this clock, we bypass
     * all source and voltage processing and perform just the actual
     * clock branch control.
     */
    if (!CLOCK_FLAG_IS_SET(pClock, BRANCH_ONLY_CONTROL))
    {
      /* Enable the domain first */
      eResult =
        Clock_EnableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags);

      if (eResult != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }
    }

    /* Enable the clock */
    HAL_clk_EnableClock (pClock->HALHandle);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                        "%s (Enabled: 1)", pClock->szName);
    }

    /* Determine whether this clock supports "IsOn" API functionality */
    if (HAL_clk_IsClockSupported (pClock->HALHandle, HAL_CLK_CLOCK_API_ISON))
    {
      bIsOn = HAL_clk_IsClockOn(pClock->HALHandle);

      /* Wait for the clock to turn ON */
      while (!bIsOn && nTimeout++ < CLOCK_CONFIG_DELAY_ATTEMPTS)
      {
        DALSYS_BusyWait(1);
        bIsOn = HAL_clk_IsClockOn(pClock->HALHandle);
      }

      /* Log a warning if the clock does not turn ON and return DAL_ERROR */
      if (!bIsOn)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_WARNING,
            "Unable to turn ON clock: %s.", pClock->szName);

        // TODO:  re-enable this code as soon as the following CRs are ready
        //        Camera – http://prism/CR/459182
        //        Video – http://prism/CR/459185
        //        Graphics - http://prism/CR/459188
        #if 0
        /* Disable the clock */
        HAL_clk_DisableClock (pClock->HALHandle);

        /* Disable the domain */
        eResult = Clock_DisableClockDomain (pDrvCtxt, pClock->pDomain, pClock->nFlags);
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_TIMEOUT;
        #endif
      }
    }

    /* Explicitly vote for XO on behalf of this clock, if necessary. */
    if (CLOCK_FLAG_IS_SET(pClock, XO_VOTE) && !CLOCK_FLAG_IS_SET(pClock, BRANCH_ONLY_CONTROL))
    {
      eResult = Clock_EnableSourceInternal(pDrvCtxt,
        &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO]], FALSE);

      if (eResult != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return eResult;
      }
    }
  }

  /* Log clock enable event */
  #ifdef WIN8EA
  if (pDrvCtxt->bQdssEnabled)
  {
    PEP_CLK_TRACE_CLOCK_STATUS(
      HAL_clk_GetTestClockId(pClock->HALHandle),
      1, pClock->nReferenceCount);
  }
  #else
    QDSS_SWEVENT(CLOCK_EVENT_CLOCK_STATUS,HAL_clk_GetTestClockId(pClock->HALHandle),pClock->nReferenceCount);
  #endif

  if (CLOCK_FLAG_IS_SET(pClock, NO_REFERENCE_COUNTING))
  {
    /* Set the reference count to 1 */
    pClock->nReferenceCount = 1;
  }
  else
  {
    /* Increment the reference count */
    pClock->nReferenceCount++;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_EnableClock */


/* =========================================================================
**  Function : Clock_DisableClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_DisableClock
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock
)
{
  ClockNodeType   *pClock = NULL;
  DALResult        eResult;

  /* Cast nClock to a proper pointer */
  pClock = (ClockNodeType*)nClock;

  /* Make sure the clock handle is valid */
  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*
   * If the reference count is one, we need to disable the clock.
   * Ignore if the DO_NOT_DISABLE bits are set.
   */
  if ((pClock->nReferenceCount == 1) &&
      !CLOCK_FLAG_IS_SET(pClock, DO_NOT_DISABLE) &&
      !CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_CLOCKS))
  {
    /* Disable the clock */
    HAL_clk_DisableClock (pClock->HALHandle);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_STATE_CHANGE) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_STATE_CHANGE))
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                        "%s (Enabled: 0)", pClock->szName);
    }

    /*
     * If the BRANCH_ONLY_CONTROL is set for this clock, we bypass
     * all source and voltage processing and perform just the actual
     * clock branch control.
     */
    if (!CLOCK_FLAG_IS_SET(pClock, BRANCH_ONLY_CONTROL))
    {
      /* Disable the domain */
      eResult =
        Clock_DisableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags);

      if (eResult != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }

      /* Remove the explicit XO vote on behalf of this clock, if necessary. */
      if (CLOCK_FLAG_IS_SET(pClock, XO_VOTE))
      {
        eResult = Clock_DisableSourceInternal(pDrvCtxt,
          &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO]], FALSE, FALSE);

        if (eResult != DAL_SUCCESS)
        {
          DALCLOCK_FREE(pDrvCtxt);
          return eResult;
        }
      }
    }
  }

  if (CLOCK_FLAG_IS_SET(pClock, NO_REFERENCE_COUNTING))
  {
    pClock->nReferenceCount = 0;
  }
  else
  {
    /* Decrement the reference count */
    if (pClock->nReferenceCount > 0)
    {
      pClock->nReferenceCount--;
    }
  }

  /* Log clock disable event */
  #ifdef WIN8EA
  if (pDrvCtxt->bQdssEnabled)
  {
    PEP_CLK_TRACE_CLOCK_STATUS(
      HAL_clk_GetTestClockId(pClock->HALHandle),
      0, pClock->nReferenceCount);
  }
  #else
    QDSS_SWEVENT(CLOCK_EVENT_CLOCK_STATUS,HAL_clk_GetTestClockId(pClock->HALHandle),pClock->nReferenceCount);
  #endif

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_DisableClock */


/* =========================================================================
**  Function : Clock_FindClockConfig
** =========================================================================*/
/**
  Finds a particular clock configuration in the BSP.

  This function finds a particular clock configuration in the BSP based on
  the specified frequency and match criteria.

  @param *pBSPConfig [in] -- Pointer to a list of configurations
  @param nFreqHz [in] -- Frequency in Hz
  @param eMatch [in] -- Match criteria
  @param **pMatchingConfig [out] -- Matching configuration

  @return
  DAL_SUCCESS -- A matching configuration was found.
  DAL_ERROR -- A matching configuration was not found.

  @dependencies
  None.
*/

static DALResult Clock_FindClockConfig
(
  ClockMuxConfigType  *pBSPConfig,
  uint32               nFreqHz,
  ClockFrequencyType   eMatch,
  ClockMuxConfigType **pMatchingConfig
)
{
  uint32              nAtLeastFrequency = 0xFFFFFFFF;
  ClockMuxConfigType *pAtLeastConfig = NULL;
  uint32              nAtMostFrequency = 0;
  ClockMuxConfigType *pAtMostConfig = NULL;

  /* Make sure the list of configurations isn't empty */
  if (pBSPConfig == NULL || pMatchingConfig == NULL)
  {
    return DAL_ERROR;
  }

  /* Loop over all configurations */
  while (pBSPConfig->nFreqHz != 0)
  {
    /*
     * Skip configurations that aren't for this chip or version, and configurations
     * that rely on an external source.
     */
    if (!Clock_IsBSPSupported(&pBSPConfig->HWVersion) ||
        ((pBSPConfig->HALConfig.eSource >= HAL_CLK_SOURCE_EXTERNAL) &&
         (pBSPConfig->HALConfig.eSource < HAL_CLK_NUM_OF_EXTERNAL_SOURCES)))
    {
      pBSPConfig++;
      continue;
    }

    /* Stop if we find an exact match */
    if (pBSPConfig->nFreqHz == nFreqHz)
    {
      *pMatchingConfig = pBSPConfig;
      return DAL_SUCCESS;
    }

    /* Look for the lowest at-least frequency */
    if ((pBSPConfig->nFreqHz > nFreqHz) &&
        (pBSPConfig->nFreqHz < nAtLeastFrequency))
    {
      nAtLeastFrequency = pBSPConfig->nFreqHz;
      pAtLeastConfig = pBSPConfig;
    }
    /* Look for the highest at-most frequency */
    else if ((pBSPConfig->nFreqHz < nFreqHz) &&
             (pBSPConfig->nFreqHz > nAtMostFrequency))
    {
      nAtMostFrequency = pBSPConfig->nFreqHz;
      pAtMostConfig = pBSPConfig;
    }

    /* Move to the next configuration */
    pBSPConfig++;
  }

  /* Select a config based on the match criteria */
  switch (eMatch)
  {
    case CLOCK_FREQUENCY_HZ_AT_LEAST:
      if (pAtLeastConfig != NULL)
      {
        *pMatchingConfig = pAtLeastConfig;
        return DAL_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_AT_MOST:
      if (pAtMostConfig != NULL)
      {
        *pMatchingConfig = pAtMostConfig;
        return DAL_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_CLOSEST:
      if ((pAtLeastConfig != NULL) && (pAtMostConfig == NULL))
      {
        *pMatchingConfig = pAtLeastConfig;
        return DAL_SUCCESS;
      }
      else if ((pAtMostConfig != NULL) && (pAtLeastConfig == NULL))
      {
        *pMatchingConfig = pAtMostConfig;
        return DAL_SUCCESS;
      }
      else if ((pAtLeastConfig != NULL) && (pAtMostConfig != NULL))
      {
        /* Select the closest match, select the lowest in case of a tie */
        if ((nAtLeastFrequency - nFreqHz) < (nFreqHz - nAtMostFrequency))
        {
          *pMatchingConfig = pAtLeastConfig;
          return DAL_SUCCESS;
        }
        else
        {
          *pMatchingConfig = pAtMostConfig;
          return DAL_SUCCESS;
        }
      }
      break;

    default:
      break;
  }

  /* No match was found */
  *pMatchingConfig = NULL;

  return DAL_ERROR;

} /* END Clock_FindClockConfig */


/* =========================================================================
**  Function : Clock_SetClockConfig
** =========================================================================*/
/*
  See ClockDriver.h.
*/

DALResult Clock_SetClockConfig
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockDomainNodeType *pDomain,
  ClockMuxConfigType  *pNewConfig
)
{
  ClockSourceNodeType *pNewSource;
  DALResult            eResult;
  uint32               nSrcIdx;
  boolean              bVoltageRequest;
  ClockVRegRequestType  VRegRequest;

  /* Validate parameters */
  if (pDomain == NULL || pNewConfig == NULL ||
      pNewConfig->HALConfig.eSource >= HAL_CLK_NUM_OF_SOURCES)
  {
    return DAL_ERROR;
  }

  /*
   * Determine if we should make a voltage request.  We do so if this
   * domain is not configured to make requests when enabled, or if it
   * is thus configured and is currently enabled.
   */
  bVoltageRequest =
    (pDomain->nReferenceCount > 0 || pDomain->nReferenceCountSuppressible > 0) &&
    !CLOCK_FLAG_IS_SET(pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /*
   * Voltage requests to make if necessary.
   */
  VRegRequest.eVRegLevel = pNewConfig->eVRegLevel;
  VRegRequest.bSuppressible = (pDomain->nReferenceCount == 0);

  /* Get the new source pointer. */
  nSrcIdx = pDrvCtxt->anSourceIndex[pNewConfig->HALConfig.eSource];

  if (nSrcIdx != 0xFF)
  {
    pNewSource = &pDrvCtxt->aSources[nSrcIdx];
  }
  else
  {
    pNewSource = NULL;
  }

  /*
   * Configure the source if required.
   */
  if (pNewSource != NULL && pNewConfig->pSourceFreqConfig != NULL)
  {
    eResult = Clock_ConfigSource(
      pDrvCtxt, pNewSource, pNewConfig->pSourceFreqConfig);

    if (eResult != DAL_SUCCESS)
    {
      // TODO error!
      return eResult;
    }
  }

  /*
   * If the domain is active, and the new source is different from the
   * current one then we enable the new source.
   */
  if (pDomain->pSource != pNewSource &&
      pNewSource != NULL)
  {
    /*
     * If there are insuppressible clocks enabled in this clock domain then we
     * need to make an insuppressible request on the new source.
     */
    if (pDomain->nReferenceCount > 0)
    {
      eResult = Clock_EnableSourceInternal(pDrvCtxt, pNewSource, FALSE);

      if (eResult != DAL_SUCCESS)
      {
        return eResult;
      }
    }

    /*
     * If there are suppressible clocks enabled in this clock domain then we
     * need to make a suppressible request on the new source.
     */
    if (pDomain->nReferenceCountSuppressible > 0)
    {
      eResult = Clock_EnableSourceInternal(pDrvCtxt, pNewSource, TRUE);

      if (eResult != DAL_SUCCESS)
      {
        return eResult;
      }
    }
  }

  /*
   * If we are increasing the voltage requirement, do so now.
   */
  if (bVoltageRequest && pNewConfig->eVRegLevel > pDomain->VRegRequest.eVRegLevel)
  {
    Clock_VoltageRequest(pDrvCtxt, &pDomain->VRegRequest, &VRegRequest);

    if (CLOCK_FLAG_IS_SET(pDomain, REPORT_CX_RAIL_UPDATES))
    {
      /*-----------------------------------------------------------------------*/
      /* Call the Limits Management callback function if one was specified.    */
      /*-----------------------------------------------------------------------*/

      if (pDrvCtxt->fpGpuUpdate != NULL)
      {
        LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

        fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
      }
    }
  }

  /*
   * Configure the clock MUX
   */
  HAL_clk_ConfigClockMux(pDomain->HALHandle, &pNewConfig->HALConfig);

  /*
   * If we are decreasing the voltage requirement, do so now.
   */
  if (bVoltageRequest && pNewConfig->eVRegLevel < pDomain->VRegRequest.eVRegLevel)
  {
    Clock_VoltageRequest(pDrvCtxt, &pDomain->VRegRequest, &VRegRequest);

    if (CLOCK_FLAG_IS_SET(pDomain, REPORT_CX_RAIL_UPDATES))
    {
      /*-----------------------------------------------------------------------*/
      /* Call the Limits Management callback function if one was specified.    */
      /*-----------------------------------------------------------------------*/

      if (pDrvCtxt->fpGpuUpdate != NULL)
      {
        LM_GpuUpdateFuncPtr fpGpuUpdate = pDrvCtxt->fpGpuUpdate;

        fpGpuUpdate((uint32)VRegRequest.eVRegLevel);
      }
    }
  }

  /*
   * If the domain is active, and the new source is different from the
   * current then we disable the old source.
   */
  if (pDomain->pSource != pNewSource &&
      pDomain->pSource != NULL)
  {
    /*
     * If there are insuppressible clocks enabled in this clock domain then we
     * need to remove the insuppressible request on the old source.
     */
    if (pDomain->nReferenceCount > 0)
    {
      eResult = Clock_DisableSourceInternal(pDrvCtxt, pDomain->pSource, FALSE, FALSE);

      if (eResult != DAL_SUCCESS)
      {
        return eResult;
      }
    }

    /*
     * If there are suppressible clocks enabled in this clock domain then we
     * need to remove the suppressible request on the old source.
     */
    if (pDomain->nReferenceCountSuppressible > 0)
    {
      eResult = Clock_DisableSourceInternal(pDrvCtxt, pDomain->pSource, TRUE, FALSE);

      if (eResult != DAL_SUCCESS)
      {
        return eResult;
      }
    }
  }

  /* Link the domain node to the new source node and update the active config */
  pDomain->pSource = pNewSource;

  /*
   * Check if the current configuration was setup dynamically
   */
  if(CLOCK_FLAG_IS_SET(pDomain, DOMAIN_DYNAMIC_CONFIG))
  {
    /*
     * If new configuration is different from the current one then
     * free up memory.
     */
    if(pDomain->pActiveMuxConfig != pNewConfig)
    {
      CLOCK_FLAG_CLEAR(pDomain, DOMAIN_DYNAMIC_CONFIG);
      DALSYS_Free (pDomain->pActiveMuxConfig);
    }
  }

  pDomain->pActiveMuxConfig = pNewConfig;

  return DAL_SUCCESS;

} /* END Clock_SetClockConfig */


/* =========================================================================
**  Function : Clock_SetClockFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetClockFrequency
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockIdType         nClock,
  uint32              nFreq,
  ClockFrequencyType  eMatch,
  uint32             *pnResultFreq
)
{
  ClockNodeType       *pClock;
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pNewConfig = NULL;
  DALResult            eResult;
  uint32               nFreqHz;
  uint32               nMult;

  /* Cast nClock to a proper pointer */
  pClock = (ClockNodeType *)nClock;

  /* Initialize the output parameter */
    if (pnResultFreq != NULL)
    {
      *pnResultFreq = 0;
    }

  /* Make sure the clock handle and domain are valid and supports frequency configuration. */
  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  if (pClock->pDomain == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  if (pClock->pDomain->pBSPConfig == NULL)
  {
    return DAL_ERROR_NOT_SUPPORTED;
  }

  pDomain = pClock->pDomain;

  /* Convert to Hz if necessary. */
  if (eMatch >= CLOCK_FREQUENCY_MHZ_AT_LEAST)
  {
    nMult = 1000000;
    nFreqHz = nFreq * 1000000;
    eMatch -= CLOCK_FREQUENCY_MHZ_AT_LEAST;
  }
  else if (eMatch >= CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    nMult = 1000;
    nFreqHz = nFreq * 1000;
    eMatch -= CLOCK_FREQUENCY_KHZ_AT_LEAST;
  }
  else
  {
    nMult = 1;
    nFreqHz = nFreq;
  }

  /* Look for a valid configuration */
  eResult = Clock_FindClockConfig (pDomain->pBSPConfig, nFreqHz, eMatch,
                                   &pNewConfig);

  if ((eResult != DAL_SUCCESS) || (pNewConfig == NULL))
  {
    return DAL_ERROR_NOT_SUPPORTED;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /* If the new config is the same as the active config, we're done */
  if (pNewConfig != pDomain->pActiveMuxConfig)
  {
    /*
     * If the clock source and voltage control is disabled, then just
     * configure the clock MUX.
     */
    if (CLOCK_FLAG_IS_SET(pClock, SUPPRESS_VOLTAGE_CONTROL))
    {
      HAL_clk_ConfigClockMux(pDomain->HALHandle, &pNewConfig->HALConfig);
      pDomain->pActiveMuxConfig = pNewConfig;
    }
    else
    {
      eResult = Clock_SetClockConfig(pDrvCtxt, pDomain, pNewConfig);
    }

    if (eResult == DAL_SUCCESS)
    {
      if (CLOCK_FLAG_IS_SET(pClock, LOG_FREQ_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
      {
        ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
                          "%s (Freq: %lu)",
                          pClock->szName, pNewConfig->nFreqHz);
      }
    }
  }
  else
  {
    eResult = DAL_SUCCESS;
  }

  if (pnResultFreq != NULL)
  {
    if (eResult == DAL_SUCCESS)
    {
      *pnResultFreq = pNewConfig->nFreqHz / nMult;

      /*
       * Only send out SW event when successful.
       */
      #ifdef WIN8EA
      if (pDrvCtxt->bQdssEnabled)
      {
        PEP_CLK_TRACE_CLOCK_FREQ(
          HAL_clk_GetTestClockId(pClock->HALHandle),
          *pnResultFreq * nMult);
      }
      #else
        QDSS_SWEVENT(CLOCK_EVENT_CLOCK_FREQ,HAL_clk_GetTestClockId(pClock->HALHandle),*pnResultFreq * nMult);
      #endif
      }
    else
    {
      *pnResultFreq = 0;
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_SetClockFrequency */


/* =========================================================================
**  Function : Clock_CalcGCD
** =========================================================================*/
/**
  Calculates greatest common divisor.

  This function calculates the GCD (greatest common divisor) of two integers.
  This is the standard Euclid's GCD calculation algorithm.

  @param uim_a [in] -- First integer
  @param uim_b [in] -- Second integer

  @return
  uint32 - GCD value

  @dependencies
  None.
*/

static uint32 Clock_CalcGCD
(
  uint32 nA,
  uint32 nB
)
{
  uint32 nC;
  if ((0 == nA) || (0 == nB))
  {
    return 0;
  }
  do
  {
    nC = nA%nB;

    if(0 == nC)
    {
      break;
    }

    nA = nB;

    nB = nC;
    /* nB is always less than nA*/
  }while(nA > nB);

  return nB;

} /* END Clock_CalcGCD */


/* =========================================================================
**  Function : Clock_SetUARTBaudClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetUARTBaudClock
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  uint32        nDI,
  uint32        nFI,
  uint32       *pnResultFreqHz
)
{
  ClockNodeType              *pClock;
  ClockDomainNodeType        *pDomain;
  DALResult                   eResult;
  ClockMuxConfigType         *pClockUARTConfig = NULL;
  uint32                      nSize;
  uint32                      nMVal, nNVal, nMNGCD;
  uint32                      nSrcIdx;
  ClockMuxConfigType         *pClockSIMBSPMuxConfig = NULL;
  ClockMuxConfigType         *pClockGSBIUARTBSPMuxConfig = NULL;
  ClockPropertyValueType      PropVal;
  uint32                      nResultFreqHz = 0;
  ClockSourceFreqConfigType  *pSourceFreqConfig;

  /*-----------------------------------------------------------------------*/
  /* Cast nClock to a proper pointer.                                      */
  /*-----------------------------------------------------------------------*/

  pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Check whether clock handle is valid.                                  */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL || pClock->pDomain == NULL)
  {
    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = 0;
    }
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Get SIM configuration.                                                */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("SIMClockConfig", &PropVal);

  if (eResult == DAL_SUCCESS)
  {
    pClockSIMBSPMuxConfig = (ClockMuxConfigType *)PropVal;
  }
  else
  {
    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = 0;
    }
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Get GSBI UART configuration.                                          */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("UARTClockConfig", &PropVal);

  if (eResult == DAL_SUCCESS)
  {
    pClockGSBIUARTBSPMuxConfig = (ClockMuxConfigType *)PropVal;
  }
  else
  {
    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = 0;
    }
    return DAL_ERROR;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  pDomain = pClock->pDomain;

  /*-----------------------------------------------------------------------*/
  /* Find source associated with SIM configuration.                        */
  /*-----------------------------------------------------------------------*/

  nSrcIdx = pDrvCtxt->anSourceIndex[pClockSIMBSPMuxConfig->HALConfig.eSource];
  if (nSrcIdx != 0xFF)
  {
    /*
     *  Compute new MND value base on:
     *  M = 16 * DI / ((GREATEST_COMMON_DIVISOR(M, N))
     *  N = nSimDivider * FI / (GREATEST_COMMON_DIVISOR(M, N))
     */
    nMVal = 16 * nDI;
    nNVal = (pClockSIMBSPMuxConfig->HALConfig.nDiv2x * nFI) / 2;

    nMNGCD = Clock_CalcGCD(nMVal, nNVal);
    nMVal /= nMNGCD;
    nNVal /= nMNGCD;

    /*
     * Calculate final GSBI UART clock frequency.
     */
    pSourceFreqConfig = pDrvCtxt->aSources[nSrcIdx].pActiveFreqConfig;
    nResultFreqHz = pSourceFreqConfig->nFreqHz * nMVal / nNVal;

    /*
     * Allocate dynamic memory for this new configuration
     */
    nSize = sizeof(ClockMuxConfigType);
    eResult = DALSYS_Malloc(nSize, (void **)&pClockUARTConfig);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to allocate %lu bytes for UART clock configuration.", nSize);

      if (pnResultFreqHz != NULL)
      {
        *pnResultFreqHz = 0;
      }
      DALCLOCK_FREE(pDrvCtxt);
      return eResult;
    }
    memset((void *)pClockUARTConfig, 0x0, nSize);

    /*
     * Update configuration parameters
     */
    pClockUARTConfig->nFreqHz = nResultFreqHz;
    pClockUARTConfig->HALConfig.eSource  = pClockSIMBSPMuxConfig->HALConfig.eSource;
    pClockUARTConfig->HALConfig.nDiv2x = 0;
    pClockUARTConfig->HALConfig.nM  = nMVal;
    pClockUARTConfig->HALConfig.nN  = nNVal;
    pClockUARTConfig->HALConfig.n2D = nNVal;
    pClockUARTConfig->eVRegLevel = CLOCK_VREG_LEVEL_NOMINAL;

    /*
     * Figure out what voltage we need to set for this frequency.
     *
     * NOTE: The following is not accurate since if our frequency value
     * is in between two different voltage levels then we could be picking up
     * higher voltage level than needed.  Better way is to have Fmax low, nominal
     * and high levels for UART in the BSP/XML and then doing comparison that way.
     * Our voltage level, for now though, is probably going to be CLOCK_VREG_LEVEL_LOW
     * after following loop is executed - so this is sufficient for now.
     */

    if (pClockGSBIUARTBSPMuxConfig == NULL)
    {
      *pnResultFreqHz = 0;
      DALSYS_Free(pClockUARTConfig);
      DALCLOCK_FREE (pDrvCtxt);
      return DAL_ERROR;
    }

    while (pClockGSBIUARTBSPMuxConfig->nFreqHz != 0)
    {
      if(nResultFreqHz <= pClockGSBIUARTBSPMuxConfig->nFreqHz)
      {
        pClockUARTConfig->eVRegLevel = pClockGSBIUARTBSPMuxConfig->eVRegLevel;
        break;
      }
      pClockGSBIUARTBSPMuxConfig++;
    }

    /*
     * Finally, we can set the new configuration for this clock.
     */
    eResult = Clock_SetClockConfig(pDrvCtxt, pDomain, pClockUARTConfig);

    if (eResult == DAL_SUCCESS)
    {
      if (CLOCK_FLAG_IS_SET(pClock, LOG_FREQ_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
      {
        ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
                          "%s (Freq: %lu)",
                          pClock->szName, pClockUARTConfig->nFreqHz);
      }

      /*
       * Set dynamic config flag
       */
      CLOCK_FLAG_SET(pDomain, DOMAIN_DYNAMIC_CONFIG);
    }
    else
    {
      /*
       * New configuration could not be set, so free up memory and
       * set resulting frequency value to 0.
       */
      DALSYS_Free (pClockUARTConfig);
      nResultFreqHz = 0;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update resulting frequency.                                           */
  /*-----------------------------------------------------------------------*/

  if (pnResultFreqHz != NULL)
  {
    *pnResultFreqHz = nResultFreqHz;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_SetUARTBaudClock */


/* =========================================================================
**  Function : Clock_SetClockDivider
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetClockDivider
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  uint32        nDivider
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure the hardware divider.                                       */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  HAL_clk_ConfigClockDivider(pClock->HALHandle, nDivider);

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pClock, LOG_CONFIG_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_CONFIG_CHANGE))
  {
    ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
                      "%s (Divider: %lu)",
                      pClock->szName, nDivider);
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_SetClockDivider */


/* =========================================================================
**  Function : Clock_InvertClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_InvertClock
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  boolean       bInvert
)
{

  /*-----------------------------------------------------------------------*/
  /* Not supported.                                                        */
  /*-----------------------------------------------------------------------*/

  return DAL_ERROR_NOT_SUPPORTED;

} /* END Clock_InvertClock */


/* =========================================================================
**  Function : Clock_ResetClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ResetClock
(
  ClockDrvCtxt   *pDrvCtxt,
  ClockIdType     nClock,
  ClockResetType  eReset
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Reset clock.                                                          */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  if (eReset == CLOCK_RESET_ASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(pClock->HALHandle, TRUE);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                        "%s (Reset: 1)", pClock->szName);
    }
  }

  if (eReset == CLOCK_RESET_DEASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(pClock->HALHandle, FALSE);

    /* Logging */
    if (CLOCK_FLAG_IS_SET(pClock, LOG_RESET) ||
        CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_RESET))
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                        "%s (Reset: 0)", pClock->szName);
    }
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_ResetClock */


/* =========================================================================
**  Function : Clock_ResetClock_STM
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ResetClock_STM
(
  ClockDrvCtxt   *pDrvCtxt,
  ClockIdType     nClock,
  ClockResetType  eReset
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Reset clock.                                                          */
  /*-----------------------------------------------------------------------*/

  if (eReset == CLOCK_RESET_ASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(pClock->HALHandle, TRUE);
  }
  if (eReset == CLOCK_RESET_DEASSERT || eReset == CLOCK_RESET_PULSE)
  {
    HAL_clk_ResetClock(pClock->HALHandle, FALSE);
  }

  return DAL_SUCCESS;

} /* END Clock_ResetClock_STM */


/* =========================================================================
**  Function : Clock_IsClockEnabled
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_IsClockEnabled
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  boolean      *pbIsEnabled
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check both pointer arguments.                                  */
  /*-----------------------------------------------------------------------*/

  if (pbIsEnabled == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output argument here.                                  */
  /*-----------------------------------------------------------------------*/

    *pbIsEnabled = FALSE;

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Get state from the HAL.                                               */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  *pbIsEnabled = HAL_clk_IsClockEnabled(pClock->HALHandle);

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_IsClockEnabled */


/* =========================================================================
**  Function : Clock_IsClockOn
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_IsClockOn
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  boolean      *pbIsOn
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check both pointer arguments.                                  */
  /*-----------------------------------------------------------------------*/

  if (pbIsOn == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output argument here.                                  */
  /*-----------------------------------------------------------------------*/

    *pbIsOn = FALSE;

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Get state from the HAL.                                               */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  *pbIsOn = HAL_clk_IsClockOn(pClock->HALHandle);

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_IsClockOn */


/* =========================================================================
**  Function : Clock_IsClockXOVote
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_IsClockXOVote
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  boolean       bCurrently,
  boolean      *pbIsXOVote
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;
  boolean        bRef;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    *pbIsXOVote = FALSE;
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Determine the state to return.                                        */
  /*-----------------------------------------------------------------------*/

  if (bCurrently == TRUE)
  {
    bRef = pClock->nReferenceCount > 0;
  }
  else
  {
    bRef = TRUE;
  }

  *pbIsXOVote = bRef &&
    !CLOCK_FLAG_IS_SET(pClock, SUPPRESSIBLE) &&
    !CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE) &&
    pClock->pDomain->pSource != NULL;
  *pbIsXOVote |= bRef && CLOCK_FLAG_IS_SET(pClock, XO_VOTE);

  return DAL_SUCCESS;

} /* END Clock_IsClockXOVote */


/* =========================================================================
**  Function : Clock_GetClockFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_GetClockFrequency
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  uint32       *pnFrequencyHz
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;
  HAL_clk_ClockMuxConfigType  HALConfig;
  uint32 nFreqHz = 0;
  uint32 nSrcIdx;
  ClockSourceFreqConfigType *pSourceFreqConfig;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL || pnFrequencyHz == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize output parameter                                           */
  /*-----------------------------------------------------------------------*/

  *pnFrequencyHz = 0;

  /*-----------------------------------------------------------------------*/
  /* Get state from current config either local copy or read from HW.      */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_LOCK(pDrvCtxt);

  if (pClock->pDomain->pActiveMuxConfig != NULL)
  {
    nFreqHz = pClock->pDomain->pActiveMuxConfig->nFreqHz;
  }
  else
  {
    HAL_clk_DetectClockMuxConfig(pClock->pDomain->HALHandle, &HALConfig);

    /*
     * Here we could loop over supported BSP configs and if found use
     * the frequency there which might be more accurate in some cases.
     */

    nSrcIdx = pDrvCtxt->anSourceIndex[HALConfig.eSource];

    if (nSrcIdx != 0xFF)
    {
      pSourceFreqConfig = pDrvCtxt->aSources[nSrcIdx].pActiveFreqConfig;

      /*-----------------------------------------------------------------------*/
      /* Verify that the source has been configured correctly.                 */
      /*-----------------------------------------------------------------------*/

      if (pSourceFreqConfig == NULL)
      {
        DALCLOCK_FREE(pDrvCtxt);
        *pnFrequencyHz = 0;
        return DAL_ERROR_INTERNAL;
      }

      nFreqHz = pSourceFreqConfig->nFreqHz;

      if (HALConfig.nDiv2x > 2)
      {
        nFreqHz = 2 * (nFreqHz / HALConfig.nDiv2x);
      }

      if (HALConfig.nM > 1)
      {
        nFreqHz *= HALConfig.nM;
      }

      if (HALConfig.nN > 1)
      {
        nFreqHz /= HALConfig.nN;
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* May need to store and use a clock divider in some cases...            */
  /*-----------------------------------------------------------------------*/

  DALCLOCK_FREE(pDrvCtxt);

  *pnFrequencyHz = nFreqHz;

  return DAL_SUCCESS;

} /* END Clock_GetClockFrequency */


/* =========================================================================
**  Function : Clock_ShowClockFrequencyAndVoltage
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ShowClockFrequencyAndVoltage
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockIdType         nClock,
  uint32              nFreq,
  ClockFrequencyType  eMatch,
  uint32             *pnResultFreq,
  uint32             *pnResultVoltage
)
{
  ClockNodeType       *pClock;
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pNewConfig = NULL;
  DALResult            eResult;
  uint32               nFreqHz;
  uint32               nMult;

  /* Cast nClock to a proper pointer */
  pClock = (ClockNodeType *)nClock;

  /* Validate passed in parameters. */
  if (pnResultFreq == NULL || pnResultVoltage == NULL)
  {
    return DAL_ERROR;
  }
  else
  {
    *pnResultFreq = 0;
    *pnResultVoltage = 0;
  }

  /* Make sure the clock handle is valid and supports frequency configuration. */
  if (pClock == NULL || pClock->pDomain == NULL ||
      pClock->pDomain->pBSPConfig == NULL)
  {
    return DAL_ERROR;
  }

  pDomain = pClock->pDomain;

  /* Convert to Hz if necessary. */
  if (eMatch >= CLOCK_FREQUENCY_MHZ_AT_LEAST)
  {
    nMult = 1000000;
    nFreqHz = nFreq * 1000000;
    eMatch -= CLOCK_FREQUENCY_MHZ_AT_LEAST;
  }
  else if (eMatch >= CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    nMult = 1000;
    nFreqHz = nFreq * 1000;
    eMatch -= CLOCK_FREQUENCY_KHZ_AT_LEAST;
  }
  else
  {
    nMult = 1;
    nFreqHz = nFreq;
  }

  /* Look for a valid configuration */
  eResult = Clock_FindClockConfig (pDomain->pBSPConfig, nFreqHz, eMatch,
                                   &pNewConfig);

  if ((eResult != DAL_SUCCESS) || (pNewConfig == NULL))
  {
    return DAL_ERROR;
  }

  /* Prepare the return results. */
  *pnResultFreq    = pNewConfig->nFreqHz / nMult;
  *pnResultVoltage = pNewConfig->eVRegLevel;

  return eResult;

} /* END Clock_ShowClockFrequencyAndVoltage */


/* =========================================================================
**  Function : Clock_FindExternalSourceConfig
** =========================================================================*/
/**
  Finds a particular external source configuration in the BSP.

  This function finds a particular external source configuration in the BSP
  based on the specified frequency. The configuration returned must be for
  a frequency that is greater than or equal to the target frequency.

  @param *pBSPConfig [in] -- Pointer to a list of configurations
  @param nFreqHz [in] -- Frequency in Hz
  @param **pMatchingConfig [out] -- Matching configuration

  @return
  DAL_SUCCESS -- A matching configuration was found.
  DAL_ERROR -- A matching configuration was not found.

  @dependencies
  None.
*/

static DALResult Clock_FindExternalSourceConfig
(
  ClockMuxConfigType  *pBSPConfig,
  uint32               nFreqHz,
  ClockMuxConfigType **pMatchingConfig
)
{
  ClockMuxConfigType *pLastConfig = NULL;

  /* Make sure the list of configurations isn't empty */
  if (pBSPConfig == NULL || pMatchingConfig == NULL)
  {
    if (pMatchingConfig != NULL)
  {
    *pMatchingConfig = NULL;
    }
    return DAL_ERROR;
  }

  /* Loop over all configurations */
  while (pBSPConfig->nFreqHz != 0)
  {
    /*
     * Skip configurations that aren't for this chip or version, and configurations
     * that do not rely on an external source.
     */
    if (!Clock_IsBSPSupported(&pBSPConfig->HWVersion) ||
        (pBSPConfig->HALConfig.eSource < HAL_CLK_SOURCE_EXTERNAL) ||
         (pBSPConfig->HALConfig.eSource >= HAL_CLK_NUM_OF_EXTERNAL_SOURCES))
    {
      pBSPConfig++;
      continue;
    }

    /*
     * Return the first configuration whose frequency is greater than or equal to
     * the target frequency.
     */
    if (pBSPConfig->nFreqHz >= nFreqHz)
    {
      *pMatchingConfig = pBSPConfig;
      return DAL_SUCCESS;
    }

    /* Save the last available configuration. */
    pLastConfig = pBSPConfig;

    /* Move to the next configuration */
    pBSPConfig++;
  }

  /* Return the last available configuration, or fail. */
  if (pLastConfig != NULL)
  {
    *pMatchingConfig = pLastConfig;
    return DAL_SUCCESS;
  }

  /* No match was found */
  *pMatchingConfig = NULL;

  return DAL_ERROR;

} /* END Clock_FindExternalSourceConfig */


/* =========================================================================
**  Function : Clock_SelectExternalSource
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SelectExternalSource
(
  ClockDrvCtxt   *pDrvCtxt,
  ClockIdType    nClock,
  uint32         nFreqHz,
  uint32         nSource,
  uint32         nDiv2x,
  uint32         nM,
  uint32         nN,
  uint32         n2D
)
{
  HAL_clk_ClockMuxConfigType Config;
  ClockNodeType *pClock = (ClockNodeType *)nClock;
  ClockDomainNodeType *pDomain;
  ClockMuxConfigType  *pNewConfig = NULL;
  boolean              bVoltageRequest;
  ClockVRegRequestType  VRegRequest;

  /*-----------------------------------------------------------------------*/
  /* Since we are directly mapping input source value to HAL source        */
  /* enum, we need to be bit more careful as to not go beyond the max      */
  /* external HAL source enum.                                             */
  /*-----------------------------------------------------------------------*/

  uint32 nMaxExternalSrcCount = (uint32) (HAL_CLK_NUM_OF_EXTERNAL_SOURCES
                                          - HAL_CLK_SOURCE_EXTERNAL);

  /*-----------------------------------------------------------------------*/
  /* Sanity check the arguments.                                           */
  /*-----------------------------------------------------------------------*/

  if ((pClock            == NULL                ) ||
      (nSource           >= nMaxExternalSrcCount))
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  if (pClock->pDomain == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  pDomain = pClock->pDomain;

  /*
   * Find the voltage corner data for the given frequency, if specified.
   * If the voltage corner data. or the frequency is not specified, then
   * assume the voltage does not matter.
   */
  if (nFreqHz != 0)
  {
    (void) Clock_FindExternalSourceConfig (pDomain->pBSPConfig, nFreqHz, &pNewConfig);
  }

  /*
   * Determine if we should make a voltage request.  We do so if this
   * domain is not configured to make requests when enabled, or if it
   * is thus configured and is currently enabled.
   */
  bVoltageRequest =
    (pDomain->nReferenceCount > 0 || pDomain->nReferenceCountSuppressible > 0) &&
    !CLOCK_FLAG_IS_SET(pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /*
   * If we are increasing the voltage requirement, do so now.
   */
  if (pNewConfig != NULL)
  {
    /*
     * Voltage requests to make if necessary.
     */
    VRegRequest.eVRegLevel = pNewConfig->eVRegLevel;
    VRegRequest.bSuppressible = (pDomain->nReferenceCount == 0);

    if (bVoltageRequest && pNewConfig->eVRegLevel > pDomain->VRegRequest.eVRegLevel)
    {
      Clock_VoltageRequest(pDrvCtxt, &pDomain->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Define the mux configuration.                                         */
  /*-----------------------------------------------------------------------*/

  Config.eSource = (HAL_clk_SourceType)
                     (nSource + (uint32)HAL_CLK_SOURCE_EXTERNAL);
  Config.nDiv2x  = nDiv2x;
  Config.nM      = nM;
  Config.nN      = nN;
  Config.n2D     = n2D;

  /*-----------------------------------------------------------------------*/
  /* Configure the clock to external source.                               */
  /*-----------------------------------------------------------------------*/

  HAL_clk_ConfigClockMux(pDomain->HALHandle, &Config);

  /*
   * If we are decreasing the voltage requirement, do so now.
   */
  if (pNewConfig != NULL)
  {
    if (bVoltageRequest && pNewConfig->eVRegLevel < pDomain->VRegRequest.eVRegLevel)
    {
      Clock_VoltageRequest(pDrvCtxt, &pDomain->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update the source tree.                                               */
  /*-----------------------------------------------------------------------*/

  if (pDomain->pSource != NULL && pDomain->nReferenceCount > 0)
  {
    Clock_DisableSourceInternal(
      pDrvCtxt, pDomain->pSource, CLOCK_FLAG_IS_SET(pDomain, SUPPRESSIBLE), FALSE);
  }

  pDomain->pSource = NULL;
  pDomain->pActiveMuxConfig = pNewConfig;

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_SelectExternalSource */


/* =========================================================================
**  Function : Clock_CalcClockFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_CalcClockFrequency
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   nClock,
  uint32       *pnFrequencyHz
)
{
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the arguments.                                           */
  /*-----------------------------------------------------------------------*/

  if ((pClock == NULL) || (pnFrequencyHz == NULL))
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output parameter.                                      */
  /*-----------------------------------------------------------------------*/

  *pnFrequencyHz = 0;

  /*-----------------------------------------------------------------------*/
  /* Call HAL to calculate clock frequency.                                */
  /*-----------------------------------------------------------------------*/

  HAL_clk_CalcClockFreq(pClock->HALHandle, pnFrequencyHz);

  return DAL_SUCCESS;

} /* END Clock_CalcClockFrequency */


/* =========================================================================
**  Function : Clock_GetPowerDomainId
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_GetPowerDomainId
(
  ClockDrvCtxt           *pDrvCtxt,
  const char             *szPowerDomain,
  ClockPowerDomainIdType *pnPowerDomainId
)
{
  uint32   nPowerDomainIndex;
  boolean  bFound;

  /*-----------------------------------------------------------------------*/
  /* Validate pointers are usable.                                         */
  /*-----------------------------------------------------------------------*/

  if (!szPowerDomain || !pnPowerDomainId)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output parameter.                                      */
  /*-----------------------------------------------------------------------*/

  *pnPowerDomainId = (ClockPowerDomainIdType)NULL;

  /*-----------------------------------------------------------------------*/
  /* Search the array of power domain nodes, break if we find a match      */
  /*-----------------------------------------------------------------------*/

  bFound = FALSE;

  for (nPowerDomainIndex = 0; nPowerDomainIndex < pDrvCtxt->nNumPowerDomains; nPowerDomainIndex++)
  {
    if (strcmp (szPowerDomain, pDrvCtxt->aPowerDomains[nPowerDomainIndex].szName) == 0)
    {
      bFound = TRUE;
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the power domain node if found, otherwise NULL    */
  /*-----------------------------------------------------------------------*/

  if (bFound)
  {
    *pnPowerDomainId =
      (ClockPowerDomainIdType)&pDrvCtxt->aPowerDomains[nPowerDomainIndex];
    return DAL_SUCCESS;
  }
  else
  {
    return DAL_ERROR_NOT_FOUND;
  }

} /* END Clock_GetPowerDomainId */


/* =========================================================================
**  Function : Clock_EnablePowerDomain
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnablePowerDomain
(
  ClockDrvCtxt           *pDrvCtxt,
  ClockPowerDomainIdType  nPowerDomainId
)
{
  ClockPowerDomainNodeType *pPowerDomain = NULL;

  /* Cast nPowerDomainId to a proper pointer */
  pPowerDomain = (ClockPowerDomainNodeType*)nPowerDomainId;

  /* Make sure the power domain handle is valid */
  if (pPowerDomain == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /* If the reference count is zero, we need to enable the power domain */
  if (pPowerDomain->nReferenceCount == 0)
  {
    /* Enable the power domain */
    if (!pPowerDomain->bEnabled)
    {
      HAL_clk_EnablePowerDomain (pPowerDomain->HALHandle);
      pPowerDomain->bEnabled = TRUE;

      /* Logging */
      if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                          "%s (Enabled: 1)", pPowerDomain->szName);
      }
    }
  }

  /* Increment the reference count */
  pPowerDomain->nReferenceCount++;

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_EnablePowerDomain */


/* =========================================================================
**  Function : Clock_DisablePowerDomain
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_DisablePowerDomain
(
  ClockDrvCtxt           *pDrvCtxt,
  ClockPowerDomainIdType  nPowerDomainId
)
{
  ClockPowerDomainNodeType *pPowerDomain = NULL;

  /* Cast nPowerDomainId to a proper pointer */
  pPowerDomain = (ClockPowerDomainNodeType*)nPowerDomainId;

  /* Make sure the power domain handle is valid */
  if (pPowerDomain == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*
   * If the reference count is one or zero, we need to disable the power domain.
   * Ignore if the DO_NOT_DISABLE bits are set.
   */
  if ((pPowerDomain->nReferenceCount <= 1) &&
      !CLOCK_FLAG_IS_SET(pPowerDomain, DO_NOT_DISABLE) &&
      !CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_POWER_DOMAINS))
  {
    /* Disable the power domain */
    if (pPowerDomain->bEnabled)
    {
      HAL_clk_DisablePowerDomain (pPowerDomain->HALHandle);
      pPowerDomain->bEnabled = FALSE;

      /* Logging */
      if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                          "%s (Enabled: 0)", pPowerDomain->szName);
      }
    }
  }

  /* Decrement the reference count */
  if (pPowerDomain->nReferenceCount > 0)
  {
    pPowerDomain->nReferenceCount--;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_DisablePowerDomain */


/* =========================================================================
**  Function : Clock_EnablePowerDomainHW
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnablePowerDomainHW
(
  ClockDrvCtxt           *pDrvCtxt,
  ClockPowerDomainIdType  nPowerDomainId
)
{
  ClockPowerDomainNodeType *pPowerDomain = NULL;

  /* Cast nPowerDomainId to a proper pointer */
  pPowerDomain = (ClockPowerDomainNodeType*)nPowerDomainId;

  /* Make sure the power domain handle is valid */
  if (pPowerDomain == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /* Make sure HW control is supported for this power domain */
  if (!HAL_clk_IsPowerDomainSupported(pPowerDomain->HALHandle, HAL_CLK_POWER_DOMAIN_API_ENABLE_HW))
  {
    return DAL_ERROR_NOT_SUPPORTED;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /* If the reference count is zero, we need to enable the power domain HW Control mode. */
  if (pPowerDomain->nReferenceCountHW == 0)
  {
    /* Enable the power domain HW Control mode. */
    if (!pPowerDomain->bEnabledHW)
    {
      HAL_clk_EnablePowerDomainHW (pPowerDomain->HALHandle);
      pPowerDomain->bEnabledHW = TRUE;

      /* Logging */
      if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                          "%s (EnabledHW: 1)", pPowerDomain->szName);
      }
    }
  }

  /* Increment the reference count */
  pPowerDomain->nReferenceCountHW++;

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_EnablePowerDomainHW */


/* =========================================================================
**  Function : Clock_DisablePowerDomainHW
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_DisablePowerDomainHW
(
  ClockDrvCtxt           *pDrvCtxt,
  ClockPowerDomainIdType  nPowerDomainId
)
{
  ClockPowerDomainNodeType *pPowerDomain = NULL;

  /* Cast nPowerDomainId to a proper pointer */
  pPowerDomain = (ClockPowerDomainNodeType*)nPowerDomainId;

  /* Make sure the power domain handle is valid */
  if (pPowerDomain == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /* Make sure HW control is supported for this power domain */
  if (!HAL_clk_IsPowerDomainSupported(pPowerDomain->HALHandle, HAL_CLK_POWER_DOMAIN_API_DISABLE_HW))
  {
    return DAL_ERROR_NOT_SUPPORTED;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*
   * If the reference count is one or zero, we need to disable the power domain HW Control mode.
   * Ignore if the DO_NOT_DISABLE bits are set.
   */
  if ((pPowerDomain->nReferenceCountHW <= 1) &&
      !CLOCK_FLAG_IS_SET(pPowerDomain, DO_NOT_DISABLE) &&
      !CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_POWER_DOMAINS))
  {
    /* Disable the power domain HW Control mode */
    if (pPowerDomain->bEnabledHW)
    {
      HAL_clk_DisablePowerDomainHW (pPowerDomain->HALHandle);
      pPowerDomain->bEnabledHW = FALSE;

      /* Logging */
      if (CLOCK_FLAG_IS_SET(pPowerDomain, LOG_STATE_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_POWER_DOMAIN_STATE_CHANGE))
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog,
                          "%s (EnabledHW: 0)", pPowerDomain->szName);
      }
    }
  }

  /* Decrement the reference count */
  if (pPowerDomain->nReferenceCountHW > 0)
  {
    pPowerDomain->nReferenceCountHW--;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return DAL_SUCCESS;

} /* END Clock_DisablePowerDomainHW */


/* =========================================================================
**  Function : Clock_ConfigClock
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ConfigClock
(
  ClockDrvCtxt     *pDrvCtxt,
  ClockIdType      nClock,
  ClockConfigType  eConfig
)
{
  DALResult eResult = DAL_SUCCESS;
  ClockNodeType *pClock = (ClockNodeType *)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Validity check for SUPPRESSIBLE/INSUPRESSIBLE requests.               */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_MARK_SUPPRESSIBLE ||
      eConfig == CLOCK_CONFIG_MARK_INSUPPRESSIBLE)
  {
    /*
     * Make sure this action is allowed for this clock
     */
    if (Clock_CheckNameList("SuppressibleList", pClock->szName) == FALSE)
    {
      return DAL_ERROR_NOT_ALLOWED;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Perform SUPPRESSIBLE/INSUPPRESSIBLE handling if requested.            */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_MARK_SUPPRESSIBLE)
  {
    if (pClock->nReferenceCount == 0)
    {
      CLOCK_FLAG_SET(pClock, SUPPRESSIBLE);
      return DAL_SUCCESS;
    }
    else
    {
      if (CLOCK_FLAG_IS_SET(pClock, SUPPRESSIBLE))
      {
        return DAL_SUCCESS;
      }
      /*
       * If the clock has already been enabled while in the INSUPPRESSIBLE
       * state, then remove the previous INSUPPRESSIBLE request before
       * asserting the new SUPPRESSIBLE one by toggling the clock enable/
       * disable logic without actually touching the hardware.
       */
      DALCLOCK_LOCK(pDrvCtxt);
      CLOCK_FLAG_SET(pClock, SUPPRESSIBLE);
      if (Clock_EnableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags) != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }
      CLOCK_FLAG_CLEAR(pClock, SUPPRESSIBLE);
      if (Clock_DisableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags) != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }
      CLOCK_FLAG_SET(pClock, SUPPRESSIBLE);
      DALCLOCK_FREE(pDrvCtxt);
      return DAL_SUCCESS;
    }
  }
  else if (eConfig == CLOCK_CONFIG_MARK_INSUPPRESSIBLE)
  {
    if (pClock->nReferenceCount == 0)
    {
      CLOCK_FLAG_CLEAR(pClock, SUPPRESSIBLE);
      return DAL_SUCCESS;
    }
    else
    {
      if (!CLOCK_FLAG_IS_SET(pClock, SUPPRESSIBLE))
      {
        return DAL_SUCCESS;
      }
      /*
       * If the clock has already been enabled while in the SUPPRESSIBLE
       * state, then remove the previous SUPPRESSIBLE request before
       * asserting the new INSUPPRESSIBLE one by toggling the clock enable/
       * disable logic without actually touching the hardware.
       */
      DALCLOCK_LOCK(pDrvCtxt);
      CLOCK_FLAG_CLEAR(pClock, SUPPRESSIBLE);
      if (Clock_EnableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags) != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }
      CLOCK_FLAG_SET(pClock, SUPPRESSIBLE);
      if (Clock_DisableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags) != DAL_SUCCESS)
      {
        DALCLOCK_FREE(pDrvCtxt);
        return DAL_ERROR_INTERNAL;
      }
      CLOCK_FLAG_CLEAR(pClock, SUPPRESSIBLE);
      DALCLOCK_FREE(pDrvCtxt);
      return DAL_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Validity check for REFERENCE COUNTER SUSPENSION/RESUMPTION requests.  */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_SUSPEND_REF_COUNTING ||
      eConfig == CLOCK_CONFIG_RESUME_REF_COUNTING)
  {
    /*
     * Make sure this action is allowed for this clock
     */
    if (Clock_CheckNameList("RefCountSuspendedList", pClock->szName) == FALSE)
    {
      return DAL_ERROR_NOT_ALLOWED;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Perform REFERENCE COUNTER SUSPENSION/RESUMPTION handling if requested.*/
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_SUSPEND_REF_COUNTING)
  {
    CLOCK_FLAG_SET(pClock, NO_REFERENCE_COUNTING);
    return DAL_SUCCESS;
  }
  else if (eConfig == CLOCK_CONFIG_RESUME_REF_COUNTING)
  {
    CLOCK_FLAG_CLEAR(pClock, NO_REFERENCE_COUNTING);
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validity check for MARK ALWAYS ON requests.                           */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_MARK_ALWAYS_ON_TRUE ||
      eConfig == CLOCK_CONFIG_MARK_ALWAYS_ON_FALSE)
  {
    /*
     * Make sure this action is allowed for this clock
     */
    if (Clock_CheckNameList("SuppressibleList",  pClock->szName) == FALSE ||
        Clock_CheckNameList("ClockAlwaysOnList", pClock->szName) == FALSE)
    {
      return DAL_ERROR_NOT_ALLOWED;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Perform MARK ALWAYS ON request handling if requested.                 */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_MARK_ALWAYS_ON_TRUE)
  {
    CLOCK_FLAG_SET(pClock, LEAVE_ALWAYS_ON);
    return DAL_SUCCESS;
  }
  else if (eConfig == CLOCK_CONFIG_MARK_ALWAYS_ON_FALSE)
  {
    CLOCK_FLAG_CLEAR(pClock, LEAVE_ALWAYS_ON);
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Validity check for FORCE_MEM_CORE/PERIPH_ENABLED requests.            */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_FORCE_MEM_CORE_ENABLED ||
      eConfig == CLOCK_CONFIG_FORCE_MEM_PERIPH_ENABLED ||
      eConfig == CLOCK_CONFIG_FORCE_MEM_CORE_AND_MEM_PERIPH_ENABLED)
  {
    /*
     * Make sure this action is allowed for this clock
     */
    if (Clock_CheckNameList("ForceMemCoreAndPeriphList", pClock->szName) == FALSE)
    {
      return DAL_ERROR_NOT_ALLOWED;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Perform REPORT CX RAIL UPDATES request handling if requested.         */
  /*-----------------------------------------------------------------------*/

  if (eConfig == CLOCK_CONFIG_REPORT_CX_RAIL_UPDATES)
  {
    CLOCK_FLAG_SET(pClock->pDomain, REPORT_CX_RAIL_UPDATES);
    return DAL_SUCCESS;
  }

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Since we have mapped the lower bits of HAL_clk_ClockConfigType to be  */
  /* the same as ClockConfigType, we can just pass the value directly to   */
  /* HAL layer.  Thus, only doing range check here.                        */
  /*-----------------------------------------------------------------------*/

  if (eConfig < CLOCK_CONFIG_TOTAL)
  {
    switch (eConfig)
    {
      case CLOCK_CONFIG_BRANCH_ONLY_ENABLE:
        /*
         * Make sure the domain is enabled and any necessary
         * voltage request is in place before allowing branch-only
         * clock control.
         */
        if (pClock->pDomain->nReferenceCount == 0)
        {
          eResult = Clock_EnableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags);

          /* Explicitly vote for XO on behalf of this clock, if necessary. */
          if ((eResult == DAL_SUCCESS) && CLOCK_FLAG_IS_SET(pClock, XO_VOTE))
          {
            eResult = Clock_EnableSourceInternal(pDrvCtxt,
              &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO]], FALSE);
          }
        }

        if (eResult == DAL_SUCCESS)
        {
          CLOCK_FLAG_SET(pClock, BRANCH_ONLY_CONTROL);
        }
        break;

      case CLOCK_CONFIG_BRANCH_ONLY_DISABLE:
        if (!CLOCK_FLAG_IS_SET(pClock, BRANCH_ONLY_CONTROL))
        {
          CLOCK_FLAG_CLEAR(pClock, BRANCH_ONLY_CONTROL);

          /*
           * If the domain is no longer necessary, make sure the domain is disabled
           * to keep the associated source and voltage properly maintained.
           */
          if (pClock->nReferenceCount == 0)
          {
            eResult = Clock_DisableClockDomain(pDrvCtxt, pClock->pDomain, pClock->nFlags);

            /* Remove the explicit XO vote on behalf of this clock, if necessary. */
            if ((eResult == DAL_SUCCESS) && CLOCK_FLAG_IS_SET(pClock, XO_VOTE))
            {
              eResult = Clock_DisableSourceInternal(pDrvCtxt,
                &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[HAL_CLK_SOURCE_XO]], FALSE, FALSE);
            }
          }
        }
        break;

      default:
        HAL_clk_ConfigClock(pClock->HALHandle, (HAL_clk_ClockConfigType) eConfig);
        break;
    }
  }
  else
  {
    eResult = DAL_ERROR_OUT_OF_RANGE_PARAMETER;
  }

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_ConfigClock */


/* =========================================================================
**  Function : Clock_LogState
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_LogState
(
  ClockDrvCtxt        *pDrvCtxt,
  ULogHandle           hULog,
  uint32               nFlags
)
{
  ClockNodeType               *pClock;
  ClockPowerDomainNodeType    *pPowerDomain;
  uint32                       i, eSource, nFreqHz, nFreqHzConfig;
  int32                        nIsOn, nIsEnabled, nReset;
  boolean                      bIsEnabled, bIsOn, bCalcSupported;

  if (hULog == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  ULOG_RT_PRINTF_0(hULog, ",CLOCK,ON,ENABLED,RESET,REF COUNT,FREQ CONFIG,FREQ CALC,VOLTAGE,SOURCE");

  /*------------------------------------------------------------------------*/
  /* Log clock state.                                                       */
  /*------------------------------------------------------------------------*/

  for (i = 0; i < pDrvCtxt->nNumClocks; i++)
  {
    pClock = &pDrvCtxt->aClocks[i];
    nIsEnabled = nIsOn = nReset = -1;
    eSource = nFreqHzConfig = 0;
    bCalcSupported = FALSE;

    /*
     * Get enabled state.
     */
    if (HAL_clk_IsClockSupported(pClock->HALHandle, HAL_CLK_CLOCK_API_ISENABLED))
    {
      Clock_IsClockEnabled(pDrvCtxt, (ClockIdType)pClock, &bIsEnabled);
      nIsEnabled = bIsEnabled ? 1 : 0;
    }

    /*
     * Get ON state.
     */
    if (HAL_clk_IsClockSupported(pClock->HALHandle, HAL_CLK_CLOCK_API_ISON))
    {
      Clock_IsClockOn(pDrvCtxt, (ClockIdType)pClock, &bIsOn);
      nIsOn = bIsOn ? 1 : 0;
    }

    /*
     * Get reset state.
     */
    if (HAL_clk_IsClockSupported(pClock->HALHandle, HAL_CLK_CLOCK_API_RESET))
    {
      nReset = HAL_clk_IsClockReset(pClock->HALHandle);
    }

    /*
     * Get frequency.
     */
    if (pClock->pDomain->pActiveMuxConfig != NULL)
    {
      nFreqHzConfig = pClock->pDomain->pActiveMuxConfig->nFreqHz;
    }

    /*
     * Calculate frequency.
     */
    if ((nFlags & CLOCK_LOG_STATE_CLOCK_FREQUENCY) &&
        HAL_clk_IsClockSupported(pClock->HALHandle, HAL_CLK_CLOCK_API_CALCFREQ))
    {
      bCalcSupported = TRUE;
      Clock_CalcClockFrequency(pDrvCtxt, (ClockIdType)pClock, &nFreqHz);
    }

    /*
     * Get source.
     */
    if (pClock->pDomain->pSource)
    {
      eSource = pClock->pDomain->pSource->eSource;
    }

    /*
     * Log results.
     */
    if (bCalcSupported)
    {
      ULOG_RT_PRINTF_9(hULog, ",%s,%d,%d,%d,%d,%u,%u,%d,%d",
        pClock->szName, nIsOn, nIsEnabled, nReset, pClock->nReferenceCount,
        nFreqHzConfig, nFreqHz, pClock->pDomain->VRegRequest.eVRegLevel, eSource);
    }
    else
    {
      ULOG_RT_PRINTF_8(hULog, ",%s,%d,%d,%d,%d,%u,-1,%d,%d",
        pClock->szName, nIsOn, nIsEnabled, nReset, pClock->nReferenceCount,
        nFreqHzConfig, pClock->pDomain->VRegRequest.eVRegLevel, eSource);
    }
  }

  /*------------------------------------------------------------------------*/
  /* Log power domain state.                                                */
  /*------------------------------------------------------------------------*/

  ULOG_RT_PRINTF_0(hULog, "");
  ULOG_RT_PRINTF_0(hULog, "");
  ULOG_RT_PRINTF_0(hULog, ",POWER DOMAIN,ON,ENABLED,REF COUNT");

  for (i = 0; i < pDrvCtxt->nNumPowerDomains; i++)
  {
    pPowerDomain = &pDrvCtxt->aPowerDomains[i];
    bIsEnabled = HAL_clk_IsPowerDomainEnabled(pDrvCtxt->aPowerDomains[i].HALHandle);
    bIsOn = HAL_clk_IsPowerDomainOn(pDrvCtxt->aPowerDomains[i].HALHandle);

    ULOG_RT_PRINTF_4(hULog, ",%s,%d,%d,%d", pPowerDomain->szName, bIsOn,
      bIsEnabled, pPowerDomain->nReferenceCount);
  }

  return DAL_SUCCESS;

} /* END Clock_LogState */


/* =========================================================================
**  Function : Clock_InitFlags
** =========================================================================*/
/**
  Initialize the flag attributes of clock(s)/domain(s).

  This function initializes the flag attributes of particular clock(s)
  and domain(s) as specified in the BSP data.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param eType     [in] -- Node type to process.

  @return
  DAL_SUCCESS -- Flag init was successful.
  DAL_ERROR -- Flag init failed.

  @dependencies
  None.
*/

DALResult Clock_InitFlags
(
  ClockDrvCtxt      *pDrvCtxt,
  ClockFlagNodeType  eType
)
{
  DALResult                  eResult;
  ClockPropertyValueType     PropVal;
  ClockFlagInitType         *pClockInitFlags;
  ClockNodeType             *pClock;
  ClockPowerDomainNodeType  *pPowerDomain;
  ClockSourceNodeType       *pSource;

  /*-----------------------------------------------------------------------*/
  /* Get the list of clock flags to initialize.                            */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockInitFlags", &PropVal);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
      "Clock_GetPropertyValue failed in Clock_InitFlags.");

    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Init the flag for each source/clock/domain present in the BSP/XML.    */
  /*-----------------------------------------------------------------------*/

  for (pClockInitFlags = (ClockFlagInitType *)PropVal;
       pClockInitFlags->eNodeType != CLOCK_FLAG_NODE_TYPE_NONE;
       pClockInitFlags++)
  {
    /*
     * Validate the target is supported.
     */
    if (pClockInitFlags->eNodeType >= CLOCK_FLAG_NODE_TYPE_MAX_SUPPORTED)
    {
      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "ClockInitFlags contains invalid node type.");

      /*
       * Skip this flag init and continue onward.
       */
      continue;
    }

    /*
     *  Init CLOCKs flags only.
     */
    if ((eType == CLOCK_FLAG_NODE_TYPE_CLOCK) &&
        (pClockInitFlags->eNodeType == CLOCK_FLAG_NODE_TYPE_CLOCK))
    {
      /*
       * Get the clock ID.
       */
      eResult =
        Clock_GetClockId(
          pDrvCtxt,
          (const char *)pClockInitFlags->pID,
          (ClockIdType *)&pClock);

      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to get clock ID[%s]", (const char *)pClockInitFlags->pID);

        /*
         * Skip this flag init and continue onward.
         */
        continue;
      }

      /*
       * Update the clock flags.
       */
        pClock->nFlags = pClockInitFlags->nFlag;
      }

    /*
     *  Init CLOCK_DOMAINs flags only.
     */
    if ((eType == CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN) &&
        (pClockInitFlags->eNodeType == CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN))
      {
      /*
       * Get the clock ID.
       */
      eResult =
        Clock_GetClockId(
        pDrvCtxt,
        (const char *)pClockInitFlags->pID,
        (ClockIdType *)&pClock);

      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to get clock ID[%s]", (const char *)pClockInitFlags->pID);

        /*
         * Skip this flag init and continue onward.
         */
        continue;
      }

      /*
       * Update the clock domain flags.
       */
      pClock->pDomain->nFlags = pClockInitFlags->nFlag;
    }

    /*
     *  Init POWER_DOMAINs flags only.
     */
    if ((eType == CLOCK_FLAG_NODE_TYPE_POWER_DOMAIN) &&
        (pClockInitFlags->eNodeType == CLOCK_FLAG_NODE_TYPE_POWER_DOMAIN))
    {
      /*
       * Get the power domain ID.
       */
      eResult =
        Clock_GetPowerDomainId(
          pDrvCtxt,
          (const char *)pClockInitFlags->pID,
          (ClockPowerDomainIdType *)&pPowerDomain);

      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to get power domain ID[%s]", (const char *)pClockInitFlags->pID);

        /*
         * Skip this flag init and continue onward.
         */
        continue;
      }

      /*
       * Update the power domain flags.
       */
      pPowerDomain->nFlags = pClockInitFlags->nFlag;
    }

    /*
     *  Init SOURCEs flags only.
     */
    if ((eType == CLOCK_FLAG_NODE_TYPE_SOURCE) &&
        (pClockInitFlags->eNodeType == CLOCK_FLAG_NODE_TYPE_SOURCE))
      {
      /*
       * Get the source ID.
       */
      eResult =
        Clock_GetSourceId(
          pDrvCtxt,
          (const char *)pClockInitFlags->pID,
          (SourceIdType *)&pSource);

      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
          "Unable to get source ID[%s]", (const char *)pClockInitFlags->pID);

        /*
         * Skip this flag init and continue onward.
         */
        continue;
      }

      /*
       * Update the source flags.
       */
      pSource->nFlags = pClockInitFlags->nFlag;
    }
  }

  return DAL_SUCCESS;

} /* END Clock_InitFlags */


/* =========================================================================
**  Function : Clock_GetSourceId
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_GetSourceId
(
  ClockDrvCtxt  *pDrvCtxt,
  const char    *szSource,
  SourceIdType  *pnId
)
{
  uint32   nSourceIndex;
  boolean  bFound;

  /*-----------------------------------------------------------------------*/
  /* Validate pointers are usable.                                         */
  /*-----------------------------------------------------------------------*/

  if (!szSource || !pnId)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize output parameter.                                          */
  /*-----------------------------------------------------------------------*/

  *pnId = (SourceIdType)NULL;

  /*-----------------------------------------------------------------------*/
  /* Search the array of source nodes, break if we find a match            */
  /*-----------------------------------------------------------------------*/

  bFound = FALSE;

  for (nSourceIndex = 0; nSourceIndex < pDrvCtxt->nNumSources; nSourceIndex++)
  {
    if (strcmp (szSource, pDrvCtxt->aSources[nSourceIndex].szName) == 0)
    {
      bFound = TRUE;
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return a pointer to the source node if found, otherwise return NULL   */
  /*-----------------------------------------------------------------------*/

  if (bFound)
  {
    *pnId = (SourceIdType)&pDrvCtxt->aSources[nSourceIndex];
    return DAL_SUCCESS;
  }
  else
  {
    return DAL_ERROR_NOT_FOUND;
  }

} /* END Clock_GetSourceId */


/* =========================================================================
**  Function : Clock_EnableSource
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnableSource
(
  ClockDrvCtxt *pDrvCtxt,
  SourceIdType  nSource
)
{
  ClockSourceNodeType *pSource = NULL;
  DALResult            eResult;

  /* Cast nSource to a proper pointer */
  pSource = (ClockSourceNodeType*)nSource;

  /* Make sure the source handle is valid */
  if (pSource == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*
   * Check if we should bypass the resource's dependencies and directly
   * configure the resource to the requested state at the HAL level.
   *
   * The clock driver provides this type of interface for resources whose
   * dependencies are implicitly met (XO, SVS voltage, etc.). In this case,
   * we bypass the DAL driver which ensures resource synchronization, and
   * initiates voltage updates.
   *
   * This is an optimization designed to avoid blocking on other threads
   * that are in the middle of these updates. The logic is that since the
   * current resource's requirements are already met, we can configure the
   * hardware directly and skip record keeping for this resource which
   * also requires grabbing the shared driver mutex.
   *
   * Note: clients must avoid making concurrent calls into the clock
   * driver DAL APIs for this resource, since the clock driver no
   * longer protects its state with a lock.
   */
  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
  DALCLOCK_LOCK(pDrvCtxt);
  }

  /*
   * If the external reference count is zero then we need to call the internal
   * enable source API.
   */
  if (pSource->nReferenceCountExternal == 0)
  {
    eResult = Clock_EnableSourceInternal(pDrvCtxt, pSource, FALSE);
    if (eResult != DAL_SUCCESS)
    {
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
      {
        DALCLOCK_FREE(pDrvCtxt);
      }
      return DAL_ERROR_INTERNAL;
    }
  }

  /* Increment the reference count */
  pSource->nReferenceCountExternal++;

  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_FREE(pDrvCtxt);
  }

  return DAL_SUCCESS;

} /* END Clock_EnableSource */


/* =========================================================================
**  Function : Clock_DisableSource
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_DisableSource
(
  ClockDrvCtxt *pDrvCtxt,
  SourceIdType  nSource
)
{
  ClockSourceNodeType  *pSource = NULL;
  DALResult             eResult;

  /* Cast nSource to a proper pointer */
  pSource = (ClockSourceNodeType*)nSource;

  /* Make sure the source handle is valid */
  if (pSource == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*
   * Check if we should bypass the DAL driver and directly configure the
   * resource to the requested state at the HAL level.
   *
   * The clock driver provides this type of interface for resources whose
   * dependencies are implicitly met (XO, SVS voltage, etc.). In this case,
   * we bypass the DAL driver which ensures resource synchronization, and
   * initiates voltage updates.
   *
   * This is an optimization designed to avoid blocking on other threads
   * that are in the middle of these updates. The logic is that since the
   * current resource's requirements are already met, we can configure the
   * hardware directly and skip record keeping for this resource which
   * also requires grabbing the shared driver mutex.
   *
   * Note: clients must avoid making concurrent calls into the clock
   * driver DAL APIs for this resource, since the clock driver no
   * longer protects its state with a lock.
   */
  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_LOCK(pDrvCtxt);
  }

  /*
   * If the external reference count is one then we need to call the internal
   * disable source API.
   */
  if (pSource->nReferenceCountExternal == 1)
  {
    eResult = Clock_DisableSourceInternal(pDrvCtxt, pSource, FALSE, FALSE);
    if (eResult != DAL_SUCCESS)
    {
      if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
      {
        DALCLOCK_FREE(pDrvCtxt);
      }
      return DAL_ERROR_INTERNAL;
    }
  }

  /* Decrement the reference count */
  if (pSource->nReferenceCountExternal > 0)
  {
    pSource->nReferenceCountExternal--;
  }

  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_FREE(pDrvCtxt);
  }

  return DAL_SUCCESS;

} /* END Clock_DisableSource */


/* =========================================================================
**  Function : Clock_SetSourceFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetSourceFrequency
(
  ClockDrvCtxt       *pDrvCtxt,
  SourceIdType        nSource,
  uint32              nFreq,
  ClockFrequencyType  eMatch,
  uint32             *pnResultFreq
)
{
  ClockSourceNodeType        *pSource;
  ClockSourceFreqConfigType  *pNewConfig = NULL;
  DALResult                   eResult;
  uint32                      nFreqHz;
  uint32                      nMult;
  uint32                      nResultFreq;

  /* Cast nSource to a proper pointer */
  pSource = (ClockSourceNodeType *)nSource;

  /* Initialize output parameter */
    if (pnResultFreq != NULL)
    {
      *pnResultFreq = 0;
    }

  /* Make sure the source handle is valid and supports frequency configuration. */
  if (pSource == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /* Convert to Hz if necessary. */
  if (eMatch >= CLOCK_FREQUENCY_MHZ_AT_LEAST)
  {
    nMult = 1000000;
    nFreqHz = nFreq * 1000000;
    eMatch -= CLOCK_FREQUENCY_MHZ_AT_LEAST;
  }
  else if (eMatch >= CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    nMult = 1000;
    nFreqHz = nFreq * 1000;
    eMatch -= CLOCK_FREQUENCY_KHZ_AT_LEAST;
  }
  else
  {
    nMult = 1;
    nFreqHz = nFreq;
  }

  /* Look for a valid configuration */
  eResult =
    Clock_FindSourceConfig(
      pSource->pBSPConfig->pSourceFreqConfig,
      nFreqHz,
      eMatch,
      &pNewConfig);

  if ((eResult != DAL_SUCCESS) || (pNewConfig == NULL))
  {
    return DAL_ERROR_NOT_SUPPORTED;
  }

  /*
   * Check if we should bypass the resource's dependencies and directly
   * configure the resource to the requested state at the HAL level.
   *
   * The clock driver provides this type of interface for resources whose
   * dependencies are implicitly met (XO, SVS voltage, etc.). In this case,
   * we bypass the DAL driver which ensures resource synchronization, and
   * initiates voltage updates.
   *
   * This is an optimization designed to avoid blocking on other threads
   * that are in the middle of these updates. The logic is that since the
   * current resource's requirements are already met, we can configure the
   * hardware directly and skip record keeping for this resource which
   * also requires grabbing the shared driver mutex.
   *
   * Note: clients must avoid making concurrent calls into the clock
   * driver DAL APIs for this resource, since the clock driver no
   * longer protects its state with a lock.
   */
  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_LOCK(pDrvCtxt);
  }

  /* If the new config is the same as the active config, we're done */
  nResultFreq = 0;
  if (pNewConfig != pSource->pActiveFreqConfig)
  {
    eResult = Clock_ConfigSource(pDrvCtxt, pSource, pNewConfig);

    if (eResult == DAL_SUCCESS)
    {
      nResultFreq = pNewConfig->nFreqHz / nMult;

      if (CLOCK_FLAG_IS_SET(pSource, LOG_FREQ_CHANGE) ||
          CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
      {
        ULOG_RT_PRINTF_2 (pDrvCtxt->hClockLog,
                          "%s (Freq: %lu)",
                          pSource->szName, pNewConfig->nFreqHz);
      }

      /*
       * Only send out SW event when successful.
       */
      #ifdef WIN8EA
      if (pDrvCtxt->bQdssEnabled)
      {
        PEP_CLK_TRACE_SOURCE_FREQ(
          pSource->eSource,
          nResultFreq * nMult);
      }
      #else
        QDSS_SWEVENT(CLOCK_EVENT_SOURCE_FREQ,pSource->eSource,nResultFreq * nMult);
      #endif
    }
    else
    {
      eResult = DAL_ERROR_INTERNAL;
    }
  }
  else
  {
    nResultFreq = pSource->pActiveFreqConfig->nFreqHz;
  }

  if (pnResultFreq != NULL)
  {
    *pnResultFreq = nResultFreq;
  }

  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_FREE(pDrvCtxt);
  }

  return eResult;

} /* END Clock_SetSourceFrequency */


/* =========================================================================
**  Function : Clock_GetSourceFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_GetSourceFrequency
(
  ClockDrvCtxt *pDrvCtxt,
  SourceIdType  nSource,
  uint32       *pnFrequencyHz
)
{
  ClockSourceNodeType *pSource = (ClockSourceNodeType *)nSource;
  HAL_clk_PLLConfigType HALConfigDetected;
  ClockSourceFreqConfigType *pSourceFreqConfig;
  uint32 nFreqHz = 0;

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pSource == NULL || pnFrequencyHz == NULL)
  {
    return DAL_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the output parameter.                                      */
  /*-----------------------------------------------------------------------*/

    *pnFrequencyHz = 0;

  /*-----------------------------------------------------------------------*/
  /* Get state from current config either local copy or read from HW.      */
  /*-----------------------------------------------------------------------*/

  /*
   * Check if we should bypass the resource's dependencies and directly
   * configure the resource to the requested state at the HAL level.
   *
   * The clock driver provides this type of interface for resources whose
   * dependencies are implicitly met (XO, SVS voltage, etc.). In this case,
   * we bypass the DAL driver which ensures resource synchronization, and
   * initiates voltage updates.
   *
   * This is an optimization designed to avoid blocking on other threads
   * that are in the middle of these updates. The logic is that since the
   * current resource's requirements are already met, we can configure the
   * hardware directly and skip record keeping for this resource which
   * also requires grabbing the shared driver mutex.
   *
   * Note: clients must avoid making concurrent calls into the clock
   * driver DAL APIs for this resource, since the clock driver no
   * longer protects its state with a lock.
   */
  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_LOCK(pDrvCtxt);
  }

  if (pSource->pActiveFreqConfig != NULL)
  {
    nFreqHz = pSource->pActiveFreqConfig->nFreqHz;
  }
  else
  {
    HAL_clk_DetectPLLConfig(pSource->eSource, &HALConfigDetected);

    /*
     * Here we loop over supported BSP configs and if found use
     * the frequency there.
     */
    pSourceFreqConfig = pSource->pBSPConfig->pSourceFreqConfig;
    while (pSourceFreqConfig->nFreqHz != 0)
    {
      if (pSourceFreqConfig->HALConfig.nL == HALConfigDetected.nL &&
          pSourceFreqConfig->HALConfig.nM == HALConfigDetected.nM &&
          pSourceFreqConfig->HALConfig.nN == HALConfigDetected.nN &&
          pSourceFreqConfig->HALConfig.nPreDiv == HALConfigDetected.nPreDiv &&
          pSourceFreqConfig->HALConfig.nPostDiv == HALConfigDetected.nPostDiv)
      {
        nFreqHz = pSourceFreqConfig->nFreqHz;
        break;
      }

      /*
       * Go to the next source frequency config.
       */
      pSourceFreqConfig++;
    }
  }

  if (!CLOCK_FLAG_IS_SET(pSource, BYPASS_DEPENDENCIES))
  {
    DALCLOCK_FREE(pDrvCtxt);
  }

  *pnFrequencyHz = nFreqHz;

  return DAL_SUCCESS;

} /* END Clock_GetSourceFrequency */


/*=========================================================================
**  Function : Clock_IsBSPSupported
** =========================================================================*/
/**
 *
  See ClockDriver.h
*/

boolean Clock_IsBSPSupported
(
  ClockHWVersionType *pHWVersion
)
{
  uint32                   nHWVersion, nHWMaxVersion, nHWMinVersion;
  DalChipInfoIdType        eChipId;
  const DalChipInfoIdType *aeChipInfoId;

  /*-----------------------------------------------------------------------*/
  /* Validate argument pointer is usable.                                  */
  /*-----------------------------------------------------------------------*/

  if (pHWVersion == NULL)
  {
    return FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate chip family. If not provided then we do not check.           */
  /*-----------------------------------------------------------------------*/

  if ( (pHWVersion->eChipInfoFamily != 0) &&
       (pHWVersion->eChipInfoFamily != DalChipInfo_ChipFamily()) )
  {
    return FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Ensure the specific chip ID is supported.                             */
  /*-----------------------------------------------------------------------*/

  aeChipInfoId = pHWVersion->aeChipInfoId;

  if (aeChipInfoId != NULL)
  {
    eChipId = DalChipInfo_ChipId();

    while (*aeChipInfoId < DALCHIPINFO_NUM_IDS)
    {
      if (eChipId == *aeChipInfoId)
      {
        break;
      }

      aeChipInfoId++;
    }

    if (*aeChipInfoId == DALCHIPINFO_NUM_IDS)
    {
      return FALSE;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get the actual hardware revision.                                     */
  /*-----------------------------------------------------------------------*/

  nHWVersion = HAL_clk_GetChipVersion();

  nHWMinVersion =
    DALCHIPINFO_VERSION(pHWVersion->Min.nMajor, pHWVersion->Min.nMinor);
  nHWMaxVersion =
    DALCHIPINFO_VERSION(pHWVersion->Max.nMajor, pHWVersion->Max.nMinor);

  /*-----------------------------------------------------------------------*/
  /* No chip version data implies support in all HW versions.              */
  /*-----------------------------------------------------------------------*/

  if ( (nHWMinVersion == 0) && (nHWMaxVersion == 0) )
  {
    return TRUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate the HW version falls within the min/max.                     */
  /*-----------------------------------------------------------------------*/

  if ( (nHWVersion >= nHWMinVersion) && (nHWVersion < nHWMaxVersion) )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


/* =========================================================================
**  Function : Clock_GetClockDebugId
** =========================================================================*/
/**
  Looks up a clock Debug ID for a specified clock.

  This function takes the ID of a clock and returns the corresponding Debug ID.

  @param pDrvCtxt  [in]  Pointer to the clock driver context.
  @param nClock    [in]  ID of the clock.
  @param pnDebugId [out] Pointer to the clock Debug ID to be filled in.

  @return
  DAL_SUCCESS -- Clock was found and the Debug ID was filled in.\n
  DAL_ERROR -- Clock was not found on this target, or the Debug ID is 0,
               i.e., undefined.

  @dependencies
  None.

  @sa
  Clock_GetClockId
*/

DALResult Clock_GetClockDebugId
(
  ClockDrvCtxt  *pDrvCtxt,
  ClockIdType    nClock,
  uint32        *pnDebugId
)
{
  ClockNodeType *pClock = NULL;

  /* Cast nClock to a proper pointer */
  pClock = (ClockNodeType*)nClock;

  /*-----------------------------------------------------------------------*/
  /* Sanity checks.                                                        */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt == NULL ||
      pClock == NULL ||
      pnDebugId == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Find the Debug ID to return.                                          */
  /*-----------------------------------------------------------------------*/

  *pnDebugId = ((HAL_clk_ClockDescType *)pClock->HALHandle)->nTestClock;

  /*-----------------------------------------------------------------------*/
  /* Validate the Debug ID before returning.                               */
  /*-----------------------------------------------------------------------*/

  if (*pnDebugId == 0)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : Clock_CheckNameList
** =========================================================================*/
/**
  Check the given clock name against the clock names in the given
  clock name list.

  Returns true if the given clock name is present in the given clock name
  list.

  @param *szListName [in] -- Name of the clock name list to check.
  @param *szClockName [in] -- Name of the clock name to check.

  @return
  TRUE -- The clock name was found in the list.
  FALSE -- The clock name is not in the list.

  @dependencies
  None.
*/

static boolean Clock_CheckNameList
(
  const char  *szListName,
  const char  *szClockName
)
{
  DALResult               eResult;
  ClockPropertyValueType  PropVal;
  ClockNameListType      *ClockNameList;
  uint32                  nIndex;

  if (szClockName == NULL || szListName == NULL)
  {
    return FALSE;
  }

  eResult = Clock_GetPropertyValue(szListName, &PropVal);

  if (eResult == DAL_SUCCESS)
  {
    ClockNameList = (ClockNameListType *)PropVal;
  }
  else
  {
    return FALSE;
  }

  for (nIndex = 0; ClockNameList[nIndex].szName != NULL; nIndex++)
  {
    if (strcmp(ClockNameList[nIndex].szName, szClockName) == 0)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END Clock_CheckNameList */


/* =========================================================================
**  Function : Clock_AssignNPAState
** =========================================================================*/
/**
  See ClockDriver.h
*/

npa_resource_state Clock_AssignNPAState
(
  npa_resource_definition *pResource,
  npa_resource_state       nRequest
)
{
  npa_resource *hResource = pResource->handle;
  npa_resource_state nActiveState;

  npa_resource_lock(hResource);
  nActiveState = hResource->node->driver_fcn(hResource, NULL, nRequest);
  npa_assign_resource_state(hResource, nActiveState);
  npa_resource_unlock(hResource);

  return nActiveState;
}


/* =========================================================================
**  Function : Clock_RegisterLMCallbacks
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_RegisterLMCallbacks
(
  ClockDrvCtxt         *pDrvCtxt,
  LM_CpuUpdateFuncPtr   fpCpuUpdate,
  LM_GpuUpdateFuncPtr   fpGpuUpdate
)
{
  /*-----------------------------------------------------------------------*/
  /* Install Limits Management callback functions.                         */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->fpCpuUpdate = fpCpuUpdate;
  pDrvCtxt->fpGpuUpdate = fpGpuUpdate;

  return DAL_SUCCESS;

} /* END Clock_RegisterLMCallbacks */

