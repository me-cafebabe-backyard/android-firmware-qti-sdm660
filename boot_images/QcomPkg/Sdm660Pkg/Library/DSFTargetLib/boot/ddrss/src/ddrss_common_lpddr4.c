/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/boot/ddrss/src/ddrss_common_lpddr4.c#15 $
$DateTime: 2017/11/28 05:32:14 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss.h"
#include "ddr_phy.h"
#include "target_config.h"
#include <string.h>

#if DSF_PXI_TRAINING_EN
   //TABLE DEPTHS
    #define NUM_WR_WDATA 16
    #define NUM_WR_DMDBI 4
    #define NUM_RD_RDATA 16
    #define NUM_PHY_CTRL_PAYLOAD 24
#endif

extern uint8 dq_dbi_bit;

// =============================================================================
// Bit-byte remapping per the bump map. 
// =============================================================================
extern uint8 byte_remapping_table[NUM_CH][NUM_DQ_PCH];
extern uint8 bit_remapping_phy2bimc_DQ[NUM_CH][NUM_DQ_PCH][PINS_PER_PHY];
extern uint8 bit_remapping_bimc2phy_DQ[NUM_CH][NUM_DQ_PCH][PINS_PER_PHY_CONNECTED_NO_DBI];
extern uint8 bit_remapping_bimc2phy_CA[NUM_CH][NUM_CA_PHY_BIT];
     
extern uint8 connected_bit_mapping_no_DBI_A [PINS_PER_PHY_CONNECTED_NO_DBI];
extern uint8 connected_bit_mapping_with_DBI_A [PINS_PER_PHY_CONNECTED_WITH_DBI];
extern uint8 connected_bit_mapping_CA [PINS_PER_PHY_CONNECTED_CA];
extern uint8 connected_bit_mapping_CA_PHY [PINS_PER_PHY_CONNECTED_CA];


uint32 freq_range[6] = {F_RANGE_1, F_RANGE_2, F_RANGE_3, F_RANGE_4, F_RANGE_5, F_RANGE_6}; 

uint8  fail_flag_per_byte[4] = {0};
uint8  fail_flag_per_bit[40] = {0};

uint8  ca_training_pattern_lpddr4[CA_PATTERN_NUM][3] = {
  { 0x00, 0x3F, 0x00 },
  { 0x3F, 0x00, 0x3F },
  { 0x15, 0x2a, 0x15 },
  { 0x2a, 0x15, 0x2a }};
  
uint16 ddr_phy_ca_pcc_link_list[NUM_PHY_PCC_LL] =  
{// Descriptor count = 63, Memory count = 450 (Manual edit for Starlord)
0x8464,	// base descriptor: addr   = 0x60 
0x0381, // sequence descriptor save 3, skip 1
0x0604, // sequence offset repeat 6 
0x85e0, // Sequence Base Address = 0x5df								//0x85df
0x0286, // Sequence descriptor: save = 2, skip = 6
0x0708, // Sequence Offset : repeat = 6									//0x0601
0x8011, // base descriptor: addr   = 0x11 save count = 1
0x0130, // addr descriptor: offset = 0x2f save count = 1			//old value 0x2f		//0x130 also works
0x0133, // addr descriptor: offset = 0x33 save count = 2
0x0037, // addr descriptor: offset = 0x37 save count = 1
0x003b, // addr descriptor: offset = 0x3b save count = 1
0x003d, // addr descriptor: offset = 0x3d save count = 1
0x003f, // addr descriptor: offset = 0x3f save count = 1
0x0041, // addr descriptor: offset = 0x41 save count = 1
0x014b, // addr descriptor: offset = 0x4b save count = 2
//0x004f, // addr descriptor: offset = 0x4f save count = 1
//0x005b, // addr descriptor: offset = 0x5b save count = 1
//0x015d, // addr descriptor: offset = 0x5d save count = 2
0x0060, // addr descriptor: offset = 0x60 save count = 1
0x8092, // base descriptor: addr   = 0x92 save count = 1
0x0001, // addr descriptor: offset = 0x1 save count = 1
0x0108, // addr descriptor: offset = 0x8 save count = 2
0x001e, // addr descriptor: offset = 0x1e save count = 1
0x0026, // addr descriptor: offset = 0x26 save count = 1
0x0229, // addr descriptor: offset = 0x29 save count = 3
0x032e, // addr descriptor: offset = 0x2e save count = 4
//0x0052, // addr descriptor: offset = 0x52 save count = 1
0x0058, // addr descriptor: offset = 0x58 save count = 1
0x0072, // addr descriptor: offset = 0x72 save count = 1
0x0178, // addr descriptor: offset = 0x78 save count = 2
0x812a, // base descriptor: addr   = 0x12a save count = 1
0x0020, // addr descriptor: offset = 0x20 save count = 1
//0x0039, // addr descriptor: offset = 0x39 save count = 1
0x0138, // addr descriptor: offset = 0x39 save count = 2
0x0242, // addr descriptor: offset = 0x42 save count = 3
0x0f4e, // addr descriptor: offset = 0x4e save count = 16
0x1d62, // addr descriptor: offset = 0x62 save count = 30
0x81aa, // base descriptor: addr   = 0x1aa save count = 1
0x2800, // addr descriptor: offset = 0x0 save count = 41
0x0046, // addr descriptor: offset = 0x46 save count = 1
0x0157, // addr descriptor: offset = 0x57 save count = 2
0x015f, // addr descriptor: offset = 0x5f save count = 2
0x824c, // base descriptor: addr   = 0x24c save count = 1
0x0201, // addr descriptor: offset = 0x1 save count = 3
0x1714, // addr descriptor: offset = 0x14 save count = 24
0x8370, // base descriptor: addr   = 0x370 save count = 1
0x0601, // addr descriptor: offset = 0x1 save count = 7
0x0b0c, // addr descriptor: offset = 0xc save count = 12
0x0720, // addr descriptor: offset = 0x20 save count = 8
0x0734, // addr descriptor: offset = 0x34 save count = 8
0x0744, // addr descriptor: offset = 0x44 save count = 8
0x0f54, // addr descriptor: offset = 0x54 save count = 16
0x0070, // addr descriptor: offset = 0x70 save count = 1
0x0074, // addr descriptor: offset = 0x74 save count = 1
0x0276, // addr descriptor: offset = 0x76 save count = 3
0x8444, // base descriptor: addr   = 0x444 save count = 1
0x0601, // addr descriptor: offset = 0x1 save count = 7
0x0714, // addr descriptor: offset = 0x14 save count = 8
//0x3328, // addr descriptor: offset = 0x28 save count = 52 //0x3328
0x1f3c,
0x1f60, // addr descriptor: offset = 0x60 save count = 32						//old value 0x1f60 
0x84e4, // base descriptor: addr   = 0x4e4 save count = 1
0x5e01, // addr descriptor: offset = 0x1 save count = 95
0x85d1, // base descriptor: addr   = 0x5d1 save count = 1
//0x010b, // addr descriptor: offset = 0xb save count = 2
//0x0013, // addr descriptor: offset = 0x13 save count = 1 (Manual add for Starlord)
//0x0147, // addr descriptor: offset = 0x47 save count = 2
0x074b, // addr descriptor: offset = 0x4b save count = 8
//0x0063, // addr descriptor: offset = 0x63 save count = 1
0x0000
};

uint16 ddr_phy_dq_pcc_link_list[NUM_PHY_PCC_LL] =  
{// Descriptor count = 63, Memory count = 449 (Manual modification for Starlord)
 0x8464,	// base descriptor: addr   = 0x60 
0x0381, // sequence descriptor save 3, skip 1
0x0604, // sequence offset repeat 7 
0x85e0, // Sequence Base Address = 0x5df												//0x85df
0x0286, // Sequence descriptor: save = 2, skip = 6
0x0708, // Sequence Offset : repeat = 6													0x0601	
0x8011, // base descriptor: addr   = 0x11 save count = 1
0x0130, // addr descriptor: offset = 0x2f save count = 1			//old value 0x2f			//0x130 also works
0x0133, // addr descriptor: offset = 0x33 save count = 2
0x0037, // addr descriptor: offset = 0x37 save count = 1
0x073b, // addr descriptor: offset = 0x3b save count = 8
0x005b, // addr descriptor: offset = 0x5b save count = 1
0x015d, // addr descriptor: offset = 0x5d save count = 2
0x0060, // addr descriptor: offset = 0x60 save count = 1
0x8092, // base descriptor: addr   = 0x92 save count = 1
0x0001, // addr descriptor: offset = 0x1 save count = 1
0x0108, // addr descriptor: offset = 0x8 save count = 2
0x001e, // addr descriptor: offset = 0x1e save count = 1
0x0026, // addr descriptor: offset = 0x26 save count = 1
0x0229, // addr descriptor: offset = 0x29 save count = 3
0x032e, // addr descriptor: offset = 0x2e save count = 4
//0x0052, // addr descriptor: offset = 0x52 save count = 1
0x0058, // addr descriptor: offset = 0x58 save count = 1
0x0072, // addr descriptor: offset = 0x72 save count = 1
0x0178, // addr descriptor: offset = 0x78 save count = 2
0x8129, // base descriptor: addr   = 0x129 save count = 1
0x0001, // addr descriptor: offset = 0x1 save count = 1
0x001b, // addr descriptor: offset = 0x1b save count = 1
0x0021, // addr descriptor: offset = 0x21 save count = 1
//0x003a, // addr descriptor: offset = 0x3a save count = 1
0x0139, // addr descriptor: offset = 0x3a save count = 2						
0x0243, // addr descriptor: offset = 0x43 save count = 3
0x0f4f, // addr descriptor: offset = 0x4f save count = 16
0x1c63, // addr descriptor: offset = 0x63 save count = 29
0x81a9, // base descriptor: addr   = 0x1a9 save count = 1
0x2900, // addr descriptor: offset = 0x0 save count = 42
0x0047, // addr descriptor: offset = 0x47 save count = 1
0x0257, // addr descriptor: offset = 0x57 save count = 3
0x025b, // addr descriptor: offset = 0x5b save count = 3
0x025f, // addr descriptor: offset = 0x5f save count = 3
0x824c, // base descriptor: addr   = 0x24c save count = 1
0x0201, // addr descriptor: offset = 0x1 save count = 3
0x0f14, // addr descriptor: offset = 0x14 save count = 16
0x0027, // addr descriptor: offset = 0x27 save count = 1
0x8370, // base descriptor: addr   = 0x370 save count = 1
0x0601, // addr descriptor: offset = 0x1 save count = 7
0x000e, // addr descriptor: offset = 0xe save count = 1
0x0710, // addr descriptor: offset = 0x10 save count = 8
0x0720, // addr descriptor: offset = 0x20 save count = 8
0x0734, // addr descriptor: offset = 0x34 save count = 8
0x0744, // addr descriptor: offset = 0x44 save count = 8
0x0f54, // addr descriptor: offset = 0x54 save count = 16
0x0070, // addr descriptor: offset = 0x70 save count = 1
0x0074, // addr descriptor: offset = 0x74 save count = 1
0x0276, // addr descriptor: offset = 0x76 save count = 3
0x8444, // base descriptor: addr   = 0x444 save count = 1
0x0601, // addr descriptor: offset = 0x1 save count = 7
0x0714, // addr descriptor: offset = 0x14 save count = 8
//0x3328, // addr descriptor: offset = 0x28 save count = 52 //0x3328
0x1f3c,
0x1f60, // addr descriptor: offset = 0x60 save count = 32	//covering up to end of cdcext_rd			//old value 0x1f60
0x84e4, // base descriptor: addr   = 0x4e4 save count = 1
0x5e01, // addr descriptor: offset = 0x1 save count = 95
0x85d1, // base descriptor: addr   = 0x5d1 save count = 1
//0x010b, // addr descriptor: offset = 0xb save count = 2
//0x0013, // addr descriptor: offset = 0x13 save count = 1 (manual add for Starlord) FPM_PRFS_1_PWRS_0_HI2_CFG
//0x0147, // addr descriptor: offset = 0x47 save count = 2
0x074b, // addr descriptor: offset = 0x4b save count = 8
//0x0063, // addr descriptor: offset = 0x63 save count = 1
0x0000
};

uint16 ddr_cc_pcc_link_list[NUM_CC_PCC_LL] =  
{// Descriptor count = 49, Memory count = 83
0x83ef, // Sequence Base Address = 0x3ef
0x0183, // Sequence descriptor: save = 1, skip = 3
0x0601, // Sequence Offset : repeat = 6
0x856f, // Sequence Base Address = 0x56f
0x0183, // Sequence descriptor: save = 1, skip = 3
0x0601, // Sequence Offset : repeat = 6
0x832b, // Sequence Base Address = 0x32b
0x0183, // Sequence descriptor: save = 1, skip = 3
0x0501, // Sequence Offset : repeat = 5
0x84ab, // Sequence Base Address = 0x4ab
0x0183, // Sequence descriptor: save = 1, skip = 3
0x0501, // Sequence Offset : repeat = 5
0x8010, // base descriptor: addr   = 0x10 save count = 1
0x0101, // addr descriptor: offset = 0x1 save count = 2
0x0314, // addr descriptor: offset = 0x14 save count = 4
0x031c, // addr descriptor: offset = 0x1c save count = 4
0x0230, // addr descriptor: offset = 0x30 save count = 3
0x0338, // addr descriptor: offset = 0x38 save count = 4
0x0040, // addr descriptor: offset = 0x40 save count = 1
0x8180, // base descriptor: addr   = 0x180 save count = 1
0x0004, // addr descriptor: offset = 0x4 save count = 1
0x0010, // addr descriptor: offset = 0x10 save count = 1
0x0014, // addr descriptor: offset = 0x14 save count = 1
0x8300, // base descriptor: addr   = 0x300 save count = 1
0x0004, // addr descriptor: offset = 0x4 save count = 1
0x0010, // addr descriptor: offset = 0x10 save count = 1
0x001c, // addr descriptor: offset = 0x1c save count = 1
0x006c, // addr descriptor: offset = 0x6c save count = 1
0x8388, // base descriptor: addr   = 0x388 save count = 1
0x0038, // addr descriptor: offset = 0x38 save count = 1
0x003c, // addr descriptor: offset = 0x3c save count = 1
0x8480, // base descriptor: addr   = 0x480 save count = 1
0x0004, // addr descriptor: offset = 0x4 save count = 1
0x0010, // addr descriptor: offset = 0x10 save count = 1
0x001c, // addr descriptor: offset = 0x1c save count = 1
0x006c, // addr descriptor: offset = 0x6c save count = 1
0x8508, // base descriptor: addr   = 0x508 save count = 1
0x0038, // addr descriptor: offset = 0x38 save count = 1
0x003c, // addr descriptor: offset = 0x3c save count = 1
0x8656, // base descriptor: addr   = 0x656 save count = 1
0x0104, // addr descriptor: offset = 0x4 save count = 2
0x000a, // addr descriptor: offset = 0xa save count = 1
0x011a, // addr descriptor: offset = 0x1a save count = 2
0x002d, // addr descriptor: offset = 0x2d save count = 1
0x001f, // addr descriptor: offset = 0x1f save count = 1
0x0050, // addr descriptor: offset = 0x50 save count = 1
0x0154, // addr descriptor: offset = 0x54 save count = 2
0x005c, // addr descriptor: offset = 0x5c save count = 1
0x016a, // addr descriptor: offset = 0x6a save count = 2
0x006f, // addr descriptor: offset = 0x6f save count = 1
0x007d, // addr descriptor: offset = 0x7d save count = 1
0x0000
};  

//----------------------------------------------------------------------------------------------------
// LPDDR4
//----------------------------------------------------------------------------------------------------
#if DSF_PXI_TRAINING_EN

//PXI tables

uint32 prbs_seeds[4] = {0x12345678,
                        0x9abcdef0,
                        0x38274837,
                        0x94827463};

//WR wdata table, 16 entries, 32 bits wide                                        
uint32 wr_wdata_table[NUM_WR_WDATA] = {0x3322115A,
                                        0x77665544,
                                        0xBBAA9988,
                                        0xFFEEDDCC,
                                        0x03020100,
                                        0x07060504,
                                        0x0B0A0908,
                                        0x0F0E0D0C,
                                        0x30201000,
                                        0x70605040,
                                        0xB0A09080,
                                        0xF0E0D0C0,
                                        0x76543210,
                                        0xFEDCBA98,
                                        0x01234567,
                                        0x89ABCDEF}; 
                                            
uint32 wr_wdata_table_dbi[NUM_WR_WDATA] = {0x00000000,
                                            0x11111111,
                                            0x22222222,
                                            0x33333333,
                                            0x44444444,
                                            0x55555555,
                                            0x66666666,
                                            0x88888888,
                                            0x88888888,
                                            0x99999999,
                                            0xAAAAAAAA,
                                            0x44444444,
                                            0xCCCCCCCC,
                                            0x22222222,
                                            0x11111111,
                                            0x00000000}; 

//WR DM/DBI table, 4 entries, 16 bits wide
uint32 wr_dmdbi_table[NUM_WR_DMDBI] = {0x00000000,
                                        0x00000000,
                                        0x00000000,
                                        0x00000000};
                                        
uint32 wr_dmdbi_table_dbi[NUM_WR_DMDBI] = {0x00000000,
                                            0x0000F000,
                                            0x0000F000,
                                            0x0000FFF0};

//RD rdata table, 16 entries, 32 bits wide                                        
uint32 rd_rdata_table_dbi[NUM_RD_RDATA] = {0x00000000,
                                            0x11111111,
                                            0x22222222,
                                            0x33333333,
                                            0x44444444,
                                            0x55555555,
                                            0x66666666,
                                            0x77777777,
                                            0x88888888,
                                            0x99999999,
                                            0xAAAAAAAA,
                                            0xBBBBBBBB,
                                            0xCCCCCCCC,
                                            0xDDDDDDDD,
                                            0xEEEEEEEE,
                                            0xFFFFFFFF}; 



#else

uint64 training_address[2][2] = {{0}};

uint32 write_in_pattern[] __attribute__((aligned(8))) = {
0xDEADBEEF, 0x5A5A5A5A, 0xA5A5A5A5, 0xFEEDFACE, 0xCAFEBABE, 0xA5A5A5A5, 0x5A5A5A5A, 0x0BADF00D, 
0xDEADBEEF, 0x5A5A5A5A, 0xA5A5A5A5, 0xFEEDFACE, 0xCAFEBABE, 0xA5A5A5A5, 0x5A5A5A5A, 0x0BADF00D,
0x22222222, 0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0x0f0f0f0f, 0xf0f0f0f0, 0x00000000, 0xffffffff, 
0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0x0f0f0f0f, 0xf0f0f0f0, 0x00000000, 0xffffffff,
0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 
0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
0x66666666, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 
0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 
0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000,
0x55555555, 0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000, 
0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 
0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808,
0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 
0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 
0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A,
0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A,

0x3789D91E, 0x19E69FC4, 0x484E3BE0, 0xCD6014C4, 0x77D1D4B1, 0xAB30DF90, 0xCB1F041D, 0xFA3D26AB, 
0x63E23084, 0x03DD0851, 0x18577023, 0x913FB1B5, 0xE81D6955, 0xCF7163D4, 0x2A452F75 ,0x01E6629F,
0x797B2280, 0x9ACE7CD7, 0xA06B1A1D, 0xBE79D5DB, 0xEBBFF686, 0x6EBB85FF, 0xBF31749A, 0x29F2E6C7, 
0x8C91AAFC, 0xAB1AAB75, 0xAC48D44E, 0x504C17D0, 0xB1C5B12A, 0xAC329613, 0xBA5D149B ,0x592054F1,
0x753B266D, 0x20944DEB, 0x3220F4C2, 0xDFDF25CD, 0x80D363CB, 0x63EEBF1B, 0x4C1A820C, 0x1E54639A, 
0x127F2554, 0xEB3C2935, 0xCDAAFAEF, 0xC84B4320, 0x2A0B9168, 0xA4CC98BF, 0xF3609880 ,0xD79CAE43,
0x713BB864, 0x72FA35F8, 0x6DED7DF2, 0x23A354E0, 0xCB34F01A, 0xB035D5A0, 0x86C06BD6, 0xEFAB7C43, 
0x74DFBE03, 0xC1E91236, 0x09CAD86F, 0x1C0D78EC, 0xDA6B8136, 0xA18EA81C, 0xEA4D7192 ,0x8B331A3B,
0x81810414, 0xA4555EFD, 0x31722982, 0xFC0E7445, 0x883A76E5, 0x4A9718FF, 0x9577C0A3, 0x49F2D41B, 
0x5D8D9AC4, 0xB48E6E84, 0x4451DBED, 0x0C03D7D7, 0x398540DD, 0xBDC56DB1, 0x29555DDF ,0x47B64FF0,
0x3DF87F32, 0x4697A951, 0x78FFBEF0, 0xA71F8CBD, 0xC449842F, 0x036EDD7C, 0x4E020585, 0xFB39FB64, 
0x4FF1CEC2, 0x7D3A52FB, 0xF8A2D60B, 0x1FD68B15, 0x092A6BD6, 0x2386376D, 0xCCFC9C10 ,0xB8257024,
0xC1A1FDED, 0x186DD915, 0xA0AC5EFE, 0x5363D067, 0x2507A9F2, 0xADD4BC69, 0xFC266ABB, 0x835F251B, 
0x9FA61759, 0x071198C9, 0x1000275A, 0xC7883CC7, 0xF3C7AB76, 0x20E052FD, 0xE3AA85F3 ,0x042B74AA
};

// Size of the array write_in_pattern[] in number of uint32s. This number is supplied to memory read/write functions used during DDR PHY training.
#define DQ_TRAINING_PATTERN_SIZE (sizeof(write_in_pattern) / sizeof(uint32))

#define NUM_FIXED_PATTERNS 22

uint64 fixed_patterns[NUM_FIXED_PATTERNS] =
{
    0x0000000000000000,
    0x0000000000000000,
    0xFF00FF00FF00FF00,
    0x00FF00FF00FF00FF,
    0xF00FF00FF00FF00F,
    0x0FF00FF00FF00FF0,
    0xF0F1F0F1F0F1F0F1,
    0xF1F0F1F0F1F0F1F0,
    0xAA55AA55AA55AA55,
    0x55AA55AA55AA55AA,
    0x5AA55AA55AA55AA5,
    0xA55AA55AA55AA55A,
    0x5A5B5A5B5A5B5A5B,
    0x5B5A5B5A5B5A5B5A,
    0xFE01FE0101FE01FE,
    0xFD02FD0202FD02FD,
    0xFB04FB0404FB04FB,
    0xF708F70808F708F7,
    0xEF10EF1010EF10EF,
    0xDF20DF2020DF20DF,
    0xBF40BF4040BF40BF,
    0x7F807F80807F807F,
};

#define NUM_DESIGN_PATTERNS 2

uint64 design_patterns[NUM_DQ_PCH][NUM_DESIGN_PATTERNS] =
{
    {
        0x0102040810204080,
        0xFEFDFBF7EFDFBF7F,
    },
    {
        0x0102040810204080,
        0xFEFDFBF7EFDFBF7F,
    },
};

uint64 pseudo_random_data_seeds[NUM_DQ_PCH] =
{
    0xFEDCBA9876543210,
    0xFEDCBA9876543210,
};
#endif


//================================================================================================//
// MR write vref value to one die at a time.
//================================================================================================//
void DDRSS_MR_Write_on_die (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 MR_addr, uint8 MR_data,uint8 die)
{ 
    //enabling just the “die”
    HWIO_OUTXF2 ( REG_OFFSET_DPE(ch) , DPE_CONFIG_13, LP4_CHB_DISABLE, LP4_CHA_DISABLE, (1-die), die);
    HWIO_OUTX   ( REG_OFFSET_DPE(ch) , DPE_CONFIG_4 , 1 );//load
    HWIO_OUTX   ( REG_OFFSET_DPE(ch) , DPE_CONFIG_4 , 0 );
    
    BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), MR_addr, MR_data);
    //enabling both die
    HWIO_OUTXF2 ( REG_OFFSET_DPE(ch) , DPE_CONFIG_13 , LP4_CHB_DISABLE, LP4_CHA_DISABLE, 0, 0);
    HWIO_OUTX   ( REG_OFFSET_DPE(ch) , DPE_CONFIG_4 , 1 ); //load
    HWIO_OUTX   ( REG_OFFSET_DPE(ch) , DPE_CONFIG_4 , 0 );
}

#if DSF_PXI_TRAINING_EN
//calculate rd_data_en timing 
void Calculate_RCW_PXI(DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint32 curr_clk_khz)
{
    uint8 phase = 0;
    uint8 byte = 0;
    uint8 table_entry = 0;
    uint8 phase_start_p0 = 0;
    uint8 phase_start_p1 = 0;
    uint8 table_entry_start_p0 = 0;
    uint8 table_entry_start_p1 = 0;
    
    uint8 tdqsck_bimc_delay_p0[4]  = {0};  //4 bytes per beat
    uint8 tdqsck_bimc_delay_p1[4]  = {0};  //4 bytes per beat
    uint8 pxi_table_start_data[4][3][2] = {{{0}}};  //4 bytes per beat, 3 entries per byte, phase
    uint32 pxi_table_entry[3] = {0};  //3 entries per table
    
    uint32 curr_period_ps = 0;
    uint8 rcw_freq_indx = 0;
    
    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
    
    curr_period_ps = CONVERT_CYC_TO_PS / curr_clk_khz;

    for (rcw_freq_indx = 0; rcw_freq_indx < ddr->misc.ddr_num_clock_levels; rcw_freq_indx++)
    { 
        if ((ddr->misc.clock_plan[rcw_freq_indx].clk_freq_in_khz) == curr_clk_khz)
        {
        break;
        }
    }

    for (byte = 0; byte < 4; byte ++)
    {
        tdqsck_bimc_delay_p0[byte] = (training_data_ptr->results.rcw.bimc_tDQSCK[rcw_freq_indx][ch][cs][byte]*100) / curr_period_ps;

        if (curr_clk_khz > 1800000)
        {
            if (tdqsck_bimc_delay_p0[byte] <= 2)
            {
                tdqsck_bimc_delay_p0[byte] = 0;
            }
            else
            {
                tdqsck_bimc_delay_p0[byte] -= 2;
            }
        }
        else if (curr_clk_khz > 1300000)
        {
            if (tdqsck_bimc_delay_p0[byte] <= 1)
            {
                tdqsck_bimc_delay_p0[byte] = 0;
            }
            else
            {
                tdqsck_bimc_delay_p0[byte] -= 1;
            }
        }
		else if (curr_clk_khz > 1200000)
        {
            if (tdqsck_bimc_delay_p0[byte] <= 2)
            {
                tdqsck_bimc_delay_p0[byte] = 0;
            }
            else
            {
                tdqsck_bimc_delay_p0[byte] -= 2;
            }
        }
        else if (curr_clk_khz > 1000000)
        {
            if (tdqsck_bimc_delay_p0[byte] <= 1)
            {
                tdqsck_bimc_delay_p0[byte] = 0;
            }
            else
            {
                tdqsck_bimc_delay_p0[byte] -= 1;
            }
        }

        tdqsck_bimc_delay_p1[byte] = tdqsck_bimc_delay_p0[byte] + 1;
    
        if (tdqsck_bimc_delay_p0[byte] >= 4)
        {  
            pxi_table_start_data[byte][2][0] = 1;
            pxi_table_start_data[byte][2][1] = 1;
        }
        else
        {
            phase_start_p0 = tdqsck_bimc_delay_p0[byte] & 0x00000001;
            phase_start_p1 = tdqsck_bimc_delay_p1[byte] & 0x00000001;
            table_entry_start_p0 = tdqsck_bimc_delay_p0[byte] >> 1;
            table_entry_start_p1 = tdqsck_bimc_delay_p1[byte] >> 1;
            pxi_table_start_data[byte][table_entry_start_p0][phase_start_p0] = 1;
            pxi_table_start_data[byte][table_entry_start_p1][phase_start_p1] = 1;
        }
    }
      
    for (table_entry = 0; table_entry < 3; table_entry++)
    {  
        for (byte = 0; byte < 4; byte++)
        {
            for (phase = 0; phase < 2; phase++)
            {
                pxi_table_entry[table_entry] += (pxi_table_start_data[byte][table_entry][phase] << (byte + 4*phase));
            }
        }
    
        pxi_table_entry[table_entry] = pxi_table_entry[table_entry] << 13;  //rd_data_en = bits 13:20
    }
    
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE1_n, 13, pxi_table_entry[0]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE1_n, 14, pxi_table_entry[1]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE1_n, 15, pxi_table_entry[2]);
          
}

