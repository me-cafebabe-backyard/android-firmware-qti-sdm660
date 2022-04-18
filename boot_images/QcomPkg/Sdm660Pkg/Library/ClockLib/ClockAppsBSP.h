#ifndef __CLOCKAPPSBSP_H__
#define __CLOCKAPPSBSP_H__
/*
===========================================================================
*/
/**
  @file ClockAppsBSP.h

  Header description for the MSM8994 apps clock driver BSP format.
*/
/*
  ====================================================================

  Copyright (c) 2010 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockAppsCPR.h"
#include "Drivers/ClockDxe/ClockBSP.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include "../HALclkLib/HALclkAPCS.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Enumeration of CPU elements.
 */
typedef enum
{
  CLOCK_APPS_CPU_C0  = HAL_CLK_APCS_CPU_CLUSTER0,
  CLOCK_APPS_CPU_C1  = HAL_CLK_APCS_CPU_CLUSTER1,
  CLOCK_APPS_CPU_L2  = HAL_CLK_APCS_CPU_CCI,
  CLOCK_APPS_CPU_CBF = CLOCK_APPS_CPU_L2,
  CLOCK_APPS_CPU_L3  = CLOCK_APPS_CPU_L2,
  CLOCK_APPS_CPU_TOTAL,

  CLOCK_ENUM_32BITS(APPS_CPU)
} ClockAppsCPUType;

/*
 * Enumeration of performance levels.
 */
enum
{
  CLOCK_APPS_PERF_LEVEL_0,
  CLOCK_APPS_PERF_LEVEL_1,
  CLOCK_APPS_PERF_LEVEL_2,
  CLOCK_APPS_PERF_LEVEL_3,
  CLOCK_APPS_PERF_LEVEL_4,
  CLOCK_APPS_PERF_LEVEL_5,
  CLOCK_APPS_PERF_LEVEL_6,
  CLOCK_APPS_PERF_LEVEL_7,
  CLOCK_APPS_PERF_LEVEL_8,
  CLOCK_APPS_PERF_LEVEL_9,
  CLOCK_APPS_PERF_LEVEL_10,
  CLOCK_APPS_PERF_LEVEL_11,
  CLOCK_APPS_PERF_LEVEL_12,
  CLOCK_APPS_PERF_LEVEL_13,
  CLOCK_APPS_PERF_LEVEL_14,
  CLOCK_APPS_PERF_LEVEL_15,
  CLOCK_APPS_PERF_LEVEL_16,
  CLOCK_APPS_PERF_LEVEL_17,
  CLOCK_APPS_PERF_LEVEL_18,
  CLOCK_APPS_PERF_LEVEL_TOTAL
};

/*
 * Enumeration of configurations for the Hydra LVT Duplex.
 */
enum
{
  CLOCK_APPS0_CONFIG_192_MHZ,
  CLOCK_APPS0_CONFIG_269_MHZ,
  CLOCK_APPS0_CONFIG_300_MHZ,
  CLOCK_APPS0_CONFIG_346_MHZ,
  CLOCK_APPS0_CONFIG_403_MHZ,
  CLOCK_APPS0_CONFIG_480_MHZ,
  CLOCK_APPS0_CONFIG_576_MHZ,
  CLOCK_APPS0_CONFIG_634_MHZ,
  CLOCK_APPS0_CONFIG_730_MHZ,
  CLOCK_APPS0_CONFIG_806_MHZ,
  CLOCK_APPS0_CONFIG_883_MHZ,
  CLOCK_APPS0_CONFIG_960_MHZ,
  CLOCK_APPS0_CONFIG_1018_MHZ,
  CLOCK_APPS0_CONFIG_1114_MHZ,
  CLOCK_APPS0_CONFIG_1190_MHZ,
  CLOCK_APPS0_CONFIG_1267_MHZ,
  CLOCK_APPS0_CONFIG_1344_MHZ,
  CLOCK_APPS0_CONFIG_1421_MHZ,
  CLOCK_APPS0_CONFIG_1459_MHZ,
  CLOCK_APPS0_CONFIG_TOTAL
};

/*
 * Enumeration of transitional configurations for the Hydra LVT Duplex.
 */
