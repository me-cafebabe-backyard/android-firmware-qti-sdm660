#ifndef SLEEP_CONFIG_H
#define SLEEP_CONFIG_H
/*==============================================================================
  FILE:         sleep_config.h
  
  OVERVIEW:     This file provides methods for reading sleep configuration
                data.
 
  DEPENDENCIES: None

                Copyright (c) 2010-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/config/sleep_config.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "DALStdDef.h"

/*==============================================================================
              EXTERNAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepConfig_readBool
 *
 * @brief Reads the value associated with the parameter and LPRM 
 *        passed in.  This function will return the value as a boolean.
 *  
 * @param lpr_name:  LPR name to read the data for.
 * @param lprm_name: LPRM name to read the data for.
 * @param param:     Parameter to read for the specified 
 *                   LPR/LPRM pair.
 * @param result:    Output buffer to write the boolean value 
 *                   read from the config data.
 * 
 * @return FALSE if an error occurred or either the LPR/LPRM 
 *         pair or parameter were not found. TRUE if the
 *         parameter was found, and the value was returned in
 *         the buffer.
 */ 
uint32 sleepConfig_readBool(char    *lpr_name,
                            char    *lprm_name,
                            char    *param,
                            uint8   *result);

#ifdef __cplusplus
}
#endif

#endif /* !SLEEP_CONFIG_H */

