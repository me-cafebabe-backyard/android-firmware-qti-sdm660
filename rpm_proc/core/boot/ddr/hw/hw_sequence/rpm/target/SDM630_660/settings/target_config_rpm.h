#ifndef TARGET_CONFIG_RPM_H
#define TARGET_CONFIG_RPM_H

/***************************************************************************************************

 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.

 ***************************************************************************************************/
// RPM-only DDR System Firmware Version

#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION        22
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION        0
// Updated only when RPM files change



#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION_SHIFT     16
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION_SHIFT      0
#define TARGET_DDR_SYSTEM_FIRMWARE_RPM_VERSION   ((TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_RPM_MAJOR_VERSION_SHIFT) \
                                                | (TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_RPM_MINOR_VERSION_SHIFT))



// Define silicon target or emulation target. Some portions of the DDR System Firmware will or will not
// be compiled depending on what this macro is defined as. 
// If TARGET_SILICON is defined as a 0, it implies an emulation build.
// If TARGET_SILICON is defined as a 1, it implies a real-silicon build.
// If TARGET_SILICON is already defined (on the compiler command line), do not override that definition.
//    This will allow users to override this emulation/silicon flag at compile time without changing the DSF.
#ifndef TARGET_SILICON
#define TARGET_SILICON                         1
#endif // #ifndef TARGET_SILICON

// BIMC and PHY Core Architecture, Major and Minor versions.
#define TARGET_BIMC_ARCH_VERSION               2
#define TARGET_BIMC_CORE_MAJOR_VERSION         3
#define TARGET_BIMC_CORE_MINOR_VERSION         3
#define TARGET_PHY_CORE_MAJOR_VERSION          4
#define TARGET_PHY_CORE_MINOR_VERSION          0

// Define DDR base address in the chip address map from APPS viewpoint.
//    From the RPM viewpoint, DDR is also at 0x80000000, but this address
//    is remapped to 0x60000000 by setting RPM_PAGE_SELECT to 2.
#define DDR_BASE                         0x80000000
#define SCMO_BASE                        0x0 //Base address from SCMO point view, should always start from 0

#define STARLORD_PLATFORM_ID               0x3006


// COMPILING_RPM_PROC is a SVE-specific build flag that kicks in for RPM build in the VI environment.
#ifdef COMPILING_RPM_PROC
    // Define DDR base address in the chip address map from RPM viewpoint
    // The RPM maps the BIMC area to 0x61000000
    #define DDR_PHY_SS_BASE             0x61080000
    #define BIMC_BASE                   0x61000000
    #define MCCC_BASE                   0x60FFD000
#else
    #define DDR_PHY_SS_BASE             0x01080000
    #define BIMC_BASE                   0x01000000
    #define MCCC_BASE                   0x00FFD000
#endif // COMPILING_RPM_PROC

#define DSF_PERIODIC_TRAINING_EN                     1

// Moved from target_config.h in DSF RPM V024
#define DSF_RCW_TRAINING_EN                          1
#define	DSF_DIT_BYTE_MODE_EN						 1


/* =============================================================================
**  Function : DDRSS_Pre_Init
** =============================================================================
*/
/**
*   @brief
*   DCO Calibration workaround for 8994 V1 only.
*
*   @param[in]  ddr          Pointer to ddr conifiguration struct
*
*   @retval  Always TRUE.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32 DDRSS_Pre_Init(DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt);


/* =============================================================================
**  Function : DDRCC_dll_analog_freq_range_table_Index
** =============================================================================
*/
/**
*   @brief
*   DDRCC DLL programming in the pre-clock-switch routine. Platform-specific code,
*   as DDRCC PLL programming characteristics and CSRs are different across targets.
*   Targets 8992 and 8994 are the same, 8996 is different.
*
*   @param[in]  ddr          	 Pointer to ddr conifiguration struct
*   @param[in]  new_clk_index    Index into the clock plan structure corresponding to the requested frequency.
*   @param[in]  ddrcc_target_pll Parameter that selects which PLL to program.
*
*   @retval  None.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint8 DDRCC_dll_analog_freq_range_table_Index (DDR_STRUCT *ddr, uint32 clk_freq_khz);

/* =============================================================================
**  Function : DDR_CC_Pre_Clock_Switch
** =============================================================================
*/
/**
*   @brief
*   DDRCC PLL programming in the pre-clock-switch routine. Platform-specific code,
*   as DDRCC PLL programming characteristics and CSRs are different across targets.
*   Targets 8992 and 8994 are the same, 8996 is different.
*
*   @param[in]  ddr          	 Pointer to ddr conifiguration struct
*   @param[in]  new_clk_index    Index into the clock plan structure corresponding to the requested frequency.
*   @param[in]  ddrcc_target_pll Parameter that selects which PLL to program.
*
*   @retval  None.
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void DDR_CC_Pre_Clock_Switch(DDR_STRUCT *ddr, uint8 ch, uint8 new_clk_idx, uint8 ddrcc_target_pll);

//================================================================================================//
// IO Calibration workaround for 8996 V1 and V2.
//================================================================================================//
void PHY_IO_Cal_Workaround_En_Dis(DDR_CHANNEL channel, uint8 enable);


#endif /* TARGET_CONFIG_RPM_H */


