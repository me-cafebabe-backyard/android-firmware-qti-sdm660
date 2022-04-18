/*==============================================================================

FILE:      rpm_mpu.c

DESCRIPTION: This file implements RPM MPU implementations and configurations as follows


                               RGN 0          RGN 1         RGN 2        RGN 3         RGN 4
            --- 0x000000 -+-------------+             |             |             |             |
             |            |             |             |             |             |             |
 CODE RAM    |            |             |             |             |             |             |
             |            |  (XRO)      |             |             |             |             |
             |            |             |             |             |             |             |
             |  variable -+ - - - - - - + - - - - - - +-------------+             |             |
             |  variable -+ - - - - - - +-------------+  (XRW)      |             |             |
             |  variable -+ - - - - - - + - - - - - - +-------------+             |             |
             |            |             | (RW)        |             |             |             |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
            --- 0x020000 -+-------------+ - - - - - - + - - - - - - +-------------+             |
DDR CODE RAM |  variable -+ - - - - - - +-------------+             |             |             |
             |            |             |             |             |  (XRO)      |             |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
             |  0x026400 -+ - - - - - - + - - - - - - + - - - - - - + - - - - - - +-------------+
             |            |             |             |             |             |             |
             |            |             |             |             |             |  (RW)       |
             |            |             |             |             |             |             |
             |            |             |             |             |             |             |
            --- 0x028000 -| - - - - - - + - - - - - - + - - - - - - +-------------+-------------+


                              RGN 5          RGN 6
            --- 0x090000 -+-------------+             |
             |            |             |             |
 DATA RAM    |            |             |             |
             |            |             |             |
             |            |  (RW)       |             |
             |            |             |             |
             |            |             |             |
             |  0x09FA20 -+ - - - - - - +-------------+
             |            |             | (NO ACCESS) |
             |  0x09FA40 -+ - - - - - - +-------------+
             |            |             |             |
             |            |             |             |
             |            |             |             |
             |            |             |             |
            --- 0x0A4000 -+ - - - - - - +             |
                          |             |             |
                0x0A8000 -+-------------+             |


PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2014-2015 Qualcomm Technologies Incorporated.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential


$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/src/rpm_mpu.c#2 $
$Date: 2017/03/15 $

==============================================================================*/

/*==============================================================================
**
**      Include Files
**
**==============================================================================
*/

#include "cortex-m3.h"
#include "rpm_mpu.h"
#include "image_layout.h"
#include "CoreVerify.h"


/*==============================================================================
**
**      Variables
**
**==============================================================================
*/
extern char Image$$CODE_RAM$$Base[];
extern char Image$$CODE_RAM_RECLAIM_POOL$$Base[];
extern char Image$$CODE_RAM_SAVE$$Base[];
extern char Image$$CODE_RAM_SAVE_END$$Base[];
extern char Image$$STACK_OVERFLOW$$Base[];
extern char Image$$STACK$$Base[];

static unsigned rpm_mpu_num_supported_regions = 0;

rpm_mpu_rgn_cfg_t rpm_mpu_cfg[RPM_MPU_RGN_COUNT] =
{
    /*
     * region 0 - RPM_MPU_RGN_CODE_RAM
     *
     * Set RPM CODE RAM (128KB) to read-only and executable
     * Enable after reclaiming code ram pool
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_CODE_RAM,
        .attr_size =
        {
            .permission      = RPM_MPU_RGN_AP_RO,
        }
    },
    /*
     * region 1 - RPM_MPU_RGN_RO_CODE_RAM
     *
     * Set the permission for RO data at end of CODE RAM to be read-only and non-executable
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_RO_CODE_RAM,
        .attr_size =
        {
            .enable          = TRUE,
            .permission      = RPM_MPU_RGN_AP_RO,
            .execute_disable = TRUE,
        }
    },

    /*
     * region 2 - RPM_MPU_RGN_CODE_RAM_HEAP
     *
     * Set the permission for RPM CODE RAM HEAP to be read-write and non-executable
     * Enable after reclaiming code ram pool
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_CODE_RAM_HEAP,
        .attr_size =
        {
            .permission      = RPM_MPU_RGN_AP_RW,
            .execute_disable = FALSE,
        }
    },
    /*
     * region 3 - RPM_MPU_RGN_CODE_RAM_HEAP_BORDER
     *
     * Set the permission for the region between CODE RAM and CODE RAM HEAP to be read-write and executable
     * because the beginning of CODE RAM HEAP region (RW) can override the permission for the end of CODE RAM (XRO).
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_CODE_RAM_HEAP_BORDER,
        .attr_size =
        {
            .enable          = TRUE,
            .permission      = RPM_MPU_RGN_AP_RW,
        }
    },
    /*
     * region 4 - RPM_MPU_RGN_DATA_RAM
     *
     * Disable instruction fetch from entire RPM DATA RAM (80KB)
     * Enable after reclaiming data ram pool
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_DATA_RAM,
        .attr_size =
        {
            .execute_disable = TRUE,
            .permission      = RPM_MPU_RGN_AP_RW,
        }
    },
    /*
     * region 5 - RPM_MPU_RGN_STACK_OVERFLOW
     *
     * Set the permission for 32 bytes between Heap and Stack to make it inaccessible to detect stack overflow
     *
     */
    {
        .rgn_id = RPM_MPU_RGN_STACK_OVERFLOW,
        .attr_size =
        {
            .enable          = TRUE,
            .permission      = RPM_MPU_RGN_AP_RO,
            .execute_disable = TRUE,
        }
    },
};


