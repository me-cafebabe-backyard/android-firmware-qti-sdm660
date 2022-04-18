/*! \file pm_pon.c
*  \n
*  \brief PMIC PowerON Peripheral driver
*  \n
*  \n This header file contains class implementation of the PON
*  \n peripheral APIs
*  \n
*  \n &copy; Copyright 2012-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
			        EDIT HISTORY FOR MODULE
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
05/09/17   czq     correct some faults in API pm_pon_gen1_config_uvlo().
05/03/17   czq     Support for PON_RESET_CFG_WARM_RESET_THEN_DVDD_SHUTDOWN_VAL.
01/06/17   al      Updated pon_init for pon_gen2 warm reset
11/11/16   aab     Updated pon_gen2_uvlo_threshold_val[]
05/06/16   aab     Updated pm_pon_overtemp_reset_cf() and pm_pon_get_reset_config_val()
05/02/16   aab     Support for RUMI with no pmic card.
03/28/16   aab     Added pm_pon_gp_reset_cfg() and pm_pon_get_reset_config_val()
03/22/16   aab     Added pm_pon_get_fault_reasons() updated pm_pon_get_all_pon_reasons() 
03/22/16   aab     Updated pm_pon_config_uvlo() Added pm_pon_gen1_config_uvlo()
12/07/15   aab     Updated to support PON GEN2 peripheral
09/16/15   al      Updating xvdd status read 
08/08/15   aab     Updated pm_pon_init() to support PON APIs with out doing pm init
11/12/15   kt      Updated pm_pon_ps_hold_cfg API.
11/19/14   al      Removing loader specific 
09/15/14   aab     Added PON Reasons status log
07/16/14   akm     Comm change Updates
08/19/14   al      Adding API to configure PON trigger
12/04/13   aab     Added PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET
11/01/13   sv      Applying CR538994 Changes with power up failure fix. (CR-570053)
10/24/13   sv      Reverting CR538994 Changes (CR-566323)
06/24/13   ps      Added PON Stage3 reset config API CR#495834 
02/27/13   kt      Added PON Reasons and IRQ related APIs  
01/24/13   umr     Add new version support.
11/20/12   umr     Created
========================================================================== */

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include "pm_version.h"
#include "pm_pon.h"
#include "pm_app_pon.h"
#include "pmio_pon.h"
#include "hw_module_type.h"
#include "device_info.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "pm_config_target.h"
#include "pm_device.h"

/* PMIC Device Index IDs */
#define PMIC_A_DEVICE_ID   0
#define PMIC_B_DEVICE_ID   1

#define PON_RESET_CFG_WARM_RESET_VAL           0x01
#define PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL  0x02
#define PON_RESET_CFG_NORMAL_SHUTDOWN_VAL      0x04
#define PON_RESET_CFG_D_VDD_SHUTDOWN_VAL       0x05
#define PON_RESET_CFG_X_VDD_SHUTDOWN_VAL       0x06
#define PON_RESET_CFG_HARD_RESET_VAL           0x07
#define PON_RESET_CFG_D_VDD_HARD_RESET_VAL     0x08
#define PON_RESET_CFG_X_VDD_HARD_RESET_VAL     0x09

#define PON_RESET_CFG_DVDD_HARD_RESET_VAL                 0x08 
#define PON_RESET_CFG_XVDD_HARD_RESET_VAL                 0x09 
#define PON_RESET_CFG_WARM_RESET_THEN_DVDD_SHUTDOWN_VAL   0x0A 
#define PON_RESET_CFG_WARM_RESET_THEN_XVDD_SHUTDOWN_VAL   0x0B 
#define PON_RESET_CFG_WARM_RESET_THEN_SHUTDOWN_VAL        0x0C 
#define PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET_VAL      0x0D 
#define PON_RESET_CFG_WARM_RESET_THEN_DVDD_HARD_RESET_VAL 0x0E 
#define PON_RESET_CFG_WARM_RESET_THEN_XVDD_HARD_RESET_VAL 0x0F

/* PON_DVDD_RB_SPARE reg Warm Reset indicating bit mask */
#define PON_DVDD_RB_SPARE_WARM_RESET_MASK                 0x01

#define PM_PON_MAX_SPARE_BIT_MASK                         0xFF

#define PMIO_PON_TRIGGER_EDGE_CONFIG                      0x881


typedef struct 
{
  uint16 s1_timer_addr; 
  uint16 s1_timer_mask; 
  uint16 s2_timer_addr;
  uint16 s2_timer_mask;
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
}pon_reset_reg_info_type;

typedef struct
{
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
}pon_ps_hold_reg_info_type;

typedef struct
{
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
}pon_overtemp_reg_info_type;

typedef struct
{
  uint16 ctl_addr;
  uint16 kpwpwr_mask;
  uint16 cblpwr_mask;
  uint16 pon1_mask;
  uint16 usb_chg_mask;
  uint16 dc_chg_mask;
  uint16 rtc_mask;
  uint16 smpl_mask;
}pon_trigger_en_reg_info_type;

typedef struct
{
    uint8 pon_reason1;
    uint8 pon_reason2;
    uint8 poff_reason1;
    uint8 poff_reason2;
    uint8 warm_reset_reason1;
    uint8 warm_reset_reason2;
    uint8 soft_reset_reason1;
    uint8 soft_reset_reason2;
}pm_reason_status_type;


static pon_trigger_en_reg_info_type
pon_trigger_en_reg =
{
  PMIO_PON_PON_TRIGGER_EN_ADDR,
  PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_BMSK,
  PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_BMSK,
  PMIO_PON_PON_TRIGGER_EN_PON1_BMSK,
  PMIO_PON_PON_TRIGGER_EN_USB_CHG_BMSK,
  PMIO_PON_PON_TRIGGER_EN_DC_CHG_BMSK,
  PMIO_PON_PON_TRIGGER_EN_RTC_BMSK,
  PMIO_PON_PON_TRIGGER_EN_SMPL_BMSK,
};

