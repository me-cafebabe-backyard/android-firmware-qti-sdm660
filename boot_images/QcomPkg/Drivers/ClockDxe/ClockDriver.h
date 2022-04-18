#ifndef __CLOCKDRIVER_H__
#define __CLOCKDRIVER_H__
/*
===========================================================================
*/
/**
  @file ClockDriver.h

  Internal header file for the clock device driver.
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

#include "com_dtypes.h"
#include "DALSys.h"
#ifdef CLOCK_ULOG_STUB
  #include "ClockULogStub.h"
#else
  #include "ULogFront.h"
#endif
#include "Include/api/systemdrivers/ClockDefs.h"
#include "ClockBSP.h"
#ifdef CLOCK_NPA_STUB
#include "ClockNPAStub.h"
#else
  #include "npa.h"
  #include "npa_resource.h"
#endif


/*=========================================================================
      Warnings to ignore
==========================================================================*/

#if !defined(__GNUC__) && !defined(_MSC_VER)
#pragma diag_suppress 188
#endif


/*=========================================================================
      Macro Definitions
==========================================================================*/

/**
 * Define __weak for non-rvct compilers.
 */
#ifdef __GNUC__
  #ifdef UEFI64
    #define __weak
  #else
  #define __weak __attribute__((weak))
  #endif
#elif !defined(__ARMCC_VERSION)
  #define __weak
#endif


/**
 * Macro lock the driver mutex.
 */
#define DALCLOCK_LOCK(drvCtxt) (drvCtxt->hLock) ? DALSYS_SyncEnter(drvCtxt->hLock) : (void)drvCtxt->hLock


/**
 * Macro try-lock the driver mutex.
 */
#define DALCLOCK_TRYLOCK(drvCtxt) (drvCtxt->hLock) ? DALSYS_SyncTryEnter(drvCtxt->hLock) : DAL_SUCCESS


/**
 * Macro to free the driver mutex.
 */
#define DALCLOCK_FREE(drvCtxt) (drvCtxt->hLock) ? DALSYS_SyncLeave(drvCtxt->hLock) : (void)drvCtxt->hLock


/**
 * Convert an NPA state to a frequency in Hz.
 */
#define NPA_TO_HZ(state) \
  (uint32)((state) == NPA_MAX_STATE ? (state) : (state) * 1000)


/**
 * Return the number of elements in an array.
 */
#define SIZEOF_ARRAY(p) (sizeof(p) / sizeof(p[0]))


/*
 * Macros for checking, setting and clearing the unified flag bits in the
 * driver nodes.  Note these work on any structure containing an "nFlags"
 * field.
 */
#define CLOCK_FLAG_IS_SET(ptr, flag) (((ptr)->nFlags & CLOCK_FLAG_##flag) ? TRUE : FALSE)
#define CLOCK_FLAG_SET(ptr, flag)    ((ptr)->nFlags |= CLOCK_FLAG_##flag)
#define CLOCK_FLAG_CLEAR(ptr, flag)  ((ptr)->nFlags &= ~CLOCK_FLAG_##flag)


/*
 * Macros for checking, setting and clearing the global flag bits in the
 * driver context.  Note these work only on the "nGlobalFlags" field
 * within the driver context structure.
 */
#define CLOCK_GLOBAL_FLAG_IS_SET(flag) ((pDrvCtxt->nGlobalFlags & CLOCK_GLOBAL_FLAG_##flag) ? TRUE : FALSE)
#define CLOCK_GLOBAL_FLAG_SET(flag)    (pDrvCtxt->nGlobalFlags |= CLOCK_GLOBAL_FLAG_##flag)
#define CLOCK_GLOBAL_FLAG_CLEAR(flag)  (pDrvCtxt->nGlobalFlags &= ~CLOCK_GLOBAL_FLAG_##flag)


/*
 * Values used for making NPA requests on clock sources.
 *  0: XO is not required at all.
 *  1: XO is always required.
 */
