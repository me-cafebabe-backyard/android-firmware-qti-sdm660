/*============================================================================
  @file sns_memmgr.c

  @brief
  Implements SNS memory manager interfaces.

  Copyright (c) 2010-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ===========================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stringl.h"
#include "sns_common.h"
#include "sns_debug_str.h"
#include "sns_memheap.h"
#include "sns_memheap_lite.h"
#include "memheap.h"
#include "sns_memmgr.h"
#include "sns_init.h"
#include "sns_queue.h"
#include "sns_uimg_utils.h"

/*============================================================================
  Type Declarations
  ===========================================================================*/

/** An entry in the queue of memory blocks that need to be freed before entering
*  uImage
*/
typedef struct
{
  sns_q_link_s q_link;
  intptr_t  memPtr;
} sns_memmgr_spillover_q_item;

/*============================================================================
  Global Data Definitions
  ===========================================================================*/

/** Queue of memory blocks that need to be freed before entering uImage */
sns_q_s sns_memmgr_spillover_q;
OS_EVENT *sns_memmgr_spillover_q_mutex;
static OS_EVENT *sns_memmgr_lowmem_cb_mutex;

/* Sensors uImage heap. All uImage dynamic allocations are done from here */
SNS_MEMMGR_UIMAGE_DATA uint8 sns_uheap_mem[SNS_UIMAGE_HEAP_SIZE];
/* Data structures used to maintain the heap */
SNS_MEMMGR_UIMAGE_DATA sns_mem_heap_type sns_uheap;
SNS_MEMMGR_UIMAGE_DATA mem_magic_number_struct sns_uheap_magic;

