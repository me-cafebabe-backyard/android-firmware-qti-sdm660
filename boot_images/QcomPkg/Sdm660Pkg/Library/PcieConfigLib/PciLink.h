#ifndef __PCIELINK_H__
#define __PCIELINK_H__
/** @file

  PCIe init function Header file.

  Copyright (c) 2014-2016, Qualcomm Technologies Inc. All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 02/08/16   tselvam  Added pcie xml config support
 06/15/15   tselvam  removed PCIe_ReadNumberofRP, since it is a static now.
                     Included support for pcie capability walk.
 05/13/15   tselvam  Unified code for multi platforms
 03/18/15   tselvam  Fixed Copyrights header
 03/16/15   tselvam  Included GCC BCR register variable
 06/16/14   hozefak  Add PcieInit protocol
 04/18/14   hozefak  First checkin for 8084
=============================================================================*/


#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

/* Macro Definitions */
#define TYPE0_BAR_TYPE_64BIT                             (0x00000002)
#define NUM_OF_RP_MASK                                   (0x00FF)
#define RP_ENABLE_MASK                                   (0xFF00)
#define RP_MASK_LENGTH                                   (8)
#define PCIE_MAX_CLK_NAME                                (80)
#define INIT_TIMEOUT                                     (150)
#define PCIE_PIPE_CLK_FREQUENCY                          (125000000)
#define PCIE_PIPE_CLK_SOURCE                             (2)
#define PCIE_PIPE_CLK_DIV                                (2)
#define PCIE_CLASS_CODE_BRIDGE_DEVICE                    (0x06)
#define PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE              (0x04)
#define PCIE_MEM_BASE_OFFS                               (0x300000 + 0x100000)
/* Max link speed */
#define CX_GEN1_MODE                                     (0x1)
#define CX_GEN2_MODE                                     (0x2)
#define CX_GEN3_MODE                                     (0x3)
/* PCIe ASPM Capability enables */
#define ASPM_L0s_DS_L1_DS                                (0x1)
#define ASPM_L0s_EN_L1_DS                                (0x1)
#define ASPM_L0s_DS_L1_EN                                (0x2)
#define ASPM_L0s_EN_L1_EN                                (0x3)
/* PCIe controller CTRL1 register values */
#define PLR_IATU_CTRL1_TYPE_CFG                          (4)
#define PLR_IATU_CTRL1_TYPE_MEMORY                       (0)
/* Bus address space */
#define PCIE_SINGLE_BUS_ADDR_SPACE_SIZE                  (0x100000)
#define PCIE_CONFIG_SPACE_LENGTH                         (0x1000)

/*
 * PCIe TYPE0/TYPE1 extended capability begin pointer
 */
#define EFI_PCIE_CAPABILITY_BASE_OFFSET                  (0x100)
/*
 * PCIe extended capability IDs
 */
#define EFI_PCIE_AER_CAP_ID                              (0x0001)
#define EFI_PCIE_VC_1_CAP_ID                             (0x0002)
#define EFI_PCIE_DEV_SN_CAP_ID                           (0x0003)
#define EFI_PCIE_PWR_BUD_CAP_ID                          (0x0004)
#define EFI_PCIE_LINK_DEC_1_CAP_ID                       (0x0005)
#define EFI_PCIE_LINK_DEC_2_CAP_ID                       (0x0006)
#define EFI_PCIE_RC_EC_EPA_CAP_ID                        (0x0007)
#define EFI_PCIE_MFVC_CAP_ID                             (0x0008)
#define EFI_PCIE_VC_2_CAP_ID                             (0x0009)
#define EFI_PCIE_RCRB_HEADER_CAP_ID                      (0x000A)
#define EFI_PCIE_VEN_SPECI_CAP_ID                        (0x000B)
#define EFI_PCIE_ACS_EXT_CAP_ID                          (0x000D)
#define EFI_PCIE_ARI_CAP_ID                              (0x000E)
#define EFI_PCIE_MCAST_CAP_ID                            (0x0012)
#define EFI_PCIE_RESIZE_BAR_CAP_ID                       (0x0015)
#define EFI_PCIE_DPA_EXT_CAP_ID                          (0x0016)
#define EFI_PCIE_TPH_REQ_CAP_ID                          (0x0017)
#define EFI_PCIE_LT_EXT_CAP_ID                           (0x0018)
#define EFI_PCIE_SEC_PCIE_EXT_CAP_ID                     (0x0019)
#define EFI_PCIE_LNR_EXT_CAP_ID                          (0x001C)
#define EFI_PCIE_DPC_EXT_CAP_ID                          (0x001D)
#define EFI_PCIE_L1SS_PM_CAP_ID                          (0x001E)
#define EFI_PCIE_PTM_CAP_ID                              (0x001F)

