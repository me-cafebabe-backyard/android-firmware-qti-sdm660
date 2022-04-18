#ifndef PM_RGB_BASE_ADDR_REGS_H
#define PM_RGB_BASE_ADDR_REGS_H
/*
===========================================================================
*/
/**
  @file pm_rgb_regs.h
  @brief Contains the base addresses for the RGB LED.

  This file contains base address register definitions 

  ===========================================================================*/
/*
  Copyright (c) 2013-2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  
===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/11/13   aks     Created.
===========================================================================*/

/*----------------------------------------------------------------------------
 * PERIPHERAL: TRI_LED
 *--------------------------------------------------------------------------*/

#define PM_LED_RGB_BASE_ADDR                       0xD000  //base address for the RGB Led
#define PM_LED_LPG_SLICE_REG_BASE_ADDR             0xB100  //base address for the LPG Slice Register
#define PM_LED_LPG_FIRST_CHANNEL_OFFSET            0x100   //base offset to get to the right channel 
#define PM_LED_RED_LED_CHANNEL_NUM                 0x03    //Red led channel num
#define PM_LED_GREEN_LED_CHANNEL_NUM               0x02    //Green Led channel num
#define PM_LED_BLUE_LED_CHANNEL_NUM                0x01    //Blue Led channel num




#endif /* PM_RGB_BASE_ADDR_REGS_H */
