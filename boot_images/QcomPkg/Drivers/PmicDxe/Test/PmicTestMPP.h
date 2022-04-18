#ifndef __PMICTESTMPP_H__
#define __PMICTESTMPP_H__

/*! @file PMICTESTMPP.h
 *
 *  PMIC Test MPP
 *
 *  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.  All Rights Reserved. 
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/15/15   RM      Added Pmic Test LPG Header file

===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <Protocol/EFIPmicMpp.h>

/*===========================================================================
                     MACRO DEFINATIONS
===========================================================================*/


/*===========================================================================
                     TYPE DECLARATIONS
===========================================================================*/

/* ATEST*/
typedef enum
{
  EFI_PM_MPP__CH_ATEST1,
  EFI_PM_MPP__CH_ATEST2,
  EFI_PM_MPP__CH_ATEST3,
  EFI_PM_MPP__CH_ATEST4,
  EFI_PM_MPP__CH_ATEST_INVALID
}EFI_PM_MPP_CH_ATEST_TYPE;

typedef enum
{
    EFI_PM_TEST_MPP_CONFIG_ATEST,
    EFI_PM_TEST_MPP_SET_LIST_SHUNT_CAP,
    EFI_PM_TEST_MPP_GET_LIST_SHUNT_CAP,
    EFI_PM_TEST_MPP_ENABLE
}EFI_PM_TEST_DRIVER_MPP_TYPE_FUNCTION;

typedef struct _EFI_PM_TEST_MPP_CONFIG_ATEST_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_MPP_WHICH_TYPE MppIndex;
    EFI_PM_MPP_CH_ATEST_TYPE Atest_select;
} EFI_PM_TEST_MPP_CONFIG_ATEST_PARAM;

typedef struct _EFI_PM_TEST_MPP_SET_GET_LIST_SHUNT_CAP_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_MPP_WHICH_TYPE MppIndex;
    uint32  *ShuntList;
} EFI_PM_TEST_MPP_SET_GET_LIST_SHUNT_CAP_PARAM;

typedef struct _EFI_PM_TEST_MPP_ENABLE_PARAM
{
    UINT8       DeviceIndex;
    EFI_PM_MPP_WHICH_TYPE MppIndex;
    boolean Enable;
}EFI_PM_TEST_MPP_ENABLE_PARAM;

typedef union _EFI_PM_TEST_MPP_FUNCTION_TYPE
{
    EFI_PM_TEST_MPP_CONFIG_ATEST_PARAM                MppConfigATest;
    EFI_PM_TEST_MPP_SET_GET_LIST_SHUNT_CAP_PARAM          MppShuntCap;
    EFI_PM_TEST_MPP_ENABLE_PARAM                      MppEnable;
}EFI_PM_TEST_MPP_FUNCTION_TYPE;

/*===========================================================================
                       FUNCTION PROTOTYPES
===========================================================================*/



#endif // __PMICTESTMPP_H__