//write PXI table data
void Write_PXI_Table_Data(uint32 base_address, uint32* table_data, uint8 table_depth)
{
    uint8 reg = 0;

    for (reg = 0; reg < table_depth; reg++)
    {
        out_dword(base_address + (reg*4), table_data[reg]);
    }
}

//Fill All PXI tables for PXI Operation, wr_rd = 0 for write, 1 for read, 2 for both
void Initialize_PXI_Tables(DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 wr_rd, uint8 dbi)
{
    uint32 curr_clk_khz = 0;
    curr_clk_khz = ddr->misc.current_clk_in_kHz;

    if (wr_rd == 1 || wr_rd == 2)
    {
        //Fill RD task
        if (dbi)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_TASK_TABLEn, 0, 0x00000100);  //fixed
        }
        else
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_TASK_TABLEn, 0, 0x00000200);  //fixed byte replicate
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_TASK_TABLEn, 1, 0x00002100);  //prbs
        }
  
        //Fill RD rdata
        if (dbi)
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_RD_RDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), rd_rdata_table_dbi, NUM_RD_RDATA);
        }
        else
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_RD_RDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_wdata_table, NUM_RD_RDATA);
        }
    }
    
  if (wr_rd == 0 || wr_rd == 2)
    {
        //Fill WR payload
        if (curr_clk_khz < 300000)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x02119000);
        }
        else if (curr_clk_khz < 1000000)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x0211B000);
        }
        else if (curr_clk_khz < 1100000)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x0211C000);
        }
        else if (curr_clk_khz < 1300000)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x0211D000);
        }
        else if (curr_clk_khz < 1800000)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x0211E000);
        }
        else
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 0, 0x0211F000);
        }

        //Fill WR task
        if (dbi)
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_TASK_TABLEn, 0, 0x00000100);  //fixed
        }
        else
        {
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_TASK_TABLEn, 0, 0x00000200);  //fixed byte replicate
            HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_TASK_TABLEn, 1, 0x00002100);  //prbs
        }

        //Fill WR wdata
        if (dbi)
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_WDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_wdata_table_dbi, NUM_WR_WDATA);
        }
        else
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_WDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_wdata_table, NUM_WR_WDATA);
        }

        //Fill WR DMDBI
        if (dbi)
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_DMDBI_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_dmdbi_table_dbi, NUM_WR_DMDBI);
        }
        else
        {
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_DMDBI_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_dmdbi_table, NUM_WR_DMDBI);
        }
    }
      
    //Fill PHY CTRL payload
    if (curr_clk_khz < 300000)
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x00115000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x07117000);
    }
    else if (curr_clk_khz < 1000000)
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x00117000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x07119000);  // was 0x0711A000
    }
    else if (curr_clk_khz < 1100000)
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x00118000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x0711A000);
    }
    else if (curr_clk_khz < 1300000)
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x00119000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x0711F000);
    }
    else if (curr_clk_khz < 1800000)
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x0011A000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x07121000);
    }
    else
    {
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 0, 0x0011B000);
		HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_PAYLOAD_TABLEn, 10, 0x07125000);
    }

#if DSF_RCW_TRAINING_EN  
    //Fill RCW calculated data
    if (curr_clk_khz > 1000000)
    {
        if (wr_rd == 1 || wr_rd == 2)
        {
            Calculate_RCW_PXI(ddr, ch, cs, curr_clk_khz);
        }
    }
#endif

    //Fill PHY_CTRL_PAT_2
    if (cs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE2_n, 31, 0x10000200);
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_PHY_CTRL_CTL_PATTERN_TABLE2_n, 31, 0x0F800200);
    }
}

#else
//================================================================================================//
// Generate x8 training data from fixed patterns and pseudo-random data seed
// uint64* x8_training_data - pointer to x8 data to create
// uint64* seed_ptr - pointer to seed for pseudo-random data generation
//================================================================================================//
void DDRSS_Generate_x8_Training_Data(uint64* x8_training_data, uint64 seed)
{
    uint8 pattern = 0, index = 0;
    
    // Load fixed patterns
    for(pattern = 0; pattern < NUM_FIXED_PATTERNS; pattern++)
    {
        x8_training_data[index] = fixed_patterns[pattern];
        index++;
    }
    
    // Fill remainder with pseudo-random data
    while(index < (DQ_TRAINING_PATTERN_SIZE / sizeof(uint64)))
    {
        x8_training_data[index] = seed;
        seed = (seed >> 1) ^ (-(seed & (uint64)0x00000001) & (uint64)0xf0f0f0f0f0f0f0f0);
        index++;
    }
}

//================================================================================================//
// Populate training data write buffer
// uint8 x8_training_data[NUM_DQ_PCH][DQ_TRAINING_PATTERN_SIZE] - x8 training data per byte
// uint8 bus_width_pch - width of DDR data bus per channel
//================================================================================================//
void DDRSS_Populate_Write_Buffer(uint8 x8_training_data[NUM_DQ_PCH][DQ_TRAINING_PATTERN_SIZE], uint8 bus_width_pch)
{
    uint8* pBuffer = (uint8*)&write_in_pattern;
    uint8 byte = 0;
    uint16 beat = 0, index = 0;

    // Load x8 training data into write buffer
    for(beat = 0; beat < DQ_TRAINING_PATTERN_SIZE; beat++)
    {
        for(byte = 0; byte < (bus_width_pch / 8); byte++)
        {
            pBuffer[index] = x8_training_data[byte][beat];
            index++;
        }
    }
}

//================================================================================================//
// Generate x8 training data and populate write buffer
// uint8 bus_width_pch - width of DDR data bus per channel
//================================================================================================//
void DDRSS_Create_Training_Data(uint8 bus_width_pch)
{
    uint8 byte = 0, pattern = 0;
    uint8 x8_training_data[NUM_DQ_PCH][DQ_TRAINING_PATTERN_SIZE] = {{0}};
    
    for(byte = 0; byte < (bus_width_pch / 8); byte++)
    {
        // Insert design patterns
        for(pattern = 0; pattern < NUM_DESIGN_PATTERNS; pattern++)
        {
            fixed_patterns[pattern] = design_patterns[byte][pattern];
        }
        
        DDRSS_Generate_x8_Training_Data((uint64*)&x8_training_data[byte], pseudo_random_data_seeds[byte]);
    }
    
    DDRSS_Populate_Write_Buffer(x8_training_data, bus_width_pch);
}
#endif

#if DSF_PXI_TRAINING_EN
//================================================================================================//
// Memory write
//================================================================================================//
void DDRSS_mem_write_PXI (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 dbi, uint8 prbs)
{
    uint32 mr3_read_value    = 0;
    uint32 mr3_write_value   = 0;
    uint32 mr3_mask_value    = 0x7F;
    uint8  curr_params_idx = 0;

    uint32 curr_clk_khz = 0;
    curr_clk_khz = ddr->misc.current_clk_in_kHz;
  
    
    curr_params_idx = BIMC_Freq_Switch_Params_Index (ddr, curr_clk_khz);
    
    if (dbi == 0x0)
    {
        //turn off WR DBI
        mr3_read_value = ddr->extended_cdt_runtime.bimc_freq_switch[curr_params_idx].MR3;
        mr3_write_value = mr3_read_value & mr3_mask_value;
        //channel, ca one-hot
        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_3, mr3_write_value);
    }
    
  HWIO_OUTXF (REG_OFFSET_DTTS(ch), DTTS_CFG_SW_PAYLOAD_START_ADDR, SW_CTRL_PXI_PL_START_ADDR, 0x00);
  
  if (cs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x08001200); //CKE0 high R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x09002000); //Activate - addr0 R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x0B002101); //Write - addr0 R1
    } 
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x00001200); //CKE0 high R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x01002000); //Activate - addr0 R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x03002101); //Write - addr0 R0
    }

    if (prbs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 1, 0x0180001F);  //write PRBS generated data and repeat 31 times
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 1, 0x0080001F);  //write fixed table data and repeat 31 times
    }

    //Fill WR GPREG
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_GPREG_TABLEn, 0, prbs_seeds[0]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_GPREG_TABLEn, 1, prbs_seeds[1]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_GPREG_TABLEn, 2, prbs_seeds[2]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_GPREG_TABLEn, 3, prbs_seeds[3]);
                    
    //request control of bus
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000033);
        
    while (HWIO_INXF (REG_OFFSET_DTTS(ch), DTTS_CFG_DDR_BUS_STATUS , DDR_BUS_ACK) == 0);
    
    //start PXI: CA, WR, PHY_CTRL
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CTL, 0x0000000D);
                                    
    
    //wait for all tables to go idle
    while ((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_STATUS) & 0x0000000F) != 0x0000000F);
    
    //give back control of bus
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000000);
    
    if (dbi == 0x0)
    {
        //turn on WR DBI
        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_3, mr3_read_value);
    }
}

#else
//================================================================================================//
// Memory write
//================================================================================================//
void DDRSS_mem_write (DDR_STRUCT *ddr, uint8 ch, uint8 cs)
{
   ddr_mem_copy (write_in_pattern, (uint32 *)(size_t)training_address[ch][cs], DQ_TRAINING_PATTERN_SIZE, 1);
}
#endif



uint16 DDRSS_dq_remapping (uint8 pattern)
{
    uint8  bit;
    uint16 return_data = 0;    
    uint8  bit_data = 0;
    uint8  byte   = 0;
    uint8 ch = 0;
    
    for (bit = 0; bit < PINS_PER_PHY_CONNECTED_NO_DBI; bit ++)
    {
        bit_data = (pattern >> bit) & 0x1;
        return_data = return_data | (bit_data << bit_remapping_bimc2phy_DQ [ch][byte][bit]);        
    }
    
    return return_data;
}

#if DSF_PXI_TRAINING_EN
//================================================================================================//
// Memory read with results per byte for RD training with Phase.
// This function will do a memory read and report pass/fail per BYTE against the expected pattern
//================================================================================================//
uint8 *DDRSS_mem_read_per_byte_phase_PXI (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq,  uint8 phase, uint8 prbs)
{
    int     word_x          = 0;
    uint8   byte            = 0;
  //uint8   byte_remap      = 0;
    uint32  fail_in_word[3] = {0,0,0};

    uint8  (*fail_flag_per_byte_ptr) = fail_flag_per_byte;

    // Reset fail_flag_per_byte_ptr
    for (byte = 0; byte < dq; byte++)
    {
      fail_flag_per_byte_ptr[byte]  = 0;
    }
    
    HWIO_OUTXF (REG_OFFSET_DTTS(ch), DTTS_CFG_SW_PAYLOAD_START_ADDR, SW_CTRL_PXI_PL_START_ADDR, 0x0A);

    if (cs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x08001200); //CKE0 high R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x09002000); //Activate - addr0 R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x0D002101); //read - addr0 R1
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x00001200); //CKE0 high R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x01002000); //Activate - addr0 R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x05002101); //read - addr0 R0
    }

    if (prbs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 1, 0x0180001F);  //read PRBS generated data and repeat 31 times
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results 
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 1, 0x0080001F);  //read fixed table data and repeat 31 times
    }

    //for (loop = 0; loop < read_test_loop_cnt; loop++)
    //{
        //Fill RD GPREG
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 0, prbs_seeds[0]);
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 1, prbs_seeds[1]);
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 2, prbs_seeds[2]);
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 3, prbs_seeds[3]);
  
        //request control of bus
        HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000033);

        //wait for control to be granted
        while (HWIO_INXF (REG_OFFSET_DTTS(ch), DTTS_CFG_DDR_BUS_STATUS , DDR_BUS_ACK) == 0);

        //start PXI: CA, PHY_CTRL, RD
        HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CTL, 0x0000000B);
        
        //wait for all tables to go idle
        while ((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_STATUS) & 0x0000000F) != 0x0000000F);

        //give back control of bus
        HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000000);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

    if(dq==2)
    {
        for (word_x=0;word_x <4;word_x++)
        {
            fail_in_word[0] |= HWIO_INXI (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_RD_ELOG_TABLE_RD_ONLYn,word_x);
        }
        fail_in_word[1] =   fail_in_word[0];
        fail_in_word[1] =   fail_in_word[1] >> 16;
        fail_in_word[0] =   fail_in_word[1] &  0x0000FFFF;
    }
        }

        // Compare results and return pass/fail per BYTE
       
    fail_in_word[2] =   fail_in_word[1] |  fail_in_word[0];
//=====================================================================================================
    for(byte=0;byte<dq;byte++)
    {
        //byte_remap = byte_remapping_table[ch][byte];
        if(fail_in_word[phase]&0xF)
        {
            //fail_flag_per_byte_ptr[byte_remap]=1;
            fail_flag_per_byte_ptr[byte]=1;
        }
        fail_in_word[phase]=fail_in_word[phase]>>8;
    }
    return (fail_flag_per_byte_ptr);    
}

#else
//================================================================================================//
// Memory read with results per byte for RD training with Phase.
// This function will do a memory read and report pass/fail per BYTE against the expected pattern
//================================================================================================//
//=====================================================================================================
uint8 *DDRSS_mem_read_per_byte_phase     (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 phase)
{
    int     word_x          = 0;
    uint8   byte            = 0;
  //uint8   byte_remap      = 0;
    uint32  fail_in_word[3] = {0,0,0};

//=====================================================================================================
    uint32 read_back_pattern[DQ_TRAINING_PATTERN_SIZE] __attribute__((aligned(8))) =  {0};
    uint8   (*fail_flag_per_byte_ptr) = fail_flag_per_byte;
    for (byte = 0; byte <dq; byte++)
    {
        fail_flag_per_byte_ptr[byte]  = 0;
    }
//=====================================================================================================
    ddr_mem_copy ((uint32 *)(size_t)training_address[ch][cs], read_back_pattern, DQ_TRAINING_PATTERN_SIZE, 1);
//=====================================================================================================

        for (word_x=0;word_x <DQ_TRAINING_PATTERN_SIZE;word_x++)
        {
            fail_in_word[0] |= (uint32) (write_in_pattern[word_x] ^ read_back_pattern[word_x]);
        }
        fail_in_word[1] =   fail_in_word[0];
        fail_in_word[1] =   fail_in_word[1] >> 16;
        fail_in_word[0] =   fail_in_word[0] &  0x0000FFFF;

    fail_in_word[2] =   fail_in_word[1] |  fail_in_word[0];
//=====================================================================================================
    for(byte=0;byte<dq;byte++)
    {
        //byte_remap = byte_remapping_table[ch][byte];
        if(fail_in_word[phase]&0xFF)
        {
            fail_flag_per_byte_ptr[byte]=1;
        }
        fail_in_word[phase]=fail_in_word[phase]>>8;
    }
    return (fail_flag_per_byte_ptr);
} 
//=====================================================================================================


#endif


#if DSF_PXI_TRAINING_EN
//================================================================================================//
// Memory read with results per byte for RD training with Phase.
// This function will do a memory read and report pass/fail per BYTE against the expected pattern
//================================================================================================//
#define PRBS_PATTERN_CNT 8
uint8 *DDRSS_mem_read_per_byte_DBI_phase_PXI (DDR_STRUCT *ddr, uint8 ch, uint8 cs, uint8 read_test_loop_cnt, uint8 phase)
{
    uint32 mask_per_byte   = 0;
    uint32 beat            = 0;
    uint32 compare_pattern = 0;
    uint8  byte            = 0;
    uint8  byte_remap      = 0;
    uint8  loop            = 0;
    uint8  (*fail_flag_per_byte_ptr) = fail_flag_per_byte;
    uint32 temp_pattern    = 0;

    uint8 pattern = 0, index = 0, byte_shft = 0, ones = 0, bit = 0, dbi_signal = 0;
    uint64 seed = 0xFEDCBA9876543210, byte_data = 0, dbi_data = 0;

    // Reset fail_flag_per_byte_ptr
    for (byte = 0; byte < NUM_DQ_PCH; byte++)
    {
      fail_flag_per_byte_ptr[byte]  = 0;
    }
   
    // Use data tables
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_WR_PAYLOAD_TABLEn, 1, 0x00800000);  //write fixed table data
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results 
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 1, 0x00800000);  //read fixed table data

    for (loop = 0; loop < read_test_loop_cnt; loop++)
    {
        for (pattern = 0; pattern < PRBS_PATTERN_CNT; pattern++)
        {
            //request control of bus
            HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000033);

            //wait for control to be granted
            while (HWIO_INXF (REG_OFFSET_DTTS(ch), DTTS_CFG_DDR_BUS_STATUS , DDR_BUS_ACK) == 0);
            
            // update pattern
            index = 0;
            while(index < (sizeof(wr_wdata_table_dbi) / sizeof(uint64)))
            {
                dbi_data = 0;
                dbi_signal = 0;
                
                // Convert from seed to DBI signal and DBI data
                for(byte = 0; byte < 8; byte++)
                {
                    byte_shft = byte * 8;
                    byte_data = (seed >> byte_shft) & 0xFF;
                    
                    ones = 0;
                    for(bit = 0; bit < 8; bit++)
                    {
                        ones += (byte_data >> bit) & 0x1;
                    }
                    
                    if(ones > 4)
                    {
                        dbi_data |= (~byte_data & 0xFF) << byte_shft;
                        dbi_signal |= 1 << byte;
                    }
                    else
                    {
                        dbi_data |= byte_data << byte_shft;
                    }
                }
                
                ((uint64*)wr_wdata_table_dbi)[index] = dbi_data;
                ((uint64*)rd_rdata_table_dbi)[index] = seed;
                ((uint8*)wr_dmdbi_table_dbi)[(4 * (index / 2)) + (index % 2)] = dbi_signal;
                
                // Generate next LFSR64 data
                seed = (seed >> 1) ^ (-(seed & (uint64)0x00000001) & (uint64)0xf0f0f0f0f0f0f0f0);
                index++;
            }
			
			Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_WDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_wdata_table_dbi, NUM_WR_WDATA);
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_WR_DMDBI_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), wr_dmdbi_table_dbi, NUM_WR_DMDBI);
            Write_PXI_Table_Data(HWIO_DTTS_CFG_PXI_RD_RDATA_TABLEn_ADDR(REG_OFFSET_DTTS(ch), 0), rd_rdata_table_dbi, NUM_RD_RDATA);

            if (cs)
            {
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x08001200); //CKE0 high R1
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x09002000); //Activate - addr0 R1
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x0B002101); //Write - addr0 R1
            } 
            else
            {
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x00001200); //CKE0 high R0
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x01002000); //Activate - addr0 R0
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x03002101); //Write - addr0 R0
            }

            // set PHY CTRL payload pointer to write data
            HWIO_OUTXF (REG_OFFSET_DTTS(ch), DTTS_CFG_SW_PAYLOAD_START_ADDR, SW_CTRL_PXI_PL_START_ADDR, 0x00);

            //start PXI: CA, WR, PHY_CTRL
            HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CTL, 0x0000000D);
            
            //wait for all tables to go idle
            while ((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_STATUS) & 0x0000000F) != 0x0000000F);
  
            if (cs)
            {
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x08001200); //CKE0 high R1
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x09002000); //Activate - addr0 R1
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x0D002101); //read - addr0 R1
            }
            else
            {
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x00001200); //CKE0 high R0
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x01002000); //Activate - addr0 R0
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x05002101); //read - addr0 R0
            }

            // set PHY CTRL payload pointer to read data
            HWIO_OUTXF (REG_OFFSET_DTTS(ch), DTTS_CFG_SW_PAYLOAD_START_ADDR, SW_CTRL_PXI_PL_START_ADDR, 0x0A);

            //start PXI: CA, PHY_CTRL, RD
            HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CTL, 0x0000000B);
        
            //wait for all tables to go idle
            while ((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_STATUS) & 0x0000000F) != 0x0000000F);
        
            //give back control of bus
            HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000000);
            
            // modify read payload table to not reset fail data
            if (pattern == 0)
            {
                //rd_payload_table[1] = 0x00800000;
                HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x00000000);  // don't clear error results
            }
        }
        // restore read payload table to reset fail data
        //rd_payload_table[1] = 0x10800000;
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

        for (beat = 0; beat < 4; beat++)
        {
            if ((phase == (beat & 0x1)) || (phase == 0x2))
            {
                // temp_pattern records the position of failed bits
                temp_pattern |= HWIO_INXI (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_RD_ELOG_TABLE_RD_ONLYn,beat);

                mask_per_byte = 0xFF;
                for (byte = 0; byte < NUM_DQ_PCH; byte++)
                {
                    // compare_pattern records the positions where the whole byte is inverted
                    compare_pattern |= (((temp_pattern & mask_per_byte) == mask_per_byte) ? mask_per_byte : 0);
                    mask_per_byte = mask_per_byte << 8;
                }
                // If failure occurs on all bits, jump out of the loop to save time 
                if (compare_pattern == 0xFFFFFFFF)
                    break;
            }
        }

        mask_per_byte = 0xFF;
        for (byte = 0; byte < NUM_DQ_PCH; byte++)
        {
            byte_remap = byte_remapping_table[ch][byte];

            // Only accumulates the specific byte compare results
            fail_flag_per_byte_ptr[byte_remap] |= (((compare_pattern & mask_per_byte) == 0) ? 0 : 1);
            // Mask shift for the next byte
            mask_per_byte = mask_per_byte << 8;
        }
    }
    
    return fail_flag_per_byte_ptr;
}

#else
//================================================================================================//
// Memory read with results per byte for RD training with Phase.
// This function will do a memory read and report pass/fail per BYTE against the expected pattern
//================================================================================================//
uint8 *DDRSS_mem_read_per_byte_DBI_phase (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 phase)
{
  uint32 read_back_pattern[DQ_TRAINING_PATTERN_SIZE] __attribute__((aligned(8))) =  {0};
  
  uint32 mask_per_byte            = 0;
  uint32 compare_mask             = 0;
  uint32 beat                     = 0;
  uint32 compare_pattern          = 0;
  uint8  byte                     = 0;
  uint8  byte_remap               = 0;
  uint32 temp_pattern             = 0;

  uint8  (*fail_flag_per_byte_ptr) = fail_flag_per_byte;

  // Reset fail_flag_per_byte_ptr
  for (byte = 0; byte < dq; byte++)
  {
     fail_flag_per_byte_ptr[byte]  = 0;
  }

  //ddr_mem_read 
  ddr_mem_copy ((uint32 *)(size_t)training_address[ch][cs], read_back_pattern, DQ_TRAINING_PATTERN_SIZE, 1);
  
  // Default compare mask for phase == 2 (both phases)
  compare_mask = 0xFFFFFFFF;
  
  // Set compare mask for phase
  if (phase == 0x0)
  {            
    compare_mask = 0x0000FFFF;
  }
  else if (phase == 0x1)
  {
    compare_mask = 0xFFFF0000;
  }
  
  // Compare each beat for pass/fail
  for (beat = 0; beat < DQ_TRAINING_PATTERN_SIZE; beat++)
  {        
    // temp_pattern records the position of failed bits
    temp_pattern = (read_back_pattern[beat] ^ write_in_pattern[beat]) & compare_mask;// & global_bit_mask;       
    
    // Set up a moving byte size mask
    mask_per_byte            = 0xFF;
    
    // only count failures where the whole byte is inverted
    for (byte = 0; byte < sizeof(uint32); byte++)
    {
      // compare_pattern records the positions where the whole byte is inverted
      compare_pattern |= (((temp_pattern & mask_per_byte) == mask_per_byte) ? mask_per_byte : 0);
      mask_per_byte = mask_per_byte << 8;
    }
    
    // If failure occurs on all bytes, jump out of the loop to save time
    if ((compare_pattern != 0) && (compare_pattern == compare_mask))
    break;  
  }     
  
  // Set up a mask for Phase 0 and Phase 1 bytes  
  mask_per_byte            = 0x00FF00FF;    
       
  for (byte = 0; byte < sizeof(uint32); byte++)
  {
     byte_remap = byte_remapping_table[ch][byte];
  
     // Only accumulates the specific byte compare results
     fail_flag_per_byte_ptr[byte_remap] |= (((compare_pattern & mask_per_byte) == 0) ? 0 : 1);
     // Mask shift for the next byte
     mask_per_byte = mask_per_byte << 8;
  }    

  return fail_flag_per_byte_ptr;
}

#endif

#if DSF_PXI_TRAINING_EN
//================================================================================================//
// Memory read with results per bit
// This function will do a memory read and report pass/fail per BIT against the expected pattern
//================================================================================================//

uint32 DDRSS_mem_read_per_bit_phase_PXI    (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY], uint8 phase, uint8 prbs)
{
    int     word_x          = 0;
    uint8   byte            = 0;
    uint8   bit_x           = 0;
    uint8   remapped_bit_x  = 0;
    uint32  fail_in_word[3] = {0,0,0};


    HWIO_OUTXF (REG_OFFSET_DTTS(ch), DTTS_CFG_SW_PAYLOAD_START_ADDR, SW_CTRL_PXI_PL_START_ADDR, 0x0A);

    if (cs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x08001200); //CKE0 high R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x09002000); //Activate - addr0 R1
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x0D002101); //read - addr0 R1
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 0, 0x00001200); //CKE0 high R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 1, 0x01002000); //Activate - addr0 R0
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CA_TASK_TABLEn, 2, 0x05002101); //read - addr0 R0
    }

    if (prbs)
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 1, 0x0180001F);  //read PRBS generated data and repeat 31 times
    }
    else
    {
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 0, 0x10000000);  //clear error results 
        HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_PAYLOAD_TABLEn, 1, 0x0080001F);  //read fixed table data and repeat 31 times
    }

    //Fill RD GPREG
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 0, prbs_seeds[0]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 1, prbs_seeds[1]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 2, prbs_seeds[2]);
    HWIO_OUTXI (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_RD_GPREG_TABLEn, 3, prbs_seeds[3]);
    //request control of bus
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000033);
    //wait for control to be granted
    while (HWIO_INXF (REG_OFFSET_DTTS(ch), DTTS_CFG_DDR_BUS_STATUS , DDR_BUS_ACK) == 0);
    //start PXI: CA, PHY_CTRL, RD
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_PXI_CTL, 0x0000000B);
    //wait for all tables to go idle
    while ((HWIO_INX (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_STATUS) & 0x0000000F) != 0x0000000F);
    //give back control of bus
    HWIO_OUTX (REG_OFFSET_DTTS(ch), DTTS_CFG_DTTS_DDR_BUS_REQ_CTL, 0x00000000);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

        for (word_x=0;word_x <4;word_x++)// 4 => pattern size
        {
            fail_in_word[0] |= HWIO_INXI (REG_OFFSET_DTTS(ch),DTTS_CFG_PXI_RD_ELOG_TABLE_RD_ONLYn,word_x);
        }//for
        fail_in_word[1] =   fail_in_word[0];
        fail_in_word[1] =   fail_in_word[1] >> 16;
        fail_in_word[0] =   fail_in_word[1] &  0x0000FFFF;

    fail_in_word[2] =   fail_in_word[1] |  fail_in_word[0];
    //====================================================================================================
    for(byte=0;byte<dq;byte++)
    {
        for(bit_x=0 ; bit_x < BYTE_SIZE ; bit_x++)
        {
            remapped_bit_x = bit_remapping_bimc2phy_DQ[ch][byte][bit_x];
            if(  fail_in_word[phase]  & 0x1)
            {
                compare_result_acc[byte][remapped_bit_x]++;
            }//if
            fail_in_word[phase]=fail_in_word[phase]>>1;
        }//bit_x
    }//byte
    //=====================================================================================================
  return (1);
}

