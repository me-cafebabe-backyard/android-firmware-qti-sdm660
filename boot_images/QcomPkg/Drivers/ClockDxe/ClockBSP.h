#ifndef __CLOCKBSP_H__
#define __CLOCKBSP_H__

/*=========================================================================

                    C L O C K   D E V I C E   D R I V E R

        B O A R D   S U P P O R T   P A C K A G E   D E F I N I T I O N S

GENERAL DESCRIPTION
  This file contains the BSP interface definitions for the
  MSM DAL Clock Device Driver.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

      Copyright (c) 2010-2016 by QUALCOMM Technologies, Inc.  All Rights Reserved.

==========================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------
11/30/10   vs      Initial release.

==========================================================================*/

/*=========================================================================
      Includes
==========================================================================*/


#include "Include/api/systemdrivers/ClockDefs.h"
#include "HALclk.h"
#include "DALSys.h"
#include "DDIChipInfo.h"
#include "Library/HALclkSharedLib/HALavs.h"


/*=========================================================================
      Constants & Macros & Typedefs
==========================================================================*/

/*
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define CLOCK_BSP_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF


/*
 * Macros for compare support BSP within the range of HW version
 * BSP HW VERSION:
 *     Bits[ 0: 7] - Max HW version minor bits
 *     Bits[15: 8] - Max HW version major bits
 *     Bits[23:16] - Min HW version minor bits
 *     Bits[31:24] - Min HW version major bits
*/

#define BSP_HW_VER(nMinMajor, nMinMinor, nMaxMajor, nMaxMinor)               \
            ( ((nMinMajor<<24)& 0xFF000000) | ((nMinMinor<<16) & 0x00FF0000) | \
              ((nMaxMajor<<8) & 0x0000FF00) |  (nMaxMinor&0xFF) )

#define BSP_HW_VER_MIN( nBSPVersion ) ( ((nBSPVersion & 0xFF000000)>>8) | \
                                        ((nBSPVersion & 0x00FF0000)>>16) )
#define BSP_HW_VER_MAX( nBSPVersion ) ( ((nBSPVersion & 0x0000FF00)<<8) | \
                                         (nBSPVersion & 0x000000FF) )


/*
 * Macros for consolidating PLL configuration in a single mask.
 */
#define CLOCK_CONFIG_PLL_FSM_MODE_ENABLE        (1 << 0)
#define CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE      (1 << 1)
#define CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE     (1 << 2)
#define CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE    (1 << 3)
#define CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE     (1 << 4)
#define CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE      (1 << 5)

/**
 * Unified flag bits
 *
 * NOTE: These flags can be used in any node that supports the
 * nFlags field.
 *
 *  LOG_STATE_CHANGE - Enable logging of enable/disable calls
 *    to a particular node.
 *  LOG_FREQ_CHANGE - Enable logging of frequency changes to
 *    a particular node.
 *  LOG_CONFIG_CHANGE - Enable logging of configuration changes
 *    to a particular node.
 *  LOG_RESET - Enable logging of resets to a particular node.
 *  LOG_SLEEP_CHANGE - Enable logging of sleep state changes.
 *  DO_NOT_DISABLE - Ignore requests to disable a particular
 *    node.
 *  SUPPRESSIBLE - Indicates XO shutdown will not be held off
 *    while the clock is on.
 *  DOMAIN_HOLD_VREG_REQUEST - Hold the voltage request even
 *    when the clock is off. When set this means the voltage
 *    request will be based solely on the configured clock
 *    frequency and will not be released when the clock is
 *    disabled.
 *  DOMAIN_DYNAMIC_CONFIG - Indicates this domain was configured
 *    dynamically and memory should be freed when the domain is
 *    reconfigured.
 *  AUTOGATE - Indicates this clock has the autogating feature
 *    enabled.
 *  BIST_FAILURE_ANTICIPATED - Indicates this clock may fail the
 *    Built-In-Self-Test due to configuration complexities, and
 *    negative results should not be treated as a hard failure.
 *  XO_VOTE - Indicates this clock should explicitly vote for
 *    XO when enabled.
 *  NO_REFERENCE_COUNTING - Indicates that reference counting for
 *    this clock has been disabled. In such cases, the reference
 *    counter is limited to the range between 0 and 1.
 *  BRANCH_ONLY_CONTROL - Indicates that when controlling this
 *    clock all source and voltage processing is bypassed and
 *    only the clock branch control is performed. Source and
 *    voltage processing is performed only when configuring
 *    this clock to be under BRANCH_ONLY_CONTROL.
 *  SUPPRESS_VOLTAGE_CONTROL - Indicates that voltage control
 *    is being performed externally and all voltage control
 *    requests need to be ignored. This is usually a very
 *    special scenario (e.g., crash dump collection in WA/WP).
 *  SUPPORTS_SLEWING - Indicates that this PLL can be
 *    dynamically re-configured without having to first
 *    be disabled and then re-enabled.
 *  SOURCE_CALIBRATED - Indicates that a PLL has been calibrated.
 *  BYPASS_DEPENDENCIES - Indicates that the resource's requirements
 *    are always satisfied or managed by an external agent.
 *    The clock driver will not make requests for this type
 *    of resource.
 */
