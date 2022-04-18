#ifndef __ICBCFG_H__
#define __ICBCFG_H__
/*============================================================================

FILE:      icbcfg.h

DESCRIPTION: Function and data structure declarations for ICB CFG driver Interface

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Include/api/buses/icbcfg.h#2 $
$DateTime: 2016/08/19 05:58:45 $
$Author: c_mvanim $
$Change: 11185940 $ 

When        Who    What, where, why
----------  ---    ----------------------------------------------------------- 
2015/07/20  sds    Add ICB_Config_PostInit().
2015/06/23  sds    Add support for multiple remaps.
2014/11/05  sds    Add ICB_Unmap_L2_TCM() API.
2014/06/03  sds    Update max number of segments
2013/10/10  sds    BIMC remap support now checks for hardware support explicitly
2013/07/23  sds    Added BIMC remap support
2012/03/27  av     Added HWIO macro support 
2012/02/07  av     Created

         Copyright (c) 2012-2015 QUALCOMM Technologies Incorporated.
                          All Rights Reserved.
                       QUALCOMM Proprietary/GTDR
============================================================================*/

#include "HALhwio.h"
#include "ddr_common.h"
#include <stdbool.h>

/*============================================================================
                          DEFINEs/MACROs
============================================================================*/

/*============================================================================
                          TYPE DEFINITION
============================================================================*/
/**
 * ICBCFG Error types.
 */ 
typedef enum
{
  ICBCFG_SUCCESS             = 0,          /**< Success */
  ICBCFG_ERROR_INVALID_PARAM,              /**< Invalid Parameters */
  ICBCFG_ERROR_INIT_FAILURE,               /**< Initialization Failure */
  ICBCFG_ERROR_EXHAUSTED_SEGMENTS,         /**< Out of slave segments. */
  ICBCFG_ERROR_UNSUPPORTED,                /**< This operation unsupported on this target. */
  /* Add new errors here */         

  ICBCFG_ERROR_SIZE = 0x7FFFFFFF, /* force 32-bit enum */
  ICBCFG_ERROR = -1
}icbcfg_error_type;

/**
 * ICBCFG remap types
*/
typedef enum
{
  ICBCFG_REMAP_INTERLEAVE_DEFAULT = 0,  /**< Remap all memory in the region. */
  ICBCFG_REMAP_INTERLEAVE_ODD,          /**< Remap ODD 1k pages in the region. */
  ICBCFG_REMAP_INTERLEAVE_EVEN,         /**< Remap EVEN 1k pages in the region. */
  ICBCFG_REMAP_INTERLEAVE_COUNT
} icbcfg_interleave_type;

typedef struct
{
  uint64                 src_addr;     /**< The source address of the region to remap (address at the memory controller) */
  uint64                 size;         /**< The size of the region to remap */
  uint64                 dest_addr;    /**< The destination address of the region to remap (desired address in system memory map) */
  icbcfg_interleave_type interleaved;  /**< Type of interleaving on the memory region */
  bool                   deinterleave; /**< Deinterleave as well as remap? */
} icbcfg_remap_info_type;

/**
 * ICBCFG memory region types
*/
typedef struct
{
  uint64 base_addr;
  uint64 size;
  bool   interleaved;
} region_type;

/* DDR channel definitions */
#define MAX_REGIONS 5
typedef struct
{
  region_type regions[MAX_REGIONS];
} regions_type;

/* DDR slave region configuration */
#define MAX_CHANNELS 2
typedef struct
{
  regions_type channels[MAX_CHANNELS];
} icb_mem_map_type;

/*============================================================================
                                 FUNCTIONS
============================================================================*/

//*============================================================================*/
/**
@brief 
      Initializes ICB config driver. It reads ICB configuration data (register 
      address and config data) from DAL Device Property file and configures 
      ICB registers.
 
@param[in]  dev  DAL string device ID.

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Config_Init( const char * dev );

//*============================================================================*/
/**
@brief 
      ICB configuration data for after everything else is done (segment/remap).
      It reads ICB configuration data (register address and config data) from
      DAL Device Property file and configures ICB registers.
 
@param[in]  dev  DAL string device ID.

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Config_PostInit( const char * dev );

//*============================================================================*/
/**
@brief 
      Configures DDR slave segments in BIMC. It reads ICB configuration data (number
      of channels, maximum memory map, etc) from DAL Device Property file and configures 
      ICB registers.
 
@param[in]  dev   DAL string device ID.
@param[in]  info  DDR channel region configuration

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      Should only be called after any and all calls to ICB_Remap/RemapEx() are complete.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Segments_Init( const char * dev, ddr_info * info );

//*============================================================================*/
/**
@brief 
      Configures the remap segments in BIMC. 

@param[in] dev   DAL string device ID.
@param[in] info  The information about the DDR configuration
@param[in] index The logical remap slot to use
@param[in] remap The information about the region to remap
                 Allowed to be NULL to clear an index

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_RemapEx( const char * dev, ddr_info * info, uint32 index, icbcfg_remap_info_type * remap );

//*============================================================================*/
/**
@brief 
      Returns the current memory map.

@param[in]    dev  DAL string device ID.
@param[inout] info The information about the DDR configuration

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Get_Memmap( const char * dev, icb_mem_map_type * info );

//*============================================================================*/
/**
@brief 
      Unmaps L2 TCM from BIMC, if present.

@param[in]    dev  DAL string device ID.

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Unmap_L2_TCM( const char * dev );

/*============================================================================
                            DEPRECATED FUNCTIONS
============================================================================*/
//*============================================================================*/
/**
@brief 
      Configures the remap segments in BIMC. 
      Uses remap index 0.

@param[in] dev  DAL string device ID.
@param[in] info The information about the DDR configuration
@param[in] remap The information about the region to remap
                 Allowed to be NULL to clear the remap

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Remap( const char * dev, ddr_info * info, icbcfg_remap_info_type * remap );

#endif /* ICBCFG_H */
