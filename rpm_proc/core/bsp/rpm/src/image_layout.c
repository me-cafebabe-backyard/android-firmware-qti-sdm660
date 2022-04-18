/*===========================================================================
                              image_layout.c

SERVICES:

DESCRIPTION:

INITIALIZATION AND SEQUENCING REQUIREMENTS:
Copyright (c) 2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.

The data RAM is laid out as follows...
For sections that don't have a fixed address, they will at least appear in the
order listed below

--------------------------------------------------------------------
|    SECTION NAME   |  ADDRESS  |   SIZE   | READABLE FROM MASTERS |
====================================================================
|                     |           |          |                       |
| IMAGE_INFO_HEADER   | 0x90000   |   0xB0   |         YES           |
| Thsi includes       |           |          |                       |
| IMAGE INFO and      |           |          |                       |
| BUILD ID            |           |          |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|    RAIL_RESIDENCIES | 0x900B0   |   0x100  |         YES           |
|                     |           |          |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|    SLEEP STATS      | 0x901B0   |   0x60   |         YES           |
|                     |           |          |                       |
--------------------------------------------------------------------
|                     |           | VARIABLE |                       |
|     CPR STATS       | 0x90210   |   PER    |         YES           |
|                     |           |  TARGET  |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|  DATA_RAM RW/ZI     | VARIABLE  | VARIABLE |         YES/NO        |
|                     |           |          |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|      STACK          | VARIABLE  |  0xA00   |         NO            |
|                     |           |          |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|       HEAP          | VARIABLE  | VARIABLE |         NO            |
|                     |           |          |                       |
--------------------------------------------------------------------
|                     |           |          |                       |
|      RPM LOG        | 0x9DC00   |  0x2400  |         YES           |
|                     |           |          |                       |
--------------------------------------------------------------------

===========================================================================*/


//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "comdef.h"
#include "image_layout.h"
#include "stringl/stringl.h"
#include "CoreVerify.h"
#include "swevent.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------

// This header is a lookup table for stats addresses. It is used by masters, so the address of this header
// and subsequent fields within the structure must be maintained

typedef struct
{
  unsigned reserved[3];
  char* rail_residencies_address;
  char* cpr_stats_address;
  char* sleep_stats_address;
  char* rpm_log_address;
  int rpm_free_heap_space;
  int rpm_min_free_heap_space;
  unsigned max_stack_usage;
  unsigned reserved2[6];
} rpm_image_info_header;

//---------------------------------------------------------------------------
// Global Constant Definitions
//---------------------------------------------------------------------------
static bool initialized = false;

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------
extern char Image$$IMAGE_INFO_HEADER$$Base[];
extern char Image$$RPM_IMAGE_ID$$Base[];
extern char Image$$RAIL_RESIDENCIES$$Base[];
extern char Image$$SLEEP_STATS$$Base[];
extern char Image$$CPR_STATS$$Base[];
extern char Image$$DATA_RAM$$Base[];
extern char Image$$STACK$$Base[];
extern char Image$$DATA_RAM_HEAP$$Base[];
extern char Image$$RPM_LOG$$Base[];
extern char Image$$DDR_STRUCT_DATA$$Base[];
extern char Image$$DDR_STRUCT_DATA$$ZI$$Limit[];
extern char Image$$VECTOR_TABLE$$Base[];
extern char Image$$DATA_RAM_RECLAIM_POOL$$Base[];
extern char Image$$DATA_RAM_RECLAIM_POOL$$Limit[];
extern char Image$$CODE_RAM_RECLAIM_POOL$$Base[];
extern char Image$$CODE_RAM_RECLAIM_POOL$$Limit[];
extern char Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Base[];
extern char Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Limit[];


const rpm_image_section_info rpm_image_section_array[RPM_IMAGE_SECTIONS_COUNT] =
{
    { //RPM_DATA_RAM
        .section_base = Image$$IMAGE_INFO_HEADER$$Base,
        .section_end  = Image$$DDR_STRUCT_DATA$$ZI$$Limit,
    },
    { //RPM_IMAGE_INFO_HEADER
        .section_base = Image$$IMAGE_INFO_HEADER$$Base,
        .section_end  = Image$$RPM_IMAGE_ID$$Base,
    },
    { //RPM_RAIL_RESIDENCIES
        .section_base = Image$$RAIL_RESIDENCIES$$Base,
        .section_end  = Image$$SLEEP_STATS$$Base,
    },
    { //RPM_SLEEP_STATS
        .section_base = Image$$SLEEP_STATS$$Base,
        .section_end  = Image$$CPR_STATS$$Base,
    },
    { //RPM_CPR_STATS
        .section_base = Image$$CPR_STATS$$Base,
        .section_end  = Image$$DATA_RAM$$Base,
    },
    { //RPM_STACK
        .section_base = Image$$STACK$$Base,
        .section_end  = Image$$VECTOR_TABLE$$Base,
    },
    { //RPM_HEAP
        .section_base = Image$$DATA_RAM_HEAP$$Base,
        .section_end  = Image$$RPM_LOG$$Base,
    },
    { //RPM_LOG
        .section_base = Image$$RPM_LOG$$Base,
        .section_end  = Image$$DDR_STRUCT_DATA$$Base,
    },
};

