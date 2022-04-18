#ifndef __PM_PBS_INFO_H__
#define __PM_PBS_INFO_H__

/*! \file  pm_pbs_info.h
 *  
 *  \brief  This file contains the pmic PBS info driver definitions.
 *  \details  This file contains the pm_pbs_info_init & pm_pbs_info_store_glb_ctxt
 *  API definitions.
 *  
 *  &copy; Copyright 2013 - 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
08/12/2016   akm     Added pm_pbs_header_info API
12/04/2015   aab     Updated pm_pbs_info_data_type 
04/29/2015   aab     Added support for PMK8001 
04/05/2013   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_target_information.h"
#include "pm_device.h"

/*===========================================================================

                    MACRO AND GLOBAL VARIABLES

===========================================================================*/
/* PBS ROM/RAM Size can be 128 or 256 words. */
/* PBS OTP/ROM Start Address */
#define PM_PBS_ROM_BASE_ADDR            0x000
/* PBS RAM Start Address */
#define PM_PBS_RAM_BASE_ADDR            0x400

/* PBS Memory Version stored at the last line */
#define PM_PBS_MEMORY_VER_LINE_FROM_END   1
/* MFG Info stored at the 7th from last line (if present in PBS ROM) */
#define PM_PBS_ROM_INFO_LINE_FROM_END     7

#define PM_PBS_PON_DATASET_SIZE           6
#define PM_PBS_SPARE_REG_DATASET_SIZE     1
#define PM_PBS_LPG_DATASET_SIZE           12
#define PM_PBS_SLEEP_DATASET_SIZE         5


#define PM_PBS_HEADER_CHECKSUM          0x50425352

typedef enum
{
    PM_PBS_INFO_IN_OTP,
    PM_PBS_INFO_IN_MISC,
    PM_PBS_INFO_INVALID
} pm_pbs_info_place_holder_type;

typedef enum
{
    PM_PBS_HEADER_SLEEP_DATASET,
    PM_PBS_HEADER_PON_REASON,
    PM_PBS_HEADER_RTRR_DATASET,
    PM_PBS_HEADER_LPG_DATASET,
    PM_PBS_HEADER_SPARE_REG_DATASET,
    PM_PBS_HEADER_INVALID
} pm_pbs_header_dataset_type;

typedef struct
{
    uint32 checksum;              /* Stores a CRC/signature to check if the PBS RAM is already loaded */
	uint8  dataset_start_address; /* Beginning of all the datasets in PBS RAM */
	uint8  header_version;        /* PBS RAM header version*/
	uint8  ram_revision_id;       /* PBS RAM Version ID */
    uint8  ram_branch_id;         /* PBS RAM Branch ID */
	
} pm_pbs_header_info_type;


typedef struct
{
	uint32 sleep_dataset_address;      /* Start address of the sleep dataset */
	uint32 pon_reason_dataset_address; /* Start address of the PON dataset */
	uint32 rtrr_dataset_address;       /* Start address of the RTRR dataset */
	uint32 spare_reg_dataset_address;  /* Start address of the HLOS/Spare Reg dataset */
	uint32 lpg_dataset_address;        /* Start address of the LPG dataset */
	
} pm_pbs_header_dataset_type_v1;


typedef struct
{
	uint32 pm_pbs_pon_reason_data[PM_PBS_PON_DATASET_SIZE]; /*  PON dataset */
	
} pm_pbs_pon_reason_dataset_type;

typedef struct
{
	uint32 pm_pbs_spare_reg_data[PM_PBS_SPARE_REG_DATASET_SIZE];  /* HLOS/Spare Reg dataset */
	
} pm_pbs_spare_reg_dataset_type;


typedef struct
{
	uint32 pm_pbs_lpg_data[PM_PBS_LPG_DATASET_SIZE]; /* LPG dataset */
	
} pm_pbs_lpg_dataset_type;

typedef struct
{
	uint32 pm_pbs_sleep_data[PM_PBS_SLEEP_DATASET_SIZE]; /* Sleep dataset */
	
} pm_pbs_sleep_dataset_type;




typedef struct
{
    uint16 pbs_otp_start_addr;
    uint16 pbs_otp_mem_size;
    uint16 pbs_ram_start_addr;
    uint16 pbs_ram_mem_size;
    pm_pbs_info_place_holder_type pbs_info_place_holder;
} pm_pbs_info_data_type;

/* global variables to store the pbs header info */
extern pm_pbs_header_info_type pm_pbs_header_info_arr[PM_MAX_NUM_PMICS];
extern pm_pbs_header_dataset_type_v1 pm_pbs_header_dataset_arr[PM_MAX_NUM_PMICS] ;
extern boolean pbs_header_info_init;


