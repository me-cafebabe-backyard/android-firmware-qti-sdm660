/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: adsppm_test_mips.c
@brief: Implementation of ADSPPM test module of MIPS/MPPS requests.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/test/adsppm_test_mips.c#1 $
*/

#include "mmpm.h"
#include "adsppm_test.h"
#include "adsppm_test_param.h"
#include "adsppm_test_utils.h"
#include "adsppm_test_asic_info.h"
#include "adsppm_utils.h"


#define MIPS_01_NAME    "mips_01"
#define MIPS_01_DETAILS "Req-Rel, all core/instance combination"

static MMPM_STATUS TestAllCoresMipsRequest(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    MmpmCoreIdType coreId;
    MmpmCoreInstanceIdType instanceId;
    uint32 clientId;

    for(coreId = MMPM_CORE_ID_LPASS_ADSP; coreId < MMPM_CORE_ID_LPASS_END; coreId++)
    {
        for(instanceId = MMPM_CORE_INSTANCE_0; instanceId < MMPM_CORE_INSTANCE_MAX; instanceId++)
        {
            if(AsicInfo_isCoreInstanceAvailable(coreId, instanceId))
            {
                clientId = Test_Register(coreId, instanceId, MIPS_01_NAME);
                if(clientId)
                {
                    sts = Test_RequestMips(clientId, 200);
                    if(MMPM_STATUS_SUCCESS != sts)
                    {
                        retSts = MMPM_STATUS_FAILED;
                    }
                    else
                    {
                        sts = Test_ReleaseResource(clientId, MMPM_RSC_ID_MIPS_EXT);
                        if(MMPM_STATUS_SUCCESS != sts)
                        {
                            retSts = MMPM_STATUS_FAILED;
                        }
                    }

                    sts = Test_Deregister(clientId);
                    if(MMPM_STATUS_SUCCESS != sts)
                    {
                        retSts = MMPM_STATUS_FAILED;
                    }
                }
                else
                {
                    retSts = MMPM_STATUS_FAILED;
                }
            }
        }
    }

    return retSts;
}

/**
 * @ingroup MIPS
 * @test mips_01
 * @brief Req-Rel, all core/instance combination
 */
static MMPM_STATUS Test_Mips_01(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_01_NAME, MIPS_01_DETAILS);

    sts = TestAllCoresMipsRequest();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_01_NAME, sts);
    return sts;
}


#define MIPS_02_NAME    "mips_02"
#define MIPS_02_DETAILS "Req-Rel, 2 same coreID/instanceID clients, expect aggregated MIPS"

static AdsppmTestType testmips02[] =
{
    {1, 2, MMPM_CORE_ID_LPASS_ADSP, MMPM_CORE_INSTANCE_0,
        {REG, REQMIPS}
    },
    {2, 2, MMPM_CORE_ID_LPASS_ADSP, MMPM_CORE_INSTANCE_0,
        {REG, REQMIPS}
    },
    {1, 2, MMPM_CORE_ID_LPASS_ADSP, MMPM_CORE_INSTANCE_0,
        {RELMIPS, DREG}
    },
    {2, 2, MMPM_CORE_ID_LPASS_ADSP, MMPM_CORE_INSTANCE_0,
        {RELMIPS, DREG}
    }
};

/**
 * @ingroup MIPS
 * @test mips_02
 * @brief Req-Rel, 2 same coreID/instanceID clients, expect aggregated MIPS
 */
static MMPM_STATUS Test_Mips_02(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, testSts[MAX_TEST][MAX_TEST_SEQUENCE];
    uint32 numTest = 0;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_02_NAME, MIPS_02_DETAILS);

    numTest = sizeof(testmips02)/sizeof(AdsppmTestType);
    sts = Test_InvokeTest(testmips02, numTest, testSts);

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_02_NAME, sts);
    return sts;
}


#define MIPS_03_NAME    "mips_03"
#define MIPS_03_DETAILS "Req-Rel-Rel, expect NO errors"