#define CLOCK_FLAG_LOG_STATE_CHANGE           PUBLIC_CLOCK_FLAG_LOG_STATE_CHANGE
#define CLOCK_FLAG_LOG_FREQ_CHANGE            PUBLIC_CLOCK_FLAG_LOG_FREQ_CHANGE
#define CLOCK_FLAG_LOG_CONFIG_CHANGE          PUBLIC_CLOCK_FLAG_LOG_CONFIG_CHANGE
#define CLOCK_FLAG_LOG_RESET                  PUBLIC_CLOCK_FLAG_LOG_RESET
#define CLOCK_FLAG_LOG_SLEEP_CHANGE           PUBLIC_CLOCK_FLAG_LOG_SLEEP_CHANGE
// Reserved for future logging                PUBLIC_CLOCK_FLAG_RESERVED_0x00000020
// Reserved for future logging                PUBLIC_CLOCK_FLAG_RESERVED_0x00000040
// Reserved for future logging                PUBLIC_CLOCK_FLAG_RESERVED_0x00000080
#define CLOCK_FLAG_DO_NOT_DISABLE             PUBLIC_CLOCK_FLAG_RESERVED_0x00000100
#define CLOCK_FLAG_SUPPRESSIBLE               PUBLIC_CLOCK_FLAG_RESERVED_0x00000200
#define CLOCK_FLAG_DOMAIN_HOLD_VREG_REQUEST   PUBLIC_CLOCK_FLAG_RESERVED_0x00000400
#define CLOCK_FLAG_DOMAIN_DYNAMIC_CONFIG      PUBLIC_CLOCK_FLAG_RESERVED_0x00000800
#define CLOCK_FLAG_AUTOGATE                   PUBLIC_CLOCK_FLAG_RESERVED_0x00001000
#define CLOCK_FLAG_BIST_FAILURE_ANTICIPATED   PUBLIC_CLOCK_FLAG_RESERVED_0x00002000
#define CLOCK_FLAG_INTERNAL_CONTROL           PUBLIC_CLOCK_FLAG_RESERVED_0x00004000
#define CLOCK_FLAG_XO_VOTE                    PUBLIC_CLOCK_FLAG_RESERVED_0x00008000
#define CLOCK_FLAG_NO_REFERENCE_COUNTING      PUBLIC_CLOCK_FLAG_RESERVED_0x00010000
#define CLOCK_FLAG_BRANCH_ONLY_CONTROL        PUBLIC_CLOCK_FLAG_RESERVED_0x00020000
#define CLOCK_FLAG_SUPPRESS_VOLTAGE_CONTROL   PUBLIC_CLOCK_FLAG_RESERVED_0x00040000
#define CLOCK_FLAG_SUPPORTS_SLEWING           PUBLIC_CLOCK_FLAG_RESERVED_0x00080000
#define CLOCK_FLAG_SOURCE_CALIBRATED          PUBLIC_CLOCK_FLAG_RESERVED_0x00100000
#define CLOCK_FLAG_BYPASS_DEPENDENCIES        PUBLIC_CLOCK_FLAG_RESERVED_0x00200000
#define CLOCK_FLAG_LEAVE_ALWAYS_ON            PUBLIC_CLOCK_FLAG_RESERVED_0x00400000
#define CLOCK_FLAG_REPORT_CX_RAIL_UPDATES     PUBLIC_CLOCK_FLAG_RESERVED_0x00800000
#define CLOCK_FLAG_SOURCE_NOT_CONFIGURABLE    PUBLIC_CLOCK_FLAG_RESERVED_0x01000000
#define CLOCK_FLAG_STUB_HW_RUMI               PUBLIC_CLOCK_FLAG_RESERVED_0x02000000
#define CLOCK_FLAG_CPU_SOURCE_PLL             PUBLIC_CLOCK_FLAG_RESERVED_0x04000000

