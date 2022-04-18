/**
 * @file:  cpr_hal.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2017/03/06 22:14:55 $
 * $Header: //components/rel/rpm.bf/1.8/core/power/cpr/common/hal/inc/cpr_hal.h#4 $
 * $Change: 12599917 $
 *
 */
#ifndef CPR_HAL_H
#define CPR_HAL_H

#include "cpr_types.h"
#include "cpr_voltage_plan.h"
#include "cpr_target_hwio.h"

#define CPR_HWIO_IN(addr)        __inpdw((uint8*)(addr))
#define CPR_HWIO_OUT(addr, val)  __outpdw((uint8*)(addr), val)

#define CPR_HWIO_OUT_SET(addr, mask)    CPR_HWIO_OUT(addr, ((CPR_HWIO_IN(addr)) | (mask)))
#define CPR_HWIO_OUT_CLEAR(addr, mask)  CPR_HWIO_OUT(addr, ((CPR_HWIO_IN(addr)) & (~(mask))))

#define CPR_HWIO_IN_MASK(addr, mask)         (CPR_HWIO_IN(addr) & (mask))
#define CPR_HWIO_OUT_MASK(addr, mask, val)    CPR_HWIO_OUT(addr, ((CPR_HWIO_IN(addr) & (~(mask))) | ((val) & (mask))))

#define CPR_HWIO_GET_FIELD_VALUE(value, field)  (((value) & field##_BMSK) >> field##_SHFT)
#define CPR_HWIO_SET_FIELD_VALUE(value, field)  (((value) << field##_SHFT) & field##_BMSK)
#define CPR_HWIO_IN_FIELD(addr, field)       (CPR_HWIO_IN_MASK( addr, field##_BMSK ) >> field##_SHFT)
#define CPR_HWIO_OUT_FIELD(addr, field, val)  CPR_HWIO_OUT_MASK( addr, field##_BMSK, (val) << field##_SHFT )


/*
 * CR 1041073:
 * RPM wdog (32ms) expired before 20 ms timeout happened.
 * The 20ms timeout counter was set to 6667, assuming each loop takes 3 usec due to busywait.
 * But when the wdog expired, the remaining counter value was 164.
 * That means each loop actually took ~4.9 usec:
 *
 *      32ms / (6667 - 164) loops = ~4.9 usec per loop
 *
 * Changed to use QTimer instead of counter to make it robust.
 */
#define RESULTS_TIMEOUT_20MS  384000 // ticks (20 ms * 19.2 tick/usec * 1000 = 384000 ticks)
#define RESULTS_TIMEOUT_5MS    96000 // ticks ( 5 ms * 19.2 tick/usec * 1000 =  96000 ticks)


typedef enum
{
    CPR_HAL_COUNT_MODE_ALL_AT_ONCE_MIN  = 0,
    CPR_HAL_COUNT_MODE_ALL_AT_ONCE_MAX  = 1,
    CPR_HAL_COUNT_MODE_STAGGERED        = 2,
    CPR_HAL_COUNT_MODE_ALL_AT_ONCE_AGE  = 3
} cpr_hal_count_mode;

/*
 * Static config for thread required for initialization only
 */
typedef struct
{
    uint8   upThresh;
    uint8   dnThresh;
    uint8   consecUp;
    uint8   consecDn;

    uint8         sensorsCount; /* Number of sensors on this thread */
    const uint8  *sensors;      /* Sensor IDs on this thread */
#if 0
    uint32 autoContInterval;
    uint8 gcntCount;
    uint8 *gcnt;
#endif

} cpr_hal_thread_cfg;

typedef struct
{
    unsigned busy     :  1; // BUSY direct connect from cpr_master.busy
    unsigned stepDn   :  1; // STEP_DN direct connect from cpr_master.step_dn
    unsigned stepUp   :  1; // STEP_UP direct connect from cpr_master.step_up
    unsigned steps    :  5; // ERROR_STEPS direct connect from cpr_master.error_steps[3:0]. This field indicates the number of PMIC steps that the cpr_master is recommending as an adjustment.
    unsigned error    : 12; // ERROR direct connect from cpr_master.error[11:0]. The error term is the difference between the actual quotient of the slowest delay chain of the slowest sensor and its target.
    unsigned errorLt0 :  1; // direct connect from cpr_master.error_lt_0. This bit indicates if the error is less than zero.
    unsigned reserved : 11;
} cpr_hal_result0;

typedef struct
{
    unsigned quotMin : 12; // QUOT_MIN The quot of that RO which is below target and furthest from target. It is the one that is used for step_up/dn and error. if all ROs are above 'target', then 'quot_min' returns minimum 'quot' that's closest to 'target' from the above, across ROs
    unsigned quotMax : 12; // QUOT_MAX The quot of that RO which is ABOVE target and furthest from target. ROs whose quot is below target are ignored and their maximum 'quot' does not contribute to 'quot_max'. 'quot_max' is per-Iteration extra datapoint to help assess process spread and also get AGE_MAX/MIN readout in one shot. It doesn't affect 'step_up/dn'
    unsigned selMin  :  4; // SEL_MIN RO ID that originated quot_min
    unsigned selMax  :  4; // SEL_MAX RO ID that originated quot_max
} cpr_hal_result1;

