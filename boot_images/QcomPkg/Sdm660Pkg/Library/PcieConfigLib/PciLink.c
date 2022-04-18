/** 
 @file PciLink.c

  PCIe Initialization function.

  Copyright (c) 2014-2016, Qualcomm Technologies Inc. All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 02/08/16 tselvam  Added pcie xml config support
 11/12/15 tselvam  KW reivew #6754 & #6755
 09/03/15 tselvam  SDM660 Support Included
 08/07/15 tselvam  Updated with new PHY seq for V3.0 h/w
 07/01/15 tselvam  Fixed the 7e bug check in HLOS by reverting the Limit region value
                   to just cover until the first 4KB of EP config space.
 06/22/15 tselvam  Fixed the compile error while 32-bit uefi.mbn build.
 06/15/15 tselvam  Used clock reset API and also updated unified code.
                   Implemented PCIe capability walk for L1ss enabling.
 05/13/15 tselvam  Unified code for multi platforms
 03/18/15 tselvam  Fixed Copyrights header
 03/09/15 tselvam  reduced some delays to improve boot time and include warning
                   messages and fixed running pcieTest more than once by adding
                   gcc bcr reset sequences.
 03/05/15 tselvam  written class code register value in PCIe_Setup_L1ss fn.
 01/26/15 tselvam  Updated as per 8994 changes
 12/15/14 tselvam  Changes for 8996 for all three root ports
 10/07/14 ahalabi  Changes for 8996
 08/04/14 nk       Changed MemLabel
 06/16/14 hozefak  Add PcieInit protocol
 05/20/14 hozefak  Edit to bring in changes for 8994 PHY
 05/07/14 hozefak  Turn on PCie during exitbootservices
 04/18/14 hozefak  First checkin for 8994
=============================================================================*/


#include <Library/IoLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/BaseLib.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFINpa.h>
#include <Include/Protocol/EFIChipInfo.h>
#include <Library/PcieConfigLib.h>
#include <Protocol/EFIPCIeInit.h>
#include <DDIChipInfo.h>

#include "PciLink.h"
#include "PcieBsp.h"
#include "DALSys.h"

/*NPA headers*/
#include "npa.h"
#include "pmapp_npa.h"

STATIC CONST pcieBsp_t * gPcieBspCtx = NULL;

/* handle for the npa client. */
STATIC npa_client_handle PcieReqClient = NULL;

STATIC EFI_STATUS PCIe_DeinitializeLDO(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (PcieReqClient != NULL)
  {
    npa_issue_required_request(PcieReqClient, PMIC_NPA_MODE_ID_PCIE_OFF);   //Sends OFF to the driver
    npa_complete_request(PcieReqClient);           //Sends the driver a 0
    npa_destroy_client(PcieReqClient);
    PcieReqClient = NULL;
  }
  else
  {
    DEBUG(( EFI_D_WARN, "PCIe_DeinitializeLDO: PcieReqClient is NULL\r\n"));
    return EFI_NOT_READY;
  }

   return Status;
}

/**
 * Turn off any root port specific PHY clocks
 *
 * @param[in] UINT32 rpIndex :- root port index
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_TurnOffPortClocks(UINT32 rpIndex)
{
  UINTN                  ClockId;
  UINT32                 ClockCount;
  EFI_CLOCK_PROTOCOL     *pClockProtocol;
  BOOLEAN                clockEnabled = FALSE;
  EFI_STATUS             Status;

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&pClockProtocol);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_TurnOffPortClocks: Clock LocateProtocol failed\r\n"));
    return Status;
  }

  for (ClockCount = gcc_pcie_phy_clk; ClockCount < gcc_max_pcie_clk; ClockCount++)
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->port_clk_name_list[rpIndex][ClockCount], &ClockId);
    Status = pClockProtocol->IsClockEnabled(pClockProtocol, ClockId, &clockEnabled);
    if(clockEnabled == TRUE)
      Status = pClockProtocol->DisableClock(pClockProtocol, ClockId);
  }

  return Status;
}

/**
 * Turn off any common PHY specific clocks
 *
 * @param[in] VOID
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_TurnOffPhyClocks()
{
  UINTN                  ClockId;
  UINT32                 ClockCount;
  EFI_CLOCK_PROTOCOL     *pClockProtocol;
  BOOLEAN                clockEnabled = FALSE;
  EFI_STATUS             Status;

  if (gPcieBspCtx->phy_clk_name_list == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_TurnOffPhyClocks: No phy clocks available\r\n"));
    return EFI_SUCCESS;
  }

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&pClockProtocol);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_TurnOffPhyClocks: Clock LocateProtocol failed\r\n"));
    return Status;
  }

  for (ClockCount = gcc_pcie_phy_cfg_ahb_clk; ClockCount < gcc_max_pcie_phy_clk; ClockCount++)
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->phy_clk_name_list[ClockCount], &ClockId);
    Status = pClockProtocol->IsClockEnabled(pClockProtocol, ClockId, &clockEnabled);
    if(clockEnabled == TRUE)
      Status = pClockProtocol->DisableClock(pClockProtocol, ClockId);
  }

  return Status;
}

/**
 * Deinitialize by turning off the clocks
 *
 * @param[in] VOID
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_Deinitialize(VOID)
{
  UINT32                 rootPortIdx = 0;
  EFI_STATUS             Status;

  do
  {
    Status = PCIe_TurnOffPortClocks(rootPortIdx);
    rootPortIdx++;
  }while (rootPortIdx < gPcieBspCtx->max_rp);

  Status = PCIe_TurnOffPhyClocks();

  Status = PCIe_DeinitializeLDO();

  return Status;
}
/**
 * Enable LDOs required by ROME through NPA
 *
 * @param VOID
 *
 * @return EFI_STATUS
 */

