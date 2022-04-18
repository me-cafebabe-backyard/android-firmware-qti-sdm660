#ifndef __SMMU_TYPES_H__
#define __SMMU_TYPES_H__
/*==============================================================================
@file SMMUTypes.h


        Copyright (c) 2008,2010,2014 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/19/15   amo     Created

=============================================================================*/
/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "Uefi.h"
#include "com_dtypes.h"

/*----------------------------------------------------------------------------*/

/* Client corresponds to SID */
typedef enum
{
    SMMU_CLIENT_USB0                 =0,
    SMMU_CLIENT_USB1,
    SMMU_CLIENT_USB2,
    SMMU_CLIENT_USB3,
    SMMU_CLIENT_SDCC0,
    SMMU_CLIENT_SDCC1,
    SMMU_CLIENT_SDCC2,
    SMMU_CLIENT_SDCC3,
    SMMU_NUM_CLIENTS
}SMMUClientID_t;

// error codes
typedef enum
{
    SMMU_ESUCCESS = 0,
    SMMU_EINVAL,
    SMMU_EBADADDR,
    SMMU_ERANGE,
    SMMU_EUNEXPECTED,
    SMMU_ENOTALLOWED,
    SMMU_EFAILURE
}SMMUError_t;

// cache property
typedef enum
{

    // device non-gathering, non-reordering, no early write acknowledgement
    SMMU_CACHE_DEVICE_nGnRnE       = 0,   // b0000
    SMMU_CACHE_DEVICE_nGnRE        = 1,   // b0001
    SMMU_CACHE_DEVICE_nGRE         = 2,   // b0010
    SMMU_CACHE_DEVICE_GRE          = 3,   // b0011
    // outer non-cacheable, inner non-cacheable
    SMMU_CACHE_OUTER_NC_INNER_NC   = 5,   // b0101
    // outer non-cacheable, inner write-through
    SMMU_CACHE_OUTER_NC_INNER_WT   = 6,   // b0110
    // outer non-cacheable, inner writeback
    SMMU_CACHE_OUTER_NC_INNER_WB   = 7,   // b0111
    SMMU_CACHE_OUTER_WT_INNER_NC   = 9,   // b1001
    SMMU_CACHE_OUTER_WT_INNER_WT   = 10,  // b1010
    SMMU_CACHE_OUTER_WT_INNER_WB   = 11,  // b1011
    SMMU_CACHE_OUTER_WB_INNER_NC   = 13,  // b1101
    SMMU_CACHE_OUTER_WB_INNER_WT   = 14,  // b1110
    SMMU_CACHE_OUTER_WB_INNER_WB   = 15,  // b1111
    // use stage 1 or outer/inner WB
    SMMU_CACHE_DEFAULT             = 15,  

    SMMU_CACHE_FORCE_ENUM_32_BIT   = 0x7FFFFFFF  /* Force to 32 bit enum */
} 
SMMUCache_t;

// sharability
typedef enum

{
    SMMU_SHARE_NONE         = 0,
    SMMU_SHARE_OUTER        = 2,
    SMMU_SHARE_INNER        = 3,
    // use stage 1 or non-cached 
    SMMU_SHARE_DEFAULT      = 0,

    SMMU_SHARE_FORCE_ENUM_32_BIT   = 0x7FFFFFFF   /* Force to 32 bit enum */
} 
SMMUShare_t;

// permission
typedef enum
{
    SMMU_PERM_X      = 0x1,
    SMMU_PERM_W      = 0x2,
    SMMU_PERM_R      = 0x4,
    SMMU_PERM_RWX    = SMMU_PERM_R | SMMU_PERM_W | SMMU_PERM_X,
    SMMU_PERM_RW     = SMMU_PERM_R | SMMU_PERM_W,
    SMMU_PERM_RX     = SMMU_PERM_R | SMMU_PERM_X,
    SMMU_PERM_WX     = SMMU_PERM_W | SMMU_PERM_X,
    // user stage 1 or RWX
    SMMU_PERM_DEFAULT= SMMU_PERM_RWX,

    SMMU_PERM_FORCE_ENUM_32_BIT = 0x7FFFFFFF  /* Force to 32 bit enum */
}
SMMUPerm_t;

typedef enum
{
    SMMU_UNMAPPED,
    SMMU_MAPPED,
    SMMU_PARTIAL_MAPPED,
    SMMU_INVALID_MAP_STATUS
}
SMMUMapStatus_t;

// memory map attributes
typedef struct
{
    uint64_t     size;
    uint64_t     inputAddr;
    uint64_t     outputAddr;
    SMMUPerm_t     perm;
    SMMUShare_t    shareAttr;
    SMMUCache_t    cacheAttr;
} 
SMMUMapAttr_t;

typedef struct
{
    uint32_t    inputBitSize;
    uint32_t    outputBitSize;
}
SMMUPageTableAttr_t;



typedef void(*SMMU_Init_func_ptr)(void);

typedef SMMUError_t(*SMMU_Map_func_ptr)(SMMUClientID_t client, const SMMUMapAttr_t *pMapAttrvar);

typedef SMMUError_t(*SMMU_Unmap_func_ptr)(SMMUClientID_t client, uint64_t inputAddrvar, 
      uint64_t sizevar);


typedef struct SMMU_fptable_s SMMU_fptable_t;
struct SMMU_fptable_s {
    SMMU_Init_func_ptr SMMU_Init_func;
    SMMU_Map_func_ptr SMMU_Map_func;
    SMMU_Unmap_func_ptr SMMU_Unmap_func;
};




#endif /* __SMMU_TYPES_H__ */
