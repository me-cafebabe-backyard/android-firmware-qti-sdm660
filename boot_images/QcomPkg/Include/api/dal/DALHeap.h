#ifndef _DAL_HEAP
#define _DAL_HEAP
/*==============================================================================
@file DALHeap.h


        Copyright (c) 2014 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary


==============================================================================*/

// Supported memory types for heap
typedef enum 
{
   DALHEAP_IMEM,
   DALHEAP_EXT_MEM,
   DALHEAP_NUM
}
DALHEAP_MEM_TYPE;

/*=============================================================================
                           PROTOTYPE DECLARATIONS
=============================================================================*/
/**
  @brief Initialize internal and external heap

  Invoke to provide heap memory to heap manager
  to heap manager.

  @param pHeapBase  : Base address of the heap
  @param dwHeapSz   : Size of the heap
  @param memType    : Type of heap

  @return None
*/
VOID DALSYS_HeapInit(VOID *pHeapBase, UINT32 dwHeapSz, 
      DALHEAP_MEM_TYPE memType);

/**
  @brief Return ready status of heap on external memory

  @return 0 : external memory is not available
          1 : external memory available
*/
UINT32 DALSYS_HeapExternalMemIsReady(VOID);

#endif //_DAL_HEAP

