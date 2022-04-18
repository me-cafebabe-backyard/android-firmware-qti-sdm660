/*========================================================================
   This file contains HWD device configuration functions

  Copyright (c) 2009-2017 QUALCOMM Technologies, Inc. (QTI).  All Rights Reserved.
  QUALCOMM Technologies, Inc. (QTI) Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.
 
  $Header: //components/rel/avs.adsp/2.8/afe/drivers/hw/lpm/src/afe_lpm.c#5 $
 ====================================================================== */

/*==========================================================================
  Include files
  ========================================================================== */
#include "DALSys.h"
#include "DALSysTypes.h"

#include "common.h"
#include "lpasshwio_devcfg.h"
#include "hwd_devcfg.h"
#include "afe_lpm.h"
#include "qurt_elite.h"
#include <stringl.h>

#if (ADSPPM_INTEGRATION==1)
#include "mmpm.h"
#endif //ADSPPM_INTEGRATION==1

extern uint32_t g_lpm_ahb_voting_scale_factor;

ADSPResult afe_mem_req_rel_lpm_bw(uint32_t *core_id_ptr, bool_t is_release_flag);
ADSPResult afe_mem_req_rel_lpm_power(uint32_t *core_id_ptr, bool_t is_release_flag);
ADSPResult afe_mem_register_lpm_core(uint32_t* lpm_core_id_ptr );
ADSPResult afe_mem_unregister_lpm_core(uint32_t* lpm_core_id_ptr );

extern qurt_elite_globalstate_t qurt_elite_globalstate;

/* Static variable declarations */
typedef struct g_lpm_info_t
{
   qurt_mem_region_t lpm_reg;
   /* Qurt memory region */
   bool_t is_cached;
   /* Whether LPM is cached or not.
    * True: Cached
    * False: Uncached */
}g_lpm_info_t;

typedef struct remote_client_lpm_info_t
{
  uint32_t size_in_bytes;
  /* Size of LPM allocated to remote client */
  uint32_t phy_addr_lsw;
  /* Lower 32 bits of the phy addr returned */
  uint32_t phy_addr_msw;
  /* Higher 32 bits of the phy addr returned */
  bool_t is_allocated;
  /* Whether LPM has already been allocated once.
   * True: Allocated. No more allocations allowed
   * False: Not allocated */
  bool_t is_release_pending;
  /* To track if LPM release request is pending.
   * True: Pending. Request received when a use case was running.
   *       Will be served after use case ends.
   * False: Not pending. Request received at a valid time. Okay to release LPM */
}remote_client_lpm_info_t;

static g_lpm_info_t g_lpm_info;
lpm_prop_struct_t *glob_lpm_prop_ptr = NULL;
remote_client_lpm_info_t remote_client_lpm_info = {0, 0, 0, FALSE, FALSE};
static uint32 lpm_client_reg_count = 0;

bool_t lpm_is_it_cached()
{
   return g_lpm_info.is_cached;
}

ADSPResult lpm_init(void)
{
   DALSYSPropertyVar prop_value;
   DALSYS_PROPERTY_HANDLE_DECLARE(handle);
   const char *dev_id="LPM";
  
   /* Get handle to the device */
   if(DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr(dev_id, handle))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "DALSYS_GetDALPropertyHandleStr failed, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   if(DAL_SUCCESS != DALSYS_GetPropertyValue(handle,"LPMPropStructPtr", 0, &prop_value))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "DALSYS_GetPropertyValue failed, LPM cannot be used!");
      return ADSP_EFAILED;
   }

   glob_lpm_prop_ptr = (lpm_prop_struct_t*)(prop_value.Val.pStruct);

   g_lpm_info.is_cached = TRUE;
   qurt_elite_globalstate.is_lpm_cached = TRUE;

   if(QURT_MEM_CACHE_NONE_SHARED == glob_lpm_prop_ptr->cache_attribute)
   {
      g_lpm_info.is_cached = FALSE;
      qurt_elite_globalstate.is_lpm_cached = FALSE;
   }

   /* Getting the LPM AHB bus voting scale factor from Device config */
   g_lpm_ahb_voting_scale_factor = glob_lpm_prop_ptr->ahb_voting_scale_factor;

   //check the size
   if (0 == glob_lpm_prop_ptr->size || 0 == glob_lpm_prop_ptr->base_phy_addr)
   {
       //LPM not present, nothing to do
       return ADSP_EOK;
   }

   return ADSP_EOK;
}


