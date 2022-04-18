#ifndef FAST_PLAYBACK_TIME_MANAGER_H
#define FAST_PLAYBACK_TIME_MANAGER_H

#ifdef sns_em_tmr_s
#undef sns_em_tmr_s
#endif

#include "sns_sam.h"

typedef void (*sns_timer_cb)(void *);

struct sns_em_tmr_s
{
  bool timer_registered;
  uint64_t expiry_time;
  sns_timer_cb timer_cb;
  void *timer_arg;
};
typedef struct sns_em_tmr_s sns_em_tmr_s;

void sns_tm_init();
void sns_tm_update_current_timestamp(uint64_t timestamp);
uint64_t sns_tm_get_current_timestamp();
sns_em_tmr_s *sns_tm_create_timer(void (*timer_cb)(void *), void *timer_cb_arg);
sns_err_code_e sns_tm_register_timer(sns_em_tmr_s *algo_timer_obj, uint64_t timeout_ticks);
sns_err_code_e sns_tm_cancel_timer(sns_em_tmr_s *algo_timer_obj);

#endif
