
// The RPM shall not make use of RVCT's semihosting.
#pragma import(__use_no_semihosting)
#pragma import(__use_no_semihosting_swi)

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifndef __clang__
#include <rt_sys.h>
#include <rt_heap.h>
#else
#include <malloc.h>
#include <string.h>
#endif
#include "comdef.h"
#include "coredump.h"
#include "image_layout.h"
#include "CoreVerify.h"
#include "swevent.h"

const char __stdin_name[] ="STDIN";
const char __stdout_name[]="STDOUT";
const char __stderr_name[]="STDERR";

static int heap_free_count;

char** stack_base_address = (char**)&rpm_image_section_array[RPM_STACK].section_end;
char** stack_end_address = (char**)&rpm_image_section_array[RPM_STACK].section_base;

#ifndef __clang__
__asm void __user_setup_stackheap()
{
  IMPORT stack_base_address
  IMPORT stack_end_address

  ldr r0, =stack_base_address
  ldr r0, [r0]
  ldr r0, [r0]
  mov sp, r0

  ldr r3, =stack_end_address
  ldr r3, [r3]
  ldr r3, [r3]

  ldr r2, =RPM_STACK_FILL_WORD

stack_fill_loop
  sub r0, r0, #0x4
  str r2, [r0]
  cmp r0, r3
  bne stack_fill_loop

  mov r0, #0
  mov r2, #0
  bx lr
  ALIGN
}
#else
__attribute__((naked)) void __user_setup_stackheap()
{

  asm("ldr r0, =stack_base_address");
  asm("ldr r0, [r0]");
  asm("ldr r0, [r0]");
  asm("mov sp, r0");
  
  asm("ldr r3, =stack_end_address");
  asm("ldr r3, [r3]");
  asm("ldr r3, [r3]");
  
  asm("stack_fill_loop:");
  asm("sub r0, r0, #0x4");
  asm("str r2, [r0]");
  asm("cmp r0, r3");
  asm("bne stack_fill_loop");
  
  asm("mov r0, #0");
  asm("mov r2, #0");
  asm("bx lr");
}
typedef int FILEHANDLE;
#endif

FILEHANDLE _sys_open(const char *name, int openmode)
{
  return -1;
}

FILEHANDLE _sys_close(FILEHANDLE fh)
{
  return -1;
}

int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
  return -1;
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
  return -1;
}

int _sys_ensure(FILEHANDLE fh)
{
  return -1;
}

long _sys_flen(FILEHANDLE fh)
{
  return -1;
}

int _sys_seek(FILEHANDLE fh, long pos)
{
  return -1;
}

int _sys_istty(FILEHANDLE fh)
{
  return -1;
}

int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
  return 0;
}

char *_sys_command_string(char *cmd, int len)
{
  return 0;
}

void _ttywrch(int ch)
{
}

void _sys_exit(int return_code)
{
  abort();
}

typedef struct rpm_heap_section_s* rpm_heap_section_t;

typedef struct rpm_heap_section_s
{
    char *heapPtr;
    char *heapLimit;
    char *initialPtr;
    rpm_heap_section_t next_section;
} rpm_heap_section_s;

typedef struct __Heap_Descriptor
{
    rpm_heap_section_t heap_sections[RPM_HEAP_SECTION_PRIORITY_COUNT];
} __Heap_Descriptor;

static rpm_heap_section_s initial_high_priority_heap_section;
static rpm_heap_section_s initial_mid_priority_heap_section;
static rpm_heap_section_s initial_low_priority_heap_section;

__Heap_Descriptor theHeap;
static bool heap_free_disabled;

void prevent_further_heap_frees(void)
{
    heap_free_disabled = true;
}

extern int __Heap_DescSize(int zero)
{
    return sizeof(__Heap_Descriptor);
}

extern char Image$$INITIAL_CODE_RAM_HEAP$$Base[];
extern char Image$$CODE_RAM_SAVE$$Base[];

static void rpm_heap_populate_section(char* base, char* limit, rpm_heap_section_t section)
{
    section->heapPtr = (char *)(((unsigned)base + 7) & ~7);
    section->heapLimit = (char *)((unsigned)limit & ~7);
    section->initialPtr = section->heapPtr;
    rpm_adjust_free_heap_space(section->heapLimit - section->heapPtr);
}

