/**********************************************************************
* ufs_bsp_jtag_Sdm660.c
*
* Board support file for SDM660
*
* Copyright (c) 2013-2016, 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
* 
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/UFS/jtag/ufs_bsp_jtag_Sdm660.c#6 $
$DateTime: 2018/10/16 09:22:30 $

YYYY-MM-DD   who     what, where, why
---------------------------------------------------------------------- 
2018-10-12   sb      Add reset api support
2016-12-21   sb      Add DAL config  
2016-06-06   sb      PHY settings for Starlord
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2015-02-12   rh      8996 V1 PHY workaround
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

#include "../inc/ufs_osal.h"
#include "../inc/ufs_bsp.h"
#include "../inc/ufs_phy_hwio_v2.h"
#include "../inc/hwio_mpm2.h"
#include "../inc/hwio_tlmm_ufs.h"
#include "../inc/hwio_gcc_ufs.h"
#include "ClockBoot.h"
#include "DDIPlatformInfo.h"

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
#define HWIO_GCC_UFS_BCR_OUT(v)        \
        out_dword(HWIO_GCC_UFS_BCR_ADDR,v)

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

DalPlatformInfoPlatformType g_platform = 0;

void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode)
{
   (void) hostid;
   if (mode == UFS_CLOCK_MODE_OFF) {
      (void) Clock_UFSInit (CLOCK_BOOT_PERF_NONE);
   }
   else if (mode == UFS_CLOCK_MODE_ON) {
      (void) Clock_UFSInit (CLOCK_BOOT_PERF_NOMINAL);
   }
}

void ufs_bsp_enable_symbol_clk (void)
{
}

/* A utility function to get the sleep timetick */
static uint32 Clock_GetSclkTimetick()
{
   uint32_t curr_count;
   uint32_t last_count;
   
   /*Grab current time count*/
   curr_count = HWIO_IN(MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL);
   
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return curr_count;
   }
   
   
   /*Keep grabbing the time until a stable count is given*/
   do 
   {
     last_count = curr_count;
     curr_count = HWIO_IN(MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL);
   } while (curr_count != last_count);
   
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
     { HWIO_UFS_UFS_PHY_POWER_DOWN_CONTROL_ADDR,                    0x01},
     { HWIO_UFS_QSERDES_COM_CMN_CONFIG_ADDR,                        0x0e},
     { HWIO_UFS_QSERDES_COM_SYSCLK_EN_SEL_ADDR,                     0x14},
     { HWIO_UFS_QSERDES_COM_CLK_SELECT_ADDR,                        0x30},
     { HWIO_UFS_QSERDES_COM_SYS_CLK_CTRL_ADDR,                      0x02},
     { HWIO_UFS_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR,               0x08},
     { HWIO_UFS_QSERDES_COM_BG_TIMER_ADDR,                          0x0a},
     { HWIO_UFS_QSERDES_COM_HSCLK_SEL_ADDR,                         0x00},
     { HWIO_UFS_QSERDES_COM_CORECLK_DIV_ADDR,                       0x0a},
     { HWIO_UFS_QSERDES_COM_CORECLK_DIV_MODE1_ADDR,                 0x0a},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP_EN_ADDR,                       0x01},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_CTRL_ADDR,                     0x00},
     { HWIO_UFS_QSERDES_COM_RESETSM_CNTRL_ADDR,                     0x20},
     { HWIO_UFS_QSERDES_COM_CORE_CLK_EN_ADDR,                       0x00},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP_CFG_ADDR,                      0x00},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_TIMER1_ADDR,                   0xff},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_TIMER2_ADDR,                   0x3f},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_MAP_ADDR,                      0x04},       // Adjust for series A
     { HWIO_UFS_QSERDES_COM_SVS_MODE_CLK_SEL_ADDR,                  0x05},
     { HWIO_UFS_QSERDES_COM_DEC_START_MODE0_ADDR,                   0x82},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START1_MODE0_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START2_MODE0_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START3_MODE0_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_CP_CTRL_MODE0_ADDR,                     0x0b},
     { HWIO_UFS_QSERDES_COM_PLL_RCTRL_MODE0_ADDR,                   0x16},
     { HWIO_UFS_QSERDES_COM_PLL_CCTRL_MODE0_ADDR,                   0x28},
     { HWIO_UFS_QSERDES_COM_INTEGLOOP_GAIN0_MODE0_ADDR,             0x80},
     { HWIO_UFS_QSERDES_COM_INTEGLOOP_GAIN1_MODE0_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE1_MODE0_ADDR,                   0x28},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE2_MODE0_ADDR,                   0x02},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP1_MODE0_ADDR,                   0xff},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP2_MODE0_ADDR,                   0x0c},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP3_MODE0_ADDR,                   0x00},
     { HWIO_UFS_QSERDES_COM_DEC_START_MODE1_ADDR,                   0x98},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START1_MODE1_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START2_MODE1_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_DIV_FRAC_START3_MODE1_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_CP_CTRL_MODE1_ADDR,                     0x0b},
     { HWIO_UFS_QSERDES_COM_PLL_RCTRL_MODE1_ADDR,                   0x16},
     { HWIO_UFS_QSERDES_COM_PLL_CCTRL_MODE1_ADDR,                   0x28},
     { HWIO_UFS_QSERDES_COM_INTEGLOOP_GAIN0_MODE1_ADDR,             0x80},
     { HWIO_UFS_QSERDES_COM_INTEGLOOP_GAIN1_MODE1_ADDR,             0x00},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE1_MODE1_ADDR,                   0xd6},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE2_MODE1_ADDR,                   0x00},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP1_MODE1_ADDR,                   0x32},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP2_MODE1_ADDR,                   0x0f},
     { HWIO_UFS_QSERDES_COM_LOCK_CMP3_MODE1_ADDR,                   0x00},
     { HWIO_UFS_QSERDES_TX_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN_ADDR,   0x45},
     { HWIO_UFS_QSERDES_TX_LANE_MODE_ADDR,                          0x06},
     { HWIO_UFS_QSERDES_RX_SIGDET_LVL_ADDR,                         0x24},
     { HWIO_UFS_QSERDES_RX_SIGDET_CNTRL_ADDR,                       0x0F},
     { HWIO_UFS_QSERDES_RX_RX_INTERFACE_MODE_ADDR,                  0x40},
     { HWIO_UFS_QSERDES_RX_SIGDET_DEGLITCH_CNTRL_ADDR,              0x1E},
     { HWIO_UFS_QSERDES_RX_UCDR_FASTLOCK_FO_GAIN_ADDR,              0x0B},
     { HWIO_UFS_QSERDES_RX_RX_TERM_BW_ADDR,                         0x5B},
     { HWIO_UFS_QSERDES_RX_RX_EQ_GAIN1_LSB_ADDR,                    0xFF},
     { HWIO_UFS_QSERDES_RX_RX_EQ_GAIN1_MSB_ADDR,                    0x3F},
     { HWIO_UFS_QSERDES_RX_RX_EQ_GAIN2_LSB_ADDR,                    0xFF},
     { HWIO_UFS_QSERDES_RX_RX_EQ_GAIN2_MSB_ADDR,                    0x3F},
     { HWIO_UFS_QSERDES_RX_RX_EQU_ADAPTOR_CNTRL2_ADDR,              0x0D},
     { HWIO_UFS_QSERDES_COM_PLL_IVCO_ADDR,                          0x0f},
     { HWIO_UFS_QSERDES_COM_BG_TRIM_ADDR,                           0x0f},
     { HWIO_UFS_UFS_PHY_RX_PWM_GEAR_BAND_ADDR,                      0x15},
     { HWIO_UFS_QSERDES_RX_UCDR_SVS_SO_GAIN_HALF_ADDR,              0x04},
     { HWIO_UFS_QSERDES_RX_UCDR_SVS_SO_GAIN_QUARTER_ADDR,           0x04},
     { HWIO_UFS_QSERDES_RX_UCDR_SVS_SO_GAIN_ADDR,                   0x04},
     { HWIO_UFS_QSERDES_RX_UCDR_SO_SATURATION_AND_ENABLE_ADDR,      0x4B},
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_INITVAL1_ADDR,                 0xFF}, 
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_INITVAL2_ADDR,                 0x00},
     { HWIO_UFS_UFS_PHY_RX_SIGDET_CTRL2_ADDR,                       0x6c},
     { HWIO_UFS_UFS_PHY_TX_LARGE_AMP_DRV_LVL_ADDR,                  0x0a},
     { HWIO_UFS_UFS_PHY_TX_SMALL_AMP_DRV_LVL_ADDR,                  0x02},
     { HWIO_UFS_UFS_PHY_RX_MIN_STALL_NOCONFIG_TIME_CAPABILITY_ADDR, 0x28},
     { HWIO_UFS_UFS_PHY_RX_SYM_RESYNC_CTRL_ADDR,                    0x03},
     {0,0}};


