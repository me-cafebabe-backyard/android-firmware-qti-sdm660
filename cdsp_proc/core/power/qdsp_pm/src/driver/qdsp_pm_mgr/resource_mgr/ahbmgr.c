/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: ahbmgr.c
@brief: ADSPPM ahb manager implementation.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/qdsp_pm_mgr/resource_mgr/ahbmgr.c#1 $
*/

#include "adsppm.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "ahbmgr.h"
#include "core_internal.h"
#include "hal_clkrgm.h"
#include "adspclkmgr.h"
#include "asic.h"


#define AHBMGR_XO_FREQ_HZ 19200000

/**
 * @struct ahb management context
 */
typedef struct
{
   uint32           preAHBClock; //!< Clock currently set
   uint32           activeAHBClock; //!< Clock calculated based on aggregated clock accounting for execution state (periodic vs non-periodic)
   uint32           aggregatedAHBClock; //!< Clock calculated based on BW requirements only for all clients
   uint32           nonSuppressibleAHBClock; //!< Clock calculated based on BW requirements only for non-suppressible clients
   uint32           ahbeClockFreq; //!< Current setting for AHBE frequency (Hz)
   DALSYSSyncHandle lock;
} ahbMgrCtxType;

static ahbMgrCtxType gAhbMgrCtx;


static Adsppm_Status ahbm_SetAHBIXClock(ahbMgrCtxType* self, uint32 ahbixClock)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    if((self->preAHBClock != ahbixClock) && ACM_IsClkIdValid(AdsppmClk_Ahb_Root))
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "AHBIX clock: %u", ahbixClock);
        sts = ClkRgm_SetClock(AdsppmClk_Ahb_Root, ahbixClock);
        if(sts == Adsppm_Status_Success)
        {
            self->preAHBClock = ahbixClock;
        }
    }
    return sts;
}

static Adsppm_Status ahbm_SetAHBEClock(ahbMgrCtxType* self, uint32 ahbeClock)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    if(ACM_GetFeatureStatus(AsicFeatureId_AhbeScaling) ==
        AsicFeatureState_Enabled)
    {
        Adsppm_Status sts = Adsppm_Status_Success;
        if((self->ahbeClockFreq != ahbeClock) && ACM_IsClkIdValid(AdsppmClk_AhbE_Hclk))
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "AHBE clock: %u", ahbeClock);
            sts = ClkRgm_SetClock(AdsppmClk_AhbE_Hclk, ahbeClock);
            if(sts == Adsppm_Status_Success)
            {
                self->ahbeClockFreq = ahbeClock;
            }
        }
    }
    return sts;
}

static void tryAhbeFrequencyUpdate(ahbMgrCtxType* self)
{
    uint32 adspFreq = 0;
    uint32 newAhbeClockFreq = 0;
    // Get current ADSP frequency
    if(AdspClkMgr_GetAdspClockFreqVote(&adspFreq) == Adsppm_Status_Success)
    {
        // Look up AHBE frequency using ADSP frequency
        if(ACM_GetAhbeFromAdspFreq(adspFreq, &newAhbeClockFreq) ==
            Adsppm_Status_Success)
        {
            if(self->ahbeClockFreq != newAhbeClockFreq)
            {
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, 
                    "ADSP: %d Hz -> AHB-E: %d Hz", adspFreq, newAhbeClockFreq);
            }
            ahbm_SetAHBEClock(self, newAhbeClockFreq);
        }
    }
}

// Handler for ADSP clock change events.  This updates the AHB-E bus frequency
// if there is a change required due to the ADSP clock change.
static void onAdspClockChange(AdsppmAdspClkManagerEventId event, void* param)
{
    ahbMgrCtxType* self = (ahbMgrCtxType*) param;
    if(event == ADSPCLKMGR_CLOCK_CHANGE_EVENT)
    {
        tryAhbeFrequencyUpdate(self);
    }
}

/**
 * @fn AHBM_Init - Initialize the AHB Manager.  Requires the ADSP Clock Manager
 *                 to be initialized already.
 * @return Adsppm_Status_Failed
 * @return Adsppm_Status_Success
 */
