/** @file DALHeap.c

  DAL Global Context

  Copyright (c) 2014, 2016 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/08/16   ak      Changed ALIGN_MASK to 8 bit
 03/27/15   unr     64 bit fixes
 08/11/14   sho     Creation

=============================================================================*/
#include "DALStdDef.h"
#include "DALHeap.h"
#include "DALSys.h"

// Use one heap even for physical mem and enforce all mem at 32 byte boundaries
#define ALIGN_MASK      0x000000007
#define ALIGN_UP( s )   (((DALSYSMemAddr)(s) + ALIGN_MASK) & ~(ALIGN_MASK))
#define ALIGN_DOWN( s ) ((DALSYSMemAddr)(s) & ~(ALIGN_MASK))

/*
* Heap is initialized in two stages. At Intial stage dal heap is set
* to immem heap and latter on switched to DDR when available.
* "Free" or "Destroy" do nothing and memory can not be reclaimed.
*/

typedef struct 
{
    DALSYSMemAddr pHeapFree;
    DALSYSMemAddr pHeapEnd;
}
DALSYSMemState;

static DALSYSMemState memState[DALHEAP_NUM] = 
   {{DALSYS_MEM_INVALID_ADDR,0}, 
    {DALSYS_MEM_INVALID_ADDR,0}}; 

VOID DALSYS_HeapInit(VOID *pHeapBase, UINT32 dwHeapSz, 
      DALHEAP_MEM_TYPE memType ) 
{
   if (DALHEAP_NUM <= memType) return;

   memState[memType].pHeapFree = ALIGN_UP((byte *)pHeapBase);
   memState[memType].pHeapEnd = ALIGN_DOWN((byte *)pHeapBase + dwHeapSz);
}

UINT32 DALSYS_HeapExternalMemIsReady(VOID)
{
   return (DALSYS_MEM_INVALID_ADDR != memState[DALHEAP_EXT_MEM].pHeapFree);
}

DALResult
DALSYS_Malloc(UINT32 dwSize, VOID **ppMem)
{
   DALHEAP_MEM_TYPE memType = (DALSYS_HeapExternalMemIsReady())? 
      DALHEAP_EXT_MEM: DALHEAP_IMEM;
   DALSYSMemAddr pNewHeapFree;

   dwSize = ALIGN_UP(dwSize);
   pNewHeapFree = memState[memType].pHeapFree + dwSize;
   if (pNewHeapFree > memState[memType].pHeapEnd)
   {
      *ppMem = NULL;
      return DAL_ERROR;
   }
   else
   {
      *ppMem = (VOID *)memState[memType].pHeapFree;
      memState[memType].pHeapFree = pNewHeapFree;
      return DAL_SUCCESS;
   }
}

DALResult
DALSYS_Free(VOID *pmem)
{
   // heap memory cannot be reclaimed
   return DAL_SUCCESS;
}
