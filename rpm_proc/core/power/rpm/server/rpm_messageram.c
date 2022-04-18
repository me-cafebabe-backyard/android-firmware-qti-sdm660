#include <stdint.h>
#include <string.h>
#include "CoreVerify.h"
#include "err.h"
#include "rpm_messageram.h"
#include "railway.h"
#include "time_service.h"
#include "msmhwiobase.h"
#include "rpm_config.h"

#define RPM_MSG_RAM_EE_SIZE             0x1000  // 4K

#define RPM_MSG_RAM_RAIL_INFO_SIZE      0x400   // 1K
#define RPM_MSG_RAM_GLINK_HEADER_SIZE   0x100   // 256bytes
#define MESSAGING_V1                    0x31726576 //'ver1' in little endian

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

typedef struct
{
  unsigned mx_microvolts;
  unsigned cx_microvolts;
} message_ram_rail_info_s;

#define message_ram_rail_info (*((message_ram_rail_info_s*)(RPM_MSG_RAM_BASE + RPM_MSG_RAM_BASE_SIZE - (RPM_MSG_RAM_RAIL_INFO_SIZE + RPM_MSG_RAM_GLINK_HEADER_SIZE))))

//message ram master mapping
typedef struct
{
  message_ram_master_t master[VMPM_MAX];
} message_ram_s;

#define message_ram (*((message_ram_s*)RPM_MSG_RAM_BASE))

//data regarding message ram block allocation
static struct message_ram_data_s
{
  message_ram_master_data_t master_data[VMPM_MAX];
} message_ram_data;

uint64 rpm_master_sync_point = 0;

void * message_ram_malloc(smem_host_type master_id, uint32_t size)
{
  char * message_ram_address = NULL;
  uint8_t master_num;
  message_ram_master_t *space;
  message_ram_master_data_t *used;

  switch(master_id)
  {
    case SMEM_APPS:
      master_num = VMPM_APPS;
      break;
    case SMEM_MODEM:
      master_num = VMPM_MODEM;
      break;
    case SMEM_Q6:
      master_num = VMPM_ADSP;
      break;
    case SMEM_RIVA:
      master_num = VMPM_WCONNECT;
      break;
    case SMEM_TZ:
      master_num = VMPM_TZ;
      break;
    case SMEM_SSC:
      master_num = VMPM_SSC;
      break;
    case SMEM_SPSS:
      master_num = VMPM_SPSS;
      break;
    case SMEM_CDSP:
      master_num = VMPM_CDSP;
      break;

    default:
      /* invalid input */
      CORE_VERIFY(0);
  }

  space = &message_ram.master[master_num];
  used = &message_ram_data.master_data[master_num];

  // 4-byte align the size
  size = (size + 3) & ~3;

  if(size <= (sizeof(space->small_alloc_space) - used->small_alloc_used))
  {
    // we can allocate from small size
    message_ram_address = ((char *)space->small_alloc_space) + used->small_alloc_used;
    used->small_alloc_used += size;
    //memset((void *)message_ram_address, 0, size);
	int *tmp = (int*)message_ram_address;
    for(int i = 0; i < size/4; ++i)
      tmp[i] = 0;
    return message_ram_address;
  }
  else if(size <= (sizeof(space->large_alloc_space) - used->large_alloc_used))
  {
    message_ram_address = ((char *)space->large_alloc_space) + used->large_alloc_used;    	  
    used->large_alloc_used += size;
    //memset((void *)message_ram_address, 0, size);
	int *tmp = (int*)message_ram_address;
    for(int i = 0; i < size/4; ++i)
      tmp[i] = 0;
    return message_ram_address;
  }

  ERR_FATAL("Out of message RAM for master %d; cannot allocate %d bytes.", master_id, size, 0);
}

vmpm_data_t *message_ram_vmpm(vmpm_masters master)
{
  CORE_VERIFY(master < ARRAY_SIZE(message_ram.master));
  return &message_ram.master[master].vmpm;
}

