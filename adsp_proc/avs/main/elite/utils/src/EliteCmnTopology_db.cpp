/*==========================================================================
EliteCmnTopology_db.cpp

This file implements the common global topology database.

   Copyright (c) 2015, 2017-2018 QUALCOMM Technologies, Incorporated.
   All Rights Reserved.
   QUALCOMM Technologies Proprietary.

Edit History

when        who    what, where, why
--------        ---      ---------------------------------------------------------
03/13/15   KR     Created file.
05/24/2017 sranumul   Added OLM Topo utils.
=========================================================================== */

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "qurt_elite.h"
#include "EliteCmnTopology_db_if.h"
#include "EliteCmnTopology_db.h"

#define UINT32_MAX  0xffffffff

#define THIS_PROC_ID ( AUDIO_DSP_PROC_ID )

typedef struct elite_cmn_topo_db_internal_entry_t elite_cmn_topo_db_internal_entry_t;

struct elite_cmn_topo_db_internal_entry_t
{
	uint32_t ref_count;
	bool_t is_active;
  elite_cmn_topo_type_t topo_type;
	uint32_t handle;
	elite_cmn_topo_db_internal_entry_t *next_ptr;
	uint32_t size;
	elite_cmn_topo_db_entry_t topo_entry;
  uint32_t num_olm_modules;       /* Number of OLM instances in the updated topology */
  elite_cmn_olm_topo_db_entry_t *olm_topos;     /* OLM topology definition array*/
};

struct elite_cmn_topo_db_t
{
	uint32_t handle_generator;
	qurt_elite_mutex_t db_lock;
	elite_cmn_topo_db_internal_entry_t *record_head_ptr;
	elite_cmn_topo_db_internal_entry_t *record_tail_ptr;
};

/*---------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/

static void elite_cmn_topo_db_destroy_db_entry(void);
static ADSPResult elite_cmn_topo_db_process_check_remove_topology(elite_cmn_topo_db_internal_entry_t *curr_ptr,elite_cmn_topo_db_internal_entry_t *prev_ptr);


/*---------------------------------------------------------------------------
 * Globals
 * -------------------------------------------------------------------------*/
elite_cmn_topo_db_t g_cmn_topology_db;

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

void elite_cmn_topo_db_init()
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	qurt_elite_mutex_init(&me_ptr->db_lock);
	me_ptr->handle_generator = 0;
	me_ptr->record_head_ptr = NULL;
	me_ptr->record_tail_ptr = NULL;
}

void elite_cmn_topo_db_deinit()
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	elite_cmn_topo_db_destroy_db_entry();
	qurt_elite_mutex_destroy(&me_ptr->db_lock);
	me_ptr->handle_generator = 0;
	me_ptr->record_head_ptr = NULL;
	me_ptr->record_tail_ptr = NULL;
}

/* Global counter for OLMs*/
uint16_t olm_global_count = 0;

bool_t is_offloaded_module(avcs_module_instance_proc_info_t *mod_info)
{
  return ((THIS_PROC_ID == mod_info->client_proc_id) ? FALSE: TRUE);
}

bool_t is_local_module(avcs_module_instance_proc_info_t *mod_info)
{
  return ((THIS_PROC_ID == mod_info->client_proc_id) ? TRUE: FALSE);
}


inline void elite_cmn_topo_db_copy_module_info_util(avcs_module_instance_proc_info_t *in_mod_ptr, /* Input module pointer */
                                                    avcs_module_instance_proc_info_t *out_mod_ptr /* Output module pointer */)
{
  /*
   *  Copy the module info
   */
  out_mod_ptr->module_id        = in_mod_ptr->module_id;
  out_mod_ptr->instance_id      = in_mod_ptr->instance_id;
  out_mod_ptr->client_proc_id   = in_mod_ptr->client_proc_id;
}

inline void  elite_cmn_topo_db_print_module_info(avcs_module_instance_proc_info_t *mod_info)
{
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
        "Module Info \n \
                    module_id      = 0x%lx \n \
                    instance_id    = %lu \n \
                    client_proc_id = 0x%x",
                    mod_info->module_id ,
                    mod_info->instance_id ,
                    mod_info->client_proc_id);
}

inline  void  elite_cmn_topo_db_print_db_topo_def_info(elite_cmn_topo_db_entry_t *db_entry_ptr)
{
  /*print topology info*/
  MSG_4(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
        "elite_cmn_topo_db_entry_t: \n \
                topology_id      = 0x%lx \n \
                topology_config  = %lu \n  \
                topology_version = %lu \n  \
                num_modules      = %lu",
                db_entry_ptr->topo_def.topology_id,
                db_entry_ptr->topo_def.topo_config,
                db_entry_ptr->topo_def.version,
                db_entry_ptr->topo_def.num_modules);

}


ADSPResult elite_cmn_topo_db_print_db_entry_info(elite_cmn_topo_db_entry_t *db_entry_ptr)
{
  ADSPResult result = ADSP_EOK;

  /*print topology info*/
  elite_cmn_topo_db_print_db_topo_def_info(db_entry_ptr);

  avcs_module_instance_proc_info_t *curr_mod = db_entry_ptr->module_info;
  for(uint32_t i =0; i <  db_entry_ptr->topo_def.num_modules; i++)
  {
    /* Print module info*/
    elite_cmn_topo_db_print_module_info(curr_mod);
    curr_mod++;
  }

  return result;
}


ADSPResult elite_cmn_topo_db_get_modules_count(avcs_topology_definition_t *topology_definition_ptr, /* Input: Topo defintion pointer */
                                               void *module_definition_ptr,    /* Input: Modules definition list ptr*/
                                               uint32_t *total_module_cnt,     /* Output: Updated modules count in topo*/
                                               uint32_t *olm_cnt               /* Output: Number of OLM modules in topo*/ )
{
  /* Initialize the counts*/
  uint32_t topo_version = topology_definition_ptr->version;

#ifdef DEBUG_ELITE_COMMON_TOPO
  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,  " Getting elite_cmn_topo_db_get_modules_count() ");
