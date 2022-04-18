
/*==============================================================================

  D A L I N T E R R U P T   C O N T R O L L E R

  DESCRIPTION
    This auto-generated file contains the interrupt configuration data for
    all the interrupts for this platform.

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All rights reserved.
  QUALCOMM Proprietary/GTDR
===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/InterruptController/config/660/adsp_slpi/kernel/InterruptConfigData.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DALInterruptControllerConfig.h"


/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/

/*
 * InterruptConfigs
 * BSP data for this target's interrupts.
 * The data layout is the following:
 * { L2VIC interrupt vector number, interrupt name, trigger type}
 *
 */
static InterruptConfigType InterruptConfigs[] =
{
  {0, NO_AON_INTERRUPT, "slpc_l2vic_wake_irq"},
  {1, NO_AON_INTERRUPT, "qdsp6_isdb_irq"},
  {2, NO_AON_INTERRUPT, "q6ss_qtmr_irq[0]"},
  {3, NO_AON_INTERRUPT, "q6ss_qtmr_irq[1]"},
  {4, NO_AON_INTERRUPT, "q6ss_qtmr_irq[2]"},
  {5, NO_AON_INTERRUPT, "qdsp6_etintreq"},
  {6, 0, "mss_ipc_out_irq[9]"},
  {7, 1, "rpm_ipc[8]"},
  {8, 2, "APCS_adspIPCInterrupt[1]"},
  {9, 3, "mss_ipc_out_irq[10]"},
  {11, NO_AON_INTERRUPT, "lpass_aud_slimbus_core_ee_irq[0]"},
  {12, NO_AON_INTERRUPT, "lpass_aud_slimbus_bam_ee_irq[0]"},
  {13, 5, "rpm_ipc[10]"},
  {14, 6, "rpm_ipc[11]"},
  {18, 10, "APCS_adspIPCInterrupt[0]"},
  {19, NO_AON_INTERRUPT, "audio_out2_irq"},
  {20, NO_AON_INTERRUPT, "bus_irq"},
  {22, 12, "mss_ipc_out_irq[8]"},
  {23, NO_AON_INTERRUPT, "dm_irq"},
  {24, 13, "dir_conn_irq_lpa_dsp[0]"},
  {25, 14, "dir_conn_irq_lpa_dsp[1]"},
  {26, 15, "dir_conn_irq_lpa_dsp[2]"},
  {27, 16, "dir_conn_irq_lpa_dsp[3]"},
  {28, 17, "dir_conn_irq_lpa_dsp[4]"},
  {29, 18, "dir_conn_irq_lpa_dsp[5]"},
  {30, 19, "rpm_ipc[9]"},
  {31, NO_AON_INTERRUPT, "q6ss_cti_irq"},
  {32, NO_AON_INTERRUPT, "q6ss_wdog_irq"},
  {33, 20, "APCS_adspIPCInterrupt[2]"},
  {34, 21, "mss_ipc_out_irq[11]"},
  {36, 23, "vfr[0]"},
  {37, 24, "adsp_ext_vfr_irq"},
  {38, 25, "summary_irq_lpa_dsp"},
  {40, 27, "vfr[1]"},
  {42, 29, "usb20s_power_event_irq"},
  {44, 31, "usb30_power_event_irq"},
  {46, 33, "APCS_adspIPCInterrupt[3]"},
  {47, 34, "usb30_ctrl_irq[2]"},
  {48, 35, "ee3_lpass_spmi_periph_irq"},
  {49, 36, "channel3_lpass_trans_done_irq"},
  {50, NO_AON_INTERRUPT, "avtimer_int_0"},
  {51, NO_AON_INTERRUPT, "vfr_irq_mux_out[0]"},
  {53, NO_AON_INTERRUPT, "resampler_irq[1]"},
  {54, 38, "usb20s_ee1_irq"},
  {55, 39, "bam_irq[1]"},
  {56, 40, "bam_irq[1]"},
  {57, 41, "o_hwe_sof_stb_vfe_0_lpass"},
  {58, 42, "o_hwe_eof_stb_vfe_0_lpass"},
  {61, 45, "spdm_realtime_irq[2]"},
  {62, 46, "summary_irq_sensors"},
  {63, NO_AON_INTERRUPT, "q6ss_avs_sw_done_irq"},
  {65, 48, "peripheral_irq[2]"},
  {66, 49, "peripheral_irq[3]"},
  {67, 50, "peripheral_irq[4]"},
  {68, 51, "peripheral_irq[5]"},
  {70, 53, "dir_conn_irq_sensors[0]"},
  {71, 54, "dir_conn_irq_sensors[1]"},
  {81, 64, "peripheral_irq[2]"},
  {82, 65, "peripheral_irq[3]"},
  {83, 66, "peripheral_irq[4]"},
  {84, 67, "peripheral_irq[5]"},
  {86, NO_AON_INTERRUPT, "lpass_qca_slimbus_core_ee_irq[0]"},
  {87, NO_AON_INTERRUPT, "lpass_qca_slimbus_bam_ee_irq[0]"},
  {90, 71, "o_timeout_slave_lpass_summary_intr"},
  {91, 72, "o_hwe_sof_stb_vfe_1_lpass"},
  {92, 73, "o_hwe_eof_stb_vfe_1_lpass"},
  {94, NO_AON_INTERRUPT, "lpass_hdmitx_interrupt"},
  {96, 76, "crypto_core_irq[1]"},
  {97, 77, "crypto_bam_irq[1]"},
  {104, 84, "phss_uart_lpass_int[0]"},
  {105, 85, "phss_uart_lpass_int[1]"},
  {106, 86, "ssc_qup_int"},
  {108, 88, "processor_0_user_int"},
  {109, 89, "processor_0_kernel_int"},
  {112, NO_AON_INTERRUPT, "lpass_core_qos_q6ss_interrupt"},
  {113, NO_AON_INTERRUPT, "lpass_qos_q6ss_interrupt"},
  {114, 92, "APCS_adspVmmIPCInterrupt[0]"},
  {115, 93, "APCS_adspVmmIPCInterrupt[1]"},
  {116, 94, "APCS_adspVmmIPCInterrupt[2]"},
  {117, 95, "APCS_adspVmmIPCInterrupt[3]"},
  {122, NO_AON_INTERRUPT, "lpass_spdif_tx_intr_q6"},
  {123, NO_AON_INTERRUPT, "sif_aud_dec_out_irq"},
  {124, NO_AON_INTERRUPT, "vfr_irq_mux_out[1]"},
  {125, 99, "camss_irq0"},
  {126, 100, "camss_irq1"},
  {127, 101, "camss_irq2"},
  {128, 102, "camss_irq3"},
  {129, 103, "camss_irq4"},
  {130, 104, "camss_irq5"},
  {131, 105, "camss_irq6"},
  {132, 106, "camss_irq7"},
  {133, 107, "camss_irq8"},
  {134, 108, "camss_irq9"},
  {135, 109, "camss_irq10"},
  {137, 111, "camss_irq12"},
  {138, 112, "camss_irq13"},
  {139, 113, "camss_irq14"},
  {140, 114, "camss_irq15"},
  {141, 115, "camss_irq16"},
  {142, 116, "camss_irq17"},
  {143, 117, "camss_irq18"},
  {146, NO_AON_INTERRUPT, "lcc_spkr_ext_clk_detect_inactive_irq"},
  {147, NO_AON_INTERRUPT, "lcc_pri_ext_clk_detect_inactive_irq"},
  {148, NO_AON_INTERRUPT, "lcc_sec_ext_clk_detect_inactive_irq"},
  {149, NO_AON_INTERRUPT, "lcc_ter_ext_clk_detect_inactive_irq"},
  {150, NO_AON_INTERRUPT, "lcc_quad_ext_clk_detect_inactive_irq"},
  {151, NO_AON_INTERRUPT, "lcc_audio_core_smmu_gds_hw_ctrl_sequence_abort_irq"},
  {152, NO_AON_INTERRUPT, "lcc_audio_wrapper_q6_smmu_gds_hw_ctrl_sequence_abort_irq"},
  {153, NO_AON_INTERRUPT, "q6ss_wakeup_rmdr"},
  {154, NO_AON_INTERRUPT, "qdsp6_iso_axim_reqpend"},
  {155, NO_AON_INTERRUPT, "iso_ahb_reqpend_irq"},
  {156, NO_AON_INTERRUPT, "enter_island_mode_irq"},
  {158, NO_AON_INTERRUPT, "lpass_irq_out_apcs[21]"},
  {159, NO_AON_INTERRUPT, "lpass_irq_out_apcs[22]"},
  {160, NO_AON_INTERRUPT, "lpass_irq_out_apcs[23]"},
  {161, NO_AON_INTERRUPT, "lpass_irq_out_apcs[24]"},
  {162, NO_AON_INTERRUPT, "lpass_irq_out_apcs[25]"},
  {163, NO_AON_INTERRUPT, "lpass_irq_out_apcs[26]"},
  {164, NO_AON_INTERRUPT, "lpass_irq_out_apcs[27]"},
  {165, NO_AON_INTERRUPT, "lpass_irq_out_apcs[28]"},
  {166, NO_AON_INTERRUPT, "lpass_irq_out_apcs[29]"},
  {167, NO_AON_INTERRUPT, "lpass_irq_out_apcs[30]"},
  {168, NO_AON_INTERRUPT, "lpass_irq_out_apcs[31]"},
  {169, NO_AON_INTERRUPT, "lpass_irq_out_apcs[32]"},
  {170, NO_AON_INTERRUPT, "lpass_irq_out_apcs[33]"},
  {171, NO_AON_INTERRUPT, "lpass_irq_out_apcs[34]"},
  {172, NO_AON_INTERRUPT, "lpass_irq_out_apcs[35]"},
  {173, NO_AON_INTERRUPT, "lpass_irq_out_apcs[36]"},
  {174, NO_AON_INTERRUPT, "lpass_irq_out_apcs[37]"},
  {175, NO_AON_INTERRUPT, "lpass_irq_out_apcs[18]"},
  {175, NO_AON_INTERRUPT, "lpass_irq_out_apcs[18]"},
  {176, NO_AON_INTERRUPT, "lpass_irq_out_apcs[19]"},
  {176, NO_AON_INTERRUPT, "lpass_irq_out_apcs[19]"},
  {177, NO_AON_INTERRUPT, "lpass_irq_out_apcs[20]"},
  {177, NO_AON_INTERRUPT, "lpass_irq_out_apcs[20]"},
  {178, NO_AON_INTERRUPT, "lpass_irq_out_apcs[12]"},
  {178, NO_AON_INTERRUPT, "lpass_irq_out_apcs[12]"},
  {179, NO_AON_INTERRUPT, "lpass_irq_out_apcs[16]"},
  {179, NO_AON_INTERRUPT, "lpass_irq_out_apcs[16]"},
  {180, NO_AON_INTERRUPT, "lpass_irq_out_apcs[17]"},
  {180, NO_AON_INTERRUPT, "lpass_irq_out_apcs[17]"},
  {181, NO_AON_INTERRUPT, "lpass_irq_out_apcs[42]"},
  {181, NO_AON_INTERRUPT, "lpass_irq_out_apcs[42]"},
  {182, NO_AON_INTERRUPT, "lpass_sensor_core_bam_irq[0]"},
  {183, NO_AON_INTERRUPT, "lpass_irq_out_security[3]"},
  {184, NO_AON_INTERRUPT, "lpass_irq_out_security[4]"},
  {185, NO_AON_INTERRUPT, "lpass_irq_out_security[2]"},
  {186, NO_AON_INTERRUPT, "lpass_dcodec_irq[0]"},
  {187, NO_AON_INTERRUPT, "lpass_dcodec_irq[1]"},
  {188, NO_AON_INTERRUPT, "alarm_irq_cx"},
  {189, NO_AON_INTERRUPT, "alarm_irq_mx"},
  {192, 123, "gcc_wind_down_req"},
  {194, NO_AON_INTERRUPT, "q6ss_spm_trig_done_irq_1"},
  {195, NO_AON_INTERRUPT, "q6ss_spm_trig_done_irq_0"},
  {196, 127, "turing_irq_out_adsp[3]"},
  {197, 128, "turing_irq_out_adsp[2]"},
  {198, 129, "turing_irq_out_adsp[1]"},
  {199, 130, "turing_irq_out_adsp[0]"},
  {200, NO_AON_INTERRUPT, "lpass_irq_out_apcs[5]"},
  {203, 133, "bi_px_ssc_22"},
  {204, 134, "bi_px_ssc_23"},
  {205, 135, "pmu_lpi_sw_slp_tmr_int"},
  {206, 136, "core_bi_px_to_core[11]"},
  {207, 137, "core_bi_px_to_core[0]"},
  {208, 138, "core_bi_px_to_core[1]"},
  {209, 139, "core_bi_px_to_core[2]"},
  {210, 140, "core_bi_px_to_core[3]"},
  {211, 141, "core_bi_px_to_core[4]"},
  {212, 142, "core_bi_px_to_core[5]"},
  {213, 143, "core_bi_px_to_core[6]"},
  {214, 144, "core_bi_px_to_core[7]"},
  {215, 145, "core_bi_px_to_core[8]"},
  {216, 146, "core_bi_px_to_core[16]"},
  {217, 147, "core_bi_px_to_core[17]"},
  {218, 148, "core_bi_px_to_core[18]"},
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
    .nMaxIRQ     = 219
  }
};