static AdsppmTestType testmips03[] =
{
    {1, 5, MMPM_CORE_ID_LPASS_ADSP, MMPM_CORE_INSTANCE_0,
        {REG, REQMIPS, RELMIPS, RELMIPS,  DREG}
    }
};

/**
 * @ingroup MIPS
 * @test mips_03
 * @brief Req-Rel-Rel, expect NO errors
 */
static MMPM_STATUS Test_Mips_03(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, testSts[MAX_TEST][MAX_TEST_SEQUENCE];
    uint32 numTest = 0;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_03_NAME, MIPS_03_DETAILS);

    numTest = sizeof(testmips03)/sizeof(AdsppmTestType);
    sts = Test_InvokeTest(testmips03, numTest, testSts);

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_03_NAME, sts);
    return sts;
}


#define MIPS_04_NAME    "mips_04"
#define MIPS_04_DETAILS "Invalid client ID Req, expect failure Req"

static MMPM_STATUS TestMipsInvalidClientId(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    uint32 clientId = 0;
    MmpmCoreIdType coreId = MMPM_CORE_ID_LPASS_ADSP;
    MmpmCoreInstanceIdType instanceId = MMPM_CORE_INSTANCE_0;

    clientId = Test_Register(coreId, instanceId, MIPS_04_NAME);

    if(clientId)
    {
        sts = Test_Deregister(clientId);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }

        sts = Test_RequestMips(clientId, 400);
        if(MMPM_STATUS_SUCCESS == sts)
        {
            ADSPPMTEST_LOG_PRINTF_0(
                ADSPPMTEST_LOG_LEVEL_ERROR,
                "[ERROR] Request did not fail as intended");
            retSts = MMPM_STATUS_FAILED;
        }
        else
        {
            ADSPPMTEST_LOG_PRINTF_0(
                ADSPPMTEST_LOG_LEVEL_ERROR,
                "[PASS] Failed return is intended");
        }
    }
    else
    {
        retSts = MMPM_STATUS_FAILED;
    }

    return retSts;
}

/**
 * @ingroup MIPS
 * @test mips_04
 * @brief Invalid client ID Req, expect failure Req
 */
static MMPM_STATUS Test_Mips_04(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_04_NAME, MIPS_04_DETAILS);

    sts = TestMipsInvalidClientId();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_04_NAME, sts);
    return sts;
}


#define MIPS_05_NAME    "mips_05"
#define MIPS_05_DETAILS "Q6 core clock frequency plan"

static MMPM_STATUS TestQ6CoreClockFreqPlan(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    uint32 clientId = 0;
    uint32 index, mips, setClkFreq, readClkFreq;
    const AsicInfo_MipsInfoType *pMipsInfo = NULL;
    const AsicInfo_ClockFreqVoltPlanType *pQ6FreqPlan = NULL;
    MmpmCoreIdType coreId = MMPM_CORE_ID_LPASS_ADSP;
    MmpmCoreInstanceIdType instanceId = MMPM_CORE_INSTANCE_0;

    clientId = Test_Register(coreId, instanceId, MIPS_05_NAME);

    if(clientId)
    {
        pMipsInfo = AsicInfo_getMipsInfo();
        pQ6FreqPlan = AsicInfo_getClockFreqVoltPlan(MMPM_CLK_ID_LPASS_ADSP_CORE);

        for(index = 0; index < pQ6FreqPlan->numFreq; index++)
        {
            setClkFreq = pQ6FreqPlan->pFreqVoltPlan[index].frequency;
            mips = setClkFreq/1000000*256/pMipsInfo->mips2clockFactor;

            sts = Test_RequestMips(clientId, mips);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
            else
            {
                // Read Q6 clock frequency
                sts = Test_InfoClk(coreId, instanceId, MMPM_CLK_ID_LPASS_ADSP_CORE, &readClkFreq);
                if(MMPM_STATUS_SUCCESS != sts)
                {
                    retSts = MMPM_STATUS_FAILED;
                }
                else
                {
                    if(!Test_CompareFreq(setClkFreq, readClkFreq * 1000))
                    {
                        ADSPPMTEST_LOG_PRINTF_2(
                            ADSPPMTEST_LOG_LEVEL_ERROR,
                            "[ERROR] setClkFreq = %u Hz, readClkFreq = %u Hz",
                            setClkFreq, readClkFreq * 1000);
                        retSts = MMPM_STATUS_FAILED;
                    }
                }
            }
        }

        sts = Test_Deregister(clientId);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }
    }
    else
    {
        retSts = MMPM_STATUS_FAILED;
    }

    return retSts;
}

