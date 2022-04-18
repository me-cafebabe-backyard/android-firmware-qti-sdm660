/*==============================================================================

FILE:      NOC_error_OEM_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/icb/src/660/NOC_error_OEM_data.c#1 $ 
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $
$Change: 22186835 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2016/08/08  kk     Port to sdm660
2015/12/02  pm     Port to 8998, including Sideband Manager support
2014/12/09  tb     Created
 
        Copyright (c) 2014 - 2016 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "NOC_error.h"
#include "NOC_error_HWIO.h"

/*============================================================================
                           TARGET SPECIFIC DATA
============================================================================*/

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/* OEM NOC Configuration Data*/
const NOCERR_info_type_oem NOCERR_cfgdata_oem[] = 
{ 
//NOCERR_INFO_OEM(name,           intr_en, error_fatal, sb_en_mask)
  NOCERR_INFO_OEM(CNOC,              TRUE, TRUE,        0x0000000F), /* Config NOC */
  NOCERR_INFO_OEM(SNOC,              TRUE, TRUE,        0x0000003F), /* System NOC */
  NOCERR_INFO_OEM(MNOC,              TRUE, TRUE,        0x00000003), /* Multimedia NOC */
  NOCERR_INFO_OEM(A2_NOC_AGGRE2_NOC, TRUE, TRUE,        0x00000001), /* AGGRE2 NOC */
};

const NOCERR_propdata_type_oem NOCERR_propdata_oem =
{
    /* Length of the config data array */
    sizeof(NOCERR_cfgdata_oem)/sizeof(NOCERR_info_type_oem), 
    /* Pointer to OEM config data array */ 
    NOCERR_cfgdata_oem,
};
