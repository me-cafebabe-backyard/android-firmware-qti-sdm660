/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: adsppm_configdata_660.c
@brief: Contains all 660-specific data definitions for Config Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/config/660/adsp_slpi/qdsp_pm_configdata_660_adsp_slpi.c#1 $
*/

#include "adsppm.h"
#include "asic.h"
#include "asic_internal.h"
#include "adsppm_utils.h"
#include "icbid.h"
#include "DDIIPCInt.h"
#include "qdsp_pm_clocks_hwio_660_adsp_slpi.h"
#include "msmhwiobase.h"
#include "limits.h"

AsicHwioRegRangeType lpassRegRange_660 = {LPASS_BASE, LPASS_BASE_PHYS, LPASS_BASE_SIZE};

// L2 configuration registers base address = TCM_BASE + 1.5 Meg + 128K
// Reference: Fig 8-3 in document 80-V9418-22 Rev C
#define TCM_BASE 0x15C00000
#define L2_CONFIG_BASE (TCM_BASE + 0x00180000 + 0x00020000)
AsicHwioRegRangeType l2ConfigRegRange_660 = {L2_CONFIG_BASE, L2_CONFIG_BASE, 0x1004 /* max expected offset needed by ADPSPM */};
//AsicHwioRegRangeType l2ConfigRegRange_660 = {0, 0, 0 /* max expected offset needed by ADPSPM */};

/**
 * Array of 660 Core Clocks per core. Arranged by to core ID
 */
const AdsppmClkIdType coreClocks_SlimBus_660[] = {AdsppmClk_Slimbus_Core, AdsppmClk_Slimbus2_Core};
const AdsppmClkIdType coreClocks_HwRsp_660[]   = {AdsppmClk_HwRsp_Core};

/**
 * Array of 660 Master Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType masterPorts_ADSP_660[]    = {AdsppmBusPort_Adsp_Master};
const AdsppmBusPortIdType masterPorts_DML_660[]     = {AdsppmBusPort_Dml_Master};
const AdsppmBusPortIdType masterPorts_AIF_660[]     = {AdsppmBusPort_Aif_Master};
const AdsppmBusPortIdType masterPorts_SlimBus_660[] = {AdsppmBusPort_Slimbus_Master, AdsppmBusPort_Slimbus2_Master};
const AdsppmBusPortIdType masterPorts_HWRSMP_660[]  = {AdsppmBusPort_HwRsmp_Master};
const AdsppmBusPortIdType masterPorts_Hdmitx_660[]  = {AdsppmBusPort_Hdmitx_Master};

/**
 * Array of 660 Slave Bus Ports per core. Arranged by to core ID
 */
const AdsppmBusPortIdType slavePorts_ADSP_660[]    = {AdsppmBusPort_Adsp_Slave};
const AdsppmBusPortIdType slavePorts_LPM_660[]     = {AdsppmBusPort_Lpm_Slave};
const AdsppmBusPortIdType slavePorts_DML_660[]     = {AdsppmBusPort_Dml_Slave};
const AdsppmBusPortIdType slavePorts_AIF_660[]     = {AdsppmBusPort_Aif_Slave};
const AdsppmBusPortIdType slavePorts_SlimBus_660[] = {AdsppmBusPort_Slimbus_Slave, AdsppmBusPort_Slimbus2_Slave};
const AdsppmBusPortIdType slavePorts_AVsync_660[]  = {AdsppmBusPort_AvSync_Slave};
const AdsppmBusPortIdType slavePorts_HWRSMP_660[]  = {AdsppmBusPort_HwRsmp_Slave};
const AdsppmBusPortIdType slavePorts_SRam_660[]  = {AdsppmBusPort_Sram_Slave};
const AdsppmBusPortIdType slavePorts_Hdmitx_660[]  = {AdsppmBusPort_Hdmitx_Slave};

/**
 * Array of 660 core descriptors. Arranged according to core ID enum
 */
const AsicCoreDescType cores_array_660[] =
{
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
                {ADSPPM_ARRAY(masterPorts_ADSP_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_ADSP_660)}, //Slave port instances
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
                {ADSPPM_ARRAY(slavePorts_LPM_660)}, //Slave port instances
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
                {ADSPPM_ARRAY(masterPorts_DML_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_DML_660)}, //Slave port instances
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
                {ADSPPM_ARRAY(masterPorts_AIF_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_AIF_660)}, //Slave port instances
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
                {ADSPPM_ARRAY(coreClocks_SlimBus_660)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_SlimBus_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_SlimBus_660)}, //Slave port instances
                Adsppm_Instance_Id_1 //Number of core instances
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
                {ADSPPM_ARRAY(slavePorts_AVsync_660)}, //Slave port instances
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
                {ADSPPM_ARRAY(coreClocks_HwRsp_660)}, //Core clock instances
                {ADSPPM_ARRAY(masterPorts_HWRSMP_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_HWRSMP_660)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
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
                AsicPowerDomain_SRam, //Power Domain
                {0, NULL}, //Core clock instances
                {0, NULL}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_SRam_660)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
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
                {ADSPPM_ARRAY(masterPorts_Hdmitx_660)}, //Master port instances
                {ADSPPM_ARRAY(slavePorts_Hdmitx_660)}, //Slave port instances
                Adsppm_Instance_Id_0 //Number of core instances
        },
};