extern void __Heap_Initialize(struct __Heap_Descriptor *h)
{
    theHeap.heap_sections[RPM_HEAP_SECTION_PRIORITY_HIGH] = &initial_high_priority_heap_section;
    theHeap.heap_sections[RPM_HEAP_SECTION_PRIORITY_MID] = &initial_mid_priority_heap_section;
    theHeap.heap_sections[RPM_HEAP_SECTION_PRIORITY_LOW] = &initial_low_priority_heap_section;

    rpm_free_heap_space_init();

    //less than 16k of heap space so no need to make a low vs mid priority call
    //rpm_heap_populate_section(Image$$INITIAL_CODE_RAM_HEAP$$Base,
    //                          Image$$CODE_RAM_SAVE$$Base,
    //                          &initial_low_priority_heap_section);

    //this section is saved on warm reset, so mark it as higher priority then rest of code RAM heap, 
    //but lower priority then data RAM heap
    rpm_heap_populate_section(Image$$INITIAL_CODE_RAM_HEAP$$Base,
                              Image$$CODE_RAM_SAVE$$Base,
                              &initial_mid_priority_heap_section);

    rpm_heap_populate_section(rpm_image_section_array[RPM_HEAP].section_base,
                              (char*) rpm_image_section_array[RPM_HEAP].section_end,
                              &initial_high_priority_heap_section);
}

extern void __Heap_Finalize(struct __Heap_Descriptor *h) {}
extern void __Heap_ProvideMemory(struct __Heap_Descriptor *h, void *mem, size_t size) {}

//To do - throw out full sections.
static void* rpm_heap_alloc_from_section_list(rpm_heap_section_t section_list, size_t size)
{
    while(section_list)
    {
        if((section_list->heapPtr)+size<=section_list->heapLimit)
        {
            char *mem = section_list->heapPtr;
            section_list->heapPtr += size;
            rpm_adjust_free_heap_space(-size);
            return mem;
        }
        section_list = section_list->next_section;
    }

    return NULL;
}

extern void *__Heap_Alloc(struct __Heap_Descriptor *h, size_t size)
{
    INTLOCK();

    size = (size + 7) & ~7; // ARM docs say to 8-byte align allocated blocks.

    for(int i=0; i<RPM_HEAP_SECTION_PRIORITY_COUNT; i++)
    {
        void* ret = rpm_heap_alloc_from_section_list(theHeap.heap_sections[i], size);

        if(ret)
        {
            INTFREE();
            return ret;
        }
    }
    SWEVENT(RPM_OUT_OF_HEAP);
    abort();
}

void rpm_heap_add_section(char* base, char* limit, rpm_heap_section_priority priority)
{
    //First ensure that this new heap section does not overlap any other section
    int i;
    char* base_address;
    char* end_address;
    for(i=0; i<RPM_HEAP_SECTION_PRIORITY_COUNT; i++) {
        rpm_heap_section_t section = theHeap.heap_sections[i];
        while(section != NULL) {
            base_address = section->initialPtr;
            end_address = section->heapLimit;
            if ( (base_address < base && end_address > base) || 
                (base_address < limit && end_address > limit) || 
                (base_address > base && end_address < limit) ) {
                ERR_FATAL("rpm_heap_add_section: heap section overlap", 0, 0, 0);
            }
            section = section->next_section;
        }
    }
    
    //Second, zero fill it so that no one can accidentally read data from it that will be eventually overwritten by the heap.
    memset(base, 0, limit - base);

    rpm_heap_section_t new_section = (rpm_heap_section_t) malloc(sizeof(rpm_heap_section_s));
    if (NULL == new_section)
    {
        ERR_FATAL("rpm_heap_add_section: malloc failed", 0, 0, 0);
    }

    rpm_heap_populate_section(base, limit, new_section);

    new_section->next_section = theHeap.heap_sections[priority];
    theHeap.heap_sections[priority] = new_section;
}

extern void __Heap_Free(struct __Heap_Descriptor *h, void *ptr)
{
    // On the RPM we don't allow people to repeatedly alloc and free. That pattern leads to
    // heap fragmentation which will eventually cause the RPM to fail with OOM.
    // Better to just prevent the pattern in the first place.

    if(heap_free_disabled)
    {
        abort();
    }
    heap_free_count++;
}

extern void *__Heap_Realloc(struct __Heap_Descriptor *h, void *old_mem, size_t size)
{
    void *new_mem = __Heap_Alloc(h, size);
    memcpy(new_mem, old_mem, size);
    return new_mem;
}

extern void *__Heap_Stats(struct __Heap_Descriptor *h,
                          int (*print)(void *, char const *format, ...),
                          void *printparam)
{
    return NULL;
}

extern int __Heap_Valid(struct __Heap_Descriptor *h,
                        int (*print)(void *, char const *format, ...),
                        void *printparam, int verbose)
{
    return 1;
}

#ifdef __clang__
void * __wrap_malloc(size_t size) {
  return __Heap_Alloc(NULL, size);
}

void  __wrap_free(void* ptr) {
  __Heap_Free(NULL, ptr);
}

void * __wrap_realloc(void *old_mem, size_t size) {
  return __Heap_Realloc(NULL, old_mem, size);
}

void * __wrap_calloc(size_t m, size_t n) {
  void * p = malloc(m*n);
  if (p) {
    size_t *z;
    n = (n + sizeof(*z) - 1)/sizeof *z;
    for(z = p; n; n--,z++) *z = 0;
  }
  return p;
}
#endif
