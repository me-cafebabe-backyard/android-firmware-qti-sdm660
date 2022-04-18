#include "DALPropDef.h"
#include "DALDeviceId.h"
#include "dalconfig.h"
#include "DALStdDef.h" 
#include "DALSysTypes.h" 

#include "DevConfig.h"
#include "Chipinfo.h"
#ifndef DAL_CONFIG_IMAGE_RPM 
#define DAL_CONFIG_IMAGE_RPM 
#endif 
extern void * glink_ssr_devcfg_config_660_xml;
extern void * xport_rpm_devcfg_proc_info_660_xml;
extern void * xport_rpm_devcfg_remote_procs_660_xml;
extern void * xport_rpm_devcfg_toc_660_xml;
extern void * clk_reg_660_xml;
extern void * smps_reg_660_xml;
extern void * ldo_reg_660_xml;
extern void * vs_reg_660_xml;
extern void * boost_reg_660_xml;
extern void * bob_reg_660_xml;
extern void * fg_reg_660_xml;
extern void * pbs_client_reg_660_xml;
extern void * fts_volt_660_xml;
extern void * fts2p5_volt_660_xml;
extern void * hfs_volt_660_xml;
extern void * boost_volt_660_xml;
extern void * nmos_volt_660_xml;
extern void * n600_volt_660_xml;
extern void * n1200_volt_660_xml;
extern void * pmos_volt_660_xml;
extern void * ln_volt_660_xml;
extern void * fts_range_660_xml;
extern void * fts2p5_range_660_xml;
extern void * hfs_range_660_xml;
extern void * boost_range_660_xml;
extern void * nmos_range_660_xml;
extern void * n600_range_660_xml;
extern void * n1200_range_660_xml;
extern void * pmos_range_660_xml;
extern void * ln_range_660_xml;
extern void * ult_nmos_volt_660_xml;
extern void * ult_pmos_volt_660_xml;
extern void * ult_nmos_range_660_xml;
extern void * ult_pmos_range_660_xml;
extern void * ult_buck_range_1_660_xml;
extern void * ult_buck_volt_1_660_xml;
extern void * ult_buck_range_2_660_xml;
extern void * ult_buck_volt_2_660_xml;
extern void * unified_rails_stepper_rate_660_xml;
extern void * ult_ldo_stepper_rate_660_xml;
extern void * ult_smps_stepper_rate_660_xml;
extern void * ldo_stepper_rate_660_xml;
extern void * bob_stepper_rate_660_xml;
extern void * smps_stepper_rate_660_xml;
extern void * ldo_vreg_ok_time_660_xml;
extern void * smps_vreg_ok_time_660_xml;
extern void * vs_vreg_ok_time_660_xml;
extern void * bob_vreg_ok_time_660_xml;
extern void * clk_ok_time_660_xml;
extern void * clk_sleep_reg_660_xml;
extern void * clk_xo_reg_660_xml;
extern void * clk_common_660_xml;
extern void * num_of_smps_660_xml;
extern void * num_of_ldo_660_xml;
extern void * num_of_vs_660_xml;
extern void * num_of_bob_660_xml;
extern void * bob_pin_mapping_660_xml;
extern void * pm_npa_rpm_pam_node_rsrcs_660_xml;
extern void * num_of_pm_rpm_nodes_660_xml;
extern void * ldo_rail_660_xml;
extern void * smps_rail_660_xml;
extern void * vs_rail_660_xml;
extern void * clk_info_660_xml;
extern void * bob_rail_660_xml;
extern void * smps_dep_660_xml;
extern void * ldo_dep_660_xml;
extern void * vs_dep_660_xml;
extern void * clk_dep_660_xml;
extern void * bob_dep_660_xml;
extern void * pm_mpm_active_cfg_660_xml;
extern void * pm_mpm_sleep_cfg_660_xml;
extern void * pm_mpm_cmd_index_660_xml;
extern void * pm_mpm_rails_info_660_xml;
extern void * sleep_enter_info_660_xml;
extern void * sleep_exit_info_660_xml;
extern void * SourceConfig_660_xml;
extern void * RPMClockConfig_660_xml;
extern void * SystemNOCClockConfig_660_xml;
extern void * PIMEMClockConfig_660_xml;
extern void * SYSNOCHSAXIClockConfig_660_xml;
extern void * ConfigNOCClockConfig_660_xml;
extern void * PeriphNOCClockConfig_660_xml;
extern void * QDSSATBAClockConfig_660_xml;
extern void * QDSSATBBClockConfig_660_xml;
extern void * QDSSATBCClockConfig_660_xml;
extern void * QDSSTraceClockConfig_660_xml;
extern void * QDSSSTMClockConfig_660_xml;
extern void * QDSSTSCTRDiv2ClockConfig_660_xml;
extern void * QDSSAPBTRIGClockConfig_660_xml;
extern void * IPAClockConfig_660_xml;
extern void * CEClockConfig_660_xml;
extern void * SPMIAHBClockConfig_660_xml;
extern void * SPMISERClockConfig_660_xml;
extern void * HMSSAHBClockConfig_660_xml;
extern void * VSenseClockConfig_660_xml;
extern void * MMSSAXIClockConfig_660_xml;
extern void * ClockLogDefaultConfig_660_xml;
extern void * icb_rpm_system_660_xml;