/*===========================================================================

      Function Definitions

============================================================================*/
/** 
 * @name pm_pbs_info_rom_init 
 *  
 * @brief This function is called to initialize the PBS Info driver.
 *        This function internally validates the PBS Core peripheral
 *        info to determine the valid PMIC Chips and calls an internal
 *        helper function to read PBS Manufacturing IDs and foundry
 *        information such as PBS Lot ID, ROM Version,
 *        Fab Id, Wafer Id, X coord and Y coord and stores it in static
 *        global variable. This function is called during pm_device_init
 *        after the PBS RAM data is loaded.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.           
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors 
 */
pm_err_flag_type pm_pbs_info_rom_init (void);


/** 
 * @name pm_pbs_info_ram_init 
 *  
 * @brief This function is called to initialize the PBS Info driver.
 *        This function internally validates the PBS Core peripheral
 *        info to determine the valid PMIC Chips and calls an internal
 *        helper function to read PBS Manufacturing IDs and foundry
 *        information such as  RAM Version and stores it in static
 *        global variable. This function is called during pm_device_init
 *        after the PBS RAM data is loaded.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.           
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors 
 */
pm_err_flag_type pm_pbs_info_ram_init (void);


/** 
 * @name pm_pbs_info_store_glb_ctxt 
 *  
 * @brief This function is called to copy the PBS info to Global
 *        Context (SMEM) from static global variables where the
 *        PBS info is stored during PBS Info initilization.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS. 
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Error in
 *          copying to shared memory. 
 */
pm_err_flag_type pm_pbs_info_store_glb_ctxt (void);

/**
 * @name pm_pbs_header_info_init
 *
 * @brief 
 *        This function internally validates the PBS Core peripheral
 *        info to determine the valid PMIC Chips and calls an internal
 *        helper function to read PBS RAM header details and stores it in static
 *        global variable. This function is called during pm_device_init
 *        after the PBS RAM data is loaded.
 *
 * @param None.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_header_info_init(void);

/**
 * @name pm_pbs_header_version_info
 *
 * @brief 
 *        This function is used to abstract the checksum, header version, PBS RAM version,
 *        start address of all dataset / End of executable code from PBS RAM and stores it in static
 *        global variable. This function is called during pm_pbs_header_info_init
 *        after the PBS RAM data is loaded.
 *
 * @param slave id of the PMICs data being retrieved 
 * @param pm_pbs_header_info_type ptr to store the header version info of specific PMIC.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_header_version_info(uint8 slave_id, pm_pbs_header_info_type *pbs_header_ptr);

/**
 * @name pm_pbs_header_dataset_info
 *
 * @brief 
 *        This function is used to abstract SLEEP,PON reasons, RTRR, HLOS(spare reg),LPG dataset start address 
 *        from PBS RAM and stores it in static global variable. This function is called during pm_pbs_header_info_init
 *        after the PBS RAM data is loaded.
 *
 * @param slave_id - slave id of the PMICs data being retrieved 
 * @param start_address - address in the PBS RAM where the beginning of dataset are being stored/ executable code ends 
 * @param pbs_header_dataset_ptr - ptr to store header dataset information of the specific PMIC 
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_header_dataset_info(uint8 slave_id, uint32 start_address, pm_pbs_header_dataset_type_v1 *pbs_header_dataset_ptr);


/**
 * @name pm_pbs_get_header_dataset_data
 *
 * @brief 
 *        This function is used to abstract PON,LPG,SLEEP, SPARE_REG  dataset DATA from PBS RAM 
 *
 * @param slave_id        - slave id of the PMICs data being retrieved 
 * @param dataset_ptr   - ptr to get dataset information of the specific PMIC 
 * @param dataset_type - 
 *                                  PM_PBS_PON_REASONS_DATASET_TYPE
 *                                  PM_PBS_LPG_DATASET_TYPE
 *                                  PM_PBS_SPARE_REG_DATASET_TYPE
 *                                  PM_PBS_SLEEP_DATASET_TYPE
  * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_ram_header_get_dataset_data(uint8 slave_id, void **dataset_ptr, pm_pbs_header_dataset_type dataset_type);


/**
 * @name pm_pbs_ram_header_config_dataset_data
 *
 * @brief 
 *        This function is used to write  LPG,SPARE_REG dataset DATA to PBS RAM 
 *
 * @param slave_id        - slave id of the PMICs data being retrieved 
 * @param dataset_ptr   - ptr to get dataset information of the specific PMIC 
 * @param dataset_type - 
 *                                  PM_PBS_LPG_DATASET_TYPE
 *                                  PM_PBS_SPARE_REG_DATASET_TYPE
  * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors
 */

pm_err_flag_type pm_pbs_ram_header_config_dataset_data(uint8 slave_id,uint32 data[], pm_pbs_header_dataset_type dataset_type);


#endif /* __PM_PBS_INFO_H__ */