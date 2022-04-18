/*========================================================================

This file implements utility functions to manage shared memory between
scorpion and Qdsp6, including physical addresses to virtual address mapping, etc.

Copyright (c) 2009, 2017-2018 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*/

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.8/elite/utils/src/EliteMem_Util.cpp#11 $$DateTime: 2018/03/19 01:57:05 $$Author: pwbldsvc $

when       who     what, where, why
--------   ---     -------------------------------------------------------
11/12/09   DC      Created file.
03/28/11   AZ      Support virtual contiguous memory.

========================================================================== */
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
// system
#include "qurt_elite.h"

// Audio
#include "EliteMem_Util.h"

#include "qurt_elite_memorymap.h"
#include "adsp_audio_memmap_api.h"

#include "ap_server_api.h"
#include "aprv2_api.h"
#include "aprv2_api_inline.h"
#include "adsp_core_api.h"
#include "pdr_ssr_avs.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define ELITEMEM_UTIL_DEBUG
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

#define AVS_MDF_NUM_MAX_PROC_IDS ( 5 )

typedef struct avs_elite_list_node_t avs_elite_list_node_t;
typedef struct avs_elite_list_t avs_elite_list_t;

struct avs_elite_list_node_t
{
  avs_elite_list_t* list;

  avs_elite_list_node_t* next;

  avs_elite_list_node_t* prev;

};

struct avs_elite_list_t
{
  avs_elite_list_node_t pivot_node;

  uint32_t size;

  //  qurt_elite_mutex_t *elite_list_mutex;

};

static avs_elite_list_t avs_mdf_local_memhandle_list = {
  {
    &avs_mdf_local_memhandle_list ,
    &avs_mdf_local_memhandle_list.pivot_node,
    &avs_mdf_local_memhandle_list.pivot_node,
  },
  0
};

//static qurt_elite_mutex_t avs_mdf_local_memhandle_list_mutex;

//static qurt_elite_mutex_t avs_mdf_remote_memhandle_list_mutex;

#define AVS_MDF_REMOTE_MEM_HANDLE_UNINITIALIZED 0xFFFFFFFF

typedef enum avs_mdf_remote_proc_status_t{

  MDF_REMOTE_PROC_STATUS_UNINITIALIZED = 0,

  MDF_REMOTE_PROC_STATUS_UP,

  MDF_REMOTE_PROC_STATUS_RESPONSE_PENDING,

  MDF_REMOTE_PROC_STATUS_MEM_MAP_SUCCESS,

  MDF_REMOTE_PROC_STATUS_MEM_MAP_FAILED

}avs_mdf_remote_proc_status_t;

typedef struct avs_elite_mdf_proc_info_node_t
{
  avs_elite_list_node_t node;

  uint32_t proc_id;

  uint16_t apr_addr;

  uint32_t remote_mem_map_handle;

  avs_mdf_remote_proc_status_t remote_proc_status;

  void* remote_mem_map_payload;

  uint32_t remote_mem_map_payload_size;

}avs_elite_mdf_proc_info_node_t;

typedef struct avs_elite_mdf_local_mapping_node_t
{
  avs_elite_list_node_t node;

  uint32_t adsp_mem_map_handle;

  uint32_t property_flag;

  uint32_t adsp_virt_addr_start;

  QURT_ELITE_HEAP_ID adsp_shmem_heap_id;

  avs_elite_list_t mdf_remote_list;

}avs_elite_mdf_local_mapping_node_t;

typedef struct avs_mdf_remote_proc_lookup_t
{
    uint32_t  proc_id;
    const char_t dns[ 15 ];

}avs_mdf_shared_mem_info_t;

static avs_mdf_remote_proc_lookup_t avs_mdf_remote_proc_info [ AVS_MDF_NUM_MAX_PROC_IDS ] =
{
  { MODEM_DSP_PROC_ID, "qcom.ap.molm" },
  { SENSOR_DSP_PROC_ID, "qcom.ap.solm" },
  { 0x0004, "\0" },
  { 0x0005, "\0" }
};

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

static ADSPResult avs_elite_list_add_to_front( avs_elite_list_t* list, avs_elite_list_node_t* node )
{
  if ( NULL == list || NULL == node )
  {
    return ADSP_EBADPARAM;
  }

  node->list = list;

  node->next = list->pivot_node.next;
  node->prev = &list->pivot_node;

  list->pivot_node.next = node;

  list->size++;

  return ADSP_EOK;
}

static ADSPResult avs_elite_list_remove_node( avs_elite_list_t* list, avs_elite_list_node_t* node )
{
  if ( NULL == list || NULL == node )
  {
    return ADSP_EBADPARAM;
  }

  avs_elite_list_node_t* pivot;

  pivot = &list->pivot_node;

  while ( pivot->next != &list->pivot_node )
  {
    if ( pivot->next == node )
    {
      pivot->next = node->next;
      node->next->prev = pivot;
      list->size--;
    }
  }

  return ADSP_EOK;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

ADSPResult elite_mem_map_get_shm_attrib(uint32_t unPhysAddrLsw,
                                uint32_t unPhysAddrMsw,
                                uint32_t unMemSize,
                                elite_mem_shared_memory_map_t *pShareMemMapTypeNode ) {

    ADSPResult nRet = ADSP_EOK;

    uint32_t unVirtAddrEnd,unVirtAddrStart;

    QURT_ELITE_ASSERT(pShareMemMapTypeNode);
    //even though memsize is uinsigned, memsize >= than 0x80000000(2Gig) is invalid for aDSP and
    //memsize =0 is also invalid. The below check will take care of this.
    if ((int32_t)unMemSize <= 0) {

        return ADSP_EBADPARAM;
    }

    if (ADSP_FAILED(nRet = qurt_elite_memorymap_get_virtual_addr_from_shmm_handle(pShareMemMapTypeNode->unMemMapClient,
                                                                                    pShareMemMapTypeNode->unMemMapHandle,
                                                                                    unPhysAddrLsw,
                                                                                    unPhysAddrMsw,
                                                                                    &unVirtAddrStart)))
    {
       MSG_5(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib failed, & input is [mapclient, maphandle, PhyMsw,PhyLsw]=[%8x,%8x,%8x,%8x],error %#x\n",
               (unsigned int)pShareMemMapTypeNode->unMemMapClient,
               (unsigned int)pShareMemMapTypeNode->unMemMapHandle,
               (unsigned int)unPhysAddrMsw,
               (unsigned int)unPhysAddrLsw,
             nRet
             );
       MSG_5(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib failed & sharednode is [PhyMsw,PhyLsw,Virt,Size]=[%8x,%8x,%8x,%8x],error %#x\n",
               (unsigned int)pShareMemMapTypeNode->unPhysAddrMsw,
               (unsigned int)pShareMemMapTypeNode->unPhysAddrLsw,
               (unsigned int)pShareMemMapTypeNode->unVirtAddr,
               (unsigned int)pShareMemMapTypeNode->unMemSize,
             nRet
             );
        return nRet;
    }

    unVirtAddrEnd = unVirtAddrStart + unMemSize-1;
    uint64_t unPhyAddrEnd = qurt_elite_memorymap_get_physical_addr(unVirtAddrEnd);

    if (0 == unPhyAddrEnd)
    {

        MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib failed, & input is [mapclient, maphandle, PhyMsw,PhyLsw]=[%8x,%8x,%8x,%8x] \n",
               (unsigned int)pShareMemMapTypeNode->unMemMapClient,
               (unsigned int)pShareMemMapTypeNode->unMemMapHandle,
               (unsigned int)unPhysAddrMsw,
                (unsigned int)unPhysAddrLsw
             );

        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib failed to get End Physical Addr, [virtAddrEnd, VirtAddrStart]=[%8x,%8x]\n",
                (unsigned int)unVirtAddrEnd,
                (unsigned int)unVirtAddrStart
             );

        return ADSP_EFAILED;
    }
