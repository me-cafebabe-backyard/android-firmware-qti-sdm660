/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: asic.h
@brief: ASIC Configuration manager's header file
        This file contains ASIC Configuration Manager specific declarations
        exposed to all components within ADSPPM.
        The header will not be exposed outside of ADSPPM.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/inc/asic.h#1 $
*/

#ifndef ASIC_H_
#define ASIC_H_

#include "adsppm.h"
#include "icbarb.h"
#include "DDIIPCInt.h"
#include "mmpm.h"
#include "qurt_memory.h"


/**
 * Default log level set for ADSPPM code
 * Note: overridden by device config value
 */
#define ADSPPM_LOG_LEVEL ADSPPM_LOG_LEVEL_DEBUG

/**
 * Number of HW threads
 * Note: overridden by device config value
 */
#define ADSP_HW_THREAD_NUMBER_DEFAULT 3

/**
 * Default delay for overhang requests in QTImer ticks.
 * Corresponds to 5ms
 */
#define ADSPPM_LPR_VOTE_TIMEOUT_DEFAULT 96000

#define ADSPPM_BW_USAGE_FACTOR  (256)

#define PERCENTS_IN_A_WHOLE  (256)


#define NPA_SCHEDULER_NODE_NAME "/init/npa_scheduled_requests"


/******************************************************************************************/
/*               ASIC Config Mgr type definitions                                         */
/******************************************************************************************/
/**
 * @enum AsicHwRscIdType - defines HW resources, which will be controlled by resource managers.
 * The values can be combined in a bitmap
 */
typedef enum
{
    AsicRsc_None        = 0x0,
    AsicRsc_Power_Mem   = 0x1,
    AsicRsc_Power_ADSP  = 0x2,
    AsicRsc_Power_Core  = 0x4,
    AsicRsc_MIPS_Clk    = 0x8,
    AsicRsc_MIPS_BW     = 0x10,
    AsicRsc_BW_Internal = 0x20,
    AsicRsc_BW_External = 0x40,
    AsicRsc_Core_Clk    = 0x80,
    AsicRsc_Latency     = 0x100,
    AsicRsc_Thermal     = 0x200,
    AsicRsc_Power_Ocmem = 0x400,
    AsicRsc_Power_Hvx   = 0x800,
    AsicRsc_EnumForce32bit = 0x7fffffff  //!< Forcing enum to be 32 bit
} AsicHwRscIdType;

/**
 * Type definition for Aggregation function pointer
 * @param pInputData - [IN] pointer to resource-specific list of the requests
 * @param pOutputData - [OUT] pointer to resource-specific value to return aggregation results
 */
typedef void (*Asic_Rsc_AggregationFnType)(void *pInputData, void *pOutputData);

/*************************************************************************************************/
/*                            Clock definitions                                                  */
/*************************************************************************************************/
/**
 * @enum AsicClkTypeType - defines how a particular clock is exposed by ClkRegime
 */
typedef enum
{
    AsicClk_TypeNone = 0,
    AsicClk_TypeNpa,          //!< Clock exposed as an NPA node
    AsicClk_TypeDalFreqSet,   //!< Clock exposed through DALSys and allows to set frequency
    AsicClk_TypeDalEnable,    //!< Clock exposed through DALSys and only allows to enable/disable it
    AsicClk_TypeInternalCGC,  //!< Clock is enable/disable type and controlled by ADSPPM internally
                                //!< Internal CGC's are physically inside LPASS Core
                                //!< Thus control interface is not provided by Clock driver
    AsicClk_TypeCBC,          //!< Some Internal CGCs have a matching CBC in LCC
                                //!< Both need to be enabled to enable clock branch
                                //!< Clock exposed through DALSys and only allows to enable/disable it
                                //!< These type was added to avoid double enable/disable calls at init
                                //!< To be enabled/disabled based on calls to the matching CGC
    AsicClk_TypeDalDomainSrc
} AsicClkTypeType;

