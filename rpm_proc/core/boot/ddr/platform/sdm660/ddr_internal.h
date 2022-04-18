#ifndef DDR_INTERNAL_H
#define DDR_INTERNAL_H

/**
 * @file ddr_internal.h
 * @brief
 * Function headers of DDR drivers internal private API
 */

/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/platform/sdm660/ddr_internal.h#1 $ 
$DateTime: 2016/11/03 00:13:13 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
12/06/12   tw      Added support for mx scaling
12/08/11   tw      Initial revision.
================================================================================
                  Copyright 2011 Qualcomm Technologies Incorporated.
                            All Rights Reserved.
                    Qualcomm Confidential and Proprietary
==============================================================================*/
#include "ddr_params.h"
#include "ddr_common.h"
#include "railway.h"

/* -----------------------------------------------------------------------
**                           DEFINES
** ----------------------------------------------------------------------- */

#define DDR_TRAINING_REQUIRED         0x6188709B
#define DDR_TRAINING_NOT_REQUIRED     0xACBE001F
#define DDR_TRAINING_DATA_UPDATED     0xDAAA11E1
#define DDR_TRAINING_DATA_NOT_UPDATED 0xDE8D526A
#define DDR_TEST_FRAMEWORK           0x3E3F2431


/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* ============================================================================
**  Function : ddr_target_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called at the end of ddr init to initialize any 
*   target specific configurations 
*   
*   @details
*   Target specific configurations such as override of timing registers and 
*   calling target specific init functions will be captured in this api
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_target_init(void);


/* ============================================================================
**  Function : ddr_pre_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before vddcx voltage switch occurs.
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_pre_vddcx_switch(const railway_settings *proposal, void * callback_cookie);

/* ============================================================================
**  Function : ddr_post_vddcx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after vddcx voltage switch occurs.
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddcx_switch(const railway_settings *proposal, void * callback_cookie);

/* ============================================================================
**  Function : ddr_pre_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right before vddmx voltage switch occurs.
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_pre_vddmx_switch(const railway_settings *proposal, void * callback_cookie);

/* ============================================================================
**  Function : ddr_post_vddmx_switch
** ============================================================================
*/
/*!
*   @brief
*   This function is called right after vddmx voltage switch occurs.
*
*   @param none
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval None
*
*   @sa None
*/

void ddr_post_vddmx_switch(const railway_settings *proposal, void * callback_cookie);

/* ============================================================================
**  Function : ddr_increase_clock_speed
** ============================================================================
*/
/*!
*   @brief
*   This function will bump up the clock speed for ddr to the maximum nominal
*   frequency
*
*   @details
*   This function will use clkrgm npa voting to vote for max nominal nominal
*   frequency
*
*   @param None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval
*   boolean - operation successful or not.
*
*   @sa None
*/

boolean ddr_increase_clock_speed(void);

void ddr_test_framework(void);
#endif
