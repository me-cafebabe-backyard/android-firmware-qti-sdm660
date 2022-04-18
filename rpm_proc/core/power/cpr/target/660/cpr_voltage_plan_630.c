/*******************************************************************************
 *
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR 630.
 *
 * DateTime: 2020/02/03 03:52:03
 *
 *******************************************************************************/

#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static const char voltage_plan_hash_value[] = "ED8C36FBE3B3799B671BEE79D3AC778F";


/*******************************************************************************
********************************************************************************
**
** Voltage Plan Data
**
********************************************************************************
********************************************************************************/

static const cpr_margin_cfg margins_510 = {
    .count = 1,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .maxFloorToCeil =      0 } }
};


static const cpr_fuse_data  fuses_0 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_quotient_cfg  quotients_14294275849 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  595 },
                                      { .ro =  7, .quotient =  553 },
                                      { .ro =  8, .quotient =  811 },
                                      { .ro =  9, .quotient =  768 },
                                      { .ro = 10, .quotient =  837 },
                                      { .ro = 11, .quotient =  811 } },
};


static const cpr_fuse_data  fuses_1430219223 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_LSB, CPR3_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_quotient_cfg  quotients_15780032753 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  687 },
                                      { .ro =  7, .quotient =  638 },
                                      { .ro =  8, .quotient =  897 },
                                      { .ro =  9, .quotient =  856 },
                                      { .ro = 10, .quotient =  938 },
                                      { .ro = 11, .quotient =  911 } },
};


static const cpr_fuse_data  fuses_3983832470 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_LSB, CPR3_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_kv_cfg  kvs_13972334153 =
{
    .count = 6,
    .kvs   = (const cpr_kv[]) { { .ro =  6, .kv =  176 },
                                { .ro =  7, .kv =  175 },
                                { .ro =  8, .kv =  183 },
                                { .ro =  9, .kv =  177 },
                                { .ro = 10, .kv =  198 },
                                { .ro = 11, .kv =  190 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9904229595 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_13972334153,
    .supportedModes  = (const cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // SVS_L1
        {.fref = 852000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  852000, .floor =  852000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL
        {.fref = 912000, .freqDelta =       0, .fuses = &fuses_1430219223, .quotients = &quotients_14294275849, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  912000, .floor =  852000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL_L1
        {.fref = 924000, .freqDelta =       0, .fuses = &fuses_1430219223, .quotients = &quotients_14294275849, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  924000, .floor =  852000, .freq =       0, .interplEnabled = false} } },

        // TURBO
        {.fref = 988000, .freqDelta =       0, .fuses = &fuses_3983832470, .quotients = &quotients_15780032753, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  988000, .floor =  852000, .freq =       0, .interplEnabled = false} } }},
};


static const cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static const cpr_quotient_cfg  quotients_9419384043 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  263 },
                                      { .ro =  7, .quotient =  247 },
                                      { .ro =  8, .quotient =  413 },
                                      { .ro =  9, .quotient =  397 },
                                      { .ro = 10, .quotient =  415 },
                                      { .ro = 11, .quotient =  412 } },
};


static const cpr_fuse_data  fuses_354107995 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW3_LSB, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_quotient_cfg  quotients_13528529687 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  375 },
                                      { .ro =  7, .quotient =  354 },
                                      { .ro =  8, .quotient =  554 },
                                      { .ro =  9, .quotient =  519 },
                                      { .ro = 10, .quotient =  573 },
                                      { .ro = 11, .quotient =  554 } },
};


static const cpr_fuse_data  fuses_333806192 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW3_LSB, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_quotient_cfg  quotients_14902452412 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  412 },
                                      { .ro =  7, .quotient =  380 },
                                      { .ro =  8, .quotient =  597 },
                                      { .ro =  9, .quotient =  562 },
                                      { .ro = 10, .quotient =  612 },
                                      { .ro = 11, .quotient =  591 } },
};


static const cpr_quotient_cfg  quotients_12386205346 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  513 },
                                      { .ro =  7, .quotient =  476 },
                                      { .ro =  8, .quotient =  722 },
                                      { .ro =  9, .quotient =  680 },
                                      { .ro = 10, .quotient =  738 },
                                      { .ro = 11, .quotient =  718 } },
};