#endif

  if(0 == topo_version || 1 == topo_version)
  {
    /*Version 0 and 1 doesn't support OLM modules hence the olm_cnt will be zero*/
    *total_module_cnt = topology_definition_ptr->num_modules;
    return ADSP_EOK;
  }
  /*Enters this section only if the version is '2' */
  avcs_module_instance_proc_info_t *module_definition_src_ptr = (avcs_module_instance_proc_info_t*)module_definition_ptr;
  avcs_module_instance_proc_info_t *prev_src_module = NULL;

  uint32_t module_idx =1;
  *total_module_cnt =0;
  *olm_cnt = 0;
  while(module_idx <= topology_definition_ptr->num_modules)
  {
    /*Increment the updated module count*/
    (*total_module_cnt)++;

    if(is_local_module(module_definition_src_ptr))
    {
      module_definition_src_ptr++;
      module_idx++;
    }
    else
    {
      /* Increment topology's olm count*/
      (*olm_cnt)++;

      /**
       *  Check if the consecutive modules are of same client proc id. If consecutive modules exists,
       *  add all those offloaded modules under same proc id.
       */
      uint32_t check_next_module = TRUE;
      prev_src_module = module_definition_src_ptr++;
      module_idx++;

      while(check_next_module &&  module_idx <= topology_definition_ptr->num_modules )
      {
        if(prev_src_module->client_proc_id != module_definition_src_ptr->client_proc_id)
        {
          check_next_module = FALSE;
        }
        else
        {
          /* Assign prev module pointer and update the source module pointer */
          prev_src_module = module_definition_src_ptr++;
          module_idx++;
        }
      }
    }
  }

#ifdef DEBUG_ELITE_COMMON_TOPO
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_modules_count:  OLM count: %lu  Old module count: %lu New module count: %lu ",
        *olm_cnt, topology_definition_ptr->num_modules, *total_module_cnt);
#endif
  return ADSP_EOK;
}

/**
 * elite_update_topology_with_olms:
 *     1. Creates an updated topology with OLMs
 *     2. If topo_version is 0/1 then returns the the actual topology.
 *     3. Also stores topologies of all the OLM instances in a updated topology.
 */
ADSPResult elite_update_topology_with_olms(avcs_topology_definition_t *topology_definition_ptr,
                                           void * module_definition_ptr,
                                           elite_cmn_topo_db_internal_entry_t *db_entry_ptr)
{

#ifdef DEBUG_ELITE_COMMON_TOPO
  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_update_topology_with_olms()");
#endif
  ADSPResult result =  ADSP_EOK;

  if( NULL == topology_definition_ptr )
  {
    result = ADSP_EBADPARAM;
    return result;
  }

  if(0 == topology_definition_ptr->num_modules)
  {
    /* No modules to update the topology*/
    return result;
  }

  if(0 == topology_definition_ptr->version)
  {
    avcs_module_info_t *temp_module_definition_src_ptr = (avcs_module_info_t*)module_definition_ptr;

    avcs_module_instance_proc_info_t *module_definition_dest_ptr = db_entry_ptr->topo_entry.module_info;

    for (uint32_t module_idx = 0; module_idx < topology_definition_ptr->num_modules; module_idx++)
    {
      module_definition_dest_ptr->module_id = temp_module_definition_src_ptr->module_id;
      module_definition_dest_ptr->instance_id = 0; //hardcoding instance id to zero. Topo version remains zero.
      module_definition_dest_ptr->client_proc_id = THIS_PROC_ID; //Set the proc Id to current processor
      temp_module_definition_src_ptr++;
      module_definition_dest_ptr++;
    }
    return result;
  }

  else if(1 == topology_definition_ptr->version)
  {
    avcs_module_instance_info_t *temp_module_definition_src_ptr = (avcs_module_instance_info_t*)module_definition_ptr;

    avcs_module_instance_proc_info_t *module_definition_dest_ptr = db_entry_ptr->topo_entry.module_info;

    for (uint32_t module_idx = 0; module_idx < topology_definition_ptr->num_modules; module_idx++)
    {
      module_definition_dest_ptr->module_id = temp_module_definition_src_ptr->module_id;
      module_definition_dest_ptr->instance_id = temp_module_definition_src_ptr->instance_id;
      module_definition_dest_ptr->client_proc_id = THIS_PROC_ID; //Set the proc Id to current processor
      temp_module_definition_src_ptr++;
      module_definition_dest_ptr++;
    }

    return result;
  }

  else
  {
    /* Enters this section when version 2 */
    avcs_module_instance_proc_info_t *prev_src_module = NULL;

    avcs_module_instance_proc_info_t *module_definition_src_ptr = (avcs_module_instance_proc_info_t *) module_definition_ptr;

    avcs_module_instance_proc_info_t *module_definition_dest_ptr = db_entry_ptr->topo_entry.module_info;

    elite_cmn_olm_topo_db_entry_t *cur_olm_topo_ptr = db_entry_ptr->olm_topos;

    /* Get the olm Modules mem blob pointer, its allocated followed by the the olm DB etnries in elite_cmn_topo_db_internal_entry_t */
    avcs_module_instance_proc_info_t* olm_modules_mem_ptr = (avcs_module_instance_proc_info_t *) ((int8_t*) db_entry_ptr->olm_topos
        + ( sizeof(elite_cmn_olm_topo_db_entry_t) *(db_entry_ptr->num_olm_modules)) );

    uint32_t module_idx = 1;
    while(module_idx <= topology_definition_ptr->num_modules)
    {
      if(is_local_module(module_definition_src_ptr))
      {
        /* Copy module info from source to destination */
        elite_cmn_topo_db_copy_module_info_util(module_definition_src_ptr,module_definition_dest_ptr);

        /* Move to next src and destination module pointers*/
        module_definition_src_ptr++;
        module_definition_dest_ptr++;

        module_idx++;
      }
      else
      {
        /* Assign OLM Module ID */
        module_definition_dest_ptr->module_id = AVCS_ADSP_OLM_MODULE_ID;

        /* OLM instance ID is given based on the global OLM instance counter */
        module_definition_dest_ptr->instance_id = olm_global_count++;

        /* Copy the client proc id*/
        module_definition_dest_ptr->client_proc_id = THIS_PROC_ID;

#ifdef DEBUG_ELITE_COMMON_TOPO
        MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_update_topology_with_olms: Topology ID: 0x%lx New OLM module created IID: 0x%lx ",
              topology_definition_ptr->topology_id, module_definition_dest_ptr->instance_id);
#endif

        /*
         * Update OLM topology header information
         */
        /* Store the olm iid in topo*/
        cur_olm_topo_ptr->olm_iid = module_definition_dest_ptr->instance_id;

        /* Initialize the new OLM's module list array info */
        cur_olm_topo_ptr->num_modules = 1;

        /* store the base addr of OLM modules list array*/
        cur_olm_topo_ptr->module_info = olm_modules_mem_ptr;

        /* Push the first offloaded module to OLMs topo db entry */
        elite_cmn_topo_db_copy_module_info_util(module_definition_src_ptr,olm_modules_mem_ptr);
        olm_modules_mem_ptr++;

        prev_src_module = NULL;

        /**
         *  Search for the consecutive offloaded modules with same client proc_id
         *  and add them the current OLM's modules list if present.
         */

        /* Assign prev module pointer and update the source module pointer */
        prev_src_module = module_definition_src_ptr++;
        module_idx++;
        bool_t check_next_module = TRUE;
        while(check_next_module &&  module_idx <= topology_definition_ptr->num_modules )
        {
          if(prev_src_module->client_proc_id == module_definition_src_ptr->client_proc_id)
          {
            /* Push the offloaded module info in to OLM's module list */
            elite_cmn_topo_db_copy_module_info_util(module_definition_src_ptr,olm_modules_mem_ptr);

            /* Increment olm modules memory blob pointer, to get new module info ptr*/
            olm_modules_mem_ptr++;

            /* Increment OLM topology's module count*/
            cur_olm_topo_ptr->num_modules++;

            /* Assign prev module pointer and update the source module pointer */
            prev_src_module = module_definition_src_ptr++;
            module_idx++;
          }
          else
          {
            check_next_module = FALSE;
          }
        }

        /* Update the mode of the OLM topology.
         * IF all the modules are off loaded then set it to sync mode,
         * else if there are any local modules set it to ASYNC mode.
         */
        if(cur_olm_topo_ptr->num_modules == topology_definition_ptr->num_modules)
        {
          cur_olm_topo_ptr->is_sync_mode = TRUE;
        }
        else
        {
          cur_olm_topo_ptr->is_sync_mode = FALSE;
        }
        /* Move to new OLM DB entry*/
        cur_olm_topo_ptr++;

        /* Update the module destination pointer*/
        module_definition_dest_ptr++;
      }
    }
  }

