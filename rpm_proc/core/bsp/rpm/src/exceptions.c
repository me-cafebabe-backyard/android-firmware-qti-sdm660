#include <string.h>
#include "cortex-m3.h"
#include "comdef.h"
#include "rpm_hwio.h"
#include "HALhwio.h"
#include "coredump.h"
#include "image_layout.h"
#include "CoreVerify.h"
#include "swevent.h"
#include "busywait.h"
#include "Chipinfo.h"
#include "dog.h"
#include "rpm_vector_table.h"

extern __asm void abort_isr(void) __irq;

#ifdef __clang__
#define __disable_irq() __asm__("cpsid	i");
#define __enable_irq() __asm__("cpsie	i");
#endif

__attribute__((section("exceptions_dram_reclaim_pool")))
void exceptions_init(void)
{
  int i, num_ints;

  // Disable interrupts globally.
  __disable_irq();

  // Default all RPM interrupts to rising edge.
  HWIO_OUT(RPM_INTR_POLARITY_0, 0xFFFFFFFF);
  HWIO_OUT(RPM_INTR_POLARITY_1, 0xFFFFFFFF);
  HWIO_OUT(RPM_INTR_EDG_LVL_0,  0xFFFFFFFF);
  HWIO_OUT(RPM_INTR_EDG_LVL_1,  0xFFFFFFFF);

  // Figure out how many interrupts are supported on this platform.
  num_ints = ((SCS.IntCtrlType & 0x1F) + 1) << 5;

  // Disable all interrupts.
  for(i = 0; i < num_ints / 32; ++i)
    SCS.NVIC.Disable[i] = 0xFFFFFFFF;

  // Clear all interrupts.
  for(i = 0; i < num_ints / 32; ++i)
    SCS.NVIC.Clear[i] = 0xFFFFFFFF;

  // Set all interrupt levels as pre-empting.
  SCS.AIRC = 0x05FA0000;

  // based on the size of vector_table and method of vector_table indexing (i (upto < num_ints) + 16)
  CORE_VERIFY( num_ints <= NUM_INTERRUPTS );

  // Set all interrupts to lowest priority.
  for(i = 0; i < num_ints / 4; ++i)
    SCS.NVIC.Priority[i] = 0xFFFFFFFF;

  // Configure the exception vector table.
  SCS.ExceptionTableOffset = (unsigned)&vector_table;

  // Enable traps on divides by 0 and double-word stack alignment.
  SCS.ConfigCtrl |= 0x210;

  // Memory/Bus/Usage faults get highest user priority.
  SCS.SystemPriority[0] = 0;

  // Other system exceptions get middling priority.
  SCS.SystemPriority[1] = 0xC0000000; // SVC = 0xC0
  SCS.SystemPriority[2] = 0xFFFF0080; // SysTick and PendSV = 0xFF, Debug = 0x80

  // Enable the usage, bus, and memory management fault handlers.
  SCS.SystemHandlerCtrlAndState = 0x70000;

  // Now that we're all set, go through and re-enable interrupts that have handlers.
  for(i = 0; i < num_ints; ++i)
  {
    // Check for weakly linked handler that doesn't exist yet.
    // Note the +16 that skips system handlers.
    if(!vector_table[i + INTERRUPT_OFFSET])
        vector_table[i + INTERRUPT_OFFSET] = abort_isr;

    if(abort_isr != vector_table[i + INTERRUPT_OFFSET])
      SCS.NVIC.Enable[i/32] = (1 << (i % 32));
  }

  // Give the watchdog bark IRQ the same priority as a fault.
  interrupt_set_priority(WATCHDOG_IRQ_NUM, 0);

  // Enable fault handling.
  set_basepri(0);
  INTLOCK();
  __enable_irq();
}

void exceptions_enable(void)
{
    INTFREE();
}

void interrupt_soft_trigger(unsigned num)
{
    CORE_VERIFY(num < NUM_INTERRUPTS);
    STIR.SoftwareTriggerInterrupt = num;
}

void interrupt_set_isr(unsigned num, isr_type isr)
{
	CORE_VERIFY(num < NUM_INTERRUPTS);
    vector_table[INTERRUPT_OFFSET+num] = isr;
}