enum
{
  CLOCK_APPS0T_CONFIG_173_MHZ,
  CLOCK_APPS0T_CONFIG_250_MHZ,
  CLOCK_APPS0T_CONFIG_300_MHZ,
  CLOCK_APPS0T_CONFIG_307_MHZ,
  CLOCK_APPS0T_CONFIG_365_MHZ,
  CLOCK_APPS0T_CONFIG_432_MHZ,
  CLOCK_APPS0T_CONFIG_518_MHZ,
  CLOCK_APPS0T_CONFIG_576_MHZ,
  CLOCK_APPS0T_CONFIG_653_MHZ,
  CLOCK_APPS0T_CONFIG_730_MHZ,
  CLOCK_APPS0T_CONFIG_787_MHZ,
  CLOCK_APPS0T_CONFIG_864_MHZ,
  CLOCK_APPS0T_CONFIG_922_MHZ,
  CLOCK_APPS0T_CONFIG_998_MHZ,
  CLOCK_APPS0T_CONFIG_1075_MHZ,
  CLOCK_APPS0T_CONFIG_1133_MHZ,
  CLOCK_APPS0T_CONFIG_1210_MHZ,
  CLOCK_APPS0T_CONFIG_1286_MHZ,
  CLOCK_APPS0T_CONFIG_1306_MHZ,
  CLOCK_APPS0T_CONFIG_TOTAL
};

/*
 * Enumeration of configurations for the Hydra sLVT Duplex.
 */
enum
{
  CLOCK_APPS1_CONFIG_300_MHZ,
  CLOCK_APPS1_CONFIG_346_MHZ,
  CLOCK_APPS1_CONFIG_403_MHZ,
  CLOCK_APPS1_CONFIG_480_MHZ,
  CLOCK_APPS1_CONFIG_576_MHZ,
  CLOCK_APPS1_CONFIG_634_MHZ,
  CLOCK_APPS1_CONFIG_730_MHZ,
  CLOCK_APPS1_CONFIG_806_MHZ,
  CLOCK_APPS1_CONFIG_883_MHZ,
  CLOCK_APPS1_CONFIG_960_MHZ,
  CLOCK_APPS1_CONFIG_1018_MHZ,
  CLOCK_APPS1_CONFIG_1114_MHZ,
  CLOCK_APPS1_CONFIG_1190_MHZ,
  CLOCK_APPS1_CONFIG_1267_MHZ,
  CLOCK_APPS1_CONFIG_1344_MHZ,
  CLOCK_APPS1_CONFIG_1421_MHZ,
  CLOCK_APPS1_CONFIG_1498_MHZ,
  CLOCK_APPS1_CONFIG_1594_MHZ,
  CLOCK_APPS1_CONFIG_TOTAL
};

/*
 * Enumeration of transitional configurations for the Hydra sLVT Duplex.
 */
enum
{
  CLOCK_APPS1T_CONFIG_300_MHZ,
  CLOCK_APPS1T_CONFIG_307_MHZ,
  CLOCK_APPS1T_CONFIG_365_MHZ,
  CLOCK_APPS1T_CONFIG_432_MHZ,
  CLOCK_APPS1T_CONFIG_518_MHZ,
  CLOCK_APPS1T_CONFIG_576_MHZ,
  CLOCK_APPS1T_CONFIG_653_MHZ,
  CLOCK_APPS1T_CONFIG_730_MHZ,
  CLOCK_APPS1T_CONFIG_787_MHZ,
  CLOCK_APPS1T_CONFIG_864_MHZ,
  CLOCK_APPS1T_CONFIG_922_MHZ,
  CLOCK_APPS1T_CONFIG_998_MHZ,
  CLOCK_APPS1T_CONFIG_1075_MHZ,
  CLOCK_APPS1T_CONFIG_1133_MHZ,
  CLOCK_APPS1T_CONFIG_1210_MHZ,
  CLOCK_APPS1T_CONFIG_1286_MHZ,
  CLOCK_APPS1T_CONFIG_1344_MHZ,
  CLOCK_APPS1T_CONFIG_1440_MHZ,
  CLOCK_APPS1T_CONFIG_TOTAL
};

/*
 * Enumeration of configurations for the CBF clock.
 */
enum
{
  CLOCK_APPS2_CONFIG_150_MHZ,
  CLOCK_APPS2_CONFIG_300_MHZ,
  CLOCK_APPS2_CONFIG_384_MHZ,
  CLOCK_APPS2_CONFIG_499_MHZ,
  CLOCK_APPS2_CONFIG_600_MHZ,
  CLOCK_APPS2_CONFIG_692_MHZ,
  CLOCK_APPS2_CONFIG_787_MHZ,
  CLOCK_APPS2_CONFIG_883_MHZ,
  CLOCK_APPS2_CONFIG_960_MHZ,
  CLOCK_APPS2_CONFIG_1037_MHZ,

