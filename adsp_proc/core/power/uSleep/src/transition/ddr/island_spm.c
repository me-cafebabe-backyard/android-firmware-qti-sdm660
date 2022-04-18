/*==============================================================================
  FILE:         island_spm.c

  OVERVIEW:     This file provides island transition SPM initialization routines

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/ddr/island_spm.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "DDIInterruptController.h"
#include "CoreVerify.h"
#include "island.h"
#include "island_spm.h"
#include "spm.h"
#include "uSleep_HALhwio.h"
#include "uSleep_hwio.h"

/*==============================================================================
                            INTERNAL VARIABLES
 =============================================================================*/
/* SPM command sequence AXI bus isolation to enter island mode */
static spm_cmd_t g_islandSpmCmdSeqIslandEntry[] =
{
  /* 0 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_HALT,           0), /* Assert bus halt request 23 */ 
  SPM_SEQ_EVENT_CTL (EVENT_3,                  0), /* Wait for bus halt          */ 
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_CLK,            0), /* Bus clock off           29 */
  SPM_SEQ_EVENT_CTL (EVENT_2,                  0), /* Wait for clock off         */ 

  /* 4 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_INT_CLAMP_SET,  0), /* Bus interface clamp     24 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_PWR_CLAMP_SET,  0), /* Bus power clamp         25 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_CLK,            0), /* Bus clk on              29 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_HALT,           0), /* Deassert bus halt       23 */

  /* 8 */
  SPM_SEQ_END_CTL   (0,                        0), /* End of Program */
};

/* SPM command sequence AXI bus de-isolation to exit island mode */
static spm_cmd_t g_islandSpmCmdSeqIslandExit[] =
{
  /* 0 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_CLK,           0), /* Bus clk off */
  SPM_SEQ_EVENT_CTL (EVENT_2,                 0), /* Wait for clock off */ 
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_PWR_CLAMP_CLR, 0), /* Clear bus power clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_FIFO_RESET,    0), /* Assert FIFO reset */
  
  /* 4 */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_FIFO_RESET,    0), /* Deassert FIFO reset */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_INT_CLAMP_CLR, 0), /* Clear bus interface clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_BUS_CLK,           0), /* Bus clk on */
  SPM_SEQ_END_CTL   (0,                       0), /* End of Program */
};

/* Entry and exit sequence data */
static island_spm_island_sequence g_islandSPMSequence = 
{
  {{g_islandSpmCmdSeqIslandEntry, sizeof(g_islandSpmCmdSeqIslandEntry)},  0},
  {{g_islandSpmCmdSeqIslandExit, sizeof(g_islandSpmCmdSeqIslandExit)},    1}
};

/* Entry and exit interrupt registration handle */
static DalDeviceHandle *g_islandDALInterruptCtrlHndl;

/* SPM handle used to update dynamic sequence data */
static spm_handle g_islandSPMHandle[1] = {0};

/*==============================================================================
                          INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * islandSPM_configSWTrigger
 * 
 * @brief Sets the SPM start address for the required entry and exit
 *        sequences
 * 
 * @param seqIdx:       Starting index of sequence
 * @param triggerType:  Enum to indicate entry or exit sequence 
 */
static void islandSPM_configSWTrigger(uint32                   seqIdx, 
                                      island_spm_soft_trigger  triggerType)
{
  CORE_VERIFY(triggerType < ISLAND_SW_TRIGGER_LAST);

  HWIO_OUTFI(LPASS_QDSP6SS_SPM_TRIG_CFGn, triggerType, SPM_STARTADDR, seqIdx);

  return;
}

/*==============================================================================
                          EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * islandSPM_setupSequenceTransition 
 */
void islandSPM_setupSequenceTransition(void)
{
  /* Setup configuration register for bus isolation sequence */
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK,
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK, AXIM2,  0)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK, AXIM,   1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK, CORE,   1));

  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL,
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL, AXIM2_FIFO_ARESET,  0) |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL, AXIM2_HALTREQ,      0) |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL, AXIM_FIFO_ARESET,   1) |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL, AXIM_HALTREQ,       1) |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL, BUSM_HALTREQ,       0));

  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP,
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_CLEAR, 1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_E_SET,   1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_CLEAR, 1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP, AXIM_CLAMP_L_SET,   1));

  HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, AXIM2_HALTACK_OVRRD, 1);
  HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, AXIM_HALTACK_OVRRD,  0);
  HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, ALL_HALTACK_OVRRD,   1);

  HWIO_OUT(LPASS_SCSR_IEC_CTL,
           HWIO_FVAL(LPASS_SCSR_IEC_CTL, L2_MISS_ISLAND_EXIT_EN,     0)  |
           HWIO_FVAL(LPASS_SCSR_IEC_CTL, ISO_AHB_MASTER_BYPASS,      0)  |
           HWIO_FVAL(LPASS_SCSR_IEC_CTL, ISO_AHB_SLAVE_BYPASS,       0)  |
           HWIO_FVAL(LPASS_SCSR_IEC_CTL, AHB_REQPEND_CLR,            1)  |
           HWIO_FVAL(LPASS_SCSR_IEC_CTL, ENTER_ISLAND_MODE_IRQ_CLR,  1));

  /* This assumes that the SPM driver has already been initilized */
  CORE_VERIFY(1 == spm_driver_get_handles(SPM_DEFAULT_INSTANCE_NAME, 
                                          1, g_islandSPMHandle));

  /* Program (de)isolation sequences into SPM */
  CORE_VERIFY(spm_instance_program_cmd_seq(g_islandSPMHandle[0], 
                                           &g_islandSPMSequence.enter.data,
                                           &g_islandSPMSequence.enter.start_addr) == SPM_SUCCESS);

  islandSPM_configSWTrigger(g_islandSPMSequence.enter.start_addr, ISLAND_SW_TRIGGER_ENTER);

  CORE_VERIFY(spm_instance_program_cmd_seq(g_islandSPMHandle[0], 
                                           &g_islandSPMSequence.exit.data,
                                           &g_islandSPMSequence.exit.start_addr) == SPM_SUCCESS);

  islandSPM_configSWTrigger(g_islandSPMSequence.exit.start_addr, ISLAND_SW_TRIGGER_EXIT);

  /* Attaching to interrupt controller and registering interrupt handlers */
  CORE_VERIFY(DAL_DeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER,
                               &g_islandDALInterruptCtrlHndl) == DAL_SUCCESS );

  /* Registering for island exit complete interrupt */
  CORE_VERIFY(DAL_SUCCESS == DalInterruptController_RegisterISR(
      g_islandDALInterruptCtrlHndl,
      ISLAND_EXIT_IRQ,
      (DALIRQ)island_exitHandler,
      (const DALIRQCtx) 0,
      DALINTRCTRL_ENABLE_CONFIG_EX(DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER,
                                   0, 1)));

  return;
}