SNS_MEMMGR_UIMAGE_DATA uint32 sns_uheap_magic_num[SNS_MAX_HEAP_INIT] =
  {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
SNS_MEMMGR_UIMAGE_DATA uint16 sns_uheap_magic_num_idx_array[SNS_MAX_HEAP_INIT] = {0,1,2,3,4};
SNS_MEMMGR_UIMAGE_DATA uint16_t sns_uheap_magic_num_index = 0;

sns_memmgr_lowmem_cb_s sns_default_heap_lowmem_cb;

/*============================================================================
  External Variable Declarations
  ===========================================================================*/

extern mem_heap_type sns_def_heap_state;
extern mem_heap_totals_type sns_def_heap_total;

//External defined in sensors.lcs.template file
extern uint32_t __sensors_island_start;
extern uint32_t __sensors_island_end;

/*============================================================================
  Static function definitions
  ===========================================================================*/

/*===========================================================================
    Initializes the heap used for uImage dynamic memory operations
  ===========================================================================*/
STATIC void sns_uheap_init(void)
{
#ifdef SNS_USES_ISLAND
  int ret_val;

  sns_uheap_magic.magic_num_index_array = sns_uheap_magic_num_idx_array;
  sns_uheap_magic.magic_num             = sns_uheap_magic_num;
  sns_uheap_magic.magic_num_index       = 0;

  ret_val =  sns_mem_init_heap( &sns_uheap,
    &sns_uheap_magic,
    sns_uheap_mem,
    sizeof(sns_uheap_mem));

  MSG_3(MSG_SSID_SNS, DBG_MED_PRIO,
    "Initialize micro Heap of size %d bytes @ %lu ret_val %de",
    sizeof(sns_uheap_mem), &sns_uheap, ret_val);
  /* Note that the failure of uheap allocation is not catastrophic.
     The system should still continue to run using the regular heap memory
     This function thus does not return an error code.
  */
#endif /* SNS_USES_ISLAND */
}

STATIC void sns_uheap_destroy(void)
{
#ifdef SNS_USES_ISLAND
  int ret_val;
  ret_val = sns_mem_deinit_heap(&sns_uheap, &sns_uheap_magic);
  MSG_2(MSG_SSID_SNS, DBG_MED_PRIO,
    "Destroyed micro Heap  @ %lu ret_val %de",
    &sns_uheap, ret_val);
#endif /* SNS_USES_ISLAND */
}

/*=====================================================================
  EXTERNAL FUNCTIONS
=======================================================================*/

sns_err_code_e sns_heap_init(void)
{
  sns_err_code_e result;
  uint8_t sns_os_err, i;

  /* Create default heap for Sensors */
  result = sns_heap_create();
  if ( result != SNS_SUCCESS ) {
    MSG_1(MSG_SSID_SNS, DBG_ERROR_PRIO,
              "Failed to initialize default heap!! Error %d\n", result);
    return SNS_ERR_FAILED;
  }

  /* Initialize the micro Heap */
  sns_uheap_init();
  sns_q_init(&sns_memmgr_spillover_q);
  sns_memmgr_spillover_q_mutex = sns_os_mutex_create(SNS_MEMMGR_DSPS_MUTEX, &sns_os_err);
  sns_memmgr_lowmem_cb_mutex = sns_os_mutex_create(SNS_MEMMGR_DSPS_MUTEX, &sns_os_err);

  /* Initialize low_mem callback structure for default heap */
  sns_default_heap_lowmem_cb.num_clients = 0;
  for( i = 0; i < SNS_MAX_NUM_MEMMGR_CLIENTS; i++ )
  {
    sns_default_heap_lowmem_cb.cb_func[i] = NULL;
  }

  return SNS_SUCCESS;
}

sns_err_code_e sns_heap_deinit(void)
{
  sns_uheap_destroy();
  sns_heap_destroy();

  return SNS_SUCCESS;
}

sns_err_code_e
sns_memmgr_init( void )
{
  sns_init_done();
  return SNS_SUCCESS;
}

sns_err_code_e
sns_memmgr_deinit( void )
{
  return SNS_SUCCESS;
}

sns_err_code_e
sns_memmgr_lowmem_cb_register( sns_memmgr_lowmem_cb_t cb )
{
  uint8_t os_err;
  sns_err_code_e err = SNS_ERR_NOTALLOWED;
  sns_os_mutex_pend(sns_memmgr_lowmem_cb_mutex, 0, &os_err);
  if( sns_default_heap_lowmem_cb.num_clients < SNS_MAX_NUM_MEMMGR_CLIENTS )
  {
    sns_default_heap_lowmem_cb.cb_func[sns_default_heap_lowmem_cb.num_clients] = cb;
    sns_default_heap_lowmem_cb.num_clients++;
    err = SNS_SUCCESS;
  }
  sns_os_mutex_post(sns_memmgr_lowmem_cb_mutex);
  return err;
}

uint32_t
sns_memmgr_default_heap_usage( void )
{
  mem_heap_get_totals(&sns_def_heap_state, &sns_def_heap_total);
  return (sns_def_heap_total.used_bytes + sns_def_heap_total.wasted_bytes + sns_def_heap_total.header_bytes);
}

static intptr_t sns_memmgr_find_spillover_buff( sns_q_s* memQ, intptr_t memPtr )
{
  sns_memmgr_spillover_q_item * itemPtr;
  itemPtr = (sns_memmgr_spillover_q_item *)sns_q_check(memQ);
  while(itemPtr != NULL)
  {
    if (itemPtr->memPtr == memPtr)
    {
      return ((intptr_t)itemPtr);
    }
    itemPtr = (sns_memmgr_spillover_q_item *)sns_q_next(memQ, &itemPtr->q_link);
  }
  return ((intptr_t)NULL);
}

void sns_memmgr_free_spillover_buffer(void * ptr)
{
  uint8_t os_err;
  sns_heap_free(ptr);
  sns_os_mutex_pend(sns_memmgr_spillover_q_mutex, 0, &os_err);
  if(0 < sns_q_cnt(&sns_memmgr_spillover_q))
  {
    sns_memmgr_spillover_q_item *item_ptr = (sns_memmgr_spillover_q_item *)sns_memmgr_find_spillover_buff(
      &sns_memmgr_spillover_q, (intptr_t)ptr);
    if(item_ptr != NULL)
    {
      sns_q_delete(&item_ptr->q_link);
      SNS_OS_FREE(item_ptr);

      if(0 == sns_q_cnt(&sns_memmgr_spillover_q))
      {
        sns_utils_remove_uimage_hold(SNS_UIMG_MEMGR);
      }
    }
  }
  sns_os_mutex_post(sns_memmgr_spillover_q_mutex);
}

void sns_memmgr_add_to_spillover_list(void *memPtr)
{
  uint8_t os_err;
  sns_memmgr_spillover_q_item *item_ptr = (sns_memmgr_spillover_q_item *)
  SNS_OS_MALLOC(0, sizeof(sns_memmgr_spillover_q_item));
  SNS_ASSERT(NULL != item_ptr);
  item_ptr->memPtr = (intptr_t)memPtr;
  sns_q_link(item_ptr, &item_ptr->q_link);
  sns_os_mutex_pend(sns_memmgr_spillover_q_mutex, 0, &os_err);
  sns_q_put(&sns_memmgr_spillover_q, &item_ptr->q_link);
  sns_utils_place_uimge_hold(SNS_UIMG_MEMGR);
  sns_os_mutex_post(sns_memmgr_spillover_q_mutex);
}

void* SNS_OS_MALLOC(uint8_t module, uint32_t size)
{
  void *buffer = NULL;
  static uint32_t counter = 0;
  uint32_t i, heap_usage;
  //TODO: add the below callback mechanism back to address the memory capacity issue in stress testcases

  /* the checkCounter will be dynamically changing depending the state of memory usage */
  static uint32_t checkCounter = SNS_HEAP_CHECK_COUNTER;

  /* check if curre_heap usage is beyond the low memory threshold. If it is, call callback function
   * to address the state before really running out of memory */
  if( counter > checkCounter )
  {
    heap_usage = sns_memmgr_default_heap_usage();
    if( heap_usage > SNS_DEFAULT_HEAP_LOW_MEM_THRESH )
    {
      UMSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO,
             "def heap calling callback function - heap usage %d, largest_free %d, checkCounter %d,",
             (uint32_t)heap_usage,
             (uint32_t)sns_def_heap_state.largest_free_block,
             checkCounter );
      for( i = 0; i < sns_default_heap_lowmem_cb.num_clients; i++ )
      {
        if(NULL != sns_default_heap_lowmem_cb.cb_func[i])
        {
          UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO,
                "default heap calling callback function i=%d", i );
          (*sns_default_heap_lowmem_cb.cb_func[i])();
        }
      }
     }
     else if( heap_usage > SNS_DEFAULT_HEAP_MEDIUM_MEM_THRESH )
     {
       checkCounter = SNS_HEAP_CHECK_COUNTER >> 1;
     }
     else
     {
       checkCounter = SNS_HEAP_CHECK_COUNTER;
     }
    counter = 0;
  }

  buffer = sns_heap_malloc(size);
  if (buffer != NULL)
  {
    SNS_OS_MEMSET(buffer, 0, size);
  }
  else
  {
    UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO, "SNS_OS_MALLOC failed - size %d",size);
  }
  return buffer;
}