const void * DALPROP_StructPtrs_660_xml[99] =  {
	&glink_ssr_devcfg_config_660_xml,
	&xport_rpm_devcfg_proc_info_660_xml,
	&xport_rpm_devcfg_remote_procs_660_xml,
	&xport_rpm_devcfg_toc_660_xml,
	&clk_reg_660_xml,
	&smps_reg_660_xml,
	&ldo_reg_660_xml,
	&vs_reg_660_xml,
	&boost_reg_660_xml,
	&bob_reg_660_xml,
	&fg_reg_660_xml,
	&pbs_client_reg_660_xml,
	&fts_volt_660_xml,
	&fts2p5_volt_660_xml,
	&hfs_volt_660_xml,
	&boost_volt_660_xml,
	&nmos_volt_660_xml,
	&n600_volt_660_xml,
	&n1200_volt_660_xml,
	&pmos_volt_660_xml,
	&ln_volt_660_xml,
	&fts_range_660_xml,
	&fts2p5_range_660_xml,
	&hfs_range_660_xml,
	&boost_range_660_xml,
	&nmos_range_660_xml,
	&n600_range_660_xml,
	&n1200_range_660_xml,
	&pmos_range_660_xml,
	&ln_range_660_xml,
	&ult_nmos_volt_660_xml,
	&ult_pmos_volt_660_xml,
	&ult_nmos_range_660_xml,
	&ult_pmos_range_660_xml,
	&ult_buck_range_1_660_xml,
	&ult_buck_volt_1_660_xml,
	&ult_buck_range_2_660_xml,
	&ult_buck_volt_2_660_xml,
	&unified_rails_stepper_rate_660_xml,
	&ult_ldo_stepper_rate_660_xml,
	&ult_smps_stepper_rate_660_xml,
	&ldo_stepper_rate_660_xml,
	&bob_stepper_rate_660_xml,
	&smps_stepper_rate_660_xml,
	&ldo_vreg_ok_time_660_xml,
	&smps_vreg_ok_time_660_xml,
	&vs_vreg_ok_time_660_xml,
	&bob_vreg_ok_time_660_xml,
	&clk_ok_time_660_xml,
	&clk_sleep_reg_660_xml,
	&clk_xo_reg_660_xml,
	&clk_common_660_xml,
	&num_of_smps_660_xml,
	&num_of_ldo_660_xml,
	&num_of_vs_660_xml,
	&num_of_bob_660_xml,
	&bob_pin_mapping_660_xml,
	&pm_npa_rpm_pam_node_rsrcs_660_xml,
	&num_of_pm_rpm_nodes_660_xml,
	&ldo_rail_660_xml,
	&smps_rail_660_xml,
	&vs_rail_660_xml,
	&clk_info_660_xml,
	&bob_rail_660_xml,
	&smps_dep_660_xml,
	&ldo_dep_660_xml,
	&vs_dep_660_xml,
	&clk_dep_660_xml,
	&bob_dep_660_xml,
	&pm_mpm_active_cfg_660_xml,
	&pm_mpm_sleep_cfg_660_xml,
	&pm_mpm_cmd_index_660_xml,
	&pm_mpm_rails_info_660_xml,
	&sleep_enter_info_660_xml,
	&sleep_exit_info_660_xml,
	&SourceConfig_660_xml,
	&RPMClockConfig_660_xml,
	&SystemNOCClockConfig_660_xml,
	&PIMEMClockConfig_660_xml,
	&SYSNOCHSAXIClockConfig_660_xml,
	&ConfigNOCClockConfig_660_xml,
	&PeriphNOCClockConfig_660_xml,
	&QDSSATBAClockConfig_660_xml,
	&QDSSATBBClockConfig_660_xml,
	&QDSSATBCClockConfig_660_xml,
	&QDSSTraceClockConfig_660_xml,
	&QDSSSTMClockConfig_660_xml,
	&QDSSTSCTRDiv2ClockConfig_660_xml,
	&QDSSAPBTRIGClockConfig_660_xml,
	&IPAClockConfig_660_xml,
	&CEClockConfig_660_xml,
	&SPMIAHBClockConfig_660_xml,
	&SPMISERClockConfig_660_xml,
	&HMSSAHBClockConfig_660_xml,
	&VSenseClockConfig_660_xml,
	&MMSSAXIClockConfig_660_xml,
	&ClockLogDefaultConfig_660_xml,
	&icb_rpm_system_660_xml,
	 0 };