#else
//================================================================================================//
// Memory read with results per bit
// This function will do a memory read and report pass/fail per BIT against the expected pattern
//================================================================================================//
uint32 DDRSS_mem_read_per_bit_phase        (DDR_STRUCT *ddr, uint8 ch, uint8 cs, PHY_BUS dq, uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY], uint8 phase)
{
    int    word_x            = 0;
    uint8    byte            = 0;
    uint8    bit_x           = 0;
    uint8    remapped_bit_x  = 0;
    uint32   fail_in_word[3] = {0,0,0};
    uint32 read_back_pattern[DQ_TRAINING_PATTERN_SIZE] __attribute__((aligned(8))) =  {0};
    //=====================================================================================================
    ddr_mem_copy ((uint32 *)(size_t)training_address[ch][cs], read_back_pattern, DQ_TRAINING_PATTERN_SIZE, 1);
    //=====================================================================================================

        for (word_x=0;word_x <DQ_TRAINING_PATTERN_SIZE;word_x++)
        {
            fail_in_word[0] |= write_in_pattern[word_x] ^ read_back_pattern[word_x];
        }//for
        fail_in_word[1] =   fail_in_word[0];
        fail_in_word[1] =   fail_in_word[1] >> 16;
        fail_in_word[0] =   fail_in_word[0] &  0x0000FFFF;

    fail_in_word[2] =   fail_in_word[1] |  fail_in_word[0];
    //====================================================================================================
    for(byte=0;byte<dq;byte++)
    {
        for(bit_x=0 ; bit_x < BYTE_SIZE ; bit_x++)
        {
            remapped_bit_x = bit_remapping_bimc2phy_DQ[ch][byte][bit_x];
            if(  fail_in_word[phase]  & 0x1)
            {
                compare_result_acc[byte][remapped_bit_x]++;
            }//if
            fail_in_word[phase]=fail_in_word[phase]>>1;
        }//bit_x
    }//byte
    //=====================================================================================================
  return (1);
} 
//=====================================================================================================

#endif

void DDRSS_rd_dqdqs_dcc_schmoo (DDR_STRUCT *ddr, 
                                uint8 ch, 
                                uint8 cs, 
                                PHY_BUS dq,
                                training_params_t *training_params_ptr, 
                                ddrss_rdwr_dqdqs_local_vars *local_vars,
                                uint32 clk_freq_khz)
{
    uint8  byte_lane                   = 0;
    uint32 dq0_ddr_phy_base            = 0;
    uint8  bit                         = 0;
    uint8  phase                       = 0;
    uint8  index                       = 0;
    uint8  flow_ctl                    = 0;  
    uint8  loopcnt                     = 0;  
    uint8  coarse_cdc_value            = 0; 
    uint8  fine_cdc_value              = 0; 
    uint8  coarse_cdc_max_value        = 8; 
    uint8  full_cycle_steps            = 0;
    uint8 *compare_result;  
    uint8  sign                        = 0; 
    
    uint8 dcc_ctl[NUM_DQ_PCH]                     = {0};   
    uint8 start  [NUM_DQ_PCH]                     = {0};   
    uint8 direction[NUM_DQ_PCH]                   = {0};   
    uint8 byte_done[NUM_DQ_PCH]                   = {0};   
    uint8 byte_pass[PHASE][NUM_DQ_PCH]            = {{0}};   
    uint8 compare_result_byte[PHASE][NUM_DQ_PCH]  = {{0}};
    uint8 rd_left_edge_coarse[NUM_DQ_PCH]         = {0};

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Set DQ0 base for addressing
    dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
                
    full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
    coarse_cdc_max_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;
                
    // Initialize the fail flag, best cdc, coarse and fine 
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Zero out the coarse and fine CDC values before training
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 0, 1, 1, cs);
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 0, 0, 1, cs);            
    }
    
    // Set all local vref to (max+min)/2 and perbit to 0xF
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {        
        for(bit = 0; bit < PINS_PER_PHY; bit++)
        {
            DDR_PHY_hal_cfg_local_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                        LOCAL_VREF_MID_VALUE,
                                        cs, 
                                        bit);
            training_data_ptr->results.rd_dqdqs.perbit_vref [ch][cs][byte_lane][bit] = LOCAL_VREF_MID_VALUE;
        }
    }    

    // Search for the left passing edge of the eye
    DDRSS_RD_left_edge_search (ddr, 
                               ch, 
                               cs, 
                               dq,
                               training_data_ptr,
                               training_params_ptr,
                               rd_left_edge_coarse,
                                   clk_freq_khz);       
    //RD Perbit Training
    DDRSS_rd_dqdqs_perbit (ddr, 
                     ch, 
                     cs, 
                     dq,
                     training_params_ptr, 
                     local_vars,
                     rd_left_edge_coarse,
                     clk_freq_khz);


    //  Phase 0 smaller than Phase 1
    //  Advance the negative edge to equalize the phases
    //
    //            FFFFFP          FFFFFP
    //         __ --->|        __ --->|  
    //  DQS   |  |____________|  |_______
    //         ___________________________ 
    //  DQ    X_______X_______X_______X____
    //  Phase     0       1       0       
   
         
    //  Phase 0 larger than Phase 1
    //  Advance the positive edge to equalize the phases
    //  
    //        FFFFFP          FFFFFP
    //         ___________     ___________
    //  DQS   |           |___|           |__
    //        --->            --->
    //        ____ ___________________________ 
    //  DQ    ____X_______X_______X_______X____
    //  Phase         0       1       0       
  

    // Set the RD CDC Coarse to the left edge and the Fine = 0
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
      DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                //rd_left_edge_coarse[byte_lane], 
                                  0, 
                                  0x1,  // 1 for coarse_delay
                                  0x1, 
                                  cs);   
 
      DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                  0, 
                                  0x0, // 0 for fine_delay
                                  0x1, 
                                  cs);  
                                  
      // Initialize the RD DQS DCC
      HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                 DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                 DCC_CTL, 
                 0);                                  
    }
	
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables (ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
#endif

    // Determine the first pass for each phase, adjust DQS DCC 
    while (flow_ctl == 0)
    {
      // Set background pattern in the dcc histogram to max_fail + 1
      memset(local_vars->coarse_schmoo.coarse_dq_dcc_info, 
             training_params_ptr->rd_dqdqs.max_loopcnt + 1, 
             NUM_DQ_PCH * NUM_CS * RX_DCC);
      
      // Initialize the DCC result scoreboard
      for (phase = 0; phase < PHASE; phase++)
      {
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {                              
           byte_pass[phase][byte_lane] = 0xFF;
        }
      }                 
                  
      //Phase loops                 
      for (phase = 0; phase < PHASE; phase++)
      {
        // CDC Schmoo loop
        for(coarse_cdc_value  = training_params_ptr->rd_dqdqs.coarse_cdc_start_value; 
            coarse_cdc_value <= coarse_cdc_max_value;
            coarse_cdc_value += training_params_ptr->rd_dqdqs.coarse_cdc_step)
        {
          for(fine_cdc_value = training_params_ptr->rd_dqdqs.fine_cdc_start_value; 
              fine_cdc_value < FINE_STEPS_PER_COARSE; 
              fine_cdc_value += training_params_ptr->rd_dqdqs.fine_cdc_step)
          {
            // Update RD CDC
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
              DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                            coarse_cdc_value, 
                                            0x1, 
                                            0x1, 
                                            cs);   
      
              DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                            fine_cdc_value, 
                                            0x0, 
                                            0x1, 
                                            cs);   // 0 for fine_delay_mode. 
                                                                                                                                                                  
              compare_result_byte[phase][byte_lane] = 0;
            }
            
            index = ((coarse_cdc_value * FINE_STEPS_PER_COARSE) + fine_cdc_value);
            
            // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.
            for (loopcnt = 0;loopcnt < training_params_ptr->rd_dqdqs.max_loopcnt ; loopcnt++) 
            {
#if DSF_PXI_TRAINING_EN
            compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, phase, 1);    //ddr, ch, cs, dq, phase, prbs    
#else
            compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, phase);       //ddr, ch, cs, dq, phase
#endif
                   
            // Accumulate the compare results per byte
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
                compare_result_byte[phase][byte_lane] += compare_result[byte_lane];
            }
          }
          
          for(byte_lane = 0; byte_lane < dq; byte_lane++)
          { 
            // If fail, increment error_count.
            local_vars->coarse_schmoo.coarse_dq_clk_dcc_info[byte_lane][cs][phase][index] = 
                        compare_result_byte[phase][byte_lane];
            if ((compare_result_byte[phase][byte_lane] == 0) && (index < byte_pass[phase][byte_lane]))
            {
              byte_pass[phase][byte_lane] = index;
            }                                                                    
          } // byte_lane                                                
        } // fine_cdc_value.
      } // CDC_LOOP      
    } //phase loop
          
    // Increment the RD DQS DCC until the phases start at the same boundary
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
      if (((start[byte_lane] == 0) || (direction[byte_lane] == 1)) && 
          (byte_pass[0][byte_lane] < byte_pass[1][byte_lane])      &&
          (byte_done[byte_lane] == 0))
      {
        start[byte_lane]     = 1;
        direction[byte_lane] = 1;
        
        if (dcc_ctl[byte_lane] == (RX_DCC-1))
        {
          flow_ctl++;
        }
        else
        {
          dcc_ctl[byte_lane]++;
        }
        
        // Set the RD DCC
        HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                    DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                    DCC_CTL, 
                    dcc_ctl[byte_lane]<<4);
 
        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][cs][byte_lane] = dcc_ctl[byte_lane]<<4;
      }
      else if (((start[byte_lane] == 0) || (direction[byte_lane] == 2)) && 
                (byte_pass[0][byte_lane] > byte_pass[1][byte_lane])     &&
                (byte_done[byte_lane] == 0))                                                            
      {
        start[byte_lane]     = 1;
        direction[byte_lane] = 2;
        
        if (dcc_ctl[byte_lane] == (RX_DCC-1))
        {
          flow_ctl++;
        }
        else
        {
          dcc_ctl[byte_lane]++;
        }

        // Set the RD DCC
        HWIO_OUTXF((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                    DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                    DCC_CTL, 
                    dcc_ctl[byte_lane]);

        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][cs][byte_lane] = dcc_ctl[byte_lane];
      }
      else
      {
        byte_done[byte_lane] = 1;
        if ((byte_done[0] + byte_done[1]) == NUM_DQ_PCH)
        {
          flow_ctl++;
          break;
        }
      }
    } // for (byte_lane)
  }// while ()
         
#if DSF_RD_DQDQS_DCC_LOG
  for(byte_lane = 0; byte_lane < dq; byte_lane++) 
  {
	  	DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                //rd_left_edge_coarse[byte_lane], 
                                  0, 
                                  0x1,  // 1 for coarse_delay
                                  0x1, 
                                  cs);   
 
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                  0, 
                                  0x0, // 0 for fine_delay
                                  0x1, 
                                  cs); 
        ddr_printf(DDR_NORMAL, "  Byte %d CS %d RD_DCC 0x%x\n",
               byte_lane,cs, training_data_ptr->results.rd_dqdqs.rd_dcc[ch][cs][byte_lane]);
  }
#endif

  // Average the RD DCC per rank after rank 1 is trained
  if (cs == 1)
  {
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
      // Initialize the sign variable
      sign = 0;
      
      // Determine the sign of the rank DCC results
      for (loopcnt = 0;loopcnt < NUM_CS;loopcnt++)
      {
        if ((training_data_ptr->results.rd_dqdqs.rd_dcc[ch][loopcnt][byte_lane]>>4) != 0)
        {
          sign |= (0x1 << loopcnt);
        }
      }
      
      // Calculate the average DCC for the two ranks
      switch (sign)
      {
        case 0x0  : // rank0 positive, rank1 positive
                  {
                    training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] + 
                       training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane]) / 2; 
                    break;                       
                  }
        case 0x1  : // rank0 negative, rank1 positive
                  {
                    // Normalize the rank0 result 
                    training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] >>= 4;
                    
                    // if rank 0 is greater than rank 1 -> the average will be negative
                    if (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] >= 
                        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane])
                    {
                      training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] - 
                       training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane])<<4; 
                    }
                    // if rank 1 is greater than rank 0 -> the average will be positive
                    else
                    {
                      training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane] - 
                       training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane]);                      
                    }
                    break;
                  }
        case 0x2  : // rank0 positive, rank1 negative
                  {
                    // Normalize the rank1 result 
                    training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane] >>= 4;
                    
                    // if rank 1 is greater than rank 0 -> the average will be negative
                    if (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane] >= 
                        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane])
                    {
                      training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane] - 
                       training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane])<<4; 
                    }
                    // if rank 0 is greater than rank 1 -> the average will be positive
                    else
                    {
                      training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] - 
                       training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane]);                      
                    }
                    break;
                  }
        case 0x3  : // rank0 negative, rank1 negative
                  {
                    training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane] = 
                      (((training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane]>>4) + 
                        (training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane]>>4))/ 2)<<4;                    
                  }
                  break;
      }
  
      // Copy the averaged result from rank 0 to rank 1 (for continuity)
      training_data_ptr->results.rd_dqdqs.rd_dcc[ch][1][byte_lane] = 
        training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane];      
  
      // Write the DCC_CTL register with the averaged value
      HWIO_OUTXF(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                 DDR_PHY_DDRPHY_CMCDCRD_TOP_CFG, 
                 DCC_CTL, 
                 training_data_ptr->results.rd_dqdqs.rd_dcc[ch][0][byte_lane]);
    }
  }   
} // DDRSS_rd_dqdqs_dcc_schmoo



//================================================================================================//
//  Function: DDRSS_rd_dqdqs_perbit().
//  Brief description: 
//================================================================================================//
void DDRSS_rd_dqdqs_perbit (DDR_STRUCT *ddr, 
                            uint8 ch, 
                            uint8 cs, 
                            PHY_BUS dq,
                            training_params_t *training_params_ptr, 
                            ddrss_rdwr_dqdqs_local_vars *local_vars,
                            uint8 *rd_left_edge_coarse,
                            uint32 clk_freq_khz)
{
    uint8  dq_pin_num           = 0;
    uint8  bit                  = 0;
    uint8  byte_lane            = 0;
    uint32 dq0_ddr_phy_base     = 0;
    uint8  phase                = 0;
    uint8  loopcnt              = 0;
    uint8  perbit               = 0;
        
    uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};     
    uint8 perbit_cdc[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Set DQ0 base for addressing
    dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

    // Set DQ0 base for addressing
    dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables (ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
#endif
    
    for(dq_pin_num = 0; dq_pin_num < PINS_PER_PHY; dq_pin_num++)
    {
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {        
            DDR_PHY_hal_cfg_local_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                         LOCAL_VREF_MID_VALUE,
                                         cs, 
                                         dq_pin_num);

            perbit_cdc [byte_lane][dq_pin_num] = 0xF;

           
        }
    }  
    
    // Train the perbit to have at least one fail at the left edge of Phase 0
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {     
        // Set the coarse and fine CDC values before training
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), rd_left_edge_coarse[byte_lane], 1, 1, cs);
        DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 0, 0, 1, cs);   
    }
    for (perbit = 0; perbit <= PERBIT_CDC_MAX_VALUE; perbit++)
    {
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for(bit = 0; bit < PINS_PER_PHY; bit++)
            {
                // Sweep all of the perbit at once
                DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                            bit, 
                                            0,   // 0 for RX.
                                            cs, 
                                            perbit);
                compare_result_acc[byte_lane][bit]  = 0x0;
            }//bit
        }//byte_lane
        for (loopcnt = 0;loopcnt < training_params_ptr->rd_dqdqs.max_loopcnt ; loopcnt++) 
        {
#if DSF_PXI_TRAINING_EN
//==================================================================================================================================        
      DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, dq,compare_result_acc, phase,1); 
//==================================================================================================================================        
#else    
//==================================================================================================================================        
      DDRSS_mem_read_per_bit_phase    (ddr, ch, cs, dq,compare_result_acc, phase); 
//==================================================================================================================================        
#endif
    }
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for (bit = 0; bit < PINS_PER_PHY; bit++)
            {
                if ((compare_result_acc[byte_lane][bit] != 0) && (perbit <= perbit_cdc[byte_lane][bit])) // Changed by Sagar
                { 
                    // perbit_cdc is in PHY order
                    perbit_cdc[byte_lane][bit] = perbit;
                }
            }
        } // perbit loop
    } // byte loop

    // Populate the PHY per-bit lanes with the trained values
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {        
        for (bit = 0; bit < PINS_PER_PHY; bit ++)
        {
            // Write the perbit values into the PHY SLICE registers including the gaps (unused, dbi)
            DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                           bit, 
                                           0,   // 0 for RX.
                                           cs, 
                                           perbit_cdc[byte_lane][bit]);
    
            // Store the perbit values into the data structure including the gaps (unused, dbi)
            training_data_ptr->results.rd_dqdqs.perbit_delay[ch][cs][byte_lane][bit] = perbit_cdc[byte_lane][bit];
#if DSF_RD_DQDQS_DCC_LOG
            ddr_printf(DDR_NORMAL,"  Byte %d PHY bit %d DCC Perbit = %d\n", byte_lane, bit, perbit_cdc[byte_lane][bit]);
#endif
        }
    }
}

void DDRSS_RD_Vref_CDC_Coarse_Schmoo (DDR_STRUCT *ddr, 
                                      uint8 ch, 
                                      uint8 cs, 
                                      PHY_BUS ca,
                                      PHY_BUS dq,
                                      training_data *training_data_ptr,
                                      training_params_t *training_params_ptr,
                                      best_eye_struct *best_eye_ptr, 
                                      ddrss_rdwr_dqdqs_local_vars *local_vars,
                                      uint32 clk_freq_khz,
                                      uint8  current_clk_inx,
                                      uint8  max_prfs_index)
{
    uint8 coarse_vref_value = 0;
    uint8 coarse_cdc_value  = 0;
    uint8 coarse_cdc_index  = 0;
    
    uint32 full_cycle_steps = 0;
    uint32 coarse_cdc_max_value = 0;
    
    uint8 byte_lane         = 0;
    uint8 loopcnt           = 0;
    uint8 *compare_result;  
    uint8 compare_result_acc[NUM_DQ_PCH]    = {0};  

    uint8 coarse_dq_error_count[NUM_DQ_PCH] = {0};
    uint32 dq0_ddr_phy_base = 0;
    
    uint8 mp_hp               = 0;
    uint8 vref_max_value      = 0;
    uint8 all_bytes_fail_flag = 0;
    
    uint8 coarse_vref_index[NUM_DQ_PCH] = {0};
    uint8 vref_start_value[NUM_DQ_PCH]  = {0};

    uint32 decouple_bit[NUM_DQ_PCH] = {0};
    uint32 ioqual_vref = 0x10; // LPDDR4 = 0x20   LPDDR4x = 0x10
	
	uint32 tmp_mpvref = 0;
      
    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;    
    
    // Determine starting VREF and minimum and maximum limits based on MPRX or HPRX
    mp_hp = (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ) ? MPVREF : HPVREF; 
    
    // Calculate the VREF max value (if not max frequency, use the previously trained VREF)
    vref_max_value = (mp_hp == HPVREF) ? 
                       ((current_clk_inx == max_prfs_index) && (cs == 0)) ? 
                         training_params_ptr->rd_dqdqs.coarse_vref_max_hprx 
                       : 0
                   :  training_params_ptr->rd_dqdqs.coarse_vref_max_mprx;

    // Calculate coarse CDC max value based on period
    full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
    coarse_cdc_max_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;
	
	// If different one-time setting for LP4 vs LP4X
	tmp_mpvref = HWIO_INXF (dq0_ddr_phy_base, DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_PAD_RFU_R0);
				   
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables (ddr, ch, cs, 0x1, 0x0); //ch, cs, wr/rd, dbi             
#endif

    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {

      // Calculate the VREF start values (if not max frequency, use the previously trained VREF)
        vref_start_value[byte_lane] = (mp_hp == HPVREF) ? 
                                ((current_clk_inx == max_prfs_index) && (cs == 0)) ? 
                                        training_params_ptr->rd_dqdqs.coarse_vref_min_hprx //2//0 
                                      : training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][0][byte_lane]
                                  :  training_params_ptr->rd_dqdqs.coarse_vref_start_mprx;
        if (mp_hp == HPVREF)  
        {    
            // Set decouple bit (RMW).This sets the IOqualifier to MPVREF. This is required durining training. bit[0] = 0 => MPRX
            decouple_bit[byte_lane] = HWIO_INX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_DQS_1_CFG);
            decouple_bit[byte_lane] = (decouple_bit[byte_lane] | (1 << 1));
            HWIO_OUTX ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_DQS_1_CFG, decouple_bit[byte_lane]);
                
            // Set MPVREF value to IOqualifier to mprx vref reg.  This value is to be set in CA PHY                 
            DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                            ioqual_vref,
                            //F_RANGE_3,
                            HIGHEST_MPVREF_PRFS_FREQ,
                            0);
        }
  
        // Initialize the fail flag and best cdc
        best_eye_ptr[byte_lane].vref_all_fail_flag = 0; // Assume all sane values to begin with.
        best_eye_ptr[byte_lane].best_cdc_value = 0;     // Assume initial value = 0, for initial retimer() setup.
    
    } // byte_lane
    
    memset(local_vars->coarse_schmoo.coarse_dq_passband_info, 
           training_params_ptr->rd_dqdqs.max_loopcnt + 1, 
           NUM_DQ_PCH * COARSE_VREF * COARSE_CDC);
     
    // If HPRX and maximum frequency and Rank 0 or MPRX - Run the full 2 dimensional eye histogram
    // Otherwise the histogram is run with only the trained VREF from the maximum frequency
    for (coarse_vref_value  = 0;
         coarse_vref_value <= vref_max_value; 
         coarse_vref_value += training_params_ptr->rd_dqdqs.coarse_vref_step)  
    {

        // Set starting VREF value 
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
          coarse_vref_index[byte_lane] = (coarse_vref_value + vref_start_value[byte_lane])/ training_params_ptr->rd_dqdqs.coarse_vref_step;

          DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                       coarse_vref_index[byte_lane],
                                       clk_freq_khz,
                                       cs);
        }
       
        // Reset all bytes failure flag
        all_bytes_fail_flag = 1;
        // CDC Schmoo loop
        for(coarse_cdc_value  = training_params_ptr->rd_dqdqs.coarse_cdc_start_value; 
            coarse_cdc_value <= coarse_cdc_max_value;
            coarse_cdc_value += training_params_ptr->rd_dqdqs.coarse_cdc_step)
        {
            coarse_cdc_index = ((coarse_cdc_value - training_params_ptr->rd_dqdqs.coarse_cdc_start_value) / 
                                 training_params_ptr->rd_dqdqs.coarse_cdc_step);
            // Update RD CDC
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
                DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                              coarse_cdc_value, 
                                              0x1, 
                                              0x1, 
                                              cs);   
                compare_result_acc[byte_lane] = 0;
            }

            // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.
            for (loopcnt = 0;loopcnt < training_params_ptr->rd_dqdqs.max_loopcnt; loopcnt++) 
            {
#if DSF_PXI_TRAINING_EN
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 0x2, 1);    //ddr, ch, cs, dq, phase, prbs    
#else
                compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, 0x2);      //ddr, ch, cs, dq, phase //wsa for phase 0 only.
#endif
                

                // Accumulate the compare results per byte
                for(byte_lane = 0; byte_lane < dq; byte_lane++) 
                {
                  compare_result_acc[byte_lane] += compare_result[byte_lane];
                  all_bytes_fail_flag &= compare_result[byte_lane];
                }
            }
             
            for(byte_lane = 0; byte_lane < dq; byte_lane++)
            { 
              // If fail, increment error_count.
              coarse_dq_error_count[byte_lane] = compare_result_acc[byte_lane];
              local_vars->coarse_schmoo.coarse_dq_passband_info[byte_lane][coarse_vref_index[byte_lane]][coarse_cdc_index] = coarse_dq_error_count[byte_lane]; 
            } // byte_lane 
        } // CDC_LOOP
        // Check for condition where all bytes fail (top of eye reached)
       // if(all_bytes_fail_flag) break;
    } // VREF_LOOP

    // Restore IO qualifier local VREF
    if(mp_hp == HPVREF)
    {
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            DDR_PHY_hal_cfg_local_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                        DQS_VREF, 
                                        cs,
                                        10
                                        );
        }
    }
    
    // Construct 2D histogram for the 4 byte lanes: [DQ][VREF][CDC]. 
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
        DDRSS_Post_Histogram_Coarse_Horizon_Eye_Max_Rectangle (ddr, ch, cs,best_eye_ptr, 
                                                 local_vars->coarse_schmoo.coarse_dq_passband_info, 
                                                 training_data_ptr, 
                                                 training_params_ptr, 
                                                 2, // 2 for RD_Training
                                                 byte_lane,
                                                 clk_freq_khz,
                                                 current_clk_inx,
                                                 max_prfs_index
                                                 ); 

        // Calculate the center of the coarse eye
        best_eye_ptr[byte_lane].best_cdc_value = ((best_eye_ptr[byte_lane].max_eye_left_boundary_cdc_value + 
                                                   best_eye_ptr[byte_lane].max_eye_right_boundary_cdc_value) / 2);    

        // Write the coarse_training CDC values into phy regs
        DDR_PHY_hal_cfg_cdc_slave_rd ((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                       best_eye_ptr[byte_lane].best_cdc_value, 
                                       1, // 1 for coarse_delay_mode.
                                       1, 
                                       cs);  

    }
    
    if(mp_hp == HPVREF)
    {
        // Restore back MPRX Vref value.
        for(byte_lane = 0; byte_lane < dq; byte_lane++)
        {
            // Restore decouple bit.
            decouple_bit[byte_lane] = (decouple_bit[byte_lane] & 0xFFFFFFFD);
            HWIO_OUTX((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), DDR_PHY_DDRPHY_PAD_DQS_1_CFG, decouple_bit[byte_lane]);
            
            // restore mprx vref to mprx vref reg.             
            DDR_PHY_hal_cfg_global_vref((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                               tmp_mpvref,
                               //F_RANGE_3,
                               HIGHEST_MPVREF_PRFS_FREQ,
                               0);
        }
    }
 
}//DDRSS_RD_Vref_CDC_Coarse_Schmoo


