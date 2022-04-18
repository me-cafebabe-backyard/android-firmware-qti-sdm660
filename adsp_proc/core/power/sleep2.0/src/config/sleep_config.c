/*==============================================================================
  FILE:         sleep_config.c
  
  OVERVIEW:     This file provides methods for reading sleep configuration
                data.
 
  DEPENDENCIES: None

                Copyright (c) 2010-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/config/sleep_config.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "sleep_config.h"
#include "CoreVerify.h"
#include "stdio.h"
#include "CoreConfig.h"
#include "sleepi.h"

/*==============================================================================
                               GLOBAL VARIABLES
 =============================================================================*/
/**
 * MAX_SECTION_NAME_LEN
 *  
 * @brief Max number of characters for a section name in the 
 *        sleep ini file.
 */
#define MAX_SECTION_NAME_LEN  128

/*==============================================================================
                        EXTERNAL FUNCTION DECLARATIONS
 =============================================================================*/
/*
 * sleepConfig_readBool
 */
uint32 sleepConfig_readBool(char   *lpr_name,
                            char   *lprm_name,
                            char   *param, 
                            uint8  *result)
{
  char              section[MAX_SECTION_NAME_LEN];
  uint32            retVal = FALSE;
  CoreConfigHandle  config;

  /* Get the CoreConfig object */
  config = sleepOS_createConfigHandle();

  if ( config == NULL )
  {
    return retVal;
  }

  CORE_VERIFY_PTR( lpr_name );

  /* Build the section to read */
  if ( lprm_name )
  {
    snprintf( section, MAX_SECTION_NAME_LEN, "%s.%s", 
              lpr_name, lprm_name );
  }
  else
  {
    snprintf( section, MAX_SECTION_NAME_LEN, "%s", lpr_name );
  }     

  /* Call upon the generic config reader subsystem to read the data
   * for the requested item.  The data will be returned as a boolean. */
  retVal = CoreConfig_ReadBool( config, section, param, result );

  sleepOS_destroyConfigHandle( config );

  return ( ( retVal == CORE_CONFIG_SUCCESS ) ? TRUE : FALSE );
}

