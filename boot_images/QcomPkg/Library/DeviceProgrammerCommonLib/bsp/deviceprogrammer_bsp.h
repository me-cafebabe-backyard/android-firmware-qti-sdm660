/*==================================================================
 *
 * FILE:        deviceprogrammer_bsp.h
 *
 * DESCRIPTION: This file provides SDCC abstraction for dependent drivers for Non-OS(BOOT).
 *
 *
 *        Copyright (c) 2013,2015 Qualcomm Technologies, Inc.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 *   YYYY-MM-DD   who     what, where, why
 *   ----------   ---     ----------------------------------------------
 *   2015-05-18   wek     Remove unused funcitons.
 *   2013-06-03   ah      Added legal header
 *   2013-05-31   ab      Initial checkin
 */

#ifndef __DEVICEPROGRAMMER_BSP_H
#define __DEVICEPROGRAMMER_BSP_H

/******************************************************************************
*
* Description:
*    This function Resets the target
*
******************************************************************************/
void bsp_target_reset(void);

/******************************************************************************
*
* Description:
*    This function Resets the target to Emergency download mode
*
******************************************************************************/
void bsp_target_reset_edl(void);

/******************************************************************************
*
* Description:
*    This function powers down the target
*
******************************************************************************/
void bsp_target_poweroff(void);


/******************************************************************************
*
* Description:
*    This function performs the HW Init for eHOSTDL
*    The HW init includes enabling SDRAM, Clocks etc...
*      
******************************************************************************/
void bsp_hw_init(void);


#endif /* __DEVICEPROGRAMMER_BSP_H */



