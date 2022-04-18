/*==================================================================
 *
 * FILE:        ddi_sdm660.c
 *
 * DESCRIPTION:
 *
 *
 *        Copyright © 2017 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 *2016-04-09      zhz     Add DQ Vref CDC shmoo test
 *2016-12-15      zhz     Initial file creation
 */
#include "ddi_sdm660.h"
#include "ddi_initialize.h"
#include "ddi_tool.h"
#include "ddi_target.h"
#include "DDIChipInfo.h"
#include "DalDevice.h"
#include "target_config.h"
#include "ddrss_training.h"

extern DDR_STRUCT *share_data;
extern uint8 gSupportedClockLevel;

#define NAME_STR_RESULT            "Pass"
#define NAME_STR_CHANNEL           "SDRamInterface"
#define NAME_STR_CS                "SDRamChipSelect"
#define NAME_STR_LOOPCOUNT         "LoopCount"
#define NAME_STR_TESTLINE          "TestLine"
#define NAME_STR_PRFSLevel         "PRFSLevel"
#define NAME_STR_OVERDRIVE         "OverDrive"
#define NAME_STR_ODT               "ODT"
#define NAME_STR_PULLUP            "PullUp"
#define NAME_STR_VOH               "VoH"
#define NAME_STR_EN_TERM           "EnableODT"
#define NAME_STR_CLOCKVALUE        "ClockValue"
#define NAME_STR_VDDQVALUE         "VDDQValue"
#define NAME_STR_VDD1VALUE         "VDD1Value"
#define NAME_STR_VDD2VALUE         "VDD2Value"
#define NAME_STR_VDDQVDD2VALUE     "VDDQandVDD2Value"
#define NAME_STR_FREQ              "Freq"
#define NAME_STR_MR3VAL            "mr3Val"
#define NAME_STR_MR11VAL           "mr11Val"
#define NAME_STR_REGNUM            "RegNum"
#define NAME_STR_REGVALUE          "RegValue"
#define NAME_STR_VREF              "Vref"
#define NAME_STR_COARSECDC         "CoarseCDC"
#define NAME_STR_FINECDC           "FineCDC"
#define NAME_STR_START_VREF        "StartVref"
#define NAME_STR_END_VREF          "EndVref"
#define NAME_STR_VREF_STEP         "VrefStep"
#define NAME_STR_START_COARSECDC   "StartCoarseCDC"
#define NAME_STR_END_COARSECDC     "EndCoarseCDC"


#define NAME_STR_ITEM_A            "OwnAddressRWTest"
#define NAME_STR_ITEM_B            "AddressLinesTest"
#define NAME_STR_ITEM_C            "DataLinesTest"
#define NAME_STR_ITEM_D            "WriteTest"
#define NAME_STR_ITEM_E            "ReadTest"
#define NAME_STR_ITEM_F            "ReadWriteTest"
#define NAME_STR_ITEM_G            "Retrain"
#define NAME_STR_ITEM_H            "ChangeDDRPhySetting"
#define NAME_STR_ITEM_I            "ReadDDRPowerSetting"
#define NAME_STR_ITEM_J            "ReadDDRPhySetting"
#define NAME_STR_ITEM_K            "ReadTemperature"
#define NAME_STR_ITEM_L            "ChangeDDRClock"
#define NAME_STR_ITEM_M            "ChangeVDDQ"
#define NAME_STR_ITEM_N            "ChangeVDD1"
#define NAME_STR_ITEM_O            "ChangeVDD2"
#define NAME_STR_ITEM_P            "ChangeVDDQandVDD2"
#define NAME_STR_ITEM_Q            "DisableDBI"
#define NAME_STR_ITEM_R            "ChangeMR3"
#define NAME_STR_ITEM_S            "ChangeMR11"
#define NAME_STR_ITEM_T            "MRWrite"
#define NAME_STR_ITEM_U            "StressTest"
#define NAME_STR_ITEM_V            "MRRead"
#define NAME_STR_DQRD_VREF_CDC     "DQReadVrefCDCShmoo"
#define NAME_STR_DQWR_VREF_CDC     "DQWriteVrefCDCShmoo"

