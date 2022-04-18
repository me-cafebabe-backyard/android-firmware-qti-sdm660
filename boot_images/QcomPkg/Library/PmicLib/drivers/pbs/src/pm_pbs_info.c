/*! \file  pm_pbs_info.c
 *  
 *  \brief  This file contains the pmic PBS info driver implementation.
 *  \details  This file contains the pm_pbs_info_init & pm_pbs_info_store_glb_ctxt
 *  API implementations.
 *  
 *  &copy; Copyright 2014 - 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
10/12/2016   akm     Added pm_get_pon_reasons, pm_get_pon_reasons_to_dump API
08/12/2016   akm     Added pm_pbs_header_info API
12/04/2015   aab     Updated  pm_pbs_info_otp_read() and  pm_pbs_info_ram_read() 
04/29/2015   aab     Added support for PMK8001 
07/16/2014     akm     Comm change Updates
11/20/2013   mr      Removed KW errors for Banned Functions API (CR-512648)
11/18/2013   kt      Added test pgm rev to pbs_info struct (increment struct format)
11/01/2013   plc     Update for Arm6 syntax ("attribute")
03/19/2013   kt      Added pm_pbs_info_add_ram_sequence API.
10/19/2012   umr     PBS Core Driver.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pbs.h"
#include "pm_pbs_driver.h"
#include "pm_pbs_info.h"
#include "pm_version.h"
#include "DALGlbCtxt.h"
#include "CoreVerify.h"
#include "pm_config_sbl.h"
#include "pm_device.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
#define DALGLBCTXT_LOCK_TYPE_SPINLOCK        0x010000

/* Format of the pm_pbs_info_smem_type structure */ 
#define PM_PBS_INFO_SMEM_FORMAT              4

#define PON_RSN_HIST_SIGNATURE 0x5250



/** 
  @struct pm_pbs_info_smem_type
  @brief Structure for the shared memory location which is used
         to store PMIC PBS related information such as PBS Lot
         ID, ROM Version, RAM Version, Fab Id, Wafer Id, X
         coord, Y coord and Test PGM Rev. PBS ROM/RAM Revision
         id and Variant (or Branch) id are stored in last 16
         bits(upper and lower 8 bits) of rom_version and
         ram_version.
 */
typedef struct
{
  uint32         format;                           /* Starts from 1 and increments if we add more data */
  uint8          lot_id[PM_PBS_INFO_NUM_LOT_IDS];  /* PBS Lot Id */
  uint32         rom_version;                      /* PBS ROM Version number */
  uint32         ram_version;                      /* PBS RAM Version number */
  uint32         fab_id;                           /* PBS Fab Id */
  uint32         wafer_id;                         /* PBS Wafer Id */
  uint32         x_coord;                          /* PBS X Coord */
  uint32         y_coord;                          /* PBS Y Coord */
  uint32         test_pgm_rev;                     /* PBS Test PGM Rev */
  pm_pbs_info_mfgid_type  mfg_id;                  /* PBS MGF ID */
} pm_pbs_info_smem_type;

/** 
  @struct pm_pbs_info_glb_ctxt_type
  @brief Global context data structure for sharing the pbs info 
         across processors.
 */
typedef struct
{
  DALGLB_HEADER             dal_glb_header;
  pm_pbs_info_smem_type     pbs_info_glb_arr[PM_MAX_NUM_PMICS];
} pm_pbs_info_glb_ctxt_type;

/* Static global variables to store the pbs info */
static pm_pbs_info_smem_type pm_pbs_info_arr[PM_MAX_NUM_PMICS];

/* Static global variables to store the pbs header info */
pm_pbs_header_info_type pm_pbs_header_info_arr[PM_MAX_NUM_PMICS];
pm_pbs_header_dataset_type_v1 pm_pbs_header_dataset_arr[PM_MAX_NUM_PMICS] ;
boolean pbs_header_info_init = FALSE;

/* Flag to check if PBS Info driver is initialized */
static boolean pm_pbs_info_initialized = FALSE;

