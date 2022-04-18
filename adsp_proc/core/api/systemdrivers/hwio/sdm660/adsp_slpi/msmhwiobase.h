#ifndef __MSMHWIOBASE_H__
#define __MSMHWIOBASE_H__
/*
===========================================================================
*/
/**
  @file msmhwiobase.h
  @brief Auto-generated HWIO base include file.
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

  $Header: //components/rel/core.qdsp6/1.0.c2/api/systemdrivers/hwio/sdm660/adsp_slpi/msmhwiobase.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0xe0000000
#define CLK_CTL_BASE_SIZE                                           0x000c0000
#define CLK_CTL_BASE_PHYS                                           0x00100000

/*----------------------------------------------------------------------------
 * BASE: RPM
 *--------------------------------------------------------------------------*/

#define RPM_BASE                                                    0xe0100000
#define RPM_BASE_SIZE                                               0x00100000
#define RPM_BASE_PHYS                                               0x00200000

/*----------------------------------------------------------------------------
 * BASE: SPDM_WRAPPER_TOP
 *--------------------------------------------------------------------------*/

#define SPDM_WRAPPER_TOP_BASE                                       0xe0220000
#define SPDM_WRAPPER_TOP_BASE_SIZE                                  0x00008000
#define SPDM_WRAPPER_TOP_BASE_PHYS                                  0x00620000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_START_ADDRESS_BASE                           0xe0378000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_SIZE                      0x00007000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_PHYS                      0x00778000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_END_ADDRESS_BASE_PHYS                        0x0077efff

/*----------------------------------------------------------------------------
 * BASE: SECURITY_CONTROL
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_BASE                                       0xe0480000
#define SECURITY_CONTROL_BASE_SIZE                                  0x00010000
#define SECURITY_CONTROL_BASE_PHYS                                  0x00780000

/*----------------------------------------------------------------------------
 * BASE: PRNG_CFG_PRNG_TOP
 *--------------------------------------------------------------------------*/

#define PRNG_CFG_PRNG_TOP_BASE                                      0xe0590000
#define PRNG_CFG_PRNG_TOP_BASE_SIZE                                 0x00010000
#define PRNG_CFG_PRNG_TOP_BASE_PHYS                                 0x00790000

/*----------------------------------------------------------------------------
 * BASE: MPM2_MPM
 *--------------------------------------------------------------------------*/

#define MPM2_MPM_BASE                                               0xe06a0000
#define MPM2_MPM_BASE_SIZE                                          0x00010000
#define MPM2_MPM_BASE_PHYS                                          0x010a0000

/*----------------------------------------------------------------------------
 * BASE: CONFIG_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define CONFIG_NOC_WRAPPER_BASE                                     0xe0700000
#define CONFIG_NOC_WRAPPER_BASE_SIZE                                0x0002a000
#define CONFIG_NOC_WRAPPER_BASE_PHYS                                0x01500000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_NOC
 *--------------------------------------------------------------------------*/

#define SYSTEM_NOC_BASE                                             0xe0820000
#define SYSTEM_NOC_BASE_SIZE                                        0x0000d100
#define SYSTEM_NOC_BASE_PHYS                                        0x01620000

/*----------------------------------------------------------------------------
 * BASE: A2_NOC_AGGRE2_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE                              0xe0ec0000
#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE_SIZE                         0x00062000
#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE_PHYS                         0x016c0000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0xe1000000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x01f00000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0xe2000000
#define TLMM_BASE_SIZE                                              0x00c00000
#define TLMM_BASE_PHYS                                              0x03000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_SOC_DBG
 *--------------------------------------------------------------------------*/

#define QDSS_SOC_DBG_BASE                                           0xe3000000
#define QDSS_SOC_DBG_BASE_SIZE                                      0x02000000
#define QDSS_SOC_DBG_BASE_PHYS                                      0x06000000

/*----------------------------------------------------------------------------
 * BASE: PMIC_ARB
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_BASE                                               0xe5000000
#define PMIC_ARB_BASE_SIZE                                          0x02800000
#define PMIC_ARB_BASE_PHYS                                          0x08000000

/*----------------------------------------------------------------------------
 * BASE: USB30_PRIM
 *--------------------------------------------------------------------------*/

#define USB30_PRIM_BASE                                             0xe8000000
#define USB30_PRIM_BASE_SIZE                                        0x00200000
#define USB30_PRIM_BASE_PHYS                                        0x0a800000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_PDM_PERPH_WEB
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_PDM_PERPH_WEB_BASE                                0xe8400000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_SIZE                           0x00004000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_PHYS                           0x0c000000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_AHB2PHY_WEST
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_AHB2PHY_WEST_BASE                                 0xe8510000
#define PERIPH_SS_AHB2PHY_WEST_BASE_SIZE                            0x00008000
#define PERIPH_SS_AHB2PHY_WEST_BASE_PHYS                            0x0c010000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC2_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC2_SDCC5_TOP_BASE                               0xe8680000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_PHYS                          0x0c080000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC1_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC1_SDCC5_TOP_BASE                               0xe87c0000
#define PERIPH_SS_SDC1_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC1_SDCC5_TOP_BASE_PHYS                          0x0c0c0000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_BLSP1_BLSP_XPU3
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_BLSP1_BLSP_XPU3_BASE                              0xe8840000
#define PERIPH_SS_BLSP1_BLSP_XPU3_BASE_SIZE                         0x00040000
#define PERIPH_SS_BLSP1_BLSP_XPU3_BASE_PHYS                         0x0c140000

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                  0xee000000
#define LPASS_BASE_SIZE                                             0x00c00000
#define LPASS_BASE_PHYS                                             0x15000000


#endif /* __MSMHWIOBASE_H__ */