void DDRSS_RD_Vref_CDC_Fine_Schmoo (DDR_STRUCT *ddr, 
                                    uint8 ch, 
                                    uint8 cs, 
                                    PHY_BUS dq,
                                    training_data *training_data_ptr,
                                    training_params_t *training_params_ptr,
                                    uint8 fine_start_vref_value,
                                    uint8 fine_max_vref_value,
                                    uint8 (*rd_boundary_fine_cdc_ptr)[PINS_PER_PHY][FINE_VREF],
                                    uint8 direction, 
                                    ddrss_rdwr_dqdqs_local_vars *local_vars,
                                    uint32 clk_freq_khz,
                                    uint8  current_clk_inx,
                                    uint8  max_prfs_index,
                                    dbi_struct *dbi_struct_ptr)
{
    uint8  fine_vref_value  = 0;
    uint8  fine_cdc_value   = 0;
    uint8  fine_vref_index  = 0;
    uint8  fine_cdc_index   = 0;
    uint8  byte_lane        = 0;
    uint8  bit              = 0;
    uint8  loopcnt          = 0;
    uint32 dq0_ddr_phy_base = 0;

    uint8 *compare_result_DBI = 0;
    uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 

    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables (ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
#endif

    // Vref Loop
    for (fine_vref_value  = fine_start_vref_value; 
         fine_vref_value <= fine_max_vref_value; 
         fine_vref_value += training_params_ptr->rd_dqdqs.fine_vref_step)  
    {
        fine_vref_index = ((fine_vref_value - fine_start_vref_value) / training_params_ptr->rd_dqdqs.fine_vref_step);

        if (current_clk_inx == max_prfs_index)
        {
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
            
             for (bit = 0; bit < PINS_PER_PHY; bit ++)
             {            
                DDR_PHY_hal_cfg_local_vref (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                            fine_vref_value, 
                                            cs,
                                            bit
                                            );
             }
            }
        }
  
        fine_cdc_value  = training_params_ptr->rd_dqdqs.fine_cdc_start_value; 

        // Fine CDC loop
        for(fine_cdc_value  = training_params_ptr->rd_dqdqs.fine_cdc_start_value; 
            fine_cdc_value <= training_params_ptr->rd_dqdqs.fine_cdc_max_value; 
            fine_cdc_value += training_params_ptr->rd_dqdqs.fine_cdc_step)
        {
            fine_cdc_index = (fine_cdc_value/ training_params_ptr->rd_dqdqs.fine_cdc_step);

            // Update CDC
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
                DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                              fine_cdc_value, 
                                              0x0, 
                                              0x1, 
                                              cs);   // 0 for fine_delay_mode. 

                for (bit = 0; bit < PINS_PER_PHY; bit ++)
                {
                    compare_result_acc [byte_lane][bit] = 0;
                }
            }  
              
            // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
            for (loopcnt = 0;loopcnt < training_params_ptr->rd_dqdqs.max_loopcnt; loopcnt++) 
            {
#if DSF_PXI_TRAINING_EN
//==================================================================================================================================        
      DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, dq,compare_result_acc, 0x2,1); 
//==================================================================================================================================        
#else
//==================================================================================================================================        
      DDRSS_mem_read_per_bit_phase    (ddr, ch, cs, dq,compare_result_acc, 0x2); 
//==================================================================================================================================        
#endif
               
               // When DBI enabled, DBI bit test needs to compare per byte
               if (dbi_struct_ptr->dbi_flag == 1)
               {
#if DSF_PXI_TRAINING_EN
                   Initialize_PXI_Tables (ddr, ch, cs, 1, 1); //ch, cs, wr/rd, dbi
                   compare_result_DBI = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 0x2, 0);    //ddr, ch, cs, dq, phase, prbs    
#else
                   compare_result_DBI = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, 0x2);       //ddr, ch, cs, dq, phase
#endif
                   
               }
               // Accumulate the compare results for DBI bit if DBI is enabled.
               // To avoid null pointer reference.
               if (compare_result_DBI != NULL)
               {
                    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
                    { 
                        compare_result_acc [byte_lane][dq_dbi_bit] += compare_result_DBI [byte_lane];
                    }//byte
               }//if
            }//loopcnt
            // Save the results into fine schmoo table 
            for(byte_lane = 0; byte_lane < dq; byte_lane++)            
            { 
                for (bit = 0; bit < PINS_PER_PHY; bit ++)  
                {
                    // If fail, increment error_count.
                    if(direction == SWEEP_LEFT) 
                    {
                        local_vars->fine_schmoo.fine_rd_dq_passband_info_left[byte_lane][bit][fine_vref_index][fine_cdc_index] = 
                                    compare_result_acc[byte_lane][bit]; 
                    }
                    if(direction == SWEEP_RIGHT) 
                    {
                        local_vars->fine_schmoo.fine_rd_dq_passband_info_right[byte_lane][bit][fine_vref_index][fine_cdc_index] = 
                                    compare_result_acc[byte_lane][bit]; 
                    }
                } //bit loop
            } // byte_lane               
        } // CDC_LOOP 
    } // VREF_LOOP 
    
    // Construct 2D histogram for the all the bits: [DQ][PIN][VREF][CDC]. Indexed [5:2] in the post_histogram function.
    if(direction == SWEEP_LEFT) 
    {
       for (byte_lane = 0; byte_lane < dq; byte_lane++)
       {  
         for (bit = 0; bit < PINS_PER_PHY; bit ++)
          {
              DDRSS_Post_Histogram_RD_Fine_Each_Boundary (local_vars->fine_schmoo.fine_rd_dq_passband_info_left, 
                                                          rd_boundary_fine_cdc_ptr, 
                                                          fine_start_vref_value, 
                                                          fine_max_vref_value, 
                                                          training_data_ptr, 
                                                          training_params_ptr, 
                                                          direction, 
                                                          byte_lane,
                                                          bit); 
          }
        }
      }

     if(direction == SWEEP_RIGHT) 
     {
       for (byte_lane = 0; byte_lane < dq; byte_lane++)
       { 
         for (bit = 0; bit < PINS_PER_PHY; bit ++)
          {
              DDRSS_Post_Histogram_RD_Fine_Each_Boundary (local_vars->fine_schmoo.fine_rd_dq_passband_info_right, 
                                                          rd_boundary_fine_cdc_ptr, 
                                                          fine_start_vref_value, 
                                                          fine_max_vref_value, 
                                                          training_data_ptr, 
                                                          training_params_ptr, 
                                                          direction, 
                                                          byte_lane,
                                                          bit); 
          }
       }
     } 
} // Fine Schmoo



void DDRSS_WR_Vref_CDC_Coarse_Schmoo (DDR_STRUCT *ddr, 
                                      uint8 ch,
                                      uint8 cs,
                                      PHY_BUS dq,
                                      training_data *training_data_ptr,
                                      training_params_t *training_params_ptr,
                                      uint8 *coarse_wrlvl_delay,
                                      uint8 *fine_wrlvl_delay,
                                      best_eye_struct *best_eye_ptr,
                                      ddrss_rdwr_dqdqs_local_vars *local_vars,
                                      uint8 phase,
                                      uint32 clk_freq_khz,
                                      uint8 max_prfs_index)
{
    uint32   dq0_ddr_phy_base  = 0;
    uint8           byte_lane  = 0;
    uint8          loop_count  = 0;
    uint8          MR14_value  = 0;
    uint8 MR14_vref_range_bit  = 0;
    
    uint8   coarse_vref_value  = 0;
    uint8       max_vref_value = 0;
    uint8     start_vref_value = 0;
    uint8     coarse_vref_step = 0;
    uint8    coarse_cdc_value  = 0;
    uint8      fine_cdc_value  = 0;
    
    uint8   coarse_vref_index[NUM_DQ_PCH]  = {0};
    uint8    coarse_cdc_index  = 0;
//    uint8          vref_index  = 0;
    uint8       max_cdc_value  = 0;
    uint8     temp_vref_start  = 0;
    uint8       temp_vref_max  = 0;
    uint8      temp_vref_step  = 0;

    uint8     *compare_result; 
    uint8     coarse_dq_error_count[NUM_DQ_PCH] = {0};
    
    uint8             clk_idx = 0;
    uint8     current_clk_inx = 0;
    
    uint8      full_cycle_steps = 0;
    
    uint8  vref_start_value[NUM_DQ_PCH]  = {0};
//#endif // #if DSF_WR_DQDQS_EYE_MASK

    full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
   
    
    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    // Choose Vref_Range_bit according to frequency threshold.
    MR14_vref_range_bit = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 0: 1;
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
#endif
    
    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1;
    
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        best_eye_ptr[byte_lane].vref_all_fail_flag = 0;  // Assume all sane values to begin with.
        best_eye_ptr[byte_lane].best_cdc_value = 0;      // Assume initial value = 0, for initial retimer() setup.

        // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
        fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];
    }
    
    memset(local_vars->coarse_schmoo.coarse_dq_passband_info, training_params_ptr->wr_dqdqs.max_loopcnt + 1, (NUM_DQ_PCH * COARSE_VREF * COARSE_CDC));

    if(current_clk_inx == max_prfs_index) // for 1804MHz only.
    {
        fine_cdc_value = training_params_ptr->wr_dqdqs.fine_cdc_top_freq_start_value;
        max_cdc_value = ((full_cycle_steps + 1) > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : (full_cycle_steps + 1);
    }
    else
    {
        fine_cdc_value = training_params_ptr->wr_dqdqs.fine_cdc_start_value;
        max_cdc_value = ((full_cycle_steps + 3) > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : (full_cycle_steps + 3);
    }
    //save default training_params values. 
    temp_vref_start = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
    temp_vref_max = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
    temp_vref_step = training_params_ptr->wr_dqdqs.coarse_vref_step; 

    //full Vref range only for top HPRX and MPRX speed.  
    //if((current_clk_inx == max_prfs_index) || (clk_freq_khz <= F_RANGE_3))
    if((current_clk_inx == max_prfs_index) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
    {
        start_vref_value = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
        max_vref_value = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
        coarse_vref_step = training_params_ptr->wr_dqdqs.coarse_vref_step;
    }
    else   //for lower frequencies, no Vref sweep is required. 
    {
        start_vref_value = 0;
        max_vref_value = 0;
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
          vref_start_value[byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch][cs][byte_lane];
        }
        coarse_vref_step = 1;
        training_params_ptr->wr_dqdqs.coarse_vref_start_value = 0;
        training_params_ptr->wr_dqdqs.coarse_vref_max_value = 0;
        training_params_ptr->wr_dqdqs.coarse_vref_step =1;
    }
    
    // Start schmoo.
    for (coarse_vref_value  = start_vref_value; 
         coarse_vref_value <= max_vref_value; 
         coarse_vref_value += coarse_vref_step)  
    {
        //if((current_clk_inx == max_prfs_index) || (clk_freq_khz <= F_RANGE_3))
        if((current_clk_inx == max_prfs_index) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
        {
            MR14_value = ((MR14_vref_range_bit << 6) | (coarse_vref_value << 0));
            BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_14, MR14_value);
            //coarse_vref_index = ((coarse_vref_value - training_params_ptr->wr_dqdqs.coarse_vref_start_value) / training_params_ptr->wr_dqdqs.coarse_vref_step);
        }
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            coarse_vref_index[byte_lane] = (coarse_vref_value + vref_start_value[byte_lane])/ training_params_ptr->wr_dqdqs.coarse_vref_step;
        }
        
  
        for(coarse_cdc_value  = training_params_ptr->wr_dqdqs.coarse_cdc_start_value; 
            coarse_cdc_value <= max_cdc_value; 
            coarse_cdc_value += training_params_ptr->wr_dqdqs.coarse_cdc_step)
        {                                          
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
               
                coarse_cdc_index = (coarse_cdc_value / training_params_ptr->wr_dqdqs.coarse_cdc_step);
                
                DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                               coarse_cdc_value, 
                                               1, 1, cs);   // 1 for coarse_delay_mode. 1 for hp_mode.                

                
                DDRSS_CDC_Retimer (ddr, 
                                   cs, 
                                   coarse_cdc_value, 
                                   fine_cdc_value, 
                                   coarse_wrlvl_delay[byte_lane],
                                   fine_wrlvl_delay[byte_lane],
                                   (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                   clk_freq_khz);  // 0 for fine_delay.                
                
                coarse_dq_error_count[byte_lane] = 0;
            }
            
            for(loop_count = training_params_ptr->wr_dqdqs.max_loopcnt; loop_count > 0 ; loop_count--)
            {                 
#if DSF_PXI_TRAINING_EN
                // The write pattern. 
                DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs

                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, phase, 1);    //ddr, ch, cs, dq, phase, prbs    
#else
                // The write pattern. 
                DDRSS_mem_write(ddr, ch, cs);
                
                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, phase);       //ddr, ch, cs, dq, phase
#endif
                

                for (byte_lane = 0; byte_lane < dq; byte_lane++) 
                { 
                    // Accumulate the error for all byte_lanes, based on loop_count number of times.
                    coarse_dq_error_count[byte_lane] += compare_result[byte_lane];
                }
            } // LOOP_COUNT 
         
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {    
                // Populate the histogram every vref and cdc with the result found.
                local_vars->coarse_schmoo.coarse_dq_passband_info[byte_lane][coarse_vref_index[byte_lane]][coarse_cdc_index] = coarse_dq_error_count[byte_lane]; 
            }
        }  //CDC loop
    } // VREF_LOOP
    
#if DSF_WR_DQDQS_TRAINING_LOG
    if (phase == 3)
        ddr_printf(DDR_NORMAL,"Write coarse training\n");
#endif
    // Construct 2D histogram for the 4 bytelanes: [DQ][VREF][CDC]. 
    for(byte_lane = 0; byte_lane < dq; byte_lane++)
    {
        DDRSS_Post_Histogram_Coarse_Horizon_Eye_Max_Rectangle (ddr, ch, cs, best_eye_ptr, 
                                                 local_vars->coarse_schmoo.coarse_dq_passband_info, 
                                                 training_data_ptr, 
                                                 training_params_ptr, 
                                                 1, // 1for WR_Training
                                                 byte_lane,
                                                 clk_freq_khz,
                                                 current_clk_inx,
                                                 max_prfs_index
                                                 ); 

#if DSF_WR_DQDQS_TRAINING_LOG
        ddr_printf(DDR_NORMAL, "  Write Byte %u Coarse L<->R Edge: %u <-> %u   Width = %u\n",
                                byte_lane,
                                best_eye_ptr[byte_lane].max_eye_left_boundary_cdc_value ,
                                best_eye_ptr[byte_lane].max_eye_right_boundary_cdc_value,
                                ((best_eye_ptr[byte_lane].max_eye_right_boundary_cdc_value -
                                best_eye_ptr[byte_lane].max_eye_left_boundary_cdc_value) +1 ));
#endif

        // Write the coarse_training values into phy regs and training_params. This is necessary in case we stop with coarse training.
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), best_eye_ptr[byte_lane].best_cdc_value, 1, 1, cs);  // 1 for coarse_delay_mode. 1 for hp_mode. respectively.
        
        DDRSS_CDC_Retimer (ddr, 
                           cs, 
                           best_eye_ptr[byte_lane].best_cdc_value, 
                           fine_cdc_value, 
                           coarse_wrlvl_delay[byte_lane],
                           fine_wrlvl_delay[byte_lane],
                           (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                           clk_freq_khz);  // 0 for fine_delay.
    }

    //restore Vref training params values 
    training_params_ptr->wr_dqdqs.coarse_vref_start_value = temp_vref_start;
    training_params_ptr->wr_dqdqs.coarse_vref_max_value = temp_vref_max;
    training_params_ptr->wr_dqdqs.coarse_vref_step = temp_vref_step;    
 
}


void DDRSS_WR_CDC_1D_Fine_Schmoo (DDR_STRUCT *ddr, 
                                  uint8 ch, 
                                  uint8 cs, 
                                  PHY_BUS dq,
                                  training_data *training_data_ptr,
                                  training_params_t *training_params_ptr, 
                                  ddrss_rdwr_dqdqs_local_vars *local_vars,
                                  best_eye_struct *best_eye_ptr,
                                  uint8 *coarse_cdc_value,
                                  uint32 clk_freq_khz,
                                  uint8 max_prfs_index,
                                  uint8 direction /*0 for Cl and 1 for Cr*/)
{
    uint32   dq0_ddr_phy_base = 0;
    uint8           byte_lane = 0;
    uint8          loop_count = 0;
    uint8      fine_cdc_value = 0;
    uint8  fine_cdc_max_value = 0;
    uint8      fine_cdc_index = 0;
    uint8               index = 0; 
    uint8             clk_idx = 0;
    uint8     current_clk_inx = 0;
    
    uint8     *compare_result;
    
    uint8             dq_error_count[NUM_DQ_PCH] = {0};
    uint8      left_boundary_eye_cdc_value[NUM_DQ_PCH];// = {0};
    uint8     right_boundary_eye_cdc_value[NUM_DQ_PCH];// = {0};
    uint8               coarse_wrlvl_delay[NUM_DQ_PCH] = {0};
    uint8               fine_wrlvl_delay  [NUM_DQ_PCH] = {0};

    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
#endif
    
    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1; 
    
    for (byte_lane = 0; byte_lane < dq; byte_lane++)
    {  
    // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
        fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];

        if(direction == 0)
        {
            // Retain these values.
            best_eye_ptr[byte_lane].best_fine_cdc_value = 0;
            left_boundary_eye_cdc_value[byte_lane]  = 0xFF;
        }
        right_boundary_eye_cdc_value[byte_lane] = 0xFF;
    }

    memset(local_vars->fine_schmoo.fine_dq_1D_passband_info, training_params_ptr->wr_dqdqs.max_loopcnt + 1, (NUM_DQ_PCH * (2 * FINE_CDC)));

    fine_cdc_max_value = training_params_ptr->wr_dqdqs.fine_cdc_max_value;

    
    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Update Coarse CDC value.
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                        coarse_cdc_value[byte_lane], 
                                        1, 1, cs);   // 1 for coarse_delay_mode. 1 for hp_mode.

        // Fine CDC Schmoo loop
        for(fine_cdc_value  = training_params_ptr->wr_dqdqs.fine_cdc_start_value;
            fine_cdc_value <= fine_cdc_max_value;
            fine_cdc_value += training_params_ptr->wr_dqdqs.fine_cdc_step)
        {
            // Update Fine CDC
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                           fine_cdc_value, 
                                           0, 1, cs);   // 0 for fine_delay_mode. 1 for hp_mode.  

            DDRSS_CDC_Retimer (ddr, 
                               cs, 
                               coarse_cdc_value[byte_lane],  
                               fine_cdc_value, 
                               coarse_wrlvl_delay[byte_lane],
                               fine_wrlvl_delay[byte_lane],
                               (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                               clk_freq_khz);  // 0 for fine_delay.
            
            fine_cdc_index = (fine_cdc_value / training_params_ptr->wr_dqdqs.fine_cdc_step);
            dq_error_count[byte_lane] = 0;
            
            for(loop_count = training_params_ptr->wr_dqdqs.max_loopcnt; loop_count > 0 ; loop_count--)
            {                 
#if DSF_PXI_TRAINING_EN
                // The write pattern. 
                DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
        
        // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 2, 1);    //ddr, ch, cs, dq, phase, prbs    
                // The write pattern. 
                
#else               
                DDRSS_mem_write(ddr, ch, cs);
                
                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, 2);       //ddr, ch, cs, dq, phase
#endif
                
                
                // Accumulate the error for all byte_lanes, based on loop_count number of times.
                dq_error_count[byte_lane] += compare_result[byte_lane];    
            }
        
            // Populate the histogram every coarase and fine cdc with the result found.
            local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][fine_cdc_index] = dq_error_count[byte_lane];
        }

        //------------------Find the fine boundary.
        for(index = 0; index <= fine_cdc_max_value; index++)
        {
            // If pass.
            if(direction == 1)
            {
                // If first point is already a FAIL.
                if(local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][0] != 0)
                {
                    right_boundary_eye_cdc_value[byte_lane] = 0;
                }
                
                if(local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][index] == 0)
                {
                    right_boundary_eye_cdc_value[byte_lane] = index;
                }
        
                // Current point is FAIL and previous point is PASS.
                else if ((index >= 1) && (local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][index-1] == 0) &&
                                            (local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][index] != 0))
                {
                    right_boundary_eye_cdc_value[byte_lane] = index - 1;
                }
            }
            
            // For all frequencies except 1804, find the left fine edge. F->P transition.
            if(direction == 0)
            {
                if(local_vars->fine_schmoo.fine_dq_1D_passband_info[byte_lane][index] == 0)
                {
                    left_boundary_eye_cdc_value[byte_lane] = index;
                    break;
                }
            }            
        }

        // Calculate the center Fine value: ((Fl + Fr)/2).
        if(direction == 0)
        {
            best_eye_ptr[byte_lane].best_fine_cdc_value = left_boundary_eye_cdc_value[byte_lane];
        }
        
        if(direction == 1) // Calculate center only after right edge has also been found.
        {
            best_eye_ptr[byte_lane].best_fine_cdc_value = ((best_eye_ptr[byte_lane].best_fine_cdc_value + right_boundary_eye_cdc_value[byte_lane]) / 2);
            
             // For 1804 only, limit fine delay to range from 5-10.
            if(current_clk_inx == max_prfs_index)
            {
                if(best_eye_ptr[byte_lane].best_fine_cdc_value < WRITE_FINE_CDC_MIN) //4 and less
                {
                    best_eye_ptr[byte_lane].best_fine_cdc_value = (best_eye_ptr[byte_lane].best_fine_cdc_value + FINE_STEPS_PER_COARSE);
                    training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] = (training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] - 1);
                }
                else if(best_eye_ptr[byte_lane].best_fine_cdc_value > WRITE_FINE_CDC_MAX) //11 and more  
                {
                    best_eye_ptr[byte_lane].best_fine_cdc_value = (best_eye_ptr[byte_lane].best_fine_cdc_value - FINE_STEPS_PER_COARSE);
                    training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane] = (training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] + 1);
                }
            }
        }
        
        // Write the center value found into the data structure.
        training_data_ptr->results.wr_dqdqs.fine_cdc [current_clk_inx][ch][cs][byte_lane] = best_eye_ptr[byte_lane].best_fine_cdc_value;
    }
    
}


void DDRSS_WR_CDC_1D_Schmoo (DDR_STRUCT *ddr, 
                             uint8 ch, 
                             uint8 cs, 
                             PHY_BUS dq,
                             training_data *training_data_ptr,
                             training_params_t *training_params_ptr, 
                             ddrss_rdwr_dqdqs_local_vars *local_vars,
                             best_eye_struct *best_eye_ptr,
                             uint8 *coarse_cdc_left_start_value,
                             uint8 *coarse_cdc_right_start_value,
                             uint32 clk_freq_khz,
                             uint8 max_prfs_index)
{
    uint32   dq0_ddr_phy_base = 0;
    uint8           byte_lane = 0;
    uint8          loop_count = 0;
    uint8    coarse_cdc_value = 0;
    uint8    coarse_cdc_index = 0;
    uint8             clk_idx = 0;
    uint8     current_clk_inx = 0;
    uint8     coarse_odd_flag = 0;
    uint8               index = 0;
    uint8          first_pass = 0;
    
    uint8     *compare_result;

    uint8            coarse_dq_error_count[NUM_DQ_PCH] = {0};
    uint8     left_boundary_eye_cdc_value [NUM_DQ_PCH] = {0};
    uint8    right_boundary_eye_cdc_value [NUM_DQ_PCH] = {0};
    uint8    coarse_wrlvl_delay           [NUM_DQ_PCH] = {0};
    uint8      fine_wrlvl_delay           [NUM_DQ_PCH] = {0};

    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
#endif
    
    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1; 
    
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
        fine_wrlvl_delay[byte_lane]   = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];

        best_eye_ptr[byte_lane].best_cdc_value  = 0;
        left_boundary_eye_cdc_value[byte_lane]  = 0xFF;
        right_boundary_eye_cdc_value[byte_lane] = 0xFF;
    }
    
    memset(local_vars->coarse_schmoo.coarse_dq_1D_passband_info, training_params_ptr->wr_dqdqs.max_loopcnt + 1, NUM_DQ_PCH * COARSE_CDC);
    

    for(byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
        // Update Fine_CDC value.
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                       training_params_ptr->wr_dqdqs.fine_cdc_start_value, 
                                       0, 1, cs);   // 0 for fine_delay_mode. 1 for hp_mode.

        // CDC Schmoo loop
        for(coarse_cdc_value  = coarse_cdc_left_start_value[byte_lane]; 
            coarse_cdc_value <= coarse_cdc_right_start_value[byte_lane]; /*This limit would be enough. */
            coarse_cdc_value += training_params_ptr->wr_dqdqs.coarse_cdc_step)
        {           
            // Update coarse CDC
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                           coarse_cdc_value, 
                                           1, 1, cs);   // 1 for coarse_delay_mode. 1 for hp_mode.

            DDRSS_CDC_Retimer (ddr, 
                               cs, 
                               coarse_cdc_value, 
                               training_params_ptr->wr_dqdqs.fine_cdc_start_value, 
                               coarse_wrlvl_delay[byte_lane],
                               fine_wrlvl_delay[byte_lane],
                               (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                               clk_freq_khz);  // 0 for fine_delay.

            coarse_cdc_index = (coarse_cdc_value / training_params_ptr->wr_dqdqs.coarse_cdc_step);
            coarse_dq_error_count[byte_lane] = 0;
            first_pass = 0;
            
            for(loop_count = training_params_ptr->wr_dqdqs.max_loopcnt; loop_count > 0 ; loop_count--)
            {                 
#if DSF_PXI_TRAINING_EN
                // The write pattern. 
                DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
        
        // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.   
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 2, 1);    //ddr, ch, cs, loop cnt, phase, prbs
#else        
        // The write pattern. 
                DDRSS_mem_write(ddr, ch, cs);
                
                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, 2);       //ddr, ch, cs, dq, phase
#endif
                
                
                // Accumulate the error for all byte_lanes, based on loop_count number of times.
                coarse_dq_error_count[byte_lane] += compare_result[byte_lane];
    
            }
        
            // Populate the histogram every coarase and fine cdc with the result found.
            local_vars->coarse_schmoo.coarse_dq_1D_passband_info[byte_lane][coarse_cdc_index] = coarse_dq_error_count[byte_lane];
        }                       

        //------------------Find the right coarse boundary.
        for(index = 0; index <= coarse_cdc_right_start_value[byte_lane]; index++)
        {
            if (local_vars->coarse_schmoo.coarse_dq_1D_passband_info[byte_lane][index] == 0)   // When the current point is PASS
            {                
                // Record the first PASS point as left boundary   
                if(first_pass == 0)
                {
                    left_boundary_eye_cdc_value[byte_lane] = index;
                    first_pass = 1;
                }
                
                // If the max_cdc point is PASS, record it as right boundary.
                if (index == coarse_cdc_right_start_value[byte_lane])
                {
                    right_boundary_eye_cdc_value[byte_lane] = index;
                }
            }
    
            // Current point is FAIL and previous point is PASS
            else if (index >= 1 && local_vars->coarse_schmoo.coarse_dq_1D_passband_info[byte_lane][index-1] == 0)
            {
                right_boundary_eye_cdc_value[byte_lane] = index - 1;
            }
        }
        
        // Subtract the left boundary by 1 so that we always start at a passing point.
        if (left_boundary_eye_cdc_value[byte_lane] > 0)
        {
            left_boundary_eye_cdc_value[byte_lane] -= 1;
        }
        // If center value is odd number, subtract right_boundary by 1 so that the center value is ALWAYS an even number.
        coarse_odd_flag = ((left_boundary_eye_cdc_value[byte_lane] + right_boundary_eye_cdc_value[byte_lane]) % 2);
        if(coarse_odd_flag == 1)
        {
            right_boundary_eye_cdc_value[byte_lane] -= 1;
        }
        
        // Calculate the center value for Coarse. ((Cl+Cr)/2).
        best_eye_ptr[byte_lane].best_cdc_value = ((left_boundary_eye_cdc_value[byte_lane] + right_boundary_eye_cdc_value[byte_lane]) / 2);
        
        training_data_ptr->results.wr_dqdqs.coarse_max_eye_left_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane] = left_boundary_eye_cdc_value[byte_lane];
        training_data_ptr->results.wr_dqdqs.coarse_max_eye_right_boundary_cdc_value[current_clk_inx][ch][cs][byte_lane] = right_boundary_eye_cdc_value[byte_lane];  
        
        // Write the value found into the data structure.
        training_data_ptr->results.wr_dqdqs.coarse_cdc [current_clk_inx][ch][cs][byte_lane] = best_eye_ptr[byte_lane].best_cdc_value;
    }

    // Calculate the fine value in the vicinity of Cl.
    DDRSS_WR_CDC_1D_Fine_Schmoo (ddr, ch, cs, dq, training_data_ptr, training_params_ptr, 
                                    local_vars, best_eye_ptr,
                                    left_boundary_eye_cdc_value,
                                    clk_freq_khz, max_prfs_index, 0);  /* 0 for direction Cl. */                                      

    // Calculate the fine value in the vicinity of Cr.
    DDRSS_WR_CDC_1D_Fine_Schmoo (ddr, ch, cs, dq, training_data_ptr, training_params_ptr, 
                                    local_vars, best_eye_ptr,
                                    right_boundary_eye_cdc_value,
                                    clk_freq_khz, max_prfs_index, 1);  /* 1 for direction Cr. */


}


