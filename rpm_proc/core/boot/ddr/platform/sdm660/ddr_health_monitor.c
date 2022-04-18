/**
 * @file ddr_health_monitor.c
 * @brief
 * DDR Health Monitor Framework.
 */


/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/platform/sdm660/ddr_health_monitor.c#2 $
$DateTime: 2017/03/15 09:06:36 $
$Author: pwbldsvc $
================================================================================
when        who     what, where, why
--------    ---     -------------------------------------------------------------
06/06/2014  tw      CORE_VERIFY(0) Enabled
06/03/2014  tw      Initial implementation   
================================================================================
                   Copyright 2014 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_health_monitor.h"
#include "page_select.h"
#include "CoreVerify.h"

/*==============================================================================
                                  MACROS
==============================================================================*/

/*==============================================================================
                                  DATA
==============================================================================*/
/**
 * Variable where DDR test log is stored, including test message, error type,
 * and address and data pattern where error occurs.
 */
typedef struct
{
  uint64 *address; /* base address of memory to test */
  uint32 size; /* in bytes */ 
  uint32 status;
} ddr_health_str;

typedef enum
{
  DDR_HEALTH_OK,
  DDR_HEALTH_FAILED_CHECK,
  DDR_HEALTH_INPUT_ERROR,
  DDR_HEALTH_MAX = 0x7FFFFFFF,
} DDR_HEALTH_STATUS;

 ddr_health_str ddr_health = {(uint64 *)0x0, 0x0, DDR_HEALTH_OK};

/* define static pattern for test 64bytes*/
#define DDR_HEALTH_PATTERN_SIZE 16
uint32 ddr_health_pattern[DDR_HEALTH_PATTERN_SIZE] = 
{
0xA5A5A5A5, 0x5A5A5A5A, 0xA5A5A5A5, 0x5A5A5A5A,
0xA5A5A5A5, 0x5A5A5A5A, 0xA5A5A5A5, 0x5A5A5A5A,
0xA5A5A5A5, 0x5A5A5A5A, 0xA5A5A5A5, 0x5A5A5A5A,
0xA5A5A5A5, 0x5A5A5A5A, 0xA5A5A5A5, 0x5A5A5A5A, 
};

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

