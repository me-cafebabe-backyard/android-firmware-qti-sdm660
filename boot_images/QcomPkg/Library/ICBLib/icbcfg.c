/*==============================================================================

FILE:      icbcfg.c

DESCRIPTION: This file implements the ICB Configuration driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/ICBLib/icbcfg.c#4 $ 
$DateTime: 2016/11/18 03:04:56 $
$Author: pwbldsvc $
$Change: 11806192 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2016/05/13  sds    Fix KW error.
2015/07/20  sds    Add ICB_Config_PostInit().
2015/06/23  sds    Add support for multiple remap requests via RemapEx()
2015/06/18  sds    Make the desperation checks a little smarter.
2015/02/10  sds    Cleaned up address compression functions and added additional
                   desperation checks for segment mapping.
2014/11/05  sds    Add ICB_Unmap_L2_TCM() API.
2014/06/03  sds    Update max number of segments, and make segment algorithm
                   aware that this can be variable.
2014/05/19  sds    Added smarter mapping/remapping schemes
2013/11/08  vg     Added auto detection for MSM8926
2013/10/21  sds    Add additional method to attempt to map BRIC segments
2013/10/10  sds    BIMC remap support now checks for hardware support explicitly
2013/09/24  sds    Refactor code for better reuse and code size.
2013/09/23  sds    Fixes for BIMC remapper support
2013/08/30  sds    Added support for BIMC remap operations
2013/05/17  sds    Fixed the handling of non-power of two regions
2013/02/26  sds    Changed how available DDR regions are handled.
2012/08/07  sy     Fixed Linux compilation Error 
2012/02/07  av     Created
 
        Copyright (c) 2012-2016 QUALCOMM Technologies, Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg.h"
#include "icbcfgi.h"
#include "DALSys.h"
#include "DALStdErr.h"
#include "busywait.h"

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
            ICB_OUT8(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN8(addr) & (rmsk)) & (uint8)(~(bmsk))) | ((data) & (bmsk))) : \
                            ((data) & (bmsk)) ))

#define ICB_CFG_16(addr, bmsk, rmsk, data) \
            ICB_OUT16(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN16(addr) & (rmsk)) & (uint16)(~(bmsk))) | ((data) & (bmsk))) : \
                            ((data) & (bmsk)) ))

#define ICB_CFG_32(addr, bmsk, rmsk, data) \
            ICB_OUT32(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN32(addr) & (rmsk)) & (uint32)(~(bmsk))) | ((data) & (bmsk))) : \
                            ((data) & (bmsk)) ))

#define ICB_CFG_IN8(addr, bmsk, rmsk, shft) \
            (((ICB_IN8(addr) & (rmsk)) & (uint8)(bmsk)) >> (shft))

#define ICB_CFG_IN16(addr, bmsk, rmsk, shft) \
            (((ICB_IN16(addr) & (rmsk)) & (uint16)(bmsk)) >> (shft))

#define ICB_CFG_IN32(addr, bmsk, rmsk, shft) \
            (((ICB_IN32(addr) & (rmsk)) & (uint32)(bmsk)) >> (shft))

#define ICB_CFG_OUT8(addr, bmsk, rmsk, shft, data) \
            ICB_OUT8(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN8(addr) & (rmsk)) & (uint8)(~(bmsk))) | (((data) & (bmsk)) << (shft))) : \
                            (((data) & (bmsk)) << (shft)) ))

#define ICB_CFG_OUT16(addr, bmsk, rmsk, shft, data) \
            ICB_OUT16(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN16(addr) & (rmsk)) & (uint16)(~(bmsk))) | (((data) & (bmsk)) << (shft))) : \
                            (((data) & (bmsk)) << (shft)) ))

#define ICB_CFG_OUT32(addr, bmsk, rmsk, shft, data) \
            ICB_OUT32(addr, ((bmsk) != (rmsk) ? \
                            (((ICB_IN32(addr) & (rmsk)) & (uint32)(~(bmsk))) | (((data) & (bmsk)) << (shft))) : \
                            (((data) & (bmsk)) << (shft)) ))

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

#define MAX_WAIT_CNT 1000
#define WAIT_US 1

/*============================================================================
                                 FUNCTIONS
============================================================================*/

/*============================================================================
                          Type definitions
============================================================================*/
/* Memory region definition */
#define LAST_REGION 4

/* A more generic implementation friendly interpretation of the ddr_size_info struct. */
#define MAX_DDR_CHANNELS 2
#define MAX_CS           2
typedef struct 
{
  uint32 sdram_size[MAX_DDR_CHANNELS][MAX_CS];
  uint64 sdram_addr[MAX_DDR_CHANNELS][MAX_CS];
} icb_ddr_size_info_type;

#define MAX_REMAP_SEGS 4

/*============================================================================
                          Global data 
============================================================================*/
static icbcfg_device_config_type *icb_dev_config = NULL;
bool                              dev_config_valid = false;
icbcfg_remap_info_type            req_remaps[MAX_REMAP_SEGS];

