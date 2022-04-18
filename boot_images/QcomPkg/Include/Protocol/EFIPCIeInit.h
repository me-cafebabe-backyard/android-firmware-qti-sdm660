/** @file EFIPCIeInit.h

  EFI protocols declerations

  Copyright (c) 2012-2015, Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/13/16   tselvam Added revision field to the protocol struct to comply
 06/08/16   tselvam Included support to dump config space for all RPs in
                    pcietest appilcation.
 01/26/15   tselvam Initial checkin for 8996
 06/16/14   hk      created

=============================================================================*/
#ifndef __EFIPCIEINIT_H__
#define __EFIPCIEINIT_H__

extern EFI_GUID gQcomPcieInitProtocolGuid;

typedef struct _QCOM_PCIE_PROTOCOL QCOM_PCIE_PROTOCOL;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
typedef
EFI_STATUS (EFIAPI * EFI_PCIE_INIT)(IN QCOM_PCIE_PROTOCOL *This);
typedef
UINT32 (EFIAPI * EFI_PCI_RP_READ_CONFIG_32)(IN UINT32 rpIndex, IN UINT32 offset);
typedef
EFI_STATUS (EFIAPI * EFI_PCIE_DEINIT)(void);
typedef
UINT32 (EFIAPI * EFI_PCI_READ_RPMASK_VAL)(IN QCOM_PCIE_PROTOCOL *This);


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/

struct _QCOM_PCIE_PROTOCOL {
  UINT64                    Revision;
  EFI_PCIE_INIT             PCIeInitHardware;
  EFI_PCI_RP_READ_CONFIG_32 PCIe_Config_Read_32;
  EFI_PCIE_DEINIT           PCIeDeInitHardware;
  EFI_PCI_READ_RPMASK_VAL   PCIeReadRPMaskVal;
};

#endif  /* __EFIPCIEINIT_H__ */
