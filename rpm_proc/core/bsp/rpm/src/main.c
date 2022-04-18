/*=============================================================================

                                MAIN

GENERAL DESCRIPTION
  This file contains the initial operations for the RPM.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2009-2015 by Qualcomm Technologies, Inc.  All Rights Reserved.

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/src/main.c#5 $
  $Author: pwbldsvc $
  $DateTime: 2018/04/11 22:49:28 $
=============================================================================*/

#include <assert.h>
#include "cortex-m3.h"
#include "comdef.h"
#include "dog.h"
#include "time_service.h"
#include "image_layout.h"

#ifdef QCS405_STUBS
#include "gpio.h"
#include "gpio_debug.h"
#include "ClockDefs.h"
#include "kvp.h"
#include "DALStdErr.h"
#include "PlatformInfo.h"
#include "HALhwio.h"
#include "coredump.h"
#include "swevent.h"
#include "apcs_hang_status_hwio.h"
#endif

extern void rpm_target_init(void);
extern void sched_run(void);
extern uint64_t sched_get_next_start(void);
extern unsigned int npa_num_pending_events(void);
extern void npa_process_event(void);
extern uint32 sleep_perform_lpm(void);


int main(void)
{
  rpm_target_init();

  #define ever ;;
  for(ever)
  {
    assert(!intlock_nest_level);
    do
    {
      pmic_wdog_pet(0); //pet the pmic wdog as need, configure if needed.
      sched_run();
      assert(!intlock_nest_level);

      if(npa_num_pending_events() > 0)
      {
        npa_process_event();
        assert(!intlock_nest_level);
      }
      else
        break; // nothing to do--try to sleep
    } while(1);

    assert(!intlock_nest_level);
    INTLOCK();

    rpm_update_stack_usage();

    if(!npa_num_pending_events() && (sched_get_next_start() >= time_service_now()))
      sleep_perform_lpm();

    INTFREE();
    assert(!intlock_nest_level);
  }
}
#ifdef QCS405_STUBS


//GPIO stubs
void gpio_toggle_init() { return;}
bool gpio_is_dir_conn_intr_enabled(uint32 gpio_num) {return TRUE;}
bool gpio_is_summary_intr(gpio_target_id_t target, uint32 gpio_num) {return TRUE;}
bool gpio_is_dir_conn_intr(gpio_target_id_t target, uint32 gpio_num) {return TRUE;}
void gpio_test_low( gpio_debug_application gpio_application, gpio_debug_transition gpio_transition ) {return;}
void gpio_test_high( gpio_debug_application gpio_application, gpio_debug_transition gpio_transition ) {return;}
unsigned gpio_lookup_gpio_cfg_addr(unsigned gpio_num) {return 0;}
unsigned gpio_lookup_gpio_in_out_addr(unsigned gpio_num) {return 0;}
void gpio_configure_gpio(uint32 gpio_num, uint32 config) {return;}
void gpio_write_gpio_out(uint32 gpio_num, uint32 value) {return;}
 
//MPM stubs 
void mpm_init (void) {return;}
void vmpm_init (void) {return;}
void mpm_init_xtal(void) {return;}
uint64_t mpm_deep_sleep_enter_latency() {return 0;}
uint64_t mpm_deep_sleep_exit_latency() {return 0;}
void vmpm_prepare_for_sleep(void) {return;}
void mpm_sw_done( uint64_t sleep_duration) {return;}
void vmpm_propogate_interrupts(void) {return;}
void mpm_teardown_sleep (void) {return;}
void mpm_set_vmin_voltages ( uint32_t mx_off_uv, uint32_t mx_on_uv, uint32_t cx_off_uv, uint32_t cx_on_uv) {return;}
void mpm_config_freeze_ios(bool enable) {return;}
void mpm_setup_chip_sleep() {return;}
 
//ICB stubs
void icb_init(void) {return;} 
 
//PlatformInfo stubs
void PlatformInfo_Init( void ) {return;}
PlatformInfoPlatformType PlatformInfo_GetPlatform (void) { return PLATFORMINFO_TYPE_UNKNOWN;}
 
//Exception ISR stubs
void detect_apps_hang(void) {}
 #endif
 
 