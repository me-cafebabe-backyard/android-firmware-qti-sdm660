#ifndef _PM_VERSION__H
#define _PM_VERSION__H
/*! \file 
 *  \n
 *  \brief  pm_version.h ---- PMIC Version 
 *  \n
 *  \n This header file contains enums and API definitions for PMIC version 
 *      detection
 *  \n
 *  \n &copy; Copyright 2013 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.qdsp6/1.0.c2/api/systemdrivers/pmic/pm_version.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/27/13   kt      Adding pm_get_pmic_info API to get the pmic device info.  
03/27/13   kt      Removing pm_set_hardware_version and pm_get_hardware_version APIs. 
03/27/13   kt      Remove comdef.h and use com_dtypes.h
03/10/12   wra     Removed old PMIC versions and added Badger PMIC versions. 
                    Reduced hardware versions in enumeration
10/18/11   jtn/mpt Add PM8821 and PM8038
04/04/11   hw      Added pm_get_hardware_version and pm_set_hardware_version API
02/08/11   hw      Merging changes from the PMIC Distributed Driver Arch branch
07/05/10   wra     Added pm_model_type entry for the PM8921 and PM8018
07/05/10   wra     Added file header and pm_model_type entry for the PM8901 
                   and ISL9519
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_lib_err.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/** 
  @enum pm_model_type
  @brief This enum gives the PMIC model type values (Peripheral
  Subtype values) for different PMIC Models. 
 */

typedef enum
{
   PMIC_IS_UNKNOWN   = 0,  /**< PMIC model is unknown. */
   PMIC_IS_PM8941    = 1,  /**< PMIC model is PM8941. */
   PMIC_IS_PM8841    = 2,  /**< PMIC model is PM8841. */
   PMIC_IS_PM8019    = 3,  /**< PMIC model is PM8019. */
   PMIC_IS_PM8026    = 4,  /**< PMIC model is PM8026. */
   PMIC_IS_PM8110    = 5,  /**< PMIC model is PM8110. */
   PMIC_IS_PMA8084   = 6,  /**< PMIC model is PMA8084. */
   PMIC_IS_PMI8962   = 7,  /**< PMIC model is PMI8962. */
   PMIC_IS_PMD9635   = 8,  /**< PMIC model is PMD9635. */
   PMIC_IS_PMD9645   = 8,  /**< PMIC model is PMD9645. */
   PMIC_IS_PM8994    = 9,  /**< PMIC model is PM8994. */
   PMIC_IS_PMI8994   = 10, /**< PMIC model is PMI8994. */
   PMIC_IS_PM8916    = 11, /**< PMIC model is PM8916. */
   PMIC_IS_PM8004    = 12, /**< PMIC model is PM8004. */
   PMIC_IS_PM8909    = 13, /**< PMIC model is PM8909. */
   PMIC_IS_PMD9655   = 15, /**< PMIC model is PMD9655. */
   PMIC_IS_PM8950    = 16, /**< PMIC model is PM8950. */
   PMIC_IS_PMI8950   = 17, /**< PMIC model is PMI8950. */
   PMIC_IS_PMK8001   = 18, /**< PMIC model is PMK8001. */
   PMIC_IS_PMI8996   = 19, /**< PMIC model is PMI8996. */
   PMIC_IS_PM8998    = 20, /**< PMIC model is PM8998. */
   PMIC_IS_PMI8998   = 21, /**< PMIC model is PMI8998. */
   PMIC_IS_PM8005    = 24, /**< PMIC model is PM8005. */
   PMIC_IS_PM8937    = 25, /**< PMIC model is PM8005. */
   PMIC_IS_PM660L    = 26, /**< PMIC model is PM660L. */
   PMIC_IS_PM660     = 27, /**< PMIC model is PM660. */
   PMIC_IS_INVALID   = 0x7FFFFFFF,
} pm_model_type;

/** 
  @struct pm_device_info_type
  @brief Stores the PMIC's Model type value, the All Layer
  Revision number and the Metal Revision number. Please refer
  to pm_model_type enum above to get more info on which PMIC
  model type value represents which PMIC.For example, for
  PM8019 v2.1 the PMIC model type value is 3 (since PM8019
  model type value is 3 as per pm_model_type enum), All layer
  revision number is '2' and Metal revision number is '1'.
 */
typedef struct
{
  pm_model_type  ePmicModel;             /**< PMIC device model type */
  uint32         nPmicAllLayerRevision;  /**< PMIC device all layer revision number */
  uint32         nPmicMetalRevision;     /**< PMIC device metal revision number */
} pm_device_info_type;

/*===========================================================================

                        API PROTOTYPE

===========================================================================*/

/** 
 * @name pm_get_pmic_model 
 *  
 * @brief This function returns the PMIC's model type value.
 *        For example, the API returns '1' for PM8941, '2'
 *        for PM8841 and so on. Please refer to pm_model_type
 *        enum above to get more info on which PMIC model type
 *        value represents which PMIC.
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1 
 *
 * @return  pm_model_type 
 *          Returns valid PMIC model/tier type if successful
 *          Returns PMIC_IS_INVALID under error conditions (like
 *          invalid device index param).
 *
 */
pm_model_type pm_get_pmic_model(uint8 pmic_device_index);

/** 
 * @name pm_get_pmic_revision 
 *  
 * @brief This function returns the PMIC's All Layer revision
 *        number. For example, the API returs '1' for PMIC v1.x,
 *        '2' for PMIC v2.x  and so on.
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1 
 *
 * @return  uint8 
 *          Returns valid PMIC All Layer revision number if
 *          successful.
 *          Returns 0 under error conditions (like invalid
 *          device index param).
 *
 */
uint8 pm_get_pmic_revision(uint8 pmic_device_index);

/** 
 * @name pm_get_pmic_info 
 *  
 * @brief This function returns information about PMIC device 
 *        for a specific device index in the pmic_device_info
 *        argument. This API returns PMIC's model type value,
 *        All layer revision number and Metal revision number in
 *        pmic_device_info structure. Please refer to
 *        pm_device_info_type structure above for more info. For
 *        example, for PM8019 v2.1 the PMIC model type value is
 *        3 (since PM8019 model type value is 3 as per
 *        pm_model_type enum), All layer revision number is '2'
 *        and Metal revision number is '1'.
 * 
 * @param[in]  pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[out] pmic_device_info:  
 *                Variable to return to the caller with PMIC
 *                device info. Please refer to
 *                pm_device_info_type structure above for more
 *                info on this structure.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG__INVALID_POINTER = Null pointer passed
 *          in.
 *          PM_ERR_FLAG__PAR1_OUT_OF_RANGE = Device Index out of
 *          range.
 *          PM_ERR_FLAG__INVALID = Error in collecting and
 *          placing PMIC info.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *
 */
pm_err_flag_type pm_get_pmic_info(uint8 pmic_device_index, pm_device_info_type* pmic_device_info);

#endif // PM_VERSION__H
