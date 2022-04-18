#ifndef CLOCKDEFS_H
#define CLOCKDEFS_H
/*
===========================================================================
*/
/**
  @file ClockDefs.h
  @brief Public definitions include file for accessing the clock device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear
      in the PDF.

      The Clock_Driver_API_mainpage.dox file contains all file/group
      descriptions that are in the output PDF generated using Doxygen and
      LaTeX. To edit or update any of the file/group text in the PDF, edit the
      Clock_Driver_mainpage.dox file or contact Tech Pubs.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2011-2015 QUALCOMM Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================


  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  05/17/11   llg     (Tech Pubs) Edited/added Doxygen comments and markup.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/** @addtogroup clock_functions
@{ */

/**
  Clock handle.
 */
typedef size_t ClockIdType;


/**
  Source handle.
 */
typedef size_t SourceIdType;


/**
  Used to search for a matching frequency input. This type describes how
  frequency matching is done for the clock frequency selection function. It
  also indicates units in Hz, kHz, or MHz.
 */
typedef enum
{
  CLOCK_FREQUENCY_HZ_AT_LEAST  = 0,     /**< Frequency is the minimum allowed in Hz. */
  CLOCK_FREQUENCY_HZ_AT_MOST   = 1,     /**< Frequency is the maximum allowed in Hz. */
  CLOCK_FREQUENCY_HZ_CLOSEST   = 2,     /**< Closest match in Hz. */
  CLOCK_FREQUENCY_HZ_EXACT     = 3,     /**< Exact match only in Hz. */

  CLOCK_FREQUENCY_KHZ_AT_LEAST = 0x10,  /**< Frequency is the minimum allowed in kHz. */
  CLOCK_FREQUENCY_KHZ_AT_MOST  = 0x11,  /**< Frequency is the maximum allowed in kHz. */
  CLOCK_FREQUENCY_KHZ_CLOSEST  = 0x12,  /**< Closest match in kHz. */
  CLOCK_FREQUENCY_KHZ_EXACT    = 0x13,  /**< Exact match only in kHz. */

  CLOCK_FREQUENCY_MHZ_AT_LEAST = 0x20,  /**< Frequency is the minimum allowed in MHz. */
  CLOCK_FREQUENCY_MHZ_AT_MOST  = 0x21,  /**< Frequency is the maximum allowed in MHz. */
  CLOCK_FREQUENCY_MHZ_CLOSEST  = 0x22,  /**< Closest match in MHz. */
  CLOCK_FREQUENCY_MHZ_EXACT    = 0x23,  /**< Exact match only in MHz. */
} ClockFrequencyType;


/**
  Type of clock reset. This defines how the reset to the clock domain
  is to be handled.
 */
typedef enum
{
  CLOCK_RESET_DEASSERT = 0,  /**< Deassert the reset signal. */
  CLOCK_RESET_ASSERT   = 1,  /**< Assert and hold the reset signal. */
  CLOCK_RESET_PULSE    = 2   /**< Assert and immediately deassert. */
} ClockResetType;


/**
  Clock QDSS levels
 */
typedef enum
{
  CLOCK_QDSS_LEVEL_OFF,      /**< clock set to CXO, and off */
  CLOCK_QDSS_LEVEL_DEBUG,    /**< clock rate follows VDD_CX */
  CLOCK_QDSS_LEVEL_HSDEBUG,  /**< clock set to high speed */
} ClockQDSSLevelType;


/**
  Type of clock configuration.  This type describes how a clock is
  configured.
 */