static pon_reset_reg_info_type
pon_kpdpwr_reg =
{
  PMIO_PON_KPDPWR_N_RESET_S1_TIMER_ADDR,
  PMIO_PON_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_KPDPWR_N_RESET_S2_TIMER_ADDR,
  PMIO_PON_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_KPDPWR_N_RESET_S2_CTL_ADDR,
  PMIO_PON_KPDPWR_N_RESET_S2_CTL2_ADDR,
  PMIO_PON_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_KPDPWR_N_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_reset_reg_info_type
pon_resin_reg =
{
  PMIO_PON_RESIN_N_RESET_S1_TIMER_ADDR,
  PMIO_PON_RESIN_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_RESIN_N_RESET_S2_TIMER_ADDR,
  PMIO_PON_RESIN_N_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_RESIN_N_RESET_S2_CTL_ADDR,
  PMIO_PON_RESIN_N_RESET_S2_CTL2_ADDR,
  PMIO_PON_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_RESIN_N_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_reset_reg_info_type
pon_resin_and_kpdpwr_reg =
{
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_CTL_ADDR,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_RESIN_AND_KPDPWR_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_reset_reg_info_type
pon_gp1_reg =
{
  PMIO_PON_GP1_RESET_S1_TIMER_ADDR,
  PMIO_PON_GP1_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_GP1_RESET_S2_TIMER_ADDR,
  PMIO_PON_GP1_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_GP1_RESET_S2_CTL_ADDR,
  PMIO_PON_GP1_RESET_S2_CTL2_ADDR,
  PMIO_PON_GP1_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_GP1_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_reset_reg_info_type
pon_gp2_reg =
{
  PMIO_PON_GP2_RESET_S1_TIMER_ADDR,
  PMIO_PON_GP2_RESET_S1_TIMER_S1_TIMER_BMSK,
  PMIO_PON_GP2_RESET_S2_TIMER_ADDR,
  PMIO_PON_GP2_RESET_S2_TIMER_S2_TIMER_BMSK,
  PMIO_PON_GP2_RESET_S2_CTL_ADDR,
  PMIO_PON_GP2_RESET_S2_CTL2_ADDR,
  PMIO_PON_GP2_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_GP2_RESET_S2_CTL_RESET_TYPE_BMSK
};

static pon_ps_hold_reg_info_type
pon_ps_hold_reg =
{
  PMIO_PON_PS_HOLD_RESET_CTL_ADDR,
  PMIO_PON_PS_HOLD_RESET_CTL2_ADDR,
  PMIO_PON_PS_HOLD_RESET_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_PS_HOLD_RESET_CTL_RESET_TYPE_BMSK
};

static pon_overtemp_reg_info_type
pon_overtemp_reg =
{
  PMIO_PON_OVERTEMP_RESET_CTL_ADDR,
  PMIO_PON_OVERTEMP_RESET_CTL2_ADDR,
  PMIO_PON_OVERTEMP_RESET_CTL2_S2_RESET_EN_BMSK,
  PMIO_PON_OVERTEMP_RESET_CTL_RESET_TYPE_BMSK
};

static uint32
pon_s1_timer_val[] =
{0, 32, 56, 80, 128, 184, 272, 408, 608, 904, 1352, 2048, 3072, 4480, 6720, 10256};

const uint32
pon_s1_timer_arr_size = sizeof(pon_s1_timer_val)/sizeof(pon_s1_timer_val[0]);

static uint32
pon_s2_timer_val[] =
{0, 10, 50, 100, 250, 500, 1000, 2000};

const uint32
pon_s2_timer_arr_size = sizeof(pon_s2_timer_val)/sizeof(pon_s2_timer_val[0]);

static uint32
pon_s3_timer_val[] =
{0, 2, 4, 8, 16, 32, 64, 128};

const uint32
pon_s3_timer_arr_size = sizeof(pon_s3_timer_val)/sizeof(pon_s3_timer_val[0]);

static uint32
pon_debounce_time_val[] =
{15600, 31200, 62500, 125000, 250000, 500000, 1000000, 2000000};

static uint32
pon_gen2_debounce_time_val[] =
{60, 120, 240, 490, 980, 2000,3900, 7800, 15600, 31200, 62500, 125000, 25000};

const uint32
pon_debounce_time_arr_size = sizeof(pon_debounce_time_val)/sizeof(pon_debounce_time_val[0]);

const uint32
pon_gen2_debounce_time_arr_size = sizeof(pon_gen2_debounce_time_val)/sizeof(pon_debounce_time_val[0]);

static uint32
pon_gen2_uvlo_hyst_val[] = 
{ 225, 375, 525, 600};

const uint32
pon_gen2_uvlo_hyst_val_arr_size = sizeof(pon_gen2_uvlo_hyst_val)/sizeof(pon_gen2_uvlo_hyst_val[0]);

static uint32
pon_gen2_uvlo_threshold_val[] = 
{ 1500, 1550, 1600, 1650, 1700, 1750, 1800, 1850, 1900, 1950, 2000, 2050, 2100, 2150, 2200, 2250, 2300,
  2350, 2400, 2450, 2500, 2550, 2600, 2650, 2700, 2750, 2800, 2850, 2900, 2950, 3000, 3050 };

const uint32
pon_gen2_uvlo_threshold_val_arr_size = sizeof(pon_gen2_uvlo_threshold_val)/sizeof(pon_gen2_uvlo_threshold_val[0]);


static boolean
pm_pon_initialized = FALSE;

/*local APIs*/
static pm_err_flag_type pm_pon_get_xvdd_rb(boolean *xvdd_status);

typedef struct
{
    peripheral_info_type preph_info;
    //pm_device_info_type  device_info;
} pm_pon_data_type;

static pm_pon_data_type pm_pon_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

Function Prototypes

===========================================================================*/
pm_err_flag_type pm_pon_gen1_config_uvlo(uint32 pmic_device_index, uint32 uvlo_thresh_voltage_in_mv, uint32 hyst_voltage_in_mv);
pm_err_flag_type pm_pon_gen2_config_uvlo(uint8 pmic_device_index, uint32 uvlo_thresh_voltage_in_mv, uint32 uvlo_hyst_voltage_in_mv, boolean uvlo_enable);
static pm_err_flag_type pm_pon_get_reset_config_val(pm_pon_reset_cfg_type pon_reset_cfg, uint8* pon_reset_cfg_val);

/*===========================================================================

API Implementation

===========================================================================*/

pm_err_flag_type
pm_pon_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint8   pmic_index  = 0;
  uint8   sid_index   = 0;
  uint8   periph_type = 0;
  uint32  pon_peripheral_index = 8;
  peripheral_info_type  pon_peripheral_info;
  uint8   warm_reset_reason[2] = { 0 };
  boolean warm_reset_occured = FALSE;

  memset(&pon_peripheral_info, 0, sizeof(peripheral_info_type));

  pon_peripheral_info.base_address = pon_peripheral_index * 0x0100;

  if (pm_pon_initialized == TRUE)
  {
    return err_flag;
  }

  //Ensure that pmic device is initialized
  err_flag |= pm_device_setup();

  /* Read PON Peripheral info and check if it's valid */
  err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_PERPH_TYPE_ADDR, &periph_type, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  if (periph_type != PM_HW_MODULE_PON)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    sid_index = pmic_index * 2;

    //Get PON perepheral type and perepheral sub type for each valid PMIC on target
    pm_get_peripheral_info(sid_index, &pon_peripheral_info);
    if (err_flag == PM_ERR_FLAG__SUCCESS)
    {
      pm_pon_data_arr[pmic_index].preph_info = pon_peripheral_info;
    }
  }

  if (pm_pon_data_arr[PMIC_A_SLAVEID_PRIM].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON) /* GEN1 */
  {
    /* Read Warm Reset reason */
    err_flag |= pm_comm_read_byte_array(PMIC_A_SLAVEID_PRIM, PMIO_PON_WARM_RESET_REASON1_ADDR, 2, warm_reset_reason, 0);  
    if ((warm_reset_reason[0] != 0) || (warm_reset_reason[1] != 0))
    {
        warm_reset_occured = TRUE;
    }
  }
  else /* GEN2 */
  {
    /* Read ON reason */
    err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_GEN2_ON_REASON_ADDR, warm_reset_reason, 0); 
    if (warm_reset_reason[0] & PMIO_PON_GEN2_ON_REASON_WARM_SEQ_BMSK)
    {
      warm_reset_occured = TRUE;
    }
  }

  /* Update the DVDD_RB_SPARE register bit <0> to 1 if Warm Reset occured */
  if (TRUE == warm_reset_occured)
  {
    err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_DVDD_RB_SPARE_ADDR, PON_DVDD_RB_SPARE_WARM_RESET_MASK, 0x01, 0);
  }

  if (err_flag == PM_ERR_FLAG__SUCCESS)
         pm_pon_initialized = TRUE;

  return err_flag;
}




