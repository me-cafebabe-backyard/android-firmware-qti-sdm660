/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: busmgr.c
@brief: ADSPPM bus manager implementation.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/qdsp_pm_mgr/resource_mgr/busmgr.c#1 $
*/

#include "adsppm.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "busmgr.h"
#include "hal_clkrgm.h"
#include "ahbmgr.h"
#include "hal_busdrv.h"
#include "clientmgr.h"
#include "stdlib.h"
#include "extbwmgr.h"
#include "cachemgr.h"
#include "usleepmgr.h"


#define MIN_AHB_BW 32767 // Bare minimal AHB BW to keep AHB always ON. Used in AHB BW aggregation

// Pre-aggregation data for external bandwidth requests.
// Requests are grouped in two classes:
//   - generic: "normal" requests, that are not modified
//   - compensated - requests which are to be modified according to compensation table
typedef struct
{
    AdsppmBusBWRequestValueType *pGeneric;
    AdsppmBusBWRequestValueType *pCompensated;
    uint32 numCompensatedAdspDdrVotes;
    uint64 maxAdspToDDrBw;
} busMgrExtPreAggregateData;

// Pre-aggregation data for internal bandwidth requests.
// Requests are grouped in two classes:
//   - generic: "normal" requests, that are not modified
//   - compensated - requests which are to be modified according to compensation table
typedef struct
{
    // Generic (non-compensated) class
    struct
    {
        AdsppmBusBWDataIbAbType totalBw;
        AdsppmBusBWDataIbAbType nonSuppressibleBw;
    } generic;
    // Compensated class
    struct
    {
        // BW votes for ADSP master, which are modified with compensation table
        AdsppmBusBWDataIbAbType adspMasterBw;
        // BW votes for non-ADSP masters, which aren't modified with compensation table
        AdsppmBusBWDataIbAbType nonAdspMasterBw;
        AdsppmBusBWDataIbAbType nonSuppressibleBw;
    } compensated;
} busMgrIntPreAggregateData;

/**
 * @struct busMgrCtxType - define bus management context
 */
typedef struct
{
    DALSYSSyncHandle            lock;
    uint32                      extRouteNum;
    AsicBusExtRouteType         *pExtRoutes;
    uint32                      preCurrentIndex; //!< Index used in pExtBwAggregateData, clockState, and snocFlootVoteMhz arrays
    AdsppmBusBWRequestValueType *pExtBwAggregateData[2];
    busMgrExtPreAggregateData   extPreAggregateData;
    busMgrIntPreAggregateData   intPreAggregateData;
    AdsppmBusBWDataIbAbType     *dcvsExtBwFloorVote[2];//!< Keeping track of dcvs floor votes	
    Hal_ClkRgmEnableDisableType clockState[2][AdsppmClk_EnumMax];
    AdsppmBusBWDataIbAbType     curAHBBwData; //!< Current aggregated AHB BW
    AdsppmBusBWDataIbAbType     nonSuppressibleAhbBW; //!< Non-suppressible AHB BW
    boolean                     bPeriodicClientBW2DDR; //!< True if at least 1 periodic client requests BW to DDR
    uint32                      snocFloorVoteMhz[2]; //!< Snoc Floor vote
    uint32                      scalingfactor;//!< flag to indicate bw scaling factor based on cache size
    boolean                     externalBwUpdatePending;//!< Flag to inform main bw call, BusMgr_ProcessRequest, to skip sending vote to ICB driver	
    npa_client_handle           uSleepHandle; //to vote on dsp pm usleep node
} busMgrCtxType;

/**
 * @enum BUSMgrBwTypeType - define bus bw type
 */
typedef enum
{
    BUSMgr_Bw_None              = 0,
    BUSMgr_Bw_Internal_Only     = 1,
    BUSMgr_Bw_External_Only     = 2,
    BUSMgr_Bw_Internal_External = 3,
    BUSMgr_Bw_ForceTo8bits      = 0x7f
} BUSMgrBwTypeType;

/**
 * @struct BUSMgr_BwDescriptorType - contains bw info for a single request
 */
typedef struct
{
    AdsppmBusPortIdType masterPort;
    AdsppmBusPortIdType slavePort;
    AdsppmBusPortIdType accessPort;
    // Master port descriptor
    const AsicBusPortDescriptorType *pMPortDescriptor;
    // Slave port descriptor
    const AsicBusPortDescriptorType *pSPortDescriptor;
    // Access port descriptor
    const AsicBusPortDescriptorType *pAPortDescriptor;
    AdsppmBusBWOperationType bwOperation;
    AdsppmBusBWDataType bwValue;
} BUSMgr_BwDescriptorType;

static busMgrCtxType gBusMgrCtx;

// Internal function to process bandwidth
static Adsppm_Status busMgrAggregateRequest(
    AdsppmBusBWRequestValueType *pBwRequest,
    AdsppmBwRequestClass reqClass);

static void busMgrAggregateExternalBW(coreUtils_Q_Type *pBWReqQ);
static void busMgrAggregateInternalBW(void);

/**
*@fn bmOnCPManagerUpdate - Internal function to act on cache partition change request
*/

static void bmOnCPManagerUpdate(AdsppmCachePartitionManagerEventId eventId,void * param);

/**
 * BuMgr_USleepNode_RegisterCB
 * 
 * @brief Registers dspPm uSleep node
 * 
 * @param see npa_callback defintion for function parameters
 */
static void BuMgr_USleepNode_RegisterCB(
			void         *context,
            unsigned int  eventType,
            void         *data,
            unsigned int  dataSize)
{
    gBusMgrCtx.uSleepHandle = npa_create_sync_client(
									QDSPPM_USLEEP_NODE_NAME, 
                                    "qdsppm_busmgr",
									NPA_CLIENT_REQUIRED);
    return;
}

/**
 * @fn BusMgr_Init - bus management init, init mutex and global variables
 */
Adsppm_Status BusMgr_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    DALResult dalResult = DAL_SUCCESS;
    uint32 index = 0;

    memset(&gBusMgrCtx, 0, sizeof(busMgrCtxType));
    dalResult = DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        (DALSYSSyncHandle *) &gBusMgrCtx.lock,
        NULL);

    if(DAL_SUCCESS != dalResult)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create lock");
        sts = Adsppm_Status_Failed;
    }
    else
    {
        /* Register a callback for dspPm uSleep node
         * create a client for BusMgr to vote on dspPm uSleep node.
		 */
        npa_resource_available_cb(QDSPPM_USLEEP_NODE_NAME,
                                  BuMgr_USleepNode_RegisterCB, NULL);
	    
        // Get support route pair number from asic manager
        gBusMgrCtx.extRouteNum = ACMBus_GetNumberOfExtRoutes();
        gBusMgrCtx.pExtRoutes =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AsicBusExtRouteType));
        gBusMgrCtx.pExtBwAggregateData[0] =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));
        gBusMgrCtx.pExtBwAggregateData[1] =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));
        gBusMgrCtx.extPreAggregateData.pGeneric =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));
        gBusMgrCtx.extPreAggregateData.pCompensated =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));
        gBusMgrCtx.dcvsExtBwFloorVote[0] =
            malloc(sizeof(AdsppmBusBWDataIbAbType));
        gBusMgrCtx.dcvsExtBwFloorVote[1] =
            malloc(sizeof(AdsppmBusBWDataIbAbType));
        gBusMgrCtx.scalingfactor  = 100; 			

        // Check for failed malloc
        if((NULL == gBusMgrCtx.pExtRoutes) ||
            (NULL == gBusMgrCtx.pExtBwAggregateData[0]) ||
            (NULL == gBusMgrCtx.pExtBwAggregateData[1]) ||
            (NULL == gBusMgrCtx.extPreAggregateData.pGeneric) ||
            (NULL == gBusMgrCtx.extPreAggregateData.pCompensated) || 
            (NULL == gBusMgrCtx.dcvsExtBwFloorVote[0]) ||
            (NULL == gBusMgrCtx.dcvsExtBwFloorVote[1])
            )
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
                "Failed to allocate aggregate buffer");

            if(NULL != gBusMgrCtx.pExtRoutes)
            {
                free(gBusMgrCtx.pExtRoutes);
            }
            if(NULL != gBusMgrCtx.pExtBwAggregateData[0])
            {
                free(gBusMgrCtx.pExtBwAggregateData[0]);
            }
            if(NULL != gBusMgrCtx.pExtBwAggregateData[1])
            {
                free(gBusMgrCtx.pExtBwAggregateData[1]);
            }
            if(NULL != gBusMgrCtx.extPreAggregateData.pGeneric)
            {
                free(gBusMgrCtx.extPreAggregateData.pGeneric);
            }
            if(NULL != gBusMgrCtx.extPreAggregateData.pCompensated)
            {
                free(gBusMgrCtx.extPreAggregateData.pCompensated);
            }
            if(NULL != gBusMgrCtx.dcvsExtBwFloorVote[0])
            {
                free(gBusMgrCtx.dcvsExtBwFloorVote[0]);
            }
            if(NULL != gBusMgrCtx.dcvsExtBwFloorVote[1])
            {
                free(gBusMgrCtx.dcvsExtBwFloorVote[1]);
            }
            sts = Adsppm_Status_NoMemory;
        }
        else
        {
            // Get supported route pairs from asic manager and save
            ACMBus_GetExtRoutes(gBusMgrCtx.pExtRoutes);
            for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
            {
                gBusMgrCtx.pExtBwAggregateData[0][index].busRoute.masterPort =
                    gBusMgrCtx.pExtRoutes[index].masterPort.adsppmMaster;
                gBusMgrCtx.pExtBwAggregateData[0][index].busRoute.slavePort =
                    gBusMgrCtx.pExtRoutes[index].slavePort.adsppmSlave;
                gBusMgrCtx.pExtBwAggregateData[0][index].bwOperation =
                    AdsppmBusBWOperation_BW;

                gBusMgrCtx.pExtBwAggregateData[1][index].busRoute.masterPort =
                    gBusMgrCtx.pExtRoutes[index].masterPort.adsppmMaster;
                gBusMgrCtx.pExtBwAggregateData[1][index].busRoute.slavePort =
                    gBusMgrCtx.pExtRoutes[index].slavePort.adsppmSlave;
                gBusMgrCtx.pExtBwAggregateData[1][index].bwOperation =
                    AdsppmBusBWOperation_BW;
            }

        }
 
    }
    return sts;
}
/**
 * @fn busMgrRegisterEvents - bus management register events with other managers
 */