#ifdef ELITEMEM_UTIL_DEBUG
    else
    {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib End Physical Addr, [unPhyAddrEnd LSW, MSW]=[%8x,%8x]\n",
                (unsigned int)unPhyAddrEnd,
                (unsigned int)(unPhyAddrEnd>>32)
              );

    }
#endif

    // Fill other field of the memory map struct.
    pShareMemMapTypeNode->unMemSize  = unMemSize;
    pShareMemMapTypeNode->unPhysAddrLsw = unPhysAddrLsw;
    pShareMemMapTypeNode->unPhysAddrMsw = unPhysAddrMsw;
    pShareMemMapTypeNode->unVirtAddr = unVirtAddrStart;

#ifdef ELITEMEM_UTIL_DEBUG
    MSG_3(MSG_SSID_QDSP6, DBG_LOW_PRIO, "[PhyMsw,PhyLsw,Virt,Size]=[%8x,%8x,%8x,%d]\n",
            (unsigned int)pShareMemMapTypeNode->unPhysAddrMsw,
            (unsigned int)pShareMemMapTypeNode->unPhysAddrLsw,
            (unsigned int)pShareMemMapTypeNode->unVirtAddr,
            (unsigned int)pShareMemMapTypeNode->unMemSize);
#endif
    return ADSP_EOK;
}


ADSPResult elite_mem_map_get_shm_attrib_ref_counted(uint32_t unPhysAddrLsw,
                                    uint32_t unPhysAddrMsw,
                                    uint32_t unMemSize,
                                    elite_mem_shared_memory_map_t *pShareMemMapTypeNode )
{

    ADSPResult rc = ADSP_EOK;

    if (ADSP_FAILED(rc= elite_mem_map_get_shm_attrib(unPhysAddrLsw,unPhysAddrMsw,unMemSize,pShareMemMapTypeNode) ))
    {
        return rc;
    }

    //At this stage pShareMemMapTypeNode should have correct values

    //Incr the ref count

    if (ADSP_FAILED(rc= qurt_elite_memorymap_shm_incr_refcount(pShareMemMapTypeNode->unMemMapClient,
            pShareMemMapTypeNode->unMemMapHandle)))
    {
           MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_get_shm_attrib_ref_counted failed when adding ref count for [mapclient, maphandle]=[%8x,%8x],error %#x\n",
                   (unsigned int)pShareMemMapTypeNode->unMemMapClient,
                   (unsigned int)pShareMemMapTypeNode->unMemMapHandle,
                   rc
                   );

    }

    return rc;

}

ADSPResult elite_mem_map_release_shm(elite_mem_shared_memory_map_t *pShareMemMapTypeNode )
{

    ADSPResult rc = ADSP_EOK;

    if (!pShareMemMapTypeNode)
    {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "pShareMemMapTypeNode revd is NULL");
        return ADSP_EFAILED;
    }

    if (ADSP_FAILED(rc = qurt_elite_memorymap_shm_decr_refcount(pShareMemMapTypeNode->unMemMapClient,
                                            pShareMemMapTypeNode->unMemMapHandle
                                        )))
    {
           MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_mem_map_release_shm failed when decr ref count for [mapclient, maphandle]=[%8x,%8x],error %#x\n",
                   (unsigned int)pShareMemMapTypeNode->unMemMapClient,
                   (unsigned int)pShareMemMapTypeNode->unMemMapHandle,
                   rc
                   );

    }

    return rc;
}



ADSPResult elite_mem_flush_cache( elite_mem_shared_memory_map_t *pSharedMemMapTypeNode )
{
    ADSPResult rc = ADSP_EOK;
    if (pSharedMemMapTypeNode->unVirtAddr) {
        if (ADSP_FAILED(rc = qurt_elite_memorymap_cache_flush(pSharedMemMapTypeNode->unVirtAddr,pSharedMemMapTypeNode->unMemSize)))
        {
            return rc;
        }
    }
    return rc;
}

ADSPResult elite_mem_invalidate_cache( elite_mem_shared_memory_map_t *pSharedMemMapTypeNode )
{
    ADSPResult rc = ADSP_EOK;

    if (pSharedMemMapTypeNode->unVirtAddr) {
        if(ADSP_FAILED(rc=qurt_elite_memorymap_cache_invalidate(pSharedMemMapTypeNode->unVirtAddr,pSharedMemMapTypeNode->unMemSize)))
        {
            return rc;
        }
    }
    return rc;
}

