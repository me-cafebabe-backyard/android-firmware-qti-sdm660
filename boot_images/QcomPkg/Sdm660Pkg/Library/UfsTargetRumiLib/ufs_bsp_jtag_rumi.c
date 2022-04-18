/**********************************************************************
* ufs_bsp_boot_rumi.c
*
* Board support file for RUMI
*
* Copyright (c) 2013-2014, 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
* 
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/UfsTargetRumiLib/ufs_bsp_jtag_rumi.c#2 $
$DateTime: 2016/11/18 03:30:29 $

YYYY-MM-DD   who     what, where, why
---------------------------------------------------------------------- 
2016-11-15   sb      Add DAL config  
2014-09-17   rh      Adapted for 8996 
2014-07-16   rh      Adding cache operation
2014-06-02   rh      PHY init adjustment
2014-03-24   rh      Adapt the BSP file for 8994
2013-10-30   rh      Clock regime function cleanup
2013-10-30   rh      More accurate delay added
2013-06-19   rh      Initial creation
===========================================================================*/

#include <Uefi.h>
#include <HALhwio.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/TimerLib.h>
#include <Protocol/EFIHWIO.h>

#include <Library/PcdLib.h>
#include <Library/ArmLib.h>

#include "ufs_osal.h"
#include "ufs_bsp.h"
#include "qrbtcv2_phy_hwio.h"
#include "hwio_mpm2.h"


#define MPM2_MPM_BASE                        0x010A0000

/* Clock regime clock offset mapping */
#define HWIO_GCC_UFS_TX_SYMBOL_0_CBCR_OUT(v)       \
        out_dword(HWIO_GCC_UFS_TX_SYMBOL_0_CBCR_ADDR,v)
#define HWIO_GCC_UFS_TX_SYMBOL_1_CBCR_OUT(v)       \
        out_dword(HWIO_GCC_UFS_TX_SYMBOL_1_CBCR_ADDR,v)
#define HWIO_GCC_UFS_RX_SYMBOL_0_CBCR_OUT(v)       \
        out_dword(HWIO_GCC_UFS_RX_SYMBOL_0_CBCR_ADDR,v)
#define HWIO_GCC_UFS_RX_SYMBOL_1_CBCR_OUT(v)       \
        out_dword(HWIO_GCC_UFS_RX_SYMBOL_1_CBCR_ADDR,v)

#define HWIO_GCC_UFS_RX_CFG_CBCR_OUT(v)         \
        out_dword(HWIO_GCC_UFS_RX_CFG_CBCR_ADDR,v)
#define HWIO_GCC_UFS_TX_CFG_CBCR_OUT(v)         \
        out_dword(HWIO_GCC_UFS_TX_CFG_CBCR_ADDR,v)

#define HWIO_GCC_UFS_AXI_CMD_RCGR_OUT(v)        \
        out_dword(HWIO_GCC_UFS_AXI_CMD_RCGR_ADDR,v)
#define HWIO_GCC_UFS_AXI_CFG_RCGR_OUT(v)        \
        out_dword(HWIO_GCC_UFS_AXI_CFG_RCGR_ADDR,v)
#define HWIO_GCC_SYS_NOC_UFS_AXI_CBCR_OUT(v)        \
        out_dword(HWIO_GCC_SYS_NOC_UFS_AXI_CBCR_ADDR,v)
#define HWIO_GCC_UFS_AXI_CBCR_OUT(v)        \
        out_dword(HWIO_GCC_UFS_AXI_CBCR_ADDR,v)
#define HWIO_GCC_UFS_AHB_CBCR_OUT(v)        \
        out_dword(HWIO_GCC_UFS_AHB_CBCR_ADDR,v)


#define RCGR_DIVBYPASS                      0
#define RCGR_DIV2                           3
#define RCGR_DIV3                           5
#define RCGR_DIV4                           7

#define RCGR_MODE_BYPASS                    0
#define RCGR_MODE_DUAL_EDGE                 2
#define RCGR_MODE_SINGLE_EDGE               3