/* inline assembly to do burst write */
#ifndef __clang__
__asm void __blocksCopy(volatile uint32 *source, volatile uint32 *destination, uint32 num_words)
{
                        MOVS    r3,r2, LSR #3           ; Number of eight word multiples.
                        BEQ     readwords               ; Less than eight words to move?
                        STMFD   sp!, {r4-r11}           ; Save some working registers.
octread                 ;LDMIA   r0, {r4-r11}            ; Load 8 words from the source
                        LDMIA   r0!, {r4-r11}
                        STMIA   r1!, {r4-r11}           ; and put them at the destination.
                        SUBS    r3, r3, #1              ; Decrement the counter.
                        BNE     octread                 ; ... copy more.
                        LDMFD   sp!, {r4-r11}           ; Dont need these now - restore

readwords               ANDS    r2, r2, #7              ; Number of odd words to copy.
                        BEQ     ret                     ; No words left to copy?

copy                    STMFD   sp!, {r4-r10}           ; Save some working registers.
                        cmp     r2,#1
                        beq     oneword                 ; write the remaining one word
                        cmp     r2,#2
                        beq     twowords                ; do a burst of two words
                        cmp     r2,#3
                        beq     threewords              ; do a burst of three words
                        cmp     r2,#4
                        beq     fourwords               ; do a burst of four words
                        cmp     r2,#5
                        beq     fivewords               ; do a burst of five words
                        cmp     r2,#6
                        beq     sixwords                ; do a burst of six words
                        cmp     r2,#7
                        beq     sevenwords              ; do a burst of seven words
                        b       stop

oneword                 ldr     r3, [r0]
                        str     r3, [r1]
                        b       stop

twowords                ldmia   r0!,{r4-r5}
                        stmia   r1!,{r4-r5}
                        b       stop

threewords              ldmia   r0!,{r4-r6}
                        stmia   r1!,{r4-r6}
                        b       stop

fourwords               ldmia   r0!,{r4-r7}
                        stmia   r1!,{r4-r7}
                        b       stop

fivewords               ldmia   r0!,{r4-r8}
                        stmia   r1!,{r4-r8}
                        b       stop

sixwords                ldmia   r0!,{r4-r9}
                        stmia   r1!,{r4-r9}
                        b       stop

sevenwords              ldmia   r0!,{r4-r10}
                        stmia   r1!,{r4-r10}

stop                    LDMFD   sp!, {r4-r10}           ; restore r4 to r11
ret                     BX      lr                      ; Return.
}
#else
__asm void __blocksCopy(volatile uint32 *source, volatile uint32 *destination, uint32 num_words)
{
asm("                        MOVS    r3,r2, LSR #3  ");         // Number of eight word multiples.
asm("                        BEQ     readwords      ");         // Less than eight words to move?
asm("                        STMFD   sp!, {r4-r11}  ");         // Save some working registers.
asm("octread:         ");     //;LDMIA   r0, {r4-r11}            // Load 8 words from the source
asm("                        LDMIA   r0!, {r4-r11}  ");
asm("                        STMIA   r1!, {r4-r11}  ");         // and put them at the destination.
asm("                        SUBS    r3, r3, #1     ");         // Decrement the counter.
asm("                        BNE     octread        ");        // ... copy more.
asm("                        LDMFD   sp!, {r4-r11}  ");        // Dont need these now - restore

asm("readwords:               ANDS    r2, r2, #7     ");         //Number of odd words to copy.
asm("                        BEQ     ret            ");         // No words left to copy?

asm("copy:                    STMFD   sp!, {r4-r10}  ");         // Save some working registers.
asm("                        cmp     r2,#1			");
asm("                        beq     oneword        ");         // write the remaining one word
asm("                        cmp     r2,#2			");
asm("                        beq     twowords       ");         // do a burst of two words
asm("                        cmp     r2,#3			");
asm("                        beq     threewords     ");         // do a burst of three words
asm("                        cmp     r2,#4			");
asm("                        beq     fourwords      ");         // do a burst of four words
asm("                        cmp     r2,#5			");
asm("                        beq     fivewords      ");         // do a burst of five words
asm("                        cmp     r2,#6			");
asm("                        beq     sixwords       ");         // do a burst of six words
asm("                        cmp     r2,#7			");
asm("                        beq     sevenwords     ");         // do a burst of seven words
asm("                        b       stop			");

asm("oneword:                 ldr     r3, [r0]		");
asm("                        str     r3, [r1]		");
asm("                        b       stop			");

asm("twowords:               ldmia   r0!,{r4-r5}		");
asm("                       stmia   r1!,{r4-r5}		");
asm("                       b       stop			");

asm("threewords:              ldmia   r0!,{r4-r6}	");
asm("                        stmia   r1!,{r4-r6}	");
asm("                        b       stop			");

asm("fourwords:               ldmia   r0!,{r4-r7}	");
asm("                        stmia   r1!,{r4-r7}	");
asm("                        b       stop			");

asm("fivewords:               ldmia   r0!,{r4-r8}	");
asm("                        stmia   r1!,{r4-r8}	");
asm("                        b       stop			");

asm("sixwords:                ldmia   r0!,{r4-r9}	");
asm("                        stmia   r1!,{r4-r9}	");
asm("                        b       stop			");

asm("sevenwords:              ldmia   r0!,{r4-r10}	");
asm("                        stmia   r1!,{r4-r10}	");

asm("stop:                    LDMFD   sp!, {r4-r10}  ");         // restore r4 to r11
asm("ret:                     BX      lr             ");         // Return.
}
#endif
/* =============================================================================
**  Function : ddr_test_walking_ones
** =============================================================================
*/
/**
*   @brief
*   Test memory integrity by walking-ones algorithm.
*
*   This function writes "0x1" to the first word of memory, and rotates data
*   pattern one bit left for each write to successive word. These patterns are
*   then verified on subsequent read pass. The start pattern is shifted one bit
*   left for each write/read pass. It runs 32 passes (1 word = 32 bits) in total
*   for all possible data patterns.
*
*   @param[in]  base     Base address of memory
*   @param[in]  limit    Maximum offset (in bytes) of memory
*
*   @retval  TRUE     Test passed
*   @retval  FALSE    Test failed
*
*   @dependencies
*   Memory size in words must be power of 2, and base address must be aligned
*   with size. Also assume data/address lines are wired properly.
*
*   @sideeffects
*   Memory is corrupted after this function is called. Error is logged if any.
*
*   @sa
*   None
*/
#if 0
static boolean ddr_test_walking_ones
(
  uint32 base,
  uint32 limit
)
{
  volatile uint32 *base_addr;
  uint32 offset;
  uint32 start_pattern, pattern;

  /* convert base address and limit for accessing memory by word */
  base_addr = (uint32 *)base;
  limit >>= 2;

  for (start_pattern = 0x1; start_pattern != 0x0; start_pattern <<= 1)
  {
    /* write pass: rotate data pattern one bit left for each successive word */
    pattern = start_pattern;
    for (offset = 0; offset <= limit; offset++)
    {
      base_addr[offset] = pattern;
      pattern <<= 1;
      if (pattern == 0x0)
      {
        pattern = 0x1;
      }
    }

    /* read pass for verification */
    pattern = start_pattern;
    for (offset = 0; offset <= limit; offset++)
    {
      if (base_addr[offset] != pattern)
      {
        return FALSE;
      }
      pattern <<= 1;
      if (pattern == 0x0)
      {
        pattern = 0x1;
      }
    }
  }

  return TRUE;
}
#endif
boolean ddr_health_copy_test(uint32 *address, uint32 size)
{
  uint32 i;
  uint32 tmp;
  void *write_address[2];
  uint32 read_data[2][DDR_HEALTH_PATTERN_SIZE] = {0};
  
  /* find the first 1kb aligned address*/
  tmp = ((uint32)address)%1024;
  
  if(tmp < DDR_HEALTH_PATTERN_SIZE * 4 &&
     tmp != 0)
  {
    /* 
     first address is not big enough to fit test pattern, skip over to the next
     address boundary, and the one after that for testing 
    */
    tmp = (uint32)(address) - tmp + 1024;
  }
  else
  {
    tmp = (uint32)address;
  }
 
  write_address[0] = (void *)tmp;
  write_address[1] = (void *)(tmp + 1024);

  
  /* perform burst copy to test address */
  __blocksCopy(ddr_health_pattern, (volatile uint32 *)write_address[0], DDR_HEALTH_PATTERN_SIZE);
  __blocksCopy(ddr_health_pattern, (volatile uint32 *)write_address[1], DDR_HEALTH_PATTERN_SIZE);
  
  /* perform check */
  __blocksCopy(write_address[0], (volatile uint32 *)read_data[0], DDR_HEALTH_PATTERN_SIZE);
  __blocksCopy(write_address[1], (volatile uint32 *)read_data[1], DDR_HEALTH_PATTERN_SIZE);

  for(i = 0; i < DDR_HEALTH_PATTERN_SIZE; i++)
  {
    if(ddr_health_pattern[i] != (read_data[0])[i] || 
       ddr_health_pattern[i] != (read_data[1])[i] )
      return FALSE;
  }

  return TRUE;
}

void ddr_health_monitor( void )
{
  if(ddr_health.size != 0)
  {
    /* test enabled */
    if(!ddr_health_copy_test((uint32_t *)ddr_health.address, ddr_health.size))
    {
      /* test failed */
      CORE_VERIFY(0);
    }
  }
}

void ddr_health_monitor_rpm_msg_hdlr(uint64 address, uint32 size)
{
  uint64 *cast_address;

  /* call rpm api to translate from system view address to rpm view address */  
  address = set_ddr_access(address);
  cast_address = (uint64 *)(uintptr_t )address;
  
  /* update internal structure to match new given size, taking into account
     rpm sliding window
   */
   ddr_health.address = cast_address;
   ddr_health.size = size;
   ddr_health.status = DDR_HEALTH_OK;
}
