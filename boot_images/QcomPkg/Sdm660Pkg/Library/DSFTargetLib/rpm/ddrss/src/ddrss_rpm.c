/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/src/ddrss_rpm.c#6 $
$DateTime: 2017/03/31 01:29:53 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss_rpm.h"
#include "target_config_rpm.h"


/* Define a neat way to trigger a compile time error based on passed
 * expression evaluating being true or false */
#define COMPILE_TIME_ASSERTION(exp) ((void)sizeof(char[1 - 2*!!((exp)-1)]))




//================================================================================================//
// DDR Software Self Refresh Enter
//================================================================================================//
boolean HAL_DDR_Enter_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   BIMC_Enter_Self_Refresh (ddr, channel, chip_select);

   return TRUE;
}

//================================================================================================//
// DDR Software Self Refresh Exit
//================================================================================================//
boolean HAL_DDR_Exit_Self_Refresh (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   BIMC_Exit_Self_Refresh (ddr, channel, chip_select);

   return TRUE;
}

//================================================================================================//
// Enter Power Collapse
//================================================================================================//
boolean HAL_DDR_Enter_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_POWER_CLPS_MODE collapse_mode, 
                                     uint32 clk_freq_khz)
{
    if(collapse_mode == DDR_POWER_CLPS_MODE_BIMC_ONLY)
    {
        // Put DRAM into self-refresh
        BIMC_Enter_Power_Collapse (ddr, channel);
        
        // Enable clamps.
        ddr_mpm_config_ebi1_freeze_io(1);
        
        // Turn on cfg clock before accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (TRUE);
        
        // Modify band0 performance settings to utilize LPCDC
        DDR_PHY_hal_hpcdc_enable (0);

        // Turn off cfg clock after accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (FALSE);
			
        // Collapse MCCC when you collapse the BIMC
        MCCC_Enter_Power_Collapse(ddr, channel);
    }
    
    if(collapse_mode == DDR_POWER_CLPS_MODE_PHY_ONLY)
    { 
        // Turn on cfg clock before accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (TRUE);

        // Call the DDR PHY Pre collapse routine
        DDR_PHY_rtn_pcc_pre_collapse (ddr, PHY_POWER_CLPS_RESTORE, clk_freq_khz);;      

        // Turn off cfg clock after accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (FALSE);
    }
    
    return TRUE;
}

//================================================================================================//
// Exit Power Collapse
//================================================================================================//
boolean HAL_DDR_Exit_Power_Collapse(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_POWER_CLPS_MODE collapse_mode, 
                                    uint32 clk_freq_khz)
{ 
#if DSF_PERIODIC_TRAINING_EN   
    uint32 chan;
#endif
    
    // Restore MCCC before restoring anything else.  It's OK if you do this twice.
    MCCC_Exit_Power_Collapse(ddr, channel);
		
    if(collapse_mode == DDR_POWER_CLPS_MODE_BIMC_ONLY)
    {
        // Turn on cfg clock before accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (TRUE);
        
        //enable HPCDC master clock
        DDR_PHY_hal_hpcdc_enable (1);     
        
        DDRSS_device_reset_cmd();   // LPDDR4 :Device reset register in DDRSS gets reset during power collapse. 
        
        // Turn off cfg clock after accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (FALSE);
        
        // Disable clamps.
        ddr_mpm_config_ebi1_freeze_io(0);
        
#if DSF_PERIODIC_TRAINING_EN
        // Restore the DTTS PXI control settings that do not get retained during power collapse.
        for (chan = 0; chan < NUM_CH; chan++)
        {
            // Idle pattern when DTTS has the bus.
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_CA_CMD_TABLEn, 16, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 8));
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_CA_CMD_TABLEn, 17, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 9));
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_CA_CMD_TABLEn, 18, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 10));
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_CA_CMD_TABLEn, 19, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 11));
                               
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 12));
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 1, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 13));
                               
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE2_n, 31, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 14));
                               
            // Flag to ensure DTTS Imem and Dmem is loaded correctly.
            HWIO_OUTXI(REG_OFFSET_DTTS(chan), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 15, 
                               HWIO_INXI(REG_OFFSET_DTTS_SRAM(chan), DTTS_SRAM_DTTS_DSRAM_WORDn, 15));
        
        }
#endif
        
        BIMC_Exit_Power_Collapse (ddr, channel);
    }
    if(collapse_mode == DDR_POWER_CLPS_MODE_PHY_ONLY)
    {
        // Turn on continuous GCC clock per channel 
        HWIO_OUTXF2 (REG_OFFSET_DPE(0), DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);
        HWIO_OUTXF (REG_OFFSET_DPE(0), DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

        // Turn on continuous GCC clock per channel 
        HWIO_OUTXF2 (REG_OFFSET_DPE(1), DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x1, 0x1);
        HWIO_OUTXF (REG_OFFSET_DPE(1), DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

        // Turn on cfg clock before accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (TRUE);

        DDR_PHY_rtn_pcc_post_collapse (ddr, PHY_POWER_CLPS_RESTORE, clk_freq_khz);  
        
        // Turn off cfg clock after accessing DDRSS CSRs
        ddr_external_set_ddrss_cfg_clk (FALSE);

        // Turn off continuous GCC clock per channel 
        HWIO_OUTXF2 (REG_OFFSET_DPE(0), DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x0, 0x0);
        HWIO_OUTXF (REG_OFFSET_DPE(0), DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

        // Turn off continuous GCC clock per channel 
        HWIO_OUTXF2 (REG_OFFSET_DPE(1), DPE_CONFIG_6, IOSTAGE_WR_DEBUG_MODE, IOSTAGE_CA_DEBUG_MODE, 0x0, 0x0);
        HWIO_OUTXF (REG_OFFSET_DPE(1), DPE_CONFIG_4, LOAD_ALL_CONFIG, 0x1);

    }
 
   return TRUE;
}

//================================================================================================//
// DDR BHS SW mode enable
//================================================================================================//
boolean HAL_DDR_BHS_SW_Override_Enable(uint8 bhs_broadcast_en, uint8 bhs_staggered_mode_en, uint8 override_val, uint8 override_sel)
{
    if(bhs_broadcast_en == 1){
        DDRSS_BHS_broadcast_override_enable();
    }

    if(bhs_staggered_mode_en == 1){
        DDRSS_BHS_staggered_override_enable(override_val, 0);
        DDRSS_BHS_staggered_override_enable(override_val, override_sel);
    }
    return TRUE;
}

boolean HAL_DDR_BHS_SW_Override_Disable(uint8 expected_ack_val)
{
    DDRSS_BHS_override_disable(expected_ack_val);
    return TRUE;
}