#define UFS_PHY_PCS_READY_TIMEOUT           1000
#define REQUEST_LIST_BUFFER_SIZE            4096  
//__attribute__((section(".bss.BOOT_OCIMEM_PAGE_TABLE_ZONE"))) char ALIGN(4*1024) transfer_request_list_buf[REQUEST_LIST_BUFFER_SIZE];      
char transfer_request_list_buf[REQUEST_LIST_BUFFER_SIZE];      

void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode)
{
   (void) hostid;
   if (mode == UFS_CLOCK_MODE_OFF)
   {
      // Turn everything off
      ;
   }
   else if (mode == UFS_CLOCK_MODE_ON)
   {
      ;
   }
}

void ufs_bsp_enable_symbol_clk (void)
{
   ;
}

/* A utility function to get the sleep timetick */
uint32 Clock_GetSclkTimetick()
{
  uint32_t curr_count;

  /*Grab current time count*/
  curr_count = HWIO_IN(MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL);
  return curr_count;
}

// Maximum delay is 134s
void ufs_bsp_busy_wait(uint32_t us)
{
   uint32_t pause_cycle = us * 32 / 1000 + us * 768 / 1000000;
   uint32_t now;

   // Need to check if there is a case of wrapping around
   now = Clock_GetSclkTimetick();
   while( Clock_GetSclkTimetick() - now <= pause_cycle);
}

// Constant table for UFS-PHY initialization
static struct ufs_mphy_init_item ufs_bsp_mphy_init_table[] = {

     { HWIO_UFS_PHY_PHY_START_ADDR                 ,  0x00}, 
     { HWIO_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR   ,  0x3f}, 
     { HWIO_QSERDES_COM_SYSCLK_EN_SEL_ADDR         ,  0x03}, 
     { HWIO_QSERDES_COM_SYS_CLK_CTRL_ADDR          ,  0x16}, 
     { HWIO_QSERDES_COM_RES_CODE_TXBAND_ADDR       ,  0xC0}, 
     { HWIO_QSERDES_COM_PLL_VCOTAIL_EN_ADDR        ,  0x03}, 
     { HWIO_QSERDES_COM_PLL_CNTRL_ADDR             ,  0x88}, 
     { HWIO_QSERDES_COM_PLL_CLKEPDIV_ADDR          ,  0x03}, // 0x02 - doesn't work, looks like timing problem
     { HWIO_QSERDES_COM_RESETSM_CNTRL_ADDR         ,  0x30}, 
     { HWIO_QSERDES_COM_PLL_RXTXEPCLK_EN_ADDR      ,  0x10}, 
     { HWIO_QSERDES_COM_PLL_CRCTRL_ADDR            ,  0x94}, 
     { HWIO_QSERDES_COM_DEC_START1_ADDR            ,  0x98}, 
     { HWIO_QSERDES_COM_DEC_START2_ADDR            ,  0x02}, 
     { HWIO_QSERDES_COM_DIV_FRAC_START1_ADDR       ,  0x8c}, 
     { HWIO_QSERDES_COM_DIV_FRAC_START2_ADDR       ,  0xae}, 
     { HWIO_QSERDES_COM_DIV_FRAC_START3_ADDR       ,  0x1f}, 
     { HWIO_QSERDES_COM_PLLLOCK_CMP1_ADDR          ,  0xf7}, 
     { HWIO_QSERDES_COM_PLLLOCK_CMP2_ADDR          ,  0x13}, 
     { HWIO_QSERDES_COM_PLLLOCK_CMP3_ADDR          ,  0x00}, 
     { HWIO_QSERDES_COM_PLLLOCK_CMP_EN_ADDR        ,  0x01}, 
     { HWIO_QSERDES_COM_PLL_IP_SETI_ADDR           ,  0x01}, 
     { HWIO_QSERDES_COM_PLL_CP_SETI_ADDR           ,  0x3b}, 
     { HWIO_QSERDES_COM_PLL_IP_SETP_ADDR           ,  0x0a}, 
     { HWIO_QSERDES_COM_PLL_CP_SETP_ADDR           ,  0x04}, 
     { HWIO_QSERDES_RX0_PWM_CNTRL1_ADDR            ,  0x8F}, 
     { HWIO_QSERDES_RX0_PWM_CNTRL2_ADDR            ,  0x61}, 
     { HWIO_QSERDES_RX0_PWM_NDIV_ADDR              ,  0x4F}, 
     { HWIO_QSERDES_RX0_CDR_CONTROL_ADDR           ,  0xf2}, 
     { HWIO_QSERDES_RX0_CDR_CONTROL_HALF_ADDR      ,  0x2a}, 
     { HWIO_QSERDES_RX0_CDR_CONTROL_QUARTER_ADDR   ,  0x2a}, 
     { HWIO_QSERDES_RX0_SIGDET_CNTRL_ADDR          ,  0xc0}, 
     { HWIO_QSERDES_RX0_SIGDET_CNTRL2_ADDR         ,  0x07}, 
     { HWIO_QSERDES_RX0_UFS_CNTRL_ADDR             ,  0x18}, 
     { HWIO_UFS_PHY_POWER_DOWN_CONTROL_ADDR        ,  0x01}, 
     {0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_rate_b_init_table[] = {
     {0,0}};

uint32_t ufs_bsp_get_mphy_init_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_init_table;
   return sizeof(ufs_bsp_mphy_init_table)/sizeof(struct ufs_mphy_init_item);
}

uint32_t ufs_bsp_get_mphy_init_rate_b_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_rate_b_init_table;
   return sizeof(ufs_bsp_mphy_rate_b_init_table)/sizeof(struct ufs_mphy_init_item);
}