#define CLOCK_LOGGING_FLAGS               \
        (                                 \
          CLOCK_FLAG_LOG_STATE_CHANGE   | \
          CLOCK_FLAG_LOG_FREQ_CHANGE    | \
          CLOCK_FLAG_LOG_CONFIG_CHANGE  | \
          CLOCK_FLAG_LOG_RESET          | \
          CLOCK_FLAG_LOG_SLEEP_CHANGE     \
        )

/**
 * Global flag bits
 *
 * NOTE: These flags are to be used only in the nGlobalFlags
 * field of the driver context structure.
 *
 *  LOG_x_STATE_CHANGE - Enable logging of enable/disable
 *    calls to all clocks, sources, or power domains as
 *    specified by x.
 *  LOG_CLOCK_FREQ_CHANGE - Enable logging of frequency changes
 *    to all clocks.
 *  LOG_CLOCK_CONFIG_CHANGE - Enable logging of configuration
 *    changes to all clocks.
 *  LOG_CLOCK_RESET - Enable logging of resets to all clocks.
 *  LOG_VOLTAGE_CHANGE - Enable logging of vdd requirement changes.
 *  DO_NOT_DISABLE_x - Ignore requests to disable all clocks,
 *    sources, or power domains as specified by x.
 *  STUB_API - Stubs out entire API (DAL and NPA nodes expected).
 *  LOG_CLOCK_SLEEP_CHANGE - Enable logging of sleep state changes.
 *  BIST_IN_PROGRESS - Indicates that a Built-In Self Test is running.
 *  LOG_MISC_STATUS - Enable logging of miscellaneous status info.
 */
#define CLOCK_GLOBAL_FLAG_LOG_CLOCK_STATE_CHANGE          PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_STATE_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE           PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_CLOCK_CONFIG_CHANGE         PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_CONFIG_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_CLOCK_RESET                 PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_RESET
#define CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE         PUBLIC_CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_POWER_DOMAIN_STATE_CHANGE   PUBLIC_CLOCK_GLOBAL_FLAG_LOG_POWER_DOMAIN_STATE_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_VOLTAGE_CHANGE              PUBLIC_CLOCK_GLOBAL_FLAG_LOG_VOLTAGE_CHANGE
#define CLOCK_GLOBAL_FLAG_LOG_SOURCE_FREQ_CHANGE          PUBLIC_CLOCK_GLOBAL_FLAG_LOG_SOURCE_FREQ_CHANGE
#define CLOCK_GLOBAL_FLAG_DO_NOT_DISABLE_CLOCKS           PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000100
#define CLOCK_GLOBAL_FLAG_DO_NOT_DISABLE_SOURCES          PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000200
#define CLOCK_GLOBAL_FLAG_DO_NOT_DISABLE_POWER_DOMAINS    PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000400
#define CLOCK_GLOBAL_FLAG_STUB_API                        PUBLIC_CLOCK_GLOBAL_FLAG_RESERVED_0x00000800
#define CLOCK_GLOBAL_FLAG_LOG_CLOCK_SLEEP_CHANGE          PUBLIC_CLOCK_GLOBAL_FLAG_LOG_CLOCK_SLEEP_CHANGE
#define CLOCK_GLOBAL_FLAG_BIST_IN_PROGRESS                PUBLIC_CLOCK_GLOBAL_FLAG_BIST_IN_PROGRESS
#define CLOCK_GLOBAL_FLAG_CPU_TEST_IN_PROGRESS            PUBLIC_CLOCK_GLOBAL_FLAG_CPU_TEST_IN_PROGRESS
#define CLOCK_GLOBAL_FLAG_LOG_MISC_STATUS                 PUBLIC_CLOCK_GLOBAL_FLAG_LOG_MISC_STATUS