/*============================================================================
                          Helper functions
============================================================================*/
//*============================================================================*/
/**
@brief
    Write out ICBCFG addr:data settings.
 
@param[in] dev_config  The settings list to use

@return    
      Success or failure.
*/ 
/*============================================================================*/
static icbcfg_error_type ICB_Configure_Settings( icbcfg_prop_type *prop_data )
{
   
   icbcfg_data_type* cfg_data;
   uint32 i, cnt = 0, data_32 = 0;
   uint16 data_16 = 0;
   uint8 data_8 = 0;
   icbcfg_error_type ret_val = ICBCFG_SUCCESS;
   
   /* Make sure we have a list first. */
   if( NULL == prop_data )
   {
      return ret_val;
   }

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

       case ICBCFG_32_BIT_READ_REG:
           /* 32-bit register read */
           data_32 = ICB_CFG_IN32(cfg_data[i].addr,
                                  cfg_data[i].bmask,
                                  cfg_data[i].rmask,
                                  cfg_data[i].data);
           break;

       case ICBCFG_16_BIT_READ_REG:
           /* 16-bit register read */
           data_16 = ICB_CFG_IN16(cfg_data[i].addr,
                                  cfg_data[i].bmask,
                                  cfg_data[i].rmask,
                                  cfg_data[i].data);
           break;

       case ICBCFG_8_BIT_READ_REG: 
           /* 8-bit register read */
           data_8 = ICB_CFG_IN8(cfg_data[i].addr,
                                cfg_data[i].bmask,
                                cfg_data[i].rmask,
                                cfg_data[i].data);
           break;
  
       case ICBCFG_32_BIT_WRITE_REG:
           /* 32-bit register write */
           ICB_CFG_OUT32(cfg_data[i].addr,
                         cfg_data[i].bmask,
                         cfg_data[i].rmask,
                         cfg_data[i].data,
                         data_32);
           break;

       case ICBCFG_16_BIT_WRITE_REG:
           /* 16-bit register write */
           ICB_CFG_OUT16(cfg_data[i].addr,
                         cfg_data[i].bmask,
                         cfg_data[i].rmask,
                         cfg_data[i].data,
                         data_16);
           break;

       case ICBCFG_8_BIT_WRITE_REG: 
           /* 8-bit register write */
           ICB_CFG_OUT8(cfg_data[i].addr,
                        cfg_data[i].bmask,
                        cfg_data[i].rmask,
                        cfg_data[i].data,
                        data_8);
           break;
  
       case ICBCFG_32_BIT_WAIT_REG:
           /* 32-bit register read */
           data_32 = ICB_CFG_IN32(cfg_data[i].addr,
                                  cfg_data[i].bmask,
                                  cfg_data[i].rmask,
                                  0);

           for(cnt = 0; cnt < MAX_WAIT_CNT && data_32 != cfg_data[i].data; cnt++)
           {
              busywait(WAIT_US);
              data_32 = ICB_CFG_IN32(cfg_data[i].addr,
                                     cfg_data[i].bmask,
                                     cfg_data[i].rmask,
                                     0);
           }

           /* If we've exceeded our wait and we still don't have the value we want,
            * we've timed out and so report an error. */
           if( cnt >= MAX_WAIT_CNT && data_32 != cfg_data[i].data )
           {
              ret_val = ICBCFG_ERROR_INIT_FAILURE;
           }
           break;

       case ICBCFG_16_BIT_WAIT_REG:
           /* 16-bit register read */
           data_16 = ICB_CFG_IN16(cfg_data[i].addr,
                                  cfg_data[i].bmask,
                                  cfg_data[i].rmask,
                                  0);

           for(cnt = 0; cnt < MAX_WAIT_CNT && data_16 != cfg_data[i].data; cnt++)
           {
              busywait(WAIT_US);
              data_16 = ICB_CFG_IN16(cfg_data[i].addr,
                                     cfg_data[i].bmask,
                                     cfg_data[i].rmask,
                                     0);
           }

           /* If we've exceeded our wait and we still don't have the value we want,
            * we've timed out and so report an error. */
           if( cnt >= MAX_WAIT_CNT && data_16 != cfg_data[i].data )
           {
              ret_val = ICBCFG_ERROR_INIT_FAILURE;
           }
           break;


       case ICBCFG_8_BIT_WAIT_REG: 
           /* 8-bit register read */
           data_8 = ICB_CFG_IN8(cfg_data[i].addr,
                                  cfg_data[i].bmask,
                                  cfg_data[i].rmask,
                                  0);

           for(cnt = 0; cnt < MAX_WAIT_CNT && data_8 != cfg_data[i].data; cnt++)
           {
              busywait(WAIT_US);
              data_8 = ICB_CFG_IN8(cfg_data[i].addr,
                                     cfg_data[i].bmask,
                                     cfg_data[i].rmask,
                                     0);
           }

           /* If we've exceeded our wait and we still don't have the value we want,
            * we've timed out and so report an error. */
           if( cnt >= MAX_WAIT_CNT && data_8 != cfg_data[i].data )
           {
              ret_val = ICBCFG_ERROR_INIT_FAILURE;
           }
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
    Count the number of bits set in a uint64.
 
@param[in]  val  The uint64 value to process.

@return    
      The number of set bits.
*/ 
/*============================================================================*/
uint32 count_set_bits(const uint64 val)
{
  /* Count the number of set bits, from Bit Twiddling Hacks. */
  uint64 r = val;  // Resulting rank of bit at pos goes here.

  // Count set bits in parallel.
  r = (r & 0x5555555555555555) + ((r >> 1) & 0x5555555555555555);
  r = (r & 0x3333333333333333) + ((r >> 2) & 0x3333333333333333);
  r = (r & 0x0f0f0f0f0f0f0f0f) + ((r >> 4) & 0x0f0f0f0f0f0f0f0f);
  r = r % 255;

  return (uint32)r;
}

//*============================================================================*/
/**
@brief
    Count the number of leading zeroes in a uint64
 
@param[in]  val  The uint64 value to process.

@return    
      The number of leading zero bits.
*/ 
/*============================================================================*/
uint32 count_leading_zeroes(const uint64 val)
{
  uint32 cnt = __builtin_clz( (uint32)((0xFFFFFFFF00000000ULL & val) >> 32) );
  if(cnt == 32)
  {
    cnt += __builtin_clz( (uint32)(0xFFFFFFFFULL & val));
  }

  return cnt;
}

//*============================================================================*/
/**
@brief
    Count the number of trailing zeroes in a uint64
 
@param[in]  val  The uint64 value to process.

@return    
      The number of trailing zero bits.
*/ 
/*============================================================================*/
uint32 count_trailing_zeroes(const uint64 val)
{
  uint32 cnt = count_leading_zeroes(val & -val);
  return val ? 63 - cnt : cnt;
}

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
         memset(req_remaps, 0, sizeof(req_remaps));
         HAL_bimc_Init(icb_dev_config->bimc_hal_info);
         icb_dev_config->best_effort = false;
         dev_config_valid = true;
      } while( false );
   }

   *dev_config = icb_dev_config;
   return dev_config_valid;
}

//*============================================================================*/
/**
@brief
    Convert from DDR info type to our internal region representation.
 
@param[in]  info
@param[in]  num_channels
@param[in]  ddr_regions

*/ 
//*============================================================================*/
void convert_ddr_regions
(
  ddr_info *              info,
  uint32                  num_channels,
  icb_mem_map_type *      ddr_regions
)
{
   uint32 cs, channel, region;
   region_type *channel_regions;
   icb_ddr_size_info_type *icb_ddr_size_info = (icb_ddr_size_info_type *)&info->ddr_size;

   /* Convert to our representation, sweeping together chip selects.
     * We can only sweep together chip selects if everything is interleaved
     * (CS0 and CS1) or nothing is, and the chip selects on the same channel
     * are contiguous. */
   memset(ddr_regions, 0, sizeof(icb_mem_map_type));
   for( channel = 0; channel < num_channels; channel++ )
   {
      region = 0;
      channel_regions = ddr_regions->channels[channel].regions;
      for( cs = 0; cs < MAX_CS; cs++ )
      { 
         uint64 cs_size;

         if( 0 == icb_ddr_size_info->sdram_size[channel][cs] )
         {
            continue;
         } 

         /* Size of the region depends on whether or not we're interleaved.
          * Multiply the size we're given by the number of channels to
          * determine the actual region size. */
         cs_size = (info->interleaved_memory & (1 << cs)) != 0 ?
                    ((uint64)icb_ddr_size_info->sdram_size[channel][cs] << 20) * num_channels:
                    (uint64)icb_ddr_size_info->sdram_size[channel][cs] << 20;

         channel_regions[region].interleaved = 
           (info->interleaved_memory & (1 << cs)) != 0;
         channel_regions[region].base_addr = 
           icb_ddr_size_info->sdram_addr[channel][cs];
         channel_regions[region].size = cs_size;
         region++;
      }
   }
}

