#ifndef ACCESS_CONTROL_COMMON_H
#define ACCESS_CONTROL_COMMON_H
/*===========================================================================
  Copyright (c) 2010-2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
  ============================================================================*/

/*===========================================================================

  EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/accesscontrol/api/ACCommon.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  09/14/10   tk      First version.
  ============================================================================*/


/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/* Permission bit mask */
#define AC_PERM_X 0x1
#define AC_PERM_W 0x2
#define AC_PERM_R 0x4

#define AC_MAX_IPA_LIST_SIZE 0x2000

#define PAGESIZE4K                          0x1000ULL
#define ALIGN_4K_UP(a)    (((a) & (PAGESIZE4K - 1))?(((a) & ~(PAGESIZE4K - 1)) + PAGESIZE4K):(a))

#define ALIGN_4K_DOWN(a)  (((a) & (PAGESIZE4K - 1))?((a) & ~(PAGESIZE4K - 1)):(a))
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef enum
{
    AC_SUCCESS                                     = 0,
    AC_FAILURE                                     = 1,
    AC_ERR_VM_CREATE_FAIL                           = 2,
    AC_ERR_VM_MAP_FAIL1                             = 3,
    AC_ERR_RAM_PARTITION_TABLE                       = 4,
    AC_ERR_VM_MAP_FAIL2                             = 5,
    AC_ERR_VM_UNMAP_FAIL1                           = 6,
    AC_ERR_VM_MAP_FAIL3                             = 7,
    AC_ERR_VM_UNMAP_FAIL2                           = 8,
    AC_ERR_TRANSLATION_SET1                         = 9,
    AC_ERR_TRANSLATION_SET2                         = 10,
    AC_ERR_TRANSLATION_SET3                         = 11,
    AC_ERR_VALIDATION_FAIL1                         = 12,
    AC_ERR_INCORRECT_VM                            = 13,
    AC_ERR_IO_ADDRESS_MISMATCH                      = 14,
    AC_ERR_SHARED_MEMORY_SINGLE_SOURCE               = 15,
    AC_ERR_SHARED_MEMORY_SOURCE_MISMATCH             = 16,
    AC_ERR_NOT_SHARED_MEMORY_MULTIPLE_SOURCE_GIVEN    = 17,
    AC_ERR_MAPPING_TYPE_NOT_SUPPORTED                = 18,
    AC_ERR_MAPPING_NOT_FOUND                        = 19,
    AC_ERR_REMOVE_MEMORY_FROM_LIST_FAIL              = 20,
    AC_ERR_CLEAR_MEMORY_FAIL                        = 21,
    AC_ERR_IS_DEVICE_MEMORY                         = 22,
    AC_ERR_VMISMAPPED_FAILED                        = 23,
    AC_ERR_UNCACHED_ALLOC_FAILED                    = 24,
    AC_ERR_MEMORY_NOT_OWNED_BY_SOURCE_VM            = 25,
    AC_ERR_TZ_ASSIGN_SMC_FAILED                    = 26,
    AC_ERR_VM_UNMAP_FAIL3                         = 27,
    AC_ERR_VM_MAP_FAIL4                           = 28,
    AC_ERR_MALLOC_FAILED                          = 29,
    AC_ERR_MEMORY_IN_OWNED_BY_TZ                   = 30,
    AC_ERR_MEMORY_IN_USE_BY_TZ                     = 31,
    AC_ERR_XPU_TYPE_NOT_SUPPORTED                  = 32,
    AC_ERR_XPU_REMOVE_MAPPING_FAILED               = 33,
    AC_ERR_XPU_ADD_MAPPING_FAILED                  = 34,
    AC_ERR_MEMORY_NOT_FOUND_IN_LIST                = 35,
    AC_ERR_MEMORY_ALREADY_IN_LIST                  = 36,
    AC_ERR_ADD_MEMORY_FROM_LIST_FAIL               = 37,
    AC_ERR_SIZE_GREATER_THAN_32BITS                = 38,
    AC_ERR_INVALID_INDEX                          = 39,
    AC_ERR_UPDATING_RAM_PARTITION_TABLE             = 40, 
    AC_ERR_NOT_4K_ALIGNED                         = 41,
    AC_ERR_MEMORY_NOT_IN_LIST                      = 42,
    AC_ERR_NOT_DDR_MEMORY                         = 43,
    AC_ERR_IPA_OVERFLOW                           = 44,
    AC_ERR_SRC_SIZE_ZERO                          = 45,
    AC_ERR_SRC_LIST_NULL                          = 46,
    AC_ERR_DST_SIZE_ZERO                          = 47,
    AC_ERR_DST_LIST_NULL                          = 48,
    AC_ERR_SID2VM_SMMU_API_FAILED                  = 49,
    AC_ERR_SID_VALIDATION_FAIL                     = 50,
    AC_ERR_UNABLE_TO_XPU_LOCK                      = 51,
    AC_ERR_STRUCT_SIZE_LESS_THAN_EXPECTED           = 52,
    AC_ERR_INVALID_POINTER                        = 53,
    AC_ERR_IPA_IST_NULL                           = 54,
    AC_ERR_IPA_LIST_SIZE_ZER0                      = 55,
    AC_ERR_MMU_ADD_MAPPING_FAILED                  = 56,
    AC_ERR_MMU_REMOVE_MAPPING_FAILED               = 57,
    AC_ERR_INVALID_PERM_TYPE                       = 58,
    AC_ERR_MPU_LOCK_MEMORY_FAILED                  = 59,
    AC_ERR_MPU_UNLOCK_MEMORY_FAILED                = 60,
    AC_ERR_USECASE_NOT_SUPPORTED                   = 61,
    AC_ERR_SRC_VM_TZ_INVALID                       = 62,
    AC_ERR_NULL_POINTER                           = 63,
    AC_ERR_TZ_IO_ASSIGN_SMC_FAILED                 = 64,
    AC_ERR_NOT_DEVICE_MEMORY                      = 65,
    AC_ERR_SMMU_CFG_TYPE_INVALID                   = 66,
    AC_ERR_INCORRECT_PERM                         = 67,
    AC_ERR_MEMORY_IS_SHARED                        = 68,
    AC_ERR_CANNOT_CHANGE_HLOS_RO_MEMORY             = 69,
    AC_ERR_UNABLE_TO_XPU_UNLOCK                    = 70,
    AC_ERR_ADD_CLEAR_REGION_FAILED                 = 71,
    AC_ERR_REMOVE_CLEAR_REGION_FAILED              = 72,
    AC_ERR_OVERLAPPING_MEMORY                     = 73,
    AC_ERR_DEVICE_RANGE_CHECK_OVERFLOW             = 74,
    AC_ERR_ITS_A_SECURE_DEVICE                    = 75,
    AC_ERR_NOT_IN_WHITELIST                       = 76,
    AC_ERR_API_FAILED                            = 77,
    AC_ERR_SRC_NUM_INVALID                	     = 78,
    AC_ERR_NUM_MAPPING_OVERFLOW                  = 79,
    AC_ERR_DST_NUM_INVALID                	      = 80,
    AC_ERR_INCORRECT_DEVICE                           = 81,
    AC_ERR_DEVICE_NOT_FOUND                           = 82,
    AC_ERR_XPU_PARTIAL_MAPPING_NOT_ALLOWED            =83,
    AC_ERR_HASH_OVERFLOW                             = 84,
    AC_ERR_RULE_NOT_FOUND                            = 85,
	AC_ERR_VM_SIZE_OVERFLOW                          = 86,
	AC_VM_RULE_FAILURE1                              = 87,
	AC_VM_RULE_FAILURE2                              = 88,
	AC_VM_RULE_FAILURE3                              = 89,
	AC_VM_RULE_FAILURE4                              = 90,
    AC_ERR_DDR_MPU_STATIC_CFG_BLACKLIST_UPDATE            = 91,
    AC_ERR_LAST,
    AC_ERR_MAX                  = 0x7FFFFFFF,
}AC_ERROR_CODE; 

