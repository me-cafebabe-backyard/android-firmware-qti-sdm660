/*-----------------------------------------------------------------------
   Copyright (c) 2015 QUALCOMM Technologies, Incorporated.
   All Rights Reserved.
   QUALCOMM Proprietary.
-----------------------------------------------------------------------*/

#ifndef SYSMON_DEVCFG_INT_H_
#define SYSMON_DEVCFG_INT_H_

#include "DALDeviceId.h"
#include "DDIChipInfo.h"
#include "DALSys.h"
#include "sysmon_global.h"

/** Sysmon device name in device configuration database  */
#define SYSMON_DEVCONFIG_DEVICE_NAME                  "/qdsp6/sysmon"

/** Device version management defines */
#define SD_HW_VER(nMinMajor, nMinMinor, nMaxMajor, nMaxMinor)               \
            ( ((nMinMajor<<24)& 0xFF000000) | ((nMinMinor<<16) & 0x00FF0000) | \
              ((nMaxMajor<<8) & 0x0000FF00) |  (nMaxMinor&0xFF) )

#define SD_HW_VER_MIN( nBSPVersion ) ( ((nBSPVersion & 0xFF000000)>>8) | \
                                        ((nBSPVersion & 0x00FF0000)>>16) )
#define SD_HW_VER_MAX( nBSPVersion ) ( ((nBSPVersion & 0x0000FF00)<<8) | \
                                         (nBSPVersion & 0x000000FF) )

/* Enum for corner voltage levels */
typedef enum
{
  SYSMON_CLOCK_VREG_LEVEL_OFF            = 0,
  SYSMON_CLOCK_VREG_LEVEL_RETENTION      = 1,
  SYSMON_CLOCK_VREG_LEVEL_RETENTION_PLUS = 2,
  SYSMON_CLOCK_VREG_LEVEL_LOW_MIN        = 3,
  SYSMON_CLOCK_VREG_LEVEL_LOW_MINUS      = 4,
  SYSMON_CLOCK_VREG_LEVEL_LOW            = 5,
  SYSMON_CLOCK_VREG_LEVEL_LOW_PLUS       = 6,
  SYSMON_CLOCK_VREG_LEVEL_NOMINAL        = 7,
  SYSMON_CLOCK_VREG_LEVEL_NOMINAL_PLUS   = 8,
  SYSMON_CLOCK_VREG_LEVEL_HIGH           = 9,
  SYSMON_CLOCK_VREG_NUM_LEVELS,
}sd_vreg_type_t;

/* Structure type for device version database */
typedef struct{
    DalChipInfoVersionType nChipVersion;
    DalChipInfoFamilyType eChipInfoFamily;
    const DalChipInfoIdType *aeChipInfoId;
}sd_hw_version_type_t;

/* Structure type for bus clock table elements */
typedef struct{
    uint32_t freqKHz;                   //frequency in KiloHertz
    sd_vreg_type_t vRegLevel;           //Voltage corner for this perf level
    sd_hw_version_type_t hwVersion;    //HW versions supporting this perf level
}sd_devcfg_bus_clk_table_t;

/* Structure type for bus clock descriptor */
typedef struct{
    uint32_t numLevels;                    //Number of perf levels in the table
    sd_devcfg_bus_clk_table_t* tablePtr;    //bus clock table pointer
}sd_devcfg_bus_clk_desc_t;

/* Structure type for core clock table elements */
typedef struct{
    uint32_t freqKHz;                   //frequency in KiloHertz
    sd_vreg_type_t vRegLevel;           //Voltage corner for this perf level
    sd_hw_version_type_t hwVersion;     //HW versions supporting this perf level
}sd_devcfg_core_clk_table_t;

/* Structure type for core clock descriptor */
typedef struct{
    uint32_t numLevels;                     //Number of perf levels in the table
    sd_devcfg_core_clk_table_t* tablePtr;   //core clock table pointer
}sd_devcfg_core_clk_desc_t;

/* Structure for DCVS configurable parameters */
typedef struct {
    uint32_t dcvsTransientDur;
    uint32_t dcvsTransientDurMax;
    uint32_t q6LoadSafe;
    uint32_t q6LoadDanger;
    uint32_t q6Load1TSafe;
    uint32_t lowerCoreQ6Load;
    uint32_t lowerCoreQ6LoadAdj;
    uint32_t lowerCoreQ6LoadMin;
    uint32_t lowerCoreWinDur;
    uint32_t lowerCoreWinHFW;
    uint32_t lowerCoreWinDurAdj;
    uint32_t lowerCoreWinDurMax;
    uint32_t lowerBusWinDur;
    uint32_t lowerBusWinHFW;
    uint32_t pCppDangerLevel;
    uint32_t pCppSafeLevel;
    uint32_t coreStallsDangerLevel;
	uint32_t pCppSafe1TLevel;
} sd_devcfg_dcvs_params_t;

