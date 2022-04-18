/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: extbwmgr.c
@brief: Implementation of ADSPPM External Bandwidth Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/qdsp_pm_mgr/resource_mgr/extbwmgr.c#1 $
*/

#include "adsppm.h"
#include "adsppm_utils.h"
#include "dcvsmgr.h"
#include "hal_busdrv.h"
#include "sysmon_dcvs_adsppm.h"
#include "usleepmgr.h"


// All state info for the External BW Manager
typedef struct
{
    DALSYSSyncHandle lock;
    boolean dcvsEnabledDisabledFlag;
    AdsppmBusBWDataIbAbType dcvsVote;
    AdsppmBusBWDataIbAbType clientsFloorVote;
    AdsppmBusBWDataIbAbType clientsFinalVote;
    AdsppmBusBWDataIbAbType finalVoteToNpa;
} AdsppmExtBwManagerType;

static AdsppmExtBwManagerType gAdsppmExtBwManager;

///////////////////////////////////////////////////////////////////////////////
// Static functions
///////////////////////////////////////////////////////////////////////////////

// Calculate new vote to NPA
// Assume lock is obtained
static void extBwMgr_CalculateNewNpaVote(
    AdsppmExtBwManagerType* self,
    AdsppmBusBWDataIbAbType* pNewClientsFinalVote,
    AdsppmBusBWDataIbAbType* pNewClientsFloorVote,
    AdsppmBusBWDataIbAbType* pNewFinalVoteToNpa)
{

    AdsppmBusBWDataIbAbType previousClientsFinalVote = self->clientsFinalVote;
    boolean changeInClientFinalVote =
        ((pNewClientsFinalVote->Ib != previousClientsFinalVote.Ib) ||
            (pNewClientsFinalVote->Ab != previousClientsFinalVote.Ab));

    if(self->dcvsVote.Ib || self->dcvsVote.Ab)
    {
        pNewFinalVoteToNpa->Ib = changeInClientFinalVote?
            MAX(pNewClientsFinalVote->Ib, self->dcvsVote.Ib):
            MAX(pNewClientsFloorVote->Ib, self->finalVoteToNpa.Ib);
        pNewFinalVoteToNpa->Ab = changeInClientFinalVote?
            MAX(pNewClientsFinalVote->Ab, self->dcvsVote.Ab):
            MAX(pNewClientsFloorVote->Ab, self->finalVoteToNpa.Ab);
    }

}

// Print current context values
// Assume lock is obtained
static void extBwMgr_PrintContext(
    AdsppmExtBwManagerType* self)
{

    if(self->dcvsEnabledDisabledFlag)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "DCVS Enabled:");
        ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
            "   Current DCVS vote:          ib=%llu, ab=%llu",
            (uint32) self->dcvsVote.Ib,
            (uint32) (self->dcvsVote.Ib >> 32),
            (uint32) self->dcvsVote.Ab,
            (uint32) (self->dcvsVote.Ab >> 32));
        ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
            "   Current Clients Floor vote: ib=%llu, ab=%llu",
            (uint32) self->clientsFloorVote.Ib,
            (uint32) (self->clientsFloorVote.Ib >> 32),
            (uint32) self->clientsFloorVote.Ab,
            (uint32) (self->clientsFloorVote.Ab >> 32));
        ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
            "   Current Clients Final vote: ib=%llu, ab=%llu",
            (uint32) self->clientsFinalVote.Ib,
            (uint32) (self->clientsFinalVote.Ib >> 32),
            (uint32) self->clientsFinalVote.Ab,
            (uint32) (self->clientsFinalVote.Ab >> 32));
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "DCVS Disabled");
    }

}