//================================================================================================//
//  Function: DDRSS_rd_dqdqs_dcc_schmoo().
//  Brief description: This function performs dcc schmoo @1555MHz per each CS and
//                       sets the average DCC for both the CS's during read training.
//                       For a fixed vref value, the function performs cdc schmoo for
//                       all the DCC settings.
//================================================================================================//
void DDRSS_wr_pbit_schmoo (DDR_STRUCT *ddr, 
                           uint8 ch, 
                           uint8 cs,
                           PHY_BUS dq,                           
                           training_params_t *training_params_ptr, 
                           ddrss_rdwr_dqdqs_local_vars *local_vars,
                           uint8 *coarse_cdc_left_start_value,
                           uint32 clk_freq_khz)
{
    uint8 byte_lane                    = 0;
    uint32 dq0_ddr_phy_base            = 0;
    uint8  bit                         = 0;
    uint8  loopcnt                     = 0;
    int8   perbit                      = 0;
    uint8  clk_idx                     = 0;
    uint8  current_clk_inx             = 0;

    //uint8 *compare_result;
    uint8 *compare_result_DBI = 0; 
    uint8 compare_result_acc[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};     
    uint8 perbit_cdc[NUM_DQ_PCH][PINS_PER_PHY]         = {{0}};
    uint8    coarse_wrlvl_delay           [NUM_DQ_PCH] = {0};
    uint8      fine_wrlvl_delay           [NUM_DQ_PCH] = {0};

    dbi_struct dbi_struct_info;
    uint32 reg_offset_dpe =  0;

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
    
    // Set DBI flag to indicate Enable DBI or not
    reg_offset_dpe = REG_OFFSET_DPE (ch);    
    
    // Set DQ0 base for addressing
    dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    dbi_struct_info.dbi_flag = HWIO_INXF (reg_offset_dpe, DPE_CONFIG_9, DBI_WR);
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
#endif

    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1;
       
    // Initialize the fail flag, best cdc, coarse and fine 
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {   
        DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                       coarse_cdc_left_start_value[byte_lane],
                                       1, 
                                       1, 
                                       cs);  // 1 for coarse_delay_mode. 1 for hp_mode.

        // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
        fine_wrlvl_delay[byte_lane]   = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];

        DDRSS_CDC_Retimer (ddr, 
                           cs, 
                           coarse_cdc_left_start_value[byte_lane],
                           training_params_ptr->wr_dqdqs.fine_cdc_top_freq_start_value,
                           coarse_wrlvl_delay[byte_lane],
                           fine_wrlvl_delay[byte_lane],
                           (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                           clk_freq_khz);                                  
        
        //Reset perbit_cdc

        for(bit = 0; bit < PINS_PER_PHY; bit++)
        {
            perbit_cdc [byte_lane][bit] = 0x0;
        }
    }//byte_lane
    

    for (perbit = 0 ; perbit <= PERBIT_CDC_MAX_VALUE; perbit++)
    {
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for(bit = 0; bit < PINS_PER_PHY; bit++)  //PHY bit
            {
                if (bit != dq_dbi_bit)  //don't sweep DBI pin yet, otherwise it will mess up with other pbit results
                {
                    // Sweep all of the perbit at once
                    DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                   bit, 
                                                   1,   // 1 for TX.
                                                   cs, 
                                                   perbit);
                }
                else   //set DBI per-bit CDC to max to make sure it passes. 
                {
                    DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                dq_dbi_bit, 
                                                1,   // 1 for TX.
                                                cs, 
                                                0);
                }//else
               // Reset the compare results
               compare_result_acc[byte_lane][bit]  = 0x0;
            }//bit
        }//byte
            
//=======================================================================================================================================
        for(loopcnt = training_params_ptr->wr_dqdqs.max_loopcnt; loopcnt > 0 ; loopcnt--)
        {         
#if DSF_PXI_TRAINING_EN
                // The write pattern. 
            DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
            DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, dq,compare_result_acc, 0x0,1); 
#else
            // The write pattern. 
            DDRSS_mem_write(ddr, ch, cs); 
            DDRSS_mem_read_per_bit_phase    (ddr, ch, cs, dq,compare_result_acc, 0x0); 
#endif
        }//loopcnt
//=======================================================================================================================================        
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for (bit = 0; bit < PINS_PER_PHY; bit++)
            {
                if (bit != dq_dbi_bit)
                {
                   
                    if(compare_result_acc[byte_lane][bit] == 0x0)
                    {
                        perbit_cdc[byte_lane][bit] = perbit;
                    }
                }
            } // bit loop
         } // byte loop 
        
    } // perbit loop

    //DBI training separately
#if DSF_PXI_TRAINING_EN
    //reinitialize tables with DBI settings
    Initialize_PXI_Tables (ddr, ch, cs, 2, 1); //ch, cs, wr/rd, dbi
#endif  
  
    // Train the perbit to have at least one fail
    if (dbi_struct_info.dbi_flag == 1)
    {
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            for(bit = 0; bit < PINS_PER_PHY; bit++)  //PHY bit
            {
                if (bit != dq_dbi_bit)  //don't sweep DBI pin yet, otherwise it will mess up with other pbit results
                {
                    // reset rest of per-bit to max value to make sure they all pass. 
                    DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                                   bit, 
                                                   1,   // 1 for TX.
                                                   cs, 
                                                   0);
                }
            }
                
            for (perbit = 0; perbit <= PERBIT_CDC_MAX_VALUE; perbit++)
            {
                // Sweep all of the perbit at once
                DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                               dq_dbi_bit, 
                                               1,   // 1 for TX.
                                               cs, 
                                               perbit);
                // Reset the compare results
                for (bit = 0; bit < PINS_PER_PHY; bit++)
                {
                    compare_result_acc[byte_lane][dq_dbi_bit]  = 0x0;
                }
        
                for(loopcnt = training_params_ptr->wr_dqdqs.max_loopcnt; loopcnt > 0 ; loopcnt--)
                {         
#if DSF_PXI_TRAINING_EN
                    compare_result_DBI = DDRSS_mem_read_per_byte_DBI_phase_PXI(ddr, ch, cs, 5, 0x0);    //ddr, ch, cs, read_test_loop_cnt, phase
#else
                    // The write pattern. 
                    DDRSS_mem_write(ddr, ch, cs); 
                    
                    // Clear the compare results
                    compare_result_DBI = DDRSS_mem_read_per_byte_DBI_phase(ddr, ch, cs, dq, 0x0);
#endif
                    
                    if (compare_result_DBI != NULL)
                    {
                        compare_result_acc [byte_lane][dq_dbi_bit] += 
                        compare_result_DBI [byte_lane];
                    }
                }

                if(compare_result_acc[byte_lane][dq_dbi_bit] == 0x0)
                {
                    perbit_cdc[byte_lane][dq_dbi_bit] = perbit;
                }

            } // perbit loop
        } // byte loop
    }

    // Populate the PHY per-bit lanes with the trained values
    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {        
        for (bit = 0; bit < PINS_PER_PHY; bit ++)
        {
            DDR_PHY_hal_cfg_pbit_dq_delay((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                           bit, 
                                           1,   // 1 for TX.
                                           cs, 
                                           perbit_cdc[byte_lane][bit]);
    
            training_data_ptr->results.wr_dqdqs.perbit_delay[ch][cs][byte_lane][bit] = perbit_cdc[byte_lane][bit];
#if DSF_WR_DQDQS_TRAINING_LOG
            ddr_printf(DDR_NORMAL,"  Byte %d PHY bit %d WR Perbit = %d\n",
                                    byte_lane,bit, perbit_cdc[byte_lane][bit]);
#endif
        }
    }
    
}  


void DDRSS_WR_coarse_fine_phase_schmoo (DDR_STRUCT *ddr, 
                                                       uint8 ch,
                                                       uint8 cs,
                                                       PHY_BUS dq,
                                                       training_data *training_data_ptr,
                                                       training_params_t *training_params_ptr,
                                                       ddrss_rdwr_dqdqs_local_vars *local_vars,
                                                       uint32 clk_freq_khz)
{
    uint32 dq0_ddr_phy_base     = 0;
    uint8 *compare_result       = 0;
    uint8  phase                = 0;
    uint8  coarse_cdc_value     = 0;
    uint8  fine_cdc_value       = 0;
    uint8  byte_lane            = 0;
#if DSF_WRLVL_TRAINING_EN
    uint8  clk_idx              = 0;
    uint8  prfs_index           = 0;
#endif
    uint8   max_cdc_value       = 0;
    uint32    half_cycle_steps  = 0;
    uint32    full_cycle_steps  = 0;
    uint8  half_cycle_steps_max = 0;
    uint8  loop_count           = 0;
    uint8  all_byte_pass        = 0;
    uint8  index                = 0;
    //uint8  stop_index           = 0;
    uint8  coarse_dq_error_count[NUM_DQ_PCH][PHASE] = {{0}};
    uint8             first_pass[NUM_DQ_PCH][PHASE] = {{0}};
    uint8          dq_half_cycle[NUM_DQ_PCH]        = {0};
    uint8          dq_full_cycle[NUM_DQ_PCH]        = {0};
    uint8            cycle_count[NUM_DQ_PCH]        = {0};
    uint8     coarse_wrlvl_delay[NUM_DQ_PCH]        = {0};
    uint8     fine_wrlvl_delay  [NUM_DQ_PCH]        = {0};
    

    //set the PHY DQ base address
    dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

    //Calculate half and full cycles in terms of coarse steps
    half_cycle_steps = (((CONVERT_CYC_TO_PS / clk_freq_khz) / 2) / COARSE_STEP_IN_PS);
    full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
  
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi, clk
#endif

    //Determine the prfs index for the current clk freq. This prfs index is used to intialize WRLVL delays
#if DSF_WRLVL_TRAINING_EN
    for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    prfs_index = clk_idx + 1;
#endif

    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
    {
 #if DSF_WRLVL_TRAINING_EN 
        // Initialize the WRLVL delays
        coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[prfs_index][ch][cs][byte_lane];
        fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[prfs_index][ch][cs][byte_lane];
#endif 
        //Determine the half and full cycle delays for each byte lane.
        dq_half_cycle[byte_lane] = DDR_PHY_hal_sta_wrlvl_dq_half (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), cs); 
        dq_full_cycle[byte_lane] = DDR_PHY_hal_sta_wrlvl_dq_full (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), cs);
    }
   

    max_cdc_value = ((full_cycle_steps + 1) > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : (full_cycle_steps + 1);
    half_cycle_steps_max = (half_cycle_steps + 1);
    memset(local_vars->coarse_schmoo.coarse_dq_clk_dcc_info,
           0,
           (NUM_DQ_PCH * NUM_CS * RX_DCC));


        //Perform 1D write schmoo in fine steps
        //CDC schmoo loop: Coarse CDC loop
    for(coarse_cdc_value = training_params_ptr->wr_dqdqs.coarse_cdc_start_value;
        coarse_cdc_value <= max_cdc_value;
        coarse_cdc_value += training_params_ptr->wr_dqdqs.coarse_cdc_step)
    {
        for (byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            if((coarse_cdc_value >= half_cycle_steps_max) && (coarse_cdc_value < max_cdc_value) && (cycle_count[byte_lane] < 2) && 
            ((coarse_dq_error_count[byte_lane][0] != 0) && (first_pass[byte_lane][0] != 1)) &&
            ((coarse_dq_error_count[byte_lane][1] != 0) && (first_pass[byte_lane][1] != 1)))
            {
                cycle_count[byte_lane]    = cycle_count[byte_lane] + 1;
                dq_half_cycle[byte_lane]  = dq_half_cycle[byte_lane] + ((cycle_count[byte_lane] >> 0) & 0x1);
                dq_full_cycle[byte_lane]  = dq_full_cycle[byte_lane] + ((cycle_count[byte_lane] >> 1) & 0x1);
                coarse_cdc_value = 0; 
            }

            //Program CDC values to all the DQ bytes
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                           coarse_cdc_value, 
                                              1, 1, cs);   // 1 for coarse_delay_mode. 1 for hp_mode. 
         }
         //Fine CDC loop. For every Coarse CDC setting , schmoo 6 fine steps.
        for (fine_cdc_value = training_params_ptr->wr_dqdqs.fine_cdc_start_value;
             fine_cdc_value < FINE_STEPS_PER_COARSE;
             fine_cdc_value += training_params_ptr->wr_dqdqs.fine_cdc_step)
        {              
            for (byte_lane = 0; byte_lane < dq; byte_lane++) 
            {     
               // coarse_cdc_index = (coarse_cdc_value / training_params_ptr->wr_dqdqs.coarse_cdc_step);    
                DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                              fine_cdc_value, 
                                              0, 1, cs);   // 0 for fine_delay_mode. 1 for hp_mode.                                            
                DDR_PHY_hal_cfg_wrlvl_half((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), cs, dq_half_cycle[byte_lane]);                
                DDR_PHY_hal_cfg_wrlvl_full((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), cs, dq_full_cycle[byte_lane]);              
                DDRSS_CDC_Retimer (ddr, 
                                    cs, 
                                    coarse_cdc_value, 
                                    fine_cdc_value, 
                                    coarse_wrlvl_delay[byte_lane],
                                    fine_wrlvl_delay[byte_lane],
                                    (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                     clk_freq_khz);  // 0 for fine_delay.                            
            }//end of byte_lane loop
            for(phase = 0; phase < 2; phase++)
            {
                coarse_dq_error_count[byte_lane][phase] = 0;
                for(loop_count = training_params_ptr->wr_dqdqs.max_loopcnt; loop_count > 0 ; loop_count--)
                {                 
                // The write pattern. 
#if DSF_PXI_TRAINING_EN
                DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1);           //ddr, ch, cs, dbi, prbs
        
                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.  
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, phase, 1);    //ddr, ch, cs, loop cnt, phase, prbs
#else
                DDRSS_mem_write(ddr, ch, cs);
                
                // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
                compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, phase);       //ddr, ch, cs, dq, phase
#endif

                    for (byte_lane = 0; byte_lane < dq; byte_lane++) 
                    { 
                    // Accumulate the error for all byte_lanes, based on loop_count number of times.
                        coarse_dq_error_count[byte_lane][phase] += compare_result[byte_lane];
                    
                    // Update a pass flag to keep track to the first pass that occured.
                    //Record the coarse/fine_cdc_values, half/full_cycle values 
                    //for first passing edge of each byte_lane of every phase. Thus,
                    // determine the passing edge of phase 0 and 1.
                        if ((coarse_dq_error_count[byte_lane][phase] == 0)  && (loop_count == 1) && (first_pass[byte_lane][phase] == 0))
                        {
                            first_pass[byte_lane][phase] = 1;
                            all_byte_pass++;
                            local_vars->coarse_schmoo.wr_dcc_1ST_pass_index[byte_lane][phase]  = index;
                            local_vars->coarse_schmoo.wr_dcc_1ST_pass_coarse[byte_lane][phase] = coarse_cdc_value;
                            local_vars->coarse_schmoo.wr_dcc_1ST_pass_fine[byte_lane][phase]   = fine_cdc_value;
                            local_vars->coarse_schmoo.wr_dcc_1ST_pass_half_cycle[byte_lane][phase] = dq_half_cycle[byte_lane]; 
                            local_vars->coarse_schmoo.wr_dcc_1ST_pass_full_cycle[byte_lane][phase] = dq_full_cycle[byte_lane];
                        }
                        //Store the corresponding pass/fails in  local_vars->coarse_schmoo.coarse_dq_clk_dcc_info[][][CLK_DCC_OFFSET_RANGE =0][][]
                        local_vars->coarse_schmoo.coarse_dq_clk_dcc_info[byte_lane][cs][phase][index] = coarse_dq_error_count[byte_lane][phase];
                        
                     }//byte_lane_count
                 } // LOOP_COUNT 
                 
             }//phase_count
            index ++;
            if(all_byte_pass == (PHASE * dq))
                break;
         }
        if(all_byte_pass == (PHASE * dq))
            break;
   }
    // stop_index = index - 1;
    // return stop_index
    
}


boolean DDRSS_midpoint_to_CDC_lpddr4 (
                               DDR_STRUCT *ddr,
                               uint32 middle,
                               uint32 clk_freq_in_khz,
                               uint8  ch,
                               uint8  cs,
                               training_data *training_data_ptr,
                               uint8  training_type, /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs*/
                               uint8  phy_inx,
                               uint8 freq_inx
                              )
{
  uint32 coarse_cdc;
  uint32 fine_delay;
  uint32 fine_cdc;

  uint32 ddr_phy_chn_base;
  wrlvl_params_struct convert_cdc_info;

  uint32        period = 0;  
  
  period = CONVERT_CYC_TO_PS / clk_freq_in_khz;

  
  // if training is rd dqdqs, write the delay value to CSRs.
  if (training_type == TRAINING_TYPE_RD_DQDQS ) 
  {
     ddr_phy_chn_base = REG_OFFSET_DDR_PHY_CH(ch);

     // Start from freq band 3 (800MHz) up to band7 (1866MHz).
     //if((clk_freq_in_khz > F_RANGE_2) && (clk_freq_in_khz < F_RANGE_7))
     if((clk_freq_in_khz > LOWEST_SCALED_PRFS_FREQ) && (clk_freq_in_khz < HIGHEST_TRAINED_FPRS_FREQ))
     {
        // When coarse delay exceed max value of CDC CSR, transfer the exceeding part to fine delay
        if (middle > ((COARSE_CDC_MAX_VALUE + 1) * COARSE_STEP_IN_PS))
        {
           coarse_cdc = COARSE_CDC_MAX_VALUE;
           fine_delay = (middle - (COARSE_CDC_MAX_VALUE + 1) * COARSE_STEP_IN_PS);
        }
        else
        {
           coarse_cdc = (middle / COARSE_STEP_IN_PS);
           fine_delay = (middle % COARSE_STEP_IN_PS);
        }

        fine_cdc = fine_delay / FINE_STEP_IN_PS;

        // When even fine delay exceeds max value of CDC CSR, return FALSE
        if (fine_cdc > FINE_CDC_MAX_VALUE) 
        {
            return FALSE;
        }
        else
        {
            DDR_PHY_hal_cfg_cdcext_slave_rd (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                             cs,
                                             coarse_cdc,
                                             1/*coarse*/,
                                             HP_MODE,
                                             freq_inx
                                            );

            DDR_PHY_hal_cfg_cdcext_slave_rd (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                             cs,
                                             fine_cdc,
                                             0/*fine*/,
                                             HP_MODE,
                                             freq_inx
                                            );

            training_data_ptr->results.rd_dqdqs.coarse_cdc[freq_inx][ch][cs][phy_inx] = coarse_cdc;
            training_data_ptr->results.rd_dqdqs.fine_cdc  [freq_inx][ch][cs][phy_inx] = fine_cdc;
            
            // Copy the rank0 value to rank1 to store in data structure.
            //if ((clk_freq_in_khz < F_RANGE_4) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
            if ((clk_freq_in_khz <= LOWEST_TRAINED_FPRS_FREQ) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
            {
               DDR_PHY_hal_cfg_cdcext_slave_rd (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                                1,
                                                coarse_cdc,
                                                1/*coarse*/,
                                                HP_MODE,
                                                freq_inx
                                               );

               DDR_PHY_hal_cfg_cdcext_slave_rd (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                                1,
                                                fine_cdc,
                                                0/*fine*/,
                                                HP_MODE,
                                                freq_inx
                                               );

               training_data_ptr->results.rd_dqdqs.coarse_cdc[freq_inx][ch][1][phy_inx] = coarse_cdc;
               training_data_ptr->results.rd_dqdqs.fine_cdc  [freq_inx][ch][1][phy_inx] = fine_cdc;
            }
        }
     }
  }
  
  else if (training_type == TRAINING_TYPE_CA_VREF )
  {
    // This API does not handle the last three parameters for CA Vref training, they are used only by WR DQDQS training.
    DDRSS_cdc_convert (ddr, &convert_cdc_info, middle, period, 0, 0, 0);  // 0: ca_vref training_type.
    
    DDRSS_writing_ext_CSR_lpddr4 (ddr,
                                  ch,
                                  cs,
                                  &convert_cdc_info,
                                  training_data_ptr,
                                  training_type,
                                  phy_inx,
                                  freq_inx
                                  );
  }

  return TRUE;
}

void DDRSS_writing_ext_CSR_lpddr4 (DDR_STRUCT *ddr,
                                   uint8 ch,
                                   uint8 cs,
                                   wrlvl_params_struct *convert_cdc_ptr,
                                   training_data *training_data_ptr,
                                   uint8 training_type, /* 0: CA Vref training; 1:wr_dqdqs training; 2: rd_dqdqs training */
                                   uint8 phy_inx,
                                   uint8 freq_inx
                                  )
{
   uint32 ddr_phy_chn_base;
   uint8 retmr_value = 0;
    
   ddr_phy_chn_base = REG_OFFSET_DDR_PHY_CH(ch);

   // CA Vref training. freq_inx will be 6, for the highest frequency that is trained.
    if (training_type == TRAINING_TYPE_CA_VREF)  
    {
       DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                        cs,
                                        (*convert_cdc_ptr).coarse_dqs_delay,
                                        1/*coarse*/,
                                        HP_MODE,
                                        freq_inx
                                       );

       DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                        cs,
                                        (*convert_cdc_ptr).fine_dqs_delay,
                                        0/*fine*/,
                                        HP_MODE,
                                        freq_inx
                                       );

       DDR_PHY_hal_cfg_wrext_ctl_update (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                         freq_inx,
                                         cs,
                                         (*convert_cdc_ptr).dqs_retmr,
                                         (*convert_cdc_ptr).dqs_half_cycle,
                                         (*convert_cdc_ptr).dqs_full_cycle
                                        );

       training_data_ptr->results.ca_vref.coarse_cdc     [0][ch][cs][phy_inx] = (*convert_cdc_ptr).coarse_dqs_delay;
       training_data_ptr->results.ca_vref.fine_cdc       [0][ch][cs][phy_inx] = (*convert_cdc_ptr).fine_dqs_delay;
       training_data_ptr->results.ca_vref.dq_retmr       [0][ch][cs][phy_inx] = (*convert_cdc_ptr).dqs_retmr;
       training_data_ptr->results.ca_vref.dq_half_cycle  [0][ch][cs][phy_inx] = (*convert_cdc_ptr).dqs_half_cycle;
       training_data_ptr->results.ca_vref.dq_full_cycle  [0][ch][cs][phy_inx] = (*convert_cdc_ptr).dqs_full_cycle;
       
       // CA training happens only for rank0 and only at the highest freq, copy the rank0 value to rank1 to store in data structure.
       if( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH)
       {
          DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           1,
                                           (*convert_cdc_ptr).coarse_dqs_delay,
                                           1/*coarse*/,
                                           HP_MODE,
                                           freq_inx
                                          );

          DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           1,
                                           (*convert_cdc_ptr).fine_dqs_delay,
                                           0/*fine*/,
                                           HP_MODE,
                                           freq_inx
                                          );

          DDR_PHY_hal_cfg_wrext_ctl_update (ddr_phy_chn_base + CA0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                            freq_inx,
                                            1,
                                            (*convert_cdc_ptr).dqs_retmr,
                                            (*convert_cdc_ptr).dqs_half_cycle,
                                            (*convert_cdc_ptr).dqs_full_cycle
                                           );

          training_data_ptr->results.ca_vref.coarse_cdc     [0][ch][1][phy_inx] = (*convert_cdc_ptr).coarse_dqs_delay;
          training_data_ptr->results.ca_vref.fine_cdc       [0][ch][1][phy_inx] = (*convert_cdc_ptr).fine_dqs_delay;
          training_data_ptr->results.ca_vref.dq_retmr       [0][ch][1][phy_inx] = (*convert_cdc_ptr).dqs_retmr;
          training_data_ptr->results.ca_vref.dq_half_cycle  [0][ch][1][phy_inx] = (*convert_cdc_ptr).dqs_half_cycle;
          training_data_ptr->results.ca_vref.dq_full_cycle  [0][ch][1][phy_inx] = (*convert_cdc_ptr).dqs_full_cycle;
       }
    }

    // wr dqdqs training
    if (training_type == TRAINING_TYPE_WR_DQDQS)  
    {
       DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                        cs,
                                        training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][cs][phy_inx],
                                        1/*coarse*/,
                                        HP_MODE,
                                        freq_inx
                                       );

       DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                        cs,
                                        training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][cs][phy_inx],
                                        0/*fine*/,
                                        HP_MODE,
                                        freq_inx
                                       );
       // Read the retimer status. No need to calculate and WR again since its already been done.
       retmr_value = DDR_PHY_hal_sta_wrlvl_dq_retmr(ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET, cs);
                                
       DDR_PHY_hal_cfg_wrext_ctl_update (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                         freq_inx,
                                         cs,
                                         retmr_value, 
                                         training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][cs][phy_inx],
                                         training_data_ptr->results.wr_dqdqs.dq_full_cycle[freq_inx][ch][cs][phy_inx]
                                        );

       // write dq dqs training should pass the max and min out
       DDR_PHY_hal_cfg_dq_vref_dqs2dq_max (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           cs,
                                           freq_inx,
                                           training_data_ptr->results.wr_dqdqs.coarse_max_eye_left_boundary_cdc_value [freq_inx][ch][cs][phy_inx],
                                           1/*coarse*/
                                          );
       DDR_PHY_hal_cfg_dq_vref_dqs2dq_min (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           cs,
                                           freq_inx,
                                           training_data_ptr->results.wr_dqdqs.coarse_max_eye_right_boundary_cdc_value [freq_inx][ch][cs][phy_inx],
                                           1/*coarse*/
                                          );

       training_data_ptr->results.wr_dqdqs.coarse_cdc    [freq_inx][ch][cs][phy_inx] = training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][cs][phy_inx];
       training_data_ptr->results.wr_dqdqs.fine_cdc      [freq_inx][ch][cs][phy_inx] = training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][cs][phy_inx];
       training_data_ptr->results.wr_dqdqs.dq_retmr      [freq_inx][ch][cs][phy_inx] = retmr_value;
       training_data_ptr->results.wr_dqdqs.dq_half_cycle [freq_inx][ch][cs][phy_inx] = training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][cs][phy_inx];
       training_data_ptr->results.wr_dqdqs.dq_full_cycle [freq_inx][ch][cs][phy_inx] = training_data_ptr->results.wr_dqdqs.dq_full_cycle[freq_inx][ch][cs][phy_inx];

       
       // For 547MHz; 777MHz and 1017MHz training, copy the rank0 value to rank1 to store in data structure.
       if ((freq_inx > 0) && (freq_inx < 5) && ( ddr->detected_ddr_device[0].populated_chipselect == DDR_CS_BOTH))
       {
          DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           1,
                                           training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][0][phy_inx],
                                           1/*coarse*/,
                                           HP_MODE,
                                           freq_inx
                                          );

          DDR_PHY_hal_cfg_cdcext_slave_wr (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                           1,
                                           training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][0][phy_inx],
                                           0/*fine*/,
                                           HP_MODE,
                                           freq_inx
                                          );
          // Read the retimer status. No need to calculate and program again since its already been done.
          retmr_value = DDR_PHY_hal_sta_wrlvl_dq_retmr(ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET, 0);
          
          DDR_PHY_hal_cfg_wrext_ctl_update (ddr_phy_chn_base + DQ0_DDR_PHY_OFFSET + phy_inx * DDR_PHY_OFFSET,
                                            freq_inx,
                                            1,
                                            retmr_value,
                                            training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][0][phy_inx],
                                            training_data_ptr->results.wr_dqdqs.dq_full_cycle[freq_inx][ch][0][phy_inx]
                                           );

          training_data_ptr->results.wr_dqdqs.coarse_cdc    [freq_inx][ch][1][phy_inx] = training_data_ptr->results.wr_dqdqs.coarse_cdc[freq_inx][ch][0][phy_inx];
          training_data_ptr->results.wr_dqdqs.fine_cdc      [freq_inx][ch][1][phy_inx] = training_data_ptr->results.wr_dqdqs.fine_cdc[freq_inx][ch][0][phy_inx];
          training_data_ptr->results.wr_dqdqs.dq_retmr      [freq_inx][ch][1][phy_inx] = retmr_value;
          training_data_ptr->results.wr_dqdqs.dq_half_cycle [freq_inx][ch][1][phy_inx] = training_data_ptr->results.wr_dqdqs.dq_half_cycle[freq_inx][ch][0][phy_inx];
          training_data_ptr->results.wr_dqdqs.dq_full_cycle [freq_inx][ch][1][phy_inx] = training_data_ptr->results.wr_dqdqs.dq_full_cycle[freq_inx][ch][0][phy_inx];
       }
    }
     
}