__attribute__((section("image_info_header")))
rpm_image_info_header rpm_image_header = {
  .reserved                 = {0},
  .rail_residencies_address = Image$$RAIL_RESIDENCIES$$Base,
  .cpr_stats_address        = Image$$CPR_STATS$$Base,
  .sleep_stats_address      = Image$$SLEEP_STATS$$Base,
  .rpm_log_address          = Image$$RPM_LOG$$Base,
  .rpm_free_heap_space      = 0,
  .rpm_min_free_heap_space  = 0,
  .max_stack_usage          = 0,
};

//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// External References
//---------------------------------------------------------------------------


//===========================================================================
//                             Macro Definitions
//===========================================================================

//===========================================================================
//                           Function Definitions
//===========================================================================


/*===========================================================================
FUNCTION: populate_image_header

DESCRIPTION:

RETURN VALUE:
===========================================================================*/
void populate_image_header(void)
{
  const uint32 build_id = RPM_BUILD_ID;

  rpm_image_info_header* rpm_image_header = (rpm_image_info_header*)rpm_image_section_array[RPM_IMAGE_INFO_HEADER].section_base;
  CORE_VERIFY((char*)&rpm_image_header[1]<=rpm_image_section_array[RPM_IMAGE_INFO_HEADER].section_end);

  memscpy(rpm_image_header->reserved, sizeof(uint32), &build_id, sizeof(uint32));
}

void rpm_adjust_free_heap_space(int heap_adjust)
{
  rpm_image_header.rpm_free_heap_space += heap_adjust;

  if((rpm_image_header.rpm_min_free_heap_space == 0) || (rpm_image_header.rpm_free_heap_space < rpm_image_header.rpm_min_free_heap_space))
  {
    rpm_image_header.rpm_min_free_heap_space = rpm_image_header.rpm_free_heap_space;
  }
}

int get_free_heap_space(void)
{
    return rpm_image_header.rpm_free_heap_space;
}

void rpm_free_heap_space_init(void)
{
    if(!initialized)
    {
        rpm_image_header.rpm_free_heap_space = 0;
        initialized = true;
    }
}

void rpm_reclaim_data_ram_pool(void)
{
    rpm_heap_add_section(Image$$DATA_RAM_RECLAIM_POOL$$Base, Image$$DATA_RAM_RECLAIM_POOL$$Limit, RPM_HEAP_SECTION_PRIORITY_HIGH);

    SWEVENT(RPM_RECLAIM_POOL, Image$$DATA_RAM_RECLAIM_POOL$$Base, Image$$DATA_RAM_RECLAIM_POOL$$Limit, get_free_heap_space());
}

void rpm_reclaim_code_ram_pool(void)
{
    rpm_heap_add_section(Image$$CODE_RAM_RECLAIM_POOL$$Base, Image$$CODE_RAM_RECLAIM_POOL$$Limit, RPM_HEAP_SECTION_PRIORITY_LOW);

    SWEVENT(RPM_RECLAIM_POOL, Image$$CODE_RAM_RECLAIM_POOL$$Base, Image$$CODE_RAM_RECLAIM_POOL$$Limit, get_free_heap_space());
}

void rpm_reclaim_smem_init_code_ram_pool(void)
{
    rpm_heap_add_section(Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Base, Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Limit, RPM_HEAP_SECTION_PRIORITY_LOW);

    SWEVENT(RPM_RECLAIM_POOL, Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Base, Image$$CODE_RAM_SMEM_INIT_RECLAIM_POOL$$Limit, get_free_heap_space());
}


void rpm_update_stack_usage(void)
{
    unsigned stack_top_addr    = (unsigned)rpm_image_section_array[RPM_STACK].section_base;
    unsigned stack_bottom_addr = (unsigned)rpm_image_section_array[RPM_STACK].section_end - rpm_image_header.max_stack_usage;

    /*
     * binary-search the deepest stack address
     */
    while(stack_bottom_addr > stack_top_addr)
    {
        unsigned mid_addr = 0xfffffffc & ((stack_top_addr + stack_bottom_addr)/2); /* must be word-aligned */

        /*
         * check if the stack address has been modified.
         */
        if(*(unsigned*)mid_addr != RPM_STACK_FILL_WORD)
        {
            /*
             * it has been modified. Update the deepest stack address.
             */
            stack_bottom_addr = mid_addr;
        }
        else
        {
            stack_top_addr = mid_addr + sizeof(unsigned);
        }
    }

    rpm_image_header.max_stack_usage = (unsigned)rpm_image_section_array[RPM_STACK].section_end - stack_bottom_addr;
}