AsicCoreDescriptorArrayType cores_660 = {ADSPPM_ARRAY(cores_array_660)};

const AsicMemDescriptorType memories_array_660[] =
{
        {   //Adsppm_Mem_Lpass_LPM
                Adsppm_Mem_Lpass_LPM, //Mem ID
                AsicPowerDomain_Lpm //Power Domain
        },
        {   //Adsppm_Mem_Sram
                Adsppm_Mem_Sram, //Mem ID
                AsicPowerDomain_SRam //Power Domain
        }
};

AsicMemDescriptorArrayType memories_660 = {ADSPPM_ARRAY(memories_array_660)};

/**
 * Array of 660 core clock descriptors. Arranged by core clock ID
 */
const AsicClkDescriptorType clocks_array_660[AdsppmClk_EnumMax] =
{
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
                AdsppmClk_HwRsp_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AdsppmClk_Aif_Csr_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AdsppmClk_AvSync_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
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
                AdsppmClk_Hdmitx_Hclk, //Clk ID
                AsicClk_TypeInternalCGC, //Clk Type
                AsicClk_CntlAlwaysON_DCG, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.hwioInfo =
                {
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_OFFS, //CAdsppmClk_AhbE_HclkGCR Offset
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_CLK_ENABLE_BMSK, //Enable mask
                        HWIO_LPASS_AUDIO_CORE_HDMITX_CORE_CGCR_HW_CTL_BMSK, //HW control mask
                        0 //Status mask
                },
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Smmu_Lpass_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "gcc_lpass_q6_smmu_axi_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {/* gcc clock for AHB2AXI bridge */
                AdsppmClk_Sysnoc_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "gcc_lpass_mport_clk", //Name
                AdsppmClk_Ahb_Root, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Sysnoc_cbc, //Clk ID
                AsicClk_TypeCBC, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_sysnoc_mport_core_clk", //Name
                AdsppmClk_Sysnoc_Hclk, //Source
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
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_smem_core_clk", //Name
                AdsppmClk_Scc_Data_Hclk, //Source
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
                AdsppmClk_Scc_Cfg_Ahb_Clk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_cfg_ahb_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
	{
                AdsppmClk_Scc_Crif_Clk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_crif_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Scc_Csr_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_csr_h_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Scc_Data_Hclk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_sensor_core_core_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_Scc_Qdsp_Sway_Clk, //Clk ID
                AsicClk_TypeDalEnable, //Clk Type
                AsicClk_CntlAlwaysON, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "island_scc_qdsp_sway_aon_clk", //Name
                AdsppmClk_AhbE_Hclk, //Source
                Adsppm_Mem_None //Memory ID
        },
        {
                AdsppmClk_HwRsp_Core, //Clk ID
                AsicClk_TypeDalFreqSet, //Clk Type
                AsicClk_CntlSW, //Cntl Type
                AsicClk_MemCntlNone, //MemCtrl Type
                .clkInfo.clkName = "audio_core_resampler_clk", //Name
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
                .clkInfo.clkName = "audio_core_avsync_stc_clk", //Name
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
};

AsicClockDescriptorArrayType clocks_660 = {ADSPPM_ARRAY(clocks_array_660)};

/**
 * Arrays of 660 register programming clocks
 */
const AdsppmClkIdType regProgClocks_Dml_660[]      = {AdsppmClk_Dml_Hclk};
const AdsppmClkIdType regProgClocks_Aif_660[]      = {AdsppmClk_Aif_Csr_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus_660[]  = {AdsppmClk_Slimbus_Hclk};
const AdsppmClkIdType regProgClocks_Slimbus2_660[] = {AdsppmClk_Slimbus2_Hclk};
const AdsppmClkIdType regProgClocks_HwRsmp_660[]   = {AdsppmClk_HwRsp_Hclk};
const AdsppmClkIdType regProgClocks_AvSync_660[]   = {AdsppmClk_AvSync_Hclk};
const AdsppmClkIdType regProgClocks_Lpm_660[]      = {AdsppmClk_Lpm_Hclk};
const AdsppmClkIdType regProgClocks_Sram_660[]     = {AdsppmClk_Sram_Hclk};
const AdsppmClkIdType regProgClocks_Hdmitx_660[]   = {AdsppmClk_Hdmitx_Hclk};
const AdsppmClkIdType regProgClocks_Adsp_660[]     = {AdsppmClk_Adsp_Hmclk, AdsppmClk_Adsp_Hsclk};

/**
 * Array of 660 Bus port descriptors arranged by Bus port ID
 */
const AsicBusPortDescriptorType busPorts_array_660[] =
{
        /* Don't remove the AdsppmBusPort_None, as used as accessport busMgrAggregateRequest()*/
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
                AdsppmClk_Slimbus2_Hclk,  //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
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
                AdsppmClk_Sysnoc_cbc, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbMaster = ICBID_MASTER_LPASS_AHB}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
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
                AdsppmBusPort_Dml_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Dml_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Dml_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Aif_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Aif_Csr_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Aif_660)},//Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                 AdsppmClk_Slimbus_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Slimbus2_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Slimbus2_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Slimbus2_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_HwRsmp_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_HwRsp_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_HwRsmp_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_AvSync_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_AvSync_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_AvSync_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Lpm_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Lpm_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Lpm_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Sram_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Sram_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Sram_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
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
                AdsppmBusPort_PerifNoc_Slave, //ID
                AsicBusPort_Ext_S, //Connection
                AdsppmClk_Smmu_Lpass_Hclk, //Bus clock
                {0, NULL}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_BLSP_1}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Master //Access port
        },
        {
                AdsppmBusPort_Hdmitx_Slave, //ID
                AsicBusPort_AhbI_S, //Connection
                AdsppmClk_Hdmitx_Hclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Hdmitx_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Ext_Ahb_Slave //Access port
        },
        {
                AdsppmBusPort_Adsp_Slave, //ID
                AsicBusPort_AhbE_S, //Connection
                AdsppmClk_Adsp_Hsclk, //Bus clock
                {ADSPPM_ARRAY(regProgClocks_Adsp_660)}, //Array of reg prog clocks
                {.icbarbSlave = ICBID_SLAVE_LPASS}, //icbarb ID
                AdsppmBusPort_Adsp_Master //Access port
        }
};