const uint32 DALPROP_PropBin_660_xml[] = {

			0x00000814, 0x00000028, 0x00000298, 0x000002a8, 0x000002a8, 
			0x00000002, 0x02000145, 0x000006a0, 0x0200009b, 0x000007ec, 
			0x666e6f63, 0x70006769, 0x5f636f72, 0x6f666e69, 0x6d657200, 
			0x5f65746f, 0x636f7270, 0x6f740073, 0x63740063, 0x625f7273, 
			0x5f657361, 0x656d616e, 0x73637400, 0x61625f72, 0x6d006573, 
			0x78657475, 0x66666f5f, 0x73746573, 0x6e6f7700, 0x6f5f6563, 
			0x65736666, 0x43007374, 0x6b636f6c, 0x72756f53, 0x00736563, 
			0x5f636367, 0x5f6d7072, 0x636f7270, 0x6c63685f, 0x6367006b, 
			0x79735f63, 0x6f6e5f73, 0x78615f63, 0x6c635f69, 0x6367006b, 
			0x67615f63, 0x32657267, 0x6f6e735f, 0x78615f63, 0x6c635f69, 
			0x6367006b, 0x79735f63, 0x6f6e5f73, 0x69705f63, 0x5f6d656d, 
			0x5f697861, 0x006b6c63, 0x5f636367, 0x5f737973, 0x5f636f6e, 
			0x615f7368, 0x635f6978, 0x67006b6c, 0x635f6363, 0x6e5f6766, 
			0x615f636f, 0x635f6268, 0x67006b6c, 0x635f6363, 0x5f636f6e, 
			0x69726570, 0x6e5f6870, 0x6874726f, 0x6268615f, 0x6b6c635f, 
			0x63636700, 0x7379735f, 0x636f6e5f, 0x5f74615f, 0x006b6c63, 
			0x5f636367, 0x636d6962, 0x5f74615f, 0x006b6c63, 0x5f636367, 
			0x7361706c, 0x74615f73, 0x6b6c635f, 0x63636700, 0x7364715f, 
			0x72745f73, 0x63656361, 0x6e696b6c, 0x6b6c635f, 0x63636700, 
			0x7364715f, 0x74735f73, 0x6c635f6d, 0x6367006b, 0x64715f63, 
			0x745f7373, 0x72746373, 0x7669645f, 0x6c635f32, 0x6367006b, 
			0x64715f63, 0x745f7373, 0x5f676972, 0x006b6c63, 0x5f636367, 
			0x5f617069, 0x006b6c63, 0x5f636367, 0x5f316563, 0x006b6c63, 
			0x5f636367, 0x696d7073, 0x6268615f, 0x6b6c635f, 0x63636700, 
			0x6d70735f, 0x65735f69, 0x6c635f72, 0x6367006b, 0x6d685f63, 
			0x615f7373, 0x635f6268, 0x67006b6c, 0x765f6363, 0x5f616464, 
			0x635f7376, 0x67006b6c, 0x765f6363, 0x78636464, 0x5f73765f, 
			0x006b6c63, 0x5f636367, 0x6d646476, 0x73765f78, 0x6b6c635f, 
			0x63636700, 0x73736d5f, 0x5f73765f, 0x006b6c63, 0x73736d6d, 
			0x6f6e6d5f, 0x78615f63, 0x6c635f69, 0x6c43006b, 0x4c6b636f, 
			0x6544676f, 0x6c756166, 0x73007374, 0x65747379, 0x4544006d, 
			0x4c554146, 0x52465f54, 0x45555145, 0x0059434e, 0x4d495451, 
			0x415f5245, 0x41425f43, 0x51004553, 0x454d4954, 0x41425f52, 
			0x00004553, 0x45524f43, 0x504f545f, 0x5253435f, 0x00000000, 
			0x00000007, 0x00040000, 0x00041000, 0x00042000, 0x00043000, 
			0x00044000, 0x00045000, 0x00046000, 0x00047000, 0x00000001, 
			0x000d4000, 0x000d4004, 0x00000012, 0x00000000, 0x00000000, 
			0xff00ff00, 0x00000012, 0x00000007, 0x00000001, 0x00000012, 
			0x00000011, 0x00000002, 0x00000012, 0x0000001e, 0x00000003, 
			0xff00ff00, 0x00000011, 0x00000022, 0x00000000, 0x00000002, 
			0x00000031, 0x01f00000, 0x00000014, 0x0000003b, 0x00000000, 
			0x00000014, 0x00000049, 0x00000024, 0xff00ff00, 0x00000012, 
			0x00000001, 0x00000004, 0x00000012, 0x00000002, 0x00000005, 
			0x00000012, 0x00000003, 0x00000006, 0x00000012, 0x00000004, 
			0x00000007, 0x00000012, 0x00000005, 0x00000008, 0x00000012, 
			0x00000033, 0x00000009, 0x00000012, 0x00000032, 0x0000000a, 
			0x00000012, 0x0000002d, 0x0000000b, 0x00000012, 0x00000006, 
			0x0000000c, 0x00000012, 0x0000001e, 0x0000000d, 0x00000012, 
			0x00000007, 0x0000000e, 0x00000012, 0x00000008, 0x0000000f, 
			0x00000012, 0x00000009, 0x00000010, 0x00000012, 0x0000000a, 
			0x00000011, 0x00000012, 0x0000000b, 0x00000012, 0x00000012, 
			0x0000000c, 0x00000013, 0x00000012, 0x0000000d, 0x00000014, 
			0x00000012, 0x0000000e, 0x00000015, 0x00000012, 0x0000001f, 
			0x00000016, 0x00000012, 0x0000000f, 0x00000017, 0x00000012, 
			0x00000010, 0x00000018, 0x00000012, 0x00000011, 0x00000019, 
			0x00000012, 0x00000012, 0x0000001a, 0x00000012, 0x00000013, 
			0x0000001b, 0x00000012, 0x00000014, 0x0000001c, 0x00000012, 
			0x00000015, 0x0000001d, 0x00000012, 0x00000027, 0x0000001e, 
			0x00000012, 0x00000025, 0x0000001f, 0x00000012, 0x00000026, 
			0x00000020, 0x00000012, 0x00000024, 0x00000021, 0x00000012, 
			0x00000020, 0x00000022, 0x00000012, 0x00000021, 0x00000023, 
			0x00000012, 0x00000022, 0x00000024, 0x00000012, 0x00000023, 
			0x00000025, 0x00000012, 0x00000030, 0x00000026, 0x00000012, 
			0x0000002b, 0x00000027, 0x00000012, 0x0000002c, 0x00000028, 
			0x00000012, 0x0000002e, 0x00000029, 0x00000012, 0x00000034, 
			0x0000002a, 0x00000012, 0x0000002f, 0x0000002b, 0x00000012, 
			0x00000016, 0x0000002c, 0x00000012, 0x00000017, 0x0000002d, 
			0x00000012, 0x00000018, 0x0000002e, 0x00000012, 0x00000035, 
			0x0000002f, 0x00000012, 0x00000031, 0x00000030, 0x00000012, 
			0x0000001a, 0x00000031, 0x00000012, 0x0000001b, 0x00000032, 
			0x00000012, 0x0000001c, 0x00000033, 0xff00ff00, 0x00000012, 
			0x00000065, 0x00000034, 0x00000012, 0x00000067, 0x00000035, 
			0x00000012, 0x00000068, 0x00000036, 0x00000012, 0x0000008d, 
			0x00000037, 0x00000012, 0x0000008e, 0x00000038, 0x00000012, 
			0x00000072, 0x00000039, 0x00000012, 0x00000073, 0x0000003a, 
			0x00000012, 0x00000086, 0x0000003b, 0x00000012, 0x00000087, 
			0x0000003c, 0x00000012, 0x00000088, 0x0000003d, 0x00000012, 
			0x00000074, 0x0000003e, 0x00000012, 0x0000008b, 0x0000003f, 
			0x00000012, 0x0000006e, 0x00000040, 0x00000012, 0x0000006d, 
			0x00000041, 0x00000012, 0x00000070, 0x00000042, 0x00000012, 
			0x00000071, 0x00000043, 0x00000012, 0x0000008c, 0x00000044, 
			0x00000012, 0x0000012d, 0x00000045, 0x00000012, 0x0000012e, 
			0x00000046, 0x00000012, 0x0000012f, 0x00000047, 0x00000012, 
			0x00000130, 0x00000048, 0x00000012, 0x00000075, 0x00000049, 
			0x00000012, 0x00000076, 0x0000004a, 0xff00ff00, 0x00000012, 
			0x00000057, 0x0000004b, 0x00000012, 0x00000064, 0x0000004c, 
			0x00000012, 0x00000076, 0x0000004d, 0x00000012, 0x0000008a, 
			0x0000004d, 0x00000012, 0x000000a2, 0x0000004e, 0x00000012, 
			0x000000bc, 0x0000004f, 0x00000012, 0x000000d3, 0x00000050, 
			0x00000012, 0x000000e7, 0x00000051, 0x00000012, 0x00000105, 
			0x00000052, 0x00000012, 0x00000118, 0x00000053, 0x00000012, 
			0x00000128, 0x00000054, 0x00000012, 0x00000139, 0x00000055, 
			0x00000012, 0x00000151, 0x00000056, 0x00000012, 0x00000162, 
			0x00000057, 0x00000012, 0x0000017a, 0x00000058, 0x00000012, 
			0x0000018c, 0x00000059, 0x00000012, 0x00000198, 0x0000005a, 
			0x00000012, 0x000001a4, 0x0000005b, 0x00000012, 0x000001b5, 
			0x0000005c, 0x00000012, 0x000001c6, 0x0000005d, 0x00000012, 
			0x000001d7, 0x0000005e, 0x00000012, 0x000001e7, 0x0000005e, 
			0x00000012, 0x000001f8, 0x0000005e, 0x00000012, 0x00000209, 
			0x0000005e, 0x00000012, 0x00000218, 0x0000005f, 0x00000012, 
			0x0000022a, 0x00000060, 0xff00ff00, 0x00000012, 0x0000023b, 
			0x00000061, 0xff00ff00, 0x00000002, 0x00000242, 0x0124f800, 
			0x00000002, 0x00000254, 0x00082000, 0x00000002, 0x00000263, 
			0x00084000, 0xff00ff00 };



