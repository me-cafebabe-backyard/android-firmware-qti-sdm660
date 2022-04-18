/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: dcvsmgr.c
@brief: Implementation of ADSPPM DCVS Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/qdsp_pm_mgr/resource_mgr/dcvsmgr.c#1 $
*/

#include "adsppm.h"
#include "adsppm_utils.h"
#include "dcvsmgr.h"
#include "observer.h"
#include "clientmgr.h"
#include "requestmgr.h"
#include "sysmon_dcvs_adsppm.h"


// All state info for the DCVS Manager
typedef struct
{
    DALSYSSyncHandle lock;
    AdsppmClientsDcvsParticipationType clientsDcvsParticipation;
    boolean dcvsEnabledDisabledFlag;
    AdsppmBusBWDataIbAbType dcvsAdsp2DdrBwVote;
    uint32 dcvsAdspClockVote;
    AdsppmObserverStateType observerState;
} AdsppmDcvsManagerType;

static AdsppmDcvsManagerType gAdsppmDcvsManager;

///////////////////////////////////////////////////////////////////////////////
// Static functions
///////////////////////////////////////////////////////////////////////////////

// Notify all registered observers of the specified event
static void dvcsMgr_notify(
    AdsppmDcvsManagerType* self,
    AdsppmDcvsManagerEventId eventId)
{
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO,
        "updating observers on event %d", eventId);
    observer_notify(&self->observerState, eventId);
    return;
}

// Callback function for change in ADSPPM client class.
// If there is a change, Notify sysmon, the change in
// the aggregate client class.
static void dvcsMgr_onActiveClientClassChange(
        AdsppmClientManagerEventId eventId,
        void *param)
{
    if (eventId != CM_ACTIVE_CLASS_CHANGE_EVENT)
        return;

    sysmon_adsppm_client_class_update(CM_GetActiveUseCaseClasses());

    return;
}

// Check for changes in ADSPPM clients' DCVS participation
// if there is a change, disable/enable DCVS accordingly
// and update corresponding aggregation managers
static void dvcsMgr_onDcvsParticipationUpdate(
    AdsppmClientManagerEventId eventId,
    void* param)
{

    AdsppmDcvsManagerType* self = (AdsppmDcvsManagerType*) param;
    AdsppmClientsDcvsParticipationType newClientsDcvsParticipation =
        CM_GetClientsDcvsParticipation();
    boolean changeInDcvsEnableDisable = FALSE;
    boolean dcvsEnableDisable = FALSE;
    boolean needAdspClockUpdate = FALSE;
    boolean needAdspDdrBwUpdate = FALSE;

    if(eventId != CM_DCVS_PARTICIPATION_CHANGE_EVENT)
        return;

    adsppm_lock(self->lock);

    // Enable/Disable SysMon DCVS
    if(!self->dcvsEnabledDisabledFlag &&
        (newClientsDcvsParticipation.numOfAdspDdrBwActiveDcvsClients ||
            newClientsDcvsParticipation.numOfMipsActiveDcvsClients))
    {
        self->dcvsEnabledDisabledFlag = TRUE;
        changeInDcvsEnableDisable = TRUE;
        dcvsEnableDisable = TRUE;
    }

    if(self->dcvsEnabledDisabledFlag &&
        !(newClientsDcvsParticipation.numOfAdspDdrBwActiveDcvsClients ||
            newClientsDcvsParticipation.numOfMipsActiveDcvsClients))
    {
        self->dcvsEnabledDisabledFlag = FALSE;
        changeInDcvsEnableDisable = TRUE;
        dcvsEnableDisable = FALSE;

        // If last release was BW, need to update ADSP clock vote
        if(self->clientsDcvsParticipation.numOfAdspDdrBwActiveDcvsClients)
            needAdspClockUpdate = TRUE;

        // If last release was MIPS, need to update ADSP DDR BW vote
        if(self->clientsDcvsParticipation.numOfMipsActiveDcvsClients)
            needAdspDdrBwUpdate = TRUE;

        // Reset DCVS votes
        self->dcvsAdsp2DdrBwVote.Ib = 0;
        self->dcvsAdsp2DdrBwVote.Ab = 0;
        self->dcvsAdspClockVote = 0;
    }

    self->clientsDcvsParticipation = newClientsDcvsParticipation;

    adsppm_unlock(self->lock);

    // Notify registered observers that DCVS enabled/disabled flag changed
    if(changeInDcvsEnableDisable)
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO,
            "%s SysMon DCVS and notify observers",
            dcvsEnableDisable?"Enable":"Disable");


        // Call SysMon DCVS API to enable/disable DCVS
        sysmon_adsppm_dcvs_state_change_request((dcvsEnableDisable?
            SYSMON_DCVS_STATE_ENABLE:SYSMON_DCVS_STATE_DISABLE));


        dvcsMgr_notify(self, DCVSMGR_DCVS_ENABLED_DISABLED_CHANGE_EVENT);
    }

    // Notify observers the need to update ADSP clock vote
    if(needAdspClockUpdate)
        dvcsMgr_notify(self, DCVSMGR_ADSP_CLOCK_VOTE_CHANGE_EVENT);

    // Notify observers the need to update ADSP DDR BW vote
    if(needAdspDdrBwUpdate)
        dvcsMgr_notify(self, DCVSMGR_ADSP_TO_DDR_BW_VOTE_CHANGE_EVENT);

}