boolean handleDDRTest(void *this_p);
boolean handleRWtest(void *this_p);
boolean handleRetrain(void *this_p);
boolean handleChangeBIMCPhySettings(void *this_p);
boolean handleReadPowerSetting(void *this_p);
boolean handleReadPhySetting(void *this_p);
boolean handleReadTemperature(void *this_p);
boolean ChangeBIMCClock_init(void *this_p);
boolean handleChangeBIMCClock(void *this_p);
boolean handleChangeVDDQ(void *this_p);
boolean handleChangeVDD1(void *this_p);
boolean handleChangeVDD2(void *this_p);
boolean handleChangeVDDQ_VDD2(void *this_p);
boolean handleDisableDBI(void *this_p);
boolean DRAMSettings_init(void *this_p);
boolean handleDRAMSettings(void *this_p);
boolean handleReadWriteMRReg(void *this_p);
boolean DQReadVrefCDCchange_init(void *this_p);
boolean handleDQReadVrefCDC(void *this_p);
boolean DQWriteVrefCDCchange_init(void *this_p);
boolean handleDQWriteVrefCDC(void *this_p);


boolean ddi_firehose_pre_work(void *this_p);
boolean ddi_firehose_post_work(void *this_p);


ddi_firehose_rspons item_result_rsp[] =
{
    {NAME_STR_RESULT,    DDI_FIREHOSE_BOOLEAN},
    {"",                 DDI_FIREHOSE_NULL}
};

ddi_firehose_rspons item_ReadPhySetting_rsp[] =
{
    {NAME_STR_OVERDRIVE,        DDI_FIREHOSE_UINT8},
    {NAME_STR_ODT,              DDI_FIREHOSE_UINT8},
    {NAME_STR_PULLUP,           DDI_FIREHOSE_UINT8},
    {NAME_STR_VOH,              DDI_FIREHOSE_UINT8},
    {"",                        DDI_FIREHOSE_NULL}
};

ddi_firehose_params item_OwnAddressRWTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_AddressLinesTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_DataLinesTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_WriteTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_LOOPCOUNT, DDI_FIREHOSE_UINT32,      1,       100000000,     1,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,             0,      ""}
};

ddi_firehose_params item_ReadTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_LOOPCOUNT, DDI_FIREHOSE_UINT32,      1,       100000000,     1,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,             0,      ""}
};

ddi_firehose_params item_ReadWriteTest_arg[] =
{
    {NAME_STR_CHANNEL,   DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_CS,        DDI_FIREHOSE_UINT8,       0,       1,             0,      ""},
    {NAME_STR_LOOPCOUNT, DDI_FIREHOSE_UINT32,      1,       100000000,     1,      ""},
    {"",                 DDI_FIREHOSE_NULL,        0,       0,             0,      ""}
};