ADSPResult elite_mem_shared_memory_map_regions_cmd_handler(uint32_t nMemMapClient,
                                      elite_apr_handle_t hAprHandle,
                                      elite_apr_packet_t *pPkt,
                                      uint32_t nRespOpcode)
{
    ADSPResult rc = ADSP_EOK;
    void * pPayload,*pDummy;
    avs_cmd_shared_mem_map_regions_t *mem_map_regions_payload_ptr;
    uint32_t mem_map_handle=0;
    elite_apr_packet_t *pRespPkt = NULL;
    QURT_ELITE_MEMORYPOOLTYPE eMemPool;
    avs_shared_map_region_payload_t **ppRegion;

    elite_apr_if_get_payload( (void**) &pPayload, pPkt );

    mem_map_regions_payload_ptr = (avs_cmd_shared_mem_map_regions_t *)pPayload;


    switch (mem_map_regions_payload_ptr->mem_pool_id)
    {
        case ADSP_MEMORY_MAP_SHMEM8_4K_POOL:
            eMemPool = QURT_ELITE_MEMORYMAP_SHMEM8_4K_POOL;
            break;

        case ADSP_MEMORY_MAP_MDF_SHMEM_4K_POOL:
            eMemPool = QURT_ELITE_MEMORYMAP_EBI1_POOL;
            MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Amar  : EliteMem MemMapRegCmdHandler: MDF SHMEM received!... flag = %d  num_regions = %d",
                  mem_map_regions_payload_ptr->property_flag, mem_map_regions_payload_ptr->num_regions );
            break;

        default:

           rc = ADSP_EBADPARAM;
           MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem MemMapRegCmdHandler: Received Invalid PoolID: %d", mem_map_regions_payload_ptr->mem_pool_id);
           goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_1;
    }

     /* Allocate the response packet */
     rc = elite_apr_if_alloc_cmd_rsp(
         hAprHandle,
         elite_apr_if_get_dst_addr( pPkt),
         elite_apr_if_get_dst_port( pPkt),
         elite_apr_if_get_src_addr( pPkt),
         elite_apr_if_get_src_port( pPkt),
         elite_apr_if_get_client_token( pPkt),
         nRespOpcode,
         sizeof(avs_cmdrsp_shared_mem_map_regions_t),
         &pRespPkt );

    if (ADSP_FAILED(rc) || NULL == pRespPkt)
    {
        rc = ADSP_ENOMEMORY;
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem MemMapRegCmdHandler: memory map response packet allocation failed with error code  = %d!", rc);
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_1;
    }

    /* prepare the Response payload pointer */
    avs_cmdrsp_shared_mem_map_regions_t *pRespPayload;
    elite_apr_if_get_payload((&pDummy), pRespPkt);
    pRespPayload = (avs_cmdrsp_shared_mem_map_regions_t *)pDummy;


    pDummy = ((uint8_t *)pPayload + sizeof(avs_cmd_shared_mem_map_regions_t));
    ppRegion = (avs_shared_map_region_payload_t **)&pDummy;

    // allocate qurt_elite_memorymap_shm_region_t, why not direct cast? because want to be free from
    // api data structure change or any compiler pack
    qurt_elite_memorymap_shm_region_t* phy_regions;
    if (NULL == (phy_regions = (qurt_elite_memorymap_shm_region_t*) qurt_elite_memory_malloc(
        sizeof(qurt_elite_memorymap_shm_region_t) * mem_map_regions_payload_ptr->num_regions,
        QURT_ELITE_HEAP_DEFAULT)))
    {
        rc = ADSP_ENOMEMORY;
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_2;
    }
    for (int i=0; i<mem_map_regions_payload_ptr->num_regions; ++i)
    {
        phy_regions[i].shm_addr_lsw = (*ppRegion+i)->shm_addr_lsw;
        phy_regions[i].shm_addr_msw = (*ppRegion+i)->shm_addr_msw;
        phy_regions[i].mem_size = (*ppRegion+i)->mem_size_bytes;
    }

    if (0 == mem_map_regions_payload_ptr->property_flag)
    {
        //physical mapping
        if (ADSP_FAILED(rc = qurt_elite_memorymap_shm_mem_map(nMemMapClient,phy_regions,
                                                    mem_map_regions_payload_ptr->num_regions,
                                                    HMEM_CACHE_WRITEBACK_L2CACHEABLE,
                                                    eMemPool,
                                                    &mem_map_handle)))
        {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: Failed to map the physical memory, error code is 0x%x",rc );
            goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
        }
    }
    else if (1 ==  mem_map_regions_payload_ptr->property_flag)
    {
        //virtual mapping
        if (ADSP_FAILED(rc = qurt_elite_memorymap_virtaddr_mem_map(nMemMapClient,phy_regions,
                                                    mem_map_regions_payload_ptr->num_regions,
                                                    HMEM_CACHE_WRITEBACK_L2CACHEABLE,
                                                    eMemPool,
                                                    &mem_map_handle)))
        {
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: Failed to map the virual memory, error code is 0x%x",rc );
            goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
        }

    }
    else
    {
        rc = ADSP_EBADPARAM;
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: invalid property flag received in the payload, error code is 0x%x",rc );
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
    }

    //store the memory map handle in the response payload
    pRespPayload->mem_map_handle         = mem_map_handle;

    if ( ADSP_MEMORY_MAP_MDF_SHMEM_4K_POOL == mem_map_regions_payload_ptr->mem_pool_id )
    {
      uint32_t adsp_mdf_virt_addr;
      avs_elite_mdf_local_mapping_node_t* adsp_mdf_node = NULL;
      QURT_ELITE_HEAP_ID mdf_heap_id;

      /* Get starting virtual address of shared memory region. */
      if ( ADSP_FAILED( rc = qurt_elite_memorymap_get_virtual_addr_from_shmm_handle( nMemMapClient,
                                                                                     mem_map_handle,
                                                                                     phy_regions[0].shm_addr_lsw,
                                                                                     phy_regions[0].shm_addr_msw,
                                                                                     &adsp_mdf_virt_addr ) ) )
      {
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: invalid MDF memhadle or address,  handle = 0x%8X, address = 0x%08X... rc =%d.",
            mem_map_handle, adsp_mdf_virt_addr, rc  );
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
      }

      rc = qurt_elite_memory_heapmgr_create( ( QURT_ELITE_HEAP_ID* )&mdf_heap_id,
                                              ( void* )adsp_mdf_virt_addr, phy_regions[0].mem_size );
      {
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Created MDF shared memory heap manager..heap_id = 0x%08X,  rc %d \n", mdf_heap_id, rc );
      }

      adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )qurt_elite_memory_malloc(
                          sizeof( avs_elite_mdf_local_mapping_node_t ), QURT_ELITE_HEAP_DEFAULT);

      if ( NULL == adsp_mdf_node )
      {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: failed to create list node" );
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
      }

      adsp_mdf_node->adsp_mem_map_handle = mem_map_handle;
      adsp_mdf_node->property_flag = mem_map_regions_payload_ptr->property_flag;

      adsp_mdf_node->adsp_shmem_heap_id = mdf_heap_id;

      adsp_mdf_node->adsp_virt_addr_start = adsp_mdf_virt_addr;

      adsp_mdf_node->mdf_remote_list.pivot_node.list = &adsp_mdf_node->mdf_remote_list;
      adsp_mdf_node->mdf_remote_list.pivot_node.next = &adsp_mdf_node->mdf_remote_list.pivot_node;
      adsp_mdf_node->mdf_remote_list.pivot_node.prev = &adsp_mdf_node->mdf_remote_list.pivot_node;
      adsp_mdf_node->mdf_remote_list.size = 0;

      if ( APR_EOK != ( rc = avs_elite_list_add_to_front( &avs_mdf_local_memhandle_list, ( avs_elite_list_node_t* )adsp_mdf_node ) ) )
      {
        MSG( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: failed to add to list" );
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
      }

    }

    /* send response */
    if ( APR_EOK != ( rc = elite_apr_if_async_send( hAprHandle, pRespPkt ) ) )
    {
        rc = ADSP_EFAILED;
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: failed to send the memory map response command, error code is  = 0x%x", rc);
        goto _elite_mem_shared_memory_map_regions_cmd_handler_bail_3;
    }

    qurt_elite_memory_free( phy_regions );
    elite_apr_if_free( hAprHandle, pPkt );
    return rc;