#define CLOCK_GLOBAL_LOGGING_FLAGS                          \
        (                                                   \
          CLOCK_GLOBAL_FLAG_LOG_CLOCK_STATE_CHANGE        | \
          CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE         | \
          CLOCK_GLOBAL_FLAG_LOG_CLOCK_CONFIG_CHANGE       | \
          CLOCK_GLOBAL_FLAG_LOG_CLOCK_RESET               | \
          CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE       | \
          CLOCK_GLOBAL_FLAG_LOG_POWER_DOMAIN_STATE_CHANGE | \
          CLOCK_GLOBAL_FLAG_LOG_VOLTAGE_CHANGE            | \
          CLOCK_GLOBAL_FLAG_LOG_SOURCE_FREQ_CHANGE        | \
          CLOCK_GLOBAL_FLAG_LOG_CLOCK_SLEEP_CHANGE        | \
          CLOCK_GLOBAL_FLAG_LOG_MISC_STATUS               | \
          CLOCK_GLOBAL_FLAG_BIST_IN_PROGRESS              | \
          CLOCK_GLOBAL_FLAG_CPU_TEST_IN_PROGRESS            \
        )

#define SOURCE_NAME(x)             \
  /* .eSource = */ HAL_CLK_SOURCE_ ## x, \
  /* .szName  = */ #x

/*
 * ClockVRegLevelType
 *
 * List of voltage levels that a client can request.  Note that the
 * enumeration values map to pmic NPA node request values.
 *
 *  OFF          - No vote
 *  RETENTION_MINUS - Lowered retention voltage level.
 *  RETENTION    - Retention voltage level.
 *  RETENTION_PLUS  - Elevated retention voltage level.
 *  LOW_MINUS    - Lowered low voltage level.
 *  LOW             - Low voltage level.
 *  LOW_PLUS        - Elevated low voltage level.
 *  NOMINAL_MINUS   - Lowered nominal voltage level.
 *  NOMINAL      - Nominal voltage level.
 *  NOMINAL_PLUS    - Elevated nominal voltage level.
 *  HIGH_MINUS      - Lowered high voltage level.
 *  HIGH            - High voltage level.
 *  HIGH_PLUS       - Elevated high voltage level.
 *  TURBO_MINUS     - Lowered turbo voltage level.
 *  TURBO           - Turbo voltage level.
 *  TURBO_PLUS      - Elevated turbo voltage level.
 */
typedef enum
{
  CLOCK_VREG_LEVEL_OFF          = HAL_CLK_VREG_LEVEL_OFF,
  CLOCK_VREG_LEVEL_RETENTION_MINUS  = HAL_CLK_VREG_LEVEL_RETENTION_MINUS,
  CLOCK_VREG_LEVEL_RETENTION    = HAL_CLK_VREG_LEVEL_RETENTION,
  CLOCK_VREG_LEVEL_RETENTION_PLUS   = HAL_CLK_VREG_LEVEL_RETENTION_PLUS,
  CLOCK_VREG_LEVEL_LOW_MINUS    = HAL_CLK_VREG_LEVEL_LOW_MINUS,
  CLOCK_VREG_LEVEL_LOW          = HAL_CLK_VREG_LEVEL_LOW,
  CLOCK_VREG_LEVEL_LOW_PLUS         = HAL_CLK_VREG_LEVEL_LOW_PLUS,
  CLOCK_VREG_LEVEL_NOMINAL_MINUS    = HAL_CLK_VREG_LEVEL_NOMINAL_MINUS,
  CLOCK_VREG_LEVEL_NOMINAL      = HAL_CLK_VREG_LEVEL_NOMINAL,
  CLOCK_VREG_LEVEL_NOMINAL_PLUS = HAL_CLK_VREG_LEVEL_NOMINAL_PLUS,
  CLOCK_VREG_LEVEL_HIGH_MINUS       = HAL_CLK_VREG_LEVEL_HIGH_MINUS,
  CLOCK_VREG_LEVEL_HIGH         = HAL_CLK_VREG_LEVEL_HIGH,
  CLOCK_VREG_LEVEL_HIGH_PLUS    = HAL_CLK_VREG_LEVEL_HIGH_PLUS,
  CLOCK_VREG_LEVEL_TURBO_MINUS      = HAL_CLK_VREG_LEVEL_TURBO_MINUS,
  CLOCK_VREG_LEVEL_TURBO            = HAL_CLK_VREG_LEVEL_TURBO,
  CLOCK_VREG_LEVEL_TURBO_PLUS       = HAL_CLK_VREG_LEVEL_TURBO_PLUS,

  CLOCK_VREG_MAX_LEVEL              = HAL_CLK_VREG_MAX_LEVEL,
  CLOCK_VREG_NUM_LEVELS         = HAL_CLK_VREG_NUM_LEVELS,
  CLOCK_BSP_ENUM_32BITS(VREG_LEVEL)
} ClockVRegLevelType;


