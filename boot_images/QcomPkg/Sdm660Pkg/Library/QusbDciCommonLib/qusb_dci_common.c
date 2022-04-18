/*=======================================================================*//**
 * @file        qusb_dci_common.c
 * @author:     kameya
 * @date        28-Dec-2015
 *
 * @brief       QUSB common parts of DCI shared by QusbFedlLib & QusbTargetLib.
 *
 * @details     This file contains the implementation of basic APIs to be used
 *              by both QusbTargetLib and QusbFedlLib
 *
 * @note        
 *
 *              Copyright 2015 - 2016 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 2016-10-05    arung   Add UsbSharedLib
// 2015-12-28    kameya  First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"    // basic types as byte word uint32 etc
#include "busywait.h"  // busywait APIs
#include "DALSys.h"    // To get phy settings
#include "qusb_dci_common.h"
#include "qusb_dci_common_hwio_Sdm660.h"
#include "qusb_log.h"
#include "UsbSharedLib.h"
#include "DDIChipInfo.h"

//defines for enabling the 1.5k pull up 
#define QUSB2PHY_PORT_UTMI_CTRL1_SUSPEND_N_EN     (HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_SUSPEND_N_BMSK)
#define QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_EN   (HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_BMSK)
#define QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_FS   (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_SHFT)
#define QUSB2PHY_PORT_UTMI_CTRL1_OP_MODE          (0x0 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OP_MODE_SHFT)
#define QUSB2PHY_PORT_UTMI_CTRL1_OP_NON_MODE      (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OP_MODE_SHFT)

#define QUSB_LINESTATE_CHECK_DELAY                (0x5)
#define QUSB_LINESTATE_CHECK_RETRY_CNT            (10000)  //50msec is the total wait time to deal with a bad cable


//============================================================================

/**
* @function  qusb_dci_delay_ms
*
* @brief Perform delay in milliseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param milliseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_ms(uint32 msecs)
{
  int counter;

  for (counter = 0; counter < msecs; counter++)
  {
    busywait(1000); // 1 ms
  }   
}


//============================================================================
/**
* @function  qusb_dci_delay_us
*
* @brief Perform delay in microseconds.
*
* @Note : The USB Timers can not be used before the core is initialized.
*
* @param microseconds
*
* @return none
*
*/
//============================================================================
void qusb_dci_delay_us(uint32 usecs)
{
  busywait( usecs );
}