void DDRSS_DIT_Slope(DDR_STRUCT *ddr,
                     uint8  ch,
                     uint8  cs,
                     uint8  die,
                     uint32 clk_freq_khz,
                     uint16 (*dit_mid_count))
{

  uint16  dit_count                         = 0;
  uint8   range                             = 0;
  uint8   index                             = 0;
  uint8   mid                               = 0;
  uint32  dit_acquisition_time              = 0;
  uint32  dit_dram_clk_period               = 0;

//  uint32  dit_training_freq                 = 0;
  uint32  dit_training_period                 = 0;
  uint32  dit_ps_per_count                  = 0;
  uint32  dit_delta_count[NUM_DIT_COUNT+1]  = {0};

  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

  // Fetch the boot training frequency
    dit_training_period = CONVERT_CYC_TO_PS/training_data_ptr->results.dit.dit_training_freq;
    // Calculate the clock period
  dit_dram_clk_period =  CONVERT_CYC_TO_PS/clk_freq_khz;

  // Fetch the boot training DIT count result
  dit_count = training_data_ptr->results.dit.dit_count[ch][cs][die];

  // Scale the DIT count to the current clock frequency
  dit_count = (dit_count * dit_dram_clk_period) / dit_training_period;


  // Calculate the clock period
//  dit_dram_clk_period =  CONVERT_CYC_TO_PS/clk_freq_khz;

  // Calculate the acquisition time
  //dit_acquisition_time = (DIT_RUNTIME_FREQ * dit_dram_clk_period);//TOFIX
  dit_acquisition_time = (training_data_ptr->results.dit.dit_runtime_count * dit_dram_clk_period);

  // Populate the center of the array with the scaled DIT count
  dit_delta_count[NUM_DIT_COUNT/2] = dit_count;

  // Calculate the time (ps) per DIT count
  dit_ps_per_count = dit_acquisition_time/dit_count;

  // Calculate the 10ps to 50ps range of the array
  for (range=1;range<=NUM_DIT_COUNT/2;range++)
  {
    // Determine the index for the delta count array
    index = range + NUM_DIT_COUNT/2;

    // Calculate the Delta count when the clock tree changes in units of 10ps (10ps * two ring oscillator half cycles)
    dit_delta_count[index] = dit_acquisition_time / (dit_ps_per_count - (range * 20));
  }

  index = (NUM_DIT_COUNT/2)-1;

  // Calculate the -50ps to -10ps range of the array
  for (range=1;range<=NUM_DIT_COUNT/2;range++)
  {
    // Calculate the Delta count when the clock tree changes in units of 10ps (10ps * two ring oscillator half cycles)
    dit_delta_count[index] = dit_acquisition_time / (dit_ps_per_count + (range * 20));
    index--;
  }

  // Poplulate the return array with the midpoints between the delta counts
  for (mid=0;mid<=NUM_DIT_COUNT-1;mid++)
  {
    // Calculate the midpoints
    dit_mid_count[mid] = (dit_delta_count[mid] + dit_delta_count[mid+1])/2;
  }
}

#if DSF_DIT_BYTE_MODE_EN

void DDRSS_DIT_Capture(uint8 ch,
                       uint8 cs,
                       uint16 dit_runtime_count,
                       uint32 *MR_19_18_data)
{
  uint32 MR23_value      = 0;
  DDR_CHANNEL ch_1hot    = DDR_CH_NONE;
  DDR_CHIPSELECT cs_1hot = DDR_CS_NONE;
  uint32 reg_offset_shke = 0;
  

  // Base pointer to SHKE
  reg_offset_shke = REG_OFFSET_SHKE(ch);

  // Convert the channel to one-hot for BIMC functions
  ch_1hot = CH_1HOT(ch);
  cs_1hot = CS_1HOT(cs);

  // Decode the runtime count for the DRAM MR23 register
  if (dit_runtime_count < 2048)
  {
    MR23_value = dit_runtime_count / 16;
  }
  else
  {
    if (dit_runtime_count == 2048)
      MR23_value = 0x40;
    else if (dit_runtime_count == 4096)
      MR23_value = 0x80;
    else if (dit_runtime_count == 8196)
      MR23_value = 0xC0;
  }

  // Set DQS interval timer runtime setting
  BIMC_MR_Write (ch_1hot, cs_1hot, JEDEC_MR_23, MR23_value);

  // Set the BIMC SHKE control register for rank
  HWIO_OUTXF2 (reg_offset_shke, SHKE_MPC_CNTL,ISSUE_TO_RANK,MPC_START,cs_1hot,1);

  // Poll for start asserted
  while(HWIO_INXF (reg_offset_shke, SHKE_MPC_CNTL,MPC_START) == 1);

  // Wait for the DRAM Oscillator to acquire the count
  seq_wait(20,US);

  // Read the DRAM Oscillator counter
  MR_19_18_data[0] = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_18);
  MR_19_18_data[1] = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_19);

}

void DDRSS_DIT_Read (DDR_STRUCT *ddr,
                     uint8  ch,
                     uint8  cs,
                     training_params_t *training_params_ptr,
                     uint8  dit_ave,
                     uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                     uint32 clk_freq_khz
                     )
{
    uint16 dit_die_count[2]     = {0};
    uint32 dit_die_count_acc[2] = {0};
    uint32 dit_die_count_max[2] = {0};
    uint32 dit_die_count_min[2] = {0xffffffff,0xffffffff};
    uint32 MR18_data            = 0;
    uint32 MR19_data            = 0;
    uint32 MR_19_18_data[2]     = {0};
    uint16 dit_runtime_count    = 0;
    uint8 loopcnt               = 0;
    uint8 die                   = 0;
    uint8 max_loopcnt           = 0;
	IO_WIDTH dit_io_width       = X16MODE; 
	uint8 die_index				= 0;
	uint16 invalid_count_flag   = 0;


    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Base pointer to SHKE

    // Calculate the clock period

    // Encode the channel and rank for the BIMC functions

    // set the time between subsequent interval time operation

    // Search for the optimal run time count for the first pass of the DIT Read function
//    {
     // If the runtime count is established, load from the data structure
     dit_runtime_count = training_data_ptr->results.dit.dit_runtime_count;
//    }

    // Read the max_loopcnt from the training params data structure
    max_loopcnt = training_params_ptr->dit.max_loopcnt;

    // Write the sample count to the results data structure for DTTS
    training_data_ptr->results.dit.dit_loop_count = max_loopcnt;
    //training_data_ptr->results.dit.dit_trac_ndx = 10; // TODO Tao Wang

    // Reset the loop count
    loopcnt = 0;

	//io_width read from DDR_STRUCT
	dit_io_width = ((cs == 0 )? 
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs0 :
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs1);
	die_index = (dit_io_width == X8MODE) ? 1: 0; // 2 dies per ch/cs for x 8 mode and 1 die / ch/cs for x16 mode
		

    // Read and average multiple DRAM Oscillator counts
    while (loopcnt < max_loopcnt)
    {

     // Read the DRAM DQS oscillator counter
      DDRSS_DIT_Capture(ch,
                        cs,
                        dit_runtime_count,
                        MR_19_18_data);

      MR18_data = MR_19_18_data[0];
      MR19_data = MR_19_18_data[1];
	  if (dit_io_width == X8MODE)
	  {
	       						
          invalid_count_flag = (
            					// Die 0 both MR18 and MR19 all zeros
            					(((MR18_data & 0x000000FF) == 0x00)   && ((MR19_data & 0x000000FF) == 0x00))   ||

            					// Die 1 both MR18 and MR19 all zeros
            					((((MR18_data>>16) & 0x00FF) == 0x00) && (((MR19_data>>16) & 0x00FF) == 0x00)) ||

            					// Die 0 both MR18 and MR19 all ones
            					(((MR18_data & 0xFF) == 0xFF)         && ((MR19_data & 0xFF) == 0xFF))         ||

           						 // Die 1 both MR18 and MR19 all ones
            					((((MR18_data>>16) & 0x00FF) == 0xFF) && (((MR19_data>>16) & 0X00FF) == 0xFF))
            					);
	  }
	  else
	  {
	       						// Die 0 both MR18 and MR19 all zeros
          invalid_count_flag = (((MR18_data & 0x00FF) == 0x00)   && ((MR19_data & 0x00FF) == 0x00))   ||

          						// Die 0 both MR18 and MR19 all ones
          						(((MR18_data & 0xFF) == 0xFF)         && ((MR19_data & 0xFF) == 0xFF)) ;       

	  }
      // Discard illegal count results
      if(!invalid_count_flag)
      {

        // Isolate the die counter results
 //       dit_die_count[0] = ((MR19_data & 0x000000ff)<<8) |  (MR18_data & 0x000000ff);
//        dit_die_count[1] = ((MR19_data & 0x00ff0000)>>8) | ((MR18_data & 0x00ff0000)>>16);

        // Calculate the minimum and maximum counts
        for (die=0; die <= die_index; die++)
        {
			//Isolate the die counter results
//		  dit_die_count[die] = ((MR18_data & (0x00FF << (8 * die))) >> (8 * die)) |
//		  						((MR19_data & (0x00FF << (8 * die))) << (8 * (1 -die)));
			//Isolate the die counter results
		  dit_die_count[die] = ((MR18_data & (0xFF << (16 * die))) >> (16 * die)) | 
		  						(((MR19_data & (0xFF << (16 * die))) >> (16 * die)) << 8 );
			
          // Accumulate the per die counter results
          dit_die_count_acc[die] += dit_die_count[die];

          // Check for the maximum
          if (dit_die_count[die] > dit_die_count_max[die])
            dit_die_count_max[die] = dit_die_count[die];

          // Check for the minimum
          if (dit_die_count[die] < dit_die_count_min[die])
            dit_die_count_min[die] = dit_die_count[die];
        }

        loopcnt++;
      }
    } // while

    // Process the accumulated count results
    for (die=0; die <= die_index; die++)
    {
      // Remove the minimum and maximum counts
      dit_die_count[die] = dit_die_count_acc[die] - (dit_die_count_max[die] + dit_die_count_min[die]);

      // Average the accumulated counts (after removing the min and max)
      dit_die_count[die] = dit_die_count[die]/(max_loopcnt-2);

      // Average any previous values with the new results
      dit_count[ch][cs][die] = (dit_die_count[die] + dit_count[ch][cs][die])/(dit_ave + 1);
 
    }
}


void DDRSS_DIT_Runtime(DDR_STRUCT *ddr,
                     uint8  ch,
                     uint8  cs,
                     training_params_t *training_params_ptr,
                     uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                     uint32 clk_freq_khz
                     )
{
    uint16 dit_die_count[2]     = {0};
    uint32 MR18_data            = 0;
    uint32 MR19_data            = 0;
    uint32 MR_19_18_data[2]     = {0};
    uint32 dit_dram_clk_period  = 0;
    uint16 dit_runtime_table[4] = {1008, 2048, 4096, 8192};
    uint16 dit_runtime_count    = 0;
    uint32 dit_delta_count[2]   = {0};
    uint32 dit_ps_per_count[2]  = {0};
    uint32 dit_acquisition_time = 0;
    uint8 loopcnt               = 0;
    uint8 die                   = 0;
	IO_WIDTH dit_io_width       = X16MODE; 
	uint8 die_index				= 0;
	uint16 dit_delta_count_flag   = 1;
	uint16 invalid_count_flag   = 0;

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Base pointer to SHKE

    // Calculate the clock period
    dit_dram_clk_period =  CONVERT_CYC_TO_PS/clk_freq_khz;

    // Encode the channel and rank for the BIMC functions

    // set the time between subsequent interval time operation

    // Search for the optimal run time count for the first pass of the DIT Read function
//    {

	//io_width read from DDR_STRUCT
	dit_io_width = (cs == 0 )? 
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs0 :
				(IO_WIDTH)ddr->detected_ddr_device[ch].interface_width_cs1;
	die_index = (dit_io_width == X8MODE) ? 1: 0; // 2 dies per ch/cs for x 8 mode and 1 die / ch/cs for x16 mode

      // Normalize the results if needed by increasing the acquisition count
 //   while ((dit_delta_count[0] < DIT_NORMAL_DELTA) /*&& (dit_delta_count[1] < DIT_NORMAL_DELTA)*/ && (loopcnt < 4))
 	while (dit_delta_count_flag && (loopcnt < 4))
    {
        // Calculate the MR23 acquisition count
        dit_runtime_count    = dit_runtime_table[loopcnt];

        DDRSS_DIT_Capture(ch,
                          cs,
                          dit_runtime_count,
                          MR_19_18_data);

        MR18_data = MR_19_18_data[0];
        MR19_data = MR_19_18_data[1];
		if (dit_io_width == X8MODE)
	  	{
			invalid_count_flag = (
								  // Die 0 both MR18 and MR19 all zeros
								  (((MR18_data & 0x000000FF) == 0x00)	&& ((MR19_data & 0x000000FF) == 0x00))	 ||
			
								  // Die 1 both MR18 and MR19 all zeros
								  ((((MR18_data>>16) & 0x00FF) == 0x00) && (((MR19_data>>16) & 0x00FF) == 0x00)) ||
			
								  // Die 0 both MR18 and MR19 all ones
								  (((MR18_data & 0xFF) == 0xFF) 		&& ((MR19_data & 0xFF) == 0xFF))		 ||
			
								   // Die 1 both MR18 and MR19 all ones
								  ((((MR18_data>>16) & 0x00FF) == 0xFF) && (((MR19_data>>16) & 0X00FF) == 0xFF))
								  );

	  	}
	  	else
	  	{
	       						// Die 0 both MR18 and MR19 all zeros
          invalid_count_flag = (((MR18_data & 0x00FF) == 0x00)   && ((MR19_data & 0x00FF) == 0x00))   ||

          						// Die 0 both MR18 and MR19 all ones
          						(((MR18_data & 0xFF) == 0xFF)         && ((MR19_data & 0xFF) == 0xFF)) ;       

	  	}
        // Discard illegal count results
        if(!invalid_count_flag)
        {
          dit_acquisition_time = dit_runtime_count * dit_dram_clk_period;

          // Calculate the dit delta count
          for (die=0;die<=die_index;die++)
          {
			  //Isolate the die counter results
//			dit_die_count[die] = ((MR18_data & (0x00FF << (8 * die))) >> (8 * die)) |
//							  ((MR19_data & (0x00FF << (8 * die))) << (8 * (1 -die)));
			  //Isolate the die counter results
			dit_die_count[die] = ((MR18_data & (0xFF << (16 * die))) >> (16 * die)) | 
								  (((MR19_data & (0xFF << (16 * die))) >> (16 * die)) << 8 );

            dit_ps_per_count[die] = dit_acquisition_time / dit_die_count[die];
            dit_delta_count[die]  = dit_acquisition_time / (dit_ps_per_count[die] + 20);
            dit_delta_count[die]  = dit_die_count[die] - dit_delta_count[die];
          }

          // Update the results data structure with the revised runtime count
          if (training_data_ptr->results.dit.dit_runtime_count < dit_runtime_count)
          training_data_ptr->results.dit.dit_runtime_count = dit_runtime_count;
		  
		  if (dit_io_width == X8MODE)
		  {
		  	dit_delta_count_flag = (dit_delta_count[0] < DIT_NORMAL_DELTA) && (dit_delta_count[1] < DIT_NORMAL_DELTA)  ;
		  }
		  else
		  {
		  	dit_delta_count_flag = (dit_delta_count[0] < DIT_NORMAL_DELTA) ;
		  }
          loopcnt++;
        }
      }
}


#else

void DDRSS_DIT_Read (DDR_STRUCT *ddr,
                     uint8  ch,
                     uint8  cs,
                     training_params_t *training_params_ptr,
                     uint8  dit_ave,
                     uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                     uint32 clk_freq_khz
                     )
{
    uint16 dit_die_count[2]     = {0};
    uint32 dit_die_count_acc[2] = {0};
    uint32 dit_die_count_max[2] = {0};
    uint32 dit_die_count_min[2] = {0xffffffff,0xffffffff};
    uint16 MR18_data            = 0;
    uint16 MR19_data            = 0;
    uint16 MR_19_18_data[2]     = {0};
    uint16 dit_runtime_count    = 0;
    uint8 loopcnt               = 0;
    uint8 die                   = 0;
    uint8 max_loopcnt           = 0;

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Base pointer to SHKE

    // Calculate the clock period

    // Encode the channel and rank for the BIMC functions

    // set the time between subsequent interval time operation

    // Search for the optimal run time count for the first pass of the DIT Read function
//    {
     // If the runtime count is established, load from the data structure
     dit_runtime_count = training_data_ptr->results.dit.dit_runtime_count;
//    }

    // Read the max_loopcnt from the training params data structure
    max_loopcnt = training_params_ptr->dit.max_loopcnt;

    // Write the sample count to the results data structure for DTTS
    training_data_ptr->results.dit.dit_loop_count = max_loopcnt;
    //training_data_ptr->results.dit.dit_trac_ndx = 10; // TODO Tao Wang

    // Reset the loop count
    loopcnt = 0;

    // Read and average multiple DRAM Oscillator counts
    while (loopcnt < max_loopcnt)
    {

     // Read the DRAM DQS oscillator counter
      DDRSS_DIT_Capture(ch,
                        cs,
                        dit_runtime_count,
                        MR_19_18_data);

      MR18_data = MR_19_18_data[0];
      MR19_data = MR_19_18_data[1];

      // Discard illegal count results
      if(!(
          // Die 0 both MR18 and MR19 all zeros
          (((MR18_data & 0x000000FF) == 0x00)   && ((MR19_data & 0x000000FF) == 0x00))   ||

          // Die 1 both MR18 and MR19 all zeros
//          ((((MR18_data>>16) & 0x00FF) == 0x00) && (((MR19_data>>16) & 0x00FF) == 0x00)) ||

          // Die 0 both MR18 and MR19 all ones
          (((MR18_data & 0xFF) == 0xFF)         && ((MR19_data & 0xFF) == 0xFF))        // ||

          // Die 1 both MR18 and MR19 all ones
//          ((((MR18_data>>16) & 0x00FF) == 0xFF) && (((MR19_data>>16) & 0X00FF) == 0xFF))
        ))
      {

        // Isolate the die counter results
        dit_die_count[0] = ((MR19_data & 0x000000ff)<<8) |  (MR18_data & 0x000000ff);
//        dit_die_count[1] = ((MR19_data & 0x00ff0000)>>8) | ((MR18_data & 0x00ff0000)>>16);

        // Calculate the minimum and maximum counts
        for (die=0;die<=1;die++)
        {
          // Accumulate the per die counter results
          dit_die_count_acc[die] += dit_die_count[die];

          // Check for the maximum
          if (dit_die_count[die] > dit_die_count_max[die])
            dit_die_count_max[die] = dit_die_count[die];

          // Check for the minimum
          if (dit_die_count[die] < dit_die_count_min[die])
            dit_die_count_min[die] = dit_die_count[die];
        }

        loopcnt++;
      }
    } // while

    // Process the accumulated count results
    for (die=0;die<NUM_DIE_PCH;die++)
    {
      // Remove the minimum and maximum counts
      dit_die_count[die] = dit_die_count_acc[die] - (dit_die_count_max[die] + dit_die_count_min[die]);

      // Average the accumulated counts (after removing the min and max)
      dit_die_count[die] = dit_die_count[die]/(max_loopcnt-2);

      // Average any previous values with the new results
      dit_count[ch][cs][die] = (dit_die_count[die] + dit_count[ch][cs][die])/(dit_ave + 1);
 
    }
}

void DDRSS_DIT_Capture(uint8 ch,
                       uint8 cs,
                       uint16 dit_runtime_count,
                       uint16 (*MR_19_18_data))
{
  uint32 MR23_value      = 0;
  DDR_CHANNEL ch_1hot    = DDR_CH_NONE;
  DDR_CHIPSELECT cs_1hot = DDR_CS_NONE;
  uint32 reg_offset_shke = 0;

  // Base pointer to SHKE
  reg_offset_shke = REG_OFFSET_SHKE(ch);

  // Convert the channel to one-hot for BIMC functions
  ch_1hot = CH_1HOT(ch);
  cs_1hot = CS_1HOT(cs);

  // Decode the runtime count for the DRAM MR23 register
  if (dit_runtime_count < 2048)
  {
    MR23_value = dit_runtime_count / 16;
  }
  else
  {
    if (dit_runtime_count == 2048)
      MR23_value = 0x40;
    else if (dit_runtime_count == 4096)
      MR23_value = 0x80;
    else if (dit_runtime_count == 8196)
      MR23_value = 0xC0;
  }

  // Set DQS interval timer runtime setting
  BIMC_MR_Write (ch_1hot, cs_1hot, JEDEC_MR_23, MR23_value);

  // Set the BIMC SHKE control register for rank
  HWIO_OUTXF2 (reg_offset_shke, SHKE_MPC_CNTL,ISSUE_TO_RANK,MPC_START,cs_1hot,1);

  // Poll for start asserted
  while(HWIO_INXF (reg_offset_shke, SHKE_MPC_CNTL,MPC_START) == 1);

  // Wait for the DRAM Oscillator to acquire the count
  seq_wait(20,US);

  // Read the DRAM Oscillator counter
  MR_19_18_data[0] = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_18);
  MR_19_18_data[1] = BIMC_MR_Read (ch_1hot,cs_1hot,JEDEC_MR_19);

}


void DDRSS_DIT_Runtime(DDR_STRUCT *ddr,
                     uint8  ch,
                     uint8  cs,
                     training_params_t *training_params_ptr,
                     uint16 (*dit_count)[NUM_CS][NUM_DIE_PCH],
                     uint32 clk_freq_khz
                     )
{
    uint16 dit_die_count[2]     = {0};
    uint16 MR18_data            = 0;
    uint16 MR19_data            = 0;
    uint16 MR_19_18_data[2]     = {0};
    uint32 dit_dram_clk_period  = 0;
    uint16 dit_runtime_table[4] = {1008, 2048, 4096, 8192};
    uint16 dit_runtime_count    = 0;
    uint32 dit_delta_count[2]   = {0};
    uint32 dit_ps_per_count[2]  = {0};
    uint32 dit_acquisition_time = 0;
    uint8 loopcnt               = 0;
    uint8 die                   = 0;

    // Training data structure pointer
    training_data *training_data_ptr;
    training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

    // Base pointer to SHKE

    // Calculate the clock period
    dit_dram_clk_period =  CONVERT_CYC_TO_PS/clk_freq_khz;

    // Encode the channel and rank for the BIMC functions

    // set the time between subsequent interval time operation

    // Search for the optimal run time count for the first pass of the DIT Read function
//    {
      // Normalize the results if needed by increasing the acquisition count
      while ((dit_delta_count[0] < DIT_NORMAL_DELTA) /*&& (dit_delta_count[1] < DIT_NORMAL_DELTA)*/ && (loopcnt < 4))
      {
        // Calculate the MR23 acquisition count
        dit_runtime_count    = dit_runtime_table[loopcnt];

        DDRSS_DIT_Capture(ch,
                          cs,
                          dit_runtime_count,
                          MR_19_18_data);

        MR18_data = MR_19_18_data[0];
        MR19_data = MR_19_18_data[1];

        // Discard illegal count results
        if(!(
            // Die 0 both MR18 and MR19 all zeros
            (((MR18_data & 0x000000FF) == 0x00)   && ((MR19_data & 0x000000FF) == 0x00))   ||

            // Die 1 both MR18 and MR19 all zeros
  //          ((((MR18_data>>16) & 0x00FF) == 0x00) && (((MR19_data>>16) & 0x00FF) == 0x00)) ||   // Changed by Sagar

            // Die 0 both MR18 and MR19 all ones
            (((MR18_data & 0xFF) == 0xFF)         && ((MR19_data & 0xFF) == 0xFF))       //  ||    // Changed by Sagar

            // Die 1 both MR18 and MR19 all ones
 //           ((((MR18_data>>16) & 0x00FF) == 0xFF) && (((MR19_data>>16) & 0X00FF) == 0xFF))      // Changed by Sagar
            ))

        {

          // Isolate the die counter results into 16 bits
          dit_die_count[0] = ((MR19_data & 0x000000ff)<<8) |  (MR18_data & 0x000000ff);
//          dit_die_count[1] = ((MR19_data & 0x00ff0000)>>8) | ((MR18_data & 0x00ff0000)>>16);

          dit_acquisition_time = dit_runtime_count * dit_dram_clk_period;

          // Calculate the dit delta count
          for (die=0;die<=1;die++)
          {
            dit_ps_per_count[die] = dit_acquisition_time / dit_die_count[die];
            dit_delta_count[die]  = dit_acquisition_time / (dit_ps_per_count[die] + 20);
            dit_delta_count[die]  = dit_die_count[die] - dit_delta_count[die];
          }

          // Update the results data structure with the revised runtime count
          if (training_data_ptr->results.dit.dit_runtime_count < dit_runtime_count)
          training_data_ptr->results.dit.dit_runtime_count = dit_runtime_count;

          loopcnt++;
        }
      }
//    }
}

#endif