//Applicable only for PON GEN1 
pm_err_flag_type
pm_pon_overtemp_reset_cfg(uint32 pmic_device_index, pm_pon_reset_cfg_type overtemp_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 overtemp_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;

  if (  (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_type     == PM_HW_MODULE_PON) && 
        (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  >= PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY) )
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED; 
  }


  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  if (overtemp_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (!pm_pon_initialized)
  {
    err_flag |= pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }


  /* Disable reset */
  err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM,
                                          pon_overtemp_reg.reset_ctl2_addr,
                                          pon_overtemp_reg.reset_en_mask, 0x0, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Requires 10 sleep clock cycles of delay */
  pm_busy_wait(300);

  switch (overtemp_cfg)
  {
     case PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
       overtemp_cfg_val = PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_NORMAL_SHUTDOWN:
       overtemp_cfg_val = PON_RESET_CFG_NORMAL_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:
       overtemp_cfg_val = PON_RESET_CFG_D_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
       overtemp_cfg_val = PON_RESET_CFG_X_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_HARD_RESET:
       overtemp_cfg_val = PON_RESET_CFG_HARD_RESET_VAL;
       break;

    case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:
      overtemp_cfg_val = PON_RESET_CFG_D_VDD_HARD_RESET_VAL;
      break;

    case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
      overtemp_cfg_val = PON_RESET_CFG_X_VDD_HARD_RESET_VAL;
      break;


     default:
       /* Enable reset */
       err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM,
                                               pon_overtemp_reg.reset_ctl2_addr,
                                               pon_overtemp_reg.reset_en_mask, 0xFF, 0);
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM,
                                          pon_overtemp_reg.reset_ctl_addr,
                                          pon_overtemp_reg.reset_type_mask,
                                          overtemp_cfg_val, 0);


  /* Enable reset */
  err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM,
                                          pon_overtemp_reg.reset_ctl2_addr,
                                          pon_overtemp_reg.reset_en_mask, 0xFF, 0);
  return err_flag;
}




pm_err_flag_type
pm_pon_ps_hold_cfg(uint32 pmic_device_index, pm_pon_reset_cfg_type ps_hold_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 ps_hold_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;
  uint32 slave_id = 0;

  if (pm_pon_initialized == FALSE)
  {
    err_flag |= pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag |= pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  if (ps_hold_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  err_flag |= pm_pon_get_reset_config_val(ps_hold_cfg, &ps_hold_cfg_val);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
     return err_flag;
  }

  /* Disable reset */
  err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, 0x0, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Requires 10 sleep clock cycles of delay */
  pm_busy_wait(300);

  err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl_addr, ps_hold_cfg_val, 0);

  /* Enable reset */
  err_flag |= pm_comm_write_byte(slave_id, pon_ps_hold_reg.reset_ctl2_addr, pon_ps_hold_reg.reset_en_mask, 0);

  return err_flag;
}




pm_err_flag_type
pm_pon_reset_source_cfg(uint32 pmic_device_index, pm_pon_reset_source_type reset_source,
                        uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 reset_en, reset_val = 0;
  uint8 s1_timer_id, s2_timer_id = 0;
  pon_reset_reg_info_type *reset_reg = NULL;
  uint32 slave_id = 0;

  if (s1_timer > pon_s1_timer_val[pon_s1_timer_arr_size - 1])
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (s2_timer > pon_s2_timer_val[pon_s2_timer_arr_size - 1])
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (reset_cfg_type >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag |= pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id index 0 */
  err_flag |= pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  /* Calc S1 & S2 timer id. Get the upper limit if a value falls in between */
  s1_timer_id = pm_utils_get_upper_idx(s1_timer, pon_s1_timer_val, pon_s1_timer_arr_size);
  s2_timer_id = pm_utils_get_upper_idx(s2_timer, pon_s2_timer_val, pon_s2_timer_arr_size);

  switch (reset_source)
  {
     case PM_PON_RESET_SOURCE_KPDPWR:
       reset_reg = &pon_kpdpwr_reg;
       break;

     case PM_PON_RESET_SOURCE_RESIN:
       reset_reg = &pon_resin_reg;
       break;

     case PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR:
       reset_reg = &pon_resin_and_kpdpwr_reg;
       break;

     case PM_PON_RESET_SOURCE_GP1:
       reset_reg = &pon_gp1_reg;
       break;

     case PM_PON_RESET_SOURCE_GP2:
       reset_reg = &pon_gp2_reg;
       break;

     default:
       return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  err_flag = pm_comm_read_byte(slave_id, reset_reg->reset_ctl2_addr, &reset_en, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  reset_en = reset_en & reset_reg->reset_en_mask;

  if (reset_en)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0x0, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
    /* Requires 10 sleep clock cycles of delay */
    pm_busy_wait(300);
  }

  /* Configure S1 timer */
  if (reset_source == PM_PON_RESET_SOURCE_KPDPWR)
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, pon_trigger_en_reg.ctl_addr,
                                            pon_trigger_en_reg.kpwpwr_mask, 0x0, 0);
    /* Requires 5 sleep clock cycles of delay */
    pm_busy_wait(150);
  }

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s1_timer_addr,
                                          reset_reg->s1_timer_mask, s1_timer_id, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  if (reset_source == PM_PON_RESET_SOURCE_KPDPWR)
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, pon_trigger_en_reg.ctl_addr, 
                                            pon_trigger_en_reg.kpwpwr_mask , 0xFF, 0);
  }

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Configure S2 timer */
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s2_timer_addr, 
                                          reset_reg->s2_timer_mask, s2_timer_id, 0);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  err_flag |= pm_pon_get_reset_config_val(reset_cfg_type, &reset_val);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
     return err_flag;
  }

  /* Configure reset value */
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl_addr, reset_reg->reset_type_mask, reset_val, 0);

  /* Enable reset if it was already in enable state */
  if (reset_en)
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0xFF, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_pon_gp_reset_cfg( uint32  pmic_device_index, pm_pon_reset_source_type reset_source, pm_pon_reset_cfg_type reset_cfg_type) 
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
    uint8 reset_en,
    reset_val = 0;
    uint32 slave_id = 0;
    pon_reset_reg_info_type *reset_reg = NULL;

    if (reset_cfg_type >= PM_PON_RESET_CFG_INVALID)
    {
       return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
    }


    if (pm_pon_initialized == FALSE)
    {
       err_flag |= pm_pon_init();
       if (err_flag != PM_ERR_FLAG__SUCCESS)
       {
         return err_flag;
       }
    }

    err_flag |= pm_get_slave_id(pmic_device_index, 0, &slave_id);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
    }

    switch (reset_source)
    {
       case PM_PON_RESET_SOURCE_GP1:
         reset_reg = &pon_gp1_reg; 
         break;
    
       case PM_PON_RESET_SOURCE_GP2:
         reset_reg = &pon_gp2_reg;
         break;
    
       default:
         return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
    }

    //Read reset status
    err_flag |= pm_comm_read_byte(slave_id, reset_reg->reset_ctl2_addr, &reset_en, 0);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
       return err_flag;
    }
    reset_en = reset_en & reset_reg->reset_en_mask;


    if (reset_en)
    {
      err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0x0, 0);//Disable Reset
      pm_busy_wait(300); /* Requires 8 sleep clock cycles of delay */ 
    }


    err_flag |= pm_pon_get_reset_config_val(reset_cfg_type, &reset_val);
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
       return err_flag;
    }
    
    /* Configure reset value */
    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl_addr, reset_reg->reset_type_mask, reset_val, 0);
  
    
    if (reset_en)
    {  /* Enable reset if it was already in enable state */
       err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0xFF, 0);
       if (err_flag != PM_ERR_FLAG__SUCCESS)
       {
         return err_flag;
       }
    }
  
    return err_flag;

}