#define CLOCK_SOURCE_NOT_REQUIRED     0
#define CLOCK_SOURCE_REQUIRED         1


/*
 * Default size of the BIST ULOG log buffer.
 *
 * NOTE: The log size should be specified in powers of 2.
 */
#define CLOCK_BIST_DEFAULT_LOG_SIZE   0x200000

/*
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define CLOCK_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF

/*
 * MAX and MIN macros.
 */
#ifndef MAX
  #define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef MIN
  #define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif


/*=========================================================================
      Type Definitions
==========================================================================*/


/**
 * Clock voltage regular configuration type.
 */
typedef struct ClockVRegConfigType
{
  uint32                         nClientCount[CLOCK_VREG_NUM_LEVELS]; /**< Number of active clients */
  ClockVRegLevelType             eMinLevel;                           /**< Minimum vreg level */
  ClockVRegLevelType             eInitLevel;                          /**< Initial vreg level */
  npa_client_handle              NPAHandle;                           /**< NPA client handle */
} ClockVRegConfigType;


/**
 * Clock voltage request type.
 */
typedef struct ClockVRegRequestType
{
  ClockVRegLevelType eVRegLevel;
  boolean            bSuppressible;
} ClockVRegRequestType;


/**
 * Clock source type.
 */
typedef struct ClockSourceNodeType ClockSourceNodeType;
struct ClockSourceNodeType
{
  HAL_clk_SourceType             eSource;                     /**< Source enum value. */
  const char                    *szName;                      /**< Source name string */
  ClockSourceConfigType         *pBSPConfig;                  /**< Pointer to BSP data */
  npa_client_handle              NPAHandle;                   /**< NPA client handle */
  ClockSourceFreqConfigType     *pActiveFreqConfig;           /**< Pointer to active config */
  uint32                         nReferenceCount;             /**< Number of active non-CPU domains */
  uint32                         nReferenceCountSuppressible; /**< Number of active suppressible domains */
  uint32                         nReferenceCountExternal;     /**< Number of active external enable requests */
  ClockVRegRequestType           VRegRequest;                 /**< Voltage request */
  uint32                         nFlags;                      /**< Flags for the source */
  uint32                         nCalibration;                /**< Source calibration data */
  ClockSourceNodeType           *pSource;                     /**< Pointer to source's source node */
};


/**
 * Clock domain type.
 */
typedef struct
{
  ClockMuxConfigType            *pBSPConfig;                  /**< Pointer to BSP data */
  HAL_clk_ClockDomainHandleType  HALHandle;                   /**< Handle to HAL data */
  ClockMuxConfigType            *pActiveMuxConfig;            /**< Pointer to active config */
  uint32                         nReferenceCount;             /**< Number of active clocks */
  uint32                         nReferenceCountSuppressible; /**< Number of active suppressible domains */
  ClockVRegRequestType           VRegRequest;                 /**< Voltage request */
  uint32                         nFlags;                      /**< Flags for the domain */
  ClockSourceNodeType           *pSource;                     /**< Pointer to source node */
} ClockDomainNodeType;


/**
 * Clock type.
 */
typedef struct
{
  const char                    *szName;              /**< Clock name string */
  HAL_clk_ClockHandleType        HALHandle;           /**< Handle to HAL data */
  uint32                         nReferenceCount;     /**< Number of active client requests */
  uint32                         nFlags;              /**< Flags for the clock */
  ClockDomainNodeType           *pDomain;             /**< Pointer to domain node */
} ClockNodeType;


/**
 * Power domain type.
 */
typedef struct
{
  const char                    *szName;              /**< Power domain name string */
  HAL_clk_PowerDomainHandleType  HALHandle;           /**< Handle to HAL data */
  uint32                         nReferenceCount;     /**< Number of active client requests */
  boolean                        bEnabled;            /**< Enabled flag */
  uint32                         nReferenceCountHW;   /**< Number of active client requests */
  boolean                        bEnabledHW;          /**< Enabled HW Control flag */
  uint32                         nFlags;              /**< Flags for the power domain */
} ClockPowerDomainNodeType;


