/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * pwrmgr.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "pwrmgr.h"
#include "DALSys.h"
#include "hal_clkrgm.h"
#include "requestmgr.h"
#include "qurt_hvx.h"
#include "usleepmgr.h"

const char LPI_RETENTION_NODE_NAME[] = "/lpi/retention";
#define LPI_RETENTION_ALLOW 0
#define LPI_RETENTION_DISALLOW 1

typedef struct
{
    DALSYSSyncHandle            lock;
    Hal_ClkRgmEnableDisableType pwrDomainState[AsicPowerDomain_EnumMax][2];
    uint32                      activeStateIndex;
    npa_client_handle           lpiRetentionHandle;
    npa_client_handle           uSleepHandle; //to vote on dsp pm usleep node
} powerMgrCtxType;

// Global context for the power manager
static powerMgrCtxType gPowerMgrCtx;

static void PWR_LpiRetentionInitCb(void *context, unsigned int event_type, void *data, unsigned int data_size);
static void PWR_USleepNode_RegisterCB(void *context, unsigned int event_type, void *data, unsigned int data_size);

Adsppm_Status PWR_Init(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    AsicPowerDomainType i = AsicPowerDomain_AON;
    gPowerMgrCtx.activeStateIndex = 0;
    for(i = AsicPowerDomain_AON; i < AsicPowerDomain_EnumMax; i++)
    {
        gPowerMgrCtx.pwrDomainState[i][0] = Hal_ClkRgmDisable;
        gPowerMgrCtx.pwrDomainState[i][1] = Hal_ClkRgmDisable;
    }
    // If LPASS Core PC feature is enabled
    // set previous status as enabled
    // so that, regardless of LPASS Core POR state,
    // ADSPPM makes a call to disable it during init
    if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC)))
    {
        uint32 prevStateIndex = gPowerMgrCtx.activeStateIndex ^ 1;
        gPowerMgrCtx.pwrDomainState[AsicPowerDomain_LpassCore][prevStateIndex] = Hal_ClkRgmEnable;
    }
    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, &gPowerMgrCtx.lock, NULL))
    {
        result = Adsppm_Status_Failed;
    }
	if(result == Adsppm_Status_Success)
	{
        npa_resource_available_cb(LPI_RETENTION_NODE_NAME, PWR_LpiRetentionInitCb, NULL);
		/* Register a callback for dspPm uSleep node
     	 * create a client for PwrMgr to vote on dspPm uSleep node.
		 */
     	npa_resource_available_cb(
							QDSPPM_USLEEP_NODE_NAME,
							PWR_USleepNode_RegisterCB,
							NULL);
    }
    return result;
}

static void PWR_LpiRetentionInitCb(void *context, unsigned int event_type, void *data, unsigned int data_size)
{
    ADSPPM_LOG_FUNC_PROFILESTART;
    gPowerMgrCtx.lpiRetentionHandle = npa_create_sync_client(
        LPI_RETENTION_NODE_NAME,
        "qdsppm_lpi_ret",
        NPA_CLIENT_REQUIRED);
    if(NULL == gPowerMgrCtx.lpiRetentionHandle)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
            "Failed to create client for ADSP power with lpi retention node");
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
}

/**
 * PWR_USleepNode_RegisterCB
 * 
 * @brief Registers dspPm uSleep node
 * 
 * @param see npa_callback defintion for function parameters
 */
static void PWR_USleepNode_RegisterCB(
			void         *context,
            unsigned int  eventType,
            void         *data,
            unsigned int  dataSize)
{
    gPowerMgrCtx.uSleepHandle = npa_create_sync_client(
											QDSPPM_USLEEP_NODE_NAME, 
                                            "qdsppm_lpass_core",
											NPA_CLIENT_REQUIRED);
    return;
}