#ifdef DEBUG_ELITE_COMMON_TOPO
  MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_update_topology_with_olms: Done. Topo Id: %lx, OLM module count: %lu Global OLM count: %lu ",
        topology_definition_ptr->topology_id , db_entry_ptr->num_olm_modules,olm_global_count);
#endif

  return result;
}

/**
 *
 * elite_cmn_topo_db_get_olm_iid:
 *        Returns OLM instance ID of the given (MID,IID) pair in the topology.
 *
 */
ADSPResult elite_cmn_topo_db_get_olm_iid(uint32_t area_bit_mask,
                                         uint32_t topology_id,
                                         uint32_t offloadedmod_module_id, /* Instance ID of OLM module */
                                         uint16_t offloadedmod_instance_id, /* Instance ID of OLM module */
                                         uint16_t *olm_instance_id /* out put args: olm Instance ID */ )
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
    if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
        (TRUE == curr_ptr->is_active) &&
        (area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
    {
      /*Find the OLM topology in the given topology and return the pointer*/
      elite_cmn_olm_topo_db_entry_t *cur_olm_entry_ptr = curr_ptr->olm_topos;

      uint32_t olm_idx = 0;
      while(olm_idx < curr_ptr->num_olm_modules )
      {
        // Check for the module in each
        avcs_module_instance_proc_info_t *temp_mod_info_ptr = cur_olm_entry_ptr->module_info;
        for(int idx =0 ; idx < cur_olm_entry_ptr->num_modules ; idx++ )
        {
          if( offloadedmod_module_id == temp_mod_info_ptr->module_id && offloadedmod_instance_id == temp_mod_info_ptr->instance_id )
          {
            // copy OLM instnace ID in output argument
            *olm_instance_id = cur_olm_entry_ptr->olm_iid;
#ifdef DEBUG_ELITE_COMMON_TOPO
            MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_olm_iid: OLM IID: 0x%x found in active topo_id 0x%lx, db_entry_addr @0x%p"
                  ,*olm_instance_id,topology_id, curr_ptr);
#endif
            qurt_elite_mutex_unlock(&me_ptr->db_lock);
            return result;
          }

        }
        cur_olm_entry_ptr++;
        olm_idx++;
      }

      MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_olm_iid: OLM with instance ID 0x%lx, was not found in topo_id 0x%lx, entry_addr: 0x%x"
            ,*olm_instance_id, topology_id, curr_ptr);
      qurt_elite_mutex_unlock(&me_ptr->db_lock);
      result = ADSP_EBADPARAM;
      return result;
    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }

  //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_olm_topology: an active topo_id 0x%lx was not found with provided bitmask %lx.",
        topology_id, area_bit_mask);
  result = ADSP_EBADPARAM;
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

/**
 *
 * elite_cmn_topo_db_get_module_info:
 *        1. Returns module info of the given (MID,IID). Returns OLMs info, if it is offloaded moudles info.
 */
ADSPResult elite_cmn_topo_db_get_module_info(uint32_t area_bit_mask,
                                             uint32_t topology_id,
                                             uint32_t module_id,
                                             uint16_t instance_id,
                                             avcs_module_instance_proc_info_t *out_module_info_ptr /* out put args: olm Instance ID */ )
{
  /* Check if the module is present in the normal topology */
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;

  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
#ifdef DEBUG_ELITE_COMMON_TOPO

    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_module_info: current topology id %lx bitmask %lx. addr %p ",
          curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->topo_entry.topo_def.topo_config, curr_ptr);
#endif
    if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
        (TRUE == curr_ptr->is_active) &&
        (area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
    {
      /*
       * Check if the module is present in updated topology entry
       */
      avcs_module_instance_proc_info_t *temp_module_definition_ptr = curr_ptr->topo_entry.module_info;
      for (uint32_t j = 0; j < curr_ptr->topo_entry.topo_def.num_modules; j++)
      {
        if(module_id == temp_module_definition_ptr->module_id && instance_id == temp_module_definition_ptr->instance_id )
        {
          elite_cmn_topo_db_copy_module_info_util(temp_module_definition_ptr,out_module_info_ptr);

#ifdef DEBUG_ELITE_COMMON_TOPO
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_module_info: an active topo_id %lx was found with provided bitmask %lx. mod_id %lx found.",
                topology_id, area_bit_mask, module_id);
#endif
          qurt_elite_mutex_unlock(&me_ptr->db_lock);
          return result;
        }
        else
        {
          temp_module_definition_ptr++;
        }
      }

      /*
       * Else search for the module in the OLM topologies
       */
      // get OLM IID for the given module
      uint16_t olm_iid =0;
      result = elite_cmn_topo_db_get_olm_iid(area_bit_mask,topology_id,module_id,instance_id,&olm_iid);
      if(ADSP_EOK != result)
      {
        //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was found, but module was not found. This is an erroneous use case.
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_module_info: mod_id 0x%lx was not found in active topo_id 0x%lx, entry_addr: 0x%x",
              module_id, topology_id, curr_ptr);
        qurt_elite_mutex_unlock(&me_ptr->db_lock);
        return result;
      }

      /*
       * Find the OLM module info pointer and return the module info
       */
      temp_module_definition_ptr = curr_ptr->topo_entry.module_info;
      for (uint32_t j = 0; j < curr_ptr->topo_entry.topo_def.num_modules; j++)
      {
        if(AVCS_ADSP_OLM_MODULE_ID == temp_module_definition_ptr->module_id && olm_iid == temp_module_definition_ptr->instance_id )
        {
          elite_cmn_topo_db_copy_module_info_util(temp_module_definition_ptr,out_module_info_ptr);

#ifdef DEBUG_ELITE_COMMON_TOPO
          MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_module_info: Module ID: 0x%x Instance ID: 0x%x",
                topology_id, area_bit_mask, module_id);

          elite_cmn_topo_db_print_module_info(out_module_info_ptr);
#endif
          qurt_elite_mutex_unlock(&me_ptr->db_lock);
          return result;
        }
        else
	{
          temp_module_definition_ptr++;
        }
      }



    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }

  //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_module_present: an active topology %lx was not found with provided bitmask %lx.",
        topology_id, area_bit_mask);
  result = ADSP_EBADPARAM;
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