/**
 * Clock driver context.
 */
typedef struct
{
  DALSYSSyncObj                  LockObj;                               /**< Sync object storage */
  DALSYSSyncHandle               hLock;                                 /**< Handle to our mutex */

  ULogHandle                     hClockLog;                             /**< Handle to our ULOG log */
  uint32                         nGlobalFlags;                          /**< Global flags for the driver */

  ULogHandle                     hClockBISTLog;                         /**< Handle to our BIST ULOG log */
  boolean                        bBISTEnabled;                          /**< Flag used to enable the BIST */
  uint32                         nBISTLogSize;                          /**< Size of the BIST ULOG log */
  ClockNameListType             *pBISTExceptions;                       /**< Pointer to the BIST Exceptions List */

  ULogHandle                     hClockDebugLog;                        /**< Handle to our Debug ULOG log */

  boolean                        bDCVSEnabled;                          /**< DCVS state */
  boolean                        bCPREnabled;                           /**< CPR state */
  void                          *pImageCtxt;                            /**< Image context */

  uint8                          anSourceIndex[HAL_CLK_NUM_OF_SOURCES]; /**< Array of source indices */
  uint32                         nNumSources;                           /**< Number of supported sources */
  ClockSourceNodeType           *aSources;                              /**< Array of supported sources */
  uint32                         nNumClockDomains;                      /**< Number of supported clock domains */
  ClockDomainNodeType           *aClockDomains;                         /**< Array of supported clock domains */
  uint32                         nNumClocks;                            /**< Number of supported clocks */
  ClockNodeType                 *aClocks;                               /**< Array of supported clocks */
  uint32                         nNumPowerDomains;                      /**< Number of supported power domains */
  ClockPowerDomainNodeType      *aPowerDomains;                         /**< Array of supported power domains */
  ClockVRegConfigType            VRegConfig;                            /**< Voltage configuration */
  ClockVRegConfigType            VRegConfigSuppressible;                /**< Suppressible voltage configuration */
  boolean                        bSuspendVoltageRequest;                /**< Voltage suspension state */
  boolean                        bQdssEnabled;                          /**< QDSS enabled status */

  LM_CpuUpdateFuncPtr            fpCpuUpdate;                           /**< LM CPU CX Voltage Corner Update callback function */
  LM_GpuUpdateFuncPtr            fpGpuUpdate;                           /**< LM GPU CX Voltage Corner Update callback function */
  uint32                         nGlobalPlatformInfo;                   /**< Global Platform info for the driver */

} ClockDrvCtxt;


/*=========================================================================
      Function Definitions
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
  DAL_SUCCESS -- Init was successful.
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
);


/* =========================================================================
**  Function : Clock_DriverDeInit
** =========================================================================*/
/**
  De-initialize the clock driver.

  This function shuts-down the clock driver.  It is not expected to ever
  be called.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_DriverDeInit
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_InitCore
** =========================================================================*/
/**
  Initialize the core portion of the clock driver.

  This function initializes the common portion of the clock driver that is
  shared with all images.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitCore
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/**
  Initialize the image specific portion of the clock driver.

  This function initializes the portion of the clock driver that is specific
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

DALResult Clock_InitImage
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_InitDCVS
** =========================================================================*/
/**
  Initialize the NPA DCVS nodes for this image in the clock driver.

  This function initializes the DCVS module for the current image.  This
  will define and create the required NPA nodes.  Nodes will be be
  active until DalClock_EnableDCVS has been called.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Init was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitDCVS
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_TestClock
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on the specified clock node
  in the driver.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param ClockId [in] -- Clock ID of the clock to be tested.

  @return
  DAL_SUCCESS -- BIST was successful.
  DAL_ERROR -- BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the test.
*/

DALResult Clock_TestClock
(
  ClockDrvCtxt *pDrvCtxt,
  ClockIdType   ClockId
);


