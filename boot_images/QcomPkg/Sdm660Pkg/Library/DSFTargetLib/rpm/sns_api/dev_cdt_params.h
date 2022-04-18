#ifndef __DEV_CDT_PARAMS_H__
#define __DEV_CDT_PARAMS_H__

/*=============================================================================

                                DDR Device CDT PARAMETERS
                                Header File
GENERAL DESCRIPTION
This file defines the DDR paramters that is stored/retrieved from CDT partition


Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/sns_api/dev_cdt_params.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
12/01/13   dp      Initial version.
==============================================================================*/
/*==========================================================================

                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"

/*==============================================================================
                                  TYPES
==============================================================================*/

/**************************/
/*** CDT DDR Parameters ***/
/**************************/

// Information about the DDR devices detected on one BIMC channel
struct detected_ddr_device_params
{
  uint32 manufacture_name;
  uint32 device_type;

  uint32 num_rows_cs0;
  uint32 num_cols_cs0;
  uint32 num_banks_cs0;
  uint32 interface_width_cs0;
  uint32 num_rows_cs1;
  uint32 num_cols_cs1;
  uint32 num_banks_cs1;
  uint32 interface_width_cs1;
  uint32 interleave_en;
  
  uint32 populated_chipselect;
  uint32 reserved_1;
  uint32 reserved_2;
  uint32 reserved_3;
};

struct ddr_device_params_lpddr
{
  /* lpddr specific parameters */
  uint32 tRFC;
  uint32 tRAS_Min;
  uint32 tREFI;
  uint32 tXSR;
  uint32 tXP;
  uint32 tWTR;
  uint32 tRP_AB;
  uint32 tRP_PB;
  uint32 tRRD;
  uint32 tWR;
  uint32 tCKE;
  uint32 tRCD;
  uint32 tFAW;
  uint32 tRTP;
  uint32 tMRR;
  uint32 tMRW;
  uint32 tCKESR;
  uint32 tODTonmax;
  uint32 tODTonmin;
  uint32 tODToffmax;
  uint32 tODToffmin;
  uint32 tDQSCK_min;
  uint32 tDQSCK_max;

  /*lpddr4 params*/
  uint32 tCCDMW;
  uint32 tCKEHCMD;
  uint32 tDQS2DQMIN;
  uint32 tDQS2DQMAX;
  uint32 tZQCAL;
  uint32 tZQLAT;
  uint32 tFC;
  uint32 tVRCG_DISABLE;

  /* reserved lpddr specific fields */
  uint32 reserved_4;
  uint32 reserved_5;
  uint32 reserved_6;
  uint32 reserved_7;
  uint32 reserved_8;
  uint32 reserved_9;
  uint32 reserved_10;
  uint32 reserved_11;
};

struct ddr_device_params_pcddr3
{
  /* PCDDR3 specific parameters */
  uint32 tRFC;
  uint32 tRAS_Min;
  uint32 tREFI;
  uint32 tXSR;
  uint32 tXP;
  uint32 tWTR;
  uint32 tRP_AB;
  uint32 tRRD;
  uint32 tWR;
  uint32 tCKE;
  uint32 tRCD;

  uint32 tFAW;
  uint32 tRTP;
  uint32 tZQoper;
  uint32 tXSDLL;
  uint32 tCKSRE;
  uint32 tCKSRX;
  uint32 tXPDLL;
  uint32 tAOFPD_Min;
  uint32 tAOFPD_Max;
  uint32 tMOD;
  uint32 tAONmax;
  uint32 tAONmin;
  uint32 tMRD;
  uint32 tXS;
  uint32 tDQSCK_min;
  uint32 tDQSCK_max;

  /* reserved pcddr3 specific fields */
  uint32 reserved_4;
  uint32 reserved_5;
  uint32 reserved_6;
  uint32 reserved_7;
  uint32 reserved_8;
  uint32 reserved_9;
  uint32 reserved_10;
  uint32 reserved_11;
};

typedef union
{
  struct ddr_device_params_lpddr  lpddr;
  struct ddr_device_params_pcddr3 pcddr3;
}  ddr_device_params;

#endif /* __DEV_CDT_PARAMS_H__ */