ddi_firehose_params item_ChangeBIMCPhySettings_arg[] =
{
    {NAME_STR_TESTLINE,         DDI_FIREHOSE_UINT8,       0,       3,      0,      ""},
    {NAME_STR_PRFSLevel,        DDI_FIREHOSE_UINT8,       0,       7,      7,      ""},
    {NAME_STR_OVERDRIVE,        DDI_FIREHOSE_UINT8,       0,       7,      0,      ""},
    {NAME_STR_PULLUP,           DDI_FIREHOSE_UINT8,       0,       7,      0,      ""},
    {NAME_STR_ODT,              DDI_FIREHOSE_UINT8,       0,       7,      0,      ""},
    {NAME_STR_VOH,              DDI_FIREHOSE_UINT8,       0,       3,      0,      ""},
    {NAME_STR_EN_TERM,          DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ReadPhySetting_arg[] =
{
    {NAME_STR_TESTLINE,         DDI_FIREHOSE_UINT8,       0,       3,      0,      ""},
    {NAME_STR_PRFSLevel,        DDI_FIREHOSE_UINT8,       0,       7,      7,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeBIMCClock_arg[] =
{
    {NAME_STR_CLOCKVALUE,       DDI_FIREHOSE_UINT8,       0,       15,     0,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeVDDQ_arg[] =
{
    {NAME_STR_VDDQVALUE,        DDI_FIREHOSE_UINT32,      500,     700,    600,    ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeVDD1_arg[] =
{
    {NAME_STR_VDD1VALUE,        DDI_FIREHOSE_UINT32,      1700,    1900,   1800,   ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeVDD2_arg[] =
{
    {NAME_STR_VDD2VALUE ,       DDI_FIREHOSE_UINT32,      1028,    1228,   1128,   ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeVDDQandVDD2_arg[] =
{
    {NAME_STR_VDDQVDD2VALUE,    DDI_FIREHOSE_UINT32,      1028,    1228,   1128,   ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeMR3_arg[] =
{
    {NAME_STR_FREQ,             DDI_FIREHOSE_UINT8,       0,       3,      0,      ""},
    {NAME_STR_MR3VAL,           DDI_FIREHOSE_UINT8,       0,       255,    0,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_ChangeMR11_arg[] =
{
    {NAME_STR_FREQ,             DDI_FIREHOSE_UINT8,       0,       3,      0,      ""},
    {NAME_STR_MR11VAL,          DDI_FIREHOSE_UINT8,       0,       255,    0,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_MRWrite_arg[] =
{
    {NAME_STR_CHANNEL,          DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {NAME_STR_CS,               DDI_FIREHOSE_UINT8,       0,       1,      0,      ""},
    {NAME_STR_REGNUM,           DDI_FIREHOSE_UINT8,       0,       40,     5,      ""},
    {NAME_STR_REGVALUE,         DDI_FIREHOSE_UINT8,       0,       255,    0,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,      ""}
};

ddi_firehose_params item_dqread_vref_cdc_arg[] =
{
    {NAME_STR_CHANNEL,          DDI_FIREHOSE_UINT8,       0,       1,      0,       ""},
    {NAME_STR_CS,               DDI_FIREHOSE_UINT8,       0,       1,      0,       ""},
    {NAME_STR_CLOCKVALUE,       DDI_FIREHOSE_UINT8,       0,       15,     0,       ""},
    {NAME_STR_START_VREF,       DDI_FIREHOSE_UINT8,       0,       55,     0,       ""},
    {NAME_STR_END_VREF,         DDI_FIREHOSE_UINT8,       0,       55,     55,      ""},
    {NAME_STR_VREF_STEP,        DDI_FIREHOSE_UINT8,       0,       55,     55,      ""},
    {NAME_STR_START_COARSECDC,  DDI_FIREHOSE_UINT8,       0,       24,     0,       ""},
    {NAME_STR_END_COARSECDC,    DDI_FIREHOSE_UINT8,       0,       24,     24,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,       ""}
};

ddi_firehose_params item_dqwrite_vref_cdc_arg[] =
{
    {NAME_STR_CHANNEL,          DDI_FIREHOSE_UINT8,       0,       1,      0,       ""},
    {NAME_STR_CS,               DDI_FIREHOSE_UINT8,       0,       1,      0,       ""},
    {NAME_STR_CLOCKVALUE,       DDI_FIREHOSE_UINT8,       0,       15,     0,       ""},
    {NAME_STR_START_VREF,       DDI_FIREHOSE_UINT8,       0,       50,     0,       ""},
    {NAME_STR_END_VREF,         DDI_FIREHOSE_UINT8,       0,       50,     50,      ""},
    {NAME_STR_VREF_STEP,        DDI_FIREHOSE_UINT8,       0,       55,     55,      ""},
    {NAME_STR_START_COARSECDC,  DDI_FIREHOSE_UINT8,       0,       24,     0,       ""},
    {NAME_STR_END_COARSECDC,    DDI_FIREHOSE_UINT8,       0,       24,     24,      ""},
    {"",                        DDI_FIREHOSE_NULL,        0,       0,      0,       ""}
};


ddi_firehose_item ddi_firehose_pack_items[] =
{
    {NAME_STR_ITEM_A,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_OwnAddressRWTest_arg,      item_result_rsp,           NULL,                         NULL,       &handleDDRTest,                 NULL},
    {NAME_STR_ITEM_B,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_AddressLinesTest_arg,      item_result_rsp,           NULL,                         NULL,       &handleDDRTest,                 NULL},
    {NAME_STR_ITEM_C,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_DataLinesTest_arg,         item_result_rsp,           NULL,                         NULL,       &handleDDRTest,                 NULL},
    {NAME_STR_ITEM_D,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_WriteTest_arg,             item_result_rsp,           NULL,                         NULL,       &handleRWtest,                  NULL},
    {NAME_STR_ITEM_E,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ReadTest_arg,              item_result_rsp,           NULL,                         NULL,       &handleRWtest,                  NULL},
    {NAME_STR_ITEM_F,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ReadWriteTest_arg,         item_result_rsp,           NULL,                         NULL,       &handleRWtest,                  NULL},
    {NAME_STR_ITEM_H,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ChangeBIMCPhySettings_arg, item_result_rsp,           NULL,                         NULL,       &handleChangeBIMCPhySettings,   NULL},
    {NAME_STR_ITEM_I,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  NULL,                           item_result_rsp,           NULL,                         NULL,       &handleReadPowerSetting,        NULL},
    {NAME_STR_ITEM_J,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ReadPhySetting_arg,        item_result_rsp,           NULL,                         NULL,       &handleReadPhySetting,          NULL},
    {NAME_STR_ITEM_K,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  NULL,                           item_result_rsp,           NULL,                         NULL,       &handleReadTemperature,         NULL},
    {NAME_STR_ITEM_L,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ChangeBIMCClock_arg,       item_result_rsp,           &ChangeBIMCClock_init,        NULL,       &handleChangeBIMCClock,         NULL},
    {NAME_STR_ITEM_M,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4),                                    item_ChangeVDDQ_arg,            item_result_rsp,           NULL,                         NULL,       &handleChangeVDDQ,              NULL},
    {NAME_STR_ITEM_N,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),                                   item_ChangeVDD1_arg,            item_result_rsp,           NULL,                         NULL,       &handleChangeVDD1,              NULL},
    {NAME_STR_ITEM_O,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),                                   item_ChangeVDD2_arg,            item_result_rsp,           NULL,                         NULL,       &handleChangeVDD2,              NULL},
    {NAME_STR_ITEM_P,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4),                                    item_ChangeVDDQandVDD2_arg,     item_result_rsp,           NULL,                         NULL,       &handleChangeVDDQ_VDD2,         NULL},
    {NAME_STR_ITEM_Q,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  NULL,                           item_result_rsp,           NULL,                         NULL,       &handleDisableDBI,              NULL},
    {NAME_STR_ITEM_R,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ChangeMR3_arg,             item_result_rsp,           &DRAMSettings_init,           NULL,       &handleDRAMSettings,            NULL},
    {NAME_STR_ITEM_S,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_ChangeMR11_arg,            item_result_rsp,           &DRAMSettings_init,           NULL,       &handleDRAMSettings,            NULL},
    {NAME_STR_ITEM_T,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_MRWrite_arg,               item_result_rsp,           NULL,                         NULL,       &handleReadWriteMRReg,          NULL},
    {NAME_STR_ITEM_G,           1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  NULL,                           item_result_rsp,           NULL,                         NULL,       &handleRetrain,                 NULL},
    {NAME_STR_DQRD_VREF_CDC,    1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_dqread_vref_cdc_arg,       item_result_rsp,           &DQReadVrefCDCchange_init,    NULL,       &handleDQReadVrefCDC,           NULL},
    {NAME_STR_DQWR_VREF_CDC,    1,     DDR_TYPE_MASK(DDR_TYPE_LPDDR4) | DDR_TYPE_MASK(DDR_TYPE_LPDDR4X),  item_dqwrite_vref_cdc_arg,      item_result_rsp,           &DQWriteVrefCDCchange_init,   NULL,       &handleDQWriteVrefCDC,          NULL},
    {"",                        0,     0,                                                                 NULL,                           NULL,                      NULL,                         NULL,       NULL,                           NULL}
};

ddi_firehose_info ddi_firehose_pack_info[DDI_FIREHOSE_SIZE_INFO_MAX] =
{
    {"", ""}
};

ddi_firehose_item_set ddi_firehose_pack =
{
    DDI_PLATFORM,               //platform
    DDI_VERSION,                //version
    ddi_firehose_pack_info,     //info
    ddi_firehose_pack_items,    //items
    &ddi_firehose_pre_work,     //preworker
    &ddi_firehose_post_work     //postworker
};


boolean handleDDRTest(void *this_p)
{
    uint8 ch = 0;
    uint8 cs = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CHANNEL, item, &ch))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CS, item, &cs))
    {
        return FALSE;
    }

    if (NULL != item)
    {
        if (strncasecmp(item->item_name, NAME_STR_ITEM_A, strlen(NAME_STR_ITEM_A)) == 0)
        {
            result = ddi_DDRTestOwnAddr(ch, cs, NAME_STR_ITEM_A);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_B, strlen(NAME_STR_ITEM_B)) == 0)
        {
            result = ddi_DDRAddressLinesTest(ch, cs, NAME_STR_ITEM_A);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_C, strlen(NAME_STR_ITEM_C)) == 0)
        {
            result = ddi_DDRDataLinesTest(ch, cs, NAME_STR_ITEM_A);
        }

        ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);
    }
    else
    {
        ddi_firehose_print_log("The cmd is not supported!");
        sendResponse(NAK);
    }

    return TRUE;
}

boolean handleRWtest(void *this_p)
{
    uint8 ch = 0;
    uint8 cs = 0;
    uint32 loopcnt = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CHANNEL, item, &ch))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CS, item, &cs))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_LOOPCOUNT, item, &loopcnt))
    {
        return FALSE;
    }

    if (NULL != item)
    {
        if (strncasecmp(item->item_name, NAME_STR_ITEM_D, strlen(NAME_STR_ITEM_D)) == 0)
        {
            result = ddi_WriteTest(ch, cs, loopcnt);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_E, strlen(NAME_STR_ITEM_E)) == 0)
        {
            result = ddi_ReadTest(ch, cs, loopcnt);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_F, strlen(NAME_STR_ITEM_F)) == 0)
        {
            result = ddi_ReadWriteTest(ch, cs, loopcnt);
        }

        ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);
    }
    else
    {
        ddi_firehose_print_log("The cmd is not supported!");
        sendResponse(NAK);
    }

    return TRUE;

}

