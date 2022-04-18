#include <stdio.h>

#include "sns_memmgr.h"
#include "sns_init.h"
#include "sns_pm.h"
#include "sns_smgr.h"
#include "sns_common.h"
#include "sns_log_api_public.h"
#include "sns_profiling.h"
#include "sns_uimg_utils.h"
#include "sns_smgr_priv.h"
/**
 * see sns_init.h
 */
void TIMETICK_SCLK_FROM_US(void){}
void sns_init_done( void )
{
  // Not much to do here, at the moment
  uint8_t errOS;
  sns_os_sigs_post( playback_sig_event, (OS_FLAGS) FPB_INIT_DONE,
    OS_FLAG_SET, &errOS );
}

void sns_deinit_done( void )
{
  // signal back to playback thread for proper tear down
  uint8_t errOS;
  sns_os_sigs_post( playback_sig_event, (OS_FLAGS) FPB_REG_DEINIT_DONE,
    OS_FLAG_SET, &errOS );
}

#ifdef FAST_PLAYBACK
smgr_sensor_cfg_s smgr_sensor_cfg[ SNS_SMGR_NUM_SENSORS_DEFINED ] =
  {
   {
	0,
	{0},
	(uint16_t)((SNS_SMGR_SENSOR_0_OFF_TO_IDLE/SNS_SMGR_USEC_PER_TICK)+1),
	(uint16_t)((SNS_SMGR_SENSOR_0_IDLE_TO_READY/SNS_SMGR_USEC_PER_TICK)+1),
	SNS_SMGR_ID_ACCEL_V01, //SNS_SMGR_SENSOR_0_ENUM_CODE,
	SNS_SMGR_SENSOR_0_BUS_ADDRESS,
	SNS_SMGR_SENSOR_0_RANGE_TYPE,
	SNS_SMGR_SENSOR_0_SENSITIVITY_DEFAULT,
	SNS_SMGR_SENSOR_0_REG_ITEM_TYPE,
	SNS_SMGR_SENSOR_0_REG_ITEM_ID,
	SNS_SMGR_SENSOR_0_CAL_PRI_TYPE,
	SNS_SMGR_SENSOR_0_CAL_PRI_ID,
	SNS_SMGR_SENSOR_0_DEVICE_ID,
	(SNS_SMGR_DD_SELF_SCHED | SNS_SMGR_NO_SENSITIVITY), //SNS_SMGR_SENSOR_0_FLAGS,
	{SNS_DDF_SENSOR_ACCEL, SNS_DDF_SENSOR__NONE},
	SNS_SMGR_SENSOR_0_GPIO_FIRST,
	SNS_SMGR_SENSOR_0_GPIO_SECOND,
	SNS_SMGR_SENSOR_0_BUS_INSTANCE
   },
   {
    0,
    {0},
    (uint16_t)((SNS_SMGR_SENSOR_1_OFF_TO_IDLE/SNS_SMGR_USEC_PER_TICK)+1),
    (uint16_t)((SNS_SMGR_SENSOR_1_IDLE_TO_READY/SNS_SMGR_USEC_PER_TICK)+1),
    SNS_SMGR_ID_GYRO_V01, //SNS_SMGR_SENSOR_1_ENUM_CODE,
    SNS_SMGR_SENSOR_1_BUS_ADDRESS,
    SNS_SMGR_SENSOR_1_RANGE_TYPE,
    SNS_SMGR_SENSOR_1_SENSITIVITY_DEFAULT,
    0, //SNS_SMGR_SENSOR_1_REG_ITEM_TYPE,
    0, //SNS_SMGR_SENSOR_1_REG_ITEM_ID,
    0, //SNS_SMGR_SENSOR_1_CAL_PRI_TYPE,
    0, //SNS_SMGR_SENSOR_1_CAL_PRI_ID,
    SNS_SMGR_SENSOR_1_DEVICE_ID,
    (SNS_SMGR_DD_SELF_SCHED | SNS_SMGR_NO_SENSITIVITY), //SNS_SMGR_SENSOR_1_FLAGS,
    {SNS_DDF_SENSOR_GYRO, SNS_DDF_SENSOR__NONE},
    SNS_SMGR_SENSOR_1_GPIO_FIRST,
    SNS_SMGR_SENSOR_1_GPIO_SECOND,
    SNS_SMGR_SENSOR_1_BUS_INSTANCE
   },
   {
    0,
    {0},
    (uint16_t)((SNS_SMGR_SENSOR_2_OFF_TO_IDLE/SNS_SMGR_USEC_PER_TICK)+1),
    (uint16_t)((SNS_SMGR_SENSOR_2_IDLE_TO_READY/SNS_SMGR_USEC_PER_TICK)+1),
    SNS_SMGR_ID_MAG_V01, //SNS_SMGR_SENSOR_2_ENUM_CODE,
    SNS_SMGR_SENSOR_2_BUS_ADDRESS,
    SNS_SMGR_SENSOR_2_RANGE_TYPE,
    SNS_SMGR_SENSOR_2_SENSITIVITY_DEFAULT,
    0, //SNS_SMGR_SENSOR_2_REG_ITEM_TYPE,
    0, //SNS_SMGR_SENSOR_2_REG_ITEM_ID,
    0, //SNS_SMGR_SENSOR_2_CAL_PRI_TYPE,
    SNS_SMGR_SENSOR_2_CAL_PRI_ID,
    SNS_SMGR_SENSOR_2_DEVICE_ID,
    (SNS_SMGR_DD_SELF_SCHED | SNS_SMGR_NO_SENSITIVITY), //SNS_SMGR_SENSOR_2_FLAGS,
    {SNS_DDF_SENSOR_MAG, SNS_DDF_SENSOR__NONE},
    SNS_SMGR_SENSOR_2_GPIO_FIRST,
    SNS_SMGR_SENSOR_2_GPIO_SECOND,
    SNS_SMGR_SENSOR_2_BUS_INSTANCE
   },
   {
    0,
    {0},
    0,
    0,
    SNS_SMGR_ID_PRESSURE_V01,
    0, //SNS_SMGR_SENSOR_2_BUS_ADDRESS,
    0, //SNS_SMGR_SENSOR_2_RANGE_TYPE,
    0, //SNS_SMGR_SENSOR_2_SENSITIVITY_DEFAULT,
    0, //SNS_SMGR_SENSOR_2_REG_ITEM_TYPE,
    0, //SNS_SMGR_SENSOR_2_REG_ITEM_ID,
    0, //SNS_SMGR_SENSOR_2_CAL_PRI_TYPE,
    0, //SNS_SMGR_SENSOR_2_CAL_PRI_ID,
    0, //SNS_SMGR_SENSOR_2_DEVICE_ID,
    (SNS_SMGR_DD_SELF_SCHED), //SNS_SMGR_SENSOR_2_FLAGS,
    {SNS_DDF_SENSOR_PRESSURE, SNS_DDF_SENSOR__NONE},
    0, //SNS_SMGR_SENSOR_2_GPIO_FIRST,
    0, //SNS_SMGR_SENSOR_2_GPIO_SECOND,
    0, //SNS_SMGR_SENSOR_2_BUS_INSTANCE
   },
   {
     0,
     {0},
     0,
     0,
     SNS_SMGR_ID_HEART_RATE_V01,
     0, //SNS_SMGR_SENSOR_2_BUS_ADDRESS,
     0, //SNS_SMGR_SENSOR_2_RANGE_TYPE,
     0, //SNS_SMGR_SENSOR_2_SENSITIVITY_DEFAULT,
     0, //SNS_SMGR_SENSOR_2_REG_ITEM_TYPE,
     0, //SNS_SMGR_SENSOR_2_REG_ITEM_ID,
     0, //SNS_SMGR_SENSOR_2_CAL_PRI_TYPE,
     0, //SNS_SMGR_SENSOR_2_CAL_PRI_ID,
     0, //SNS_SMGR_SENSOR_2_DEVICE_ID,
     (SNS_SMGR_DD_SELF_SCHED), //SNS_SMGR_SENSOR_2_FLAGS,
     {SNS_DDF_SENSOR_HEART_RATE_RAW, SNS_DDF_SENSOR__NONE}, //{SNS_DDF_SENSOR_HEART_RATE, SNS_DDF_SENSOR_HEART_RATE_RAW},
     0, //SNS_SMGR_SENSOR_2_GPIO_FIRST,
     0, //SNS_SMGR_SENSOR_2_GPIO_SECOND,
     0, //SNS_SMGR_SENSOR_2_BUS_INSTANCE
    },
    {
     0,
     {0},
     0,
     0,
     SNS_SMGR_ID_PROX_LIGHT_V01,
     0, //SNS_SMGR_SENSOR_2_BUS_ADDRESS,
     0, //SNS_SMGR_SENSOR_2_RANGE_TYPE,
     0, //SNS_SMGR_SENSOR_2_SENSITIVITY_DEFAULT,
     0, //SNS_SMGR_SENSOR_2_REG_ITEM_TYPE,
     0, //SNS_SMGR_SENSOR_2_REG_ITEM_ID,
     0, //SNS_SMGR_SENSOR_2_CAL_PRI_TYPE,
     0, //SNS_SMGR_SENSOR_2_CAL_PRI_ID,
     0, //SNS_SMGR_SENSOR_2_DEVICE_ID,
     (SNS_SMGR_DD_SELF_SCHED), //SNS_SMGR_SENSOR_2_FLAGS,
     {SNS_DDF_SENSOR_PROXIMITY, SNS_DDF_SENSOR__NONE}, //{SNS_DDF_SENSOR_HEART_RATE, SNS_DDF_SENSOR_HEART_RATE_RAW},
     0, //SNS_SMGR_SENSOR_2_GPIO_FIRST,
     0, //SNS_SMGR_SENSOR_2_GPIO_SECOND,
     0, //SNS_SMGR_SENSOR_2_BUS_INSTANCE
    }
  };
