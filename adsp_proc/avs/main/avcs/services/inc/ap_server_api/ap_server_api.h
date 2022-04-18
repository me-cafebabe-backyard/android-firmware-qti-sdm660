#ifndef _AP_SERVER_API_H_
#define _AP_SERVER_API_H_

/**
@file ap_server_api.h

@brief This file contains the structure definitions for the Audio
Processing Server commands used in client-Remote AP communications.
 */
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      AV_Core_Service_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
  Copyright (c) 2017 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Technologies, Inc Proprietary. Export of this technology or software
  is regulated by the U.S. Government, Diversion contrary to U.S. law prohibited.

===========================================================================*/

/*========================================================================
Edit History

$Header:

when       who     what, where, why
--------   ---     -------------------------------------------------------
05/16/17   RR      Created file.
========================================================================== */
/*------------------------------------------------------------------------------
 *  Header Includes
 *----------------------------------------------------------------------------*/
#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#define AP_MAX_CHANNEL_SUPPORTED  32

  /*------------------------------------------------------------------------------
   *  Command Definitions
   *----------------------------------------------------------------------------*/
#include "adsp_begin_pack.h"
  /*  Common Header Structure for the AP Server Commands

    This structure indicates the command handling module
    along with the container instance ID.

    Immediately following this structure are param_size bytes of the
    parameter data. The structure and size depend on the param_id
    value.
   */
  struct ap_server_stat_cmn_header_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the module handling the incoming commands.
         @values #AP_MODULE_AUDPROC_ID_DEFAULT */

    uint16_t                  instance_id;
    /**< Valid ID of the container instance. */

    uint16_t                  reserved;
    /**< This field must be set to 0. */

    uint32_t                  param_id;
    /**< Valid ID of the parameters associated with the container instance.
         @values See Chapter @xref{hdr:APModules} */

    uint32_t                  param_size;
    /**< Maximum size of the parameter data based on the module_id/param_id
         combination.
         @values > 0 bytes, in multiples of 4 bytes */

    uint32_t                  param_version;
    /**< Valid Version of the param_id. Used to identify the payload structure
         @values - See the definition of each of the param IDs */

    uint32_t                  param_struct_size;
    /**< Unit Size of the structure associated with the specified param version
         @values - Depends on the param_id/param_version combination
     */
  }
#include "adsp_end_pack.h"
  ;

  /*
   Module ID used for handling commands related to AudProc Container
   on the AP Server Static Service

   Supports the following Param IDs.
        #AP_PARAM_ID_CREATE_CONTAINER
        #AP_PARAM_ID_CREATE_CONTAINER_PROP
        #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO
        #AP_PARAM_ID_CREATE_CONTAINER_RSP
        #AP_PARAM_ID_DESTROY_CONTAINER
        #AP_PARAM_ID_MEM_MAP
        #AP_PARAM_ID_MEM_MAP_RSP
        #AP_PARAM_ID_MEM_UNMAP
        #AP_PARAM_ID_SET_CONTAINER_MID_PARAM
        #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM
        #AP_PARAM_ID_GET_CONTAINER_MID_PARAM
        #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM
        #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP
        #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP
        #AP_PARAM_ID_DATA_WRITE
        #AP_PARAM_ID_DATA_READ
        #AP_PARAM_ID_DATA_WRITE_DONE
        #AP_PARAM_ID_DATA_READ_DONE
        #AP_PARAM_ID_REGISTER_EVENT
        #AP_PARAM_ID_REGISTER_EVENT_RSP
        #AP_PARAM_ID_CUSTOM_EVENT
        #AP_PARAM_ID_SUSPEND
        #AP_PARAM_ID_FLUSH
        #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT
        #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT
        #AP_PARAM_ID_RUN
        #AP_PARAM_ID_SET_CONTAINER_PROP
        #AP_PARAM_ID_GET_CONTAINER_PROP


   */
#define AP_MODULE_AUDPROC_ID_DEFAULT                                        0x00012932


  /** @ingroup ap_cmd_open
       Creates a AP container instance.

    @apr_hdr_fields
        Opcode -- AP_CMD_OPEN
    @par
        Dst_port -- Ignored
        Dst_addr -- AP Static Service

    @apr_msgpayload
      The payload consists of the following parameter IDs
      along with the command header structure.
       #AP_PARAM_ID_CREATE_CONTAINER
       #AP_PARAM_ID_CREATE_CONTAINER_PROP
       #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO

    @return
       #AP_CMDRSP_OPEN with the status and relevant information
       using #AP_PARAM_ID_CREATE_CONTAINER_RSP

  @dependencies
    None.

   */
#define AP_CMD_OPEN                                                         0x00012933

#include "adsp_begin_pack.h"
  /*
    Structure to identify a module ID-instance ID pair in the
    AP Containers.
   */
  struct ap_module_instance_info_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the module. */

    uint16_t                  instance_id;
    /**< Valid ID of the module instance. */

    uint16_t                  reserved;
    /**< This field must be set to 0. */
  }
#include "adsp_end_pack.h"
  ;

  /** Current supported version of the #AP_PARAM_ID_CREATE_CONTAINER parameter.
      This indicates the structure definition of the parameter payload to be
      parsed.

        @values - {1 .. #AP_PARAM_CREATE_CONTAINER_VERSION}

        @desc param_version
          - 1 -- associated payload %{ap_module_instance_info_t}

  */
#define AP_PARAM_CREATE_CONTAINER_VERSION                                   0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
    the client to create a container for a given list of modules via
    #AP_CMD_OPEN.

      The payload for this parameter consists of a variable sized list of
    module ID/instance ID pairs that need to be instantiated.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
    param_version is 1

   */
#define AP_PARAM_ID_CREATE_CONTAINER                                        0x00012934

  /** Current supported version of the #AP_PARAM_ID_CREATE_CONTAINER_PROP parameter.
      This indicates the structure definition of the parameter payload to be
      parsed.

      @values - {1 .. #AP_PARAM_CREATE_CONTAINER_PROP_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_create_container_prop_v1_t}

  */
#define AP_PARAM_CREATE_CONTAINER_PROP_VERSION                              0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows the
    client to configure the properties for the container during creation via
    #AP_CMD_OPEN

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
    param_version is 1

   */