/*==============================================================================
**
**      Function Definitions
**
**==============================================================================
*/
/*==============================================================================
**
** rpm_mpu_memory_barrier
**
** ensures all subsequence data transfers before this complete and
** instructions after this are fetched from cache or memory.
**
** NOTE:
** - The barrier intrinsics do not implicitly act as a sequence point.
**   It is necessary to insert __schedule_barrier intrinsics either side of the
**   memory barrier intrinsic. It creates a special sequence point that prevents
**   operations with side effects from moving past it under all circumstances.
**
** - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka14552.html
**
**/
static void rpm_mpu_memory_barrier(void)
{
    __schedule_barrier();

    /* Force Memory Writes before continuing */
    __dsb(0xf);

    __schedule_barrier();

    /* Flush and refill pipline */
    __isb(0xf);

    __schedule_barrier();
}

/*==============================================================================
**
** rpm_mpu_enable
**
** enables/disables MPU.
**
**     enable - TRUE to enable MPU,
**              FALSE to disable MPU
**
**/
void rpm_mpu_enable(bool enable)
{
    if(enable)
    {
        SCS.MPU.Ctrl = (RPM_MPU_ENABLE_BG_RGN<<2) | RPM_MPU_ENABLE;

        /*
         * ensure subsequent memory accesses use updated MPU settings.
         */
        rpm_mpu_memory_barrier();
    }
    else
    {
        /*
         * ensure any data transfers complete before disabling MPU
         */
        rpm_mpu_memory_barrier();

        SCS.MPU.Ctrl = 0;
    }
}

/*==============================================================================
**
** rpm_mpu_setup_region
**
** sets up the base address, size, and attributes of the specified MPU region 
** disables the region if its configuration is not defined in rpm_mpu_cfg[].
**
**     rgn_num - an MPU region number
**
**/
static void rpm_mpu_setup_region(int rgn_num)
{
    if(rgn_num < RPM_MPU_RGN_COUNT)
    {
        CORE_VERIFY(rgn_num == rpm_mpu_cfg[rgn_num].rgn_id);

        SCS.MPU.RegionNumber   = rgn_num;
        SCS.MPU.RegionBaseAddr = rpm_mpu_cfg[rgn_num].base_addr;
        SCS.MPU.RegionAttrSize = (rpm_mpu_cfg[rgn_num].attr_size.execute_disable<<28) |
                                 (rpm_mpu_cfg[rgn_num].attr_size.permission<<24) |
                                 (RPM_MPU_RGN_ATTR_SCB<<16) |
                                 (rpm_mpu_cfg[rgn_num].attr_size.sub_rgn_disable<<8) |
                                 (rpm_mpu_cfg[rgn_num].attr_size.size<<1) |
                                 (rpm_mpu_cfg[rgn_num].attr_size.enable);
    }
    else
    {
        SCS.MPU.RegionNumber   = rgn_num;
        SCS.MPU.RegionBaseAddr = 0;
        SCS.MPU.RegionAttrSize = 0;
    }
}

/*==============================================================================
**
** rpm_mpu_enable_region
**
** enables/disables memory protection for the specified region.
**
**     region - an MPU region name enum
**     enable - TRUE to enable protection for the region,
**              FALSE to disable
**
**/
void rpm_mpu_enable_region(rpm_mpu_rgn_num_t region, bool enable)
{
    CORE_VERIFY(region < RPM_MPU_RGN_COUNT);

    rpm_mpu_cfg[region].attr_size.enable = enable;

    rpm_mpu_enable(FALSE);

    rpm_mpu_setup_region(region);

    rpm_mpu_enable(TRUE);
}

