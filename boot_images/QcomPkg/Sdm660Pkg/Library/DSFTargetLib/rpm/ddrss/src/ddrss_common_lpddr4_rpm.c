/****************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2015, Qualcomm Technologies Incorporated. All rights reserved.
 ****************************************************************************/
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/ddrss/src/ddrss_common_lpddr4_rpm.c#5 $
$DateTime: 2017/03/31 01:29:53 $
$Author: pwbldsvc $
================================================================================
when       who          what, where, why
--------   ---          --------------------------------------------------------
05/11/14   arindamm     First edit history header. Add new entries at top.
================================================================================*/

#include "ddrss_rpm.h"
#include "target_config_rpm.h"
#include <string.h>


/* ============================================================================
**  Function : DDRSS_device_reset_cmd
** ============================================================================
*/
/*!
*   @brief
*   Sets the Device reset register in DDRSS gets reset during power collapse. 
*   
*   @details
*  Sets the Device reset register in DDRSS gets reset during power collapse. 
*   
*/
void DDRSS_device_reset_cmd()
{
 // Device reset register in DDRSS gets reset during power collapse. Hence set this register
   // to drive reset deasserted to the device before unfreezing the IOs.
   HWIO_OUTX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD, 1);
   while ( HWIO_INX (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_RESET_CMD) != 1); 
}

void DDRSS_BHS_broadcast_override_enable()
{
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG0, SW_HS_BROADCAST_MODE, 1); 
}

void DDRSS_BHS_staggered_override_enable(uint8 override_val, uint8 override_sel)
{
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENR_ACK_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENR_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENR_ACK_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENR_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENR_OVR_SEL, override_sel); 

        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENF_ACK_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENF_OVR, override_val); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENF_ACK_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENF_OVR_SEL, override_sel); 
        HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENF_OVR_SEL, override_sel); 
}

void DDRSS_BHS_override_disable(uint8 expected_ack_val)
{
    uint8 actual_enf_ack = 0;
    uint8 actual_enr_ack = 0;

    actual_enf_ack = ~expected_ack_val;
    actual_enr_ack = ~expected_ack_val;

    //Disabling Override serially on each HS
    //Wait until teh expected ACK is received on HS

    //All ENFs ***
    //CH0 DQ0
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_DQ0_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CH0 CA
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_CA_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CH0 DQ1
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_DQ1_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CC
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, CC_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CH1 DQ1
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_DQ1_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CH1 CA
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_CA_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //CH1 DQ0
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENF_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_DQ0_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //Aggregator
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENF_ACK_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enf_ack != expected_ack_val)
    {
        actual_enf_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, GDSC_HS_ENF_ACK);
    }
    actual_enf_ack = ~expected_ack_val;
    
    //All ENRs ***
    //CH0 DQ0
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ0_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_DQ0_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CH0 CA
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_CA_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_CA_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CH0 DQ1
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH0_DQ1_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH0_DQ1_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CC
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_CC_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, CC_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CH1 DQ1
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ1_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_DQ1_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CH1 CA
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_CA_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_CA_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //CH1 DQ0
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_PHYCH1_DQ0_HS_ENR_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, PHYCH1_DQ0_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
    //Aggregator
    HWIO_OUTXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_CFG1, SW_GDSC_HS_ENR_ACK_OVR_SEL, 0); 
    //Poll for the expected ACK
    while(actual_enr_ack != expected_ack_val)
    {
        actual_enr_ack = HWIO_INXF (DDR_PHY_SS_BASE + SEQ_DDR_SS_DDR_REG_DDR_SS_REGS_OFFSET, DDR_SS_REGS_DDRSS_HS_STA, GDSC_HS_ENR_ACK);
    }
    actual_enr_ack = ~expected_ack_val;
    
}



