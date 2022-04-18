/*==============================================================================

  HW Event Configuration

DESCRIPTION
  This file has port configurations for trace funnels for a given chipset.

REFERENCES

             Copyright (c) 2016 QUALCOMM Technologies Inc.
                  All Rights Reserved.
                 QUALCOMM Proprietary/GTDR
===========================================================================*/

#include "com_dtypes.h"

typedef struct HWEventRegisterValue_t HWEventRegisterValue;
typedef struct HWEventAddrRange_t HWEventAddrRange;

/*
This structure defines the topology of a funnel configuration.
*/
struct HWEventRegisterValue_t{
   uint32 reg_phys_addr;
   uint32 reg_value;
};

struct HWEventAddrRange_t
{
   uint32 lower_range;
   uint32 higher_range;
   uint32 unlock_value;
};

typedef struct HWEventTableSize_t HWEventTableSize;
struct HWEventTableSize_t {
   uint32 size;
};


const HWEventRegisterValue hwevent_config_table[]={  
{NULL,NULL} /*indicates end of table*/
};


#ifndef HWEVENT_CONFIG_TABLE_SIZE
#define HWEVENT_CONFIG_TABLE_SIZE sizeof(hwevent_config_table)/sizeof(HWEventRegisterValue)
#endif


const HWEventTableSize table_size_array[]={
   {HWEVENT_CONFIG_TABLE_SIZE},
 };

const HWEventAddrRange hwevent_addr_table[]={
{0x15062028,0x15062038,0x0},//LPASS_SCSR_IEC_HWEVENTS_SEL0	[0-3]_ADDR
{0x1570200C,0x1570200C,0x0},
{NULL,NULL,NULL}
};

#define HWEVENT_ADDR_RANGE_TABLE_SIZE  sizeof(hwevent_addr_table)/sizeof(HWEventAddrRange)


const HWEventTableSize addr_range_table_size[]={
   {HWEVENT_ADDR_RANGE_TABLE_SIZE}
 };