/* Pointer to the PBS_INFO_DATA Structure */
static pm_pbs_info_data_type *pm_pbs_data = NULL;

//Global variable to Store PON reason History before PM device init 
static pm_pbs_pon_reason_history_data_type pon_reason_history[1];
   

/*==========================================================================

                FUNCTION DEFINITIONS

==========================================================================*/
/** 
 * @name pm_pbs_info_otp_read
 *  
 * @brief This is an internal helper function for reading
 *        PBS info for PBS Peripheral with 128/256 word ROM
 *        and RAM support. This function reads the PBS
 *        ROM/RAM addresses for PMIC PBS Manufacturing IDs
 *        and foundry information such as PBS Lot ID, ROM
 *        Version, RAM Version, Fab Id, Wafer Id, X coord
 *        and Y coord. This function internally calls
 *        pm_pbs_enable/disable_access to enable/disable
 *        PBS ROM/RAM access and pm_pbs_config_access to
 *        configure READ BURST mode access to PBS ROM/RAM.
 *  
 * @param[in]  slave_id. PMIC chip's slave id value.
 * @param[out] pbs_info_ptr: Variable to return to the caller with
 *             PBS info. Please refer to pm_pbs_info_smem_type structure
 *             above for more info on this structure.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          else SPMI ERROR.
 *  
 * @dependencies None.
 */
static pm_err_flag_type pm_pbs_info_otp_read (uint32 slave_id, pm_pbs_info_smem_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32           read_info_temp = 0;
  uint16           pbs_element_info_temp_addr = 0;  /* Address from where PBS Info to be read */

  uint8            lot_info_cnt = PM_PBS_INFO_NUM_LOT_IDS;
  uint8            lot_info_reg_reads_cnt = (PM_PBS_INFO_NUM_LOT_IDS/3);

  pbs_info_ptr->format = PM_PBS_INFO_SMEM_FORMAT;

  /* Configuring to enable PBS core access for ROM reads */
  err_flag = pm_pbs_enable_access(slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Configuring the base address for reading PBS ROM info.
   * PM_PBS_INFO_ADDR = pm_pbs_data->pbs_otp_start_addr + 4 * [pm_pbs_data->pbs_otp_mem_size - 7];
   */
  pbs_element_info_temp_addr = pm_pbs_data->pbs_otp_start_addr + 4 * (pm_pbs_data->pbs_otp_mem_size - PM_PBS_ROM_INFO_LINE_FROM_END);

  err_flag = pm_pbs_config_access(slave_id, pbs_element_info_temp_addr, PM_PBS_ACCESS_READ_BURST);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Reading the Fab id and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_info_temp, 1);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
     return err_flag;
  }

  /* Masking the opcode and reserved bits from temp variable 
     storing the Fab id and TEST_PGM_REV in the pbs info struct */
  pbs_info_ptr->test_pgm_rev = (uint32)(read_info_temp & 0x000000FF);
  pbs_info_ptr->fab_id = (uint32)((read_info_temp>>8) & 0x000000FF);
  read_info_temp = 0;

  /* Reading the Wafer ID, X and Y coords and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_info_temp, 1);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
     return err_flag;
  }

  /* Masking the opcode bits from temp variable storing the Wafer ID, X and
     Y coords along with the existing Fab ID in the pbs info struct */
  pbs_info_ptr->wafer_id = (uint32)(read_info_temp & 0x000000FF);
  pbs_info_ptr->x_coord = (uint32)((read_info_temp>>8) & 0x000000FF);
  pbs_info_ptr->y_coord = (uint32)((read_info_temp>>16) & 0x000000FF);
  read_info_temp = 0;

  /* Reading the LOT info and storing it in the pbs info struct */
  while((lot_info_reg_reads_cnt != 0) && (lot_info_cnt > 2))
  {
    /* Reading the LOT info and storing it in temp variable */
    err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_info_temp, 1);

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }

    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)(read_info_temp & 0x000000FF);
    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)((read_info_temp >> 8) & 0x000000FF);
    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)((read_info_temp >> 16) & 0x000000FF);

    read_info_temp = 0;

    lot_info_reg_reads_cnt--;
  }

  /* Reading the ROM version info and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_info_temp, 1);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Store the ROM version info in the PBS Info struct */
  pbs_info_ptr->rom_version = (uint32)(read_info_temp & 0x0000FFFF);
  read_info_temp = 0;


  /* Configuring to disable PBS core read access */
  err_flag = pm_pbs_disable_access(slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  return err_flag;
}



