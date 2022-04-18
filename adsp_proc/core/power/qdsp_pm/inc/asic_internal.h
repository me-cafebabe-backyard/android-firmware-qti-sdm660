/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: asic_internal.h
@brief: Contains internal Asic Config Manager's definitions.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/inc/asic_internal.h#1 $
*/

#ifndef ASIC_INTERNAL_H_
#define ASIC_INTERNAL_H_

#include "asic.h"


#define ASIC_CONFIG_DEVICE_NAME "/core/power/adsppm"

typedef struct
{
    const int numElements;
    const AsicCoreDescType *pCores;
} AsicCoreDescriptorArrayType;

typedef struct
{
    int numElements;
    AsicMemDescriptorFullType pMemories[Adsppm_Mem_Max];
} AsicMemDescriptorFullArrayType;

typedef struct
{
    const int numElements;
    const AsicMemDescriptorType *pPwrDomainDesc;
} AsicMemDescriptorArrayType;

typedef struct
{
    const int numElements;
    const AsicClkDescriptorType *pClocks;
} AsicClockDescriptorArrayType;

typedef struct
{
    const int numElements;
    const AsicBusPortDescriptorType *pPorts;
} AsicBusPortDescriptorArrayType;

typedef struct
{
    const int numElements;
    const AdsppmBusRouteType *pRoutes;
} AsicBusRouteArrayType;

typedef struct
{
    const int numElements;
    const uint64 *pRegProgSpeeds;
} AsicRegProgSpeedArrayType;

typedef struct
{
    const int numElements;
    const AsicPowerDomainDescriptorType *pPwrDomains;
} AsicPwrDescriptorArrayType;

typedef struct
{
    const int numElements;
    const AsicCompensatedDdrBwTableEntryType *pRows;
} AsicCompensatedDdrBwTableType;

typedef struct
{
    uint64 bwThreshold;         // honest BW threshold (bytes/sec)
    uint64 bwVote;              // compensated Vote (bytes/sec)
} AsicCompensatedAhbBwTableEntryType;

typedef struct
{
    const int numElements;
    const AsicCompensatedAhbBwTableEntryType *pRows;
} AsicCompensatedAhbBwTableType;

typedef struct
{
    // Concurrency is considered active if the number of ADSP->DDR BW voters
    // is greather than this threshold
    uint32 adspDdrConcurrencyVotersThreshold;
    // Ab DDR BW threshold value
    uint64 adspDdrCompensatedBWThreshold;
    // The factor to be applied to ADSP->DDR BW votes when concurrency is
    // active. This value will be divided by 256.
    uint32 adspDdrConcurrencyFactorArray[3];
} AsicBwConcurrencySettingsType;

typedef struct
{
    uint32 oneThreadActive;
    uint32 twoThreadActive;
    uint32 threeThreadActive;
    uint32 fourThreadActive;
} AsicThreadLoadingInfoType;

typedef struct
{
    const int numElements;
    const AsicThreadLoadingInfoType *pRows;
} AsicThreadLoadingInfoTableType;

typedef struct
{
    const int numElements;
    const uint32 *pData;
} AsicAudioVoiceCppTrendFactorsType;

typedef struct
{
    uint32 adspFreqHz;  // threshold for ADSP frequency
    uint32 ahbeFreqHz;  // corresponding AHBE frequency when <= ADSP threshold
} AsicAdspToAhbeFreqTableEntry;

typedef struct
{
    uint32 cachesize;  // current cache size
    uint32 scalingfactor;  // corresponding fudging factor
} AsicAdspCacheSizeBWScalingTableEntry;

typedef struct
{
    const int numElements;
    const AsicAdspCacheSizeBWScalingTableEntry *pRows;
} AsicAdspCacheSizeBWScalingTableType;


typedef struct
{
    const int numElements;
    const AsicAdspToAhbeFreqTableEntry *pRows;
} AsicAdspToAhbeFreqTableType;

/**
 * Enumeration to indicate function set used for this chip
 */
typedef enum
{
    AsicFnSetId_Default = 0 //!< AsicFnID_Default
} AsicFnSetIdType;

typedef struct
{
    MmpmClientClassType clientClass;  // client class
    uint32 mppsThreshold;  // corresponding mpps threshold
} AsicAdspCacheSizeMPPSThresholdTableEntry;

typedef struct
{
    const int numElements;
    const AsicAdspCacheSizeMPPSThresholdTableEntry *pRows;
} AsicAdspCacheSizeMPPSThresholdTableType;


typedef struct
{
    AsicFnSetIdType functionSet;
    uint32  debugLevel;
    uint32  adspHwThreadNumber;
    uint64  adsppmLprTimeoutValue; //!< LPR timeout value in QTimer ticks (19.2Mhz)
    uint32  chipVersion;
    AsicHwioRegRangeType *lpassRegRange; //!< Register range for LPASS
    AsicHwioRegRangeType *l2ConfigRegRange; //!< Register range for L2 config
    AsicCoreDescriptorArrayType *cores;
    AsicMemDescriptorFullArrayType memories;
    AsicClockDescriptorArrayType *clocks;
    AsicBusPortDescriptorArrayType *busPorts;
    AsicBusRouteArrayType *extBusRoutes;
    AsicBusRouteArrayType *mipsBusRoutes;
    AsicRegProgSpeedArrayType *regProgSpeeds;
    AsicPwrDescriptorArrayType *pwrDomains;
    AsicCompensatedDdrBwTableType *compensatedDdrBwTable;
    AsicCompensatedAhbBwTableType *compensatedAhbBwTable;
    AsicThreadLoadingInfoTableType *threadLoadingInfoTable;
    AsicAudioVoiceCppTrendFactorsType *audioVoiceCppFactors;
    AsicCachePartitionConfigTableType *cachePartitionConfigTable;
    AsicBwConcurrencySettingsType* bwConcurrencySettings;
    AsicAdspToAhbeFreqTableType* adspToAhbeFreqTable;
    AsicAdspCacheSizeMPPSThresholdTableType *cachesizeMPPSThresholdTable;
    AsicAdspCacheSizeBWScalingTableType*  cacheSizeBWscalingTable;	
    Adsppm_Status (*pFn_GetBWFromMips)(AdsppmMIPSToBWAggregateType *pMipsAggregateData);
    Adsppm_Status (*pFn_GetClockFromMips)(AdsppmMIPSToClockAggregateType *pMipsAggregateData);
    Adsppm_Status (*pFn_GetClockFromBW)(uint32 *pClocks, AdsppmBusBWDataIbAbType *pAHBBwData);
    Adsppm_Status (*pFn_BusBWAggregate)(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue);
    AsicFeatureDescType features[AsicFeatureId_enum_max]; //!< Feature enablement status
} AsicConfigType;

typedef struct
{
    uint32 numClients;
    uint32 factor;
} AsicFactorType;

/**
 * @fn asicGetAsicConfig - fill in ASIC configuration from Device Config image
 * @param pConfig - [OUT] pointer to ASIC configuration structure
 * @return completion status
 */
Adsppm_Status asicGetAsicConfig(AsicConfigType *pConfig);


#endif /* ASIC_INTERNAL_H_ */

