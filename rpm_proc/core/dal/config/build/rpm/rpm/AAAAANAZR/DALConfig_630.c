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
extern void * glink_ssr_devcfg_config_630_xml;
extern void * xport_rpm_devcfg_proc_info_630_xml;
extern void * xport_rpm_devcfg_remote_procs_630_xml;
extern void * xport_rpm_devcfg_toc_630_xml;
extern void * icb_rpm_system_630_xml;

const void * DALPROP_StructPtrs_630_xml[6] =  {
	&glink_ssr_devcfg_config_630_xml,
	&xport_rpm_devcfg_proc_info_630_xml,
	&xport_rpm_devcfg_remote_procs_630_xml,
	&xport_rpm_devcfg_toc_630_xml,
	&icb_rpm_system_630_xml,
	 0 };
const uint32 DALPROP_PropBin_630_xml[] = {

			0x00000190, 0x00000020, 0x000000ac, 0x000000bc, 0x000000bc, 
			0x00000001, 0x0200009b, 0x00000168, 0x666e6f63, 0x70006769, 
			0x5f636f72, 0x6f666e69, 0x6d657200, 0x5f65746f, 0x636f7270, 
			0x6f740073, 0x63740063, 0x625f7273, 0x5f657361, 0x656d616e, 
			0x73637400, 0x61625f72, 0x6d006573, 0x78657475, 0x66666f5f, 
			0x73746573, 0x6e6f7700, 0x6f5f6563, 0x65736666, 0x73007374, 
			0x65747379, 0x4544006d, 0x4c554146, 0x52465f54, 0x45555145, 
			0x0059434e, 0x4d495451, 0x415f5245, 0x41425f43, 0x51004553, 
			0x454d4954, 0x41425f52, 0x00004553, 0x45524f43, 0x504f545f, 
			0x5253435f, 0x00000000, 0x00000007, 0x00040000, 0x00041000, 
			0x00042000, 0x00043000, 0x00044000, 0x00045000, 0x00046000, 
			0x00047000, 0x00000001, 0x000d4000, 0x000d4004, 0x00000012, 
			0x00000000, 0x00000000, 0xff00ff00, 0x00000012, 0x00000007, 
			0x00000001, 0x00000012, 0x00000011, 0x00000002, 0x00000012, 
			0x0000001e, 0x00000003, 0xff00ff00, 0x00000011, 0x00000022, 
			0x00000000, 0x00000002, 0x00000031, 0x01f00000, 0x00000014, 
			0x0000003b, 0x00000000, 0x00000014, 0x00000049, 0x00000024, 
			0xff00ff00, 0x00000012, 0x00000057, 0x00000004, 0xff00ff00, 
			0x00000002, 0x0000005e, 0x0124f800, 0x00000002, 0x00000070, 
			0x00082000, 0x00000002, 0x0000007f, 0x00084000, 0xff00ff00 };



const StringDevice driver_list_630_xml[] = {
			{"/dev/core/mproc/glink/ssr",944539910u, 236, NULL, 0, NULL },
			{"/dev/core/mproc/glink/xport_rpm",2797335449u, 252, NULL, 0, NULL },
			{"/dev/core/mproc/smem",1012060316u, 292, NULL, 0, NULL },
			{"/dev/icb/rpm",2545934574u, 344, NULL, 0, NULL }
};


extern char Image$$630_xml_DEVCONFIG_DATA$$Base[];
extern char Image$$630_xml_DEVCONFIG_DATA$$ZI$$Limit[];

const DALPROP_Target_Data DALPROP_Target_Data_630_xml = {
    DALPROP_StructPtrs_630_xml,
    sizeof(DALPROP_StructPtrs_630_xml),
    DALPROP_PropBin_630_xml,
    sizeof(DALPROP_PropBin_630_xml),
    driver_list_630_xml,
    sizeof(driver_list_630_xml)/sizeof(const StringDevice),
    DALCONFIG_CHIPINFO_FAMILY_MSM630_xml,
    Image$$630_xml_DEVCONFIG_DATA$$Base,
    Image$$630_xml_DEVCONFIG_DATA$$ZI$$Limit,
};