pm_err_flag_type
pm_pon_reset_source_ctl(uint32 pmic_device_index,
                        pm_pon_reset_source_type reset_source, pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pon_reset_reg_info_type *reset_reg = NULL;
  uint8 data = 0;
  uint32 slave_id = 0;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id index 0 */
  err_flag |= pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  switch (reset_source)
  {
     case PM_PON_RESET_SOURCE_KPDPWR:
       reset_reg = &pon_kpdpwr_reg;
       break;

     case PM_PON_RESET_SOURCE_RESIN:
       reset_reg = &pon_resin_reg;
       break;

     case PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR:
       reset_reg = &pon_resin_and_kpdpwr_reg;
       break;

     case PM_PON_RESET_SOURCE_GP1:
       reset_reg = &pon_gp1_reg;
       break;

     case PM_PON_RESET_SOURCE_GP2:
       reset_reg = &pon_gp2_reg;
       break;

     default:
       return PM_ERR_FLAG__PAR_OUT_OF_RANGE; 
  }

  data = (on_off == PM_ON) ? 0xFF : 0;

  err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, data, 0);
 

  return err_flag;
}




pm_err_flag_type
pm_pon_stage3_reset_source_cfg(uint32 pmic_device_index,
                               pm_pon_reset_source_type reset_source,
                               uint32 s3_timer)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 s3_timer_id = 0;
  uint32 slave_id = 0;

  if (s3_timer > pon_s3_timer_val[pon_s3_timer_arr_size - 1])
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (reset_source > PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id index 0 */
  err_flag |= pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  /* Set Stage 3 reset source */
  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_RESET_S3_SRC_ADDR,  
                                          PMIO_PON_RESET_S3_SRC_RMSK, reset_source, 0);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  /* Calc S3 timer id. Get the upper limit if a value falls in between */
  s3_timer_id = pm_utils_get_upper_idx(s3_timer, pon_s3_timer_val, pon_s3_timer_arr_size);

  /*Unlock Before Writing to the secure register*/
  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_SEC_ACCESS_ADDR, PMIO_PON_SEC_ACCESS_RMSK, 0xA5, 0);
  if(err_flag != PM_ERR_FLAG__SUCCESS) 
  {
     return err_flag;
  }

  /* Set Stage 3 reset timer */
  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_RESET_S3_TIMER_ADDR,  
                                          PMIO_PON_RESET_S3_TIMER_RMSK, s3_timer_id, 0);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  return err_flag;
}




//Applicable only for PON GEN2 
pm_err_flag_type
pm_pon_get_fsm_current_state(uint8 pmic_device_index, pm_pon_fsm_status_type *pon_fsm_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  pm_register_data_type fsm_status_val = 0x00;


  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if (  (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_type     == PM_HW_MODULE_PON) && 
        (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  <  PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY) ) 
  {
     return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  
  }

  if (pon_fsm_status == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_GEN2_FSM_STATUS_ADDR, &fsm_status_val, 0);

  *pon_fsm_status = (pm_pon_fsm_status_type)fsm_status_val & PMIO_PON_GEN2_FSM_STATUS_BMSK;  
  
  return err_flag;
}




//Applicable for both PON GEN1 and GEN2 peripherals. Added needed update
pm_err_flag_type
pm_pon_get_pon_reason(uint32 pmic_device_index, pm_pon_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type pon_reg_addr = 0x00;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
     pon_reg_addr = PMIO_PON_PON_REASON1_ADDR;
  }
  else if ( (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )   ||   //GEN2
            (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_SECONDARY) )
  {
     pon_reg_addr = PMIO_PON_GEN2_PON_REASON1_ADDR;
  }
  else
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  err_flag = pm_comm_read_byte(slave_id, pon_reg_addr, (uint8*)reason, 0);

  return err_flag;
}





pm_err_flag_type
pm_pon_get_poff_reason(uint32 pmic_device_index, pm_pon_poff_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type poff_reg_addr = 0x00;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
     poff_reg_addr = PMIO_PON_POFF_REASON1_ADDR;
  }
  else if ( (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )   ||   //GEN2
            (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_SECONDARY) )
  {
     poff_reg_addr = PMIO_PON_GEN2_POFF_REASON1_ADDR;
  }
  else
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  err_flag = pm_comm_read_byte_array(slave_id, poff_reg_addr, 2, (uint8*)reason, 0);

  return err_flag;
}





pm_err_flag_type
pm_pon_get_warm_reset_reason(uint32 pmic_device_index, pm_pon_warm_reset_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type warm_reset_reason_reg_addr = 0x00;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
     warm_reset_reason_reg_addr = PMIO_PON_WARM_RESET_REASON1_ADDR;
  }
  else if ( (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )   ||   //GEN2
            (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_SECONDARY) )
  {
     warm_reset_reason_reg_addr = PMIO_PON_GEN2_WARM_RESET_REASON1_ADDR;
  }
  else
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  err_flag = pm_comm_read_byte_array(slave_id, warm_reset_reason_reg_addr, 2, (uint8*)reason, 0);

  return err_flag;
}




