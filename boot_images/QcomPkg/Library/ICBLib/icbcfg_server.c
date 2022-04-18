/*==============================================================================

FILE:      icbcfg_server.c

DESCRIPTION: This file implements the ICB Configuration driver for server chips.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

$Change: 11185940 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2015/04/07  pm     Created
 
        Copyright (c) 2012-2015 QUALCOMM Technologies, Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg.h"
#include "icbcfgi_server.h"
#include "DALSys.h"
#include "DALStdErr.h"

/*============================================================================
                          DEFINES/MACROS
============================================================================*/
#define ICB_IN8(addr)         (*((volatile uint8 *) (addr)))
#define ICB_IN16(addr)        (*((volatile uint16 *) (addr)))
#define ICB_IN32(addr)       (*((volatile uint32 *) (addr)))


#define ICB_OUT8(addr, data)   (*((volatile uint8 *) (addr)) = ((uint8) (data)))
#define ICB_OUT16(addr, data)  (*((volatile uint16 *) (addr)) = ((uint16) (data)))
#define ICB_OUT32(addr, data)  (*((volatile uint32 *) (addr)) = ((uint32) (data)))


#define ICB_CFG_8(addr, bmsk, rmsk, data) \
            ICB_OUT8(addr,((bmsk) != (rmsk) ? \
                          (((ICB_IN8(addr) & rmsk) & (uint8)(~(bmsk))) | (data & bmsk)) :  \
                          (data & bmsk) ))

#define ICB_CFG_16(addr, bmsk, rmsk, data) \
            ICB_OUT16(addr,((bmsk) != (rmsk) ? \
                           (((ICB_IN16(addr) & rmsk) & (uint16)(~(bmsk))) | (data & bmsk)) : \
                           (data & bmsk) ))

#define ICB_CFG_32(addr, bmsk, rmsk, data) \
            ICB_OUT32(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN32(addr) & rmsk) & (uint32)(~(bmsk))) | (data & bmsk)) : \
                            (data & bmsk) ))

/*============================================================================
                                 FUNCTIONS
============================================================================*/
static icbcfg_error_type ICB_Configure_Settings( icbcfg_device_config_type *dev_config );

/*============================================================================
                          Type definitions
============================================================================*/

/*============================================================================
                          Global data 
============================================================================*/
static icbcfg_device_config_type *icb_dev_config = NULL;
bool                            dev_config_valid = false;

/*============================================================================
                          Helper functions
============================================================================*/
//*============================================================================*/
/**
@brief
    Fetch the items we have in device config
 
@param[in]  dev         DAL string device ID.
@param[in]  dev_config  The pointer to store the device configuration pointer to

@return    
    Whether or not the config data is valid
*/ 
/*============================================================================*/
bool get_device_configuration
(
   const char *                dev,
   icbcfg_device_config_type **dev_config
)
{
   if( !dev_config_valid )
   {
      do
      {
         DALSYS_PROPERTY_HANDLE_DECLARE(hICBProp);
         DALSYSPropertyVar          ICBPropVar;
         icbcfg_info_type *         icbcfg_info;
         DalChipInfoFamilyType      family;
         DalChipInfoVersionType     version;
         uint32                     i;

         if (DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(dev, hICBProp))
         {
            break;
         }

         if ((DAL_SUCCESS != DALSYS_GetPropertyValue(hICBProp,
                                                   "icbcfg_info", 0, &ICBPropVar)))
         {
            break;
         }
         
         icbcfg_info = (icbcfg_info_type *)ICBPropVar.Val.pStruct;
         if( NULL == icbcfg_info )
         {
            break;
         }

         family  = DalChipInfo_ChipFamily();
         version = DalChipInfo_ChipVersion();
         
         for( i = 0; i < icbcfg_info->num_configs; i++ )
         {
            icbcfg_device_config_type *device_config = icbcfg_info->configs[i];
            if( family != device_config->family )
            {
               continue;
            }

            /* We've found a matching version in two different conditions:
             * We have an exact match
             * We don't need an exact match and the version is great than or equal to 
             * what we're looking for. */
            if( version == device_config->version ||
                (false == device_config->match && version >= device_config->version) )
            {
               icb_dev_config = device_config;
               break;
            }
         }

         /* Check to see if we found a matching configuration. */
         if( i == icbcfg_info->num_configs )
         {
            break;
         }

         /* Bookkeeping */
         dev_config_valid = true;
      } while( false );
   }

   *dev_config = icb_dev_config;
   return dev_config_valid;
}