ADSPResult elite_cmn_topo_db_get_mid_iid(uint32_t area_bit_mask,
                                         uint32_t topology_id,
                                         uint32_t module_id, /* Instance ID of OLM module */
                                         uint16_t instance_id, /* Instance ID of OLM module */
                                         uint32_t *out_module_id, /* out put args: Local module ID */
                                         uint16_t *out_instance_id /* Out put args: local instance ID*/
)
{
  /* Check if the module is present in the normal topology */
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  *out_module_id   = 0;
  *out_instance_id = 0;
  ADSPResult result = ADSP_EOK;

  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
#ifdef DEBUG_ELITE_COMMON_TOPO

    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_mid_iid: current topology id %lx bitmask %lx. addr %p ",
          curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->topo_entry.topo_def.topo_config, curr_ptr);
#endif
    if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
        (TRUE == curr_ptr->is_active) &&
        (area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
    {
      /*
       * Check if the module is present in updated topology entry
       */
      avcs_module_instance_proc_info_t *temp_module_definition_ptr = curr_ptr->topo_entry.module_info;
      for (uint32_t j = 0; j < curr_ptr->topo_entry.topo_def.num_modules; j++)
      {
        if(module_id == temp_module_definition_ptr->module_id && instance_id == temp_module_definition_ptr->instance_id )
        {
          *out_module_id = temp_module_definition_ptr->module_id ;
          *out_instance_id = temp_module_definition_ptr->instance_id ;

#ifdef DEBUG_ELITE_COMMON_TOPO
          MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_mid_iid: Input MID: 0x%x, IID: 0x%x ; Output  MID: 0x%x, IID: 0x%x ",
                module_id,instance_id,*out_module_id, *out_instance_id);
#endif
          qurt_elite_mutex_unlock(&me_ptr->db_lock);
          return result;
	}
	else
	{
          temp_module_definition_ptr++;
        }
	}
      /*
       * Else search for the module in the OLM topologies
       */
      uint16_t olm_iid =0;
      result = elite_cmn_topo_db_get_olm_iid(area_bit_mask,topology_id,module_id,instance_id,&olm_iid);
      if(ADSP_EOK != result)
      {
        //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was found, but module was not found. This is an erroneous use case.
        MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_mid_iid: mod_id 0x%lx was not found in active topo_id 0x%lx, entry_addr: 0x%x",
              module_id, topology_id, curr_ptr);
        qurt_elite_mutex_unlock(&me_ptr->db_lock);
        return result;
      }

      /* Update return module id and IID */
      *out_module_id = AVCS_ADSP_OLM_MODULE_ID ;
      *out_instance_id = olm_iid;

#ifdef DEBUG_ELITE_COMMON_TOPO
      MSG_4(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_mid_iid: Input MID: 0x%x, IID: 0x%x ; Output  MID: 0x%x, IID: 0x%x ",
            module_id,instance_id,*out_module_id, *out_instance_id);
#endif
      qurt_elite_mutex_unlock(&me_ptr->db_lock);
      return result;
    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }
  //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_mid_iid: an active topology %lx was not found with provided bitmask %lx.",
        topology_id, area_bit_mask);
  result = ADSP_EBADPARAM;
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

ADSPResult elite_cmn_topo_db_add_topology(avcs_topology_definition_t *topology_definition_ptr,
                                          void *module_definition_ptr,
                                          elite_cmn_topo_type_t topo_type)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;
  uint32_t internal_db_entry_size = 0, db_entry_size = 0;
  uint32_t topo_version = 0;
  uint32_t mod_inf_addr_offset = 0;
  uint32_t olm_topos_addr_offset = 0;
  uint32_t olm_cnt =0, new_mod_cnt = 0; /* Used only If topology is of version '2' */

  /* Acquire mutex lock on database. */
  qurt_elite_mutex_lock(&me_ptr->db_lock);

  topo_version = topology_definition_ptr->version;

  /*Get total modules count and OLMs count from updated topology*/
  elite_cmn_topo_db_get_modules_count(topology_definition_ptr, module_definition_ptr, &new_mod_cnt, &olm_cnt);

  /*
   * Memory needed for the elite_cmn_topo_db_internal_entry_t, which includes updated topology information and
   * OLM topology info.
   */
  internal_db_entry_size =     sizeof(elite_cmn_topo_db_internal_entry_t)
                                + (sizeof(avcs_module_instance_proc_info_t) * ( topology_definition_ptr->num_modules + olm_cnt))
                                + (sizeof(elite_cmn_olm_topo_db_entry_t) * (olm_cnt));

	//Allocate memory for the elite_cmn_topo_db_internal_entry_t entry.
  elite_cmn_topo_db_internal_entry_t *entry_ptr = (elite_cmn_topo_db_internal_entry_t*) qurt_elite_memory_malloc(internal_db_entry_size, QURT_ELITE_HEAP_DEFAULT);

	if (NULL == entry_ptr)
	{
		MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_add_topology: Failed to allocate memory for topology definition: elite_cmn_topo_db_internal_entry_t");
		result = ADSP_ENOMEMORY;
		qurt_elite_mutex_unlock(&me_ptr->db_lock);
		return result;
	}
	else
	{
#ifdef DEBUG_ELITE_COMMON_TOPO
    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_add_topology: Malloc %lu bytes (internal_size) %lu bytes (ext_size) success for elite_cmn_topo_db_internal_entry_t node @ 0x%p",
          internal_db_entry_size,db_entry_size, entry_ptr);
    MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Modules offset size: %lu bytes OLM topos Addr offset: %lu bytes"
          ,mod_inf_addr_offset,olm_topos_addr_offset);