pm_err_flag_type
pm_pon_get_soft_reset_reason(uint32 pmic_device_index, pm_pon_soft_reset_reason_type *reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type soft_reset_reason_reg_addr = 0x00;
  uint32 slave_id = 0;

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
     soft_reset_reason_reg_addr = PMIO_PON_SOFT_RESET_REASON1_ADDR;
  }
  else if ( (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )   ||   //GEN2
            (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_SECONDARY) )
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }
  else
  {
     err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  err_flag = pm_comm_read_byte_array(slave_id, soft_reset_reason_reg_addr, 2, (uint8*)reason, 0);

  return err_flag;
}




//Applicable only for PON GEN2 
pm_err_flag_type 
pm_pon_get_on_reason(uint32 pmic_device_index, pm_pon_on_state_reason_type* reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }


  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_GEN2_ON_REASON_ADDR, (uint8*)reason, 0);

  return err_flag;
}




//Applicable only for PON GEN2
pm_err_flag_type 
pm_pon_get_off_reason(uint32 pmic_device_index, pm_pon_off_state_reason_type* reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }


  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_GEN2_OFF_REASON_ADDR, (uint8*)reason, 0);
  
  return err_flag;
}




//Applicable only for PON GEN2
pm_err_flag_type 
pm_pon_get_fault_reason(uint32 pmic_device_index, pm_pon_fault_state_reason_type* reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  if (reason == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte_array(slave_id, PMIO_PON_GEN2_FAULT_REASON1_ADDR, 2, (uint8*)reason, 0);

  return err_flag;
}




//Applicable only for PON GEN2
pm_err_flag_type 
pm_pon_get_stage3_reset_reason(uint32 pmic_device_index, pm_pon_stage3_reset_reason_type* reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )
  {
      return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED; 
  }

  if (reason == NULL)
  {
    return err_flag = PM_ERR_FLAG__INVALID_POINTER;
  }

  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag =  PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte(slave_id, PMIO_PON_GEN2_S3_RESET_REASON_ADDR, (uint8*)reason, 0);

  return err_flag;
}




pm_err_flag_type
pm_pon_get_all_pon_reasons(uint32 pmic_device_index, uint64 *pon_reasons)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if (pon_reasons == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  /* Get PMIC device Primary slave id value since PON module is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON )  //GEN1
  {
        err_flag = pm_comm_read_byte_array(slave_id, PMIO_PON_PON_REASON1_ADDR, 8, (uint8*) pon_reasons, 0);
  }
  else if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  >= PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )    //GEN2
  {
      err_flag |= pm_comm_read_byte_array(slave_id, PMIO_PON_GEN2_PON_REASON1_ADDR, 8, (uint8*) pon_reasons, 0);
  }

  return err_flag;
}



//Applicable only for PON GEN2
pm_err_flag_type
pm_pon_get_fault_reasons(uint32 pmic_device_index, uint64* fault_reasons)  
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;

  if (fault_reasons == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  < PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )    //GEN2
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  /* Get PMIC device Primary slave id value since PON module is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag |= pm_comm_read_byte_array(slave_id, PMIO_PON_GEN2_FAULT_REASON1_ADDR, 4, (uint8*) fault_reasons, 0);
  
  return err_flag;
  }





pm_err_flag_type
pm_pon_debounce_ctl(uint32 pmic_device_index, uint32 time_delay)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8 debounce_time_id = 0;
  uint8 mask = PMIO_PON_DEBOUNCE_CTL_DEBOUNCE_BMSK;

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }


  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON ) //GEN1
  {
     if (time_delay > pon_debounce_time_val[pon_debounce_time_arr_size - 1])
     {
       return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
     }

     /* Calc Debounce time id. Get the upper limit if a value falls in between */
     debounce_time_id = pm_utils_get_upper_idx(time_delay, pon_debounce_time_val, pon_debounce_time_arr_size);
     mask = PMIO_PON_DEBOUNCE_CTL_DEBOUNCE_BMSK;
  }
  else if ( (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )   ||   //GEN2
            (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  == PM_HW_MODULE_PON_LV_PON_GEN2_SECONDARY) )
  {
     if (time_delay > pon_gen2_debounce_time_val[pon_gen2_debounce_time_arr_size - 1])
     {
       return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
     }

  /* Calc Debounce time id. Get the upper limit if a value falls in between */
     debounce_time_id = pm_utils_get_upper_idx(time_delay, pon_gen2_debounce_time_val, pon_gen2_debounce_time_arr_size);
     mask = PMIO_PON_GEN2_DEBOUNCE_CTL_DEBOUNCE_BMSK;
  }
  else
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;  //Unkown PON peripheral
  }

  err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_DEBOUNCE_CTL_ADDR, mask, debounce_time_id, 0);

   /* Requires 5 sleep clock cycles of delay */
   pm_busy_wait (150);

  return err_flag;
}




pm_err_flag_type
pm_pon_irq_enable(uint32 pmic_device_index, pm_pon_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1<<irq;
  
  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if (enable)
  {
    err_flag = pm_comm_write_byte(slave_id, PMIO_PON_INT_EN_SET_ADDR, mask, 0);
  }
  else
  {
    err_flag = pm_comm_write_byte(slave_id, PMIO_PON_INT_EN_CLR_ADDR, mask, 0);
  }
    
  return err_flag;
}




pm_err_flag_type
pm_pon_irq_clear(uint32  pmic_device_index, pm_pon_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1<<irq;
  
  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_write_byte(slave_id, PMIO_PON_INT_LATCHED_CLR_ADDR, mask, 0);
    
  return err_flag;
}




pm_err_flag_type
pm_pon_irq_set_trigger(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1<<irq;
  uint8 set_type = 0;
  uint8 polarity_high = 0;
  uint8 polarity_low = 0;
  
  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }
    
  switch (trigger)
  {
  case PM_IRQ_TRIGGER_ACTIVE_LOW:
    set_type = 0x00;
    polarity_high = 0x00;
    polarity_low = 0xFF;
    break;
  case PM_IRQ_TRIGGER_ACTIVE_HIGH:
    set_type = 0x00;
    polarity_high = 0xFF;
    polarity_low = 0x00;
    break;
  case PM_IRQ_TRIGGER_RISING_EDGE:
    set_type = 0xFF;
    polarity_high = 0xFF;
    polarity_low = 0x00;
    break;
  case PM_IRQ_TRIGGER_FALLING_EDGE:
    set_type = 0xFF;
    polarity_high = 0x00;
    polarity_low = 0xFF;
    break;
  case PM_IRQ_TRIGGER_DUAL_EDGE:
    set_type = 0xFF;
    polarity_high = 0xFF;
    polarity_low = 0xFF;
    break;
  default:
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_INT_SET_TYPE_ADDR, mask, set_type, 0);
  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_INT_POLARITY_HIGH_ADDR, mask, polarity_high, 0);
  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_INT_POLARITY_LOW_ADDR, mask, polarity_low, 0);
    
  return err_flag;
}




