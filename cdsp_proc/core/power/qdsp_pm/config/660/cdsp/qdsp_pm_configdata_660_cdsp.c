/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: adsppm_configdata_660.c
@brief: Contains all 660-specific data definitions for Config Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/config/660/cdsp/qdsp_pm_configdata_660_cdsp.c#1 $
*/

#include "adsppm.h"
#include "asic.h"
#include "asic_internal.h"
#include "adsppm_utils.h"
#include "icbid.h"
#include "DDIIPCInt.h"
#include "qdsp_pm_clocks_hwio_660_cdsp.h"
#include "msmhwiobase.h"
#include "limits.h"

AsicHwioRegRangeType lpassRegRange_660 = {0, 0, 0};

// L2 configuration registers base address = TCM_BASE + 1.5 Meg + 128K
// Reference: Fig 8-3 in document 80-V9418-22 Rev C
#define TCM_BASE 0x17400000
#define L2_CONFIG_BASE (TCM_BASE + 0x00180000 + 0x00020000)
//AsicHwioRegRangeType l2ConfigRegRange_660 = {L2_CONFIG_BASE, L2_CONFIG_BASE, 0x1004 /* max expected offset needed by ADPSPM */};
AsicHwioRegRangeType l2ConfigRegRange_660 = {0, 0, 0 /* max expected offset needed by ADPSPM */};

/**
 * Array of 660 Master Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType masterPorts_ADSP_660[]    = {AdsppmBusPort_Adsp_Master};

/**
 * Array of 660 Slave Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType slavePorts_ADSP_660[]    = {AdsppmBusPort_Adsp_Slave};

/**
 * Array of 660 core descriptors. Arranged according to core ID enum
 */
const AsicCoreDescType cores_array_660[] =
{
        {   //Adsppm_Core_Id_None
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Q6_DSP
                Adsppm_Core_Id_Q6_DSP, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_ADSP, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_Adsp, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_ADSP_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_ADSP_660)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_LPASS_Core
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_LPM
                Adsppm_Core_Id_None, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_DML
                Adsppm_Core_Id_None, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_AIF
                Adsppm_Core_Id_AIF, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_SlimBus
                Adsppm_Core_Id_SlimBus, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Midi
                Adsppm_Core_Id_Midi, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_AVsync
                Adsppm_Core_Id_AVsync, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_HWRSMP
                Adsppm_Core_Id_HWRSMP, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_SRam
                Adsppm_Core_Id_SRam, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_DCodec
                Adsppm_Core_Id_DCodec, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Spdif
                Adsppm_Core_Id_Spdif, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Hdmirx
                Adsppm_Core_Id_Hdmirx, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances

        },
        {   //Adsppm_Core_Id_Hdmitx
                Adsppm_Core_Id_Hdmitx, //Core ID
                {
						AsicRsc_None, //None
						AsicRsc_None, //Power
						AsicRsc_None, //Core Clock
						AsicRsc_None, //Sleep Latency
						AsicRsc_None, //MIPS
						AsicRsc_None, //BW
						AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_Sif
                Adsppm_Core_Id_Sif, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_BSTC
                Adsppm_Core_Id_BSTC, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_AON, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_None //Number of core instances
        },
        {   //Adsppm_Core_Id_HVX //TODO: check the Rsc & ports usage
                Adsppm_Core_Id_HVX, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Hvx, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_None, //Sleep Latency
                        AsicRsc_None, //MIPS
                        AsicRsc_None, //BW
                        AsicRsc_None //Thermal
                }, //HwResource IDs
                AsicPowerDomain_Hvx, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {0, NULL}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        }
};

AsicCoreDescriptorArrayType cores_660 = {ADSPPM_ARRAY(cores_array_660)};