/** 
 * @name pm_pbs_info_ram_read
 *  
 * @brief This is an internal helper function for reading
 *        PBS info for PBS Peripheral with 128/256 word 
 *        RAM support. This function reads the PBS
 *        RAM addresses for PMIC PBS Manufacturing IDs
 *        and foundry information such as PBS Lot ID, ROM
 *        Version, RAM Version, Fab Id, Wafer Id, X coord
 *        and Y coord. This function internally calls
 *        pm_pbs_enable/disable_access to enable/disable
 *        PBS RAM access and pm_pbs_config_access to
 *        configure READ BURST mode access to PBS ROM/RAM.
 *  
 * @param[in]  slave_id. PMIC chip's slave id value.
 * @param[out] pbs_info_ptr: Variable to return to the caller with
 *             PBS info. Please refer to pm_pbs_info_smem_type structure
 *             above for more info on this structure.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          else SPMI ERROR.
 *  
 * @dependencies None.
 */
static pm_err_flag_type pm_pbs_info_ram_read (uint32 slave_id, pm_pbs_info_smem_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32           read_info_temp = 0;
  uint16           pbs_element_info_temp_addr = 0;  /* Address from where PBS Info to be read */


  pbs_info_ptr->format = PM_PBS_INFO_SMEM_FORMAT;

  /* Configuring to enable PBS core access for ROM reads */  
  err_flag = pm_pbs_enable_access(slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }


  /* Configuring the base address for reading PBS RAM version info */
  pbs_element_info_temp_addr = pm_pbs_data->pbs_ram_start_addr + 4 * (pm_pbs_data->pbs_ram_mem_size - PM_PBS_MEMORY_VER_LINE_FROM_END);

  err_flag = pm_pbs_config_access(slave_id, pbs_element_info_temp_addr, PM_PBS_ACCESS_READ_BURST);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Reading the RAM version info and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_info_temp, 1);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Store the RAM version info in the PBS Info struct */
  pbs_info_ptr->ram_version = (uint32)(read_info_temp & 0x0000FFFF);
  read_info_temp = 0;

  /* Configuring to disable PBS core read access */
  err_flag = pm_pbs_disable_access(slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  return err_flag;
}



/** 
 * @name pm_pbs_info_rom_init 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_rom_init (void) 
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
  uint32             slave_id = 0;
  uint8              pmic_index = 0;
  uint8              data = 0;

  DALSYS_memset(pm_pbs_info_arr, 0, sizeof(pm_pbs_info_arr));

  /* Retrieve place where PBS info stored */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);

  if(NULL == pm_pbs_temp_data)
  {
     return PM_ERR_FLAG__INVALID_POINTER;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Get PMIC device primary slave id */
    err_flag = pm_get_slave_id(pmic_index, 0, &slave_id);

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      /* Second or third PMIC doesn't exist */
      err_flag = PM_ERR_FLAG__SUCCESS;
      continue;
    }

    /* Read PBS Peripheral info and check if PBS peripheral exists */
    err_flag = pm_comm_read_byte(slave_id, PMIO_PBS_CORE_PERPH_TYPE_ADDR, &data, 0);

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
       return err_flag;
    }

    if (data != PM_HW_MODULE_PBS)
    {
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    pm_pbs_data = pm_pbs_temp_data[pmic_index];

    if((pm_pbs_data == NULL) || (PM_PBS_INFO_IN_MISC == pm_pbs_data->pbs_info_place_holder))
    {
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    /* Read all the PMIC's PBS Manufacturing IDs from PBS ROM */
    err_flag = pm_pbs_info_otp_read(slave_id, &(pm_pbs_info_arr[pmic_index]));

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      /* Configuring to disable PBS core read access */
      pm_pbs_disable_access(slave_id);

      return err_flag;
    }
  }

  pm_pbs_info_initialized = TRUE;
  return err_flag;
}