Adsppm_Status AHBM_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ahbMgrCtxType* self = &gAhbMgrCtx;
    
    self->preAHBClock = 0;
    self->activeAHBClock = 0;
    self->aggregatedAHBClock = 0;
    self->nonSuppressibleAHBClock = 0;
    self->ahbeClockFreq = 0;
    self->lock = NULL;

    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, (DALSYSSyncHandle *)&self->lock, NULL))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create lock");
        sts = Adsppm_Status_Failed;
    }

    // Requires ADSP Clock Manager to be initialized already
    if(ACM_GetFeatureStatus(AsicFeatureId_AhbeScaling) ==
        AsicFeatureState_Enabled)
    {
        // Scale AHB-E according to current ADSP core frequency
        tryAhbeFrequencyUpdate(self);
        // Register for any subsequent changes to ADSP core frequency
        AdspClkMgr_RegisterEvent(ADSPCLKMGR_CLOCK_CHANGE_EVENT,
            onAdspClockChange, self);
    }
    
    return sts;
}

Adsppm_Status AHBM_SetSleepAHBClock(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ahbMgrCtxType* self = &gAhbMgrCtx;
	uint32 sleepAhbClockFreq = self->nonSuppressibleAHBClock;
	uint32 sleepAhbEClockFreq = AHBMGR_XO_FREQ_HZ;
	AsicFeatureDescType *pDesc = NULL;
	AdsppmBusBWDataIbAbType minAHBBwVal;

    // Scale down AHBIX clock

    // WORKAROUND: for HW issue QCTDD00667975
    // Slimbus requires AHB bus freq to be at least 7.4 MHz even in sleep
    // The following logic uses adsppm internal counters to check whether slimbus core clocks are ON
    // If they are found to be ON, choose the max between 7.4 MHz and current aggregated ahb freq
    // Otherwise, use current aggregated ahb freq

    uint32 slimbusCore1ClockFreq = 0;
    uint32 slimbusCore2ClockFreq = 0;

    // Note: Targets with no Slimbus HW will return Freq = 0 on ClkRgm_GetClockFrequency() call
    if (ACM_IsClkIdValid(AdsppmClk_Slimbus_Core))
		ClkRgm_GetClockFrequency(AdsppmClk_Slimbus_Core, &slimbusCore1ClockFreq);

	if (ACM_IsClkIdValid(AdsppmClk_Slimbus2_Core))
	    ClkRgm_GetClockFrequency(AdsppmClk_Slimbus2_Core, &slimbusCore2ClockFreq);

    sleepAhbClockFreq =
        ((0 < slimbusCore1ClockFreq) || (0 < slimbusCore2ClockFreq))?
        MAX(self->nonSuppressibleAHBClock, 7400000):
        self->nonSuppressibleAHBClock;

	/* Limit the AHB-I clock to min value supported */
	if ((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_Ahb_Scaling)))
	{
		pDesc = ACM_GetFeatureDescriptor(AsicFeatureId_Ahb_Scaling);
		if (pDesc) {
			/* Using min value for Ab & Ib */
			minAHBBwVal.Ab = pDesc->min;
			minAHBBwVal.Ib = pDesc->min;
			minAHBBwVal.latencyNs = 0;
			sts = ACM_GetClockFromBW(&sleepAhbClockFreq, &minAHBBwVal);
		}
	}

	/* Limit the AHB-X clock to min value supported */
	if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_AhbeScaling)))
	{
		pDesc = ACM_GetFeatureDescriptor(AsicFeatureId_AhbeScaling);
		if (pDesc) {
			/* Using min value for Ab & Ib */
			minAHBBwVal.Ab = pDesc->min;
			minAHBBwVal.Ib = pDesc->min;
			minAHBBwVal.latencyNs = 0;
			sts = ACM_GetClockFromBW(&sleepAhbEClockFreq, &minAHBBwVal);
		}
	}

	sts = ahbm_SetAHBIXClock(self, sleepAhbClockFreq);

    // Scale down AHBE clock
    if(sts == Adsppm_Status_Success)
    {
        sts = ahbm_SetAHBEClock(self, sleepAhbEClockFreq);
    }

    return sts;
}

