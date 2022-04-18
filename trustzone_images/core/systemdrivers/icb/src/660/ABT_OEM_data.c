/*==============================================================================

FILE:      ABT_OEM_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/icb/src/660/ABT_OEM_data.c#1 $ 
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $
$Change: 22186835 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------  
2017/02/14  sds    Add OEM control of NoC timeout
2016/08/08  kk     Port to sdm660
2015/10/23  pm     Port to 8998
2014/12/09  tb     Created
 
        Copyright (c) 2014 - 2017 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "ABTimeout.h"
#include "ABTimeout_HWIO.h"

/*============================================================================
                      TARGET AND PLATFORM SPECIFIC DATA
============================================================================*/

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/* OEM ABT Configuration Data*/
const ABT_slave_info_type_oem ABT_cfgdata_oem[] = 
{ 
//ABT_SLAVE_INFO_OEM_OEM(name,      sl_en, int_en, to_val)
  ABT_SLAVE_INFO_OEM(CNOC_0_CENTER_LEFT,  TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_0_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_0_NORTH,        TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_0_SOUTH,        TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_1_CENTER_LEFT,  TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_1_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_1_NORTH,        TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_2_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_2_NORTH,        TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_3_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_4_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_5_CENTER_RIGHT, TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_MM,             TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_USB2,           TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(CNOC_USB3,           TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_1,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_2,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_3,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(SNOC_4,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_0,              TRUE,  TRUE,  0xFF), 
  ABT_SLAVE_INFO_OEM(MMSS_1,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_2,              TRUE,  TRUE,  0xFF),
  ABT_SLAVE_INFO_OEM(MMSS_3,              TRUE,  TRUE,  0xFF),
};

/* OEM ABT Configuration Property Data*/
const ABT_propdata_type_oem ABT_propdata_oem =  
{
    /* Length of the OEM config data array */
    sizeof(ABT_cfgdata_oem)/sizeof(ABT_slave_info_type_oem), 
    /* Pointer to OEM config data array */ 
    ABT_cfgdata_oem,
    /* NoC timeout global enable */
    TRUE
};