///////////////////////////////////////////////////////////////////////////////
// Public functions
///////////////////////////////////////////////////////////////////////////////

Adsppm_Status DcvsMgr_Init(void)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;

    memset(self, 0, sizeof(AdsppmDcvsManagerType));

    if(DAL_SUCCESS != DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        &self->lock,
        NULL))
    {
        return Adsppm_Status_Failed;
    }

    if(observer_init(&self->observerState) != Adsppm_Status_Success)
        return Adsppm_Status_Failed;

    if(ACM_GetFeatureStatus(AsicFeatureId_DcvsControl) ==
        AsicFeatureState_Enabled)
    {
        if(CM_RegisterEvent(
                CM_DCVS_PARTICIPATION_CHANGE_EVENT,
                dvcsMgr_onDcvsParticipationUpdate,
                (void*) self) !=
            Adsppm_Status_Success)
        {
            return Adsppm_Status_Failed;
        }

        if(CM_RegisterEvent(
                CM_ACTIVE_CLASS_CHANGE_EVENT,
                dvcsMgr_onActiveClientClassChange,
                (void*) self) !=
            Adsppm_Status_Success)
        {
            return Adsppm_Status_Failed;
        }
    }

    return Adsppm_Status_Success;

}

boolean DcvsMgr_GetDcvsEnabledDisabledFlag(void)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;
    boolean result;

    adsppm_lock(self->lock);
    result = self->dcvsEnabledDisabledFlag;
    adsppm_unlock(self->lock);

    return result;

}

void DcvsMgr_GetDcvsAdsp2DdrBwVote(AdsppmBusBWDataIbAbType *pDcvsVote)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;

    adsppm_lock(self->lock);
    *pDcvsVote = self->dcvsAdsp2DdrBwVote;
    adsppm_unlock(self->lock);

}

void DcvsMgr_GetDcvsAdspClockVote(uint32 *pDcvsVote)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;

    adsppm_lock(self->lock);
    *pDcvsVote = self->dcvsAdspClockVote;
    adsppm_unlock(self->lock);

}

void DcvsMgr_SysMonDcvsAdsp2DdrBwRequest(
    AdsppmBusBWDataIbAbType *pAdsp2DdrBwIbAb)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;

    adsppm_lock(self->lock);
    self->dcvsAdsp2DdrBwVote = *pAdsp2DdrBwIbAb;
    adsppm_unlock(self->lock);

    dvcsMgr_notify(self, DCVSMGR_ADSP_TO_DDR_BW_VOTE_CHANGE_EVENT);

}

void DcvsMgr_SysMonDcvsAdspClockRequest(
    uint32 adspClockHz)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;

    adsppm_lock(self->lock);
    self->dcvsAdspClockVote = adspClockHz;
    adsppm_unlock(self->lock);

    dvcsMgr_notify(self, DCVSMGR_ADSP_CLOCK_VOTE_CHANGE_EVENT);

}

Adsppm_Status DcvsMgr_RegisterEvent(
    AdsppmDcvsManagerEventId event,
    AdsppmDcvsEventHandler handler, void* param)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;
    // Assuming AdsppmDcvsEventHandler can be cast to AdsppmEventHandler
    return observer_add(
        &self->observerState, event,
        (AdsppmEventHandler) handler, param);

}

Adsppm_Status DcvsMgr_UnregisterEvent(
    AdsppmDcvsManagerEventId event,
    AdsppmDcvsEventHandler handler)
{

    AdsppmDcvsManagerType* self = &gAdsppmDcvsManager;
    // Assuming AdsppmDcvsEventHandler can be cast to AdsppmEventHandler
    return observer_remove(
        &self->observerState, event,
        (AdsppmEventHandler) handler);

}