Adsppm_Status busMgrRegisterEvents (void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    busMgrCtxType *self = &gBusMgrCtx;
    uint32 cachepartitionsize = 0;

    //Register an event with Cache Partition Manager for notification regarding
    //change in Cache Partition size
    if(ACM_GetFeatureStatus(AsicFeatureId_CacheSizeBWScaling) ==
                                     AsicFeatureState_Enabled)
     {			
         if (CPM_RegisterEvent(CPM_CACHE_CONFIGURATION_CHANGE, bmOnCPManagerUpdate,
                              (void*) self) != Adsppm_Status_Success)
           {
                sts = Adsppm_Status_Failed;					
           }
         else
          {
                cachepartitionsize = FULL_SIZE;
                ACM_GetBWScalingFactorFromCacheSize(cachepartitionsize, &gBusMgrCtx.scalingfactor);
          }
      }
  return sts;
}
static Adsppm_Status busMgrProcessClocks(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    const AsicClkDescriptorType *pClkDesc = NULL;
    uint32 index = 0;

    for(index = AdsppmClk_AhbI_Hclk;
        (index < AdsppmClk_EnumMax) && (Adsppm_Status_Success == sts);
        index++)
    {
        if(gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex^1][index] !=
            gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index])
        {
            pClkDesc = ACMClk_GetClockDescriptorById(index);
            if(NULL == pClkDesc)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "Clock descriptor is NULL, clkId=%u", index);
                sts = Adsppm_Status_Failed;
            }
            else
            {
                switch(pClkDesc->clkCntlType)
                {
                case AsicClk_CntlSW_DCG:
                case AsicClk_CntlAlwaysON_DCG:
                case AsicClk_CntlSW:
                    sts = ClkRgm_EnableClock(
                        (AdsppmClkIdType) index,
                        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index]);
                    break;
                default:
                    // Ignore AON and AOFF clocks
                    break;
                }
            }
        }
    }

    return sts;
}


static uint32 busMgrProcessExternalBW(AdsppmBusBWRequestValueType *pUpdateExtBusBwValue)
{
    uint32 index = 0, numOfBW = 0;
    AdsppmBusBWRequestValueType* pCurrentBwVote = NULL;
    AdsppmBusBWRequestValueType* pPreviousBwVote = NULL;

    for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
    {
        pCurrentBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index]);
        pPreviousBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex^1][index]);

        if((pPreviousBwVote->bwValue.busBwAbIb.Ab != pCurrentBwVote->bwValue.busBwAbIb.Ab) ||
            (pPreviousBwVote->bwValue.busBwAbIb.Ib != pCurrentBwVote->bwValue.busBwAbIb.Ib))
        {
            // Apply BW to DDR optimization if:
            // 1. use case is periodic
            // 2. and at least 1 periodic client requests BW > 0 to DDR from Q6
            if((AdsppmBusPort_Adsp_Master == pCurrentBwVote->busRoute.masterPort) &&
                (AdsppmBusPort_Ddr_Slave == pCurrentBwVote->busRoute.slavePort) &&
                (AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationBw)))
            {
                if(IsPeriodicUseCase() && gBusMgrCtx.bPeriodicClientBW2DDR &&
                    (0 < pCurrentBwVote->bwValue.busBwAbIb.Ib))
                {
                    pCurrentBwVote->bwValue.busBwAbIb.Ib = ACM_AdjustParamValue(
                        AsicFeatureId_TimelineOptimisationBw,
                        pCurrentBwVote->bwValue.busBwAbIb.Ib);
                }
            }
            // Copy updated bus vote to buffer
            memscpy(&(pUpdateExtBusBwValue[numOfBW]),
                sizeof(AdsppmBusBWRequestValueType),
                pCurrentBwVote,
                sizeof(AdsppmBusBWRequestValueType));
            ADSPPM_LOG_PRINTF_6(ADSPPM_LOG_LEVEL_INFO_EXT,
                "ext BW %u updated: Ib=%llu, Ab=%llu Latency=%u",
                numOfBW,
                (uint32) pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ib,
                (uint32) (pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ib >> 32),
                (uint32) pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ab,
                (uint32) (pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ab >> 32),
                (uint32) pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.latencyNs);
            numOfBW++;
        }
    }

    return numOfBW;
}

// Aggregate DCVS ADSP to DDR BW Floor vote
static Adsppm_Status busMgrAggregateDcvsFloorVote(
    AdsppmBusBWRequestValueType* pBwRequest,
    AdsppmBusBWDataIbAbType* pDcvsFloorVote)
{
    Adsppm_Status sts = Adsppm_Status_Success;

    sts = ACM_BusBWAggregate(pDcvsFloorVote, &pBwRequest->bwValue);

    return sts;
}

static Adsppm_Status busMgrUpdateUSleepMgr(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 index = 0;
    AdsppmBusBWRequestValueType* pCurrentBwVote = NULL;
    uint64 ddrAb = 0;

    for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
    {
        pCurrentBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index]);
        if(pCurrentBwVote->busRoute.slavePort == AdsppmBusPort_Ddr_Slave)
        {
            ddrAb += pCurrentBwVote->bwValue.busBwAbIb.Ab;
        }
    }

	if (gBusMgrCtx.uSleepHandle)
	{
		boolean uSleep_vote;

   		/* Allow sleep only then aggr DDR bw = 0 */ 
    	uSleep_vote = ddrAb ? QDSPPM_USLEEP_DISALLOW : QDSPPM_USLEEP_ALLOW;
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT,
                       "NPA request to %s usleep", (uSleep_vote ? "Allow" : "DisAllow"));

        npa_issue_required_request(gBusMgrCtx.uSleepHandle, uSleep_vote);
	}

    return sts;
}

/****
*@Fn busMgr_SendExternalBWInfo -- Sned final bw info vote to ICB
*@param input void
*@return Adspppm_Status
*/
Adsppm_Status busMgr_SendExternalBWInfo (uint32 numUpdatedExtBwVotes,AdsppmBusBWRequestValueType *updateExtBusBwValue, boolean snocFloorChanged, uint32 snocFloorVoteMhz)
{
    Adsppm_Status sts = Adsppm_Status_Success;
  	
    if(sts == Adsppm_Status_Success )
    {
        if(ACM_GetFeatureStatus(AsicFeatureId_DcvsControl) == 
                                 AsicFeatureState_Enabled)
         {
            sts = ExtBwMgr_IssueExtBwRequest(
                numUpdatedExtBwVotes,
                &updateExtBusBwValue[0],
                gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex^1]);
         }
        else
        {
            if(numUpdatedExtBwVotes > 0)
            {
              sts = Bus_IssueBWRequest(
                     numUpdatedExtBwVotes, &updateExtBusBwValue[0]);
            }
        }
        if((Adsppm_Status_Success == sts) && snocFloorChanged)
           sts = Bus_IssueSnocRequest(snocFloorVoteMhz);
    }

   return sts;
}