static const cpr_fuse_data  fuses_1253398200 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW3_LSB, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_fuse_data  fuses_1677607257 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW3_LSB, CPR0_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_temp_adj_cfg  temp_adj_cfg_cx_4_6_0_25_85 =
{
    .tempSensorStartId = 4,
    .tempSensorEndId   = 6,
    .tempPoints        = { 0, 25, 85 }, // degree C
};


static const cpr_kv_cfg  kvs_8132522154 =
{
    .count = 6,
    .kvs   = (const cpr_kv[]) { { .ro =  6, .kv =  179 },
                                { .ro =  7, .kv =  176 },
                                { .ro =  8, .kv =  199 },
                                { .ro =  9, .kv =  190 },
                                { .ro = 10, .kv =  214 },
                                { .ro = 11, .kv =  202 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_8986606289 =
{
    .modesCount      = 6,
    .tempAdjCfg      = &temp_adj_cfg_cx_4_6_0_25_85,
    .kvCfg           = &kvs_8132522154,
    .supportedModes  = (const cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 644000, .freqDelta =       0, .fuses = &fuses_354107995, .quotients = &quotients_9419384043, .margins = &margins_510,
         .marginTempBands = { 0, 0, 0, 0 }, // PMIC step size
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = false} } },

        // SVS
        {.fref = 724000, .freqDelta =       0, .fuses = &fuses_333806192, .quotients = &quotients_13528529687, .margins = &margins_510,
         .marginTempBands = { 0, 0, 0, 0 }, // PMIC step size
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = false} } },

        // SVS_L1
        {.fref = 788000, .freqDelta =       0, .fuses = &fuses_333806192, .quotients = &quotients_14902452412, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  788000, .floor =  652000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL
        {.fref = 868000, .freqDelta =       0, .fuses = &fuses_1253398200, .quotients = &quotients_12386205346, .margins = &margins_510,
         .marginTempBands = { 0, 0, 0, 0 }, // PMIC step size
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  868000, .floor =  712000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL_L1
        {.fref = 924000, .freqDelta =       0, .fuses = &fuses_1253398200, .quotients = &quotients_14294275849, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  924000, .floor =  744000, .freq =       0, .interplEnabled = false} } },

        // TURBO
        {.fref = 988000, .freqDelta =       0, .fuses = &fuses_1677607257, .quotients = &quotients_15780032753, .margins = &margins_510,
         .marginTempBands = { 0, 0, 0, 0 }, // PMIC step size
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  988000, .floor =  784000, .freq =       0, .interplEnabled = false} } }},
};


static const cpr_fuse_data  fuses_2084178192 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_MSB, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_fuse_data  fuses_3046179949 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_MSB, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_6236683706 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_13972334153,
    .supportedModes  = (const cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // SVS_L1
        {.fref = 848000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  848000, .floor =  848000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL
        {.fref = 912000, .freqDelta =       0, .fuses = &fuses_2084178192, .quotients = &quotients_14294275849, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  912000, .floor =  848000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL_L1
        {.fref = 920000, .freqDelta =       0, .fuses = &fuses_2084178192, .quotients = &quotients_14294275849, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  920000, .floor =  848000, .freq =       0, .interplEnabled = false} } },

        // TURBO
        {.fref = 992000, .freqDelta =       0, .fuses = &fuses_3046179949, .quotients = &quotients_15780032753, .margins = &margins_510,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  992000, .floor =  848000, .freq =       0, .interplEnabled = false} } }},
};


static const cpr_margin_cfg margins_55014 = {
    .count = 1,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 7, .openLoop =       0, .closedLoop =   11000, .maxFloorToCeil =      0 } }
};


static const cpr_quotient_cfg  quotients_10149653726 =
{
    .count = 6,
    .quots = (const cpr_quotient[]) { { .ro =  6, .quotient =  174 },
                                      { .ro =  7, .quotient =  167 },
                                      { .ro =  8, .quotient =  294 },
                                      { .ro =  9, .quotient =  292 },
                                      { .ro = 10, .quotient =  303 },
                                      { .ro = 11, .quotient =  313 } },
};


static const cpr_fuse_data  fuses_1525307024 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_MSB, CPR4_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_margin_cfg margins_159976 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -20000, .closedLoop =  -20000, .maxFloorToCeil =      0 } }
};


static const cpr_margin_cfg margins_319976 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -40000, .closedLoop =  -40000, .maxFloorToCeil =      0 } }
};