boolean handleRetrain(void *this_p)
{
    retrainDDR();
    return TRUE;
}

boolean handleChangeBIMCPhySettings(void *this_p)
{
    uint8 testline = 0;
    uint8 prfs = 0;
    uint8 ovrdrv = 0;
    uint8 PU = 0;
    uint8 ODT = 0;
    uint8 VOH = 0;
    uint8 ODTE = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_TESTLINE, item, &testline))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_PRFSLevel, item, &prfs))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_OVERDRIVE, item, &ovrdrv))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_PULLUP, item, &PU))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_ODT, item, &ODT))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VOH, item, &VOH))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_EN_TERM, item, &ODTE))
    {
        return FALSE;
    }

    result = ddi_ChangePHYSettings(testline, prfs, ovrdrv, PU, ODT, VOH, ODTE);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleReadPowerSetting(void *this_p)
{
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    result = ddi_readPowerSetting();
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleReadPhySetting(void *this_p)
{
    uint8 testline = 0;
    uint8 prfs = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_TESTLINE, item, &testline))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_PRFSLevel, item, &prfs))
    {
        return FALSE;
    }

    result = ddi_ReadPHYSettings(testline, prfs);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleReadTemperature(void *this_p)
{
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    result = ddi_readTemperature();
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean ChangeBIMCClock_init(void *this_p)
{
    ddi_firehose_item_p item = NULL;
    ddi_firehose_params_p tmpPar = NULL;

    if(NULL == this_p)
        return FALSE;

    item = (ddi_firehose_item_p)this_p;

    if(NULL != item->item_params_arr)
    {
        tmpPar = item->item_params_arr;
        while(0 != strlen(tmpPar->param_name))
        {
            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_CLOCKVALUE, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;
                tmpPar->param_max = gSupportedClockLevel-1;
                tmpPar->param_default = gSupportedClockLevel / 2;
            }
            tmpPar++;
        }
    }
    return TRUE;
}