rpm_master_stats_t *
message_ram_master_stats (unsigned ee)
{
  CORE_VERIFY(ee < ARRAY_SIZE(message_ram.master));
  return &message_ram.master[ee].master_stats;
}

void update_message_ram_rail_info (const railway_settings *settings, void* cookie)
{
  int rail_num = (int)cookie;

  if (rail_num == 0)
    message_ram_rail_info.mx_microvolts = settings->microvolts;
  else if (rail_num == 1)
    message_ram_rail_info.cx_microvolts = settings->microvolts;
}

/*
 * message_ram_update_master_stats_periodic()
 * This has been called in rpm_halt_enter, rpm_halt_exit,
 * deep_sleep_exit paths to update the master stats periodically  
 */
void message_ram_update_master_stats_periodic()
{ 
  uint64 now = time_service_now();  
  rpm_spm_status_type subsystem_status;
  
  for(uint32 i = 0 ; i<RPM_EE_COUNT ; i++)
  {
    rpm_master_stats_t *stats	=	message_ram_master_stats(i); 
	
	CORE_VERIFY(stats);
	subsystem_status = rpm->ees[i].subsystem_status;
	
	// update the accumulation duration periodically until subsystem in in sleep state
	if((stats->xo_last_entered_at > stats->xo_last_exited_at) && 
	   (subsystem_status ==  SPM_SLEEPING))
    {
	    stats->xo_accumulated_duration += (now - rpm_master_sync_point);
	}
   }
   //update the sync point to current time stamp for updating stats for next time
   rpm_master_sync_point	=	now;   
	
}

void message_ram_update_master_xo_stats(unsigned ee, int vote)
{
  uint64 now = time_service_now();
  rpm_master_stats_t *stats = message_ram_master_stats(ee);

  if(vote)
  {
      uint64 last_entered_at = stats->xo_last_entered_at;

      if(last_entered_at)
      {
          stats->xo_last_exited_at        = now;
      }
  }
  else
  {
      stats->xo_last_entered_at = now;
      stats->xo_count++;
  }
}

unsigned read_message_ram_rail_info(unsigned int index)
{
  unsigned microvolts = 0;
  if (index == 0)
    microvolts =  message_ram_rail_info.mx_microvolts;
  else if (index == 1)
    microvolts =  message_ram_rail_info.cx_microvolts;
  return microvolts;
}

void message_ram_init(void)
{
   message_ram_master_t *space;
   unsigned num_rails = 2;

   for(int i=0; i<num_rails; i++)
   {
     railway_set_callback(i, RAILWAY_POSTCHANGE_CB, update_message_ram_rail_info, (void*)i);
   }

   for(vmpm_masters master_num = VMPM_APPS; master_num < VMPM_MAX; master_num++)
   {
     space = &message_ram.master[master_num];
     //memset (&(space->vmpm), 0, sizeof(vmpm_data_t));
	 int *tmp = (int*)(&space->vmpm);
      for(int i = 0; i < sizeof(vmpm_data_t) / 4; ++i)
        tmp[i] = 0;
     //memset (&(space->master_stats), 0, sizeof(rpm_master_stats_t));
	 tmp = (int*)(&space->master_stats);
      for(int i =0; i < sizeof(rpm_master_stats_t)/4;++i)
        tmp[i] = 0;
     if(master_num == VMPM_APPS)
     {
       space->master_stats.reserved[0] = MESSAGING_V1;         
     }
   }
}

#define member_sizeof(type, field) (sizeof(((type *)0)->field))
#define STATIC_CORE_VERIFY(tag, cond) extern int COMPILE_TIME_ASSERT__##tag[(cond)?1:-1]
STATIC_CORE_VERIFY(small_alloc_is_multiple_of_4, member_sizeof(message_ram_master_t, small_alloc_space) % 4 == 0);
STATIC_CORE_VERIFY(vmpm_is_multiple_of_4,        member_sizeof(message_ram_master_t, vmpm) % 4 == 0);
STATIC_CORE_VERIFY(region_kB_per_master, sizeof(message_ram_master_t) == RPM_MSG_RAM_EE_SIZE);

