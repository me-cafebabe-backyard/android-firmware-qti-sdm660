/**
 * @file:  cpr_image_api.h
 * @brief:
 *
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2017/03/06 22:14:55 $
 * $Header: //components/rel/rpm.bf/1.8/core/api/power/cpr/rpm/cpr_image_api.h#2 $
 * $Change: 12599917 $
 */
#ifndef CPR_IMAGE_API_H
#define CPR_IMAGE_API_H

#include "railway.h"

/*
 * RPM specific global API
 */
uint32 cpr_railway_get_voltage(int railwayRailId, railway_corner railwayCorner);
void cpr_railway_get_supported_corners(int railwayRailId, railway_corner *corners, uint32 *cornerCount );
uint16 cpr_get_mpm_ro_div(uint32 mxSleepUV);
boolean cpr_is_mx_chain_broken(void);
boolean cpr_is_retention_failed(void);
void cpr_lpi_controller_config(boolean config);

#endif