_elite_mem_shared_memory_map_regions_cmd_handler_bail_3:
    qurt_elite_memory_free(phy_regions);
_elite_mem_shared_memory_map_regions_cmd_handler_bail_2:
   (void)elite_apr_if_free(hAprHandle,pRespPkt);
_elite_mem_shared_memory_map_regions_cmd_handler_bail_1:
    elite_apr_if_end_cmd(hAprHandle, pPkt, rc);
    return rc;

}

ADSPResult elite_mem_shared_memory_un_map_regions_cmd_handler(uint32_t nMemMapClient,
                                        elite_apr_handle_t hAprHandle,
                                        elite_apr_packet_t *pPkt)
{
    ADSPResult rc = ADSP_EOK;
    void * pPayload;
    avs_cmd_shared_mem_unmap_regions_t *pMemUnMapRegionsPayload;

    elite_apr_if_get_payload( (void**) &pPayload, pPkt );

    pMemUnMapRegionsPayload = (avs_cmd_shared_mem_unmap_regions_t *)pPayload;

    elite_mem_mdf_unmap_shared_mem( pMemUnMapRegionsPayload->mem_map_handle, hAprHandle, pPkt );

    if (0 == pMemUnMapRegionsPayload->mem_map_handle)
    {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: null memory map handle received in the unmap cmd payload");
        rc = ADSP_EBADPARAM;
        goto _elite_mem_shared_memory_un_map_regions_cmd_handler_bail_1;
    }

    if (ADSP_FAILED(rc = qurt_elite_memorymap_shm_mem_unmap(nMemMapClient,pMemUnMapRegionsPayload->mem_map_handle)))
    {
        MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: Failed to unmap the phyiscal memory, error code is 0x%x",rc );
    }

_elite_mem_shared_memory_un_map_regions_cmd_handler_bail_1:
    elite_apr_if_end_cmd(hAprHandle, pPkt, rc);
    return rc;

}

