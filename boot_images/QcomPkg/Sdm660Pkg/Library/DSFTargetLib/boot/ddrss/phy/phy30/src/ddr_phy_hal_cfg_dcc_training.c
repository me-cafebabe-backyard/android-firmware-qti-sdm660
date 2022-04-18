//===========================================================================
//  Copyright (c) 2014 - 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ddr_phy.h"
#include "ddrss.h"

uint32 DDR_PHY_rtn_training_dcc_wrlvl(DDR_STRUCT *ddr, uint32 _inst_)
{
    uint32 wrlvl_stat = 0;
    
    // Start WRLVL DCC training    
    // Set the DCC direction
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_1_CFG, CM_DIRECTION, 1); // default = 0

    // Select the WRLVL DCC adjust (0) to connect to the DCC monitor  
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, DCC_MON_SRC_SEL, 0); // default = 0
    
    // Set CM Mode=1 to select the FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_MODE, 1 ); // default = 1
    
    // Open the DCC WRLVL Latch close the DCC training loop
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 1);
    
    // Start the DCC FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_CNTRL_START, 1);
    
    // Poll the DCC Done Status 
    while (!HWIO_INXF (_inst_,DDR_PHY_DDRPHY_DCC_STATUS_0_STA , CM_DCC_DONE));
    
    // Read the WRLVL adjustment value
    wrlvl_stat = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_DCC_STATUS_4_STA, CM_DCC_DQS_ADJ_STATUS);
    
    // Write the DCC WRLVL adjustment value into the DCC WRLVL CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_MAN_ADJ, wrlvl_stat);
    
    // Stop DCC FSM and return the FSM to the reset state
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_CNTRL_START, 0);
    
    // Set CM Mode=0 to select the CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_MODE, 0 ); // default = 1
    
    // Close the DCC WRLVL Latch enable to hold the DCC trained value
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 0);
    
    return (wrlvl_stat);
}

uint32 DDR_PHY_rtn_training_dcc_t90(DDR_STRUCT *ddr, uint32 _inst_)
{
    uint32 t90_stat;

    // Set the DCC direction
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_1_CFG, CM_DIRECTION, 1); // default = 0

    // Select the T90 DCC to connect to the monitor  
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, DCC_MON_SRC_SEL, 1); // default = 0
    
    // Set CM Mode=1 to select the FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_MODE, 1 ); // default = 1
    
    // Set CM_ADJ_DWQ_SW_OVRD=0 to select the FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_ADJ_DQ_SW_OVRD, 0 ); // default = 0
    
    // Open the latch enable to close the DCC training loop
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 1);
    
    // Start the DCC FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_CNTRL_START, 1);
    
    // Poll the DCC Done Status 
    while (!HWIO_INXF (_inst_,DDR_PHY_DDRPHY_DCC_STATUS_0_STA , CM_DCC_DONE));
    
    // Read the T90 adjustment value
    t90_stat = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_DCC_STATUS_4_STA, CM_DCC_DQS_ADJ_STATUS);
    
    // Write the DCC T90 adjustment value into the DCC T90 CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_ADJ_DQ_SW_OVRD_VAL, t90_stat);
    
    // Close the latch enable to hold the trained value in the adjuster
    //HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WR_CDC_LATCH_EN, 0); // default = 1
    
    // Stop DCC FSM and return the FSM to the reset state
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_CNTRL_START, 0);
    
    // Set CM_ADJ_DWQ_SW_OVRD=0 to select the CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_ADJ_DQ_SW_OVRD, 1 ); // default = 0
    
    // Set CM Mode=0 to select the CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, CM_MODE, 0 ); // default = 1
    
    // Return the DCC Monitor source select to default
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_CMCDCWR_TOP_CFG, DCC_MON_SRC_SEL, 0);

    // Open the DCC WRLVL Latch for the rest of the training sequence
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, CM_DCC_CTLR_WRLVL_CDC_LATCH_EN, 1);
    
    return (t90_stat);
}

uint32 DDR_PHY_rtn_training_dcc_io_dqs(DDR_STRUCT *ddr, uint32 _inst_)
{
    uint32 io_dqs_stat = 0;
    
    // Disable DQ DCC by selecting the CSR and setting the value to 0
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD_VAL, 0 );
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_3_CFG, IO_ADJ_DQ_SW_OVRD    , 1 );
    
    // Set IO Mode=1 to select the FSM for training DQS
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, IO_MODE, 1 ); // default = 1
    
    // Start the DCC FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, IO_CNTRL_START, 1); // default = 0
    
    // poll staus of IO/Pad DCC training
    while (!HWIO_INXF (_inst_,DDR_PHY_DDRPHY_DCC_STATUS_0_STA , IO_DCC_DONE ));
    
    // Read the IO DQS adjustment
    io_dqs_stat = HWIO_INXF (_inst_, DDR_PHY_DDRPHY_DCC_STATUS_4_STA, IO_DCC_DQS_ADJ_STATUS);
    
    // Write the DCC IO adjustment value into the DCC IO CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_1_CFG, IO_MAN_ADJ , io_dqs_stat);
    
    // Set IO Mode=0 to select the CSR 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, IO_MODE, 0 ); // default = 1
    
    // Stop the DCC FSM 
    HWIO_OUTXF (_inst_, DDR_PHY_DDRPHY_DCC_TOP_0_CFG, IO_CNTRL_START, 0);
    
    return (io_dqs_stat);
}