/**
 * @enum AsicClkCntlTypeType - defines how a particular clock is controlled
 */
typedef enum
{
    AsicClk_CntlNone = 0,
    AsicClk_CntlOff,          //!< Clock is set to OFF at init time and never turned ON
    AsicClk_CntlAlwaysON,     //!< Clock is set to ON at init time and never turned OFF
    AsicClk_CntlAlwaysON_DCG, //!< If DCG feature is enabled set clock to HW control,
                                //!< else, treat it as a AsicClk_CntlAlwaysON clock
    AsicClk_CntlSW,           //!< Clock is SW clock gated based on client requests
    AsicClk_CntlSW_DCG        //!< If DCG feature is enabled set clock to HW control,
                                //!< else, treat it as a AsicClk_CntlSW clock
} AsicClkCntlTypeType;

/**
 * @enum AsicClkMemRetentionType - defines how a memory core for particular clock is controlled
 */
typedef enum
{
    AsicClk_MemCntlNone = 0,
    AsicClk_MemCntlAlwaysRetain, //!< Memory core for this clock should be always retained.
} AsicClkMemRetentionType;

typedef struct
{
    uint32 baseAddr;
    uint32 physAddr;
    uint32 size;
} AsicHwioRegRangeType;

/**
 * @struct AsicClkHwIoInfoType - defines info structure storing register level information about HWIO type clocks
 */
typedef struct
{
    uint32 regOffset;  //!< CGC register address offset
    uint32 enableMask; //!< Mask for the enable field
    uint32 hwctlMask;  //!< Mask for HW control field
    uint32 stateMask;  //!< Mask for clock state field. If 0 - state check is skipped
} AsicClkHwIoInfoType;

/**
 * @struct AsicClkDesctiptorType - defines a descriptor for a particular clock.
 * The descriptor will be used by ClkRegime Wrapper to determine proper handling
 * of the requests for a particular clock.
 */
typedef struct
{
    AdsppmClkIdType clkId;                  //!< Internal ADSPPM Clock Id
    AsicClkTypeType clkType;                //!< Type of the clock as exposed by ClkRegime
    AsicClkCntlTypeType clkCntlType;        //!< Type of clock control scheme
    AsicClkMemRetentionType clkMemCntlType; //!< How memory core is controlled
    union
    {
        AsicClkHwIoInfoType hwioInfo;          //!< Register information for HWIO type clocks
        char clkName[MAX_ADSPPM_CLIENT_NAME]; //!< Name of the clock as exposed by ClkRegime
    } clkInfo;
    AdsppmClkIdType clkSrcId;               //!< Clock Id for frequency setting if the clock is enable/disable only
    AdsppmMemIdType memoryId;               //!< Memory ID if the clock is sourcing memory
} AsicClkDescriptorType;

/**
 * @struct AsicClockArrayType - defines a generic structure wchich members are a
 * pointer to an array of clock Ids and the number of clock IDs in it.
 */
typedef struct
{
    const uint32 numClocks;
    const AdsppmClkIdType *pClocks;
} AsicClockArrayType;

/*************************************************************************************************/
/*                            Bus definitions                                                    */
/*************************************************************************************************/
typedef struct
{
    AdsppmBusPortIdType adsppmMaster;
    ICBId_MasterType  icbarbMaster;
} AsicBusExtMasterType;

typedef struct
{
    AdsppmBusPortIdType adsppmSlave;
    ICBId_SlaveType  icbarbSlave;
} AsicBusExtSlaveType;

typedef struct
{
    AsicBusExtMasterType masterPort;
    AsicBusExtSlaveType slavePort;
} AsicBusExtRouteType;

/**
 * @enum AsicBusPortConnectionType - specifies which of the buses the port is
 * connected to. The enum is a bitmap and the values can be combined together
 * if an endpoint has more than one connection.
 */
