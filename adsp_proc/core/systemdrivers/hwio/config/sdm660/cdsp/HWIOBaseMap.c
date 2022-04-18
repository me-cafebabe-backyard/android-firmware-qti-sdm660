
/*
===========================================================================
*/
/**
  @file HWIOBaseMap.c
  @brief Auto-generated HWIO Device Configuration base file.

  DESCRIPTION:
    This file contains Device Configuration data structures for mapping
    physical and virtual memory for HWIO blocks.
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hwio/config/sdm660/cdsp/HWIOBaseMap.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "DalHWIO.h"


/*=========================================================================
      Data Definitions
==========================================================================*/

static HWIOModuleType HWIOModules_CLK_CTL[] =
{
  { "GCC_CLK_CTL_REG",                             0x00000000, 0x000b0000 },
  { "GCC_RPU_RPU32Q2N7S1V0_176_CL36L12",           0x000b0000, 0x00006800 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM[] =
{
  { "RPM_DEC",                                     0x00080000, 0x00002000 },
  { "RPM_QTMR_AC",                                 0x00082000, 0x00001000 },
  { "RPM_F0_QTMR_V1_F0",                           0x00083000, 0x00001000 },
  { "RPM_F1_QTMR_V1_F1",                           0x00084000, 0x00001000 },
  { "RPM_MSTR_MPU",                                0x00086000, 0x00001a00 },
  { "RPM_VMIDMT",                                  0x00088000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SPDM_WRAPPER_TOP[] =
{
  { "SPDM_SPDM_CREG",                              0x00000000, 0x00000120 },
  { "SPDM_SPDM_OLEM",                              0x00001000, 0x0000015c },
  { "SPDM_SPDM_RTEM",                              0x00002000, 0x00000318 },
  { "SPDM_SPDM_SREG",                              0x00004000, 0x00000120 },
  { "SPDM_APU32Q2N7S1V1_1_CL36",                   0x00006000, 0x00001080 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SECURITY_CONTROL[] =
{
  { "SECURITY_CONTROL_CORE",                       0x00000000, 0x00007000 },
  { "SECURE_CHANNEL",                              0x00008000, 0x00003000 },
  { "SEC_CTRL_APU_APU32Q2N7S1V0_25_CL36",          0x0000e000, 0x00001c80 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PRNG_CFG_PRNG_TOP[] =
{
  { "PRNG_CFG_CM_CM_PRNG_CM",                      0x00000000, 0x00001000 },
  { "PRNG_CFG_TZ_TZ_PRNG_TZ",                      0x00001000, 0x00001000 },
  { "PRNG_CFG_MSA_MSA_PRNG_SUB",                   0x00002000, 0x00001000 },
  { "PRNG_CFG_EE2_EE2_PRNG_SUB",                   0x00003000, 0x00001000 },
  { "PRNG_CFG_EE3_EE3_PRNG_SUB",                   0x00004000, 0x00001000 },
  { "PRNG_CFG_EE4_EE4_PRNG_SUB",                   0x00005000, 0x00001000 },
  { "PRNG_CFG_EE5_EE5_PRNG_SUB",                   0x00006000, 0x00001000 },
  { "PRNG_CFG_EE6_EE6_PRNG_SUB",                   0x00007000, 0x00001000 },
  { "PRNG_CFG_EE7_EE7_PRNG_SUB",                   0x00008000, 0x00001000 },
  { "PRNG_CFG_EE8_EE8_PRNG_SUB",                   0x00009000, 0x00001000 },
  { "PRNG_CFG_EE9_EE9_PRNG_SUB",                   0x0000a000, 0x00001000 },
  { "PRNG_CFG_EE10_EE10_PRNG_SUB",                 0x0000b000, 0x00001000 },
  { "PRNG_CFG_EE11_EE11_PRNG_SUB",                 0x0000c000, 0x00001000 },
  { "PRNG_CFG_EE12_EE12_PRNG_SUB",                 0x0000d000, 0x00001000 },
  { "PRNG_CFG_EE13_EE13_PRNG_SUB",                 0x0000e000, 0x00001000 },
  { "PRNG_CFG_EE14_EE14_PRNG_SUB",                 0x0000f000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_DDR_SS[] =
{
  { "MCCC_MCCC",                                   0x00000000, 0x00000800 },
  { "MCCC_MCCC_CH0_MCCC_CH0_MCCC_CH_REGS",         0x00000000, 0x00000100 },
  { "MCCC_MCCC_CH1_MCCC_CH1_MCCC_CH_REGS",         0x00000100, 0x00000100 },
  { "MCCC_MCCC_REGS",                              0x00000200, 0x00000100 },
  { "MCCC_XPU_APU32Q2N7S1V0_2_CL36",               0x00001000, 0x00001100 },
  { "BIMC",                                        0x00003000, 0x00080000 },
  { "BIMC_GLOBAL0",                                0x00003000, 0x00001000 },
  { "BIMC_GLOBAL1",                                0x00004000, 0x00001000 },
  { "BIMC_GLOBAL2",                                0x00005000, 0x00001000 },
  { "BIMC_CONFIG_APU",                             0x00007000, 0x00001800 },
  { "BIMC_PERFMON",                                0x00006000, 0x00001000 },
  { "BIMC_DTE",                                    0x00009000, 0x0000005c },
  { "BIMC_M_APP_MPORT",                            0x0000b000, 0x00001000 },
  { "BIMC_M_GPU_MPORT",                            0x0000f000, 0x00001000 },
  { "BIMC_M_MMSS_MPORT",                           0x00013000, 0x00001000 },
  { "BIMC_M_SYS_MPORT",                            0x00017000, 0x00001000 },
  { "BIMC_M_PIMEM_MPORT",                          0x0001b000, 0x00001000 },
  { "BIMC_M_MDSP_MPORT",                           0x0001f000, 0x00001000 },
  { "BIMC_M_CDSP_MPORT",                           0x00023000, 0x00001000 },
  { "BIMC_M_APP_PROF",                             0x0000c000, 0x00001000 },
  { "BIMC_M_GPU_PROF",                             0x00010000, 0x00001000 },
  { "BIMC_M_MMSS_PROF",                            0x00014000, 0x00001000 },
  { "BIMC_M_SYS_PROF",                             0x00018000, 0x00001000 },
  { "BIMC_M_PIMEM_PROF",                           0x0001c000, 0x00001000 },
  { "BIMC_M_MDSP_PROF",                            0x00020000, 0x00001000 },
  { "BIMC_M_CDSP_PROF",                            0x00024000, 0x00001000 },
  { "BIMC_S_DDR0_SCMO",                            0x00033000, 0x00001000 },
  { "BIMC_S_DDR1_SCMO",                            0x0003f000, 0x00001000 },
  { "BIMC_S_APP_SWAY",                             0x0004b000, 0x00001000 },
  { "BIMC_S_SYS0_SWAY",                            0x00053000, 0x00001000 },
  { "BIMC_S_DEFAULT_SWAY",                         0x0005b000, 0x00001000 },
  { "BIMC_S_DDR0_ARB",                             0x00034000, 0x00001000 },
  { "BIMC_S_DDR1_ARB",                             0x00040000, 0x00001000 },
  { "BIMC_S_APP_ARB",                              0x0004c000, 0x00001000 },
  { "BIMC_S_SYS0_ARB",                             0x00054000, 0x00001000 },
  { "BIMC_S_DEFAULT_ARB",                          0x0005c000, 0x00001000 },
  { "BIMC_S_DDR0",                                 0x00035000, 0x00001c80 },
  { "BIMC_S_DDR0_DPE",                             0x00037000, 0x00001000 },
  { "BIMC_S_DDR0_SHKE",                            0x00038000, 0x00001000 },
  { "BIMC_S_DDR0_DTTS_CFG",                        0x00039000, 0x00001000 },
  { "BIMC_S_DDR0_DTTS_SRAM",                       0x0003a000, 0x00004000 },
  { "BIMC_S_DDR1",                                 0x00041000, 0x00001c80 },
  { "BIMC_S_DDR1_DPE",                             0x00043000, 0x00001000 },
  { "BIMC_S_DDR1_SHKE",                            0x00044000, 0x00001000 },
  { "BIMC_S_DDR1_DTTS_CFG",                        0x00045000, 0x00001000 },
  { "BIMC_S_DDR1_DTTS_SRAM",                       0x00046000, 0x00004000 },
  { "CH0_CA0_DDR_PHY",                             0x00083000, 0x00001000 },
  { "CH0_CA1_DDR_PHY",                             0x00084000, 0x00001000 },
  { "CH0_DQ0_DDR_PHY",                             0x00085000, 0x00001000 },
  { "CH0_DQ1_DDR_PHY",                             0x00086000, 0x00001000 },
  { "CH0_DQ2_DDR_PHY",                             0x00087000, 0x00001000 },
  { "CH0_DQ3_DDR_PHY",                             0x00088000, 0x00001000 },
  { "CH0_DDR_CC",                                  0x00089000, 0x00001000 },
  { "CH1_CA0_DDR_PHY",                             0x0008a000, 0x00001000 },
  { "CH1_CA1_DDR_PHY",                             0x0008b000, 0x00001000 },
  { "CH1_DQ0_DDR_PHY",                             0x0008c000, 0x00001000 },
  { "CH1_DQ1_DDR_PHY",                             0x0008d000, 0x00001000 },
  { "CH1_DQ2_DDR_PHY",                             0x0008e000, 0x00001000 },
  { "CH1_DQ3_DDR_PHY",                             0x0008f000, 0x00001000 },
  { "CH1_DDR_CC",                                  0x00090000, 0x00001000 },
  { "DDR_REG_DDR_SS_REGS",                         0x00091000, 0x00000400 },
  { "DDR_CC_MCCC_DDR_CC_MCCC",                     0x00092000, 0x00000400 },
  { "DDRSS_AHB2PHY_SWMAN",                         0x000a1000, 0x00000400 },
  { "DDRSS_AHB2PHY_BROADCAST_SWMAN1",              0x000a2000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MPM2_MPM[] =
{
  { "MPM2_MPM",                                    0x00000000, 0x00001000 },
  { "MPM2_G_CTRL_CNTR",                            0x00001000, 0x00001000 },
  { "MPM2_G_RD_CNTR",                              0x00002000, 0x00001000 },
  { "MPM2_SLP_CNTR",                               0x00003000, 0x00001000 },
  { "MPM2_QTIMR_AC",                               0x00004000, 0x00001000 },
  { "MPM2_QTIMR_V1",                               0x00005000, 0x00001000 },
  { "MPM2_TSYNC",                                  0x00006000, 0x00001000 },
  { "MPM2_WDOG",                                   0x00007000, 0x00000020 },
  { "MPM2_APU",                                    0x00008000, 0x00001680 },
  { "MPM2_TSENS0",                                 0x0000a000, 0x00001000 },
  { "MPM2_TSENS0_TSENS0_TM",                       0x0000b000, 0x00001000 },
  { "MPM2_PSHOLD",                                 0x0000c000, 0x00001000 },
  { "MPM2_TSENS1",                                 0x0000d000, 0x00001000 },
  { "MPM2_TSENS1_TSENS1_TM",                       0x0000e000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CONFIG_NOC_WRAPPER[] =
{
  { "CNOC_A2NOC_MPU_CNOC_A2_NOC_MPU_CFG",          0x00028000, 0x00001300 },
  { "CNOC_SNOC_MPU_CFG",                           0x00024000, 0x00001300 },
  { "CNOC_QDSS_MPU_CFG",                           0x00022000, 0x00001180 },
  { "CNOC_SNOC_MS_MPU_CNOC_MS_NOC_MPU_CFG",        0x00020000, 0x00001f00 },
  { "CNOC_SERVICE_NETWORK",                        0x00000000, 0x00001180 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SYSTEM_NOC[] =
{
  { "SYSTEM_NOC",                                  0x00000000, 0x0000d100 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CORE_TOP_CSR[] =
{
  { "TCSR_MUTEX_RPU32Q2N7S1V0_64_CL36L12",         0x00000000, 0x00003000 },
  { "TCSR_TCSR_MUTEX",                             0x00040000, 0x00040000 },
  { "TCSR_REGS_RPU32Q2N7S1V0_40_CL36L12",          0x00080000, 0x00002400 },
  { "TCSR_TCSR_REGS",                              0x000c0000, 0x00026000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_TLMM[] =
{
  { "TLMM_XPU_SOUTH_XS",                           0x00000000, 0x00006780 },
  { "TLMM_SOUTH",                                  0x00100000, 0x00300000 },
  { "TLMM_XPU_CENTER_XC",                          0x00400000, 0x00006780 },
  { "TLMM_CENTER",                                 0x00500000, 0x00300000 },
  { "TLMM_XPU_NORTH_XN",                           0x00800000, 0x00006780 },
  { "TLMM_NORTH",                                  0x00900000, 0x00300000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_QDSS_SOC_DBG[] =
{
  { "QDSS_APSS_APSS_APSS_DBG",                     0x01800000, 0x00800000 },
  { "QDSS_APSS_APSS_GOLD_APB_APSS_GOLD_APB_A53_APB", 0x01c00000, 0x00341000 },
  { "QDSS_APSS_DL_DL_DRAGONLINK_SLV_CS8254B64",    0x01bc0000, 0x00003000 },
  { "QDSS_APSS_DL_TPDM0_TPDM0_TPDM_ATB32_DSB64_CSF8B13A8B", 0x01bc0000, 0x00001000 },
  { "QDSS_APSS_DL_TPDM0_TPDM_ATB32_DSB64_CSF8B13A8B_SUB", 0x01bc0280, 0x00000d80 },
  { "QDSS_APSS_DL_TPDM0_TPDM_ATB32_DSB64_CSF8B13A8B_GPR", 0x01bc0000, 0x0000027d },
  { "QDSS_APSS_DL_CTI0_CTI0_QC_CTI_CORE",          0x01bc1000, 0x00001000 },
  { "QDSS_APSS_DL_TPDA_TPDA_TPDA_S1_W32_D2_M32_CS78201FC2", 0x01bc2000, 0x00001000 },
  { "QDSS_APSS_APSS_APSS_DEBUG_UI",                0x01bf0000, 0x00001000 },
  { "QDSS_APSS_APSS_APB_APSS_APB_APSS_APB_DFD",    0x01bd0000, 0x00010000 },
  { "QDSS_APSS_APSS_APB_APSS_APB_APSS_APB_MDUMP",  0x01be0000, 0x00010000 },
  { "QDSS_APSS_DL_OLC_DL_OLC_DRAGONLINK_SLV_CS2CE2C3AD", 0x01b90000, 0x00003000 },
  { "QDSS_APSS_DL_OLC_TPDM0_TPDM0_TPDM_ATB32_CMB64_CSE183A91F", 0x01b90000, 0x00001000 },
  { "QDSS_APSS_DL_OLC_TPDM0_TPDM_ATB32_CMB64_CSE183A91F_SUB", 0x01b90280, 0x00000d80 },
  { "QDSS_APSS_DL_OLC_TPDM0_TPDM_ATB32_CMB64_CSE183A91F_GPR", 0x01b90000, 0x0000027d },
  { "QDSS_APSS_DL_OLC_CTI0_CTI0_QC_CTI_CORE",      0x01b91000, 0x00001000 },
  { "QDSS_APSS_DL_OLC_TPDA_TPDA_TPDA_S1_W32_D2_M64_CSE87E6F2", 0x01b92000, 0x00001000 },
  { "QDSS_APSS_CTI_CTI_CSCTI",                     0x01b80000, 0x00001000 },
  { "QDSS_APSS_FUN_FUN_CXATBFUNNEL_128W8SP",       0x01b70000, 0x00001000 },
  { "QDSS_APSS_FUN_ATB_FUN_ATB_CXATBFUNNEL_128W8SP", 0x01b60000, 0x00001000 },
  { "QDSS_APSS_APSS_SILVER_APB_APSS_SILVER_APB_A53_APB", 0x01800000, 0x00341000 },
  { "QDSS_DDRSS_DDRSS_DDR_SS_APB",                 0x011d8000, 0x00008000 },
  { "QDSS_DDRSS_CH0_TGU0_CH0_TGU0_QC_TGU_APCLK_TC_CS734CAB6E", 0x011d8000, 0x00001000 },
  { "QDSS_DDRSS_CH0_TGU1_CH0_TGU1_QC_TGU_APCLK_TC_CS734CAB6E", 0x011d9000, 0x00001000 },
  { "QDSS_DDRSS_CH0_TGU2_CH0_TGU2_QC_TGU_APCLK_TC_CSFA82A8A7", 0x011da000, 0x00001000 },
  { "QDSS_DDRSS_CH1_TGU0_CH1_TGU0_QC_TGU_APCLK_TC_CS734CAB6E", 0x011db000, 0x00001000 },
  { "QDSS_DDRSS_CH1_TGU1_CH1_TGU1_QC_TGU_APCLK_TC_CS734CAB6E", 0x011dc000, 0x00001000 },
  { "QDSS_DDRSS_CH1_TGU2_CH1_TGU2_QC_TGU_APCLK_TC_CSFA82A8A7", 0x011dd000, 0x00001000 },
  { "QDSS_QM_QM_QM_APB",                           0x011d0000, 0x00001000 },
  { "QDSS_QM_MMSS_QM_MMSS_QM_TPDM_ATB32_APCLK_GPRCLK_BC32_DSB128_CSFE693679", 0x011d0000, 0x00001000 },
  { "QDSS_QM_MMSS_QM_TPDM_ATB32_APCLK_GPRCLK_BC32_DSB128_CSFE693679_SUB", 0x011d0280, 0x00000d80 },
  { "QDSS_QM_MMSS_QM_TPDM_ATB32_APCLK_GPRCLK_BC32_DSB128_CSFE693679_GPR", 0x011d0000, 0x0000027d },
  { "QDSS_DLCT_DLCT_DRAGONLINK_SLV_CSCF55D9CA",    0x011c2000, 0x00002000 },
  { "QDSS_DLCT_TPDM0_TPDM0_TPDM_ATB32_DSB160_CS758AC51E", 0x011c2000, 0x00001000 },
  { "QDSS_DLCT_TPDM0_TPDM_ATB32_DSB160_CS758AC51E_SUB", 0x011c2280, 0x00000d80 },
  { "QDSS_DLCT_TPDM0_TPDM_ATB32_DSB160_CS758AC51E_GPR", 0x011c2000, 0x0000027d },
  { "QDSS_DLCT_QATBFUNNEL_QATBFUNNEL_QATBFUNNEL_32W8SP", 0x011c3000, 0x00001000 },
  { "QDSS_WCSS_WCSS_WCSS_DBG",                     0x01198000, 0x00020000 },
  { "QDSS_WCSS_ROM_ROM_WCSS_DBG_DAPROM",           0x01198000, 0x00001000 },
  { "QDSS_WCSS_CSR_CSR_WCSS_DBG_CSR",              0x01199000, 0x00001000 },
  { "QDSS_WCSS_TSGEN_TSGEN_CXTSGEN",               0x0119a000, 0x00001000 },
  { "QDSS_WCSS_TPDM_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D", 0x0119c000, 0x00001000 },
  { "QDSS_WCSS_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D_SUB", 0x0119c280, 0x00000d80 },
  { "QDSS_WCSS_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D_GPR", 0x0119c000, 0x0000027d },
  { "QDSS_WCSS_TPDA_TPDA_TPDA_S1_W128_D8_M64_CS5CD79236", 0x0119d000, 0x00001000 },
  { "QDSS_WCSS_FUN_FUN_CXATBFUNNEL_128W2SP",       0x0119e000, 0x00001000 },
  { "QDSS_WCSS_ETFETB_ETFETB_CXTMC_F128W8K",       0x0119f000, 0x00001000 },
  { "QDSS_WCSS_CTI0_CTI0_CSCTI",                   0x011a4000, 0x00001000 },
  { "QDSS_WCSS_CTI1_CTI1_CSCTI",                   0x011a5000, 0x00001000 },
  { "QDSS_WCSS_CTI2_CTI2_CSCTI",                   0x011a6000, 0x00001000 },
  { "QDSS_WCSS_GPR_GPR_CXGPR_8M",                  0x011b6000, 0x00001000 },
  { "QDSS_WCSS_DSBMUX_DSBMUX_WCSS_DBG_DSBMUX",     0x011b7000, 0x00001000 },
  { "QDSS_NAV_NAV_NAV_DBG",                        0x01190000, 0x00002000 },
  { "QDSS_NAV_DLSLV_DLSLV_DRAGONLINK_SLV_CS84036DC7", 0x01190000, 0x00002000 },
  { "QDSS_NAV_DLSLV_TPDM0_TPDM0_TPDM_ATB32_GPRCLK_CMB32_CS5A073C07", 0x01190000, 0x00001000 },
  { "QDSS_NAV_DLSLV_TPDM0_TPDM_ATB32_GPRCLK_CMB32_CS5A073C07_SUB", 0x01190280, 0x00000d80 },
  { "QDSS_NAV_DLSLV_TPDM0_TPDM_ATB32_GPRCLK_CMB32_CS5A073C07_GPR", 0x01190000, 0x0000027d },
  { "QDSS_NAV_DLSLV_TPDA_TPDA_TPDA_S1_W32_D2_M32_CS78201FC2", 0x01191000, 0x00001000 },
  { "QDSS_MMSS_MMSS_MMSS_MISC_APB_REG",            0x01188000, 0x00008000 },
  { "QDSS_MMSS_MMSS_CSCTI_MMSS_CSCTI_CSCTI",       0x01188000, 0x00001000 },
  { "QDSS_MMSS_MMSS_A9_MMSS_A9_A9ETM",             0x01189000, 0x00001000 },
  { "QDSS_MMSS_MMSS_FUNNEL_MMSS_FUNNEL_CXATBFUNNEL_32W8SP", 0x0118c000, 0x00001000 },
  { "QDSS_A5X_A5X_A5X_DBG",                        0x01100000, 0x00080000 },
  { "QDSS_A5X_SP0_ISDB_SP0_ISDB_A5X_ISDB_0",       0x01100000, 0x00001000 },
  { "QDSS_A5X_SP1_ISDB_SP1_ISDB_A5X_ISDB_0",       0x01101000, 0x00001000 },
  { "QDSS_A5X_SP2_ISDB_SP2_ISDB_A5X_ISDB_0",       0x01102000, 0x00001000 },
  { "QDSS_A5X_SP3_ISDB_SP3_ISDB_A5X_ISDB_0",       0x01103000, 0x00001000 },
  { "QDSS_A5X_HLSQ_ISDB_HLSQ_ISDB_ISDB_HLSQ_REG_DB", 0x01110000, 0x00001000 },
  { "QDSS_A5X_TPDM_TPDM_TPDM_ATB32_ATCLK_APCLK_DSB32_CS870877E5", 0x01111000, 0x00001000 },
  { "QDSS_A5X_TPDM_TPDM_ATB32_ATCLK_APCLK_DSB32_CS870877E5_SUB", 0x01111280, 0x00000d80 },
  { "QDSS_A5X_TPDM_TPDM_ATB32_ATCLK_APCLK_DSB32_CS870877E5_GPR", 0x01111000, 0x0000027d },
  { "QDSS_A5X_ISDB_CTI_ISDB_CTI_CSCTI",            0x01121000, 0x00001000 },
  { "QDSS_A5X_CX_ATBF_CX_ATBF_QATBFUNNEL_32W8SP",  0x01140000, 0x00001000 },
  { "QDSS_TURING_QDSP6_CTI_TURING_QDSP6_CTI_CSCTI", 0x01068000, 0x00001000 },
  { "QDSS_LPASS_LPASS_LPASS_TRACE32_DEBUG",        0x01060000, 0x00008000 },
  { "QDSS_LPASS_CTI_0_CTI_0_CSCTI",                0x01060000, 0x00001000 },
  { "QDSS_LPASS_CTI_1_CTI_1_CSCTI",                0x01061000, 0x00001000 },
  { "QDSS_LPASS_STM_STM_CXSTM_2_4_4_TRUE",         0x01063000, 0x00001000 },
  { "QDSS_LPASS_FUN0_FUN0_CXATBFUNNEL_32W2SP",     0x01064000, 0x00001000 },
  { "QDSS_LPASS_LPASS_ETFETB_LPASS_ETFETB_CXTMC_F32W16K", 0x01065000, 0x00001000 },
  { "QDSS_LPASS_TSGEN_TSGEN_CXTSGEN",              0x01066000, 0x00001000 },
  { "QDSS_APB2JTAG_APB2JTAG_APB2JTAG",             0x01058000, 0x00001000 },
  { "QDSS_DCC_DCC_DCC_DBG",                        0x01054000, 0x00004000 },
  { "QDSS_DCC_DCC_TPDM_DCC_TPDM_TPDM_ATB8_ATCLK_CMB32_CS6DCF0636", 0x01054000, 0x00001000 },
  { "QDSS_DCC_DCC_TPDM_TPDM_ATB8_ATCLK_CMB32_CS6DCF0636_SUB", 0x01054280, 0x00000d80 },
  { "QDSS_DCC_DCC_TPDM_TPDM_ATB8_ATCLK_CMB32_CS6DCF0636_GPR", 0x01054000, 0x0000027d },
  { "QDSS_PIMEM_PIMEM_PIMEM_DBG",                  0x01050000, 0x00004000 },
  { "QDSS_PIMEM_PIMEM_TPDM_PIMEM_TPDM_TPDM_ATB64_APCLK_GPRCLK_BC8_TC2_CMB64_DSB64_CSAF4CCF0", 0x01050000, 0x00001000 },
  { "QDSS_PIMEM_PIMEM_TPDM_TPDM_ATB64_APCLK_GPRCLK_BC8_TC2_CMB64_DSB64_CSAF4CCF0_SUB", 0x01050280, 0x00000d80 },
  { "QDSS_PIMEM_PIMEM_TPDM_TPDM_ATB64_APCLK_GPRCLK_BC8_TC2_CMB64_DSB64_CSAF4CCF0_GPR", 0x01050000, 0x0000027d },
  { "QDSS_PRNG_PRNG_PRNG_DBG",                     0x0104c000, 0x00004000 },
  { "QDSS_PRNG_PRNG_TPDM_PRNG_TPDM_TPDM_ATB32_APCLK_CMB32_CSA14715CD", 0x0104c000, 0x00001000 },
  { "QDSS_PRNG_PRNG_TPDM_TPDM_ATB32_APCLK_CMB32_CSA14715CD_SUB", 0x0104c280, 0x00000d80 },
  { "QDSS_PRNG_PRNG_TPDM_TPDM_ATB32_APCLK_CMB32_CSA14715CD_GPR", 0x0104c000, 0x0000027d },
  { "QDSS_RPM_M3_CTI_RPM_M3_CTI_CSCTI",            0x01048000, 0x00001000 },
  { "QDSS_MSS_MSS_MSS_DBG",                        0x01040000, 0x00004000 },
  { "QDSS_MSS_QDSP6_CTI_QDSP6_CTI_CSCTI",          0x01041000, 0x00001000 },
  { "QDSS_MSS_TPDM_TPDM_TPDM_ATB32_CMB14_DSB35_CS9E39B966", 0x01042000, 0x00001000 },
  { "QDSS_MSS_TPDM_TPDM_ATB32_CMB14_DSB35_CS9E39B966_SUB", 0x01042280, 0x00000d80 },
  { "QDSS_MSS_TPDM_TPDM_ATB32_CMB14_DSB35_CS9E39B966_GPR", 0x01042000, 0x0000027d },
  { "QDSS_MSS_TPDA_TPDA_TPDA_S1_W32_D2_M32_CS9FAD450C", 0x01043000, 0x00001000 },
  { "QDSS_VSENSE_VSENSE_VSENSE_CONTROLLER",        0x01038000, 0x00001000 },
  { "QDSS_VSENSE_VSENSE_CONTROLLER_GPR",           0x01038000, 0x0000027d },
  { "QDSS_VSENSE_TPDM_ATB8_ATCLK_GPRCLK_CMB32_CS7743FED2_SUB", 0x01038280, 0x00000d80 },
  { "QDSS_QDSS",                                   0x00000000, 0x01000000 },
  { "QDSS_QDSS_QDSS_APB",                          0x00000000, 0x00080000 },
  { "QDSS_QDSS_QDSSCSR",                           0x00001000, 0x00001000 },
  { "QDSS_QDSS_CXSTM_8_32_32_TRUE",                0x00002000, 0x00001000 },
  { "QDSS_QDSS_QDSS_DL_SLV_QDSS_DL_SLV_DRAGONLINK_SLV_CSB2AEF242", 0x00004000, 0x00002000 },
  { "QDSS_QDSS_QDSS_DL_SLV_TPDA_TPDA_TPDA_S12_W64_D8_M64_CS402BE332", 0x00004000, 0x00001000 },
  { "QDSS_QDSS_QDSS_DL_SLV_QATBFUNNEL_QATBFUNNEL_QATBFUNNEL_64W8SP", 0x00005000, 0x00001000 },
  { "QDSS_QDSS_TPDM0_TPDM0_TPDM_ATB64_DSB256_CSB5ABA515", 0x00006000, 0x00001000 },
  { "QDSS_QDSS_TPDM0_TPDM_ATB64_DSB256_CSB5ABA515_SUB", 0x00006280, 0x00000d80 },
  { "QDSS_QDSS_TPDM0_TPDM_ATB64_DSB256_CSB5ABA515_GPR", 0x00006000, 0x0000027d },
  { "QDSS_QDSS_TGU_HWE_TGU_HWE_QC_TGU_APCLK_TC_CSE0B89182", 0x0000e000, 0x00001000 },
  { "QDSS_QDSS_CTI0_CTI0_CSCTI",                   0x00010000, 0x00001000 },
  { "QDSS_QDSS_CTI1_CTI1_CSCTI",                   0x00011000, 0x00001000 },
  { "QDSS_QDSS_CTI2_CTI2_CSCTI",                   0x00012000, 0x00001000 },
  { "QDSS_QDSS_CTI3_CTI3_CSCTI",                   0x00013000, 0x00001000 },
  { "QDSS_QDSS_CTI4_CTI4_CSCTI",                   0x00014000, 0x00001000 },
  { "QDSS_QDSS_CTI5_CTI5_CSCTI",                   0x00015000, 0x00001000 },
  { "QDSS_QDSS_CTI6_CTI6_CSCTI",                   0x00016000, 0x00001000 },
  { "QDSS_QDSS_CTI7_CTI7_CSCTI",                   0x00017000, 0x00001000 },
  { "QDSS_QDSS_CTI8_CTI8_CSCTI",                   0x00018000, 0x00001000 },
  { "QDSS_QDSS_CTI9_CTI9_CSCTI",                   0x00019000, 0x00001000 },
  { "QDSS_QDSS_CTI10_CTI10_CSCTI",                 0x0001a000, 0x00001000 },
  { "QDSS_QDSS_CTI11_CTI11_CSCTI",                 0x0001b000, 0x00001000 },
  { "QDSS_QDSS_CTI12_CTI12_CSCTI",                 0x0001c000, 0x00001000 },
  { "QDSS_QDSS_CTI13_CTI13_CSCTI",                 0x0001d000, 0x00001000 },
  { "QDSS_QDSS_CTI14_CTI14_CSCTI",                 0x0001e000, 0x00001000 },
  { "QDSS_QDSS_CTI15_CTI15_CSCTI",                 0x0001f000, 0x00001000 },
  { "QDSS_QDSS_CSTPIU_CSTPIU_CSTPIU",              0x00040000, 0x00001000 },
  { "QDSS_QDSS_IN_FUN0_IN_FUN0_CXATBFUNNEL_128W8SP", 0x00041000, 0x00001000 },
  { "QDSS_QDSS_REPL64_REPL64_CXATBREPLICATOR_64WP", 0x00046000, 0x00001000 },
  { "QDSS_QDSS_ETR_ETR_CXTMC_R64W32D",             0x00048000, 0x00001000 },
  { "QDSS_QDSS_IN_FUN1_IN_FUN1_CXATBFUNNEL_128W8SP", 0x00042000, 0x00001000 },
  { "QDSS_QDSS_MERG_FUN_MERG_FUN_CXATBFUNNEL_128W2SP", 0x00045000, 0x00001000 },
  { "QDSS_QDSS_ETFETB_ETFETB_CXTMC_F128W64K",      0x00047000, 0x00001000 },
  { "QDSS_QDSS_VMIDETR_VMIDETR_VMIDMT_IDX_2_SSD1", 0x00049000, 0x00001000 },
  { "QDSS_QDSS_NDPBAM_NDPBAM_BAM_NDP_TOP_AUTO_SCALE_V2_0_XPU3", 0x00060000, 0x00019000 },
  { "QDSS_QDSS_NDPBAM_BAM",                        0x00064000, 0x00015000 },
  { "QDSS_QDSS_QDSS_AHB",                          0x00080000, 0x00001000 },
  { "QDSS_QDSS_VMIDDAP_VMIDDAP_VMIDMT_IDX_2_SSD1", 0x00080000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PMIC_ARB[] =
{
  { "SPMI_CFG_TOP",                                0x00000000, 0x0000d000 },
  { "SPMI_GENI_CFG",                               0x0000a000, 0x00000700 },
  { "SPMI_CFG",                                    0x0000a700, 0x00001a00 },
  { "SPMI_PIC",                                    0x02400000, 0x00220000 },
  { "PMIC_ARB_MPU32Q2N7S1V1_25_CL36M27L12_AHB",    0x00020000, 0x00001c80 },
  { "PMIC_ARB_CORE",                               0x0000f000, 0x00001000 },
  { "PMIC_ARB_CORE_REGISTERS",                     0x00400000, 0x01000000 },
  { "PMIC_ARB_CORE_REGISTERS_OBS",                 0x01400000, 0x01000000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_USB30_PRIM[] =
{
  { "DWC_USB3",                                    0x00000000, 0x0000cd00 },
  { "USB30_QSRAM_REGS",                            0x000fc000, 0x00000100 },
  { "USB30_QSCRATCH",                              0x000f8800, 0x00000400 },
  { "USB30_DBM_REGFILE",                           0x000f8000, 0x00000400 },
  { "USB30_BAM",                                   0x00104000, 0x00017000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS_PDM_PERPH_WEB[] =
{
  { "PERIPH_SS_PDM_WEB_TCXO4",                     0x00000000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS_AHB2PHY_WEST[] =
{
  { "PERIPH_SS_USB3PHY_USB3PHY_CM_USB3_SW",        0x00000000, 0x00001000 },
  { "PERIPH_SS_USB3PHY_QSERDES_COM_QSERDES_COM_USB3_DP_COM", 0x00000000, 0x000001c4 },
  { "PERIPH_SS_USB3PHY_QSERDES_TXA_QSERDES_TXA_USB3_DP_QMP_TX", 0x00000200, 0x0000010c },
  { "PERIPH_SS_USB3PHY_QSERDES_RXA_QSERDES_RXA_USB3_DP_QMP_RX", 0x00000400, 0x000001e0 },
  { "PERIPH_SS_USB3PHY_QSERDES_TXB_QSERDES_TXB_USB3_DP_QMP_TX", 0x00000600, 0x0000010c },
  { "PERIPH_SS_USB3PHY_QSERDES_RXB_QSERDES_RXB_USB3_DP_QMP_RX", 0x00000800, 0x000001e0 },
  { "PERIPH_SS_USB3PHY_PCS_MISC_PCS_MISC_USB3_PCS_MISC", 0x00000a00, 0x00000030 },
  { "PERIPH_SS_USB3PHY_PCS_PCS_USB3_PCS",          0x00000c00, 0x00000218 },
  { "PERIPH_SS_DP_PHY_DP_PHY_CM_DP_4LN_SW",        0x00001000, 0x00000e00 },
  { "PERIPH_SS_DP_PHY",                            0x00001000, 0x0000017c },
  { "PERIPH_SS_DP_PHY_QSERDES_RX0_QSERDES_RX0_USB3_DP_QMP_RX", 0x00001200, 0x000001e0 },
  { "PERIPH_SS_DP_PHY_QSERDES_TX0_QSERDES_TX0_USB3_DP_QMP_TX", 0x00001400, 0x0000010c },
  { "PERIPH_SS_DP_PHY_QSERDES_RX1_QSERDES_RX1_USB3_DP_QMP_RX", 0x00001600, 0x000001e0 },
  { "PERIPH_SS_DP_PHY_QSERDES_TX1_QSERDES_TX1_USB3_DP_QMP_TX", 0x00001800, 0x0000010c },
  { "PERIPH_SS_DP_PHY_QSERDES_COM_QSERDES_COM_USB3_DP_COM", 0x00001c00, 0x000001c4 },
  { "PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PRIM_CM_QUSB2_LQ_1EX", 0x00002000, 0x00000180 },
  { "PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_SEC_CM_QUSB2_LQ_1EX", 0x00004000, 0x00000180 },
  { "PERIPH_SS_AHB2PHY_SWMAN",                     0x00006000, 0x00000400 },
  { "PERIPH_SS_AHB2PHY_BROADCAST_SWMAN",           0x00007000, 0x00000400 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS_SDC2_SDCC5_TOP[] =
{
  { "PERIPH_SS_SDC2_SDCC_SDCC5_HC",                0x00004000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS_SDC1_SDCC5_TOP[] =
{
  { "PERIPH_SS_SDC1_SDCC_SDCC5_HC",                0x00004000, 0x00001000 },
  { "PERIPH_SS_SDC1_SDCC_SDCC5_HC_CMDQ",           0x00005000, 0x00001000 },
  { "PERIPH_SS_SDC1_SDCC_ICE",                     0x00008000, 0x00008000 },
  { "PERIPH_SS_SDC1_SDCC_ICE_REGS",                0x00008000, 0x00002000 },
  { "PERIPH_SS_SDC1_SDCC_ICE_LUT_KEYS",            0x0000a000, 0x00002000 },
  { "PERIPH_SS_SDC1_SDCC_ICE_XPU3",                0x0000c000, 0x00001200 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_PERIPH_SS_BLSP1_BLSP_XPU3[] =
{
  { "PERIPH_SS_BLSP1_BLSP_BAM",                    0x00004000, 0x0001f000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_XPU3",               0x00001000, 0x00003000 },
  { "PERIPH_SS_BLSP1_BLSP_BAM_VMIDMT",             0x00000000, 0x00001000 },
  { "PERIPH_SS_BLSP1_BLSP_UART0_UART0_DM",         0x0002f000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_UART1_UART1_DM",         0x00030000, 0x00000200 },
  { "PERIPH_SS_BLSP1_BLSP_QUP0",                   0x00035000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP1",                   0x00036000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP2",                   0x00037000, 0x00000600 },
  { "PERIPH_SS_BLSP1_BLSP_QUP3",                   0x00038000, 0x00000600 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_TURING[] =
{
  { "TURING_TURING_CC_REG",                        0x00000000, 0x0003f000 },
  { "TURING_TURING_TCSR",                          0x00080000, 0x0000e000 },
  { "TURING_TURING_QOS",                           0x000a0000, 0x00004000 },
  { "TURING_QOS_QOS_TURING_GENERIC",               0x000a0000, 0x00000100 },
  { "TURING_QOS_QOS_TURING_DEBUG",                 0x000a0100, 0x00000200 },
  { "TURING_QOS_QOS_TURING_DANGER",                0x000a0300, 0x00000200 },
  { "TURING_QOS_QOS_TURING_INTERRUPTS",            0x000a1000, 0x00002000 },
  { "TURING_QOS_QOS_THROTTLE",                     0x000a3000, 0x00000100 },
  { "TURING_AHBE_TIME",                            0x000b7000, 0x00001000 },
  { "TURING_Q6SS_MPU",                             0x000b8000, 0x00001e00 },
  { "TURING_QDSP6V60SS_PUBLIC",                    0x00300000, 0x00080000 },
  { "TURING_QDSP6V60SS_PUB",                       0x00300000, 0x00004040 },
  { "TURING_QDSP6V60SS_PRIVATE",                   0x00380000, 0x00080000 },
  { "TURING_QDSP6V60SS_CSR",                       0x00380000, 0x00008028 },
  { "TURING_QDSP6V60SS_L2VIC",                     0x00390000, 0x00001000 },
  { "TURING_QDSP6SS_QDSP6SS_QTMR_AC",              0x003a0000, 0x00001000 },
  { "TURING_QDSP6SS_QTMR_F0_0",                    0x003a1000, 0x00001000 },
  { "TURING_QDSP6SS_QTMR_F1_1",                    0x003a2000, 0x00001000 },
  { "TURING_QDSP6SS_QTMR_F2_2",                    0x003a3000, 0x00001000 },
  { "TURING_QDSP6SS_QDSP6SS_SAW4_QDSP6SS_NOPMIC_WRAPPER", 0x003b0000, 0x00001000 },
  { "TURING_QDSP6SS_SAW4_SPM",                     0x003b0000, 0x00000800 },
  { "TURING_QDSP6SS_SAW4_AVS",                     0x003b0800, 0x00000400 },
  { "TURING_QDSP6SS_SAW4_STS",                     0x003b0c00, 0x00000400 },
  { NULL, 0, 0 }
};

HWIOPhysRegionType HWIOBaseMap[] =
{
  {
    "CLK_CTL",
    (DALSYSMemAddr)0x00100000,
    0x000c0000,
    (DALSYSMemAddr)0xa0000000,
    HWIOModules_CLK_CTL
  },
  {
    "RPM",
    (DALSYSMemAddr)0x00200000,
    0x00100000,
    (DALSYSMemAddr)0xa0100000,
    HWIOModules_RPM
  },
  {
    "SPDM_WRAPPER_TOP",
    (DALSYSMemAddr)0x00620000,
    0x00008000,
    (DALSYSMemAddr)0xa0220000,
    HWIOModules_SPDM_WRAPPER_TOP
  },
  {
    "RPM_SS_MSG_RAM_START_ADDRESS",
    (DALSYSMemAddr)0x00778000,
    0x00007000,
    (DALSYSMemAddr)0xa0378000,
    HWIOModules_RPM_SS_MSG_RAM_START_ADDRESS
  },
  {
    "SECURITY_CONTROL",
    (DALSYSMemAddr)0x00780000,
    0x00010000,
    (DALSYSMemAddr)0xa0480000,
    HWIOModules_SECURITY_CONTROL
  },
  {
    "PRNG_CFG_PRNG_TOP",
    (DALSYSMemAddr)0x00790000,
    0x00010000,
    (DALSYSMemAddr)0xa0590000,
    HWIOModules_PRNG_CFG_PRNG_TOP
  },
  {
    "DDR_SS",
    (DALSYSMemAddr)0x00ffd000,
    0x000a3000,
    (DALSYSMemAddr)0xa1ffd000,
    HWIOModules_DDR_SS
  },
  {
    "MPM2_MPM",
    (DALSYSMemAddr)0x010a0000,
    0x00010000,
    (DALSYSMemAddr)0xa30a0000,
    HWIOModules_MPM2_MPM
  },
  {
    "CONFIG_NOC_WRAPPER",
    (DALSYSMemAddr)0x01500000,
    0x0002a000,
    (DALSYSMemAddr)0xa3100000,
    HWIOModules_CONFIG_NOC_WRAPPER
  },
  {
    "SYSTEM_NOC",
    (DALSYSMemAddr)0x01620000,
    0x0000d100,
    (DALSYSMemAddr)0xa3220000,
    HWIOModules_SYSTEM_NOC
  },
  {
    "CORE_TOP_CSR",
    (DALSYSMemAddr)0x01f00000,
    0x00100000,
    (DALSYSMemAddr)0xa3300000,
    HWIOModules_CORE_TOP_CSR
  },
  {
    "TLMM",
    (DALSYSMemAddr)0x03000000,
    0x00c00000,
    (DALSYSMemAddr)0xa4000000,
    HWIOModules_TLMM
  },
  {
    "QDSS_SOC_DBG",
    (DALSYSMemAddr)0x06000000,
    0x02000000,
    (DALSYSMemAddr)0xa5000000,
    HWIOModules_QDSS_SOC_DBG
  },
  {
    "PMIC_ARB",
    (DALSYSMemAddr)0x08000000,
    0x02800000,
    (DALSYSMemAddr)0xa7000000,
    HWIOModules_PMIC_ARB
  },
  {
    "USB30_PRIM",
    (DALSYSMemAddr)0x0a800000,
    0x00200000,
    (DALSYSMemAddr)0xaa000000,
    HWIOModules_USB30_PRIM
  },
  {
    "PERIPH_SS_PDM_PERPH_WEB",
    (DALSYSMemAddr)0x0c000000,
    0x00004000,
    (DALSYSMemAddr)0xaa400000,
    HWIOModules_PERIPH_SS_PDM_PERPH_WEB
  },
  {
    "PERIPH_SS_AHB2PHY_WEST",
    (DALSYSMemAddr)0x0c010000,
    0x00008000,
    (DALSYSMemAddr)0xaa510000,
    HWIOModules_PERIPH_SS_AHB2PHY_WEST
  },
  {
    "PERIPH_SS_SDC2_SDCC5_TOP",
    (DALSYSMemAddr)0x0c080000,
    0x00020000,
    (DALSYSMemAddr)0xaa680000,
    HWIOModules_PERIPH_SS_SDC2_SDCC5_TOP
  },
  {
    "PERIPH_SS_SDC1_SDCC5_TOP",
    (DALSYSMemAddr)0x0c0c0000,
    0x00020000,
    (DALSYSMemAddr)0xaa7c0000,
    HWIOModules_PERIPH_SS_SDC1_SDCC5_TOP
  },
  {
    "PERIPH_SS_BLSP1_BLSP_XPU3",
    (DALSYSMemAddr)0x0c140000,
    0x00040000,
    (DALSYSMemAddr)0xaa840000,
    HWIOModules_PERIPH_SS_BLSP1_BLSP_XPU3
  },
  {
    "TURING",
    (DALSYSMemAddr)0x1a000000,
    0x00800000,
    (DALSYSMemAddr)0xe8000000,
    HWIOModules_TURING
  },
  { NULL, 0, 0, 0, NULL }
};

