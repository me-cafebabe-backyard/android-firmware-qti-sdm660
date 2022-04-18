/*! \file
 *  
 *  \brief  pm_appsbl_proc_npa.c ----This file contains initialization functions for NPA
 *  \details This file contains initialization functions for NPA
 *          and node definitions.
 *  
* Copyright (c) 2014 , Qualcomm Technologies Inc. All rights reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/
/*=============================================================================
                              EDIT HISTORY


 when            who     what, where, why
 --------     ---     -----------------------------------------------------------
 08/29/14     al         KW fixes
 05/28/14     va         Adding History

=============================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

//#include "pm_uefi.h"
#include <Library/BaseLib.h>

#include "npa.h"
#include "npa_resource.h"



#include "CoreVerify.h"

#include "pmapp_npa.h"
#include "pm_npa.h"
#include "pm_appsbl_proc_npa_device.h"
#include "pm_appsbl_proc_npa.h"
#include "pm_npa_device.h"
#include "pm_target_information.h"
#include "pm_utils.h"
#include "DDIPlatformInfo.h"
#include "pm_sw_event.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                LOCAL FUNCTION PROTOTYPES

===========================================================================*/
unsigned                            num_of_nodes = 0;
npa_node_definition                *pmic_npa_appsbl_nodes = NULL;
npa_resource_definition            *pmic_npa_appsbl_resources = NULL;

//void ShowNodeRsc(pm_npa_node_resource_info *nodeRsc);

void pm_appsbl_proc_npa_device_init(void);
/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/

/*===========================================================================

                         FUNCTION DEFINITIONS

===========================================================================*/
/* Surf, FFA, FLUID platform info*/
DalPlatformInfoPlatformInfoType pm_npa_platform_info;


/*===========================================================================

                FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION pm_appsbl_proc_npa_platform_compensate

DESCRIPTION
    This function performes the changes needed for surf ffa on PAM data.

INPUT PARAMETERS
  None.

RETURN VALUE
  None.

DEPENDENCIES
  Platform detection should be avaliable.

SIDE EFFECTS
  NONE.

===========================================================================*/
static void
pm_appsbl_proc_npa_platform_compensate(void)
{
  DalDeviceHandle      *phPFormInfo = NULL;
  DALResult             eResult;

  eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPFormInfo);

  if (DAL_SUCCESS == eResult)
  {
    DalDevice_Open(phPFormInfo, DAL_OPEN_SHARED);
    DalPlatformInfo_GetPlatformInfo(phPFormInfo, &pm_npa_platform_info);
    DalDevice_Close(phPFormInfo);
  }
}


/*===========================================================================

FUNCTION pm_appsbl_proc_pam_init                                EXTERNAL
FUNCTION

DESCRIPTION
This function initializes the PAM for PMIC.

It does the following:
* Initializes the NPA PMIC Nodes and resources.

INPUT PARAMETERS
None.

RETURN VALUE
None.

DEPENDENCIES
NPA Framework should be available in the build being compiled for

SIDE EFFECTS
NONE.

===========================================================================*/
static void
pm_appsbl_proc_pam_init(void)
{
  pm_appsbl_proc_npa_platform_compensate();
} /* end of pm_appsbl_proc_pam_init() */


