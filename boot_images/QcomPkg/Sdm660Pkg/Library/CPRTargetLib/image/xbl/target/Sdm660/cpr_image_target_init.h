/**
 * @file:  cpr_image_target_init.h
 * @brief:
 *
 * Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2016/09/06 05:38:07 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/CPRTargetLib/image/xbl/target/Sdm660/cpr_image_target_init.h#2 $
 * $Change: 11305838 $
 */
#ifndef CPR_IMAGE_TARGET_INIT_H
#define CPR_IMAGE_TARGET_INIT_H

//******************************************************************************
// Default Enablement Structures
//******************************************************************************
struct cpr_cfg_funcs;

typedef enum
{
    CPR_INIT_NONE, /* used to disable CPR */
    CPR_INIT_OPEN_LOOP,
    CPR_INIT_SW_CLOSED_LOOP,

    CPR_INIT_FUNCS_COUNT
} cpr_init_funcs_id;

struct cpr_cfg_funcs* cpr_image_target_get_init_func(cpr_init_funcs_id func_id);

#endif