static struct ufs_mphy_init_item ufs_bsp_mphy_rate_b_init_table[] = {
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_MAP_ADDR,                      0x44},
     {0,0}};

uint32_t ufs_bsp_get_mphy_init_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_init_table;
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0;
   }
   else {
      return sizeof(ufs_bsp_mphy_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_init_rate_b_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_rate_b_init_table;
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0;
   }
   else {
      return sizeof(ufs_bsp_mphy_rate_b_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

// Start the PHY and wait for the PHY to be ready
uint32_t ufs_bsp_mphy_start (uint8_t hostid)
{
   uintptr_t base_addr;
   int32_t tout = UFS_PHY_PCS_READY_TIMEOUT;

   // RUMI Specific PHY address 
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return SUCCESS;
   }

   base_addr = ufs_bsp_get_reg_baseaddress (hostid);
   HWIO_REG_OUTM (base_addr, UFS_UFS_PHY_PHY_START_ADDR, 1, 1);
   ufs_bsp_busy_wait (10);
   
   
   while (!(HWIO_REG_IN(base_addr, UFS_UFS_PHY_PCS_READY_STATUS_ADDR) & 0x01)) {
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

void ufs_bsp_reset (uint8_t hostid)
{
   (void) hostid; 

   HWIO_GCC_UFS_BCR_OUT(1); 
   ufs_bsp_busy_wait(500);
   HWIO_GCC_UFS_BCR_OUT(0); 
}

void ufs_bsp_device_reset (uint8_t hostid)
{
   (void) hostid; 

   out_dword(HWIO_TLMM_UFS_RESET_ADDR, 0); 
   ufs_bsp_busy_wait(10); 
   out_dword(HWIO_TLMM_UFS_RESET_ADDR, 1); 
   ufs_bsp_busy_wait(10); 
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
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      itm->skip_gear_sw = 1;
      itm->slow_xfer = 1;
      itm->skip_link_start = 0;
      itm->core_skip = 0; 
   }
   else {
      /* VIRTIO or Silicon */
      itm->skip_gear_sw = 0;
      itm->slow_xfer = 0;
      itm->skip_link_start = 0;
      itm->core_skip = 0; 
   }
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