#define AP_PARAM_ID_CREATE_CONTAINER_PROP                                   0x00012935

  /** @weakgroup ap_create_container_prop_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_CREATE_CONTAINER_PROP parameter for version 1 */
  struct ap_create_container_prop_v1_t
  {
    uint32_t                  client_frame_size;
    /**< The operating frame size of the client in number of unit frames */

    uint32_t                  scale_factor;
    /**< Factor used to determine resource voting for the dynamic container */

    uint32_t                  usecase_type;
    /**< Specifies the type of use case being executed
         @values 0, 1
               0 - Non Real Time Use case
               1 - Real Time Use Case
     */

    uint32_t                  reserved;
    /**< This must be set to zero */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup ap_create_container_prop_v1_t */

  /** Current supported version of the #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO
      parameter. This indicates the structure definition of the parameter payload to be
      parsed.

      @values - {1 .. #AP_PARAM_CREATE_CONTAINER_OUTBAND_INFO_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_create_container_outband_info_v1_t}
  */
#define AP_PARAM_CREATE_CONTAINER_OUTBAND_INFO_VERSION                      0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows the
      client to provide shared memory information during creation via
      #AP_CMD_OPEN.

      On successful creation of the container, this memory region is used to return
      specific fields of #AP_PARAM_ID_CREATE_CONTAINER_RSP back to the client.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1

   */
#define AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO                           0x00012936

  /** @weakgroup ap_create_container_outband_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO parameter for version 1 */
  struct ap_create_container_outband_info_v1_t
  {
    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

         This is returned via #AP_CMD_SHARED_MEM_MAP_REGIONS.
         For in-band messages, this field must be set to 0.

         @values
         - Non-NULL -- Out-of-band
          - The payload begins at the specified physical address
             corresponding to the virtual offset.
            - The total size is data_payload_size bytes. @tablebulletend */

    uint32_t                  data_payload_size;
    /**< Actual Size of the out-band memory shared to the remote module.
         The Remote would write part of response payload information.

         @values > 0 bytes */

  }
#include "adsp_end_pack.h"
  ;

  /** @} */ /* end_weakgroup weak_ap_create_container_outband_info_v1_t */

  /** @ingroup ap_cmdrsp_open
       Returns the status along with relevant container information to the
    client in response to a #AP_CMD_OPEN

    @apr_hdr_fields
        Opcode -- AP_CMDRSP_OPEN
    @par
        Dst_port -- Client
        Dst_addr -- Client

    @apr_msgpayload
        The payload consists of the parameter ID #AP_PARAM_ID_CREATE_CONTAINER_RSP
    along with the common header

    @return
       None

    @dependencies
       #AP_CMD_OPEN must have been issued.

   */

#define AP_CMDRSP_OPEN                                                      0x00012937

/** @weakgroup topo_extn_info_t
@{ */
#include "adsp_begin_pack.h"

  /** Payload indicating the list of active modules in the dynamic
      container.

      The actual information pertaining to the module list is
      available in the shared memory information provided as part
      of #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO as part of
      #AP_CMD_OPEN after the %{topo_extn_info_t} extended payload

      This is currently used by #AP_MODULE_ID_AUDPROC_DEFAULT as part
      of #AP_PARAM_ID_CREATE_CONTAINER_RSP structure.

      The extended payload is of type %{ap_module_instance_info_t}
    */

  struct topo_active_module_list_t
  {
    uint32_t                  num_active_modules;
    /** < Number of modules created in the dynamic container */

    uint32_t                  payload_size;
    /** < Payload size of the module list */
  }
#include "adsp_end_pack.h"
  ;

  /** @weakgroup topo_extn_info_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload indicating the interface and framework extensions
    available in the dynamic container after creation.

    The actual information pertaining to these extensions is
    available in the shared memory information provided as part
    of #AP_PARAM_ID_CREATE_CONTAINER_OUTBAND_INFO as part of
    #AP_CMD_OPEN

    This is currently used by #AP_MODULE_ID_AUDPROC_DEFAULT as part
    of #AP_PARAM_ID_CREATE_CONTAINER_RSP structure
  */

  struct topo_extn_info_t
  {
    uint32_t                  status;
    /**<  Status operation to get the interface and
          framework extension information. (error code).
            @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */

    uint32_t                  num_inf_extn;
    /**< Number of Interface extensions supported by the Container */

    uint32_t                  inf_extn_payload_size;
    /**< Size of the Interface extension Information  */

    uint32_t                  num_fwk_extn;
    /**< Number of Framework extensions supported by the Container */

    uint32_t                  fwk_extn_payload_size;
    /**< Size of the Framework extension information  */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup topo_extn_info_t */

  /** Current supported version of the #AP_PARAM_ID_CREATE_CONTAINER_RSP
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_CREATE_CONTAINER_RSP_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_create_container_rsp_v1_t}

  */
#define AP_PARAM_CREATE_CONTAINER_RSP_VERSION                               0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT as part of the
      command #AP_CMDRSP_OPEN to provide information about the container
      creation status.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1

   */
#define AP_PARAM_ID_CREATE_CONTAINER_RSP                                    0x00012938

  /** @weakgroup ap_create_container_rsp_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_CREATE_CONTAINER_RSP parameter for version 1 */
  struct ap_create_container_rsp_v1_t
  {
    uint32_t                  status;
    /**< Result of the #AP_CMD_OPEN command(error code).
          @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */

    uint32_t                  container_id;
    /**< Unique ID associated with the dynamic container instance */

    uint32_t                  input_num_ports;
    /**< Number of input ports associated with the dynamic container instance */

    uint32_t                  output_num_ports;
    /**< Number of input ports associated with the dynamic container instance */

    uint16_t                  container_apr_addr;
    /**< The registered APR address for the dynamic container instance */

    uint16_t                  reserved;
    /**< Reserved field. Must be set to zero */

    topo_extn_info_t          topo_extension_info_t;
    /**< Information regarding the interface/framework extensions in the
          dynamic container instance */

    topo_active_module_list_t active_topo_def;
    /**< Information regarding the active topology in the dynamic container
          instance */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup ap_create_container_rsp_v1_t */

  /** @ingroup ap_cmd_close
       Destroys an instance of the AP Container.

    @apr_hdr_fields
       Opcode -- AP_CMD_CLOSE
    @par
       Dst_port -- Ignored
       Dst_addr -- AP Static Service

    @apr_msgpayload
       The payload consists of the parameter ID #AP_PARAM_ID_DESTROY_CONTAINER
    along with the common header

    @return
       #APRV2_IBASIC_RSP_RESULT

    @dependencies
       #AP_CMD_OPEN must have been used to create the Container Instance
    successfully

   */
#define AP_CMD_CLOSE                                                        0x00012939

  /** Current supported version of the #AP_PARAM_ID_DESTROY_CONTAINER
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_DESTROY_CONTAINER_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_destroy_container_v1_t}

  */
#define AP_PARAM_DESTROY_CONTAINER_VERSION                                  0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to destroy an instance of AP Dynamic Container using
      #AP_CMD_CLOSE

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1
  */
#define AP_PARAM_ID_DESTROY_CONTAINER                                       0x0001293A

  /** @weakgroup ap_destroy_container_v1_t
@{ */
#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_DESTROY_CONTAINER parameter for version 1 */
  struct ap_destroy_container_v1_t
  {
    uint32_t                  container_id;
    /**< Unique ID associated with the dynamic container instance to be destroyed */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup ap_destroy_container_v1_t */


  /** @ingroup ap_cmd_shared_mem_map_regions
       Commands to the AP to map multiple shared memory regions.
       All the regions must be from the same memory pool.

    @apr_hdr_fields
        Opcode -- AP_CMD_SHARED_MEM_MAP_REGIONS
    @par
        Dst_port -- Ignored
        Dst_addr -- AP Static Service

    @apr_msgpayload
      The payload contains the following parameter ID
      along with the common header structure.
       #AP_PARAM_ID_MEM_MAP

    @return
       #AP_CMDRSP_SHARED_MEM_MAP_REGIONS with the mapped handle information

    @dependencies
        None

   */

#define AP_CMD_SHARED_MEM_MAP_REGIONS                                       0x0001293B

  /**  Current supported version of the #AP_PARAM_ID_MEM_MAP
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_MEM_MAP_VERSION}

       @desc param_version
         - 1 -- associated payload %{ap_cmd_shared_mem_map_regions_v1_t}

  */
#define AP_PARAM_MEM_MAP_VERSION                                            0x1

  /**  Current supported version of the extended payload of #AP_PARAM_ID_MEM_MAP
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_MEM_MAP_REGION_VERSION}

       @desc payload_version
         - 1 -- associated payload %{ap_shared_map_region_payload_v1_t}

  */
#define AP_PARAM_MEM_MAP_REGION_VERSION                                     0x1


  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to enable
      the client map shared memory regions from the same pool using
      #AP_CMD_SHARED_MEM_MAP_REGIONS

      The value of the supported param_version is 1 and the value of the
      supported extended payload version is 1.

   */

#define AP_PARAM_ID_MEM_MAP                                                 0x0001293C

  /** @weakgroup ap_cmd_shared_mem_map_regions_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_MEM_MAP parameter for version 1*/

  struct ap_cmd_shared_mem_map_regions_v1_t
  {
    uint16_t                  mem_pool_id;
    /** Type of memory on which this memory region is mapped.
         @values
              - ADSP_MEMORY_MAP_SHMEM8_4K_POOL

         The memory ID implicitly defines the characteristics of the memory.
         Characteristics can include alignment type, permissions, etc. */

    uint16_t                  num_regions;
    /**< Number of regions to map.

         @values Any value greater than zero */

    uint32_t                  payload_version;
    /**< Valid Version of the map_region_payload.

             @values 1 to #AP_PARAM_MEM_MAP_REGION_VERSION */

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version

             @values Depends on the param_id/param_version combination */

    uint32_t                  property_flag;
    /**< Configures one common property for all regions in the payload.

         @values 0x00000000 to 0x00000001

         Bit 0 is the IsVirtual flag that indicates physical or virtual
         mapping:
           - 0 -- The shared memory address provided in
                  map payload is a physical address. The
                  shared memory must be mapped (a hardware TLB entry), and a
                  software entry must be added for internal bookkeeping.

         @contcell
         Bit 0 (cont.)
           - 1 -- The shared memory address provided in the map
                  payload[usRegions] is a virtual address. The shared memory
                  must not be mapped (because the hardware TLB entry is already
                  available), but a software entry must be added for internal
                  bookkeeping. \n
                  This bit value (1) is useful if two services within the same
                  processor are communicating via the APR. They can directly
                  communicate via the virtual address instead of the physical
                  address. The virtual regions must be contiguous.

         Bits 31 to 1 are reserved and must be set to 0. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_cmd_shared_mem_map_regions_v1_t */

#include "adsp_begin_pack.h"

  /** @weakgroup ap_shared_map_region_payload_v1_t
@{ */

  /* Payload with information of each of the regions to be mapped
     Used in conjunction with the ap_cmd_shared_mem_map_regions_v1_t structure. */
  struct ap_shared_map_region_payload_v1_t
  {
    uint32_t                  shm_addr_lsw;
    /**< Lower 32 bits of the shared memory address of the memory region to
         map. This word must be contiguous memory, and it must be
         4&nbsp;KB aligned.

         @values Any 32-bit value */

    uint32_t                  shm_addr_msw;
    /**< Upper 32 bits of the shared memory address of the memory region to
         map. This word must be contiguous memory, and it must be
         4&nbsp;KB aligned.

         @values
         - For a 32-bit shared memory address, this field must be set to 0.
         - For a 36-bit address, bits 31 to 4 must be set to
           0.
         - For a 64-bit shared memory address, any 32-bit value.
         @tablebulletend */

    uint32_t                  mem_size_bytes;
    /**< Number of bytes in the region.

         @values Multiples of 4 KB

         The regions are always mapped as virtual contiguous memory, but
         the memory size must be in multiples of 4 KB to avoid gaps in the
         virtually contiguous mapped memory. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_shared_map_region_payload_v1_t */


  /** @ingroup ap_cmdrsp_shared_mem_map_regions
        Returns the memory map handle in response to the
            #AP_CMD_SHARED_MEM_MAP_REGIONS command.

    @apr_hdr_fields
        Opcode -- AP_CMDRSP_SHARED_MEM_MAP_REGIONS
    @par
        Dst_port -- Client
        Dst_Addr -- Client

    @apr_msgpayload
        The payload contains the following parameter IDs
        along with the common header structure.
          #AP_PARAM_ID_MEM_MAP_RSP

    @return
        None.

    @dependencies
        #AP_CMD_SHARED_MEM_MAP_REGIONS command must have been issued.
   */
#define AP_CMDRSP_SHARED_MEM_MAP_REGIONS                                    0x0001293D

  /**  Current supported version of the #AP_PARAM_ID_MEM_MAP_RSP
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_MEM_MAP_RSP_VERSION}

       @desc param_version
         - 1 -- associated payload %{ap_cmdrsp_shared_mem_map_regions_v1_t}

  */
#define AP_PARAM_MEM_MAP_RSP_VERSION                                        0x1

   /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT as part of the
       command #AP_CMDRSP_SHARED_MEM_MAP_REGIONS to provide information about the
       status of the memory map operation.

       For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
       param_version is 1
    */
#define AP_PARAM_ID_MEM_MAP_RSP                                             0x0001293E

#include "adsp_begin_pack.h"

  /** @weakgroup ap_cmdrsp_shared_mem_map_regions_v1_t
@{ */

  /*  Payload of the structure used by #AP_PARAM_ID_MEM_MAP_RSP for version 1 */
  struct ap_cmdrsp_shared_mem_map_regions_v1_t
  {
    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

         This handle is returned as a response to
         #AP_CMD_SHARED_MEM_MAP_REGIONS.

         @values Any 32-bit value

         This handle can be used to retrieve the shared memory attributes.
         Also, it is an abstract representation of the shared memory
         regions that are being mapped. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_cmdrsp_shared_mem_map_regions_v1_t */

  /** @ingroup ap_cmd_shared_mem_unmap_regions
         Unmaps the shared memory regions.

    @apr_hdr_fields
        Opcode -- AP_CMD_SHARED_MEM_UNMAP_REGIONS
    @par
        Dst_port -- (ignored)
        Dst_addr -- AP Static Svc

    @apr_msgpayload
        The payload contains the following parameter IDs
        along with the common header structure.
          #AP_PARAM_ID_MEM_UNMAP

    @return
        APRV2_IBASIC_RSP_RESULT (refer to @xrefcond{Q3,80-N1463-2,80-NA601-5}).

    @dependencies
        A corresponding #AP_CMD_SHARED_MEM_MAP_REGIONS command must have been
        issued.
   */
#define AP_CMD_SHARED_MEM_UNMAP_REGIONS                                     0x0001293F

  /** Current supported version of the #AP_PARAM_ID_MEM_UNMAP
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_MEM_UNMAP_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_cmd_shared_mem_unmap_regions_v1_t}

  */
#define AP_PARAM_MEM_UNMAP_VERSION                                          0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to unmap shared memory regions from the same pool.

      The value of the supported param_version is 1
  */

#define AP_PARAM_ID_MEM_UNMAP                                               0x00012940

  /** @weakgroup ap_cmd_shared_mem_unmap_regions_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_MEM_UNMAP parameter for version 1 */
  struct ap_cmd_shared_mem_unmap_regions_v1_t
  {
    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

         This handle was previously returned via a response to
         #AP_CMD_SHARED_MEM_MAP_REGIONS.

         @values Any 32-bit value

         The handle is used to retrieve the associated shared
         memory regions and unmap them. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_cmd_shared_mem_unmap_regions_v1_t */


  /** @ingroup ap_cmd_set_param_config_v1
       Sets calibration/tuning parameters for the container instance.

    @apr_hdr_fields
        Opcode -- AP_CMD_SET_PARAM_CONFIG_V1
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
      The payload consists of the following parameter ID
      along with the common header structure.
       #AP_PARAM_ID_SET_CONTAINER_MID_PARAM

    @return
       #APRV2_IBASIC_RSP_RESULT with the status

  @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_SET_PARAM_CONFIG_V1                                          0x00012941

  /** Current supported version of the common payload used by
      #AP_PARAM_ID_SET_CONTAINER_MID_PARAM, #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM
      and #AP_PARAM_ID_SET_CONTAINER_PROP parameters. This version can be obtained
      from the field param_version of the common header structures associated with
      these parameter IDs.

      The version of the extended payload is available in the common payload structure.

      @values - {1 .. #AP_PARAM_SET_CONTAINER_PARAM_COMMON_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_set_param_config_info_v1_t}

  */
#define AP_PARAM_SET_CONTAINER_PARAM_COMMON_VERSION                         0x1


  /** @weakgroup ap_container_set_param_config_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Common Payload used by #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM,
     #AP_PARAM_ID_SET_CONTAINER_MID_PARAM and #AP_PARAM_ID_SET_CONTAINER_PROP
     to provide the shared memory information for version 1 */
  struct ap_container_set_param_config_info_v1_t
  {
    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

         This is returned via #AP_CMD_SHARED_MEM_MAP_REGIONS.
         For in-band messages, this field must be set to 0.

                 @values
                 - Non-NULL -- Out-of-band
                 - The payload begins at the specified physical address
                   corresponding to the virtual offset.
                 - The total size is data_payload_size bytes. @tablebulletend */

    uint32_t                  data_payload_size;
    /**< Actual size of the variable payload accompanying the message or in
         shared memory. This field is used for parsing both in-band and
         out-of-band data.

                 @values > 0 bytes */

    uint32_t                  payload_version;
    /**< Valid Version of the extended set param payload containing the calibration
         information. This is derived from the param_id in the common header structure.
                 @values
                  - 1 to #AP_PARAM_SET_MID_PARAM_VERSION for
                                         #AP_PARAM_ID_SET_CONTAINER_MID_PARAM
                  - 1 to #AP_PARAM_SET_MID_IID_PARAM_VERSION for
                                         #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM
                  - 1 to #AP_PARAM_CONTAINER_PROP_VERSION for
                                         #AP_PARAM_ID_SET_CONTAINER_PROP */

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version
                 @values Depends on the param_id/payload_version combination */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_set_param_config_info_v1_t */

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_SET_CONTAINER_MID_PARAM parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_SET_MID_PARAM_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_set_mid_param_info_v1_t}

  */
#define AP_PARAM_SET_MID_PARAM_VERSION                                      0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to set the tuning parameter of an AP Dynamic Container instance
      using #AP_CMD_SET_PARAM_CONFIG_V1

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1.
  */
#define AP_PARAM_ID_SET_CONTAINER_MID_PARAM                                 0x00012942

  /** @weakgroup ap_container_set_mid_param_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_SET_CONTAINER_MID_PARAM parameter for version 1

      Immediately following this structure are param_size bytes of the
      parameter data. The structure and size depend on the module_id/param_id
      pair. */
  struct ap_container_set_mid_param_info_v1_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the module */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
            @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  param_size;
    /**< Size of the parameter data based on the module_id/param_id
          combination.
            @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_set_mid_param_info_v1_t */


  /** @ingroup ap_cmd_set_param_config_v2
       Sets calibration/tuning parameters for the container instance.

    @apr_hdr_fields
        Opcode -- AP_CMD_SET_PARAM_CONFIG_V2
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
      The payload consists of the following parameter IDs
      along with the common header structure.
        #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM

    @return
       #APRV2_IBASIC_RSP_RESULT with the status

  @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_SET_PARAM_CONFIG_V2                                          0x00012943
  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_SET_MID_IID_PARAM_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_set_mid_iid_param_info_v1_t}

   */
#define AP_PARAM_SET_MID_IID_PARAM_VERSION                                0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to set the tuning parameter of an AP Dynamic Container instance
      using #AP_CMD_SET_PARAM_CONFIG_V2

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1.
  */
#define AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM                             0x00012944

  /** @weakgroup ap_container_set_mid_iid_param_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_SET_CONTAINER_MID_IID_PARAM parameter

      Immediately following this structure are param_size bytes of the
      parameter data. The structure and size depend on the module_id/param_id
      pair.
   */
  struct ap_container_set_mid_iid_param_info_v1_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the module. */

    uint16_t                  instance_id;
    /**< Valid ID of the module instance. */

    uint16_t                  reserved;
    /**< This field must be set to 0 */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
            @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  param_size;
    /**< Size of the parameter data based on the module_id/param_id
          combination.
            @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_set_mid_iid_param_info_v1_t */

  /** @ingroup ap_cmd_get_param_config_v1
       Gets configuration information of the container instance

    The configuration can be module properties/tuning parameters.

    @apr_hdr_fields
        Opcode -- AP_CMD_GET_PARAM_CONFIG_V1
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
      The payload consists of the following parameter IDs
      along with the common header structure.
       #AP_PARAM_ID_GET_CONTAINER_MID_PARAM

    @return
       #AP_CMDRSP_GET_PARAM_CONFIG_V1 with appropriate information

    @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_GET_PARAM_CONFIG_V1                                          0x00012945

  /** Current supported version of the common payload used by
      #AP_PARAM_ID_GET_CONTAINER_MID_PARAM , #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM
      and #AP_PARAM_ID_GET_CONTAINER_PROP parameters. This version can be obtained from
      the field param_version of the common header structures associated with these
      parameter IDs.

      The version of the extended payload is available in the common payload structure.

      @values - {1 .. #AP_PARAM_GET_CONTAINER_PARAM_COMMON_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_get_param_config_info_v1_t}

    */
#define AP_PARAM_GET_CONTAINER_PARAM_COMMON_VERSION                         0x1

  /** @weakgroup ap_container_get_param_config_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Common payload used by #AP_PARAM_ID_GET_CONTAINER_MID_PARAM and
    #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM to provide the shared memory
    information for version 1 */
  struct ap_container_get_param_config_info_v1_t
  {
    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

         This is returned via #AP_CMD_SHARED_MEM_MAP_REGIONS.
         For in-band messages, this field must be set to 0.

         @values
         - Non-NULL -- Out-of-band
         - The payload begins at the specified physical address
           corresponding to the virtual offset.
         - The total size is data_payload_size bytes. @tablebulletend */

    uint32_t                  data_payload_size;
    /**< Actual size of the variable payload accompanying the message or in
             shared memory. This field is used for parsing both in-band and
             out-of-band data. */

    uint32_t                  payload_version;
    /**< Valid Version of the extended set param payload containing the calibration
         information. This is derived from the param_id in the common header structure.
                 @values
                  - 1 to #AP_PARAM_GET_MID_PARAM_VERSION for
                                         #AP_PARAM_ID_GET_CONTAINER_MID_PARAM
                  - 1 to #AP_PARAM_GET_MID_IID_PARAM_VERSION for
                                         #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM
                  - 1 to #AP_PARAM_CONTAINER_PROP_VERSION for
                                          #AP_PARAM_ID_GET_CONTAINER_PROP */

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version
                     @values Depends on the param_id/payload_version combination */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_param_config_info_v1_t */

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_GET_CONTAINER_MID_PARAM parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_GET_MID_PARAM_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_get_mid_param_info_v1_t}

    */
#define AP_PARAM_GET_MID_PARAM_VERSION                                      0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to get the tuning parameters of module(s) within an AP Dynamic
      container instance via #AP_CMD_GET_PARAM_CONFIG_V1

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1.
   */
#define AP_PARAM_ID_GET_CONTAINER_MID_PARAM                                 0x00012946

  /** @weakgroup ap_container_get_mid_param_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_GET_CONTAINER_MID_PARAM parameter for version 1 */
  struct ap_container_get_mid_param_info_v1_t
  {
    uint32_t                  module_id;
    /**< Information about the module ID/ Instance ID pair */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
             @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  max_param_size;
    /**< Maximum size of the parameter data based on the module_id/param_id
             combination.

             @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_mid_param_info_v1_t */

  /** @ingroup ap_cmd_get_param_config_v2
       Gets configuration information of the container instance

    The configuration can be module properties/tuning parameters.

    @apr_hdr_fields
        Opcode -- AP_CMD_GET_PARAM_CONFIG_V2
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
        The payload consists of the following parameter IDs
        along with the common header structure.
          #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM

    @return
       #AP_CMDRSP_GET_PARAM_CONFIG_V2 with appropriate information

    @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_GET_PARAM_CONFIG_V2                                          0x00012947

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_GET_MID_IID_PARAM_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_get_mid_iid_param_info_v1_t}

  */
#define AP_PARAM_GET_MID_IID_PARAM_VERSION                                0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
    the client to get the tuning parameters of module(s) within an AP Dynamic
    container instance via #AP_CMD_GET_CONFIG

    For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
    param_version (indicating the common payload) is 1 and the value of the
    supported payload_version is 1.
  */
#define AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM                             0x00012948

  /** @weakgroup ap_container_get_mid_iid_param_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM parameter for version 1 */
  struct ap_container_get_mid_iid_param_info_v1_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the Module. */

    uint16_t                  instance_id;
    /**< Valid ID of the module instance */

    uint16_t                  reserved;
    /**< This field must be set to 0 */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
             @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  max_param_size;
    /**< Maximum size of the parameter data based on the module_id/param_id
             combination.

             @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_mid_iid_param_info_v1_t */


  /** Current supported version of the common payload used by
      #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP and
      #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP parameters.
      This version can be obtained from the field param_version of thecommon header
      structures associated with these two parameter IDs.

      The version of the extended payload is available in the common payload structure.

      @values - {1 .. #AP_PARAM_GET_CONTAINER_PARAM_RSP_COMMON_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_get_param_rsp_v1_t}

  */
#define AP_PARAM_GET_CONTAINER_PARAM_RSP_COMMON_VERSION                     0x1

  /** @weakgroup ap_container_get_param_rsp_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Common Payload for the #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP and
      #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP to provide the status
      and extended payload version information. */
  struct ap_container_get_param_rsp_v1_t
  {
    uint32_t                  status;
    /**< Result of the Get Param operation (error code).
          @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */

    uint32_t                  payload_version;
    /**< Valid Version of the extended get param response payload containing the
         calibration information. This is derived from the param_id in the common
         header structure.
                     @values
                      - 1 to #AP_PARAM_GET_MID_PARAM_RSP_VERSION for
                                         #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP
                      - 1 to #AP_PARAM_GET_MID_IID_PARAM_RSP_VERSION for
                                         #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP */

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version
                     @values Depends on the param_id/payload_version combination */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_param_rsp_v1_t */

  /** @ingroup ap_cmdrsp_get_config_v1
       Acknowledgment to #AP_CMD_GET_PARAM_CONFIG_V1

    The configuration can be module properties/tuning parameters.

    @apr_hdr_fields
        Opcode -- AP_CMDRSP_GET_PARAM_CONFIG_V1

    @apr_msgpayload
        The payload consists of the following parameter IDs
        along with the common header structure.
           #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP
           #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP

    @return
       None

    @dependencies
        The command #AP_CMD_GET_PARAM_CONFIG_V1 must have been issued on a valid
    Container instance

   */

#define AP_CMDRSP_GET_PARAM_CONFIG_V1                                       0x00012949

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_GET_MID_PARAM_RSP_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_get_mid_param_rsp_v1_t}

  */
#define AP_PARAM_GET_MID_PARAM_RSP_VERSION                                  0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the container to return the configured calibration parameters of module(s) of
      an AP Dynamic Container using #AP_CMDRSP_GET_PARAM_CONFIG_V1.

      For in-band data, immediately following the common get param response structure is
      acknowledgment parameter data variable payload .The payload depends on the
      size of the parameter.

     For out-of-band data, the acknowledgement parameter data variable payload is present
     at the shared memory address provided by the client.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1
   */

#define AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP                             0x0001294A

  /** @weakgroup ap_container_get_mid_param_rsp_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_GET_CONTAINER_MID_PARAM_RSP parameter for version 1 */
  struct ap_container_get_mid_param_rsp_v1_t
  {
    uint32_t                  module_id;
    /**< Valid ID of the module */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
                @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  param_size;
    /**< Size of the parameter data based on the module_id/param_id
              combination.
                @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_mid_param_rsp_t */

  /** @ingroup ap_cmdrsp_get_param_config_v2
       Acknowledgment to #AP_CMD_GET_PARAM_CONFIG_V2

    The configuration can be module properties/tuning parameters.

    @apr_hdr_fields
        Opcode -- AP_CMDRSP_GET_PARAM_CONFIG_V2

    @apr_msgpayload
        The payload consists of the following parameter IDs
        along with the common header structure.
            #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP

    @return
       None

    @dependencies
        The command #AP_CMD_GET_PARAM_CONFIG_V2 must have been issued on a valid
    Container instance

   */

#define AP_CMDRSP_GET_PARAM_CONFIG_V2                                       0x0001294B
  /** Current supported version of the extended payload of
      #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP parameter. This indicates the
      structure definition of the parameter payload.

        @values - {1 .. #AP_PARAM_GET_MID_IID_PARAM_RSP_VERSION}

        @desc param_version
          - 1 -- associated payload %{ap_container_get_mid_iid_param_rsp_v1_t}

   */
#define AP_PARAM_GET_MID_IID_PARAM_RSP_VERSION                              0x1

 /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
     the container to return the configured calibration parameters of module(s) of
     an AP Dynamic Container using #AP_CMDRSP_GET_CONFIG_V2.

     For in-band data, immediately following the common get param response structure is
     acknowledgment parameter data variable payload .The payload depends on the
     size of the parameter.

     For out-of-band data, the acknowledgement parameter data variable payload is present
     at the shared memory address provided by the client.

     For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
     param_version (indicating the common payload) is 1 and the value of the
     supported payload_version is 1
  */
#define AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP                         0x0001294C

  /** @weakgroup ap_container_get_mid_iid_param_rsp_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_GET_CONTAINER_MID_IID_PARAM_RSP parameter for version 1 */
  struct ap_container_get_mid_iid_param_rsp_v1_t
  {
    ap_module_instance_info_t container;
    /**< Information about the module ID/ Instance ID pair */

    uint32_t                  param_id;
    /**< Valid ID of the parameter.
                @values See Chapter @xref{hdr:AudioPostProcIDs} */

    uint32_t                  param_size;
    /**< Size of the parameter data based on the module_id/param_id
              combination.
                @values > 0 bytes, in multiples of 4 bytes */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_get_mid_iid_param_rsp_v1_t */

  /** @ingroup ap_cmd_data
         Data processing command to the remote AP from the client

    @apr_hdr_fields
        Opcode -- AP_CMD_DATA
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
        The payload consists of the following parameter IDs
        along with the common header structure.
            #AP_PARAM_ID_DATA_WRITE
            #AP_PARAM_ID_DATA_READ

    @return
        AP_CMDRSP_DATA with the appropriate information

    @dependencies
        The AP Dynamic Container must have been opened via #AP_CMD_OPEN
   */
#define AP_CMD_DATA                                                         0x0001294D

  /** @weakgroup ap_container_data_flags_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the flags variable in the data buffers.

     The definition is inline with %{capi_v2_stream_flags_t}. This is used by the
     parameters #AP_PARAM_ID_DATA_WRITE and #AP_PARAM_ID_DATA_READ_DONE */
  struct ap_container_data_flags_t
  {
    uint32_t                  is_timestamp_valid :1;
    /**< Specifies whether the timestamp is valid.

          @values
          - 0 -- Not valid
          - 1 -- Valid @tablebulletend */

    uint32_t                  end_of_frame :1;
    /**< Specifies whether the buffer ends with the end of an encoded frame.

          @values
          - 0 -- The buffer might have an incomplete frame (relevant for
            compressed data only)
          - 1 --The buffer ends with the end of a frame. This allows the module
            to start processing without scanning for the end of frame.
            @tablebulletend */

    uint32_t                  marker_eos :1;
    /**< Indicates that this data is the last valid data from the upstream
          port. */

    uint32_t                  marker_1 :1;
    /**< Data marker 1 used to track data.

          The container module must propagate this marker from the input port
          to any output port that gets input from this port. */

    uint32_t                  marker_2 :1;
    /**< Data marker 2 used to track data.

          The container module must propagate this marker from the input port
          to any output port that gets input from this port. */

    uint32_t                  marker_3 :1;
    /**< Data marker 3 used to track data.

          The container module must propagate this marker from the input port
          to any output port that gets input from this port. */

    uint32_t                  reserved :26;
    /**< Reserved for future use. The client must ignore this value for input
          buffers and set it to zero for output buffers. */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup ap_container_data_flags_t */

  /**  Current supported version of the #AP_PARAM_ID_DATA_WRITE
        parameter. This indicates the structure definition of the parameter payload.

        @values - {1 .. #AP_PARAM_DATA_WRITE_VERSION}

        @desc param_version
          - 1 -- associated payload %{ap_container_data_write_buffer_v1_t}

  */
#define AP_PARAM_DATA_WRITE_VERSION                                         0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to allow the
      client to provide an input buffer to the AP dynamic container using
      #AP_CMD_DATA

      For #AP_MODULE_ID_AUDPROC_DEFAULT, The value of the supported param_version is 1

  */
#define AP_PARAM_ID_DATA_WRITE                                              0x0001294E

  /* Macro definition for port index 0 */
#define AP_CONTAINER_PORT_INDEX_ZERO                                        0x0

  /* Macro definition for port index 1 */
#define AP_CONTAINER_PORT_INDEX_ONE                                         0x1

  /* Macro definition for invalid port index */
#define AP_CONTAINER_PORT_INDEX_INVALID                                     0xF

  /** @weakgroup ap_container_data_write_buffer_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload of the #AP_PARAM_ID_DATA_WRITE buffer provided by the client */
  struct ap_container_data_write_buffer_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the input port number for which the data is provided
            @values
                - #AP_CONTAINER_PORT_INDEX_ZERO
                - #AP_CONTAINER_PORT_INDEX_ONE */

    uint16_t                  reserved;
    /**< Must be set to zero */

    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

       This is returned via #AP_CMD_SHARED_MEM_MAP_REGIONS.
       For in-band messages, this field must be set to 0.

       @values
       - Non-NULL -- Out-of-band
          - The payload begins at the specified physical address
             corresponding to the virtual offset.
          - The total size is buf_size bytes. @tablebulletend */

    uint64_t                  timestamp;
    /**< Timestamp of the buffer in microseconds */

    uint32_t                  buf_size;
    /**< Number of valid bytes available in the buffer. The
             first byte starts at the buffer address.
             @values @ge 0 */

    uint32_t                  seq_id;
    /**< Optional buffer sequence ID. */

    uint32_t                  data_avail;
    /**< Mask to indicate the data availability across all the
         input ports in relation to #AP_CONTAINER_PORT_INDEX_ZERO */

    ap_container_data_flags_t flags;
    /**< Flags to indicated the data buffer properties. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_data_write_buffer_v1_t */

  /**  Current supported version of the #AP_PARAM_ID_DATA_READ
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_DATA_READ_VERSION}

       @desc param_version
         - 1 -- associated payload %{ap_container_data_read_param_v1_t}

  */
#define AP_PARAM_DATA_READ_VERSION                                          0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to allow the
      client to provide an output buffer to the AP dynamic container via
      #AP_CMD_DATA

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1

  */
#define AP_PARAM_ID_DATA_READ                                               0x0001294F

  /** @weakgroup ap_container_data_read_param_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_DATA_READ parameter for version 1 */

  struct ap_container_data_read_param_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the output port number for which the data is provided
            @values
                - #AP_CONTAINER_PORT_INDEX_ZERO */

    uint16_t                  reserved;
    /**< Must be set to zero */

    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.

     This is returned via #AP_CMD_SHARED_MEM_MAP_REGIONS.
     For in-band messages, this field must be set to 0.

     @values
     - Non-NULL -- Out-of-band
        - The payload begins at the specified physical address
           corresponding to the virtual offset.
        - The total size is buf_size bytes. @tablebulletend */

    uint32_t                  buf_size;
    /**< Number of bytes available for the AP Container to read.

         @values > 0  */

    uint32_t                  seq_id;
    /**< Optional buffer sequence ID. */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_data_read_param_v1_t */

  /** @ingroup ap_cmdrsp_data
         Data processing response from the AP to the client

    @apr_hdr_fields
        Opcode -- AP_CMDRSP_DATA
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
        The payload consists of the following parameter IDs
        along with the common header structure.
            #AP_PARAM_ID_DATA_WRITE_DONE
            #AP_PARAM_ID_DATA_READ_DONE

    @return
        AP_CMDRSP_DATA with the appropriate information

    @dependencies
        #AP_CMD_DATA must have been received and processed
   */
#define AP_CMDRSP_DATA                                                      0x00012950

  /** Current supported version of the #AP_PARAM_ID_DATA_WRITE_DONE
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_DATA_WRITE_DONE_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_data_write_buffer_done_v1_t}

  */
#define AP_PARAM_DATA_WRITE_DONE_VERSION                                    0x1


  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to send
      an acknowledgment to the client that the write buffer was consumed via
      AP_CMDRSP_DATA

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1
 */
#define AP_PARAM_ID_DATA_WRITE_DONE                                         0x00012951

#include "adsp_begin_pack.h"

  /** @weakgroup ap_container_data_write_buffer_done_v1_t
@{ */

  /* Payload of the #AP_PARAM_ID_DATA_WRITE_DONE for version 1, which indicates
     that the referenced buffer has been fully consumed and is again available
     to the client */
  struct ap_container_data_write_buffer_done_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the input port number for which the data is provided
            @values
                - #AP_CONTAINER_PORT_INDEX_ZERO
                - #AP_CONTAINER_PORT_INDEX_ONE */

    uint16_t                  reserved;
    /**< Must be set to zero */

    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address. */

    uint32_t                  status;
    /**< Status message (error code) that indicates whether the referenced
         buffer has been successfully consumed.

         @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */
  }
#include "adsp_end_pack.h"
  ;
  /** @} *//* end_weakgroup weak_ap_container_data_write_buffer_done_v1_t */

  /** Current supported version of the #AP_PARAM_ID_DATA_READ_DONE
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_DATA_READ_DONE_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_data_write_buffer_done_t}

  */
#define AP_PARAM_DATA_READ_DONE_VERSION                                    0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to send the filled
      output buffer to the client via #AP_CMDRSP_DATA.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1
   */
#define AP_PARAM_ID_DATA_READ_DONE                                          0x00012952

  /** @weakgroup ap_container_data_read_done_param_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_DATA_READ_DONE parameter for version 1 */

  struct ap_container_data_read_done_param_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the output port number for which the data is provided
            @values
                - #AP_CONTAINER_PORT_INDEX_ZERO */

    uint16_t                  reserved;
    /**< Must be set to zero */

    uint32_t                  status;
    /**< Status message (error code).
        @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */

    uint32_t                  shm_virtual_offset;
    /**< Offset to be applied to the base of the mapped shared memory */

    uint32_t                  mem_map_handle;
    /**< Unique identifier for the shared memory address.*/

    uint32_t                  reserved2;

    uint64_t                  timestamp;
    /**< 64-bit output buffer timestamp */

    uint32_t                  buf_size;
    /**< Total size of the buffer filled in bytes.
        @values @ge 0  */

    ap_container_data_flags_t flags;
    /**< Flags to indicated the data buffer properties. */

    uint32_t                  seq_id;
    /**< Optional buffer sequence ID. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} *//* end_weakgroup weak_ap_container_data_read_done_param_v1_t */

  /** @ingroup ap_cmd_event
       Commands used by the client and AP to communicate information
    via events.

    @apr_hdr_fields
        Opcode -- AP_CMD_EVENT
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Container Service/Client

    @apr_msgpayload
        The payload contains the following parameter IDs
        along with the common header structure.
            #AP_PARAM_ID_REGISTER_EVENT
            #AP_PARAM_ID_REGISTER_EVENT_RSP
            #AP_PARAM_ID_CUSTOM_EVENT

    @return
        Appropriate Response based on the type of PARAM ID

    @dependencies
        The AP Container must have been successfully created using
        #AP_CMD_OPEN

   */

#define AP_CMD_EVENT                                                        0x00012953

  /** Current supported version of the #AP_PARAM_ID_REGISTER_EVENT
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_DESTROY_CONTAINER_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_register_event_v1_t}

  */
#define AP_PARAM_REGISTER_EVENT_VERSION                                     0x1

  /**  Current supported version of the extended payload of #AP_PARAM_ID_REGISTER_EVENT
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_REGISTER_EVENT_PAYLOAD_VERSION}

       @desc payload_version
         - 1 -- associated payload %{ap_container_register_event_info_v1_t}

  */
#define AP_PARAM_REGISTER_EVENT_PAYLOAD_VERSION                             0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to register for
      events with the AP Dynamic Container via #AP_CMD_EVENT

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1 and the value of the supported extended payload_version is 1

   */

#define AP_PARAM_ID_REGISTER_EVENT                                          0x00012954

  /** @weakgroup ap_container_register_event_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_REGISTER_EVENT parameter for version 1 */
  struct ap_container_register_event_v1_t
  {
    uint32_t                  payload_version;
    /**< Valid Version of the map_region_payload.

             @values 1 to #AP_PARAM_REGISTER_EVENT_PAYLOAD_VERSION */

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version

             @values Depends on the param_id/param_version combination */

    uint32_t                  num_events;
    /**< Num of events to be registered with the service */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_register_event_v1_t */

  /** @weakgroup ap_container_register_event_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Bit mask definition for Register Event */
#define AP_MODULE_BITMASK_REGISTER_EVENT_FLAG                               (1 >> 0)

  /* Bit mask definition for De-Register Event */
#define AP_MODULE_BITMASK_DEREGISTER_EVENT_FLAG                             (1 >> 1)

  /* Payload containing information about the register event for version 1 */
  struct ap_container_register_event_info_v1_t
  {
    uint32_t                  event_id;
    /**< Event ID to be registered */

    uint32_t                  module_id;
    /**<  Module ID to be registered */

    uint16_t                  instance_id;
    /**< Instance ID of the module in the current topology
            If Module ID, Instance ID both are set to 0, then the
                event is registered with all the modules and
                the instances in the topology

            If Module ID is set to 0 and Instance ID is set to a
                non-zero value, it is treated as invalid payload */

    uint16_t                  reserved;
    /**< reserved field. This should be set to 0     */

    uint32_t                  config_mask;
    /**< This is a configuration mask to handle the events.
                @values{for bit 0}
                    0 - Event Registration is disabled
                    1 - Event Registration is enabled

            To enable/disable this bit use
            #AP_MODULE_BITMASK_REGISTER_EVENT_FLAG and
            #AP_MODULE_BITMASK_DEREGISTER_EVENT_FLAG respectively

          Other bits are reserved and are set to 0 */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_register_event_info_v1_t */

  /** Current supported version of the #AP_PARAM_ID_REGISTER_EVENT_RSP
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_REGISTER_EVENT_RSP_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_register_event_rsp_v1_t}

    */
#define AP_PARAM_REGISTER_EVENT_RSP_VERSION                                 0x1


  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to send events raised
      by AP Dynamic Container using #AP_CMD_EVENT. The client must have registered
      for these using #AP_PARAM_ID_REGISTER_EVENT

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1

  */
#define AP_PARAM_ID_REGISTER_EVENT_RSP                                      0x00012955

  /** @weakgroup ap_container_register_event_rsp_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_REGISTER_EVENT_RSP for version 1 */
  struct ap_container_register_event_rsp_v1_t
  {
    uint32_t                  event_id;
    /**< Event ID for which payload is generated */

    uint32_t                  module_id;
    /**< Module ID which raised the event */

    uint16_t                  instance_id;
    /**< Instance ID which raised the event */

    uint16_t                  reserved;
    /**< Reserved field to be set to 0 */

    uint32_t                  payload_size;
    /**< Size of the event response payload.
         Immediately following this is the event specific payload */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_register_event_rsp_v1_t */

  /** Current supported version of the #AP_PARAM_ID_CUSTOM_EVENT
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_CUSTOM_EVENT_VERSION}

      @desc param_version
        - 1 -- associated payload %{ap_container_custom_event_v1_t}

  */
#define AP_PARAM_CUSTOM_EVENT_VERSION                                       0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to raise custom
      asynchronous events to the client.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1.

      Based on the event type, the extended payloads have associated versions.
   */

#define AP_PARAM_ID_CUSTOM_EVENT                                            0x00012956

#include "adsp_begin_pack.h"

  /** @weakgroup ap_container_custom_event_v1_t
@{ */

  /** Payload containing information about the custom event
    Immediately following this is event_id specific payload
   */
  struct ap_container_custom_event_v1_t
  {
    ap_module_instance_info_t container;
    /**< Information about the module instance raising the event */

    uint32_t                  event_id;
    /**< Event ID for which the payload is generated
          @expected values
            #AP_EVENT_OUTPUT_MEDIA_FORMAT
            #AP_EVENT_NUM_UNIT_FRAMES
            #AP_EVENT_DELAY
     */
    
    uint32_t                  event_status;
    /**< Event Status (error code).
        @values Refer to @xrefcond{Q5,80-NF774-4,80-NA610-4} */
        
    uint32_t                  event_version;
    /**< Valid Version of the event_id.
           @values Depends on the event_id/module_id combination */

    uint32_t                  event_struct_size;
    /**< Unit Size of the structure associated with the specified event_version
           @values Depends on the param_id/param_version combination */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_custom_event_v1_t */

  /** Below are Valid event IDs for the #AP_PARAM_ID_CUSTOM_EVENT parameter
      These are used in the event_id field of the custom event payload */

  /** Current supported version of the event payload of #AP_EVENT_OUTPUT_MEDIA_FORMAT
      parameter. This indicates the structure definition of the parameter payload.
      This value is available in the event_version field of the custom event payload

       @values - {1 .. #AP_PARAM_OUTPUT_MEDIA_FORMAT_VERSION}

       @desc payload_version
         - 1 -- associated payload %{ap_container_event_output_media_format_v1_t}

    */
#define AP_PARAM_OUTPUT_MEDIA_FORMAT_VERSION                                0x1

  /** Event to indicate a change in output media format for the container

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      event_version is 1
  */
#define AP_EVENT_OUTPUT_MEDIA_FORMAT                                        0x00012957

  /** @weakgroup ap_container_event_output_media_format_v1_t
@{ */
#include "adsp_begin_pack.h"

  /** Payload containing information about the #AP_EVENT_OUTPUT_MEDIA_FORMAT
      for version 1

      Immediately following this is the appropriate payload configuration
      based on the type of param_id & payload_version

      For #AP_MODULE_ID_AUDPROC_DEFAULT, the supported payload_version values are
      1 for the event param IDs #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT and
      #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT */
  struct ap_container_event_output_media_format_v1_t
  {
    uint32_t                  event_param_id;
    /**< Param ID to indicate the type of media format
              @expected values
                #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT
                #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT */

    uint32_t                  payload_version;
    /**< Valid Version of the media format payload.
             @values based on event_param_id
             - 1 to #AP_PARAM_MCH_PCM_MEDIA_FORMAT_VERSION (or)
             - 1 to #AP_PARAM_COMPRESSED_MEDIA_FORMAT_VERSION*/

    uint32_t                  payload_struct_size;
    /**< Unit Size of the structure associated with the specified payload_version
                 @values Depends on the event_param_id/param_version combination */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_event_output_media_format_t */

  /** Current supported version of the event payload of #AP_EVENT_NUM_UNIT_FRAMES
        parameter. This indicates the structure definition of the parameter payload.
        This value is available in the event_version field of the custom event payload

         @values - {1 .. #AP_PARAM_NUM_UNIT_FRAMES_VERSION}

         @desc payload_version
           - 1 -- associated payload %{ap_container_event_num_frames_v1_t}

   */
#define AP_PARAM_NUM_UNIT_FRAMES_VERSION                                    0x1

  /**< Event to indicate a change in processing frame size for the container

       For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
        event_version is 1
  */
#define AP_EVENT_NUM_UNIT_FRAMES                                            0x00012958

  /** @weakgroup ap_container_event_num_frames_v1_t
@{ */

#include "adsp_begin_pack.h"

  /** Payload containing information about the #AP_EVENT_NUM_UNIT_FRAMES for version 1
   */
  struct ap_container_event_num_frames_v1_t
  {
    uint32_t                  num_frames;
    /**< Number of unit frames in the processing frame size of the container */

    uint32_t                  port_threshold;
    /**< Indicates if the processing frame size of the container is a result of
         #CAPI_V2_EVENT_PORT_DATA_THRESHOLD_CHANGE from the container topology
            @values
             - 0 : no event raised
             - 1 : event raised */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup ap_container_event_num_frames_v1_t */

  /** Current supported version of the event payload of #AP_EVENT_DELAY
      parameter. This indicates the structure definition of the parameter payload.
      This value is available in the event_version field of the custom event payload

       @values - {1 .. #AP_PARAM_DELAY_VERSION}

       @desc payload_version
         - 1 -- associated payload %{ap_container_event_delay_v1_t}

   */
#define AP_PARAM_DELAY_VERSION                                              0x1
  /**< Event to indicate a change in the delay for the container

       For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
        event_version is 1
  */
#define AP_EVENT_DELAY                                                      0x00012959

  /** @weakgroup ap_container_event_delay_v1_t
@{ */
#include "adsp_begin_pack.h"

  /** Payload containing information about the #AP_EVENT_DELAY for version 1 */
  struct ap_container_event_delay_v1_t
  {
    uint32_t                  delay;
    /**< Value of delay of the container */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_event_delay_v1_t */

  /** Current supported version of the event payload of #AP_EVENT_DISABLE
        parameter. This indicates the structure definition of the parameter payload.
        This value is available in the event_version field of the custom event payload

         @values - {1 .. #AP_PARAM_OUTPUT_MEDIA_FORMAT_VERSION}

         @desc payload_version
           - 1 -- associated payload %{ap_container_event_output_media_format_v1_t}

  */
#define AP_PARAM_EVENT_DISABLE_VERSION                                      0x1

  /** Event used by the AP Container or the client to indicate that the sender is in a
        bad state. This event is used by the receiver to disable itself.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
        event_version is 1. There is no payload associated with this command.
  */
#define AP_EVENT_DISABLE                                                    0x0001296E

  /** @ingroup ap_cmd_suspend
        Suspends the AP Container. All hardware resources held by the Container service are
    relinquished.


    @apr_hdr_fields
        Opcode -- AP_CMD_SUSPEND
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure along with
    parameter IDs
        #AP_PARAM_ID_SUSPEND

    @return
        APRV2_IBASIC_RSP_RESULT (refer to @xrefcond{Q3,80-N1463-2,80-NA601-5}).

    @dependencies
        The specified instance ID must have been successfully opened via
    #AP_CMD_OPEN
   */

#define AP_CMD_SUSPEND                                                      0x0001295A
  /** Current supported version of the #AP_PARAM_ID_SUSPEND
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_SUSPEND_VERSION}

      @desc param_version
        - 1 -- no associated payload

  */
#define AP_PARAM_SUSPEND_VERSION                                            0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to suspend the
      AP Container.

      There is no payload structure associated with this parameter.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1
   */
#define AP_PARAM_ID_SUSPEND                                                 0x0001295B

  /** @ingroup ap_cmd_flush
        Flushes the AP Container.


    @apr_hdr_fields
        Opcode -- AP_CMD_FLUSH
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure along with
    parameter IDs
           #AP_PARAM_ID_FLUSH

    @return
        APRV2_IBASIC_RSP_RESULT (refer to @xrefcond{Q3,80-N1463-2,80-NA601-5}).

    @dependencies
        The specified instance ID must have been successfully opened via
    #AP_CMD_OPEN
   */

#define AP_CMD_FLUSH                                                        0x0001295C
  /** Current supported version of the #AP_PARAM_ID_FLUSH
      parameter. This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_FLUSH_VERSION}

      @desc param_version
        - 1 -- no associated payload

  */
#define AP_PARAM_FLUSH_VERSION                                              0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to flush the
      AP Container.

      There is no payload structure associated with this parameter.

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version is 1
   */
#define AP_PARAM_ID_FLUSH                                                   0x0001295D


  /** @ingroup ap_cmd_data_eos
        Communicates an End of Stream (EoS) marker, which indicates that the last
    buffer to the AP Container has been delivered.


    @apr_hdr_fields
        Opcode -- AP_CMD_DATA_EOS
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure with parameter ID
            #AP_PARAM_ID_EOS

    @return
        #AP_DATA_CMD_RENDERED_EOS is raised when the last sample before EOS is
    delivered

    @dependencies
        The specified instance ID must have been successfully opened via
    #AP_CMD_OPEN
   */

#define AP_CMD_DATA_EOS                                                     0x0001295E
  /** Current supported version of the #AP_PARAM_ID_EOS
      parameter for #AP_CMD_DATA_EOS.
      This indicates the structure definition of the parameter payload.

      @values - {1 .. #AP_PARAM_EOS_VERSION}

      @desc param_version
        - 1 -- no associated payload

  */
#define AP_PARAM_EOS_VERSION                                                0x1

  /** Current supported version of the #AP_PARAM_ID_EOS
       parameter for #AP_CMD_DATA_RENDERED_EOS.
       This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_EOS_VERSION}

       @desc param_version
         - 1 -- no associated payload

   */
#define AP_PARAM_EOS_RENDERED_VERSION                                        0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to indicate the
      end of stream from the client side.

      There is no payload structure associated with this parameter.
   */
#define AP_PARAM_ID_EOS                                                     0x0001295F

  /** @ingroup ap_cmd_data_rendered_eos
        Indicates that the last sample in the AP Container has been
    successfully rendered after an #AP_CMD_DATA_EOS is received, and that no
    more samples will be rendered.


    @apr_hdr_fields
        Opcode -- AP_CMD_DATA_RENDERED_EOS
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure with parameter ID
           #AP_PARAM_ID_EOS

    @return
        None

    @dependencies
        #AP_CMD_DATA_EOS must have been issued to the AP Container
   */

#define AP_CMD_DATA_RENDERED_EOS                                            0x00012960

  /** @ingroup ap_cmd_data_media_fmt_update
        Indicates an update to the media format, which applies to future buffers
    written to this stream


    @apr_hdr_fields
        Opcode -- AP_CMD_DATA_MEDIA_FMT_UPDATE
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure with parameter ID
            - #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT
            - #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT

    @return
        None

    @detdesc
        This message must be properly sequenced with corresponding
    #AP_DATA_CMD with #AP_PARAM_ID_DATA_WRITE

    @par
        If #AP_DATA_CMD commands for #AP_PARAM_ID_DATA_WRITE arrive before this
    command, the data buffers are discarded. Corresponding response
    #AP_CMDRSP_DATA with #AP_PARAM_ID_DATA_WRITE_DONE are raised with an
    error status.

    @dependencies
        The specified instance ID must have been successfully opened via
    #AP_CMD_OPEN and put to run state using #AP_CMD_RUN
   */


#define AP_CMD_DATA_MEDIA_FMT_UPDATE                                        0x00012961

  /**  Current supported version of the extended payload of #AP_EVENT_OUTPUT_MEDIA_FORMAT
       and #AP_CMD_DATA_MEDIA_FMT_UPDATE for #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT parameter ID.
       This indicates the structure definition of the PCM media format payload.

       @values - {1 .. #AP_PARAM_MCH_PCM_MEDIA_FORMAT_VERSION}

       @desc payload_version
          - 1 -- associated payload %{ap_container_mch_pcm_fmt_blk_v1_t}

   */
#define AP_PARAM_MCH_PCM_MEDIA_FORMAT_VERSION                               0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to specify the
      PCM input/output media format of the AP Container.

      For #AP_MODULE_ID_AUDPROC_DEFAULT, the supported payload_version value is 1
   */

#define AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT                                    0x00012962


#include "adsp_begin_pack.h"

  /** @weakgroup ap_container_mch_pcm_fmt_blk_v1_t
@{ */

  /* Payload of the #AP_PARAM_ID_MCH_PCM_MEDIA_FORMAT parameter for version 1 */
  struct ap_container_mch_pcm_fmt_blk_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the input port number for which the data is provided
            @values
               for input media format
                - #AP_CONTAINER_PORT_INDEX_ZERO
                - #AP_CONTAINER_PORT_INDEX_ONE

               for output media format
                - #AP_CONTAINER_PORT_INDEX_INVALID
     */

    uint16_t                  num_channels;
    /**< Number of channels.
         Supported values: 1 to 8 */

    uint16_t                  bits_per_sample;
    /**< Number of bits per sample per channel. */

    uint16_t                  q_format;
    /** < Q format of the fixed point data */

    uint16_t                  is_signed;
    /**< Indicates that the samples are signed (1). */

    uint16_t                  is_interleaved;
    /**< Specifies whether the data is interleaved.
             @values
             - 0 -- De-interleaved
             - 1 -- Interleaved @tablebulletend */

    uint32_t                  sample_rate;
    /**< Number of samples per second (in Hertz). */

    uint32_t                  media_format;
    /**< Format of the data. */

    uint8_t                   channel_mapping[AP_MAX_CHANNEL_SUPPORTED];
    /**< Array of channel mappings of size 8.
         Channel[i] mapping describes channel I. Each element i of the array
             describes channel I inside the buffer where 0 @le I < num_channels.
             An unused channel is set to zero. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_mch_pcm_fmt_blk_v1_t */

  /**  Current supported version of the extended payload of #AP_EVENT_OUTPUT_MEDIA_FORMAT
       and #AP_CMD_DATA_MEDIA_FMT_UPDATE for #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT parameter ID.
       This indicates the structure definition of the compressed media format payload.

       @values - {1 .. #AP_PARAM_COMPRESSED_MEDIA_FORMAT_VERSION}

       @desc payload_version
          - 1 -- associated payload %{ap_container_compr_fmt_blk_v1_t}

   */
#define AP_PARAM_COMPRESSED_MEDIA_FORMAT_VERSION                            0x1

  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to specify the
      Compressed input/output media format of the AP Container.

      For #AP_MODULE_ID_AUDPROC_DEFAULT, the supported payload_version value is 1
   */
#define AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT                                 0x00012963

  /** @weakgroup ap_container_compr_fmt_blk_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_COMPRESSED_MEDIA_FORMAT parameter, to
   specify the updated compressed input media format for the subsequent buffers
   queued to this container. */

  struct ap_container_compr_fmt_blk_v1_t
  {
    uint16_t                  port_index;
    /**< Indicates the input port number for which the data is provided
            @values
            @values
               for input media format
                - #AP_CONTAINER_PORT_INDEX_ZERO
                - #AP_CONTAINER_PORT_INDEX_ONE

               for output media format
                - #AP_CONTAINER_PORT_INDEX_INVALID */

    uint16_t                  reserved;
    /**< Must be set to zero */

    uint16_t                  num_channels;
    /**< Number of channels.

             @values 1 to 8 */

    uint16_t                  bits_per_sample;
    /**< Number of bits per sample per channel. */

    uint32_t                  sample_rate;
    /**< Number of samples per second (in Hertz). */

    uint32_t                  media_format;
    /**< Format of the compressed data.

             This parameter uses the ASM_MEDIA_FMT* definitions in
             adsp_media_fmt.h. */
  }
#include "adsp_end_pack.h"
  ;
  /** @} *//* end_weakgroup weak_ap_container_compr_fmt_blk_v1_t */

  /** @ingroup ap_cmd_run
        Runs the AP Container.
    @par
        This is needed by the AP Container to process subsequent data
    path commands.

    @apr_hdr_fields
        Opcode -- AP_CMD_RUN
    @par
        Dst_port: Container Instance ID
        Dst_addr: AP Container

    @apr_msgpayload
        The payload contains the common header structure along with
    parameter ID specific structures. Supported parameters include
            - #AP_PARAM_ID_RUN

    @return
        APRV2_IBASIC_RSP_RESULT (refer to @xrefcond{Q3,80-N1463-2,80-NA601-5}).

    @dependencies
        The specified instance ID must have been successfully opened via
    #AP_CMD_OPEN
   */

#define AP_CMD_RUN                                                          0x00012964
  /** Current supported version of the #AP_PARAM_ID_RUN
       parameter. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_RUN_VERSION}

       @desc param_version
         - 1 -- no associated payload

   */
#define AP_PARAM_RUN_VERSION                                                0x1

   /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT to run the
       AP Container.

       There is no payload structure associated with this parameter.

       For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
       param_version is 1
    */
#define AP_PARAM_ID_RUN                                                     0x00012965

  /** @ingroup ap_cmd_set_prop_config
       Sets general properties of the container instance

    @apr_hdr_fields
        Opcode -- AP_CMD_SET_PROP_CONFIG
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
      The payload consists of the following parameter IDs
      along with the common header structure.
       #AP_PARAM_ID_SET_CONTAINER_PROP

    @return
       #APRV2_IBASIC_RSP_RESULT with the status

  @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_SET_PROP_CONFIG                                              0x00012966

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_SET_CONTAINER_PROP parameter. This indicates the
       structure definition of the parameter payload.

         @values - {1 .. #AP_PARAM_CONTAINER_PROP_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_prop_info_v1_t}

  */
#define AP_PARAM_CONTAINER_PROP_VERSION                                     0x1

  /**  Current supported version of the extended payload of
       #AP_PARAM_ID_SET_CONTAINER_PROP parameter. This indicates the
       structure definition of the actual prop payload structure

         @values - {1 .. #AP_PARAM_CONTAINER_PROP_PAYLOAD_VERSION}

         @desc param_version
           - 1 -- associated payload %{ap_container_prop_payload_v1_t}

  */
#define AP_PARAM_CONTAINER_PROP_PAYLOAD_VERSION                             0x1


  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to set the properties of module(s) of an AP Container instance
      using #AP_CMD_SET_PROP_CONFIG

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1 and supported prop_version is 1

   */
#define AP_PARAM_ID_SET_CONTAINER_PROP                                      0x00012967

  /** @weakgroup ap_container_prop_info_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Payload of the #AP_PARAM_ID_SET_CONTAINER_PROP parameter for version 1 */

  struct ap_container_prop_info_v1_t
  {
    uint32_t                  num_prop;
    /**< Number of properties in the payload */

    uint32_t                  prop_version;
    /**< Valid Version of the extended set/get prop payload containing the property
         information. This is derived from the param_id in the common header structure.
               @values
                  - 1 to #AP_PARAM_CONTAINER_PROP_PAYLOAD_VERSION for
                         #AP_PARAM_ID_SET_CONTAINER_PROP and
                         #AP_PARAM_ID_GET_CONTAINER_PROP */

    uint32_t                  prop_struct_size;
    /**< Unit Size of the structure associated with the specified prop_version
              @values Depends on the param_id/payload_version combination */
  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_prop_info_v1_t */

  /** @weakgroup ap_container_prop_payload_v1_t
@{ */

#include "adsp_begin_pack.h"

  /* Actual Property payload of the #AP_PARAM_ID_SET_CONTAINER_PROP parameter */

  struct ap_container_prop_payload_v1_t
  {
    uint32_t                  prop_id;
    /**< ID of the property */

    uint32_t                  prop_payload_size;
    /**< Size of the payload corresponding to the property
          Immediately following this is the prop_payload_size bytes of data */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_container_prop_payload_v1_t */

  /** @ingroup ap_cmd_get_prop_config
       Sets general properties of the container instance

    @apr_hdr_fields
        Opcode -- AP_CMD_GET_PROP_CONFIG
    @par
        Dst_port -- Instance ID
        Dst_addr -- AP Dynamic Container

    @apr_msgpayload
      The payload consists of the following parameter IDs
      along with the common header structure.
       #AP_PARAM_ID_GET_CONTAINER_PROP

    @return
       #APRV2_IBASIC_RSP_RESULT with the status

  @dependencies
        The Dynamic Container Instance must have been opened successfully via #AP_CMD_OPEN.

   */

#define AP_CMD_GET_PROP_CONFIG                                              0x00012968


  /** Parameter used by module #AP_MODULE_AUDPROC_ID_DEFAULT which allows
      the client to get the properties of module(s) f an AP Container instance
      using #AP_CMD_GET_PROP_CONFIG

      For module #AP_MODULE_AUDPROC_ID_DEFAULT, the value of the supported
      param_version (indicating the common payload) is 1 and the value of the
      supported payload_version is 1 and supported prop_version is 1
   */
#define AP_PARAM_ID_GET_CONTAINER_PROP                                      0x00012969

  /** @ingroup ap_event_static_service_up
       Returns the status of the AP Static Service.

       This event is sent from Remote DSP to ADSP, once the static service
       in remote DSP is initialized successfully.

      @apr_hdr_fields
          Opcode -- AP_EVENT_STATIC_SERVICE_UP
      @par
          Dst_port -- None
          Dst_addr -- Audio Core Service {AVCS} in ADSP

      @apr_msgpayload
        The payload consists of the payload %{
        along with the common header structure.
         #AP_PARAM_ID_SERVICE_STATUS

      @return
         #APRV2_IBASIC_RSP_RESULT with the status

      @dependencies
          The remote AP Static Service must have been created successfully

  */
#define AP_EVENT_STATIC_SERVICE_UP                                          0x0001296A
  /** Current supported version of the #AP_PARAM_ID_SERVICE_STATUS
       command. This indicates the structure definition of the parameter payload.

       @values - {1 .. #AP_PARAM_SERVICE_STATUS_VERSION}

       @desc param_version
         - 1 -- associated payload %{ap_event_static_service_up_v1_t}

   */
#define AP_PARAM_SERVICE_STATUS_VERSION                                     0x1

  /** Parameter used by the AP Static Service which sends the service status
      to the Audio Voice Core Service (AVCS) in the aDSP using
      #AP_EVENT_STATIC_SERVICE_UP

      The value of the supported param_version is 1
  */
#define AP_PARAM_ID_SERVICE_STATUS                                          0x0001296B

#include "adsp_begin_pack.h"
  /** @weakgroup ap_event_static_service_up_v1_t
 @{ */

  /* Payload of #AP_PARAM_ID_SERVICE_STATUS parameter for version 1 */
  struct ap_event_static_service_up_v1_t
  {
    uint32_t                  proc_id;
    /**< Current processor ID. */

  }
#include "adsp_end_pack.h"
  ;
  /** @} */ /* end_weakgroup weak_ap_event_static_service_up_v1_t */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _AP_SERVER_API_H_ */