#endif
	}
  memset(entry_ptr, 0, internal_db_entry_size);

  /*
   * External size is the size of elite_cmn_topo_db_entry_t* for the updated topology
   * which is returned as part of elite_cmn_topo_db_get_topology()
   */
  db_entry_size =    sizeof(elite_cmn_topo_db_entry_t)
                                                + (sizeof(avcs_module_instance_proc_info_t) * (new_mod_cnt));

  /*
   * mod_inf_addr_offset is the address offset for the updated topology's modules list.
   * i.e  entry_ptr->topo
   */
  mod_inf_addr_offset =  sizeof(elite_cmn_topo_db_internal_entry_t);

  olm_topos_addr_offset =    sizeof(elite_cmn_topo_db_internal_entry_t)
                                                  + (sizeof(avcs_module_instance_proc_info_t) * (new_mod_cnt));

	//Populate avcs_topology_definition_t information.
	entry_ptr->topo_entry.topo_def.topo_config = topology_definition_ptr->topo_config;
	entry_ptr->topo_entry.topo_def.topology_id = topology_definition_ptr->topology_id;
	entry_ptr->topo_entry.topo_def.version = topology_definition_ptr->version;
  entry_ptr->topo_entry.topo_def.num_modules = new_mod_cnt;
  entry_ptr->topo_entry.module_info = (avcs_module_instance_proc_info_t *)( (uint8_t*)entry_ptr + mod_inf_addr_offset);

	//Set the topo type to be the right topo type.
	entry_ptr->topo_type = topo_type;

	//Populate next_ptr and size.
	entry_ptr->next_ptr = NULL;
  entry_ptr->size = db_entry_size; //These are the number of bytes the client would be concerned about (reading).

	//Update ref count and is_active flag.
	entry_ptr->ref_count = 1;
	entry_ptr->is_active = TRUE; //This flag will be used to distinguish de-registered nodes in the future

	//Update handle_generator. Valid handle values 1 <= handle <= UINT32_MAX - 1
	me_ptr->handle_generator = (UINT32_MAX - 1 == me_ptr->handle_generator) ? (1) : (me_ptr->handle_generator+1);

	//Update handle for this topology node.
	entry_ptr->handle = me_ptr->handle_generator;

  /* Update no.of OLM modules in the topo*/
  entry_ptr->num_olm_modules = olm_cnt;

  /* Only meaning full if the OLMs are present */
  if(0 == entry_ptr->num_olm_modules)
	{
    entry_ptr->olm_topos = NULL;
	}
	else
	{
    entry_ptr->olm_topos = (elite_cmn_olm_topo_db_entry_t *) ( (uint8_t*)entry_ptr + olm_topos_addr_offset);
		}

  /*
   *  Update the given topology with the OLM modules and populate the
   *  modules information in the db entry. If it has olm modules, update
   *  the OLM topologies in the db entry
   */
  result = elite_update_topology_with_olms(topology_definition_ptr, module_definition_ptr, entry_ptr);

  if(ADSP_EOK != result)
			{
    MSG(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_add_topology: elite_update_topology_with_olms. Failed. ");

    //Release mutex lock on database.
    qurt_elite_mutex_unlock(&me_ptr->db_lock);
    return result;
	}


#ifdef DEBUG_ELITE_COMMON_TOPO

  elite_cmn_topo_db_print_db_entry_info(&entry_ptr->topo_entry);

  MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_add_topology: num_modules %lu, olm_mod_count: %lu new_mod_cnt: %lu",
        entry_ptr->topo_entry.topo_def.num_modules, olm_cnt, new_mod_cnt);

  MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_add_topology: success: topo_id 0x%lx added, area_bit_mask %lx, external_size: %lu, #modules: %lu, new_mod_cnt: %lu",
        entry_ptr->topo_entry.topo_def.topology_id, (entry_ptr->topo_entry.topo_def.topo_config & 0x0000000f), entry_ptr->size,
        entry_ptr->topo_entry.topo_def.num_modules, new_mod_cnt);

#endif

	//Add node into linked list.
	if(NULL == me_ptr->record_tail_ptr)
	{
		me_ptr->record_head_ptr = entry_ptr;
		me_ptr->record_tail_ptr = entry_ptr;
	}
	else
	{
		me_ptr->record_tail_ptr->next_ptr = entry_ptr;
		me_ptr->record_tail_ptr = entry_ptr;
	}
#ifdef DEBUG_ELITE_COMMON_TOPO

	MSG_5(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_add_topology: success: topo_id %lx added, area_bit_mask %lx, external_size: %lu, #modules: %lu, new_ref_count: %lu",
			entry_ptr->topo_entry.topo_def.topology_id, (entry_ptr->topo_entry.topo_def.topo_config & 0x0000000f), entry_ptr->size,
			entry_ptr->topo_entry.topo_def.num_modules, entry_ptr->ref_count);
#endif
  //Release mutex lock on database.
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

ADSPResult elite_cmn_topo_db_deregister_all_custom_topologies(void)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;
  //Acquire mutex lock on database.
  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr, *prev_ptr, *next_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  prev_ptr = NULL;
  next_ptr = NULL;
  while(NULL != curr_ptr)
  {
    next_ptr = curr_ptr->next_ptr;
    if( ELITE_CMN_CUSTOM_TOPOLOGIES  ==  curr_ptr->topo_type && curr_ptr->is_active)
    {
      curr_ptr->is_active = FALSE;
      MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_deregister_topology: deregister successful. handle: %lu, topo_id: %lx, ref_count: %lu",
            curr_ptr->handle, curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->ref_count);
      //At this point if ref_count becomes 1 and this node is marked for deletion (de-register), go ahead and delete the node.
      //Else, this node will not be removed, and we can therefore move prev ptr to here.
      if(ADSP_ENOTREADY == elite_cmn_topo_db_process_check_remove_topology(curr_ptr,prev_ptr))
      {
        prev_ptr = curr_ptr;
      }
    }
    else
    {
#ifdef DEBUG_ELITE_COMMON_TOPO
      //Remove all custom topologies until the end of topo db is reached.
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_deregister_topology:  Topology %lu is no longer active, continuing", curr_ptr->handle);
#endif
      prev_ptr = curr_ptr;
    }


    curr_ptr = next_ptr;

  }

	//Release mutex lock on database.
	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}