typedef struct
{
    unsigned stepQuotMin : 6; // STEP_QUOT_MIN Actual min step_quot (Kv) as measured by the controller. step_quot_min is per-arst-session running average of 'quot_delta_min' across all ROs and all sensors of the thread
    unsigned stepQuotMax : 6; // STEP_QUOT_MAX Actual max step_quot (Kv) as measured by the controller. step_quot_max is per-arst-session running average of 'quot_delta_max' across all ROs and all sensors of the thread
    unsigned reserved    : 4;
    unsigned sensorMin   : 8; // SENSOR_MIN Sensor ID/position that originated 'quot_min'
    unsigned sensorMax   : 8; // SENSOR_MAX Sensor ID/position that originated 'quot_max'
} cpr_hal_result2;

typedef struct
{
    cpr_hal_result0  result0;
    cpr_hal_result1  result1;
    cpr_hal_result2  result2;
} cpr_hal_results;

/*
 * Thread Info
 */
typedef struct
{
    uint8    id;             /* Thread ID (can be used as the index of threads array of controller) */

    /*
     * Status data used for RO enablement and debugging
     */
    boolean  init;           /* 1: initialized, 0: not initialized yet */
    boolean  enabled;        /* 1: thread is enabled, 0: thread is disabled */
    uint16   roMask4Thread;  /* each bit for corresponding 16 ROs: 1: masked, 0: unmasked */

    cpr_hal_results *results;

    const cpr_hal_thread_cfg  *cfg;
} cpr_hal_thread;

/*
 * Static config for controller for initialization only
 */
typedef struct
{
    uint8  sensorsTotal;        /* Total number of sensors in the controller */
    uint8  bypassSensorsCount;  /* The number of bypassSensors */
    uint8  disableSensorsCount; /* The number of disableSensors */

    uint8  stepQuotMax;         /* [11:6] STEP_QUOT_INIT_MAX */
    uint8  stepQuotMin;         /* [ 5:0] STEP_QUOT_INIT_MIN */

    const uint8  *bypassSensors;
    const uint8  *disableSensors;

    const char   *refClk;
    const char   *ahbClk;
} cpr_hal_controller_cfg;

/*
 * NOTE: the order is different from IPcat due to little endian
 */
typedef struct
{
    unsigned hotTempCx10 :12; // Hot temperature on the last Tsense reading in degree C x10
    unsigned hotSensor   : 4; // Hot sensor on the last tsense reading
    unsigned coldTempCx10:12; // Cold temperature on the last Tsense reading in degree C x10
    unsigned coldSensor  : 4; // Cold sensor on the last tsense reading
} cpr_hal_temp_data;

/*
 * Controller Info
 */
typedef struct
{
    uintptr_t           base;  /* CPR controller base address */
    cpr_controller_type type;
    uint8               threadsCount; /* The number of threads */

    /*
     * Status data used for RO enablement and debugging
     */
    boolean             init;    /* 1: initialized, 0: not initialized yet */
    boolean             enabled; /* 1: LOOP_EN is 1, 0: LOOP_EN is 0 */
    boolean             marginAdjEnabled;
    uint16              roMask;  /* each bit for corresponding 16 ROs: 1: disabled (GCNT=0), 0: enabled (GCNT=19) */
    cpr_hal_temp_data   tempSensorData;

    const cpr_hal_controller_cfg  *cfg;

    cpr_hal_thread     **threads; /* Threads info on this Controller */
} cpr_hal_controller;


typedef struct
{
  cpr_hal_controller  *controller;
  cpr_hal_thread      *thread;
} cpr_hal_handle;



boolean cpr_hal_get_results(cpr_hal_handle* hdl, cpr_results* rslts, uint32 timeout_ticks);
void cpr_hal_ack_result(cpr_hal_handle* hdl, boolean ack);
void cpr_hal_clear_interrupts(cpr_hal_handle* hdl);

void cpr_hal_enable_controller(cpr_hal_handle* hdl, boolean enable);
void cpr_hal_init_controller(cpr_hal_handle* hdl, boolean configureHW);
void cpr_hal_start_poll(cpr_hal_handle* hdl);
void cpr_hal_stop_poll(cpr_hal_handle* hdl);
void cpr_hal_enable_up_interrupt(cpr_hal_handle* hdl, boolean enable);
void cpr_hal_enable_down_interrupt(cpr_hal_handle* hdl, boolean enable);
void cpr_hal_enable_rail(cpr_hal_handle* hdl, boolean up, boolean down, boolean mid, boolean swControl);
void cpr_hal_set_targets(cpr_hal_handle* hdl, cpr_voltage_mode mode, uint32 freq, cpr_quotient* tgts, uint32 count);
void cpr_hal_disable_rail(cpr_hal_handle* hdl);
void cpr_hal_set_count_mode(cpr_hal_handle* hdl, cpr_hal_count_mode count_mode);

/*
 * De-Aging
 */
void cpr_hal_enable_aging(cpr_hal_handle* hdl, const cpr_aging_cfg* aging_cfg);
void cpr_hal_disable_aging(cpr_hal_handle* hdl, const cpr_aging_cfg* aging_cfg);
boolean cpr_hal_get_aging_delta(cpr_hal_handle* hdl, int32 *aging_delta, uint32 *retry_count);

/*
 * CPR4 Temperature Margin Adjustment
 */
void cpr_hal_init_temp_margin_adj(cpr_hal_handle* hdl, uint8 modeIndex, const cpr_voltage_plan* vp);
void cpr_hal_enable_temp_margin_adj(cpr_hal_handle* hdl, const cpr_voltage_plan* vp, boolean enable );
void cpr_hal_set_temp_margin(cpr_hal_handle* hdl, uint8 modeIndex, const cpr_voltage_plan* vp);

#endif