ADSPResult lpm_deinit(void)
{
   return ADSP_EOK;
}


//***************************************************************************
// Global state structure for resource monitoring & debugging
//***************************************************************************

// heap id of AFE DMA buffers used in LPA
QURT_ELITE_HEAP_ID elite_mem_lpm_heap_id = QURT_ELITE_HEAP_DEFAULT;


#define RELEASE_RESOURCE    TRUE
#define REQUEST_RESOURCE    FALSE



ADSPResult afe_lpm_client_register(void)
{
   ADSPResult result;

   MSG(MSG_SSID_QDSP6, DBG_LOW_PRIO,"Entering afe_lpm_client_register");


   // check if this is the first time this function is being called
   // if first time, only then create the LPM region and heap manager
   if(0 == lpm_client_reg_count)
   {
       MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM client registering");
       lpm_client_reg_count++;
   }
   else
   {
	   lpm_client_reg_count++;
	   return ADSP_EOK;
   }

   uint32_t phy_addr_lsw = (uint32_t) (glob_lpm_prop_ptr->base_phy_addr & 0xffffffff);
   uint32_t phy_addr_msw = (uint32_t) ((glob_lpm_prop_ptr->base_phy_addr >> 32) & 0xffffffff) ;
   MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM base physical address MSW = 0x%lx, LSW = 0x%lx. Size = %lu",
         phy_addr_msw, phy_addr_lsw, glob_lpm_prop_ptr->size);

     //Query the LPM memory pool. This needs to go away once
     //we define a generic LPASS driver pool
     qurt_mem_pool_t pool = 0;

     char pool_name[]="ADSP_DRIVER_POOL";
     int res = qurt_mem_pool_attach(pool_name, &pool);

     if (QURT_EOK != res)
     {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to attach to memory pool, LPM cannot be used!");
        return ADSP_EFAILED;
     }

     //initialize region attributes
     qurt_mem_region_attr_t reg_attr;
     qurt_mem_region_attr_init(&reg_attr);

     qurt_mem_region_attr_set_cache_mode(&reg_attr, glob_lpm_prop_ptr->cache_attribute);
     qurt_mem_region_attr_set_mapping(&reg_attr, QURT_MEM_MAPPING_PHYS_CONTIGUOUS);
     qurt_mem_region_attr_set_physaddr(&reg_attr, (qurt_addr_t) phy_addr_lsw);
     qurt_mem_region_attr_set_type(&reg_attr, QURT_MEM_REGION_LOCAL);

     //create the region
     res = qurt_mem_region_create(&g_lpm_info.lpm_reg, glob_lpm_prop_ptr->size, pool, &reg_attr);

     if (QURT_EOK != res)
     {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to create memory region, LPM cannot be used!");
        return ADSP_EFAILED;
     }

     //get updated attributes
     res = qurt_mem_region_attr_get(g_lpm_info.lpm_reg, &reg_attr);

     if (QURT_EOK != res)
     {
        MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to get memory region attributes, LPM cannot be used!");
        afe_lpm_client_deregister();
        return ADSP_EFAILED;
     }

     uint32_t virt_addr = 0;
     qurt_mem_region_attr_get_virtaddr(&reg_attr, (unsigned int *) (&virt_addr));

     MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM virtual address = 0x%lx", virt_addr);

     //fill up the buffer details
     qurt_elite_globalstate_t *glob_state = &qurt_elite_globalstate;
     uint64_t phy_addr = glob_lpm_prop_ptr->base_phy_addr;

     //store base addr and size in global state
     glob_state->lpm_virt_addr = virt_addr;
     glob_state->lpm_size = glob_lpm_prop_ptr->size;

     if (glob_lpm_prop_ptr->size_afe_dma_buf != 0)
     {
         glob_state->lpm_afe_dma_buf.phy_addr = phy_addr;
         glob_state->lpm_afe_dma_buf.virt_addr = virt_addr;
         glob_state->lpm_afe_dma_buf.size = glob_lpm_prop_ptr->size_afe_dma_buf;

         /*Initializing heap manager for AFE DMA buffer in LPM*/
         if (ADSP_FAILED(result = qurt_elite_memory_heapmgr_create(&elite_mem_lpm_heap_id,
                     (void *) qurt_elite_globalstate.lpm_afe_dma_buf.virt_addr, qurt_elite_globalstate.lpm_afe_dma_buf.size)))
         {
             MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to initialize heap manager for AFE DMA buffers!!\n");
             return ADSP_EFAILED;
         }
     }

   qurt_elite_globalstate.lpm_heapid = elite_mem_lpm_heap_id;

   MSG(MSG_SSID_QDSP6, DBG_LOW_PRIO,"Leaving afe_lpm_client_register");

   return ADSP_EOK;
}

