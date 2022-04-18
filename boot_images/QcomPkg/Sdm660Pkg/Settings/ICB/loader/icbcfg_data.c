/*==============================================================================

FILE:      icbcfg_data.c

DESCRIPTION: This file implements the ICB Configuration driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/ICB/loader/icbcfg_data.c#9 $ 
$DateTime: 2017/03/20 23:41:17 $
$Author: pwbldsvc $
$Change: 12770453 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2016/11/30  pra    Remove OCMEM workaround, as POR value of OCIMEM_GEN_CTL for SDM660 is 0x00180000
2016/06/21  pra    Add SDM660 support
2016/03/31  sds    Add 8997 support
2016/03/14  sds    Settings recommendation update
2015/11/05  sds    Settings recommendation due to QCTDD02644034:
                   BIMC redirect for RICISH/RICOSH only.
2015/10/27  sds    After verification on RUMI, additional enable required.
2015/10/20  sds    Add initial QM config
2015/10/12  sds    SW workaround for QCTDD02523582:
                   OCIMEM exclusive granularity -> 64B
2015/08/24  sds    Created
 
           Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
                        All Rights Reserved.
                     QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg.h"
#include "icbcfg_hwio.h"
#include "../../../../Library/ICBLib/icbcfgi.h"
#include "../../../../Library/ICBLib/HALbimc.h"
#include "../../../../Library/ICBLib/HALbimcHwioGeneric.h"

/*---------------------------------------------------------------------------*/
/*          Macro and constant definitions                                   */
/*---------------------------------------------------------------------------*/
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

/* DDR slave indexes */
#define SLAVE_DDR_CH0 0
#define SLAVE_DDR_CH1 1

#define BIMC_S_DDR_ARB_REG_BASE(b)  ((b)      + 0x00031000)
#define BIMC_S_DDR_ARB_MODE_ADDR(b,n)   (BIMC_S_DDR_ARB_REG_BASE(b) + (0xC000 * (n)) + 0x00000210)

#define DDR_ARB_MODE(slave,mode) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_S_DDR_ARB_MODE_ADDR((uint8_t *)BIMC_BASE,slave), \
   BIMC_S_ARB_MODE_RMSK, \
   BIMC_S_ARB_MODE_RMSK, \
   (mode) }

#define MPORT_MODE(master,mode) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_MODE_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_MODE_RMSK, \
   BIMC_M_MODE_RMSK, \
   (mode) }

#define MPORT_BKE_ENABLE(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE_ENABLE_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE_ENABLE_RMSK, \
   BIMC_M_BKE_ENABLE_RMSK, \
   (value) }

#define MPORT_BKE1_ENABLE(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE1_ENABLE_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE1_ENABLE_RMSK, \
   BIMC_M_BKE1_ENABLE_RMSK, \
   (value) }

#define MPORT_BKE2_ENABLE(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE2_ENABLE_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE2_ENABLE_RMSK, \
   BIMC_M_BKE2_ENABLE_RMSK, \
   (value) }

#define MPORT_BKE3_ENABLE(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_ENABLE_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_ENABLE_RMSK, \
   BIMC_M_BKE3_ENABLE_RMSK, \
   (value) }

#define MPORT_BKE3_GRANT_PERIOD(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_GRANT_PERIOD_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_GRANT_PERIOD_RMSK, \
   BIMC_M_BKE3_GRANT_PERIOD_RMSK, \
   (value) }

#define MPORT_BKE3_GRANT_COUNT(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_GRANT_COUNT_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_GRANT_COUNT_RMSK, \
   BIMC_M_BKE3_GRANT_COUNT_RMSK, \
   (value) }

#define MPORT_BKE3_THRESHOLD_MEDIUM(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_THRESHOLD_MEDIUM_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_THRESHOLD_MEDIUM_RMSK, \
   BIMC_M_BKE3_THRESHOLD_MEDIUM_RMSK, \
   (value) }