typedef enum
{
  CLOCK_CONFIG_NULL                 = 0,  /**< NULL configuration. */

  CLOCK_CONFIG_MMSS_SOURCE_CSI0     = 1,  /**< Select CSI0 source. */
  CLOCK_CONFIG_MMSS_SOURCE_CSI1     = 2,  /**< Select CSI1 source. */
  CLOCK_CONFIG_MMSS_SOURCE_CSI2     = 3,  /**< Select CSI2 source. */

  CLOCK_CONFIG_AUTOGATE_ENABLE      = 4,  /**< Enable autogating. */
  CLOCK_CONFIG_AUTOGATE_DISABLE     = 5,  /**< Disable autogating. */

  CLOCK_CONFIG_BRANCH_ONLY_ENABLE   = 6,  /**< Enable clock branch only. */
  CLOCK_CONFIG_BRANCH_ONLY_DISABLE  = 7,  /**< Disable clock branch only. */

  CLOCK_CONFIG_MARK_SUPPRESSIBLE    = 8,  /**< Mark the clock as suppressible. */
  CLOCK_CONFIG_MARK_INSUPPRESSIBLE  = 9,  /**< Mark the clock as insuppressible. */

  CLOCK_CONFIG_SUSPEND_REF_COUNTING = 10, /**< Suspend reference counting for the clock. */
  CLOCK_CONFIG_RESUME_REF_COUNTING  = 11, /**< Resume reference counting for the clock. */

  CLOCK_CONFIG_MARK_ALWAYS_ON_TRUE                    = 12, /**< Mark the clock as always on. */
  CLOCK_CONFIG_MARK_ALWAYS_ON_FALSE                   = 13, /**< Mark the clock as not always on. */

  CLOCK_CONFIG_FORCE_MEM_CORE_ENABLED                 = 14, /**< Enable override of the normal FORCE MEM CORE operation. */
  CLOCK_CONFIG_FORCE_MEM_PERIPH_ENABLED               = 15, /**< Enable override of the normal FORCE MEM PERIPH operation. */
  CLOCK_CONFIG_FORCE_MEM_CORE_AND_MEM_PERIPH_ENABLED  = 16, /**< Enable override of the normal FORCE MEM CORE & FORCE MEM PERIPH operation. */

  CLOCK_CONFIG_REPORT_CX_RAIL_UPDATES                 = 17, /**< Enable CX rail update callbacks. */

  /** @cond
  */
  CLOCK_CONFIG_TOTAL = 18
  /** @endcond */
} ClockConfigType;

/**
  Options for the DalClock_LogState API.
 */
typedef enum
{
  CLOCK_LOG_STATE_CLOCK_FREQUENCY = (1 << 0),
} ClockLogStateFlags;

/** @} */ /* end_addtogroup clock_functions */

/** @addtogroup power_domain_functions
@{ */


/**
  Power domain handle.
 */
typedef size_t ClockPowerDomainIdType;


/** @} */ /* end_addtogroup power_domain_functions */

/** @addtogroup topology_functions
@{ */

/**
 * Enumeration of clusters comprising the APSS.
 */
typedef enum
{
  CLOCK_APPS_CLUSTER_A7,
  CLOCK_APPS_CLUSTER_A53,
  CLOCK_APPS_CLUSTER_A57,
  CLOCK_APPS_CLUSTER_CCI,
  CLOCK_APPS_CLUSTER_HYDRA_0,
  CLOCK_APPS_CLUSTER_HYDRA_1,
  CLOCK_APPS_CLUSTER_TOTAL
} ClockAppsClusterIdType;

/**
  Types of cores recognized in a topology.
 */
typedef enum
{
  CLOCK_CORE_PROCESSOR,
  CLOCK_CORE_L1_CACHE,
  CLOCK_CORE_L2_CACHE,
  CLOCK_CORE_L3_CACHE,
  CLOCK_CORE_CCI,
  CLOCK_CORE_TYPE_TOTAL
} ClockCoreType;

/**
  Types of clusters recognized in a topology.
 */
typedef enum
{
  CLOCK_CLUSTER_SYNCHRONOUS,
  CLOCK_CLUSTER_ASYNCHRONOUS,
  CLOCK_CLUSTER_TYPE_TOTAL
} ClockClusterType;


/** @} */ /* end_addtogroup topology_functions */

/** @addtogroup misc_functions
@{ */


/**
  Processor Sleep mode. This type defines the different kinds of sleep modes
  that can be entered.
 */
typedef enum
{
  CLOCK_SLEEP_MODE_HALT,            /**< Processor halt only. */
  CLOCK_SLEEP_MODE_POWER_COLLAPSE   /**< Processor power collapse. */
} ClockSleepModeType;


/*
 * Impending CPU core state.
 */
typedef enum
{
  CLOCK_CORE_WENT_OFFLINE,          /* Processor core went offline. */
  CLOCK_CORE_COMING_ONLINE,         /* Processor core coming online. */
  CLOCK_CORE_STATE_TOTAL
} ClockCoreStateType;

/*
 * CPR Client ID Type.
 */