/*
 * ClockHWVersionType;
 *
 * HW version information.
 *
 *  Min             - Minimum supported HW Major/Minor revision
 *  Max             - Maximum supported HW Major/Minor revision
 *                    '0xFF' indicates all versions.
 *  eChipInfoFamily - Chip this configuration is for. '0' indicates all chips.
 *  aeChipInfoId    - Array of chip id's that the configuration supports.
 *                    NULL indicates all chips.
 */
typedef struct
{
  struct
  {
    uint8 nMajor;
    uint8 nMinor;
  } Min;

  struct
  {
    uint8 nMajor;
    uint8 nMinor;
  } Max;

  DalChipInfoFamilyType    eChipInfoFamily;
  const DalChipInfoIdType *aeChipInfoId;

} ClockHWVersionType;


/*
 * ClockSourceFreqConfigType
 *
 * Frequency configuration information for a PLL.
 *
 *  nFreqHz     - Frequency in Hz for this configuration.
 *  HALConfig   - Configuration to pass to the HAL.
 *  eVRegLevel  - Voltage level for this configuration.
 *  HWVersion   - Version of the chip HW this configuration is for.
 *  bLastEntry  - Boolean indicator if this is the last entry.
 */
typedef struct
{
  uint32                nFreqHz;
  HAL_clk_PLLConfigType HALConfig;
  ClockVRegLevelType    eVRegLevel;
  ClockHWVersionType    HWVersion;
  boolean               bLastEntry;
} ClockSourceFreqConfigType;


/*
 * ClockSourceConfigType
 *
 * Configuration information for a PLL.
 *
 *  eSource           - Source ENUM value.
 *  szName            - Name of source.
 *  nConfigMask       - Mask of misc PLL configurations such as aux out,
 *                      bist out, early out, etc.
 *  pSourceFreqConfig - Pointer to array of source configurations.
 *  pCalibrationFreqConfig  - Pointer to the calibration configuration.
 *  eDisableMode            - PLL disable/enable mode.
 */
typedef struct
{
  HAL_clk_SourceType         eSource;
  const char                *szName;
  uint32                     nConfigMask;
  ClockSourceFreqConfigType *pSourceFreqConfig;
  ClockSourceFreqConfigType *pCalibrationFreqConfig;
  HAL_clk_SourceDisableModeType  eDisableMode;
} ClockSourceConfigType;


/*
 * ClockMuxConfigType
 *
 * Configuration information for a clock mux.
 *
 *  nFreqHz           - Frequency in Hz for this configuration.
 *  HALConfig         - Configuration to pass to the HAL.
 *  eVRegLevel        - Voltage level for this configuration.
 *  HWVersion         - Version of the chip HW this configuration is for.
 *  pSourceFreqConfig - Optional pointer to a PLL to configure for this.
 */
typedef struct
{
  uint32                     nFreqHz;
  HAL_clk_ClockMuxConfigType HALConfig;
  ClockVRegLevelType         eVRegLevel;
  ClockHWVersionType         HWVersion;
  ClockSourceFreqConfigType *pSourceFreqConfig;
} ClockMuxConfigType;