/*============================================================================*/

/*============================================================================
                          External functions
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
icbcfg_error_type 
ICB_Config_Init( const char * dev )
{
   icbcfg_error_type ret_val = ICBCFG_ERROR_INIT_FAILURE;

   do
   {
      icbcfg_device_config_type *dev_config;

      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }

      ret_val = ICB_Configure_Settings(dev_config);
   } while( false );

   return ret_val;
}

static icbcfg_error_type ICB_Configure_Settings( icbcfg_device_config_type *dev_config )
{
   
   icbcfg_prop_type* prop_data;
   icbcfg_data_type* cfg_data;
   uint32 i;
   icbcfg_error_type ret_val = ICBCFG_SUCCESS;
   
   prop_data = dev_config->prop_data;
   cfg_data = prop_data->cfg_data;
               
   for (i=0; i < prop_data->len ; i++)
   {
      /* Check against NULL pointer */
      if(cfg_data[i].addr == NULL &&
         cfg_data[i].cfg_type != ICBCFG_DEFAULT) 
      {
          ret_val = ICBCFG_ERROR_INVALID_PARAM;
          break;
      }
  
      switch(cfg_data[i].cfg_type) 
      {           
       case ICBCFG_32_BIT_REG:
           /* 32 bit register configuration */
           ICB_CFG_32(cfg_data[i].addr, 
                      cfg_data[i].bmask,
                      cfg_data[i].rmask,
                      cfg_data[i].data);
           break;
        
       case ICBCFG_16_BIT_REG:
           /* 16 bit register configuration */
           ICB_CFG_16(cfg_data[i].addr, 
                      cfg_data[i].bmask,
                      cfg_data[i].rmask,
                      cfg_data[i].data);
           break;
  
       case ICBCFG_8_BIT_REG:
           /* 8 bit register configuration */
           ICB_CFG_8(cfg_data[i].addr, 
                     cfg_data[i].bmask,
                     cfg_data[i].rmask,
                     cfg_data[i].data);
            break;
  
       case ICBCFG_DEFAULT:
            /* Nothing to do, return success */
            return ICBCFG_SUCCESS;
  
       default:
           /* Error */
           ret_val = ICBCFG_ERROR_INVALID_PARAM;
           break;
       }
   } 
   return ret_val;
}

//*============================================================================*/
/**
@brief 
      Configures DDR slave segments in BIMC. It reads ICB configuration data (number
      of channels, maximum memory map, etc) from DAL Device Property file and configures 
      ICB registers.
 
@param[in]  dev     DAL string device ID.
@param[in]  config  DDR channel region configuration

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type
ICB_Segments_Init( const char * dev, ddr_info * info )
{
   icbcfg_error_type ret_val = ICBCFG_ERROR;

   return ret_val;
}

//*============================================================================*/
/**
@brief 
      Configures the remap segments in BIMC. 

@param[in] dev  DAL string device ID.
@param[in] info The information about the DDR configuration
@param[in] remap The information about the region to remap

@return    
      icbcfg_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type ICB_Remap( const char * dev, ddr_info * info, icbcfg_remap_info_type * remap )
{
   icbcfg_error_type          ret_val = ICBCFG_ERROR;

   return ret_val;
}

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
icbcfg_error_type ICB_Get_Memmap( const char * dev, icb_mem_map_type * info )
{
   icbcfg_error_type ret_val = ICBCFG_ERROR;

   return ret_val;
}

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
icbcfg_error_type ICB_Unmap_L2_TCM( const char * dev )
{
   icbcfg_error_type ret_val = ICBCFG_ERROR;

   return ret_val;
}

/* vim: set ts=3 sts=3 sw=3 et :*/ 