ADSPResult elite_mem_map_mdf_shared_memory_cmd_handler(
  uint32_t nMemMapClient,
                                      elite_apr_handle_t hAprHandle,
  elite_apr_packet_t *pPkt
)
{
    ADSPResult rc = ADSP_EOK;
    void * pPayload;
    avcs_cmd_map_mdf_shared_memory_t *mdf_shmem_payload;
    elite_apr_packet_t *ap_pkt = NULL;
    avs_shared_map_region_payload_t *ppRegion;
    ap_cmd_shared_mem_map_regions_v1_t* ap_shmem_payload;
    ap_shared_map_region_payload_v1_t* ap_shmem_region;
    avs_elite_mdf_proc_info_node_t* remot_proc_node;
    bool_t proc_id_valid = FALSE;
    bool_t found_adsp_mem_handle = FALSE;
    avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
    avs_elite_list_node_t* pivot_node;
    avs_elite_list_node_t* pivot_node2;
    int32_t  j;
    uint32_t payload_size;
    uint32_t param_size;
    uint16_t remote_proc_apr_addr;

    elite_apr_if_get_payload( (void**) &pPayload, pPkt );
    payload_size = elite_apr_if_get_payload_size( pPkt );

    mdf_shmem_payload = ( avcs_cmd_map_mdf_shared_memory_t *)pPayload;

    ppRegion = ( avs_shared_map_region_payload_t * )( ( uint8_t * )pPayload + sizeof( avcs_cmd_map_mdf_shared_memory_t ) );

    MSG_2( MSG_SSID_QDSP6, DBG_MED_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
           "proc_id %d, number of regions %d ", mdf_shmem_payload->proc_id, mdf_shmem_payload->num_regions );

    /* Validate input arguments.*/

    /* Validate payload size. */
    if ( payload_size != ( sizeof( avcs_cmd_map_mdf_shared_memory_t ) +
         ( mdf_shmem_payload->num_regions * sizeof ( ap_shared_map_region_payload_v1_t ) ) ) )
    {
      MSG_1( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
             "invalid payload_size %d ", payload_size );

      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_EBADPARAM );
      return ADSP_EOK;
    }

    /* Validate mem_map_handle. */
    pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

    while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
    {

      adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

      if ( adsp_mdf_node->adsp_mem_map_handle == mdf_shmem_payload->mem_map_handle )
      {
        found_adsp_mem_handle = TRUE;
        break;
      }

      pivot_node = pivot_node->next;
    }

    if ( FALSE == found_adsp_mem_handle )
    {

      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
             "invalid handle 0x%08X ", mdf_shmem_payload->mem_map_handle );
      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_EHANDLE );
      return ADSP_EOK;

    }

    /* Validate remote_proc_id. */

    for ( j = 0; j < AVS_MDF_NUM_MAX_PROC_IDS; j++ )
    {
      if ( avs_mdf_remote_proc_info[j].proc_id == mdf_shmem_payload->proc_id )
      {
        proc_id_valid = TRUE;
        ( void ) __aprv2_cmd_local_dns_lookup(
                 (char_t*)avs_mdf_remote_proc_info[j].dns, sizeof( avs_mdf_remote_proc_info[j].dns ), &remote_proc_apr_addr );
      }
    }

    if ( TRUE != proc_id_valid )
    {
      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
             "invalid proc_id %d ", mdf_shmem_payload->proc_id );

      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_EBADPARAM );
      return ADSP_EOK;
    }

    /* Check if one region was already mapped for this Proc ID with same ADSP mem map handle.*/
    pivot_node2 = &( adsp_mdf_node->mdf_remote_list.pivot_node );

    while ( pivot_node2->next != &( adsp_mdf_node->mdf_remote_list.pivot_node ) )
    {
      remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;
      if ( remot_proc_node->proc_id == mdf_shmem_payload->proc_id )
      {
        proc_id_valid = FALSE;
        break;
      }
      pivot_node2 = pivot_node2->next;
    }

    if ( TRUE != proc_id_valid )
    {
      MSG_2( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
             "proc_id %d already mapped with same adsp memhandle 0x%08X ",
             mdf_shmem_payload->proc_id, adsp_mdf_node->adsp_mem_map_handle );

      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_EALREADY );
      return ADSP_EOK;
    }

    /* All input param validations are success. */

    remot_proc_node = NULL;

    remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )qurt_elite_memory_malloc(
                         sizeof( avs_elite_mdf_proc_info_node_t ), QURT_ELITE_HEAP_DEFAULT);

    if ( NULL == remot_proc_node )
    {
      MSG( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler failed to alocate node" );

      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_ENORESOURCE );
      return ADSP_EOK;
    }

    remot_proc_node->proc_id = mdf_shmem_payload->proc_id;
    remot_proc_node->apr_addr = remote_proc_apr_addr;
    remot_proc_node->remote_mem_map_handle = AVS_MDF_REMOTE_MEM_HANDLE_UNINITIALIZED;
    remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_UNINITIALIZED;

    if ( APR_EOK != ( rc = avs_elite_list_add_to_front( &(adsp_mdf_node->mdf_remote_list), ( avs_elite_list_node_t*)remot_proc_node ) ) )
    {
      MSG( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: failed to add to list" );
      qurt_elite_memory_free( (void*)remot_proc_node );
      elite_apr_if_end_cmd(hAprHandle, pPkt, rc);
      return ADSP_EOK;
    }

    param_size = sizeof ( ap_cmd_shared_mem_map_regions_v1_t ) +
                  ( mdf_shmem_payload->num_regions * sizeof ( ap_shared_map_region_payload_v1_t ) );

    remot_proc_node->remote_mem_map_payload_size = param_size + sizeof(ap_server_stat_cmn_header_t);

    remot_proc_node->remote_mem_map_payload = ( void* )qurt_elite_memory_malloc(
                                                remot_proc_node->remote_mem_map_payload_size, QURT_ELITE_HEAP_DEFAULT);

    if ( NULL == remot_proc_node->remote_mem_map_payload )
    {
      MSG( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler failed to alocate node" );
      qurt_elite_memory_free( (void*)remot_proc_node );
      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_ENORESOURCE );
      return ADSP_EOK;
    }

    elite_apr_if_alloc_cmd( hAprHandle,
                            elite_apr_if_get_dst_addr( pPkt),
                            elite_apr_if_get_dst_port( pPkt),
                            remot_proc_node->apr_addr,
                            0, mdf_shmem_payload->mem_map_handle,
                            AP_CMD_SHARED_MEM_MAP_REGIONS,
                            param_size + sizeof(ap_server_stat_cmn_header_t),
                            &ap_pkt );

    /* Get remote command payload pointer in the packet*/
    uint8_t *payload_ptr = ( uint8_t* )elite_apr_if_get_payload_ptr(ap_pkt);

    ap_server_stat_cmn_header_t *header_ptr = (ap_server_stat_cmn_header_t*) payload_ptr;
    header_ptr->module_id         = AP_MODULE_AUDPROC_ID_DEFAULT;
    header_ptr->instance_id       = 1;
    header_ptr->param_id          = AP_PARAM_ID_MEM_MAP;
    header_ptr->reserved          = 0;
    header_ptr->param_size        = param_size;
    header_ptr->param_version     = AP_PARAM_MEM_MAP_VERSION;
    header_ptr->param_struct_size = sizeof(ap_cmd_shared_mem_map_regions_v1_t);

    ap_shmem_payload = ( ap_cmd_shared_mem_map_regions_v1_t* )( payload_ptr + sizeof( ap_server_stat_cmn_header_t ) );

    ap_shmem_payload->mem_pool_id = ADSP_MEMORY_MAP_SHMEM8_4K_POOL;

    ap_shmem_payload->num_regions = mdf_shmem_payload->num_regions;

    ap_shmem_payload->property_flag = adsp_mdf_node->property_flag;

    ap_shmem_payload->payload_version = AP_PARAM_MEM_MAP_REGION_VERSION;

    ap_shmem_payload->payload_struct_size = sizeof(ap_shared_map_region_payload_v1_t);

    ap_shmem_region = ( ap_shared_map_region_payload_v1_t* )( (int8_t*)ap_shmem_payload + sizeof ( ap_cmd_shared_mem_map_regions_v1_t ) );

    /* Since the supported version of AP_MEM_MAP command is 1, direct memscpy will work. */
    memscpy( ( void* )ap_shmem_region, ( mdf_shmem_payload->num_regions * sizeof ( ap_shared_map_region_payload_v1_t ) ),
             ( void* )ppRegion, ( mdf_shmem_payload->num_regions * sizeof ( ap_shared_map_region_payload_v1_t ) ) );

    /* Cache the payload of remote mem map command. */

    memscpy( ( void* )remot_proc_node->remote_mem_map_payload, remot_proc_node->remote_mem_map_payload_size,
            ( void* )payload_ptr, remot_proc_node->remote_mem_map_payload_size );

    if (APR_EOK != (rc = elite_apr_if_async_send(hAprHandle, ap_pkt)))
    {
      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_map_mdf_shared_memory_cmd_handler,"
             "apr_send failed 0x%x",rc );
      elite_apr_if_end_cmd( hAprHandle, pPkt, ADSP_ENOTREADY );
      return ADSP_EOK;
    }

    remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_RESPONSE_PENDING;

    elite_apr_if_end_cmd(hAprHandle, pPkt, rc);

    return ADSP_EOK;
}