/**
*@fn busMgr_ProgramExternalBW -- Process final external bw information
*@param input void
*@return Adsppm_Status
*/
uint32  busMgr_ProcessExternalBWInfo (AdsppmBusBWRequestValueType *updateExtBusBwValue, boolean *snocFloorChanged, uint32 *snocFloorVoteMhz)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    // Locals to track change in SNOC floor vote
    uint32 numUpdatedExtBwVotes=0 ;
	
    // Process External Bandwidth
    if(Adsppm_Status_Success == sts)
    {
        numUpdatedExtBwVotes = busMgrProcessExternalBW(&updateExtBusBwValue[0]);
    }
	
    // Check for change in required SNOC floor vote
    if(gBusMgrCtx.snocFloorVoteMhz[gBusMgrCtx.preCurrentIndex] !=
        gBusMgrCtx.snocFloorVoteMhz[gBusMgrCtx.preCurrentIndex ^ 1])
    {
        *snocFloorVoteMhz = gBusMgrCtx.snocFloorVoteMhz[gBusMgrCtx.preCurrentIndex];
        *snocFloorChanged = TRUE;
    }
	
   return numUpdatedExtBwVotes;
}
/**
 * @fn BusMgr_ProcessRequest - bus management main function,
 *                             separate bw to external and internal bw and do external bw aggregate
 * @param input: coreUtils_Q_Type *pBWReqQ
 * @return Adsppm_Status
 */
