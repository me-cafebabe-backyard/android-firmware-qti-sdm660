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

  $Header: //components/rel/rpm.bf/1.8/core/api/systemdrivers/hwio/sdm660/msmhwiobase.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: RPM
 *--------------------------------------------------------------------------*/

#define RPM_BASE                                                    0x00000000
#define RPM_BASE_SIZE                                               0x00100000
#define RPM_BASE_PHYS                                               0x00000000

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0x60100000
#define CLK_CTL_BASE_SIZE                                           0x000b7000
#define CLK_CTL_BASE_PHYS                                           0x60100000

/*----------------------------------------------------------------------------
 * BASE: RPM_CODE_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_CODE_RAM_START_ADDRESS_BASE                             0x60200000
#define RPM_CODE_RAM_START_ADDRESS_BASE_SIZE                        0x00000000
#define RPM_CODE_RAM_START_ADDRESS_BASE_PHYS                        0x60200000

/*----------------------------------------------------------------------------
 * BASE: RPM_CODE_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_CODE_RAM_END_ADDRESS_BASE                               0x60227fff
#define RPM_CODE_RAM_END_ADDRESS_BASE_SIZE                          0x00000000
#define RPM_CODE_RAM_END_ADDRESS_BASE_PHYS                          0x60227fff

/*----------------------------------------------------------------------------
 * BASE: SPDM_WRAPPER_TOP
 *--------------------------------------------------------------------------*/

#define SPDM_WRAPPER_TOP_BASE                                       0x60620000
#define SPDM_WRAPPER_TOP_BASE_SIZE                                  0x00008000
#define SPDM_WRAPPER_TOP_BASE_PHYS                                  0x60620000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_START_ADDRESS_BASE                           0x60778000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_SIZE                      0x00000000
#define RPM_SS_MSG_RAM_START_ADDRESS_BASE_PHYS                      0x60778000

/*----------------------------------------------------------------------------
 * BASE: RPM_MSG_RAM
 *--------------------------------------------------------------------------*/

#define RPM_MSG_RAM_BASE                                            0x60778000
#define RPM_MSG_RAM_BASE_SIZE                                       0x00007000
#define RPM_MSG_RAM_BASE_PHYS                                       0x60778000

/*----------------------------------------------------------------------------
 * BASE: RPM_SS_MSG_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define RPM_SS_MSG_RAM_END_ADDRESS_BASE                             0x6077efff
#define RPM_SS_MSG_RAM_END_ADDRESS_BASE_SIZE                        0x00000000
#define RPM_SS_MSG_RAM_END_ADDRESS_BASE_PHYS                        0x6077efff

/*----------------------------------------------------------------------------
 * BASE: SECURITY_CONTROL
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_BASE                                       0x60780000
#define SECURITY_CONTROL_BASE_SIZE                                  0x00010000
#define SECURITY_CONTROL_BASE_PHYS                                  0x60780000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_EAST
 *--------------------------------------------------------------------------*/

#define AHB2PHY_EAST_BASE                                           0x60ff0000
#define AHB2PHY_EAST_BASE_SIZE                                      0x00004000
#define AHB2PHY_EAST_BASE_PHYS                                      0x60ff0000

/*----------------------------------------------------------------------------
 * BASE: DDR_SS
 *--------------------------------------------------------------------------*/

#define DDR_SS_BASE                                                 0x60ffd000
#define DDR_SS_BASE_SIZE                                            0x000a3000
#define DDR_SS_BASE_PHYS                                            0x60ffd000

/*----------------------------------------------------------------------------
 * BASE: MPM2_MPM
 *--------------------------------------------------------------------------*/

#define MPM2_MPM_BASE                                               0x610a0000
#define MPM2_MPM_BASE_SIZE                                          0x00010000
#define MPM2_MPM_BASE_PHYS                                          0x610a0000

/*----------------------------------------------------------------------------
 * BASE: CONFIG_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define CONFIG_NOC_WRAPPER_BASE                                     0x61500000
#define CONFIG_NOC_WRAPPER_BASE_SIZE                                0x0002a000
#define CONFIG_NOC_WRAPPER_BASE_PHYS                                0x61500000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_NOC
 *--------------------------------------------------------------------------*/

#define SYSTEM_NOC_BASE                                             0x61620000
#define SYSTEM_NOC_BASE_SIZE                                        0x0000e000
#define SYSTEM_NOC_BASE_PHYS                                        0x61620000

/*----------------------------------------------------------------------------
 * BASE: A2_NOC_AGGRE2_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE                              0x616c0000
#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE_SIZE                         0x00062000
#define A2_NOC_AGGRE2_NOC_WRAPPER_BASE_PHYS                         0x616c0000

/*----------------------------------------------------------------------------
 * BASE: CRYPTO0_CRYPTO_TOP
 *--------------------------------------------------------------------------*/

#define CRYPTO0_CRYPTO_TOP_BASE                                     0x61dc0000
#define CRYPTO0_CRYPTO_TOP_BASE_SIZE                                0x00040000
#define CRYPTO0_CRYPTO_TOP_BASE_PHYS                                0x61dc0000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0x61f00000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x61f00000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0x63000000
#define TLMM_BASE_SIZE                                              0x00c00000
#define TLMM_BASE_PHYS                                              0x63000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_SOC_DBG
 *--------------------------------------------------------------------------*/

#define QDSS_SOC_DBG_BASE                                           0x66000000
#define QDSS_SOC_DBG_BASE_SIZE                                      0x02000000
#define QDSS_SOC_DBG_BASE_PHYS                                      0x66000000

/*----------------------------------------------------------------------------
 * BASE: PMIC_ARB
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_BASE                                               0x68000000
#define PMIC_ARB_BASE_SIZE                                          0x02608000
#define PMIC_ARB_BASE_PHYS                                          0x68000000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_AHB2PHY_WEST
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_AHB2PHY_WEST_BASE                                 0x6c010000
#define PERIPH_SS_AHB2PHY_WEST_BASE_SIZE                            0x00008000
#define PERIPH_SS_AHB2PHY_WEST_BASE_PHYS                            0x6c010000

/*----------------------------------------------------------------------------
 * BASE: MMSS
 *--------------------------------------------------------------------------*/

#define MMSS_BASE                                                   0x6c800000
#define MMSS_BASE_SIZE                                              0x00800000
#define MMSS_BASE_PHYS                                              0x6c800000

/*----------------------------------------------------------------------------
 * BASE: IPA_0_IPA_WRAPPER
 *--------------------------------------------------------------------------*/

#define IPA_0_IPA_WRAPPER_BASE                                      0x74780000
#define IPA_0_IPA_WRAPPER_BASE_SIZE                                 0x00100000
#define IPA_0_IPA_WRAPPER_BASE_PHYS                                 0x74780000

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                  0x75000000
#define LPASS_BASE_SIZE                                             0x00800000
#define LPASS_BASE_PHYS                                             0x75000000


#endif /* __MSMHWIOBASE_H__ */