boolean handleChangeBIMCClock(void *this_p)
{
    uint8 clockPlanIx = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if (share_data->ddi_buf[0] != DDI_MAGIC_IS_RETRAINED)
    {
        ddi_firehose_print_log("Please run Retrain test first before using this feature");
        sendResponse(NAK);
        return TRUE;
    }

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CLOCKVALUE, item, &clockPlanIx))
    {
        return FALSE;
    }

    result = ddi_ChangeBIMCClock(clockPlanIx);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}


boolean handleChangeVDDQ(void *this_p)
{
    uint32 vddVal = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VDDQVALUE, item, &vddVal))
    {
        return FALSE;
    }

    result = ddi_ChangeVDDQ(vddVal);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleChangeVDD1(void *this_p)
{
    uint32 vddVal = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VDD1VALUE, item, &vddVal))
    {
        return FALSE;
    }

    result = ddi_ChangeVDD1(vddVal);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleChangeVDD2(void *this_p)
{
    uint32 vddVal = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VDD2VALUE , item, &vddVal))
    {
        return FALSE;
    }

    result = ddi_ChangeVDD2(vddVal);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean handleChangeVDDQ_VDD2(void *this_p)
{
    uint32 vddVal = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VDDQVDD2VALUE, item, &vddVal))
    {
        return FALSE;
    }

    result = ddi_ChangeVDDQ(vddVal);
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;

}