EFI_STATUS PCIe_InitialzeLDO(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(PcieReqClient == NULL)
  {
    PcieReqClient =  npa_create_sync_client(
                                         PMIC_NPA_GROUP_ID_PCIE,          // Connect to the usb hs1 resource
                                         "pcie", // Descriptive name
                                         NPA_CLIENT_REQUIRED);   /* Your client type --  types can be:
                                                                   // * NPA_CLIENT_REQUIRED: Request must honor request
                                                                   // * NPA_CLIENT_IMPULSE: Poke the resource - node defines the impulse response
                                                                   // * NPA_CLIENT_LIMIT_MAX: Set maximum value for the resource
                                                                   // * NPA_CLIENT_VECTOR: Vector request
                                                                   // * NPA_CLIENT_SUPPRESSIBLE: Suppressible Scalar request -- requests
                                                                   // *                          honored only in active set
                                                                   // * NPA_CLIENT_SUPPRESSIBLE_VECTOR: Suppressible Vector request
                                                                   // */
  }

  if (NULL == PcieReqClient)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitialzeLDO: npa_create_sync_client returned NULL\r\n"));
    return EFI_DEVICE_ERROR;
  }

  npa_issue_required_request(PcieReqClient, PMIC_NPA_MODE_ID_PCIE_ACTIVE_NOMINAL);   //Sends Activate to the driver

  return Status;
}

/**
 * Enable all the clocks and reset the GDSCR
 *
 * @param VOID
 *
 * @return EFI_STATUS
 */

EFI_STATUS PCIe_EnableClocks(PRootPort_Config_Data *Head)
{
  UINTN                 ClockId;
  EFI_CLOCK_PROTOCOL    *pClockProtocol;
  PRootPort_Config_Data CurrentNode;
  UINTN                 uClockPowerDomainId;
  UINT32                ClockCount, nFreqHz;
  BOOLEAN               clockEnabled = FALSE;
  EFI_STATUS Status;

  if (Head == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
   
  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&pClockProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: Clock LocateProtocol failed\r\n"));
    return Status;
  }

  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    Status = pClockProtocol->GetClockPowerDomainID(pClockProtocol, gPcieBspCtx->clk_pwr_dmn_name_list[CurrentNode->rootPortIdx], &uClockPowerDomainId);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: GetClockPowerDomainID failed\r\n"));
      return Status;
    }
    Status =  pClockProtocol->EnableClockPowerDomain(pClockProtocol, uClockPowerDomainId);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: EnableClockPowerDomain failed\r\n"));
      return Status;
    }

    for (ClockCount = gcc_pcie_phy_cfg_ahb_clk; ClockCount < gcc_max_pcie_phy_clk; ClockCount++)
    {
      /*
       * This clock name list is optional for some targets
       * So, check for NULL before accessing it
       */
      if (gPcieBspCtx->phy_clk_name_list == NULL)
      {
        DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: No Phy clocks available\r\n"));
        break;
      }

      Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->phy_clk_name_list[ClockCount], &ClockId);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: GetClockID failed %s\r\n",
                gPcieBspCtx->phy_clk_name_list[ClockCount]));
        return Status;
      }

      Status = pClockProtocol->IsClockEnabled(pClockProtocol, ClockId, &clockEnabled);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: IsClockEnabled failed %s\r\n",
                gPcieBspCtx->phy_clk_name_list[ClockCount]));
        return Status;
      }
      if (clockEnabled == FALSE)
      {
        /* Perform reset once for this block of clocks */
        if (ClockCount == gcc_pcie_phy_cfg_ahb_clk)
        {
          Status = pClockProtocol->ResetClock(pClockProtocol, ClockId, EFI_CLOCK_RESET_PULSE);
          if EFI_ERROR (Status)
          {
            DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: ResetClock failed %s\r\n",
                    gPcieBspCtx->phy_clk_name_list[ClockCount]));
            return Status;
          }
        }
        Status = pClockProtocol->EnableClock(pClockProtocol, ClockId);
        if EFI_ERROR (Status)
        {
          DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: EnableClock failed %s\r\n",
                  gPcieBspCtx->phy_clk_name_list[ClockCount]));
          return Status;
        }
      }
    }

    for (ClockCount = gcc_pcie_phy_clk; ClockCount < gcc_max_pcie_clk; ClockCount++)
    {
      Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][ClockCount], &ClockId);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: GetClockID failed %s\r\n",
                gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][ClockCount]));
        return Status;
      }

      /* Perform reset once for this block of clocks */
      if (ClockCount == gcc_pcie_phy_clk)
      {
        Status = pClockProtocol->ResetClock(pClockProtocol, ClockId, EFI_CLOCK_RESET_ASSERT);
        if EFI_ERROR (Status)
        {
          DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: ResetClock assert failed %s\r\n",
                  gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][ClockCount]));
          return Status;
        }
        gBS->Stall(500);
        Status = pClockProtocol->ResetClock(pClockProtocol, ClockId, EFI_CLOCK_RESET_DEASSERT);
        if EFI_ERROR (Status)
        {
          DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: ResetClock deassert failed %s\r\n",
                  gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][ClockCount]));
          return Status;
        }
      }

      Status = pClockProtocol->EnableClock(pClockProtocol, ClockId);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: EnableClock failed %s\r\n",
                gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][ClockCount]));
        return Status;
      }
    }

    Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_aux_clk], &ClockId);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: EnableClock failed %s\r\n",
              gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_aux_clk]));
      return Status;
    }

    //Try exact frequency match
    Status = pClockProtocol->SetClockFreqHz(pClockProtocol, ClockId,
                                           1000000,
                                           EFI_CLOCK_FREQUENCY_HZ_CLOSEST, &nFreqHz);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_EnableClocks: SetClockFreqHz failed %s\r\n",
              gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_aux_clk]));
      return Status;
    }

    CurrentNode = CurrentNode->Next;
  }

  return Status;
}

/**
 * Add the data struct for each RP as a node into the Linked List
 *
 * @param CurrentData, Data for each RP
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_AddtoLinkedList(PRootPort_Config_Data CurrentData, PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data NewNode, Current;
  EFI_STATUS Status;

  Status = gBS->AllocatePool(EfiBootServicesData, sizeof(RootPort_Config_Data), (VOID *)&NewNode); //Init 1st node
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_AddtoLinkedList: AllocatePool failed\r\n"));
    return Status;
  }

  NewNode->ConfigBaseAddress = CurrentData->ConfigBaseAddress;
  NewNode->ParfBaseAddress = CurrentData->ParfBaseAddress;
  NewNode->ElbiBaseAddress = CurrentData->ElbiBaseAddress;
  NewNode->AxiAddrSpaceSize = CurrentData->AxiAddrSpaceSize;
  NewNode->rootPortIdx = CurrentData->rootPortIdx;
  NewNode->EndpointPresent = FALSE; /* ASSUME NO ENDPOINT*/
  /* SmmuByPassMode, need to be read dynamically */
  NewNode->SmmuByPassMode = TRUE;
  /*EcamBlockerEn, need to be read dynamically */
  NewNode->EcamBlockerEn = TRUE;
  NewNode->Next = NULL;
  if (*Head == NULL)
  {
    *Head = NewNode;
  }
  else
  {
    Current = *Head;
    while (Current->Next != NULL)
    {
      Current = Current->Next;
    }
    Current->Next = NewNode;
  }

  return EFI_SUCCESS;
}

