#ifndef DDR_COMMON_H
#define DDR_COMMON_H

#define DDR_COMMON_H_MAJOR  04
#define DDR_COMMON_H_MINOR  00

/**
  @file ddr_common.h
  @brief
  Common definitions used by DDR drivers on all targets.
*/
/*=============================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      The ddr_mainpage.dox file contains all file/group descriptions that
      are in the output PDF generated using Doxygen and Latex. To edit or 
      update any of the file/group text in the PDF, edit the 
      ddr_mainpage.dox file or contact Tech Pubs.
=============================================================================*/
/*=============================================================================
  Copyright (c) 2015 Qualcomm Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Include/api/boot/ddr_common.h#4 $ 
$DateTime: 2016/12/19 10:54:29 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/18/14   tw      added support for highest bank bit information
12/01/13   dp      Initial revision.
=============================================================================*/

 #include "comdef.h"
 
// Add a definition of 'inline' to work around the QNPL comdef.h, which mysteriously omits a definition // of inline.
#if (! defined inline)
#define inline __inline
#endif /* (! defined inline) */



/** DDR interfaces. */
typedef enum
{
  DDR_CH_NONE   = 0x0,
  DDR_CH0       = 0x1,
  DDR_CH1       = 0x2,
  DDR_CH_BOTH   = 0x3,
  DDR_CH_MAX    = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_CHANNEL;

/** DDR chip selects. */
typedef enum
{
  DDR_CS_NONE        = 0,                 /**< 0b00 -- no chip select. */
  DDR_CS0            = 1,                 /**< 0b01 -- chip select 0 only. */
  DDR_CS1            = 2,                 /**< 0x10 -- chip select 1 only. */
  DDR_CS_BOTH        = 3,                 /**< 0x11 -- Both chip selects. */
  DDR_CHIPSELECT_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_CHIPSELECT;

/** DDR status. */
typedef enum
{
  DDR_STATUS_UNAVAILABLE,               /**< DDR is unavailable on this chip select. */
  DDR_STATUS_ACTIVE,                    /**< Active mode. */
  DDR_STATUS_SELF_REFRESH,              /**< Self Refresh mode. */
  DDR_STATUS_STALL,                     /**< Stalled mode. */
  DDR_STATUS_DPD,                       /**< Deep Power Down mode. */
  DDR_STATUS_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_SNS_STATUS;

/** DDR Status Cause */
typedef enum
{
  DDR_STATUS_REASON_NONE,
  DDR_STATUS_REASON_SELF_REFRESH,
  DDR_STATUS_REASON_DMM,
  DDR_STATUS_REASON_XO_SHUTDOWN,
}DDR_STATUS_REASON;


/** SDRAM interfaces. */
typedef enum
{
  SDRAM_INTERFACE_NONE = 0x0,        /**< None */
  SDRAM_INTERFACE_0    = 0x1,        /**< Interface0 */
  SDRAM_INTERFACE_1    = 0x2,        /**< Interface1 */
  SDRAM_INTERFACE_BOTH = 0x3,        /**< Interface0 && Interface1 */
  SDRAM_INTERFACE_MAX  = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} SDRAM_INTERFACE;

/** SDRAM chip selects. */
typedef enum
{
  SDRAM_CS_NONE = 0,                 /**< 0b00 -- no chip select. */
  SDRAM_CS0     = 1,                 /**< 0b01 -- chip select 0 only. */
  SDRAM_CS1     = 2,                 /**< 0x10 -- chip select 1 only. */
  SDRAM_BOTH    = 3,                 /**< 0x11 -- Both chip selects. */
  SDRAM_CHIPSELECT_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} SDRAM_CHIPSELECT;

/** SDRAM status. */
typedef enum
{
  DDR_UNAVAILABLE,               /**< SDRAM is unavailable on this chip select. */
  DDR_ACTIVE,                    /**< Active mode. */
  DDR_SELF_REFRESH,              /**< Self Refresh mode. */
  DDR_STALL,                     /**< Stalled mode. */
  DDR_DPD,                       /**< Deep Power Down mode. */
  SDARM_STATUS_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} SDRAM_STATUS;

/** SDRAM Status Cause */
typedef enum
{
  DDR_REASON_NONE,
  DDR_REASON_SELF_REFRESH,
  DDR_REASON_DMM,
  DDR_REASON_XO_SHUTDOWN,
}SDRAM_STATUS_REASON;

/** DDR types. */
typedef enum
{
  DDR_TYPE_LPDDR1 = 0,           /**< Low power DDR1. */
  DDR_TYPE_LPDDR2 = 2,       /**< Low power DDR2  set to 2 for compatibility*/
  DDR_TYPE_PCDDR2 = 3,           /**< Personal computer DDR2. */
  DDR_TYPE_PCDDR3 = 4,           /**< Personal computer DDR3. */
  
  DDR_TYPE_LPDDR3 = 5,           /**< Low power DDR3. */  
  DDR_TYPE_LPDDR4 = 6,           /**< Low power DDR4. */
  DDR_TYPE_LPDDR4X = 7,          /**< Low power DDR4X (with lower IO voltage). */

  DDR_TYPE_RESERVED = 8,         /**< Reserved for future use. */
  DDR_TYPE_UNUSED = 0x7FFFFFFF  /**< For compatibility with deviceprogrammer(features not using DDR). */
} DDR_TYPE;

/** DDR manufacturers. */
typedef enum
{
  RESERVED_0,                        /**< Reserved for future use. */
  SAMSUNG,                           /**< Samsung. */
  QIMONDA,                           /**< Qimonda. */
  ELPIDA,                            /**< Elpida Memory, Inc. */
  ETRON,                             /**< Etron Technology, Inc. */
  NANYA,                             /**< Nanya Technology Corporation. */
  HYNIX,                             /**< Hynix Semiconductor Inc. */
  MOSEL,                             /**< Mosel Vitelic Corporation. */
  WINBOND,                           /**< Winbond Electronics Corp. */
  ESMT,                              /**< Elite Semiconductor Memory Technology Inc. */
  RESERVED_1,                        /**< Reserved for future use. */
  SPANSION,                          /**< Spansion Inc. */
  SST,                               /**< Silicon Storage Technology, Inc. */
  ZMOS,                              /**< ZMOS Technology, Inc. */
  INTEL,                             /**< Intel Corporation. */
  NUMONYX = 254,                     /**< Numonyx, acquired by Micron Technology, Inc. */
  MICRON = 255,                      /**< Micron Technology, Inc. */
  DDR_MANUFACTURES_MAX = 0x7FFFFFFF  /**< Forces the enumerator to 32 bits. */
} DDR_MANUFACTURES;

/** DDR interleave type */
typedef enum
{
  SDRAM_CS0_INTERLEAVE = 1,
  SDRAM_CS1_INTERLEAVE = 2,
  SDRAM_CS0_CS1_INTERLEAVE = 3,
} ddr_interleave_type;

typedef enum                             
{                                        
  DDR_CS0_INTERLEAVE = 1,                
  DDR_CS1_INTERLEAVE = 2,                
  DDR_CS0_CS1_INTERLEAVE = 3,            
} ddr_sns_interleave_type;      


/** @brief DDR states of all interfaces and chip selects. */
typedef struct
{
  SDRAM_STATUS sdram0_cs0;    /**< SDRAM status of Interface0 and chip select 0. */
  SDRAM_STATUS sdram0_cs1;    /**< SDRAM status of Interface0 and chip select 1. */
  SDRAM_STATUS sdram1_cs0;    /**< SDRAM status of Interface1 and chip select 0. */
  SDRAM_STATUS sdram1_cs1;    /**< SDRAM status of Interface1 and chip select 1. */

  uint32 clk_speed;           /**< Clock speed. */
  uint32 vddmx_voltage;       /**< VDDMX level in microvolts. */
  uint32 vddcx_voltage;       /**< VDDCX level in microvolts. */
} ddr_interface_state;

/** @brief DDR sizes and start addresses of all interfaces and chip selects. */
typedef struct
{
  uint32 sdram0_cs0;       /**< DDR size of Interface0 and chip select 0. */
  uint32 sdram0_cs1;       /**< DDR size of Interface0 and chip select 1. */
  uint32 sdram1_cs0;       /**< DDR size of Interface1 and chip select 0. */
  uint32 sdram1_cs1;       /**< DDR size of Interface0 and chip select 1. */
  
  uint64 sdram0_cs0_addr;  /**< DDR start address of Interface0 and chip select 0. */
  uint64 sdram0_cs1_addr;  /**< DDR start address of Interface0 and chip select 1. */
  uint64 sdram1_cs0_addr;  /**< DDR start address of Interface1 and chip select 0. */
  uint64 sdram1_cs1_addr;  /**< DDR start address of Interface1 and chip select 1. */
  uint32 highest_bank_bit; /**< DDR Highest bank bit based on detected topology */
} ddr_size_info;

/** @brief ddr information that are relevent to clients outside of ddr driver */
typedef struct
{
  ddr_size_info ddr_size; /**< DDR size and address configuration */  
  uint32 interleaved_memory; /**< Return whether the ddr is interleaved or not. */
  DDR_TYPE ddr_type;  /**< Return ddr type enum. */ 
} ddr_info;

typedef struct
{
  uint32 num_partitions;   /**< DDR size of Interface0/CS0 */
  uint64 sdram_addr;       /**< DDR start address of Interface0/CS0 */
} ddr_partitions;

typedef struct
{
  ddr_partitions sdram0_cs0; /**< Partition information for Interface 0 CS0 */
  ddr_partitions sdram0_cs1; /**< Partition information for Interface 0 CS1 */
  ddr_partitions sdram1_cs0; /**< Partition information for Interface 1 CS0 */
  ddr_partitions sdram1_cs1; /**< Partition information for Interface 1 CS1 */
} ddr_size_partition;



/** @brief DDR states of all interfaces and chip selects. */
typedef struct
{
  SDRAM_STATUS ddr0_cs0;    /**< SDRAM status of Interface0 and chip select 0. */
  SDRAM_STATUS ddr0_cs1;    /**< SDRAM status of Interface0 and chip select 1. */
  SDRAM_STATUS ddr1_cs0;    /**< SDRAM status of Interface1 and chip select 0. */
  SDRAM_STATUS ddr1_cs1;    /**< SDRAM status of Interface1 and chip select 1. */

  uint32 clk_speed;           /**< Clock speed. */
  uint32 vddmx_voltage;       /**< VDDMX level in microvolts. */
  uint32 vddcx_voltage;       /**< VDDCX level in microvolts. */
} ddr_sns_interface_state;

/** @brief DDR sizes and start addresses of all interfaces and chip selects. */
typedef struct
{
  uint32 ddr0_cs0_mb;    /**< DDR size in MBytes of Interface0 and chip select 0. */
  uint32 ddr0_cs1_mb;    /**< DDR size in MBytes of Interface0 and chip select 1. */
  uint32 ddr1_cs0_mb;    /**< DDR size in MBytes of Interface1 and chip select 0. */
  uint32 ddr1_cs1_mb;    /**< DDR size in MBytes of Interface0 and chip select 1. */

  uint8 ddr0_cs0_io_width;    /**< DDR Device IO Width of Interface0 and chip select 0. */
  uint8 ddr0_cs1_io_width;    /**< DDR Device IO Width of Interface0 and chip select 1. */
  uint8 ddr1_cs0_io_width;    /**< DDR Device IO Width of Interface1 and chip select 0. */
  uint8 ddr1_cs1_io_width;    /**< DDR Device IO Width of Interface0 and chip select 1. */
  
  uint64 ddr0_cs0_addr;  /**< DDR start address of Interface0 and chip select 0. */
  uint64 ddr0_cs1_addr;  /**< DDR start address of Interface0 and chip select 1. */
  uint64 ddr1_cs0_addr;  /**< DDR start address of Interface1 and chip select 0. */
  uint64 ddr1_cs1_addr;  /**< DDR start address of Interface1 and chip select 1. */

  uint64 ddr0_cs0_remapped_addr;  /**< DDR remapped start address of Interface0 and chip select 0. */
  uint64 ddr0_cs1_remapped_addr;  /**< DDR remapped start address of Interface0 and chip select 1. */
  uint64 ddr1_cs0_remapped_addr;  /**< DDR remapped start address of Interface1 and chip select 0. */
  uint64 ddr1_cs1_remapped_addr;  /**< DDR remapped start address of Interface1 and chip select 1. */
  
  uint32 highest_bank_bit; /**< DDR Highest bank bit based on detected topology */
} ddr_sns_size_info;

typedef struct
{
  uint32 num_partitions;   /**< DDR size of Interface0/CS0 */
  uint64 ddr_addr;       /**< DDR start address of Interface0/CS0 */
} ddr_sns_partitions;

typedef struct
{
  ddr_partitions ddr0_cs0; /**< Partition information for Interface 0 CS0 */
  ddr_partitions ddr0_cs1; /**< Partition information for Interface 0 CS1 */
  ddr_partitions ddr1_cs0; /**< Partition information for Interface 1 CS0 */
  ddr_partitions ddr1_cs1; /**< Partition information for Interface 1 CS1 */
} ddr_sns_size_partition;


/** @} */ /* end_addtogroup ddr_data_structures */

#endif  /* DDR_COMMON_H */