boolean handleDisableDBI(void *this_p)
{
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    result = disableDBI();
    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;
}

boolean DRAMSettings_init(void *this_p)
{
    ddi_firehose_item_p item = NULL;
    ddi_firehose_params_p tmpPar = NULL;
    uint8 level;

    if (NULL == this_p)
        return FALSE;

    item = (ddi_firehose_item_p)this_p;

    if (getDDRType() == DDR_TYPE_LPDDR4X)
    {
        level =0;
        while(bimc_freq_switch_params_struct_lp4x[level].freq_switch_range_in_kHz != 0)
        {
            level++;
        }
    }
    else
    {
        level =0;
        while(bimc_freq_switch_params_struct[level].freq_switch_range_in_kHz != 0)
        {
            level++;
        }
    }

    if(NULL != item->item_params_arr)
    {
        tmpPar = item->item_params_arr;
        while(0 != strlen(tmpPar->param_name))
        {
            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_FREQ, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;
                tmpPar->param_max = level -1;
                tmpPar->param_default = (level -1) / 2;
            }
            tmpPar++;
        }
    }

    return TRUE;
}

boolean handleDRAMSettings(void *this_p)
{
    uint8 freq = 0;
    uint8 mr3Val = 0;
    uint8 mr11Val = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_FREQ, item, &freq))
    {
        return FALSE;
    }

    if(NULL != item)
    {
        if (strncasecmp(item->item_name, NAME_STR_ITEM_R, strlen(NAME_STR_ITEM_R)) == 0)
        {
            if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_MR3VAL, item, &mr3Val))
            {
                return FALSE;
            }

            result = ddi_ChangeMR3(freq, mr3Val);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_S, strlen(NAME_STR_ITEM_S)) == 0)
        {
            if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_MR11VAL, item, &mr11Val))
            {
                return FALSE;
            }

            result = ddi_ChangeMR11(freq, mr11Val);
        }

        ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);
    }
    else
    {
        ddi_firehose_print_log("The cmd is not supported!");
        sendResponse(NAK);
    }

    return TRUE;
}

boolean handleReadWriteMRReg(void *this_p)
{
    uint8 ch = 0;
    uint8 cs = 0;
    uint8 RegNum = 0;
    uint8 regVal = 0;
    boolean result = TRUE;
    ddi_firehose_item_p item = NULL;

    if (share_data->ddi_buf[0] != DDI_MAGIC_IS_RETRAINED)
    {
        ddi_firehose_print_log("Please run Retrain test first before using this feature");
        sendResponse(NAK);
        return TRUE;
    }

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CHANNEL, item, &ch))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CS, item, &cs))
    {
        return FALSE;
    }
    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_REGNUM, item, &RegNum))
    {
        return FALSE;
    }

    if (NULL != item)
    {
        if (strncasecmp(item->item_name, NAME_STR_ITEM_V, strlen(NAME_STR_ITEM_V)) == 0)
        {
            result = ddi_readMRReg(ch, cs, RegNum);
        }
        else if (strncasecmp(item->item_name, NAME_STR_ITEM_T, strlen(NAME_STR_ITEM_T)) == 0)
        {
            if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_REGVALUE, item, &regVal))
            {
                return FALSE;
            }

            result = ddi_writeMRReg(ch, cs, RegNum, regVal);
        }

        ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);
    }
    else
    {
        ddi_firehose_print_log("The cmd is not supported!");
        sendResponse(NAK);
    }

    return TRUE;
}