/**
 * @ingroup MIPS
 * @test mips_05
 * @brief Q6 core clock frequency plan
 */
static MMPM_STATUS Test_Mips_05(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_05_NAME, MIPS_05_DETAILS);

    sts = TestQ6CoreClockFreqPlan();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_05_NAME, sts);
    return sts;
}


#define MIPS_06_NAME    "mips_06"
#define MIPS_06_DETAILS "Very large and casted negative MIPS value should result in highest Q6 freq"

MMPM_STATUS TestVeryLargeAndNegativeMipsReq(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    uint32 clientId = 0;
    uint32 mips, setClkFreq, readClkFreq;
    int negativeMips;
    const AsicInfo_ClockFreqVoltPlanType *pQ6FreqPlan = NULL;
    MmpmCoreIdType coreId = MMPM_CORE_ID_LPASS_ADSP;
    MmpmCoreInstanceIdType instanceId = MMPM_CORE_INSTANCE_0;

    clientId = Test_Register(coreId, instanceId, MIPS_06_NAME);

    if(clientId)
    {
        pQ6FreqPlan = AsicInfo_getClockFreqVoltPlan(MMPM_CLK_ID_LPASS_ADSP_CORE);
        setClkFreq = pQ6FreqPlan->pFreqVoltPlan[pQ6FreqPlan->numFreq - 1].frequency;

        // Very large MIPS value
        mips = 0xFFFFFFFF;

        sts = Test_RequestMips(clientId, mips);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }
        else
        {
            // Read Q6 clock frequency
            sts = Test_InfoClk(coreId, instanceId, MMPM_CLK_ID_LPASS_ADSP_CORE, &readClkFreq);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
            else
            {
                if(!Test_CompareFreq(setClkFreq, readClkFreq * 1000))
                {
                    ADSPPMTEST_LOG_PRINTF_2(
                        ADSPPMTEST_LOG_LEVEL_ERROR,
                        "[ERROR] setClkFreq = %u Hz, readClkFreq = %u Hz",
                        setClkFreq, readClkFreq * 1000);
                    retSts = MMPM_STATUS_FAILED;
                }
            }

            sts = Test_ReleaseResource(clientId, MMPM_RSC_ID_MIPS_EXT);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
        }

        // Very large MIPS value 2
        mips = 0x800000F0;

        sts = Test_RequestMips(clientId, mips);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }
        else
        {
            // Read Q6 clock frequency
            sts = Test_InfoClk(coreId, instanceId, MMPM_CLK_ID_LPASS_ADSP_CORE, &readClkFreq);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
            else
            {
                if(!Test_CompareFreq(setClkFreq, readClkFreq * 1000))
                {
                    ADSPPMTEST_LOG_PRINTF_2(
                        ADSPPMTEST_LOG_LEVEL_ERROR,
                        "[ERROR] setClkFreq = %u Hz, readClkFreq = %u Hz",
                        setClkFreq, readClkFreq * 1000);
                    retSts = MMPM_STATUS_FAILED;
                }
            }

            sts = Test_ReleaseResource(clientId, MMPM_RSC_ID_MIPS_EXT);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
        }

        // Casted Negative MIPS value
        negativeMips = -240;
        mips = (uint32)negativeMips;

        sts = Test_RequestMips(clientId, mips);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }
        else
        {
            // Read Q6 clock frequency
            sts = Test_InfoClk(coreId, instanceId, MMPM_CLK_ID_LPASS_ADSP_CORE, &readClkFreq);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
            else
            {
                if(!Test_CompareFreq(setClkFreq, readClkFreq * 1000))
                {
                    ADSPPMTEST_LOG_PRINTF_2(
                        ADSPPMTEST_LOG_LEVEL_ERROR,
                        "[ERROR] setClkFreq = %u Hz, readClkFreq = %u Hz",
                        setClkFreq, readClkFreq * 1000);
                    retSts = MMPM_STATUS_FAILED;
                }
            }

            sts = Test_ReleaseResource(clientId, MMPM_RSC_ID_MIPS_EXT);
            if(MMPM_STATUS_SUCCESS != sts)
            {
                retSts = MMPM_STATUS_FAILED;
            }
        }

        sts = Test_Deregister(clientId);
        if(MMPM_STATUS_SUCCESS != sts)
        {
            retSts = MMPM_STATUS_FAILED;
        }
    }
    else
    {
        retSts = MMPM_STATUS_FAILED;
    }

    return retSts;
}