static const cpr_fuse_data  fuses_1335669278 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_LSB, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_margin_cfg margins_349976 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =    5000, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -50000, .closedLoop =  -45000, .maxFloorToCeil =      0 } }
};


static const cpr_margin_cfg margins_109976 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =    5000, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -20000, .closedLoop =  -15000, .maxFloorToCeil =      0 } }
};


static const cpr_fuse_data  fuses_2888268017 =
{
    .volt       = (const cpr_fuse[]) { {.count = 2, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_MSB, CPR4_TARG_VOLT_NOM_4), CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_LSB, CPR4_TARG_VOLT_NOM_3_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static const cpr_margin_cfg margins_9976 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   11000, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -15000, .closedLoop =   -4000, .maxFloorToCeil =      0 } }
};


static const cpr_margin_cfg margins_140024 = {
    .count = 2,
    .data = (const cpr_margin_data[]) { { .cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   26000, .maxFloorToCeil =      0 },
                                        { .cprRevMin = 2, .cprRevMax = 7, .openLoop =  -15000, .closedLoop =   11000, .maxFloorToCeil =      0 } }
};


static const cpr_fuse_data  fuses_94616107 =
{
    .volt       = (const cpr_fuse[]) { {.count = 1, .data = (const struct raw_fuse_data[]) { CPR_FUSE_MAPPING(QFPROM_CORR_CALIB_ROW5_LSB, CPR4_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_14302599601 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_8132522154,
    .supportedModes  = (const cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_MIN_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // MIN_SVS
        {.fref = 584000, .freqDelta =       0, .fuses = &fuses_1525307024, .quotients = &quotients_10149653726, .margins = &margins_55014,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  584000, .floor =  504000, .freq =       0, .interplEnabled = false} } },

        // LOW_SVS
        {.fref = 648000, .freqDelta =       0, .fuses = &fuses_1525307024, .quotients = &quotients_9419384043, .margins = &margins_159976,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  672000, .floor =  504000, .freq =       0, .interplEnabled = false} } },

        // SVS
        {.fref = 720000, .freqDelta =       0, .fuses = &fuses_1335669278, .quotients = &quotients_13528529687, .margins = &margins_319976,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = false} } },

        // SVS_L1
        {.fref = 792000, .freqDelta =       0, .fuses = &fuses_1335669278, .quotients = &quotients_14902452412, .margins = &margins_349976,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  792000, .floor =  648000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL
        {.fref = 864000, .freqDelta =       0, .fuses = &fuses_2888268017, .quotients = &quotients_12386205346, .margins = &margins_109976,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = false} } },

        // NOMINAL_L1
        {.fref = 920000, .freqDelta =       0, .fuses = &fuses_2888268017, .quotients = &quotients_14294275849, .margins = &margins_9976,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  920000, .floor =  744000, .freq =       0, .interplEnabled = false} } },

        // TURBO
        {.fref = 992000, .freqDelta =       0, .fuses = &fuses_94616107, .quotients = &quotients_15780032753, .margins = &margins_140024,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (const cpr_freq_data[]){ {.ceiling =  992000, .floor =  784000, .freq =       0, .interplEnabled = false} } }},
};


/*
 * Aging configs
 */

/*
 * Versioned Voltage Plans
 */

static const cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_14302599601 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static const cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6236683706 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static const cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_8986606289 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static const cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9904229595 },
     },
    .count    = 1,
    .agingCfg = NULL
};

/*******************************************************************************
********************************************************************************
**
** Enablement Config Data
**
********************************************************************************
********************************************************************************/

/*
 * CPR Controller Thread Config
 */

static const cpr_hal_thread_cfg cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 2,
    .sensors      = (const uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48 },
    .sensorsCount = 49,
};


static cpr_hal_thread  cx_thread = {
    .id   = 0,
    .cfg  = &cx_thread_cfg,
};


static const cpr_hal_thread_cfg lpi_cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 2,
    .sensors      = (const uint8[]){ 15,16,17 },
    .sensorsCount = 3,
};


static cpr_hal_thread  lpi_cx_thread = {
    .id   = 0,
    .cfg  = &lpi_cx_thread_cfg,
};


static const cpr_hal_thread_cfg mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 2,
    .sensors      = NULL,
    .sensorsCount = 0,
};


