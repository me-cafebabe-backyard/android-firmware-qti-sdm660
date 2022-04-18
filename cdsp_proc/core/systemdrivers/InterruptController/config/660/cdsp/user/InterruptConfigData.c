
/*==============================================================================

  D A L I N T E R R U P T   C O N T R O L L E R

  DESCRIPTION
    This auto-generated file contains the interrupt configuration data for
    all the interrupts for this platform.

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All rights reserved.
  QUALCOMM Proprietary/GTDR
===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/InterruptController/config/660/cdsp/user/InterruptConfigData.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DALInterruptControllerUserConfig.h"


/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/

/*
 * InterruptConfigs
 * BSP data for this target's interrupts.
 * The data layout is the following:
 * { L2VIC interrupt vector number, interrupt name}
 *
 */
static InterruptConfigType InterruptConfigs[] =
{
  {0, NO_AON_INTERRUPT, "slpc_l2vic_wake_irq"},
  {1, NO_AON_INTERRUPT,"q6ss_isdb_irq"},
  {2, NO_AON_INTERRUPT,"q6ss_qtmr_irq[0]"},
  {3, NO_AON_INTERRUPT,"q6ss_qtmr_irq[1]"},
  {4, NO_AON_INTERRUPT,"q6ss_qtmr_irq[2]"},
  {5, NO_AON_INTERRUPT,"q6ss_etm_irq"},
  {8, NO_AON_INTERRUPT,"vapss_vma_err_irq"},
  {12, NO_AON_INTERRUPT,"vapss_ubwcdma_err_irq"},
  {16, NO_AON_INTERRUPT,"vapss_vma_irq"},
  {20, NO_AON_INTERRUPT,"vapss_vma_strm_irq"},
  {24, NO_AON_INTERRUPT,"vapss_ubwcdma_irq"},
  {26, NO_AON_INTERRUPT,"trs_int"},
  {29, NO_AON_INTERRUPT,"acvremoval_int"},
  {31, NO_AON_INTERRUPT,"q6ss_cti_irq"},
  {32, NO_AON_INTERRUPT,"mss_ipc_out_irq[13]"},
  {33, NO_AON_INTERRUPT,"rpm_ipc[0]"},
  {34, NO_AON_INTERRUPT,"APCS_cdspHlosIPCInterrupt[1]"},
  {35, NO_AON_INTERRUPT,"mss_ipc_out_irq[12]"},
  {39, NO_AON_INTERRUPT,"rpm_ipc[2]"},
  {40, NO_AON_INTERRUPT,"rpm_ipc[3]"},
  {44, NO_AON_INTERRUPT,"APCS_cdspHlosIPCInterrupt[0]"},
  {46, NO_AON_INTERRUPT,"bus_irq"},
  {48, NO_AON_INTERRUPT,"mss_ipc_out_irq[14]"},
  {50, NO_AON_INTERRUPT,"dir_conn_irq_cdsp[0]"},
  {51, NO_AON_INTERRUPT,"dir_conn_irq_cdsp[1]"},
  {56, NO_AON_INTERRUPT,"rpm_ipc[1]"},
  {58, NO_AON_INTERRUPT,"q6ss_wdog_irq"},
  {59, NO_AON_INTERRUPT,"APCS_cdspHlosIPCInterrupt[2]"},
  {60, NO_AON_INTERRUPT,"mss_ipc_out_irq[15]"},
  {64, NO_AON_INTERRUPT,"summary_irq_cdsp"},
  {65, NO_AON_INTERRUPT,"nav_irq"},
  {67, NO_AON_INTERRUPT,"usb30_ctrl_irq[2]"},
  {68, NO_AON_INTERRUPT,"usb20s_power_event_irq"},
  {70, NO_AON_INTERRUPT,"turing_irq_in_usb30[3]"},
  {72, NO_AON_INTERRUPT,"APCS_cdspHlosIPCInterrupt[3]"},
  {80, NO_AON_INTERRUPT,"usb20s_ee1_irq"},
  {83, NO_AON_INTERRUPT,"o_hwe_eof_stb_vfe_0_lpass"},
  {84, NO_AON_INTERRUPT,"o_hwe_sof_stb_vfe_0_lpass"},
  {87, NO_AON_INTERRUPT,"spdm_realtime_irq[2]"},
  {89, NO_AON_INTERRUPT,"q6ss_avs_sw_done_irq"},
  {91, NO_AON_INTERRUPT, "peripheral_irq[2]"},
  {92, NO_AON_INTERRUPT, "peripheral_irq[3]"},
  {93, NO_AON_INTERRUPT, "peripheral_irq[4]"},
  {94, NO_AON_INTERRUPT, "peripheral_irq[5]"},
  {104,NO_AON_INTERRUPT, "lpass_irq_out_cdsp[3]"},
  {105, NO_AON_INTERRUPT, "ee5_ssc_spmi_periph_irq"},
  {107, NO_AON_INTERRUPT, "peripheral_irq[2]"},
  {108, NO_AON_INTERRUPT, "peripheral_irq[3]"},
  {109, NO_AON_INTERRUPT, "peripheral_irq[4]"},
  {110, NO_AON_INTERRUPT, "peripheral_irq[5]"},
  {115,NO_AON_INTERRUPT, "turing_irq_in_usb30[4]"},
  {116,NO_AON_INTERRUPT, "o_timeout_slave_turing_summary_intr"},
  {117,NO_AON_INTERRUPT, "o_hwe_eof_stb_vfe_1_lpass"},
  {118,NO_AON_INTERRUPT, "o_hwe_sof_stb_vfe_1_lpass"},
  {119, NO_AON_INTERRUPT, "channel5_ssc_trans_done_irq"},
  {121,NO_AON_INTERRUPT, "lpass_irq_out_cdsp[2]"},
  {122,NO_AON_INTERRUPT, "crypto_core_irq[1]"},
  {123,NO_AON_INTERRUPT, "crypto_bam_irq[1]"},
  {130,NO_AON_INTERRUPT, "phss_uart_ssc_int[0]"},
  {131,NO_AON_INTERRUPT, "phss_uart_ssc_int[1]"},
  {134,NO_AON_INTERRUPT, "processor_2_user_int"},
  {135,NO_AON_INTERRUPT, "processor_2_kernel_int"},
  {136,NO_AON_INTERRUPT, "lpass_irq_out_cdsp[0]"},
  {137,NO_AON_INTERRUPT, "lpass_irq_out_cdsp[1]"},
  {139,NO_AON_INTERRUPT, "turing_qos_q6_interrupt"},
  {140,NO_AON_INTERRUPT, "APCS_cdspHypIPCInterrupt[0]"},
  {141,NO_AON_INTERRUPT, "APCS_cdspHypIPCInterrupt[1]"},
  {142,NO_AON_INTERRUPT, "APCS_cdspHypIPCInterrupt[2]"},
  {143,NO_AON_INTERRUPT, "APCS_cdspHypIPCInterrupt[3]"},
  {146,NO_AON_INTERRUPT, "turing_irq_in_usb30[5]"},
  {151,NO_AON_INTERRUPT, "camss_irq0"},
  {152,NO_AON_INTERRUPT, "camss_irq1"},
  {153,NO_AON_INTERRUPT, "camss_irq2"},
  {154,NO_AON_INTERRUPT, "camss_irq3"},
  {155,NO_AON_INTERRUPT, "camss_irq4"},
  {156,NO_AON_INTERRUPT, "camss_irq5"},
  {157,NO_AON_INTERRUPT, "camss_irq6"},
  {158,NO_AON_INTERRUPT, "camss_irq7"},
  {159,NO_AON_INTERRUPT, "camss_irq8"},
  {160,NO_AON_INTERRUPT, "camss_irq9"},
  {161,NO_AON_INTERRUPT, "camss_irq10"},
  {163,NO_AON_INTERRUPT, "camss_irq12"},
  {164,NO_AON_INTERRUPT, "camss_irq13"},
  {165,NO_AON_INTERRUPT, "camss_irq14"},
  {166,NO_AON_INTERRUPT, "camss_irq15"},
  {167,NO_AON_INTERRUPT, "camss_irq16"},
  {168,NO_AON_INTERRUPT, "camss_irq17"},
  {169,NO_AON_INTERRUPT, "camss_irq18"},
  {170,NO_AON_INTERRUPT, "camss_dsp_streaming_0_irq"},
  {171,NO_AON_INTERRUPT, "camss_dsp_streaming_1_irq"},
  {178,NO_AON_INTERRUPT, "lcc_turing_wrapper_q6_smmu_gds_hw_ctrl_sequence_abort_irq"},
  {184,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[0]"},
  {185,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[1]"},
  {186,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[2]"},
  {187,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[3]"},
  {188,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[4]"},
  {189,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[5]"},
  {190,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[6]"},
  {191,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[7]"},
  {192,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[8]"},
  {193,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[9]"},
  {194,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[10]"},
  {195,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[11]"},
  {196,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[12]"},
  {197,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[13]"},
  {198,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[14]"},
  {199,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[15]"},
  {200,NO_AON_INTERRUPT, "turing_q6_smmu_CIrpt[16]"},
  {INVALID_INTERRUPT, NO_AON_INTERRUPT, ""}
};


/*
 * pInterruptControllerConfigData
 * This is used by the interrupt controller driver to query platform specific data.
 */
InterruptPlatformDataType pInterruptControllerConfigData[] =
{
  {
    .pIRQConfigs = InterruptConfigs,
    .nMaxIRQ     = 201
  }
};