ADSPResult afe_lpm_client_deregister(void)
{
   MSG(MSG_SSID_QDSP6, DBG_LOW_PRIO,"Entering afe_lpm_client_deregister");

   // check if this is the last free to be done
   // if last, then destroy the LPM region and heap manager
   if (lpm_client_reg_count)
   {
       lpm_client_reg_count--;

       if (0 == lpm_client_reg_count)
       {
    	   MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM client deregistering");

    	   // delete heap manager for AFE DMA buffers in LPM
    	   if (qurt_elite_globalstate.lpm_afe_dma_buf.size != 0)
    	   {
    	       qurt_elite_memory_heapmgr_delete(elite_mem_lpm_heap_id);
    	   }

    	   if (0 != g_lpm_info.lpm_reg)
    	   {
    	       qurt_mem_region_delete(g_lpm_info.lpm_reg);
    	       g_lpm_info.lpm_reg = 0;
    	   }

         if (remote_client_lpm_info.is_release_pending)
         {
             /* At this point all validations are successful, so we just have to increase the size of LPM available to AFE */
             glob_lpm_prop_ptr->size = glob_lpm_prop_ptr->size + remote_client_lpm_info.size_in_bytes;
             glob_lpm_prop_ptr->size_afe_dma_buf = glob_lpm_prop_ptr->size_afe_dma_buf + remote_client_lpm_info.size_in_bytes;
             remote_client_lpm_info.is_allocated = FALSE;
             remote_client_lpm_info.is_release_pending = FALSE;
             MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Remote client released LPM of size = %lu. Total available LPM : %lu", remote_client_lpm_info.size_in_bytes, glob_lpm_prop_ptr->size);
         }
       }
   }
   else
   {
	   MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "LPM client already deregistered");
	   return ADSP_EFAILED;
   }

   MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO,"Leaving afe_lpm_client_deregister. LPM clients active: %lx", lpm_client_reg_count);

   return ADSP_EOK;
}