boolean DQReadVrefCDCchange_init(void *this_p)
{
    ddi_firehose_item_p item = NULL;
    ddi_firehose_params_p tmpPar = NULL;
    training_params_t training_params;

    if(NULL == this_p)
        return FALSE;

    DDRSS_set_training_params((training_params_t *)&training_params);

    item = (ddi_firehose_item_p)this_p;

    if(NULL != item->item_params_arr)
    {
        tmpPar = item->item_params_arr;
        while(0 != strlen(tmpPar->param_name))
        {
            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_CLOCKVALUE, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;
                tmpPar->param_max = gSupportedClockLevel - 1;
                tmpPar->param_default = gSupportedClockLevel - 1;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_START_VREF, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;//training_params.rd_dqdqs.coarse_vref_start_value;
                tmpPar->param_max = training_params.rd_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = 2;//0; //training_params.rd_dqdqs.coarse_vref_start_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_END_VREF, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = training_params.rd_dqdqs.coarse_vref_start_value;
                tmpPar->param_max = training_params.rd_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = 11;//training_params.rd_dqdqs.coarse_vref_max_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_VREF_STEP, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 1; //training_params.rd_dqdqs.coarse_vref_start_value;
                tmpPar->param_max = training_params.rd_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = 1;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_START_COARSECDC, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = training_params.rd_dqdqs.coarse_cdc_start_value;
                tmpPar->param_max = training_params.rd_dqdqs.coarse_cdc_max_value;
                tmpPar->param_default = training_params.rd_dqdqs.coarse_cdc_start_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_END_COARSECDC, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = training_params.rd_dqdqs.coarse_cdc_start_value;
                tmpPar->param_max = training_params.rd_dqdqs.coarse_cdc_max_value;
                tmpPar->param_default = training_params.rd_dqdqs.coarse_cdc_max_value / 2;
            }

            tmpPar++;
        }
    }
    return TRUE;

}

boolean handleDQReadVrefCDC(void* this_p)
{
    uint8 ch = 0;
    uint8 cs = 0;
    uint8 clockPlanIx = 0;
    uint8 start_vref = 0;
    uint8 end_vref = 0;
    uint8 vref_step = 0;
    uint8 start_coarse_cdc = 0;
    uint8 end_coarse_cdc = 0;
    boolean result;
    ddi_firehose_item_p item = NULL;

    if (share_data->ddi_buf[0] == DDI_MAGIC_IS_RETRAINED)
    {
        ddi_firehose_print_log("Please reload DDI again, and don't run Retrain first before runing this test!");
        sendResponse(NAK);
        return TRUE;
    }

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CHANNEL, item, &ch))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CS, item, &cs))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CLOCKVALUE, item, &clockPlanIx))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_START_VREF, item, &start_vref))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_END_VREF, item, &end_vref))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VREF_STEP, item, &vref_step))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_START_COARSECDC, item, &start_coarse_cdc))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_END_COARSECDC, item, &end_coarse_cdc))
    {
        return FALSE;
    }

    result = ddi_DQ_Read_Vref_CDC_Shmoo(ch, cs, clockPlanIx, start_vref, end_vref, vref_step, start_coarse_cdc, end_coarse_cdc);

    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;

}

boolean DQWriteVrefCDCchange_init(void *this_p)
{
    ddi_firehose_item_p item = NULL;
    ddi_firehose_params_p tmpPar = NULL;
    training_params_t training_params;

    if(NULL == this_p)
        return FALSE;

    DDRSS_set_training_params((training_params_t *)&training_params);

    item = (ddi_firehose_item_p)this_p;

    if(NULL != item->item_params_arr)
    {
        tmpPar = item->item_params_arr;
        while(0 != strlen(tmpPar->param_name))
        {
            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_CLOCKVALUE, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;
                tmpPar->param_max = gSupportedClockLevel - 1;
                tmpPar->param_default = gSupportedClockLevel - 1;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_START_VREF, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0; //training_params.wr_dqdqs.coarse_vref_start_value;
                tmpPar->param_max = training_params.wr_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = 0; //training_params.wr_dqdqs.coarse_vref_start_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_END_VREF, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 0;//training_params.wr_dqdqs.coarse_vref_start_value;
                tmpPar->param_max = training_params.wr_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = training_params.wr_dqdqs.coarse_vref_max_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_VREF_STEP, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = 1;
                tmpPar->param_max = training_params.wr_dqdqs.coarse_vref_max_value;
                tmpPar->param_default = 2;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_START_COARSECDC, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = training_params.wr_dqdqs.coarse_cdc_start_value;
                tmpPar->param_max = training_params.wr_dqdqs.coarse_cdc_max_value;
                tmpPar->param_default = training_params.wr_dqdqs.coarse_cdc_start_value;
            }

            if(0 == strncasecmp(tmpPar->param_name, NAME_STR_END_COARSECDC, strlen((const char *)tmpPar->param_name)))
            {
                tmpPar->param_min = training_params.wr_dqdqs.coarse_cdc_start_value;
                tmpPar->param_max = training_params.wr_dqdqs.coarse_cdc_max_value;
                tmpPar->param_default = training_params.wr_dqdqs.coarse_cdc_max_value / 2;
            }

            tmpPar++;
        }
    }
    return TRUE;

}

