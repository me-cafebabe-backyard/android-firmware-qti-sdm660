#ifndef ACCESS_CONTROL_HYP_H
#define ACCESS_CONTROL_HYP_H
/*==============================================================================
  @file ACSmmu.h
  Public interface for Access Control SMMU specific functionality

  Copyright (c) 2014 Qualcomm Technologies Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc. Confidential and Proprietary
  ==============================================================================*/

/*==============================================================================

  EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/accesscontrol/api/AccessControlHyp.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $


  when       who      what, where, why
  --------   ---      ------------------------------------
  09/02/14   ps       Created

  ==============================================================================*/
/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include <comdef.h>
#include "ACCommon.h"
#include "tz_syscall_pub.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
    
/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

typedef enum
{
    AC_CLEAR_MEMORY_ON_ASSIGN                 = 0,
    AC_CLEAR_MEMORY_ON_UNASSIGN               = 1,
    AC_CLEAR_MEMORY_ONLY_ON_SECURE_DEVICE      = 2,
    AC_CLEAR_MEMORY_LAST,
    AC_CLEAR_MEMORY_UNSUPPORTED = 0x7FFFFFFF,
}ACClearMemoryFlag;

typedef enum
{
    // device non-gathering, non-reordering, no early write acknowledgement
    AC_CACHE_DEVICE_nGnRnE       = 0,   // b0000
    AC_CACHE_DEVICE_nGnRE        = 1,   // b0001
    AC_CACHE_DEVICE_nGRE         = 2,   // b0010
    AC_CACHE_DEVICE_GRE          = 3,   // b0011
    // outer non-cacheable, inner non-cacheable
    AC_CACHE_OUTER_NC_INNER_NC   = 5,   // b0101
    // outer non-cacheable, inner write-through
    AC_CACHE_OUTER_NC_INNER_WT   = 6,   // b0110
    // outer non-cacheable, inner writeback
    AC_CACHE_OUTER_NC_INNER_WB   = 7,   // b0111
    AC_CACHE_OUTER_WT_INNER_NC   = 9,   // b1001
    AC_CACHE_OUTER_WT_INNER_WT   = 10,  // b1010
    AC_CACHE_OUTER_WT_INNER_WB   = 11,  // b1011
    AC_CACHE_OUTER_WB_INNER_NC   = 13,  // b1101
    AC_CACHE_OUTER_WB_INNER_WT   = 14,  // b1110
    AC_CACHE_OUTER_WB_INNER_WB   = 15,  // b1111
    // use stage 1 or outer/inner WB
    AC_MEMORY_ATTR_DEFAULT             = 15, 

    AC_MEMORY_ATTR_SUPPORTED_MAX,
    AC_MEMORY_ATTR_UNSUPPORTED = 0x7FFFFFFF, // force to 32-bit enum
} ACMemoryAttributesType;


typedef enum
{

    AC_MEMORY_SHAREABLE_NONE         = 0,
    AC_MEMORY_SHAREABLE_OUTER        = 2,
    AC_MEMORY_SHAREABLE_INNER        = 3,
    // use stage 1 or non-cached 
    AC_MEMORY_SHAREABLE_DEFAULT      = 0,
    AC_MEMORY_SHAREABLE_SUPPORTED_MAX,
    AC_MEMORY_SHAREABLE_SIZE = 0x7FFFFFFF,  // force to 32-bit enum

} ACMemoryShareabilityType;

typedef struct
{
    bool32 bClearMemoryOnlyOnSecuredDevice; /* Clear Memory only on Secured device */
    bool32 bClearMemoryOnAssign; /* When memory is given from HLOS/AC_VM_HLOS_UNMAPPED, clear it */
    bool32 bClearMemoryOnUnassign; /* When memory is given to HLOS/AC_VM_HLOS_UNMAPPED, clear it */
}ACVirtualMachineConfigType;


// mapping attributes for populating the Block/Page descriptor
typedef struct
{
    uint64                        uSize; /* In Bytes */
    uint64                        uInputAddr;
    uint64                        uOutputAddr;
    uint32                        uPermissions; 
    ACMemoryShareabilityType      eShareability;
    ACMemoryAttributesType        eMemAttributes;
} ACMapAttributesType;

typedef struct
{
    uint64 uSize; /* In Bytes */
    uint64 uInputAddr;
}ACUnmapAttributesType;


typedef struct 
{
    ACVirtualMachineId eDestinationVm; 
    uint32 uPermissions; 
    ACMemoryShareabilityType eShareability; 
    ACMemoryAttributesType eMemAttributes;
    uint64 ctx;
    uint32 uCtxSize;
}ACDestinationVmAndMemAttrType;

typedef struct
{
    ACMemoryShareabilityType eShareability; 
    ACMemoryAttributesType eMemAttributes;
}ACDestinationAttrType;

typedef struct 
{
    uint64 uSize; /* In Bytes */
    uint64 uInputAddr;
    uint64 uOutputAddr;
}ACMapAddrType;