Adsppm_Status BusMgr_ProcessRequest(coreUtils_Q_Type *pBWReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 index = 0, bwNum = 0;
    RMHandleType *pRMHandle = NULL;
    AdsppmBusBWRequestValueType updateExtBusBwValue[gBusMgrCtx.extRouteNum];
    //AdsppmBusBWDataIbAbType dcvsExtBwFloorVote;
    uint32 numUpdatedExtBwVotes=0;
    // Locals to track change in SNOC floor vote            
    uint32 snocFloorVoteMhz = 0;
    boolean snocFloorChanged = FALSE, bSendICBRequest=FALSE;	

    if(NULL == pBWReqQ)
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Pointer is NULL");
    }
    else
    {
        if(NULL == gBusMgrCtx.lock)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            sts = Adsppm_Status_NotInitialized;
        }
        else
        {
            uint32 newRequestClientId = 0;
            uint32 newAdspDdrReqClientId = 0;
            uint32 releasedRequestClientId = 0;
            uint32 releaseAdspDdrReqClientId = 0;
            // Number of requests for the current client that are valid and
            // have a non-zero bandwidth.
            uint32 numNonZeroRequests = 0;
            // Number of requests for the current client that are valid and
            // have a non-zero ADSP to DDR bandwidth.
            uint32 numNonZeroAdspDdrRequests = 0;


            // Lock for bus manager global data update
            adsppm_lock(gBusMgrCtx.lock);
            ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_BW);

            // Init variables
            memset(updateExtBusBwValue, 0, gBusMgrCtx.extRouteNum*sizeof(AdsppmBusBWRequestValueType));
            gBusMgrCtx.curAHBBwData.Ib = gBusMgrCtx.nonSuppressibleAhbBW.Ib = MIN_AHB_BW;
            gBusMgrCtx.curAHBBwData.Ab = gBusMgrCtx.nonSuppressibleAhbBW.Ab = 0;
            gBusMgrCtx.bPeriodicClientBW2DDR = FALSE;
            gBusMgrCtx.extPreAggregateData.numCompensatedAdspDdrVotes = 0;
            gBusMgrCtx.extPreAggregateData.maxAdspToDDrBw = 0;
            gBusMgrCtx.snocFloorVoteMhz[gBusMgrCtx.preCurrentIndex] = 0;
            gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]->Ab = 0;
            gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]->Ib = 0;
            gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]->latencyNs= 0;

            for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
            {
                gBusMgrCtx.extPreAggregateData.pGeneric[index].bwValue.busBwAbIb.Ab = 0;
                gBusMgrCtx.extPreAggregateData.pGeneric[index].bwValue.busBwAbIb.Ib = 0;
                gBusMgrCtx.extPreAggregateData.pCompensated[index].bwValue.busBwAbIb.Ab = 0;
                gBusMgrCtx.extPreAggregateData.pCompensated[index].bwValue.busBwAbIb.Ib = 0;
                gBusMgrCtx.extPreAggregateData.pCompensated[index].bwValue.busBwAbIb.latencyNs = 0;
            }

            memset(&gBusMgrCtx.intPreAggregateData, 0, sizeof(busMgrIntPreAggregateData));

            for(index = AdsppmClk_AhbI_Hclk; index < AdsppmClk_Audio_Core_AON; index++)
            {
				if(ACM_IsClkIdValid(index))
				{
					gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index] =
						(AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Ahb_Sw_CG))?
						Hal_ClkRgmEnable:Hal_ClkRgmDisable;
				}
            }

            for(index = AdsppmClk_HwRsp_Core; index < AdsppmClk_EnumMax; index++)
            {
				if(ACM_IsClkIdValid(index))
				{
					gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index] =
						(AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_CoreClk_Scaling))?
						Hal_ClkRgmEnable:Hal_ClkRgmDisable;
				}
            }

            // Go through each client's bw request
            pRMHandle = (RMHandleType *)coreUtils_Q_Check(pBWReqQ);

            for(index = 0; (index < pBWReqQ->nCnt) && (NULL != pRMHandle); index++)
            {
                numNonZeroRequests = 0;

                // Generic BW Request
                if(RM_Valid == pRMHandle->validFlag)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Generic BW Request");
                    if((NULL == (AdsppmBwReqType *)(pRMHandle->pRequestData)) ||
                        (NULL == pRMHandle->pClient))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                            "pRequestData(%u) or pClient(%u) is NULL",
                            (AdsppmBwReqType *) (pRMHandle->pRequestData), pRMHandle->pClient);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        AdsppmBwReqType *pBwReqData = (AdsppmBwReqType *) (pRMHandle->pRequestData);
                        // Go through each bw request for this client
                        for(bwNum = 0; (bwNum < pBwReqData->numOfBw) && (Adsppm_Status_Success == sts); bwNum++)
                        {
                            AdsppmBusBWRequestValueType *pBwRequest = &pBwReqData->pBwArray[bwNum];

                            // Get bus port IDs corresponding to this core instance if applicable
                            pBwRequest->busRoute.masterPort = ACMBus_GetInstanceMasterBusPortId(
                                pRMHandle->pClient->coreId,
                                pRMHandle->pClient->instanceId,
                                pBwRequest->busRoute.masterPort);
                            pBwRequest->busRoute.slavePort = ACMBus_GetInstanceSlaveBusPortId(
                                pRMHandle->pClient->coreId,
                                pRMHandle->pClient->instanceId,
                                pBwRequest->busRoute.slavePort);

                            // Filter out requests with bus ports that have no connections
                            // meaning they do not exit in current chip set
                            AsicBusPortConnectionType masterPortConnection =
                                ACMBus_GetPortConnections(pBwRequest->busRoute.masterPort);
                            AsicBusPortConnectionType slavePortConnection =
                                ACMBus_GetPortConnections(pBwRequest->busRoute.slavePort);

                            if((masterPortConnection == AsicBusPort_None) ||
                                (slavePortConnection == AsicBusPort_None))
                            {
                                ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
                                    "BW request with non-existing ports: from %s(%u) to %s(%u)",
                                    adsppm_getBusPortName(pBwRequest->busRoute.masterPort),
                                    pBwRequest->busRoute.masterPort,
                                    adsppm_getBusPortName(pBwRequest->busRoute.slavePort),
                                    pBwRequest->busRoute.slavePort);
                                sts = Adsppm_Status_UnSupported;
                                break;
                            }
                            else
                            {
                                // Filter out BW values of Zero
                                if(0 == pBwRequest->bwValue.busBwValue.bwBytePerSec)
                                {
                                    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
                                        "BW request of Zero from %s(%u) to %s(%u), exclude from aggregation",
                                        adsppm_getBusPortName(pBwRequest->busRoute.masterPort),
                                        pBwRequest->busRoute.masterPort,
                                        adsppm_getBusPortName(pBwRequest->busRoute.slavePort),
                                        pBwRequest->busRoute.slavePort);
                                }
                                else
                                {
                                    // Special considerations for BW requests from ADSP to DDR
                                    if((pBwRequest->busRoute.masterPort == AdsppmBusPort_Adsp_Master) &&
                                        (pBwRequest->busRoute.slavePort == AdsppmBusPort_Ddr_Slave))
                                    {
                                        // Check if at least 1 periodic client requests BW to DDR
                                        if((!gBusMgrCtx.bPeriodicClientBW2DDR) &&
                                            (Adsppm_ClientType_Periodic ==
                                                pRMHandle->pClient->periodicityType))
                                        {
                                            gBusMgrCtx.bPeriodicClientBW2DDR = TRUE;
                                        }

                                        if(ACM_GetFeatureStatus(AsicFeatureId_DcvsControl) ==
                                            AsicFeatureState_Enabled)
                                        {
                                            // Aggregate DCVS Floor vote depending on client's
                                            // participation in DCVS
                                            // Two type of clients counts towards DCVS Floor vote:
                                            // 1. Clients that voted for DCVS disabled
                                            // 2. Clients that voted for DCVS enabled and
                                            //    chose MMPM_DCVS_ADJUST_ONLY_UP as enable option
                                            if((!pRMHandle->pClient->dcvsParticipation.enable) ||
                                                (pRMHandle->pClient->dcvsParticipation.enable &&
                                                    (pRMHandle->pClient->dcvsParticipation.enableOpt ==
                                                        MMPM_DCVS_ADJUST_ONLY_UP)))
                                            {
                                                sts = busMgrAggregateDcvsFloorVote(
                                                    pBwRequest, gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]);
                                                if(sts != Adsppm_Status_Success)
                                                {
                                                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
                                                        "Aggregation of DCVS floor vote failed");
                                                    break;
                                                }
                                            }
                                        }
                                        numNonZeroAdspDdrRequests += 1;
                                    }
                                    numNonZeroRequests += 1;
                                    sts = busMgrAggregateRequest(pBwRequest, pBwReqData->requestClass);
                                }
                            }
                        }
                    }
                }

                // Register Programming
                if(RM_Valid == pRMHandle->validFlag_Ext)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Register Programming");
                    if((NULL == (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext)) ||
                        (NULL == pRMHandle->pClient))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                            "pRequestData_Ext(%u) or pClient(%u) is NULL",
                            (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext),
                            pRMHandle->pClient);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        AdsppmBusBWRequestValueType *pRegBwReqData =
                            (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext);

                        // Get slave port for this core instance
                        pRegBwReqData->busRoute.slavePort = ACMBus_GetCoreSlavePort(
                            pRMHandle->pClient->coreId,
                            pRMHandle->pClient->instanceId);

                        ADSPPM_LOG_PRINTF_5(ADSPPM_LOG_LEVEL_INFO_EXT,
                            "RegProg: M=%s(%u), S=%s(%u), bw=%u",
                            adsppm_getBusPortName(pRegBwReqData->busRoute.masterPort),
                            pRegBwReqData->busRoute.masterPort,
                            adsppm_getBusPortName(pRegBwReqData->busRoute.slavePort),
                            pRegBwReqData->busRoute.slavePort,
                            (uint32) pRegBwReqData->bwValue.busBwValue.bwBytePerSec);

                        // Filter out requests with bus ports that have no connections
                        // meaning they do not exit in current chip set
                        // and requests with AdsppmBusPort_None
                        AsicBusPortConnectionType slavePortConnection =
                            ACMBus_GetPortConnections(pRegBwReqData->busRoute.slavePort);

                        if(slavePortConnection == AsicBusPort_None)
                        {
                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                                "Reg prog for coreID %u instanceID %u not supported",
                                pRMHandle->pClient->coreId,
                                pRMHandle->pClient->instanceId);
                            sts = Adsppm_Status_UnSupported;
                            break;
                        }

                        numNonZeroRequests += 1;
                        sts = busMgrAggregateRequest(pRegBwReqData, Adsppm_BwReqClass_Generic);
                    }
                }

                if(Adsppm_Status_Success != sts)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "BW aggregation failed");
                    break;
                }

                // Keep track of new and released requests;
                // Assuming there is no more than one of each for each
                // time this function is called
                if(pRMHandle->lifecycleState == NEW_REQUEST)
                {
                    if(numNonZeroRequests > 0)
                    {
                        // This is a normal new/modified request with non-zero
                        // BW
                        if(newRequestClientId)
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                                "more than one new request received");
                        }
                        newRequestClientId = pRMHandle->clientId;
                    }
                    else
                    {
                        // This is a new/modified request with zero BW, which
                        // we treat similar to a release request
                        if(releasedRequestClientId)
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                                "more than one request released");
                        }
                        releasedRequestClientId = pRMHandle->clientId;
                    }

                    if(numNonZeroAdspDdrRequests > 0)
                    {
                        // This is a normal new/modified request with
                        // non-zero ADSP to DDR BW
                        if(newAdspDdrReqClientId)
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                                "more than one new ADSP to DDR request received");
                        }
                        newAdspDdrReqClientId = pRMHandle->clientId;
                    }
                    else
                    {
                        // This is a new/modified request with zero BW, which
                        // we treat similar to a release request
                        if(releaseAdspDdrReqClientId)
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                                "more than one ADSP to DDR request released");
                        }
                        releaseAdspDdrReqClientId = pRMHandle->clientId;
                    }
                }
                else if((pRMHandle->lifecycleState == RELEASED_REQUEST) &&
                    (pRMHandle->validFlag != RM_Valid) &&
                    (pRMHandle->validFlag_Ext != RM_Valid))
                {
                    // This is a fully released request since both validFlag
                    // and validFlag_Ext are false
                    if(releasedRequestClientId)
                    {
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                            "more than one request released");
                    }
                    releasedRequestClientId = pRMHandle->clientId;

                    if(releaseAdspDdrReqClientId)
                    {
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                            "more than one ADSP to DDR request released");
                    }
                    releaseAdspDdrReqClientId = pRMHandle->clientId;
                }

                pRMHandle = (RMHandleType *) coreUtils_Q_Next(pBWReqQ, &pRMHandle->link);
            }

            if(Adsppm_Status_Success == sts)
            {
                // Previous processing only applied pre-aggregation for
                // external BW.  Now do final aggregation for external BW
                // requests.
                busMgrAggregateExternalBW(pBWReqQ);
            }

            if(Adsppm_Status_Success == sts)
            {
                // Previous processing only applied pre-aggregation for
                // internal (AHB) BW.  Now do final aggregation for internal BW
                // requests.
                busMgrAggregateInternalBW();
            }

            // Process Internal AHB bandwidth
            if(Adsppm_Status_Success == sts)
            {
                sts = AHBM_ProcessRequest(&gBusMgrCtx.curAHBBwData, &gBusMgrCtx.nonSuppressibleAhbBW);
            }

            // Process clocks
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrProcessClocks();
            }

            //Prepare final external bw results
            numUpdatedExtBwVotes = busMgr_ProcessExternalBWInfo(&updateExtBusBwValue[0], &snocFloorChanged, &snocFloorVoteMhz);

			//Update adsp to ddr floor votes if changed
			if((gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]->Ab != 
			    gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex^1]->Ab) ||
               (gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]->Ib != 
			    gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex^1]->Ib))
			{
				ExtBwMgr_UpdateAdsptoDDrClientFloorVotes(gBusMgrCtx.dcvsExtBwFloorVote[gBusMgrCtx.preCurrentIndex]);
			}

	    // Update uSleep manager
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrUpdateUSleepMgr();
            }

            // Update the index for next iteration
            gBusMgrCtx.preCurrentIndex ^= 1;

            //ReSet flag to make sure that BW process request sends request to ICB
            if(numUpdatedExtBwVotes > 0)
                gBusMgrCtx.externalBwUpdatePending = TRUE;

            ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_BW);
            adsppm_unlock(gBusMgrCtx.lock);

            // Update client properties
            if(newRequestClientId)
            {
                // BW request is now active for client making the new request
                CM_SetProperty(newRequestClientId, CM_BW_REQ_ACTIVE_PROPERTY, TRUE);
            }
            if(releasedRequestClientId)
            {
                // BW request is no longer active for client making the released request
                // clientId should still be valid for released requests
                CM_SetProperty(releasedRequestClientId, CM_BW_REQ_ACTIVE_PROPERTY, FALSE);
            }
            if(newAdspDdrReqClientId)
            {
                // ADSP to DDR BW request is now active for client making the new request
                CM_SetProperty(newAdspDdrReqClientId,
                    CM_ADSP_DDR_BW_REQ_ACTIVE_PROPERTY, TRUE);
            }
            if(releaseAdspDdrReqClientId)
            {
                // ADSP to DDR BW request is no longer active for client making the
                // released request clientId should still be valid for released requests
                CM_SetProperty(releaseAdspDdrReqClientId,
                    CM_ADSP_DDR_BW_REQ_ACTIVE_PROPERTY, FALSE);
            }
            //Send Final bw infor to ICB
            adsppm_lock(gBusMgrCtx.lock);
            bSendICBRequest = gBusMgrCtx.externalBwUpdatePending;
            gBusMgrCtx.externalBwUpdatePending = FALSE;
            adsppm_unlock(gBusMgrCtx.lock);
                  
            if (bSendICBRequest == TRUE )
                  busMgr_SendExternalBWInfo(numUpdatedExtBwVotes,&updateExtBusBwValue[0], snocFloorChanged,snocFloorVoteMhz );

            }
        }
    return sts;
}