ADSPResult afe_request_lpm_resources_by_remote_client_handler(void *ptr)
{
	elite_apr_packet_t *rsp_apr_pkt_ptr = NULL;
	int32_t result = APR_EOK;
	int32_t rc = APR_EOK;
	uint32_t rsp_pkt_size = 0;
	void *apr_rsp_payload_ptr = NULL;
	elite_apr_packet_t *apr_pkt_ptr = (elite_apr_packet_t *)ptr;

	if (elite_apr_if_get_payload_size(apr_pkt_ptr) < \
	      (sizeof(afe_cmd_request_lpm_resources))+(sizeof(afe_cmd_request_lpass_resources)))
	{
	  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Apr payload of insufficient size received for LPM resources");
	  result = ADSP_EUNEXPECTED;
	  goto afe_request_lpm_resources_error_1;
	}

	/* Parse command payload */
	int8_t *apr_payload_ptr;
	afe_cmd_request_lpm_resources *cmd_payload_ptr;
	apr_payload_ptr = (int8_t *)(elite_apr_if_get_payload_ptr(apr_pkt_ptr));
	/* Get the actual payload for LPM request */
	cmd_payload_ptr = (afe_cmd_request_lpm_resources *)(apr_payload_ptr + sizeof(afe_cmd_request_lpass_resources));

    if (NULL == cmd_payload_ptr)
	{
	  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "apr_payload_ptr is NULL");
	  result = ADSP_EUNEXPECTED;
	  goto afe_request_lpm_resources_error_1;
	}

	/* Calculate response apr packet size */
	rsp_pkt_size = sizeof(afe_cmdrsp_request_lpass_resources)  + \
			       sizeof(afe_cmdrsp_request_lpm_resources);

	/* Allocate the return packet */
	if (APR_EOK != (result = elite_apr_if_alloc_cmd_rsp(afe_svc_global_ptr->apr_handle,
	                                                elite_apr_if_get_dst_addr(apr_pkt_ptr),
	                                                elite_apr_if_get_dst_port(apr_pkt_ptr),
	                                                elite_apr_if_get_src_addr(apr_pkt_ptr),
	                                                elite_apr_if_get_src_port(apr_pkt_ptr),
	                                                elite_apr_if_get_client_token(apr_pkt_ptr),
	                                                AFE_CMDRSP_REQUEST_LPASS_RESOURCES,
	                                                rsp_pkt_size, &rsp_apr_pkt_ptr)))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, \
	        "AFE_SVC_CMD_REQUEST_LPASS_RESOURCES Response packet allocation failed  = %ld!", result);
	  result = ADSP_EFAILED;
	  goto afe_request_lpm_resources_error_1;
	}

	if (NULL == rsp_apr_pkt_ptr)
	{
	  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, \
	      "APR Response packet allocation failed. pPacket is NULL");
	  result = ADSP_ENOMEMORY;
	  goto afe_request_lpm_resources_error_1;
	}

	/* Get the response payload */
	elite_apr_if_get_payload((void **)(&apr_rsp_payload_ptr), rsp_apr_pkt_ptr);
	afe_cmdrsp_request_lpm_resources *lpm_rsp_payload_ptr;
	afe_cmdrsp_request_lpass_resources    *lpass_resource_rsp_payload_ptr;
	lpass_resource_rsp_payload_ptr = (afe_cmdrsp_request_lpass_resources *)apr_rsp_payload_ptr;
	lpm_rsp_payload_ptr = (afe_cmdrsp_request_lpm_resources *)(lpass_resource_rsp_payload_ptr+1);

	/* Fill the response payload ptr with success values */
	lpass_resource_rsp_payload_ptr->status       =  ADSP_EOK;
	lpass_resource_rsp_payload_ptr->resource_id  =  AFE_LPM_RESOURCE_ID;
	lpm_rsp_payload_ptr->size_in_bytes       =  cmd_payload_ptr->size_in_bytes;

	/* Check if any use case is running. If it is, error out. */
	if (0 != lpm_client_reg_count)
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Remote client LPM request failed! Use case already running. LPM clients active: %lx", lpm_client_reg_count);
	  result = ADSP_EFAILED;
	  goto afe_request_lpm_resources_response;
	}

	/* Check if LPM has already been allocated once to remote client. If it has, error out. */
	if (remote_client_lpm_info.is_allocated)
	{
	  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Remote client LPM already allocated once. Another request not allowed before releasing previous");
	  result = ADSP_EFAILED;
	  goto afe_request_lpm_resources_response;
	}

	MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Remote client requested LPM of size = %lu",
	      cmd_payload_ptr->size_in_bytes);

	if (cmd_payload_ptr->size_in_bytes > glob_lpm_prop_ptr->size)
	{
	  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Requested LPM of size = %lu is greater than available LPM of size = %lu",
	        cmd_payload_ptr->size_in_bytes, glob_lpm_prop_ptr->size);
	  result = ADSP_EFAILED;
	  goto afe_request_lpm_resources_response;
	}

  /* Calculate the phy addr to return to remote client. */

  /* Actual phy addr to return will be = (Base addr of LPM + size of LPM) - size of LPM requested by remote client */
	uint64_t phy_addr = glob_lpm_prop_ptr->base_phy_addr + glob_lpm_prop_ptr->size - cmd_payload_ptr->size_in_bytes;
	lpm_rsp_payload_ptr->phy_addr_lsw = (uint32_t) (phy_addr & 0xffffffff);
	lpm_rsp_payload_ptr->phy_addr_msw = (uint32_t) ((phy_addr >> 32) & 0xffffffff);

	MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Remote client requested LPM base physical address MSW = 0x%lx, LSW = 0x%lx. Size = %lu",
	      lpm_rsp_payload_ptr->phy_addr_msw, lpm_rsp_payload_ptr->phy_addr_lsw, lpm_rsp_payload_ptr->size_in_bytes);

	/* Reduce the size of available LPM for AFE */
	glob_lpm_prop_ptr->size = glob_lpm_prop_ptr->size - lpm_rsp_payload_ptr->size_in_bytes;
	glob_lpm_prop_ptr->size_afe_dma_buf = glob_lpm_prop_ptr->size_afe_dma_buf - lpm_rsp_payload_ptr->size_in_bytes;

	MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Size of LPM left after remote client request = %lu", glob_lpm_prop_ptr->size);

	afe_request_lpm_resources_response:
	/* If any allocation failed, then send AFE_LPM_INVALID_REQUEST in response. */
	if (ADSP_FAILED(result))
	{
		lpass_resource_rsp_payload_ptr->status = ADSP_EFAILED;
		lpm_rsp_payload_ptr->size_in_bytes = AFE_LPM_INVALID_REQUEST;
		lpm_rsp_payload_ptr->phy_addr_lsw = AFE_LPM_INVALID_REQUEST;
		lpm_rsp_payload_ptr->phy_addr_msw = AFE_LPM_INVALID_REQUEST;

		MSG_1(MSG_SSID_QDSP6,DBG_ERROR_PRIO, "Error in allocating LPM resources: 0x%x",result);
	}

	/* Send response packet out */
	if (APR_EOK != (rc = elite_apr_if_async_send(afe_svc_global_ptr->apr_handle, rsp_apr_pkt_ptr)))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "afe_remote_lpm_resources_reqeust Response send failed  = %ld!", rc);
	  result = ADSP_EFAILED;
	  goto afe_request_lpm_resources_error_2;
	}

	/* Cache the values only if allocation is successful. */
	if (APR_EOK == result)
	{
	  /* Store the allocated address and size for validation during release request */
	  remote_client_lpm_info.size_in_bytes = lpm_rsp_payload_ptr->size_in_bytes;
	  remote_client_lpm_info.phy_addr_lsw = lpm_rsp_payload_ptr->phy_addr_lsw;
	  remote_client_lpm_info.phy_addr_msw = lpm_rsp_payload_ptr->phy_addr_msw;
	  remote_client_lpm_info.is_allocated = TRUE;
	}

	/* free the original packet */
	(void)elite_apr_if_free(afe_svc_global_ptr->apr_handle, apr_pkt_ptr);

	return ADSP_EOK;

	afe_request_lpm_resources_error_2:
	/* Free response packet */
	(void)elite_apr_if_free(afe_svc_global_ptr->apr_handle, rsp_apr_pkt_ptr);

	afe_request_lpm_resources_error_1:
	/* ack back the apr packet */
	(void)elite_apr_if_end_cmd(afe_svc_global_ptr->apr_handle, apr_pkt_ptr, result);
	return result;
}