ADSPResult elite_mem_mdf_shared_memory_response_handler(
  elite_apr_handle_t hAprHandle,
  elite_apr_packet_t *pPkt,
  bool_t map_success
)
{
    void * pPayload;
    ap_cmdrsp_shared_mem_map_regions_v1_t *ap_shmem_rsp;
    avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
    avs_elite_list_node_t* pivot_node;
    avs_elite_list_node_t* pivot_node2;
    avs_elite_mdf_proc_info_node_t* remot_proc_node;

    elite_apr_if_get_payload( &pPayload, pPkt );

    MSG_1( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_mdf_shared_memory_response_handler,"
           "map_success = %d", map_success );

    pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

    while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
    {

      adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

      if ( adsp_mdf_node->adsp_mem_map_handle == pPkt->token )
      {
        pivot_node2 = &(adsp_mdf_node->mdf_remote_list.pivot_node);

        while ( pivot_node2->next != &(adsp_mdf_node->mdf_remote_list.pivot_node) )
        {

          remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;
          if ( remot_proc_node->apr_addr == elite_apr_if_get_src_addr( pPkt) )
          {
            if ( FALSE == map_success )
            {
              /* Memory map with remote failed.*/
              aprv2_ibasic_rsp_result_t* rsp_payload;
              elite_apr_if_get_payload( (void**) &rsp_payload, pPkt );

              if ( APR_ENOSERVICE == rsp_payload->status )
              {
               /* Memory map failed due to remote static service not up. We can retry when the status event is received from remote processor.
                  Race condition handling : "AP_EVENT_STATIC_SERVICE_UP" can never reach ADSP before APR_ENOSERVICE failure.
                  Hence a retry can be performed when the event is received at ADSP.
               */
                remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_UNINITIALIZED;
              } else {
                /* General mem map failure with remote DSP.*/
                remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_MEM_MAP_FAILED;
              }

            } else {
              /*Shared memory mapping with remote processor is successful.*/
              ap_server_stat_cmn_header_t *pHeader = (ap_server_stat_cmn_header_t*)pPayload;
              if(AP_PARAM_MEM_MAP_RSP_VERSION < pHeader->param_version || 0 == pHeader->param_version)
              {
                MSG_2( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_mdf_shared_memory_response_handler,"
                                     "received invalid rsp version 0x%08X, token %d", pHeader->param_version, pPkt->token );
                remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_MEM_MAP_FAILED;
                break;
              }
              /* Supported version for this param is 1. The supported payload type is ap_cmdrsp_shared_mem_map_regions_v1_t */
              ap_shmem_rsp = ( ap_cmdrsp_shared_mem_map_regions_v1_t* )( ( uint8_t* )pPayload + sizeof( ap_server_stat_cmn_header_t ) );

              MSG_2( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_mdf_shared_memory_response_handler,"
                     "received handle 0x%08X, token %d", ap_shmem_rsp->mem_map_handle, pPkt->token );
              remot_proc_node->remote_mem_map_handle = ap_shmem_rsp->mem_map_handle;
              remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_MEM_MAP_SUCCESS;
            }
            break;
          }
          pivot_node2 = pivot_node2->next;
        }

        break;
      }

      pivot_node = pivot_node->next;
    }

    elite_apr_if_free( hAprHandle, pPkt );

    return ADSP_EOK;
}