static cpr_hal_thread  mx_thread = {
    .id   = 1,
    .cfg  = &mx_thread_cfg,
};


static const cpr_hal_thread_cfg wlan_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 2,
    .sensors      = NULL,
    .sensorsCount = 0,
};


static cpr_hal_thread  wlan_thread = {
    .id   = 2,
    .cfg  = &wlan_thread_cfg,
};


static const cpr_hal_thread_cfg lpi_mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 2,
    .sensors      = NULL,
    .sensorsCount = 0,
};


static cpr_hal_thread  lpi_mx_thread = {
    .id   = 3,
    .cfg  = &lpi_mx_thread_cfg,
};


/*
 * CPR Controller Config
 */

static const cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 12,
    .stepQuotMax         = 14,
    .sensorsTotal        = 49,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (const uint8[]){ 3,4,44,45 },
    .disableSensorsCount = 4,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cpr3_controller = {
    .base                = 0x60628000,
    .type                = CPR_CONTROLLER_TYPE_SW_CL_ONLY,
    .cfg                 = &cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &cx_thread },
    .threadsCount        = 1,
};


static const cpr_hal_controller_cfg mx_cpr3_controller_cfg = {
    .stepQuotMin         = 12,
    .stepQuotMax         = 14,
    .sensorsTotal        = 22,
    .bypassSensors       = (const uint8[]){ 2,3,4,5,6,7,8,9,12,13,14 },
    .bypassSensorsCount  = 11,
    .disableSensors      = (const uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,18,19,20,21 },
    .disableSensorsCount = 19,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mx_cpr3_controller = {
    .base                = 0x6062c000,
    .type                = CPR_CONTROLLER_TYPE_SW_CL_ONLY,
    .cfg                 = &mx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &lpi_cx_thread, &mx_thread, &wlan_thread, &lpi_mx_thread },
    .threadsCount        = 4,
};


/*
 * HAL Rail Config
 */

static cpr_rail cpr_rail_cx_cfg = {
    .id               = CPR_RAIL_CX,
    .name             = "CX",
    .hal              = { .controller = &cpr3_controller, .thread = &cx_thread },
    .interruptId      = 54,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_cx_cfg = {
    .id               = CPR_RAIL_LPI_CX,
    .name             = "LPI_CX",
    .hal              = { .controller = &mx_cpr3_controller, .thread = &lpi_cx_thread },
    .interruptId      = 17,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_mx_cfg = {
    .id               = CPR_RAIL_LPI_MX,
    .name             = "LPI_MX",
    .hal              = { .controller = &mx_cpr3_controller, .thread = &lpi_mx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mx_cfg = {
    .id               = CPR_RAIL_MX,
    .name             = "MX",
    .hal              = { .controller = &mx_cpr3_controller, .thread = &mx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


/*
 * Rail Enablement Config
 */

static const cpr_version  ver_ANY_0_0_255_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(0,0), .max = CPR_CHIPINFO_VERSION(255,255) };


static const cpr_enablement cpr_rail_cx_enablement_0_0_255_255 =
{
    .id                = CPR_RAIL_CX,
    .version           = &ver_ANY_0_0_255_255,
    .funcId            = CPR_INIT_SMEM,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
};


static const cpr_enablement cpr_rail_lpi_cx_enablement_0_0_255_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_0_0_255_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
};


static const cpr_enablement cpr_rail_lpi_mx_enablement_0_0_255_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_0_0_255_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
};


static const cpr_enablement cpr_rail_mx_enablement_0_0_255_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_0_0_255_255,
    .funcId            = CPR_INIT_SMEM,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
};


static const cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {0x6078423c, 7, 0x380} } }
};


const cpr_settings cpr_settings_630 =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (const cpr_versioned_voltage_plan*[]) { &cx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mx_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mx_cfg },
    .railsCount       = 4,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &mx_cpr3_controller },
    .controllersCount = 2,

    .enablements      = (const cpr_enablement*[]) { &cpr_rail_cx_enablement_0_0_255_255, &cpr_rail_lpi_cx_enablement_0_0_255_255, &cpr_rail_lpi_mx_enablement_0_0_255_255, &cpr_rail_mx_enablement_0_0_255_255 },
    .enablementsCount = 4,

    .miscCfg          = &misc_cfg,
};