typedef enum
{
    AsicBusPort_None = 0,
    AsicBusPort_AhbE_M = 0x1,     //!< Master on AHB-E
    AsicBusPort_AhbE_S = 0x2,     //!< Slave on AHB-E
    AsicBusPort_AhbI_M = 0x4,     //!< Master on AHB-I
    AsicBusPort_AhbI_S = 0x8,     //!< Slave on AHB-I
    AsicBusPort_AhbX_M = 0x10,    //!< Master on AHB-X
    AsicBusPort_AhbX_S = 0x20,    //!< Slave on AHB-X
    AsicBusPort_Ahb_Any = 0x3F,   //!< Any connection on AHB
    AsicBusPort_Ext_M = 0x40,     //!< External Master
    AsicBusPort_Ext_S = 0x80,     //!< External Slave
    AsicBusPort_Ext_Any = 0xC0,   //!< Any external connection
    AsicBusPort_Any = 0xFF
} AsicBusPortConnectionType;

/**
 * @struct AsicBusPortDescriptorType - Bus port descriptor defining connections of the port and corresponding controls.
 */
typedef struct
{
    AdsppmBusPortIdType port;
    AsicBusPortConnectionType portConnection; //!< Defines a bitmap of port connections to the buses
    AdsppmClkIdType busClk;                   //!< Bus clock for the port. Applicable only for AHB connected ports
    AsicClockArrayType regProgClocks;         //!< Ponter to array of clocks for register programming
    union
    {
        ICBId_MasterType icbarbMaster;        //!< ICBArb master definition for the port. Applicable only for external master connections
        ICBId_SlaveType  icbarbSlave;         //!< ICBArb slave definition for the port. Applicable only for external slave connections
    } icbarbId;                               //!< Descriptor for the port.  ICB definitions for external ports and for NOC port for internal ones
    AdsppmBusPortIdType accessPort;           //!< Access port. Port used to access from/to external NOC
} AsicBusPortDescriptorType;

/**
 * @struct AsicBusPortArrayType - defines a generic structure wchich members are a
 * pointer to an array of bus port Ids and the number of bus port IDs in it.
 */
typedef struct
{
    const uint32 numBusPorts;
    const AdsppmBusPortIdType *pBusPorts;
} AsicBusPortArrayType;

typedef struct
{
    uint64 bwThreshold;         // Honest BW threshold (bytes/sec)
    uint64 bwVote;              // Compensated Vote(bytes/sec), -1 means use honest vote
    uint32 latencyVote;         // latency in (nanoSec), 0 means no latency vote needed
    uint32 snocFloorVoteMhz;    // snoc Floor Vote from ADSPPM (Mhz)
    uint32 honestFlag;          // Flag indicating Honest/dishonest voting
} AsicCompensatedDdrBwTableEntryType;

/*************************************************************************************************/
/*                            Power definitions                                                  */
/*************************************************************************************************/
typedef enum
{
    AsicPowerDomain_AON = 0,       //!< Always On
    AsicPowerDomain_Adsp = 1,      //!< ADSP (Q6SS) Power Island
    AsicPowerDomain_LpassCore = 2, //!< LPASS Core Power Island
    AsicPowerDomain_Lpm = 3,       //!< LPM memory core
    AsicPowerDomain_SRam = 4,      //!< Sensors RAM Memory core
    AsicPowerDomain_Ocmem = 5,     //!< OCMEM
    AsicPowerDomain_Hvx = 6,       //!< HVX
    AsicPowerDomain_EnumMax
} AsicPowerDomainType;

typedef struct
{
    AsicPowerDomainType pwrDomain;
    char pwrDomainName[MAX_ADSPPM_CLIENT_NAME];
    AsicHwRscIdType pwrDomainType;
    AdsppmClkIdType clkId;
    DalIPCIntInterruptType intrReinitTrigger;   //!< Interrupt Id to trigger re-initialization (TZ) after power up
    uint32 intrReinitDone;                      //!< Interrupt Id acknowledging re-init (TZ) completion after power up
    AsicClockArrayType securityClocks;          //!< Pointer to the array of security clocks for the domain
} AsicPowerDomainDescriptorType;