typedef enum
{
    AC_COMPLETE,  
    AC_ABSENT, 
    AC_PARTIAL,
    AC_STATUS_LAST,
    AC_STATUS_MAX = 0x7FFFFFFF,
}ACStatusTypeId;

typedef enum
{
    AC_SMMU,
    AC_MASTER_XPU,
    AC_OTHER,
    AC_SMMU_NO_INIT,
    AC_SMMU_NO_ATTACH,
    AC_SEC,
    AC_LAST,
    AC_MAX = 0x7FFFFFFF,
} ACVMTypeId;

typedef enum 
{
    AC_VM_NONE                                    = 0,
    AC_VM_TZ                                      = 1,   
    AC_VM_RPM                                     = 2,  /* Single stage */
    AC_VM_HLOS                                    = 3,
    AC_VM_HYP                                     = 4,
    AC_VM_SSC_Q6_ELF                               = 5,   /* Single */  /* IPA = PA */
    AC_VM_ADSP_Q6_ELF                              = 6,   /* Single */
    AC_VM_SSC_HLOS                                = 7,  
    AC_VM_CP_TOUCH                                = 8,
    AC_VM_CP_BITSTREAM                             = 9,
    AC_VM_CP_PIXEL                                = 10,
    AC_VM_CP_NON_PIXEL                             = 11,
    AC_VM_VIDEO_FW                                = 12,  /* IPA not equal PA */
    AC_VM_CP_CAMERA                               = 13,
    AC_VM_HLOS_UNMAPPED                            = 14,  /* Memory owned by HLOS but not currently mapped in HLOS VM */
    AC_VM_MSS_MSA                                 = 15,  /* Not to be used without talking to AccessControlAdmins */
    AC_VM_MSS_NONMSA                              = 16,   
    AC_VM_CP_SECDISP                              = 17,
    AC_VM_CP_APP                                  = 18,
    AC_VM_UNMAPPED                                = 19,   /* Used for unmapping a SID from a particular VM*/
    AC_VM_TZ_UNMAPPED                             = 20,   /* TZ owned but not currently xPU locked. Considered as Non Secured memory */
    AC_VM_TZ_STATIC                               = 21,   /* Used internally by TZ to denote no xPU modifications needed */
    AC_VM_LPASS                                   = 22, /* Single */  /* IPA = PA */
    AC_VM_ALL                                    = 23,   /* Used for unmapping particular IO range from all VMs */
    AC_VM_WLAN                                   = 24,   /* Adrastea local traffic */
    AC_VM_WLAN_COPYENG                           = 25,   /* Adrastea copy engine traffic */
    AC_VM_SPSS_SP                                = 26,   /* All SP=1 accesses from SecureProc */
    AC_VM_SPSS_NONSP                             = 27,
    RESERVED_AC_VM1                              = 28,   /* Unused VM which can be reused*/
    AC_VM_CP_CAMERA_PREVIEW                      = 29,
    AC_VM_CDSP_Q6_ELF                            = 30,   /* Single stage */
    RESERVED_AC_VM2                              = 31,
    AC_VM_HLOS_GSI                               = 32,
	AC_VM_ADSP_HEAP_SHARED                       = 33,  /* Shared to ADSP for heap usage */
	AC_VM_ADSP_SHARED                            = 34,  /* Shared wb/w ADSP and TA */
    AC_VM_PCIE                                   = 35,
	AC_VM_SHARED_SSC_HEAP                        = 38,  /* SHARED naming is used for duplicate VMs. SSC heap shared with HLOS. To Keep compatibility accross branches it is discontinuous number */
	AC_VM_SHARED_GPU_PIL                         = 39,  /* GPU PIL uses this shared VM */
	AC_VM_SPSS_SP_SHARED                         = 40,  /* Shared wb/w SPSS and TA */	
    AC_VM_LAST                                   = 41,
    AC_VM_MAX = 0x7FFFFFFF,
}ACVirtualMachineId;

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "SMMUDynamicSID.h"

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/


/**
  @brief ACMapSidToVM: Unmaps SID from non-secure/Secure VM and maps it to secure/NS VM
  @param uSmmuInstance: Type of SMMU who's CB is to be modified
  @param pSIDList: List of SIDs which are to be removed from NS/Sec and mapped to Secure/NS
  @param uNumSIDs: Number of SIDs passed
  @param uDestinationVm: The destination VM on the Secure side
  @return AC_SUCCESS if passes, otherwise AC_FAILURE
  */
int ACMapSidToVM(SMMU_Instance_e_type uSmmuInstance, 
        uint32 *pSIDList, 
        uint32 uNumSIDs, 
        ACVirtualMachineId uDestinationVm);



#endif /* ACCESS_CONTROL_COMMON_H */
