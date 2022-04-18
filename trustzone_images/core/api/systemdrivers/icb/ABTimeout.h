#ifndef __ABTIMEOUT_H__
#define __ABTIMEOUT_H__
/*============================================================================

FILE:      ABTtimeout.h

DESCRIPTION: Function and data structure declarations for AHB timeout driver Interface

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.7.1/api/systemdrivers/icb/ABTimeout.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $
$Change: 22186835 $ 

When        Who    What, where, why
----------  ---    ----------------------------------------------------------- 
2017/02/14  sds    Add OEM control of NoC timeout
2014/12/09  tb     Split OEM modifiable data from internal data
2013/11/14  tb     Added support for multiple enable/status registers
2013/04/16  pm     Added interrupt priority
2012/10/04  av     Support for disabling ABT
2012/05/31  av     Created

                Copyright (c) 2012 - 2014, 2017 Qualcomm Technologies Incorporated.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
============================================================================*/
#include "com_dtypes.h"

/*============================================================================
                          DEFINEs/MACROs
============================================================================*/

/* Flag for no local global enable register */
#define ABT_NO_LCL_GLB_EN 0x7FFFFFFF

/* Flag for no interrupt to register for */
#define ABT_NO_INTERRUPT 0x5FFFFFFF

/* Macro for internal Slave info initialization */
#define ABT_SLAVE_INFO(name, local, shared) \
                      {                                      \
                        #name,                               \
                        ABT_##name##_BMSK,                   \
                        (void*)ABT_##name##_BASE_ADDR,       \
                        ABT_##name##_CLK,                    \
                        local,                               \
                        shared,                              \
                      }

/* Macro for OEM Slave info initialization */
#define ABT_SLAVE_INFO_OEM(name, slave_en, intr_en, timeout_val) \
                      {                                          \
                        #name,                                   \
                        slave_en,                                \
                        intr_en,                                 \
                        timeout_val,                             \
                      }

/*============================================================================
                          TYPE DEFINITION
============================================================================*/

/**
 * Internal ABT configuration Data type
 */
typedef struct
{
    char* name;                     /**< ABT Slave name */
    uint8 slave_id;                 /**< ABT Slave internal id */
    void* base_addr;                /**< ABT Slave base address */
    char* clk_name;                 /**< ABT Slave clk name */
    uint8 local;                    /**< Slave local to this processor */
    uint8 shared;                   /**< Slave shared with another processor */
}ABT_slave_info_type;

/**
 * OEM ABT configuration Data type
 */
typedef struct
{
    char* name;                     /**< ABT Slave name */
    uint8 slave_enable;             /**< Slave enable */
    uint8 intr_enable;              /**< Slave Interrupt enable */
    uint8 timeout_val;              /**< Slave timeout value */
}ABT_slave_info_type_oem;

/**
 * ABT Platform Data type
 */
typedef struct
{
    char*  name;                    /**< Platform name */
    const void *const *intr_map_addr;           /**< ABT Interrupt map reg address */
    const void *const *intr_status_addr;        /**< ABT Interrupt pending status 
                                         regisger address*/
    void*  globa_en_addr;           /**< ABT Slave Global EN reg address */
    uint32 intr_vector;             /**< Summary Interrupt vector */
    uint32 intr_priority;           /**< Interrupt priority */
    uint32 num_status_reg;          /**< Number of ABT Interrupt enable/status registers */
    void*  local_global_en_addr;    /**< ABT Slave Local Global EN reg address */
    uint32 local_global_mask;       /**< ABT Slave Local Global EN bit mask */
}ABT_platform_info_type;


/**
 * ABT Device Property Data type
 */
typedef struct
{
    uint8 len;                             /**< Length of property data array */
    const ABT_slave_info_type* slave_info;       /**< Pointer to cfgdata array*/
    const ABT_platform_info_type *platform_info; /**< Pointer to platform info */
}ABT_propdata_type;

/**
 * ABT Device Property Data type
 */
typedef struct
{
    uint8 len;                                      /**< Length of property data array */
    const ABT_slave_info_type_oem* slave_info_oem;  /**< Pointer to cfgdata array*/
    uint8 local_global_enable;                      /**< Local global enable */
}ABT_propdata_type_oem;

/**
 * ICBCFG Error types.
 */ 
typedef enum
{
  ABT_SUCCESS = 0,      				/**< Success */
  ABT_ERROR_INVALID_PARAM,              /**< Invalid Parameters */
  ABT_ERROR_INIT_FAILURE,               /**< Initialization Failure */
  /* Add new errors here */         

  ABT_ERROR_SIZE = 0x7FFFFFFF,          /* force 32-bit enum */
  ABT_ERROR = -1
}ABT_error_type;

/*============================================================================
                                 FUNCTIONS
============================================================================*/

//*============================================================================*/
/**
@brief 
      Initializes AHB Timeout driver. It configures interrupt and timeout values
      for AHB timeout slaves
 
@param[in]  None.

@return    
      None.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
void ABT_Init(void);


#endif /* __ABTIMEOUT_H__ */