/*************************************************************************************************/
/*                            Core definitions                                                   */
/*************************************************************************************************/
/**
 * @struct AsicCoreDescType - Defines entry in the ASIC config table defining Core Descriptor
 */
typedef struct
{
    AdsppmCoreIdType coreId;
    AsicHwRscIdType hwResourceId[Adsppm_Rsc_Id_Max]; //!< Array of HW Resource Ids by Resource Id
    AsicPowerDomainType pwrDomain;
    AsicClockArrayType coreClockInstances;
    AsicBusPortArrayType masterBusPortInstances;
    AsicBusPortArrayType slaveBusPortInstances;
    AdsppmInstanceIdType numInstances;
    //TODO: include aggregation function pointer here?
    //Asic_Rsc_AggregationFnType aggregateFn;
} AsicCoreDescType;

/*************************************************************************************************/
/*                            Memory type definitions                                            */
/*************************************************************************************************/
typedef struct
{
    uint64 startAddr; //!< Start address
    uint32 size;      //!< memory range size
} AsicAddressRangeType;

/**
 * @struct AsicMemDescriptorType - Defines entry in the ASIC config table defining Memory Descriptor
 */
typedef struct
{
    AdsppmMemIdType memId;
    AsicPowerDomainType pwrDomain;
} AsicMemDescriptorType;

/**
 * @struct AsicMemDescFullType - Defines entry in the ASIC config table defining Memory Descriptor
 */
typedef struct
{
    const AsicMemDescriptorType *pDescriptor; //!< pointer to memory descriptor
    AsicAddressRangeType virtAddr;            //!< virtual address range
} AsicMemDescriptorFullType;

/*****************************************************************************/
/*                  Cache partitioning configuration definitions             */
/*****************************************************************************/

typedef struct
{
    MmpmClientClassType aggregateClass;
    qurt_cache_partition_size_t mainPartSize;
} AsicCachePartitionConfigType;

typedef struct
{
    const uint32 numEntries;
    const AsicCachePartitionConfigType* pConfigEntries;
} AsicCachePartitionConfigTableType;

typedef struct
{
    uint32 floorFudgeFactor;
    uint32 ceilingFudgeFactor;
} AsicCompensatedBWFudgeFactor;


/******************************************************************************************/
/*                            Feature definitions                                         */
/******************************************************************************************/
typedef enum
{
    AsicFeatureId_Adsp_Clock_Scaling,
    AsicFeatureId_Adsp_LowTemp_Voltage_Restriction,
    AsicFeatureId_Adsp_PC,
    AsicFeatureId_Ahb_Scaling,
    AsicFeatureId_Ahb_Sw_CG,
    AsicFeatureId_Ahb_DCG,
    AsicFeatureId_LpassCore_PC,
    AsicFeatureId_LpassCore_PC_TZ_Handshake,
    AsicFeatureId_Bus_Scaling,
    AsicFeatureId_CoreClk_Scaling,           //!< Feature to control core clocks. If disabled the clocks will be forced to max
    AsicFeatureId_Min_Adsp_BW_Vote,          //!< Feature to issue min ext BW vote to support min MIPS
    AsicFeatureId_InitialState,              //!< Feature to set up initial state during init. If enabled ADSPPM will bring down all resources to the min state
    AsicFeatureId_TimelineOptimisationMips,  //!< Feature to enable MIPS vote optimization for periodic clients
    AsicFeatureId_TimelineOptimisationBw,    //!< Feature to enable BW vote optimization for periodic clients
    AsicFeatureId_TimelineOptimisationAhb,   //!< Feature to enable AHB clock optimization for periodic clients
    AsicFeatureId_LpassClkSleepOptimization, //!< Feature to enable gating of some of the LPASS clocks when Q6 is going into sleep
    AsicFeatureId_LPMRetention,              //!< Feature to control LPM retention
    AsicFeatureId_DomainCoreClocks,          //!< Feature to enable/disable domain core clocks voting
    AsicFeatureId_CachePartitionControl,     //!< Feature to enable/disable Dynamic cache partitioning
    AsicFeatureId_DcvsControl,               //!< Feature to enable/disable DCVS from ADSPPM
    AsicFeatureId_AhbeScaling,               //!< Feature to enable/disable scaling of AHB-E bus frequency
    AsicFeatureId_CacheSizeMPPSThreshold,    //!<Feature to enable/disable MPPS-based cache size	
    AsicFeatureId_CacheSizeBWScaling,        //!< Feature to enable/disable scaling of external compensated BW vote 
	AsicFeatureId_ComputeDSP,				 //!< Feature to indicate this is TuringSS, Compute Processor
    AsicFeatureId_enum_max,
    AsicFeatureId_force_32bit = 0x7FFFFFFF
} AsicFeatureIdType;

