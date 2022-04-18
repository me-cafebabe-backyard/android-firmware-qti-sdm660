/*==============================================================================

FILE:      rpm_messageram.h

      Copyright (c) 2015 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$DateTime: 2020/02/10 01:57:30 $
$Header: //components/rel/core.qdsp6/1.0.c2/power/rpm/inc/8998/rpm_messageram.h#1 $
$Change: 22511909 $

==============================================================================*/

#ifndef RPM_MESSAGERAM_H
#define RPM_MESSAGERAM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include "msmhwiobase.h"

/*==============================================================================
**
** Macros
**
**==============================================================================
*/

#define RPM_MSG_RAM_BASE    RPM_SS_MSG_RAM_START_ADDRESS_BASE
#define RPM_MSG_RAM_SIZE    RPM_SS_MSG_RAM_START_ADDRESS_BASE_SIZE

#define RPM_MSG_RAM_DATA    ((message_ram_s*)RPM_MSG_RAM_BASE)


/*==============================================================================
**
** Type Definitions
**
**==============================================================================
*/

typedef enum
{
    VMPM_APPS        = 0,
    VMPM_MODEM       = 1,
    VMPM_ADSP        = 2,
    VMPM_WCONNECT    = 3,
    VMPM_SSC         = VMPM_WCONNECT,
    VMPM_NUM_MASTERS = 4, /* APPS, MODEM, ADSP, SSC (SPSS does not configure GPIOs as wakeup interrupt to MPM) */
    VMPM_TZ          = 4,
    VMPM_SPSS        = 5,
    VMPM_MAX
} vmpm_masters;

typedef struct
{
    uint64_t wakeup_time;        // QTimer count of planned wakeup.  '0' does *not* mean infinite, it means "wakeup immediately."
    uint32_t vmpm_enable[3];     // '1' = enabled, '0' = don't care (might still be enabled by someone else)
    uint32_t vmpm_detect_lower[3]; // requires both ctl bits and polarity to determine trigger type
    uint32_t vmpm_detect_higher[3]; // requires both ctl bits and polarity to determine trigger type
    uint32_t vmpm_polarity[3];   // '0' = low/falling, '1' = high/rising
    uint32_t vmpm_status[3];     // Bits will be set to '1' for each interrupt pending when deep sleep is exited.
    uint32_t reserved;           // reserved field to maintain alignment
} vmpm_data_t;

typedef struct
{
    uint32_t active_cores; // Bitmask of active cores - core 0 = bit 0, core 1 = bit 1 ..
    uint32_t num_shutdowns; // number of times all cores have power collapsed
    uint64_t shutdown_req; // timestamp of last shutdown of all cores
    uint64_t wakeup_ind; // timestamp of last master wakeup ind
    uint64_t bringup_req; // timestamp of last bring up req
    uint64_t bringup_ack; // timestamp of last bring up ack
    uint32_t wakeup_reason; // 0 = rude wakeup, 1 = scheduled wakeup
    uint32_t last_sleep_transition_duration; // time taken (in ticks) for the last W->S transition
    uint32_t last_wake_transition_duration; // time taken (in ticks) for the last S->W transition
    uint32_t xo_count;                // Shows how many times the SS has power collapsed and voted for XO shutdown
    uint64_t xo_last_entered_at;      // Last timestamp the SS power collapsed and voted for XO shutdown
    uint64_t xo_last_exited_at;       // Last timestamp the SS exited PC( with vote for XO shutdown) and woken up by RPM
    uint64_t xo_accumulated_duration; // Shows how long the SS has been in a sleep mode since it has booted 
    uint32_t reserved[6];
} rpm_master_stats_t;

//per master message ram memory mapping
typedef struct
{
    uint32_t            small_alloc_space[84];
    rpm_master_stats_t  master_stats;
    vmpm_data_t         vmpm;
    uint32_t            reserved[384];
    uint32_t            large_alloc_space[512];
} message_ram_master_t;

//message ram master mapping
typedef struct
{
    message_ram_master_t master[VMPM_MAX];
} message_ram_s;


/*==============================================================================
**
** APIs
**
**==============================================================================
*/

inline vmpm_data_t* rpm_message_ram_vmpm(vmpm_masters master)
{
    return &(RPM_MSG_RAM_DATA->master[master].vmpm);
}

inline rpm_master_stats_t* rpm_message_ram_master_stats(vmpm_masters master)
{
    return &(RPM_MSG_RAM_DATA->master[master].master_stats);
}

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // RPM_MESSAGERAM_H