STATIC SNS_MEMMGR_UIMAGE_CODE void* sns_memmgr_int_u_malloc(uint8_t module, uint32_t size, uint32_t calldepth)
{
  void *buffer = NULL;
  buffer = sns_mem_malloc(&sns_uheap, &sns_uheap_magic, size, calldepth + 1);
  if (buffer != NULL)
  {
    SNS_OS_MEMSET(buffer, 0, size);
  }

  return buffer;
}

SNS_MEMMGR_UIMAGE_CODE void* SNS_OS_U_MALLOC(uint8_t module, uint32_t size)
{
  return sns_memmgr_int_u_malloc(module, size, 1);
}

SNS_MEMMGR_UIMAGE_CODE void SNS_OS_FREE(void *ptr)
{
  if (NULL == ptr)
  {
    // Do nothing
  }
  else if (SNS_OS_IS_UIMG_ADDR(ptr))
  {
    sns_mem_free(&sns_uheap, &sns_uheap_magic, ptr);
  }
  else
  {
    sns_memmgr_free_spillover_buffer(ptr);
  }
}

SNS_MEMMGR_UIMAGE_CODE void* sns_memmgr_int_any_malloc(uint8_t module, uint32_t size, uint32_t calldepth)
{
  /* the checkCounter will be dynamically changing depending the state of memory usage */
  static uint32_t checkCounter = SNS_HEAP_CHECK_COUNTER;
  void *buffer = NULL;
  static uint32_t counter = 0;
  uint32_t i, heap_usage;

  buffer = sns_memmgr_int_u_malloc(module, size, 1 + calldepth);

  //TODO: add the below callback mechanism back to address the memory capacity issue in stress testcases

  if (NULL == buffer)
  {
    sns_utils_place_uimge_hold(SNS_UIMG_MEMGR);

    /* check if curre_heap usage is beyond the low memory threshold. If it is, call callback function
     * to address the state before really running out of memory */

    if( counter > checkCounter )
    {
      heap_usage = sns_memmgr_default_heap_usage();
      if( heap_usage > SNS_DEFAULT_HEAP_LOW_MEM_THRESH )
      {
        UMSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO,
               "def heap calling callback function - heap usage %d, largest_free %d, checkCounter %d,",
               (uint32_t)heap_usage,
               (uint32_t)sns_def_heap_state.largest_free_block,
               checkCounter );
        for( i = 0; i < sns_default_heap_lowmem_cb.num_clients; i++ )
        {
          if(NULL != sns_default_heap_lowmem_cb.cb_func[i])
          {
            UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO,
                  "default heap calling callback function i=%d", i );
            (*sns_default_heap_lowmem_cb.cb_func[i])();
          }
        }
       }
       else if( heap_usage > SNS_DEFAULT_HEAP_MEDIUM_MEM_THRESH )
       {
         checkCounter = SNS_HEAP_CHECK_COUNTER >> 1;
       }
       else
       {
         checkCounter = SNS_HEAP_CHECK_COUNTER;
       }
      counter = 0;
    }

    buffer = sns_heap_malloc(size);
    sns_memmgr_add_to_spillover_list(buffer);
  }

  if (buffer != NULL)
  {
    SNS_OS_MEMSET(buffer, 0, size);
  }
  else
  {
    UMSG_1(MSG_SSID_SNS, DBG_HIGH_PRIO, "malloc failed - size %d",size);
  }

  return buffer;
}