//================================================================================================//
//  Function: DDRSS_WR_half_full_cycle_search().
//  Brief description: This function determines the optimal full cycle and half cycle delays to use
//                     for all of the following steps in write training.  This function finds the
//                     left edge of the phase 0 eye to make it immune to DQS and DQ duty cycle.
//================================================================================================//
void DDRSS_WR_half_full_cycle_search  (DDR_STRUCT *ddr, 
                                 uint8 ch, 
                                 uint8 cs, 
                                 PHY_BUS dq,
                                 training_data *training_data_ptr,
                                 training_params_t *training_params_ptr,
                                 uint8* coarse_wrlvl_delay,
                                 uint8* fine_wrlvl_delay,
                                 ddrss_rdwr_dqdqs_local_vars *local_vars,
                                 uint32 clk_freq_khz,
                                 uint8 max_prfs_index) 
{
    uint32    dq0_ddr_phy_base  = 0;
    uint8            byte_lane  = 0;
    uint8           loop_count  = 0;
    uint8           MR14_value  = 0;
    uint8     coarse_cdc_value  = 0;
    uint8     min_coarse_value  = 0;
    uint8     max_coarse_value  = 0;
    
    uint8               clk_idx = 0;
    uint8       current_clk_inx = 0;
    
    uint8      half_cycle_steps = 0;
    uint8      full_cycle_steps = 0;
    
    uint8      half_cycle_count = 0;
    uint8  max_half_cycle_count = 4;
    
    uint16              full_cycle_in_ps = 0;
    uint16              half_cycle_in_ps = 0;
    
    uint8         start_full_cycle_count = 0;
    uint8         start_half_cycle_count = 0;
    
    uint8      dq_half_cycle[NUM_DQ_PCH] = {0};
    uint8      dq_full_cycle[NUM_DQ_PCH] = {0};
    
    uint8                *compare_result;
    uint8 compare_result_acc[NUM_DQ_PCH] = {0};
    uint8                 byte_lane_done = 0;
    uint8    byte_lane_found[NUM_DQ_PCH] = {0};
    
    // Initialize local vars
    memset(local_vars->coarse_schmoo.coarse_dq_full_half_cdc, training_params_ptr->wr_dqdqs.max_loopcnt + 1, (NUM_DQ_PCH * NUM_FULL * NUM_HALF * COARSE_CDC));
    
    // Set DQ0 base for addressing
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
        
#if DSF_PXI_TRAINING_EN
    Initialize_PXI_Tables(ddr, ch, cs, 2, 0); // 2 for write, 0 for dbi
#endif
    
    // Convert from clock frequency to clock index
    for(clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
    {
       if (clk_freq_khz >= freq_range[clk_idx-1])
          break;
    }
    current_clk_inx = clk_idx + 1;
    
    // Set the Vref value to use if maximum terminated or unterminated frequency
    if((current_clk_inx == max_prfs_index) || (clk_freq_khz <= LOWEST_TRAINED_FPRS_FREQ))
    {
        MR14_value = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? WRITE_TERMINATED_MR14_VREF: WRITE_UNTERMINATED_MR14_VREF;
        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_14, MR14_value);
    }
    
    // Calculate coarse sweep range to stay between T and T/2
    full_cycle_in_ps = CONVERT_CYC_TO_PS / clk_freq_khz;
    half_cycle_in_ps = full_cycle_in_ps / 2;
    full_cycle_steps = (full_cycle_in_ps / COARSE_STEP_IN_PS) + 1;
    half_cycle_steps = (half_cycle_in_ps / COARSE_STEP_IN_PS) + 1;
    max_coarse_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;
    min_coarse_value = (half_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : half_cycle_steps;
    
    // Calculate initial half and full cycle delays
    //max_half_cycle_count = (((CONVERT_CYC_TO_PS / clk_freq_khz) + MAX_TDQS2DQ_IN_PS) / ((CONVERT_CYC_TO_PS / clk_freq_khz) / 2));
    max_half_cycle_count = (MAX_TDQS2DQ_IN_PS / half_cycle_in_ps) + 1;
    
    start_full_cycle_count = max_half_cycle_count / 2;
    start_half_cycle_count = max_half_cycle_count % 2;
    
    if(start_full_cycle_count > (NUM_FULL - 1))
    {
       start_full_cycle_count = (NUM_FULL - 1);
    }
    
    for(byte_lane = 0; byte_lane < dq; byte_lane++)            
    {
        dq_full_cycle[byte_lane] = start_full_cycle_count;
        dq_half_cycle[byte_lane] = start_half_cycle_count;
    }
    
    // Sweep half and full cycle delay
    for(half_cycle_count = (max_half_cycle_count + 1); half_cycle_count > 0;)
    {
        half_cycle_count--;
        
        // Set full and half cycle delays
        for(byte_lane = 0; byte_lane < dq; byte_lane++)            
        {
            DDR_PHY_hal_cfg_wrlvl_half((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), cs, dq_half_cycle[byte_lane]);
            DDR_PHY_hal_cfg_wrlvl_full((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), cs, dq_full_cycle[byte_lane]);
        }
        
        // Sweep coarse delay from T to T/2 looking for fail to pass transition
        for(coarse_cdc_value = max_coarse_value; coarse_cdc_value >= min_coarse_value; coarse_cdc_value--)
        {
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
                // Set coarse delay
                DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                             coarse_cdc_value, 1, 1, cs); // 1 for coarse delay, 1 for HPCDC
                
                // Set retimer
                DDRSS_CDC_Retimer(ddr, cs,
                                  coarse_cdc_value,
                                  WRITE_FINE_CDC_MAX,
                                  coarse_wrlvl_delay[byte_lane],
                                  fine_wrlvl_delay[byte_lane],
                                  (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                  clk_freq_khz);           
            }
            
            // Write and verify data pattern
            for(loop_count = 0; loop_count < training_params_ptr->wr_dqdqs.max_loopcnt; loop_count++) 
            {
#if DSF_PXI_TRAINING_EN
                DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); // 0 for dbi, 1 for prbs
                compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 0, 1); // 0 for phase, 1 for prbs
#else
                DDRSS_mem_write(ddr, ch, cs);
                compare_result = DDRSS_mem_read_per_byte_phase(ddr, ch, cs, dq, 0); // 0 for phase
#endif

                // Accumulate the compare results per byte
                for(byte_lane = 0; byte_lane < dq; byte_lane++) 
                {
                  compare_result_acc[byte_lane] += compare_result[byte_lane];
                }
            }
            
            // Check for right edge
            for(byte_lane = 0; byte_lane < dq; byte_lane++)
            {
                local_vars->coarse_schmoo.coarse_dq_full_half_cdc[byte_lane][dq_full_cycle[byte_lane]][dq_half_cycle[byte_lane]][coarse_cdc_value]
                    = compare_result_acc[byte_lane];
                
                if(compare_result_acc[byte_lane] == 0)
                {
                    if(byte_lane_found[byte_lane] == 0)
                    {
                        byte_lane_done++;
                        byte_lane_found[byte_lane]++;
                    }
                }
                
                compare_result_acc[byte_lane] = 0;
            }
            
            // Exit when all bytes are done
            if(byte_lane_done == dq) 
            {
                break;
            }
        }  // coarse sweep
        
        // Exit when all bytes are done or eye not found
        if((byte_lane_done == dq) || (half_cycle_count == 0))
        {
            break;
        }
        
        // Increase half and full cycle for bytes which are not done
        for(byte_lane = 0; byte_lane < dq; byte_lane++)            
        {
            if(byte_lane_found[byte_lane] == 0)
            {
                if(dq_half_cycle[byte_lane] == 0)
                {
                    dq_half_cycle[byte_lane] = 1;
                    
                    dq_full_cycle[byte_lane]--;
                }
                else
                {
                    dq_half_cycle[byte_lane]--;
                }
            }
        }
    } // half cycle sweep
    
    // Save training results
    for(byte_lane = 0; byte_lane < dq; byte_lane++)            
    {
        training_data_ptr->results.wr_dqdqs.dq_half_cycle[current_clk_inx][ch][cs][byte_lane] = dq_half_cycle[byte_lane];
        training_data_ptr->results.wr_dqdqs.dq_full_cycle[current_clk_inx][ch][cs][byte_lane] = dq_full_cycle[byte_lane];
    }
} // DDRSS_WR_right_edge_search

void DDRSS_RD_left_edge_search  (DDR_STRUCT *ddr, 
                                 uint8 ch, 
                                 uint8 cs, 
                                 PHY_BUS dq,
                                 training_data *training_data_ptr,
                                 training_params_t *training_params_ptr,
                                 uint8 *rd_left_edge_coarse,
                                 uint32 clk_freq_khz) 
{
    uint8 coarse_cdc_value                  = 0;
    uint8 byte_lane                         = 0;
    uint8 loopcnt                           = 0;
    uint8 byte_lane_done                    = 0;
    uint8 *compare_result;  
    uint8 compare_result_acc[NUM_DQ_PCH]    = {0};  
    uint8 byte_lane_found[NUM_DQ_PCH]       = {0};
    uint32 dq0_ddr_phy_base                 = 0;
    
    uint32 full_cycle_steps = 0;
    uint32 coarse_cdc_max_value = 0;
  
#if DSF_PXI_TRAINING_EN
  Initialize_PXI_Tables(ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi, clk
#endif

    // Set DQ0 base for addressing
    dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    
    // Calculate coarse CDC max value based on period
    full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
    coarse_cdc_max_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;

    // CDC Schmoo loop
    for(coarse_cdc_value  = training_params_ptr->rd_dqdqs.coarse_cdc_start_value; 
        coarse_cdc_value <= coarse_cdc_max_value;
        coarse_cdc_value += training_params_ptr->rd_dqdqs.coarse_cdc_step)
    {
       // Update RD CDC
        for(byte_lane = 0; byte_lane < dq; byte_lane++) 
        {
            DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                          coarse_cdc_value, 
                                          0x1, 
                                          0x1, 
                                          cs);   
            compare_result_acc[byte_lane] = 0;
        }

        // Read-back and compare. Fail info given on a byte_lane basis, in an array of 4.                 
        for (loopcnt = 0;loopcnt < training_params_ptr->rd_dqdqs.max_loopcnt; loopcnt++) 
        {
#if DSF_PXI_TRAINING_EN
            compare_result = DDRSS_mem_read_per_byte_phase_PXI(ddr, ch, cs, dq, 0x0, 1);    //ddr, ch, cs, loop cnt, phase, prbs
#else
            compare_result = DDRSS_mem_read_per_byte_phase    (ddr, ch, cs, dq, 0x0);       //ddr, ch, cs, dq, phase
#endif

            // Accumulate the compare results per byte
            for(byte_lane = 0; byte_lane < dq; byte_lane++) 
            {
              compare_result_acc[byte_lane] += compare_result[byte_lane];
            }
        }
         
        for(byte_lane = 0; byte_lane < dq; byte_lane++)            
        { 
          // If pass, capture left edge
          if(compare_result_acc[byte_lane] == 0)
          {
            if (byte_lane_found[byte_lane] == 0)
            {
              byte_lane_done++;
              byte_lane_found[byte_lane]++;
              rd_left_edge_coarse[byte_lane] = coarse_cdc_value;
            }
          }
        } // byte_lane
        
        if (byte_lane_done == dq)
        {
          break;
        } 
    } // CDC_LOOP 
        
    // Print the left boundary of the eye
    for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
    {
#if DSF_RD_DQDQS_TRAINING_LOG
      ddr_printf(DDR_NORMAL, "    RD Byte %d Coarse Left Edge: %d \n",
                byte_lane, rd_left_edge_coarse[byte_lane]);
#endif
    } // byte_lane
#if DSF_RD_DQDQS_TRAINING_LOG
    ddr_printf(DDR_NORMAL, "\n");
#endif
}//DDRSS_RD_left_edge_search

#if DSF_RD_DQDQS_COARSE_FINE_PLOT
//================================================================================================//
//  Function: rd_dqdqs_coarse_fine_plot().
//  Brief description: 
//================================================================================================//
void DDRSS_rd_dqdqs_coarse_fine_plot (DDR_STRUCT *ddr, 
                                      training_params_t *training_params_ptr,
                                      uint32 clk_freq_khz
                                      )
{
#define CH_START  1
  uint8  ch                   = 0;
  uint8  cs                   = 0;
  uint8  bit                  = 0;
  uint8  byte_lane            = 0;
  uint32 dq0_ddr_phy_base     = 0;
  uint8  phase                = 0;
  uint8  vref                 = 0;
  uint8  coarse_cdc           = 0;
  uint8  coarse_cdc_max_value = 0;
  uint8  fine_cdc             = 0;
  uint8  mc_bit               = 0;
  uint8  phy_bit              = 0;
  uint8  mp_hp                = 0;
  uint8  full_cycle_steps     = 0;
  uint8  vref_max_value       = 0;
  uint8  vref_start_value     = 0;
  uint16 super_iteration      = 0;
  uint32 word[NUM_CH][NUM_CS][PHASE]                   = {{{0}}};      
  uint8 compare_result_acc_0[NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint8 compare_result_acc_1[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};
  uint8 decouple_bit[NUM_DQ_PCH]                       = {0};    
  uint8 ioqual_vref           = 0x10;
  uint8 tmp_vref[NUM_CH][NUM_CS][NUM_CA_PCH]           = {{{0}}};
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

  // Determine starting VREF and minimum and maximum limits based on MPVREF or HPVREF
  mp_hp = (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ) ? MPVREF : HPVREF; 

  // Calculate the VREF max value (if not max frequency, use the previously trained VREF)
  vref_max_value = (mp_hp == HPVREF) ? 
                       training_params_ptr->rd_dqdqs.coarse_vref_max_hprx 
 
                 :     training_params_ptr->rd_dqdqs.coarse_vref_max_mprx;

  // Calculate coarse CDC max value based on period
  full_cycle_steps = ((CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS);
  coarse_cdc_max_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;
		   
  // Calculate the VREF start values (if not max frequency, use the previously trained VREF)
  vref_start_value = (mp_hp == HPVREF) ? 0 : training_params_ptr->rd_dqdqs.coarse_vref_start_mprx;
  
  
  for (ch=CH_START;ch<NUM_CH;ch++)
  {
    for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
    {
      dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;

      if (mp_hp == HPVREF)  
      {    
        tmp_vref[ch][0][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                VREF_TRIM);
          
        // Set decouple bit (RMW).This sets the IOqualifier to MPVREF. This is required durining training. 
        // bit[0] = 0 => MPRX
        decouple_bit[byte_lane] = HWIO_INX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                            DDR_PHY_DDRPHY_PAD_DQS_1_CFG);
                                            
        decouple_bit[byte_lane] = (decouple_bit[byte_lane] | (1 << 1));
        
        HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                   DDR_PHY_DDRPHY_PAD_DQS_1_CFG, 
                   decouple_bit[byte_lane]);
            
        // Set MPVREF value to IOqualifier to mprx vref reg.  This value is to be set in CA PHY                 
        DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                        ioqual_vref,
                        HIGHEST_MPRX_FPRS_FREQ,
                        0);
      }
      else 
      {
        for (cs=0;cs<NUM_CS;cs++)
        {
          // Store the global VREF to restore after plotting
          if (cs == 0)
          {
            tmp_vref[ch][cs][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                     DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                     VREF_PAD_RFU_R0);
          }
          else
          {
            tmp_vref[ch][cs][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                     DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                     VREF_PAD_RFU_R1);
          }
        }            
      }
    }
  }      
   
  // Main VREF/CDC sweep loop     
  for (vref  = vref_start_value;vref < vref_max_value; vref++)  
  {   
    for (ch=CH_START;ch<NUM_CH;ch++)
    {      
      dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
      
      for (cs=0;cs<NUM_CS;cs++)
      {
        for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
        {   
          // Sweep Coarse VREF for CA0
          DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                      vref,
                                      clk_freq_khz,
                                      cs);
        }
      }
    } 
  
    for (coarse_cdc = 0; coarse_cdc < coarse_cdc_max_value; coarse_cdc++)
    {
      for (ch=CH_START;ch<NUM_CH;ch++)
      {
        for (cs=0;cs<NUM_CS;cs++)
        {
          // Set DQ0 base for addressing
          dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
          
          for (byte_lane=0;byte_lane<NUM_DQ_PCH;byte_lane++)
          {
            DDR_PHY_hal_cfg_cdc_slave_rd(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                         coarse_cdc, 
                                         1, 
                                         1, 
                                         cs);
          }
        }
      }

      for (fine_cdc = 0;fine_cdc <FINE_STEPS_PER_COARSE; fine_cdc++)
      {
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          { 
            // Set DQ0 base for addressing
            dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            
            for (byte_lane=0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              DDR_PHY_hal_cfg_cdc_slave_rd(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                           fine_cdc, 
                                           0, 
                                           1, 
                                           cs);   
            }
          }
        }
           
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          {   
#if DSF_PXI_TRAINING_EN
            Initialize_PXI_Tables (ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
            DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0,1);
            DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1,1);     
#else
            DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0);
            DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1);           
#endif
            
            for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              for (bit=0;bit<PINS_PER_PHY_CONNECTED_NO_DBI;bit++)
              {
                phy_bit = connected_bit_mapping_no_DBI_A[bit];
               // mc_bit  = bit_remapping_phy2bimc_DQ_Even[bit];
				mc_bit = bit_remapping_phy2bimc_DQ[ch][byte_lane][bit];//Changed by Sagar

                word[ch][cs][0] |= compare_result_acc_0[byte_lane][phy_bit] << (mc_bit + (byte_lane * BYTE_SIZE));
                word[ch][cs][1] |= compare_result_acc_1[byte_lane][phy_bit] << (mc_bit + (byte_lane * BYTE_SIZE));
                
                compare_result_acc_0[byte_lane][phy_bit] = 0;
                compare_result_acc_1[byte_lane][phy_bit] = 0;                 
              }          
            }
          } // cs
        } // ch
        
        printf ("%d,%d,0,%d,%d,%d,PASS",super_iteration,clk_freq_khz,vref,coarse_cdc,fine_cdc);
        super_iteration++;
        
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          { 
            for (phase=0;phase<PHASE;phase++)
            {
              printf (",%08x",word[ch][cs][phase]);
              word[ch][cs][phase] = 0;
            }
          }
        }
        printf ("\n");
	   } // fine_cdc     
    } // coarse_cdc 
  } // VREF
  
  // Restore the Global VREF and IO qualifier local VREF
  for (ch=CH_START;ch<NUM_CH;ch++)
  {
    dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
   
    for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
    {     
      if(mp_hp == HPVREF)
      {
          // Restore decouple bit.
          decouple_bit[byte_lane] = (decouple_bit[byte_lane] & 0xFFFFFFFD);
          HWIO_OUTX(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                    DDR_PHY_DDRPHY_PAD_DQS_1_CFG, 
                    decouple_bit[byte_lane]);
					
					// restore mprx vref to mprx vref reg.             
          DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                      0x1F,
                                      //F_RANGE_3,
                                      HIGHEST_MPRX_FPRS_FREQ,
                                      0);
						
          // Restore the stored global VREF
          HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_TRIM,tmp_vref[ch][0][byte_lane]);
        
          // Restore the IO Qualifier local VREF
          DDR_PHY_hal_cfg_local_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                     DQS_VREF, 
                                     cs,
                                     10
                                     );
      }
      else
      {
        for (cs=0;cs<NUM_CS;cs++)
        {
          // Store the global VREF to restore after plotting
          if (cs == 0)
          {
            HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                        DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                        VREF_PAD_RFU_R0,
                        tmp_vref[ch][cs][byte_lane]);
          }
          else
          {
            HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                        DDR_PHY_DDRPHY_PAD_VREF_CFG, VREF_PAD_RFU_R1, 
                        tmp_vref[ch][cs][byte_lane]);
          }
        } 
      }
    }
  }    
}
#endif  // DSF_RD_DQDQS_COARSE_FINE_PLOT


#if DSF_WR_DQDQS_COARSE_FINE_PLOT
//================================================================================================//
//  Function: wr_dqdqs_coarse_fine_plot().
//  Brief description: 
//================================================================================================//
void DDRSS_wr_dqdqs_coarse_fine_plot (DDR_STRUCT *ddr, 
                                      training_params_t *training_params_ptr,
                                      uint32 clk_freq_khz
                                      )
{
#define  CH_START 1
  uint8  ch                   = 0;
  uint8  cs                   = 0;
  uint8  bit                  = 0;
  uint8  byte_lane            = 0;
  uint32 dq0_ddr_phy_base     = 0;
  uint32 ca0_ddr_phy_base     = 0;
  uint8  phase                = 0;
  uint8  vref                 = 0;
  uint8  coarse_cdc           = 0;
  uint8  coarse_cdc_max_value = 0;
  uint8  fine_cdc             = 0;
  uint8  mc_bit               = 0;
  uint8  phy_bit              = 0;
  uint8  mp_hp                = 0;
  uint8  full_cycle_steps     = 0;
  uint8  vref_max_value       = 0;
  uint8  vref_start_value     = 0;
  uint16 super_iteration      = 0;
  uint32 word[NUM_CH][NUM_CS][PHASE]                   = {{{0}}};      
  uint8 compare_result_acc_0[NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint8 compare_result_acc_1[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};
  uint8 decouple_bit[NUM_DQ_PCH]                       = {0};    
  uint8 ioqual_vref           = 0x10;
  uint8 tmp_vref[NUM_CH][NUM_CS][NUM_CA_PCH]           = {{{0}}};
  
  uint8          MR14_value  = 0;
  uint8 MR14_vref_range_bit  = 0;
  
  uint8             clk_idx = 0;
  uint8     current_clk_inx = 0;
  
  uint8 coarse_wrlvl_delay[NUM_DQ_PCH] = {0};
  uint8 fine_wrlvl_delay  [NUM_DQ_PCH] = {0};
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
  
  // Choose Vref_Range_bit according to frequency threshold.
  MR14_vref_range_bit = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 0: 1;
  
  for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
  {
    if (clk_freq_khz >= freq_range[clk_idx-1])
      break;
  }
  current_clk_inx = clk_idx + 1;
  
  for (byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
  {
    // Initialize the WRLVL delays
    coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
    fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];
  }
  
  // Calculate coarse CDC max value based on period
  full_cycle_steps = (CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS;
  coarse_cdc_max_value = ((full_cycle_steps + 1) > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : (full_cycle_steps + 1);
  
  // Vref range
  vref_start_value = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
  vref_max_value = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
  
  // Main VREF/CDC sweep loop     
  for (vref = vref_start_value; vref <= vref_max_value; vref++)  
  {
    for (ch=CH_START;ch<NUM_CH;ch++)
    {
      // Set DQ0 base for addressing
      dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
      
      for (cs=0;cs<NUM_CS;cs++)
      {
        MR14_value = ((MR14_vref_range_bit << 6) | (vref << 0));
        BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_14, MR14_value);
      }
    }
        
    for (coarse_cdc = 0; coarse_cdc <= coarse_cdc_max_value; coarse_cdc++)
    {
      for (ch=CH_START;ch<NUM_CH;ch++)
      {
        // Set DQ0 base for addressing
        dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
        
        for (cs=0;cs<NUM_CS;cs++)
        {
          for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
          {
            DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                          coarse_cdc,
                                          1, 1, cs); // 1 for coarse_delay_mode. 1 for hp_mode.
          }
        }
      }
        
      for (fine_cdc = WRITE_FINE_CDC_MIN; fine_cdc <= WRITE_FINE_CDC_MAX; fine_cdc++)
      {
        for (ch=0;ch<NUM_CH;ch++)
        {
          // Set DQ0 base for addressing
          dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
          
          for (cs=0;cs<NUM_CS;cs++)
          {
            for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                            fine_cdc,
                                            0, 1, cs); // 0 for coarse_delay_mode. 1 for hp_mode.
              DDRSS_CDC_Retimer (ddr,
                                 cs,
                                 coarse_cdc,
                                 fine_cdc,
                                 coarse_wrlvl_delay[byte_lane],
                                 fine_wrlvl_delay[byte_lane],
                                 (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                 clk_freq_khz);
            }
          }
        }
        
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          {
#if DSF_PXI_TRAINING_EN
            Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
            DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
            Initialize_PXI_Tables(ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
            DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0,1);
            DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1,1);                
#else 
            DDRSS_mem_write(ddr, ch, cs);
            DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0);
            DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1);           
#endif
            
            for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              for (bit=0;bit<PINS_PER_PHY_CONNECTED_NO_DBI;bit++)
              {
                phy_bit = connected_bit_mapping_no_DBI_A[bit];
                mc_bit  = bit_remapping_phy2bimc_DQ[ch][byte_lane][bit];
                
                word[ch][cs][0] |= compare_result_acc_0[byte_lane][phy_bit] << (mc_bit + (byte_lane * BYTE_SIZE));
                word[ch][cs][1] |= compare_result_acc_1[byte_lane][phy_bit] << (mc_bit + (byte_lane * BYTE_SIZE));
                
                compare_result_acc_0[byte_lane][phy_bit] = 0;
                compare_result_acc_1[byte_lane][phy_bit] = 0;             
              }        
            }
          } // cs
        } // ch
        
        printf ("%d,%d,0,%d,%d,%d,PASS",super_iteration,clk_freq_khz,vref,coarse_cdc,fine_cdc);
        super_iteration++;
        
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          { 
            for (phase=0;phase<PHASE;phase++)
            {
              printf (",%08x",word[ch][cs][phase]);
              word[ch][cs][phase] = 0;
            }
          }
        }
        printf ("\n");
	   } // fine_cdc
    } // coarse_cdc
  } // VREF
}
#endif  // DSF_WR_DQDQS_COARSE_FINE_PLOT


void DDR_PHY_rtn_ca_pcc_link_list_load (uint32 ddr_phy_addr_base)
{
  uint32 maxLLIndex           = NUM_PHY_PCC_LL;
  uint32 curLLIndex           = 0;

  /// Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x100); //LL_IDX_RST
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x1000);// MEM_IDX_RST

  /// De-Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x0);//LL_IDX_RST
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x0);//MEM_IDX_RST

  /// Write the Link List descriptors into the Link memory
  for (curLLIndex = 0; curLLIndex < maxLLIndex; curLLIndex = curLLIndex + 2) 
  {
    HWIO_OUTX(ddr_phy_addr_base,
              DDR_PHY_DDRPHY_PCCLL_ADDR_CFG,
             ((ddr_phy_ca_pcc_link_list[curLLIndex+1]<<16) | (ddr_phy_ca_pcc_link_list[curLLIndex]))
             );
  }
}

void DDR_PHY_rtn_dq_pcc_link_list_load (uint32 ddr_phy_addr_base)
{
  uint32 maxLLIndex           = NUM_PHY_PCC_LL;
  uint32 curLLIndex           = 0;

  /// Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x100); //LL_IDX_RST
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x1000);// MEM_IDX_RST

  /// De-Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_LL_CFG, 0x0);//LL_IDX_RST
  HWIO_OUTX(ddr_phy_addr_base,DDR_PHY_DDRPHY_PCC_MEM_CFG,0x0);//MEM_IDX_RST

  /// Write the Link List descriptors into the Link memory
  for (curLLIndex = 0; curLLIndex < maxLLIndex; curLLIndex = curLLIndex + 2) 
  {
    HWIO_OUTX(ddr_phy_addr_base,
              DDR_PHY_DDRPHY_PCCLL_ADDR_CFG,
             ((ddr_phy_dq_pcc_link_list[curLLIndex+1]<<16) | (ddr_phy_dq_pcc_link_list[curLLIndex]))
             );
  }
}

void DDR_CC_rtn_pcc_link_list_load (uint32 ddr_cc_addr_base)
{
  uint32 maxLLIndex           = NUM_CC_PCC_LL;
  uint32 curLLIndex           = 0;
  
  /// Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_cc_addr_base,DDR_CC_DDRCC_PCC_LL_CFG,  0x100);// LL_IDX_RST
  HWIO_OUTX(ddr_cc_addr_base,DDR_CC_DDRCC_PCC_MEM_CFG,0x1000);//MEM_IDX_RST

  /// De-Assert SW Reset of the Linked List and Memory
  HWIO_OUTX(ddr_cc_addr_base,DDR_CC_DDRCC_PCC_LL_CFG, 0x0);//LL_IDX_RST
  HWIO_OUTX(ddr_cc_addr_base,DDR_CC_DDRCC_PCC_MEM_CFG,0x0);//MEM_IDX_RST

  /// Write the Link List descriptors into the Link memory
  for (curLLIndex = 0; curLLIndex < maxLLIndex; curLLIndex = curLLIndex + 2) 
  {
    HWIO_OUTX(ddr_cc_addr_base,
              DDR_CC_DDRCC_PCCLL_ADDR_CFG,
              ((ddr_cc_pcc_link_list[curLLIndex+1]<<16) | (ddr_cc_pcc_link_list[curLLIndex]))
              );
  } 
}

