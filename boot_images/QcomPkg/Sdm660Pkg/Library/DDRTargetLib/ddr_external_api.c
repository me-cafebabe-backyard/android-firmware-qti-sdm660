/*
===========================================================================

FILE:         ddr_external_api.c

DESCRIPTION:  
  This is external APIs to support usage of SCALe sequences

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 
===========================================================================
                                EDIT HISTORY

================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
06/16/16   qbz     Added DDI support.
04/05/14   sr      Initial version.
================================================================================
*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "seq_hwio.h"
#include "ddr_external.h"
#include "ddr_params.h"
#include "ClockBoot.h"
#include "ddr_target.h"
#include "busywait.h"
#include "ddr_hwio.h"

#include  "boot_error_if.h"
#include "boot_extern_ddi_api_interface.h"
#include "boot_build_component.h"


/*==============================================================================
                                  MACROS
==============================================================================*/
#define MAX_AVAILABLE_TEMP_TRAINING_BUFFER ( 64 * 1024 ) /* 100kb */

/*==============================================================================
                                  DATA
==============================================================================*/
/* reserve 20kb for training data */
static uint32 training_data_offset = 20 * 1024;

/* starting from offset of 0 for extended training log */
static uint32 training_log_offset_size = 0; 
/*==============================================================================
                                  ASSEMBLY
==============================================================================*/


/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void sbl1_save_ddr_training_data_to_partition
(
  uint8* ddr_training_data_ptr,
  uint32 ddr_training_data_size,
  uint32 ddr_training_data_offset
);
/* ============================================================================
**  Function : ddr_external_set_clk_speed
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to set the clock speed
*   
*   @details
*   This api will set the clock speed accordingly as specified in the parameter to this function
*   
*   @param 
*   @param clk_in_khz       -  [IN] clock speed in khz 
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   
*   @sa None
*/

boolean ddr_external_set_clk_speed(uint32 clk_in_khz)
{
     Clock_SetBIMCSpeed(clk_in_khz);
     return TRUE;
}

/* ============================================================================
**  Function : ddr_mpm_config_ebi1_freeze_io
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library while entering/exiting Power Collapse
*   
*   @details
*   This api will be called by SNS library to enable/disable IO clamps during PC
*   
*   @param 
*   @param flag         -  [IN] boolean flag to enable/disable IO clamps
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

void ddr_mpm_config_ebi1_freeze_io( boolean flag ) 
{ 
	if(flag)
	{
		HWIO_OUTF(MPM2_MPM_DDR_PHY_FREEZEIO_EBI1, DDR_PHY_FREEZEIO_EBI1, 0x1);
	}
	else
	{
		HWIO_OUTF(MPM2_MPM_DDR_PHY_FREEZEIO_EBI1, DDR_PHY_FREEZEIO_EBI1, 0x0);
	}
}


/* ============================================================================
**  Function : ddr_external_get_buffer
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @details
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @param 
*   @param buffer             -  [IN/OUT] uint32 ** buffer where we will populate 
*                                                   with pointer to buffer
*   @param size               -  [IN] uint32 *  we will populate with size of 
*                                                   buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   reutrn operation success\failure
*   
*   @sa None
*/
boolean ddr_external_get_buffer( void ** buffer, uint32 *size )
{
  *buffer = (void *)(0x290000); 
  if ( *size > MAX_AVAILABLE_TEMP_TRAINING_BUFFER )
	  return FALSE ;
  memset(*buffer, 0, *size);
  return TRUE;
}

/* ============================================================================
**  Function : ddr_external_page_to_storage
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage
*   
*   @details
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage. This api has to take care of offsets for 
* 	saving to external storage so we do not run out of space.
*   api will perform a memset 0 on input buffer of input size before returning
*   
*   @param 
*   @param buffer             -  [IN] uint32 * buffer where traiing logs are located
*   @param size               -  [IN] uint32  size of data in buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  void
*
*   
*   @sa None
*/
void ddr_external_page_to_storage( void * buffer, uint32 size )
{
	if(PcdGet32 (PcdBuildType) != SBL_BUILD_DDRDEBUGIMAGE)
	{
		if(buffer != NULL)
		{
			if( size != 0 && 
			(size+training_log_offset_size+training_data_offset) < DDR_MAX_LOG_SIZE)
			{
				/* call sbl1 function to save into flash storage */
				sbl1_save_ddr_training_data_to_partition(buffer, 
													   size, 
													   training_log_offset_size + training_data_offset);	

				/* increment offset for next page*/
				training_log_offset_size += size;

				/* check to see if offset is 1k aligned, if not we need to pad it */
				if(training_log_offset_size%1024 != 0)
				{
					/* divide by 1024 (round down divide), add 1 to the result and multiply by
					 * 1024 again to get the rounded up to 1k align size
					 * this is equivalent operation of doing a round up divide by 1024 then 
					 * multiply by 1024 again
					 */
					training_log_offset_size =  ((training_log_offset_size/1024)+1) * 1024;
				}
			}

			/* zero initialize buffer regardless  */
			memset(buffer, 0, size);
		}
	
	
	}
	else
	{
	 /* zero initialize buffer   */
		memset(buffer, 0, size);
	
	}

 
}

/* ============================================================================
**  Function : ddr_external_get_training_log_size
** ============================================================================
*/
/*!
*   @brief
*   This function is used to return the current stored training log size
*   
*   @details
*   This function is used to return the current stored training log size
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  uint32
*   size of current trainig log saved to emmc
*   
*   @sa None
*/
uint32 ddr_external_get_training_log_size(void)
{
  return training_log_offset_size;
}

boolean ddr_external_set_ddrss_cfg_clk(boolean on_off)
{
/* Clock_EnableClock & Clock_DisableClock APIs are not 
   supported in SBL1 and only supported on RPM */ 
   return TRUE;
}

void seq_wait(uint32 time_value, SEQ_TimeUnit time_unit)
  {

    if(time_unit == SEC)
    {
       busywait(time_value * 1000 * 1000);
    }
    else if(time_unit == MS)
    {
       busywait(time_value * 1000);
    }
    else if(time_unit == US)
    {
       busywait(time_value);
    }
    else
    {
       /* time_unit == NS */
       busywait(time_value / 1000);
    }

}

/* ============================================================================
**  Function : ddr_send_data_to_ddi
** ============================================================================
*/
/*!
*   @brief
*   This function is called during training to pass training results to ddi
*   
*   @details
*   This function is called during training to pass training results to ddi
*   
*   @param 
*   @param flag             -  [IN] boolean flag to enable/disable IO clamps
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

void ddr_external_send_data_to_ddi(void * buffer, uint32 size, ddr_training_args* tArgs, void *training_params_ptr)
{ 
  boot_ddr_sendDatatoDDI(buffer, size, (ddr_training_args *)tArgs, training_params_ptr); 
} 

void ddr_abort(void)
{
  /* force assert boot error */
  BL_VERIFY(0,BL_ERR_CORE_VERIFY);
}