pm_err_flag_type
pm_pon_irq_status(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1<<irq;
  uint8 data = 0;
  
  if (status == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }
  
  if (irq >= PM_PON_IRQ_INVALID)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  switch (type)
  {
  case PM_IRQ_STATUS_RT:
    err_flag = pm_comm_read_byte(slave_id, PMIO_PON_INT_RT_STS_ADDR, &data, 0);
    break;
  case PM_IRQ_STATUS_LATCHED:
    err_flag = pm_comm_read_byte(slave_id, PMIO_PON_INT_LATCHED_STS_ADDR, &data, 0);
    break;
  case PM_IRQ_STATUS_PENDING:
    err_flag = pm_comm_read_byte(slave_id, PMIO_PON_INT_PENDING_STS_ADDR, &data, 0);
    break;
  default:
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  if(err_flag == PM_ERR_FLAG__SUCCESS)
  {
    data = data & mask;
  }

  *status = data ? TRUE : FALSE;
    
  return err_flag;
}




pm_err_flag_type
pm_pon_config_uvlo(uint32 pmic_device_index, uint32 uvlo_thresh_voltage_in_mv, uint32 uvlo_hyst_voltage_in_mv, boolean uvlo_enable)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;

  if (pmic_device_index > PMIC_A_DEVICE_ID) 
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  < PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY )
  {
     err_flag |= pm_pon_gen1_config_uvlo(pmic_device_index, uvlo_thresh_voltage_in_mv, uvlo_hyst_voltage_in_mv);
  }
  else if ( pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  >= PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY) 
  {
     err_flag |= pm_pon_gen2_config_uvlo(pmic_device_index, uvlo_thresh_voltage_in_mv, uvlo_hyst_voltage_in_mv, uvlo_enable);
  }
  else
  {
     return err_flag |= PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}






//Applicable only for PON GEN1
pm_err_flag_type
pm_pon_gen1_config_uvlo(uint32 pmic_device_index, uint32 uvlo_thresh_voltage_in_mv, uint32 hyst_voltage_in_mv)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint32             data_rising_volt = 0;
  uint8              data_hyst_volt = 0;
  

  if (  (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_type     == PM_HW_MODULE_PON) && 
        (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  >= PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY) )
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED; 
  }

  if (pmic_device_index > PMIC_A_DEVICE_ID) 
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /*Value out of Range check 
	  Hyst_Voltage Range
		  Vhyst = hysteresis voltage set with bits[2:1] 
		  00: Traditional UVLO hysteresis setting (175mV nominal)
		  01: Increase UVLO hysteresis to 300mV (+125mV from 00 setting)
		  10: Increase UVLO hysteresis to 425mV (+250mV from 00 setting)
		  11: Same as 00 setting
  */

  if( (hyst_voltage_in_mv < 175) || (hyst_voltage_in_mv > 425) )
  {
	err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;    
	return err_flag;
  }
  
  else if( (hyst_voltage_in_mv >= 175) && (hyst_voltage_in_mv <= 237) )
  {
	data_hyst_volt = 0x00;
  }
  else if( (hyst_voltage_in_mv > 237) && (hyst_voltage_in_mv <= 362) )
  {
	data_hyst_volt = 0x02;
  }
  else if( (hyst_voltage_in_mv > 362) )
  {
	data_hyst_volt = 0x04;
  }
  /*Value out of Range check   
      Rising Voltage Threshold Range calculation
		  Rising threshold = 1675 + (X *5 0) 
		  X = value of bits[7:3] = 0 : 31
		  Falling threshold = Rising Threshold - Vhyst 
		  Falling threshold Absolute minimum voltage  = 2450mV ,   vHyst_max = 425
		  Rising threshold Min = Falling threshold AMV + vHyst_max = 2450 + 425 = 2875
		  Rising threshold Max = 1675 + (31 * 50) = 3225
		  Hence Range of X = 24 to 31
  */
  if((uvlo_thresh_voltage_in_mv < 2875) || (uvlo_thresh_voltage_in_mv > 3225) )
  {
    err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;    
	return err_flag;
  }
  uvlo_thresh_voltage_in_mv = uvlo_thresh_voltage_in_mv - 1675;
  data_rising_volt = ((uvlo_thresh_voltage_in_mv + 25 )/ 50) ;
  data_rising_volt = data_rising_volt << 3;
  
  // Unlock for writing   
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_SEC_ACCESS_ADDR, PMIO_PON_SEC_ACCESS_RMSK, 0xA5, 0);
  if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag; 
  // Write Hyst Voltage
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_UVLO_VOLT_HYST_ADDR, PMIO_PON_UVLO_VOLT_HYST_RMSK, data_hyst_volt, 0); 
  if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;
  
  // Unlock for writing   
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_SEC_ACCESS_ADDR, PMIO_PON_SEC_ACCESS_RMSK, 0xA5, 0);
  if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag; 
  //Write Rising threshold voltage
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_UVLO_THRESH_ADDR , PMIO_PON_UVLO_THRESH_RMSK, data_rising_volt, 0);
  if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag;
  
  return err_flag;
}



//Applicable only for PON GEN2 (PON_UVLO_CTL : 0x00884)
pm_err_flag_type
pm_pon_gen2_config_uvlo(uint8 pmic_device_index, uint32 uvlo_thresh_voltage_in_mv, uint32 uvlo_hyst_voltage_in_mv, boolean uvlo_enable)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 uvlo_thresh_data = 0;
  uint8 uvlo_hyst_data   = 0;
  uint8 enable_data = 0;
  uint8 reg_data = 0;
  

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  if (  (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_type     == PM_HW_MODULE_PON) && 
        (pm_pon_data_arr[pmic_device_index].preph_info.peripheral_subtype  < PM_HW_MODULE_PON_LV_PON_GEN2_PRIMARY) )
  {
     return err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED; 
  }

  //Input Parameter check
  if (pmic_device_index > PMIC_A_DEVICE_ID) //Only Primary PMIC is supported for now
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  
  if( (uvlo_hyst_voltage_in_mv < 150) || (uvlo_hyst_voltage_in_mv > 600) )
  {
        err_flag = PM_ERR_FLAG__PAR_OUT_OF_RANGE;    
        return err_flag;
  }

  if( (uvlo_thresh_voltage_in_mv < pon_gen2_uvlo_threshold_val[0]) || 
      (uvlo_thresh_voltage_in_mv > pon_gen2_uvlo_threshold_val[pon_gen2_uvlo_threshold_val_arr_size - 1]) )
  {
        err_flag = PM_ERR_FLAG__PAR_OUT_OF_RANGE;    
        return err_flag;
  }


  //Calculate UVLO HYST
  uvlo_hyst_data = pm_utils_get_upper_idx(uvlo_hyst_voltage_in_mv, pon_gen2_uvlo_hyst_val, pon_gen2_uvlo_hyst_val_arr_size);

  //Calculate UVLO Treshold
  uvlo_thresh_data = pm_utils_get_upper_idx(uvlo_thresh_voltage_in_mv, pon_gen2_uvlo_threshold_val, pon_gen2_uvlo_threshold_val_arr_size);
  
  //Convert uvlo_enable to register code
  enable_data = uvlo_enable ? 0x80: 0x0;
  
  //combine into one
  reg_data = enable_data | (uvlo_hyst_data << PMIO_PON_GEN2_UVLO_VOLT_HYST_SHFT) | uvlo_thresh_data;

  //Configuration
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_SEC_ACCESS_ADDR, PMIO_PON_SEC_ACCESS_RMSK, 0xA5, 0); // Unlock for writing
  if(err_flag != PM_ERR_FLAG__SUCCESS) return err_flag; 
  err_flag = pm_comm_write_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_GEN2_UVLO_VOLT_CLT_ADDR, reg_data, 0); // Write to register

  return err_flag;
}