/**
 * Read number of Root ports
 *
 * @param[out] number_of_rps, number of RPs to be enabled
 * @param[out] enabled_rps,   rp index to be enabled
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_ReadNumberofRP(UINT32 * number_of_rps, UINT32 * enabled_rps)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32     RPMask = 0;

  /* Get the number of RPs*/
  RPMask = gPcieBspCtx->RPMask;

  *number_of_rps = RPMask & NUM_OF_RP_MASK;
  if (*number_of_rps == 0)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ReadNumberofRP: No RPs found to initialized\r\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  *enabled_rps = (RPMask & RP_ENABLE_MASK) >> RP_MASK_LENGTH;
  if (*enabled_rps == 0)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ReadNumberofRP: No RPs to be initialized\r\n"));
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

Exit:
  return Status;
}

/**
 * Fill in linked list with data for each root port based
 * on number of root ports available
 *
 * @param[out] StartNode, Pointer to the first Node of the
 *       linked list which contains data about all Root Ports
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_ReadConfigData(PRootPort_Config_Data *StartNode)
{
  DALSYS_PROPERTY_HANDLE_DECLARE (hPcieBootProperties);
  RootPort_Config_Data           Config_Data;
  UINT32 				         rootPortIdx = 0;
  UINT32 				         enabled_rps = 0;
  UINT32                         total_rps = 0;
  CONST CHAR8 *                  pcieBspPropName = "PCIE_BSP";
  DALSYSPropertyVar              propertyVar;
  CONST pcieBsp_t *              pcieBsp = NULL;
  EFI_STATUS 			         Status;

  /* Init DAL sys */
  DALSYS_InitMod(NULL);

  Status = DALSYS_GetDALPropertyHandleStr("/core/hwengines/pcie", hPcieBootProperties);
  if (Status != DAL_SUCCESS)
  {
     return EFI_LOAD_ERROR;
  }

  Status = DALSYS_GetPropertyValue(hPcieBootProperties,
                                   pcieBspPropName,
                                   0,
                                   &propertyVar);
  if (Status != DAL_SUCCESS)
  {
     return EFI_LOAD_ERROR;
  }

  pcieBsp = (pcieBsp_t *)propertyVar.Val.pStruct;
  if (pcieBsp == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ReadConfigData: DALConfig returned NULL\r\n"));
    return EFI_LOAD_ERROR;
  }

  gPcieBspCtx = pcieBsp;

  Status = PCIe_ReadNumberofRP(&total_rps, &enabled_rps);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ReadConfigData: PCIe_ReadNumberofRP failed\r\n"));
    return Status;
  }

  while (total_rps)
  {
    rootPortIdx = __builtin_ctz(enabled_rps);
    if (rootPortIdx >= gPcieBspCtx->max_rp)
    {
      DEBUG(( EFI_D_WARN, "PCIe_ReadConfigData: __builtin_ctz rootPortIdx OORange\r\n"));
      return EFI_INVALID_PARAMETER ;
    }

    Config_Data.ConfigBaseAddress = gPcieBspCtx->reg_base_address[dbi_reg_base][rootPortIdx];
    Config_Data.ParfBaseAddress   = gPcieBspCtx->reg_base_address[parf_reg_base][rootPortIdx];
    Config_Data.ElbiBaseAddress   = gPcieBspCtx->reg_base_address[elbi_reg_base][rootPortIdx];
    Config_Data.AxiAddrSpaceSize  = gPcieBspCtx->axi_addr_space_size[rootPortIdx];
    Config_Data.rootPortIdx = rootPortIdx;

    Status = PCIe_AddtoLinkedList(&Config_Data, StartNode);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_ReadConfigData: PCIe_AddtoLinkedList failed\r\n"));
      return Status;
    }

    /* Masking out the identified root port index */
    enabled_rps &= (~ (((UINT32)0x01) << rootPortIdx) );
    total_rps--;
  }

  return EFI_SUCCESS;
}

/**
 * Initialize the common PHY
 *
 * @param[out] Head, Pointer to the first Node of the linked
 *       list which contains data about all Root Ports
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_InitializePHY()
{
  UINT32                index = 0;
  UINT32                rootPortIdx = 0;
  UINT32                isTimeout = 0;

  if (gPcieBspCtx->phy_register_seq[index].reg_offset == PHY_REG_NOP)
  {
    return EFI_SUCCESS;
  }

  REG_WRITE_CONDITIONAL(gPcieBspCtx->reg_base_address[gPcieBspCtx->phy_register_seq[index].base][rootPortIdx],
    gPcieBspCtx->phy_register_seq[index].reg_offset,
    gPcieBspCtx->phy_register_seq[index].reg_val,
    index);

  /*POLL status */
  index++;

  POLL_UNTIL (
    gPcieBspCtx->reg_base_address[gPcieBspCtx->phy_register_seq[index].base][0] +
    gPcieBspCtx->phy_register_seq[index].reg_offset,
    gPcieBspCtx->phy_register_seq[index].reg_val,
    TRUE,
    100,
    isTimeout
  );

  if(isTimeout) {
	  return EFI_LOAD_ERROR;
  }

  return EFI_SUCCESS;
}