/**
 * @ingroup MIPS
 * @test mips_06
 * @brief Very large and casted negative MIPS value should result in highest Q6 freq
 */
MMPM_STATUS Test_Mips_06(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MIPS_06_NAME, MIPS_06_DETAILS);

    sts = TestVeryLargeAndNegativeMipsReq();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MIPS_06_NAME, sts);
    return sts;
}

#define MPPS_07_NAME    "mpps_07"
#define MPPS_07_DETAILS "Req-Rel all core/instances combination for MPPS"

static MMPM_STATUS TestAllCoresMppsRequest(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    MmpmCoreIdType coreId;
    MmpmCoreInstanceIdType instanceId;
    uint32 clientId;
    MmpmMppsReqType mppsReq;

    mppsReq.mppsTotal = 200;
    // Don't care about floor clock for this test
    mppsReq.adspFloorClock = 0;

    for(coreId = MMPM_CORE_ID_LPASS_ADSP; coreId < MMPM_CORE_ID_LPASS_END; coreId++)
    {
        for(instanceId = MMPM_CORE_INSTANCE_0; instanceId < MMPM_CORE_INSTANCE_MAX; instanceId++)
        {
            if(AsicInfo_isCoreInstanceAvailable(coreId, instanceId))
            {
                clientId = Test_Register(coreId, instanceId, MPPS_07_NAME);
                if(clientId)
                {
                    sts = Test_RequestMpps(clientId, &mppsReq);
                    if(MMPM_STATUS_SUCCESS != sts)
                    {
                        retSts = MMPM_STATUS_FAILED;
                    }
                    else
                    {
                        sts = Test_ReleaseResource(clientId, MMPM_RSC_ID_MPPS);
                        if(MMPM_STATUS_SUCCESS != sts)
                        {
                            retSts = MMPM_STATUS_FAILED;
                        }
                    }

                    sts = Test_Deregister(clientId);
                    if(MMPM_STATUS_SUCCESS != sts)
                    {
                        retSts = MMPM_STATUS_FAILED;
                    }
                }
                else
                {
                    retSts = MMPM_STATUS_FAILED;
                }
            }
        }
    }

    return retSts;
}

/**
 * @ingroup MIPS
 * @test mpps_07
 * @brief Req-Rel all core/instances combination for MPPS
 */
static MMPM_STATUS Test_Mpps_07(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MPPS_07_NAME, MPPS_07_DETAILS);

    sts = TestAllCoresMppsRequest();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MPPS_07_NAME, sts);
    return sts;
}

#define MPPS_08_NAME    "mpps_08"
#define MPPS_08_DETAILS "Test MPPS query"

typedef struct
{
    uint32 clientId;
    MmpmClientClassType clientClassId;
} ClientClassTestType;

static ClientClassTestType clientClassId[] =
{
    {0, MMPM_AUDIO_CLIENT_CLASS},
    {0, MMPM_VOICE_CLIENT_CLASS},
    {0, MMPM_COMPUTE_CLIENT_CLASS},
    {0, MMPM_STREAMING_1HVX_CLIENT_CLASS},
    {0, MMPM_STREAMING_2HVX_CLIENT_CLASS}
};