/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
/**
  @brief ACStaticConfigInit - Initializes AC SMMU static configs 
  @return AC_SUCCESS on success, failure values on Failure
  */
int ACStaticConfigInit(void);

/**
  @brief ACConfigureVirtualMachine: Configure properties of a Virtual Machine 
  @param ACVirtualMachineId: Virtual Machine Id
  @param pConfig: VM configuration
  */
int ACConfigureVirtualMachine(ACVirtualMachineId eVm, 
        ACVirtualMachineConfigType *pConfig);

/**
  @brief ACIsMemoryRangeInVm: Checks if the given mapping is owned by the given VM
  This is to be used with VM limited to SMMU/MMU type not xPU type
  @param uAddress: Memory start address
  @param uSize: Size of the mapping to be checked
  @param eVm: VM to be checked
  @return TRUE if mapping is present, FALSE values on Failure
*/
  bool32 ACIsMemoryRangeInVm(uint64 uAddress,
  uint32 uSize,
  ACVirtualMachineId eVm);


/**
@brief ACMapIORange: Maps IO region in a VMs pagetable 
@param eVm: VM enum to map the IO region VM_ALL is not supported for this API
@param pAttr: Pointer to an array of structures of type 
ACMapAttributesType
@param uNumMappings: Number of mappings pointed by pAttr
@return AC_SUCCESS on success, failure values on Failure
*/
int ACMapIoRange(ACVirtualMachineId eVm, 
        const ACMapAttributesType *pAttr,
        uint32 uNumMappings);

/**
  @brief ACUnmapIORange: Unmaps IO region from a VMs pagetable 
  @param eVm: VM enum to unmap the IO region from
  @param puAddress: Pointer to an array of addresseses to be unmapped
  @param uNumAddresses: Number of addresses pointed by puAddress
  @return AC_SUCCESS on success, failure values on Failure
  */
int ACUnmapIoRange(ACVirtualMachineId eVm, 
        const ACUnmapAttributesType *pUnmapAttributes,
        uint32 uNumMappings);



/**
  IMPORTANT: This is to be used only by HYPX
  @brief ACHlosMapMemoryRange: Unmaps from HLOS & maps to HLOS as RO or RW
  @param pMappings: Pointer to an array of structures of type 
  ACMapAddrType
  @param uNumMappings: Number of mappings pointed by pMappings
  @param uPerm: The permission for the mappings
  @return AC_SUCCESS on success, failure values on Failure
  */
AC_ERROR_CODE ACHlosMapMemoryRange(ACMapAddrType *pMappings,
        uint32 uNumMappings,
        uint32 uPerm);

/**
  @brief ACMapMemoryRangeExt: Maps memory range in a pagetable. This API is used when 
  different permissions nneds to be given to different DestinationVMs
  VM_ALL is not supported
  @param eDestinationVmidList: List of all the destination VMIDs
  @param uNumDestinationVmid: Number of VMIDs in the destination lists
  @param eSourceVmidList: List of all the source VMIDs
  @param uNumSourceVmid: Number of VMIDs in the source lists
  @param pAttr: Pointer to an array of structures of type 
  ACMapAttributesType
  @param uNumMappings: Number of mappings pointed by pAttr
  @return AC_SUCCESS on success, failure values on Failure
  */
int ACMapMemoryRangeExt(ACDestinationVmAndMemAttrType *pACDestinationVmAndMemAttrList, 
        uint32 uNumDestinationVmAndMemAttr,
        ACVirtualMachineId *pSourceVmList,
        uint32 uNumSourceVm,
        ACMapAddrType *pMappings,
        uint32 uNumMappings);

/**
  @brief ACMapMemoryRange: Maps memory range in a pagetable. This API is used when 
  different permissions nneds to be given to different DestinationVMs 
  VM_ALL is not supported
  @param eDestinationVmidList: List of all the destination VMIDs
  @param uNumDestinationVmid: Number of VMIDs in the destination lists
  @param eSourceVmidList: List of all the source VMIDs
  @param uNumSourceVmid: Number of VMIDs in the source lists
  @param pAttr: Pointer to an array of structures of type 
  ACMapAttributesType
  @param uNumMappings: Number of mappings pointed by pAttr
  @return AC_SUCCESS on success, failure values on Failure
  */
int ACMapMemoryRange(hyp_memprot_dstVM_perm_info_t *pDestinationVMList, 
        uint32 uNumDestinationVm,
        uint32 *pSourceVmList,
        uint32 uNumSourceVm,
        hyp_memprot_ipa_info_t *pIPAinfo,
        uint32 uNumMappings);
        


/**
    IMPORTANT NOTE : ACHlosMapMemoryRange function declaration 
                     needs to be in Sync with HYPX definition.
*/
typedef AC_ERROR_CODE (*ACHandler) (ACMapAddrType *pMappings,
                                    uint32 uNumMappings,
                                    uint32 uPerm); 

#endif /* #ifndef ACCESS_CONTROL_HYP_H */
