/*============================================================================

FILE:      rpm_mpu.h

DESCRIPTION: RPM MPU type and function declarations

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

      Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
               All Rights Reserved.
         QUALCOMM Proprietary and Confidential

$Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/inc/rpm_mpu.h#1 $
$Date: 2016/11/03 $

============================================================================*/

#ifndef RPM_MPU_H
#define RPM_MPU_H


#define RPM_MPU_NUM_SUB_RGN     8

/*==============================================================================
**
**      Type Definitions
**
**==============================================================================
*/

typedef enum
{
    RPM_MPU_RGN_CODE_RAM = 0,
    RPM_MPU_RGN_RO_CODE_RAM,
    RPM_MPU_RGN_CODE_RAM_HEAP,
    RPM_MPU_RGN_CODE_RAM_HEAP_BORDER,
    RPM_MPU_RGN_DATA_RAM,
    RPM_MPU_RGN_STACK_OVERFLOW,

    RPM_MPU_RGN_COUNT,
} rpm_mpu_rgn_num_t;

typedef enum
{
    RPM_MPU_DISABLE        = 0,
    RPM_MPU_ENABLE         = 1, /* enable MPU */
} rpm_mpu_ena_t;

typedef enum
{
    RPM_MPU_DISABLE_HF_NMI = 0,
    RPM_MPU_ENABLE_HF_NMI  = 1, /* enable the MPU during the HardFault handler and NMI handler */
} rpm_mpu_hf_nmi_ena_t;

typedef enum
{
    RPM_MPU_DISABLE_BG_RGN = 0,
    RPM_MPU_ENABLE_BG_RGN  = 1, /* enable background region (region -1). If this bit is not set,
                                   any access not covered by any enabled region will cause a fault */
} rpm_mpu_priv_def_ena_t;

/*
 * SCS.MPU.RegionAttrSize[0] SZ_ENABLE
 */
typedef enum
{
    RPM_MPU_RGN_DISNABLE       = 0,
    RPM_MPU_RGN_ENABLE         = 1,
} rpm_mpu_rgn_ena_t;

/*
 * SCS.MPU.RegionAttrSize[5:1] REGION_SIZE
 */
typedef enum
{
    RPM_MPU_RGN_SIZE_RESERVED1 =  0,
    RPM_MPU_RGN_SIZE_RESERVED2 =  1,
    RPM_MPU_RGN_SIZE_RESERVED3 =  2,
    RPM_MPU_RGN_SIZE_RESERVED4 =  3,
    RPM_MPU_RGN_SIZE_32B       =  4,
    RPM_MPU_RGN_SIZE_64B       =  5,
    RPM_MPU_RGN_SIZE_128B      =  6,
    RPM_MPU_RGN_SIZE_256B      =  7,
    RPM_MPU_RGN_SIZE_512B      =  8,
    RPM_MPU_RGN_SIZE_1KB       =  9,
    RPM_MPU_RGN_SIZE_2KB       = 10,
    RPM_MPU_RGN_SIZE_4KB       = 11,
    RPM_MPU_RGN_SIZE_8KB       = 12,
    RPM_MPU_RGN_SIZE_16KB      = 13,
    RPM_MPU_RGN_SIZE_32KB      = 14,
    RPM_MPU_RGN_SIZE_64KB      = 15,
    RPM_MPU_RGN_SIZE_128KB     = 16,
    RPM_MPU_RGN_SIZE_256KB     = 17,
    RPM_MPU_RGN_SIZE_512KB     = 18,
    RPM_MPU_RGN_SIZE_1MB       = 19,
    RPM_MPU_RGN_SIZE_2MB       = 20,
    RPM_MPU_RGN_SIZE_4MB       = 21,
    RPM_MPU_RGN_SIZE_8MB       = 22,
    RPM_MPU_RGN_SIZE_16MB      = 23,
    RPM_MPU_RGN_SIZE_32MB      = 24,
    RPM_MPU_RGN_SIZE_64MB      = 25,
    RPM_MPU_RGN_SIZE_128MB     = 26,
    RPM_MPU_RGN_SIZE_256MB     = 27,
    RPM_MPU_RGN_SIZE_512MB     = 28,
    RPM_MPU_RGN_SIZE_1GB       = 29,
    RPM_MPU_RGN_SIZE_2GB       = 30,
    RPM_MPU_RGN_SIZE_4GB       = 31,
} rpm_mpu_rgn_size_t;