const StringDevice driver_list_660_xml[] = {
			{"/dev/core/mproc/glink/ssr",944539910u, 728, NULL, 0, NULL },
			{"/dev/core/mproc/glink/xport_rpm",2797335449u, 744, NULL, 0, NULL },
			{"/dev/core/mproc/smem",1012060316u, 784, NULL, 0, NULL },
			{"/rpm/pmic/common",2887753651u, 836, NULL, 0, NULL },
			{"/rpm/pmic/target",3536625265u, 1416, NULL, 0, NULL },
			{"/dev/icb/rpm",2545934574u, 2012, NULL, 0, NULL }
};


extern char Image$$660_xml_DEVCONFIG_DATA$$Base[];
extern char Image$$660_xml_DEVCONFIG_DATA$$ZI$$Limit[];

const DALPROP_Target_Data DALPROP_Target_Data_660_xml = {
    DALPROP_StructPtrs_660_xml,
    sizeof(DALPROP_StructPtrs_660_xml),
    DALPROP_PropBin_660_xml,
    sizeof(DALPROP_PropBin_660_xml),
    driver_list_660_xml,
    sizeof(driver_list_660_xml)/sizeof(const StringDevice),
    DALCONFIG_CHIPINFO_FAMILY_MSM660_xml,
    Image$$660_xml_DEVCONFIG_DATA$$Base,
    Image$$660_xml_DEVCONFIG_DATA$$ZI$$Limit,
};

