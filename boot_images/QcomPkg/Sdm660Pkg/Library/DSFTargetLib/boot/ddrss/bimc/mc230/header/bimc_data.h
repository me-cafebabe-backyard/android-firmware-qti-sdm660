/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/bimc/mc230/header/bimc_data.h#4 $
$DateTime: 2018/09/27 20:55:21 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __BIMC_DATA_H__
#define __BIMC_DATA_H__


// lpddrx_geometry_table[][2]:
//  Rows:       DRAM device density
//  Columns:    [Number of rows, Number of columns] for the DRAM density.
extern uint8 lpddr_geometry_table[][2][2];
extern uint16 lpddr_size_table[][2][2];
extern uint16 lpddr_timing_table[][2];
extern uint16 lpddr_timing_table_sdm630[][2];
extern uint8 lpddr_byte_mode_timing_table[][2];

extern uint32 interface_width[];
#endif
