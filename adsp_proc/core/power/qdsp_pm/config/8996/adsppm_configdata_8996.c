/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: adsppm_configdata_8996.c
@brief: Contains all 8996-specific data definitions for Config Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/config/8996/adsppm_configdata_8996.c#1 $
*/

#include "adsppm.h"
#include "asic.h"
#include "asic_internal.h"
#include "adsppm_utils.h"
#include "icbid.h"
#include "DDIIPCInt.h"
#include "lpass_clocks_hwio_8996.h"
#include "msmhwiobase.h"
#include "limits.h"

AsicHwioRegRangeType lpassRegRange_8996 = {LPASS_BASE, LPASS_BASE_PHYS, LPASS_BASE_SIZE};

// L2 configuration registers base address = TCM_BASE + 1.5 Meg + 128K
// Reference: Fig 8-3 in document 80-V9418-20 Rev. E
#define TCM_BASE 0x09400000
#define L2_CONFIG_BASE (TCM_BASE + 0x00180000 + 0x00020000)
AsicHwioRegRangeType l2ConfigRegRange_8996 = {L2_CONFIG_BASE, L2_CONFIG_BASE, 0x1004 /* max expected offset needed by ADPSPM */};

/**
 * Array of 8996 Core Clocks per core. Arranged by to core ID
 */
const AdsppmClkIdType coreClocks_SlimBus_8996[] = {AdsppmClk_Slimbus_Core, AdsppmClk_Slimbus2_Core};
//const AdsppmClkIdType coreClocks_Midi_8996[]    = {AdsppmClk_Midi_Core};
const AdsppmClkIdType coreClocks_HwRsp_8996[]   = {AdsppmClk_HwRsp_Core};

/**
 * Array of 8996 Master Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType masterPorts_ADSP_8996[]    = {AdsppmBusPort_Adsp_Master};
const AdsppmBusPortIdType masterPorts_DML_8996[]     = {AdsppmBusPort_Dml_Master};
const AdsppmBusPortIdType masterPorts_AIF_8996[]     = {AdsppmBusPort_Aif_Master};
const AdsppmBusPortIdType masterPorts_SlimBus_8996[] = {AdsppmBusPort_Slimbus_Master, AdsppmBusPort_Slimbus2_Master};
//const AdsppmBusPortIdType masterPorts_Midi_8996[]    = {AdsppmBusPort_Midi_Master};
const AdsppmBusPortIdType masterPorts_HWRSMP_8996[]  = {AdsppmBusPort_HwRsmp_Master};
//const AdsppmBusPortIdType masterPorts_Spdif_8996[]   = {AdsppmBusPort_Spdif_Master};
//const AdsppmBusPortIdType masterPorts_Hdmirx_8996[]  = {AdsppmBusPort_Hdmirx_Master};
const AdsppmBusPortIdType masterPorts_Hdmitx_8996[]  = {AdsppmBusPort_Hdmitx_Master};
//const AdsppmBusPortIdType masterPorts_Sif_8996[]     = {AdsppmBusPort_Sif_Master};

/**
 * Array of 8996 Slave Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType slavePorts_ADSP_8996[]    = {AdsppmBusPort_Adsp_Slave};
const AdsppmBusPortIdType slavePorts_LPM_8996[]     = {AdsppmBusPort_Lpm_Slave};
const AdsppmBusPortIdType slavePorts_DML_8996[]     = {AdsppmBusPort_Dml_Slave};
const AdsppmBusPortIdType slavePorts_AIF_8996[]     = {AdsppmBusPort_Aif_Slave};
const AdsppmBusPortIdType slavePorts_SlimBus_8996[] = {AdsppmBusPort_Slimbus_Slave, AdsppmBusPort_Slimbus2_Slave};
//const AdsppmBusPortIdType slavePorts_Midi_8996[]    = {AdsppmBusPort_Midi_Slave};
const AdsppmBusPortIdType slavePorts_AVsync_8996[]  = {AdsppmBusPort_AvSync_Slave};
const AdsppmBusPortIdType slavePorts_HWRSMP_8996[]  = {AdsppmBusPort_HwRsmp_Slave};
//const AdsppmBusPortIdType slavePorts_SRam_8996[]    = {AdsppmBusPort_Sram_Slave};
//const AdsppmBusPortIdType slavePorts_DCodec_8996[]  = {AdsppmBusPort_Dcodec_Slave};
//const AdsppmBusPortIdType slavePorts_Spdif_8996[]   = {AdsppmBusPort_Spdif_Slave};
//const AdsppmBusPortIdType slavePorts_Hdmirx_8996[]  = {AdsppmBusPort_Hdmirx_Slave};
const AdsppmBusPortIdType slavePorts_Hdmitx_8996[]  = {AdsppmBusPort_Hdmitx_Slave};
//const AdsppmBusPortIdType slavePorts_Sif_8996[]     = {AdsppmBusPort_Sif_Slave};
//const AdsppmBusPortIdType slavePorts_BSTC_8996[]    = {AdsppmBusPort_Bstc_Slave};

/**
 * Array of 8996 core descriptors. Arranged according to core ID enum
 */