/** @struct sd_core_clk_table_t
 *  @brief Core clock table element structure type */
typedef struct{
    uint32_t freqKHz;
    /**< frequency in kiloHertz */

    sd_vreg_type_t vRegLevel;
    /**< corner voltage level */

    uint32_t maxFreqKHz;
    /**< maximum frequency at this corner */

    uint32_t prevMaxFreqKHz;
    /**< maximum frequency of previous corner */
}sd_core_clk_table_t;

/** @struct sd_core_clk_desc_t
 *  @brief Structure type for core clock descriptor */
typedef struct{
    uint32_t numPerfLevels;
    /**< number of performance levels present in core clock table */

    uint32_t currPerfLevel;
    /**< index into the core clock table for current clock */

    sd_core_clk_table_t* core_clk_table;
    /**< pointer to core clock table */
}sd_core_clk_desc_t;

/** @struct sd_bus_clk_table_t
 *  @brief bus clock table element structure type */
typedef struct{
    uint32_t freqKHz;
    /**< frequency in KiloHertz */

    sd_vreg_type_t vRegLevel;
    /**< corner voltage level */
}sd_bus_clk_table_t;

/** @struct sd_bus_clk_desc_t
 *  @brief Structure type for bus clock descriptor */
typedef struct{
    uint32_t numPerfLevels;
    /**< number of performance levels present in bus clock table */

    uint32_t currPerfLevel;
    /**< index into the bus clock table for current clock */

    uint32_t currFreqKHz;
    /**< Current frequency in kHz */

    sd_bus_clk_table_t* bus_clk_table;
    /**< pointer to bus clock table */

    uint32_t maxNominalFreqKHz;
    /**< Maximum clock frequency at NOMINAL votage level */
}sd_bus_clk_desc_t;

/** @struct sd_hvx_rm_descriptor_t */
typedef struct {
    unsigned char resThresPerc;
    uint32_t tryLockTimeout;
    uint32_t lockTimeout;
    uint32_t obsWinDur;
}sd_hvx_rm_descriptor_t;

/* structure definition for global sysmon device config data */
typedef struct{
    /* Device version information from DAL */
    DalChipInfoFamilyType nChipFamily;
    DalChipInfoIdType nChipId;
    DalChipInfoVersionType nChipVersion;
    /* Clock table descriptors */
    sd_devcfg_bus_clk_desc_t* devCfgBusClkDesc;
    sd_devcfg_core_clk_desc_t* devCfgCoreClkDesc;
    sd_core_clk_desc_t core_clk_desc;
    sd_bus_clk_desc_t bus_clk_desc;
    /**< bus clock descriptor structure */
    uint32_t bwPrefetchMissFact;
    uint32_t bwDemandMissFact;
    uint32_t bwWriteMissFact;
    uint32_t bwCoprocMissFact;
    uint32_t bwOverallFact;
    uint32_t bCoreToSNOC;
    uint32_t axiBusWidth;
    uint32_t npaBusClkMult;
    uint32_t hfwAvgWinAud;
    uint32_t hfwAvgWinNonAud;
    uint32_t bwPeaksWindow;
    uint32_t bwPeaksMax;
    uint32_t bwPeaksWindowCompute;
    uint32_t bwPeaksMaxCompute;
    sd_devcfg_dcvs_params_t* dcvsBalancedParams;
    sd_devcfg_dcvs_params_t* dcvsPowerSaverParams;
    sd_devcfg_dcvs_params_t* dcvsPowerSaverAggressiveParams;
    sd_devcfg_dcvs_params_t* dcvsPerformanceParams;
    sd_devcfg_dcvs_params_t* dcvsParams;
    sd_vreg_type_t* dcvsClientCoreCornerConv;
    sd_vreg_type_t* dcvsClientBusCornerConv;
    /* HVX resource manager structure */
    unsigned char hvxRMEnable;
    sd_hvx_rm_descriptor_t* hvxRMDes;
}sysmon_devcfg_struct_t;

/**************************************************************************//**
 * @fn sysmon_devcfg_init
 *
 * @brief SysMon device configuration init function. Initializes device
 *        interface and reads the configuration parameters
 *
 * @return @a SYSMON_SUCCESS - for success
 * @return @a SYSMON_FAILURE - for failure
 *****************************************************************************/
SYSMON_RETURN sysmon_devcfg_init(void);

/**************************************************************************//**
 *  @fn sysmon_devcfg_npa_coreClkUpdate
 *
 *  @brief Updates core clock perf index in sysmon dcvs structure.
 *
 *      Search the core clock table for the provided frequency and update
 *      DCVS core clock performance index.
 *
 *  @note To be called only from sysmon internally whenever there is a change
 *  in the event of ADSP core clock change.
 *
 *  @param freqkHz current core clock frequency in kHz.
 *
 *  @return @a SYSMON_SUCCESS for success
 *  @return @a SYSMON_FAILURE for failure
 *****************************************************************************/