ADSPResult afe_release_lpm_resources_by_remote_client_handler(void *ptr)
{
  ADSPResult result = APR_EOK;
  uint32_t expected_apr_pkt_size=0;
  elite_apr_packet_t *apr_pkt_ptr = (elite_apr_packet_t *)ptr;

  if (!apr_pkt_ptr)
  {
    return ADSP_EBADPARAM;
  }
  /* parse command payload */
  /* This ptr is already validated before calling this function */
  afe_cmd_release_lpass_resources *apr_payload_ptr;
  apr_payload_ptr = (afe_cmd_release_lpass_resources *)(elite_apr_if_get_payload_ptr(apr_pkt_ptr));

  afe_cmd_release_lpm_resources *cmd_payload_ptr;
  cmd_payload_ptr = (afe_cmd_release_lpm_resources *)(apr_payload_ptr + 1);

  if (cmd_payload_ptr == NULL)
  {
    result = ADSP_EFAILED;
    MSG(MSG_SSID_QDSP6,DBG_ERROR_PRIO," Null pointer for APR payload");
    goto afe_release_lpm_resources_error;
  }

  /*apr pkt size should be sizeof(afe_cmd_release_lpass_resources)+
     afe_cmd_release_lpm_resources */
  expected_apr_pkt_size = sizeof(afe_cmd_release_lpass_resources)+\
                          sizeof(afe_cmd_release_lpm_resources);

  if (elite_apr_if_get_payload_size(apr_pkt_ptr) < expected_apr_pkt_size)
  {
    MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Apr payload of insufficient size received for AFE_SVC_CMD_RELEASE_LPM_RESOURCES");
    result = ADSP_EUNEXPECTED;
    goto afe_release_lpm_resources_error;
  }

  /*Do the actual processing for releasing resources*/
  {
    /* first validate the given payload.If validation is failed, just return the error code*/
    /* We are not freeing any resources if validation is failed*/
    /* This validation checks whether HLOS sending the same resources which are allocated in request command */
  if ((remote_client_lpm_info.size_in_bytes != cmd_payload_ptr-> size_in_bytes) || \
      (remote_client_lpm_info.phy_addr_lsw != cmd_payload_ptr->phy_addr_lsw) || \
      (remote_client_lpm_info.phy_addr_msw != cmd_payload_ptr->phy_addr_msw))
    {
      MSG(MSG_SSID_QDSP6,DBG_ERROR_PRIO, "Received LPM address which is not allocated to HLOS, erroring out");
      result = ADSP_EFAILED;
      goto afe_release_lpm_resources_error;
    }

	/* This validation checks if any use case is running which is using LPM. */
	if (0 != lpm_client_reg_count)
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Remote client LPM release failed. Use case running. LPM clients active: %lx. Will release when all clients have deregistered", lpm_client_reg_count);
    remote_client_lpm_info.is_release_pending = TRUE;
	  result = ADSP_EOK;
	  goto afe_release_lpm_resources_error;
	}

    /* At this point all validations are successful, so we can release the resources*/
	glob_lpm_prop_ptr->size = glob_lpm_prop_ptr->size + cmd_payload_ptr->size_in_bytes;
	glob_lpm_prop_ptr->size_afe_dma_buf = glob_lpm_prop_ptr->size_afe_dma_buf + cmd_payload_ptr->size_in_bytes;
  remote_client_lpm_info.is_allocated = FALSE;
  remote_client_lpm_info.is_release_pending = FALSE;
  MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Remote client released LPM of size = %lu. Total available LPM : %lu", cmd_payload_ptr->size_in_bytes, glob_lpm_prop_ptr->size);
  }

  afe_release_lpm_resources_error:
  /* end command */
  (void)elite_apr_if_end_cmd(afe_svc_global_ptr->apr_handle, apr_pkt_ptr, result);
  return result;
}