typedef enum
{
    AsicFeatureState_Disabled, //!< Feature completely disabled
    AsicFeatureState_Enabled,  //!< Feature enabled
    AsicFeatureState_Limited   //!< Feature behaviour limited
} AsicFeatureStateType;

typedef struct
{
    AsicFeatureStateType state;
    uint64 min;
    uint64 max;
} AsicFeatureDescType;

/******************************************************************************************/
/*               Restricted functions definitions                                         */
/******************************************************************************************/
Adsppm_Status ACM_Init(void);

uint32 ACM_GetDebugLevel(void);

AsicHwRscIdType ACM_GetHwRscId(AdsppmCoreIdType, AdsppmRscIdType);

//Asic_Rsc_AggregationFnType ACM_GetAggregationFn(AsicHwRscIdType, AdsppmCoreIdType);

/**
 * @fn ACM_BusBWAggregate - Aggregate bw
 */
Adsppm_Status ACM_BusBWAggregate(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue);

Adsppm_Status ACM_GetBWFromMips(AdsppmMIPSToBWAggregateType *pMipsAggregateData);

Adsppm_Status ACM_GetClockFromMips(AdsppmMIPSToClockAggregateType *pMipsAggregateData);

Adsppm_Status ACM_GetClockFromBW(uint32 *pClock, AdsppmBusBWDataIbAbType *pAHBBwData);

void ACM_GetCompensatedDdrBwTableEntry( uint64 vote, AsicCompensatedDdrBwTableEntryType *pTableEntry);

void ACM_ApplyAdspDdrBwConcurrencyFactor(uint32 numVotes, uint64 maxBw, uint64* pAb, uint64* pIb, AsicCompensatedBWFudgeFactor *compensatedBWFudgeFactorValues);

uint32 ACM_GetMipsFromMpps(uint32 mppsTotal, uint32 numDominantThreads);

Adsppm_Status ACM_ApplyAhbBwCompensation(uint64 bwVoteIn, uint64* pBwVoteOut);

Adsppm_Status ACM_GetAhbeFromAdspFreq(uint32 adspClockFreq, uint32* ahbClockFreq);

Adsppm_Status ACM_GetMPPSThresholdfromClientClass(MmpmClientClassType clientClass, uint32* mppsThreshold);

Adsppm_Status ACM_GetBWScalingFactorFromCacheSize(uint32 cachesize, uint32* scalingfactor);

/**
 * Request number of supported routes (master/slave pairs) for external BW requests
 * @return number of supported routes (master/slave pairs) for external BW requests
 */
int ACMBus_GetNumberOfExtRoutes(void);

/**
 * Request supported routes (master/slave pairs) for external BW requests
 * @param pExtRoutes - [OUT] array to be filled with supported routes (master/slave pairs) for external BW requests
 */