/** 
 * @name pm_pbs_info_ram_init 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_ram_init (void) 
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
  uint32             slave_id = 0;
  uint8              pmic_index = 0;
  uint8              data = 0;


  /* Return error if PBS ROM driver is not already initialized */
  if (!pm_pbs_info_initialized)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
 	

  /* Retrieve place where PBS info stored */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);

  if(NULL == pm_pbs_temp_data)
  {
     return PM_ERR_FLAG__INVALID_POINTER;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Get PMIC device primary slave id */
    err_flag = pm_get_slave_id(pmic_index, 0, &slave_id);

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      /* Second or third PMIC doesn't exist */
      err_flag = PM_ERR_FLAG__SUCCESS;
      continue;
    }

    /* Read PBS Peripheral info and check if PBS peripheral exists */
    err_flag = pm_comm_read_byte(slave_id, PMIO_PBS_CORE_PERPH_TYPE_ADDR, &data, 0);

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
       return err_flag;
    }

    if (data != PM_HW_MODULE_PBS)
    {
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    pm_pbs_data = pm_pbs_temp_data[pmic_index];

    if((pm_pbs_data == NULL) || (PM_PBS_INFO_IN_MISC == pm_pbs_data->pbs_info_place_holder))
    {
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    /* Read all the PMIC's PBS Manufacturing IDs from PBS ROM */
    err_flag = pm_pbs_info_ram_read(slave_id, &(pm_pbs_info_arr[pmic_index]));

    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      /* Configuring to disable PBS core read access */
      pm_pbs_disable_access(slave_id);

      return err_flag;
    }
  }

  pm_pbs_info_initialized = TRUE;
  return err_flag;
}

/** 
 * @name pm_pbs_info_store_glb_ctxt 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_store_glb_ctxt (void) 
{
  pm_pbs_info_glb_ctxt_type*  pbs_glb_ctxt_ptr = NULL;
  uint8                       pmic_index = 0;

  /* Return error if PBS driver is not already initialized */
  if (!pm_pbs_info_initialized)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Ensure global context has been initialized */
  if(DAL_SUCCESS != DALGLBCTXT_Init())
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Allocate the context */
  if(DAL_SUCCESS != DALGLBCTXT_AllocCtxt("PM_PBS_INFO", sizeof(pm_pbs_info_glb_ctxt_type),
                                         DALGLBCTXT_LOCK_TYPE_SPINLOCK, (void **)&pbs_glb_ctxt_ptr))
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  if (pbs_glb_ctxt_ptr == NULL)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Fill in the global context with PMIC's PBS info */
    DALSYS_memscpy(&(pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index]), sizeof(pm_pbs_info_smem_type), &(pm_pbs_info_arr[pmic_index]), sizeof(pm_pbs_info_smem_type));
  }

  return PM_ERR_FLAG__SUCCESS;
}

