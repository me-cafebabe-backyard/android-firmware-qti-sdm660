/*
  @brief: This module provides an internal the interface to the 
  SPMI bus driver software.
  
  Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved. 
  
  $DateTime: 2016/08/19 05:58:45 $
  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/SpmiBusInternal.h#2 $
  $Change: 11185940 $ 
  
                               Edit History
  Date      Description
  --------  -------------------------------------------------------------------
  11/10/15  Initial Version
*/
#ifndef SPMIBUSINTERNAL_H
#define SPMIBUSINTERNAL_H

#include "SpmiTypes.h"
#include "SpmiInfo.h"
#include "SpmiBusCfg.h"

/**
 * @brief Get the SPMI bus information structure
 *
 * This function gets the internal SPMI bus information 
 * structure.
 * 
 * @param[in] vSlaveId   Virtual slave Id of the device (see 
 *                       SpmiEncodeVSid)
 * 
 * @return Pointer to the device info structure, or 
 *         NULL on errror
 */
SpmiDevInfo *_SpmiBus_GetDevInfo(uint8 vSlaveId);

Spmi_Result SpmiBusCfg_ConfigureChannel(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* chanCfg, boolean autoAssignChan);

#endif
