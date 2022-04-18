/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/bimc/mc230/header/bimc.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __BIMC_H__
#define __BIMC_H__

#include "HALhwio.h"
#include "HAL_SNS_DDR.h"
#include "bimc_seq_hwiobase.h"
#include "bimc_seq_hwioreg.h"
#include "target_config_rpm.h"
#include "bimc_data.h"
#include "bimc_config.h"



// Initialization functions
void BIMC_Config(DDR_STRUCT *ddr);
void BIMC_Memory_Device_Init_Lpddr (DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
boolean BIMC_DDR_Geometry_Detection(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint32 mr8_value);
DDR_CHIPSELECT BIMC_DDR_Topology_Detection(DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
boolean BIMC_Init_Pre_MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel);
boolean BIMC_Init_Post_MCCC_Init_GHS(DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Pre_Init_Setup (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
void BIMC_Program_Lpddr_AC_Parameters(DDR_STRUCT *ddr, DDR_CHANNEL channel);
void BIMC_Post_Init_Setup (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
void BIMC_Memory_Device_Init (DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select, uint8 in_self_refresh);
void BIMC_DDR_Addr_Setup (DDR_STRUCT *ddr, uint8 ch_inx, uint8 rank_index);
uint32 BIMC_DDR_Get_Rank_Base_Addr (DDR_STRUCT *ddr, DDR_CHANNEL ChannelSel, DDR_CHIPSELECT chip_select);
void BIMC_Auto_Refresh_Ctrl (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select, uint8 enable);
void BIMC_Refresh_Rate_Ctrl (DDR_CHANNEL channel, DDR_CHIPSELECT chip_select);


// CA training functions
void BIMC_CA_Training_Entry(uint8 ch, DDR_CHIPSELECT chip_select, uint8 FSP_OP);
void BIMC_CA_Training_Exit_MR (uint8 ch, DDR_CHIPSELECT chip_select, uint8 FSP_OP);
void BIMC_CA_Training_Exit_CKE_ON (uint8 ch, DDR_CHIPSELECT chip_select);
void BIMC_Send_CA_Pattern (uint8 ch, uint8 cs);
void BIMC_write_CA_Pattern (uint32 _inst_, uint8   pattern[3]);
void BIMC_Send_Vref_Data (uint8 ch, uint8 cs, uint8 vref_data_ch_a, uint8 vref_data_ch_b);
void BIMC_CA_Training_Pulse_Ctrl (uint8 ch, uint8 enable);

#endif