SYSMON_RETURN sysmon_devcfg_npa_coreClkUpdate(uint32_t freqkHz);

/**************************************************************************//**
 *  @fn sysmon_devcfg_npa_busClkUpdate
 *
 *  @brief Updates the current performance level (index to the bus clock
 *         table generated from NPA/Device configuration)
 *
 *  Search the bus clock table for the provided frequency vote from NPA and
 *  updates DCVS bus clock performance index.
 *
 *  @note To be called only from sysmon internally whenever there is a change
 *  in the event of ADSP bus clock vote change.
 *
 *  @param freqkHz current bus clock frequency vote in kHz.
 *
 *  @return @a SYSMON_SUCCESS for success
 *  @return @a SYSMON_FAILURE for failure
 *****************************************************************************/
SYSMON_RETURN sysmon_devcfg_npa_busClkUpdate(uint32_t freqkHz);

/**************************************************************************//**
 * @fn sysmon_devcfg_findBusClkEntry
 *
 * @brief Searches the bus clock table for the nearest entry which can
 *        support the provided frequency (freqKHz) and returns the
 *        matching entry's index to the caller.
 *        In case, clock table is not populated OR if the search fails
 *        to find any suitable entry in the clock table, it returns '-1'
 *
 * @param freqKHz bus Frequency vote in KHz
 *
 * @note  Caller should check for the return value to see if the search
 *        is successful (return value other than '-1')
 *****************************************************************************/
int sysmon_devcfg_findBusClkEntry(uint32_t freqKHz);

/**************************************************************************//**
 * @fn sysmon_devcfg_findCoreClkEntry
 *
 * @brief Returns index of the provided frequency in core clock descriptor
 *        table.
 *
 * @param freqKHz core clock frequency in kilo-hertz
 *
 * @return Index into the device configuration clock table on success
 * @return '-1' on failure
 *****************************************************************************/
int sysmon_devcfg_findCoreClkEntry(uint32_t freqKHz);

/**************************************************************************//**
 * @fn sysmon_devcfg_coreClkAtIndex
 *
 * @brief Returns the clock frequency from the table at given index
 *
 * @param index index into the clock frequency table
 *
 * @return uint32_t frequency in kilo-hertz
 * @return 0 on failure
 *****************************************************************************/
uint32_t sysmon_devcfg_coreClkAtIndex(uint32_t index);

/**************************************************************************//**
 * @fn sysmon_devcfg_busClkAtIndex
 *
 * @brief Returns the clock frequency from the table at given index
 *
 * @param index index into the clock frequency table
 *
 * @return uint32_t frequency in kilo-hertz
 * @return 0 on failure
 *****************************************************************************/
uint32_t sysmon_devcfg_busClkAtIndex(uint32_t index);

/**************************************************************************//**
 * @fn sysmon_devcfg_coreClkCornerAtIndex
 *
 * @brief Returns the voltage corner for the frequency at given index
 *
 * @param index index into the clock frequency table
 *
 * @return sd_vreg_type_t Corner voltage
 * @return SYSMON_CLOCK_VREG_NUM_LEVELS on failure
 *****************************************************************************/
sd_vreg_type_t sysmon_devcfg_coreClkCornerAtIndex(uint32_t index);

/**************************************************************************//**
 * @fn sysmon_devcfg_busClkCornerAtIndex
 *
 * @brief Returns the voltage corner for the frequency at given index
 *
 * @param index index into the clock frequency table
 *
 * @return sd_vreg_type_t Corner voltage
 * @return SYSMON_CLOCK_VREG_NUM_LEVELS on failure
 *****************************************************************************/
sd_vreg_type_t sysmon_devcfg_busClkCornerAtIndex(uint32_t index);

/**************************************************************************//**
 * @fn sysmon_devcfg_npa_coreClkCornerQuery
 *
 * @brief Returns the corner voltage for the current core clock frequency
 *
 * @return uint32_t Corner voltage (enum: sd_vreg_type_t)
 *****************************************************************************/
sd_vreg_type_t sysmon_devcfg_npa_coreClkCornerQuery();

/**************************************************************************//**
 * @fn sysmon_devcfg_npa_busClkCornerQuery
 *
 * @brief Returns the corner voltage for the current bus clock frequency
 *
 * @return uint32_t Corner voltage (enum: sd_vreg_type_t)
 *****************************************************************************/
sd_vreg_type_t sysmon_devcfg_npa_busClkCornerQuery();

/**************************************************************************//**
 * @fn sysmon_devcfg_npa_busClkFreqQuery
 *
 * @brief Returns the current bus clock frequency vote
 *
 * @return uint32_t frequency in kilo-hertz
 *****************************************************************************/
uint32_t sysmon_devcfg_npa_busClkFreqQuery();

#endif /* SYSMON_DEVCFG_INT_H_ */