typedef enum
{
  CLOCK_VREG_VDD_APC0_CLIENT_A53,
  CLOCK_VREG_VDD_APC0_CLIENT_CCI,
  CLOCK_VREG_VDD_APC0_CLIENT_TOTAL,
  CLOCK_VREG_VDD_APC1_CLIENT_A57 = 0,
  CLOCK_VREG_VDD_APC1_CLIENT_TOTAL
} ClockVRegClientIdType;

/*
 * Voltage regulator ID Type.
 */
typedef enum
{
  CLOCK_VREG_VDD_CX,
  CLOCK_VREG_VDD_MSS,
  CLOCK_VREG_VDD_APC,
  CLOCK_VREG_VDD_APC0,
  CLOCK_VREG_VDD_APC1,
  CLOCK_VREG_TOTAL
} ClockVRegIdType;


/*
 * CPR Voltage Corner Type.
 */
typedef enum
{
  CPR_CORNER_LOW_SVS,
  CPR_CORNER_SVS,
  CPR_CORNER_NOMINAL,
  CPR_CORNER_TURBO,
  CPR_CORNER_TOTAL
} ClockCPRCornerType;


/*
 * CPR callback functions
 */
typedef void (*CPR_PreSwitchFuncPtr) (void *pContext, void *pClientContext);
typedef void (*CPR_GetVoltageFuncPtr)(void *pContext, void *pClientContext, uint32 nVoltageMode, uint32 *pRawVoltageUV);
typedef void (*CPR_PostSwitchFuncPtr)(void *pContext, void *pClientContext, boolean bIsLDOEnabled, uint32 nRawVoltageUV);


/*
 * Corner voltage data.
 */
typedef struct
{
  uint32              nUVMin;                   /* voltage floor   (uV)          */
  uint32              nUVMax;                   /* voltage ceiling (uV)          */
  uint32              nUVMaxStatic;             /* static voltage ceiling (uV)   */
  ClockCPRCornerType  eCornerType;  /* CPR Corner Type enum        */
  uint32              nFreqKHz;                 /* corresponding frequency (KHz) */
  uint32              nInitialVoltageUV;        /* initial voltage (uV)          */
  uint32              nInitialVoltageUVStatic;  /* static initial voltage (uV)   */
} ClockVRegCornerDataType;


/*
 * Limits Management callback functions
 */
typedef void (*LM_CpuUpdateFuncPtr)(uint32 nVoltageCorner);
typedef void (*LM_GpuUpdateFuncPtr)(uint32 nVoltageCorner);


/*
 * Clock Debug List Data Structure.
 */
typedef struct
{
  uint32      nDebugId;             /* QDSS clock debug ID */
  uint32      nIndex;               /* clock index */
} ClockDebugListDataStructureType;


/*
 * Clock Debug Data Structure.
 */
typedef struct
{
  uint32      nDebugId;             /* QDSS clock debug ID */
  const char *szClockName;          /* clock name string */
} ClockDebugDataStructureType;


/*
 * Debug filter type used to specify data of interest.
 */
typedef enum
{                                   /* Returns data for: */
  CLOCK_FILTER_NONE,                /*  all clocks */
  CLOCK_FILTER_ENABLED,             /*  all clocks in ENABLED state */
  CLOCK_FILTER_ON,                  /*  all clocks in ON state */
  CLOCK_FILTER_REF,                 /*  all clocks with non-zero reference count */
  CLOCK_FILTER_XO,                  /*  all clocks blocking XO */
  CLOCK_FILTER_TOTAL
} ClockDebugFilterType;


/*
 * Structure returning a local NPA Resource's list of clocks.
 */
typedef struct LocalNPAResourceClocksList
{
  const char *szName;
  const void *pNULL;
} LocalNPAResourceClocksList;


/**
  Processor Sleep mode flag masks. RAMP_DOWN_CPU triggers frequency switching
  to a lower performance level before SWFI.  L2CACHE_FLUSH flushes the contents
  of L2 cache when entering power collapse. In some cases, the L2 cache frequency
  needs to be lowered with the CPU frequency. In other cases, the L2 cache
  frequency needs to remain untouched. This is when the RAMP_DOWN_L2CACHE flag
  becomes useful.
 */