#if DSF_RD_DQDQS_COARSE_FINE_PLOT_PIVOT
//================================================================================================//
//  Function: rd_dqdqs_coarse_fine_plot().
//  Brief description: 
//================================================================================================//
void DDRSS_rd_dqdqs_coarse_fine_plot_pivot (DDR_STRUCT *ddr,
                                            char *fout,
                                            training_params_t *training_params_ptr,
                                            uint32 clk_freq_khz
                                            )
{
  #define CH_START  1
  FILE  *fp;
  uint8  ch                   = 0;
  uint8  cs                   = 0;
  uint8  bit                  = 0;
  uint8  byte_lane            = 0;
  uint32 dq0_ddr_phy_base     = 0;
  uint32 rd_cdc               = 0;
  uint32 period               = 0;
  uint8  phase                = 0;
  uint8  vref                 = 0;
  uint8  coarse_cdc           = 0;
  uint8  coarse_cdc_max_value = 0;
  uint8  fine_cdc             = 0;
  uint8  mc_bit               = 0;
  uint8  phy_bit              = 0;
  uint8  mp_hp                = 0;
  uint8  full_cycle_steps     = 0;
  uint8  vref_max_value       = 0;
  uint8  vref_start_value     = 0;
  uint32 word[NUM_CH][NUM_CS][PHASE]                   = {{{0}}};      
  uint8 compare_result_acc_0[NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint8 compare_result_acc_1[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};
  uint8 decouple_bit[NUM_DQ_PCH]                       = {0};    
  uint8 ioqual_vref                                    = 0x10;
  uint8 trained_vref[NUM_CH][NUM_CS][NUM_DQ_PCH]       = {{{0}}};
  uint8 trained_coarse_cdc[NUM_CH][NUM_CS][NUM_DQ_PCH] = {{{0}}};
  uint8 trained_fine_cdc  [NUM_CH][NUM_CS][NUM_DQ_PCH] = {{{0}}};
  
  uint16 cdc_start  [NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0}};
  uint16 cdc_width  [NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0}};   
  uint16 vref_start [NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0xFFFF}}; 
  uint16 vref_height[NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint16 dq_dcd     [NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint16 dqs_dcd    [NUM_CH][NUM_CS][PHASE][NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 

  uint8 version = TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION;
  uint8 clk_idx;
  uint8 current_clk_inx;
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);

  // Determine starting VREF and minimum and maximum limits based on MPVREF or HPVREF
  mp_hp = (clk_freq_khz <= HIGHEST_MPVREF_PRFS_FREQ) ? MPVREF : HPVREF; 

  // Calculate the VREF max value (if not max frequency, use the previously trained VREF)
  vref_max_value = (mp_hp == HPVREF) ? 
                       training_params_ptr->rd_dqdqs.coarse_vref_max_hprx 
 
                 :     training_params_ptr->rd_dqdqs.coarse_vref_max_mprx;

  // Calculate coarse CDC max value based on period
  period           = CONVERT_CYC_TO_PS / clk_freq_khz;
  full_cycle_steps = period / COARSE_STEP_IN_PS;
  coarse_cdc_max_value = (full_cycle_steps > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : full_cycle_steps;
		   
  // Calculate the VREF start values (if not max frequency, use the previously trained VREF)
  vref_start_value = (mp_hp == HPVREF) ? 0 : training_params_ptr->rd_dqdqs.coarse_vref_start_mprx;
  
  // Calculate the clk index from the frequency
  for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
  {
    if (clk_freq_khz >= freq_range[clk_idx-1])
      break;
  }
  current_clk_inx = clk_idx + 1; 
  
  printf ("\nStart RD Plot for %d MHz\n\n",clk_freq_khz);
  
  if ((fp = fopen(fout,"w")) != NULL)
  {
    // Print CSV file header
    fprintf(fp,"MSM Serial,DSF Version,Frequency,Read/Write,Channel,Rank,Byte,Bit,Phase,Vref,Coarse,Fine,Value,CDC Start,Width,VREF Start,Height,DQ DCD,DQS DCD\r\n");

    for (ch=CH_START;ch<NUM_CH;ch++)
    {
      for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
      {
        dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
                
        for (cs=0;cs<NUM_CS;cs++)
        { 
          trained_vref      [ch][cs][byte_lane] = training_data_ptr->results.rd_dqdqs.coarse_vref[mp_hp][ch][cs][byte_lane];
          trained_coarse_cdc[ch][cs][byte_lane] = training_data_ptr->results.rd_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane];
          trained_fine_cdc  [ch][cs][byte_lane] = training_data_ptr->results.rd_dqdqs.fine_cdc[current_clk_inx][ch][cs][byte_lane];
          
          trained_coarse_cdc[ch][cs][byte_lane] += trained_fine_cdc[ch][cs][byte_lane]/FINE_STEPS_PER_COARSE;                   
          trained_fine_cdc  [ch][cs][byte_lane] %= FINE_STEPS_PER_COARSE;          
        }
    
        if (mp_hp == HPVREF)  
        {    
            // Store the global VREF to restore after plotting
            trained_vref[ch][0][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                        DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                        VREF_TRIM);
            trained_vref[ch][1][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                        DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                        VREF_TRIM);
            
            // Set decouple bit (RMW).This sets the IOqualifier to MPVREF. This is required durining training. bit[0] = 0 => MPRX
            decouple_bit[byte_lane] = HWIO_INX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_PAD_DQS_1_CFG);
            decouple_bit[byte_lane] = (decouple_bit[byte_lane] | (1 << 1));
            HWIO_OUTX (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                       DDR_PHY_DDRPHY_PAD_DQS_1_CFG, 
                       decouple_bit[byte_lane]);
                
            // Set MPVREF value to IOqualifier to mprx vref reg.  This value is to be set in CA PHY                 
            DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                        ioqual_vref,
                                        HIGHEST_MPRX_FPRS_FREQ,
                                        0);
        }
        else 
        {
          // Store the global VREF to restore after plotting
          if (cs == 0)
          {
            trained_vref[ch][cs][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                         DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                         VREF_PAD_RFU_R0);
          }
          else
          {
            trained_vref[ch][cs][byte_lane] = HWIO_INXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                                         DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                                                         VREF_PAD_RFU_R1);
          }          
        }
      }
    }      
     
    //-----------------------------------------------------------------------------------------
    // Main VREF/CDC sweep loop  
    //-----------------------------------------------------------------------------------------
    ddr_printf (DDR_NORMAL,"Plotting Vref  ");
    for (vref  = vref_start_value;vref < vref_max_value; vref++)  
    {   
      ddr_printf (DDR_NORMAL,"->%d",vref);
      for (ch=CH_START;ch<NUM_CH;ch++)
      {
        // Set DQ0 base for addressing
        dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
               
        for (cs=0;cs<NUM_CS;cs++)
        {
          for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
          {
            // Sweep Coarse VREF
            DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                        vref,
                                        clk_freq_khz,
                                        cs);
            for (phase=0;phase<PHASE;phase++)
            {
              for (bit=0;bit<PINS_PER_PHY_CONNECTED_NO_DBI;bit++)
              {         
                cdc_start[ch][cs][phase][byte_lane][bit] = 0xFFFF;
                cdc_width[ch][cs][phase][byte_lane][bit] = 0;
                dq_dcd[ch][cs][phase][byte_lane][bit]    = 0;
                dqs_dcd[ch][cs][phase][byte_lane][bit]   = 0;
              }
            }
          }
        }
      }
 
    
      for (coarse_cdc = 0; coarse_cdc <= coarse_cdc_max_value; coarse_cdc++)
      {
        for (ch=CH_START;ch<NUM_CH;ch++)
        {
          for (cs=0;cs<NUM_CS;cs++)
          {
            // Set DQ0 base for addressing
            dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            
            for (byte_lane=0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                            coarse_cdc, 
                                            1, 
                                            1, 
                                            cs);
            }
          }
        }
    
        for (fine_cdc = 0;fine_cdc <FINE_STEPS_PER_COARSE; fine_cdc++)
        {
          for (ch=CH_START;ch<NUM_CH;ch++)
          {
            for (cs=0;cs<NUM_CS;cs++)
            { 
              // Set DQ0 base for addressing
              dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
              
              for (byte_lane=0;byte_lane<NUM_DQ_PCH;byte_lane++)
              {
                DDR_PHY_hal_cfg_cdc_slave_rd((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)), 
                                              fine_cdc, 
                                              0, 
                                              1, 
                                              cs);   
              }
            }
          }
             
          for (ch=CH_START;ch<NUM_CH;ch++)
          {
            for (cs=0;cs<NUM_CS;cs++)
            {   
#if DSF_PXI_TRAINING_EN
              Initialize_PXI_Tables (ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
              DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0,1);
              DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1,1);     
#else
              DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0);
              DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1);           
#endif
              
              for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
              {
                for (bit=0;bit<PINS_PER_PHY_CONNECTED_NO_DBI;bit++)
                {
                  phy_bit = connected_bit_mapping_no_DBI_A[bit];
                  mc_bit  = bit_remapping_phy2bimc_DQ[ch][byte_lane][bit];                  

                  if (compare_result_acc_0[byte_lane][phy_bit] == 0)
                  {
                    cdc_width[ch][cs][0][byte_lane][phy_bit] += FINE_STEP_IN_PS;
                                                              
                    if ((coarse_cdc * COARSE_STEP_IN_PS) + (fine_cdc * FINE_STEP_IN_PS) <= cdc_start[ch][cs][0][byte_lane][phy_bit])
                    {
                      cdc_start[ch][cs][0][byte_lane][phy_bit] = (coarse_cdc * COARSE_STEP_IN_PS) + (fine_cdc * FINE_STEP_IN_PS); 
                    }
                    if (vref >= vref_height[ch][cs][0][byte_lane][phy_bit])
                    {
                      vref_height[ch][cs][0][byte_lane][phy_bit] = vref;
                    }
                    if (vref <= vref_start[ch][cs][0][byte_lane][phy_bit])
                    {
                      vref_start[ch][cs][0][byte_lane][phy_bit] = vref;
                    }                    
                  }
                  
                  if (compare_result_acc_1[byte_lane][phy_bit] == 0)
                  {
                    cdc_width[ch][cs][1][byte_lane][phy_bit] += FINE_STEP_IN_PS;
                                                              
                    if ((coarse_cdc * COARSE_STEP_IN_PS) + (fine_cdc * FINE_STEP_IN_PS) <= cdc_start[ch][cs][1][byte_lane][phy_bit])
                    {
                      cdc_start[ch][cs][1][byte_lane][phy_bit] = (coarse_cdc * COARSE_STEP_IN_PS) + (fine_cdc * FINE_STEP_IN_PS);                      
                    }
                    
                    if (vref >= vref_height[ch][cs][1][byte_lane][phy_bit])
                    {
                      vref_height[ch][cs][1][byte_lane][phy_bit] = vref;
                    }
                    if (vref <= vref_start[ch][cs][1][byte_lane][phy_bit])
                    {
                      vref_start[ch][cs][1][byte_lane][phy_bit] = vref;
                    }                                        
                  }      
                  
                  for (phase=0;phase<PHASE;phase++)
                  {                    
                    if ((vref       == trained_vref      [ch][cs][byte_lane]) && 
                        (coarse_cdc == trained_coarse_cdc[ch][cs][byte_lane])  &&
                        (fine_cdc   == trained_fine_cdc  [ch][cs][byte_lane]))
                    {
                      compare_result_acc_0[byte_lane][phy_bit] = 1;
                      compare_result_acc_1[byte_lane][phy_bit] = 1;
                    } 
                    
                    if ((cdc_width[ch][cs][0][byte_lane][phy_bit] & cdc_width[ch][cs][1][byte_lane][phy_bit]) != 0)
                    {
                      dq_dcd[ch][cs][phase][byte_lane][phy_bit] = (cdc_width[ch][cs][phase][byte_lane][phy_bit] * 100)/
                                                                  (cdc_width[ch][cs][0][byte_lane][phy_bit] + cdc_width[ch][cs][1][byte_lane][phy_bit]);
                    }
                    
                    if (cdc_start[ch][cs][1][byte_lane][phy_bit] >= cdc_start[ch][cs][0][byte_lane][phy_bit])
                    {
                      dqs_dcd[ch][cs][0][byte_lane][phy_bit]  = (((period/2) - (cdc_start[ch][cs][1][byte_lane][phy_bit] - 
                                                                                cdc_start[ch][cs][0][byte_lane][phy_bit])) * 100)/period;
                      dqs_dcd[ch][cs][1][byte_lane][phy_bit]  = (((period/2) + (cdc_start[ch][cs][1][byte_lane][phy_bit] - 
                                                                                cdc_start[ch][cs][0][byte_lane][phy_bit])) * 100)/period;                                                                                    
                    }
                    else
                    {
                      dqs_dcd[ch][cs][1][byte_lane][phy_bit]  = (((period/2) - (cdc_start[ch][cs][0][byte_lane][phy_bit] - 
                                                                                cdc_start[ch][cs][1][byte_lane][phy_bit])) * 100)/period;
                      dqs_dcd[ch][cs][0][byte_lane][phy_bit]  = (((period/2) + (cdc_start[ch][cs][0][byte_lane][phy_bit] - 
                                                                                cdc_start[ch][cs][1][byte_lane][phy_bit])) * 100)/period;                                  
                    }
                    
                    if (phase == 0)
                    {
                      fprintf (fp,"DSF_SIM,%d,%d,READ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
                               version,clk_freq_khz,ch,cs,byte_lane,phy_bit,phase,vref,coarse_cdc,
                               fine_cdc,compare_result_acc_0[byte_lane][phy_bit],
                               (cdc_start[ch][cs][phase][byte_lane][phy_bit] == 0xFFFF) ? 0 : cdc_start[ch][cs][phase][byte_lane][phy_bit],
                               (coarse_cdc == coarse_cdc_max_value) ? cdc_width[ch][cs][phase][byte_lane][phy_bit] : 0,
                               (vref_start[ch][cs][phase][byte_lane][phy_bit] == 0xFFFF) ? 0 : vref_start[ch][cs][phase][byte_lane][phy_bit],
                               vref_height[ch][cs][phase][byte_lane][phy_bit],
                               (coarse_cdc == coarse_cdc_max_value) ? dq_dcd[ch][cs][phase][byte_lane][phy_bit]  : 0 ,
                               (coarse_cdc == coarse_cdc_max_value) ? dqs_dcd[ch][cs][phase][byte_lane][phy_bit] : 0);
                    }
                    else
                    {
                      fprintf (fp,"DSF_SIM,%d,%d,READ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
                               version,clk_freq_khz,ch,cs,byte_lane,phy_bit,phase,vref,coarse_cdc,
                               fine_cdc,compare_result_acc_1[byte_lane][phy_bit]<<1,
                               (cdc_start[ch][cs][phase][byte_lane][phy_bit] == 0xFFFF) ? 0 : cdc_start[ch][cs][phase][byte_lane][phy_bit],
                               (coarse_cdc == coarse_cdc_max_value) ? cdc_width[ch][cs][phase][byte_lane][phy_bit] : 0,
                               (vref_start[ch][cs][phase][byte_lane][phy_bit] == 0xFFFF) ? 0 : vref_start[ch][cs][phase][byte_lane][phy_bit],
                               vref_height[ch][cs][phase][byte_lane][phy_bit],
                               (coarse_cdc == coarse_cdc_max_value) ? dq_dcd[ch][cs][phase][byte_lane][phy_bit]  : 0,
                               (coarse_cdc == coarse_cdc_max_value) ? dqs_dcd[ch][cs][phase][byte_lane][phy_bit] : 0);                    
                    }
                  }                 
                  compare_result_acc_0[byte_lane][phy_bit] = 0;
                  compare_result_acc_1[byte_lane][phy_bit] = 0;                 
                }          
              }
            } // cs
          } // ch          
	      } // fine_cdc     
      } // coarse_cdc 
    } // VREF
    ddr_printf (DDR_NORMAL,"\n\n");
    
    // Restore the Global VREF and IO qualifier local VREF
    for (ch=CH_START;ch<NUM_CH;ch++)
    {
      dq0_ddr_phy_base    = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
     
      for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++) 
      {     
        if(mp_hp == HPVREF)
        {
            // Restore decouple bit.
            decouple_bit[byte_lane] = (decouple_bit[byte_lane] & 0xFFFFFFFD);
            HWIO_OUTX(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                      DDR_PHY_DDRPHY_PAD_DQS_1_CFG, 
                      decouple_bit[byte_lane]);
	  				
	  				// restore mprx vref to mprx vref reg.             
            DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                        0x1F,
                                        HIGHEST_MPRX_FPRS_FREQ,
                                        0);
                                         
            // restore mprx vref to mprx vref reg.             
            DDR_PHY_hal_cfg_global_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET),
                                        trained_vref[ch][0][byte_lane],
                                        clk_freq_khz,
                                        0);
          
            // Restore the IO Qualifier local VREF
            DDR_PHY_hal_cfg_local_vref(dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                                       DQS_VREF, 
                                       cs,
                                       10
                                       );
        }
        else
        {
          for (cs=0;cs<NUM_CS;cs++)
          {
            // Store the global VREF to restore after plotting
            if (cs == 0)
            {
              HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                          DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                          VREF_PAD_RFU_R0,
                          trained_vref[ch][cs][byte_lane]);
            }
            else
            {
              HWIO_OUTXF (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET), 
                          DDR_PHY_DDRPHY_PAD_VREF_CFG, 
                          VREF_PAD_RFU_R1, 
                          trained_vref[ch][cs][byte_lane]);
            }
          } 
        }
      }
    }  
    fclose(fp);  
    printf ("\nEnd RD Plot for %d MHz\n\n",clk_freq_khz);   
  } // FILE open    
}
#endif  // DSF_RD_DQDQS_COARSE_FINE_PLOT_PIVOT

#if DSF_WR_DQDQS_COARSE_FINE_PLOT_PIVOT
//================================================================================================//
//  Function: wr_dqdqs_coarse_fine_plot().
//  Brief description: 
//================================================================================================//
void DDRSS_wr_dqdqs_coarse_fine_plot_pivot (DDR_STRUCT *ddr, 
                                            char *fout,
                                            training_params_t *training_params_ptr,
                                            uint32 clk_freq_khz
                                            )
{
#define CH_START 1
  FILE  *fp;
  uint8  ch                   = 0;
  uint8  cs                   = 0;
  uint8  bit                  = 0;
  uint8  byte_lane            = 0;
  uint32 dq0_ddr_phy_base     = 0;
  uint32 ca0_ddr_phy_base     = 0;
  uint8  phase                = 0;
  uint8  vref                 = 0;
  uint8  coarse_cdc           = 0;
  uint8  coarse_cdc_max_value = 0;
  uint8  fine_cdc             = 0;
  uint8  mc_bit               = 0;
  uint8  phy_bit              = 0;
  uint8  mp_hp                = 0;
  uint8  full_cycle_steps     = 0;
  uint8  vref_max_value       = 0;
  uint8  vref_start_value     = 0;
  uint16 super_iteration      = 0;
  uint32 word[NUM_CH][NUM_CS][PHASE]                   = {{{0}}};      
  uint8 compare_result_acc_0[NUM_DQ_PCH][PINS_PER_PHY] = {{0}}; 
  uint8 compare_result_acc_1[NUM_DQ_PCH][PINS_PER_PHY] = {{0}};
  uint8 decouple_bit[NUM_DQ_PCH]                       = {0};    
  uint8 ioqual_vref           = 0x10;
  uint8 trained_vref[NUM_CH][NUM_CS][NUM_DQ_PCH]       = {{{0}}};
  uint8 trained_coarse_cdc[NUM_CH][NUM_CS][NUM_DQ_PCH] = {{{0}}};
  uint8 trained_fine_cdc  [NUM_CH][NUM_CS][NUM_DQ_PCH] = {{{0}}};
  uint8 version = TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION;
 
  uint8          MR14_value  = 0;
  uint8 MR14_vref_range_bit  = 0;
  
  uint8             clk_idx = 0;
  uint8     current_clk_inx = 0;
  
  uint8 coarse_wrlvl_delay[NUM_DQ_PCH] = {0};
  uint8 fine_wrlvl_delay  [NUM_DQ_PCH] = {0};
  
  // Training data structure pointer
  training_data *training_data_ptr;
  training_data_ptr = (training_data *)(&ddr->flash_params.training_data);
  
  // Choose Vref_Range_bit according to frequency threshold.
  MR14_vref_range_bit = (clk_freq_khz > ODT_FSP_EN_FREQ_THRESHOLD) ? 0: 1;
  
  for (clk_idx = (sizeof(freq_range)/sizeof(freq_range[0])); clk_idx > 0; clk_idx--)
  {
    if (clk_freq_khz >= freq_range[clk_idx-1])
      break;
  }
  current_clk_inx = clk_idx + 1;
  
  for (byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
  {
    // Initialize the WRLVL delays
    coarse_wrlvl_delay[byte_lane] = training_data_ptr->results.wrlvl.dq_coarse_dqs_delay[current_clk_inx][ch][cs][byte_lane];
    fine_wrlvl_delay  [byte_lane] = training_data_ptr->results.wrlvl.dq_fine_dqs_delay[current_clk_inx][ch][cs][byte_lane];
  }
  
  // Calculate coarse CDC max value based on period
  full_cycle_steps = (CONVERT_CYC_TO_PS / clk_freq_khz) / COARSE_STEP_IN_PS;
  coarse_cdc_max_value = ((full_cycle_steps + 1) > COARSE_CDC_MAX_VALUE) ? COARSE_CDC_MAX_VALUE : (full_cycle_steps + 1);
  
  // Vref range
  vref_start_value = training_params_ptr->wr_dqdqs.coarse_vref_start_value;
  vref_max_value = training_params_ptr->wr_dqdqs.coarse_vref_max_value;
  
  printf ("\nWR Plot for %d MHz\n\n",clk_freq_khz);

  if ((fp = fopen(fout,"w")) != NULL)
  {
    // Print CSV file header
    fprintf(fp,"MSM Serial,DSF Version,Frequency,Read/Write,Channel,Rank,Byte,Bit,Phase,Vref,Coarse,Fine,Value\r\n");
      
    // Read the trained CDC and VREF  
    for (ch=CH_START;ch<NUM_CH;ch++)
    {
      dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
      
      for (cs=0;cs<NUM_CS;cs++)
      {  
        for (byte_lane = 0;byte_lane < NUM_DQ_PCH;byte_lane++)
        {
          trained_vref      [ch][cs][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value[current_clk_inx][ch][cs][0];
          trained_coarse_cdc[ch][cs][byte_lane] = training_data_ptr->results.wr_dqdqs.coarse_cdc[current_clk_inx][ch][cs][byte_lane];
          trained_fine_cdc  [ch][cs][byte_lane] = training_data_ptr->results.wr_dqdqs.fine_cdc[current_clk_inx][ch][cs][byte_lane];  
          
          trained_coarse_cdc[ch][cs][byte_lane] += trained_fine_cdc[ch][cs][byte_lane]/FINE_STEPS_PER_COARSE;                   
          trained_fine_cdc  [ch][cs][byte_lane] %= FINE_STEPS_PER_COARSE;         
        }
      }
    }      
    
    ddr_printf (DDR_NORMAL, "WR Plot Vref ");
    // Main VREF/CDC sweep loop     
    for (vref = vref_start_value; vref <= vref_max_value; vref++)  
    {
      ddr_printf (DDR_NORMAL, "->%d",vref);
      for (ch=CH_START;ch<NUM_CH;ch++)
      {
        // Set DQ0 base for addressing
        dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
        
        for (cs=0;cs<NUM_CS;cs++)
        {
          MR14_value = ((MR14_vref_range_bit << 6) | (vref << 0));
          BIMC_MR_Write (CH_1HOT(ch), CS_1HOT(cs), JEDEC_MR_14, MR14_value);
        }
      }
          
      for (coarse_cdc = 0; coarse_cdc <= coarse_cdc_max_value; coarse_cdc++)
      {
        for (ch=0;ch<NUM_CH;ch++)
        {
          // Set DQ0 base for addressing
          dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
          
          for (cs=0;cs<NUM_CS;cs++)
          {
            for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
            {
              DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                            coarse_cdc,
                                            1, 1, cs); // 1 for coarse_delay_mode. 1 for hp_mode.
            }
          }
        }
        
        for (fine_cdc = 0;fine_cdc <FINE_STEPS_PER_COARSE; fine_cdc++)       
      //for (fine_cdc = WRITE_FINE_CDC_MIN; fine_cdc <= WRITE_FINE_CDC_MAX; fine_cdc++)
        {
          for (ch=CH_START;ch<NUM_CH;ch++)
          {
            // Set DQ0 base for addressing
            dq0_ddr_phy_base = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
            
            for (cs=0;cs<NUM_CS;cs++)
            {
              for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
              {
                DDR_PHY_hal_cfg_cdc_slave_wr((dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                              fine_cdc,
                                              0, 1, cs); // 0 for coarse_delay_mode. 1 for hp_mode.
                DDRSS_CDC_Retimer (ddr,
                                   cs,
                                   coarse_cdc,
                                   fine_cdc,
                                   coarse_wrlvl_delay[byte_lane],
                                   fine_wrlvl_delay[byte_lane],
                                   (dq0_ddr_phy_base + (byte_lane * DDR_PHY_OFFSET)),
                                   clk_freq_khz);
              }
            }
          }
          
          for (ch=CH_START;ch<NUM_CH;ch++)
          {
            for (cs=0;cs<NUM_CS;cs++)
            {
#if DSF_PXI_TRAINING_EN
              Initialize_PXI_Tables(ddr, ch, cs, 2, 0); //ch, cs, wr/rd, dbi
              DDRSS_mem_write_PXI(ddr, ch, cs, 0, 1); //ddr, ch, cs, dbi, prbs
              Initialize_PXI_Tables(ddr, ch, cs, 1, 0); //ch, cs, wr/rd, dbi
              DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0,1);
              DDRSS_mem_read_per_bit_phase_PXI(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1,1);                
#else 
              DDRSS_mem_write(ddr, ch, cs);
              DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_0, 0x0);
              DDRSS_mem_read_per_bit_phase(ddr, ch, cs, NUM_DQ_PCH, compare_result_acc_1, 0x1);           
#endif
              for (byte_lane =0;byte_lane<NUM_DQ_PCH;byte_lane++)
              {
                for (bit=0;bit<PINS_PER_PHY_CONNECTED_NO_DBI;bit++)
                {
                  phy_bit = connected_bit_mapping_no_DBI_A[bit];
                  mc_bit  = bit_remapping_phy2bimc_DQ[ch][byte_lane][bit];
                  
                  for (phase=0;phase<PHASE;phase++)
                  {
                    // Print the training center pixel
                    if ((vref       == trained_vref      [ch][cs][byte_lane]) && 
                        (coarse_cdc == trained_coarse_cdc[ch][cs][byte_lane])  &&
                        (fine_cdc   == trained_fine_cdc  [ch][cs][byte_lane]))
                    {
                      compare_result_acc_0[byte_lane][phy_bit] = 1;
                      compare_result_acc_1[byte_lane][phy_bit] = 1;
                    }   
                    
                    if (phase == 0)
                    {
                      fprintf (fp,"DSF_SIM,%d,%d,WRITE,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
                               version,clk_freq_khz,ch,cs,byte_lane,phy_bit,phase,vref,coarse_cdc,fine_cdc,compare_result_acc_0[byte_lane][phy_bit]);
                    }
                    else
                    {
                      fprintf (fp,"DSF_SIM,%d,%d,WRITE,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
                               version,clk_freq_khz,ch,cs,byte_lane,phy_bit,phase,vref,coarse_cdc,fine_cdc,compare_result_acc_1[byte_lane][phy_bit]<<1);                    
                    }
                  }                  
                  compare_result_acc_0[byte_lane][phy_bit] = 0;
                  compare_result_acc_1[byte_lane][phy_bit] = 0;                 
                }          
              }              
            } // cs
          } // ch          
	     } // fine_cdc
      } // coarse_cdc
    } // VREF
    ddr_printf (DDR_NORMAL, "\n\n");
    fclose(fp);    
  } // file open
}
#endif  // DSF_WR_DQDQS_COARSE_FINE_PLOT_PIVOT

