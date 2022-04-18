
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/HWIO/core/HWIOBaseMap.c#4 $
  $DateTime: 2016/12/16 06:36:38 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/HWIODxe/DalHWIO.h"
#include "msmhwiobase.h"


/*=========================================================================
      Data Definitions
==========================================================================*/

static HWIOModuleType HWIOModules_CNOC_0_CENTER_LEFT_BUS_TIMEOUT[] =
{
  { "CNOC_0_CENTER_LEFT_BUS_TIMEOUT",              0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_2_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_2_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_3_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_3_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_2_NORTH_BUS_TIMEOUT[] =
{
  { "CNOC_2_NORTH_BUS_TIMEOUT",                    0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_4_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_4_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_0_NORTH_BUS_TIMEOUT[] =
{
  { "CNOC_0_NORTH_BUS_TIMEOUT",                    0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_1_NORTH_BUS_TIMEOUT[] =
{
  { "CNOC_1_NORTH_BUS_TIMEOUT",                    0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_5_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_5_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_1_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_1_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_USB2_BUS_TIMEOUT[] =
{
  { "CNOC_USB2_BUS_TIMEOUT",                       0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_MM_BUS_TIMEOUT[] =
{
  { "CNOC_MM_BUS_TIMEOUT",                         0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_1_CENTER_LEFT_BUS_TIMEOUT[] =
{
  { "CNOC_1_CENTER_LEFT_BUS_TIMEOUT",              0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_0_SOUTH_BUS_TIMEOUT[] =
{
  { "CNOC_0_SOUTH_BUS_TIMEOUT",                    0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_0_CENTER_RIGHT_BUS_TIMEOUT[] =
{
  { "CNOC_0_CENTER_RIGHT_BUS_TIMEOUT",             0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CNOC_USB3_BUS_TIMEOUT[] =
{
  { "CNOC_USB3_BUS_TIMEOUT",                       0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

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

static HWIOModuleType HWIOModules_BOOT_ROM[] =
{
  { "BOOT_ROM_MPU32Q2N7S1V0_4_CL36M17L10_AHB",     0x000fe000, 0x00001200 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RAMBLUR_PIMEM[] =
{
  { "RAMBLUR_PIMEM_REGS",                          0x00000000, 0x00004000 },
  { "RAMBLUR_PIMEM_APU_APU32Q2N7S1V1_2_CL36",      0x00004000, 0x00001100 },
  { "RAMBLUR_PIMEM_MPU_MPU32Q2N7S1V1_8_CL36M25L10_AXI", 0x00006000, 0x00001400 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_OCIMEM_WRAPPER_CSR[] =
{
  { "OCIMEM_CSR",                                  0x00000000, 0x00000800 },
  { "OCIMEM_APU",                                  0x00002000, 0x00001100 },
  { "OCIMEM_MPU",                                  0x00004000, 0x00001400 },
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

static HWIOModuleType HWIOModules_CPR3[] =
{
  { "CPR3",                                        0x00000000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MX_CPR3[] =
{
  { "MX_CPR3",                                     0x00000000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MSS_MPU_MSS_MPU_WRAPPER[] =
{
  { "MSS_MPU_MSS_MPU_MSS_MPU_MPU32Q2N7S1V0_16_CL36M35L12_AXI", 0x00000000, 0x00001800 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MSS_Q6_MPU_MPU32Q2N7S1V0_16_CL36M35L12_AXI[] =
{
  { "MSS_Q6_MPU_MPU32Q2N7S1V0_16_CL36M35L12_AXI",  0x00000000, 0x00001800 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_RPM_MSG_RAM[] =
{
  { "RPM_MSG_RAM",                                 0x00000000, 0x00008000 },
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

static HWIOModuleType HWIOModules_GLM_WRAPPER[] =
{
  { "GLM_PRIVATE",                                 0x00001000, 0x00001000 },
  { "GLM_PRIVATE_LLM_PRIVATE",                     0x00001000, 0x00000800 },
  { "GLM_PUBLIC",                                  0x00000000, 0x00001000 },
  { "GLM_PUBLIC_LLM_PUBLIC",                       0x00000000, 0x00000800 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_AHB2PHY_EAST[] =
{
  { "A_CM_QREFS_VBG_INT_VREF_SW",                  0x00000000, 0x00000080 },
  { "AHB2PHY_EAST_AHB2PHY_SWMAN",                  0x00002000, 0x00000400 },
  { "AHB2PHY_EAST_AHB2PHY_BROADCAST_SWMAN",        0x00003000, 0x00000400 },
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

static HWIOModuleType HWIOModules_DCC_WRAPPER[] =
{
  { "DCC",                                         0x00003000, 0x00001000 },
  { "DCC_SEC",                                     0x00002000, 0x00001000 },
  { "DCC_XPU",                                     0x00000000, 0x00001080 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_DCC_RAM_START_ADDRESS[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_QM[] =
{
  { "QM",                                          0x00000000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_QM_MPU_CFG_QM_MPU_WRAPPER[] =
{
  { "QM_MPU_CFG_QM_MPU_CFG_QM_MPU_CFG_MPU32Q2N7S1V0_4_CL36M23L12_AHB", 0x00000000, 0x00001200 },
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

static HWIOModuleType HWIOModules_A2_NOC_AGGRE2_NOC_WRAPPER[] =
{
  { "A2_NOC_MPU32Q2N7S1V0_16_CL36M35L12_AXI",      0x00060000, 0x00001800 },
  { "A2_NOC_AGGRE2_NOC",                           0x00040000, 0x00010080 },
  { "A2_NOC_QSMMUV2_WRAP_ANOC2_STARLORD",          0x00000000, 0x00040000 },
  { "A2_NOC_SMMU",                                 0x00000000, 0x00040000 },
  { "A2_NOC_SMMU_GLOBAL0",                         0x00000000, 0x00001000 },
  { "A2_NOC_SMMU_GLOBAL1",                         0x00001000, 0x00001000 },
  { "A2_NOC_SMMU_IMPL_DEF0",                       0x00002000, 0x00001000 },
  { "A2_NOC_SMMU_PERF_MON",                        0x00003000, 0x00001000 },
  { "A2_NOC_SMMU_SSD",                             0x00004000, 0x00001000 },
  { "A2_NOC_SMMU_IMPL_DEF1",                       0x00006000, 0x00001000 },
  { "A2_NOC_A_CB0_CB0_SMMU_CONTEXT_BANK",          0x00020000, 0x00001000 },
  { "A2_NOC_A_CB1_CB1_SMMU_CONTEXT_BANK",          0x00021000, 0x00001000 },
  { "A2_NOC_A_CB2_CB2_SMMU_CONTEXT_BANK",          0x00022000, 0x00001000 },
  { "A2_NOC_A_CB3_CB3_SMMU_CONTEXT_BANK",          0x00023000, 0x00001000 },
  { "A2_NOC_A_CB4_CB4_SMMU_CONTEXT_BANK",          0x00024000, 0x00001000 },
  { "A2_NOC_A_CB5_CB5_SMMU_CONTEXT_BANK",          0x00025000, 0x00001000 },
  { "A2_NOC_A_CB6_CB6_SMMU_CONTEXT_BANK",          0x00026000, 0x00001000 },
  { "A2_NOC_A_CB7_CB7_SMMU_CONTEXT_BANK",          0x00027000, 0x00001000 },
  { "A2_NOC_A_CB8_CB8_SMMU_CONTEXT_BANK",          0x00028000, 0x00001000 },
  { "A2_NOC_A_CB9_CB9_SMMU_CONTEXT_BANK",          0x00029000, 0x00001000 },
  { "A2_NOC_A_CB10_CB10_SMMU_CONTEXT_BANK",        0x0002a000, 0x00001000 },
  { "A2_NOC_A_CB11_CB11_SMMU_CONTEXT_BANK",        0x0002b000, 0x00001000 },
  { "A2_NOC_A_CB12_CB12_SMMU_CONTEXT_BANK",        0x0002c000, 0x00001000 },
  { "A2_NOC_A_CB13_CB13_SMMU_CONTEXT_BANK",        0x0002d000, 0x00001000 },
  { "A2_NOC_A_CB14_CB14_SMMU_CONTEXT_BANK",        0x0002e000, 0x00001000 },
  { "A2_NOC_A_CB15_CB15_SMMU_CONTEXT_BANK",        0x0002f000, 0x00001000 },
  { "A2_NOC_A_CB16_CB16_SMMU_CONTEXT_BANK",        0x00030000, 0x00001000 },
  { "A2_NOC_A_CB17_CB17_SMMU_CONTEXT_BANK",        0x00031000, 0x00001000 },
  { "A2_NOC_A_CB18_CB18_SMMU_CONTEXT_BANK",        0x00032000, 0x00001000 },
  { "A2_NOC_A_CB19_CB19_SMMU_CONTEXT_BANK",        0x00033000, 0x00001000 },
  { "A2_NOC_A_CB20_CB20_SMMU_CONTEXT_BANK",        0x00034000, 0x00001000 },
  { "A2_NOC_A_CB21_CB21_SMMU_CONTEXT_BANK",        0x00035000, 0x00001000 },
  { "A2_NOC_A_CB22_CB22_SMMU_CONTEXT_BANK",        0x00036000, 0x00001000 },
  { "A2_NOC_A_CB23_CB23_SMMU_CONTEXT_BANK",        0x00037000, 0x00001000 },
  { "A2_NOC_A_CB24_CB24_SMMU_CONTEXT_BANK",        0x00038000, 0x00001000 },
  { "A2_NOC_A_CB25_CB25_SMMU_CONTEXT_BANK",        0x00039000, 0x00001000 },
  { "A2_NOC_A_CB26_CB26_SMMU_CONTEXT_BANK",        0x0003a000, 0x00001000 },
  { "A2_NOC_A_CB27_CB27_SMMU_CONTEXT_BANK",        0x0003b000, 0x00001000 },
  { "A2_NOC_A_CB28_CB28_SMMU_CONTEXT_BANK",        0x0003c000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_THROTTLE_1THROTTLE_WRAPPER_2[] =
{
  { "THROTTLE_1THROTTLE_0_THROTTLE_0_THROTTLE",    0x00000000, 0x00000100 },
  { "THROTTLE_1THROTTLE_1_THROTTLE_1_THROTTLE",    0x00000200, 0x00000100 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MMSS_NOC[] =
{
  { "MMSS_NOC",                                    0x00000000, 0x0000f080 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_UFS_UFS_REGS[] =
{
  { "UFS",                                         0x00004000, 0x00003000 },
  { "UFS_MPHY_UFS",                                0x00007000, 0x00000e00 },
  { "UFS_QSERDES_COM_QSERDES_COM_UFS_QSRV_COM",    0x00007000, 0x000001c4 },
  { "UFS_QSERDES_TX_QSERDES_TX_UFS_QMP_TX",        0x00007400, 0x0000012c },
  { "UFS_QSERDES_RX_QSERDES_RX_UFS_QMP_RX",        0x00007600, 0x00000200 },
  { "UFS_UFS_PHY_UFS_PHY_UFS_PCS",                 0x00007c00, 0x000001b8 },
  { "UFS_ICE",                                     0x00010000, 0x00008000 },
  { "UFS_ICE_REGS",                                0x00010000, 0x00002000 },
  { "UFS_ICE_LUT_KEYS",                            0x00012000, 0x00002000 },
  { "UFS_ICE_XPU3",                                0x00014000, 0x00001200 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_CRYPTO0_CRYPTO_TOP[] =
{
  { "CRYPTO0_CRYPTO",                              0x0003a000, 0x00006000 },
  { "CRYPTO0_CRYPTO_BAM",                          0x00004000, 0x00024000 },
  { "CRYPTO0_CRYPTO_BAM_XPU3_BAM",                 0x00001000, 0x00003000 },
  { "CRYPTO0_CRYPTO_BAM_VMIDMT_BAM",               0x00000000, 0x00001000 },
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

static HWIOModuleType HWIOModules_MODEM_TOP[] =
{
  { "MPSS_TOP",                                    0x00180000, 0x00080000 },
  { "MPSS_RMB",                                    0x00180000, 0x00010000 },
  { "MSS_UIM0_UART_DM",                            0x00190000, 0x00000200 },
  { "MSS_UIM1_UART_DM",                            0x00194000, 0x00000200 },
  { "MSS_UIM2_UART_DM",                            0x00198000, 0x00000200 },
  { "MSS_UIM3_UART_DM",                            0x0019c000, 0x00000200 },
  { "MSS_CXM_UART_DM",                             0x001a0000, 0x00000204 },
  { "MPSS_PERPH",                                  0x001a8000, 0x00008000 },
  { "MSS_CONF_BUS_TIMEOUT",                        0x001b0000, 0x00001000 },
  { "MSS_CPR3",                                    0x001b1000, 0x00001000 },
  { "MSS_MGPI",                                    0x001b2000, 0x00000128 },
  { "MSS_ENCRYPT_ACC",                             0x001b3000, 0x00000080 },
  { "MSS_STMR",                                    0x001b4000, 0x000000fd },
  { "MSS_RFC",                                     0x001b8000, 0x00008000 },
  { "MSS_PDMEM",                                   0x001b8000, 0x00006000 },
  { "MSS_RFC_SWI",                                 0x001bfc00, 0x00000400 },
  { "MSS_CRYPTO_TOP",                              0x001c0000, 0x00040000 },
  { "MSS_CRYPTO",                                  0x001fa000, 0x00006000 },
  { "MSS_CRYPTO_BAM",                              0x001c4000, 0x00024000 },
  { "MSS_NAV",                                     0x00200000, 0x000f888d },
  { "MSS_NAV_WTR_BASE",                            0x00200000, 0x00001900 },
  { "MSS_NAV_TOP_BASE",                            0x00201900, 0x00000700 },
  { "MSS_NAV_BB_BASE",                             0x00202000, 0x000c6000 },
  { "MSS_QDSP6V60SS_PUB",                          0x00080000, 0x00004040 },
  { "MSS_QDSP6V60SS_PRIVATE",                      0x00100000, 0x00080000 },
  { "MSS_QDSP6V60SS_CSR",                          0x00100000, 0x00008028 },
  { "MSS_QDSP6V60SS_L2VIC",                        0x00110000, 0x00001000 },
  { "MSS_QDSP6SS_QDSP6SS_QTMR_AC",                 0x00120000, 0x00001000 },
  { "MSS_QDSP6SS_QTMR_F0_0",                       0x00121000, 0x00001000 },
  { "MSS_QDSP6SS_QTMR_F1_1",                       0x00122000, 0x00001000 },
  { "MSS_QDSP6SS_QTMR_F2_2",                       0x00123000, 0x00001000 },
  { "MSS_QDSP6SS_QDSP6SS_SAW4_QDSP6SS_PDW16_WRAPPER", 0x00130000, 0x00001000 },
  { "MSS_QDSP6SS_SAW4_SPM",                        0x00130000, 0x00000800 },
  { "MSS_QDSP6SS_SAW4_AVS",                        0x00130800, 0x00000400 },
  { "MSS_QDSP6SS_SAW4_STS",                        0x00130c00, 0x00000400 },
  { "MSS_QDSP6SS_QDSP6SS_CPR3",                    0x00140000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_A5X[] =
{
  { "RBBM_BLOCK0",                                 0x00000000, 0x00002000 },
  { "RBBM_BLOCK6",                                 0x0003c000, 0x00000005 },
  { "RBBM_BLOCK7",                                 0x0003d000, 0x00003000 },
  { "CP_BLOCK0",                                   0x00002000, 0x00000f00 },
  { "CP_BLOCK7",                                   0x0003c040, 0x0000000d },
  { "VSC_BLOCK0",                                  0x00002f00, 0x00000300 },
  { "UCHE_BLOCK0",                                 0x00003a00, 0x00000100 },
  { "GRAS_BLOCK0",                                 0x00003200, 0x00000100 },
  { "GRAS_BLOCK1",                                 0x00008600, 0x00000100 },
  { "GRAS_BLOCK2",                                 0x00009600, 0x00000100 },
  { "GRAS_BLOCK3",                                 0x00038000, 0x00000500 },
  { "GRAS_BLOCK4",                                 0x0003a000, 0x00000500 },
  { "RB_BLOCK0",                                   0x00003300, 0x00000100 },
  { "RB_BLOCK1",                                   0x00008400, 0x00000200 },
  { "RB_BLOCK2",                                   0x00009400, 0x00000200 },
  { "RB_BLOCK3",                                   0x00038500, 0x00000500 },
  { "RB_BLOCK4",                                   0x0003a500, 0x00000500 },
  { "VPC_BLOCK0",                                  0x00003980, 0x00000080 },
  { "VPC_BLOCK3",                                  0x00038a00, 0x00000400 },
  { "VPC_BLOCK4",                                  0x0003aa00, 0x00000400 },
  { "VPC_BLOCK5",                                  0x00034000, 0x00000800 },
  { "PC_BLOCK0",                                   0x00003400, 0x00000100 },
  { "PC_BLOCK1",                                   0x00008300, 0x00000100 },
  { "PC_BLOCK2",                                   0x00009300, 0x00000100 },
  { "PC_BLOCK3",                                   0x00038e00, 0x00000200 },
  { "PC_BLOCK4",                                   0x0003ae00, 0x00000200 },
  { "VFD_BLOCK0",                                  0x00003900, 0x00000080 },
  { "VFD_BLOCK3",                                  0x00039000, 0x00000600 },
  { "VFD_BLOCK4",                                  0x0003b000, 0x00000600 },
  { "VFD_BLOCK5",                                  0x00034800, 0x00000100 },
  { "SP_BLOCK0",                                   0x00003b00, 0x00000100 },
  { "SP_BLOCK1",                                   0x00008100, 0x00000100 },
  { "SP_BLOCK2",                                   0x00009100, 0x00000100 },
  { "SP_BLOCK3",                                   0x00039600, 0x00000600 },
  { "SP_BLOCK4",                                   0x0003b600, 0x00000600 },
  { "TPL1_BLOCK0",                                 0x00003c00, 0x00000100 },
  { "TPL1_BLOCK1",                                 0x00008000, 0x00000100 },
  { "TPL1_BLOCK2",                                 0x00009000, 0x00000100 },
  { "TPL1_BLOCK3",                                 0x00039c00, 0x00000200 },
  { "TPL1_BLOCK4",                                 0x0003bc00, 0x00000200 },
  { "HLSQ_BLOCK0",                                 0x00003800, 0x00000100 },
  { "HLSQ_BLOCK1",                                 0x00008200, 0x00000100 },
  { "HLSQ_BLOCK2",                                 0x00009200, 0x00000100 },
  { "HLSQ_BLOCK3",                                 0x00039e00, 0x00000200 },
  { "HLSQ_BLOCK4",                                 0x0003be00, 0x00000200 },
  { "HLSQ_BLOCK5",                                 0x00020000, 0x00002000 },
  { "HLSQ_BLOCK6",                                 0x00028000, 0x00002000 },
  { "HLSQ_BLOCK7",                                 0x0002f000, 0x00001000 },
  { "CX_BLOCK0",                                   0x00060000, 0x0000000d },
  { "VBIF",                                        0x0000c000, 0x00003000 },
  { "VBIF_GPU",                                    0x0000c000, 0x00003000 },
  { "SMMU",                                        0x00040000, 0x00010000 },
  { "SMMU_GLOBAL0",                                0x00040000, 0x00001000 },
  { "SMMU_GLOBAL1",                                0x00041000, 0x00001000 },
  { "SMMU_IMPL_DEF0",                              0x00042000, 0x00001000 },
  { "SMMU_PERF_MON",                               0x00043000, 0x00001000 },
  { "SMMU_SSD",                                    0x00044000, 0x00001000 },
  { "SMMU_IMPL_DEF1",                              0x00046000, 0x00001000 },
  { "CB0_SMMU_CONTEXT_BANK",                       0x00048000, 0x00001000 },
  { "CB1_SMMU_CONTEXT_BANK",                       0x00049000, 0x00001000 },
  { "CB2_SMMU_CONTEXT_BANK",                       0x0004a000, 0x00001000 },
  { "CB3_SMMU_CONTEXT_BANK",                       0x0004b000, 0x00001000 },
  { "CB4_SMMU_CONTEXT_BANK",                       0x0004c000, 0x00001000 },
  { "CB5_SMMU_CONTEXT_BANK",                       0x0004d000, 0x00001000 },
  { "CB6_SMMU_CONTEXT_BANK",                       0x0004e000, 0x00001000 },
  { "CB7_SMMU_CONTEXT_BANK",                       0x0004f000, 0x00001000 },
  { "GPUCC",                                       0x00065000, 0x00010000 },
  { "GPU_CPR",                                     0x00061000, 0x00004000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD[] =
{
  { "LPASS_Q6_SMMU",                               0x00000000, 0x00040000 },
  { "LPASS_Q6_SMMU_SMMU_GLOBAL0",                  0x00000000, 0x00001000 },
  { "LPASS_Q6_SMMU_SMMU_GLOBAL1",                  0x00001000, 0x00001000 },
  { "LPASS_Q6_SMMU_SMMU_IMPL_DEF0",                0x00002000, 0x00001000 },
  { "LPASS_Q6_SMMU_SMMU_PERF_MON",                 0x00003000, 0x00001000 },
  { "LPASS_Q6_SMMU_SMMU_SSD",                      0x00004000, 0x00001000 },
  { "LPASS_Q6_SMMU_SMMU_IMPL_DEF1",                0x00006000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB0_CB0_SMMU_CONTEXT_BANK",   0x00020000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB1_CB1_SMMU_CONTEXT_BANK",   0x00021000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB2_CB2_SMMU_CONTEXT_BANK",   0x00022000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB3_CB3_SMMU_CONTEXT_BANK",   0x00023000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB4_CB4_SMMU_CONTEXT_BANK",   0x00024000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB5_CB5_SMMU_CONTEXT_BANK",   0x00025000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB6_CB6_SMMU_CONTEXT_BANK",   0x00026000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB7_CB7_SMMU_CONTEXT_BANK",   0x00027000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB8_CB8_SMMU_CONTEXT_BANK",   0x00028000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB9_CB9_SMMU_CONTEXT_BANK",   0x00029000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB10_CB10_SMMU_CONTEXT_BANK", 0x0002a000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB11_CB11_SMMU_CONTEXT_BANK", 0x0002b000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB12_CB12_SMMU_CONTEXT_BANK", 0x0002c000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB13_CB13_SMMU_CONTEXT_BANK", 0x0002d000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB14_CB14_SMMU_CONTEXT_BANK", 0x0002e000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB15_CB15_SMMU_CONTEXT_BANK", 0x0002f000, 0x00001000 },
  { "LPASS_Q6_SMMU_A_CB16_CB16_SMMU_CONTEXT_BANK", 0x00030000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_TURING_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD[] =
{
  { "TURING_Q6_SMMU",                              0x00000000, 0x00040000 },
  { "TURING_Q6_SMMU_SMMU_GLOBAL0",                 0x00000000, 0x00001000 },
  { "TURING_Q6_SMMU_SMMU_GLOBAL1",                 0x00001000, 0x00001000 },
  { "TURING_Q6_SMMU_SMMU_IMPL_DEF0",               0x00002000, 0x00001000 },
  { "TURING_Q6_SMMU_SMMU_PERF_MON",                0x00003000, 0x00001000 },
  { "TURING_Q6_SMMU_SMMU_SSD",                     0x00004000, 0x00001000 },
  { "TURING_Q6_SMMU_SMMU_IMPL_DEF1",               0x00006000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB0_CB0_SMMU_CONTEXT_BANK",  0x00020000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB1_CB1_SMMU_CONTEXT_BANK",  0x00021000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB2_CB2_SMMU_CONTEXT_BANK",  0x00022000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB3_CB3_SMMU_CONTEXT_BANK",  0x00023000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB4_CB4_SMMU_CONTEXT_BANK",  0x00024000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB5_CB5_SMMU_CONTEXT_BANK",  0x00025000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB6_CB6_SMMU_CONTEXT_BANK",  0x00026000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB7_CB7_SMMU_CONTEXT_BANK",  0x00027000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB8_CB8_SMMU_CONTEXT_BANK",  0x00028000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB9_CB9_SMMU_CONTEXT_BANK",  0x00029000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB10_CB10_SMMU_CONTEXT_BANK", 0x0002a000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB11_CB11_SMMU_CONTEXT_BANK", 0x0002b000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB12_CB12_SMMU_CONTEXT_BANK", 0x0002c000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB13_CB13_SMMU_CONTEXT_BANK", 0x0002d000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB14_CB14_SMMU_CONTEXT_BANK", 0x0002e000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB15_CB15_SMMU_CONTEXT_BANK", 0x0002f000, 0x00001000 },
  { "TURING_Q6_SMMU_A_CB16_CB16_SMMU_CONTEXT_BANK", 0x00030000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS_LPASS_CC_TOP[] =
{
  { "LPASS_LPASS_CC_TOP",                          0x00000000, 0x00013000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS_CFG_MPU_MPU32Q2N7S1V0_10_CL36M22L12_AHB[] =
{
  { "LPASS_CFG_MPU_MPU32Q2N7S1V0_10_CL36M22L12_AHB", 0x00000000, 0x00001500 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS_LPASS_QOS_GASKET[] =
{
  { "LPASS_QOS_GASKET_QOS_GASKET_THROTTLE",        0x00000100, 0x00000100 },
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

static HWIOModuleType HWIOModules_QSPI[] =
{
  { "QSPI",                                        0x00000000, 0x00001000 },
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

static HWIOModuleType HWIOModules_PERIPH_SS_BLSP2_BLSP_XPU3[] =
{
  { "PERIPH_SS_BLSP2_BLSP_BAM",                    0x00004000, 0x0001f000 },
  { "PERIPH_SS_BLSP2_BLSP_BAM_XPU3",               0x00001000, 0x00003000 },
  { "PERIPH_SS_BLSP2_BLSP_BAM_VMIDMT",             0x00000000, 0x00001000 },
  { "PERIPH_SS_BLSP2_BLSP_UART0_UART0_DM",         0x0002f000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_UART1_UART1_DM",         0x00030000, 0x00000200 },
  { "PERIPH_SS_BLSP2_BLSP_QUP0",                   0x00035000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP1",                   0x00036000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP2",                   0x00037000, 0x00000600 },
  { "PERIPH_SS_BLSP2_BLSP_QUP3",                   0x00038000, 0x00000600 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_USB2USB20S[] =
{
  { "USB2DWC_USB3",                                0x00000000, 0x0000cd00 },
  { "USB2USB30_QSCRATCH",                          0x000f8800, 0x00000400 },
  { "USB2USB30_DBM_REGFILE",                       0x000f8000, 0x00000400 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MMSS[] =
{
  { "MMSS_MISC",                                   0x00028000, 0x00004000 },
  { "MMSS_CSI_PHY_0",                              0x00024000, 0x00001000 },
  { "MMSS_CSI_PHY_0_CSIPHY_LN0_CSIPHY_LN0_CSI_2PHASE_DATALN", 0x00024000, 0x000000dc },
  { "MMSS_CSI_PHY_0_CSIPHY_LN1_CSIPHY_LN1_CSI_3PHASE_DATALN", 0x00024100, 0x00000100 },
  { "MMSS_CSI_PHY_0_CSIPHY_LN2_CSIPHY_LN2_CSI_2PHASE_DATALN", 0x00024200, 0x000000dc },
  { "MMSS_CSI_PHY_0_CSIPHY_LN3_CSIPHY_LN3_CSI_3PHASE_DATALN", 0x00024300, 0x00000100 },
  { "MMSS_CSI_PHY_0_CSIPHY_LN4_CSIPHY_LN4_CSI_2PHASE_DATALN", 0x00024400, 0x000000dc },
  { "MMSS_CSI_PHY_0_CSIPHY_LN5_CSIPHY_LN5_CSI_3PHASE_DATALN", 0x00024500, 0x00000100 },
  { "MMSS_CSI_PHY_0_CSIPHY_LN6_CSIPHY_LN6_CSI_2PHASE_DATALN", 0x00024600, 0x000000dc },
  { "MMSS_CSI_PHY_0_CSIPHY_LNCK_CSIPHY_LNCK_CSI_2PHASE_DATALN", 0x00024700, 0x000000dc },
  { "MMSS_CSI_PHY_0_CSIPHY_CMN_CSIPHY_CMN_CSI_3PHASE_COMMON", 0x00024800, 0x00000100 },
  { "MMSS_CSI_PHY_1",                              0x00025000, 0x00001000 },
  { "MMSS_CSI_PHY_1_CSIPHY_LN0_CSIPHY_LN0_CSI_2PHASE_DATALN", 0x00025000, 0x000000dc },
  { "MMSS_CSI_PHY_1_CSIPHY_LN1_CSIPHY_LN1_CSI_3PHASE_DATALN", 0x00025100, 0x00000100 },
  { "MMSS_CSI_PHY_1_CSIPHY_LN2_CSIPHY_LN2_CSI_2PHASE_DATALN", 0x00025200, 0x000000dc },
  { "MMSS_CSI_PHY_1_CSIPHY_LN3_CSIPHY_LN3_CSI_3PHASE_DATALN", 0x00025300, 0x00000100 },
  { "MMSS_CSI_PHY_1_CSIPHY_LN4_CSIPHY_LN4_CSI_2PHASE_DATALN", 0x00025400, 0x000000dc },
  { "MMSS_CSI_PHY_1_CSIPHY_LN5_CSIPHY_LN5_CSI_3PHASE_DATALN", 0x00025500, 0x00000100 },
  { "MMSS_CSI_PHY_1_CSIPHY_LN6_CSIPHY_LN6_CSI_2PHASE_DATALN", 0x00025600, 0x000000dc },
  { "MMSS_CSI_PHY_1_CSIPHY_LNCK_CSIPHY_LNCK_CSI_2PHASE_DATALN", 0x00025700, 0x000000dc },
  { "MMSS_CSI_PHY_1_CSIPHY_CMN_CSIPHY_CMN_CSI_3PHASE_COMMON", 0x00025800, 0x00000100 },
  { "MMSS_CSI_PHY_2",                              0x00026000, 0x00001000 },
  { "MMSS_CSI_PHY_2_CSIPHY_LN0_CSIPHY_LN0_CSI_2PHASE_DATALN", 0x00026000, 0x000000dc },
  { "MMSS_CSI_PHY_2_CSIPHY_LN1_CSIPHY_LN1_CSI_3PHASE_DATALN", 0x00026100, 0x00000100 },
  { "MMSS_CSI_PHY_2_CSIPHY_LN2_CSIPHY_LN2_CSI_2PHASE_DATALN", 0x00026200, 0x000000dc },
  { "MMSS_CSI_PHY_2_CSIPHY_LN3_CSIPHY_LN3_CSI_3PHASE_DATALN", 0x00026300, 0x00000100 },
  { "MMSS_CSI_PHY_2_CSIPHY_LN4_CSIPHY_LN4_CSI_2PHASE_DATALN", 0x00026400, 0x000000dc },
  { "MMSS_CSI_PHY_2_CSIPHY_LN5_CSIPHY_LN5_CSI_3PHASE_DATALN", 0x00026500, 0x00000100 },
  { "MMSS_CSI_PHY_2_CSIPHY_LN6_CSIPHY_LN6_CSI_2PHASE_DATALN", 0x00026600, 0x000000dc },
  { "MMSS_CSI_PHY_2_CSIPHY_LNCK_CSIPHY_LNCK_CSI_2PHASE_DATALN", 0x00026700, 0x000000dc },
  { "MMSS_CSI_PHY_2_CSIPHY_CMN_CSIPHY_CMN_CSI_3PHASE_COMMON", 0x00026800, 0x00000100 },
  { "MMSS_CC",                                     0x000c0000, 0x00040000 },
  { "MMSS_MDSS",                                   0x00100000, 0x00100000 },
  { "MMSS_MDSS_HW",                                0x00100000, 0x00001000 },
  { "MMSS_MDP",                                    0x00101000, 0x0008f000 },
  { "MMSS_MDP_SSPP_TOP0",                          0x00101000, 0x00000030 },
  { "MMSS_MDP_SMP_TOP0",                           0x00101030, 0x000001b8 },
  { "MMSS_MDP_SSPP_TOP1",                          0x001011e8, 0x00000114 },
  { "MMSS_MDP_SMP_TOP1",                           0x001012fc, 0x00000004 },
  { "MMSS_MDP_DSPP_TOP0",                          0x00101300, 0x00000080 },
  { "MMSS_MDP_PERIPH_TOP0",                        0x00101380, 0x00000028 },
  { "MMSS_MDP_SSPP_TOP2",                          0x001013a8, 0x00000048 },
  { "MMSS_MDP_PERIPH_TOP1",                        0x001013f0, 0x00000c10 },
  { "MMSS_MDP_CTL_0",                              0x00102000, 0x00000100 },
  { "MMSS_MDP_CTL_1",                              0x00102200, 0x00000100 },
  { "MMSS_MDP_CTL_2",                              0x00102400, 0x00000100 },
  { "MMSS_MDP_CTL_3",                              0x00102600, 0x00000100 },
  { "MMSS_MDP_CTL_4",                              0x00102800, 0x00000100 },
  { "MMSS_MDP_SSPP_IGC_LUT",                       0x00103000, 0x00000101 },
  { "MMSS_MDP_VP_0_VIG_0_SSPP",                    0x00105000, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_0",                         0x00105200, 0x00001d80 },
  { "MMSS_MDP_VP_0_VIG_0_QSEED3",                  0x00105a00, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_0_QSEED3_COEF_LUT",         0x00105b00, 0x00000700 },
  { "MMSS_MDP_VP_0_VIG_0_PA_HIST",                 0x00106200, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_0_PA_MEMCOL",               0x00106280, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_0_PA_SZONE",                0x00106300, 0x00000020 },
  { "MMSS_MDP_VP_0_VIG_0_LUTV_RAM",                0x00106400, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_0_HIST_RAM",                0x00106600, 0x00000400 },
  { "MMSS_MDP_VP_0_VIG_0_CSC_1",                   0x00106a00, 0x00000100 },
  { "MMSS_MDP_VP_0_VIG_0_PCC",                     0x00106b00, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_1_SSPP",                    0x00107000, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_1",                         0x00107200, 0x00001d80 },
  { "MMSS_MDP_VP_0_VIG_1_QSEED3",                  0x00107a00, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_1_QSEED3_COEF_LUT",         0x00107b00, 0x00000700 },
  { "MMSS_MDP_VP_0_VIG_1_PA_HIST",                 0x00108200, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_1_PA_MEMCOL",               0x00108280, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_1_PA_SZONE",                0x00108300, 0x00000020 },
  { "MMSS_MDP_VP_0_VIG_1_LUTV_RAM",                0x00108400, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_1_HIST_RAM",                0x00108600, 0x00000400 },
  { "MMSS_MDP_VP_0_VIG_1_CSC_1",                   0x00108a00, 0x00000100 },
  { "MMSS_MDP_VP_0_VIG_1_PCC",                     0x00108b00, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_2_SSPP",                    0x00109000, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_2",                         0x00109200, 0x00001d80 },
  { "MMSS_MDP_VP_0_VIG_2_QSEED3",                  0x00109a00, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_2_QSEED3_COEF_LUT",         0x00109b00, 0x00000700 },
  { "MMSS_MDP_VP_0_VIG_2_PA_HIST",                 0x0010a200, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_2_PA_MEMCOL",               0x0010a280, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_2_PA_SZONE",                0x0010a300, 0x00000020 },
  { "MMSS_MDP_VP_0_VIG_2_LUTV_RAM",                0x0010a400, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_2_HIST_RAM",                0x0010a600, 0x00000400 },
  { "MMSS_MDP_VP_0_VIG_2_CSC_1",                   0x0010aa00, 0x00000100 },
  { "MMSS_MDP_VP_0_VIG_2_PCC",                     0x0010ab00, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_3_SSPP",                    0x0010b000, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_3",                         0x0010b200, 0x00001d80 },
  { "MMSS_MDP_VP_0_VIG_3_QSEED3",                  0x0010ba00, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_3_QSEED3_COEF_LUT",         0x0010bb00, 0x00000700 },
  { "MMSS_MDP_VP_0_VIG_3_PA_HIST",                 0x0010c200, 0x00000800 },
  { "MMSS_MDP_VP_0_VIG_3_PA_MEMCOL",               0x0010c280, 0x00000080 },
  { "MMSS_MDP_VP_0_VIG_3_PA_SZONE",                0x0010c300, 0x00000020 },
  { "MMSS_MDP_VP_0_VIG_3_LUTV_RAM",                0x0010c400, 0x00000200 },
  { "MMSS_MDP_VP_0_VIG_3_HIST_RAM",                0x0010c600, 0x00000400 },
  { "MMSS_MDP_VP_0_VIG_3_CSC_1",                   0x0010ca00, 0x00000100 },
  { "MMSS_MDP_VP_0_VIG_3_PCC",                     0x0010cb00, 0x00000080 },
  { "MMSS_MDP_VP_0_RGB_0_SSPP",                    0x00115000, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_0",                         0x00115200, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_0_PCC",                     0x00115380, 0x00000080 },
  { "MMSS_MDP_VP_0_RGB_1_SSPP",                    0x00117000, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_1",                         0x00117200, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_1_PCC",                     0x00117380, 0x00000080 },
  { "MMSS_MDP_VP_0_RGB_2_SSPP",                    0x00119000, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_2",                         0x00119200, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_2_PCC",                     0x00119380, 0x00000080 },
  { "MMSS_MDP_VP_0_RGB_3_SSPP",                    0x0011b000, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_3",                         0x0011b200, 0x00000200 },
  { "MMSS_MDP_VP_0_RGB_3_PCC",                     0x0011b380, 0x00000080 },
  { "MMSS_MDP_VP_0_DMA_0_SSPP",                    0x00125000, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_0",                         0x00125200, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_0_PCC",                     0x00125380, 0x00000080 },
  { "MMSS_MDP_VP_0_DMA_1_SSPP",                    0x00127000, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_1",                         0x00127200, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_1_PCC",                     0x00127380, 0x00000080 },
  { "MMSS_MDP_VP_0_DMA_2_SSPP",                    0x00129000, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_2",                         0x00129200, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_2_PCC",                     0x00129380, 0x00000080 },
  { "MMSS_MDP_VP_0_DMA_3_SSPP",                    0x0012b000, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_3",                         0x0012b200, 0x00000200 },
  { "MMSS_MDP_VP_0_DMA_3_PCC",                     0x0012b380, 0x00000080 },
  { "MMSS_MDP_VP_0_CURSOR_0",                      0x00135000, 0x00000400 },
  { "MMSS_MDP_VP_0_CURSOR_0_SSPP",                 0x00135000, 0x00000200 },
  { "MMSS_MDP_VP_0_CURSOR_1",                      0x00137000, 0x00000400 },
  { "MMSS_MDP_VP_0_CURSOR_1_SSPP",                 0x00137000, 0x00000200 },
  { "MMSS_MDP_VP_0_LAYER_0",                       0x00145000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_0_PGC",                   0x001453c0, 0x00000040 },
  { "MMSS_MDP_VP_0_LAYER_1",                       0x00146000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_1_PGC",                   0x001463c0, 0x00000040 },
  { "MMSS_MDP_VP_0_LAYER_2",                       0x00147000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_2_PGC",                   0x001473c0, 0x00000040 },
  { "MMSS_MDP_VP_0_LAYER_3",                       0x00148000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_3_PGC",                   0x001483c0, 0x00000040 },
  { "MMSS_MDP_VP_0_LAYER_4",                       0x00149000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_4_PGC",                   0x001493c0, 0x00000040 },
  { "MMSS_MDP_VP_0_LAYER_5",                       0x0014a000, 0x00000400 },
  { "MMSS_MDP_VP_0_LAYER_5_PGC",                   0x0014a3c0, 0x00000040 },
  { "MMSS_MDP_VP_0_DSPP_0",                        0x00155000, 0x00001800 },
  { "MMSS_MDP_VP_0_DSPP_0_PA_HIST",                0x00155800, 0x00000800 },
  { "MMSS_MDP_VP_0_DSPP_0_PA_MEMCOL",              0x00155880, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_0_PA_SZONE",               0x00155900, 0x00000020 },
  { "MMSS_MDP_VP_0_DSPP_0_LUTV_RAM",               0x00155a00, 0x00000200 },
  { "MMSS_MDP_VP_0_DSPP_0_HIST_RAM",               0x00155c00, 0x00000400 },
  { "MMSS_MDP_VP_0_DSPP_0_GAMUT",                  0x00156600, 0x00000100 },
  { "MMSS_MDP_VP_0_DSPP_0_PCC",                    0x00156700, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_0_PGC",                    0x001567c0, 0x00000040 },
  { "MMSS_MDP_VP_0_DSPP_1",                        0x00157000, 0x00001800 },
  { "MMSS_MDP_VP_0_DSPP_1_PA_HIST",                0x00157800, 0x00000800 },
  { "MMSS_MDP_VP_0_DSPP_1_PA_MEMCOL",              0x00157880, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_1_PA_SZONE",               0x00157900, 0x00000020 },
  { "MMSS_MDP_VP_0_DSPP_1_LUTV_RAM",               0x00157a00, 0x00000200 },
  { "MMSS_MDP_VP_0_DSPP_1_HIST_RAM",               0x00157c00, 0x00000400 },
  { "MMSS_MDP_VP_0_DSPP_1_GAMUT",                  0x00158600, 0x00000100 },
  { "MMSS_MDP_VP_0_DSPP_1_PCC",                    0x00158700, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_1_PGC",                    0x001587c0, 0x00000040 },
  { "MMSS_MDP_VP_0_DSPP_2",                        0x00159000, 0x00001800 },
  { "MMSS_MDP_VP_0_DSPP_2_PA_HIST",                0x00159800, 0x00000800 },
  { "MMSS_MDP_VP_0_DSPP_2_PA_MEMCOL",              0x00159880, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_2_PA_SZONE",               0x00159900, 0x00000020 },
  { "MMSS_MDP_VP_0_DSPP_2_LUTV_RAM",               0x00159a00, 0x00000200 },
  { "MMSS_MDP_VP_0_DSPP_2_HIST_RAM",               0x00159c00, 0x00000400 },
  { "MMSS_MDP_VP_0_DSPP_2_GAMUT",                  0x0015a600, 0x00000100 },
  { "MMSS_MDP_VP_0_DSPP_2_PCC",                    0x0015a700, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_2_PGC",                    0x0015a7c0, 0x00000040 },
  { "MMSS_MDP_VP_0_DSPP_3",                        0x0015b000, 0x00001800 },
  { "MMSS_MDP_VP_0_DSPP_3_PA_HIST",                0x0015b800, 0x00000800 },
  { "MMSS_MDP_VP_0_DSPP_3_PA_MEMCOL",              0x0015b880, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_3_PA_SZONE",               0x0015b900, 0x00000020 },
  { "MMSS_MDP_VP_0_DSPP_3_LUTV_RAM",               0x0015ba00, 0x00000200 },
  { "MMSS_MDP_VP_0_DSPP_3_HIST_RAM",               0x0015bc00, 0x00000400 },
  { "MMSS_MDP_VP_0_DSPP_3_GAMUT",                  0x0015c600, 0x00000100 },
  { "MMSS_MDP_VP_0_DSPP_3_PCC",                    0x0015c700, 0x00000080 },
  { "MMSS_MDP_VP_0_DSPP_3_PGC",                    0x0015c7c0, 0x00000040 },
  { "MMSS_MDP_DEST_SCALER_0",                      0x00161000, 0x00003000 },
  { "MMSS_MDP_DEST_SCALER_0_DEST_SCL0",            0x00161800, 0x00000800 },
  { "MMSS_MDP_DEST_SCALER_0_DEST_SCL0_COEF_LUT",   0x00161900, 0x00000700 },
  { "MMSS_MDP_DEST_SCALER_0_DEST_SCL1",            0x00162000, 0x00000800 },
  { "MMSS_MDP_DEST_SCALER_0_DEST_SCL1_COEF_LUT",   0x00162100, 0x00000700 },
  { "MMSS_MDP_WB_0",                               0x00165000, 0x00000400 },
  { "MMSS_MDP_WB_1",                               0x00165800, 0x00000400 },
  { "MMSS_MDP_WB_2",                               0x00166000, 0x00000400 },
  { "MMSS_MDP_INTF_0",                             0x0016b000, 0x00000300 },
  { "MMSS_MDP_INTF_1",                             0x0016b800, 0x00000300 },
  { "MMSS_MDP_INTF_2",                             0x0016c000, 0x00000300 },
  { "MMSS_MDP_INTF_3",                             0x0016c800, 0x00000300 },
  { "MMSS_MDP_INTF_4",                             0x0016d000, 0x00000300 },
  { "MMSS_MDP_PP_0",                               0x00171000, 0x00000100 },
  { "MMSS_MDP_PP_1",                               0x00171800, 0x00000100 },
  { "MMSS_MDP_PP_2",                               0x00172000, 0x00000100 },
  { "MMSS_MDP_PP_3",                               0x00172800, 0x00000100 },
  { "MMSS_MDP_PP_4",                               0x00173000, 0x00000100 },
  { "MMSS_MDP_PPB_0",                              0x00174000, 0x00000100 },
  { "MMSS_MDP_PPB_0_DITHER",                       0x001740e0, 0x00000020 },
  { "MMSS_MDP_PPB_1",                              0x00174800, 0x00000100 },
  { "MMSS_MDP_PPB_1_DITHER",                       0x001748e0, 0x00000020 },
  { "MMSS_MDP_PPB_2",                              0x00175000, 0x00000100 },
  { "MMSS_MDP_PPB_2_DITHER",                       0x001750e0, 0x00000020 },
  { "MMSS_MDP_PPB_3",                              0x00175800, 0x00000100 },
  { "MMSS_MDP_PPB_3_DITHER",                       0x001758e0, 0x00000020 },
  { "MMSS_MDP_ENCR_NS_0",                          0x00177000, 0x00000010 },
  { "MMSS_MDP_ENCR_S_0",                           0x00177400, 0x00000030 },
  { "MMSS_MDP_AADC_0",                             0x00179000, 0x00000200 },
  { "MMSS_MDP_AADC_1",                             0x00179800, 0x00000200 },
  { "MMSS_MDP_AADC_2",                             0x0017a000, 0x00000200 },
  { "MMSS_MDP_CDM_0",                              0x0017a200, 0x00000240 },
  { "MMSS_MDP_CDM_0_CSC_10",                       0x0017a200, 0x00000100 },
  { "MMSS_MDP_CDM_0_CDWN2",                        0x0017a300, 0x00000100 },
  { "MMSS_MDP_CDM_0_HDMI_PACK",                    0x0017a400, 0x00000010 },
  { "MMSS_MDP_DSC_0",                              0x00181000, 0x00000200 },
  { "MMSS_MDP_DSC_1",                              0x00181400, 0x00000200 },
  { "MMSS_MDP_SCM3_0",                             0x00181600, 0x00000020 },
  { "MMSS_MDP_QDSS",                               0x00181a00, 0x00000200 },
  { "MMSS_DP",                                     0x00190000, 0x00001600 },
  { "MMSS_DP_AHBCLK",                              0x00190000, 0x00000200 },
  { "MMSS_DP_AUXCLK",                              0x00190200, 0x00000200 },
  { "MMSS_DP_LCLK",                                0x00190400, 0x00000600 },
  { "MMSS_DP_PCLK",                                0x00190a00, 0x00000600 },
  { "MMSS_DSI_0",                                  0x00194000, 0x00001000 },
  { "MMSS_DSI_0_DSI",                              0x00194000, 0x00000400 },
  { "MMSS_DSI_0_PHY",                              0x00194400, 0x00000588 },
  { "MMSS_DSI_0_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON", 0x00194400, 0x0000007c },
  { "MMSS_DSI_0_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN", 0x00194500, 0x00000080 },
  { "MMSS_DSI_0_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN", 0x00194580, 0x00000080 },
  { "MMSS_DSI_0_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN", 0x00194600, 0x00000080 },
  { "MMSS_DSI_0_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN", 0x00194680, 0x00000080 },
  { "MMSS_DSI_0_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN", 0x00194700, 0x00000080 },
  { "MMSS_DSI_0_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE", 0x00194800, 0x00000124 },
  { "MMSS_DSI_1",                                  0x00196000, 0x00001000 },
  { "MMSS_DSI_1_DSI",                              0x00196000, 0x00000400 },
  { "MMSS_DSI_1_PHY",                              0x00196400, 0x00000588 },
  { "MMSS_DSI_1_PHY_DSIPHY_CMN_DSIPHY_CMN_DSI_COMMON", 0x00196400, 0x0000007c },
  { "MMSS_DSI_1_PHY_DSIPHY_DLN0_DSIPHY_DLN0_DSI_DATALN", 0x00196500, 0x00000080 },
  { "MMSS_DSI_1_PHY_DSIPHY_DLN1_DSIPHY_DLN1_DSI_DATALN", 0x00196580, 0x00000080 },
  { "MMSS_DSI_1_PHY_DSIPHY_DLN2_DSIPHY_DLN2_DSI_DATALN", 0x00196600, 0x00000080 },
  { "MMSS_DSI_1_PHY_DSIPHY_DLN3_DSIPHY_DLN3_DSI_DATALN", 0x00196680, 0x00000080 },
  { "MMSS_DSI_1_PHY_DSIPHY_CKLN_DSIPHY_CKLN_DSI_DATALN", 0x00196700, 0x00000080 },
  { "MMSS_DSI_1_PHY_DSIPHY_PLL_DSIPHY_PLL_DSI_COM_LITE", 0x00196800, 0x00000124 },
  { "MMSS_HDMI",                                   0x001a0000, 0x00001300 },
  { "MMSS_HDMI_PHY_QSERDES_COM_QSERDES_COM_HDMI_COM", 0x001a0600, 0x0000018c },
  { "MMSS_HDMI_PHY_QSERDES_TX_L0_QSERDES_TX_L0_HDMI_TX", 0x001a0a00, 0x00000038 },
  { "MMSS_HDMI_PHY_QSERDES_TX_L1_QSERDES_TX_L1_HDMI_TX", 0x001a0c00, 0x00000038 },
  { "MMSS_HDMI_PHY_QSERDES_TX_L2_QSERDES_TX_L2_HDMI_TX", 0x001a0e00, 0x00000038 },
  { "MMSS_HDMI_PHY_QSERDES_TX_L3_QSERDES_TX_L3_HDMI_TX", 0x001a1000, 0x00000038 },
  { "MMSS_HDMI_PHY",                               0x001a1200, 0x000000e8 },
  { "MMSS_MHL",                                    0x001a8000, 0x00000800 },
  { "MMSS_MHL_CBUS",                               0x001a8400, 0x00000100 },
  { "MMSS_MHL_PHY",                                0x001a8500, 0x00000124 },
  { "MMSS_MHL_PHY_PLL",                            0x001a8700, 0x000000f4 },
  { "MMSS_ROT",                                    0x001a8800, 0x00002900 },
  { "MMSS_ROT_ROTTOP",                             0x001a8800, 0x00000100 },
  { "MMSS_ROT_SSPP",                               0x001a8900, 0x00000200 },
  { "MMSS_ROT_WB",                                 0x001a8b00, 0x00000300 },
  { "MMSS_ROT_REGDMA",                             0x001a8e00, 0x00002100 },
  { "MMSS_ROT_REGDMA_RAM",                         0x001a8e00, 0x00002000 },
  { "MMSS_ROT_REGDMA_CSR",                         0x001aae00, 0x00000100 },
  { "MMSS_ROT_QDSS",                               0x001aaf00, 0x00000200 },
  { "MMSS_VBIF",                                   0x001b0000, 0x00003000 },
  { "MMSS_VBIF_VBIF_SDE",                          0x001b0000, 0x00003000 },
  { "MMSS_VBIF_NRT",                               0x001b8000, 0x00003000 },
  { "MMSS_VBIF_NRT_VBIF_ROT",                      0x001b8000, 0x00003000 },
  { "MMSS_XPU",                                    0x001c8000, 0x00001400 },
  { "MMSS_MDSS_SEC",                               0x001d0000, 0x00030000 },
  { "MMSS_MDSS_SEC_HDCP_SEC_TZ_ONLY",              0x001d0000, 0x00001000 },
  { "MMSS_MDSS_SEC_DP_HDCP_SEC_TZ_ONLY",           0x001d1000, 0x00001000 },
  { "MMSS_MDSS_SEC_HDCP_SEC_TZ_HV",                0x001d8000, 0x00001000 },
  { "MMSS_MDSS_SEC_DSI_0_SEC",                     0x001d9000, 0x00001000 },
  { "MMSS_MDSS_SEC_DSI_1_SEC",                     0x001da000, 0x00001000 },
  { "MMSS_MDSS_SEC_DP_HDCP_SEC_TZ_HV",             0x001db000, 0x00001000 },
  { "MMSS_MDSS_SEC_HDCP_SEC_TZ_HV_HLOS",           0x001e0000, 0x00001000 },
  { "MMSS_MDSS_SEC_DP_HDCP_SEC_TZ_HV_HLOS",        0x001e1000, 0x00001000 },
  { "MMSS_MDSS_SEC_HDCP_SEC_DBG",                  0x001f0000, 0x00001000 },
  { "MMSS_MDSS_SEC_DP_HDCP_SEC_DBG",               0x001f1000, 0x00001000 },
  { "MMSS_CAMSS",                                  0x00200000, 0x00100000 },
  { "MMSS_A_CAMSS",                                0x00200000, 0x00004000 },
  { "MMSS_A_CAMSS_MICRO",                          0x00204000, 0x00004000 },
  { "MMSS_A_CCI",                                  0x0020c000, 0x00004000 },
  { "MMSS_A_VFE_0",                                0x00210000, 0x00004000 },
  { "MMSS_A_VFE_1",                                0x00214000, 0x00004000 },
  { "MMSS_A_CPP",                                  0x00218000, 0x00004000 },
  { "MMSS_A_JPEG_0",                               0x0021c000, 0x00004000 },
  { "MMSS_A_CSID_0",                               0x00230000, 0x00000400 },
  { "MMSS_A_CSID_1",                               0x00230400, 0x00000400 },
  { "MMSS_A_CSID_2",                               0x00230800, 0x00000400 },
  { "MMSS_A_CSID_3",                               0x00230c00, 0x00000400 },
  { "MMSS_A_ISPIF",                                0x00231000, 0x00000c00 },
  { "MMSS_A_VBIF_VFE",                             0x00240000, 0x00003000 },
  { "MMSS_A_VBIF_VFE_VBIF_VFE_DENOISE",            0x00240000, 0x00003000 },
  { "MMSS_A_VBIF_JPEG",                            0x00260000, 0x00003000 },
  { "MMSS_A_VBIF_CPP",                             0x00280000, 0x00003000 },
  { "MMSS_A_JPEG_3",                               0x002a0000, 0x00004000 },
  { "MMSS_VENUS0",                                 0x00400000, 0x00100000 },
  { "MMSS_VENUS0_VENC_TOP_BASE",                   0x00400000, 0x00001000 },
  { "MMSS_VENUS0_VENC_SS",                         0x00400000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VSP_BASE",                   0x00401000, 0x00003000 },
  { "MMSS_VENUS0_VENC_VSP_TOP",                    0x00401000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VSP_CCE",                    0x00402000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VSP_SDE",                    0x00403000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_BASE",                   0x00404000, 0x0000a000 },
  { "MMSS_VENUS0_VENC_VPP_TOP",                    0x00404000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_SE",                     0x00405000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_PE",                     0x00406000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_TE",                     0x00407000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_FE",                     0x00408000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_SSE",                    0x00409000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_ISE",                    0x0040a000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_FSE",                    0x0040b000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_VPE",                    0x0040c000, 0x00001000 },
  { "MMSS_VENUS0_VENC_VPP_MVP",                    0x0040d000, 0x00001000 },
  { "MMSS_VENUS0_VENC_DMA_BASE",                   0x0040f000, 0x00001000 },
  { "MMSS_VENUS0_VENC_DMA",                        0x0040f000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_TOP_BASE",                   0x00430000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_SS",                         0x00430000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VSP_BASE",                   0x00431000, 0x00003000 },
  { "MMSS_VENUS0_VDEC_VSP_TOP",                    0x00431000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VSP_CCE",                    0x00432000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VSP_SDE",                    0x00433000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_BASE",                   0x00434000, 0x00006000 },
  { "MMSS_VENUS0_VDEC_VPP_TOP",                    0x00434000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_SE",                     0x00435000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_PE",                     0x00436000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_TE",                     0x00437000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_FE",                     0x00438000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_VPP_PPE",                    0x00439000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_DMA_BASE",                   0x0043f000, 0x00001000 },
  { "MMSS_VENUS0_VDEC_DMA",                        0x0043f000, 0x00001000 },
  { "MMSS_VENUS0_VENUS_CPU_BASE",                  0x004c0000, 0x00020000 },
  { "MMSS_VENUS0_CPU_WD",                          0x004c1000, 0x00001000 },
  { "MMSS_VENUS0_CPU_TM",                          0x004c2000, 0x00001000 },
  { "MMSS_VENUS0_CPU_CS",                          0x004d2000, 0x00001000 },
  { "MMSS_VENUS0_CPU_IQ",                          0x004df000, 0x00001000 },
  { "MMSS_VENUS0_VENUS_VENUS_VBIF_TOP_VENUS_STARHAWK", 0x00480000, 0x00003000 },
  { "MMSS_VENUS0_VENUS_VBIF_VENUS",                0x00480000, 0x00003000 },
  { "MMSS_VENUS0_VENUS_WRAPPER_BASE",              0x004e0000, 0x00020000 },
  { "MMSS_VENUS0_VENUS_WRAPPER_TOP",               0x004e0000, 0x00010000 },
  { "QHS_MMSS0_U_AHB_BUS_TIMEOUT0",                0x00000000, 0x00001000 },
  { "QHS_MMSS1_U_AHB_BUS_TIMEOUT1",                0x00001000, 0x00001000 },
  { "QHS_MMSS2_U_AHB_BUS_TIMEOUT2",                0x00002000, 0x00001000 },
  { "QHS_MMSS3_U_AHB_BUS_TIMEOUT3",                0x00003000, 0x00001000 },
  { "MMSS_BIMC_SMMU_U_MMSS_BIMC_SMMU",             0x00500000, 0x00040000 },
  { "MMSS_BIMC_SMMU",                              0x00500000, 0x00040000 },
  { "MMSS_BIMC_SMMU_SMMU_GLOBAL0",                 0x00500000, 0x00001000 },
  { "MMSS_BIMC_SMMU_SMMU_GLOBAL1",                 0x00501000, 0x00001000 },
  { "MMSS_BIMC_SMMU_SMMU_IMPL_DEF0",               0x00502000, 0x00001000 },
  { "MMSS_BIMC_SMMU_SMMU_PERF_MON",                0x00503000, 0x00001000 },
  { "MMSS_BIMC_SMMU_SMMU_SSD",                     0x00504000, 0x00001000 },
  { "MMSS_BIMC_SMMU_SMMU_IMPL_DEF1",               0x00506000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB0_CB0_SMMU_CONTEXT_BANK",  0x00520000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB1_CB1_SMMU_CONTEXT_BANK",  0x00521000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB2_CB2_SMMU_CONTEXT_BANK",  0x00522000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB3_CB3_SMMU_CONTEXT_BANK",  0x00523000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB4_CB4_SMMU_CONTEXT_BANK",  0x00524000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB5_CB5_SMMU_CONTEXT_BANK",  0x00525000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB6_CB6_SMMU_CONTEXT_BANK",  0x00526000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB7_CB7_SMMU_CONTEXT_BANK",  0x00527000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB8_CB8_SMMU_CONTEXT_BANK",  0x00528000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB9_CB9_SMMU_CONTEXT_BANK",  0x00529000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB10_CB10_SMMU_CONTEXT_BANK", 0x0052a000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB11_CB11_SMMU_CONTEXT_BANK", 0x0052b000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB12_CB12_SMMU_CONTEXT_BANK", 0x0052c000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB13_CB13_SMMU_CONTEXT_BANK", 0x0052d000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB14_CB14_SMMU_CONTEXT_BANK", 0x0052e000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB15_CB15_SMMU_CONTEXT_BANK", 0x0052f000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB16_CB16_SMMU_CONTEXT_BANK", 0x00530000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB17_CB17_SMMU_CONTEXT_BANK", 0x00531000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB18_CB18_SMMU_CONTEXT_BANK", 0x00532000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB19_CB19_SMMU_CONTEXT_BANK", 0x00533000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB20_CB20_SMMU_CONTEXT_BANK", 0x00534000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB21_CB21_SMMU_CONTEXT_BANK", 0x00535000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB22_CB22_SMMU_CONTEXT_BANK", 0x00536000, 0x00001000 },
  { "MMSS_BIMC_SMMU_A_CB23_CB23_SMMU_CONTEXT_BANK", 0x00537000, 0x00001000 },
  { "THROTTLE_DISPLAY_U_THROTTLE_WRAPPER_DISPLAY", 0x000b1000, 0x00001000 },
  { "THROTTLE_DISPLAY_THROTTLE_0_THROTTLE_0_THROTTLE", 0x000b1000, 0x00000100 },
  { "THROTTLE_DISPLAY_THROTTLE_1_THROTTLE_1_THROTTLE", 0x000b1200, 0x00000100 },
  { "THROTTLE_DISPLAY_THROTTLE_2_THROTTLE_2_THROTTLE", 0x000b1400, 0x00000100 },
  { "THROTTLE_CAMSS_U_THROTTLE_WRAPPER_CAMSS",     0x000b2000, 0x00001000 },
  { "THROTTLE_CAMSS_THROTTLE_0_THROTTLE_0_THROTTLE", 0x000b2000, 0x00000100 },
  { "THROTTLE_CAMSS_THROTTLE_1_THROTTLE_1_THROTTLE", 0x000b2200, 0x00000100 },
  { "THROTTLE_CAMSS_THROTTLE_2_THROTTLE_2_THROTTLE", 0x000b2400, 0x00000100 },
  { "THROTTLE_VENUS_U_THROTTLE_WRAPPER_VENUS",     0x000b3000, 0x00001000 },
  { "THROTTLE_VENUS_THROTTLE_0_THROTTLE_0_THROTTLE", 0x000b3000, 0x00000100 },
  { "THROTTLE_VENUS_THROTTLE_1_THROTTLE_1_THROTTLE", 0x000b3200, 0x00000100 },
  { "XPU3_MNOC_U_XPU3_AHB_WRAPPER_MNOC",           0x00010000, 0x00001700 },
  { "MMSS_XPU3_MMSS_CC_U_XPU3_MMCC_WRAPPER",       0x00012000, 0x00001880 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MODEM[] =
{
  { "MODEM_VUIC",                                  0x00000000, 0x00200000 },
  { "QLSS_QLBR_TOP",                               0x00020000, 0x00010000 },
  { "QLSS_QLBR_PDMEM",                             0x00020000, 0x00004000 },
  { "QLSS_SEQ",                                    0x00024000, 0x00000200 },
  { "QLSS_QLBR",                                   0x00024200, 0x00000200 },
  { "QLSS_QDBG",                                   0x00024400, 0x00000200 },
  { "MCDMA_X0_3_VUSS2_TOP",                        0x00040000, 0x00020000 },
  { "MCDMA_X0_3_VUSS_CSR",                         0x00040000, 0x00000800 },
  { "MCDMA_VUSS_DMEM_X4X8",                        0x00041000, 0x00004000 },
  { "SVUSS1_X8_2_VUSS1_TOP",                       0x00060000, 0x00020000 },
  { "SVUSS1_X8_2_VUSS_CSR",                        0x00060000, 0x00000800 },
  { "SVUSS1_PMEMSS_CSR",                           0x00060800, 0x00000800 },
  { "SVUSS1_VUSS_DMEM_X4X8",                       0x00061000, 0x00004000 },
  { "SVUSS2_ENC_TOP",                              0x00080000, 0x00020000 },
  { "SVUSS2_VUSS_CSR",                             0x00080000, 0x00000800 },
  { "SVUSS2_VUSS_DMEM_ENC",                        0x00081000, 0x0000d800 },
  { "SVUSS3_X4_1_VUSS2_TOP",                       0x000a0000, 0x00020000 },
  { "SVUSS3_X4_1_VUSS_CSR",                        0x000a0000, 0x00000800 },
  { "SVUSS3_VUSS_DMEM_X4X8",                       0x000a1000, 0x00004000 },
  { "DEMOD1_X0_2_VUSS1_TOP",                       0x000c0000, 0x00020000 },
  { "DEMOD1_X0_2_VUSS_CSR",                        0x000c0000, 0x00000800 },
  { "DEMOD1_PMEMSS_CSR",                           0x000c0800, 0x00000800 },
  { "DEMOD1_VUSS_DMEM_X4X8",                       0x000c1000, 0x00004000 },
  { "CCH1_CCHP_TOP",                               0x000e0000, 0x00020000 },
  { "CCH1_X0_1_VUSS_CSR",                          0x000e0000, 0x00000800 },
  { "CCH1_VUSS_DMEM_CCHP",                         0x000e1000, 0x00008000 },
  { "DEC1_DECODER",                                0x00100000, 0x00000380 },
  { "VUSS1_X8_0_VUSS1_TOP",                        0x00120000, 0x00020000 },
  { "VUSS1_X8_0_VUSS_CSR",                         0x00120000, 0x00000800 },
  { "VUSS1_PMEMSS_CSR",                            0x00120800, 0x00000800 },
  { "VUSS1_VUSS_DMEM_X4X8",                        0x00121000, 0x00004000 },
  { "VUSS2_X8_0_VUSS2_TOP",                        0x00140000, 0x00020000 },
  { "VUSS2_X8_0_VUSS_CSR",                         0x00140000, 0x00000800 },
  { "VUSS2_VUSS_DMEM_X4X8",                        0x00141000, 0x00004000 },
  { "MPMU_TOP",                                    0x00300000, 0x00100000 },
  { "MODEM_MPMU_CSR",                              0x00300400, 0x00000400 },
  { "MTC_TOP",                                     0x00500000, 0x00010000 },
  { "MCDMA",                                       0x00500400, 0x00000400 },
  { "A2",                                          0x00500800, 0x00000400 },
  { "DBG",                                         0x00500c00, 0x00000400 },
  { "MTC_BRDG",                                    0x00501000, 0x00000400 },
  { "A2_MEM",                                      0x00502000, 0x00002000 },
  { "MCDMA_TS_TRIF",                               0x00504000, 0x00000c00 },
  { "MNOC_AXI_BR_CSR",                             0x00400000, 0x00100000 },
  { "MNOC_AXI_BR_MEM",                             0x01000000, 0x01000000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_L2_TCM[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SNOC_4_BUS_TIMEOUT[] =
{
  { "SNOC_4_BUS_TIMEOUT",                          0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SNOC_1_BUS_TIMEOUT[] =
{
  { "SNOC_1_BUS_TIMEOUT",                          0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SNOC_3_BUS_TIMEOUT[] =
{
  { "SNOC_3_BUS_TIMEOUT",                          0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SNOC_2_BUS_TIMEOUT[] =
{
  { "SNOC_2_BUS_TIMEOUT",                          0x00000000, 0x00001000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_MSS_NAV_MPU_MPU32Q2N7S1V1_16_CL36M35L12_AXI[] =
{
  { "MSS_NAV_MPU_MPU32Q2N7S1V1_16_CL36M35L12_AXI", 0x00000000, 0x00001800 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_SYSTEM_IMEM[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_IPA_0_IPA_WRAPPER[] =
{
  { "IPA_0_BAM_NDP",                               0x00000000, 0x0002b000 },
  { "IPA_0_BAM",                                   0x00004000, 0x00027000 },
  { "IPA_0_XPU3",                                  0x00001000, 0x00003000 },
  { "IPA_0_IPA_VMIDMT",                            0x00030000, 0x00001000 },
  { "IPA_0_IPA",                                   0x00040000, 0x00010000 },
  { "IPA_0_IPA_UC",                                0x00050000, 0x00014000 },
  { "IPA_0_IPA_UC_IPA_UC_RAM",                     0x00050000, 0x00008000 },
  { "IPA_0_IPA_UC_IPA_UC_PER",                     0x00060000, 0x00002000 },
  { "IPA_0_IPA_UC_IPA_UC_MBOX",                    0x00062000, 0x00002000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_LPASS[] =
{
  { "LPASS_CC",                                    0x00000000, 0x00058000 },
  { "LPASS_SCSR",                                  0x00060000, 0x00020000 },
  { "LPASS_PMU_REGS",                              0x00060000, 0x00001000 },
  { "LPASS_SCSR_REGS",                             0x00061000, 0x0000f000 },
  { "LPASS_TLMM_GPIO",                             0x00070000, 0x00010000 },
  { "LPASS_TCSR",                                  0x00080000, 0x00028000 },
  { "LPASS_QOS",                                   0x000b0000, 0x00003000 },
  { "LPASS_QOS_QOS_GENERIC",                       0x000b0000, 0x00000100 },
  { "LPASS_QOS_QOS_DANGER",                        0x000b0300, 0x00000200 },
  { "LPASS_QOS_QOS_INTERRUPTS",                    0x000b1000, 0x00002000 },
  { "LPASS_AHBE_TIME",                             0x000b7000, 0x00001000 },
  { "LPASS_Q6SS_MPU",                              0x000b8000, 0x00002100 },
  { "LPASS_CSR",                                   0x000c0000, 0x0001f000 },
  { "LPASS_AHBI_TIME",                             0x000f6000, 0x00001000 },
  { "LPASS_SYNC",                                  0x000f7000, 0x00000ffd },
  { "LPASS_AVTIMER",                               0x000f7000, 0x00000100 },
  { "LPASS_HDMITX",                                0x000f8000, 0x00007000 },
  { "LPASS_ATIMER",                                0x000ff000, 0x00000100 },
  { "LPASS_LPM",                                   0x00120000, 0x00010000 },
  { "LPASS_TLB",                                   0x00130000, 0x00005000 },
  { "LPASS_RESAMPLER",                             0x00138000, 0x00008000 },
  { "LPASS_AUD_LPASS_SB0",                         0x00180000, 0x00080000 },
  { "LPASS_AUD_SB_SLIMBUS_BAM_LITE",               0x00180000, 0x0002e000 },
  { "LPASS_AUD_SB_BAM",                            0x00184000, 0x0002a000 },
  { "LPASS_AUD_SLIMBUS",                           0x001c0000, 0x0002c000 },
  { "LPASS_QCA_SBMASTER0_BASE",                    0x00200000, 0x00080000 },
  { "LPASS_QCA_SB_SLIMBUS_BAM_LITE",               0x00200000, 0x00024000 },
  { "LPASS_QCA_SB_BAM",                            0x00204000, 0x00020000 },
  { "LPASS_QCA_SLIMBUS",                           0x00240000, 0x0002c000 },
  { "LPASS_LPA_IF",                                0x00280000, 0x00028000 },
  { "LPASS_AUDIO_CODEC",                           0x002c0000, 0x00000314 },
  { "LPASS_SOUND_WIRE",                            0x002c1000, 0x00000400 },
  { "LPASS_PAGE",                                  0x002c1000, 0x00000004 },
  { "LPASS_CDC_TX9",                               0x002c1304, 0x0000000c },
  { "LPASS_CDC_TX10",                              0x002c1314, 0x0000000c },
  { "LPASS_CDC_TX11",                              0x002c1324, 0x0000000c },
  { "LPASS_CDC_TX12",                              0x002c1334, 0x0000000c },
  { "LPASS_CDC_COMPANDER7",                        0x002c1024, 0x00000020 },
  { "LPASS_CDC_COMPANDER8",                        0x002c1044, 0x00000020 },
  { "LPASS_CDC_RX7",                               0x002c11a4, 0x00000048 },
  { "LPASS_CDC_RX8",                               0x002c1384, 0x00000048 },
  { "LPASS_CDC_BOOST0",                            0x002c1064, 0x00000010 },
  { "LPASS_CDC_BOOST1",                            0x002c1084, 0x00000010 },
  { "LPASS_SWR_AHB_BRIDGE_SWR_AHB_BRIDGE_SWR_AHB_BRIDGE", 0x002c10a4, 0x00000048 },
  { "LPASS_CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL", 0x002c1104, 0x0000000c },
  { "LPASS_SWR_TOP_SWR_TOP_SWR_TOP",               0x002c1204, 0x00000038 },
  { "LPASS_AHBL_TIME",                             0x002c3000, 0x00001000 },
  { "LPASS_SENSOR_LPASS_BLSP",                     0x00400000, 0x00040000 },
  { "LPASS_SENSOR_BLSP_BAM",                       0x00404000, 0x00021000 },
  { "LPASS_SENSOR_BLSP_BAM_XPU3",                  0x00401000, 0x00003000 },
  { "LPASS_SENSOR_BLSP_BAM_VMIDMT",                0x00400000, 0x00001000 },
  { "LPASS_SENSOR_BLSP_UART0_UART0_DM",            0x0042f000, 0x00000200 },
  { "LPASS_SENSOR_BLSP_UART1_UART1_DM",            0x00430000, 0x00000200 },
  { "LPASS_SENSOR_BLSP_UART2_UART2_DM",            0x00431000, 0x00000200 },
  { "LPASS_SENSOR_BLSP_UART3_UART3_DM",            0x00432000, 0x00000200 },
  { "LPASS_SENSOR_BLSP_QUP0",                      0x00435000, 0x00000600 },
  { "LPASS_SENSOR_BLSP_QUP1",                      0x00436000, 0x00000600 },
  { "LPASS_SENSOR_BLSP_QUP2",                      0x00437000, 0x00000600 },
  { "LPASS_SENSOR_MEM",                            0x00440000, 0x00008000 },
  { "LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT",    0x00448000, 0x00001000 },
  { "LPASS_SENSOR_CORE_CSR",                       0x00450000, 0x00009000 },
  { "LPASS_TRACE32_DBG",                           0x00490000, 0x00008000 },
  { "LPASS_CTI_0_CTI_0_CSCTI",                     0x00490000, 0x00001000 },
  { "LPASS_CTI_1_CTI_1_CSCTI",                     0x00491000, 0x00001000 },
  { "LPASS_STM_STM_CXSTM_2_4_4_TRUE",              0x00493000, 0x00001000 },
  { "LPASS_FUN0_FUN0_CXATBFUNNEL_32W2SP",          0x00494000, 0x00001000 },
  { "LPASS_LPASS_ETFETB_LPASS_ETFETB_CXTMC_F32W16K", 0x00495000, 0x00001000 },
  { "LPASS_TSGEN_TSGEN_CXTSGEN",                   0x00496000, 0x00001000 },
  { "LPASS_STM",                                   0x00500000, 0x00100000 },
  { "LPASS_QDSP6V60SS_PUBLIC",                     0x00700000, 0x00080000 },
  { "LPASS_QDSP6V60SS_PUB",                        0x00700000, 0x00004040 },
  { "LPASS_QDSP6V60SS_PRIVATE",                    0x00780000, 0x00080000 },
  { "LPASS_QDSP6V60SS_CSR",                        0x00780000, 0x00008028 },
  { "LPASS_QDSP6V60SS_L2VIC",                      0x00790000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_QTMR_AC",               0x007a0000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F0_0",                     0x007a1000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F1_1",                     0x007a2000, 0x00001000 },
  { "LPASS_QDSP6SS_QTMR_F2_2",                     0x007a3000, 0x00001000 },
  { "LPASS_QDSP6SS_QDSP6SS_SAW4_QDSP6SS_NOPMIC_WRAPPER", 0x007b0000, 0x00001000 },
  { "LPASS_QDSP6SS_SAW4_SPM",                      0x007b0000, 0x00000800 },
  { "LPASS_QDSP6SS_SAW4_AVS",                      0x007b0800, 0x00000400 },
  { "LPASS_QDSP6SS_SAW4_STS",                      0x007b0c00, 0x00000400 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_A53SS[] =
{
  { "APCS_GIC_NOC",                                0x0011b000, 0x00000080 },
  { "APCS_GIC500_GICD",                            0x00200000, 0x00010000 },
  { "APCS_GIC500_GICM",                            0x00210000, 0x00010000 },
  { "APCS_GIC500_GITS",                            0x00220000, 0x00020000 },
  { "APCS_ALIAS0_GIC500_GICR",                     0x00300000, 0x00020000 },
  { "APCS_ALIAS1_GIC500_GICR",                     0x00320000, 0x00020000 },
  { "APCS_ALIAS2_GIC500_GICR",                     0x00340000, 0x00020000 },
  { "APCS_ALIAS3_GIC500_GICR",                     0x00360000, 0x00020000 },
  { "APCS_ALIAS4_GIC500_GICR",                     0x00380000, 0x00020000 },
  { "APCS_ALIAS5_GIC500_GICR",                     0x003a0000, 0x00020000 },
  { "APCS_ALIAS6_GIC500_GICR",                     0x003c0000, 0x00020000 },
  { "APCS_ALIAS7_GIC500_GICR",                     0x003e0000, 0x00020000 },
  { "APCS_BANKED_APSS_ACS",                        0x00008000, 0x00001000 },
  { "APCS_ALIAS0_APSS_ACS",                        0x00188000, 0x00001000 },
  { "APCS_ALIAS1_APSS_ACS",                        0x00198000, 0x00001000 },
  { "APCS_ALIAS2_APSS_ACS",                        0x001a8000, 0x00001000 },
  { "APCS_ALIAS3_APSS_ACS",                        0x001b8000, 0x00001000 },
  { "APCS_ALIAS4_APSS_ACS",                        0x00088000, 0x00001000 },
  { "APCS_ALIAS5_APSS_ACS",                        0x00098000, 0x00001000 },
  { "APCS_ALIAS6_APSS_ACS",                        0x000a8000, 0x00001000 },
  { "APCS_ALIAS7_APSS_ACS",                        0x000b8000, 0x00001000 },
  { "OLC_WRAP",                                    0x001c0000, 0x00011000 },
  { "OSM_OSM",                                     0x001c0000, 0x00004000 },
  { "PERF_CPRH_WRAPPER",                           0x001c4000, 0x00004000 },
  { "PWR_CPRH_WRAPPER",                            0x001c8000, 0x00004000 },
  { "PERF_LLM_WRAPPER",                            0x001cc000, 0x00002000 },
  { "PERF_LLM_PRIVATE_LLM_PRIVATE_LMH_DCVS",       0x001cd800, 0x00000401 },
  { "PERF_LLM_PRIVATE",                            0x001cd000, 0x00000800 },
  { "PERF_LLM_PUBLIC_LLM_PUBLIC_LMH_DCVS_PUB",     0x001cc800, 0x00000401 },
  { "PERF_LLM_PUBLIC",                             0x001cc000, 0x00000800 },
  { "PWR_LLM_WRAPPER",                             0x001ce000, 0x00002000 },
  { "PWR_LLM_PRIVATE_LLM_PRIVATE_LMH_DCVS",        0x001cf800, 0x00000401 },
  { "PWR_LLM_PRIVATE",                             0x001cf000, 0x00000800 },
  { "PWR_LLM_PUBLIC_LLM_PUBLIC_LMH_DCVS_PUB",      0x001ce800, 0x00000401 },
  { "PWR_LLM_PUBLIC",                              0x001ce000, 0x00000800 },
  { "APSS_APM_WRAP",                               0x001d0000, 0x00001000 },
  { "APCS_BANKED_APSS_LDO_BHS_PRIV_REGS",          0x00007000, 0x00001000 },
  { "APC4_APSS_LDO_BHS_PRIV_REGS",                 0x00087000, 0x00001000 },
  { "APC5_APSS_LDO_BHS_PRIV_REGS",                 0x00097000, 0x00001000 },
  { "APC6_APSS_LDO_BHS_PRIV_REGS",                 0x000a7000, 0x00001000 },
  { "APC7_APSS_LDO_BHS_PRIV_REGS",                 0x000b7000, 0x00001000 },
  { "APCS_BANKED_APSS_LDO_BHS_REGS",               0x00006000, 0x00001000 },
  { "APC4_APSS_LDO_BHS_REGS",                      0x00086000, 0x00001000 },
  { "APC5_APSS_LDO_BHS_REGS",                      0x00096000, 0x00001000 },
  { "APC6_APSS_LDO_BHS_REGS",                      0x000a6000, 0x00001000 },
  { "APC7_APSS_LDO_BHS_REGS",                      0x000b6000, 0x00001000 },
  { "APCS_ALIAS0_APSS_CFG",                        0x00110000, 0x00001000 },
  { "APCS_ALIAS0_APSS_GLB",                        0x00111000, 0x00001000 },
  { "APCS_CLUSTER0_APSS_RC",                       0x00114000, 0x00000800 },
  { "APCS_CLUSTER0_ACD",                           0x00114800, 0x00000800 },
  { "APCLUS0_L2_SAW4_1_1_HMSS_CBF_PDW16_WRAPPER",  0x00112000, 0x00001000 },
  { "APCLUS0_L2_SAW4_1_1_SPM",                     0x00112000, 0x00000800 },
  { "APCLUS0_L2_SAW4_1_1_AVS",                     0x00112800, 0x00000400 },
  { "APCLUS0_L2_SAW4_1_1_STS",                     0x00112c00, 0x00000400 },
  { "APCS_BANKED_SAW4_1_1_HMSS_CPU_WRAPPER",       0x00009000, 0x00001000 },
  { "APCS_BANKED_SAW4_1_1_SPM",                    0x00009000, 0x00000800 },
  { "APCS_BANKED_SAW4_1_1_AVS",                    0x00009800, 0x00000400 },
  { "APCS_BANKED_SAW4_1_1_STS",                    0x00009c00, 0x00000400 },
  { "APCS_ALIAS0_SAW4_1_1_HMSS_CPU_WRAPPER",       0x00189000, 0x00001000 },
  { "APCS_ALIAS0_SAW4_1_1_SPM",                    0x00189000, 0x00000800 },
  { "APCS_ALIAS0_SAW4_1_1_AVS",                    0x00189800, 0x00000400 },
  { "APCS_ALIAS0_SAW4_1_1_STS",                    0x00189c00, 0x00000400 },
  { "APCS_ALIAS1_SAW4_1_1_HMSS_CPU_WRAPPER",       0x00199000, 0x00001000 },
  { "APCS_ALIAS1_SAW4_1_1_SPM",                    0x00199000, 0x00000800 },
  { "APCS_ALIAS1_SAW4_1_1_AVS",                    0x00199800, 0x00000400 },
  { "APCS_ALIAS1_SAW4_1_1_STS",                    0x00199c00, 0x00000400 },
  { "APCS_ALIAS2_SAW4_1_1_HMSS_CPU_WRAPPER",       0x001a9000, 0x00001000 },
  { "APCS_ALIAS2_SAW4_1_1_SPM",                    0x001a9000, 0x00000800 },
  { "APCS_ALIAS2_SAW4_1_1_AVS",                    0x001a9800, 0x00000400 },
  { "APCS_ALIAS2_SAW4_1_1_STS",                    0x001a9c00, 0x00000400 },
  { "APCS_ALIAS3_SAW4_1_1_HMSS_CPU_WRAPPER",       0x001b9000, 0x00001000 },
  { "APCS_ALIAS3_SAW4_1_1_SPM",                    0x001b9000, 0x00000800 },
  { "APCS_ALIAS3_SAW4_1_1_AVS",                    0x001b9800, 0x00000400 },
  { "APCS_ALIAS3_SAW4_1_1_STS",                    0x001b9c00, 0x00000400 },
  { "APCS_ALIAS4_SAW4_1_1_HMSS_CPU_WRAPPER",       0x00089000, 0x00001000 },
  { "APCS_ALIAS4_SAW4_1_1_SPM",                    0x00089000, 0x00000800 },
  { "APCS_ALIAS4_SAW4_1_1_AVS",                    0x00089800, 0x00000400 },
  { "APCS_ALIAS4_SAW4_1_1_STS",                    0x00089c00, 0x00000400 },
  { "APCS_ALIAS5_SAW4_1_1_HMSS_CPU_WRAPPER",       0x00099000, 0x00001000 },
  { "APCS_ALIAS5_SAW4_1_1_SPM",                    0x00099000, 0x00000800 },
  { "APCS_ALIAS5_SAW4_1_1_AVS",                    0x00099800, 0x00000400 },
  { "APCS_ALIAS5_SAW4_1_1_STS",                    0x00099c00, 0x00000400 },
  { "APCS_ALIAS6_SAW4_1_1_HMSS_CPU_WRAPPER",       0x000a9000, 0x00001000 },
  { "APCS_ALIAS6_SAW4_1_1_SPM",                    0x000a9000, 0x00000800 },
  { "APCS_ALIAS6_SAW4_1_1_AVS",                    0x000a9800, 0x00000400 },
  { "APCS_ALIAS6_SAW4_1_1_STS",                    0x000a9c00, 0x00000400 },
  { "APCS_ALIAS7_SAW4_1_1_HMSS_CPU_WRAPPER",       0x000b9000, 0x00001000 },
  { "APCS_ALIAS7_SAW4_1_1_SPM",                    0x000b9000, 0x00000800 },
  { "APCS_ALIAS7_SAW4_1_1_AVS",                    0x000b9800, 0x00000400 },
  { "APCS_ALIAS7_SAW4_1_1_STS",                    0x000b9c00, 0x00000400 },
  { "APCS_C0_APSS_HF_PLL",                         0x00116000, 0x00001000 },
  { "APCS_CLUSTER0_APSS_HYP",                      0x0011a000, 0x00001000 },
  { "APCS_QTMR0_QTMR_AC",                          0x00120000, 0x00001000 },
  { "APCS_QTMR0_F0V1_QTMR_V1",                     0x00121000, 0x00001000 },
  { "APCS_QTMR0_F0V2_QTMR_V2",                     0x00122000, 0x00001000 },
  { "APCS_QTMR0_F1V1_QTMR_V1",                     0x00123000, 0x00001000 },
  { "APCS_QTMR0_F2V1_QTMR_V1",                     0x00124000, 0x00001000 },
  { "APCS_QTMR0_F3V1_QTMR_V1",                     0x00125000, 0x00001000 },
  { "APCS_QTMR0_F4V1_QTMR_V1",                     0x00126000, 0x00001000 },
  { "APCS_QTMR0_F5V1_QTMR_V1",                     0x00127000, 0x00001000 },
  { "APCS_QTMR0_F6V1_QTMR_V1",                     0x00128000, 0x00001000 },
  { "APCS_ALIAS1_APSS_CFG",                        0x00010000, 0x00001000 },
  { "APCS_ALIAS1_APSS_GLB",                        0x00011000, 0x00001000 },
  { "APCS_CLUSTER1_APSS_RC",                       0x00014000, 0x00000800 },
  { "APCS_CLUSTER1_ACD",                           0x00014800, 0x00000800 },
  { "APCLUS1_L2_SAW4_1_1_HMSS_CBF_PDW16_WRAPPER",  0x00012000, 0x00001000 },
  { "APCLUS1_L2_SAW4_1_1_SPM",                     0x00012000, 0x00000800 },
  { "APCLUS1_L2_SAW4_1_1_AVS",                     0x00012800, 0x00000400 },
  { "APCLUS1_L2_SAW4_1_1_STS",                     0x00012c00, 0x00000400 },
  { "APCS_C1_APSS_HF_PLL",                         0x00016000, 0x00001000 },
  { "APCS_WDT_TMR1_APSS_WDT",                      0x00017000, 0x00001000 },
  { "APCS_CLUSTER1_APSS_HYP",                      0x0001a000, 0x00001000 },
  { "APCS_QTMR1_QTMR_AC",                          0x00020000, 0x00001000 },
  { "APCS_QTMR1_F0V1_QTMR_V1",                     0x00021000, 0x00001000 },
  { "APCS_QTMR1_F0V2_QTMR_V2",                     0x00022000, 0x00001000 },
  { "APCS_QTMR1_F1V1_QTMR_V1",                     0x00023000, 0x00001000 },
  { "APCS_QTMR1_F2V1_QTMR_V1",                     0x00024000, 0x00001000 },
  { "APCS_QTMR1_F3V1_QTMR_V1",                     0x00025000, 0x00001000 },
  { "APCS_QTMR1_F4V1_QTMR_V1",                     0x00026000, 0x00001000 },
  { "APCS_QTMR1_F5V1_QTMR_V1",                     0x00027000, 0x00001000 },
  { "APCS_QTMR1_F6V1_QTMR_V1",                     0x00028000, 0x00001000 },
  { "APCS_CCI_GLADIATOR",                          0x00100000, 0x0000e000 },
  { "APCS_XPU3",                                   0x001d8000, 0x00004000 },
  { "APCS_COMMON_APSS_SHARED",                     0x001d1000, 0x00001000 },
  { "CCI_SAW4_1_1_HMSS_CPU_WRAPPER",               0x001d2000, 0x00001000 },
  { "CCI_SAW4_1_1_SPM",                            0x001d2000, 0x00000800 },
  { "CCI_SAW4_1_1_AVS",                            0x001d2800, 0x00000400 },
  { "CCI_SAW4_1_1_STS",                            0x001d2c00, 0x00000400 },
  { "CCI_SAW_APSS_CCI_REGS",                       0x001d4000, 0x00001000 },
  { "CCI_SAW_APSS_CCI_HYP_REGS",                   0x001d5000, 0x00001000 },
  { "APCS_COMMON_APSS_VS",                         0x001d6000, 0x00001000 },
  { "APSS_GIC500_GIC500_LEGACY",                   0x00400000, 0x00040000 },
  { "APCS_ISENSE_CONTROLLER",                      0x001dc000, 0x00002000 },
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_WCSS_WRAPPER[] =
{
  { "WCSS_ECAHB",                                  0x00000000, 0x00000400 },
  { "WCSS_ECAHB_TSLV",                             0x00010000, 0x00001000 },
  { "WCSS_SR",                                     0x00020000, 0x00020000 },
  { "WCSS_HM",                                     0x00080000, 0x00780000 },
  { "WCSS_HM_A_PMM_PMM_DEC",                       0x00080000, 0x00000268 },
  { "WCSS_HM_A_WCSS_WAHB_AHB_SS_WFSS_AHB_SS_DEC",  0x00100000, 0x00000400 },
  { "WCSS_HM_A_WCSS_WAHB_AHB_TSLV_WFSS_WAHB_AHB_TSLV", 0x00101000, 0x00001000 },
  { "WCSS_HM_A_NOC_CFG_WIFI_NOC",                  0x00180000, 0x00008000 },
  { "WCSS_HM_A_WCSS_CLK_CTL_WCSS_CC_REG_DEC",      0x001d0000, 0x00010000 },
  { "WCSS_HM_A_WIFI_APB_1",                        0x00200000, 0x00080000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_WMAC_TOP_REG_T0", 0x00200000, 0x00020000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_PDG_REG",  0x00210000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_TXDMA_REG", 0x00210400, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_RXDMA_REG", 0x00210800, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_MCMN_REG", 0x00211000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_RXPCU_REG", 0x00212000, 0x00004000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_TXPCU_REG", 0x00216000, 0x00004000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_AMPI_REG", 0x0021a000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_RXOLE_REG", 0x0021b000, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_A_RXOLE_PARSER_MAC_RXOLE_PARSER_REG", 0x0021b200, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_CCE_REG",  0x0021b600, 0x00000a00 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_TXOLE_REG", 0x0021c000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_A_TXOLE_PARSER_MAC_TXOLE_PARSER_REG", 0x0021c400, 0x00000c00 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_RRI_REG",  0x0021d000, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_CRYPTO_REG", 0x0021f000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_HWSCH_REG", 0x0021f400, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T0_MAC_MXI_REG",  0x0021fc00, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_WMAC_TOP_REG_T1", 0x00220000, 0x00020000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_PDG_REG",  0x00230000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_TXDMA_REG", 0x00230400, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_RXDMA_REG", 0x00230800, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_MCMN_REG", 0x00231000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_RXPCU_REG", 0x00232000, 0x00004000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_TXPCU_REG", 0x00236000, 0x00004000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_AMPI_REG", 0x0023a000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_RXOLE_REG", 0x0023b000, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_A_RXOLE_PARSER_MAC_RXOLE_PARSER_REG", 0x0023b200, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_CCE_REG",  0x0023b600, 0x00000a00 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_TXOLE_REG", 0x0023c000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_A_TXOLE_PARSER_MAC_TXOLE_PARSER_REG", 0x0023c400, 0x00000c00 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_RRI_REG",  0x0023d000, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_CRYPTO_REG", 0x0023f000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_HWSCH_REG", 0x0023f400, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_1_A_WMAC_T1_MAC_MXI_REG",  0x0023fc00, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE0_WFSS_CE_0_REG", 0x00240000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE1_WFSS_CE_1_REG", 0x00241000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE2_WFSS_CE_2_REG", 0x00242000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE3_WFSS_CE_3_REG", 0x00243000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE4_WFSS_CE_4_REG", 0x00244000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE5_WFSS_CE_5_REG", 0x00245000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE6_WFSS_CE_6_REG", 0x00246000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE7_WFSS_CE_7_REG", 0x00247000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE8_WFSS_CE_8_REG", 0x00248000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE9_WFSS_CE_9_REG", 0x00249000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE10_WFSS_CE_10_REG", 0x0024a000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE11_WFSS_CE_11_REG", 0x0024b000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE_COMMON_WRAPPER", 0x0024c000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_WFSS_CE_SECURE_WRAPPER", 0x0024d000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_MAC_CMN_PARSER_WFSS_CMN_PARSER_REG", 0x0024e000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_MAC_TRC_MAC_TRC_REG",  0x00250000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_TOP_REG",  0x00260000, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_BMH_REG",  0x00260000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_LCMH_REG", 0x00260400, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_MCIBASIC_REG", 0x00260800, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_LMH_REG",  0x00260a00, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_SMH_REG",  0x00260c00, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_CXC_TOP_CXC_PMH_REG",  0x00260e00, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_1_A_WCSS_WAHB_APB_TSLV_WFSS_WAHB_APB_TSLV", 0x00272000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_2",                        0x002c0000, 0x00003000 },
  { "WCSS_HM_A_WIFI_APB_2_A_RFACTRL_CH0_RFACTRL_CH0_REG", 0x002c0000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_2_A_RFACTRL_CH1_RFACTRL_CH1_REG", 0x002c1000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_2_A_BBANA_RFACTRL_BBANA_RFACTRL_REG", 0x002c2000, 0x00001000 },
  { "WCSS_HM_WLANDAC_1",                           0x002c3000, 0x00000100 },
  { "WCSS_HM_WLANDAC_2",                           0x002c4000, 0x00000100 },
  { "WCSS_HM_A_WCSS_DBG",                          0x002d0000, 0x00020000 },
  { "WCSS_HM_A_WCSS_DBG_ROM_ROM_WCSS_DBG_DAPROM",  0x002d0000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_CSR_CSR_WCSS_DBG_CSR",     0x002d1000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_TSGEN_TSGEN_CXTSGEN",      0x002d2000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_TPDM_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D", 0x002d4000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D_SUB", 0x002d4280, 0x00000d80 },
  { "WCSS_HM_A_WCSS_DBG_TPDM_TPDM_ATB64_GPRCLK_CMB40_DSB256_CSC0E9EC9D_GPR", 0x002d4000, 0x0000027d },
  { "WCSS_HM_A_WCSS_DBG_TPDA_TPDA_TPDA_S1_W128_D8_M64_CS5CD79236", 0x002d5000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_FUN_FUN_CXATBFUNNEL_128W2SP", 0x002d6000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_ETFETB_ETFETB_CXTMC_F128W8K", 0x002d7000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_CTI0_CTI0_CSCTI",          0x002dc000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_CTI1_CTI1_CSCTI",          0x002dd000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_CTI2_CTI2_CSCTI",          0x002de000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_GPR_GPR_CXGPR_8M",         0x002ee000, 0x00001000 },
  { "WCSS_HM_A_WCSS_DBG_DSBMUX_DSBMUX_WCSS_DBG_DSBMUX", 0x002ef000, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_3",                        0x002f0000, 0x00110000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WCMN_MAC_WCMN_REG",    0x002f0000, 0x00004000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_BB_REG_MAP_T0", 0x00300000, 0x00060300 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RXB_REG_MAP_ADR80PLUS", 0x00300000, 0x00000040 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_AGC_REG_MAP_ADR80PLUS", 0x00300100, 0x00000700 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RXFE_REG_MAP_ADR80PLUS", 0x00301900, 0x00000c00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TXTD_REG_MAP_ADR80PLUS", 0x00302500, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TPC_REG_MAP_ADR80PLUS", 0x00304500, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RFCNTL_REG_MAP_ADR80PLUS", 0x00305500, 0x00000e00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_AGC1_REG_MAP_ADR80PLUS", 0x00307000, 0x00000400 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RXFE1_REG_MAP_ADR80PLUS", 0x00308800, 0x00000c00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TXTD1_REG_MAP_ADR80PLUS", 0x00309400, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TPC1_REG_MAP_ADR80PLUS", 0x0030b400, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RFCNTL1_REG_MAP_ADR80PLUS", 0x0030c400, 0x00000e00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RSFD_REG_MAP_ADR80PLUS", 0x00340500, 0x00001400 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_SM_REG_MAP_ADR80PLUS", 0x00346300, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TXBE_REG_MAP_ADR80PLUS", 0x00346500, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_RSFD1_REG_MAP_ADR80PLUS", 0x00347400, 0x00001400 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_TXBE1_REG_MAP_ADR80PLUS", 0x0034d400, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_SVD_REG_MAP_ADR80PLUS", 0x0035e000, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T0_DEC_REG_MAP_ADR80PLUS", 0x00360100, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_BB_REG_MAP_T1", 0x00380000, 0x00060300 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_RXB_REG_MAP_1RX", 0x00380000, 0x00000040 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_AGC_REG_MAP_1RX", 0x00380100, 0x00000700 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_RXFE_REG_MAP_1RX", 0x00381900, 0x00000c00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_TXTD_REG_MAP_1RX", 0x00382500, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_TPC_REG_MAP_1RX", 0x00384500, 0x00001000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_RFCNTL_REG_MAP_1RX", 0x00385500, 0x00000e00 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_RSFD_REG_MAP_1RX", 0x003c0500, 0x00001400 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_SM_REG_MAP_1RX", 0x003c6300, 0x00000200 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_TXBE_REG_MAP_1RX", 0x003c6500, 0x00000800 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_SVD_REG_MAP_1RX", 0x003de000, 0x00002000 },
  { "WCSS_HM_A_WIFI_APB_3_A_WFAC_T1_DEC_REG_MAP_1RX", 0x003e0100, 0x00000200 },
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

static HWIOModuleType HWIOModules_PIMEM[] =
{
  { NULL, 0, 0 }
};

static HWIOModuleType HWIOModules_DDR_MEM[] =
{
  { NULL, 0, 0 }
};

HWIOPhysRegionType HWIOBaseMap[] =
{
  {
    "CNOC_0_CENTER_LEFT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00021000,
    0x00001000,
    (DALSYSMemAddr)0x00021000,
    HWIOModules_CNOC_0_CENTER_LEFT_BUS_TIMEOUT
  },
  {
    "CNOC_2_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00023000,
    0x00001000,
    (DALSYSMemAddr)0x00023000,
    HWIOModules_CNOC_2_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_3_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00024000,
    0x00001000,
    (DALSYSMemAddr)0x00024000,
    HWIOModules_CNOC_3_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_2_NORTH_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00025000,
    0x00001000,
    (DALSYSMemAddr)0x00025000,
    HWIOModules_CNOC_2_NORTH_BUS_TIMEOUT
  },
  {
    "CNOC_4_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00026000,
    0x00001000,
    (DALSYSMemAddr)0x00026000,
    HWIOModules_CNOC_4_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_0_NORTH_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00027000,
    0x00001000,
    (DALSYSMemAddr)0x00027000,
    HWIOModules_CNOC_0_NORTH_BUS_TIMEOUT
  },
  {
    "CNOC_1_NORTH_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00028000,
    0x00001000,
    (DALSYSMemAddr)0x00028000,
    HWIOModules_CNOC_1_NORTH_BUS_TIMEOUT
  },
  {
    "CNOC_5_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00029000,
    0x00001000,
    (DALSYSMemAddr)0x00029000,
    HWIOModules_CNOC_5_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_1_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002a000,
    0x00001000,
    (DALSYSMemAddr)0x0002a000,
    HWIOModules_CNOC_1_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_USB2_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002b000,
    0x00001000,
    (DALSYSMemAddr)0x0002b000,
    HWIOModules_CNOC_USB2_BUS_TIMEOUT
  },
  {
    "CNOC_MM_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002c000,
    0x00001000,
    (DALSYSMemAddr)0x0002c000,
    HWIOModules_CNOC_MM_BUS_TIMEOUT
  },
  {
    "CNOC_1_CENTER_LEFT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002d000,
    0x00001000,
    (DALSYSMemAddr)0x0002d000,
    HWIOModules_CNOC_1_CENTER_LEFT_BUS_TIMEOUT
  },
  {
    "CNOC_0_SOUTH_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002e000,
    0x00001000,
    (DALSYSMemAddr)0x0002e000,
    HWIOModules_CNOC_0_SOUTH_BUS_TIMEOUT
  },
  {
    "CNOC_0_CENTER_RIGHT_BUS_TIMEOUT",
    (DALSYSMemAddr)0x0002f000,
    0x00001000,
    (DALSYSMemAddr)0x0002f000,
    HWIOModules_CNOC_0_CENTER_RIGHT_BUS_TIMEOUT
  },
  {
    "CNOC_USB3_BUS_TIMEOUT",
    (DALSYSMemAddr)0x00030000,
    0x00001000,
    (DALSYSMemAddr)0x00030000,
    HWIOModules_CNOC_USB3_BUS_TIMEOUT
  },
  {
    "CLK_CTL",
    (DALSYSMemAddr)0x00100000,
    0x000c0000,
    (DALSYSMemAddr)0x00100000,
    HWIOModules_CLK_CTL
  },
  {
    "RPM",
    (DALSYSMemAddr)0x00200000,
    0x00100000,
    (DALSYSMemAddr)0x00200000,
    HWIOModules_RPM
  },
  {
    "BOOT_ROM",
    (DALSYSMemAddr)0x00300000,
    0x00100000,
    (DALSYSMemAddr)0x00300000,
    HWIOModules_BOOT_ROM
  },
  {
    "RAMBLUR_PIMEM",
    (DALSYSMemAddr)0x00610000,
    0x00008000,
    (DALSYSMemAddr)0x00610000,
    HWIOModules_RAMBLUR_PIMEM
  },
  {
    "OCIMEM_WRAPPER_CSR",
    (DALSYSMemAddr)0x00618000,
    0x00006000,
    (DALSYSMemAddr)0x00618000,
    HWIOModules_OCIMEM_WRAPPER_CSR
  },
  {
    "SPDM_WRAPPER_TOP",
    (DALSYSMemAddr)0x00620000,
    0x00008000,
    (DALSYSMemAddr)0x00620000,
    HWIOModules_SPDM_WRAPPER_TOP
  },
  {
    "CPR3",
    (DALSYSMemAddr)0x00628000,
    0x00004000,
    (DALSYSMemAddr)0x00628000,
    HWIOModules_CPR3
  },
  {
    "MX_CPR3",
    (DALSYSMemAddr)0x0062c000,
    0x00004000,
    (DALSYSMemAddr)0x0062c000,
    HWIOModules_MX_CPR3
  },
  {
    "MSS_MPU_MSS_MPU_WRAPPER",
    (DALSYSMemAddr)0x00634000,
    0x00001800,
    (DALSYSMemAddr)0x00634000,
    HWIOModules_MSS_MPU_MSS_MPU_WRAPPER
  },
  {
    "MSS_Q6_MPU_MPU32Q2N7S1V0_16_CL36M35L12_AXI",
    (DALSYSMemAddr)0x00636000,
    0x00001800,
    (DALSYSMemAddr)0x00636000,
    HWIOModules_MSS_Q6_MPU_MPU32Q2N7S1V0_16_CL36M35L12_AXI
  },
  {
    "RPM_MSG_RAM",
    (DALSYSMemAddr)0x00778000,
    0x00008000,
    (DALSYSMemAddr)0x00778000,
    HWIOModules_RPM_MSG_RAM
  },
  {
    "SECURITY_CONTROL",
    (DALSYSMemAddr)0x00780000,
    0x00010000,
    (DALSYSMemAddr)0x00780000,
    HWIOModules_SECURITY_CONTROL
  },
  {
    "PRNG_CFG_PRNG_TOP",
    (DALSYSMemAddr)0x00790000,
    0x00010000,
    (DALSYSMemAddr)0x00790000,
    HWIOModules_PRNG_CFG_PRNG_TOP
  },
  {
    "GLM_WRAPPER",
    (DALSYSMemAddr)0x007a0000,
    0x00002000,
    (DALSYSMemAddr)0x007a0000,
    HWIOModules_GLM_WRAPPER
  },
  {
    "AHB2PHY_EAST",
    (DALSYSMemAddr)0x00ff0000,
    0x00004000,
    (DALSYSMemAddr)0x00ff0000,
    HWIOModules_AHB2PHY_EAST
  },
  {
    "DDR_SS",
    (DALSYSMemAddr)0x00ffd000,
    0x000a3000,
    (DALSYSMemAddr)0x00ffd000,
    HWIOModules_DDR_SS
  },
  {
    "MPM2_MPM",
    (DALSYSMemAddr)0x010a0000,
    0x00010000,
    (DALSYSMemAddr)0x010a0000,
    HWIOModules_MPM2_MPM
  },
  {
    "DCC_WRAPPER",
    (DALSYSMemAddr)0x010b0000,
    0x00004000,
    (DALSYSMemAddr)0x010b0000,
    HWIOModules_DCC_WRAPPER
  },
  {
    "DCC_RAM_START_ADDRESS",
    (DALSYSMemAddr)0x010b4000,
    0x00000800,
    (DALSYSMemAddr)0x010b4000,
    HWIOModules_DCC_RAM_START_ADDRESS
  },
  {
    "QM",
    (DALSYSMemAddr)0x010b8000,
    0x00004000,
    (DALSYSMemAddr)0x010b8000,
    HWIOModules_QM
  },
  {
    "QM_MPU_CFG_QM_MPU_WRAPPER",
    (DALSYSMemAddr)0x010bc000,
    0x00001200,
    (DALSYSMemAddr)0x010bc000,
    HWIOModules_QM_MPU_CFG_QM_MPU_WRAPPER
  },
  {
    "CONFIG_NOC_WRAPPER",
    (DALSYSMemAddr)0x01500000,
    0x0002a000,
    (DALSYSMemAddr)0x01500000,
    HWIOModules_CONFIG_NOC_WRAPPER
  },
  {
    "SYSTEM_NOC",
    (DALSYSMemAddr)0x01620000,
    0x0000d100,
    (DALSYSMemAddr)0x01620000,
    HWIOModules_SYSTEM_NOC
  },
  {
    "A2_NOC_AGGRE2_NOC_WRAPPER",
    (DALSYSMemAddr)0x016c0000,
    0x00062000,
    (DALSYSMemAddr)0x016c0000,
    HWIOModules_A2_NOC_AGGRE2_NOC_WRAPPER
  },
  {
    "THROTTLE_1THROTTLE_WRAPPER_2",
    (DALSYSMemAddr)0x01722000,
    0x00001000,
    (DALSYSMemAddr)0x01722000,
    HWIOModules_THROTTLE_1THROTTLE_WRAPPER_2
  },
  {
    "MMSS_NOC",
    (DALSYSMemAddr)0x01740000,
    0x0000f080,
    (DALSYSMemAddr)0x01740000,
    HWIOModules_MMSS_NOC
  },
  {
    "UFS_UFS_REGS",
    (DALSYSMemAddr)0x01da0000,
    0x00020000,
    (DALSYSMemAddr)0x01da0000,
    HWIOModules_UFS_UFS_REGS
  },
  {
    "CRYPTO0_CRYPTO_TOP",
    (DALSYSMemAddr)0x01dc0000,
    0x00040000,
    (DALSYSMemAddr)0x01dc0000,
    HWIOModules_CRYPTO0_CRYPTO_TOP
  },
  {
    "CORE_TOP_CSR",
    (DALSYSMemAddr)0x01f00000,
    0x00100000,
    (DALSYSMemAddr)0x01f00000,
    HWIOModules_CORE_TOP_CSR
  },
  {
    "TLMM",
    (DALSYSMemAddr)0x03000000,
    0x00c00000,
    (DALSYSMemAddr)0x03000000,
    HWIOModules_TLMM
  },
  {
    "MODEM_TOP",
    (DALSYSMemAddr)0x04000000,
    0x01000000,
    (DALSYSMemAddr)0x04000000,
    HWIOModules_MODEM_TOP
  },
  {
    "A5X",
    (DALSYSMemAddr)0x05000000,
    0x00075000,
    (DALSYSMemAddr)0x05000000,
    HWIOModules_A5X
  },
  {
    "LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD",
    (DALSYSMemAddr)0x05100000,
    0x00040000,
    (DALSYSMemAddr)0x05100000,
    HWIOModules_LPASS_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD
  },
  {
    "TURING_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD",
    (DALSYSMemAddr)0x05180000,
    0x00040000,
    (DALSYSMemAddr)0x05180000,
    HWIOModules_TURING_Q6_SMMU_QSMMUV2_WRAP_LPASS_Q6_STARLORD
  },
  {
    "LPASS_LPASS_CC_TOP",
    (DALSYSMemAddr)0x05240000,
    0x00013000,
    (DALSYSMemAddr)0x05240000,
    HWIOModules_LPASS_LPASS_CC_TOP
  },
  {
    "LPASS_CFG_MPU_MPU32Q2N7S1V0_10_CL36M22L12_AHB",
    (DALSYSMemAddr)0x05280000,
    0x00001500,
    (DALSYSMemAddr)0x05280000,
    HWIOModules_LPASS_CFG_MPU_MPU32Q2N7S1V0_10_CL36M22L12_AHB
  },
  {
    "LPASS_LPASS_QOS_GASKET",
    (DALSYSMemAddr)0x05282000,
    0x00002000,
    (DALSYSMemAddr)0x05282000,
    HWIOModules_LPASS_LPASS_QOS_GASKET
  },
  {
    "QDSS_SOC_DBG",
    (DALSYSMemAddr)0x06000000,
    0x02000000,
    (DALSYSMemAddr)0x06000000,
    HWIOModules_QDSS_SOC_DBG
  },
  {
    "PMIC_ARB",
    (DALSYSMemAddr)0x08000000,
    0x02800000,
    (DALSYSMemAddr)0x08000000,
    HWIOModules_PMIC_ARB
  },
  {
    "USB30_PRIM",
    (DALSYSMemAddr)0x0a800000,
    0x00200000,
    (DALSYSMemAddr)0x0a800000,
    HWIOModules_USB30_PRIM
  },
  {
    "PERIPH_SS_PDM_PERPH_WEB",
    (DALSYSMemAddr)0x0c000000,
    0x00004000,
    (DALSYSMemAddr)0x0c000000,
    HWIOModules_PERIPH_SS_PDM_PERPH_WEB
  },
  {
    "QSPI",
    (DALSYSMemAddr)0x0c004000,
    0x00001000,
    (DALSYSMemAddr)0x0c004000,
    HWIOModules_QSPI
  },
  {
    "PERIPH_SS_AHB2PHY_WEST",
    (DALSYSMemAddr)0x0c010000,
    0x00008000,
    (DALSYSMemAddr)0x0c010000,
    HWIOModules_PERIPH_SS_AHB2PHY_WEST
  },
  {
    "PERIPH_SS_SDC2_SDCC5_TOP",
    (DALSYSMemAddr)0x0c080000,
    0x00020000,
    (DALSYSMemAddr)0x0c080000,
    HWIOModules_PERIPH_SS_SDC2_SDCC5_TOP
  },
  {
    "PERIPH_SS_SDC1_SDCC5_TOP",
    (DALSYSMemAddr)0x0c0c0000,
    0x00020000,
    (DALSYSMemAddr)0x0c0c0000,
    HWIOModules_PERIPH_SS_SDC1_SDCC5_TOP
  },
  {
    "PERIPH_SS_BLSP1_BLSP_XPU3",
    (DALSYSMemAddr)0x0c140000,
    0x00040000,
    (DALSYSMemAddr)0x0c140000,
    HWIOModules_PERIPH_SS_BLSP1_BLSP_XPU3
  },
  {
    "PERIPH_SS_BLSP2_BLSP_XPU3",
    (DALSYSMemAddr)0x0c180000,
    0x00040000,
    (DALSYSMemAddr)0x0c180000,
    HWIOModules_PERIPH_SS_BLSP2_BLSP_XPU3
  },
  {
    "USB2USB20S",
    (DALSYSMemAddr)0x0c200000,
    0x00100000,
    (DALSYSMemAddr)0x0c200000,
    HWIOModules_USB2USB20S
  },
  {
    "MMSS",
    (DALSYSMemAddr)0x0c800000,
    0x00800000,
    (DALSYSMemAddr)0x0c800000,
    HWIOModules_MMSS
  },
  {
    "MODEM",
    (DALSYSMemAddr)0x10000000,
    0x02000000,
    (DALSYSMemAddr)0x10000000,
    HWIOModules_MODEM
  },
  {
    "L2_TCM",
    (DALSYSMemAddr)0x14000000,
    0x00100000,
    (DALSYSMemAddr)0x14000000,
    HWIOModules_L2_TCM
  },
  {
    "SNOC_4_BUS_TIMEOUT",
    (DALSYSMemAddr)0x14600000,
    0x00001000,
    (DALSYSMemAddr)0x14600000,
    HWIOModules_SNOC_4_BUS_TIMEOUT
  },
  {
    "SNOC_1_BUS_TIMEOUT",
    (DALSYSMemAddr)0x14601000,
    0x00001000,
    (DALSYSMemAddr)0x14601000,
    HWIOModules_SNOC_1_BUS_TIMEOUT
  },
  {
    "SNOC_3_BUS_TIMEOUT",
    (DALSYSMemAddr)0x14602000,
    0x00001000,
    (DALSYSMemAddr)0x14602000,
    HWIOModules_SNOC_3_BUS_TIMEOUT
  },
  {
    "SNOC_2_BUS_TIMEOUT",
    (DALSYSMemAddr)0x14603000,
    0x00001000,
    (DALSYSMemAddr)0x14603000,
    HWIOModules_SNOC_2_BUS_TIMEOUT
  },
  {
    "MSS_NAV_MPU_MPU32Q2N7S1V1_16_CL36M35L12_AXI",
    (DALSYSMemAddr)0x14604000,
    0x00001800,
    (DALSYSMemAddr)0x14604000,
    HWIOModules_MSS_NAV_MPU_MPU32Q2N7S1V1_16_CL36M35L12_AXI
  },
  {
    "SYSTEM_IMEM",
    (DALSYSMemAddr)0x14680000,
    0x00040000,
    (DALSYSMemAddr)0x14680000,
    HWIOModules_SYSTEM_IMEM
  },
  {
    "IPA_0_IPA_WRAPPER",
    (DALSYSMemAddr)0x14780000,
    0x00080000,
    (DALSYSMemAddr)0x14780000,
    HWIOModules_IPA_0_IPA_WRAPPER
  },
  {
    "LPASS",
    (DALSYSMemAddr)0x15000000,
    0x00c00000,
    (DALSYSMemAddr)0x15000000,
    HWIOModules_LPASS
  },
  {
    "A53SS",
    (DALSYSMemAddr)0x17800000,
    0x00800000,
    (DALSYSMemAddr)0x17800000,
    HWIOModules_A53SS
  },
  {
    "WCSS_WRAPPER",
    (DALSYSMemAddr)0x18800000,
    0x00800000,
    (DALSYSMemAddr)0x18800000,
    HWIOModules_WCSS_WRAPPER
  },
  {
    "TURING",
    (DALSYSMemAddr)0x1a000000,
    0x00800000,
    (DALSYSMemAddr)0x1a000000,
    HWIOModules_TURING
  },
  {
    "PIMEM",
    (DALSYSMemAddr)0x1c000000,
    0x04000000,
    (DALSYSMemAddr)0x1c000000,
    HWIOModules_PIMEM
  },
  {
    "DDR_MEM",
    (DALSYSMemAddr)0x80000000,
    0x100000000,
    (DALSYSMemAddr)0x80000000,
    HWIOModules_DDR_MEM
  },
  { NULL, 0, 0, 0, NULL }
};