ADSPResult elite_mem_remote_service_event_handler(
  elite_apr_handle_t hAprHandle,
  elite_apr_packet_t *pPkt
)
{
    //The incoming pPkt is freed in the caller function in AVCS

    ap_event_static_service_up_v1_t* pPayload;
    avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
    avs_elite_list_node_t* pivot_node;
    avs_elite_list_node_t* pivot_node2;
    avs_elite_mdf_proc_info_node_t* remot_proc_node;
    elite_apr_packet_t *ap_pkt = NULL;
    ADSPResult rc;

    elite_apr_if_get_payload( (void**)&pPayload, pPkt );

    ap_server_stat_cmn_header_t *pHeader = (ap_server_stat_cmn_header_t*)pPayload;

    if(pHeader->param_version > AP_PARAM_SERVICE_STATUS_VERSION || (0 == pHeader->param_version))
    {
      MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_remote_service_event_handler,"
                           "received invalid version 0x%x",pHeader->param_version );
      return ADSP_EBADPARAM;
    }

    pPayload = ( ap_event_static_service_up_v1_t* )( ( uint8_t* )pPayload + sizeof( ap_server_stat_cmn_header_t ) );

    pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

    while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
    {

      adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

      pivot_node2 = &(adsp_mdf_node->mdf_remote_list.pivot_node);

      while ( pivot_node2->next != &(adsp_mdf_node->mdf_remote_list.pivot_node) )
      {

        remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;
        if ( remot_proc_node->apr_addr == elite_apr_if_get_src_addr( pPkt) )
        {
          if ( MDF_REMOTE_PROC_STATUS_UNINITIALIZED == remot_proc_node->remote_proc_status  )
          {

            MSG_1( MSG_SSID_QDSP6, DBG_HIGH_PRIO, "EliteMem: elite_mem_remote_service_event_handler,"
                     "Retrying for proc ID 0x%x",remot_proc_node->proc_id );

            /*Send commmand to remote processor. */
            elite_apr_if_alloc_cmd( hAprHandle,
                            elite_apr_if_get_dst_addr( pPkt),
                            elite_apr_if_get_dst_port( pPkt),
                            remot_proc_node->apr_addr,
                            0, adsp_mdf_node->adsp_mem_map_handle,
                            AP_CMD_SHARED_MEM_MAP_REGIONS,
                            remot_proc_node->remote_mem_map_payload_size,
                            &ap_pkt );
            //RR: Check for NULL pointer for ap_pkt?

            /* Get payload pointer in the allocated packet */
            void *ap_pkt_payload_ptr = ( void* )elite_apr_if_get_payload_ptr(ap_pkt);

            memscpy( ap_pkt_payload_ptr, remot_proc_node->remote_mem_map_payload_size,
                     ( void* )remot_proc_node->remote_mem_map_payload, remot_proc_node->remote_mem_map_payload_size );

            if ( APR_EOK != ( rc = elite_apr_if_async_send( hAprHandle, ap_pkt ) ) )
            {
              MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_remote_service_event_handler,"
                     "apr_send failed 0x%x",rc );
              avs_elite_list_remove_node( &( adsp_mdf_node->mdf_remote_list ), ( avs_elite_list_node_t* )remot_proc_node );

              qurt_elite_memory_free( (void*)remot_proc_node->remote_mem_map_payload );
              qurt_elite_memory_free( (void*)remot_proc_node );
            }

          } else if ( MDF_REMOTE_PROC_STATUS_RESPONSE_PENDING == remot_proc_node->remote_proc_status  ){
            /* Already command sent to Remote processor. Wait for response.*/
            remot_proc_node->remote_proc_status = MDF_REMOTE_PROC_STATUS_UP;
          }
          break;
        }
        pivot_node2 = pivot_node2->next;
      }

      pivot_node = pivot_node->next;
    }

    return ADSP_EOK;
}

void elite_mem_mdf_unmap_shared_mem( uint32_t adsp_mem_handle,
  elite_apr_handle_t hAprHandle,
  elite_apr_packet_t *pPkt
)
{
  ADSPResult rc = ADSP_EOK;
  elite_apr_packet_t *ap_pkt = NULL;

  ap_cmd_shared_mem_unmap_regions_v1_t* ap_shmem_unmap_payload;
  avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
  avs_elite_list_node_t* pivot_node;
  avs_elite_list_node_t* pivot_node2;
  avs_elite_mdf_proc_info_node_t* remot_proc_node;

  MSG_1( MSG_SSID_QDSP6, DBG_MED_PRIO, "EliteMem: elite_mem_mdf_unmap_shared_mem, 0x%08X", adsp_mem_handle );

  if ( 0 == adsp_mem_handle )
  {
    return;
  }

  pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

  while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
  {

    adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

    if ( adsp_mdf_node->adsp_mem_map_handle == adsp_mem_handle )
    {

      pivot_node2 = &( adsp_mdf_node->mdf_remote_list.pivot_node );

      while ( pivot_node2->next != &( adsp_mdf_node->mdf_remote_list.pivot_node ) )
      {
        /* Supported version is 1, so request appropriate size of pkt */
        uint32_t param_size = sizeof ( ap_cmd_shared_mem_unmap_regions_v1_t );

        remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;

        elite_apr_if_alloc_cmd( hAprHandle,
                                elite_apr_if_get_dst_addr( pPkt ),
                                elite_apr_if_get_dst_port( pPkt ),
                                remot_proc_node->apr_addr,
                                0, 0, AP_CMD_SHARED_MEM_UNMAP_REGIONS,
                                param_size + sizeof( ap_server_stat_cmn_header_t ),
                                &ap_pkt );

        /* Get remote command payload pointer in the packet*/
        uint8_t *payload_ptr = ( uint8_t* )elite_apr_if_get_payload_ptr( ap_pkt );

        ap_server_stat_cmn_header_t *header_ptr = ( ap_server_stat_cmn_header_t* ) payload_ptr;
        header_ptr->module_id         = AP_MODULE_AUDPROC_ID_DEFAULT;
        header_ptr->instance_id       = 1;
        header_ptr->param_id          = AP_PARAM_ID_MEM_UNMAP;
        header_ptr->reserved          = 0;
        header_ptr->param_size        = param_size;
        header_ptr->param_version     = AP_PARAM_MEM_UNMAP_VERSION;
        header_ptr->param_struct_size = sizeof(ap_cmd_shared_mem_unmap_regions_v1_t);

        /* Supported version is 1, so typecast directly */
        ap_shmem_unmap_payload = ( ap_cmd_shared_mem_unmap_regions_v1_t* )( payload_ptr + sizeof( ap_server_stat_cmn_header_t ) );

        ap_shmem_unmap_payload->mem_map_handle = remot_proc_node->remote_mem_map_handle;

        MSG_1( MSG_SSID_QDSP6, DBG_MED_PRIO, "EliteMem: elite_mem_mdf_unmap_shared_mem,"
               " mem_map_handle 0x%08X", remot_proc_node->remote_mem_map_handle );

        if ( APR_EOK != ( rc = elite_apr_if_async_send( hAprHandle, ap_pkt ) ) )
        {
          MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_unmap_shared_mem,"
                 "apr_send failed 0x%x",rc );
        }

        pivot_node2 = pivot_node2->next;

        avs_elite_list_remove_node( &( adsp_mdf_node->mdf_remote_list ), ( avs_elite_list_node_t* )remot_proc_node );
        qurt_elite_memory_free( (void*)remot_proc_node->remote_mem_map_payload );
        qurt_elite_memory_free( (void*)remot_proc_node );

      }

      qurt_elite_memory_heapmgr_delete(adsp_mdf_node->adsp_shmem_heap_id );

      avs_elite_list_remove_node( &avs_mdf_local_memhandle_list, ( avs_elite_list_node_t* )adsp_mdf_node );
      qurt_elite_memory_free( (void*)adsp_mdf_node );

      break;
    }

    pivot_node = pivot_node->next;
  }

  MSG( MSG_SSID_QDSP6, DBG_MED_PRIO, "EliteMem: elite_mem_mdf_unmap_shared_mem, return "  );

}


