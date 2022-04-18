#ifndef TARGET_CONFIG_H
#define TARGET_CONFIG_H

/***************************************************************************************************

 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.

 ***************************************************************************************************/
 
 #include "target_config_rpm.h"
 
#define TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION            37
#define TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION            0



#define TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION_SHIFT     16
#define TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION_SHIFT      0
#define TARGET_DDR_SYSTEM_FIRMWARE_VERSION   ((TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_MAJOR_VERSION_SHIFT) \
                                            | (TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION << TARGET_DDR_SYSTEM_FIRMWARE_MINOR_VERSION_SHIFT))

 
// Size of statically allocated area in ZI data area that training functions will
// use in place of local variables to reduce stack growth pressure.
// Used in the function HAL_DDR_Boot_Training().
// Allow a DSF user to override this if they like.
#ifndef LOCAL_VARS_AREA_SIZE            
#define LOCAL_VARS_AREA_SIZE            0x10000 /* 64KB */
#endif


// The flat 32-bit system address from APPS or RPM viewpoint where PHY training code will write
// training patterns to and read back from. Training addresses currently are hard-coded to assume
// that System Address Bit 10 is the interleave bit, hence the address for channel 1 is 0x00000400.
// The training address is at 0x60000000 if we are compiling for RPM processor since system address
// 0x80000000 appears at RPM address 0x60000000 by platform architecture.
// COMPILING_RPM_PROC is a RPM-specific build flag.
#ifdef COMPILING_RPM_PROC
    #define TRAINING_BASE_ADDRESS_OFFSET     0x60000000   
#else
    #define TRAINING_BASE_ADDRESS_OFFSET     0x10000000   
#endif  // COMPILING_RPM_PROC

#define TRAINING_INTERLEAVE_ADDRESS_OFFSET  0x00000400


#define DSF_MAX_SUPPORTED_DDR_FREQ         1804800      
#define STARLORD_PLATFORM_ID               0x3006
#define STARHAWK_PLATFORM_ID               0x3007

#define DSF_PXI_TRAINING_EN                          0

#define DSF_CA_VREF_TRAINING_EN                      0 
#define DSF_CA_VREF_TRAINING_LOG                     0
#define DSF_WRLVL_TRAINING_EN                        1
#define DSF_WRLVL_TRAINING_LOG                       0

//#define DSF_RCW_TRAINING_EN                        0 // Moved to target_config_rpm.h in DSF RPM V024
#define DSF_RCW_TRAINING_LOG                         0

#define DSF_PASS_1_DCC_TRAINING_EN                   1    //DCC training at the beginning
#define DSF_DCC_TRAINING_DQ_DCC_EN                   1    //DQ DCC disabled.
#define DSF_DCC_TRAINING_DQ_DCC_LOG                  0
#define DSF_DCC_TRAINING_CA_DCC_EN                   1    //CA DCC enabled.
#define DSF_DCC_TRAINING_CA_DCC_LOG                  0

#define DSF_RD_DQDQS_TRAINING_EN                     1
#define DSF_RD_DQDQS_TRAINING_LOG                    0
#define DSF_CLK_DCC_RD_DQDQS                         0
#define DSF_CLK_DCC_RD_DQDQS_LOG                     0
#define DSF_RD_DQDQS_DCC                             1
#define DSF_RD_DQDQS_DCC_LOG                         1
#define DSF_RD_DQDQS_EYE_MASK                        0
#define DSF_RD_DQDQS_COARSE_FINE_PLOT                0
#define DSF_RD_DQDQS_COARSE_FINE_PLOT_PIVOT          0

#define DSF_RD_DQDQS_COARSE_FINE_PLOT_FREQ           1804800
#define DSF_WR_VREF_BYTE_MODE_EN        			 0 
#define	DSF_DIT_BYTE_MODE_EN						 1