pm_err_flag_type pm_get_pbs_info(uint8 pmic_device_index, pm_pbs_info_type* pbs_info_ptr)
{
   /* Return error if PBS driver is not already initialized or invalid arguments are passed */
  if((NULL == pbs_info_ptr) || (pmic_device_index >= PM_MAX_NUM_PMICS) || (!pm_pbs_info_initialized)) 
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  if (pm_pbs_info_arr[pmic_device_index].format != PM_PBS_INFO_SMEM_FORMAT)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  //get the PBS info from static global variable and return it
  DALSYS_memscpy(pbs_info_ptr->lot_id, sizeof(pbs_info_ptr->lot_id), pm_pbs_info_arr[pmic_device_index].lot_id, sizeof(pbs_info_ptr->lot_id));
  pbs_info_ptr->rom_version = pm_pbs_info_arr[pmic_device_index].rom_version;
  pbs_info_ptr->ram_version = pm_pbs_info_arr[pmic_device_index].ram_version;
  pbs_info_ptr->fab_id = pm_pbs_info_arr[pmic_device_index].fab_id;
  pbs_info_ptr->wafer_id = pm_pbs_info_arr[pmic_device_index].wafer_id;
  pbs_info_ptr->x_coord = pm_pbs_info_arr[pmic_device_index].x_coord;
  pbs_info_ptr->y_coord = pm_pbs_info_arr[pmic_device_index].y_coord;
  pbs_info_ptr->test_pgm_rev = pm_pbs_info_arr[pmic_device_index].test_pgm_rev;

  pbs_info_ptr->mfg_id.major = 0;
  pbs_info_ptr->mfg_id.minor = 0;
  pbs_info_ptr->mfg_id.shrink = 0;

  return PM_ERR_FLAG__SUCCESS;
}

pm_err_flag_type pm_pbs_header_info_init(void)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint32             slave_id = 0;
  uint8              pmic_index = 0;
  uint8              data = 0;


  if(pbs_header_info_init != TRUE)
  { 
    for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
    {
        /* Get PMIC device primary slave id */
        err_flag = pm_get_slave_id(pmic_index, 0, &slave_id);
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
          /* Second or third PMIC doesn't exist */
          err_flag = PM_ERR_FLAG__SUCCESS;
          continue;
        }

        /* Read PBS Peripheral info and check if PBS peripheral exists */
        err_flag = pm_comm_read_byte(slave_id, PMIO_PBS_CORE_PERPH_TYPE_ADDR, &data, 0);
        if ((err_flag != PM_ERR_FLAG__SUCCESS) || (data != PM_HW_MODULE_PBS))
        {
           continue;
        }

        // Enable PBS access
        err_flag = pm_pbs_enable_access(slave_id);
        
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
            return err_flag;
        }
        /* Retrieve Header version and checksum*/
        err_flag = pm_pbs_header_version_info(slave_id, &(pm_pbs_header_info_arr[pmic_index]));

        /*If header version  is 1, then populate the struct with appropriate dataset addresses */
        if(pm_pbs_header_info_arr[pmic_index].header_version == 1)
        {
           err_flag = pm_pbs_header_dataset_info(slave_id, pm_pbs_header_info_arr[pmic_index].dataset_start_address , &(pm_pbs_header_dataset_arr[pmic_index]));
        }

        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
          /* Configuring to disable PBS core read access */
          pm_pbs_disable_access(slave_id);

          return err_flag;
        }
    }
  }
  if(err_flag == PM_ERR_FLAG__SUCCESS)
  {
     pbs_header_info_init = TRUE;
  }

  return err_flag;
}