Adsppm_Status AHBM_SetActiveAHBClock(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ahbMgrCtxType* self = &gAhbMgrCtx;

    // Restore AHBIX clock
    sts = ahbm_SetAHBIXClock(self, self->activeAHBClock);

    // Restore AHBE clock
    if(sts == Adsppm_Status_Success)
    {
        sts = ahbm_SetAHBEClock(self, self->ahbeClockFreq);
    }

    return sts;
}

Adsppm_Status AHBM_AdjustAndSetAHBClock(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    adsppm_lock(gAhbMgrCtx.lock);

    // Adjust AHB clock if ADSP is active
    // The timeline optimization by keeping AHB clock not lower than predefined frequency (19.2MHz) is applied
    // also to non-periodic clients in order to compensate for inadequate BW voting from audio clients.
    // Periodic usecases may have different (higher) AHB clock requirements to optimize their timeline
    if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationAhb)) && IsPeriodicUseCase())
    {
        // Select baseline or aggregated value if it is higher
        gAhbMgrCtx.activeAHBClock =
            ACM_AdjustParamValue(AsicFeatureId_TimelineOptimisationAhb, gAhbMgrCtx.aggregatedAHBClock);
    }
    else
    {
        gAhbMgrCtx.activeAHBClock = gAhbMgrCtx.aggregatedAHBClock;
    }

    sts = AHBM_SetActiveAHBClock();
    adsppm_unlock(gAhbMgrCtx.lock);
    return sts;
}

/**
 * @fn AHBM_ProcessRequest - Convert AHB bandwidth  to AHB clock
 * @param input AdsppmBusBWDataIbAbType *pCurAHBBwData
 * @param input AdsppmBusBWDataIbAbType *pNonSuppressibleAhbBW
 * @return Adsppm_Status
 */
Adsppm_Status AHBM_ProcessRequest(AdsppmBusBWDataIbAbType *pCurAHBBwData, AdsppmBusBWDataIbAbType *pNonSuppressibleAhbBW)
{
    Adsppm_Status sts = Adsppm_Status_Success;

    if((NULL == pCurAHBBwData) || (NULL == pNonSuppressibleAhbBW))
    {
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
            "pCurAHBBwData=%u, pNonSuppressibleAhbBW=%u",
            pCurAHBBwData, pNonSuppressibleAhbBW);
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        if(NULL == gAhbMgrCtx.lock)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            sts = Adsppm_Status_NotInitialized;
        }
        else
        {
            adsppm_lock(gAhbMgrCtx.lock);
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT,
                "Aggregated BW: Ab=%u, Ib=%u",
                (uint32)(pCurAHBBwData->Ab), (uint32)(pCurAHBBwData->Ib));
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT,
                "Aggregated non-suppressible BW: Ab=%u, Ib=%u",
                (uint32)(pNonSuppressibleAhbBW->Ab), (uint32)(pNonSuppressibleAhbBW->Ib));

            sts = ACM_GetClockFromBW(&gAhbMgrCtx.nonSuppressibleAHBClock, pNonSuppressibleAhbBW);
            if(Adsppm_Status_Success == sts)
            {
                // Adjust BW based on feature config
                pCurAHBBwData->Ib = ACM_AdjustParamValue(AsicFeatureId_Ahb_Scaling, pCurAHBBwData->Ib);
                sts = ACM_GetClockFromBW(&gAhbMgrCtx.aggregatedAHBClock, pCurAHBBwData);
            }
            adsppm_unlock(gAhbMgrCtx.lock);

            if(Adsppm_Status_Success == sts)
            {
                sts = AHBM_AdjustAndSetAHBClock();
            }
        }
    }

    return sts;
}

Adsppm_Status AHBM_GetInfo(AdsppmInfoAhbType* ahbInfo)
{
    Adsppm_Status status = Adsppm_Status_Failed;
    if(ahbInfo != NULL)
    {
        ahbMgrCtxType* self = &gAhbMgrCtx;
        adsppm_lock(self->lock);
        ahbInfo->ahbeFreqHz = self->ahbeClockFreq;
        status = Adsppm_Status_Success;
        adsppm_unlock(self->lock);
    }
    return status;
}