#endif

void sns_uimg_utils_init(void)
{
  // Not much to do here, at the moment
  return;
}


void sns_hw_set_qup_clk(bool enable_flag){}
void sns_ddf_timer_dispatch(void){}
void sns_ddf_signal_dispatch(void){}

void sns_smgr_reboot_sensor(sns_smgr_ddf_sensor_s* ddf_sensor_ptr){}
void sns_smgr_sampling_cycle(void){}
void sns_smgr_handle_bigimage_signals(OS_FLAGS sig_flags){}
void sns_smgr_task(void* p_arg){}
sns_err_code_e sns_logpkt_commit(log_pkt_t log_pkt_type,
                                 void* log_pkt_ptr){}
sns_err_code_e sns_logpkt_malloc(log_pkt_t log_pkt_type,
                                 uint32_t pkt_size,
                                 void** log_pkt_ptr){}
void sns_smgr_update_total_sampling_freq
(
  uint16_t            in_freq_Hz,
  uint16_t            out_freq_Hz
){}
void sns_smgr_update_eff_rept_rate_est
(
  q16_t               max_rep_rate_Hz,
  q16_t               sum_rep_rate_Hz,
  sns_proc_type_e_v01 proc_type
)
{}
void sns_smgr_update_avgitems
(
   void
){}
void sns_smgr_update_bw_reqd
(
  void
){}
sns_ddf_status_e sns_smgr_set_attr(
  sns_smgr_sensor_s*       sensor_ptr,
  sns_ddf_sensor_e         sensor,
  sns_ddf_attribute_e      attrib,
  void*                    value)
{

}
sns_ddf_status_e sns_smgr_get_attr(
  sns_smgr_sensor_s*     sensor_ptr,
  sns_ddf_sensor_e       sensor,
  sns_ddf_attribute_e    attrib,
  void**                 value,
  uint32_t*              num_elems)
{

}

void sns_ddf_memhandler_free_ex(sns_ddf_memhandler_s* memhandler, sns_ddf_handle_t sensor_handle)
{

}
void smgr_get_data(sns_smgr_ddf_sensor_s* in_ddf_sensor_ptr)
{

}
sns_pm_err_code_e sns_pm_vote_img_mode( sns_pm_handle_t client_handle,
                                        sns_pm_img_mode_e mode)
{
  return SNS_PM_ERR_FAILED;
}
sns_pm_err_code_e sns_pm_client_init( sns_pm_handle_t *client_handle,
                                      suspend_cb_t callback,
                                      char* client_name,
                                      sns_pm_client_id_e client_id)
{
  return SNS_PM_ERR_FAILED;
}

void sns_pm_ap_wakeup_broadcast(void)
{

}
void sns_ddf_memhandler_init(sns_ddf_memhandler_s* memhandler)
{

}
void sns_profiling_log_latency_poll(
        sns_profiling_latency_s    latency,
        int32_t                    sensor_id)
{

}
uint8_t sns_debug_is_module_disabled(sns_debug_module_id_e module_id){return 0;}
bool sns_ddf_smgr_is_in_uimage(void){ return false;}