/*==============================================================================
**
** rpm_mpu_set_base_addr_and_size
**
** sets the region size based on the size in bytes.
** sets a base address aligned to be a multiple of region size.
** disables sub-regions which are outside the given region if region size > 128B.
**
**      rgn_num             - region number
**      base_addr           - initial base address
**      end_addr            - size of region in bytes
**      base_addr_inclusive - TRUE to ensure the sub-region containing the give base_addr is enabled.
**                            FALSE to disable all sub-regions which base address is lower than the given base_addr 
**      end_addr_inclusive  - TRUE to ensure the sub-region containing the give end_addr is enabled.
**                            FALSE to disable all sub-regions which end address is higher than the given end_addr 
**
** NOTE:
** - It uses the fact that SIZE is the exponent of power of 2 minus 1.
**
**      (Region size in bytes) = 2^(SIZE+1)
**
**   e.g. if size is 7500 bytes, 7500 is < 2^13 and SIZE is 13 - 1 = 12, which is RPM_MPU_RGN_SIZE_8KB.
**
** - The region size must be >= 32B and <= 4GB.
** - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Cihegaib.html
**
**/
__attribute__((section("mpu_dram_reclaim_pool")))
static void rpm_mpu_set_base_addr_and_size(rpm_mpu_rgn_num_t rgn_num, unsigned base_addr, unsigned end_addr, bool base_addr_inclusive, bool end_addr_inclusive)
{
    unsigned size_bytes = end_addr - base_addr;
    unsigned exponent = 31 - __clz(size_bytes);
    unsigned rgn_size_type = 0;
    unsigned aligned_base_addr;
    unsigned aligned_size_bytes;

    CORE_VERIFY((base_addr < end_addr) && (size_bytes >= 32));

    if(size_bytes & ((1<<exponent)-1))
    {
        exponent += 1;
    }

    /*
     * find supported region size and base address which covers the given range
     * NOTE:
     * - The region size MUST be a power of 2
     * - The base address MUST be a multiple of the region size.
     */
    while(TRUE)
    {
        aligned_size_bytes = (1 << exponent);
        aligned_base_addr  = base_addr & ~(aligned_size_bytes - 1);

        if(aligned_base_addr + aligned_size_bytes >= end_addr)
        {
            break;
        }

        CORE_VERIFY(exponent <= RPM_MPU_RGN_SIZE_4GB);

        exponent++;
    }

    CORE_VERIFY((aligned_base_addr % aligned_size_bytes) == 0);

    rgn_size_type = exponent - 1;

    CORE_VERIFY((rgn_size_type >= RPM_MPU_RGN_SIZE_32B) && (rgn_size_type <= RPM_MPU_RGN_SIZE_4GB));

    rpm_mpu_cfg[rgn_num].base_addr      = aligned_base_addr;
    rpm_mpu_cfg[rgn_num].attr_size.size = (rpm_mpu_rgn_size_t)rgn_size_type;

    /*
     * Disable sub-regoins which are outside the given range
     * The sub-region disable bits are Unpredictable for region sizes of 32 bytes, 64 bytes, and 128 bytes.
     */
    if(rgn_size_type > RPM_MPU_RGN_SIZE_128B)
    {
        unsigned sub_rgn_size = aligned_size_bytes / RPM_MPU_NUM_SUB_RGN;
        unsigned sub_rgn_base_addr;
        unsigned sub_rgn_end_addr;
        int sub_rgn_num;

        /*
         * disable sub-regions at lower address than the given base_addr
         */
        sub_rgn_num       = 0;
        sub_rgn_base_addr = aligned_base_addr;

        while((sub_rgn_base_addr < base_addr) && (sub_rgn_num < RPM_MPU_NUM_SUB_RGN))
        {
            if((!base_addr_inclusive) || (sub_rgn_base_addr + sub_rgn_size <= base_addr))
            {
                rpm_mpu_cfg[rgn_num].attr_size.sub_rgn_disable |= (1 << sub_rgn_num);
            }

            sub_rgn_base_addr += sub_rgn_size;
            sub_rgn_num++;
        }

        /*
         * disable sub-regions at higher address than the end address
         */
        sub_rgn_num      = RPM_MPU_NUM_SUB_RGN - 1;
        sub_rgn_end_addr = aligned_base_addr + aligned_size_bytes;

        while((sub_rgn_end_addr > end_addr) && (sub_rgn_num >= 0))
        {
            if((!end_addr_inclusive) || (sub_rgn_end_addr - sub_rgn_size >= end_addr))
            {
                rpm_mpu_cfg[rgn_num].attr_size.sub_rgn_disable |= (1 << sub_rgn_num);
            }

            sub_rgn_end_addr -= sub_rgn_size;
            sub_rgn_num--;
        }

        /*
         * abort if all sub-regions were disabled
         */
        CORE_VERIFY(rpm_mpu_cfg[rgn_num].attr_size.sub_rgn_disable < 0xFF);
    }
}

