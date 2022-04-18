#ifndef SVS_H
#define SVS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum
{
  CPU_SLOW2 = 0,
  CPU_SLOW, 
  CPU_FAST,
  CPU_NUM_MODES
} cpu_mode_id;

void cpu_init(void);

// Request that the SVS driver re-assess the RPM's workload and adjust the RPM
// speed accordingly.
//
// Typical use scenarios:
//    - The RPM is going into halt (not chip sleep!)
//        - In this case, the RPM speed may be reduced to allow system-wide SVS to occur.
//        - The RPM speed may even be reduced below the "normal" SVS speed if there is extra time.
//    - The RPM is coming out of halt or chip sleep
//        - In this case, the RPM speed may need to be increased to optimally process the incoming workload.
//    - The RPM receives new work (while running).
//        - In this case, the RPM speed may need to be increased to optimally process the incoming workload.
//
// Note: we do *not* call this function when we complete work.  In such a case,
// we *might* want to lower the RPM clock speed--but instead of doing that
// immediately, we instead churn through our remaining workload in order to get
// to sleep faster.  Stopping to "slow down" is going to burn more power than
// just finishing and getting to sleep.
bool cpu_update_speed(int change_speed);

// This updates to SVS2 when entering halt, updates to the mode prior to halt when exiting
void cpu_update_idle(bool entering_idle);

// Return the duration for switching SVS speed
unsigned cpu_get_switch_time(void);

// Return the current speed at which the RPM is running.
cpu_mode_id cpu_current_speed(void);

// Return the current frequency in kHz at which the RPM is running.
unsigned int cpu_get_freq(cpu_mode_id mode);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // SVS_H