static MMPM_STATUS TestMppsQuery(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    MmpmMppsReqType mppsReq;
    MmpmInfoMppsType mppsInfo;
    uint32 clientClasses = 0;
    uint32 index = 0;
    uint32 numOfClientClasses = sizeof(clientClassId)/sizeof(clientClassId[0]);

    mppsReq.mppsTotal = 100;
    // Don't care about floor clock for this test
    mppsReq.adspFloorClock = 0;

    for(index = 0; index < numOfClientClasses; index++)
    {
        clientClassId[index].clientId = Test_Register(
            MMPM_CORE_ID_LPASS_ADSP,
            MMPM_CORE_INSTANCE_0,
            MPPS_08_NAME);
        if(clientClassId[index].clientId == 0)
            goto TestMppsQuery_error;

        sts = Test_SetClientClass(
            clientClassId[index].clientId,
            clientClassId[index].clientClassId);
        if(sts != MMPM_STATUS_SUCCESS)
            goto TestMppsQuery_error;

        sts = Test_RequestMpps(clientClassId[index].clientId, &mppsReq);
        if(sts != MMPM_STATUS_SUCCESS)
            goto TestMppsQuery_error;

        mppsInfo.clientClasses = clientClassId[index].clientClassId;
        mppsInfo.aggregateMpps = 0;
        sts = Test_InfoMpps(&mppsInfo);
        if(sts != MMPM_STATUS_SUCCESS)
            goto TestMppsQuery_error;

        if(mppsInfo.aggregateMpps < mppsReq.mppsTotal)
        {
            ADSPPMTEST_LOG_PRINTF_0(ADSPPMTEST_LOG_LEVEL_ERROR,
                "[ERROR] unexpected aggregate MPPS returned from query");
            goto TestMppsQuery_error;
        }

        clientClasses |= clientClassId[index].clientClassId;
    }

    mppsInfo.clientClasses = clientClasses;
    mppsInfo.aggregateMpps = 0;
    sts = Test_InfoMpps(&mppsInfo);
    if(sts != MMPM_STATUS_SUCCESS)
        goto TestMppsQuery_error;

    if(mppsInfo.aggregateMpps <
        mppsReq.mppsTotal * numOfClientClasses)
    {
        ADSPPMTEST_LOG_PRINTF_0(ADSPPMTEST_LOG_LEVEL_ERROR,
            "[ERROR] unexpected aggregate MPPS returned from query");
        goto TestMppsQuery_error;
    }

    for(index = 0; index < numOfClientClasses; index++)
    {
        sts = Test_Deregister(clientClassId[index].clientId);
        if(sts != MMPM_STATUS_SUCCESS)
            goto TestMppsQuery_error;
    }

    return sts;

TestMppsQuery_error:

    for(index = 0; index < numOfClientClasses; index++)
        if(clientClassId[index].clientId)
            Test_Deregister(clientClassId[index].clientId);

    return MMPM_STATUS_FAILED;

}

/**
 * @ingroup MIPS
 * @test mpps_08
 * @brief Test MPPS query
 */
static MMPM_STATUS Test_Mpps_08(void)
{

    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MPPS_08_NAME, MPPS_08_DETAILS);

    sts = TestMppsQuery();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MPPS_08_NAME, sts);
    return sts;

}

#define MPPS_09_NAME    "mpps_09"
#define MPPS_09_DETAILS "Scaling of AHB-E frequency with ADSP frequency"

typedef struct
{
    uint32 q6FreqHz;    // DSP clock setting
    uint32 ahbeFreqHz;  // expected AHB-E frequency
} q6AhbFreqPair;