boolean handleDQWriteVrefCDC(void* this_p)
{
    uint8 ch = 0;
    uint8 cs = 0;
    uint8 clockPlanIx = 0;
    uint8 start_vref = 0;
    uint8 end_vref = 0;
    uint8 vref_step = 0;
    uint8 start_coarse_cdc = 0;
    uint8 end_coarse_cdc = 0;
    boolean result;
    ddi_firehose_item_p item = NULL;

    if (share_data->ddi_buf[0] == DDI_MAGIC_IS_RETRAINED)
    {
        ddi_firehose_print_log("Please reload DDI again, and don't run Retrain first before runing this test!");
        sendResponse(NAK);
        return TRUE;
    }

    if(NULL != this_p)
        item = (ddi_firehose_item_p)this_p;
    else
        return FALSE;

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CHANNEL, item, &ch))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CS, item, &cs))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_CLOCKVALUE, item, &clockPlanIx))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_START_VREF, item, &start_vref))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_END_VREF, item, &end_vref))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_VREF_STEP, item, &vref_step))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_START_COARSECDC, item, &start_coarse_cdc))
    {
        return FALSE;
    }

    if(FALSE == ddi_firehose_fetch_parameters(NAME_STR_END_COARSECDC, item, &end_coarse_cdc))
    {
        return FALSE;
    }

    result = ddi_DQ_Write_Vref_CDC_Shmoo(ch, cs, clockPlanIx, start_vref, end_vref, vref_step, start_coarse_cdc, end_coarse_cdc);

    ddi_firehose_print_response(item->item_name, NAME_STR_RESULT, ddi_firehose_bool_name[result]);

    return TRUE;

}

boolean ddi_firehose_pre_work(void* this_p)
{
    DalDeviceHandle *hChipinfo = NULL;
    char platform_id[10]= {0};
    int32 ret = 0;
    //ddr_interface_state ddi_state;
    //ddr_size_info ddi_sizeInfo;

    ret = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &hChipinfo);
    if((ret == DAL_SUCCESS) && (hChipinfo != NULL))
    {
        DalChipInfo_GetChipIdString(hChipinfo, platform_id,10);

        snprintf(ddi_firehose_pack.platform,
                 strlen(platform_id) + 1,
                 "%s",
                 platform_id);
    }

#if 0
    ddi_state = ddr_get_status();
    ddi_sizeInfo = ddr_get_size();

    if (DDR_UNAVAILABLE != ddi_state.sdram0_cs0)
    {
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram0_cs0_addr", 'x', &ddi_sizeInfo.sdram0_cs0_addr);
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram0_cs0_size", 'x', &ddi_sizeInfo.sdram0_cs0);
    }
    if (DDR_UNAVAILABLE != ddi_state.sdram0_cs1)
    {
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram0_cs1_addr", 'x', &ddi_sizeInfo.sdram0_cs1_addr);
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram0_cs1_size", 'x', &ddi_sizeInfo.sdram0_cs1);
    }
    if (DDR_UNAVAILABLE != ddi_state.sdram1_cs0)
    {
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram1_cs0_addr", 'x', &ddi_sizeInfo.sdram1_cs0_addr);
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram1_cs0_size", 'x', &ddi_sizeInfo.sdram1_cs0);
    }

    if (DDR_UNAVAILABLE != ddi_state.sdram1_cs1)
    {
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram1_cs1_addr", 'x', &ddi_sizeInfo.sdram1_cs1_addr);
        ddi_firehose_add_ddi_infomation(ddi_firehose_pack.info_arr, "sdram1_cs1_size", 'x', &ddi_sizeInfo.sdram1_cs1);
    }
#endif

    update_ddr_clock_table();
    initDDIBuffer();
    initMRStruct();

    return TRUE;

}

boolean ddi_firehose_post_work(void* this_p)
{

    return TRUE;
}

//The entry point from SBL.
void ddi_entry(boot_pbl_shared_data_type *pbl_shared)
{
    extern pm_sbl_pdm_config_type pm_psi_header;
    pm_psi_header.pm_psi_info->major_ver = 0x01;
    ddi_firehose_update_item_set(&ddi_firehose_pack);
    ddi_init_hw();
    main_firehose();
}

