/*
===========================================================================

  @file PcieBsp.h

  Copyright (c) 2015-2016, Qualcomm Technologies, Inc. All Rights Reserved.
===========================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 01/28/16  tselvam  File renamed to pcieBsp.h from PcieConfigData.h
                    Part of this moved all the data to xml file and
                    kept only the declerations of all data types
 01/26/16  tselvam  Fixed the copyright header
 01/25/16  tselvam  Suppress support for 11.ad
 01/08/16  tselvam  Included support for 11.ad and pcie1 port
 10/12/15  tselvam  KW review #5917: Array 'pcie20_wrapper_axi_bases' of size
                    3 may use index value(s) 3..7 at PCIe_ReadConfigData
 09/17/15  tselvam  Incorporated V3/V4 specific PHY changes and made changes to
                    version dependent PHY settings, so that it can be
                    extensible in future platforms
 08/20/15  tselvam  Changed the GPIO function for CLK REQ
 08/07/15  tselvam  Updated with new PHY seq for V3.0 h/w
 07/22/15  tselvam  New PHY sequence based on QMP PCIe 3-port PHY 14LPP
                    Version 5.0.
 06/15/15  tselvam  Removed unwanted macros and unified data structs and also
                    updated PHY sequence for V2 and V3 hardware.
                    Renamed the file to PcieConfigData.h from PcieHwioRegDef.h
 05/15/15  tselvam  First checkin as part of Unified code for multi platforms
 
===========================================================================
*/

#ifndef __PCIEBSP_H__
#define __PCIEBSP_H__

#include <Uefi.h>
#include "PcieHwioRegs.h"
#include <HALhwio.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFITlmm.h>
#include <Library/DebugLib.h>
#include "msmhwiobase.h"

/*
 * Register setting special meaning macros
 */
#define PCIE_INVALID_REG_BASE                            (0xFFFFFFFFUL)
#define PHY_REG_DELAY_VAL                                (0xDEDEDEDE)
#define PHY_REG_NOP                                      (0xFFFFFFFF)

/*----------------------------------------------------------------------------
 * Enum Definitions
 * -------------------------------------------------------------------------*/

typedef enum pin_config_type
{
  NONE = 0,
  MSM_GPIO,
  PMIC_GPIO,
  PMIC_MPP,
  DELAY
} pin_config_type;

typedef enum {
  invalid_reg_base = 0,
  dbi_reg_base,
  elbi_reg_base,
  parf_reg_base,
  port_reg_base,
  rx_reg_base,
  tx_reg_base,
  phy_reg_base
}reg_base_index;

enum pcie_phy_clk_name_index
{
  gcc_pcie_phy_cfg_ahb_clk = 0,
  gcc_pcie_phy_aux_clk,
  gcc_max_pcie_phy_clk
};

enum pcie_clk_name_index
{
  gcc_pcie_phy_clk = 0,
  gcc_pcie_aux_clk,
  gcc_pcie_slv_axi_clk,
  gcc_pcie_mstr_axi_clk,
  gcc_pcie_cfg_ahb_clk,
  gcc_max_pcie_clk
};

typedef struct
{
  /* Base addresses for the registers to be configured */
  reg_base_index base;
  /* Offset for the registers to be configured */
  UINT32         reg_offset;
  /* Values for the register listed above */
  UINT32         reg_val;
} pciePhyRegSeq_t;

typedef struct
{
  UINT32 GpioNum;
  UINT32 Func;
  UINT32 Direction;
  UINT32 Pull;
  UINT32 DriveStrength;
  TLMM_ValueType value;
}tlmmGpioParam_t;

typedef struct
{
  UINT32 PmicIndex;
  EFI_PM_GPIO_WHICH_TYPE GpioNum;
  EFI_PM_GPIO_OUT_BUFFER_CONFIG_TYPE OutBuffConfig;
  EFI_PM_GPIO_VOLTAGE_SOURCE_TYPE VSrc;
  EFI_PM_GPIO_SOURCE_CONFIG_TYPE Source;
  EFI_PM_GPIO_OUT_BUFFER_DRIVE_STRENGTH_TYPE BufferStrength;
  BOOLEAN inversion;
}pmicGpioParam_t;

typedef union
{
  tlmmGpioParam_t TlmmGpioParam;
  pmicGpioParam_t PmicGpioParam;
  UINTN DelayValue;
}gpioConfigParam_t;

typedef struct
{
  pin_config_type type;
  gpioConfigParam_t GpioConfigParam;
}gpioPinConfig_t;

typedef struct
{
  CONST UINT32                       RPMask;
  CONST UINT32                       max_rp;
  CONST UINTN **                     reg_base_address;
  CONST UINTN *                      axi_addr_space_size;
  CONST char **                      phy_clk_name_list;
  CONST char ***                     port_clk_name_list;
  CONST char **                      clk_pwr_dmn_name_list;
  CONST pciePhyRegSeq_t *            phy_register_seq;
  CONST pciePhyRegSeq_t *            port_phy_register_seq;
  CONST gpioPinConfig_t *            clk_req_gpio_config;
  CONST gpioPinConfig_t **           perst_gpio_config;
}pcieBsp_t;

#endif /* __PCIECONFIGDATA_H__ */