pm_err_flag_type pm_pbs_header_version_info(uint8 slave_id, pm_pbs_header_info_type *pbs_header_ptr)
{
    pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
    uint32             read_data =0;
    pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
    pm_pbs_info_data_type *pm_pbs_data = NULL;
    uint8 pmic_index = 0;
    
    
    /* Retrieve PBS info config data */
    pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
    if(NULL == pm_pbs_temp_data)
    {
      return PM_ERR_FLAG__INVALID_POINTER;
    }
    pmic_index = (uint8)(slave_id / 2); 
    pm_pbs_data = pm_pbs_temp_data[pmic_index];

    /* Configuring read access in burst mode to PBS RAM */
    err_flag = pm_pbs_config_access(slave_id, pm_pbs_data->pbs_ram_start_addr, PM_PBS_ACCESS_READ_BURST);
    if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag; //Stop on first error
    
    
    /* Configuring to enable PBS core access for ROM reads */
    err_flag = pm_pbs_enable_access(slave_id);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }

    /* Reading the Checksum - 1st Row in PBS header */
    err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_data, 1);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }
    
    pbs_header_ptr->checksum = (uint32)read_data;

    if(pbs_header_ptr->checksum != PM_PBS_HEADER_CHECKSUM)
    {
        return err_flag;
    }


    //Reading 2nd line of PBS header to get the header version and start address
    err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_data, 1);
    
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
    
    pbs_header_ptr->dataset_start_address = (uint32)((read_data >> 24) & 0x000000FF);
    pbs_header_ptr->header_version = (uint32)((read_data >>16) & 0x000000FF);
    pbs_header_ptr->ram_revision_id = (uint32)((read_data >>8) & 0x000000FF); 
    pbs_header_ptr->ram_branch_id = (uint32)(read_data & 0x000000FF);

    /* Configuring to disable PBS core read access */
    err_flag |= pm_pbs_disable_access(slave_id);
    
    return err_flag;
}

pm_err_flag_type pm_pbs_header_dataset_info(uint8 slave_id, uint32 start_address, pm_pbs_header_dataset_type_v1 *pbs_header_dataset_ptr)
{
    pm_err_flag_type   err_flag  = PM_ERR_FLAG__SUCCESS;
    uint32  read_data            = 0;
    uint32  dataset_address[5]; 
    uint8   i                    = 0; 
    
    pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
    pm_pbs_info_data_type *pm_pbs_data = NULL;
    uint8 pmic_index = 0;
    
    
    /* Retrieve PBS info config data */
    pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
    if(NULL == pm_pbs_temp_data)
    {
      return PM_ERR_FLAG__INVALID_POINTER;
    }
    pmic_index = (uint8)(slave_id / 2); 
    pm_pbs_data = pm_pbs_temp_data[pmic_index];
    
    err_flag = pm_pbs_config_access(slave_id, pm_pbs_data->pbs_ram_start_addr + start_address , PM_PBS_ACCESS_READ_BURST);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }
    
    /* Configuring to enable PBS core access for ROM reads */
    err_flag = pm_pbs_enable_access(slave_id);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }

    /* Retrieve all the header information */
    
    for (i =0 ; i <5 ; i++)
    {
       err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_data, 1);
       if (err_flag != PM_ERR_FLAG__SUCCESS)
       {
          return err_flag;
       }
       if((uint32)read_data == 0xFFFFFFFF)
       {
          dataset_address[i] = 0xFFFF;
       }
       else
       {
          dataset_address[i] = ((uint32)read_data & 0x0000FFFF) ;
       }        
    }
    
    pbs_header_dataset_ptr->sleep_dataset_address = dataset_address[0] ;
    pbs_header_dataset_ptr->pon_reason_dataset_address = dataset_address[1];
    pbs_header_dataset_ptr->rtrr_dataset_address = dataset_address[2];
    pbs_header_dataset_ptr->spare_reg_dataset_address= dataset_address[3];
    pbs_header_dataset_ptr->lpg_dataset_address = dataset_address[4];

    /* Configuring to disable PBS core read access */
    err_flag |= pm_pbs_disable_access(slave_id);

    return err_flag;
    
}


pm_err_flag_type pm_pbs_ram_header_get_dataset_data(uint8 slave_id, void **dataset_ptr, pm_pbs_header_dataset_type dataset_type)