AsicBusPortDescriptorArrayType busPorts_660 = {ADSPPM_ARRAY(busPorts_array_660)};

/**
 * List of supported external bus routes
 */
const AdsppmBusRouteType extBusRoutes_array_660[] =
{
        {
                AdsppmBusPort_Adsp_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        },
        {
                AdsppmBusPort_Ext_Ahb_Master, //master
                AdsppmBusPort_Ddr_Slave //slave
        }
};

AsicBusRouteArrayType extBusRoutes_660 = {ADSPPM_ARRAY(extBusRoutes_array_660)};

const AdsppmBusRouteType mipsBwRoutes_array_660[] =
{
        {
                AdsppmBusPort_Adsp_Master,
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
                AsicRsc_Power_Mem, //Type
                AdsppmClk_Sram_Hclk, //Clock ID
                DALIPCINT_NUM_INTS, //TZ notify
                0, //TZ Done
                {0, NULL} //array of Security clocks
        },       
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
		{           115000000,                -1,          800,             120,            1 },
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

// Table for cache partition configuration.
// Audio and voice classes are grouped together for the purposes
// of determining class concurrency.
// Client class combinations not present in the table will default
// to a shared cache (no partitioning).
const AsicCachePartitionConfigType cachePartitionConfig_array_660[] = {

    // aggregateClass,                mainPartSize

    { MMPM_AUDIO_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

    { MMPM_VOICE_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

    { MMPM_AUDIO_CLIENT_CLASS |
      MMPM_VOICE_CLIENT_CLASS |
      MMPM_COMPUTE_CLIENT_CLASS,      HALF_SIZE }, // 2 way AV/comp

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
        // adspFreqHz,      ahbeFreqHz
	{   124796928,       49900000 }, // MIN SVS f-max
    {   249593856,       49900000 }, // MIN SVS f-max
    {   326400000,       49900000 }, // LOW SVS f-max
    {   499200000,       99800000 }, // SVS f-max
    {   614400000,       99800000 }, // SVS_L1 f-max
    {   748800000,      204800000 }, // nominal f-max
    {   864000000,      204800000 }, // NOM_L1 f-max
    {   998400000,      204800000 }, // turbo ADSP f-max (nom. AHBE, no turbo)
};

AsicAdspToAhbeFreqTableType adspToAhbeFreqTable_660 = 
    { ADSPPM_ARRAY(adspToAhbeFreq_array_660) };

//Table to lookup MPPS threshold values for different client classes
//Class Name, Threshold value
const AsicAdspCacheSizeMPPSThresholdTableEntry adspcachesizeMPPSThreshold_array_660[] = {
    {   MMPM_AUDIO_CLIENT_CLASS,  100  },

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
                998, //max MHz
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
                196000000, //min bytes per second corresponds to 49Mhz clock
                819200000, //max bytes per secondcorresponds to 204Mhz clock
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
                196000000, //min bytes per second corresponds to 49Mhz clock (49M * 32 /8)
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
                AsicFeatureState_Enabled,
                0, // min (not used)
                0, // max (not used)
        },
		// AsicFeatureId_ComputeDSP
		{
				AsicFeatureState_Disabled,
				0, // min (not used)
				0, // max (not used)
		},	
};