Adsppm_Status PWR_ProcessRequest(coreUtils_Q_Type *pPwrReqQ)
{
    Adsppm_Status result = Adsppm_Status_Success;
    Adsppm_Status hvxLockCheckStatus = Adsppm_Status_Success;
    RMHandleType *pRMHandle = NULL;

    if(NULL == pPwrReqQ)
    {
        result = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Bad parameter");
    }
    else
    {
        if(NULL == gPowerMgrCtx.lock)
        {
            result = Adsppm_Status_NotInitialized;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
        else
        {
            int index = 0;
            AsicPowerDomainType pwrDomain = AsicPowerDomain_AON;
            adsppm_lock(gPowerMgrCtx.lock);
            ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_Power);
            //Clear current state
            for(pwrDomain = AsicPowerDomain_AON; pwrDomain < AsicPowerDomain_EnumMax; pwrDomain++)
            {
                gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmDisable;
            }
            //Loop through all clients
            pRMHandle = (RMHandleType *)coreUtils_Q_Check(pPwrReqQ);
            for(index = 0; index < pPwrReqQ->nCnt; index++)
            {
                if(NULL != pRMHandle)
                {
                    if(NULL == pRMHandle->pClient)
                    {
                        result = Adsppm_Status_BadParm;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pClient is NULL");
                    }
                    else
                    {
                        // If request is valid that means that power has to be On
                        if(RM_Valid == pRMHandle->validFlag)
                        {
                            // Get the power domain based on core ID for this client
                            pwrDomain = ACMPwr_GetPowerDomain(pRMHandle->pClient->coreId);

							if (AsicPowerDomain_EnumMax != pwrDomain)
								gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
                        }
                        // HVX HW bug workaround for 8996 (CR 777974):
                        // Return error if HVX power off is requested while the
                        // client still has HVX locked.  This can only be
                        // checked for synchronous requests since
                        // qurt_hvx_get_lock_val() checks the status for only
                        // the current thread.  Also we only check for !unknown
                        // client classes, to avoid this logic during testing.
                        if((pRMHandle->validFlag == RM_InValid) &&
                            (pRMHandle->lifecycleState == RELEASED_REQUEST) &&
                            (pwrDomain == AsicPowerDomain_Hvx) &&
                            (pRMHandle->synchronousRequest == TRUE) &&
                            (pRMHandle->pClient->clientClass != MMPM_UNKNOWN_CLIENT_CLASS) &&
                            (qurt_hvx_get_lock_val() == QURT_HVX_LOCKED))
                        {
                            hvxLockCheckStatus = Adsppm_Status_Failed;
                            // Mark request as valid and keep power enabled,
                            // since release will fail
                            gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] =
                                Hal_ClkRgmEnable;
                            pRMHandle->validFlag = RM_Valid;
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_WARNING,
                                "HVX power was requested off before HVX was unlocked");
                        }
                    }
                    pRMHandle = (RMHandleType *)coreUtils_Q_Next(pPwrReqQ, &pRMHandle->link);
                }
            }
            ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_Power);


            // Apply overrides based on feature settings
            if((AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Adsp_PC)) &&
				(ACM_IsPwrDomainValid(AsicPowerDomain_Adsp)))
            {
                gPowerMgrCtx.pwrDomainState[AsicPowerDomain_Adsp][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
            }
            if((AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC)) &&
				(ACM_IsPwrDomainValid(AsicPowerDomain_LpassCore)))
            {
                gPowerMgrCtx.pwrDomainState[AsicPowerDomain_LpassCore][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
            }

            for(pwrDomain = AsicPowerDomain_AON; pwrDomain < AsicPowerDomain_EnumMax; pwrDomain++)
            {
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_DEBUG,
                    "Power domain %u state %u: ",
                    pwrDomain, gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);

                // Only Call Clk regime wrapper to enable/disable power domains if the state changes
                if(gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] !=
                    gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex ^ 1])
                {
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO,
                        "Power domain %u requested state %u",
                        pwrDomain,
                        gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);
                    result = ClkRgm_RequestPower(
                        pwrDomain, gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);
                    if(Adsppm_Status_Success != result)
                    {
                        break;
                    }
                    if((pwrDomain == AsicPowerDomain_LpassCore) && (ACM_IsPwrDomainValid(AsicPowerDomain_LpassCore)))
                    {
						Hal_ClkRgmEnableDisableType lpass_core_state;
                        boolean lpi_vote;
						boolean uSleep_vote;
                        
						lpass_core_state = gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex];

                        /* Allow lpi retention only when LPASS Core is in disabled state */
                        lpi_vote = lpass_core_state ? LPI_RETENTION_DISALLOW : LPI_RETENTION_ALLOW;

                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO,
                                          "NPA request to %s lpi retention", (lpi_vote ? "DisAllow" : "Allow"));
                        if(gPowerMgrCtx.lpiRetentionHandle)
                            npa_issue_required_request(gPowerMgrCtx.lpiRetentionHandle, lpi_vote);
						else
							ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Invalid lpiRetentionHandle");

						/* Allow usleep only when LPASS Core is in disabled state */
						uSleep_vote = lpass_core_state ? QDSPPM_USLEEP_DISALLOW : QDSPPM_USLEEP_ALLOW;

                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT,
                                          "NPA request to %s usleep", (uSleep_vote ? "Allow" : "DisAllow"));
                        if(gPowerMgrCtx.uSleepHandle)
                            npa_issue_required_request(gPowerMgrCtx.uSleepHandle, uSleep_vote);
						else
							ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Invalid uSleepHandle");
                    }
                }
            }

            // Flip active/previous request
            gPowerMgrCtx.activeStateIndex ^= 1;
            adsppm_unlock(gPowerMgrCtx.lock);
        }
    }


    if(hvxLockCheckStatus == Adsppm_Status_Failed)
    {
        // Workaround invoked:
        // New request for HVX power was made without prior HVX lock
        return Adsppm_Status_Failed;
    }
    else
    {
        return result;
    }
}