#if 0
static void ShowNodeRsc(pm_npa_node_resource_info *nodeRsc)
{

  if(!nodeRsc)
  {
    DEBUG((EFI_D_ERROR, "BAD PARAM \n\r"));
    return;
  }

  DEBUG((EFI_D_ERROR, "grp Name (%s) \n\r ", nodeRsc->group_name));
  DEBUG((EFI_D_ERROR,"Nde Name (%s) \n\r", nodeRsc->node_name));

  DEBUG((EFI_D_ERROR,"dependency_count (%d)\n\r ", nodeRsc->dependency_count));
  DEBUG((EFI_D_ERROR,"Max Mode (%d)\n\r", nodeRsc->max_mode));

  DEBUG((EFI_D_ERROR,"node_attributes (%d)\n\r ", nodeRsc->node_attributes));
  if(NULL != nodeRsc->node_data)
  DEBUG((EFI_D_ERROR,"nodeRsc->node_data Valid (%d)\n\r", nodeRsc->node_data));
  else
  DEBUG((EFI_D_ERROR,"nodeRsc->node_data In Valid \n\r"));

  if(NULL != nodeRsc->node_dependencies)
  {
    DEBUG((EFI_D_ERROR,"nodeRsc->node_dependencies Valid (%d)\n\r", nodeRsc->node_dependencies));
    DEBUG((EFI_D_ERROR,"nodeRsc->node_dependencies Client Name (%s)\n\r", nodeRsc->node_dependencies->name));
    DEBUG((EFI_D_ERROR,"nodeRsc->node_dependencies Client type (%d)\n\r", nodeRsc->node_dependencies->client_type));
    DEBUG((EFI_D_ERROR,"nodeRsc->node_dependencies Client Handle (%d)\n\r", nodeRsc->node_dependencies->handle));
  }
  else
  DEBUG((EFI_D_ERROR,"nodeRsc->node_dependencies In Valid \n\r"));

  DEBUG((EFI_D_ERROR,"nodeRsc->resource_attributes (%d)\n\r ", nodeRsc->resource_attributes));

  if(NULL != nodeRsc->resource_data)
  DEBUG((EFI_D_ERROR,"nodeRsc->resource_data (%d)\n\r ", nodeRsc->resource_data));
  else
  DEBUG((EFI_D_ERROR,"nodeRsc->resource_data Invalid \n\r "));

}
#endif
/*===========================================================================

FUNCTION pm_appsbl_proc_npa_init                                EXTERNAL FUNCTION

DESCRIPTION
This function initializes the NPA for PMIC.

It does the following:
* It initializes the PMIC NPA Node and resources.

INPUT PARAMETERS
None.

RETURN VALUE
None.

DEPENDENCIES
NPA Framework should be available in the build being compiled for

SIDE EFFECTS
NONE.

===========================================================================*/
void
pm_uefi_proc_npa_init(void)
{
  unsigned i;

  uint32 *nodes = NULL;

  pm_sw_event(PMIC_MPSS_PAM_INIT, 0);


  pm_npa_node_resource_info  *nodeRscArray  = NULL;
  pm_npa_node_resource_info  *nodeRsc       = NULL;

  /* Init PAM */
  pm_appsbl_proc_pam_init();

  /* Init RPM device trans-apply */
  pm_appsbl_proc_npa_device_init();

  // Get the PAM info
  nodeRscArray = (pm_npa_node_resource_info *)pm_target_information_get_specific_info(PM_PROP_PAM_NODE_RSRCS);

  nodes = (uint32 *)pm_target_information_get_specific_info(PM_PROP_PAM_NODE_NUM);

  CORE_VERIFY_PTR(nodes);

  num_of_nodes = *nodes;

  if (num_of_nodes && nodeRscArray)
  {
    pm_malloc(sizeof(npa_node_definition) * num_of_nodes, (void **)&pmic_npa_appsbl_nodes);
    pm_malloc(sizeof(npa_resource_definition) * num_of_nodes, (void **)&pmic_npa_appsbl_resources);

    memset(pmic_npa_appsbl_resources, 0x00, sizeof(npa_resource_definition) * num_of_nodes);
    memset(pmic_npa_appsbl_nodes, 0x00, sizeof(npa_node_definition) * num_of_nodes);

    // construct the PMIC RPM resources
    for (i = 0; i < num_of_nodes; i++)
    {
      nodeRsc = &nodeRscArray[i];

      //ShowNodeRsc(nodeRsc);

      // construct the PMIC RPM resources
      pmic_npa_appsbl_resources[i].name = nodeRsc->group_name;
      pmic_npa_appsbl_resources[i].units = "ModeID";
      pmic_npa_appsbl_resources[i].max = nodeRsc->max_mode;
      pmic_npa_appsbl_resources[i].attributes = nodeRsc->resource_attributes;
      if ((pmic_npa_appsbl_resources[i].attributes & NPA_RESOURCE_SINGLE_CLIENT) ==
             NPA_RESOURCE_SINGLE_CLIENT)
      {
        pmic_npa_appsbl_resources[i].plugin = &npa_identity_plugin;
      }
      else
      {
        pmic_npa_appsbl_resources[i].plugin = &npa_max_plugin;
      }
      pmic_npa_appsbl_resources[i].data = nodeRsc->resource_data;

      // construct the PMIC RPM Nodes
      pmic_npa_appsbl_nodes[i].name = nodeRsc->node_name;

      //Set appropriate callback function in case of MSS Node
      if (AsciiStrCmp(pmic_npa_appsbl_resources[i].name, PMIC_NPA_GROUP_ID_MEM_UVOL) == 0)
      {
        pmic_npa_appsbl_nodes[i].driver_fcn = pm_npa_resource_set_vdd_uvol;
      }
      else
      {
        pmic_npa_appsbl_nodes[i].driver_fcn = pm_npa_resource_set;
      }

      pmic_npa_appsbl_nodes[i].attributes = nodeRsc->node_attributes;
      pmic_npa_appsbl_nodes[i].data = nodeRsc->node_data;
      pmic_npa_appsbl_nodes[i].dependencies = nodeRsc->node_dependencies;
      pmic_npa_appsbl_nodes[i].dependency_count = nodeRsc->dependency_count;
      pmic_npa_appsbl_nodes[i].resource_count = 1;
      pmic_npa_appsbl_nodes[i].resources = NULL;
    }
  }
  else
  {
    ERR_FATAL("PMIC-UEFI PAM initialization failed ", 0, 0, 0);
  }

  for (i = 0; i < num_of_nodes; i++)
  {
    pmic_npa_appsbl_nodes[i].resources = &pmic_npa_appsbl_resources[i];
    npa_define_node(pmic_npa_appsbl_nodes + i, NULL, NULL);
  }

} /* end of pm_appsbl_proc_npa_init() */


//#endif // PM_IMAGE_appsbl_PROC