// Check changes in final vote to NPA
// Assume lock is obtained
static boolean extBwMgr_checkChangeInFinalVoteToNpa(
    AdsppmExtBwManagerType* self,
    AdsppmBusBWDataIbAbType* pNewFinalVoteToNpa)
{

    boolean result = FALSE;

    if((pNewFinalVoteToNpa->Ib != self->finalVoteToNpa.Ib) ||
        (pNewFinalVoteToNpa->Ab != self->finalVoteToNpa.Ab) ||
        (pNewFinalVoteToNpa->latencyNs != self->finalVoteToNpa.latencyNs))
    {
        self->finalVoteToNpa = *pNewFinalVoteToNpa;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
            "Send new ADSP to DDR BW to HAL");

        extBwMgr_PrintContext(self);

        result = TRUE;
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
            "NO updates on ADSP to DDR BW");

        result = FALSE;
    }

    ADSPPM_LOG_PRINTF_5(ADSPPM_LOG_LEVEL_INFO,
        "   Current vote to NPA: ib=%llu, ab=%llu, latency=%u",
        (uint32) self->finalVoteToNpa.Ib,
        (uint32) (self->finalVoteToNpa.Ib >> 32),
        (uint32) self->finalVoteToNpa.Ab,
        (uint32) (self->finalVoteToNpa.Ab >> 32),
        self->finalVoteToNpa.latencyNs);

    return result;

}

// Check for changes in ADSP to DDR BW vote
// if there is a change, update local variable
static void extBwMgr_onAdspToDdrBwVoteUpdate(
    AdsppmDcvsManagerEventId eventId,
    void* param)
{

    AdsppmExtBwManagerType* self = (AdsppmExtBwManagerType*) param;
    AdsppmBusBWRequestValueType newFinalVoteToNpa;
    boolean changeInFinalVoteToNpa = FALSE;
    AdsppmBusBWDataIbAbType dcvsVote;

    if(eventId != DCVSMGR_ADSP_TO_DDR_BW_VOTE_CHANGE_EVENT)
        return;

    DcvsMgr_GetDcvsAdsp2DdrBwVote(&dcvsVote);

    adsppm_lock(self->lock);

    newFinalVoteToNpa.busRoute.masterPort = AdsppmBusPort_Adsp_Master;
    newFinalVoteToNpa.busRoute.slavePort = AdsppmBusPort_Ddr_Slave;
    newFinalVoteToNpa.bwOperation = AdsppmBusBWOperation_BW;
    newFinalVoteToNpa.bwValue.busBwAbIb = self->clientsFinalVote;

    if(self->dcvsEnabledDisabledFlag)
    {
        // update self->dcvsVote
        self->dcvsVote = dcvsVote;

        if(self->dcvsVote.Ib || self->dcvsVote.Ab)
        {
            newFinalVoteToNpa.bwValue.busBwAbIb.Ib = MAX(
                self->clientsFloorVote.Ib, self->dcvsVote.Ib);
            newFinalVoteToNpa.bwValue.busBwAbIb.Ab = MAX(
                self->clientsFloorVote.Ab, self->dcvsVote.Ab);
        }
    }

    if(USleepMgr_GetUSleepVoteEnabled())
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "Usleep Enabled, discard dcvs Ab Vote");
        newFinalVoteToNpa.bwValue.busBwAbIb.Ab = 0;
    }
    changeInFinalVoteToNpa = extBwMgr_checkChangeInFinalVoteToNpa(
        self, &newFinalVoteToNpa.bwValue.busBwAbIb);

    adsppm_unlock(self->lock);

    // Send final ADSP to DDR BW vote to HAL
    if(changeInFinalVoteToNpa)
        Bus_IssueBWRequest(1, &newFinalVoteToNpa);

}

// Check for changes in DCVS' enabled/disabled flag
// if there is a change, update local variable
static void extBwMgr_onDcvsEnabledDisabledUpdate(
    AdsppmDcvsManagerEventId eventId,
    void* param)
{

    AdsppmExtBwManagerType* self = (AdsppmExtBwManagerType*) param;
    boolean dcvsEnabledDisabledFlag = DcvsMgr_GetDcvsEnabledDisabledFlag();

    adsppm_lock(self->lock);

    // update self->dcvsEnabledDisabledFlag
    self->dcvsEnabledDisabledFlag = dcvsEnabledDisabledFlag;

    if(!dcvsEnabledDisabledFlag)
    {
        self->dcvsVote.Ib = 0;
        self->dcvsVote.Ab = 0;
    }

    adsppm_unlock(self->lock);

}