/* =========================================================================
**  Function : Clock_InitBISTLog
** =========================================================================*/
/**
  Initializes the BIST log.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- BIST log initialization was successful.
  DAL_ERROR -- BIST log initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitBISTLog
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_BIST
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on all clock nodes in the
  driver.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- BIST was successful.
  DAL_ERROR -- BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the BIST.
*/

DALResult Clock_BIST
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_ImageBIST
** =========================================================================*/
/**
  Perform a non-destructive built-in self test on the image specific portion
  of the clock driver.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *bBISTPassed [in/out] -- Pointer to the main BIST passed boolean.
  @param *nFailedTests [in/out] -- Pointer to the main BIST value which stores
                                   number of failed tests.

  @return
  DAL_SUCCESS -- Image BIST was successful.
  DAL_ERROR -- Image BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the Image BIST.
*/

static DALResult Clock_ImageBIST
(
  ClockDrvCtxt  *pDrvCtxt,
  boolean       *bBISTPassed,
  uint32        *nFailedTests
);


/* =========================================================================
**  Function : Clock_SetClockConfig
** =========================================================================*/
/**
  Sets a clock configuration.

  This function configures a clock domain to a particular configuration.
  It is used internally only.

  @param *pDrvCtxt [in] -- Driver context.
  @param *pClockDomain [in] -- Clock domain to configure.
  @param *pNewConfig [in] -- New configuration to use.

  @return
  DAL_SUCCESS -- The domain was successfully configured.
  DAL_ERROR -- The domain configuration failed.

  @dependencies
  The clock mutex must be locked.
*/

DALResult Clock_SetClockConfig
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockDomainNodeType *pDomain,
  ClockMuxConfigType  *pNewConfig
);


/* =========================================================================
**  Function : Clock_InitSources
** =========================================================================*/
/**
  Initialize clock sources.

  This function allocates memory for the clock source nodes and initializes
  them based on the BSP/XML data.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Initialization was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitSources
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_EnableSourceInternal
** =========================================================================*/
/**
  Requests to enable a source.

  This function enables a source, generally as a result of a call to
  Clock_EnableClockDomain().  CPU based source requests are tracked
  independently of non-CPU based as the former will be automatically
  released when the CPU goes to sleep.
  A reference count is maintained so callers must ensure that all Enables
  and Disables are matched.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pSource [in] -- Pointer to a source node.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.

  @return
  DAL_SUCCESS -- The source was successfully enabled.
  DAL_ERROR -- The source was not enabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

DALResult Clock_EnableSourceInternal
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  boolean              bSuppressibleRequest
);


/* =========================================================================
**  Function : Clock_DisableSourceInternal
** =========================================================================*/
/**
  Disables a source.

  This function disables a source, generally as a result of a call to
  Clock_DisableClockDomain().
  A reference count is maintained so callers must ensure that all Enables
  and Disables are matched.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pSource [in] -- Pointer to a source node.
  @param bSuppressibleRequest [in] -- TRUE if this is a source request is for a suppressible clock.
  @param  bDoNotDisable [in]        -- TRUE if this is a source request that should not disable the source.

  @return
  DAL_SUCCESS -- The source was successfully disabled.
  DAL_ERROR -- The source was not disabled.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

DALResult Clock_DisableSourceInternal
(
  ClockDrvCtxt        *pDrvCtxt,
  ClockSourceNodeType *pSource,
  boolean              bSuppressibleRequest,
  boolean              bDoNotDisable
);


/* =========================================================================
**  Function : Clock_FindSourceConfig
** =========================================================================*/
/**
  Finds a particular source configuration in the BSP.

  This function finds a particular source configuration in the BSP based on
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
DALResult Clock_FindSourceConfig
(
  ClockSourceFreqConfigType   *pBSPConfig,
  uint32                       nFreqHz,
  ClockFrequencyType           eMatch,
  ClockSourceFreqConfigType  **pMatchingConfig
);


/* =========================================================================
**  Function : Clock_FindSourceConfigByVersion
** =========================================================================*/
/**
  Finds a particular source configuration in the BSP based on the chip
  version number.

  This function finds a particular source configuration in the BSP based on
  the chip version number.

  @param *pBSPConfig [in] -- Pointer to a list of configurations
  @param **pMatchingConfig [out] -- Matching configuration

  @return
  DAL_SUCCESS -- A matching configuration was found.
  DAL_ERROR -- A matching configuration was not found.

  @dependencies
  None.
*/
DALResult Clock_FindSourceConfigByVersion
(
  ClockSourceFreqConfigType   *pBSPConfig,
  ClockSourceFreqConfigType  **pMatchingConfig
);