pm_err_flag_type
pm_pon_warm_reset_status(uint32 pmic_device_index, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint8              data = 0;

  if (status == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  //PMICs are Not currently supported in RUMI
  uint8 pmic_index = (uint8) PMIC_A_SLAVEID_PRIM / 2;
  pm_model_type pmic_model = PMIC_IS_INVALID;
  pmic_model = pm_get_pmic_model(pmic_index);
  if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
  {
      return err_flag = PM_ERR_FLAG__SUCCESS; //Temp Fix:  PMICs are Not currently supported in RUMI
  }
  
  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Read the spare register to know if the WARM RESET occured */
  err_flag = pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_DVDD_RB_SPARE_ADDR, &data, 0);

  if(err_flag == PM_ERR_FLAG__SUCCESS)
  {
    data = data & PON_DVDD_RB_SPARE_WARM_RESET_MASK;
  }

  *status = data ? TRUE : FALSE;

  return err_flag;
}




pm_err_flag_type
pm_pon_warm_reset_status_clear(uint32 pmic_device_index)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint8              data = 0;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  /* Writing 0x00 to the spare register to clear the Warm Reset status */
  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_DVDD_RB_SPARE_ADDR, PON_DVDD_RB_SPARE_WARM_RESET_MASK, data, 0);

  return err_flag;
}




pm_err_flag_type 
pm_pon_pbl_get_status(uint32  pmic_device_index, pm_pon_pbl_status_type pbl_status, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint32 slave_id = 0;
  uint8  data = 0;

  if (status == NULL)
  {
    return PM_ERR_FLAG__INVALID_POINTER;
  }
  
  if (pbl_status >= PM_PON_PBL_STATUS_INVALID)
  {
    return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Get PMIC device Primary slave id value since PON module
     is on the Primary slave id */
  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }
  
  if(pbl_status ==  PM_PON_PBL_DVDD_RB_OCCURRED)
  {
    err_flag = pm_comm_read_byte(slave_id, PMIO_PON_PON_PBL_STATUS_ADDR, &data, 0);
	if(err_flag == PM_ERR_FLAG__SUCCESS)
  {
      data = data & PMIO_PON_PON_PBL_STATUS_DVDD_RB_OCCURRED_BMSK;
    }
  }
  else if(pbl_status ==  PM_PON_PBL_XVDD_RB_OCCURRED) 
  {
    err_flag = pm_comm_read_byte(slave_id, PMIO_PON_PON_PBL_STATUS_ADDR, &data, 0);
	if(err_flag == PM_ERR_FLAG__SUCCESS)
  {
      data = data & PMIO_PON_PON_PBL_STATUS_XVDD_RB_OCCURRED_BMSK;
    }
  }
  *status = data ? TRUE : FALSE;


  return err_flag;
}




pm_err_flag_type
pm_pon_get_spare_reg(uint32 pmic_device_index, pm_pon_spare_reg_type spare_reg, uint8* data_ptr)
{
  pm_err_flag_type	 err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type  spare_register_addr =  0x00;
  
  if ((spare_reg >= PM_PON_SPARE_INVALID) ||
  	  (pmic_device_index > PMIC_A_DEVICE_ID) ||
  	  (!data_ptr))
  {
	return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
	err_flag = pm_pon_init();
	if (err_flag != PM_ERR_FLAG__SUCCESS)
	{
	  return err_flag;
	}
  }

  switch(spare_reg)
  	{
    case PM_PON_PERPH_SPARE:
		 spare_register_addr = PMIO_PON_PERPH_RB_SPARE_ADDR;
	     break;
		 
	case PM_PON_DVDD_SPARE:
		 spare_register_addr = PMIO_PON_DVDD_RB_SPARE_ADDR;
         break;
		 
    case PM_PON_XVDD_SPARE:
		 spare_register_addr = PMIO_PON_XVDD_RB_SPARE_ADDR;
	     break;
		 
	case PM_PON_SOFT_SPARE:
  	     spare_register_addr = PMIO_PON_SOFT_RB_SPARE_ADDR;
		 break;
		 
    default:
         err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  	}

  if(PM_ERR_FLAG__SUCCESS == err_flag)
  	{
      err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, spare_register_addr, data_ptr, 0);
	
  	}

  
  return err_flag;
}


pm_err_flag_type
pm_pon_set_spare_reg(uint32 pmic_device_index, pm_pon_spare_reg_type spare_reg, uint8 set_value, uint8 mask)
{
  pm_err_flag_type	 err_flag = PM_ERR_FLAG__SUCCESS;
  pm_register_address_type  spare_register_addr;

  if ((spare_reg >= PM_PON_SPARE_INVALID) ||
      (pmic_device_index > PMIC_A_DEVICE_ID)||
      (mask > PM_PON_MAX_SPARE_BIT_MASK)
      )
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  switch (spare_reg)
  {
    case PM_PON_PERPH_SPARE:
      spare_register_addr = PMIO_PON_PERPH_RB_SPARE_ADDR;
      break;

    case PM_PON_DVDD_SPARE:
      spare_register_addr = PMIO_PON_DVDD_RB_SPARE_ADDR;
      break;

    case PM_PON_XVDD_SPARE:
      spare_register_addr = PMIO_PON_XVDD_RB_SPARE_ADDR;
      break;

    case PM_PON_SOFT_SPARE:
      spare_register_addr = PMIO_PON_SOFT_RB_SPARE_ADDR;
      break;

    default:
      err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  if (PM_ERR_FLAG__SUCCESS == err_flag)
  {
    err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, spare_register_addr, mask, set_value, 0);

  }

  return err_flag;
}


pm_err_flag_type
pm_pon_trigger_enable_status(uint32 pmic_device_index, pm_pon_trigger_type trigger, boolean *status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;

  uint8 pon_trigger;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  else if (trigger >= PM_PON_TRIGGER_INVALID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  else if (NULL == status)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_PON_TRIGGER_EN_ADDR, &pon_trigger, 0);

  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }

  switch (trigger)
  {
     case PM_PON_TRIGGER_KPDPWR:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_CBLPWR:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_PON1:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_PON1_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_USB_CHG:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_USB_CHG_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_DC_CHG:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_DC_CHG_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_RTC:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_RTC_BMSK) ? TRUE : FALSE;
       break;
     case PM_PON_TRIGGER_SMPL:
       *status = (pon_trigger & PMIO_PON_PON_TRIGGER_EN_SMPL_BMSK) ? TRUE : FALSE;
       break;
     default:
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