//*============================================================================*/
/**
@brief
    Compress a region struct to minimal regions and apply constraints
 
@param[in]     dev_config   a pointer to the device configuration data to use
@param[in]     constrain    whether or not to constrain the minimal region sweeping
                            to avoid our safe reset/hardware reserved region
@param[inout]  ddr_regions  the regions descriptor to sweep together

*/ 
//*============================================================================*/
void compress_regions
(
  icbcfg_device_config_type *dev_config,
  bool                       constrain,
  icb_mem_map_type *         ddr_regions
)
{
   uint64 map_ddr_start_addr = 0, map_ddr_end_addr = 0;
   uint32 channel;

   /* Condense regions to remove any size zero regions.
    * Also sort by base address to make the next step easier. */
   for( channel = 0; channel < dev_config->num_channels; channel++ )
   {
      uint32 i, pass;
      region_type *channel_regions = ddr_regions->channels[channel].regions, temp_region;

      /* First, clear any zero size regions. */
      for( i = 1; i < MAX_REGIONS; i++ )
      {
         if( 0 == channel_regions[i].size )
         {
            channel_regions[i].base_addr   = 0;
            channel_regions[i].interleaved = false;
         }
      }

      /* Now sort, lowest addresses first. */
      for( pass = 0; pass < (MAX_REGIONS - 1); pass++ )
      {
         for( i = 0; i < (MAX_REGIONS - 1 - pass); i++ )
         {
            /* Swap if:
             * The next region has a lower base address and a size
             * The next region has a size and the current region does not. */
            if( (channel_regions[i+1].base_addr < channel_regions[i].base_addr && 0 != channel_regions[i+1].size) ||
                (0 != channel_regions[i+1].size && 0 == channel_regions[i].size) )
            {
               temp_region = channel_regions[i];
               channel_regions[i] = channel_regions[i+1];
               channel_regions[i+1] = temp_region;
            }
         }
      }
   }

   /* Sweep together segments in place, if possible. */
   for( channel = 0; channel < dev_config->num_channels; channel++ )
   {
      region_type *channel_regions = ddr_regions->channels[channel].regions;
      uint32 region, comp_region;

      /* Skip the first region, since we are doing an in-place sweep. */
      for( comp_region = 0, region = 0; region < MAX_REGIONS; region++ )
      { 
         if( 0 == channel_regions[region].size )
         {
            continue;
         }

         /* Do no "sweeping together" for the first region/comp region pair.
          * They're the same thing, but we still need to apply constraints
          * if requested to do so. */
         if( 0 == region &&  0 == comp_region )
         {
           /* Nothing to do here. */
         }
         /* Regions are only considered contiguous regions if they
         * share the same interleaving mode, and are address contiguous. */
         else if( !((channel_regions[region].interleaved ==
                     channel_regions[comp_region].interleaved) &&
                     ( /* This region is contiguous after the previous region */
                       (channel_regions[region].base_addr==
                       (channel_regions[comp_region].base_addr +
                        channel_regions[comp_region].size)) ||
                       /* This region is contiguous before the previous region */
                       (channel_regions[comp_region].base_addr ==
                       (channel_regions[region].base_addr +
                        channel_regions[region].size))
                     )))
         {
            /* Create a new region. We're either the first, or a new one. */
            comp_region++;
            channel_regions[comp_region].interleaved = channel_regions[region].interleaved;
            channel_regions[comp_region].base_addr = channel_regions[region].base_addr;
            channel_regions[comp_region].size = channel_regions[region].size;
         }
         /* Not the first region, and extendable. */
         else
         {
            /* Add to existing region. */
            channel_regions[comp_region].size += channel_regions[region].size;

            /* If the merged region is under the existing region, use the merged region's start address. */
            if( channel_regions[comp_region].base_addr > channel_regions[region].base_addr )
            {
               channel_regions[comp_region].base_addr = channel_regions[region].base_addr;
            }
         }

         /* Constrain segment addresses/sizes, if required. */
         if( constrain )
         {
            /* First find the appropriate region to match to, since we need to limit
             * sweeping together of regions that aren't valid.
             * If we are below the start or DDR space, make it the start of DDR.
             * If we are past the end of DDR space, adjust the size accordingly. */
            uint32 ridx;
            for( ridx = 0; ridx < dev_config->map_ddr_region_count; ridx++ )
            {
               /* If the start address of either region lies in the other, select it. */
               if( (channel_regions[comp_region].base_addr >= dev_config->map_ddr_regions[ridx].start_addr &&
                    channel_regions[comp_region].base_addr < dev_config->map_ddr_regions[ridx].end_addr) ||
                   (dev_config->map_ddr_regions[ridx].start_addr >= channel_regions[comp_region].base_addr &&
                    dev_config->map_ddr_regions[ridx].start_addr < (channel_regions[comp_region].base_addr +channel_regions[comp_region].size)) )
               {
                  map_ddr_start_addr = dev_config->map_ddr_regions[ridx].start_addr;
                  map_ddr_end_addr   = dev_config->map_ddr_regions[ridx].end_addr;
                  break;
               }
            }

            /* If we didn't find a region that matches, skip it. */
            if( ridx == dev_config->map_ddr_region_count )
            {
               continue;
            }

            /* Enforce memory map limits on DDR space. */
            if( channel_regions[comp_region].base_addr < map_ddr_start_addr )
            {
               channel_regions[comp_region].size -= map_ddr_start_addr - channel_regions[comp_region].base_addr;
               channel_regions[comp_region].base_addr = map_ddr_start_addr;
            }
            if( channel_regions[comp_region].base_addr + channel_regions[comp_region].size > map_ddr_end_addr )
            {
               channel_regions[comp_region].size = map_ddr_end_addr - channel_regions[comp_region].base_addr;
            }
         }
      }

      /* Check to see if we exceed the number of segments allowed. */
      if( comp_region > dev_config->num_segments )
      {
        dev_config->best_effort = true;
        break;
      }

      /* Clear unused regions. */
      for( comp_region++; comp_region < MAX_REGIONS; comp_region++ )
      {
         channel_regions[comp_region].interleaved = false;
         channel_regions[comp_region].base_addr = 0;
         channel_regions[comp_region].size = 0;
      }
   }
}

