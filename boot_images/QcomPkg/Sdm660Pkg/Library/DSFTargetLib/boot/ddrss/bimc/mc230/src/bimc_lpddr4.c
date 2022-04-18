/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/bimc/mc230/src/bimc_lpddr4.c#13 $
$DateTime: 2018/12/26 02:55:51 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc.h"
#include "bimc_rpm.h"

//================================================================================================//
// Geometry Tables
// Number of rows and columns for each device density
//================================================================================================//
uint8   lpddr_geometry_table[][2][2] = {
  
  /* Device_Width x16  |  Device_Width x8  */
  /* nrows, ncols      |  nrows, ncols     */
    {{14,    10},         {15,    10}},  //  4 Gb per die ( 2 Gb per channel)
    {{15,    10},         {16,    10}},  //  6 Gb per die ( 3 Gb per channel)
    {{15,    10},         {16,    10}},  //  8 Gb per die ( 4 Gb per channel)
    {{16,    10},         {17,    10}},  // 12 Gb per die ( 6 Gb per channel)
    {{16,    10},         {17,    10}},  // 16 Gb per die ( 8 Gb per channel)
    {{17,    10},         {17,    10}},  // 24 Gb per die (12 Gb per channel)TODO:value TBD in spec  //Micron 12 Gb ref
    {{0,     0 },         {0,     0 }},  // Reserved
    {{16,    10},         {17,    10}}   // 32 Gb per die (16 Gb per channel)TODO:value TBD in spec
};
uint16   lpddr_size_table[][2][2] = {

/* DDR_WIDTH_PCH(per channel) 
             0=> DDR_WIDTH=16 | 1=> DDR_WIDTH =32       */
  /* size_mb, addr_offset_bit | size_mb, addr_offset_bit*/

  
    {{0x100,       28},          {0x200,       29}},  //  4 Gb per die ( 2 Gb per channel)
    {{0x180,       29},          {0x300,       30}},  //  6 Gb per die ( 3 Gb per channel)
    {{0x200,       29},          {0x400,       30}},  //  8 Gb per die ( 4 Gb per channel)
    {{0x300,       30},          {0x600,       31}},  // 12 Gb per die ( 6 Gb per channel)
    {{0x400,       30},          {0x800,       31}},  // 16 Gb per die ( 8 Gb per channel)
    {{0x600,       31},          {0xc00,       31}},  // 24 Gb per die (12 Gb per channel) TBD as per JEDEC spec
    {{0x800,       31},          {0x1000,      31}}   // 32 Gb per die (16 Gb per channel) TBD as per JEDEC spec
};
uint16   lpddr_timing_table[][2] = {
  /* trfc, txsr in 100ps*/
    {1300, 1375},  //  4 Gb per die ( 2 Gb per channel)
    {1800, 1875},  //  6 Gb per die ( 3 Gb per channel)
    {1800, 1875},  //  8 Gb per die ( 4 Gb per channel)
    {2800, 2875},  // 12 Gb per die ( 6 Gb per channel)
    {2800, 2875},  // 16 Gb per die ( 8 Gb per channel)
    {2800, 2875},  // 24 Gb per die (12 Gb per channel), trfc TBD
    {2800, 2875}   // 32 Gb per die (16 Gb per channel), trfc TBD
};
uint16   lpddr_timing_table_sdm630[][2] = {
  /* trfc, txsr in 100ps*/
    {1300, 1375},  //  4 Gb per die ( 2 Gb per channel)
    {1800, 1875},  //  6 Gb per die ( 3 Gb per channel)
    {1800, 1875},  //  8 Gb per die ( 4 Gb per channel)
    {2800, 2875},  // 12 Gb per die ( 6 Gb per channel)
    {2800, 2875},  // 16 Gb per die ( 8 Gb per channel)
    {3800, 3875},  // 24 Gb per die (12 Gb per channel), trfc TBD //micron 12Gb ref
    {2800, 2875}   // 32 Gb per die (16 Gb per channel), trfc TBD
};
uint8   lpddr_byte_mode_timing_table[][2] = {
  /* tWR, tWTR in 100ps*/
  /* Device_Width x16 | Device_Width x8  */
    {180,               200},  //tWR  
    {  6,                 4},  //tWR_MIN_CYC  
    {100,               120},  //tWTR  
    {  8,                 8}   //tWTR_MIN_CYC  
};
uint32 interface_width[]                        = {16,8};