pm_err_flag_type 
pm_pon_trigger_enable(uint32 pmic_device_index, pm_pon_trigger_type trigger, boolean enable)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint8 mask, data;

  data = (enable) ? 0xFF : 0x00;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }
  else if (trigger >= PM_PON_TRIGGER_INVALID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  switch (trigger)
  {
     case PM_PON_TRIGGER_KPDPWR:
       mask = PMIO_PON_PON_TRIGGER_EN_KPDPWR_N_BMSK;
       break;
     case PM_PON_TRIGGER_CBLPWR:
       mask = PMIO_PON_PON_TRIGGER_EN_CBLPWR_N_BMSK;
       break;
     case PM_PON_TRIGGER_PON1:
       mask = PMIO_PON_PON_TRIGGER_EN_PON1_BMSK;
       break;
     case PM_PON_TRIGGER_USB_CHG:
       mask = PMIO_PON_PON_TRIGGER_EN_USB_CHG_BMSK;
       break;
     case PM_PON_TRIGGER_DC_CHG:
       mask = PMIO_PON_PON_TRIGGER_EN_DC_CHG_BMSK;
       break;
     case PM_PON_TRIGGER_RTC:
       mask = PMIO_PON_PON_TRIGGER_EN_RTC_BMSK;
       break;
     case PM_PON_TRIGGER_SMPL:
       mask = PMIO_PON_PON_TRIGGER_EN_SMPL_BMSK;
       break;
     default:
       return PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
  }

  /* Requires 3 sleep clock cycles of delay */
  pm_busy_wait(100);

  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_PON_TRIGGER_EN_ADDR, mask, data, 0);

  return err_flag;
}


static pm_err_flag_type pm_pon_get_xvdd_rb(boolean *xvdd_status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;
  uint8             xvdd_rb_spare = 0;

  if (NULL == xvdd_status)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_XVDD_RB_SPARE_ADDR, &xvdd_rb_spare, 0);
  /*if 0 then only xvdd occured*/
  *xvdd_status = (xvdd_rb_spare & 0x1) ? FALSE : TRUE;

  return err_flag;
}


pm_err_flag_type pm_pon_set_xvdd_rb(uint32 pmic_device_index, boolean xvdd_data)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG__SUCCESS;

  pm_register_data_type data = (xvdd_data)? 0xFF : 0x00;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }

  err_flag = pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_XVDD_RB_SPARE_ADDR, 0x1, data, 0);

  return err_flag;
}




pm_err_flag_type
pm_pon_get_reset_config_val(pm_pon_reset_cfg_type pon_reset_cfg, uint8* pon_reset_cfg_val)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

  //Map App level allowed config enums to PON config enums
  switch (pon_reset_cfg)
  {
     case PM_PON_RESET_CFG_WARM_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_WARM_RESET_VAL;
       break;

     case PM_PON_RESET_CFG_NORMAL_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_NORMAL_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_D_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_D_VDD_HARD_RESET_VAL;
       break;
	   
	 case PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_WARM_RESET_THEN_DVDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
       *pon_reset_cfg_val = PON_RESET_CFG_X_VDD_SHUTDOWN_VAL;
       break;

     case PM_PON_RESET_CFG_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_HARD_RESET_VAL;
       break;

    case PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN:
      *pon_reset_cfg_val = PON_RESET_CFG_IMMEDIATE_X_VDD_SHUTDOWN_VAL;
      break;

    case PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
      *pon_reset_cfg_val = PON_RESET_CFG_X_VDD_HARD_RESET_VAL;
      break;

    case PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET:
       *pon_reset_cfg_val = PON_RESET_CFG_WARM_RESET_THEN_XVDD_HARD_RESET_VAL;
       break;

     default:
       err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
       break;
  }

  return err_flag;
}

pm_err_flag_type pm_pon_set_option_bit(uint32 pmic_device_index, pm_pon_option_bit_type cfg_field, boolean cfg_data)
{
  pm_err_flag_type   err_flag       = PM_ERR_FLAG__SUCCESS;
  pm_register_data_type data   = (cfg_data)? 0x01 : 0x00 ;
  pm_register_data_type write_data  = 0;
  pm_register_data_type mask   = 0;
  uint32 read_data = 0;

  if (pmic_device_index > PMIC_A_DEVICE_ID)
  {
    return PM_ERR_FLAG__PAR_OUT_OF_RANGE;
  }

  if (pm_pon_initialized == FALSE)
  {
    err_flag = pm_pon_init();
    if (err_flag != PM_ERR_FLAG__SUCCESS)
    {
      return err_flag;
    }
  }
  
  switch (cfg_field)
  {
    case PM_PON_OPTION_KPDPWR_FEDGE_PON:
        write_data = data << PMIO_PON_OPTION_BIT_KPDPWR_FEDGE_PON_SHFT;
		mask = PMIO_PON_OPTION_BIT_KPDPWR_FEDGE_PON_BMSK;
        break;

    case PM_PON_OPTION_PON1_REDGE_PON:
        write_data = data << PMIO_PON_OPTION_BIT_PON1_REDGE_PON_SHFT;
		mask = PMIO_PON_OPTION_BIT_PON1_REDGE_PON_BMSK;
        break;

    case PM_PON_OPTION_CBLPWR_FEDGE_PON:
        write_data = data << PMIO_PON_OPTION_BIT_CBLPWR_FEDGE_PON_SHFT;
		mask = PMIO_PON_OPTION_BIT_CBLPWR_FEDGE_PON_BMSK;
        break;

    case PM_PON_OPTION_USB_CHG_REDGE_PON:
        write_data = data << PMIO_PON_OPTION_BIT_USB_CHG_REDGE_PON_SHFT;
		mask = PMIO_PON_OPTION_BIT_USB_CHG_REDGE_PON_BMSK;
        break;

    case PM_PON_OPTION_DC_CHG_REDGE_PON:
        write_data = data << PMIO_PON_OPTION_BIT_DC_CHG_REDGE_PON_SHFT;
		mask = PMIO_PON_OPTION_BIT_DC_CHG_REDGE_PON_BMSK;
        break;

    default:
        err_flag = PM_ERR_FLAG__FEATURE_NOT_SUPPORTED;
        break;
  }
  
  if (err_flag != PM_ERR_FLAG__SUCCESS)
  {
    return err_flag;
  }
  
  err_flag |= pm_comm_write_byte_mask(PMIC_A_SLAVEID_PRIM, PMIO_PON_OPTION_BIT_ADDR,mask, write_data, 0);
  
  //Read the data from 0x882 and Write it to 0x881
  err_flag |= pm_comm_read_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_OPTION_BIT_ADDR, (uint8 *)&read_data, 0);
  
  err_flag |= pm_comm_write_byte(PMIC_A_SLAVEID_PRIM, PMIO_PON_TRIGGER_EDGE_CONFIG ,read_data, 0);

  return err_flag;
}