ADSPResult elite_cmn_topo_db_deregister_single_topology(uint32_t topology_id)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult   result = ADSP_EFAILED;

  //Acquire mutex lock on database.
  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr, *prev_ptr,*next_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  prev_ptr = NULL;
  next_ptr = NULL;
  while(NULL != curr_ptr)
  {
    next_ptr = curr_ptr->next_ptr;
    if(topology_id  == curr_ptr->topo_entry.topo_def.topology_id && ELITE_CMN_CUSTOM_TOPOLOGIES == curr_ptr->topo_type)
    {
      if(FALSE == curr_ptr->is_active)
      {
        MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_deregister_topology:  Topology %lu is no longer active, continuing", curr_ptr->handle);
      }
      else
      {
        curr_ptr->is_active = FALSE;
        MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_deregister_topology: deregister successful. handle: %lu, topo_id: %lx, ref_count: %lu",
              curr_ptr->handle, curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->ref_count);
        //At this point if ref_count becomes 1 and this node is marked for deletion (de-register), go ahead and delete the node.
        elite_cmn_topo_db_process_check_remove_topology(curr_ptr,prev_ptr);
#ifdef DEBUG_ELITE_COMMON_TOPO
        MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_deregister_topology: head ptr %p, tail ptr %p",me_ptr->record_head_ptr,me_ptr->record_tail_ptr);
#endif
        result = ADSP_EOK;
        qurt_elite_mutex_unlock(&me_ptr->db_lock);
        return result;
      }
    }
    prev_ptr = curr_ptr;
    curr_ptr = next_ptr;
  }
  //If we reach here, it means the topo is not found. We will return an error here.
  //Release mutex lock on database.
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

ADSPResult elite_cmn_topo_db_get_topology(uint32_t area_bit_mask,
                                          uint32_t topology_id,
                                          elite_cmn_topo_db_entry_t **topology_ptr_ptr,
                                          uint32_t *actual_size_ptr,
                                          uint32_t *handle_ptr)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	qurt_elite_mutex_lock(&me_ptr->db_lock);

	elite_cmn_topo_db_internal_entry_t  *curr_ptr;
	curr_ptr = me_ptr->record_head_ptr;
	while(NULL != curr_ptr)
	{
		if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
				(TRUE == curr_ptr->is_active) &&
				(area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
		{
			//Wrap-around protection
			if(UINT32_MAX == curr_ptr->ref_count)
			{
				MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_topology: an active topo_id %lx was found with provided bitmask %lx. However, there are too many references.",
						topology_id, area_bit_mask);
				*handle_ptr = ELITE_CMN_TOPO_DB_INVALID_HANDLE;
				result = ADSP_EBADPARAM;

				qurt_elite_mutex_unlock(&me_ptr->db_lock);
				return result;
			}

			//Fill in details
			curr_ptr->ref_count++;
			*handle_ptr = curr_ptr->handle;
			*actual_size_ptr = curr_ptr->size;
			*topology_ptr_ptr = &(curr_ptr->topo_entry);

			MSG_6(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_topology: an active topo_id %lx was found with provided bitmask %lx. actual_size: %lu, handle: %lu, node @0x%p, new_ref_count: %lu",
					topology_id, area_bit_mask, curr_ptr->size, curr_ptr->handle, &(curr_ptr->topo_entry), curr_ptr->ref_count);

			qurt_elite_mutex_unlock(&me_ptr->db_lock);
			return result;
		}
		else
		{
			curr_ptr = curr_ptr->next_ptr;
		}
	}

	//If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
	MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_topology: an active topo_id %lx was not found with provided bitmask %lx.",
			topology_id, area_bit_mask);
	*handle_ptr = ELITE_CMN_TOPO_DB_INVALID_HANDLE;
	result = ADSP_EBADPARAM;

	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}

ADSPResult elite_cmn_topo_db_get_olm_topology(uint32_t area_bit_mask,   /* Input: Area bit mask */
                                              uint32_t topology_id,     /* Input: Topology ID */
                                              uint16_t olm_instance_id, /* Input: Instance ID of OLM module */
                                              elite_cmn_olm_topo_db_entry_t **olm_topo_ptr_ptr /* Output: Ptr to OLM topology pointer*/
)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;

  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
    if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
        (TRUE == curr_ptr->is_active) &&
        (area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
    {

      /*Find the OLM topology in the given topology and return the pointer*/
      elite_cmn_olm_topo_db_entry_t *cur_olm_entry_ptr = curr_ptr->olm_topos;

      uint32_t olm_idx = 0;
      while(olm_idx < curr_ptr->num_olm_modules )
      {
        /* Check if OLM's topology ID is same as olm_instance ID*/
        if(olm_instance_id == cur_olm_entry_ptr->olm_iid)
        {
          /* Copy the OLM topology's DB entry pointer to Output argument*/
          *olm_topo_ptr_ptr = cur_olm_entry_ptr;

          qurt_elite_mutex_unlock(&me_ptr->db_lock);
          return result;
        }
        else
        {
          cur_olm_entry_ptr++;
          olm_idx++;
        }
      }
      qurt_elite_mutex_unlock(&me_ptr->db_lock);
      result = ADSP_EBADPARAM;
      return result;
    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }

  //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_olm_topology: an active topo_id 0x%lx was not found with provided bitmask %lx.",
        topology_id, area_bit_mask);
  result = ADSP_EBADPARAM;
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}

ADSPResult elite_cmn_topo_db_get_olm_topologies(uint32_t area_bit_mask, /*Input arg: Area bit mask */
                                                uint32_t topology_id,   /*Input arg: Topology ID */
                                                uint32_t *num_olm_modules,  /*Output arg: Pointer to number of modules */
                                                elite_cmn_olm_topo_db_entry_t **olm_topo_arr_ptr_ptr /*Output arg: Pointer to topo array ptr */
)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;

  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
    if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
        (TRUE == curr_ptr->is_active) &&
        (area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
    {
      /* Copy the OLM related info into output arguments*/
      *num_olm_modules  = curr_ptr->num_olm_modules;
      *olm_topo_arr_ptr_ptr = curr_ptr->olm_topos;

      MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_get_topology: an active topo_id 0x%lx was found with provided bitmask 0x%lx. node @0x%p",
            topology_id, area_bit_mask, &(curr_ptr->topo_entry));

      qurt_elite_mutex_unlock(&me_ptr->db_lock);
      return result;
    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }

  //If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
  MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_get_topology: an active topo_id %lx was not found with provided bitmask %lx.",
        topology_id, area_bit_mask);
  result = ADSP_EBADPARAM;

  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}


ADSPResult elite_cmn_topo_db_process_check_remove_topology(elite_cmn_topo_db_internal_entry_t *curr_ptr,elite_cmn_topo_db_internal_entry_t *prev_ptr)
{
  ADSPResult result = ADSP_ENOTREADY;
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  if(NULL == curr_ptr)
  {
  MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_check_remove_topology: ERROR: curr_ptr is null, exiting.");
  goto __bailout;
  }

  if (FALSE == curr_ptr->is_active && 1 == curr_ptr->ref_count && ELITE_CMN_CUSTOM_TOPOLOGIES == curr_ptr->topo_type)
  {
    //Remove the next ptr of the current pointer from linked list
    if(curr_ptr == me_ptr->record_head_ptr )//Indicates the node to remove is the first node.
    {
      me_ptr->record_head_ptr = curr_ptr->next_ptr;
    }
    if(curr_ptr == me_ptr->record_tail_ptr)
    {
      me_ptr->record_tail_ptr = prev_ptr;
    }
    if(prev_ptr != NULL)
    {
      prev_ptr->next_ptr = curr_ptr->next_ptr;
    }
    MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_check_remove_topology: freeing ptr at  %p", curr_ptr);
    qurt_elite_memory_free(curr_ptr);
    result = ADSP_EOK;
  }
  __bailout:
  return result;
}

