/*============================================================================

FILE:      err.h

DESCRIPTION: Function declarations

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2010 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/inc/dog.h#1 $
$Date: 2016/11/03 $

============================================================================*/

#ifndef DOG_H
#define DOG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

/* Includes for PMIC wdog */
#include "pm_pon.h"

/* Includes for PMIC RTC */
#include "pm_rtc.h"

#define DOG_STATS_ENTRIES 4
typedef enum
{
  DOG_KICK,
  PMIC_DOG_KICK,
  PMIC_DOG_CFG,
  PMIC_DOG_DECFG,
} dog_event_type;

typedef struct 
{
  dog_event_type dog_event;
  void          *dog_event_source;
  uint64_t       timestamp;
} dog_stats_entry_type;

typedef struct
{
  dog_stats_entry_type entries[DOG_STATS_ENTRIES];
  unsigned             index;
} dog_stats_type;

/* Start the watchdog. */
void dog_init(void);

void dog_enable(unsigned enable);

/* Reset the watchdog.  Should be done periodically by SW. */
void dog_kick(void);

void dog_set_bark_time(unsigned bark_time);
void dog_set_bite_time(unsigned bite_time);

/* PMIC WDOG */

#define PMIC_WDOG_MAX_SLEEP_TIME 0x112A8800 // 15 sec

void pmic_wdog_pet(bool unconditional);

/* PMIC RTC Logging */

void pmic_rtc_init(void);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif /* DOG_H */