#define ADSPPM_NULL_HANDLE 0

ADSPResult afe_mem_register_lpm_core(uint32_t* lpm_core_id_ptr )
{
    if (!lpm_core_id_ptr)
    {
        return ADSP_EFAILED;
    }

#if (ADSPPM_INTEGRATION==1)

   //register LPM core with ADSPPM
   char client_name[]="AFE_LPM";      
   MmpmRegParamType regParam;

   regParam.rev             = MMPM_REVISION;
   regParam.instanceId      = MMPM_CORE_INSTANCE_0;
   regParam.pwrCtrlFlag     = PWR_CTRL_NONE; //PWR_CTRL_STATIC_DISPLAY, PWR_CTRL_THERMAL
   regParam.callBackFlag    = CALLBACK_NONE; //CALLBACK_STATIC_DISPLAY, CALLBACK_THERMAL, CALLBACK_REQUEST_COMPLETE
   regParam.MMPM_Callback   = NULL;
   regParam.cbFcnStackSize  = 0;
   regParam.coreId          = MMPM_CORE_ID_LPASS_LPM;
   regParam.pClientName     = client_name;

   if (ADSPPM_NULL_HANDLE == (*lpm_core_id_ptr = MMPM_Register_Ext(&regParam)))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MMPM_Register_Ext for AFE LPM core failed");
      return ADSP_EFAILED;
   }
   else
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MMPM client for AFE LPM core %lu", *lpm_core_id_ptr);
      
   }

    //Register for client class as Audio to ADSPPM.
    MmpmClientClassType class_type = MMPM_AUDIO_CLIENT_CLASS;
    MmpmParameterConfigType param_cfg;
    param_cfg.pParamConfig = (void*)&class_type;
    param_cfg.paramId = MMPM_PARAM_ID_CLIENT_CLASS;
    MMPM_STATUS status = MMPM_SetParameter(*lpm_core_id_ptr, &param_cfg);
    if(status != MMPM_STATUS_SUCCESS)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MMPM_SetParameter class type failed for client id %lu with status %lu "
            , *lpm_core_id_ptr,(uint32_t)status);
    }
    else
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MMPM_SetParameter class type success for client id %lu"
            ,*lpm_core_id_ptr);
    }
  
    //Register for DCVS up only
    //LPM's core/bus votes are subject to automatic up adjustment by DCVS
    MmpmDcvsParticipationType dcvs_participation;
    dcvs_participation.enable = TRUE;
    dcvs_participation.enableOpt = MMPM_DCVS_ADJUST_ONLY_UP;
    param_cfg.pParamConfig = (void*)&dcvs_participation;
    param_cfg.paramId = MMPM_PARAM_ID_DCVS_PARTICIPATION;
    status = MMPM_SetParameter(*lpm_core_id_ptr, &param_cfg);
    if(status != MMPM_STATUS_SUCCESS)
    {
      MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MMPM_SetParameter DCVS participation for Only UP failed for client id %lu"
                                           " with status %lu ", *lpm_core_id_ptr, (uint32_t)status);
    }
    else
    {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "MMPM_SetParameter DCVS participation for Only UP success for client id %lu ", 
            *lpm_core_id_ptr);
    }