// Start the PHY and wait for the PHY to be ready
uint32_t ufs_bsp_mphy_start (uint8_t hostid)
{
   
   uintptr_t base_addr;
   int32_t tout = UFS_PHY_PCS_READY_TIMEOUT;

   base_addr = ufs_bsp_get_reg_baseaddress (hostid);

   HWIO_REG_OUTM (base_addr, UFS_PHY_PHY_START_ADDR, 1, 1);
   ufs_bsp_busy_wait (10);
   
   while (!(HWIO_REG_IN(base_addr, UFS_PHY_PCS_READY_STATUS_ADDR) & 0x01)) {
      if (tout-- == 0) {
         return FAIL;
      }
      ufs_bsp_busy_wait (1);
   }

   while ((HWIO_REG_IN(base_addr, QSERDES_COM_RESET_SM_ADDR) != 0x3d)) {
      if (tout-- == 0) {
         return FAIL;
      }
      ufs_bsp_busy_wait (1);
   }

   return SUCCESS;
}

void ufs_bsp_post_link_init (uint8_t hostid)
{
   (void) hostid;
}

void ufs_bsp_cache_op (void *addr, uint32_t len, uint32_t op) 
{
   (void) addr;
   (void) len;
   (void) op;
}

void ufs_bsp_memory_barrier ()
{
   ArmDataMemoryBarrier();
}

void *ufs_bsp_allocate_norm_buf (size_t size)
{
   (void) size;
   void *mem = transfer_request_list_buf;
   return mem;
}

void  ufs_bsp_free_norm_buf (void *pmem)
{
   (void) pmem;
}

void *ufs_bsp_allocate_xfer_buf (size_t size)
{
   (void) size;
   void *mem = transfer_request_list_buf;
   return mem;
}

void  ufs_bsp_free_xfer_buf (void *pmem)
{
   (void) pmem;
}

void ufs_bsp_get_platform_config (struct ufs_bsp_config_item *itm)
{
   itm->skip_gear_sw = 1;
   itm->slow_xfer = 1;
   itm->skip_link_start = 0;
}

uintptr_t ufs_bsp_get_reg_baseaddress (uint8_t hostid)
{
   (void) hostid;
   return (uintptr_t) 0x1da0000;
}

boolean ufs_bsp_get_dal_config(struct ufs_dal_config_item *itm)
{
   (void) itm; 
   return TRUE; 
}

