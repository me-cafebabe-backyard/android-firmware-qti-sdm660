/*===========================================================================
  FILE:         vmpm_target.c
  
  OVERVIEW:     This file contains the function that obtains target specific
                data for mpm driver and assigns them to various structures
                variables so that common driver can use them.

  DEPENDENCY:   DevCfg support. If not available, we may need other 
                implementation of function that initializes target specific
                data.

                Copyright (c) 2013-2014,2016 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/os/default/vmpm_target.c#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 

#include "CoreVerify.h"
#include "DalDevice.h"            /* Header files for DevCfg queries */
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include "DDIHWIO.h"              /* HWIO mapping */
#include "vmpm_internal.h"        /* MPM driver header files */
#include "msmhwiobase.h"
#include "vmpm_src_util.h"
#include "rpm_messageram.h"

/*==========================================================================
 *                           EXTERNAL VARIABLES
 *==========================================================================*/
extern vmpm_data_t *g_messageRamBase;

/*==========================================================================
 *                      GLOBAL FUNCTIONS
 *==========================================================================*/
/*
 * Obtains target specific data and use them to intialize various variables.
 */
void vmpm_TargetDataInit( void )
{
  DALSYSPropertyVar         prop;
  mpm_int_pin_mapping_type  *mappingTablePtr;
  DALSYS_PROPERTY_HANDLE_DECLARE(mpmDevCfgHandle);

  /* Obtaining a DAL handle for our driver */
  CORE_DAL_VERIFY( DALSYS_GetDALPropertyHandleStr( "/dev/core/power/mpm", 
                                                   mpmDevCfgHandle ) );

  /* Set pointer to mpm mapping table */
  CORE_DAL_VERIFY( DALSYS_GetPropertyValue( mpmDevCfgHandle, 
                                            "vmpm_pinNumMappingTable", 
                                            0, &prop ) );
  mappingTablePtr = (mpm_int_pin_mapping_type *)prop.Val.pStruct;

  /* Determine the MPM IRQ/GPIO table size */
  vmpm_setMapTblSize(mappingTablePtr);
  vmpm_setMapTblData(mappingTablePtr);

  /* Get the message ram area for this master */
  g_messageRamBase = rpm_message_ram_vmpm(VMPM_MASTER);
}
