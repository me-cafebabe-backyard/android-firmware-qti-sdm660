/*==============================================================================
@file DALProps.c

$Header: //components/rel/rpm.bf/1.8/core/dal/framework/sys/src/rpm/DevCfg_Init.c#7 $

Copyright (c) 2010, 2011
Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
==============================================================================*/

#include "DALStdDef.h"
#include "DALStdErr.h"
#include "DALSys.h"
#include "DALPropDef.h"
#include "DALSysCmn.h"
#include <string.h>
#include "CoreVerify.h"
#include "DevConfig.h"
#include "Chipinfo.h"
#include "image_layout.h"



#ifdef MSM8998_IMAGE_LAYOUT
extern const DALPROP_Target_Data DALPROP_Target_Data_8998_xml;

const DALPROP_Target_Data* DALPROP_Target_Data_array[] =
{
    &DALPROP_Target_Data_8998_xml
};
#endif

#ifdef SDM660_IMAGE_LAYOUT
extern const DALPROP_Target_Data DALPROP_Target_Data_660_xml;
extern const DALPROP_Target_Data DALPROP_Target_Data_630_xml;

const DALPROP_Target_Data* DALPROP_Target_Data_array[] =
{
    &DALPROP_Target_Data_660_xml,
    &DALPROP_Target_Data_630_xml,
};
#endif
#ifdef QCS405_IMAGE_LAYOUT
extern const DALPROP_Target_Data DALPROP_Target_Data_405_xml;

const DALPROP_Target_Data* DALPROP_Target_Data_array[] =
{
    &DALPROP_Target_Data_405_xml,
};
#endif

#ifdef SDM_NICOBAR_IMAGE_LAYOUT
extern const DALPROP_Target_Data DALPROP_Target_Data_nicobar_xml;

const DALPROP_Target_Data* DALPROP_Target_Data_array[] =
{
    &DALPROP_Target_Data_nicobar_xml,
};
#endif

const DALPROP_Multi_Target_Data DALPROP_Multi_Target_Data_Instance =
{
    sizeof(DALPROP_Target_Data_array)/sizeof(const DALPROP_Target_Data*),
    DALPROP_Target_Data_array,
};


extern const DALPROP_Multi_Target_Data DALPROP_Multi_Target_Data_Instance;
extern const unsigned DALPROP_Target_Data_array_count;

DALProps DALPROP_PropsInfo;

extern void Add_Heap_Section(char* base, char* limit);

#if 0 // NOTE: This section is merged into DATA_RAM_RECLAIM_POOL section in order to have large consecutive memory space.
extern char Image$$DAL_CONFIG_SECTIONS$$Base[];
extern char Image$$DAL_CONFIG_SECTIONS$$Limit[];
#endif


static inline unsigned get_struct_ptr_index(const DALPROP_Target_Data* target_data, const StringDevice* str_dev)
{
    unsigned dwIdx = ((uint32*)(((uint8*)target_data->prop_bin) + str_dev->dwOffset))[2];

    CORE_VERIFY(dwIdx < (target_data->size_of_DALPROP_StructPtrs/sizeof(target_data->struct_ptrs[0])));

    return dwIdx;
}

/*
 * Since there is no memory left to have two complete set of device config data,
 * we only have device config data for the driver which requires different configs.
 *
 * Replace DeviceConfig pointer with appropriate one.
 *
 * NOTE: Only support DeviceConfig of the drivers which has String names.
 *       The drivers must have DeviceConfig for both targets in order to replace pointer.
 */
__attribute__((section("dal_dram_reclaim_pool")))
static void replace_devcfg_ptr(const DALPROP_Target_Data* dst_target_data, const DALPROP_Target_Data* src_target_data)
{
    unsigned i, j;

    for(i = 0; i < src_target_data->driver_list_count; i++)
    {
        const StringDevice* src_drv = &src_target_data->the_driver_list[i];
        unsigned src_dwIdx = get_struct_ptr_index(src_target_data, src_drv);
        unsigned dst_dwIdx = 0xffffffff;

        /*
         * Find the string device and replace DeviceConfig pointer.
         */
        for(j = 0; j < dst_target_data->driver_list_count; j++)
        {
            const StringDevice* dst_drv = &dst_target_data->the_driver_list[j];

            //if(0 == strcmp(src_drv->pszName, dst_drv->pszName))
            if(src_drv->dwHash == dst_drv->dwHash) // Hash value is calculated for pszName (device string name)
            {
                dst_dwIdx = get_struct_ptr_index(dst_target_data, dst_drv);

                ((const void**)dst_target_data->struct_ptrs)[dst_dwIdx] = src_target_data->struct_ptrs[src_dwIdx];

                break;
            }
        }

        /*
         * The string device in the source target does not exist in the destination/base target.
         */
        CORE_VERIFY(dst_dwIdx != 0xffffffff);
    }
}

