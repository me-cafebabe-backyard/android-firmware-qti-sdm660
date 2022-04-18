/*
===========================================================================

FILE:         ddr_params.c

DESCRIPTION:
  Information of DDR devices supported by target.

===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
03/12/14   sr      Initial revision.

===========================================================================
                   Copyright 2014 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
===========================================================================
*/

/*==============================================================================
                                    INCLUDES
==============================================================================*/
#include "ddr_params.h"
#include "crc.h"
#include "ddr_log.h"
#include "dev_flash_params.h"
#define USE_LOADER_UTILS
#include "LoaderUtils.h"
#include "boot_build_component.h"
#include "ddi_tool.h"

/*==============================================================================
                                      DATA
==============================================================================*/
/* Pointer to DDR CDT Header, updated by ddr_set_params() */
static struct ddr_device_params_header_v2 *ddr_device_header = NULL;

/* Pointer to extended cdt in memory, updated by ddr_set_params() */
static EXTENDED_CDT_STRUCT *ddr_ecdt_ptr = NULL;

/* Pointer to DDR detected params of CH0 and CH1, updated by ddr_set_params */
static struct detected_ddr_device_params *ddr_detected_params_ch0 = NULL;
static struct detected_ddr_device_params *ddr_detected_params_ch1 = NULL;

/* Pointer to device params (cdt params), updated by ddr_set_params */
static ddr_device_params *ddr_device_table = NULL;


/* Size of DDR CDT header, updated by ddr_set_params() */
static uint32 ddr_device_header_size = 0;

/* Size of extended cdt, updated by ddr_set_params() */
static uint32 ddr_ecdt_size = 0;

/* Size of DDR detected params, updated by ddr_set_params() */
static uint32 ddr_detected_params_size = 0;

/* Size of DDR device params, updated by ddr_set_params() */
static uint32 ddr_device_params_size = 0;

/* Number of entries in DDR device table, updated by ddr_set_params() */
static uint32 ddr_device_table_entry_num = 0;

/* Size of DDR device table entry, updated by ddr_set_params() */
static uint32 ddr_device_table_entry_size = 0;

DDR_STRUCT *ddrsns_share_data = (DDR_STRUCT *)DDR_GLOBAL_STRUCT_DATARAM_ADDR;


/*==============================================================================
                                   FUNCTIONS
==============================================================================*/