//*============================================================================*/
/**
@brief
    Get the current system memory map from the hardware, inserting reserved
    region to the memory map if it is determined we removed it earlier,
    and we are asked to do so.
 
@param[in]  hICBProp       the property handle to use
@param[in]  add_reserved   whether or not to insert the safe reset/hw reserved region
                           back into the memory map
@param[in]  sys_map        the structure to store the memory map in

*/ 
//*============================================================================*/
void get_system_memory_map
(
  icbcfg_device_config_type *dev_config,
  bool                       add_reserved,
  icb_mem_map_type *         sys_map
)
{
   uint32 channel;
   icb_mem_map_type sub_map;

   /* Clear the map structure passed to us. */
   memset(sys_map, 0, sizeof(icb_mem_map_type));

   for( channel = 0; channel < dev_config->num_channels; channel++ )
   {
      uint32 region, pass, seg, sub_seg = 0, add_seg = 0;
      memset(&sub_map, 0, sizeof(sub_map));

      /* Go through and collect any enabled segments. */
      for( region = 0; region < dev_config->num_segments; region++ )
      {
         HAL_bimc_SlaveSegmentType hal_seg;
         region_type *channel_regions;
         HAL_bimc_GetSlaveSegment( dev_config->bimc_hal_info, 
                                   dev_config->channel_map[channel],
                                   region, &hal_seg ); 

         if( hal_seg.bEnable )
         {
            if( hal_seg.type == BIMC_SEGMENT_TYPE_ADDITIVE )
            {
               /* Additive segments go to the sys_map passed to us.
                * We'll deal with any subtractive mappings later. */
               channel_regions = sys_map->channels[channel].regions;
               seg = add_seg++;
            }
            else
            {
               /* Subtractive segments go to the sub_map we're keeping.
                * We'll use these to shrink the sys_map after we've collected them.
                * If we are expected to add the reserved region to the map,
                * skip any subtractive segments that look like it. */
               if( add_reserved &&
                   hal_seg.uStartAddr   == dev_config->safe_reset_seg->uStartAddr &&
                   hal_seg.uSegmentSize == dev_config->safe_reset_seg->uSegmentSize )
               {
                 continue;
               }
               channel_regions = sub_map.channels[channel].regions;
               seg = sub_seg++;
            }

            channel_regions[seg].base_addr   = hal_seg.uStartAddr;
            channel_regions[seg].size        = hal_seg.uSegmentSize;
            channel_regions[seg].interleaved = 
              (hal_seg.interleave == BIMC_INTERLEAVE_EVEN || hal_seg.interleave == BIMC_INTERLEAVE_ODD);
         }
      }

      /* Shrink sys_map regions, if we found any subtractive mappings. 
       * We will, at most, have to make as many passes through the additive
       * segments as we have subtractive segments.
       * It's more work to sweep together the subtractive segments than it is
       * to just brute force check after every modification. */
      for( pass = 0; pass < sub_seg; pass++ )
      {
         for( seg = 0; seg < sub_seg; seg++ )
         {
            region_type *sub_region = &sub_map.channels[channel].regions[seg];
            if( 0 == sub_region->size )
            {
               continue;
            }
            
            for( region = 0; region < dev_config->num_segments; region++ )
            {
               region_type *add_region = &sys_map->channels[channel].regions[region];
               if( 0== add_region->size )
               {
                  continue;
               }
               
               /* Check here if subtractive segment will stack at the end. */
               if( (add_region->base_addr + add_region->size) ==
                   (sub_region->base_addr + sub_region->size) )

               {
                  /* We found a match, so shrink the additive region.
                   * Also clear the subtractive region for any subsequent passes. */
                  add_region->size      -= sub_region->size;
                  sub_region->base_addr  = 0;
                  sub_region->size       = 0;
               }
               /* Check here if the subtractive segment is contained by region. */
               else if( (add_region->base_addr < sub_region->base_addr) &&
                        ((add_region->base_addr + add_region->size) >
                         (sub_region->base_addr + sub_region->size)))
               {
                  /* We found a match, so split the additive region.
                   * First, copy the additive region we're working on to the next slot.
                   * Resize the first half of the split. */
                  sys_map->channels[channel].regions[region+1] = *add_region;
                  add_region->size       = sub_region->base_addr - add_region->base_addr;

                  /* Now, adjust the second half. */
                  add_region = &sys_map->channels[channel].regions[region+1];
                  add_region->size      -= (sub_region->base_addr - add_region->base_addr) + sub_region->size;
                  add_region->base_addr  = sub_region->base_addr + sub_region->size;

                  /* Finally, clear the subtractive region for any subsequent passes. */
                  sub_region->base_addr  = 0;
                  sub_region->size       = 0;
               }
               /* Check here if the subtractive segment will stack at the start. */
               else if( (add_region->base_addr == sub_region->base_addr &&
                         add_region->size > sub_region->size) )
               {
                  /* We found a match, so shrink the additive region.
                   * Also clear the subtractive region for any subsequent passes. */
                  add_region->base_addr += sub_region->size;
                  add_region->size      -= sub_region->size;
                  sub_region->base_addr  = 0;
                  sub_region->size       = 0;
               }
            }
         }
      }
   }
}

//*============================================================================*/
/**
@brief
    Get the largest valid segment size we can use with the given start address.
 
@param[in]  start_addr
@param[in]  size

*/ 
//*============================================================================*/
uint64 get_largest_valid_size
(
  uint64 start_addr,
  uint64 size
)
{
   uint64 largest_size = 1ULL << (63 - count_leading_zeroes( size ));

   /* The largest size is the smallest power of two of 
    * either the largest power of two in the size or the smaller power of two
    * in the start_address. The easiest way to get that
    * is to just bitwise OR the start and size together. */
   largest_size = 1ULL << count_trailing_zeroes( start_addr | largest_size );

   return largest_size;
}

//*============================================================================*/
/**
@brief
    Get the minimum number of segments required to map this region with 
    additive only mappings.
 
@param[in] region_base_addr
@param[in] region_size

*/ 
//*============================================================================*/
uint32 get_simple_segment_count
(
   uint64 region_base_addr,
   uint64 region_size
)
{
   uint32 num_segments = 0;
   uint64 base = region_base_addr;
   uint64 size = region_size;

   if( size > 0 )
   {
      /* Determine additive segments until we hit the end of the region. */
      while( base < (region_base_addr + region_size) )
      {
         uint64 seg_size = get_largest_valid_size( base, size );
         size -= seg_size;
         base += seg_size;
         num_segments++;
      }
   }

   return num_segments;
}

//*============================================================================*/
/**
@brief
    Get the minimum number of segments required to map this region with 
    additive and subtractive mappings.
 
@param[in] region_base_addr
@param[in] region_size

*/ 
//*============================================================================*/
uint32 get_minimum_segment_count
(
   uint64 region_base_addr,
   uint64 region_size
)
{
   uint64 base = region_base_addr, size;
   uint32 num_segments = 0;

   if( region_size > 0 )
   {
      /* Get the number of simple additive segments. */
      num_segments = get_simple_segment_count( region_base_addr, region_size );

      /* If we're greater than 2, try harder.
       * Maybe we can get it in fewer with a subtractive segment. */
      if( num_segments > 2 )
      {
         /* Start at 1, because we will have a subtractive segment. */
         uint32 segments = 1;
         
         /* Adjust the end to the next power of 2. */
         uint64 region_end = region_base_addr + region_size;
         uint64 next_end = 1ULL << (64 - count_leading_zeroes( region_end ));
         region_size += next_end - region_end;
         size = region_size;

         /* Determine additive segments until we hit the end of the region. */
         while( base < (region_base_addr + region_size) )
         {
            uint64 seg_size = get_largest_valid_size( base, size );
            size -= seg_size;
            base += seg_size;
            segments++;
         }

         /* If we're less, save that. */
         if( segments < num_segments )
         {
            num_segments = segments;
         }
      }
   }

   return num_segments;
}

