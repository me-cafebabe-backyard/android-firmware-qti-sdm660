#ifndef SPM_COMMON_H
#define SPM_COMMON_H
/*==============================================================================
  FILE:         spm_common.h

  OVERVIEW:     This file contains common public APIs for SPM functionalities that can
                be used by multiple drivers.

  DEPENDENCIES: SPM driver must be initialized before calling any APIs.

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary

  $Header: //components/rel/core.qdsp6/1.0.c2/api/power/spm_common.h#1 $
================================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                           GLOBAL TYPE DEFINITIONS
 =============================================================================*/
/**
 * @brief Default instance name, used mainly for single SPM targets
 */
#define SPM_DEFAULT_INSTANCE_NAME "SPM"

/** 
 * Common macro to fill out structure members for array followed by its size. 
 */ 
#define SPM_ARRAY(arr) arr, (sizeof(arr)/sizeof(arr[0]))

/**
 * @brief SPM cmd type that will be written to actual HW register.
 */
typedef uint8 spm_cmd_t;

/**
 * @brief Type to specify an SPM command sequence for a low power mode or 
 *        other type of SPM sequence reqirement.
 */
typedef struct spm_sequence_data_s
{
  spm_cmd_t *cmds;      /* Pointer to initial command sequence */
  uint16    length;     /* Length of above command sequence */
}spm_sequence_data_t;

/**
 * @brief Return value enumeration for different SPM APIs.
 */
typedef enum
{
  SPM_SUCCESS               = 0,
  SPM_INVALID_HANDLE,        
  SPM_INVALID_PARAM,         
  SPM_NO_SEQ_MEMORY,         
  SPM_MODE_ID_NOT_EXIST,

  SPM_ERROR                 = -1
}spm_result_t;

/**
 * @brief Forward declaration for handle
 */
struct spm_s;
typedef struct spm_s* spm_handle;

/*==============================================================================
                        GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * @brief Programs input command sequence to SPM HW and returns the start
 *        address of the programed sequence.
 *
 * @param handle    : Handle to SPM that will be updated.
 * @param new_seq   : Sequence data to be programed
 * @param start_addr: Start address of given programed sequence
 *
 * @return SPM_SUCCESS if sequence was programmed successfully else error code
 *         - see spm_result_t.
 */
spm_result_t spm_instance_program_cmd_seq(spm_handle          handle,
                                          spm_sequence_data_t *new_seq,
                                          uint16              *start_addr);

/**
 * @brief Updates the existing command sequence in SPM HW.
 *
 * This function should be used when client needs to update its command
 * sequence in SPM depending on run time scenario. This function provides
 * a mechanism to avoid having multiple sequences which are similar
 * in SPM HW. It is useful especially on SPM instances with limited command
 * registers.
 *
 *       As of now this function does not support subsequent command sequences
 *       to be longer than the one programmed for the first time.
 * 
 * @param handle     : Handle to SPM that will be updated. 
 * @param start_addr : Start address set previously from the inital call to 
 *                     spm_instance_program_cmd_seq 
 * @param new_seq    : New sequence data to be programed
 *  
 * @return SPM_SUCCESS if sequence was updated successfully else error
 *         code - see spm_result_t.
 */
spm_result_t spm_instance_update_sequence(spm_handle          handle,
                                          uint16              start_addr,
                                          spm_sequence_data_t *new_seq);

/**
 * @brief Updates a single command in already programmed command sequence.
 *
 * This function is useful if client needs to change only a few commands
 * instead of almost entire sequence at run time.
 *
 * @param handle      : Handle to SPM that will be updated.   
 * @param start_addr  : Start address set previously from the inital call to 
 *                      spm_instance_program_cmd_seq  
 * @param cmd_offset  : Offset of the command in the sequence which will 
 *                      be updated (must be less than sequence length)
 * @param command     : Updated command which will be copied to SPM HW.
 *
 * @return SPM_SUCCESS if command was updated correctly else error code
 *         - see spm_result_t
 */
spm_result_t spm_instance_update_cmd_in_seq(spm_handle   handle,
                                            uint16       start_addr,
                                            uint16       cmd_offset,
                                            spm_cmd_t    command);

/**
 * @brief Returns the SPM handles associated with input entity in passed
 *        buffer. It will return minimum of available handles and handle
 *        buffer size.
 *
 * @dependency spm_driver_init
 *
 * @param entity: Name of the entity SPM handles are requested for (e.g
 *                C0, CL1, L3, Sys).
 * @param count: Number of elements input buffer (next parameter) can
 *               accomodate.
 * @param handles: Input buffer where SPM handles will be returned.
 *
 * @return Number of SPM handles returned for the entity (ideally it should
 *         be equal to count parameter).
 */
uint32 spm_driver_get_handles(const char *entity,
                              uint32     count,
                              spm_handle *handles);

/**
 * @brief Returns number of SPM associated with input entity. This function
 *        is used before actually getting handles to SPMs for the entity.
 *
 * @dependency spm_driver_init
 *
 * @param entity: Name of the entity for which we are querying SPM count
 *                (e.g C0, CL1, L3, Sys)
 *
 * @return Number of SPMs associated with the entity.
 */
uint32 spm_driver_get_count(const char *entity);

#endif