/*
 * ClockLogType
 *
 * Default configuration for the clock log.
 *
 *  nLogSize         - Log size in bytes.  Must be a power of 2.
 *  nGlobalLogFlags  - Global log flags.
 */
typedef struct
{
  uint32      nLogSize;
  uint32      nGlobalLogFlags;
} ClockLogType;


/*
 * ClockXOVoterType
 *
 * Structure to hold clocks which need to explicitly hold a source.
 */
typedef struct
{
  const char *szName;
} ClockXOVoterType;


/*
 * ClockPropertyValueType
 *
 * Generic clock property data.  Actual data type will depend on the property
 * and will not even necessarily be a pointer (i.e. could be straight uint32).
 */
typedef const void *ClockPropertyValueType;


/*
 * ClockPropertyType
 *
 * Generic clock property structure, the BSP data in non-DAL environments
 * will consist of an array of these.
 *
 *  szName - Name of the property
 *  Value  - Property value
 */
typedef struct
{
  const char            *szName;
  ClockPropertyValueType Value;
} ClockPropertyType;



/*
 * ClockAVSCoreCfgType
 *
 * BSP Data structure for describing delay synthesizer to CPU frequency
 * requirements.
 *
 * nDelaySynth    - The synthesizer value to program to the coprocessor.
 * nMinVdd        - The lowest voltage that AVS can set automatically at this frequency.
 * nPerfVdd       - The performance level associated voltage in uV.
 */
typedef struct
{
  uint32 nDelaySynth;
  uint32 nMinVdd;
  uint32 nPerfVdd;
}ClockAVSCoreFreqCfgType;


/*
 * ClockAVSCoreConfigType
 *
 * BSP Data structure for initializing an AVS core.
 *
 * nPhysicalBase    - The physical base address for this AVS core.
 * eCore            - The Core ID for this instance.
 * ePMIC            - The PMIC type for this core.
 * eStepSize        - The step size of voltage adjustment requests.
 * nVddRequestDelay - The delay between HW voltage requests.
 * nClockDiv        - The clock divider.
 * HWVersion        - The version of the chip HW this configuration is for.
 */
typedef struct
{
  uint32               nPhysicalBase;
  HAL_avs_CoreType     eCore;
  HAL_avs_PmicType     ePMIC;
  HAL_avs_StepSizeType eStepSize;
  uint32               nVddRequestDelay;
  uint32               nClockDiv;
  ClockHWVersionType   HWVersion;
}ClockAVSCoreConfigType;


/*
 * ClockFlagNodeType
 *
 * List of nodes that init flags can be applied to.
 *
 *  CLOCK        - Flags are to be applied to the specified clock.
 *  CLOCK_DOMAIN - Flags are to be applied to the specified domain.
 *  SOURCE       - Flags are to be applied to the specified source.
 *  POWER_DOMAIN - Flags are to be applied to the specified power domain.
 *
 */
typedef enum
{
  CLOCK_FLAG_NODE_TYPE_NONE          = 0,
  CLOCK_FLAG_NODE_TYPE_CLOCK         = 1,
  CLOCK_FLAG_NODE_TYPE_CLOCK_DOMAIN  = 2,
  CLOCK_FLAG_NODE_TYPE_SOURCE        = 3,
  CLOCK_FLAG_NODE_TYPE_POWER_DOMAIN  = 4,
  CLOCK_FLAG_NODE_TYPE_MAX_SUPPORTED = 5
} ClockFlagNodeType;


/*
 * ClockFlagInitType
 *
 * BSP Data structure for initializing the flags of an individual clock,
 * clock domain, power domain, or source.
 *
 *  eNodeType - The node to which the flags should be applied.
 *  id        - The ID to lookup this node info.
 *              (This type is dependent upon the eNodeType).
 *  nFlag   - Init value for the clock's flags.
 */
typedef struct
{
  ClockFlagNodeType  eNodeType;
  void              *pID;
  uint32             nFlag;
} ClockFlagInitType;


/*
 * ClockNameListType
 *
 * Generic type for lists consisting only of clock names.
 *
 * szName - Name of the clock in the list.
 */
typedef struct
{
  const char  *szName;
} ClockNameListType;


#endif  /* __CLOCKBSP_H__ */