//*============================================================================*/
/**
@brief
    Write a memory map to the hardware.
 
@param[in]  dev_config
@param[in]  map

*/ 
//*============================================================================*/
void map_segments
(
   icbcfg_device_config_type *dev_config,
   icb_mem_map_type *         map
)
{
   uint32 channel;
   region_type *channel_regions;
   HAL_bimc_SlaveSegmentType segs[MAX_REGIONS];

   /* Map segments. */
   for( channel = 0; channel < dev_config->num_channels; channel++ )
   {
      HAL_bimc_SlaveSegmentType hal_seg;
      region_type sub_regions[MAX_REGIONS];
      uint32 segment = 0, region, num_segs = 0, used_subs = 0, sub_idx;
      channel_regions = map->channels[channel].regions;
      memset(segs, 0, sizeof(segs));
      memset(sub_regions, 0, sizeof(sub_regions));

      /* Find the number of valid regions and the number of set bits we have.
       * That'll determine how (if?) we can actually map this.
       * At some point we'll want to determine here if it's even possible to map
       * what we're being asked. Until then, do best effort. */
      for( region = 0; region < dev_config->num_segments; region++ )
      {
         num_segs += get_minimum_segment_count( channel_regions[region].base_addr,
                                                channel_regions[region].size );
      }

      /* If we have more segments to map than we have and more than 1 region 
       * it's time to get desperate. We only have a limited number of segments 
       * in the hardware, so this gets ugly. Merge the segments, even if they aren't
       * contiguous. Just remember to store any breaks that we're glossing over. */
      if( num_segs > dev_config->num_segments )
      {
         uint32 merge_region = 0;
         for( region = 1; region < dev_config->num_segments; region++ )
         {
            uint64 merge_base, merge_end, region_base, region_end;

            /* Skip regions without any size. */
            if( 0 == channel_regions[region].size )
            {
              continue;
            }

            /* Short-hand some of this calculations to make this more readable. */
            merge_base  = channel_regions[merge_region].base_addr;
            merge_end   = merge_base + channel_regions[merge_region].size;
            region_base = channel_regions[region].base_addr;
            region_end  = region_base + channel_regions[region].size;

            /* Determine if the two regions are contiguous.
             * Merge them, depending on *how* the are contiguous. */
            if( merge_end == region_base )
            {
               /* Base region is the the lower of the two. Extend it and clear the other. */
               channel_regions[merge_region].size += channel_regions[region].size;
               channel_regions[region].base_addr   = 0;
               channel_regions[region].size        = 0;
            }
            else if( region_end == merge_base)
            {
               /* Base region is the the higher of the two.
                  * Adjust base and extend it, and clear the other. */
               channel_regions[merge_region].base_addr  = region_base;
               channel_regions[merge_region].size      += channel_regions[region].size;
               channel_regions[region].base_addr        = 0;
               channel_regions[region].size             = 0;
            }
            /* We're not contiguous. Determine which region is lower and adjust accordingly.
             * Remember to log the hole we're glossing over. */
            else
            {
               if( merge_base < region_base )
               {
                  uint64 sub_size = region_base - merge_end;

                  /* If this sub section we're trying to make cannot be done with a single subtract,
                   * don't merge. */
                  if( sub_size > get_largest_valid_size(merge_end, sub_size) )
                  {
                     merge_region++;
                     continue;
                  }

                  /* Base region is the the lower of the two.
                  * Determine the "glossed over" region. */
                  sub_regions[used_subs].base_addr = merge_end;
                  sub_regions[used_subs].size      = sub_size;

                  /* Extend the base region and clear the other. */
                  channel_regions[merge_region].size += (channel_regions[region].size + sub_regions[used_subs].size);
                  channel_regions[region].base_addr   = 0;
                  channel_regions[region].size        = 0;
                  used_subs++;
               }
               else
               {
                  uint64 sub_size = merge_base - region_end;

                  /* If this sub section we're trying to make cannot be done with a single subtract,
                   * don't merge. */
                  if( sub_size > get_largest_valid_size(region_end, sub_size) )
                  {
                     merge_region++;
                     continue;
                  }

                  /* Base region is the the higher of the two.
                   * Determine the "glossed over" region. */
                  sub_regions[used_subs].base_addr = region_end;
                  sub_regions[used_subs].size      = sub_size;

                  /* Extend the base region and clear the other. */
                  channel_regions[merge_region].base_addr  = region_base;
                  channel_regions[merge_region].size      += (channel_regions[region].size + sub_regions[used_subs].size);
                  channel_regions[region].base_addr        = 0;
                  channel_regions[region].size             = 0;
                  used_subs++;
               }
            }
         }

         /* If we were able to merge into one region, we need to see if what we just did even helps. */
         if( 0 == merge_region )
         {
            uint32 seg_cnt = get_simple_segment_count( channel_regions[0].base_addr,
                                                       channel_regions[0].size  );

            /* If the number of bits is still greater than the number of remaining segments
            * (number of segments - number of subs we just had to add above)
            * we're going to get really desperate.
            * We need to see if we can move either of the ends to get us aligned.
            * We may even have to move both, but check both ends to see if one or the other will align us. */
            if( seg_cnt > (dev_config->num_segments - used_subs) )
            {
               uint64 region_end = channel_regions[0].base_addr + channel_regions[0].size;
               uint64 aligned_size;

               /* Only try and move the end if it's not aligned to a power of 2.
                * If it's aligned, there's no point.
                * If we're not aligned, resize and record the segment we need to remove. */
               if( 1 != count_set_bits( region_end ) )
               {
                  uint64 next_end = 1ULL << (64 - count_leading_zeroes( region_end ));

                  sub_regions[used_subs].base_addr = channel_regions[0].base_addr +
                                                   channel_regions[0].size;
                  sub_regions[used_subs].size      = next_end - region_end;
                  channel_regions[0].size         += sub_regions[used_subs].size;
                  used_subs++;

                  /* Move the region end to point at the end we're now using for the next step. */
                  region_end = next_end;
               }

               /* Now, see if we need to move the start.
                * We know that by the time we get here, the end is aligned to a power of 2.
                * To see if the start is aligned, we just check to see if the aligned size is equal to our region size. */
               aligned_size = get_largest_valid_size( channel_regions[0].base_addr, channel_regions[0].size );
               if( aligned_size != channel_regions[0].size )
               {
                  uint64 new_size = 1ULL << (64 - count_leading_zeroes( channel_regions[0].size ));
                  uint64 new_base = region_end - new_size;

                  sub_regions[used_subs].base_addr = new_base;
                  sub_regions[used_subs].size      = channel_regions[0].base_addr - sub_regions[used_subs].base_addr;
                  channel_regions[0].base_addr     = new_base;
                  channel_regions[0].size          = new_size;
                  used_subs++;
               }
            }
         }
      }

      num_segs = 0;
      for( region = 0; region < dev_config->num_segments; region++ )
      {
         num_segs += get_simple_segment_count( channel_regions[region].base_addr,
                                               channel_regions[region].size );
      }
      for( region = 0; region < dev_config->num_segments; region++ )
      {
         uint64 start_addr, size;
         bool   needs_subtractive = false;

         /* Skip regions with a size of zero. */
         if( 0 == channel_regions[region].size )
         {
             continue;
         }

         /* Divide into segments. */
         start_addr = channel_regions[region].base_addr;
         size       = channel_regions[region].size;

         /* Initialize segment information. */
         hal_seg.bEnable    = true;
         hal_seg.type       = BIMC_SEGMENT_TYPE_ADDITIVE;
         hal_seg.interleave = channel_regions[region].interleaved?
                                 (channel % 2 == 0?
                                   BIMC_INTERLEAVE_EVEN:
                                   BIMC_INTERLEAVE_ODD) :
                                 BIMC_INTERLEAVE_NONE;

         /* If we have more bits set in the size than our amount
           * of remaining segments, we will have to use subtractive segments. */
         needs_subtractive = (get_simple_segment_count( start_addr, size ) > 1) && (num_segs > (dev_config->num_segments - used_subs));
         if( needs_subtractive )
         {
           /* Resize our starting segment to be the next power of 2 greater than
             * the desired size, as following segments will shrink the mapped area. */
             size = 1ULL << (64 - count_leading_zeroes( size ));
         }

         /* Keep adding segments while size remains and there are remaining segments. */
         while( size > 0 && segment < dev_config->num_segments )
         {
            hal_seg.uStartAddr   = start_addr;

            /* If we don't need subtractive, the segment size is the largest power of two
             * that divides evenly into our base address. */
            if( !needs_subtractive )
            {
              hal_seg.uSegmentSize = get_largest_valid_size( start_addr, size );
            }
            /* Otherwise, use the size we are given. */
            else
            {
              hal_seg.uSegmentSize = size;
            }

            /* Copy temp segment into segment list. */
            segs[segment] = hal_seg;

            if( needs_subtractive )
            {
              /* Adjust size remaining. */
              if( hal_seg.type == BIMC_SEGMENT_TYPE_ADDITIVE )
              {
                  /* If the previous segment was additive, the size remaining
                  * is calculated differently. */
                  start_addr   = hal_seg.uStartAddr + channel_regions[region].size;
                  size         = hal_seg.uSegmentSize - channel_regions[region].size;
              }
              else
              {
                  start_addr  = hal_seg.uStartAddr + size;
                  size       -= hal_seg.uSegmentSize;
              }

              /* Subtractive segments must be linear. */
              hal_seg.type       = BIMC_SEGMENT_TYPE_SUBTRACTIVE;
              hal_seg.interleave = BIMC_INTERLEAVE_NONE;
            }
            else
            {
              start_addr  = hal_seg.uStartAddr + hal_seg.uSegmentSize;
              size       -= hal_seg.uSegmentSize;
            }
            segment++;

            /* If we've run out of segments, and there was some size remaining,
            * indicate that we've entered "best effort" mode. */
            if( size > 0 && segment == dev_config->num_segments )
            {
               dev_config->best_effort = true;
            }
         }
      }

      /* If we have too many sub segments to program, go through the list.
       * If there is a sub segment that is the safe segment, make sure it 
       * makes the cut. Swap it with the last spot we can program. */
      if( used_subs > (dev_config->num_segments - segment) )
      {
         region_type temp_sub;
         uint32 swap_idx = dev_config->num_segments - segment - 1;

         for(sub_idx = 0; sub_idx < used_subs; sub_idx++)
         {
            if( sub_regions[sub_idx].base_addr == dev_config->safe_reset_seg->uStartAddr &&
                sub_regions[sub_idx].size == dev_config->safe_reset_seg->uSegmentSize )
            {
               temp_sub = sub_regions[swap_idx];
               sub_regions[swap_idx] = sub_regions[sub_idx];
               sub_regions[sub_idx] = temp_sub;
               break;
            }
         }
      }

      /* Add any "extra" subs we needed to create earlier, if any. */
      for(sub_idx = 0;
          sub_idx < used_subs && segment < dev_config->num_segments;
          sub_idx++)
      {
         segs[segment].bEnable      = true;
         segs[segment].uStartAddr   = sub_regions[sub_idx].base_addr;
         segs[segment].uSegmentSize = sub_regions[sub_idx].size;
         segs[segment].type         = BIMC_SEGMENT_TYPE_SUBTRACTIVE;
         segs[segment].interleave   = BIMC_INTERLEAVE_NONE;
         segment++;
      }

      /* Preemptively disable any enabled additive segments. */
      for( segment = dev_config->num_segments;
           segment > 0;
           segment-- )
      {
         HAL_bimc_SlaveSegmentType cur_seg;

         HAL_bimc_GetSlaveSegment( dev_config->bimc_hal_info,
                                   dev_config->channel_map[channel],
                                   segment-1,
                                   &cur_seg );

         if( true == cur_seg.bEnable &&
             BIMC_SEGMENT_TYPE_ADDITIVE == cur_seg.type )
         {
            HAL_bimc_EnableSlaveSegment( dev_config->bimc_hal_info,
                                         dev_config->channel_map[channel],
                                         segment-1,
                                         false );

         }
      }

      /* Program segments in reverse order. */
      for( segment = dev_config->num_segments;
           segment > 0;
           segment-- )
      {
        HAL_bimc_SetSlaveSegment( dev_config->bimc_hal_info,
                                  dev_config->channel_map[channel],
                                  segment-1, &segs[segment-1] );
      }
   }
}