//================================================================================================//
// Programs the AC Parameters for LPDDR4, during BIMC Pre Init
//================================================================================================//
void BIMC_Program_Lpddr_AC_Parameters(DDR_STRUCT *ddr, DDR_CHANNEL channel)
{
   uint32 reg_offset_dpe  = 0;
   reg_offset_dpe  = REG_OFFSET_DPE(channel);
 
   HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_24, TCCDMW, ddr->cdt_params.lpddr.tCCDMW);
   HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_25, TCKEHCMD, ddr->cdt_params.lpddr.tCKEHCMD);
   HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_29, TDQS2DQMIN, TDQS2DQMAX,
                 ddr->cdt_params.lpddr.tDQS2DQMIN, ddr->cdt_params.lpddr.tDQS2DQMAX);
   HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_30, TZQL, ddr->cdt_params.lpddr.tZQLAT);
   HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_31, TDQSCKMIN, TDQSCKMAX,
                 ddr->cdt_params.lpddr.tDQSCK_min, ddr->cdt_params.lpddr.tDQSCK_max);
   HWIO_OUTXF  (reg_offset_dpe, DPE_DRAM_TIMING_34, TFC, ddr->cdt_params.lpddr.tFC);
   HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_LP4_ODT_ON_CNTL, LP4_ODT_ONMAX, LP4_ODT_ONMIN,
                 ddr->cdt_params.lpddr.tODTonmax, ddr->cdt_params.lpddr.tODTonmin);
   HWIO_OUTXF2 (reg_offset_dpe, DPE_DRAM_TIMING_LP4_ODT_OFF_CNTL, LP4_ODT_OFFMAX, LP4_ODT_OFFMIN,
                 ddr->cdt_params.lpddr.tODToffmax, ddr->cdt_params.lpddr.tODToffmin);
}

//================================================================================================//
// LPDDR4 Device Initialization
// Does device initialization steps of enabling CK and CKE sequentially
//================================================================================================//
void BIMC_Memory_Device_Init_Lpddr (DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel , DDR_CHIPSELECT chip_select)
{
   uint8  ch                     = 0;
   uint8  ch_1hot                = 0;
   uint32 reg_offset_shke        = 0;
 //uint8 cs                      = 0; 
   uint8  soc_odt_override_value = 0;
   

   for (ch = 0; ch < 2; ch++)
   {
      ch_1hot = CH_1HOT(ch);
      reg_offset_shke = REG_OFFSET_SHKE(ch);

      if ((channel >> ch) & 0x1)
      {
         // After RESET_n is deasserted, wait at least tINIT3 before activating CKE.
         // BIMC keeps CKE off at power up. Set CKE off again to trigger DPE timer to satisfy tINIT3
         // Convert tINIT3=2ms to Timer clock cycle (32KHz): 2ms/ 0.03125ms = 64 = 0x40
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_TIMER_CLOCK, 0x40);

         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CKE_OFF, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_OFF));

         //Turn CK on and wait tINIT4=5tck
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_XO_CLOCK, 0x05);

         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CK_ON, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CK_ON));

         // Turn CKE on and then wait tINIT5
         // Convert tINIT5=2us to XO clock cycle (0.052us): 2us/0.052us = 39 (after roundup) = 0x27
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_XO_CLOCK, 0x27);

         HWIO_OUTXF2 (reg_offset_shke, SHKE_DRAM_MANUAL_0, RANK_SEL, CKE_ON, chip_select, 1);
         while (HWIO_INXF (reg_offset_shke, SHKE_DRAM_MANUAL_0, CKE_ON));

         // Reset manual_1 timer
         BIMC_Wait_Timer_Setup ((DDR_CHANNEL)ch_1hot, WAIT_XO_CLOCK, 0x00);
      }
   }

   if (ddr->misc.target_silicon == 1)
   {
      // Enable DBI-WR, DBI-RD/PDDS/PU-CAL/WR_PST are set to default
      //FSP = Settings
      if (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X) // For LP4x apply these settings
      {
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_3, 0xB0); //10  < F <= 400MHz, set MR3[0],PU-CAL=VDDQ/2.5 for fsp0, it was 0xB1(VDDQ/3)
      }
      else // for lp4 device apply these settings
      {
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_3, 0xB0); //10  < F <= 400MHz, set MR3[0],PU-CAL=VDDQ/2.5 for fsp0, it was 0xB1(VDDQ/3)
      }

     // BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, 0x0); //set SOC_ODT to disable for fsp0. it was SOC_ODT=40ohm for FSP=0 