/* =========================================================================
**  Function : Clock_ConfigSource
** =========================================================================*/
/**
  Configures a source.

  This function configures a source, generally a PLL.  This can only be
  done if there are no users of the source and we own the PLL.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pSource [in] -- Pointer to a source node.
  @param *pConfig [in] -- New configuration.

  @return
  DAL_SUCCESS -- The source was successfully configures.
  DAL_ERROR -- The source was not configured, either due to invalid
               parameter or (more likely) the source was in use.

  @dependencies
  The clock mutex must be locked prior to calling this function.
*/

DALResult Clock_ConfigSource
(
  ClockDrvCtxt               *pDrvCtxt,
  ClockSourceNodeType        *pSource,
  ClockSourceFreqConfigType  *pConfig
);


/* =========================================================================
**  Function : Clock_InitSource
** =========================================================================*/
/**
  Configures a source.

  This function initializes a source, generally a PLL, from the current BSP
  data.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param eSource [in] -- Which source to initialize.
  @param  nFreqHz  [in] -- Optional frequency to init this source to.
                           The first source frequency config is used if
                           this argument is 0.

  @return
  DAL_SUCCESS -- The source was successfully initialized.
  DAL_ERROR -- The source was not initialized, generally because the source
               has no valid BSP data.

  @dependencies
  The clock mutex should be locked prior to calling this function or
  we should be a single execution thread environment (like boot).
*/

DALResult Clock_InitSource
(
  ClockDrvCtxt               *pDrvCtxt,
  HAL_clk_SourceType          eSource,
  uint32              nFreqHz
);


/* =========================================================================
**  Function : Clock_GetPropertyValue
** =========================================================================*/
/**
  Retrieve a clock driver property from the environment store.

  This function retrieves the given clock property from the relevant
  storage location (may be DAL properties DB or another source).

  @param *szName [in] -- Name of the property to look up
  @param *pValue [out] -- Location to store the result

  @return
  DAL_SUCCESS if property was found and retrieved, DAL_ERROR otherwise.

  @dependencies
  None.
*/

DALResult Clock_GetPropertyValue
(
  const char              *szName,
  ClockPropertyValueType  *pValue
);


/* =========================================================================
**  Function : Clock_MapHWIORegion
** =========================================================================*/
/**
  Map a HWIO region into memory for the clock driver.

  This function maps a physical HWIO region into memory for the clock driver
  using environment appropriate APIs.  If the mapping is not available
  the virtual address will be set to the provided physical address.

  @param nPhysAddr [in] -- Physical address.
  @param nSizeBytes [in] -- Size of the region in bytes.
  @param *pnVirtAddr [out] -- Location to store the mapped address.

  @return
  DAL_SUCCESS if mapping was ok, otherwise error code based on failure.

  @dependencies
  None.
*/

DALResult Clock_MapHWIORegion
(
  size_t  nPhysAddr,
  uint32  nSizeBytes,
  size_t *pnVirtAddr
);