//*============================================================================*/
/**
@brief
    Adjust the regions for a given channel based on a region to remove.
 
@param[inout]  dev_config
@param[inout]  input_region
@param[inout]  channel_regions
@param[in]     assume_props     assume properties of overlayed region?

@returns true if the region was found
         false otherwise
*/ 
//*============================================================================*/
bool adjust_channel
(
   icbcfg_device_config_type *dev_config,
   region_type *              input_region,
   region_type *              channel_regions,
   bool                       assume_props
)
{
   uint32 free_region, region;
   bool found = false;

   /* Find the first unallocated region, in case we need to split later. */
   for( free_region = 0; free_region < dev_config->num_segments; free_region++ )
   {
      if( 0 == channel_regions[free_region].size )
      {
         break;
      }
   }

   /* Run through the regions and check for overlap.
      * We check for:
      * 1.) Complete overlap
      * 2.) Remap start in region
      * 3.) Remap start and end in region
      * 4.) Only input_region end in region */
   for( region = 0; region < dev_config->num_segments; region++ )
   {
      /* Skip size zero regions. */
      if( 0 == channel_regions[region].size )
      {
         continue;
      }

      /* Check for a complete overlap. */
      if( input_region->base_addr <= channel_regions[region].base_addr &&
         (input_region->base_addr + input_region->size) >=
            (channel_regions[region].base_addr + channel_regions[region].size))
      {
         found = true;
         if( assume_props )
         {
            input_region->interleaved = channel_regions[region].interleaved;
         }

         /* Completely overlapped, remove this region. */
         channel_regions[region].base_addr = 0;
         channel_regions[region].size      = 0;
      }
      /* Start exists in region */
      else if( (input_region->base_addr > channel_regions[region].base_addr) &&
               input_region->base_addr < (channel_regions[region].base_addr + channel_regions[region].size) )
      {
         found = true;
         if( assume_props )
         {
            input_region->interleaved = channel_regions[region].interleaved;
         }

         /* Check to see if the end also exists in this region, and we have a free region to split to. */
         if( (input_region->base_addr + input_region->size) > channel_regions[region].base_addr &&
             (input_region->base_addr + input_region->size) < (channel_regions[region].base_addr + channel_regions[region].size) &&
             free_region < dev_config->num_segments )
         {
            channel_regions[free_region].base_addr = input_region->base_addr + input_region->size;
            channel_regions[free_region].size      = channel_regions[region].size -
                                                            (input_region->size + (input_region->base_addr - channel_regions[region].base_addr));
         }
         channel_regions[region].size = input_region->base_addr - channel_regions[region].base_addr;

         /* If we were out of free regions, flag 'best effort' */
         if( free_region >= dev_config->num_segments )
         {
            dev_config->best_effort = true;
         }
      }
      /* End exists in region, but not the start address. */
      else if( (input_region->base_addr + input_region->size) > channel_regions[region].base_addr &&
               (input_region->base_addr + input_region->size) < (channel_regions[region].base_addr + channel_regions[region].size) )
      {
         found = true;
         if( assume_props )
         {
            input_region->interleaved = channel_regions[region].interleaved;
         }

         channel_regions[region].size -= (input_region->base_addr + input_region->size) - channel_regions[region].base_addr;
         channel_regions[region].base_addr = (input_region->base_addr + input_region->size);
      }
   }

   return found;
}