void* elite_mem_mdf_malloc(
  uint32_t size,
  uint32_t proc_id,
  uint32_t* ret_mem_handle,
  uint32_t* ret_virt_addr_offset
)
{
  void* alloc_ptr = NULL;
  uint64_t phy_addr_64bit;
  ADSPResult rc = ADSP_EOK;
  bool_t found_proc_id = FALSE;
  avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
  avs_elite_list_node_t* pivot_node;
  avs_elite_list_node_t* pivot_node2;
  avs_elite_mdf_proc_info_node_t* remot_proc_node;
  uint32_t offset;
  uint32_t cache_align_size = L2_LINESIZE;

  size  =  size + (cache_align_size  - size % cache_align_size);  // Making the size a multiple of 64 bytes.

  for ( ; ; )
  {

    if ( NULL == ret_mem_handle || NULL == ret_virt_addr_offset )
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_malloc, bad_params..." );
      rc = ADSP_EFAILED;
      break;
    }

    /* Check if the Shared memory is available for MDF. */

    pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

    while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
    {

      adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

      pivot_node2 = &( adsp_mdf_node->mdf_remote_list.pivot_node );

      while ( pivot_node2->next != &( adsp_mdf_node->mdf_remote_list.pivot_node ) )
      {
        remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;
        if ( remot_proc_node->proc_id == proc_id )
        {
          found_proc_id = TRUE;
          break;
        }
        pivot_node2 = pivot_node2->next;
      }

      if ( TRUE == found_proc_id &&
           AVS_MDF_REMOTE_MEM_HANDLE_UNINITIALIZED != remot_proc_node->remote_mem_map_handle )
      {
        /* Allocate from Shared memory heap. */
        alloc_ptr = qurt_elite_memory_heapmgr_aligned_malloc( size, cache_align_size, ( QURT_ELITE_HEAP_ID )adsp_mdf_node->adsp_shmem_heap_id );

        if ( NULL != alloc_ptr )
    {
      break;
    }
        found_proc_id = FALSE;
      }

      pivot_node = pivot_node->next;
    }

    if ( NULL == alloc_ptr )
    {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_malloc, no shared memory for MDF..." );
      rc = ADSP_EFAILED;
      break;
    }

    offset = ( uint32_t )( alloc_ptr ) - adsp_mdf_node->adsp_virt_addr_start;

    uint32_t virt_addr_alloc = (uint32_t)alloc_ptr;

    *ret_mem_handle = remot_proc_node->remote_mem_map_handle;

    phy_addr_64bit = qurt_elite_memorymap_get_physical_addr( adsp_mdf_node->adsp_virt_addr_start );

    phy_addr_64bit += offset;

    *ret_virt_addr_offset = offset;
//#ifdef ELITEMEM_UTIL_DEBUG
    MSG_4( MSG_SSID_QDSP6, DBG_MED_PRIO, "EliteMem: elite_mem_mdf_malloc alloc_ptr: 0x%08X,"
           " *ret_virt_addr LSW 0x%08X virt_addr 0x%x size 0x%x", alloc_ptr, *ret_virt_addr_offset, virt_addr_alloc, size);
//#endif
    if(ADSP_FAILED(qurt_elite_memorymap_cache_flush(virt_addr_alloc, size)))
    {
      MSG_2( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_malloc Failed to flush "
             "cache for virt_addr 0x%x size 0x%x", virt_addr_alloc, size);

    }

    break;
  }

  if ( rc != ADSP_EOK && NULL != alloc_ptr )
  {
    qurt_elite_memory_heapmgr_aligned_free( alloc_ptr, ( QURT_ELITE_HEAP_ID )adsp_mdf_node->adsp_shmem_heap_id );
    alloc_ptr = NULL;
  }

  return alloc_ptr;

}

void elite_mem_mdf_mem_free( void* ptr, uint32_t mem_map_handle, uint32_t size )
{

  avs_elite_mdf_local_mapping_node_t* adsp_mdf_node;
  avs_elite_list_node_t* pivot_node;
  avs_elite_list_node_t* pivot_node2;
  avs_elite_mdf_proc_info_node_t* remot_proc_node;
  bool_t found_remote_node = FALSE;
  uint32_t cache_align_size = L2_LINESIZE;

  size  =  size + (cache_align_size  - size % cache_align_size);  // Making the size a multiple of 64 bytes.

  if ( NULL == ptr )
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_mem_free, NULL pointer .." );
    return;
  }

  pivot_node = &avs_mdf_local_memhandle_list.pivot_node;

  while ( pivot_node->next != ( &avs_mdf_local_memhandle_list.pivot_node ) )
  {

    adsp_mdf_node = ( avs_elite_mdf_local_mapping_node_t* )pivot_node->next;

    pivot_node2 = &( adsp_mdf_node->mdf_remote_list.pivot_node );

    while ( pivot_node2->next != &( adsp_mdf_node->mdf_remote_list.pivot_node ) )
    {
      remot_proc_node = ( avs_elite_mdf_proc_info_node_t* )pivot_node2->next;

      if ( remot_proc_node->remote_mem_map_handle == mem_map_handle )
      {
       found_remote_node = TRUE;
       break;
      }
      pivot_node2 = pivot_node2->next;
    }

    if ( TRUE == found_remote_node )
    {
      break;
    }

    pivot_node = pivot_node->next;
  }

  if ( FALSE == found_remote_node )
  {
    MSG_1( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_mem_free, "
           "mem handle not found!!.0x08X..", mem_map_handle );
    return;
  }

  uint32_t virt_addr = (uint32_t)ptr;
//#ifdef ELITEMEM_UTIL_DEBUG
  MSG_2( MSG_SSID_QDSP6, DBG_ERROR_PRIO, "EliteMem: elite_mem_mdf_mem_free, "
           "Virt Addr is 0x%x.. size is 0x%x", virt_addr,size );
//#endif
  (void)qurt_elite_memorymap_cache_invalidate(virt_addr, size);

  qurt_elite_memory_heapmgr_aligned_free( ptr, ( QURT_ELITE_HEAP_ID )adsp_mdf_node->adsp_shmem_heap_id );

}


