   /*============================================================================
  @file therm_npa_mitigate.c

  Define NPA nodes representing mitigation states.
  
 
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/src/driver/thermal/adsppm_therm_npa_mitigate.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Author: pwbldsvc $
========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "npa_resource.h"
#include "CoreVerify.h"
#include "ULog.h"
#include "ULogFront.h"
#include "VCSDefs.h"
#include "adsppm_utils.h"
#include "adsppm_therm_npa_mitigate.h"

/*=======================================================================

                  STATIC MEMBER / FUNCTION DECLARATIONS / DEFINITIONS

========================================================================*/

static npa_client_handle lpiCXHandle = NULL;

static npa_resource_state adsppm_therm_node_mitigate_driver_fcn(npa_resource *resource,
                                                         npa_client   *client,
                                                         npa_resource_state state);

static void lpiCxHandleInitCb ( void  *context,
      unsigned int  event_type,
      void         *data,
      unsigned int  data_size );
														 
/*=======================================================================

                  GLOBAL DEFINITIONS

========================================================================*/
/* Supplies device list for QMI request for mitigation device list.
   Must edit if additional mitigation devices are added. */
const char *adsppm_therm_mitigation_devices[] = 
{
  "cpuv_restriction_cold"
};


const unsigned int adsppm_therm_mitigation_devices_count =
 ARR_SIZE(adsppm_therm_mitigation_devices);

/* "/therm/mitigate" node and resource
   Must edit if additional mitigation devices are added. */

static npa_resource_plugin adsppm_therm_mitigate_plugin;

static npa_resource_definition adsppm_therm_mitigate_resource[] =
{
  {
    "/therm/mitigate/cpuv_restriction_cold",               /* name of resource */
    "State Level",                      /* Units of the resource */
    0x1,                                /* Maximum value of resource */
    &adsppm_therm_mitigate_plugin,
    NPA_RESOURCE_DRIVER_UNCONDITIONAL,
    NULL,
    NULL
  }
};

npa_node_definition adsppm_therm_mitigate_node = 
{
  "/node/therm/mitigate",            /* Node name - info only */
  adsppm_therm_node_mitigate_driver_fcn,    /* Driver function for temperature */
  NPA_NODE_DEFAULT,                  /* No attributes */
  NULL,                              /* No User Data */
  NPA_EMPTY_ARRAY,                   /* No Dependencies */
  NPA_ARRAY(adsppm_therm_mitigate_resource) /* Resources */
};

/* Used to limit max mitigation to zero for special test cases */
//static boolean limit_max_zero = FALSE;

/*=======================================================================

                  LOCAL FUNCTION DEFINITIONS

========================================================================*/

/**
  @brief adsppm_therm_node_mitigate_driver_fcn

  Mitigate node driver function.  Nothing to update.

  @param  : resource: A dynamic system element that work requests can be made against.
            client: The handle to the clients registered to the
            resource.
            state: Update function state.

  @return : Resource state.
*/
static npa_resource_state adsppm_therm_node_mitigate_driver_fcn(npa_resource *resource,
                                                         npa_client   *client,
                                                         npa_resource_state state)
{
  if(client->type == NPA_CLIENT_INITIALIZE)
  {
    // The driver function will be called with this client *before* it is 
    // made publicly available, so you can place any initialization you 
    // need here.

    // The value of state passed here is provided by the 
    // npa_define_node function.
  }
  if(NULL != lpiCXHandle)
  {

  	if(state==1)
	{
		/* When mitigation is requested */
		/* issue npa request to clkregime lpi_cx for NOR vote */
		npa_issue_required_request(lpiCXHandle, VCS_CORNER_NOMINAL);

		ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, 
					"Mitigation %s set to NOMINAL",
					adsppm_therm_mitigation_devices[resource->index]);
	}
	else
	{
		/* cancel/remove npa request to clkregime lpi_cx*/
		npa_cancel_request(lpiCXHandle);

		ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, 
					"Mitigation %s cancelled",
					adsppm_therm_mitigation_devices[resource->index]);
	}				
  }
  else
  {
		ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "lpiCXHandle is NULL");
  }

  return state;
}

static void lpiCxHandleInitCb ( void  *context,
				 unsigned int  event_type,
				 void         *data,
				unsigned int  data_size )
{
    ADSPPM_LOG_FUNC_PROFILESTART;

	ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "lpiCxHandleInitCb");
	
    lpiCXHandle = npa_create_sync_client( LPICX_NODE_NAME,
           LPICX_ADSPPM_CLIENT_NAME,
            NPA_CLIENT_REQUIRED);
    if (NULL == lpiCXHandle)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create NPAclient for lpi_cx!");
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
}

/*=======================================================================

                 PUBLIC FUNCTION DEFINITIONS

========================================================================*/

/**
  @brief adsppm_therm_npa_mitigate_init

  Thermal mitigate init function.

  @param  : None

  @return : None.
*/
void adsppm_therm_npa_mitigate_init( void )
{ 
  npa_resource_state adsppm_initial_state = 0; /* Default is disabled */

  /* Copy all attributes of standard NPA max pluggin */
  memscpy(&adsppm_therm_mitigate_plugin, sizeof(npa_resource_plugin), &npa_max_plugin, sizeof(npa_resource_plugin));
  adsppm_therm_mitigate_plugin.supported_clients |= NPA_CLIENT_CUSTOM1;

  /* check clkregime lpi_cx resource is available*/
  npa_resource_available_cb(LPICX_NODE_NAME, lpiCxHandleInitCb, NULL);

   /* Define SW mitigate nodes */ 
  npa_define_node( &adsppm_therm_mitigate_node, &adsppm_initial_state, NULL );
}