static BUSMgrBwTypeType busMgrGetBwType(AsicBusPortConnectionType masterPortConnection, AsicBusPortConnectionType slavePortConnection)
{
    BUSMgrBwTypeType bwType = BUSMgr_Bw_None;

    if((0 != (masterPortConnection & AsicBusPort_Ext_Any)) &&
        (0 != (slavePortConnection & AsicBusPort_Ext_Any)))
    {
        bwType = BUSMgr_Bw_External_Only;
    }
    else if((0 != (masterPortConnection & AsicBusPort_Ahb_Any)) &&
        (0 != (slavePortConnection & AsicBusPort_Ahb_Any)))
    {
        bwType = BUSMgr_Bw_Internal_Only;
    }
    else if(((0 != (masterPortConnection & AsicBusPort_Ext_Any)) ||
            (0 != (masterPortConnection & AsicBusPort_Ahb_Any))) &&
        ((0 != (slavePortConnection & AsicBusPort_Ext_Any)) ||
            (0 != (slavePortConnection & AsicBusPort_Ahb_Any))))
    {
        bwType = BUSMgr_Bw_Internal_External;
    }

    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT,
        "connectM=%u, connectS=%u, bwType=%u",
        masterPortConnection, slavePortConnection, bwType);

    return bwType;
}


static Adsppm_Status busMgrPreAggregateInternalBW(
    BUSMgr_BwDescriptorType *pBwDesc,
    AdsppmBwRequestClass requestClass)
{
    Adsppm_Status sts = Adsppm_Status_Success;

    if(requestClass == Adsppm_BwReqClass_Compensated)
    {
        AdsppmBusBWDataIbAbType* pAdspMasterBw;
        AdsppmBusBWDataIbAbType* pNonAdspMasterBw;
        AdsppmBusBWDataIbAbType* pNonSuppressibleBw;

        pAdspMasterBw =
            &gBusMgrCtx.intPreAggregateData.compensated.adspMasterBw;
        pNonAdspMasterBw =
            &gBusMgrCtx.intPreAggregateData.compensated.nonAdspMasterBw;
        pNonSuppressibleBw =
            &gBusMgrCtx.intPreAggregateData.compensated.nonSuppressibleBw;

        if(AdsppmBusPort_Adsp_Master == pBwDesc->masterPort)
        {
            sts = ACM_BusBWAggregate(pAdspMasterBw, &pBwDesc->bwValue);
            if(Adsppm_Status_Success != sts)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "internal BW aggregation failed: %u", sts);
            }
        }
        else
        {
            sts = ACM_BusBWAggregate(pNonAdspMasterBw, &pBwDesc->bwValue);
            if(Adsppm_Status_Success != sts)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "internal BW aggregation failed: %u", sts);
            }
            else
            {
                // Aggregate all non-suppressible BW requests
                // All BW requirements originating from ADSP are considered
                // suppressible and should be excluded
                sts = ACM_BusBWAggregate(pNonSuppressibleBw, &pBwDesc->bwValue);
                if(Adsppm_Status_Success != sts)
                {
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                        "internal BW aggregation failed: %u", sts);
                }
            }
        }

    }
    else // if(requestClass == Adsppm_BwReqClass_Generic)
    {
        AdsppmBusBWDataIbAbType* pTotalBw;
        AdsppmBusBWDataIbAbType* pNonSuppressibleBw;
        pTotalBw =
            &gBusMgrCtx.intPreAggregateData.generic.totalBw;
        pNonSuppressibleBw =
            &gBusMgrCtx.intPreAggregateData.generic.nonSuppressibleBw;

        sts = ACM_BusBWAggregate(pTotalBw, &pBwDesc->bwValue);
        if(Adsppm_Status_Success != sts)
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                "internal BW aggregation failed: %u", sts);
        }
        // Aggregate all non-suppressible BW requests
        // All BW requirements originating from ADSP are considered
        // suppressible and should be excluded
        if((Adsppm_Status_Success == sts) &&
            (AdsppmBusPort_Adsp_Master != pBwDesc->masterPort))
        {
            sts = ACM_BusBWAggregate(pNonSuppressibleBw, &pBwDesc->bwValue);
            if(Adsppm_Status_Success != sts)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "internal non-supressible BW aggregation failed: %u", sts);
            }
        }
    }

    return sts;
}

static void busMgrAggregateInternalBW(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmBusBWDataIbAbType compTotalBw;

    // Pointers for generic BW votes
    AdsppmBusBWDataIbAbType* pGenTotalBw =
        &gBusMgrCtx.intPreAggregateData.generic.totalBw;
    AdsppmBusBWDataIbAbType* pGenNSBw =
        &gBusMgrCtx.intPreAggregateData.generic.nonSuppressibleBw;

    // Pointers for compensated BW votes
    AdsppmBusBWDataIbAbType* pCompNSBw =
        &gBusMgrCtx.intPreAggregateData.compensated.nonSuppressibleBw;
    AdsppmBusBWDataIbAbType* pCompAdspBw =
        &gBusMgrCtx.intPreAggregateData.compensated.adspMasterBw;
    AdsppmBusBWDataIbAbType* pCompNonAdspBw =
        &gBusMgrCtx.intPreAggregateData.compensated.nonAdspMasterBw;

    // 
    // Intermediate aggregation for internal BW:
    // Aggregate BW for -compensated- BW class.
    // - inputs
    //   (a) pre-aggregated votes for ADSP master
    //   (b) pre-aggregated votes for !ADSP master
    // - compensation table is applied to (a)
    // - output to compTotalBw
    // 

    compTotalBw.Ab = compTotalBw.Ib = 0;

    // Ab: compensated(a)
    sts = ACM_ApplyAhbBwCompensation(pCompAdspBw->Ab, &compTotalBw.Ab);
    if(sts == Adsppm_Status_Success)
    {
        // Ab: compensated(a) + b
        compTotalBw.Ab += pCompNonAdspBw->Ab;
    }
    if(sts == Adsppm_Status_Success)
    {
        // Ib: compensated(a)
        sts = ACM_ApplyAhbBwCompensation(pCompAdspBw->Ib, &compTotalBw.Ib);
        if(sts == Adsppm_Status_Success)
        {
            // Ib: max(compensated(a), b)
            compTotalBw.Ib = MAX(compTotalBw.Ib, pCompNonAdspBw->Ib);
        }
    }

    // 
    // Final aggregation for internal BW:
    //   Separately for total and non-suppressible BW:
    //     Ab = sum(generic vote, compensated vote)
    //     Ib = max(generic vote, compensated vote)
    // 

    // Total ABH BW
    // 
    // curAHBBwData may have initial values, so preserving
    gBusMgrCtx.curAHBBwData.Ab += compTotalBw.Ab + pGenTotalBw->Ab;
    gBusMgrCtx.curAHBBwData.Ib = MAX(gBusMgrCtx.curAHBBwData.Ib, compTotalBw.Ib);
    gBusMgrCtx.curAHBBwData.Ib = MAX(gBusMgrCtx.curAHBBwData.Ib, pGenTotalBw->Ib);

    // Non-suppressible BW.
    // 
    // No compensation is applied, assuming non-suppressible BW never
    // has ADSP as master.
    // nonSuppressibleAhbBW may have initial values, so preserving
    gBusMgrCtx.nonSuppressibleAhbBW.Ab += pCompNSBw->Ab + pGenNSBw->Ab;
    gBusMgrCtx.nonSuppressibleAhbBW.Ib = MAX(gBusMgrCtx.nonSuppressibleAhbBW.Ib, pCompNSBw->Ib);
    gBusMgrCtx.nonSuppressibleAhbBW.Ib = MAX(gBusMgrCtx.nonSuppressibleAhbBW.Ib, pGenNSBw->Ib);
}

static Adsppm_Status busMgrPreAggregateExternalBW(
    BUSMgr_BwDescriptorType *pBwDesc,
    AdsppmBwRequestClass requestClass)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 extRouteIndex = 0;

    // Search corresponding external route
    for(extRouteIndex = 0; extRouteIndex < gBusMgrCtx.extRouteNum; extRouteIndex++)
    {
        if((gBusMgrCtx.pExtRoutes[extRouteIndex].masterPort.adsppmMaster == pBwDesc->masterPort) &&
           (gBusMgrCtx.pExtRoutes[extRouteIndex].slavePort.adsppmSlave == pBwDesc->slavePort))
        {
            if(requestClass == Adsppm_BwReqClass_Compensated)
            {
                sts = ACM_BusBWAggregate(
                    &(gBusMgrCtx.extPreAggregateData.pCompensated[extRouteIndex].bwValue.busBwAbIb),
                    &(pBwDesc->bwValue));

                if((sts == Adsppm_Status_Success) &&
                    (pBwDesc->masterPort == AdsppmBusPort_Adsp_Master) &&
                    (pBwDesc->slavePort == AdsppmBusPort_Ddr_Slave))
                {
                    gBusMgrCtx.extPreAggregateData.numCompensatedAdspDdrVotes += 1;

                    // Get max ADSP to DDR BW requested
                    gBusMgrCtx.extPreAggregateData.maxAdspToDDrBw =
                        MAX(gBusMgrCtx.extPreAggregateData.maxAdspToDDrBw,
                        pBwDesc->bwValue.busBwValue.bwBytePerSec);
                }
            }
            else // if(requestClass == Adsppm_BwReqClass_Generic)
            {
                sts = ACM_BusBWAggregate(
                    &(gBusMgrCtx.extPreAggregateData.pGeneric[extRouteIndex].bwValue.busBwAbIb),
                    &(pBwDesc->bwValue));
            }
            if(Adsppm_Status_Success != sts)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "External BW pre-aggregation failed: %u", sts);
            }
            break;
        }
    }

    if(gBusMgrCtx.extRouteNum == extRouteIndex)
    {
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
            "Invalid external route, M=%u, S=%u",
            pBwDesc->masterPort, pBwDesc->slavePort);
        sts = Adsppm_Status_BadParm;
    }

    return sts;
}