ADSPResult elite_cmn_topo_db_release_topology(uint32_t handle)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	if(ELITE_CMN_TOPO_DB_INVALID_HANDLE == handle || 0 == handle)
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_release_topology: Invalid handle %lu provided", handle);
		result = ADSP_EBADPARAM;
		return result;
	}

	qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr, *prev_ptr, *next_ptr;
	curr_ptr = me_ptr->record_head_ptr;
  prev_ptr = NULL;
  next_ptr = NULL;
	while(NULL != curr_ptr)
	{
    next_ptr = curr_ptr->next_ptr;
		if(handle == curr_ptr->handle)
		{
			//Wrap-around protection. There should always be one ref_count (after all client releases). Check done prior to decrementing ref_count.
			if(1 >= curr_ptr->ref_count)
			{
				MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_release_topology: Too many releases on handle %lu", curr_ptr->handle);
				result = ADSP_EBADPARAM;
			}
			else
			{
				curr_ptr->ref_count--;
				MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_release_topology: release successful. handle: %lu, topo_id: %lx, new ref_count: %lu",
						curr_ptr->handle, curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->ref_count);
			}

      //At this point if ref_count becomes 1 and this node is marked for deletion (de-register), go ahead and delete the node.
      elite_cmn_topo_db_process_check_remove_topology(curr_ptr,prev_ptr);

			qurt_elite_mutex_unlock(&me_ptr->db_lock);
			return result;
		}
		else
		{
      prev_ptr = curr_ptr;
      curr_ptr = next_ptr;
		}
	}

	//If code execution has reached here, then the provided handle was not found. This is an erroneous use case.
	MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_release_topology: release failed. handle: %lu does not exist", handle);
	result = ADSP_EBADPARAM;
	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}


ADSPResult elite_cmn_topo_db_print_topology_info(uint32_t topology_id)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
  ADSPResult result = ADSP_EOK;

  qurt_elite_mutex_lock(&me_ptr->db_lock);

  elite_cmn_topo_db_internal_entry_t  *curr_ptr;
  curr_ptr = me_ptr->record_head_ptr;
  while(NULL != curr_ptr)
  {
    if(topology_id == curr_ptr->topo_entry.topo_def.topology_id)
    {
#ifdef DEBUG_ELITE_COMMON_TOPO
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_print_topology_info: Printing topo_id 0x%lx info.", topology_id);
#endif
      elite_cmn_topo_db_print_db_entry_info(&curr_ptr->topo_entry);

      qurt_elite_mutex_unlock(&me_ptr->db_lock);
      return result;
    }
    else
    {
      curr_ptr = curr_ptr->next_ptr;
    }
  }

  //If code execution has reached here, then the provided topology was not found. Therefore it is unique.
  MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_print_topology_info: Could not find topo_id 0x%lx in the DB.", topology_id);
  qurt_elite_mutex_unlock(&me_ptr->db_lock);
  return result;
}


ADSPResult elite_cmn_topo_db_is_topology_unique(uint32_t topology_id)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	qurt_elite_mutex_lock(&me_ptr->db_lock);

	elite_cmn_topo_db_internal_entry_t  *curr_ptr;
	curr_ptr = me_ptr->record_head_ptr;
	while(NULL != curr_ptr)
	{
		if(topology_id == curr_ptr->topo_entry.topo_def.topology_id && TRUE == curr_ptr->is_active)
		{
			MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_topology_unique: an active topo_id %lx already exists. It is not unique.", topology_id);
			result = ADSP_EBADPARAM;
			qurt_elite_mutex_unlock(&me_ptr->db_lock);
			return result;
		}
		else
		{
			curr_ptr = curr_ptr->next_ptr;
		}
	}

	//If code execution has reached here, then the provided topology was not found. Therefore it is unique.
	MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_topology_unique: not an active topo_id %lx. It is unique.", topology_id);
	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}

ADSPResult elite_cmn_topo_db_is_active_custom_topology_found(uint32_t topology_id)
{
  elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
   ADSPResult result = ADSP_EBADPARAM;

   qurt_elite_mutex_lock(&me_ptr->db_lock);

   elite_cmn_topo_db_internal_entry_t  *curr_ptr;
   curr_ptr = me_ptr->record_head_ptr;
   while(NULL != curr_ptr)
   {
     if(topology_id == curr_ptr->topo_entry.topo_def.topology_id && TRUE == curr_ptr->is_active && ELITE_CMN_CUSTOM_TOPOLOGIES == curr_ptr->topo_type)
     {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_active_custom_topology_found: an active custom topo_id 0x%lx is found.", topology_id);
       result = ADSP_EOK;
       qurt_elite_mutex_unlock(&me_ptr->db_lock);
       return result;
     }
     else
     {
       curr_ptr = curr_ptr->next_ptr;
     }
   }

   //If code execution has reached here, then the provided topology was not found. Return error.
   MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_active_custom_topology_found: no active custom topo_id %lx is found here.", topology_id);
   qurt_elite_mutex_unlock(&me_ptr->db_lock);
   return result;
}

ADSPResult elite_cmn_topo_db_is_module_present(uint32_t area_bit_mask, uint32_t topology_id, uint32_t module_id)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	qurt_elite_mutex_lock(&me_ptr->db_lock);

	elite_cmn_topo_db_internal_entry_t  *curr_ptr;
	curr_ptr = me_ptr->record_head_ptr;
	while(NULL != curr_ptr)
	{
#ifdef DEBUG_ELITE_COMMON_TOPO

    MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_module_present: current topology id %lx bitmask %lx. addr %p ",
          curr_ptr->topo_entry.topo_def.topology_id, curr_ptr->topo_entry.topo_def.topo_config, curr_ptr);