#endif //ADSPPM_INTEGRATION==1
   return ADSP_EOK;
}


ADSPResult afe_mem_unregister_lpm_core(uint32_t* lpm_core_id_ptr )
{
    if (!lpm_core_id_ptr)
    {
        return ADSP_EFAILED;
    }

#if (ADSPPM_INTEGRATION==1)
   //unregister LPM core with ADSPPM
   if (ADSPPM_NULL_HANDLE != *lpm_core_id_ptr)
   {
      if (MMPM_STATUS_SUCCESS != MMPM_Deregister_Ext(*lpm_core_id_ptr))
      {
         MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "MMPM_Deregister_Ext for AFE LPM core failed");
         return ADSP_EFAILED;
      }
      else
      {
         *lpm_core_id_ptr = ADSPPM_NULL_HANDLE;
      }
   }
#endif //(ADSPPM_INTEGRATION==1)
   return ADSP_EOK;

}


ADSPResult afe_mem_req_rel_lpm_power(uint32_t *core_id_ptr, bool_t is_release_flag)
{
    ADSPResult result = ADSP_EOK;

    if (!core_id_ptr)
    {
        return ADSP_EFAILED;
    }

#if (ADSPPM_INTEGRATION==1)

   #define NUM_REQUEST 1
   MmpmRscParamType rscParam[NUM_REQUEST];
   MMPM_STATUS      retStats[NUM_REQUEST];
   rscParam[0].rscId          = MMPM_RSC_ID_POWER;
   //rscParam[0].rscParam     = NULL; not applicable.

   MmpmRscExtParamType reqParam;
   reqParam.apiType                    = MMPM_API_TYPE_SYNC;
   reqParam.numOfReq                   = NUM_REQUEST;
   reqParam.pExt                       = NULL;     //for future
   reqParam.pReqArray                  = rscParam;
   reqParam.pStsArray                  = retStats; //for most cases mmpmRes is good enough, need not check this array.
   reqParam.reqTag                     = NULL;     //for async only

   MMPM_STATUS mmpmRes;
   if (is_release_flag)
   {
      mmpmRes = MMPM_Release_Ext(*core_id_ptr, &reqParam);
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"AFE LPM releasing power for core id %lu",*core_id_ptr);
   }
   else
   {
      mmpmRes = MMPM_Request_Ext(*core_id_ptr, &reqParam);
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO,"AFE LPM requesting power for core id %lu",*core_id_ptr);
   }

   if(MMPM_STATUS_SUCCESS != mmpmRes)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADSPPM_Request/release for power failed for core id %lu", *core_id_ptr);
      result = ADSP_EFAILED;
   }
   else
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADSPPM_Request/release for power success for core id %lu", *core_id_ptr);
   }

#endif //(ADSPPM_INTEGRATION==1)

   return result;
}