const AsicCoreDescType cores_array_8996[] =
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
        {   //Adsppm_Core_Id_ADSP
                Adsppm_Core_Id_ADSP, //Core ID
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
                {ADSPPM_ARRAY(masterPorts_ADSP_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_ADSP_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_LPASS_Core
                Adsppm_Core_Id_LPASS_Core, //Core ID
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
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_LPM
                Adsppm_Core_Id_LPM, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Mem, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_LPM_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_DML
                Adsppm_Core_Id_DML, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_DML_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_DML_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_AIF
                Adsppm_Core_Id_AIF, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_AIF_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_AIF_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_SlimBus
                Adsppm_Core_Id_SlimBus, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {ADSPPM_ARRAY(coreClocks_SlimBus_8996)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_SlimBus_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_SlimBus_8996)}, //Slave port instances
                Adsppm_Instance_Id_1 //Number of core instances
        },
        {   //Adsppm_Core_Id_Midi
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
        {   //Adsppm_Core_Id_AVsync
                Adsppm_Core_Id_AVsync, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_AVsync_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_HWRSMP
                Adsppm_Core_Id_HWRSMP, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_Core_Clk, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {ADSPPM_ARRAY(coreClocks_HwRsp_8996)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_HWRSMP_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_HWRSMP_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_SRam
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
        {   //Adsppm_Core_Id_DCodec
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
        {   //Adsppm_Core_Id_Spdif
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
        {   //Adsppm_Core_Id_Hdmirx
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
        {   //Adsppm_Core_Id_Hdmitx
                Adsppm_Core_Id_Hdmitx, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_Power_Core, //Power
                        AsicRsc_None, //Core Clock
                        AsicRsc_Latency, //Sleep Latency
                        AsicRsc_MIPS_Clk | AsicRsc_MIPS_BW, //MIPS
                        AsicRsc_BW_Internal | AsicRsc_BW_External, //BW
                        AsicRsc_Thermal //Thermal
                }, //HwResource IDs
                AsicPowerDomain_LpassCore, //Power Domain
                {0, NULL}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_Hdmitx_8996)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_Hdmitx_8996)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
        {   //Adsppm_Core_Id_Sif
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
        {   //Adsppm_Core_Id_BSTC
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
        {   //Adsppm_Core_Id_HVX
                Adsppm_Core_Id_HVX, //Core ID
                {
                        AsicRsc_None, //None
                        AsicRsc_None, //Power
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

AsicCoreDescriptorArrayType cores_8996 = {ADSPPM_ARRAY(cores_array_8996)};

const AsicMemDescriptorType memories_array_8996[] =
{
        {   //Adsppm_Mem_None
                Adsppm_Mem_None, //Mem ID
                AsicPowerDomain_AON //Power Domain
        },
        {   //Adsppm_Mem_Ocmem
                Adsppm_Mem_Ocmem, //Mem ID
                AsicPowerDomain_Ocmem //Power Domain
        },
        {   //Adsppm_Mem_Lpass_LPM
                Adsppm_Mem_Lpass_LPM, //Mem ID
                AsicPowerDomain_Lpm //Power Domain
        },
        {   //Adsppm_Mem_Sram
                Adsppm_Mem_Sram, //Mem ID
                AsicPowerDomain_SRam //Power Domain
        }
};

AsicMemDescriptorArrayType memories_8996 = {ADSPPM_ARRAY(memories_array_8996)};

/**
 * Array of 8996 core clock descriptors. Arranged by core clock ID
 */
const AsicClkDescriptorType clocks_array_8996[] =
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
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_core_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbI_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbX_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Sysnoc_cbc, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_RESAMPLER_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Dml_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_DML_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
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
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_LPAIF_CSR_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Slimbus_cbc, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus_cbc, //Clk ID
                AsicClk_TypeCBC, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlAlwaysRetain, //MemCtrl Type
                .clkInfo.clkName = "audio_core_aud_slimbus_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Slimbus2_cbc, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_cbc, //Clk ID
                AsicClk_TypeCBC, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlAlwaysRetain, //MemCtrl Type
                .clkInfo.clkName = "audio_core_qca_slimbus_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
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
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_AVSYNC_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atimer_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_ATIMER_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lpm_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_LPM_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Lpm_cbc, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Lpm_cbc, //Clk ID
                AsicClk_TypeCBC, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_lpm_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_Lpass_LPM //Memory ID
        },
        {
                AdsppmClk_Csr_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_CORE_CSR_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
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
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlSW_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
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
                .clkInfo.clkName = "audio_core_peripheral_smmu_client_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sysnoc_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sysnoc_cbc, //Clk ID
                AsicClk_TypeCBC, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_sysnoc_mport_core_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Bus_Timeout_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Tlb_Preload_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_TLB_PRELOAD_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Qos_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_QOS_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Qdsp_Sway_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_OFFS, //CGCR Offset
                        HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_AhbE_Hclk, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_aon_clk", //Name
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
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_qdsp_sway_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Security_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_sysnoc_sway_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Security_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_mpu_cfg_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Wrapper_Br_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_q6_ahbm_mpu_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Core_AON, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_qos_ahbs_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Audio_Wrapper_AON, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_wrapper_bus_timeout_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_resampler_core_clk", //Name
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
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_aud_slimbus_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Slimbus2_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_qca_slimbus_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Avtimer_core, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_avsync_stc_xo_clk", //Name
                AdsppmClk_None, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Atime_core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_avsync_atime_clk", //Name
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

AsicClockDescriptorArrayType clocks_8996 = {ADSPPM_ARRAY(clocks_array_8996)};

/**
 * Arrays of 8996 register programming clocks
 */
const AdsppmClkIdType regProgClocks_Dml_8996[]      = {AdsppmClk_Dml_Hclk};
const AdsppmClkIdType regProgClocks_Aif_8996[]      = {AdsppmClk_Aif_Csr_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus_8996[]  = {AdsppmClk_Slimbus_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus2_8996[] = {AdsppmClk_Slimbus2_Hclk};
//const AdsppmClkIdType regProgClocks_Midi_8996[]     = {AdsppmClk_Midi_Hclk};
const AdsppmClkIdType regProgClocks_HwRsmp_8996[]   = {AdsppmClk_HwRsp_Hclk};
const AdsppmClkIdType regProgClocks_AvSync_8996[]   = {AdsppmClk_AvSync_Hclk};
const AdsppmClkIdType regProgClocks_Lpm_8996[]      = {AdsppmClk_Lpm_Hclk};
const AdsppmClkIdType regProgClocks_Sram_8996[]     = {AdsppmClk_Sram_Hclk};
//const AdsppmClkIdType regProgClocks_Spdif_8996[]    = {AdsppmClk_Spdif_Hsclk};
//const AdsppmClkIdType regProgClocks_Hdmirx_8996[]   = {AdsppmClk_Hdmirx_Hclk};
const AdsppmClkIdType regProgClocks_Hdmitx_8996[]   = {AdsppmClk_Hdmitx_Hclk};
//const AdsppmClkIdType regProgClocks_Sif_8996[]      = {AdsppmClk_Sif_Hclk};
//const AdsppmClkIdType regProgClocks_Bstc_8996[]     = {AdsppmClk_Bstc_Hclk};
//const AdsppmClkIdType regProgClocks_Dcodec_8996[]   = {AdsppmClk_Dcodec_Hclk};
const AdsppmClkIdType regProgClocks_Adsp_8996[]     = {AdsppmClk_Adsp_Hmclk, AdsppmClk_Adsp_Hsclk};

/**
 * Array of 8996 Bus port descriptors arranged by Bus port ID
 */
const AsicBusPortDescriptorType busPorts_array_8996[] =
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
                AdsppmBusPort_Adsp_Master, //ID
                AsicBusPort_AhbE_M | AsicBusPort_Ext_M,  //Connection
                AdsppmClk_Adsp_Hmclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_PROC}, //icbarb ID
                AdsppmBusPort_Adsp_Master //Access port
        },
        {
                AdsppmBusPort_Dml_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Dml_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Aif_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Aif_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Slimbus_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Slimbus_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Master, //ID
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Slimbus2_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
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
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_HwRsp_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //ID
                AsicBusPort_Ext_M, //Connection
                AdsppmClk_AhbX_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
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
                AsicBusPort_AhbI_M, //Connection
                AdsppmClk_Hdmitx_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
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
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Dml_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Dml_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Aif_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Aif_Csr_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Aif_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Slimbus_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Slimbus2_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus2_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Midi_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_HwRsp_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_HwRsmp_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_AvSync_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_AvSync_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_AvSync_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Lpm_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Lpm_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Lpm_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Sram_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Ext_Ahb_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_AhbE_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Ddr_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_EBI1}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Ocmem_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_OCMEM}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_PerifNoc_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_BLSP_1}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Spdif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Hdmirx_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port

        },
        {
                AdsppmBusPort_Hdmitx_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Hdmitx_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Hdmitx_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Sif_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Bstc_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Dcodec_Slave, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Core, //ID
                0, //Connection
                AdsppmClk_None, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_None //Access port
        },
        {
                AdsppmBusPort_Adsp_Slave, //ID
                AsicBusPort_AhbE_S, //Connection
                AdsppmClk_Adsp_Hsclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Adsp_8996)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Adsp_Master //Access port
        }
};

AsicBusPortDescriptorArrayType busPorts_8996 = {ADSPPM_ARRAY(busPorts_array_8996)};

/**
 * List of supported external bus routes
 */
const AdsppmBusRouteType extBusRoutes_array_8996[] =
{
        {
                AdsppmBusPort_Adsp_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        },
        {
                AdsppmBusPort_Adsp_Master, //master
                AdsppmBusPort_PerifNoc_Slave //slave
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        }
};

AsicBusRouteArrayType extBusRoutes_8996 = {ADSPPM_ARRAY(extBusRoutes_array_8996)};

const AdsppmBusRouteType mipsBwRoutes_array_8996[] =
{
        {
                AdsppmBusPort_Adsp_Master,
                AdsppmBusPort_Ddr_Slave
        }
};

AsicBusRouteArrayType mipsBwRoutes_8996 = {ADSPPM_ARRAY(mipsBwRoutes_array_8996)};

/**
* Array of register programming speeds in byte/sec
*/
const uint64 regProgSpeeds_array_8996[] =
{
        0,          //Adsppm_RegProg_None
        19200000*4, //Adsppm_RegProg_Norm
        61410000*4  //Adsppm_RegProg_Fast
};

AsicRegProgSpeedArrayType regProgSpeeds_8996 = {ADSPPM_ARRAY(regProgSpeeds_array_8996)};

/**
 * Array of power domain descriptors
 */
const AsicPowerDomainDescriptorType pwrDomains_array_8996[] =
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
                "VDD_AUDIO_CORE", //Name
                AsicRsc_Power_Core, //Type
                AdsppmClk_None, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },
        {
                AsicPowerDomain_Lpm, //Id
                "", //Name
                AsicRsc_Power_Mem, //Type
                AdsppmClk_Lpm_cbc, //Clock ID
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

AsicPwrDescriptorArrayType pwrDomains_8996 = {ADSPPM_ARRAY(pwrDomains_array_8996)};

/**
 * Table of DDR compensation factors to be applied at different BW ranges
 * This is used to compensate for bus latencies/cache misses
 * Latency/Snoc floor vote also updated
 */
const AsicCompensatedDdrBwTableEntryType compensatedDdrBw_array_8996[] = {
        //        bwThreshold,            bwVote,   latencyVote,  snocFloorVote,    honestFlag
        {            10000000,         153000000,            0,               0,           0 },
        {            60000000,         399000000,            0,               0,           0 },
        {            96000000,                -1,          600,              50,           1 },
        {           120000000,                -1,          450,              50,           1 },
        {           155000000,                -1,          300,             100,           1 },
        {           230000000,                -1,          300,             150,           1 },
        {           250000000,                -1,          300,             200,           1 },
        {          ULLONG_MAX,                -1,          300,             266,           1 }
};

AsicCompensatedDdrBwTableType compensatedDdrBwTable_8996 = {ADSPPM_ARRAY(compensatedDdrBw_array_8996)};

const AsicCompensatedAhbBwTableEntryType compensatedAhbBw_array_8996[] = {
    // bwThreshold,            bwVote
    {      9784305,          61440000 }, // target SVS2  19.2 Mhz
    {     19568611,         122880000 }, // target SVS2  38.4 Mhz
    {     39137222,         245760000 }, // target SVS   76.8 Mhz
    {    490240000,         490240000 }, // target NOM  153.2 Mhz
    {   ULLONG_MAX,                -1 },
};

AsicCompensatedAhbBwTableType compensatedAhbBwTable_8996 = {ADSPPM_ARRAY(compensatedAhbBw_array_8996)};

const AsicThreadLoadingInfoType threadLoadingData_array_8996[] =
{
        { 90,   10,      0,     0 },    // oneDominantThreadLoading
        { 65,   25,     10,     0 },    // twoDominantThreadLoading
        { 50,   30,     20,     0 }     // threeDominantThreadLoading
};

AsicThreadLoadingInfoTableType threadLoadingData_8996 = {ADSPPM_ARRAY(threadLoadingData_array_8996)};

const uint32 audioVoiceCppFactors_array_8996[] =
{
        3500,    // one thread active CPP   * 1000
        2500,    // two thread active CPP   * 1000
        1700,    // three thread active CPP * 1000
           0     // four thread active CPP  * 1000
};

AsicAudioVoiceCppTrendFactorsType audioVoiceCppFactors_8996 = {
        ADSPPM_ARRAY(audioVoiceCppFactors_array_8996)};

// Table for cache partition configuration.
// Audio and voice classes are grouped together for the purposes
// of determining class concurrency.
// Client class combinations not present in the table will default
// to a shared cache (no partitioning).
const AsicCachePartitionConfigType cachePartitionConfig_array_8996[] = {

    // aggregateClass,                mainPartSize

    { MMPM_AUDIO_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

    { MMPM_VOICE_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

    { MMPM_AUDIO_CLIENT_CLASS |
      MMPM_VOICE_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

};

AsicCachePartitionConfigTableType cachePartitionConfigTable_8996 =
    { ADSPPM_ARRAY(cachePartitionConfig_array_8996) };

const AsicBwConcurrencySettingsType bwConcurrencySettings_8996 =
{

    3,          /* adspDdrConcurrencyVotersThreshold*/
    15000000,   /* adspDdrBwAbValueThreshol*/
    {
        256,    /* adspDdrConcurrencyFactor = 1*/
        384,    /* adspDdrConcurrencyFactor = 1.5*/
        512,    /* adspDdrConcurrencyFactor = 2*/
    }
};

const AsicAdspToAhbeFreqTableEntry adspToAhbeFreq_array_8996v1[] = {
    // adspFreqHz,      abheFreqHz
    {   172800000,       38400000 }, // SVS2 f-max
    {   249600000,       76800000 }, // SVS f-max
    {   422400000,      153600000 }, // nominal f-max
    {   480600000,      153600000 }, // turbo ADSP f-max (nom. AHBE, no turbo)
};

AsicAdspToAhbeFreqTableType adspToAhbeFreqTable_8996v1 = 
    { ADSPPM_ARRAY(adspToAhbeFreq_array_8996v1) };

const AsicAdspToAhbeFreqTableEntry adspToAhbeFreq_array_8996v2[] = {
    // adspFreqHz,      abheFreqHz
    {   297600000,       38400000 }, // SVS2 f-max
    {   460800000,       76800000 }, // SVS f-max
    {   652800000,      153600000 }, // nominal f-max
    {   729600000,      153600000 }, // turbo ADSP f-max (nom. AHBE, no turbo)
};

AsicAdspToAhbeFreqTableType adspToAhbeFreqTable_8996v2 = 
    { ADSPPM_ARRAY(adspToAhbeFreq_array_8996v2) };

const AsicAdspToAhbeFreqTableEntry adspToAhbeFreq_array_8996v3[] = {
    // adspFreqHz,      abheFreqHz
    {   297600000,       38400000 }, // SVS2 f-max
    {   480000000,       76800000 }, // SVS f-max
    {   652800000,      153600000 }, // nominal f-max
    {   825600000,      153600000 }, // turbo ADSP f-max (nom. AHBE, no turbo)
};

AsicAdspToAhbeFreqTableType adspToAhbeFreqTable_8996v3 = 
    { ADSPPM_ARRAY(adspToAhbeFreq_array_8996v3) };

//Table to lookup MPPS threshold values for different client classes
//Class Name, Threshold value
const AsicAdspCacheSizeMPPSThresholdTableEntry adspcachesizeMPPSThreshold_array_8996[] = {
    {   MMPM_AUDIO_CLIENT_CLASS,  0  },

};

AsicAdspCacheSizeMPPSThresholdTableType   adspCacheSizeMPPSThreshold_8996 = {ADSPPM_ARRAY(adspcachesizeMPPSThreshold_array_8996)};

const AsicAdspCacheSizeBWScalingTableEntry adspCacheSizeBwScaling_array_8996[] = {
    {   FULL_SIZE,             67  },
    {   THREE_QUARTER_SIZE,   100  },
    {   HALF_SIZE,            100  },    
};

AsicAdspCacheSizeBWScalingTableType   adspCacheSizeBwScaling_8996 = {ADSPPM_ARRAY(adspCacheSizeBwScaling_array_8996)};

const AsicFeatureDescType features_8996 [AsicFeatureId_enum_max] =
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
                AsicFeatureState_Enabled,
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
                AsicFeatureState_Enabled,
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
                AsicFeatureState_Enabled,
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
                AsicFeatureState_Enabled,
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
                AsicFeatureState_Enabled,
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
                0, // min (not used)
                0, // max (not used)
        },
        // AsicFeatureId_CacheSizeMPPSThreshold
        {
                AsicFeatureState_Disabled,
                0, // min (not used)
                0, // max (not used)
        },
        // AsicFeatureId_CacheSizeBWScaling
        {
                AsicFeatureState_Enabled,
                0, // min (not used)
                0, // max (not used)
        },		
};

