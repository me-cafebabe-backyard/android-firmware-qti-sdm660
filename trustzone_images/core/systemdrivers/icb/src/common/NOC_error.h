#ifndef __NOC_ERROR_H__
#define __NOC_ERROR_H__
/*============================================================================

FILE:      NOC_Error.h

DESCRIPTION: APIs and data structure declarations 
             for NOC Error Handler

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/icb/src/common/NOC_error.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $
$Change: 22186835 $ 

When        Who    What, where, why
----------  ---    ----------------------------------------------------------- 
2015/11/23  pm     Added Sideband Manager support
2014/12/09  tb     Split OEM modifiable data from internal data
2013/05/10  pm     Added NOC_ERRLOG6 macro to support FlexNoc 2.8
2012/10/03  av     Created

                Copyright (c) 2014 - 2016 Qualcomm Technologies Incorporated.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
============================================================================*/
#include "com_dtypes.h"
#include "stdint.h"


/*============================================================================
                          DEFINEs/MACROs
============================================================================*/

#define BIT_FLAG(x) ((uint32)(1 << x))

/** ERRLOG flags for log filter */
#define NOC_ERRLOG0   BIT_FLAG(0)
#define NOC_ERRLOG1   BIT_FLAG(1)
#define NOC_ERRLOG2   BIT_FLAG(2)
#define NOC_ERRLOG3   BIT_FLAG(3)
#define NOC_ERRLOG4   BIT_FLAG(4)
#define NOC_ERRLOG5   BIT_FLAG(5)
#define NOC_ERRLOG6   BIT_FLAG(6)

/* Macro for internal Slave info initialization */
#define NOCERR_INFO(name, intr_vector, log_filter, sb_base_addr)  \
                      {                                      \
                        #name,                               \
                        (void*)NOCERR_##name##_BASE_ADDR,    \
                        intr_vector,                         \
                        log_filter,                          \
                        (void*)sb_base_addr,                 \
                      }
/* Macro for OEM Slave info initialization */
#define NOCERR_INFO_OEM(name, intr_en, error_fatal, sb_en_mask)  \
                      {                                      \
                        #name,                               \
                        intr_en,                             \
                        error_fatal,                         \
                        sb_en_mask,                          \
                      }

/*============================================================================
                          TYPE DEFINITION
============================================================================*/
/**
 * Internal NOC error Info data type
 */
typedef struct
{
    char* name;               /**< NOC name */
    void* base_addr;          /**< NOC base address */
    uintptr_t intr_vector;    /**< NOC interrupt vector */
    uint32 errlog_filter;     /**< NOC ErrLog <n>-bitfield to filter ERRLog<n> */    
    void* sb_base_addr;       /**< NOC sideband base address */
}NOCERR_info_type;

/**
 * OEM NOC error Info data type
 */
typedef struct
{
    char* name;               /**< NOC name */
    uint8 intr_enable;        /**< NOC errorlogger interrupt enable */
    uint8 error_fatal;        /**< NOC interrupt error fatal */ 
    uint32 sb_enable_mask;    /**< NOC interrupt enable mask */
}NOCERR_info_type_oem;

/**
 * NOC Error Internal Property Data type
 */
typedef struct
{
    uint8 len;                        /**< Length of cfgdata array */
    const NOCERR_info_type* NOCInfo;        /**< Pointer to internal cfgdata array*/
    const char *const *BIMC_reg_names;
    const uint64 *BIMC_reg_addr;
    uint8 BIMC_num_reg;
    const uint64 *clock_reg_addr;
    uint8 clock_num_reg;
}NOCERR_propdata_type;

/**
 * NOC Error OEM Property Data type
 */
typedef struct
{
    uint8 len;                        /**< Length of cfgdata array */
    const NOCERR_info_type_oem* NOCInfoOEM; /**< Pointer to OEM cfgdata array*/
}NOCERR_propdata_type_oem;

/**
 * NOC Error Syndrome Register Data Type
 */
typedef struct
{
    char* name;                     /**< NOC name */
    uint32 ERRLOG0;
    uint32 ERRLOG1;
    uint32 ERRLOG2;
    uint32 ERRLOG3;
    uint32 ERRLOG4;
    uint32 ERRLOG5;
    uint32 ERRLOG6;
    uint32 FLAGINSTATUS0;
    uint32 SENSEIN0;
}NOCERR_syndrome_type;

/*============================================================================
                                 FUNCTIONS
============================================================================*/

//*============================================================================*/
/**
@brief 
      Performs initialization for NOC error handler.
      It enables interrupts required to handle NOC errors.
 
@param[in]  None.

@return    
      None.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
void NOC_Error_Init(void);

#endif /* __NOC_ERROR_H__ */
