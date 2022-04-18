#ifndef VMPM_TARGET_H
#define VMPM_TARGET_H

#include "comdef.h"
#include "HALmpmint.h"
#include "gpio.h"
#include "rpm_messageram.h"

#define NUM_RPM_WAKEUP_INTS 2

/* structure describing a master */
typedef struct
{
  gpio_target_id_t target_id;
  void (*pfnSendWakeup)(void);
  void (*pfnSendInterrupt)(void);
  unsigned vmpm_interrupt;
} vmpm_master_info_type;

typedef struct
{
  unsigned mpm_interrupt_index;
  unsigned rpm_interrupt_index;
} mpm_rpm_interrupt_type;

/* defined in mpm\src\<MSM_ID>\vmpm_target.c */
extern const vmpm_master_info_type vmpm_masters_info[VMPM_NUM_MASTERS];
extern mpm_rpm_interrupt_type rpm_wakeup_ints[NUM_RPM_WAKEUP_INTS];

#endif /* VMPM_TARGET_H */