//*============================================================================*/
/**
@brief
    Adjust the memory map to add the new region.
 
@param[in]  dev_config
@param[in]  remap
@param[in]  map

*/ 
//*============================================================================*/
void adjust_memory_map
(
   icbcfg_device_config_type *dev_config,
   icbcfg_remap_info_type *   remap,
   icb_mem_map_type *         map
)
{
   uint32 channel;
   region_type curr_map;

   curr_map.base_addr   = remap->src_addr;
   curr_map.size        = remap->size;
   curr_map.interleaved = true;

   /* Run through each channel and remove the existing region. */
   for( channel = 0; channel < dev_config->num_channels; channel++ )
   {
      region_type *channel_regions = map->channels[channel].regions;

      /* Add the new region to the end of the map, if we found a match.
      * Assume the same interleaving mode as the segment it left */
      if( adjust_channel( dev_config, &curr_map, channel_regions, true ) )
      {
        uint32 other_channel;

        channel_regions[LAST_REGION].base_addr   = remap->dest_addr;
        channel_regions[LAST_REGION].size        = remap->size;
        channel_regions[LAST_REGION].interleaved = curr_map.interleaved;

        /* Now, if this region isn't interleaved, we need to check to see
         * if we're going to overlap something on the other channels.
         * If we do, we need to shrink the section we're overlapping. */
        if( !curr_map.interleaved )
        {
          for( other_channel = 0; other_channel < dev_config->num_channels; other_channel++ )
          {
            region_type *other_channel_regions = map->channels[other_channel].regions;

            /* Skip if channel is the current one. */
            if( other_channel == channel )
            {
              continue;
            }

            (void)adjust_channel( dev_config, &channel_regions[LAST_REGION], other_channel_regions, false );
          }
        }
      }
   }

   compress_regions(dev_config, true, map);
}

//*============================================================================*/
/**
@brief
    Configure required remap segments for the remapping desired.
 
@param[in]  dev_config
@param[in]  remap

*/ 
//*============================================================================*/
void configure_remaps( icbcfg_device_config_type *dev_config )
{
   uint32 idx, remap;
   HAL_bimc_RemapSegmentType remaps[MAX_REMAP_SEGS];
   
   memset(remaps, 0, sizeof(remaps));

   /* Go through each remap. */
   idx = 0;
   for(remap = 0;
       remap < ARRAY_SIZE(req_remaps) && idx < ARRAY_SIZE(remaps);
       remap++ )
   {
      /* Skip any unused remap requests. */
      if( req_remaps[remap].src_addr == req_remaps[remap].dest_addr )
      {
         continue;
      }

      /* Place into HAL structure for splitting, if necessary. */
      remaps[idx].bEnable        = true;
      remaps[idx].uStartAddr     = req_remaps[remap].dest_addr;
      remaps[idx].uSegmentSize   = req_remaps[remap].size;
      remaps[idx].nSegmentOffset = (int64)req_remaps[remap].src_addr -
                                    (int64)req_remaps[remap].dest_addr;
      remaps[idx].bDeinterleave  = false;
      remaps[idx].interleave     = (HAL_bimc_InterleaveType)req_remaps[remap].interleaved;

      /* Split remap segments if necessary.
      * Follow the same base/sizing rules as with memory segments. */
      for( ; idx < ARRAY_SIZE(remaps); idx++ )
      {
         uint64 size = get_largest_valid_size(remaps[idx].uStartAddr, remaps[idx].uSegmentSize);

         /* Check if this region is aligned. */
         if( size == remaps[idx].uSegmentSize )
         {
            /* Advance the index for the next segment, and bail out. */
            idx += 1;
            break;
         }
         /* Unaligned, we need to split. */
         else
         {
            /* No remap region to split to, bail out. */
            if( (idx + 1) >= ARRAY_SIZE(remaps) )
            {
               dev_config->best_effort = true;
               break;
            }

            /* Split the remap region. */
            remaps[idx+1].bEnable        = true;
            remaps[idx+1].uStartAddr     = remaps[idx].uStartAddr + size;
            remaps[idx+1].uSegmentSize   = remaps[idx].uSegmentSize - size;
            remaps[idx+1].nSegmentOffset = remaps[idx].nSegmentOffset;
            remaps[idx+1].bDeinterleave  = remaps[idx].bDeinterleave;
            remaps[idx+1].interleave     = remaps[idx].interleave;

            remaps[idx].uSegmentSize     = size;
         }
      }
   }

   /* If we weren't able to fit all remaps, flag it. */
   if( remap < ARRAY_SIZE(req_remaps) )
   {
      dev_config->best_effort = true;
   }

   /* Program the remap segments. */
   for( idx = 0; idx < ARRAY_SIZE(remaps); idx++ )
   {
      HAL_bimc_SetRemapSegment( dev_config->bimc_hal_info, idx, &remaps[idx] );
   }
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

      ret_val = ICB_Configure_Settings(dev_config->prop_data);
   } while( false );

   return ret_val;
}

//
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
      Should only be called after any and all calls to ICB_Remap/RemapEx() are complete.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