/*
 * POLL_ULTIL - polls the "addr" for bit specified in
 * "mask" with an internal of "delay" for each
 * iteration until the "cond" specified for that
 * bit is met
 *
 * addr  - address to be polled
 * mask  - bit mask to be checked for
 * cond  - loop exit condition to be met
 * delay - delay in usec between each iteration
 * tout  - tout returns '1' if the loop timed out
 */
#define POLL_UNTIL(addr, mask, cond, delay, tout) \
{ \
  UINT32 CountVariable = INIT_TIMEOUT; \
  volatile UINT32 StatusBit; \
  UINT32 Shift = __builtin_ctz((mask)); \
  do \
  { \
    gBS->Stall(delay); \
    StatusBit = MmioRead32(addr); \
    StatusBit = (StatusBit & (mask)) >> Shift; \
    CountVariable--; \
  }while ( !(StatusBit == (cond)) && CountVariable); \
 \
  if(!CountVariable) \
  { \
    tout = 1; \
  } \
}

/*
 * REG_WRITE_CONDITIONAL - based on the iput offset
 * value, this macro decides what is the best action
 * to take.
 *
 * base   - base address to be written to
 * offset - offset from the base to be written to
 * value  - value to be written to
 * index  - index to be rolled over each iteration
 */
#define REG_WRITE_CONDITIONAL(base, offset, value, index) \
  while(offset != PHY_REG_NOP) \
  { \
    switch (offset) \
    { \
    case PHY_REG_DELAY_VAL: \
      gBS->Stall(value); \
    break; \
    case PHY_REG_NOP: \
    break; \
    default: \
      MmioWrite32(base + offset, value); \
    } \
    index++; \
  }


/*
 * Register offset inside capability block
 */
typedef enum
{
  cap_reg_offset = 0x04,
  control1_reg_offset = 0x08,
  control2_reg_offset = 0x0c
}CapBlockRegOffset_t;

/*
 * Data Structure Definition
 */

typedef struct ROOTPORT_DATA
{
  UINT32  rootPortIdx;
  UINTN   ConfigBaseAddress;
  UINTN   ParfBaseAddress;
  UINTN   ElbiBaseAddress;
  UINTN   AxiAddrSpaceSize;
  BOOLEAN EndpointPresent;
  BOOLEAN SmmuByPassMode;
  BOOLEAN EcamBlockerEn;
  struct  ROOTPORT_DATA *Next;
} RootPort_Config_Data, *PRootPort_Config_Data;

/*
* Initialize the config space by setting up the base address,
* setup the ATU's and check if the EP is connected
*
* @param Head,Address of first Node in Linked List
*
* @return EFI_STATUS
*/
EFI_STATUS PCIe_InitializeConfigSpace (PRootPort_Config_Data *Head) ;

/*
* Figure out the the total memory requirement for Prefetch and
* Non Prefetch Memory and setup the window registers
*
* @param Head
*
* @return EFI_STATUS
*/
EFI_STATUS PCIe_GetBarMemoryRequirement (PRootPort_Config_Data *Head);

/*
* Initialize the PHY for virtio
*
* @param Head, Address of first Node in Linked List
*
* @return EFI_STATUS
*/
EFI_STATUS PCIe_InitialzeLink (PRootPort_Config_Data *Head);

/*
* Initialize common PHY
*
* @param Head,Address of first Node in Linked List
*
* @return EFI_STATUS
* EFI_INVALID_PARAMETER : NULL Head adddress
* EF_SUCCESS : Phy Initialized
*/
EFI_STATUS PCIe_InitializePHY (VOID);

/*
* Initialize port PHY
*
* @param Head,Address of first Node in Linked List
*
* @return EFI_STATUS
* EFI_INVALID_PARAMETER : NULL Head adddress
* EF_SUCCESS : Phy Initialized
*/
EFI_STATUS PCIe_InitializePortPHY (PRootPort_Config_Data *Head);

/*
 * Read Config File and fill in linked list with data for each
 * Root port
 *
 * @param[out] StartNode, Pointer to the first Node of the
 *       linked list which contains data about all Root Ports
 *
 * @return EFI_STATUS
 */
EFI_STATUS PCIe_ReadConfigData (PRootPort_Config_Data *StartNode);

// Enable all the clocks
EFI_STATUS PCIe_EnableClocks (PRootPort_Config_Data *Head);

/*
* Enable LDOs required by ROME
*
* @param VOID
*
* @return EFI_STATUS
*/

EFI_STATUS PCIe_InitialzeLDO (VOID);

EFI_STATUS PCIe_InitAdditionalGPIO(PRootPort_Config_Data *Head);

EFI_STATUS PCIe_ChangeClockSource (PRootPort_Config_Data *Head);

EFI_STATUS PCIe_Deinitialize(VOID);

EFI_STATUS PCIe_Setup_L1ss (PRootPort_Config_Data *Head);

#endif/* #ifndef __PCIELINK_H__ */