#define MPORT_BKE3_THRESHOLD_LOW(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_THRESHOLD_LOW_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_THRESHOLD_LOW_RMSK, \
   BIMC_M_BKE3_THRESHOLD_LOW_RMSK, \
   (value) }

#define MPORT_BKE3_HEALTH_0(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_BKE3_HEALTH_0_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_BKE3_HEALTH_0_RMSK, \
   BIMC_M_BKE3_HEALTH_0_RMSK, \
   (value) }

#define MPORT_REDIRECT_CTRL(master, value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_REDIRECT_CTRL_ADDR((uint8_t *)BIMC_BASE,master), \
   BIMC_M_REDIRECT_CTRL_RMSK, \
   BIMC_M_REDIRECT_CTRL_RMSK, \
   (value) }

 #define MPORT_PIPE0_GATHERING(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_PIPE0_GATHERING_ADDR(BIMC_BASE, master), \
   BIMC_M_PIPE0_GATHERING_RMSK, \
   BIMC_M_PIPE0_GATHERING_RMSK, \
   (value) }
 
 #define MPORT_PIPE1_GATHERING(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_PIPE1_GATHERING_ADDR(BIMC_BASE, master), \
   BIMC_M_PIPE1_GATHERING_RMSK, \
   BIMC_M_PIPE1_GATHERING_RMSK, \
   (value) }
 
 #define MPORT_PIPE2_GATHERING(master,value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_M_PIPE2_GATHERING_ADDR(BIMC_BASE, master), \
   BIMC_M_PIPE2_GATHERING_RMSK, \
   BIMC_M_PIPE2_GATHERING_RMSK, \
   (value) }

/* Master indexes */
#define MASTER_APP   0
#define MASTER_GPU   1
#define MASTER_MMSS  2
#define MASTER_SYS   3
#define MASTER_PIMEM 4
#define MASTER_MDSP  5
#define MASTER_CDSP  6


#define DT_AGG_REQ_CFG(n, value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_DT_AGG_REQ_CFG_n_ADDR(BIMC_BASE, n), \
   BIMC_DT_AGG_REQ_CFG_n_RMSK, \
   BIMC_DT_AGG_REQ_CFG_n_RMSK, \
   (value) }

#define BIMC_BRIC_MSA_LOCKS_ADDR(b)      (BIMC_GLOBAL1_REG_BASE(b) + 0x0300)
#define BIMC_BRIC_PROTNS_LOCKS_ADDR(b)   (BIMC_GLOBAL1_REG_BASE(b) + 0x0310)

#define BRIC_MSA_LOCKS(value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_BRIC_MSA_LOCKS_ADDR((uint8_t *)BIMC_BASE), \
   (value), \
   0xffffffff, \
   (value) }

#define BRIC_PROTNS_LOCKS(value) \
  {ICBCFG_32_BIT_REG, \
   (void *)BIMC_BRIC_PROTNS_LOCKS_ADDR((uint8_t *)BIMC_BASE), \
   (value), \
   0xffffffff, \
   (value) }

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/*---------------------------------------------------------------------------*/
/*          Properties data for device ID  = "icbcfg/boot"                   */
/*---------------------------------------------------------------------------*/

/* ICBcfg Boot Configuration Data*/
/*---------------------------------------------------------------------------*/
/* SDM660 v1                                                                */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_boot_data_v1[] = 
{

#if 1
  /* DSAT core registers */
  ICBCFG_HWIOF_DW(GCC_MMSS_QM_CORE_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_MMSS_QM_CORE_CBCR, CLK_OFF, 0x0),
  ICBCFG_HWIOF_DW(GCC_MMSS_QM_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_MMSS_QM_AHB_CBCR, CLK_OFF, 0x0),
  ICBCFG_HWIO_DW(QM_CORE_CLK_CGC_CNTRL, 0x1),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_0, 0x60),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_1, 0x27),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_2, 0x27),
  ICBCFG_HWIO_DW(QM_PRE_STALL_TIMEOUT_CNT_URG_3, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_0, 0x60),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_1, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_2, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_TIMEOUT_CNT_URG_3, 0x27),
  ICBCFG_HWIO_DW(QM_POST_STALL_WDW_OVERLAP_CNTL, 0x1),
  
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_CNTRL, 7, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL, 7, 0x1),
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_CNTRL, 8, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL, 8, 0x1),
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_CNTRL, 9, 0x3),
  ICBCFG_HWIOI_DW(QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL, 9, 0x1),
  ICBCFG_HWIO_DW(QM_DSP_DANGER_AGGR_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_DSP_DANGER_AGGR_MODEM_CNTRL, 0x1),
