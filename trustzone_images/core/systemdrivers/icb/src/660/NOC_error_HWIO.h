#ifndef __NOC_ERROR_HWIO_H__
#define __NOC_ERROR_HWIO_H__
/*
===========================================================================
*/
/**
  @file NOC_error_HWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q1r63]
 
  This file contains HWIO register definitions for the following modules:
    CNOC_SERVICE_NETWORK
    MMSS_NOC
    SYSTEM_NOC
    A2_NOC_AGGRE2_NOC
    BIMC_GLOBAL1
    BIMC_S_DDR0_SCMO
    BIMC_S_DDR1_SCMO
    BIMC_S_DEFAULT_SWAY
    APCS_CCI_GLADIATOR
    GCC_CLK_CTL_REG

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
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

  $Header: //components/rel/core.tz/1.0.7.1/systemdrivers/icb/src/660/NOC_error_HWIO.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: CNOC_SERVICE_NETWORK
 *--------------------------------------------------------------------------*/

#define CNOC_SERVICE_NETWORK_REG_BASE  (CONFIG_NOC_WRAPPER_BASE + 0x00000000)

#define HWIO_CNOC_OBS_ID_COREID_ADDR   (CNOC_SERVICE_NETWORK_REG_BASE + 0x00000000)
#define HWIO_CNOC_SBM_ID_COREID_ADDR   (CNOC_SERVICE_NETWORK_REG_BASE + 0x00000100)
/*----------------------------------------------------------------------------
 * MODULE: MMSS_NOC
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_REG_BASE              (MMSS_NOC_BASE + 0x00000000)

#define HWIO_MNOC_OBS_ID_COREID_ADDR   (MMSS_NOC_REG_BASE + 0x00000000)
#define HWIO_MNOC_SBM_ID_COREID_ADDR   (MMSS_NOC_REG_BASE + 0x00000100)

/*----------------------------------------------------------------------------
 * MODULE: SYSTEM_NOC
 *--------------------------------------------------------------------------*/

#define SYSTEM_NOC_REG_BASE            (SYSTEM_NOC_BASE + 0x00000000)

#define HWIO_SNOC_OBS_ID_COREID_ADDR   (SYSTEM_NOC_REG_BASE + 0x00000000)
#define HWIO_SNOC_SBM_ID_COREID_ADDR   (SYSTEM_NOC_REG_BASE + 0x00000100)

/*----------------------------------------------------------------------------
 * MODULE: A2_NOC_AGGRE2_NOC
 *--------------------------------------------------------------------------*/

#define A2_NOC_AGGRE2_NOC_REG_BASE     (A2_NOC_AGGRE2_NOC_WRAPPER_BASE + 0x00040000)

#define HWIO_A2_NOC_AGGRE2NOC_OBS_ID_COREID_ADDR  (A2_NOC_AGGRE2_NOC_REG_BASE + 0x00000000)
#define HWIO_A2_NOC_AGGRE2NOC_SBM_ID_COREID_ADDR  (A2_NOC_AGGRE2_NOC_REG_BASE + 0x00000100)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_GLOBAL1
 *--------------------------------------------------------------------------*/

#define BIMC_GLOBAL1_REG_BASE                                                   (DDR_SS_BASE      + 0x00004000)

#define HWIO_BIMC_BRIC_INTERRUPT_0_STATUS_0_ADDR                                (BIMC_GLOBAL1_REG_BASE      + 0x00000100)

#define HWIO_BIMC_BRIC_INTERRUPT_0_STATUS_1_ADDR                                (BIMC_GLOBAL1_REG_BASE      + 0x00000110)

#define HWIO_BIMC_BRIC_INTERRUPT_0_STATUS_2_ADDR                                (BIMC_GLOBAL1_REG_BASE      + 0x00000120)

#define HWIO_BIMC_BRIC_INTERRUPT_0_STATUS_3_ADDR                                (BIMC_GLOBAL1_REG_BASE      + 0x00000130)

#define HWIO_BIMC_BRIC_INTERRUPT_0_STATUS_4_ADDR                                (BIMC_GLOBAL1_REG_BASE      + 0x00000140)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR0_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR0_SCMO_REG_BASE                                                    (DDR_SS_BASE      + 0x00033000)

#define HWIO_BIMC_S_DDR0_SCMO_INTERRUPT_STATUS_ADDR                                  (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR_ADDR                                         (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_ADDR1_ADDR                                        (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_0_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_1_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR0_SCMO_ESYN_APACKET_2_ADDR                                    (BIMC_S_DDR0_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DDR1_SCMO
 *--------------------------------------------------------------------------*/

#define BIMC_S_DDR1_SCMO_REG_BASE                                                    (DDR_SS_BASE      + 0x0003f000)

#define HWIO_BIMC_S_DDR1_SCMO_INTERRUPT_STATUS_ADDR                                  (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR_ADDR                                         (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000120)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_ADDR1_ADDR                                        (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000124)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_0_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000128)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_1_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x0000012c)

#define HWIO_BIMC_S_DDR1_SCMO_ESYN_APACKET_2_ADDR                                    (BIMC_S_DDR1_SCMO_REG_BASE      + 0x00000130)

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_DEFAULT_SWAY
 *--------------------------------------------------------------------------*/

#define BIMC_S_DEFAULT_SWAY_REG_BASE                                                   (DDR_SS_BASE      + 0x0005b000)

#define HWIO_BIMC_S_DEFAULT_SWAY_INTERRUPT_STATUS_ADDR                                 (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000100)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_0_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000400)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_1_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000410)

#define HWIO_BIMC_S_DEFAULT_SWAY_DEFAULT_SLAVE_STATUS_2_ADDR                           (BIMC_S_DEFAULT_SWAY_REG_BASE      + 0x00000420)

/*----------------------------------------------------------------------------
 * MODULE: APCS_CCI_GLADIATOR
 *--------------------------------------------------------------------------*/

#define APCS_CCI_GLADIATOR_REG_BASE                                                                            (A53SS_BASE      + 0x00100000)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRVLD_ADDR                                                        (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001014)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG0_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x0000101c)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG1_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001020)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG2_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001024)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG3_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001028)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG4_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x0000102c)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG5_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001030)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG6_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x00001034)

#define HWIO_APCS_CCI_GLADIATOR_MAIN_CRIXUS_ERRLOG8_ADDR                                                       (APCS_CCI_GLADIATOR_REG_BASE      + 0x0000103c)


/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                 (CLK_CTL_BASE      + 0x00000000)

#define HWIO_GCC_SNOC_BUS_TIMEOUT_EXTREF_CTL_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x00049024)

#define HWIO_GCC_CNOC_BUS_TIMEOUT_EXTREF_CTL_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x0008003c)


#endif /* __NOC_ERROR_HWIO_H__ */