{
    pm_err_flag_type err_flag           = PM_ERR_FLAG__SUCCESS;
    uint32           read_data          = 0;
    uint8            read_counter       = 0;
    uint32           start_address      = 0;
    uint8            dataset_size       = 0;

    pm_pbs_lpg_dataset_type *lpg_ptr = NULL;
    pm_pbs_spare_reg_dataset_type *spare_reg_ptr = NULL;
    pm_pbs_pon_reason_dataset_type *pon_reason_ptr = NULL;
    pm_pbs_sleep_dataset_type *sleep_ptr = NULL;

    uint8 pmic_index = (uint8)(slave_id / 2); 

    if(pbs_header_info_init != TRUE)
    {
      err_flag = pm_pbs_header_info_init();
    }
    switch(dataset_type)
    {
      case PM_PBS_HEADER_LPG_DATASET:
           start_address = pm_pbs_header_dataset_arr[pmic_index].lpg_dataset_address;
           dataset_size  = PM_PBS_LPG_DATASET_SIZE;
           pm_malloc(sizeof(pm_pbs_lpg_dataset_type), (void**)&lpg_ptr);
           *dataset_ptr = lpg_ptr;
           break;
           
      case PM_PBS_HEADER_SPARE_REG_DATASET:
           start_address = pm_pbs_header_dataset_arr[pmic_index].spare_reg_dataset_address;         
           dataset_size  = PM_PBS_SPARE_REG_DATASET_SIZE;
           pm_malloc(sizeof(pm_pbs_spare_reg_dataset_type), (void**)&spare_reg_ptr);
           *dataset_ptr = spare_reg_ptr;
           break;
           
      case PM_PBS_HEADER_PON_REASON:
           start_address = pm_pbs_header_dataset_arr[pmic_index].pon_reason_dataset_address;
           dataset_size  = PM_PBS_PON_DATASET_SIZE;
           pm_malloc(sizeof(pm_pbs_pon_reason_dataset_type), (void**)&pon_reason_ptr);
           *dataset_ptr = pon_reason_ptr;
           break;
           
      case PM_PBS_HEADER_SLEEP_DATASET:
           start_address = pm_pbs_header_dataset_arr[pmic_index].sleep_dataset_address;
           dataset_size  = PM_PBS_SLEEP_DATASET_SIZE;
           pm_malloc(sizeof(pm_pbs_sleep_dataset_type), (void**)&sleep_ptr);
           *dataset_ptr = sleep_ptr;
           break;
           
      default:
           return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    } 


    //Return if  start address of dataset is not configured 
    if(start_address == 0xFFFF)
    {
        dataset_ptr = 0;
        return err_flag;    
    }

        
    err_flag = pm_pbs_config_access(slave_id, start_address , PM_PBS_ACCESS_READ_BURST);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }
    
    /* Configuring to enable PBS core access for ROM reads */
    err_flag = pm_pbs_enable_access(slave_id);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }

    /* Retrieve all the pon data information */
    for (read_counter = 0; read_counter < dataset_size; read_counter++)
    {
        err_flag = pm_comm_read_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_RD_DATA0_ADDR, 4, (uint8*)&read_data, 1);
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
          return err_flag;
        }

        switch(dataset_type)
        {
          case PM_PBS_HEADER_LPG_DATASET:
               lpg_ptr->pm_pbs_lpg_data[read_counter] = (uint32)read_data;
               break;
               
          case PM_PBS_HEADER_SPARE_REG_DATASET:
               spare_reg_ptr->pm_pbs_spare_reg_data[read_counter] = (uint32)read_data;
               break;
               
          case PM_PBS_HEADER_PON_REASON:
               pon_reason_ptr->pm_pbs_pon_reason_data[read_counter] = (uint32)read_data;
               break;
               
          case PM_PBS_HEADER_SLEEP_DATASET:
               sleep_ptr->pm_pbs_sleep_data[read_counter] = (uint32)read_data;
               break;
          case PM_PBS_HEADER_RTRR_DATASET:
          case PM_PBS_HEADER_INVALID:
               break;
         }
    }

    /* Configuring to disable PBS core read access */
    err_flag |= pm_pbs_disable_access(slave_id);

    return err_flag;
    
}



pm_err_flag_type pm_pbs_ram_header_config_dataset_data(uint8 slave_id,uint32* data, pm_pbs_header_dataset_type dataset_type)

