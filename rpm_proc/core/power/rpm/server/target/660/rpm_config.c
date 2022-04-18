/*===========================================================================

  Copyright (c) 2012-2015 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include "rpm_config.h"

static const unsigned SUPPORTED_CLASSES   = 32; // TODO: may need to adjust
static const unsigned SUPPORTED_RESOURCES = 148; // TODO; may need to adjust

//
// BEGIN config data; should migrate to the system enumeration data method
//
static SystemData temp_config_data =
{
    .num_ees = 5, // 6 EE's, [apps, modem, lpass, tz, cdsp]

    .ees    = (EEData[] ) {
        [RPM_EE_APSS] = {
            .remote_ss = "apss",
            .glink_fifo_sz = 1024,
            .ee_buflen = 256,
            .priority  = TASK_PRIORITY_APPS,
            .wakeupInt = (1 << 5) | (1 << 7),
            .spm       = {
                             .numCores = 1,
                             .bringupInts  = (unsigned[]) {  6 }, // ? Monaco
                             .bringupAcks  = (unsigned[]) { 17 }, // ? Monaco
                             .shutdownInts = (unsigned[]) { 14 }, // ? Monaco
                             .shutdownAcks = (unsigned[]) {  1 }, // ? Monaco
                         },
        },
        [RPM_EE_MPSS] = {
            .remote_ss = "mpss",
            .glink_fifo_sz = 1024,
            .ee_buflen = 1024,
            .priority  = TASK_PRIORITY_MODEM,
            .wakeupInt = (1 << 13) | (1 << 15),
            .spm       = {
                             .numCores = 1,
                             .bringupInts  = (unsigned[]) { 33 },
                             .bringupAcks  = (unsigned[]) { 22 },
                             .shutdownInts = (unsigned[]) { 43 },
                             .shutdownAcks = (unsigned[]) {  6 },
                         },
        },
        [RPM_EE_LPASS] = {
            .remote_ss = "lpass",
            .glink_fifo_sz = 1024,
            .ee_buflen = 256,
            .priority  = TASK_PRIORITY_QDSP,
            .wakeupInt = (1 << 9) | (1 << 11),
            .spm       = {
                             .numCores = 1,
                             .bringupInts  = (unsigned[]) { 56 },
                             .bringupAcks  = (unsigned[]) { 21 },
                             .shutdownInts = (unsigned[]) { 57 },
                             .shutdownAcks = (unsigned[]) {  5 },
                         },
        },
        [RPM_EE_TZ] = {
            .remote_ss = "tz",
            .glink_fifo_sz = 1024,
            .ee_buflen = 256,
            .priority  = TASK_PRIORITY_TZ,
            .wakeupInt = 0,
            .spm       = {
                             .numCores = 0,
                         },
        },
        [RPM_EE_CDSP] = {
            .remote_ss = "cdsp",
            .glink_fifo_sz = 1024,
            .ee_buflen = 256,
            .priority  = TASK_PRIORITY_CDSP,
            .wakeupInt = (1 << 1) | (1 << 3),
            .spm       = {
                             .numCores = 1,
                             .bringupInts  = (unsigned[]) { 26 },
                             .bringupAcks  = (unsigned[]) { 24 },
                             .shutdownInts = (unsigned[]) { 27 },
                             .shutdownAcks = (unsigned[]) {  9 },
                         },
        },
    },

    .supported_classes   = SUPPORTED_CLASSES,
    .supported_resources = SUPPORTED_RESOURCES,
    .classes             = (ResourceClassData[SUPPORTED_CLASSES]) { 0 },
    .resources           = (ResourceData[SUPPORTED_RESOURCES])    { 0 },
    .resource_seeds      = (int16_t[SUPPORTED_RESOURCES])         { 0 },
};
//
// END config data
//

__attribute__((section("cram_save_pool")))
SystemData * const rpm = &temp_config_data;

