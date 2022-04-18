/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/header/ddrss_rpm.h#8 $
$DateTime: 2017/03/31 01:29:53 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#ifndef __DDRSS_RPM_H__
#define __DDRSS_RPM_H__

#include "HAL_SNS_DDR.h"
#include "ddr_ss_seq_hwioreg.h"
#include "ddr_ss_seq_hwiobase.h"
#include "target_config_rpm.h"


#define NUM_CH                    2 // Number of DDR channels
#define NUM_CS                    2 // Number of ranks (chip selects)
#define NUM_DQ_PCH                2 // Number of DQ PHYs
#define NUM_CA_PCH                1 // Number of CA PHYs Per Channel
#define NUM_PLL                   2 // Number of PLLs in DDRCC
#define NUM_DIE_PCH               ((DSF_DIT_BYTE_MODE_EN == 1) ? 2 : 1)//1  // Number of DRAM Die per Channel


#include "ddrss_training_rpm.h"
#include "bimc_rpm.h"
#include "dtts_load_ram_rpm.h"

#include "ddr_phy_rpm.h"

#include "mccc_rpm.h"
#include "ddr_cc_mccc_rpm.h"

#define CONVERT_CYC_TO_PS        1000000000

#define DDR_PHY_OFFSET           0x1000     // DDR PHY Address offset (4k Bytes)
#define CA0_DDR_PHY_OFFSET       0x0000
#define DQ0_DDR_PHY_OFFSET       0x2000
#define DQ1_DDR_PHY_OFFSET       0x3000
#define DDR_CC_OFFSET            0x6000
#define DDR_CC_MCCC_OFFSET       0xF000

#define REG_OFFSET_DDR_PHY_CH(ch) ((ch == 0)  ? \
                                  DDR_PHY_SS_BASE : \
                                  DDR_PHY_SS_BASE + 0x7000)

#define REG_OFFSET_DDR_CC_CH(ch)  ((ch == 0)  ? \
                                  DDR_PHY_SS_BASE :\
                                  DDR_PHY_SS_BASE )

#define BROADCAST_BASE DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_BROADCAST_SWMAN1_OFFSET

extern uint64 training_address[2][2];

  
void DDRSS_ddr_phy_sw_freq_switch    (DDR_STRUCT *ddr, uint8 ch);
void DDRSS_ddr_phy_sw_freq_switch_PC (DDR_STRUCT *ddr);


void DDRSS_device_reset_cmd(void);

/***************************************************************************************************
 PHY Power Collapse
 ***************************************************************************************************/
void DDR_PHY_DCC_Reset (uint8 ch);

//================================================================================================//
// DDR BHS SW mode enable
//================================================================================================//
boolean HAL_DDR_BHS_SW_Override_Enable(uint8 bhs_broadcast_en, uint8 bhs_staggered_mode_en, uint8 override_val, uint8 override_sel);
boolean HAL_DDR_BHS_SW_Override_Disable(uint8 expected_ack_val);
void DDRSS_BHS_broadcast_override_enable(void);
void DDRSS_BHS_staggered_override_enable(uint8 override_val, uint8 override_sel);
void DDRSS_BHS_override_disable(uint8 expected_ack_val);


#endif /* __DDRSS_RPM_H__ */
 
