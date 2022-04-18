/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/header/bimc_data_rpm.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __BIMC_DATA_RPM_H__
#define __BIMC_DATA_RPM_H__


// MR23 data
extern uint8 MR23_table[];
  
// ODTLon[][2]:
//  Rows:       Frequency band such as 533 < freq <= 800MHz.
//  Columns:    [WPRE_1, WPRE_2] for the frequency band.
extern uint8 ODTLon[][2];


extern uint32 dpe_config_8[];
extern uint32 dpe_timer_3[];
extern uint32 dpe_timing_13[];

// MR13_wrdata[][2]:
//  Rows:       FSP Set
//  Columns:    [MR13_1, MR13_2] to be applied for the FSP set.
extern uint8 MR13_wrdata[][2];

extern struct ecdt_bimc_freq_switch_params_runtime_struct    bimc_freq_switch_params_struct[];
extern struct ecdt_bimc_freq_switch_params_runtime_struct    bimc_freq_switch_params_struct_lp4x[];

extern struct ecdt_dram_latency_runtime_struct               RL_WL_lpddr_struct[];

#endif