/*
 * SCS.MPU.RegionAttrSize[15:8] SRD (Sub-Region Disable)
 */
typedef enum
{
    RPM_MPU_RGN_SREN           = 0,    /* Enable all Sub-Regions */
    RPM_MPU_RGN_SRD0           = 1<<0, /* Disable Sub-Region 0 (lowest address) */
    RPM_MPU_RGN_SRD1           = 1<<1, /* Disable Sub-Region 1 */
    RPM_MPU_RGN_SRD2           = 1<<2, /* Disable Sub-Region 2 */
    RPM_MPU_RGN_SRD3           = 1<<3, /* Disable Sub-Region 3 */
    RPM_MPU_RGN_SRD4           = 1<<4, /* Disable Sub-Region 4 */
    RPM_MPU_RGN_SRD5           = 1<<5, /* Disable Sub-Region 5 */
    RPM_MPU_RGN_SRD6           = 1<<6, /* Disable Sub-Region 6 */
    RPM_MPU_RGN_SRD7           = 1<<7, /* Disable Sub-Region 7 (highest address) */
} rpm_mpu_rgn_srd_t;

/*
 * SCS.MPU.RegionAttrSize[18:16] S/C/B (Shareable/Cacheable/Bufferable)
 */
typedef enum
{
    RPM_MPU_RGN_ATTR_NO_SCB    = 0,
    RPM_MPU_RGN_ATTR_B         = 1, /*                         Bufferable */
    RPM_MPU_RGN_ATTR_C         = 2, /*             Cacheable              */
    RPM_MPU_RGN_ATTR_CB        = 3, /*             Cacheable & Bufferable */
    RPM_MPU_RGN_ATTR_S         = 4, /* Shareable                          */
    RPM_MPU_RGN_ATTR_SB        = 5, /* Shareable             & Bufferable */
    RPM_MPU_RGN_ATTR_SC        = 6, /* Shareable & Cacheable              */
    RPM_MPU_RGN_ATTR_SCB       = 7, /* Shareable & Cacheable & Bufferable */
} rpm_mpu_rgn_attr_t;

/*
 * SCS.MPU.RegionAttrSize[26:24] AP (Access Permission)
 */
typedef enum
{
    RPM_MPU_RGN_AP_NO_ACCESS   = 0,
    RPM_MPU_RGN_AP_RW          = 1,
    RPM_MPU_RGN_AP_RO          = 5,
} rpm_mpu_rgn_ap_t;

/*
 * SCS.MPU.RegionAttrSize[28] XN (Execute-Never)
 */
typedef enum
{
    RPM_MPU_RGN_EXECUTABLE     = 0,
    RPM_MPU_RGN_NON_EXECUTABLE = 1,
} rpm_mpu_rgn_xn_t;

typedef struct
{
    bool               enable;
    rpm_mpu_rgn_size_t size;
    uint8_t            sub_rgn_disable;
    rpm_mpu_rgn_ap_t   permission;
    bool               execute_disable;
} rpm_mpu_rgn_attr_size_t;

typedef struct
{
    unsigned base_addr; /* NOTE: region base address must be a multiple of its size */
    rpm_mpu_rgn_num_t  rgn_id;
    rpm_mpu_rgn_attr_size_t attr_size;
} rpm_mpu_rgn_cfg_t;


/*==============================================================================
**
**      Function Prototypes
**
**==============================================================================
*/

/*==============================================================================
**
** rpm_mpu_enable
**
** enables/disables MPU.
**
**     enable - TRUE to enable MPU,
**              FALSE to disable MPU
**
**/
void rpm_mpu_enable(bool enable);

/*==============================================================================
**
** rpm_mpu_enable_region
**
** enables/disables memory protection for the specified region.
**
**     region - an MPU region name enum
**     enable - TRUE to enable protection for the region,
**              FALSE to disable
**
**/
void rpm_mpu_enable_region(rpm_mpu_rgn_num_t region, bool enable);

/*==============================================================================
**
** rpm_mpu_init
**
** initializes MPU and enables it.
**
**/
void rpm_mpu_init(void);

#endif /* RPM_MPU_H */