#define CLOCK_SLEEP_FLAG_NONE                   0x00000000
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_CPU          0x00000001
#define CLOCK_SLEEP_FLAG_L2CACHE_FLUSH          0x00000002
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_L2CACHE      0x00000004
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_L3CACHE      0x00000008
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_APSS         0x00000010
#define CLOCK_SLEEP_FLAG_RAMP_DOWN_XO           0x00000010
#define CLOCK_SLEEP_FLAG_CORE_RET               0x00000020

/**
  Clock driver logging options. This is a unified set. No every option is
  available for use with a single clock.

  Note: these values are related to the clock flag bits defined in the file
  ClockBSP.h
 */
#define CLOCK_LOG_CLOCK_STATE_CHANGE            0x01
#define CLOCK_LOG_CLOCK_FREQ_CHANGE             0x02
#define CLOCK_LOG_CLOCK_CONFIG_CHANGE           0x04
#define CLOCK_LOG_CLOCK_RESET                   0x08
#define CLOCK_LOG_SOURCE_STATE_CHANGE           0x10
#define CLOCK_LOG_POWER_DOMAIN_STATE_CHANGE     0x20
#define CLOCK_LOG_VOLTAGE_CHANGE                0x40
// Reserved for future logging                  0x80

#define CLOCK_LOG_MASK                          0xFF


/*
 * Clock Driver External Configuration Parameter Type.
 */
typedef enum
{
  CLOCK_CONFIG_PARAM_APCS_VOLTAGE_STEP_SIZE,
  CLOCK_CONFIG_PARAM_APCS_VOLTAGE_OFFSET,
  CLOCK_CONFIG_PARAM_IS_EXTERNAL_BUCK_USED,
  CLOCK_CONFIG_PARAM_RETURN_SPEED_BIN,
  CLOCK_CONFIG_PARAM_RETURN_SPEED_BIN_RAW,
  CLOCK_CONFIG_PARAM_RETURN_SPEED_BIN_STATUS,
  CLOCK_CONFIG_PARAM_RETURN_PVS_BIN,
  CLOCK_CONFIG_PARAM_RETURN_PVS_BIN_SECONDARY,
  CLOCK_CONFIG_PARAM_RETURN_UPLIFT_FUSE,
  CLOCK_CONFIG_PARAM_RETURN_ACC_L1_REGISTER,
  CLOCK_CONFIG_PARAM_RETURN_METAL_REV,
  CLOCK_CONFIG_PARAM_RETURN_SPEED_BIN_SECONDARY,
  CLOCK_CONFIG_PARAM_TOTAL,
} eConfigParamType;


typedef struct
{
  uint32  nVoltageOffset;             /* Number of 10mV steps to offset from the standard voltage. */
  boolean bSubtract;                  /* 1: subtract,
                                         0: add the nVoltageOffset from/to the standard voltage. */
} ClockCprEfuseType;


/**
 * PVS and Speed Bin Validation Parameter Type.
 */
typedef struct
{
  uint32            nChipId;            /* Chip ID as returned by the ChipInfo library */
  uint32            nChipVersion;       /* Chip Version in the MAJOR.minor format */
  uint32            nPVSBin;            /* PVS bin number */
  uint32            nPVSBinSecondary;   /* Secondary PVS bin number */
  uint32            nSpeedBinRaw;       /* Speed bin number */
  uint32            nSpeedBinStatus;    /* Speed bin status */
  uint32            nCPRRev;            /* CPR Revision Level */
  uint32            nAccL1Register;     /* Normalized value of the ACC_L1 Register 0xFC4B81B4[15:10] */
  uint32            nUpliftFuse;        /* Normalized value of the UPLIFT_FUSE 0xFC4B80B4[53] */
  uint32            nMetalRev;          /* Normalized value of the METAL_REV 0xFC4B8454[19:18] */
  ClockCprEfuseType C0_SVS;             /* Normalized value of the APSS Cluster 0 SVS e-fuse */
  ClockCprEfuseType C0_Nominal;         /* Normalized value of the APSS Cluster 0 Nominal e-fuse */
  ClockCprEfuseType C0_Turbo;           /* Normalized value of the APSS Cluster 0 Turbo e-fuse */
  ClockCprEfuseType C1_SVS;             /* Normalized value of the APSS Cluster 1 SVS e-fuse */
  ClockCprEfuseType C1_Nominal;         /* Normalized value of the APSS Cluster 1 Nominal e-fuse */
  ClockCprEfuseType C1_Turbo;           /* Normalized value of the APSS Cluster 1 Turbo e-fuse */
  uint32            nSpeedBinPrimary;   /* Primary Cluster speed bin number */
  uint32            nSpeedBinSecondary; /* Secondary Cluster speed bin number */
} ClockBinValidationType;