// ===========================================================================
/**
 * @function    qusb_hs_phy_gcc_reset
 * 
 * @brief   API used for resetting High Speed QUSB2 PHY using GCC control
 *  
 * @details API is used for resetting High Speed QUSB2 PHY using GCC control
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_hs_phy_gcc_reset(void)
{
  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,
    (0x1 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));

  qusb_dci_delay_us(100);

  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,
    (0x0 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
}

// ===========================================================================
/**
 * @function    qusb_dci_usb30_gcc_reset
 * 
 * @brief   API used for resetting the Link and PHYs using GCC control
 *  
 * @details This API is used for resetting the Link and PHYs using clock control 
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_usb30_gcc_reset(void)
{
  // Reset SNPS Link controller 
  HWIO_GCC_USB_30_BCR_OUTM(HWIO_GCC_USB_30_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_USB_30_BCR_BLK_ARES_SHFT));

  qusb_dci_delay_us(100);

  HWIO_GCC_USB_30_BCR_OUTM(HWIO_GCC_USB_30_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_USB_30_BCR_BLK_ARES_SHFT));

  // Reset QUSB (USB 2.0) and QMP (USB 3.0) PHYs 
  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3_PHY_BCR_OUTM(HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_USB3_PHY_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3PHY_PHY_BCR_OUTM(HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK, (0x1 << HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_SHFT));

  qusb_dci_delay_us(100);

  HWIO_GCC_USB3PHY_PHY_BCR_OUTM(HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_BMSK, (0x0 << HWIO_GCC_USB3PHY_PHY_BCR_BLK_ARES_SHFT));
  HWIO_GCC_USB3_PHY_BCR_OUTM(HWIO_GCC_USB3_PHY_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_USB3_PHY_BCR_BLK_ARES_SHFT));
  HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));

  return; 
}

// ===========================================================================
/**
 * @function    qusb_hs_phy_refclk_enable
 * 
 * @brief   This function will be used to enable / disable HS PHY reference clock.
 * 
 * @param  TRUE or FALSE depending on enable or disable.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_hs_phy_refclk_enable(boolean enable)
{
  HWIO_GCC_RX0_USB2_CLKREF_EN_OUTM(HWIO_GCC_RX0_USB2_CLKREF_EN_RX0_USB2_ENABLE_BMSK,
    enable << HWIO_GCC_RX0_USB2_CLKREF_EN_RX0_USB2_ENABLE_SHFT);

  HWIO_GCC_RX0_USB2_CLKREF_EN_OUTM(HWIO_GCC_RX0_USB2_CLKREF_EN_SW_RXTAP1_EN_BMSK,
    enable << HWIO_GCC_RX0_USB2_CLKREF_EN_SW_RXTAP1_EN_SHFT);

}

// ===========================================================================
/**
 * @function    qusb_dci_select_utmi_clk
 * 
 * @brief   This is used for configuring the core to UTMI clock instead of pipe
 *          clock.  This needs to be called when there is no SS USB PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_select_utmi_clk(void)
{
  qusb_error_log(QUSB_DCI_SELECT_UTMI_CLK_LOG, 0, 0);
  
  // If operating without SS PHY, follow this sequence to disable 
  // pipe clock requirement
  HWIO_GENERAL_CFG_OUTM(HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
                      0x1 << HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);

  qusb_dci_delay_us(100);

  HWIO_GENERAL_CFG_OUTM(HWIO_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK,
                      0x1 << HWIO_GENERAL_CFG_PIPE_UTMI_CLK_SEL_SHFT);

  qusb_dci_delay_us(100);
  
  HWIO_GENERAL_CFG_OUTM(HWIO_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK,
    0x1 << HWIO_GENERAL_CFG_PIPE3_PHYSTATUS_SW_SHFT);

  qusb_dci_delay_us(100);

  HWIO_GENERAL_CFG_OUTM(HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
                      0x0 << HWIO_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);
}

// ===========================================================================
/**
 * @function    qusb_dci_hs_phy_update_hstx_trim
 * 
 * @brief   This function will update TUNE2 HSTX_TRIM register bits if feature is enabled.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_dci_hs_phy_update_hstx_trim(void)
{
    uint8 hstx_trim_val = 
        HWIO_QFPROM_CORR_CALIB_ROW11_LSB_INM(HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_BMSK) 
        >> HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_SHFT;

    if(hstx_trim_val)
    {
        HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_OUTM(
            HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_UTM_HSTX_TRIM_BMSK, 
            (hstx_trim_val - QUSB_HSTX_TRIM_OFFSET) << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_TUNE2_UTM_HSTX_TRIM_SHFT);
    }
}

// =============================================================================
/**
 * @function    qusb_dci_ahb2phy_cfg
 * 
 * @brief   Configures AHB2PHY read/write states to be 1 wait cycle each.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// =============================================================================
void qusb_dci_ahb2phy_cfg(void)
{
  qusb_dci_delay_us(10);
  
  // Write 0x11 to AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG so that 
  // writes and reads to/from the PHY use one wait state.
  // This is essential to operate at nominal freq with lower CX rail voltages.
  HWIO_PERIPH_SS_AHB2PHY_TOP_CFG_OUT(0x11);
}

// ===========================================================================
/**
 * @function    qusb_hs_phy_init
 * 
 * @brief   API used to initialize the High Speed PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
boolean qusb_hs_phy_init(void)
{
  return usb_shared_hs_phy_init();
}

// ===========================================================================
/**
 * @function    qusb_dci_dp_gnd_check
 * 
 * @brief   API used to check if D+ is grounded.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
boolean qusb_dci_dp_gnd_check(void)
{
  uint32 linestate = 0x0;
  int32 retries = 0x0;
  uint32 enable_fs_xvr = 0x0;

  // Enable UTMI_TEST_MUX_SEL
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_BMSK,
    0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_SHFT);

  //Disable the D+ Pull down 
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_BMSK, 
    (0x0 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_SHFT ));
    

  // Enable the D- Pull down 
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_BMSK,
      (0x1 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_SHFT));


  //Select the FS transceiver and enable the 1.5k pull-up. 
  enable_fs_xvr = (QUSB2PHY_PORT_UTMI_CTRL1_SUSPEND_N_EN | QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_EN | 
                   QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_FS | QUSB2PHY_PORT_UTMI_CTRL1_OP_MODE); 

  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OUT(enable_fs_xvr);

  
  do
  {
    //wait for 5 microseconds 
    qusb_dci_delay_us(QUSB_LINESTATE_CHECK_DELAY); 
    
    //read the linestate
    linestate = HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_STATUS_INM(
                    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_STATUS_LINESTATE_BMSK);
    
    //if D+ is still high, then the device should not enter the EDL Mode 
    if(linestate != 0x0)
    {
      break; 
    }
    
    retries++;

  }while (retries < QUSB_LINESTATE_CHECK_RETRY_CNT);

  //disable the 1.5K Pull up resistor
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OUT(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_BMSK);

  // Disable UTMI_TEST_MUX_SEL
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_BMSK,
    0x0 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_SHFT);

  if(linestate != 0x0)
  {
    qusb_error_log(DCI_SKIP_FEDL_LOG, 0, linestate);
    return FALSE;
  }

  //D+ is connected to the GND
  qusb_error_log(DCI_ENTER_FEDL_LOG, 0, linestate);
  return TRUE;

}

// =============================================================================
/**
 * @function    qusb_hs_phy_nondrive_cfg
 * 
 * @brief   Function used to configure High Speed PHY in non-drive mode.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// =============================================================================
void qusb_hs_phy_nondrive_cfg(void)
{

  uint32 enable_fs_xvr = 0x0;

  //Disable the D+ Pull down 
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_BMSK, 
    (0x0 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DPPULLDOWN_SHFT ));
    

  // Disable the D- Pull down 
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
      HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_BMSK,
      (0x0 <<HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_DMPULLDOWN_SHFT));
  
  // Select the FS transceiver and put into non-drive mode
  // Putting phy to suspend as SUSPEND_N = 0 (power on default)
  enable_fs_xvr = (QUSB2PHY_PORT_UTMI_CTRL1_TERM_SELECT_EN
                   | QUSB2PHY_PORT_UTMI_CTRL1_XCVR_SELECT_FS
                   | QUSB2PHY_PORT_UTMI_CTRL1_OP_NON_MODE 
                   | QUSB2PHY_PORT_UTMI_CTRL1_SUSPEND_N_EN);

  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL1_OUT(enable_fs_xvr);

  // Enable UTMI_TEST_MUX_SEL
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_BMSK,
    0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_UTMI_CTRL2_UTMI_TEST_MUX_SEL_SHFT);


  qusb_dci_delay_us(10);

  // Keep PHY in power down
  HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_OUTM(
    HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_BMSK,
    (0x1 << HWIO_PERIPH_SS_QUSB2PHY_PRIM_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_SHFT));

  //Power down the Secondary QUSB2 PHY to plug leakage
  if (DalChipInfo_ChipFamily() == DALCHIPINFO_FAMILY_SDM660)
  {
    HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_OUTM(
	  HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_BMSK,
	  (0x1 << HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PORT_POWERDOWN_POWER_DOWN_SHFT));
  }

}

