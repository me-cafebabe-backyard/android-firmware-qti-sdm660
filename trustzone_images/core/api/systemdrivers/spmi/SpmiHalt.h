/**
 * @file: SpmiHalt.h
 * @brief: A standalone API for disabling the SPMI bus
 * 
 * Copyright (c) 2013, 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2020/01/14 12:35:09 $
 * $Header: //components/rel/core.tz/1.0.7.1/api/systemdrivers/spmi/SpmiHalt.h#1 $
 * $Change: 22186835 $
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */
#ifndef SPMIHALT_H
#define	SPMIHALT_H

#include "SpmiTypes.h"

/**
 * @brief Gracefully halts the SPMI Bus
 * 
 * This function disables all SPMI controllers so no future bus
 * requests are processed.  If this function returns successfully,
 * all buses will have completed any in progress transaction and will be
 * disabled.
 * 
 * @return  SPMI_SUCCESS on success, error code on failure
*/
Spmi_Result SpmiHalt_DisableAllBuses(void);

/**
 * @brief Gracefully halts the SPMI Bus
 * 
 * This function disables the SPMI controller so no future bus
 * requests are processed.  If this function returns successfully,
 * the bus will have completed any in progress transaction and will be
 * disabled.
 * 
 * @param[in] busId  The bus to disable
 * 
 * @return  SPMI_SUCCESS on success, error code on failure
*/
Spmi_Result SpmiHalt_DisableBus(uint8 busId);

#endif
