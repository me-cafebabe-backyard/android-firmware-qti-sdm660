/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/bimc/mc230/src/bimc_data_lpddr4_rpm.c#10 $
$DateTime: 2017/11/28 05:32:14 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/04/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "bimc_rpm.h"

//================================================================================================//
// Read and Write Latency Tables
// RL, WL and corresponding MR2 values
//================================================================================================//
struct ecdt_dram_latency_runtime_struct RL_WL_lpddr_struct[] =
{
    /*RL,      RL         RL         RL 
   DBI_OFF_x16 DBI_ON_x16 DBI_OFF_x8 DBI_ON_x8  WL,  MR2,  freq */
   { 6 ,        6 ,         6 ,         6 ,     4 ,  0x00, 266000},  /*   10 < F <= 266MHz  */
   { 10,        12,         10,         12,     6 ,  0x09, 533000},  /*  266 < F <= 533MHz  */
   { 14,        16,         16,         18,     8 ,  0x12, 800000},  /*  533 < F <= 800MHz  */
   { 20,        22,         22,         24,     10,  0x1B, 1066000}, /*  800 < F <= 1066MHz */
   { 24,        28,         26,         30,     12,  0x24, 1333000}, /* 1066 < F <= 1333MHz */
   { 28,        32,         32,         36,     14,  0x2D, 1600000}, /* 1333 < F <= 1600MHz */
   { 32,        36,         36,         40,     16,  0x36, 1866000}, /* 1600 < F <= 1866MHz */
   { 36,        40,         40,         44,     18,  0x3F, 2133000}, /* 1866 < F <= 2133MHz */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}, /* reserved */
   {  0,         0,          0,          0,      0,     0,       0}  /* reserved */

};

uint8 RL_WL_freq_range_table_size = sizeof(RL_WL_lpddr_struct)/sizeof(struct ecdt_dram_latency_runtime_struct);

//================================================================================================//
// Frequency tables for other LPDDR4 specific timing parameters
// ODTLon:  ODTLon values.
// MR13_wrdata: MR13 write data used during frequency switch across 2 FSP sets.
//================================================================================================//
uint8 ODTLon[][2]= {
   /*WPRE_1, WPRE_2*/
   { 0x4,    0x4 },     /*   10 < F <= 266MHz  */
   { 0x4,    0x4 },     /*  266 < F <= 533MHz  */
   { 0x4,    0x4 },     /*  533 < F <= 800MHz  */
   { 0x4,    0x4 },     /*  800 < F <= 1066MHz */
   { 0x6,    0x4 },     /* 1066 < F <= 1333MHz */
   { 0x6,    0x6 },     /* 1333 < F <= 1600MHz */
   { 0x8,    0x6 },     /* 1600 < F <= 1866MHz */
   { 0x8,    0x8 }      /* 1866 < F <= 2133MHz */
};

struct ecdt_bimc_freq_switch_params_runtime_struct bimc_freq_switch_params_struct[] =
{
   /* RD-DBI, ODT, FSP, MR1,  MR3,  MR11, freq_switch_params_freq_range */
   { 0,   0,   0,   0x16,   0xB0,   0x00,  400000}, /*  10  < F <= 400MHz, WR-pre =1, DBI_WR=1          */
   { 0,   0,   0,   0x26,   0xB0,   0x00,  750000}, /* 400  < F <= 750MHz, PU-CAL=Vddq/2.5              */
   { 0,   0,   0,   0x36,   0xB0,   0x00, 1000000}, /* 750  < F <= 1000MHz,                             */
   { 0,   1,   1,   0xC6,   0xB1,   0x45, 1295000}, /* 1000 < F <= 1295MHz CA-ODT=Rzq/2, DQ-ODT=Rzq/3   */ //MR1 - 0x46 (Default)
   { 0,   1,   1,   0xDE,   0xB1,   0x45, 1570000}, /* 1295 < F <= 1570MHz RD-PRE=1,  DQ ODT = 80ohm    */ //MR1 - 0x5E (Default)
   { 0,   1,   1,   0xEE,   0xB3,   0x45, 1890000}, /* 1570 < F <= 1890MHz WR-PST =1, DQ ODT = 60ohm    */ //MR1 - 0x6E (Default)
   { 0,   0,   0,      0,      0,      0,       0}, /* reserved                                         */
   { 0,   0,   0,      0,      0,      0,       0}  /* reserved                                         */
};