#endif
		if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
				(TRUE == curr_ptr->is_active) &&
				(area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
		{

      avcs_module_instance_proc_info_t *temp_module_definition_ptr = curr_ptr->topo_entry.module_info;
			for (uint32_t j = 0; j < curr_ptr->topo_entry.topo_def.num_modules; j++)
			{
				if(module_id == temp_module_definition_ptr->module_id)
				{
					MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_module_present: an active topo_id %lx was found with provided bitmask %lx. mod_id %lx found.",
							topology_id, area_bit_mask, module_id);
					qurt_elite_mutex_unlock(&me_ptr->db_lock);
					return result;
				}
				else
				{
					temp_module_definition_ptr++;
				}
			}

      /*Find the OLM topology in the given topology and return the pointer*/
      elite_cmn_olm_topo_db_entry_t *cur_olm_entry_ptr = curr_ptr->olm_topos;

      uint32_t olm_idx = 0;
      while(olm_idx < curr_ptr->num_olm_modules )
      {
        // Check for the module in each
        avcs_module_instance_proc_info_t *temp_mod_info_ptr = cur_olm_entry_ptr->module_info;
        for(int idx =0 ; idx < cur_olm_entry_ptr->num_modules ; idx++ )
        {
          if( module_id == temp_mod_info_ptr->module_id )
          {
            MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_module_present: an active topo_id %lx was found with provided bitmask %lx. mod_id %lx found.",
                  topology_id, area_bit_mask, module_id);
            qurt_elite_mutex_unlock(&me_ptr->db_lock);
            return result;
          }

        }
        cur_olm_entry_ptr++;
        olm_idx++;
      }

			//If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was found, but module was not found. This is an erroneous use case.
			MSG_3(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_module_present: an active topo_id %lx was found with provided bitmask %lx. but mod_id %lx was not found.",
					topology_id, area_bit_mask, module_id);
			result = ADSP_EBADPARAM;
			qurt_elite_mutex_unlock(&me_ptr->db_lock);
			return result;
		}
		else
		{
			curr_ptr = curr_ptr->next_ptr;
		}
	}

	//If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found. This is an erroneous use case.
	MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_module_present: an active topology %lx was not found with provided bitmask %lx.",
			topology_id, area_bit_mask);
	result = ADSP_EBADPARAM;
	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}

ADSPResult elite_cmn_topo_db_is_active_topology_present(uint32_t area_bit_mask, uint32_t topology_id)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	ADSPResult result = ADSP_EOK;

	qurt_elite_mutex_lock(&me_ptr->db_lock);

	elite_cmn_topo_db_internal_entry_t  *curr_ptr;
	curr_ptr = me_ptr->record_head_ptr;
	while(NULL != curr_ptr)
	{
		if((topology_id == curr_ptr->topo_entry.topo_def.topology_id) &&
				(TRUE == curr_ptr->is_active) &&
				(area_bit_mask == (curr_ptr->topo_entry.topo_def.topo_config & 0x0000000f & area_bit_mask)))
		{
			MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_is_active_topology_present: an active topo_id %lx was found with provided bitmask %lx",
					topology_id, area_bit_mask);
			qurt_elite_mutex_unlock(&me_ptr->db_lock);
			return result;
		}
		else
		{
			curr_ptr = curr_ptr->next_ptr;
		}
	}

	//If code execution has reached here, then an active topology with the provided topology_id with provided area_bit_mask was not found.
	MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_is_module_present: an active topology %lx was not found with provided bitmask %lx.",
			topology_id, area_bit_mask);
	result = ADSP_EBADPARAM;
	qurt_elite_mutex_unlock(&me_ptr->db_lock);
	return result;
}

static void elite_cmn_topo_db_destroy_db_entry(void)
{
	elite_cmn_topo_db_t *me_ptr = &g_cmn_topology_db;
	elite_cmn_topo_db_internal_entry_t  *curr_ptr;
	elite_cmn_topo_db_internal_entry_t  *next_ptr;
	curr_ptr = me_ptr->record_head_ptr;
	while(NULL != curr_ptr)
	{
		next_ptr = curr_ptr->next_ptr;
#ifdef DEBUG_ELITE_COMMON_TOPO
		MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "elite_cmn_topo_db_destroy_db_entry: Freeing elite_cmn_topo_db_internal_entry_t node @ 0x%p", curr_ptr);
#endif
		qurt_elite_memory_free(curr_ptr);
		curr_ptr = next_ptr;
	}
}

ADSPResult elite_cmn_db_init(void)
{
	ADSPResult result;

	//Initialize database
	elite_cmn_topo_db_init();

	//Add audio PP static topologies followed by modules into this database
	result = aud_add_static_topos_and_mods_to_cmn_db();
	if (ADSP_FAILED(result))
	{
		MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_db_init: failed to aud_add_static_topos_and_mods_to_cmn_db with %d", result);
		elite_cmn_topo_db_deinit();
		return result;
	}

	//Adding AFE static topologies and by modules into common database
	result = afe_add_static_topos_and_mods_to_cmn_db();
	if (ADSP_FAILED(result))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_db_init: failed to afe_add_static_topos_and_mods_to_cmn_db with %d", result);
	  elite_cmn_topo_db_deinit();
	  return result;
	}

	//Adding LSM static topologies into common database
	result = lsm_add_static_topos_to_cmn_db();
	if (ADSP_FAILED(result))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_db_init: failed to lsm_add_static_topos_and_mods_to_cmn_db with %d", result);
	  elite_cmn_topo_db_deinit();
	  return result;
	}

	result = voice_add_static_topologies_and_modules_v2();
	if (ADSP_FAILED(result))
	{
	   MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_db_init: failed to voice_add_static_topologies_and_modules_v2 with %d", result);
	   elite_cmn_topo_db_deinit();
	   return result;
	}

	return result;
}

void elite_cmn_db_deinit(void)
{
	elite_cmn_topo_db_deinit();
}

ADSPResult elite_cmn_topo_db_reset(void)
{
	ADSPResult result;
	elite_cmn_topo_db_deinit();
	elite_cmn_topo_db_init();
	result = aud_add_static_topos_to_cmn_db();
	if (ADSP_FAILED(result))
	{
            MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_reset: failed to aud_add_static_topos_to_cmn_db with %d", result);
            elite_cmn_topo_db_deinit();
            return result;
	}

	result = afe_add_static_topos_to_cmn_db();
	if (ADSP_FAILED(result))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_reset: failed to afe_add_static_topos_to_cmn_db with %d", result);
	  elite_cmn_topo_db_deinit();
	  return result;
	}

	result = lsm_add_static_topos_to_cmn_db();
	if (ADSP_FAILED(result))
	{
	  MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_reset: failed to lsm_add_static_topos_to_cmn_db with %d", result);
	  elite_cmn_topo_db_deinit();
	  return result;
	}

	result = voice_add_static_topos_to_cmn_db();
	if (ADSP_FAILED(result))
	{
           MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "elite_cmn_topo_db_reset: failed to voice_add_static_topos_to_cmn_db with %d", result);
           elite_cmn_topo_db_deinit();
           return result;
	}

	return result;
}