static void busMgrAggregateExternalBW(coreUtils_Q_Type *pBWReqQ)
{
    uint32 extRouteIndex = 0, scalingfactor=0;
    AdsppmBusBWRequestValueType *pAggregate;
    AdsppmBusBWRequestValueType *pPreAggregateGeneric;
    AdsppmBusBWRequestValueType *pPreAggregateCompensated;
    AsicCompensatedDdrBwTableEntryType tableEntry;
    uint64 tempPreAggregateCompensatedAb = 0,tempPreAggregateCompensatedIb = 0;
    uint32 tempPreAggregateCompensatedLatency = 0;
    AsicCompensatedBWFudgeFactor compensatedBWFudgeFactorValues;

    // For each route:
    // Ab = sum(generic vote, compensated vote)
    // Ib = max(generic vote, compensated vote)
    for(extRouteIndex = 0; extRouteIndex < gBusMgrCtx.extRouteNum; extRouteIndex++)
    {

        pAggregate = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][extRouteIndex]);
        pPreAggregateGeneric = &(gBusMgrCtx.extPreAggregateData.pGeneric[extRouteIndex]);
        pPreAggregateCompensated = &(gBusMgrCtx.extPreAggregateData.pCompensated[extRouteIndex]);

        // Compensated BW vote class: apply compensated vote table
        // Compensation only applies if Master port is ADSP and
        // slave port is DDR; otherwise treat as uncompensated
        if(pAggregate->busRoute.masterPort == AdsppmBusPort_Adsp_Master &&
            pAggregate->busRoute.slavePort == AdsppmBusPort_Ddr_Slave)
        {
            //Fudge Factor should only be applied--if there is a new request
            //If fudge factor is called for cache size change initiated by new BW request, this part should be ignored
            if(gBusMgrCtx.externalBwUpdatePending == FALSE)
                {
                    // Apply BW concurrency factor before compensated vote table
                    ACM_ApplyAdspDdrBwConcurrencyFactor(
                        gBusMgrCtx.extPreAggregateData.numCompensatedAdspDdrVotes,
                        gBusMgrCtx.extPreAggregateData.maxAdspToDDrBw,
                        &pPreAggregateCompensated->bwValue.busBwAbIb.Ab,
                        &pPreAggregateCompensated->bwValue.busBwAbIb.Ib,
                        &compensatedBWFudgeFactorValues);

                    if(compensatedBWFudgeFactorValues.floorFudgeFactor && compensatedBWFudgeFactorValues.ceilingFudgeFactor)
                    {
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
                                        "Ab value is more than threshold\n");
                        BusMgr_GetCompensatedFudgedBwValue (pBWReqQ, 
                                                        &pPreAggregateCompensated->bwValue.busBwAbIb.Ab,
                                                        &pPreAggregateCompensated->bwValue.busBwAbIb.Ib,
                                                        &compensatedBWFudgeFactorValues);
                    }
                
                }
            else
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
                                        "Concurrency Factor Calculation Skipped\n");
                }
            tempPreAggregateCompensatedAb = pPreAggregateCompensated->bwValue.busBwAbIb.Ab;
            tempPreAggregateCompensatedIb = pPreAggregateCompensated->bwValue.busBwAbIb.Ib;
            scalingfactor = gBusMgrCtx.scalingfactor;
            tempPreAggregateCompensatedAb = ((tempPreAggregateCompensatedAb * (uint64) scalingfactor)/100ull);
            tempPreAggregateCompensatedIb = ((tempPreAggregateCompensatedIb * (uint64) scalingfactor)/100ull);
            ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
                    "BW Values after scaling factor (compensated): ib=%llu, ab=%llu",
                    (uint32) tempPreAggregateCompensatedIb,
                    (uint32) (tempPreAggregateCompensatedIb >> 32),
                    (uint32) tempPreAggregateCompensatedAb,
                    (uint32) (tempPreAggregateCompensatedAb >> 32));

            ACM_GetCompensatedDdrBwTableEntry(
                MAX(tempPreAggregateCompensatedIb,
                tempPreAggregateCompensatedAb),
                &tableEntry);


            gBusMgrCtx.snocFloorVoteMhz[gBusMgrCtx.preCurrentIndex] =
                tableEntry.snocFloorVoteMhz;

            tempPreAggregateCompensatedLatency = tableEntry.latencyVote;

            // Dishonest ib vote selected
            if(tableEntry.honestFlag == 0)
            {
                // Map ib to dishonest vote from table
                //     ab to dishonest vote equal to 2 times honest vote
                tempPreAggregateCompensatedAb  *= 2;
                tempPreAggregateCompensatedIb = tableEntry.bwVote;
            }

            pAggregate->bwValue.busBwAbIb.Ab        = tempPreAggregateCompensatedAb; 
            pAggregate->bwValue.busBwAbIb.Ib        = tempPreAggregateCompensatedIb;
            pAggregate->bwValue.busBwAbIb.latencyNs = tempPreAggregateCompensatedLatency;                

            }
            else
            {
                pAggregate->bwValue.busBwAbIb.Ab        = pPreAggregateCompensated->bwValue.busBwAbIb.Ab;
                pAggregate->bwValue.busBwAbIb.Ib        = pPreAggregateCompensated->bwValue.busBwAbIb.Ib;
                pAggregate->bwValue.busBwAbIb.latencyNs = pPreAggregateCompensated->bwValue.busBwAbIb.latencyNs;
            }        

        // Generic BW vote class (no compensation)
        pAggregate->bwValue.busBwAbIb.Ab += pPreAggregateGeneric->bwValue.busBwAbIb.Ab;
        pAggregate->bwValue.busBwAbIb.Ib = MAX(
            pPreAggregateGeneric->bwValue.busBwAbIb.Ib,
            pAggregate->bwValue.busBwAbIb.Ib);

    }
}


static void busMgrVoteForAhbBusClocks(AsicBusPortConnectionType portConnection)
{
    if((portConnection & (AsicBusPort_AhbE_M | AsicBusPort_AhbE_S)) && ACM_IsClkIdValid(AdsppmClk_AhbE_Hclk))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbE_Hclk] = Hal_ClkRgmEnable;
    }
    if((portConnection & (AsicBusPort_AhbI_M | AsicBusPort_AhbI_S)) && ACM_IsClkIdValid(AdsppmClk_AhbI_Hclk))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbI_Hclk] = Hal_ClkRgmEnable;
    }
    if((portConnection & (AsicBusPort_AhbX_M | AsicBusPort_AhbX_S)) && ACM_IsClkIdValid(AdsppmClk_AhbX_Hclk))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbX_Hclk] = Hal_ClkRgmEnable;
    }
}


static Adsppm_Status busMgrVoteForRegProgClock(AdsppmClkIdType clkId)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    const AsicClkDescriptorType *pClkDesc = ACMClk_GetClockDescriptorById(clkId);

    if(NULL == pClkDesc)
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
            "Clock descriptor is NULL, clkId=%u", clkId);
        sts = Adsppm_Status_Failed;
    }
    else
    {
        switch(pClkDesc->clkCntlType)
        {
        case AsicClk_CntlSW:
            gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][clkId] = Hal_ClkRgmEnable;
            break;

        case AsicClk_CntlSW_DCG:
            if(AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Ahb_DCG))
            {
                gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][clkId] = Hal_ClkRgmEnable;
            }
            break;

        default:
            break;
        }
    }

    return sts;
}


static Adsppm_Status busMgrAggregateClocks(BUSMgr_BwDescriptorType *pBwDesc)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT,
        "clkM=%u, clkS=%u, clkA=%u",
        pBwDesc->pMPortDescriptor->busClk,
        pBwDesc->pSPortDescriptor->busClk,
        pBwDesc->pAPortDescriptor->busClk);

    if(AdsppmBusBWOperation_RegAccess == pBwDesc->bwOperation)
    {
        uint32 index = 0;
        sts = busMgrVoteForRegProgClock(pBwDesc->pMPortDescriptor->busClk);

        // Aggregate register programming clocks voting from Slave Port
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT,
            "num of regProgClocks=%u",
            pBwDesc->pSPortDescriptor->regProgClocks.numClocks);

        for(index = 0;
            (Adsppm_Status_Success == sts) &&
                (index < pBwDesc->pSPortDescriptor->regProgClocks.numClocks);
            index++)
        {
            sts = busMgrVoteForRegProgClock(pBwDesc->pSPortDescriptor->regProgClocks.pClocks[index]);
        }
    }
    else // pBwDesc->bwOperation == AdsppmBusBWOperation_BW
    {
		if (ACM_IsClkIdValid(pBwDesc->pMPortDescriptor->busClk))
			gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pMPortDescriptor->busClk] = Hal_ClkRgmEnable;
		if (ACM_IsClkIdValid(pBwDesc->pSPortDescriptor->busClk))
			gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pSPortDescriptor->busClk] = Hal_ClkRgmEnable;
		if (ACM_IsClkIdValid(pBwDesc->pAPortDescriptor->busClk))
			gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pAPortDescriptor->busClk] = Hal_ClkRgmEnable;
    }

    if(Adsppm_Status_Success == sts)
    {
        busMgrVoteForAhbBusClocks(pBwDesc->pMPortDescriptor->portConnection);
        busMgrVoteForAhbBusClocks(pBwDesc->pSPortDescriptor->portConnection);
        busMgrVoteForAhbBusClocks(pBwDesc->pAPortDescriptor->portConnection);
    }

    return sts;
}