// So, R0 needs to be terminated and R1 should be unterminated
      if(ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X) 
      {
         if(chip_select == DDR_CS_BOTH)
         {
				//If we have byte mode or hybrid mode, make sure there is no double termination 
				if((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_0)) & 0x2) ==0x2)){  //check if device supports byte mode, both ranks return same value if device supports byte mode
					//if both byte mode CS0=0x84, CS1=0xFC
					if( ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x78);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x78);
					}
					//if CS0 is byte mode and CS1 is x16
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x78);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x38);
					}

					//if CS0 is x16 and CS1 is x8
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x78);
					}						
				
				}
			else {
				BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);
				BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x38);
			}
			
		 }
         else if(chip_select == DDR_CS0)
         {
            BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x38);  //FSP-1, SoC ODT = 60ohm, CK/CS/CA = 1 
                                                                   //CK term, CA unterm,CS unterm 
         }
      }
      else
      {
 
            BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, 0x00);  //FSP-1, SoC ODT = 80ohm, CK/CS = 0, CA = 1. Same for LP4 for both ranks 
      }	 	 
      if(ecdt != NULL)
      {
         if(ecdt->extended_cdt_ecdt.dram_soc_odt[0].apply_override == 1)
         {
            soc_odt_override_value = ((0x0 & 0xF8) | ecdt->extended_cdt_ecdt.dram_soc_odt[0].dram_soc_odt);
            BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, soc_odt_override_value);
         }
      }
      // Enable 16 or 32 sequential (on-the-fly) burst length
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_1, 0x06);

    
      // Set CA-Vref
      if (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X)
      {
		 
		 //if (((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_5)) ==SAMSUNG) && ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8))&0x3C)>>2) ==0x6))	//For Samsung 8GB devices
		 if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8))&0x3C)>>2) ==0x6)|| ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8))&0x3C)>>2) ==0x4)) 	//For all 8GB devices(16Gb per die and 32Gb per die)
		 {
			BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x60);//0x5D
		 }
		 else
		 {
			BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x58);//0x5D
		 }
	  }
      else
      {
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x51);
      }    
    
      // Set FSP-WR=1 to write MR11, 12 and 14 values
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_13, 0x40);
    
	
      if (ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X)
      {
		 if (((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_5)) ==0xFF) && ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8))&0x3C)>>2) ==0x3))	//Micron 3GB
		 { 
			BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0xF);//0x5D
		 }
		 else 
		 {
			BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x18);//0x5D
		 }
		 // Set DQ-Vref
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_14, 0x18);
		 // Set ODT
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_11, 0x44);  // was 0x34,, DQ ODT 60Ohm. Level 2: both CK and DQ ODT =80ohm.  
		   
      }
      else
      {
		 // Set CA-Vref 
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x11);
		 // Set DQ-Vref
         BIMC_MR_Write (channel, chip_select, JEDEC_MR_14, 0x11);
		 // Set ODT
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_11, 0x44);  // was 0x34,, DQ ODT 60Ohm. Level 2: both CK and DQ ODT =80ohm.  
      }
     
    
      

      // CA ODT setting based on device type
      // For LP4x , CA ODT doesn't have bond pad. R0 and R1 share the ODT value. 
      // So, R0 needs to be terminated and R1 should be unterminated
      if(ddr->detected_ddr_device[0].device_type == DDR_TYPE_LPDDR4X) 
      {
         if(chip_select == DDR_CS_BOTH)
         {
				//If we have byte mode or hybrid mode, make sure there is no double termination 
				if((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_0)) & 0x2) ==0x2)){  //check if device supports byte mode, both ranks return same value if device supports byte mode
					//if both byte mode CS0=0x84, CS1=0xFC
					if( ((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x84);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x6C);
					}
					//if CS0 is byte mode and CS1 is x16
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x4C);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x24);
					}

					//if CS0 is x16 and CS1 is x8
					if (((((BIMC_MR_Read(channel,DDR_CS0,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x16) && ((((BIMC_MR_Read(channel,DDR_CS1,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8) ){
						BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x24);
						BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x4C);
					}						
			/*		for(cs=0;cs<2;cs++){
						cs_1hot=CH_1HOT(cs);
						if((((BIMC_MR_Read(channel,cs_1hot,JEDEC_MR_8)) & 0xC0)>>6) ==DEVICE_WIDTH_IS_x8){
								//In a hybrid device,
								//for x8 ranks- Disabling one x8 CK, CA, and enabling one x8 CK and CA 
								//and CS ODT is diabled on both x8s, SOC ODT: 60ohm
								BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_22, 0xFC);
						}
						else {
								//In a hybrid device, for x16 rank - Disabling CK, CA, CS ODT, SoC ODT = 60 ohm
								BIMC_MR_Write (channel, cs_1hot, JEDEC_MR_22, 0x3C);
							}
					
					} */
				
				}
			else {
				BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x04);
				BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x2C);
			}
			
		 }
         else if(chip_select == DDR_CS0)
         {
            BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x04);  //FSP-1, SoC ODT = 60ohm, CK/CS/CA = 1 
                                                                   //CK term, CA unterm,CS unterm 
         }
      }
      else
      {
 
            //BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, 0x23);  //FSP-1, SoC ODT = 40ohm, CK/CS = 0, CA = 1. Same for LP4 for both ranks 
			//BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x06);	//CA ODT updated for LP4 
			//BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x2E);	//CA ODT updated for LP4 
			BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x06);	//CA ODT updated for LP4 
			BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x36);	//CA ODT updated for LP4 
      }
      if(ecdt != NULL)
      {
         if(ecdt->extended_cdt_ecdt.dram_soc_odt[1].apply_override == 1)
         {
            soc_odt_override_value = ((0x23 & 0xF8) | ecdt->extended_cdt_ecdt.dram_soc_odt[1].dram_soc_odt);
            BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, soc_odt_override_value);
         }    
      }
   }
   else
   {
      // ddr->misc.target_silicon != 1

      // Use these values to initialize the DDR mode regs for emulation    

      // Comment out the below lines for bringup. DBI-WR will be enabled post
      // bringup. Uncomment it then. Also needs bimc_config.c update to enable DBI-WR
      //// Enable DBI-WR, DBI-RD/PDDS/PU-CAL/WR_PST are set to default
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_3, 0xB1);
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_22, 0x6); //SOC_ODT=40ohm for FSP=0
      
      // Enable 16 or 32 sequential (on-the-fly) burst length
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_1, 0x02);
      
      // Set FSP-WR=1 to write MR11, 12 and 14 values
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_13, 0x40);
      // Set ODT
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_11, 0x23);
      // Set CA-Vref
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_12, 0x18);
      // Set DQ-Vref
      BIMC_MR_Write (channel, chip_select, JEDEC_MR_14, 0x18);
      
      // Force CS0 ODT on when rank0 is in self refresh while the other rank is active
      BIMC_MR_Write (channel, DDR_CS0, JEDEC_MR_22, 0x2E/*0x28*//*0x2B*/);  //set SoC ODT = 80ohm for FSP=1
      // set SoC ODT = 80ohm for rank1
      BIMC_MR_Write (channel, DDR_CS1, JEDEC_MR_22, 0x6 /*0x00*//*0x3*/);  //set SoC ODT = 80ohm for FSP=1   
   }
    
   // Reset FSP-WR=0
   BIMC_MR_Write (channel, chip_select, JEDEC_MR_13, 0x00);
}

