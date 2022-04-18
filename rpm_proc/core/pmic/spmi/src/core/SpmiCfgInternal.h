/**
 * @file:  SpmiCfg.h
 * @brief: This module provides configuration options for the SPMI controller
 * 
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/pmic/spmi/src/core/SpmiCfgInternal.h#1 $
 * $Change: 11690628 $ 
 * 
 *                              Edit History
 * Date      Description
 * --------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/14/14  Initial Version
 */
#ifndef SPMICFGINTERNAL_H
#define	SPMICFGINTERNAL_H

#include "SpmiBusCfg.h"
#include "SpmiInfo.h"

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiBusCfg_ConfigureChannel(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* chanCfg, boolean autoAssignChan);

#endif