static Adsppm_Status busMgrAggregateRequest(
    AdsppmBusBWRequestValueType *pBwRequest,
    AdsppmBwRequestClass requestClass)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    BUSMgr_BwDescriptorType bwDesc;
    BUSMgrBwTypeType busMgrBwType = BUSMgr_Bw_None;

    bwDesc.masterPort = pBwRequest->busRoute.masterPort;
    bwDesc.slavePort = pBwRequest->busRoute.slavePort;
    bwDesc.accessPort = AdsppmBusPort_None;
    bwDesc.pMPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.masterPort);
    bwDesc.pSPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.slavePort);
    bwDesc.pAPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.accessPort);
    bwDesc.bwOperation = pBwRequest->bwOperation;
    bwDesc.bwValue = pBwRequest->bwValue;

    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
        "M=%s(%u), S=%s(%u)",
        adsppm_getBusPortName(bwDesc.masterPort), bwDesc.masterPort,
        adsppm_getBusPortName(bwDesc.slavePort), bwDesc.slavePort);

    if((NULL == bwDesc.pMPortDescriptor) ||
        (NULL == bwDesc.pSPortDescriptor) ||
        (NULL == bwDesc.pAPortDescriptor))
    {
        ADSPPM_LOG_PRINTF_6(ADSPPM_LOG_LEVEL_ERROR,
            "Bus route descriptor is NULL, M=%s(%u), S=%s(%u), A=%s(%u)",
            adsppm_getBusPortName(bwDesc.masterPort), bwDesc.masterPort,
            adsppm_getBusPortName(bwDesc.slavePort), bwDesc.slavePort,
            adsppm_getBusPortName(bwDesc.accessPort), bwDesc.accessPort);
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        busMgrBwType = busMgrGetBwType(
            bwDesc.pMPortDescriptor->portConnection,
            bwDesc.pSPortDescriptor->portConnection);

        switch(busMgrBwType)
        {
        case BUSMgr_Bw_None:
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                "None BW type, connectM=%u, connectS=%u",
                bwDesc.pMPortDescriptor->portConnection,
                bwDesc.pSPortDescriptor->portConnection);
            sts = Adsppm_Status_Failed;
            break;

        case BUSMgr_Bw_Internal_External:
            if(0 != (AsicBusPort_Ext_M & bwDesc.pMPortDescriptor->portConnection))
            {
                bwDesc.slavePort = bwDesc.pSPortDescriptor->accessPort;
                bwDesc.accessPort = bwDesc.slavePort;
            }
            else if(0 != (AsicBusPort_Ext_S & bwDesc.pSPortDescriptor->portConnection))
            {
                bwDesc.masterPort = bwDesc.pMPortDescriptor->accessPort;
                bwDesc.accessPort = bwDesc.masterPort;
            }
            bwDesc.pAPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.accessPort);
            if(NULL == bwDesc.pAPortDescriptor)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "Access port descriptor is NULL, accessPort:%u",
                    bwDesc.accessPort);
                sts = Adsppm_Status_Failed;
            }

            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrPreAggregateInternalBW(&bwDesc, requestClass);
            }
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateClocks(&bwDesc);
            }
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrPreAggregateExternalBW(&bwDesc, requestClass);
            }
            break;

        case BUSMgr_Bw_Internal_Only:
            sts = busMgrPreAggregateInternalBW(&bwDesc, requestClass);
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateClocks(&bwDesc);
            }
            break;

        case BUSMgr_Bw_External_Only:
            sts = busMgrPreAggregateExternalBW(&bwDesc, requestClass);
            break;

        default:
             break;
        }
    }

    return sts;
}

Adsppm_Status BusMgr_GetAggregatedBwInfo(AdsppmInfoAggregatedBwType *pBusInfo)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    int index = 0;
    AdsppmBusBWRequestValueType* pBwVote = NULL;

    if(pBusInfo == NULL)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pBusInfo is NULL");
        return Adsppm_Status_BadParm;
    }

    if(gBusMgrCtx.lock == NULL)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        return Adsppm_Status_NotInitialized;
    }

    // Lock for bus manager global data update
    adsppm_lock(gBusMgrCtx.lock);

    for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
    {
        pBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex^1][index]);

        if((AdsppmBusPort_Adsp_Master == pBwVote->busRoute.masterPort) &&
            (AdsppmBusPort_Ddr_Slave == pBwVote->busRoute.slavePort))
        {
            pBusInfo->adspDdrBwAb = pBwVote->bwValue.busBwAbIb.Ab;
            pBusInfo->adspDdrBwIb = pBwVote->bwValue.busBwAbIb.Ib;
        }

        if((AdsppmBusPort_Ext_Ahb_Master == pBwVote->busRoute.masterPort) &&
            (AdsppmBusPort_Ddr_Slave == pBwVote->busRoute.slavePort))
        {
            pBusInfo->extAhbDdrBwAb = pBwVote->bwValue.busBwAbIb.Ab;
            pBusInfo->extAhbDdrBwIb = pBwVote->bwValue.busBwAbIb.Ib;
        }
    }

    // Internal AHB BW
    pBusInfo->intAhbBwAb = gBusMgrCtx.curAHBBwData.Ab;
    pBusInfo->intAhbBwIb = gBusMgrCtx.curAHBBwData.Ib;

    adsppm_unlock(gBusMgrCtx.lock);

    ADSPPM_LOG_PRINTF_8(ADSPPM_LOG_LEVEL_INFO,
        "ADSP-DDR BW: Ab=%llu, Ib=%llu; AHB BW: Ab=%llu, Ib=%llu",
        (uint32) pBusInfo->adspDdrBwAb,
        (uint32) (pBusInfo->adspDdrBwAb >> 32),
        (uint32) pBusInfo->adspDdrBwIb,
        (uint32) (pBusInfo->adspDdrBwIb >> 32),
        (uint32) pBusInfo->intAhbBwAb,
        (uint32) (pBusInfo->intAhbBwAb >> 32),
        (uint32) pBusInfo->intAhbBwIb,
        (uint32) (pBusInfo->intAhbBwIb >> 32));

    return sts;
}