/* ============================================================================
**  Function : ddr_set_params
** ============================================================================
*/
/**
*   @brief
*   This function sets the DDR driver's device table to an external device table.
*   It will also update the interleaving mode information according to the parameter
*   header that's passed in.
*   User should append ddr_device_params_header_v1 header in front of their own DDR device 
*   table and pass  a pointer points to the beginning of this header via the this API to 
*   force DDR driver to utilize the user defined parameters.
*   The user defined ddr device table must contain a minimal number of entries to 
*   match the system's ddr devices.
*   For example if a system has two ddr devices attached then the external table must 
*   define at least two entries to match those two devices.
*   However, more entries can be added to the end of table to support other ddr devices
*   with different parameters.
*
*   @param[in]  ddr_params_ptr   Pointer to the external ddr parameters. It should
*                                point to the user defined ddr device table with ddr
*                                parameters header appended in front. This pointer must
*                                points to a 4 bytes aligned address.
*                         
*
*   @return
*   TRUE if DDR device table is updated, FALSE if an error happens and this operation
*   is aborted
*
*   @dependencies
*   Must be called prior to ddr_initialize_device. 
*   This API will take no effect after ddr_initialize_device
*
*   @sa
*   None
*
*   @sa
*   None
*/
boolean ddr_set_params(void *ddr_params_ptr, uint32 ddr_params_size)
{
  boolean status = FALSE;
  uint32 *ddr_params_header_version = NULL;

  do
  {
    /*First check to see if external ddr parameters exists*/
    if(ddr_params_ptr == NULL || ddr_params_size == 0)
    {
      break;
    }

    /*We know the first byte in ddr parameters data is its version number*/
    ddr_params_header_version = (uint32 *)ddr_params_ptr;

    if(*ddr_params_header_version == 2)
    {
      /*The beginning of external DDR parameters is a header which tells the
        number of interfaces and size of ddr device table entry*/
      ddr_device_header = (struct ddr_device_params_header_v2 *)
                          ddr_params_ptr;
      ddr_device_header_size = DDR_PARAMS_HEADER_V2_SIZE;

      /*Check if the magic number in the header is correct*/
      if(ddr_device_header->magic_number != DDR_PARAMS_MAGIC_NUM)
      {
        break;
      }
	  
	  ddr_detected_params_ch0 = (struct detected_ddr_device_params *) ((size_t)ddr_params_ptr + ddr_device_header_size);
	  ddr_detected_params_size = sizeof(struct detected_ddr_device_params);
	  ddr_detected_params_ch1 = (struct detected_ddr_device_params *) ((size_t)ddr_detected_params_ch0 + ddr_detected_params_size);
	  
	  /* Do not memset the ddr_struct to zero when ddr_struct_cookie is set to 0xCEACC00C */
	  if (PcdGet32 (PcdBuildType) != SBL_BUILD_DDRDEBUGIMAGE)
	  {
		  if(ddrsns_share_data->misc.ddr_struct_cookie != DDR_STRUCT_COOKIE)
		  {
			  /* memset the 8KB dataram pointer to zero */
			  memset(ddrsns_share_data, 0x0, sizeof(DDR_STRUCT));
			  ddrsns_share_data->detected_ddr_device[0] = *ddr_detected_params_ch0;
	          ddrsns_share_data->detected_ddr_device[1] = *ddr_detected_params_ch1;
		  }
	  }
	  else
	  {
	    if (ddrsns_share_data->ddi_buf[0] != DDI_MAGIC_IS_RETRAINED)// DDI came out of training
	    {
	      /* leave the ddi_buf as is */
	      memset(ddrsns_share_data, 0x0, (sizeof(DDR_STRUCT)-sizeof(ddrsns_share_data->ddi_buf)));
	    }
		ddrsns_share_data->detected_ddr_device[0] = *ddr_detected_params_ch0;
	    ddrsns_share_data->detected_ddr_device[1] = *ddr_detected_params_ch1;
	  }
	  
      /* Update number of device table entries*/
      ddr_device_table_entry_num = ddr_device_header->num_of_device;

      /* Update size of device table entry */
      switch (ddr_detected_params_ch0->device_type)
      {
        case DDR_TYPE_LPDDR2:
        case DDR_TYPE_LPDDR3:
      	case DDR_TYPE_LPDDR4:
				case DDR_TYPE_LPDDR4X:
      	    ddr_device_table_entry_size = sizeof(struct ddr_device_params_lpddr);
            if(ddr_detected_params_ch0->device_type == DDR_TYPE_LPDDR4 || ddr_detected_params_ch0->device_type == DDR_TYPE_LPDDR4X)
			{
				ddr_device_table = (ddr_device_params *) ((size_t)ddr_detected_params_ch1 + ddr_detected_params_size);
				ddr_device_params_size = sizeof(ddr_device_params);
				ddrsns_share_data->cdt_params = *ddr_device_table; 
      	    }
			break;

        case DDR_TYPE_PCDDR3:
            ddr_device_table_entry_size = sizeof(struct ddr_device_params_pcddr3);
			break;

        default:
            ddr_device_table_entry_size = 0;
			break;
      }
	  
	  /* parse for extended CDT params */
	  ddr_ecdt_ptr = (EXTENDED_CDT_STRUCT *) ((size_t)ddr_device_table + ddr_device_params_size);
      ddr_ecdt_size = sizeof(EXTENDED_CDT_STRUCT);

      /* Check if size of device table entry matches size written in header */
      if (ddr_device_table_entry_size == 0 ||
          ddr_device_table_entry_size != ddr_device_header->size_of_param)
      {
        break;
      }
    }
    else
    {
      /* Currently only Version 2 is supported */
      break;
    }

    status = TRUE;

  } while(0);

  return status;
}


/* ============================================================================
**  Function : ddr_get_header
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters header. This contains useful information such as
*   interleave mode, optional features, etc that applies to all ddr devices
*
*   @param[in]  None
*
*   @return
*   DDR device header
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
struct ddr_device_params_header_v2 *ddr_get_header(void)
{
#ifdef BUILD_BOOT_CHAIN
    /* Use external table for Boot */
    return ddr_device_header;