__attribute__((section("dal_dram_reclaim_pool")))
void DALSYS_PropsInit(void)
{
    unsigned i;

    const DALPROP_Target_Data* target_data = NULL;
    ChipInfoFamilyType chip_family = Chipinfo_GetFamily();

    //First, find the correct dev config for this target.
	for(i=0; i<DALPROP_Multi_Target_Data_Instance.supported_target_count; i++)
    {
        const DALPROP_Target_Data* cur_target_data = DALPROP_Multi_Target_Data_Instance.supported_targets[i];

        /*
         * CR 977970 - Use 660 DevCfg for 630
         */
        if( (cur_target_data->supported_chipset == chip_family) ||
            ((cur_target_data->supported_chipset == CHIPINFO_FAMILY_SDM660) && (chip_family == CHIPINFO_FAMILY_SDM630)) )
        {
            /*
             * Skip 630 target data since 660 target data is used for 630 chip
            */
            if(cur_target_data->supported_chipset == CHIPINFO_FAMILY_SDM630)
            {
                continue;
            }

            target_data = cur_target_data;
#if  !defined(QCS405_IMAGE_LAYOUT) && !defined(SDM_NICOBAR_IMAGE_LAYOUT)
            /*
             * For 630 chip, use 660 target data and replace 660 DevCfg with 630 DevCfg
             */
            if(chip_family == CHIPINFO_FAMILY_SDM630)
            {
                /*
                 * Replace 660 DevCfg with 630 DevCfg if exists
                 */
				replace_devcfg_ptr(&DALPROP_Target_Data_660_xml, &DALPROP_Target_Data_630_xml);

                /*
                 * Add the 660-specific devcfg section to the heap since it's not needed for 630 chip
                 * NOTE: the common data between 660 and 630 is stored in different devcfg section.
                 */
                rpm_heap_add_section(
                    cur_target_data->section_start,
                    cur_target_data->section_limit,
                    RPM_HEAP_SECTION_PRIORITY_HIGH);    //Add as high priority as this is data ram.
            }
#endif 
       }
        else

			{
            rpm_heap_add_section(
                cur_target_data->section_start,
                cur_target_data->section_limit,
                RPM_HEAP_SECTION_PRIORITY_HIGH);    //Add as high priority as this is data ram.
        }
    }

    CORE_VERIFY(target_data!=NULL);

    CORE_VERIFY_PTR(DALPROP_PropsInfo.pDALPROP_PropBin    = (const byte*)malloc(target_data->size_of_DALPROP_PropBin));
    CORE_VERIFY_PTR(DALPROP_PropsInfo.pDALPROP_StructPtrs = (void *)malloc(target_data->size_of_DALPROP_StructPtrs));
    CORE_VERIFY_PTR(DALPROP_PropsInfo.pDevices            = (StringDevice *)malloc(target_data->driver_list_count * sizeof(StringDevice)));

    DALPROP_PropsInfo.dwDeviceSize = target_data->driver_list_count;

    memcpy((void *)(DALPROP_PropsInfo.pDALPROP_StructPtrs), target_data->struct_ptrs, target_data->size_of_DALPROP_StructPtrs);
    memcpy((void *)(DALPROP_PropsInfo.pDALPROP_PropBin), target_data->prop_bin, target_data->size_of_DALPROP_PropBin);

    //Now copy over the driver list...
    //To do - add asserts etc
    for(i=0; i<target_data->driver_list_count; i++)
    {
        StringDevice* target   = (StringDevice*)&(DALPROP_PropsInfo.pDevices[i]);
        unsigned buffer_length = strlen(target_data->the_driver_list[i].pszName)+1;
        target->pszName = malloc(buffer_length);
        CORE_VERIFY(target->pszName !=NULL );
        strlcpy(target->pszName, target_data->the_driver_list[i].pszName, buffer_length);
        target->dwHash = target_data->the_driver_list[i].dwHash;
        target->dwOffset = target_data->the_driver_list[i].dwOffset;
        target->pFunctionName = target_data->the_driver_list[i].pFunctionName;
        target->dwNumCollision = target_data->the_driver_list[i].dwNumCollision;
        target->pdwCollisions = NULL;
    }

#if 0 // NOTE: This section is merged into DATA_RAM_RECLAIM_POOL section in order to have large consecutive memory space.
    //Now add the devconfig image section back to the heap.
    rpm_heap_add_section(Image$$DAL_CONFIG_SECTIONS$$Base,
                         Image$$DAL_CONFIG_SECTIONS$$Limit,
                         RPM_HEAP_SECTION_PRIORITY_HIGH);    //Add as high priority as this is data ram.
#endif
    
}