Adsppm_Status BusMgr_GetCompensatedFudgedBwValue(
    coreUtils_Q_Type* pBwRequestQueue,
    uint64* pAb, 
    uint64* pIb,
    AsicCompensatedBWFudgeFactor *pcompensatedBWFudgeFactorValues
    )
{
    RMHandleType* pRequest = NULL;
    uint32 ceilingFF= 0, floorFF=0, abFF=0; 
    uint64 tempAb=0, tempIb = 0, finalAb=0, finalIb=0 ;
    uint32 BwUsageFactor = 0;
    uint64 bwValue =  0;
    AdsppmBusBWDataIbAbType bwValueAbIb;
    AdsppmBusBWDataType *pBwValue;
    Adsppm_Status sts = Adsppm_Status_Success;

    if((pBwRequestQueue == NULL) ||
        (pAb== NULL) ||
        (pIb== NULL) ||
        (pcompensatedBWFudgeFactorValues == NULL))
    {
        return Adsppm_Status_BadParm;
    }
    tempAb = *pAb;
    tempIb = *pIb;

    ceilingFF = (pcompensatedBWFudgeFactorValues->ceilingFudgeFactor * 10/256);//Multiplying by 10 as it is decimal no.
    floorFF = ((pcompensatedBWFudgeFactorValues->floorFudgeFactor * 10)/256);//Multiplying by 10 as it is decimal no.

    // Go through each client's bw request; aggregate the BW requests only for
    // compensated request types
    pRequest = (RMHandleType*) coreUtils_Q_Check(pBwRequestQueue);
    while(pRequest != NULL)
    {
        AdsppmBwReqType* pBwReqData = (AdsppmBwReqType*) pRequest->pRequestData;
        if((pRequest->validFlag == RM_Valid) &&
            (pBwReqData != NULL) &&
            (pBwReqData->requestClass == Adsppm_BwReqClass_Compensated))
        {
            uint32 bwIndex;
            // For each sub-request within current client's request
            for(bwIndex = 0; bwIndex < pBwReqData->numOfBw; bwIndex++)
            {
                AdsppmBusBWRequestValueType* pBwReq =
                    &pBwReqData->pBwArray[bwIndex];
                if((pBwReq->busRoute.masterPort == AdsppmBusPort_Adsp_Master) &&
                    (pBwReq->busRoute.slavePort == AdsppmBusPort_Ddr_Slave))
                {
                    pBwValue = &pBwReq->bwValue; 
                    bwValue = pBwValue->busBwValue.bwBytePerSec;
                    BwUsageFactor = ADSPPM_BW_USAGE_FACTOR; 
                    
                    // Apply bus usage factor to bw
                    bwValue = scale64(bwValue, BwUsageFactor, PERCENTS_IN_A_WHOLE);
                    // Translate bw to ab and ib
                    bwValueAbIb.Ab = scale64(bwValue, pBwValue->busBwValue.usagePercentage, 100);
                    bwValueAbIb.Ib = bwValue;
                    //As per the algorithm, if Ab/Client's Ab is greater than ceiling FF, use "ceiling" fudge factor
                    if(bwValueAbIb.Ab && (((tempAb*10)/bwValueAbIb.Ab) > ceilingFF))
                        {
                            finalAb += ((bwValueAbIb.Ab * ceilingFF)/10);
                            finalIb += ((bwValueAbIb.Ib * ceilingFF)/10);
                        }
                    //As per the algorithm, if Ab/Client's Ab is less than floor FF, use "floor" fudge factor
                    else if (bwValueAbIb.Ab && (((tempAb * 10)/bwValueAbIb.Ab) < floorFF))
                        {
                            finalAb += ((bwValueAbIb.Ab * floorFF)/10);  //Since it is decimal no.
                            finalIb += ((bwValueAbIb.Ib * floorFF)/10);
                        }
                    //As per the algorithm, if Ab/Client's Ab is between ceiling and floor FF, use Ab/Client's Ab as fudge factor
                    else if (bwValueAbIb.Ab)
                        {
                            abFF = ((tempAb * 10)/bwValueAbIb.Ab);
                            finalAb += tempAb;
                            finalIb += ((abFF * bwValueAbIb.Ib)/10);
                        }
                

                }
            }
        }
        pRequest = (RMHandleType*) coreUtils_Q_Next(pBwRequestQueue,
            &pRequest->link);
    }

    *pAb = finalAb;
    *pIb = finalIb;
    
    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
        "After BW Concurrency Adjustment v2 - Ab %llu Ib %llu ",
        (uint32) *pAb, // two params for %llu
        (uint32) (*pAb >> 32),
        (uint32) *pIb, // two params for %llu
        (uint32) (*pIb >> 32));

    return sts;
}


Adsppm_Status BusMgr_GetCompensatedBw(
    coreUtils_Q_Type* pBwRequestQueue,
    AdsppmBusRouteType* pRoute,
    uint64* pTotalRequestedBw)
{
    busMgrCtxType* self = &gBusMgrCtx;
    RMHandleType* pRequest = NULL;
    AdsppmBusBWDataIbAbType aggResult;
    uint32 failCount = 0;
    AsicCompensatedBWFudgeFactor compensatedBWFudgeFactorValues;

    if((pBwRequestQueue == NULL) ||
        (pTotalRequestedBw == NULL) ||
        (pRoute == NULL))
    {
        return Adsppm_Status_BadParm;
    }

    if(self->lock == NULL)
    {
        return Adsppm_Status_NotInitialized;
    }

    memset(&aggResult, 0, sizeof(AdsppmBusBWDataIbAbType));

    ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_BW);

    // Go through each client's bw request; aggregate the BW requests only for
    // compensated request types
    pRequest = (RMHandleType*) coreUtils_Q_Check(pBwRequestQueue);
    while(pRequest != NULL)
    {
        AdsppmBwReqType* pBwReqData = (AdsppmBwReqType*) pRequest->pRequestData;
        if((pRequest->validFlag == RM_Valid) &&
            (pBwReqData != NULL) &&
            (pBwReqData->requestClass == Adsppm_BwReqClass_Compensated))
        {
            uint32 bwIndex;
            // For each sub-request within current client's request
            for(bwIndex = 0; bwIndex < pBwReqData->numOfBw; bwIndex++)
            {
                AdsppmBusBWRequestValueType* pBwReq =
                    &pBwReqData->pBwArray[bwIndex];
                if((pBwReq->busRoute.masterPort == pRoute->masterPort) &&
                    (pBwReq->busRoute.slavePort == pRoute->slavePort))
                {
                    if(ACM_BusBWAggregate(&aggResult, &pBwReq->bwValue) !=
                        Adsppm_Status_Success)
                    {
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
                            "BW aggregation failed");
                        failCount += 1;
                    }
                }
            }
        }
        pRequest = (RMHandleType*) coreUtils_Q_Next(pBwRequestQueue,
            &pRequest->link);
    }

    if((AdsppmBusPort_Adsp_Master == pRoute->masterPort) &&
        (AdsppmBusPort_Ddr_Slave == pRoute->slavePort))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
                "BW Aggregation for ADSP-to-DDR, Get fudged BW val");
        ACM_ApplyAdspDdrBwConcurrencyFactor(
                gBusMgrCtx.extPreAggregateData.numCompensatedAdspDdrVotes,
                gBusMgrCtx.extPreAggregateData.maxAdspToDDrBw,
                &aggResult.Ab, &aggResult.Ib,
                &compensatedBWFudgeFactorValues);

        if(compensatedBWFudgeFactorValues.floorFudgeFactor && compensatedBWFudgeFactorValues.ceilingFudgeFactor)
                {
                    BusMgr_GetCompensatedFudgedBwValue (pBwRequestQueue, 
                                                        &aggResult.Ab,
                                                        &aggResult.Ib,
                                                        &compensatedBWFudgeFactorValues);
                }        
    }

    ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_BW);

    // Query result set to Max of Ab, Ib.
    // This result is used as input for the lookup table.
    *pTotalRequestedBw = MAX(aggResult.Ab, aggResult.Ib);

    return (failCount == 0) ? Adsppm_Status_Success : Adsppm_Status_Failed;
}
/**
*@fn - BusMgrApplyCacheSizeExtCompBWVote - Function used to update ext compensated bw vote
*/
static Adsppm_Status BusMgrApplyCacheSizeExtCompBWVote (uint32 cacheSize)
{
    Adsppm_Status sts = Adsppm_Status_Success;	
    uint32 numUpdatedExtBwVotes=0;	
    AdsppmBusBWRequestValueType updateExtBusBwValue[gBusMgrCtx.extRouteNum];
    // Locals to track change in SNOC floor vote            
    uint32 snocFloorVoteMhz = 0;
    boolean snocFloorChanged = FALSE;

    memset(updateExtBusBwValue, 0, gBusMgrCtx.extRouteNum*sizeof(AdsppmBusBWRequestValueType));
    adsppm_lock(gBusMgrCtx.lock); 
    ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_BW);
    //Go back to old index
    gBusMgrCtx.preCurrentIndex ^= 1;       

    ACM_GetBWScalingFactorFromCacheSize(cacheSize, &gBusMgrCtx.scalingfactor);

    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Scaling Factor is %u",gBusMgrCtx.scalingfactor);
    AdsppmCoreCtxType* pAdsppmCoreCtx = GetAdsppmCoreContext();
    
    busMgrAggregateExternalBW(&pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_BW-1]);
    
    
    gBusMgrCtx.externalBwUpdatePending = FALSE;

    numUpdatedExtBwVotes = busMgr_ProcessExternalBWInfo(&updateExtBusBwValue[0], &snocFloorChanged, &snocFloorVoteMhz);

    //Go back on previously set buffer
    gBusMgrCtx.preCurrentIndex ^= 1;
    ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_BW);
    adsppm_unlock(gBusMgrCtx.lock);

    //Send Final bw infor to ICB
    busMgr_SendExternalBWInfo(numUpdatedExtBwVotes,&updateExtBusBwValue[0], snocFloorChanged,snocFloorVoteMhz);
    	
    return sts;
}
/**
* @fn - bmOnCPManagerUpdate - Check for change in active client classes, and if there is a change, select
* a new cache partitioning configuration based on the new mix of client 
*	classes
*/ 
static void bmOnCPManagerUpdate(AdsppmCachePartitionManagerEventId eventId,void * param)
{

    busMgrCtxType *self =
        (busMgrCtxType *) param;
    uint32 cachepartitionsize = 0;

    if(self && eventId == CPM_CACHE_CONFIGURATION_CHANGE)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "BW request due to change in cache size");
        // Get the current partition size
        if (Adsppm_Status_Success == CPM_GetCachePartitionSize(&cachepartitionsize))
            BusMgrApplyCacheSizeExtCompBWVote(cachepartitionsize);
        else
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "CPM cache size returned invalid value; skipping bw scaling");
     }
}