icbcfg_error_type
ICB_Config_PostInit( const char * dev )
{
   icbcfg_error_type ret_val = ICBCFG_ERROR_INIT_FAILURE;

   do
   {
      icbcfg_device_config_type *dev_config;

      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }

      ret_val = ICB_Configure_Settings(dev_config->post_prop_data);
   } while( false );

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
   icbcfg_error_type ret_val = ICBCFG_ERROR_INIT_FAILURE;

   do 
   {
      icbcfg_device_config_type *dev_config;
      icb_mem_map_type ddr_regions;

      /* Validate config pointer. */
      if (NULL == info)
      {
         ret_val = ICBCFG_ERROR_INVALID_PARAM;
         break;
      }

      /* Fetch device configuration data. */
      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }

      /* Convert to our representation, sweeping together chip selects. */
      convert_ddr_regions(info, dev_config->num_channels, &ddr_regions);
      compress_regions(dev_config, true, &ddr_regions);
      
      /* Map it to segments and write it to the hardware. */
      map_segments(dev_config, &ddr_regions);

      ret_val = ICBCFG_SUCCESS;
   } while( false );

   return ret_val;
}

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
icbcfg_error_type ICB_RemapEx
(
   const char *            dev,
   ddr_info *              info,
   uint32                  index,
   icbcfg_remap_info_type *remap
)
{
   icbcfg_error_type          ret_val = ICBCFG_ERROR;

   do
   {
      icb_mem_map_type           ddr_regions;
      uint32                     channel, region = 0, src_regions[MAX_DDR_CHANNELS], i;
      bool                       found;
      icbcfg_device_config_type *dev_config;

      /* Validate input parameters. */
      if(NULL == dev ||
         NULL == info ||
         index >= ARRAY_SIZE(req_remaps) )
      {
         ret_val = ICBCFG_ERROR_INVALID_PARAM;
         break;
      }

      /* Fetch device configuration data. */
      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }

      /* See if this operation is supported. */
      if(!HAL_bimc_IsRemapSupported( dev_config->bimc_hal_info ))
      {
         ret_val = ICBCFG_ERROR_UNSUPPORTED;
         break;
      }

      /* Get the current DDR address space (minimal segments) */
      convert_ddr_regions(info, dev_config->num_channels, &ddr_regions);
      compress_regions(dev_config, false, &ddr_regions);

      /* Update the proper remap index the the remap the caller wants.
       * If the remap pointer is NULL or the source equals dest, clear that index.
       * This is considered to automatically have been found. It had to have been
       * previously found in order to have been stored in the first place. */
	    memset(src_regions, 0, sizeof(src_regions));
      if(NULL == remap ||
         remap->src_addr == remap->dest_addr)
      {
         memset(&req_remaps[index], 0, sizeof(icbcfg_remap_info_type));
         found = true;
      }
      /* Otherwise, copy the desired remap setting.
       * Just check if it's possible first. */
      else
      {
         /* If the source address of the segment to remap isn't in the 
          * DDR physical memory, bail out. */
         found = false;
         for(channel = 0; channel < dev_config->num_channels; channel++)
         {
            src_regions[channel] = MAX_REGIONS;
            for(region = 0; region < dev_config->num_segments; region++)
            {
               region_type *channel_regions = &ddr_regions.channels[channel].regions[region];
   
               /* Are we contained by this region? */
               if(remap->src_addr >= channel_regions->base_addr &&
                  (remap->src_addr + remap->size) <= 
                  (channel_regions->base_addr + channel_regions->size))
               {
                  /* Save the matched region index, so we can refer to it later, if necessary. */
                  src_regions[channel] = region;
                  found = true;
                  break;
               }
            }
         }
         if(!found)
         {
            break;
         }

         /* Save to the index specified. */
         req_remaps[index] = *remap;
      }
   
      /* Go through our list of remaps and apply them to the system memory map. */
      for(i = 0; i < MAX_REMAP_SEGS; i++)
      {
         icbcfg_remap_info_type *req_remap = &req_remaps[i];

         /* Skip any remap without anything to do. */
         if(req_remap->src_addr == req_remap->dest_addr)
         {
            continue;
         }

         /* Check if the system memory map will support the
          * destination address for the remapped region. */
         found = false;
         for(channel = 0; channel < dev_config->num_channels && !found; channel++)
         {
            /* Only check the regions in this channel if it also has a matching
             * region in the DDR setup. */
            if(src_regions[channel] >= MAX_REGIONS)
            {
               continue;
            }

            for(region = 0; region < dev_config->num_segments; region++)
            {
               region_type *channel_regions = &ddr_regions.channels[channel].regions[region];
   
               /* Are we contained by this region? */
               if(req_remap->dest_addr >= channel_regions->base_addr &&
                  (req_remap->dest_addr + req_remap->size) <= 
                  (channel_regions->base_addr + channel_regions->size) )
               {
                  found = true;
                  break;
               }
            }
         }
   
         /* If we don't find an existing region, we must adjust the system memory map. */
         if(!found)
         {
            adjust_memory_map(dev_config, req_remap, &ddr_regions);
         }
      }
   
      /* Rewrite the memory map and update remapped segments. */
      compress_regions(dev_config, true, &ddr_regions);
      map_segments(dev_config, &ddr_regions);
      configure_remaps(dev_config);

      ret_val = ICBCFG_SUCCESS;
   } while(false);

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
   return ICB_RemapEx(dev, info, 0, remap);
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

   do
   {
      icbcfg_device_config_type *dev_config;

      /* Validate config pointers. */
      if (NULL == dev || NULL == info)
      {
         ret_val = ICBCFG_ERROR_INVALID_PARAM;
         break;
      }

      /* Fetch device configuration data. */
      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }

      /* Get the system memory map, holes and all. */
      get_system_memory_map(dev_config, false, info);
      compress_regions(dev_config, true, info);

      ret_val = ICBCFG_SUCCESS;
   } while( false );

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
   icbcfg_error_type ret_val = ICBCFG_ERROR_INIT_FAILURE;
   uint32 seg_idx;

   do 
   {
      icbcfg_device_config_type *dev_config;

      /* Validate config pointer. */
      if(NULL == dev)
      {
         ret_val = ICBCFG_ERROR_INVALID_PARAM;
         break;
      }

      /* Fetch device configuration data. */
      if(!get_device_configuration(dev, &dev_config))
      {
         break;
      }
      ret_val = ICBCFG_SUCCESS;

      /* Make sure we have unmap information. */
      if(NULL == dev_config->unmap)
      {
         break;
      }

      /* Write the segment configuration to disable. */
      for(seg_idx = 0; seg_idx < dev_config->unmap->num_segments; seg_idx++)
      {
         HAL_bimc_SetSlaveSegment(dev_config->bimc_hal_info,
                                  dev_config->unmap->slave_idx,
                                  dev_config->unmap->segments[seg_idx].segment_idx,
                                  &dev_config->unmap->segments[seg_idx].segment);
      }
   }
   while( false );

   return ret_val;
}

/* vim: set ts=3 sts=3 sw=3 et :*/ 