{
    pm_err_flag_type err_flag           = PM_ERR_FLAG__SUCCESS;
    uint8            write_counter      = 0;
    uint32           start_address      = 0;
    uint8            size               = 0;
    uint8 pmic_index = (uint8)(slave_id / 2); 
    
    if(pbs_header_info_init != TRUE)
    {
      err_flag = pm_pbs_header_info_init();
    }

    switch(dataset_type)
    {
      case PM_PBS_HEADER_LPG_DATASET:
           start_address = pm_pbs_header_dataset_arr[pmic_index].lpg_dataset_address;
           size          = PM_PBS_LPG_DATASET_SIZE;
           break;
           
      case PM_PBS_HEADER_SPARE_REG_DATASET:
           start_address = pm_pbs_header_dataset_arr[pmic_index].spare_reg_dataset_address;         
           size          = PM_PBS_SPARE_REG_DATASET_SIZE;
           break;
      default:
           return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
    }

    
        
    err_flag = pm_pbs_config_access(slave_id, start_address , PM_PBS_ACCESS_WRITE_BURST);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }
    
    // Configuring to enable PBS core access for ROM reads 
    err_flag = pm_pbs_enable_access(slave_id);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
        return err_flag;
    }

    // Retrieve all the pon data information 
    for (write_counter = 0; write_counter < size; write_counter++)
    {
        err_flag = pm_comm_write_byte_array(slave_id, PMIO_PBS_CORE_MEM_INTF_WR_DATA0_ADDR, 4, (uint8*)&data[write_counter], 1);
        if (err_flag != PM_ERR_FLAG__SUCCESS)
        {
          return err_flag;
        }
    }

    // Configuring to disable PBS core read access 
    err_flag |= pm_pbs_disable_access(slave_id);

    return err_flag;
    
}

pm_err_flag_type 
pm_get_pon_reason_history(void)
{

   pm_err_flag_type err_flag                    = PM_ERR_FLAG__SUCCESS;
   pm_pbs_pon_reason_dataset_type *pon_data_ptr = NULL;
   boolean valid_sid                            = FALSE;
   uint32 slave_id                              = 0; 
   uint8 pmic_index                             = 0; 
   uint8 pon_data_count                         = 0;
   uint8 pon_rsn_dump_count                     = 0;
   uint32 rev_id_read;

   
   pon_reason_history[0].signature = PON_RSN_HIST_SIGNATURE; //PR
   pon_reason_history[0].version   = 0x01;

   for (pmic_index =0 ; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
    {

		pm_get_slave_id(pmic_index, 0, &slave_id);
		pm_resolve_chip_revision(slave_id, &valid_sid, &rev_id_read);
        if (valid_sid == FALSE)
        {
		   // Updating the array pointer to leave space for the slave id without PMIC
		   pon_rsn_dump_count = pon_rsn_dump_count + NO_OF_PON_RSN_PER_PMIC;
           continue;  //PMIC does not exist
        }
        err_flag = pm_pbs_ram_header_get_dataset_data(slave_id, (void **)&pon_data_ptr, PM_PBS_HEADER_PON_REASON);

        CORE_VERIFY_PTR(pon_data_ptr);

        for(pon_data_count =0; pon_data_count < NO_OF_PON_RSN_PER_PMIC; pon_data_count++  )
        {
           pon_reason_history[0].pbs_pon_rsn_hist_data[pon_rsn_dump_count] = (uint32)(pon_data_ptr->pm_pbs_pon_reason_data[pon_data_count]);
           pon_rsn_dump_count++;
        }
    }
   
   return err_flag;

}


pm_err_flag_type 
pm_get_pon_reason_history_to_dump(pm_pbs_pon_reason_history_data_type *pon_reason_history_ptr )
{
  
    pm_err_flag_type  err_flag = PM_ERR_FLAG__SUCCESS;
  
    //Copy the data from Local variable to the memory dump location
    DALSYS_memscpy(pon_reason_history_ptr, sizeof(pm_pbs_pon_reason_history_data_type), &pon_reason_history, sizeof(pm_pbs_pon_reason_history_data_type));

    return err_flag;
  
}


