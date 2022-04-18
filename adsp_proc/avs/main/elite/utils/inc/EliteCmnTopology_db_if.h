/*========================================================================*/
/**
@file EliteCmnTopology_db_if.h
@brief This file declares the interface for the common global topology database (registered via AVCS).
This allows query of topologies and modules in a topology.
 */
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Elite_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*========================================================================
Copyright (c) 2015 Qualcomm Technologies, Inc. All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================== */

/*========================================================================
Edit History

when           who     what, where, why
-------------      ---       -----------------------
03/12/15      KR      Created file.
========================================================================== */
#ifndef ELITE_CMN_TOPOLOGY_DB_IF_H
#define ELITE_CMN_TOPOLOGY_DB_IF_H

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "adsp_core_api.h"
#include "adsp_error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/** @addtogroup elite_topodb_datatypes_cmn
@{ */

/** Invalid handle ID returned by the database in case of an error. */
#define ELITE_CMN_TOPO_DB_INVALID_HANDLE             0xFFFFFFFF

typedef struct elite_cmn_topo_db_entry_t elite_cmn_topo_db_entry_t;

/** Topology database entry nodes.
*/
struct elite_cmn_topo_db_entry_t
{
    avcs_topology_definition_t topo_def;
    /**< Topology definition information. */

    avcs_module_instance_proc_info_t* module_info;
    /**< Contains the pointer to modules list array for the given topology entry*/
};

/** @} */ /* end_addtogroup elite_topodb_datatypes_cmn */

typedef struct elite_cmn_olm_topo_db_entry_t elite_cmn_olm_topo_db_entry_t;

/** Topology database entry nodes.
*/
struct elite_cmn_olm_topo_db_entry_t
{
    uint16_t olm_iid;
    /**< OLM instance ID */

    uint32_t num_modules;
    /**< Number of modules in the OLM topo */

    uint16_t is_sync_mode;
    /* Mode -  Synchronous or Asynchronous module */

    avcs_module_instance_proc_info_t* module_info;
    /**< Contains the pointer to modules list array for the given topology entry*/
};



/** @ingroup elite_topodb_db_get_topo_cmn
  Gets a topology definition from the common global topology database.

  @datatypes
  elite_cmn_topo_db_entry_t

  @param[in]     area_bit_mask     Area bitmask of the client making this
                                   request.
  @param[in]     topology_id       ID of the topology for which the definition
                                   is requested.
  @param[in,out] topology_ptr_ptr  Double pointer to the topology definition
                                   (which includes its module properties).
  @param[out]    actual_size_ptr   Pointer to the actual size (in bytes) of the
                                   data pointed by topology_ptr_ptr.
  @param[out]    handle_ptr        Pointer to a handle that the client uses for
                                   future transactions (such as release).

  @return
  ADSP_EOK -- Success.
  @par
  Error code:
  - Topology definition could not be retrieved.
  - Provided topology_id does not have the area_bit_mask.
  - Topology is not active (it is marked for deregister).
  @par
  For all three error codes, the topology database returns NULL, the actual
  size is set to zero, and the handle is set to
  #ELITE_CMN_TOPO_DB_INVALID_HANDLE.

  @dependencies
  The elite_cmn_topo_db_init() function was called successfully.
 */
ADSPResult elite_cmn_topo_db_get_topology(uint32_t area_bit_mask, uint32_t topology_id, elite_cmn_topo_db_entry_t **topology_ptr_ptr, uint32_t *actual_size_ptr, uint32_t *handle_ptr);

/** @ingroup elite_topodb_db_rel_topo_cmn
  Notifies the common global topology database that the client released a
  topology.

  The client must call this function once it is finished using the topology
  definition pointer.

  @param[in] handle   Handle to be released.

  @return
  ADSP_EOK -- Success.
  @par
  Error code -- Specified handle does not exist.

  @dependencies
  The elite_cmn_topo_db_init() function was called successfully.
 */
ADSPResult elite_cmn_topo_db_release_topology(uint32_t handle);

//#ifdef DEBUG_ELITE_COMMON_TOPO

ADSPResult elite_cmn_topo_db_print_topology_info(uint32_t topology_id);

ADSPResult elite_cmn_topo_db_print_db_entry_info(elite_cmn_topo_db_entry_t *db_entry_ptr);

ADSPResult elite_cmn_topo_db_get_module_info(uint32_t area_bit_mask,
                                             uint32_t topology_id,
                                             uint32_t module_id, /* Instance ID of OLM module */
                                             uint16_t instance_id, /* Instance ID of OLM module */
                                             avcs_module_instance_proc_info_t *out_module_info /* out put args: olm Instance ID */ );

//#endif //#ifdef DEBUG_ELITE_COMMON_TOPO


/** @ingroup elite_cmn_topo_db_get_mid_iid
  Looks for (module_id, instance_id) in the given topology_id and,
      1. If it is a offloaded module, returns corresponding OLMs (MID, IID).
      2. Else if it is a local module, returns the input (MID, IID)

  @param[in]     area_bit_mask     Area bitmask of the client making this
                                   request.
  @param[in]     topology_id       ID of the topology for which the definition
                                   is requested.
  @param[in]     module_id         Module ID
  @param[in]     instance_id       Instance ID.
  @param[in,out] out_mid_ptr       Pointer to the output module ID.
  @param[in,out] out_iid_ptr       Pointer to the output instance ID.

  @return
  ADSP_EOK -- Success.

  @par
  Error code
    - Topology definition could not be retrieved.
    - Provided topology_id does not have the area_bit_mask.
    - A module with (module_id, instance_id) is not found in the topology.

  @dependencies
  The elite_cmn_topo_db_init() function was called successfully.
 */
ADSPResult elite_cmn_topo_db_get_mid_iid(uint32_t area_bit_mask,
                                             uint32_t topology_id,
                                             uint32_t module_id, /* Module ID of input module */
                                             uint16_t instance_id, /* Instance ID of input module */
                                             uint32_t *out_mid_ptr, /* out put ptr: output module ID */
                                             uint16_t *out_iid_ptr /* Out put ptr: output instance ID*/
                                             );

/** @ingroup elite_cmn_topo_db_get_olm_topology
  Gets a OLM topology definition in a given topology.

  @datatypes
  elite_cmn_topo_db_entry_t

  @param[in]     area_bit_mask     Area bitmask of the client making this
                                   request.
  @param[in]     topology_id       ID of the topology for which the definition
                                   is requested.
  @param[in]     olm_instance_id   OLM instance ID for whose topology definition
                                   is requested.
  @param[in,out] topology_ptr_ptr  Double pointer to the OLM topology definition
                                   (which includes its off-loaded modules list).

  @return
  ADSP_EOK -- Success.

  @par
  Error code
    - Topology definition could not be retrieved.
    - Provided topology_id does not have the area_bit_mask.
    - Topology is not active (it is marked for deregister).
    - OLM instance not found in the topology.

  @dependencies
  The elite_cmn_topo_db_init() function was called successfully.
 */
ADSPResult elite_cmn_topo_db_get_olm_topology(uint32_t area_bit_mask,   /* Input: area bit mask*/
                                              uint32_t topology_id,     /* Input: topology ID */
                                              uint16_t olm_instance_id, /* Input: Instance ID of OLM module */
                                              elite_cmn_olm_topo_db_entry_t **olm_topo_ptr_ptr /* Output arg: Pointer to OLM db entry in given topology*/
                                              );

/*
 * elite_cmn_topo_db_get_olm_topologies:
 *  -> Returns the array of OLM db entries for the given topology id, corresponding to all OLM instances in the topology.
 *  -> The db entry will contain the list of offloaded modules for the given olm instance.
 */
/** @ingroup elite_cmn_topo_db_get_olm_topologies
  Gets a all OLM topology definitions in a given topology.
    -> Returns the array of OLM db entries corresponding to all OLM instances in the topology.

  @datatypes
  elite_cmn_topo_db_entry_t

  @param[in]     area_bit_mask         Area bitmask of the client making this
                                       request.
  @param[in]     topology_id           ID of the topology for which the definition
                                       is requested.
  @param[in]     num_olm_instances     Number of OLM instances in the topology.
  @param[in,out] olm_topo_arr_ptr_ptr  Double pointer to the list of db entries to
                                       OLM topologies.
                                       (each entry includes its off-loaded modules list).

  @return
  ADSP_EOK -- Success.

  @par
  Error code
    - Topology definition could not be retrieved.
    - Provided topology_id does not have the area_bit_mask.
    - Topology is not active (it is marked for deregister).
    - No OLM instances in the topology.

  @dependencies
  The elite_cmn_topo_db_init() function was called successfully.
 */
ADSPResult elite_cmn_topo_db_get_olm_topologies(uint32_t area_bit_mask, /*Input arg: Area bit mask */
                                                uint32_t topology_id,   /*Input arg: Topology ID */
                                                uint32_t *num_olm_instances,  /*Output arg: Pointer to number of modules */
                                                elite_cmn_olm_topo_db_entry_t **olm_topo_arr_ptr_ptr /*Output arg: Pointer to OLM topo array ptr  */
                                                );

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef ELITE_CMN_TOPOLOGY_DB_IF_H