ADSPResult afe_mem_req_rel_lpm_bw(uint32_t *core_id_ptr, bool_t is_release_flag)
{
    ADSPResult result = ADSP_EOK;

    if (!core_id_ptr)
    {
        return ADSP_EFAILED;
    }

#if (ADSPPM_INTEGRATION==1)
    uint32_t adsp_lpm_kbps;
    uint32_t adsp_lpm_usage;

    if (is_release_flag)
    {
        adsp_lpm_kbps     = 0;
        adsp_lpm_usage    = 0;
    }
    else
    {
        adsp_lpm_kbps     = 100;
        adsp_lpm_usage    = 100;

    }

   MMPM_STATUS mmpmRes;
   MmpmRscExtParamType reqParam;
   reqParam.apiType  = MMPM_API_TYPE_SYNC;

   uint32_t numBw = 0, adsp_lpm_ind;
   MmpmGenBwValType bwArr[1];

   //previously MMPM_AUD_BW_TYPE_CPU , MMPM_AUD_BW_PORT_LPM, MMPM_AUD_BW_PORT_LPM
   adsp_lpm_ind = numBw;
   bwArr[numBw].busRoute.masterPort                 = MMPM_BW_PORT_ID_ADSP_MASTER;
   bwArr[numBw].busRoute.slavePort                  = MMPM_BW_PORT_ID_LPM_SLAVE;
   bwArr[numBw].bwValue.busBwValue.bwBytePerSec     = adsp_lpm_kbps*1024/8;
   bwArr[numBw].bwValue.busBwValue.usagePercentage  = adsp_lpm_usage;
   bwArr[numBw].bwValue.busBwValue.usageType        = MMPM_BW_USAGE_LPASS_DSP;
   numBw++; //1

   MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO,
       "AFE MEM requesting ADSPPM (BW bytesPerSec, Usage perc): ADSP LPM (0x%lx%lx, %ld)",
       (uint32_t)(bwArr[adsp_lpm_ind].bwValue.busBwValue.bwBytePerSec>>32),(uint32_t)bwArr[adsp_lpm_ind].bwValue.busBwValue.bwBytePerSec,
       (uint32_t)bwArr[adsp_lpm_ind].bwValue.busBwValue.usagePercentage);


    MmpmGenBwReqType bwReq;
    bwReq.numOfBw            = numBw;
    bwReq.pBandWidthArray    = bwArr;

    #define NUM_REQUEST 1
    MmpmRscParamType rscParam[NUM_REQUEST];
    MMPM_STATUS      retStats[NUM_REQUEST];
    rscParam[0].rscId                   = MMPM_RSC_ID_GENERIC_BW;
    rscParam[0].rscParam.pGenBwReq      = &bwReq;

    reqParam.numOfReq                   = NUM_REQUEST;
    reqParam.pExt                       = NULL;     //for future
    reqParam.pReqArray                  = rscParam;
    reqParam.pStsArray                  = retStats; //for most cases mmpmRes is good enough, need not check this array.
    reqParam.reqTag                     = NULL;     //for async only

    //for BW any client Id is fine (independent if DML, or some other). Actually client id is specific only for power, register access.
    if(is_release_flag)
    {
        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADSPPM_Release for AFE LPM BW\n");
        mmpmRes = MMPM_Release_Ext(*core_id_ptr, &reqParam);
        
    }
    else
    {

        MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADSPPM_Request for AFE LPM BW\n");
        mmpmRes = MMPM_Request_Ext(*core_id_ptr, &reqParam);

    }

    if(MMPM_STATUS_SUCCESS != mmpmRes)
    {
       MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "ADSPPM_Request/Release for AFE LPM BW failed\n");
       result = ADSP_EFAILED;
    }
    else
    {
       MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "ADSPPM_Request/Release for AFE LPM BW success\n");
    }

#endif //(ADSPPM_INTEGRATION==1)

   return result;

}

#ifdef AFE_SSR_DUMP_LPM_MEM
ADSPResult afe_ssr_lpm_dump(void *dump_ptr,  uint64_t lpm_virt_addr, size_t size)
{
   ADSPResult result = ADSP_EOK;

   if (size != 0)
   {

      /* Copy the LPM content into global buffer */
      memscpy(dump_ptr,
              size,
             (void *)lpm_virt_addr,
             size);
   }

   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "LPM size[%d] is LPM addr:0x%lx]", size, lpm_virt_addr);
   
   return result;    
}
#endif