void ACMBus_GetExtRoutes(AsicBusExtRouteType *pExtRoutes);

/**
 * Get core clock ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param coreClock
 * @return if core clock is associated to this core, return associated core instance core clock ID
 *         else return core clock ID passed in coreClock
 */
AdsppmClkIdType ACMClk_GetInstanceCoreClockId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmClkIdType coreClock);

/**
 * Get master bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param masterBusPort
 * @return if master bus port is associated to this core, return associated core instance master bus port ID
 *         else return bus port ID passed in masterBusPort
 */
AdsppmBusPortIdType ACMBus_GetInstanceMasterBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType masterBusPort);

/**
 * Get slave bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param slaveBusPort
 * @return if slave bus port is associated to this core, return associated core instance slave bus port ID
 *         else return bus port ID passed in slaveBusPort
 */
AdsppmBusPortIdType ACMBus_GetInstanceSlaveBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType slaveBusPort);

/**
 * @fn ACMBus_GetCoreSlavePort - returns slave bus port associated with the core the client is registered for
 * @param coreId
 * @param instanceId
 * @return slave bus port ID associated with the registered core
 */
AdsppmBusPortIdType ACMBus_GetCoreSlavePort(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId);

/**
 * Returns pointer to the the descriptor for the specified bus port.
 * @param port
 * @return pointer to the bus port descriptor
 */
const AsicBusPortDescriptorType *ACMBus_GetPortDescriptor(AdsppmBusPortIdType);

/**
 * @fn ACMBus_GetPortConnections
 * @brief Returns bus port connections for the specified bus port.
 * @param port - AdsppmBusPortIdType
 * @return busPortConnections - AsicBusPortConnectionType
 */
AsicBusPortConnectionType ACMBus_GetPortConnections(AdsppmBusPortIdType port);

/**
 * Get type of the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
AsicClkTypeType ACMClk_GetClockType(AdsppmClkIdType);

/**
 * @fn ACM_IsClkIdValid - get ClkId present in the global clkId array
 *
 * Function gets ...
 *
 * @return completion status
 */
boolean ACM_IsClkIdValid(AdsppmClkIdType clk);

/**
 * @fn ACM_GetClkIdx - get ClkId index in global clkId array
 *
 * Function gets ...
 *
 * @return completion status
 */
Adsppm_Status ACM_GetClkIdx(AdsppmClkIdType clk , uint32 *clkIdx);

/**
 * Request number of clock descriptors
 * @return number of clock descriptors
 */
const int ACMClk_GetNumberOfClockDescriptors(void);

/**
 * Get descriptor the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
const AsicClkDescriptorType *ACMClk_GetClockDescriptor(uint32 clkDesIndex);

/**
 * Get descriptor the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
const AsicClkDescriptorType *ACMClk_GetClockDescriptorById(AdsppmClkIdType);

/**
 * @fn ACM_IsPwrDomainValid - get pwrDomain present in the global pwr array
 *
 * Function gets ...
 *
 * @return completion status
 */
boolean ACM_IsPwrDomainValid(AsicPowerDomainType domain);

/**
 * @fn ACM_GetPwrDomainIdx - get pwrDomain index in global pwrDomain array
 *
 * Function gets ...
 *
 * @return completion status
 */
Adsppm_Status ACM_GetPwrDomainIdx(AsicPowerDomainType domain , uint32 *domainIdx);

/**
 * Request number of pwrDomain descriptors
 * @return number of pwrDomain descriptors
 */
const int ACMClk_GetNumberOfPwrDomainDescriptors(void);

/**
 * Get info about the power domain
 * @param Domain Id
 * @return Power Domain Info
 */
const AsicPowerDomainDescriptorType *ACMClk_GetPwrDomainDescriptor(uint32);