const AsicMemDescriptorType memories_array_660[] =
{
        {   //Adsppm_Mem_None
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
        {   //Adsppm_Mem_Ocmem
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
        {   //Adsppm_Mem_Lpass_LPM
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
        {   //Adsppm_Mem_Sram
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
};

AsicMemDescriptorArrayType memories_660 = {ADSPPM_ARRAY(memories_array_660)};

/**
 * Array of 660 core clock descriptors. Arranged by core clock ID
 */
const AsicClkDescriptorType clocks_array_660[AdsppmClk_EnumMax] =
{
        {
                AdsppmClk_None, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Adsp_Core, //Clk ID
                AsicClk_TypeNpa, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "/clk/cpu", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Ahb_Root, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbI_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbX_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Dml_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID

        },
        {
                AdsppmClk_Aif_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Aif_Csr_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_cbc, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_cbc, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Midi_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atimer_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lpm_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID

        },
        {
                AdsppmClk_Lpm_cbc, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID

        },
        {
                AdsppmClk_Csr_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Dcodec_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Spdif_Hmclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Spdif_Hsclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Hdmirx_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Hdmitx_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID

        },
        {
                AdsppmClk_Sif_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Bstc_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Smmu_Adsp_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Smmu_Lpass_Hclk, //Clk ID
				AsicClk_TypeDalEnable, //Clk Type
				AsicClk_CntlSW, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "turing_wrapper_q6_smmu_axi_clk", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID 
        },
        {
                AdsppmClk_Sysnoc_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sysnoc_cbc, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Bus_Timeout_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Tlb_Preload_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Qos_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Qdsp_Sway_Hclk, //Clk ID
				AsicClk_TypeNone, //Clk Type
				AsicClk_CntlNone, //Cntl Type
				AsicClk_MemCntlNone, //MemCtrl Type
				.clkInfo.clkName = "", //Name
				AdsppmClk_None, //Source
				Adsppm_Mem_None //Memory ID

	   },
        {
                AdsppmClk_AhbE_Hclk, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_aon_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Adsp_Hmclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "q6ss_ahbm_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Adsp_Hsclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "q6ss_ahbs_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sram_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lcc_Hclk, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Security_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_sysnoc_sway_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Security_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_mpu_cfg_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Br_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_q6_ahbm_mpu_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Core_AON, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_qos_ahbs_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Wrapper_AON, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "turing_wrapper_bus_timeout_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Midi_Core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Xo, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Bt, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AvSync_Fm, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_Core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Avtimer_core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atime_core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atime2_core, //Clk ID
                AsicClk_TypeNone, //Clk Type
                AsicClk_CntlNone, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        }
};

AsicClockDescriptorArrayType clocks_660 = {ADSPPM_ARRAY(clocks_array_660)};

/**
 * Arrays of 660 register programming clocks
 */
const AdsppmClkIdType regProgClocks_Adsp_660[]     = {AdsppmClk_Adsp_Hmclk, AdsppmClk_Adsp_Hsclk};

/**
 * Array of 660 Bus port descriptors arranged by Bus port ID
 */
const AsicBusPortDescriptorType busPorts_array_660[] =
{
        {
                AdsppmBusPort_None, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Q6DSP_Master, //ID
                AsicBusPort_AhbE_M,  //Connection
                AdsppmClk_Adsp_Hmclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_CDSP_PROC}, //icbarb ID
                AdsppmBusPort_Q6DSP_Master //Access port
        },
        {
                AdsppmBusPort_Dml_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Aif_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Slimbus_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Midi_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Spdif_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Hdmirx_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port

        },
        {
                AdsppmBusPort_Hdmitx_Master, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Sif_Master, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_APPSS_PROC}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Dml_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Aif_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Slimbus_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Midi_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_AvSync_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Lpm_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Sram_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Ddr_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port		/*access port applicable only in case data is triggered other than Q6 to DDR*/
        },
        {
                AdsppmBusPort_Ocmem_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_PerifNoc_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Spdif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Hdmirx_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port

        },
        {
                AdsppmBusPort_Hdmitx_Slave, //ID
                AsicBusPort_None, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Sif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Bstc_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Dcodec_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Core, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Adsp_Slave, //ID
                AsicBusPort_AhbE_S, //Connection
                AdsppmClk_Adsp_Hsclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Adsp_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_CDSP}, //icbarb ID
                AdsppmBusPort_Q6DSP_Master //Access port
        }
};

AsicBusPortDescriptorArrayType busPorts_660 = {ADSPPM_ARRAY(busPorts_array_660)};

/**
 * List of supported external bus routes
 */
const AdsppmBusRouteType extBusRoutes_array_660[] =
{
        {
                AdsppmBusPort_Q6DSP_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        },
};

AsicBusRouteArrayType extBusRoutes_660 = {ADSPPM_ARRAY(extBusRoutes_array_660)};

const AdsppmBusRouteType mipsBwRoutes_array_660[] =
{
        {
                AdsppmBusPort_Q6DSP_Master,
                AdsppmBusPort_Ddr_Slave
        }
};

AsicBusRouteArrayType mipsBwRoutes_660 = {ADSPPM_ARRAY(mipsBwRoutes_array_660)};

/**
* Array of register programming speeds in byte/sec
*/
const uint64 regProgSpeeds_array_660[] =
{
        0,          //Adsppm_RegProg_None
        19200000*4, //Adsppm_RegProg_Norm
        61410000*4  //Adsppm_RegProg_Fast
};

AsicRegProgSpeedArrayType regProgSpeeds_660 = {ADSPPM_ARRAY(regProgSpeeds_array_660)};

/**
 * Array of power domain descriptors
 */
const AsicPowerDomainDescriptorType pwrDomains_array_660[] =
{
        {
                AsicPowerDomain_AON, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Adsp, //Id
                "/core/cpu/latency", //Name
                AsicRsc_Power_ADSP, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_LpassCore, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Lpm, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_SRam, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Ocmem, //Id
                "", //Name
                AsicRsc_None, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Hvx, //Id
                "/clk/hvx", //Name
                AsicRsc_Power_Hvx, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        }
};

AsicPwrDescriptorArrayType pwrDomains_660 = {ADSPPM_ARRAY(pwrDomains_array_660)};

/**
 * Table of DDR compensation factors to be applied at different BW ranges
 * This is used to compensate for bus latencies/cache misses
 * Latency/Snoc floor vote also updated
 */
const AsicCompensatedDdrBwTableEntryType compensatedDdrBw_array_660[] = {
        //        bwThreshold,            bwVote,   latencyVote,  snocFloorVote,    honestFlag
        {            35000000,         399000000,            0,              75,            0 },
        {            85000000,                -1,          800,              75,            1 },
        {           230000000,                -1,          450,             120,            1 },
        {           345000000,                -1,          300,             160,            1 },
		{          ULLONG_MAX,                -1,          230,             200,            1 }
};

AsicCompensatedDdrBwTableType compensatedDdrBwTable_660 = {ADSPPM_ARRAY(compensatedDdrBw_array_660)};

const AsicCompensatedAhbBwTableEntryType compensatedAhbBw_array_660[] = {
    // bwThreshold,            bwVote
    {      9784305,          61440000 }, // target SVS2  19.2 Mhz
    {     19568611,         122880000 }, // target SVS2  38.4 Mhz
    {     39137222,         245760000 }, // target SVS   76.8 Mhz
    {    490240000,         490240000 }, // target NOM  153.2 Mhz
    {   ULLONG_MAX,                -1 },
};

AsicCompensatedAhbBwTableType compensatedAhbBwTable_660 = {ADSPPM_ARRAY(compensatedAhbBw_array_660)};

const AsicThreadLoadingInfoType threadLoadingData_array_660[] =
{
        { 90,   10,      0,     0 },    // oneDominantThreadLoading
        { 65,   35,      0,     0 },    // twoDominantThreadLoading
        { 35,   60,      0,     0 }     // threeDominantThreadLoading
};

AsicThreadLoadingInfoTableType threadLoadingData_660 = {ADSPPM_ARRAY(threadLoadingData_array_660)};

const uint32 audioVoiceCppFactors_array_660[] =
{
        3300,    // one thread active CPP   * 1000
        2300,    // two thread active CPP   * 1000
        1700,    // three thread active CPP * 1000
           0     // four thread active CPP  * 1000
};

AsicAudioVoiceCppTrendFactorsType audioVoiceCppFactors_660 = {
        ADSPPM_ARRAY(audioVoiceCppFactors_array_660)};


//TODO: Should only compute Class be retained??
// Table for cache partition configuration.
// Audio and voice classes are grouped together for the purposes
// of determining class concurrency.
// Client class combinations not present in the table will default
// to a shared cache (no partitioning).
const AsicCachePartitionConfigType cachePartitionConfig_array_660[] = {

    // aggregateClass,                mainPartSize

    { MMPM_STREAMING_1HVX_CLIENT_CLASS  |
      MMPM_COMPUTE_CLIENT_CLASS,      		HALF_SIZE }, // 2 way AV/comp

    { MMPM_STREAMING_2HVX_CLIENT_CLASS  |
      MMPM_COMPUTE_CLIENT_CLASS,      		HALF_SIZE }, // 2 way AV/comp

    { MMPM_STREAMING_1HVX_CLIENT_CLASS |
      MMPM_STREAMING_2HVX_CLIENT_CLASS  |
      MMPM_COMPUTE_CLIENT_CLASS,      		HALF_SIZE }, // 2 way AV/comp

};

AsicCachePartitionConfigTableType cachePartitionConfigTable_660 =
    { ADSPPM_ARRAY(cachePartitionConfig_array_660) };

const AsicBwConcurrencySettingsType bwConcurrencySettings_660 =
{

    3,          /* adspDdrConcurrencyVotersThreshold*/
    15000000,   /* adspDdrCompensatedBWThreshold*/
    {
        256,    /* adspDdrConcurrencyFactor = 1*/
        384,    /* adspDdrConcurrencyFactor = 1.5*/
        512,    /* adspDdrConcurrencyFactor = 2*/
    }
};

const AsicAdspToAhbeFreqTableEntry adspToAhbeFreq_array_660[] = {
     // adspFreqHz,      abheFreqHz
    {   144000000,       51200000 }, // Min SVS f-max
    {   297600000,       51200000 }, // Low SVS f-max
    {   480000000,      102400000 }, // SVS f-max
    {   652800000,      204800000 }, // nominal f-max
    {   825600000,      204800000 }, // turbo f-max
};

AsicAdspToAhbeFreqTableType adspToAhbeFreqTable_660 = 
    { ADSPPM_ARRAY(adspToAhbeFreq_array_660) };

//Table to lookup MPPS threshold values for different client classes
//Class Name, Threshold value
//TODO: to check the client class for this table
const AsicAdspCacheSizeMPPSThresholdTableEntry adspcachesizeMPPSThreshold_array_660[] = {
    {   MMPM_COMPUTE_CLIENT_CLASS,  100  },

};

AsicAdspCacheSizeMPPSThresholdTableType  adspCacheSizeMPPSThreshold_660 = {ADSPPM_ARRAY(adspcachesizeMPPSThreshold_array_660)};

const AsicAdspCacheSizeBWScalingTableEntry adspcachesizebwscaling_array_660[] = {
    {   FULL_SIZE,             67  },
    {   THREE_QUARTER_SIZE,   100  },
    {   HALF_SIZE,            100  },    
};

AsicAdspCacheSizeBWScalingTableType  adspcachesizebwscaling_660 = {ADSPPM_ARRAY(adspcachesizebwscaling_array_660)};
	
const AsicFeatureDescType features_660 [AsicFeatureId_enum_max] =
{
        //AsicFeatureId_Adsp_Clock_Scaling
        {
                AsicFeatureState_Enabled,
#ifdef ADSPPM_TEST
                19, //min MHz
#else
                80, //min MHz
#endif
                825, //max MHz
        },
        //AsicFeatureId_Adsp_LowTemp_Voltage_Restriction
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Adsp_PC
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Ahb_Scaling
        {
                AsicFeatureState_Disabled,
                76000000, //min bytes per second corresponds to 19Mhz clock
                614400000, //max bytes per second
        },
        //AsicFeatureId_Ahb_Sw_CG
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Ahb_DCG
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LpassCore_PC
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LpassCore_PC_TZ_Handshake
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_Bus_Scaling
        {
                AsicFeatureState_Enabled,
                32768, //min bytes per second
                0x7FFFFFFF, //max bytes per second
        },
        //AsicFeatureId_CoreClk_Scaling
        {
                AsicFeatureState_Enabled,
                0, //min Hz
                307200000, //max Hz
        },
        //AsicFeatureId_Min_Adsp_BW_Vote
        {
                AsicFeatureState_Enabled,
                10000000, //min bytes per second
                0x7FFFFFFF, //max bytes per second
        },
        //AsicFeatureId_InitialState
        {
                AsicFeatureState_Enabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_TimelineOptimisationMips
        {
                AsicFeatureState_Disabled,
                240, //min MIPS for periodic clients
                905  //max MIPS value
        },
        //AsicFeatureId_TimelineOptimisationBw
        {
                AsicFeatureState_Disabled,
                76000000*8, //min ext BW in bytes per second (targeting above 76Mhz SNOC clk)
                0x7FFFFFFF, //max ext BW in bytes per second
        },
        //AsicFeatureId_TimelineOptimisationAhb
        {
                AsicFeatureState_Disabled,
                60000000, //min AHB clock in Hz
                153600000, //max AHB clock in Hz
        },
        //AsicFeatureId_LpassClkSleepOptimization
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_LPMRetention
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        //AsicFeatureId_DomainCoreClocks
        {
                AsicFeatureState_Disabled,
                0, //min
                0, //max
        },
        // AsicFeatureId_CachePartitionControl
        {
                AsicFeatureState_Disabled,
                0, // min (not used)
                0, // max (not used)
        },
        // AsicFeatureId_DcvsControl
        {
                AsicFeatureState_Enabled,
                0, // min (not used)
                0, // max (not used)
        },
        // AsicFeatureId_AhbeScaling
        {
                AsicFeatureState_Enabled,
                204800000, //min bytes per second corresponds to 51.2MHz clock (51.2M * 32 /8)
                819200000, //max bytes per secondcorresponds to 204.8Mhz clock
        },
        // AsicFeatureId_CacheSizeMPPSThreshold
        {
                AsicFeatureState_Disabled,
                0, // min (not used)
                0, // max (not used)
        },
        // AsicFeatureId_CacheSizeBWScaling
        {
                AsicFeatureState_Disabled,
                0, // min (not used)
                0, // max (not used)
        },
		// AsicFeatureId_ComputeDSP
		{
				AsicFeatureState_Enabled,
				0, // min (not used)
				0, // max (not used)
		},
};