/**
 * Initialize the PHY for each root port
 *
 * @param[out] Head, Pointer to the first Node of the linked
 *       list which contains data about all Root Ports
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_InitializePortPHY(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                index;
  UINT32                isTimeout;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializePortPHY: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializePortPHY: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    index = 0;
    isTimeout = 0;
    if(gPcieBspCtx->port_phy_register_seq[index].reg_offset == PHY_REG_NOP)
    {
      CurrentNode = CurrentNode->Next;
      continue;
    }

    REG_WRITE_CONDITIONAL(gPcieBspCtx->reg_base_address[gPcieBspCtx->port_phy_register_seq[index].base][CurrentNode->rootPortIdx],
      gPcieBspCtx->port_phy_register_seq[index].reg_offset,
	  gPcieBspCtx->port_phy_register_seq[index].reg_val,
      index);

    /*POLL status */
    index++;

    POLL_UNTIL (
      gPcieBspCtx->reg_base_address[gPcieBspCtx->port_phy_register_seq[index].base][CurrentNode->rootPortIdx] +
      gPcieBspCtx->port_phy_register_seq[index].reg_offset,
      gPcieBspCtx->port_phy_register_seq[index].reg_val,
      FALSE,
      100,
      isTimeout
    );

    if(isTimeout) {
  	  return EFI_LOAD_ERROR;
    }

    CurrentNode = CurrentNode->Next;
  }

  return EFI_SUCCESS;
}

/**
 * Initialize Link training
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_InitialzeLink(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                isTimeout;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitialzeLink: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitialzeLink: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    isTimeout = 0;
    /*Link Training*/
    MmioWrite32(HWIO_ADDRI(PCIE20_PARF_LTSSM, CurrentNode->ParfBaseAddress), HWIO_PCIE20_PARF_LTSSM_LTSSM_EN_BMSK);

    /* Poll for PCIe Link up*/
    POLL_UNTIL(
            HWIO_ADDRI(PCIE20_ELBI_SYS_STTS, CurrentNode->ElbiBaseAddress),
            HWIO_PCIE20_ELBI_SYS_STTS_XMLH_LINK_UP_BMSK,
            TRUE,
            1000,
            isTimeout);

    if(isTimeout) {
      CurrentNode->EndpointPresent = FALSE;
    }else {
      CurrentNode->EndpointPresent = TRUE;
    }
    CurrentNode = CurrentNode->Next;
  }
  return EFI_SUCCESS;
}

/**
 * Change clock source to PHY PIPE Clock
 *
 * @param void
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_ChangeClockSource(PRootPort_Config_Data *Head)
{
  UINTN  ClockId;
  EFI_CLOCK_PROTOCOL     *pClockProtocol;
  PRootPort_Config_Data  CurrentNode;
  EFI_STATUS Status;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ChangeClockSource: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ChangeClockSource: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&pClockProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG(( EFI_D_WARN, "PCIe_ChangeClockSource: Clock Locate Protocol failed\r\n"));
    return Status;
  }

  do
  {
    Status = pClockProtocol->GetClockID(pClockProtocol, gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_phy_clk], &ClockId);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_ChangeClockSource: GetClockID %s failed\r\n",
        gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_phy_clk]));
      return Status;
    }
    //Try exact frequency match
    Status = pClockProtocol->SelectExternalSource(pClockProtocol,
                                              ClockId,
                                              PCIE_PIPE_CLK_FREQUENCY,
                                              PCIE_PIPE_CLK_SOURCE,
                                              PCIE_PIPE_CLK_DIV,
                                              0,
                                              0,
                                              0);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_ChangeClockSource: SelectExternalSource %s failed\r\n",
        gPcieBspCtx->port_clk_name_list[CurrentNode->rootPortIdx][gcc_pcie_phy_clk]));
      return Status;
    }
    CurrentNode = CurrentNode->Next;
  }while (CurrentNode);

  return Status;
}

/**
 * Configure TLMM GPIO
 *
 * @param const gpioPinConfig_t *
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_ConfigTLMMGPIO(CONST gpioPinConfig_t * pTLMMConfigData)
{
  EFI_TLMM_PROTOCOL       *TLMMProtocol     = NULL;
  EFI_STATUS              Status;

  Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (VOID **)&TLMMProtocol);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ConfigTLMMGPIO: TLMM Locate Protocol failed\r\n"));
    return Status;
  }

  Status = TLMMProtocol->ConfigGpio(
                EFI_GPIO_CFG(
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.GpioNum,
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Func,
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Direction,
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Pull,
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.DriveStrength),
                TLMM_GPIO_ENABLE);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ConfigTLMMGPIO: ConfigGpio failed\r\n"));
    return Status;
  }

  if (pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Direction == GPIO_OUTPUT)
  {
    Status = TLMMProtocol->GpioOut(
                  EFI_GPIO_CFG(
                    pTLMMConfigData->GpioConfigParam.TlmmGpioParam.GpioNum,
                    pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Func,
                    pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Direction,
                    pTLMMConfigData->GpioConfigParam.TlmmGpioParam.Pull,
                    pTLMMConfigData->GpioConfigParam.TlmmGpioParam.DriveStrength),
                  pTLMMConfigData->GpioConfigParam.TlmmGpioParam.value);
    if EFI_ERROR (Status)
    {
      DEBUG(( EFI_D_WARN, "PCIe_ConfigTLMMGPIO: GpioOut failed\r\n"));
      return Status;
    }
  }

  return Status;
}

/**
 * Configure PMIC GPIO
 *
 * @param const gpioPinConfig_t *
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_ConfigPMICGPIO(CONST gpioPinConfig_t * pPMICConfigData)
{
  EFI_QCOM_PMIC_GPIO_PROTOCOL   *PmicGpioProtocol = NULL;
  EFI_STATUS                    Status;

  Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid, NULL, (VOID **)&PmicGpioProtocol);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ConfigPMICGPIO: PMIC Locate Protocol failed\r\n"));
    return Status;
  }
  Status = PmicGpioProtocol->ConfigDigitalOutput(
                pPMICConfigData->GpioConfigParam.PmicGpioParam.PmicIndex,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.GpioNum,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.OutBuffConfig ,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.VSrc,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.Source,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.BufferStrength,
                pPMICConfigData->GpioConfigParam.PmicGpioParam.inversion);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_ConfigPMICGPIO: ConfigDigitalOutput failed\r\n"));
    return Status;
  }

  return Status;
}

/**
 * Configure GPIOs based on its type
 *
 * @param const gpioPinConfig_t *
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_ConfigureGPIOs(CONST gpioPinConfig_t * pGPIOConfigData)
{
  EFI_STATUS  Status = EFI_SUCCESS;

  switch (pGPIOConfigData->type)
  {
  case MSM_GPIO:
    Status = PCIe_ConfigTLMMGPIO(pGPIOConfigData);
    break;
  case PMIC_GPIO:
    Status = PCIe_ConfigPMICGPIO(pGPIOConfigData);
    break;
  case DELAY:
    gBS->Stall(pGPIOConfigData->GpioConfigParam.DelayValue);
    break;
  case NONE:
  case PMIC_MPP:
  default:
    break;
  }

  return Status;
}

/**
 * Configure GPIO need for platform
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_InitAdditionalGPIO(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                index = 0;
  EFI_STATUS            Status = EFI_SUCCESS;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitAdditionalGPIO: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;

  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitAdditionalGPIO: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while(CurrentNode)
  {
    index = 0;
    while(gPcieBspCtx->perst_gpio_config[CurrentNode->rootPortIdx][index].type != NONE)
    {
	  Status = PCIe_ConfigureGPIOs(&gPcieBspCtx->perst_gpio_config[CurrentNode->rootPortIdx][index]);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_InitAdditionalGPIO: PCIe_ConfigureGPIOs failed\r\n"));
        return Status;
      }
      index++;
    }
    CurrentNode = CurrentNode->Next;
  }

  return Status;
}

/*
 * Sets up Miscellaneous configuration space registers
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 * EFI_INVALID_PARAMETER : NULL Head address
 * EFI_SUCCESS : RC MISC config registers Initialized
 */