#define DSF_WR_DQDQS_TRAINING_EN                     1
#define DSF_WR_DQDQS_TRAINING_LOG                    0
#define DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_EN         1    //WR dqdqs training for band0.
#define DSF_WR_DQDQS_TRAINING_TDQS2DQ_CAL_LOG        0   
#define DSF_WR_DQDQS_EYE_MASK                        0
#define DSF_WR_DQDQS_COARSE_FINE_PLOT                0
#define DSF_WR_DQDQS_COARSE_FINE_PLOT_PIVOT          0

#define DSF_WR_DQDQS_COARSE_FINE_PLOT_FREQ           1804800

// ----------------------------------------------------------------------
//                    |   CHANNEL 1      |         CHANNEL 0          |
// ----------------------------------------------------------------------
// { na| na| CC|na} {na |DQ1|DQ0|na }{CA0|CC|na |na } {DQ1|DQ0|na |CA0}
// ----------------------------------------------------------------------
// { 15| 14| 13| 12}{ 11| 10|  9|  8}{  7|  6|  5|  4}{  3|  2|  1|  0}
// {---------------}{---------------}{---------------}{---------------}--
#define PHY_BC_DISABLE         0x0000

//Channel 0                 
#define CS_CH0_DDRPHY_CA0      0x0001 
#define CS_CH0_DDRPHY_DQ0      0x0004 
#define CS_CH0_DDRPHY_DQ1      0x0008 
#define CS_CH0_DDRCC           0x0040 


//Channel 1                               
#define CS_CH1_DDRPHY_CA0      0x0080  
#define CS_CH1_DDRPHY_DQ0      0x0200  
#define CS_CH1_DDRPHY_DQ1      0x0400   
//#define CS_CH1_DDRCC           0x0200   

//All Channels

#define ALL_CAs     (CS_CH0_DDRPHY_CA0 | CS_CH1_DDRPHY_CA0)
                              
#define ALL_DQs     (CS_CH0_DDRPHY_DQ0 | CS_CH0_DDRPHY_DQ1 | CS_CH1_DDRPHY_DQ0 | CS_CH1_DDRPHY_DQ1)
                                  
#define ALL_CCs     ( CS_CH0_DDRCC )

#define ALL_CAsDQs (CS_CH0_DDRPHY_CA0 | CS_CH1_DDRPHY_CA0 | \
                    CS_CH0_DDRPHY_DQ0 | CS_CH0_DDRPHY_DQ1 | \
                    CS_CH1_DDRPHY_DQ0 | CS_CH1_DDRPHY_DQ1 )

#define PCH_DQs(ch) ((ch == 0)  ? \
                        CS_CH0_DDRPHY_DQ0 | CS_CH0_DDRPHY_DQ1 : \
                        CS_CH1_DDRPHY_DQ0 | CS_CH1_DDRPHY_DQ1)

#define PCH_CAs(ch) ((ch == 0)  ? \
                        CS_CH0_DDRPHY_CA0 : \
                        CS_CH1_DDRPHY_CA0)                        
                    
                    
                    
/* =============================================================================
**  Function : DDRSS_Copy_Clock_Plan_Struct
** =============================================================================
*/
/**
*   @brief
*   Calculate PLL settings for the DDR clock plan structure based on requested 
*   frequencies.  When this function is called, at the beginning of HAL_DDR_Init(), 
*   ddr->misc.clock_plan[] should contain an in-order list of valid DDR frequencies.  
*   This function will fill in the rest of the PLL parameters contained in
*   ddr->misc.clock_plan[].
*
*   @param[in]  ddr          Pointer to ddr configuration struct, including clock plan
*
*   @retval  void
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
void DDRSS_Copy_Clock_Plan_Struct(DDR_STRUCT *ddr);

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
**  Function : DDRSS_Post_Init
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
uint32 DDRSS_Post_Init (DDR_STRUCT *ddr, EXTENDED_CDT_STRUCT *ecdt, DDR_CHANNEL channel , DDR_CHIPSELECT chip_select);

//================================================================================================//
// IO Calibration workaround for 8996 V1 and V2.
//================================================================================================//
void PHY_IO_Cal_Workaround_En_Dis(DDR_CHANNEL channel, uint8 enable);


#endif /* TARGET_CONFIG_H */


