/*============================================================================
  @file sns_uimg_utils.c

  @brief
  Contains implementation of utilities to make writing uImage aware code easier.

  Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include "sns_common.h"
#include "sns_uimg_utils.h"
#include "sns_pm.h"
#include "sns_memmgr.h"

/*============================================================================
  Static Variables
  ===========================================================================*/

STATIC bool sns_memmgr_module_restrictions[ SNS_UIMG_SMR_MAX_CLIENTS ];
STATIC OS_EVENT *sns_uimg_utils_mutex;
STATIC SNS_MEMMGR_UIMAGE_DATA sns_pm_handle_t sns_utils_pm_client_handle;

/*============================================================================
  Static Function Definitions
  ===========================================================================*/

/**
 * @return true if there are no modules blocking uImage; false otherwise
 */
STATIC bool sns_utils_no_blocking_module(void)
{
  int i;
  for(i = 0; i < SNS_UIMG_SMR_MAX_CLIENTS; i++)
  {
    if(sns_memmgr_module_restrictions[i])
    {
      return false;
    }
  }
  return true;
}

/*============================================================================
  Public Function Definitions
  ===========================================================================*/

void sns_utils_remove_uimage_hold(sns_uimg_module_e module)
{
  uint8_t sns_os_err;
  SNS_ASSERT(sns_utils_pm_client_handle != NULL);
  sns_os_mutex_pend(sns_uimg_utils_mutex, 0, &sns_os_err);
  sns_memmgr_module_restrictions[module] = false;
  if(sns_utils_no_blocking_module())
  {
    sns_pm_vote_img_mode(sns_utils_pm_client_handle, SNS_IMG_MODE_NOCLIENT);
  }
  sns_os_mutex_post(sns_uimg_utils_mutex);
}

void sns_uimg_utils_init(void)
{
  uint8_t i, sns_os_err;
  sns_pm_err_code_e pm_err;
  pm_err = sns_pm_client_init(&sns_utils_pm_client_handle, NULL, "UTIL", SNS_PM_CLIENT_ID_UTIL);
  SNS_ASSERT(pm_err == SNS_PM_SUCCESS);
  sns_uimg_utils_mutex = sns_os_mutex_create(SNS_MEMMGR_DSPS_MUTEX, &sns_os_err);

  sns_os_mutex_pend(sns_uimg_utils_mutex, 0, &sns_os_err);
  for(i = 0; i < SNS_UIMG_SMR_MAX_CLIENTS; i++)
  {
    sns_memmgr_module_restrictions[i] = false;
  }
  sns_os_mutex_post(sns_uimg_utils_mutex);
}

SNS_MEMMGR_UIMAGE_CODE void sns_utils_place_uimge_hold(sns_uimg_module_e module)
{
  uint8_t sns_os_err;
  SNS_ASSERT(sns_utils_pm_client_handle != NULL);
  sns_pm_vote_img_mode(sns_utils_pm_client_handle, SNS_IMG_MODE_BIG);
  sns_os_mutex_pend(sns_uimg_utils_mutex, 0, &sns_os_err);
  sns_memmgr_module_restrictions[module] = true;
  sns_os_mutex_post(sns_uimg_utils_mutex);
}