EFI_STATUS PCIe_SetupMiscConfig(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                TempReg;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupMiscConfig: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupMiscConfig: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    if( CurrentNode->EndpointPresent)
    {
	  /* SMMU By-Pass Mode En/Dis */
	  if( CurrentNode->SmmuByPassMode )
	  {
	    TempReg = MmioRead32(HWIO_ADDRI(PCIE20_PARF_MHI_CLOCK_RESET_CTRL, CurrentNode->ParfBaseAddress));
	    TempReg = TempReg | (HWIO_PCIE20_PARF_MHI_CLOCK_RESET_CTRL_BYPASS_BMSK);
	    MmioWrite32(HWIO_ADDRI(PCIE20_PARF_MHI_CLOCK_RESET_CTRL, CurrentNode->ParfBaseAddress), TempReg);
	  }

	  TempReg = MmioRead32 (HWIO_ADDRI(TYPE1_STATUS_COMMAND_REG, CurrentNode->ConfigBaseAddress));
	  /* Memory Enable Compliance */
	  TempReg = TempReg | HWIO_TYPE1_STATUS_COMMAND_REG_MSE_BMSK;
	  MmioWrite32 (HWIO_ADDRI(TYPE1_STATUS_COMMAND_REG, CurrentNode->ConfigBaseAddress), TempReg);

	  /* Enable DBI_RO_WR_EN to access CS1 region */
	  MmioWrite32 (HWIO_ADDRI(MISC_CONTROL_1_REG, CurrentNode->ConfigBaseAddress),
	    HWIO_MISC_CONTROL_1_REG_DBI_RO_WR_EN_BMSK);
	  MemoryFence();

	  TempReg = MmioRead32 (HWIO_ADDRI(LINK_CAPABILITIES_REG, CurrentNode->ConfigBaseAddress));
	  /* Optionality Compliance */
	  TempReg = TempReg | HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE_BMSK;
	  /* clear AS_LINK_PM_SUPT */
	  TempReg = TempReg & (~(UINT32)(HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_BMSK));
	  /* Disable L0s & Enable L1 */
	  TempReg = TempReg | (ASPM_L0s_DS_L1_EN << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_SHFT);
	  /* Clear Max Link speed BMSK */
	  TempReg = TempReg & (~(UINT32)(HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED_BMSK));
	  /* Program Max Link speed BMSK */
	  TempReg = TempReg | (CX_GEN2_MODE << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED_SHFT);
	  MmioWrite32 (HWIO_ADDRI(LINK_CAPABILITIES_REG, CurrentNode->ConfigBaseAddress), TempReg);

	  /* Update Base class and Sub class */
	  TempReg = MmioRead32 (HWIO_ADDRI(TYPE1_CLASS_CODE_REV_ID_REG, CurrentNode->ConfigBaseAddress)) ;
	  TempReg = TempReg & (~(UINT32)(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_BMSK));
	  TempReg = TempReg | (PCIE_CLASS_CODE_BRIDGE_DEVICE << HWIO_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_SHFT);
	  TempReg = TempReg & (~(UINT32)(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_BMSK));
	  TempReg = TempReg | (PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE << HWIO_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_SHFT);
	  MmioWrite32 (HWIO_ADDRI(TYPE1_CLASS_CODE_REV_ID_REG, CurrentNode->ConfigBaseAddress), TempReg);

	  /* Disable DBI_RO_WR_EN bit to access CS1 region */
	  MmioWrite32 (HWIO_ADDRI(MISC_CONTROL_1_REG, CurrentNode->ConfigBaseAddress),
	    !(HWIO_MISC_CONTROL_1_REG_DBI_RO_WR_EN_BMSK));
	  MemoryFence();
    }
    CurrentNode = CurrentNode->Next;
  }

  return EFI_SUCCESS;
}

/*
 * Sets up ATUs for config space access of endpoints.
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 * EFI_INVALID_PARAMETER : NULL Head address
 * EFI_SUCCESS : iATU Initialized
 */
