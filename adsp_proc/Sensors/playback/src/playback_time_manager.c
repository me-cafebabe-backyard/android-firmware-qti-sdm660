#include <stdbool.h>
#include "playback_time_manager.h"
#include "sns_sam_cb.h"

/*
 * TODO:
 * Right now, this time manager supports only one instance of a timer.
 * However, the APIs are in place to extend this to support one timer instance
 * per algorithm instance.
 */

static uint64_t current_timestamp;
static sns_em_tmr_s *g_timer_obj = NULL;

void sns_tm_init()
{
  current_timestamp = 0;
  g_timer_obj = (sns_em_tmr_s *) SNS_OS_MALLOC(SNS_SAM_DBG_MOD, sizeof(sns_em_tmr_s));
  g_timer_obj->timer_arg = NULL;
  g_timer_obj->timer_registered = false;
  g_timer_obj->expiry_time = 0;
  g_timer_obj->timer_cb = NULL;
}

void sns_tm_update_current_timestamp(uint64_t timestamp)
{
  if((NULL != g_timer_obj) && (g_timer_obj->timer_registered))
  {
    if(timestamp >= g_timer_obj->expiry_time)
    {
      current_timestamp = g_timer_obj->expiry_time;
      g_timer_obj->timer_cb(g_timer_obj->timer_arg);
      sns_tm_cancel_timer(g_timer_obj);
    }
  }

  current_timestamp = timestamp;
}

uint64_t sns_tm_get_current_timestamp()
{
  return current_timestamp;
}

sns_em_tmr_s *sns_tm_create_timer(void (*timer_cb)(void *), void *timer_cb_arg)
{
  if(NULL != g_timer_obj)
  {
    g_timer_obj->timer_cb = timer_cb;
    g_timer_obj->timer_arg = timer_cb_arg;
  }

  return g_timer_obj;
}

sns_err_code_e sns_tm_register_timer(sns_em_tmr_s *algo_timer_obj, uint64_t timeout_ticks)
{
  if((NULL != g_timer_obj) && (algo_timer_obj->timer_arg == g_timer_obj->timer_arg))
  {
    g_timer_obj->timer_registered = true;
    g_timer_obj->expiry_time = current_timestamp + timeout_ticks;
    return SNS_SUCCESS;
  }

  return SNS_ERR_FAILED;
}

sns_err_code_e sns_tm_cancel_timer(sns_em_tmr_s *algo_timer_obj)
{
  if((NULL != g_timer_obj) && (algo_timer_obj->timer_arg == g_timer_obj->timer_arg))
  {
    g_timer_obj->timer_registered = false;
    g_timer_obj->expiry_time = 0;
    return SNS_SUCCESS;
  }

  return SNS_ERR_FAILED;
}