// Send updated clients final vote to SysMon DCVS
// using SysMon DCVS API
static void extBwMgr_SendNewClientsFinalVoteToDcvs(
    AdsppmBusBWDataIbAbType* pNewClientsFinalVote)
{

    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
        "Send new clients final vote to DCVS: ib=%llu, ab=%llu",
        (uint32) pNewClientsFinalVote->Ib,
        (uint32) (pNewClientsFinalVote->Ib >> 32),
        (uint32) pNewClientsFinalVote->Ab,
        (uint32) (pNewClientsFinalVote->Ab >> 32));

    // Call SysMon DCVS API to update client's DDR BW vote to DCVS
    sd_adsppm_vote_t adsp2DdrBw;
    adsp2DdrBw.busVoteinAbIb.uIb = pNewClientsFinalVote->Ib;
    adsp2DdrBw.busVoteinAbIb.uAb = pNewClientsFinalVote->Ab;

    sysmon_adsppm_static_vote_update(
        SYSMON_DCVS_RSC_ID_ADSP_DDR_BW, &adsp2DdrBw);


}

///////////////////////////////////////////////////////////////////////////////
// Public functions
///////////////////////////////////////////////////////////////////////////////

Adsppm_Status ExtBwMgr_Init(void)
{

    AdsppmExtBwManagerType* self = &gAdsppmExtBwManager;

    memset(self, 0, sizeof(AdsppmExtBwManagerType));

    if(DAL_SUCCESS != DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        &self->lock,
        NULL))
    {
        return Adsppm_Status_Failed;
    }

    if(ACM_GetFeatureStatus(AsicFeatureId_DcvsControl) ==
        AsicFeatureState_Enabled)
    {
        if(DcvsMgr_RegisterEvent(
                DCVSMGR_DCVS_ENABLED_DISABLED_CHANGE_EVENT,
                extBwMgr_onDcvsEnabledDisabledUpdate,
                (void*) self) !=
            Adsppm_Status_Success)
        {
            return Adsppm_Status_Failed;
        }

        if(DcvsMgr_RegisterEvent(
                DCVSMGR_ADSP_TO_DDR_BW_VOTE_CHANGE_EVENT,
                extBwMgr_onAdspToDdrBwVoteUpdate,
                (void*) self) !=
            Adsppm_Status_Success)
        {
            return Adsppm_Status_Failed;
        }
    }

    return Adsppm_Status_Success;

}