void interrupt_configure(unsigned num, interrupt_config config)
{
    volatile unsigned *RPM_INTERRUPT_POLARITY = (unsigned int *)HWIO_RPM_INTR_POLARITY_0_ADDR;
    volatile unsigned *RPM_INTERRUPT_EDGE = (unsigned int *)HWIO_RPM_INTR_EDG_LVL_0_ADDR;

	CORE_VERIFY(num < NUM_INTERRUPTS);
	
    switch(config)
    {
        case RISING_EDGE:
            RPM_INTERRUPT_POLARITY[num/32] |=  (1 << (num % 32));
            RPM_INTERRUPT_EDGE[num/32]     |=  (1 << (num % 32));
            break;

        case FALLING_EDGE:
            RPM_INTERRUPT_POLARITY[num/32] &= ~(1 << (num % 32));
            RPM_INTERRUPT_EDGE[num/32]     |=  (1 << (num % 32));
            break;

        case LEVEL_HIGH:
            RPM_INTERRUPT_POLARITY[num/32] |=  (1 << (num % 32));
            RPM_INTERRUPT_EDGE[num/32]     &= ~(1 << (num % 32));
            break;

        case LEVEL_LOW:
            RPM_INTERRUPT_POLARITY[num/32] &= ~(1 << (num % 32));
            RPM_INTERRUPT_EDGE[num/32]     &= ~(1 << (num % 32));
            break;
    }
}

void interrupt_set_priority(unsigned num, unsigned priority)
{
    unsigned priority_word;
    unsigned priority_offset;
    unsigned priority_mask;

	CORE_VERIFY(num < NUM_INTERRUPTS);
	
	priority_word = SCS.NVIC.Priority[num/4];
    priority_offset = 8 * (num % 4);
    priority_mask = ~(0xff << priority_offset);

    SCS.NVIC.Priority[num/4] = (priority_word & priority_mask) | ((0xff & priority) << priority_offset);
}

void interrupt_enable(unsigned num) 
{ 
    unsigned idx = num / 32, mask = (1 << (num % 32)); 
 
    CORE_VERIFY(num < NUM_INTERRUPTS); 
 
    // Clear the interrupt before enabling it, or the NVIC may store a previously sampled edge. 
    // This is since the NVIC samples *all* interrupts (internally it has no notion of 'level'), and latches them. 
    SCS.NVIC.Clear[idx]  = mask; 
    SCS.NVIC.Enable[idx] = mask; 
} 
 
void interrupt_enable_no_clear(unsigned num) 
{ 
    unsigned idx = num / 32, mask = (1 << (num % 32)); 
 
    CORE_VERIFY(num < NUM_INTERRUPTS); 
 
    SCS.NVIC.Enable[idx] = mask; 
} 
 
void interrupt_disable(unsigned num) 
{ 
    CORE_VERIFY(num < NUM_INTERRUPTS); 
 
    SCS.NVIC.Disable[num/32]    = (1 << (num % 32)); 
} 
 
void interrupt_clear(unsigned num) 
{ 
    CORE_VERIFY(num < NUM_INTERRUPTS); 
 
    SCS.NVIC.Clear[num/32]      = (1 << (num % 32)); 
} 
 
bool interrupt_is_pending(unsigned num) 
{ 
    CORE_VERIFY(num < NUM_INTERRUPTS); 
 
    return SCS.NVIC.Set[num/32] & (1 << (num % 32)); 
}

unsigned intlock_nest_level = 0;

void lock_ints(void)
{
#ifdef VIRTIO_WORKAROUND
  // Disable interrupts globally.
  __disable_irq();
#endif

  unsigned _was_masked = get_basepri();
  set_basepri(0x10);
  assert(!intlock_nest_level || _was_masked);
  ++intlock_nest_level;

#ifdef VIRTIO_WORKAROUND
  __enable_irq();
#endif
}

void unlock_ints(void)
{
#ifdef VIRTIO_WORKAROUND
  // Disable interrupts globally.
  __disable_irq();
#endif

  unsigned _is_masked = get_basepri();
  assert(intlock_nest_level && _is_masked);
  if(!--intlock_nest_level)
  {
    set_basepri(0);
  }

#ifdef VIRTIO_WORKAROUND
  __enable_irq();
#endif
}
/*===========================================================================
FUNCTION: is_any_interrupt_pending

DESCRIPTION: 
ARM TRM says that ISRPENDING indicates a pending interrupt irrespective
of whether it is enabled or not. So This cannot be used for checking.
VECTPENDING gives the highest priority pending exception, but it also includes the 
effect of the BASEPRI and FAULTMASK registers, but not any effect of the PRIMASK register. 
We’re in an intlocked context, and we use BASEPRI as our intlock mechanism. 
BASEPRI will be 16, and thus VECTPENDING will effectively mask out all of the other interrupts.
Instead we check NVIC Enabled and Set registers to understand whether interrupts
are pending.

RETURN VALUE: True if any interrupt is pending
===========================================================================*/
bool is_any_interrupt_pending(void)
{
  int num_ints, i;
  bool result = false;
  num_ints = ((SCS.IntCtrlType & 0x1F) + 1) << 5;
  for(i = 0; ((i < num_ints / 32) && !result); i++)
  {
    if (SCS.NVIC.Enable[i] & SCS.NVIC.Set[i])
      result = true;
  }
  return result;
}