EFI_STATUS PCIe_SetupiATU(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                EndPointConfigAddress, Bus = 0, BnrRegValue = 0;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupiATU: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupiATU: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    if (CurrentNode->EndpointPresent)
    {
      /* Select 1st region index */
      MmioWrite32(HWIO_ADDRI(IATU_VIEWPORT_REG, CurrentNode->ConfigBaseAddress),
        1);
      MmioWrite32(HWIO_ADDRI(PL_IATU_REGION_CTRL_REG_1_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        PLR_IATU_CTRL1_TYPE_CFG);
      MmioWrite32(HWIO_ADDRI(PL_IATU_REGION_CTRL_REG_2_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        HWIO_PL_IATU_REGION_CTRL_REG_2_OUTBOUND_0_REGION_EN_BMSK);
      /* currently assume we have 1 device on bus 1 should */
      EndPointConfigAddress = CurrentNode->ConfigBaseAddress + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE;
      MmioWrite32(HWIO_ADDRI(PL_IATU_LWR_BASE_ADDR_REG_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        EndPointConfigAddress);
      MmioWrite32(HWIO_ADDRI(PL_IATU_UPPER_BASE_ADDR_REG_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        0);
      MmioWrite32(HWIO_ADDRI(PL_IATU_LIMIT_ADDR_REG_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        EndPointConfigAddress);
      /*
       * Init region for access to first device's configuration register space.
       * Target address for config space: Bus[31:24] Device[23:19] Function[18:16]
       */
      MmioWrite32(HWIO_ADDRI(PL_IATU_LWR_TARGET_ADDR_REG_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        ((Bus + 1) << 24));
      MmioWrite32(HWIO_ADDRI(PL_IATU_UPPER_TARGET_ADDR_REG_OUTBOUND_0, CurrentNode->ConfigBaseAddress),
        0);
      /*
       * 0:7-> Primary Bus Number | 8:15 -> Secondary Bus Number | 16:23 ->  Subordinate Bus Number
       * Assuming only one device present under each bus
       *
       * Always write '0' as primary and '1' as secondary and subordinate bus numbers, since
       * these root ports are going to be in different segments in HLOS
       */
      BnrRegValue = ( ((UINT8)Bus) << HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_PRIM_BUS_SHFT ) |
    		        (((UINT8)(Bus + 1)) << HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SEC_BUS_SHFT) |
    		        (((UINT8)(Bus + 1)) << HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SUB_BUS_SHFT);
      MmioWrite32(HWIO_ADDRI(SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG, CurrentNode->ConfigBaseAddress),
        BnrRegValue);
      /* Writing Slave address space size */
      MmioWrite32(HWIO_ADDRI(PCIE20_PARF_SLV_ADDR_SPACE_SIZE, CurrentNode->ParfBaseAddress),
        CurrentNode->AxiAddrSpaceSize);
    }

    CurrentNode = CurrentNode->Next;
  }

  return EFI_SUCCESS;
}

/*
 * Sets up ECAM blocker for the RP
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 * EFI_INVALID_PARAMETER : NULL Head address
 * EFI_SUCCESS : ECAM blocker configured
 */
EFI_STATUS PCIe_SetupECAM(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                Temp;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupECAM: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupECAM: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  while (CurrentNode)
  {
    if( CurrentNode->EndpointPresent)
    {
      if(CurrentNode->EcamBlockerEn == FALSE)
      {
        /* Disable PCIE20_PARF_PCIE20_PARF_SYS_CTRL:Bit:27 ECAM_REMOVE_OFFSET_EN  & Bit:26 ECAM_BLOCKER_EN*/
        Temp = MmioRead32(HWIO_ADDRI(PCIE20_PARF_SYS_CTRL, CurrentNode->ParfBaseAddress));
        Temp = Temp & ~(HWIO_PCIE20_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK);
        Temp = Temp & ~(HWIO_PCIE20_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_BMSK);
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_SYS_CTRL, CurrentNode->ParfBaseAddress), Temp);
      }
      else
      {
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_ECAM_BASE, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress);

        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_BLOCK_SLV_AXI_WR_BASE, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + PCIE_CONFIG_SPACE_LENGTH);
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_BLOCK_SLV_AXI_WR_LIMIT, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + (PCIE_SINGLE_BUS_ADDR_SPACE_SIZE -1));
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_BLOCK_SLV_AXI_RD_BASE, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + PCIE_CONFIG_SPACE_LENGTH);
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_BLOCK_SLV_AXI_RD_LIMIT, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + (PCIE_SINGLE_BUS_ADDR_SPACE_SIZE -1));
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_ECAM_OFFSET_REMOVAL_BASE, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + PCIE_CONFIG_SPACE_LENGTH);
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_ECAM_OFFSET_REMOVAL_LIMIT, CurrentNode->ParfBaseAddress),
          CurrentNode->ConfigBaseAddress + (PCIE_SINGLE_BUS_ADDR_SPACE_SIZE -1));

        /* Enable PCIE_1_PCIE20_PARF_PCIE20_PARF_SYS_CTRL:Bit:27 ECAM_REMOVE_OFFSET_EN  & Bit:26 ECAM_BLOCKER_EN*/
        Temp = MmioRead32(HWIO_ADDRI(PCIE20_PARF_SYS_CTRL, CurrentNode->ParfBaseAddress));
        Temp = Temp | (HWIO_PCIE20_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK);
        Temp = Temp | (HWIO_PCIE20_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_BMSK);
        MmioWrite32(HWIO_ADDRI(PCIE20_PARF_SYS_CTRL, CurrentNode->ParfBaseAddress), Temp);
      }
    }
    CurrentNode = CurrentNode->Next;
  }

  return EFI_SUCCESS;
}