//  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_AGGR_CNTRL, 0x80000003),
//  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL, 0x0),
//  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_OUTPUT, 0xAAAAA0),
  ICBCFG_HWIO_DW(QM_DSP_SYSTEM_DANGER_OUTPUT_EN, 0x0),
  ICBCFG_HWIO_DW(QM_DSP_PRIORITY_MODE_SEL, 0x0),

  ICBCFG_HWIO_DW(QM_THROTTLE_LEVEL_LEGACY_SELECT, 0x0),
  ICBCFG_HWIOI_DW(QM_THROTTLE_LEVEL_QOS_n, 1, 0x7FC),
  ICBCFG_HWIOI_DW(QM_THROTTLE_LEVEL_QOS_n, 2, 0x7FC),
  ICBCFG_HWIOI_DW(QM_THROTTLE_LEVEL_QOS_n, 3, 0x80FC),
  ICBCFG_HWIOI_DW(QM_THROTTLE_LEVEL_QOS_n, 4, 0x7FC),

  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 7, 1, 0),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 7, 2, 0xEE000081),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 7, 3, 0xEA000082),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 7, 4, 0xEE000003),
  ICBCFG_HWIOFI_DW(QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN, 7, THROTTLE_LEVEL_EN, 0x1),
  
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 8, 1, 0xEE000001),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 8, 2, 0xEE000002),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 8, 3, 0xEE000003),
  ICBCFG_HWIOFI_DW(QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN, 8, THROTTLE_LEVEL_EN, 0x1),

  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 9, 1, 0xEE000001),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 9, 2, 0xEE000002),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 9, 3, 0xEE000003),
  ICBCFG_HWIOFI_DW(QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN, 9, THROTTLE_LEVEL_EN, 0x1),
  
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 10, 1, 0xEE000001),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 10, 2, 0xEE000002),
  ICBCFG_HWIOI2_DW(QM_CLNT_m_THROTTLE_LEVEL_QOS_n, 10, 3, 0xEE000003),
  ICBCFG_HWIOFI_DW(QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN, 10, THROTTLE_LEVEL_EN, 0x1),

  ICBCFG_HWIOF_READ_DW(BIMC_DDR_CH0_CLK_PERIOD,PERIOD),
  ICBCFG_HWIOF_WRITE_DW(QM_PERIOD_BUS_CFG,PERIOD_BUS_SW),
  ICBCFG_HWIOF_DW(QM_PERIOD_BUS_CFG, PERIOD_BUS_LOAD_SW, 0x1),
  ICBCFG_HWIOF_DW(QM_PERIOD_BUS_CFG, PERIOD_BUS_SW_OVERRIDE, 0x0),
  ICBCFG_HWIOI_DW(QOS_FREQ_BAND_BNDRY_n, 0, 0x97B),
  ICBCFG_HWIOI_DW(QOS_FREQ_BAND_BNDRY_n, 1, 0x0),
  ICBCFG_HWIOI_DW(QOS_FREQ_BAND_BNDRY_n, 2, 0x0),
  ICBCFG_HWIO_DW(QM_AGGR_SAFE_OVERRIDE_CNTRL, 0x1),
  ICBCFG_HWIO_DW(QM_DSP_SAFE_MASK_CNTRL, 0x3),
  ICBCFG_HWIO_DW(QM_DANGER_SAFE_CNTRL,0x1),
  
  /* MMSS NOC AHB enable */
  ICBCFG_HWIOF_DW(GCC_MMSS_NOC_CFG_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_WAIT_HWIOF_DW(GCC_MMSS_NOC_CFG_AHB_CBCR, CLK_OFF, 0x0),

  /* VENUS throttle related registers */
  ICBCFG_HWIOF_DW(MMSS_VIDEO_TOP_GDSCR, SW_COLLAPSE, 0x0),
  ICBCFG_WAIT_HWIOF_DW(MMSS_VIDEO_TOP_GDSCR, PWR_ON, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_VIDEO_CXO_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_VIDEO_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_VIDEO_AXI_CBCR, CLK_ENABLE, 0x1),

  /* VFE throttle related registers */
  ICBCFG_HWIOF_DW(MMSS_CAMSS_TOP_GDSCR, SW_COLLAPSE, 0x0),
  ICBCFG_WAIT_HWIOF_DW(MMSS_CAMSS_TOP_GDSCR, PWR_ON, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_CAMSS_CXO_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_CAMSS_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_CAMSS_AXI_CBCR, CLK_ENABLE, 0x1),

  /* MDP throttle related registers */
  ICBCFG_HWIOF_DW(MMSS_MDSS_GDSCR, SW_COLLAPSE, 0x0),
  ICBCFG_WAIT_HWIOF_DW(MMSS_MDSS_GDSCR, PWR_ON, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_MDSS_CXO_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_MDSS_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(MMSS_THROTTLE_MDSS_AXI_CBCR, CLK_ENABLE, 0x1),
#if 1
  /* LPASS throttle related registers */
  ICBCFG_HWIOF_DW(GCC_LPASS_SWAY_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(GCC_LPASS_Q6_AXI_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(GCC_LPASS_Q6_SMMU_AHB_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(GCC_LPASS_CNOC_CFG_CBCR, CLK_ENABLE, 0x1),
  ICBCFG_HWIOF_DW(LPASS_TCSR_QOS_CTL, QOS_ENABLE, 0x1),

  ICBCFG_HWIOF_DW(LPASS_QOS_GASKET_CGC_CNTRL, THROTTLE_CGC_EN, 0x1),
  ICBCFG_HWIOF_DW(LPASS_QOS_GASKET_GRANT_PERIOD, GRANT_PERIOD, 0x3e8),
  ICBCFG_HWIO_DW(LPASS_QOS_GASKET_THRESHOLD_03, 0x0000FFFF),
  ICBCFG_HWIO_DW(LPASS_QOS_GASKET_THRESHOLD_02, 0xFFFF2710),
  ICBCFG_HWIO_DW(LPASS_QOS_GASKET_THRESHOLD_01, 0x0BB80BB8),
  ICBCFG_HWIO_DW(LPASS_QOS_GASKET_THRESHOLD_00, 0x0BB80BB8),
  ICBCFG_HWIOF_DW(LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT, PEAK_ACCUM_CREDIT, 0x100),  
  ICBCFG_HWIO_DW(LPASS_QOS_GASKET_CNTRL, 0xF801),
#endif
#endif
  /* BIMC DT/QOS aggregator */
  DT_AGG_REQ_CFG(0, 0x500),
  DT_AGG_REQ_CFG(2, 0x500),

  /* Danger BKE configuration, AP master port */
  MPORT_BKE3_GRANT_PERIOD(MASTER_APP, 0x14),
  MPORT_BKE3_GRANT_COUNT(MASTER_APP, 0x64),
  MPORT_BKE3_THRESHOLD_MEDIUM(MASTER_APP, 0xFFCE),
  MPORT_BKE3_THRESHOLD_LOW(MASTER_APP, 0xFF9C),
  MPORT_BKE3_HEALTH_0(MASTER_APP, 0x80000000),
  MPORT_BKE_ENABLE(MASTER_APP, 0x010F0000),
  MPORT_BKE1_ENABLE(MASTER_APP, 0x02000000),
  MPORT_BKE2_ENABLE(MASTER_APP, 0x04000000),
  MPORT_BKE3_ENABLE(MASTER_APP, 0xF8000001),

  /* Danger BKE configuration, GPU master port */
  MPORT_BKE3_GRANT_PERIOD(MASTER_GPU, 0x14),
  MPORT_BKE3_GRANT_COUNT(MASTER_GPU, 0x64),
  MPORT_BKE3_THRESHOLD_MEDIUM(MASTER_GPU, 0xFFCE),
  MPORT_BKE3_THRESHOLD_LOW(MASTER_GPU, 0xFF9C),
  MPORT_BKE3_HEALTH_0(MASTER_GPU, 0x80000000),
  MPORT_BKE_ENABLE(MASTER_GPU, 0x030F0000),
  MPORT_BKE2_ENABLE(MASTER_GPU, 0x04000000),
  MPORT_BKE3_ENABLE(MASTER_GPU, 0xF8000001),

  MPORT_BKE3_GRANT_PERIOD(MASTER_CDSP, 0x14),
  MPORT_BKE3_GRANT_COUNT(MASTER_CDSP, 0x64),
  MPORT_BKE3_THRESHOLD_MEDIUM(MASTER_CDSP, 0xFFCE),
  MPORT_BKE3_THRESHOLD_LOW(MASTER_CDSP, 0xFF9C),
  MPORT_BKE3_HEALTH_0(MASTER_CDSP, 0x80000000),
  MPORT_BKE_ENABLE(MASTER_CDSP, 0x030F0000),
  MPORT_BKE2_ENABLE(MASTER_CDSP, 0x04000000),
  MPORT_BKE3_ENABLE(MASTER_CDSP, 0xF8000001),

  /* Enable redirect for some master ports.
   * Only enable RICISH/RICOSH as required by QCTDD02644034. */
  MPORT_REDIRECT_CTRL(MASTER_GPU,  0xFF0),
  MPORT_REDIRECT_CTRL(MASTER_MMSS, 0xFF0),
  MPORT_REDIRECT_CTRL(MASTER_SYS,  0x60),
  MPORT_REDIRECT_CTRL(MASTER_MDSP, 0xFF0),
  MPORT_REDIRECT_CTRL(MASTER_CDSP, 0xFF0),

  MPORT_PIPE0_GATHERING(MASTER_SYS,0x00060000),
  MPORT_PIPE1_GATHERING(MASTER_SYS,0x00060000),
  MPORT_PIPE2_GATHERING(MASTER_APP,0x0000000f),
  MPORT_PIPE2_GATHERING(MASTER_SYS,0x00060000),
  
  /* DDR slaveway config */
  DDR_ARB_MODE(SLAVE_DDR_CH0, 0x10000001), 
  DDR_ARB_MODE(SLAVE_DDR_CH1, 0x10000001), 
};

icbcfg_prop_type icbcfg_boot_prop_v1 = 
{
    /* Length of the config  data array */
    ARRAY_SIZE(icbcfg_boot_data_v1),
    /* Pointer to config data array */ 
    icbcfg_boot_data_v1                                    
};

icbcfg_data_type icbcfg_boot_post_data_v1[] = 
{
    ICBCFG_HWIO_DW(BIMC_BRIC_REDIRECT_MSTR_EN, 0x002E002E),
    ICBCFG_HWIO_DW(BIMC_BRIC_REDIRECT_CTRL, 0x82000100),

    BRIC_MSA_LOCKS(0x00008000),
    BRIC_PROTNS_LOCKS(0x00008000),
};

icbcfg_prop_type icbcfg_boot_post_prop_v1 = 
{
    /* Length of the config  data array */
    ARRAY_SIZE(icbcfg_boot_post_data_v1),
    /* Pointer to config data array */ 
    icbcfg_boot_post_data_v1                                    
};


/* DDR map information. */
icbcfg_mem_region_type map_ddr_regions[1] =
{
  { 0x020000000ULL, 0x400000000ULL },
};

uint32 channel_map[2] = { SLAVE_DDR_CH0, SLAVE_DDR_CH1 };

HAL_bimc_InfoType bimc_hal_info =
{
  (uint8_t *)BIMC_BASE, /* Base address */
  19200,                /* QoS frequency */
  {
    0,
    0,
    0,
    0,
    0,
    0,
    4, /**< Number of segments for address decode. */
  }
};

/* Make sure the config region is always prohibited when "resetting" */
HAL_bimc_SlaveSegmentType safe_reset_seg =
{
  true,
  0x00000000ULL,                 /* start of config region */
  0x20000000ULL,                 /* 512 MB */
  BIMC_SEGMENT_TYPE_SUBTRACTIVE,
  BIMC_INTERLEAVE_NONE,
};

/* L2 TCM unmapping */
icbcfg_segment_type unmap_Sdm660_segments[] =
{
  {
    0,
    {
      false,
    }
  },
};

icbcfg_l2_unmap_info_type l2_tcm_unmap =
{
  2,
  ARRAY_SIZE(unmap_Sdm660_segments),
  unmap_Sdm660_segments,
};

icbcfg_device_config_type Sdm660_v1 =
{
  /* Chip version information for this device data. */
  DALCHIPINFO_FAMILY_SDM660,  /**< Chip family */
  false,                       /**< Exact match for version? */
  0x0,                         /**< Chip version */

  /* Device information. */
  &icbcfg_boot_prop_v1,        /**< ICB_Config_Init() prop data */
  ARRAY_SIZE(channel_map),     /**< Number of DDR channels */
  channel_map,                 /**< Map of array indicies to channel numbers */
  4,                           /**< Number of BRIC segments per slave */
  ARRAY_SIZE(map_ddr_regions), /**< Number of regions in the DDR map */
  map_ddr_regions,             /**< Array of mappable DDR regions */
  &bimc_hal_info,              /**< BIMC HAL info structure */
  &safe_reset_seg,             /**< The segment config to use while reseting segments */
  false,                       /**< Have we entered best effort mode? */
  &l2_tcm_unmap,               /**< L2 TCM unmap configuration */
  &icbcfg_boot_post_prop_v1,   /**< ICB_Config_PostInit() prop data */
};

icbcfg_device_config_type Sdm630_v1 =
{
  /* Chip version information for this device data. */
  DALCHIPINFO_FAMILY_SDM630,  /**< Chip family */
  false,                       /**< Exact match for version? */
  0x0,                         /**< Chip version */

  /* Device information. */
  &icbcfg_boot_prop_v1,        /**< ICB_Config_Init() prop data */
  ARRAY_SIZE(channel_map),     /**< Number of DDR channels */
  channel_map,                 /**< Map of array indicies to channel numbers */
  4,                           /**< Number of BRIC segments per slave */
  ARRAY_SIZE(map_ddr_regions), /**< Number of regions in the DDR map */
  map_ddr_regions,             /**< Array of mappable DDR regions */
  &bimc_hal_info,              /**< BIMC HAL info structure */
  &safe_reset_seg,             /**< The segment config to use while reseting segments */
  false,                       /**< Have we entered best effort mode? */
  &l2_tcm_unmap,               /**< L2 TCM unmap configuration */
  &icbcfg_boot_post_prop_v1,   /**< ICB_Config_PostInit() prop data */
};



/* Definitions list */
icbcfg_device_config_type *configs[] =
{
  &Sdm660_v1,
  &Sdm630_v1,
};

/* Exported target definitions */
icbcfg_info_type icbcfg_info =
{
  ARRAY_SIZE(configs),
  configs,
};