/**
 * Get power domain for the specified core
 * @param Core ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetPowerDomain(AdsppmCoreIdType);

/**
 * Get power domain for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetMemPowerDomain(AdsppmMemIdType mem);

/**
 * Get power resource type  for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicHwRscIdType ACMPwr_GetMemPowerType(AdsppmMemIdType mem);

/**
 * Get descriptor for the specified core
 * @param Core ID
 * @return pointer to the descriptor for this core
 */
const AsicCoreDescType *ACM_GetCoreDescriptorById(AdsppmCoreIdType);

/**
 * Get Interrupt ID for the TZ secure interrupt
 */
uint32 ACM_GetTZSecureInterrupt(void);

/**
 * Get feature enablement status for a particular feature
 */
AsicFeatureStateType ACM_GetFeatureStatus(AsicFeatureIdType);

/**
 * Get feature descriptor for a particular feature
 */
AsicFeatureDescType *ACM_GetFeatureDescriptor(AsicFeatureIdType featureId);

/**
 * Adjust parameter value based on feature enablement and configuration data
 * @param featureId - feature ID.
 * @param value - value, which needs to be adjusted
 * @return - adjusted value
 */
uint64 ACM_AdjustParamValue(AsicFeatureIdType featureId, uint64 value);

/**
 * Convert time in ms to sclk
 * @param ms - time in ms.
 * @return - number of sclks
 */
uint64 ACM_ms_to_sclk(uint64 ms);

/**
 * Convert time in us to qclk (QTimer clock ticks)
 * @param us - time in us.
 * @return - number of qclks
 */
uint64 ACM_us_to_qclk(uint64 us);

/**
 * Request number of supported routes (master/slave pairs) for MIPS BW requests
 * @return number of supported routes (master/slave pairs) for MIPS BW requests
 */
const int ACMBus_GetNumberOfMipsBwRoutes(void);

/**
 * Request list supported routes (master/slave pairs) for MIPS BW requests
 * @return pointer to array of supported routes (master/slave pairs) for MIPS BW requests
 */
const AdsppmBusRouteType *ACMBus_GetMipsBwRoutes(void);

/**
 * Get number of HW threads for the ASIC's ADSP
 * @return number of threads
 */
uint32 ACM_GetHwThreadNumber(void);

/**
 * Get a timeout value in ms for MIPS/BW optimization LPR
 * @return timeout value in ms
 */
uint64 ACM_GetLprVoteTimeoutValue(void);

/**
 * Get LPASS HWIO base address
 * @return pointer to the structure containing HWIO base address
 */
AsicHwioRegRangeType *ACM_GetLpassRegRange(void);

/**
 * Get L2 cache configuration registers address range
 * @return pointer to the structure containing registers address range
 */
AsicHwioRegRangeType *ACM_GetL2ConfigRegRange(void);

/**
 * Get info about the power domain
 * @param Memory Id
 * @return Memory Info
 */
AsicMemDescriptorFullType *ACM_GetMemoryDescriptor(AdsppmMemIdType mem);

/**
 * Get address range for the specified memory
 * @param Memory ID
 * @return address range
 */
AsicAddressRangeType *ACM_GetVirtMemAddressRange(AdsppmMemIdType mem);

/**
 * Set address range for the specified memory
 * @param mem - Memory ID
 * @param addr - start address
 * @param size - address range size
 * @return operation status
 */
AdsppmStatusType ACM_SetVirtMemAddressRange(AdsppmMemIdType mem, uint64 addr, uint32 size);

AsicCachePartitionConfigTableType* ACM_GetCachePartitionConfig();

/**
 * Apply scaling of 64-bit input:
 * output = input * num / denom
 * UINT_MAX is returned if result would overflow 32-bit unsigned integer
 */
uint64 scale64(uint64 input, uint32 num, uint32 denom);

/**
 * Apply scaling of 32-bit input:
 * output = input * num / denom
 * UINT_MAX is returned if result would overflow 32-bit unsigned integer
 */
uint32 scale32(uint32 input, uint32 num, uint32 denom);



#endif /* ASIC_H_ */