/** @} */ /* end_addtogroup misc_functions */

/** @addtogroup npa_functions
@{ */
/** @name NPA Query Requests
@{ */

/**
  NPA query ID for a performance level frequency. This query
  gets the frequency in kHz for the node performance level. The actual
  performance level is to be added to this ID (i.e., to query frequency
  for performance level 2, pass DALCLOCK_NPA_QUERY_PERF_LEVEL_KHZ + 2).
 */
#define CLOCK_NPA_QUERY_PERF_LEVEL_KHZ (NPA_QUERY_RESERVED_END + 1)

/**
  NPA query ID for the number of supported performance levels.
  This query returns the number of supported performance levels for
  the resource in question.
 */
#define CLOCK_NPA_QUERY_NUM_PERF_LEVELS (CLOCK_NPA_QUERY_PERF_LEVEL_KHZ + 0x20)

/**
  NPA query for the minimum supported frequency in kHz for a resource.
  This query returns the minimum supported frequency for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_MIN_FREQ_KHZ (CLOCK_NPA_QUERY_NUM_PERF_LEVELS + 1)

/**
  NPA query ID for the corner voltage table.
  This query returns the voltage values of each corner for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_TABLE (CLOCK_NPA_QUERY_MIN_FREQ_KHZ + 1)

/**
  NPA query ID for the number of voltage corners.
  This query returns the number of voltage corners for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES (CLOCK_NPA_QUERY_VOLTAGE_TABLE + 1)

/**
  NPA query ID for the current voltage corner.
  This query returns the id (voltage table index) of for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY (CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES + 1)

/**
  NPA query ID for the corner voltage table of rail 0.
  This query returns the voltage values of each corner for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_TABLE_RAIL_0 (CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY + 1)

/**
  NPA query ID for the number of voltage corners of rail 0.
  This query returns the number of voltage corners for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_RAIL_0 (CLOCK_NPA_QUERY_VOLTAGE_TABLE_RAIL_0 + 1)

/**
  NPA query ID for the current voltage corner of rail 0.
  This query returns the id (voltage table index) of for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_RAIL_0 (CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_RAIL_0 + 1)

/**
  NPA query ID for the corner voltage table of rail 1.
  This query returns the voltage values of each corner for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_TABLE_RAIL_1 (CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_RAIL_0 + 1)

/**
  NPA query ID for the number of voltage corners of rail 1.
  This query returns the number of voltage corners for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_RAIL_1 (CLOCK_NPA_QUERY_VOLTAGE_TABLE_RAIL_1 + 1)

/**
  NPA query ID for the current voltage corner of rail 1.
  This query returns the id (voltage table index) of for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_RAIL_1 (CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_RAIL_1 + 1)

/**
  NPA query ID for the corner voltage table for CCI.
  This query returns the voltage values of each corner for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_TABLE_CCI (CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_RAIL_1 + 1)

/**
  NPA query ID for the number of voltage corners for CCI.
  This query returns the number of voltage corners for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_CCI (CLOCK_NPA_QUERY_VOLTAGE_TABLE_CCI + 1)

/**
  NPA query ID for the current voltage corner for CCI.
  This query returns the id (voltage table index) of for the resource
  based on the target and configured limitations.
 */
#define CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_CCI (CLOCK_NPA_QUERY_VOLTAGE_NUM_ENTRIES_CCI + 1)

/**
  NPA query for the CPU rail voltage in mV.

  NOTE: This is the clock driver's vote for the CPU VREG, but it may not map
        directly to the supplied voltage. In cases where the CPU VREG isn't
        wholly owned by the CPU, then the actual VREG voltage will be at least
        this level, but may be higher.
 */
#define CLOCK_NPA_QUERY_CPU_RAIL_VOLTAGE_MV   (CLOCK_NPA_QUERY_VOLTAGE_CURRENT_ENTRY_CCI + 1)


/** @} */ /* end_name_group NPA Query Requests */
/** @} */ /* end_addtogroup npa_functions */


#endif /* !CLOCKDEFS_H */