static MMPM_STATUS TestQ6AhbeScaling(void)
{
    MMPM_STATUS sts = MMPM_STATUS_FAILED, retSts = MMPM_STATUS_SUCCESS;
    uint32 clientId = 0;
    MmpmCoreIdType coreId = MMPM_CORE_ID_LPASS_ADSP;
    MmpmCoreInstanceIdType instanceId = MMPM_CORE_INSTANCE_0;
    AdsppmInfoAhbType ahbInfo;
    q6AhbFreqPair table[] =
        {
            // 
            // Warning: Target-specific and version-specific data here.
            //          Data below is for 8996 v2 and would need update for
            //          other versions.
            //          
            // 
            //         Q6,  expected AHBE
            {   297600000,       38400000 }, // SVS2 f-max
            {   460800000,       76800000 }, // SVS f-max
            {   652800000,      153600000 }, // nominal f-max
            {   729600000,      153600000 }, // nominal ADSP f-max

            {   100000000,       38400000 },
            {   200000000,       38400000 },
            {   300000000,       76800000 },
            {   400000000,       76800000 },
            {   500000000,      153600000 },
            {   600000000,      153600000 },
            {   700000000,      153600000 },
            {   800000000,      153600000 },
        };
    uint32 i;
    MmpmMppsReqType mppsReq;

    clientId = Test_Register(coreId, instanceId, MIPS_04_NAME);

    if(clientId == 0)
        goto TestQ6AhbeScaling_error;

    for(i = 0; i < ADSPPM_ARRAY_SIZE(table); i++)
    {

        // Request DSP floor clock
        mppsReq.mppsTotal = 0;
        mppsReq.adspFloorClock = table[i].q6FreqHz;
        sts = Test_RequestMpps(clientId, &mppsReq);
        if(MMPM_STATUS_SUCCESS != sts)
            goto TestQ6AhbeScaling_error;

        // Query AHB-E freq
        sts = Test_InfoAhb(coreId, instanceId, &ahbInfo);
        if(MMPM_STATUS_SUCCESS != sts)
            goto TestQ6AhbeScaling_error;

        ADSPPMTEST_LOG_PRINTF_2(ADSPPMTEST_LOG_LEVEL_INFO,
            "AHB-E: expected %u, actual %u Hz",
            table[i].ahbeFreqHz,
            ahbInfo.ahbeFreqHz);

        // Check expected AHB-E freq
        // Can only check if actual freq is too low, since other clients
        // may have MIPS/MPPS requests concurrently
        if(ahbInfo.ahbeFreqHz < table[i].ahbeFreqHz)
            goto TestQ6AhbeScaling_error;

    }

    sts = Test_Deregister(clientId);
    if(MMPM_STATUS_SUCCESS != sts)
    {
        retSts = MMPM_STATUS_FAILED;
    }

    return retSts;

TestQ6AhbeScaling_error:
    Test_Deregister(clientId);

    return MMPM_STATUS_FAILED;

}

/**
 * @ingroup MIPS
 * @test mpps_09
 * @brief Test scaling of AHB-E frequency with ADSP frequency
 */
static MMPM_STATUS Test_Mpps_09(void)
{

    MMPM_STATUS sts = MMPM_STATUS_FAILED;
    ADSPPMTEST_LOG_TEST_HEADER(MPPS_09_NAME, MPPS_09_DETAILS);

    sts = TestQ6AhbeScaling();

    ADSPPMTEST_LOG_TEST_RESULT(AdsppmTestId_MIPS, MPPS_09_NAME, sts);
    return sts;

}

void Test_Mips()
{
    // Req-Rel, all core/instance combination
    Test_Mips_01();

    // Req-Rel, 2 same coreID/instanceID clients, expect aggregated MIPS
    Test_Mips_02();

    // Req-Rel-Rel, expect NO errors
    Test_Mips_03();

    // Invalid client ID Req, expect failure Req
    Test_Mips_04();

    // Q6 core clock frequency plan
    Test_Mips_05();

    // Very large and casted negative MIPS value should result in highest Q6 freq
//    Test_Mips_06();

    // Req-Rel all core/instances combination for MPPS
    Test_Mpps_07();

    // Test MPPS query
    Test_Mpps_08();

    // Test scaling of AHB-E frequency with ADSP frequency
    Test_Mpps_09();



}