/* =========================================================================
**  Function : Clock_InitVoltage
** =========================================================================*/
/**
  Initialize voltage tracking subsystem.

  This function prepares the voltage tracking module for managing voltage
  requests.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Initialization was successful.
  DAL_ERROR -- Initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitVoltage
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_VoltageRequest
** =========================================================================*/
/**
  Make a voltage regulator request.

  This function is used internally for a clock domain to make a voltage
  regulator level request.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pCurrentRequest [in/out] -- Pointer to currently requested voltage config.
                                      Updated to pNewRequest.
  @param *pNewRequest [in] -- New voltage requirement.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

DALResult Clock_VoltageRequest
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockVRegRequestType  *pCurrentRequest,
  ClockVRegRequestType  *pNewRequest
);


/* =========================================================================
**  Function : Clock_VoltageSuspend
** =========================================================================*/
/**
  Make a request to suspend voltage requests.

  This function is used internally to suspend voltage requests.

  @param *pDrvCtxt [in]       -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR   -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

DALResult Clock_VoltageSuspend
(
  ClockDrvCtxt  *pDrvCtxt
);


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
);


/* =========================================================================
**  Function : Clock_VoltageResume
** =========================================================================*/
/**
  Make a request to resume voltage requests.

  This function is used internally to resume voltage requests.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param bUpdate [in] -- Flag to update voltage request immediately upon resume.

  @return
  DAL_SUCCESS -- Request was successful.
  DAL_ERROR   -- Request failed.

  @dependencies
  The clock mutex must be locked.
*/

DALResult Clock_VoltageResume
(
  ClockDrvCtxt  *pDrvCtxt,
  boolean        bUpdate
);


/*=========================================================================
**  Function : Clock_IsBSPSupported
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

boolean Clock_IsBSPSupported
(
  ClockHWVersionType *pHWVersion
);


/*=========================================================================
**  Function : Clock_AssignNPAState
** =========================================================================*/
/**
  Invoke an NPA driver function and assign the resource state.

  This function calls an NPA node driver function with nRequest, and
  assigns the resource state to the return value. This function bypasses
  the NPA aggregation layer and can be used to override the current request
  state of a node.

  @param *pResource [in] -- Pointer to NPA resource to assign.
  @param nRequest [in] -- New request state.

  @return
  npa_resource_state -- Active state of the resource.

  @dependencies
  The NPA node pointed to by pResource must have already been created.
*/

npa_resource_state Clock_AssignNPAState
(
  npa_resource_definition *pResource,
  npa_resource_state       nRequest
);


/*=========================================================================
**  Function : Clock_NormalizeChipInfo
** =========================================================================*/
/**

  This is an optional function used to normalize ChipInfo when the official
  chip info data makes no sense due to marketing considerations.

  @param HALClkCtxt [in/out] - Pointer to HAL context containing the official
                               Chip Info data

  @return
  None.

  @dependencies
  None.
*/

void Clock_NormalizeChipInfo
(
  HAL_clk_ContextType *HALClkCtxt
);


/*=========================================================================
      Function Definitions From DDIClock.h
==========================================================================*/

DALResult Clock_GetClockId( ClockDrvCtxt *pDrvCtxt,  const char * szClock,  ClockIdType * pnId);
DALResult Clock_EnableClock( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock);
DALResult Clock_DisableClock( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock);
DALResult Clock_SetClockFrequency( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq );
DALResult Clock_SetExternalSourceDiv( ClockDrvCtxt *pDrvCtxt,  const char * szClock,  uint32  nDivider);
DALResult Clock_SetClockDivider( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  uint32  nDivider);
DALResult Clock_InvertClock( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  boolean  bInvert);
DALResult Clock_ResetClock( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  ClockResetType  eReset);
DALResult Clock_ConfigClock(ClockDrvCtxt *pDrvCtxt, ClockIdType nClock, ClockConfigType eConfig);
DALResult Clock_IsClockEnabled( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  boolean * pbIsOn);
DALResult Clock_IsClockOn( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  boolean * pbIsOn);
DALResult Clock_GetClockFrequency( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  uint32 * pnFrequencyHz);
DALResult Clock_IsClockXOVote( ClockDrvCtxt *pDrvCtxt, ClockIdType nClock, boolean bCurrently, boolean * pbIsXOVote);
DALResult Clock_SelectExternalSource( ClockDrvCtxt *pDrvCtxt, ClockIdType nClock, uint32 nFreqHz, uint32 nSource, uint32 nDiv2x, uint32 nM, uint32 nN, uint32 n2D);
DALResult Clock_CalcClockFrequency( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  uint32 * pnFrequencyHz);
DALResult Clock_SetUARTBaudClock( ClockDrvCtxt *pDrvCtxt,  ClockIdType  nClock,  uint32 nDI, uint32 nFI, uint32 *pnResultFreq );
DALResult Clock_LogState ( ClockDrvCtxt *pDrvCtxt, ULogHandle hULog, uint32 nFlags );