/*==============================================================================
**
** rpm_mpu_get_effective_base_addr
**
** returns the base address of the given region from which the region permission is
** taken effect.
**
**      rgn_num - region number
**
** RETURN - the effective base address of the given region
**
**/
__attribute__((section("mpu_dram_reclaim_pool")))
static unsigned rpm_mpu_get_effective_base_addr(rpm_mpu_rgn_num_t rgn_num)
{
    unsigned base_addr          = rpm_mpu_cfg[rgn_num].base_addr;
    unsigned rgn_size_bytes     = (1 << (rpm_mpu_cfg[rgn_num].attr_size.size + 1));
    unsigned sub_rgn_size_bytes = rgn_size_bytes / RPM_MPU_NUM_SUB_RGN;
    unsigned sub_rgn_disable    = rpm_mpu_cfg[rgn_num].attr_size.sub_rgn_disable;

    /*
     * find the base address of the lowest sub region which is not disabled
     */
    while(sub_rgn_disable & 0x1)
    {
        base_addr += sub_rgn_size_bytes;
        sub_rgn_disable >>= 1;
    }

    return base_addr;
}

/*==============================================================================
**
** rpm_mpu_cfg_init
**
** sets up the config for MPU regions.
**
** NOTE:
** - Region start address must be a multiple of its size
** - Regions can overlap other regions
** - Region 7 has highest priority, region 0 has lowest priority
** - Attributes of overlapping regions will be set to the attributes of
**   the higher priority region (if overlapping regions enabled)
**
**/
__attribute__((section("mpu_dram_reclaim_pool")))
static void rpm_mpu_cfg_init(void)
{
    unsigned end_addr;
    unsigned base_addr;

    /*
     * region 0 - RPM_MPU_RGN_CODE_RAM
     */
    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_CODE_RAM, (unsigned)Image$$CODE_RAM$$Base, (unsigned)Image$$CODE_RAM_SAVE_END$$Base, TRUE, TRUE);

    /*
     * region 1 - RPM_MPU_RGN_RO_CODE_RAM
     */
    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_RO_CODE_RAM, (unsigned)Image$$CODE_RAM_SAVE$$Base, (unsigned)Image$$CODE_RAM_SAVE_END$$Base, TRUE, TRUE);

    /*
     * region 2 - RPM_MPU_RGN_CODE_RAM_HEAP
     */
    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_CODE_RAM_HEAP, (unsigned)Image$$CODE_RAM_RECLAIM_POOL$$Base, (unsigned)Image$$CODE_RAM_SAVE$$Base, TRUE, TRUE);

    /*
     * region 3 - RPM_MPU_RGN_CODE_RAM_HEAP_BORDER
     */
    base_addr = rpm_mpu_get_effective_base_addr(RPM_MPU_RGN_CODE_RAM_HEAP);
    end_addr  = (unsigned)Image$$CODE_RAM_RECLAIM_POOL$$Base;
    /*
     * make sure the region size is >= 32 bytes which is the smallest region size supported by MPU.
     */
    if(end_addr < base_addr + 32)
    {
        end_addr += 32;
    }

    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_CODE_RAM_HEAP_BORDER, base_addr, end_addr, TRUE, TRUE);

    /*
     * region 4 - RPM_MPU_RGN_DATA_RAM
     */
    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_DATA_RAM, (unsigned)rpm_image_section_array[RPM_DATA_RAM].section_base, (unsigned)rpm_image_section_array[RPM_DATA_RAM].section_end, TRUE, TRUE);

    /*
     * region 5 - RPM_MPU_RGN_STACK_OVERFLOW
     */
    rpm_mpu_set_base_addr_and_size(RPM_MPU_RGN_STACK_OVERFLOW, (unsigned)Image$$STACK_OVERFLOW$$Base, (unsigned)Image$$STACK$$Base, TRUE, TRUE);
}

/*==============================================================================
**
** rpm_mpu_get_num_supported_regions
**
** gets the number of supported MPU regions. 0 if MPU is not present.
**
** RETURN - the number of supported MPU regions
**
**/
__attribute__((section("mpu_dram_reclaim_pool")))
static unsigned rpm_mpu_get_num_supported_regions(void)
{
    return 0xff & (SCS.MPU.Type >> 8);
}

/*==============================================================================
**
** rpm_mpu_init
**
** initializes MPU configs and enables MPU.
**
**/
__attribute__((section("mpu_dram_reclaim_pool")))
void rpm_mpu_init(void)
{
    int i;

    rpm_mpu_num_supported_regions = rpm_mpu_get_num_supported_regions();

    CORE_VERIFY(rpm_mpu_num_supported_regions);
    CORE_VERIFY(RPM_MPU_RGN_COUNT <= rpm_mpu_num_supported_regions);

    rpm_mpu_cfg_init();

    rpm_mpu_enable(FALSE);

    for(i = 0; i < rpm_mpu_num_supported_regions; i++)
    {
        rpm_mpu_setup_region(i);
    }

    rpm_mpu_enable(TRUE);
}