#else
    /* Use shared IMEM table for RPM */
    return shared_ddr_device_table_header;
#endif
} /* ddr_get_header */

/* ============================================================================
**  Function : ddr_get_params
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters.
*
*   @param[in]  interface_name  Interface to get DDR device parameters for
*
*   @return
*   DDR device parameters
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
ddr_device_params *ddr_get_params(DDR_CHANNEL interface_name)
{
  ddr_device_params *device_params;
  
  device_params = &(ddrsns_share_data->cdt_params);

  return device_params;
} /* ddr_get_params */

/* ============================================================================
**  Function : ddr_get_detected_params
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters.
*
*   @param[in]  interface_name  Interface to get DDR device parameters for
*
*   @return
*   DDR device parameters
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
struct detected_ddr_device_params *ddr_get_detected_params(DDR_CHANNEL interface_name)
{
  struct detected_ddr_device_params *ddr_detected_params;
  
  ddr_detected_params = (interface_name == DDR_CH0) ? &(ddrsns_share_data->detected_ddr_device[0])
															: &(ddrsns_share_data->detected_ddr_device[1]);

  return ddr_detected_params;
} /* ddr_get_detected_params */

/* ============================================================================
**  Function : ddr_get_extended_cdt_params
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters.
*
*   @param[in]  interface_name  Interface to get DDR device parameters for
*
*   @return
*   DDR device parameters
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
void *ddr_get_extended_cdt_params(void)
{
  if(ddr_ecdt_size != 0)
  {
    return (void *)ddr_ecdt_ptr;
  }
  else
  {
    return NULL;
  }
} /* ddr_get_extended_cdt_params */


/* ============================================================================
**  Function : ddr_param_interleaved
** ============================================================================
*/
/**
*   @brief
*   Return the interleave setting based on ddr parameters
*
*   @return
*   return a bitmask of interleave status
*
*   @dependencies
*   Must be called after ddr_set_params. Calling it before ddr_set_params will
*   return the default setting which is TRUE.
*
*   @sa
*   None
*
*   @sa
*   None
*/
uint32 ddr_param_interleaved(void)
{
  return ddrsns_share_data->detected_ddr_device[0].interleave_en;
}

/* =============================================================================
**  Function : ddr_params_get_training_data
** =============================================================================
*/
/**
*   @brief
*   Get DDR parameter partition: partition base is returned, and partition size
*   is updated through pointer.
*
*   @param[out]  size  DDR parameter partition size
*
*   @return
*   DDR parameter partition base
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
void *ddr_params_get_training_data(uint32 *size)
{
  *size = sizeof(struct ddr_params_partition);

  return (void *)&(ddrsns_share_data->flash_params);

} /* ddr_params_get_partition */