DALResult Clock_GetSourceId( ClockDrvCtxt *pDrvCtxt,  const char * szSource,  SourceIdType * pnId);
DALResult Clock_EnableSource( ClockDrvCtxt *pDrvCtxt,  SourceIdType  nSource);
DALResult Clock_DisableSource( ClockDrvCtxt *pDrvCtxt,  SourceIdType  nSource);
DALResult Clock_SetSourceFrequency( ClockDrvCtxt *pDrvCtxt,  SourceIdType  nSource,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq );
DALResult Clock_GetSourceFrequency( ClockDrvCtxt *pDrvCtxt,  SourceIdType  nSource,  uint32 * pnFrequencyHz);

DALResult Clock_GetPowerDomainId( ClockDrvCtxt *pDrvCtxt,  const char * szPowerDomain,  ClockPowerDomainIdType * pnPowerDomainId);
DALResult Clock_EnablePowerDomain( ClockDrvCtxt *pDrvCtxt,  ClockPowerDomainIdType  nPowerDomainId);
DALResult Clock_DisablePowerDomain( ClockDrvCtxt *pDrvCtxt,  ClockPowerDomainIdType  nPowerDomainId);

DALResult Clock_GetClockDebugId( ClockDrvCtxt *pDrvCtxt, ClockIdType nClock, uint32 * pnDebugId );

DALResult __weak Clock_EnableAVS( ClockDrvCtxt *pDrvCtxt);
void      __weak Clock_NormalizeChipInfo ( HAL_clk_ContextType *HALClkCtxt );
DALResult Clock_EnterLowPowerMode( ClockDrvCtxt *pDrvCtxt);
DALResult Clock_ExitLowPowerMode( ClockDrvCtxt *pDrvCtxt);
DALResult Clock_GetCpuFrequencyHz( ClockDrvCtxt *pDrvCtxt, uint32 *pfrequencyHz);

/*=========================================================================
      Stubbed out functions
==========================================================================*/

static inline DALResult Clock_EnableDCVS( ClockDrvCtxt *pDrvCtxt){return DAL_SUCCESS;}
static inline DALResult Clock_LoadNV( ClockDrvCtxt *pDrvCtxt){return DAL_SUCCESS;}
static inline DALResult Clock_ProcessorSleep( ClockDrvCtxt *pDrvCtxt,  ClockSleepModeType  eMode,  uint32  nFlags){return DAL_SUCCESS;}
static inline DALResult Clock_ProcessorRestore( ClockDrvCtxt *pDrvCtxt,  ClockSleepModeType  eMode,  uint32  nFlags){return DAL_SUCCESS;}
static inline DALResult Clock_SetVoltage( ClockDrvCtxt *pDrvCtxt, ClockVRegIdType eVRegId, uint32 nVoltageUV, boolean *pbIsLDOEnabled){return DAL_SUCCESS;}
static inline DALResult Clock_RegisterCPRCallbacks( ClockDrvCtxt *pDrvCtxt, CPR_PreSwitchFuncPtr fpPreSwitch, CPR_PostSwitchFuncPtr fpPostSwitch, CPR_GetVoltageFuncPtr fpGetVoltage){return DAL_SUCCESS;}
static inline DALResult Clock_ImageBIST(ClockDrvCtxt  *pDrvCtxt, boolean *bBISTPassed, uint32 *nFailedTests){return DAL_SUCCESS;}

#endif /* !__CLOCK_DRIVER_H__ */


