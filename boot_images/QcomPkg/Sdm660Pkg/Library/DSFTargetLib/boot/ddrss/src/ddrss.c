/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss.c#16 $
$DateTime: 2018/01/31 04:21:03 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include "dtts_load_ram.h"
#include "target_config.h"


/* Define a neat way to trigger a compile time error based on passed
 * expression evaluating being true or false */
#define COMPILE_TIME_ASSERTION(exp) ((void)sizeof(char[1 - 2*!!((exp)-1)]))


//================================================================================================//
// DDR Initialization
//================================================================================================//
boolean HAL_DDR_Init (DDR_STRUCT *ddr,
                      DDR_CHANNEL channel, 
                      DDR_CHIPSELECT chip_select,
                      uint32 clk_freq_khz)
{
   DDR_CHANNEL ch_1hot = DDR_CH_NONE;
   uint8 ch = 0;
   uint8 in_self_refresh =0;
   uint32 msa_lock_value = 0;
   uint32 protns_lock_value = 0;   
   uint32 lock_value = 0;
   uint32 reg_offset_shke;
   //volatile unsigned int delay = 0x1000;
   EXTENDED_CDT_STRUCT *ecdt;
       
  /* Trigger compile time check to ensure DDR_STRUCT size does not exceed
   * SW allocation of same structure.*/
  COMPILE_TIME_ASSERTION(sizeof(DDR_STRUCT) < 8000 );
  COMPILE_TIME_ASSERTION(sizeof(ddr->cdt_params) < 512 /*Total cdt and eCDT = 1024*/ /*min cdt: 489*/);
  COMPILE_TIME_ASSERTION(sizeof(ddr->extended_cdt_runtime) < 512 /*Total cdt and eCDT = 1024*/ /*min eCDT: 385*/);
  COMPILE_TIME_ASSERTION(sizeof(ddr->flash_params.training_data) < 5001 );
  
  /* Trigger compile time check to ensure local_vars size does not exceed 64KB. */
  COMPILE_TIME_ASSERTION(sizeof(ddrss_rdwr_dqdqs_local_vars) < 65536);
  COMPILE_TIME_ASSERTION(sizeof(ddrss_ca_vref_local_vars) < 65536);
  
   // Fill in the current version numbers for the DDR System Firmware, the BIMC Core and the PHY core.
   ddr->version            = TARGET_DDR_SYSTEM_FIRMWARE_VERSION;
   ddr->rpm_version        = TARGET_DDR_SYSTEM_FIRMWARE_RPM_VERSION;
   ddr->ctlr.version.arch  = TARGET_BIMC_ARCH_VERSION;
   ddr->ctlr.version.major = TARGET_BIMC_CORE_MAJOR_VERSION;
   ddr->ctlr.version.minor = TARGET_BIMC_CORE_MAJOR_VERSION;
   ddr->phy.version.major  = TARGET_PHY_CORE_MAJOR_VERSION;
   ddr->phy.version.minor  = TARGET_PHY_CORE_MAJOR_VERSION;
//#if DSF_ECDT_EN
   ecdt = (EXTENDED_CDT_STRUCT *)((size_t)(ddr->ecdt_input));
//#endif

 
        ddr->misc.bus_width_pch = 16;
   
   // Store our initial DDR frequency
   ddr->misc.current_clk_in_kHz = clk_freq_khz;
   ddr->misc.new_clk_in_kHz = clk_freq_khz;

   // Execute Pre-Init function for workarounds, if any.
   DDRSS_Pre_Init(ddr, ecdt);
   
   if (ddr->misc.target_silicon == 1)
   {
        //Enabling clocks for successful CSR access
        MCCC_Clk_CBCR_Enable(ddr, channel);
   }

   // BIMC one-time settings
   BIMC_Config(ddr);

   if (ddr->misc.target_silicon == 1)
   {
        // Only configure Phy & clock controller on silicon --- they are not included in the emulation build
        // DDR PHY and CC one-time settings
        DDR_PHY_CC_Config(ddr);
   }
   else
   {
        // Byte swizzling for Nazgul emulation is different than on silicon.
        //    Fix that config for emulation.
        HWIO_OUTX(REG_OFFSET_DPE(0), DPE_CONFIG_DQ_MAP, 0x00000000);
        HWIO_OUTX(REG_OFFSET_DPE(1), DPE_CONFIG_DQ_MAP, 0x00000000);
   }
   
   BIMC_Pre_Init_Setup (ddr, channel, chip_select);
    
   if (ddr->misc.target_silicon == 1)
   {
        // Don't configure MCCC or Phy & clock controller on emulation --- they are not included in the HW build
        // Initialize the MCCC
        MCCC_Init(ddr, channel);
		
		DDR_CC_MCCC_Config(ddr);

        DDR_PHY_CC_init (ddr, channel);  //workaround 19.2MHz SW switching hang issue.
       // DDR_PHY_Init_GHS (ddr, channel);
   }

   // IO Calibration workaround for 8996 V1 and V2.
   //   PHY_IO_Cal_Workaround_En_Dis(channel, 1);  // 1 for enable.

  
   
   //detects if we are in self-refresh
   //Changing the condition check only as a workaround. This needs to be reverted once root caused. 
   in_self_refresh = (((HWIO_INXF(REG_OFFSET_SHKE(0), SHKE_DRAM_STATUS, SW_SELF_RFSH)) |
                       (HWIO_INXF(REG_OFFSET_SHKE(1), SHKE_DRAM_STATUS, SW_SELF_RFSH))) |
                      ((HWIO_INXF(REG_OFFSET_SHKE(0), SHKE_DRAM_STATUS, WDOG_SELF_RFSH)) |
                       (HWIO_INXF(REG_OFFSET_SHKE(1), SHKE_DRAM_STATUS, WDOG_SELF_RFSH))));   

   // If it is a warm reset we just need to do a warm-bootup . 
   // 'WDOG_SELF_RFSH' when set indicates that the memory controller is currently in self refresh due to a watchdog reset event
   // and requires a manual 'EXIT_SELF_REFRESH' trigger to exit from the forced self refresh state.
   if ( in_self_refresh == 1) 
   {
      // Disable clamps.
      ddr_mpm_config_ebi1_freeze_io(0);
      // fix done for proper self refresh exit in STARLORD
      for (ch = 0; ch < NUM_CH; ch++)
      {
        reg_offset_shke = REG_OFFSET_SHKE(ch);

        if ((channel >> ch) & 0x1)
        {           
          HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK0_EN, 1);
          HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK0_INITCOMPLETE, 1);
          if (ddr->detected_ddr_device[ch].populated_chipselect & DDR_CS1)
          {
            HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK1_EN, 1);
            HWIO_OUTXF (reg_offset_shke, SHKE_CONFIG, RANK1_INITCOMPLETE, 1);
          }
        }
      }
        
	/* Patch to fix DL mode hang issues  */
    // if (ddr->misc.platform_id == STARLORD_PLATFORM_ID)
	// {  
	/*   while (0 != delay--);
	   delay = 0x1000;
	   HWIO_OUTX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD, 0);
	   while (0 != delay--);
	   delay = 0x1000;
       HWIO_OUTX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD, 1);
	   while (0 != delay--);*/
	// }        
	   
	   ch=0;
       BIMC_Exit_Self_Refresh (ddr, channel, (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
       BIMC_Memory_Device_Init (ddr, ecdt, channel, (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect, in_self_refresh);   		   
   } 
   else 
   {   // If BIMC is not SW_SELF_REFRSH, we need to do a cold boot style init
       //assert and deassert RESET_n pin to reset DRAM device in case lock-up happens inside DRAM after Wdog reset   
       HWIO_OUTX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD, 1);
       BIMC_Memory_Device_Init (ddr, ecdt, channel, chip_select, in_self_refresh);  

       //Topology detection only during cold boot: 
       for (ch = 0; ch < 2; ch++)
       {
           ch_1hot = CH_1HOT(ch);
           
           if ((channel >> ch) & 0x1)
           {
               ddr->detected_ddr_device[ch].populated_chipselect = BIMC_DDR_Topology_Detection (ddr, ch_1hot, chip_select);
           }
       }
   }

   for (ch = 0; ch < 2; ch++)
   {
      ch_1hot = CH_1HOT(ch);

      if ((channel >> ch) & 0x1)
      {
         BIMC_Post_Init_Setup (ddr, ch_1hot, (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
      }
   }
      // Execute Post-Init function for workarounds, if any.
      for (ch = 0; ch < 2; ch++)
   {
      ch_1hot = CH_1HOT(ch);

      if ((channel >> ch) & 0x1)
      {
         DDRSS_Post_Init (ddr, ecdt, ch_1hot, (DDR_CHIPSELECT)ddr->detected_ddr_device[ch].populated_chipselect);
      }
   }
   // CSR locking   
   for (ch = 0; ch < 2; ch++)
   {
      if ((channel >> ch) & 0x1)
      {
         lock_value = (ch ==0) ? 0x00010000 : 0x00020000;
         msa_lock_value = (HWIO_INXF (REG_OFFSET_GLOBAL1, BRIC_GLOBAL1_BRIC_MSA_LOCKS, LOCK )) | lock_value;
         protns_lock_value = (HWIO_INXF (REG_OFFSET_GLOBAL1, BRIC_GLOBAL1_BRIC_PROTNS_LOCKS, LOCK )) | lock_value ; 		 
         HWIO_OUTXF (REG_OFFSET_GLOBAL1, BRIC_GLOBAL1_BRIC_MSA_LOCKS, LOCK, msa_lock_value);
         HWIO_OUTXF (REG_OFFSET_GLOBAL1, BRIC_GLOBAL1_BRIC_PROTNS_LOCKS, LOCK, protns_lock_value); 
      }
   }
   
   return TRUE;
}


//================================================================================================//
// DDR Device Mode Register Read
//================================================================================================//
uint32 HAL_DDR_Read_Mode_Register (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select,
                                   uint32 MR_addr)
{
   return BIMC_MR_Read (channel, chip_select, MR_addr);
}

//================================================================================================//
// DDR Device Mode Register Write
//================================================================================================//
boolean HAL_DDR_Write_Mode_Register (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select,
                                     uint32 MR_addr, uint32 MR_data)
{
   BIMC_MR_Write (channel, chip_select, MR_addr, MR_data);

   return TRUE;
}

//================================================================================================//
// ZQ Calibration
//================================================================================================//
boolean HAL_DDR_ZQ_Calibration (DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
   BIMC_ZQ_Calibration (ddr, channel, chip_select);

   return TRUE;
}


//============================================================================
// HAL_DDR_Enter_Deep_Power_Down
//============================================================================
boolean HAL_DDR_Enter_Deep_Power_Down(DDR_STRUCT *ddr, DDR_CHANNEL channel,
  DDR_CHIPSELECT chip_select)
{
    return(BIMC_Enter_Deep_Power_Down(ddr, channel, chip_select));
}

//============================================================================
// HAL_DDR_Exit_Deep_Power_Down
//============================================================================
boolean HAL_DDR_Exit_Deep_Power_Down(DDR_STRUCT *ddr, DDR_CHANNEL channel,
  DDR_CHIPSELECT chip_select, uint32 clkspeed)
{
    return(BIMC_Exit_Deep_Power_Down(ddr, channel, chip_select));
}

//============================================================================
// HAL_DDR_IOCTL
//============================================================================
boolean HAL_DDR_IOCTL (DDR_STRUCT *ddr, IOCTL_CMD ioctl_cmd, IOCTL_ARG *ioctl_arg)
{
    boolean return_value;

    switch (ioctl_cmd)
    {
        case IOCTL_CMD_GET_CORE_REGISTERS_FOR_CRASH_DEBUG:
            ioctl_arg->result_code = IOCTL_RESULT_COMMAND_NOT_IMPLEMENTED;
            return_value = FALSE;
            break;

        /* For the IOCTL_CMD_GET_HIGHEST_BANK_BITcommand, ioctl_arg->results
           is where this API will write the highest DRAM bank bit. */
        case IOCTL_CMD_GET_HIGHEST_BANK_BIT:
            // Calculate highest DRAM bank bit in the 32-bit system address here.
            // Starting with LSB traveling towards MSB in the system address, we have
            //
            // Byte Address: 1b for x16 device, 2b for x32 device.
            // Remove SA[10] for interleave, assign next set of LSBs for column address bits, which is 10 for LPDDR4 parts supported.
            // Next set of LSBs is bank address, 3 bits.
            // Next set of LSBs is row address.
            //
            // This code assumes total symmetry of geometry across all dies, across all channels.
            // Given that assumption, this API simply resolves to:
            //
            // If interleave is enabled,  SA[15:13] are DRAM BA[2:0] i.e. highest bank address bit is 15. (Channel interleave bit is SA[10]).
            // If interleave is disabled, SA[14:12] are DRAM BA[2:0] i.e. highest bank address bit is 14. (Channel interleave bit is SA[30]).

             ioctl_arg->results = (3 + ddr->detected_ddr_device[0].interleave_en + ddr->detected_ddr_device[0].num_cols_cs0 + (ddr->misc.bus_width_pch/16)) - 1;

            // No need to update ioctl_arg->result_code, since we are returning return_value as TRUE, caller software
            // should ignore result_code.
            // ioctl_arg->result_code = IOCTL_RESULT_COMMAND_NOT_IMPLEMENTED;
            return_value = TRUE;
            break;

        case IOCTL_CMD_TEMP_CTRL_MIN_FREQ:
            ioctl_arg->results = BIMC_Temp_Ctrl_Min_Freq (ddr, DDR_CH_BOTH);

            return_value = TRUE;
            break;

        /* Bad command, return appropriate result code. */
        default:
            ioctl_arg->result_code = IOCTL_RESULT_ILLEGAL_COMMAND;
            return_value = FALSE;
    }

    return return_value;
}


//================================================================================================//
// DDR Post Boot Training Setup.
//================================================================================================//
boolean DDRSS_Post_Boot_Training(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{    

    DDR_CHIPSELECT qualified_cs = (DDR_CHIPSELECT)(chip_select & ddr->detected_ddr_device[0].populated_chipselect);
#if DSF_ECDT_EN
    EXTENDED_CDT_STRUCT *ecdt;
    ecdt = (EXTENDED_CDT_STRUCT *)((size_t)(ddr->ecdt_input));

    // PHY eCDT.
    if(ecdt != NULL)
    {
        DDR_PHY_CC_eCDT_Override(ddr, ecdt, channel); 
    }
#endif    
    // Refresh rate control through TUF bit override
    BIMC_Refresh_Rate_Ctrl (channel, qualified_cs);
    // Enables DownTime requests
    BIMC_Downtime_Request_Ctrl ( channel, 1);
   
    // Add Power Collapse Save mode after training is done.
   
    ddr_printf(DDR_NORMAL, "DDR PHY Power Collapse SAVE\n\n");
       
    // 200MHz is ok to use, since this parameter does not matter for SAVE mode.
    ddr_external_set_clk_speed (200000);
    DDR_PHY_rtn_pcc_pre_collapse (ddr, PHY_POWER_CLPS_SAVE, 200000);
    DDR_PHY_rtn_pcc_post_collapse(ddr, PHY_POWER_CLPS_SAVE, 200000);
    
#if DSF_PERIODIC_TRAINING_EN
    HAL_DDR_Periodic_Training(ddr, channel, chip_select, DDR_TRAINING_MODE_INIT);
#endif // #if DSF_PERIODIC_TRAINING_EN
    
   return TRUE;
}