SNS_MEMMGR_UIMAGE_CODE void* SNS_OS_ANY_MALLOC(uint8_t module, uint32_t size)
{
  return sns_memmgr_int_any_malloc(module, size, 1);
}

SNS_MEMMGR_UIMAGE_CODE void* SNS_OS_MEMCOPY(void *dest, const void *source, size_t size)
{
  return memcpy(dest, source, size);
}

SNS_MEMMGR_UIMAGE_CODE void* SNS_OS_MEMSET(void *ptr, int value, size_t size)
{
  return memset(ptr, value, size);
}

SNS_MEMMGR_UIMAGE_CODE void* SNS_OS_MEMZERO(void *ptr, size_t size)
{
  return memset(ptr, 0, size);
}

SNS_MEMMGR_UIMAGE_CODE int SNS_OS_MEMCMP(const void *ptr1, const void *ptr2, size_t size)
{
  return memcmp(ptr1, ptr2, size);
}

SNS_MEMMGR_UIMAGE_CODE size_t SNS_OS_MEMSCPY(void *dest, size_t dest_size, const void *source, size_t source_size )
{
  return memscpy(dest, dest_size, source, source_size);
}

SNS_MEMMGR_UIMAGE_CODE bool SNS_OS_IS_UIMG_ADDR(void const *addr)
{
  return ( (void*)addr >= (void*)&__sensors_island_start && (void*)addr <= (void*)&__sensors_island_end );
}