/* =============================================================================
**  Function : ddr_params_set_training_data
** =============================================================================
*/
/**
*   @brief
*   Set DDR parameter partition.
*
*   @param[in]  base  DDR parameter partition base
*   @param[in]  size  DDR parameter partition size
*
*   @retval  TRUE   Partition set successfully
*   @retval  FALSE  Partition set unsuccessfully
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_params_set_training_data(void *base, uint32 size)
{
  boolean success = FALSE;

  if ( base != NULL && size == sizeof(struct ddr_params_partition) )
  {
    ddrsns_share_data->flash_params = *(struct ddr_params_partition *)base;
    success = TRUE;
  }
  return success;
}


/* =============================================================================
**  Function : ddr_get_training_checksum
** =============================================================================
*/
/**
*   @brief
*   Get DDR training checksum.
*
*   @param
*   None
*
*   @return
*   DDR training data checksum, 0 if no valid training partition is found
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
uint32 ddr_get_training_checksum(uint32 serial_number)
{
  uint32 tr_data_size_in_bits = 0;
  uint32 crc32_training = 0x0UL;
  
  uint8 crc_buff[sizeof(struct ddr_clock_plan) * MAX_NUM_CLOCK_PLAN + sizeof(uint32)] = {0}; //buffer clock plan/fmax
  uint32 clk_plan_tbl_size = sizeof(struct ddr_clock_plan) * ddrsns_share_data->misc.ddr_num_clock_levels;
  uint32 clock_freq_size_in_bits = 0, i = 0;
  uint32 crc32_clock_freq = 0x0UL;
  
  if (&(ddrsns_share_data->flash_params) != NULL)
  {
    /* Calculate the training data size in bits */
    tr_data_size_in_bits = sizeof(uint8) * (TRAINING_DATA_SIZE_IN_BYTES-1) * 8; /* TRAINING_DATA_SIZE_IN_BYTES is the training size for LP4 , allocated in ddr_params_partition */
    crc32_training = crc_32_calc((uint8 *)(ddrsns_share_data->flash_params.training_data), (uint16)(tr_data_size_in_bits), serial_number);

    /* buffer clock plan */
    for(i = 0; i < clk_plan_tbl_size; i++) {
      crc_buff[i] = *((uint8*)&(ddrsns_share_data->misc.clock_plan) + i);
  }

    /* buffer fmax*/
    for(i = 0; i < sizeof(uint32); i++) {
      crc_buff[clk_plan_tbl_size + i] = *((uint8*)&(ddrsns_share_data->misc.max_ddr_frequency) + i);
    }

    /* Calculate clock_plan/max_ddr_frequency crc */
    clock_freq_size_in_bits = sizeof(uint8) * (clk_plan_tbl_size + sizeof(uint32)) * 8;
    crc32_clock_freq = crc_32_calc(crc_buff, (uint16)(clock_freq_size_in_bits), serial_number);

    ddr_printf (DDR_NORMAL, "DDR: Computed CRC checksum retrieved from flash is %d", crc32_training ^ crc32_clock_freq);
    return crc32_training ^ crc32_clock_freq;
  }
  else
  {
    return 0;
  }
}
/* =============================================================================
**  Function : ddr_set_training_checksum
** =============================================================================
*/
/**
*   @brief
*   Compute the checksum over entire training data
*
*   @param
*   Serial number
*
*   @return
*   CRC checksum
*
*   @dependencies
*   None
*
*   @sideeffects
*   None
*
*   @sa
*   None
*/
boolean ddr_set_training_checksum(uint32 serial_number)
{
  uint32 tr_data_size_in_bits = 0;
  uint32 crc32_training = 0x0UL;
	
  uint8 crc_buff[sizeof(struct ddr_clock_plan) * MAX_NUM_CLOCK_PLAN + sizeof(uint32)] = {0}; //buffer clock plan/fmax
  uint32 clk_plan_tbl_size = sizeof(struct ddr_clock_plan) * ddrsns_share_data->misc.ddr_num_clock_levels;
  uint32 clock_freq_size_in_bits = 0, i = 0;
  uint32 crc32_clock_freq = 0x0UL;

  if (&(ddrsns_share_data->flash_params) != NULL)
  {
      /* Calculate the training data size in bits */
    tr_data_size_in_bits = sizeof(uint8) * (TRAINING_DATA_SIZE_IN_BYTES-1) * 8; /* TRAINING_DATA_SIZE_IN_BYTES is the training size for LP4 , allocated in ddr_params_partition */ 
    crc32_training = crc_32_calc((uint8 *)(ddrsns_share_data->flash_params.training_data), (uint16)(tr_data_size_in_bits), serial_number);

    /* buffer clock plan */
    for(i = 0; i < clk_plan_tbl_size; i++) {
      crc_buff[i] = *((uint8*)&(ddrsns_share_data->misc.clock_plan) + i);
    }

    /* buffer fmax*/
    for(i = 0; i < sizeof(uint32); i++) {
      crc_buff[clk_plan_tbl_size + i] = *((uint8*)&(ddrsns_share_data->misc.max_ddr_frequency) + i);
    }

    /* Calculate clock_plan/max_ddr_frequency crc */
    clock_freq_size_in_bits = sizeof(uint8) * (clk_plan_tbl_size + sizeof(uint32)) * 8;
    crc32_clock_freq = crc_32_calc(crc_buff, (uint16)(clock_freq_size_in_bits), serial_number);

    ddrsns_share_data->flash_params.checksum = crc32_training ^ crc32_clock_freq;
    ddr_printf (DDR_NORMAL, "DDR: Checksum to be stored on flash is %d", ddrsns_share_data->flash_params.checksum);
	  return TRUE;
  }
  else
  {
    return FALSE;
  }
}