/**
 * Initialize the config space by setting up the base address,
 * setup the ATU's and check if the EP is connected
 *
 * @param Head,Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_InitializeConfigSpace(PRootPort_Config_Data *Head)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializeConfigSpace: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = PCIe_SetupMiscConfig(Head);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializeConfigSpace: PCIe_SetupMiscConfig failed\r\n"));
    return Status;
  }

  Status = PCIe_SetupiATU(Head);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializeConfigSpace: PCIe_SetupiATU failed\r\n"));
    return Status;
  }

  Status = PCIe_SetupECAM(Head);
  if EFI_ERROR (Status)
  {
    DEBUG(( EFI_D_WARN, "PCIe_InitializeConfigSpace: PCIe_SetupECAM failed\r\n"));
    return Status;
  }

  return Status;
}


/**
 * Will query all the BARs and figure out the total Prefetch and
 * Non-Prefetch memory requirement.
 *
 * @param Prefetch_Memory, Pointer to Total Prefetch memory
 * @param NonPrefetch_Memory,Pointer to Total NonPrefetch memory
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS PCIe_GetBAR(PRootPort_Config_Data *Head, UINT32 *Prefetch_Memory, UINT32 *NonPrefetch_Memory)
{
  UINT32                BAR, Temp;
  volatile UINT32       BARvalueL, BARvalueU;
  PRootPort_Config_Data CurrentNode;
  UINTN                 EndPointConfigAddress = 0;
  UINT32                * MemLength = NULL;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_GetBAR: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;

  /* End point is one bus away from the root port */
  EndPointConfigAddress = CurrentNode->ConfigBaseAddress + PCIE_SINGLE_BUS_ADDR_SPACE_SIZE;

  BAR = HWIO_TYPE0_BAR0_REG_1_OFFS;
  do
  {
    MmioWrite32 (EndPointConfigAddress + BAR, HWIO_TYPE0_BAR0_REG_1_RMSK);
    BARvalueL = MmioRead32 (EndPointConfigAddress + BAR);

    if(!BARvalueL)
    {      
      goto BARAssignLoopEnd;
    }

    if (BARvalueL & HWIO_TYPE0_BAR0_REG_1_BAR0_MEM_IO_BMSK)
    {
      goto BARAssignLoopEnd; /* NO IO Supported*/
    }
    else if (BARvalueL & HWIO_TYPE0_BAR0_REG_1_BAR0_PREFETCH_BMSK)
    {
      MemLength = Prefetch_Memory;
    }
    else if ( ~(BARvalueL & HWIO_TYPE0_BAR0_REG_1_BAR0_PREFETCH_BMSK) )
    {
      MemLength = NonPrefetch_Memory;
    }

    /* 64-bit BAR */
    Temp = (BARvalueL & HWIO_TYPE0_BAR0_REG_1_BAR0_TYPE_BMSK) >> HWIO_TYPE0_BAR0_REG_1_BAR0_TYPE_SHFT;
    if( Temp == TYPE0_BAR_TYPE_64BIT )
    {
      BAR = BAR + 4 ;
      MmioWrite32 (EndPointConfigAddress + BAR, HWIO_TYPE0_BAR0_REG_1_RMSK);
      BARvalueU = MmioRead32 (EndPointConfigAddress + BAR);

      if(BARvalueU != HWIO_TYPE0_BAR0_REG_1_RMSK)
      {
        /* BAR size is more than 4GB (Not Supported) */
        goto BARAssignLoopEnd;
      }
    }

  *MemLength = *MemLength + ( ~(BARvalueL & HWIO_TYPE0_BAR0_REG_1_BAR0_START_BMSK) ) + 1;
  
BARAssignLoopEnd:
    BAR = BAR + 4;
  }while(BAR <= HWIO_TYPE0_BAR5_REG_1_OFFS);

  return EFI_SUCCESS;
}

/**
 * It will setup the window i.e the base and limit for Prefectch
 * and Non-Prefetch Memory
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
STATIC VOID PCIe_SetupWindow(PRootPort_Config_Data *Head, UINT32  Prefetch_Memory, UINT32  NonPrefetch_Memory)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                Non_Prefetch_Base = 0, Non_Prefetch_Limit = 0;
  UINT32                Prefetch_Limit, Prefetch_Base;
  UINT32                Temp;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_SetupWindow: Head is NULL\r\n"));
    return;
  }
  CurrentNode = *Head;

  /* we need to start at base address + 1MB (BDF 100) + 1MB (Config space)
   * Don't know why we offset by 4MB? May be because of some resourece issue?
   */
  Non_Prefetch_Base = CurrentNode->ConfigBaseAddress + PCIE_MEM_BASE_OFFS;
  Non_Prefetch_Limit = Non_Prefetch_Base + NonPrefetch_Memory;
  if (NonPrefetch_Memory == 0)
  {
    /* Setting MEM Base greater than limit to ignore this req. */
    Temp = (0x00000000) | (0xFFFF) ;
  }
  else
  {
    Temp = (Non_Prefetch_Limit & HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_BMSK) | (Non_Prefetch_Base >> HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_RESERV_SHFT) ;
  }
  MmioWrite32(HWIO_ADDRI(MEM_LIMIT_MEM_BASE_REG, CurrentNode->ConfigBaseAddress), Temp);

  Prefetch_Base = Non_Prefetch_Limit;
  Prefetch_Limit = Prefetch_Base + Prefetch_Memory;
  if (Prefetch_Memory == 0)
  {
    /* Setting MEM Base greater than limit to ignore this req. */
    Temp = (0x00000000) | (0xFFFF) ;
  }
  else
  {
    Temp = (Prefetch_Limit & HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_BMSK) | (Prefetch_Base >> HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_RESERV_SHFT) ;
  }
  MmioWrite32(HWIO_ADDRI(PREF_MEM_LIMIT_PREF_MEM_BASE_REG, CurrentNode->ConfigBaseAddress), Temp);
}

/**
 * Figure out the the total memory requirement for Prefetch and
 * Non Prefetch Memory and setup the window registers
 *
 * @param Head, Address of first Node in Linked List
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_GetBarMemoryRequirement(PRootPort_Config_Data *Head)
{

  PRootPort_Config_Data CurrentNode;
  UINT32                Prefetch_Memory, NonPrefetch_Memory;
  EFI_STATUS            Status;

  if (Head == NULL)
  {
    DEBUG(( EFI_D_WARN, "PCIe_GetBarMemoryRequirement: Head is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;
  if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
  {
    DEBUG(( EFI_D_WARN, "PCIe_GetBarMemoryRequirement: rootPortIdx out of range\r\n"));
    return EFI_INVALID_PARAMETER;
  }
   
  while (CurrentNode)
  {
    if (CurrentNode->EndpointPresent)
    {
      Prefetch_Memory = 0;
      NonPrefetch_Memory = 0;
      Status = PCIe_GetBAR(&CurrentNode, &Prefetch_Memory, &NonPrefetch_Memory);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_GetBarMemoryRequirement: PCIe_GetBAR failed\r\n"));
        return Status;
      }

      if ( (Prefetch_Memory + NonPrefetch_Memory) <= CurrentNode->AxiAddrSpaceSize)
      {
        PCIe_SetupWindow(&CurrentNode, Prefetch_Memory, NonPrefetch_Memory);
      }
      else
      {
        DEBUG(( EFI_D_WARN, "WARN!! PCIe_GetBarMemoryRequirement: PCIe MEM base and limit are not configured\r\n"));
      }
    }
    CurrentNode = CurrentNode->Next;
  }
  return EFI_SUCCESS;
}

/**
 * Find the capability pointer offset for the specified
 * capability by walking through the capability list.
 *
 * @param CapID (input)     , 16-bit PCIe extended capability ID
 * @param RegBase (input)   , configuration register base of the device
 * @param CapOffset (output), offset found based on CapID
 *
 * @return EFI_STATUS
 */