Adsppm_Status ExtBwMgr_IssueExtBwRequest(
    uint32 numUpdatedExtBwVotes,
    AdsppmBusBWRequestValueType* pUpdatedExtBusBwValues,
    AdsppmBusBWDataIbAbType* pNewClientsFloorVote)
{

    AdsppmExtBwManagerType* self = &gAdsppmExtBwManager;
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmBusBWRequestValueType newFinalVoteToNpa;
    boolean changeInFinalVoteToNpa = FALSE;
    boolean sendClientVoteToDcvs = FALSE;

    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
        "DCVS, clients floor value: ib=%llu, ab=%llu",
        (uint32) pNewClientsFloorVote->Ib,
        (uint32) (pNewClientsFloorVote->Ib >> 32),
        (uint32) pNewClientsFloorVote->Ab,
        (uint32) (pNewClientsFloorVote->Ab >> 32));

    // Find new clients final vote
    AdsppmBusBWDataIbAbType newClientsFinalVote;
    int i = 0;
    boolean foundNewClientsVote = FALSE;

    newClientsFinalVote.Ib = 0;
    newClientsFinalVote.Ab = 0;
    newClientsFinalVote.latencyNs = 0;

    for(i = 0; i < numUpdatedExtBwVotes; i++)
    {
        if((pUpdatedExtBusBwValues[i].busRoute.masterPort ==
                AdsppmBusPort_Adsp_Master) &&
            (pUpdatedExtBusBwValues[i].busRoute.slavePort ==
                AdsppmBusPort_Ddr_Slave))
        {
            foundNewClientsVote = TRUE;
            newClientsFinalVote = pUpdatedExtBusBwValues[i].bwValue.busBwAbIb;

            // ADSP BW to DDR will be issued separately
            pUpdatedExtBusBwValues[i].busRoute.masterPort = AdsppmBusPort_None;
            pUpdatedExtBusBwValues[i].busRoute.slavePort = AdsppmBusPort_None;

            break;
        }
    }

    if(foundNewClientsVote)
    {
        newFinalVoteToNpa.busRoute.masterPort = AdsppmBusPort_Adsp_Master;
        newFinalVoteToNpa.busRoute.slavePort = AdsppmBusPort_Ddr_Slave;
        newFinalVoteToNpa.bwOperation = AdsppmBusBWOperation_BW;
        newFinalVoteToNpa.bwValue.busBwAbIb = newClientsFinalVote;

        adsppm_lock(self->lock);

        if(self->dcvsEnabledDisabledFlag &&
            (newClientsFinalVote.Ib || newClientsFinalVote.Ab))
        {
            sendClientVoteToDcvs =
                ((newClientsFinalVote.Ib != self->clientsFinalVote.Ib) ||
                (newClientsFinalVote.Ab != self->clientsFinalVote.Ab));

            extBwMgr_CalculateNewNpaVote(self, &newClientsFinalVote,
                pNewClientsFloorVote, &newFinalVoteToNpa.bwValue.busBwAbIb);
        }

        // Store new clients final and floor vote
        self->clientsFinalVote = newClientsFinalVote;
        self->clientsFloorVote = *pNewClientsFloorVote;

        if(USleepMgr_GetUSleepVoteEnabled())
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "Usleep Enabled, discard dcvs Ab Vote");
            newFinalVoteToNpa.bwValue.busBwAbIb.Ab = 0;
        }
        changeInFinalVoteToNpa = extBwMgr_checkChangeInFinalVoteToNpa(
            self, &newFinalVoteToNpa.bwValue.busBwAbIb);

        adsppm_unlock(self->lock);
    }

    // Send ADSP to DDR BW to HAL
    if((sts == Adsppm_Status_Success) && changeInFinalVoteToNpa)
        sts = Bus_IssueBWRequest(1, &newFinalVoteToNpa);

    // Send non ADSP to DDR external BW votes to HAL
    if((sts == Adsppm_Status_Success) && numUpdatedExtBwVotes)
        sts = Bus_IssueBWRequest(numUpdatedExtBwVotes, pUpdatedExtBusBwValues);

    // Update SysMon DCVS with new clients final vote
    if((sts == Adsppm_Status_Success) && sendClientVoteToDcvs)
        extBwMgr_SendNewClientsFinalVoteToDcvs(&newClientsFinalVote);

    return sts;

}

Adsppm_Status ExtBwMgr_GetInfo(AdsppmInfoDcvsAdspDdrBwType* pDcvsAdspDdrBwInfo)
{

    AdsppmExtBwManagerType* self = &gAdsppmExtBwManager;

    if(pDcvsAdspDdrBwInfo == NULL)
        return Adsppm_Status_NullPointer;

    adsppm_lock(self->lock);
    pDcvsAdspDdrBwInfo->dcvsVote         = self->dcvsVote;
    pDcvsAdspDdrBwInfo->clientsFloorVote = self->clientsFloorVote;
    pDcvsAdspDdrBwInfo->clientsFinalVote = self->clientsFinalVote;
    pDcvsAdspDdrBwInfo->finalVoteToNpa   = self->finalVoteToNpa;
    adsppm_unlock(self->lock);

    return Adsppm_Status_Success;

}

void ExtBwMgr_UpdateAdsptoDDrClientFloorVotes( AdsppmBusBWDataIbAbType* pNewClientsFloorVote)
{
	
	AdsppmExtBwManagerType* self = &gAdsppmExtBwManager;
    	
	if(NULL != pNewClientsFloorVote)
	{
		if(NULL != self)
		{	
			adsppm_lock(self->lock);
			
			//Update Clients floor vote
             ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
            "Current Clients floor Votes : Ib=%llu, Ab=%llu",
            (uint32) self->clientsFloorVote.Ib,
            (uint32) (self->clientsFloorVote.Ib >> 32),
            (uint32) self->clientsFloorVote.Ab,
            (uint32) (self->clientsFloorVote.Ab >> 32));
            
			self->clientsFloorVote = *pNewClientsFloorVote;
            
            ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO,
            "New Clients floor Votes : Ib=%llu, Ab=%llu",
            (uint32) self->clientsFloorVote.Ib,
            (uint32) (self->clientsFloorVote.Ib >> 32),
            (uint32) self->clientsFloorVote.Ab,
            (uint32) (self->clientsFloorVote.Ab >> 32));
			adsppm_unlock(self->lock);
		}
	}
}