/*  ********************************* Original setting ************************
 struct ecdt_bimc_freq_switch_params_runtime_struct bimc_freq_switch_params_struct_lp4x[] =
{
   // RD-DBI, ODT, FSP, MR1,  MR3,  MR11, freq_switch_params_freq_range 
   { 0,   0,   0,   0x06,   0xB0,   0x00,  400000}, //  10  < F <= 400MHz, WR-pre =1, DBI_WR=1         
   { 0,   0,   0,   0x06,   0xB0,   0x00,  750000}, // 400  < F <= 750MHz, PU-CAL=Vddq/2.5              
   { 0,   0,   0,   0x06,   0xB0,   0x00, 1000000}, // 750  < F <= 1000MHz,                             
   { 0,   1,   1,   0x06,   0xB0,   0x33, 1295000}, // 1000 < F <= 1295MHz CA-ODT=Rzq/2, DQ-ODT=Rzq/3  
   { 0,   1,   1,   0x0E,   0xB0,   0x33, 1570000}, // 1295 < F <= 1570MHz RD-PRE=1,  DQ ODT = 80ohm    
   { 0,   1,   1,   0x0E,   0xB2,   0x34, 1890000}, // 1570 < F <= 1890MHz WR-PST =1, DQ ODT = 60ohm   
   { 0,   0,   0,      0,      0,      0,       0}, // reserved                                         
   { 0,   0,   0,      0,      0,      0,       0}  // reserved                                        
};
*/
struct ecdt_bimc_freq_switch_params_runtime_struct bimc_freq_switch_params_struct_lp4x[] =
{
   /* RD-DBI, ODT, FSP, MR1,  MR3,  MR11, freq_switch_params_freq_range */
   { 0,   0,   0,   0x16,   0xB0,   0x00,  400000}, /*  10  < F <= 400MHz, WR-pre =1, DBI_WR=1          */
   { 0,   0,   0,   0x26,   0xB0,   0x00,  750000}, /* 400  < F <= 750MHz, PU-CAL=Vddq/2.5              */
   { 0,   0,   0,   0x36,   0xB0,   0x00, 1000000}, /* 750  < F <= 1000MHz,                             */
   { 0,   1,   1,   0xC6,   0xB0,   0x44, 1295000}, /* 1000 < F <= 1295MHz CA-ODT=Rzq/2, DQ-ODT=Rzq/3   */
   { 0,   1,   1,   0xDE,   0xB0,   0x44, 1570000}, /* 1295 < F <= 1570MHz RD-PRE=1,  DQ ODT = 80ohm    */
   { 0,   1,   1,   0xEE,   0xB2,   0x44, 1890000}, /* 1570 < F <= 1890MHz WR-PST =1, DQ ODT = 60ohm    */
   { 0,   0,   0,      0,      0,      0,       0}, /* reserved                                         */
   { 0,   0,   0,      0,      0,      0,       0}  /* reserved                                         */
};

uint8 bimc_freq_switch_params_table_size = sizeof(bimc_freq_switch_params_struct)/sizeof(struct ecdt_bimc_freq_switch_params_runtime_struct);


uint8 MR13_wrdata[][2] = {

   /*MR13_1, MR13_2*/
   { 0x58,   0x10},    /*  Next clock FSP Set 0  */
   { 0x98,   0xD0}     /*  Next clock FSP Set 1  */
   /*   FSP Set 0
        MR13_1 = 0x48; //FSP-OP=0, FSP-WR=1, VRCG=1, RRO=1
        MR13_2 = 0x00; //FSP-OP=0, FSP-WR=0, VRCG=0, RRO=1

        FSP Set 1
        MR13_1 = 0x88; //FSP-OP=1, FSP-WR=0, VRCG=1, RRO=1
        MR13_2 = 0xC0; //FSP-OP=1, FSP-WR=1, VRCG=0, RRO=1
   */
};