STATIC EFI_STATUS LocatePciExpressCapabilityRegBlock (IN UINT16 CapID,
                                                      IN UINTN RegBase,
                                                      OUT UINT16 * CapOffset)
{
  UINT16 CapabilityPtr;
  UINT32 CapabilityEntry;
  UINT16 CapabilityID;

  CapabilityPtr = EFI_PCIE_CAPABILITY_BASE_OFFSET;

  if(CapOffset == NULL)
  {
    DEBUG(( EFI_D_WARN, "LocatePciExpressCapabilityRegBlock: CapOffset is NULL\r\n"));
    return EFI_INVALID_PARAMETER;
  }

  do
  {
    /*
     * Mask it to DWORD alignment as per PCI spec
     */
    CapabilityPtr &= 0xFFC;
    CapabilityEntry = MmioRead32 (RegBase + CapabilityPtr);
    if (CapabilityEntry == 0xFFFF)
    {
      DEBUG(( EFI_D_WARN, "LocatePciExpressCapabilityRegBlock: Cap Reg not accessible\r\n"));
      return EFI_NOT_FOUND;
    }
    CapabilityID = (UINT16) CapabilityEntry;

    if (CapabilityID == CapID)
    {
      *CapOffset = CapabilityPtr;
      return EFI_SUCCESS;
    }

    CapabilityPtr = (CapabilityEntry & HWIO_L1SUB_CAP_HEADER_REG_NEXT_OFFSET_BMSK)
                                     >> HWIO_L1SUB_CAP_HEADER_REG_NEXT_OFFSET_SHFT;
  }while(CapabilityPtr != 0);

  return EFI_NOT_FOUND;
}

/**
 * It will enable L1ss on the root port and endpoint as well
 *
 * @param Prefetch_Memory
 * @param NonPrefetch_Memory
 * @param Head
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_Setup_L1ss(PRootPort_Config_Data *Head)
{
  PRootPort_Config_Data CurrentNode;
  UINT32                TempReg;
  UINT16                L1SubCtrlBase = 0;
  UINTN                 EndPointConfigAddr;
  EFI_STATUS            Status = EFI_SUCCESS;

  if (Head == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  CurrentNode = *Head;

  while (CurrentNode)
  {
    if(CurrentNode->EndpointPresent)
    {
      if (CurrentNode->rootPortIdx >= gPcieBspCtx->max_rp)
      {
        DEBUG(( EFI_D_WARN, "PCIe_Setup_L1ss: rootPortIdx out of range\r\n"));
        return EFI_INVALID_PARAMETER;
      }

      Status = LocatePciExpressCapabilityRegBlock(EFI_PCIE_L1SS_PM_CAP_ID,
                                                  CurrentNode->ConfigBaseAddress,
                                                  &L1SubCtrlBase);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_Setup_L1ss: CapOffset not found for %d root complex\r\n",
                CurrentNode->rootPortIdx));
        Status = EFI_SUCCESS;
        goto L1ssSetupWhileLoopEnd;
      }

      TempReg = MmioRead32(CurrentNode->ConfigBaseAddress + L1SubCtrlBase + control1_reg_offset);
      /* L1_2_PCIPM_EN | L1_1_PCIPM_EN | L1_2_ASPM_EN | L1_1_ASPM_EN */
      TempReg |= 0x0000000F;
      MmioWrite32(CurrentNode->ConfigBaseAddress + L1SubCtrlBase + control1_reg_offset, TempReg);

      TempReg = MmioRead32(HWIO_ADDRI(TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1,
                                      CurrentNode->ConfigBaseAddress));
      /* PCIE_1_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1.PCIE_CAP_LTR_EN Enable */
      TempReg |=  HWIO_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1_PCIE_CAP_LTR_EN_BMSK;
      MmioWrite32(HWIO_ADDRI(TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1,
                             CurrentNode->ConfigBaseAddress), TempReg);

      /* Get the endpoint base address from the iATU viewport registers */
      MmioWrite32(HWIO_ADDRI(IATU_VIEWPORT_REG, CurrentNode->ConfigBaseAddress), 1);
      EndPointConfigAddr = MmioRead32(HWIO_ADDRI(PL_IATU_LWR_BASE_ADDR_REG_OUTBOUND_0,
                                                 CurrentNode->ConfigBaseAddress));

      Status = LocatePciExpressCapabilityRegBlock(EFI_PCIE_L1SS_PM_CAP_ID,
                                                  EndPointConfigAddr,
                                                  &L1SubCtrlBase);
      if EFI_ERROR (Status)
      {
        DEBUG(( EFI_D_WARN, "PCIe_Setup_L1ss: CapOffset not found for EP of %d root complex\r\n",
                CurrentNode->rootPortIdx));
        Status = EFI_SUCCESS;
        goto L1ssSetupWhileLoopEnd;
      }

      TempReg = MmioRead32(EndPointConfigAddr + L1SubCtrlBase + control1_reg_offset);
      /* L1_2_PCIPM_EN | L1_1_PCIPM_EN | L1_2_ASPM_EN | L1_1_ASPM_EN */
      TempReg |= 0x0000000F;
      MmioWrite32(EndPointConfigAddr + L1SubCtrlBase + control1_reg_offset, TempReg);

      TempReg = MmioRead32(HWIO_ADDRI(TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1, EndPointConfigAddr));
      /* PCIE_1_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1.PCIE_CAP_LTR_EN Enable */
      TempReg |=  HWIO_TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1_PCIE_CAP_LTR_EN_BMSK;
      MmioWrite32(HWIO_ADDRI(TYPE0_DEVICE_CONTROL2_DEVICE_STATUS2_REG_1, EndPointConfigAddr), TempReg);

      /* CLKREQ GPIO ENABLE */
      Status = PCIe_ConfigureGPIOs(&gPcieBspCtx->clk_req_gpio_config[CurrentNode->rootPortIdx]);
      if EFI_ERROR (Status)
      {
        return Status;
      }
    }

L1ssSetupWhileLoopEnd:
    CurrentNode = CurrentNode->Next;
  }

  return Status;
}
