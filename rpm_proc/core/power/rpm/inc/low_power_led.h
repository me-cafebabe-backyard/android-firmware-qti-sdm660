#ifndef RPM_LOW_POWER_LED_H
#define RPM_LOW_POWER_LED_H

#include "comdef.h"

#define LOW_POWER_LED_REQ_ENAB      0x62616E65 //enab
#define LOW_POWER_LED_REQ_COLOR_MAP 0x70616D63 //cmap
#define LOW_POWER_LED_REQ_BRIGHTNESS 0x67697262 //brig

#define LOW_POWER_LED_POSSIBLE_STATES 16 //4 masters means 16 possible states

/* The internal representation of the low power LED */
typedef struct
{
  /*
  Construct index via awake/sleep state of masters (sleeping = 0, awake = 1)
    Bit 0 = APSS
    Bit 1 = MPSS
    Bit 2 = LPASS
    Bit 3 = WCNSS
  Value is a bitmask of colors that should be on
  */
  uint8 color_map[LOW_POWER_LED_POSSIBLE_STATES];
  uint32 enabled;
} low_power_led_inrep;

// Query for the enabled status of low power led functionality
uint32 rpm_low_power_led_enabled(void);

void rpm_low_power_led_toggle_led(void);

void low_power_led_init(void);

#endif //#ifndef RPM_LOW_POWER_LED_H