  CLOCK_APPS2_CONFIG_TOTAL
};

/*
 * ClockAppsPerfLevelConfigType
 *
 * Configuration parameters for a performance level.
 *
 *  Mux         - General mux configuration.
 *  nVDDMem     - VDD_MEM value in millivolts.
 *  eVRegAPCCorner - APC rail voltage corner for CPR control.
 *  nVRegAPCCornerIndex - Index to APC rail voltage corner for CPR control.
 *  AVSCoreData - Structure for DCVS and AVS voltage programming.
 */
typedef struct
{
  ClockMuxConfigType      Mux;
  uint32                  nVDDMem;
  ClockVRegLevelType      eVRegAPCCorner;
  uint32                  nVRegAPCCornerIndex;
  ClockAVSCoreFreqCfgType AVSCoreData;
} ClockAppsPerfLevelConfigType;

/*
 * Actual format for the data stored in the BSP.
 */
typedef struct
{
  uint32                        nMinPerfLevel;
  uint32                        nMaxPerfLevel;
  uint32                        anPerfLevel[CLOCK_APPS_PERF_LEVEL_TOTAL];
  ClockAppsPerfLevelConfigType  aPerfConfig[CLOCK_APPS_PERF_LEVEL_TOTAL];
} ClockAppsBSPCPUConfigType;

/*
 * CPU BSP type.
 */
typedef struct
{
  const char                *szName;
  HAL_clk_SourceType         eHFPLLSource;
  ClockAppsBSPCPUConfigType *pConfig;
  ClockAppsBSPCPUConfigType *pConfigTransitional;
  ClockVRegCornerDataType   *pVRegCornerData;
  ClockOLCPReFuseDataType    mStartingVoltage;
} ClockAppsBSPCPUType;

/*
 * Apps BSP type.
 */
typedef struct
{
  ClockAppsBSPCPUType aCPUConfig[CLOCK_APPS_CPU_TOTAL];
  boolean             bInterpolationEnabled;
  boolean             bLimitInterpolationEnabled;
  boolean             bEnableDynamicCeiling;
} ClockAppsBSPType;

/* =========================================================================
**  Function : Clock_InitAppsBSP
** =========================================================================*/
/**
  Initializes the Apps BSP data.

  Initializes the Apps BSP data by doing any necessary runtime detection based
  on information such as: chip ID, chip version, PVS bins, and speed bins.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  DAL_SUCCESS -- BSP initialized successfully.
  DAL_ERROR -- BSP initialization failed.

  @dependencies
  None.
*/

DALResult Clock_InitAppsBSP
(
  ClockDrvCtxt *pDrvCtxt
);

/* =========================================================================
**  Function : Clock_GetAppsBSP
** =========================================================================*/
/**
  Returns a pointer to the Apps BSP data.

  @return
  Pointer to the BSP data.

  @dependencies
  None.
*/

ClockAppsBSPType *Clock_GetAppsBSP
(
  void
);
#if 0
/* =========================================================================
**  Function : Clock_TestVoltagePlan
** =========================================================================*/
/**
    Returns voltage for a hypothetical device to test local implementation
    of the official voltage plan.

    This function accepts a set of parameters that specify a hypothetical
    device supported by the clock driver and returns the corresponding
    APCS rail voltage derived from the local implementation of the device's
    voltage plan. The intent of this function is to allow independent validation
    of the implementation of the voltage plan.

    Not every parameter value in the input data structure is applicable to every
    device. The clock driver will validate only the parameter values that apply
    to the particular voltage plan as determined by the nChipId. Every parameter
    applicable to the particular nChipId will be validated based on the range of
    acceptable values, all other parameters will be ignored.

    @param pDrvCtxt -- Pointer to clock driver context.
    @param eCPU [in] -- CPU of interest.
    @param nPerfLevel [in] -- Performance Level of interest.
    @param pmBinValidationParams [in] -- Data structure specifying parameters of
                                         a hypothetical device to validate.
    @param pnVoltageUV [out] -- Specifies address for the returned voltage.

    @return
    DAL_SUCCESS -- The value returned is the corresponding voltage.
    DAL_ERROR -- One or more input parameter is invalid.

    @dependencies
    None.
*/

DALResult Clock_TestVoltagePlan
(
  ClockDrvCtxt           *pDrvCtxt,
  ClockAppsCPUType        eCPU,
  uint32                  nPerfLevel,
  ClockBinValidationType *pmBinValidationParams,
  uint32                 *pnVoltageUV
);
#endif
#endif  /* __CLOCKAPPSBSP_H__ */

