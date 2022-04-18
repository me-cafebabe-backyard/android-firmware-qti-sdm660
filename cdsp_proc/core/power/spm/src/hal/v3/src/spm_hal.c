/*==============================================================================
  FILE:         spm_hal.c

  OVERVIEW:     This file implements HAL APIs exposed to SPM driver and performs
                actual HW register read and write.

  DEPENDENCIES: The implementation can be SAW/SPM version specific.
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/v3/src/spm_hal.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#include "spm_hal.h"
#include "spm_hwio.h"

/*===========================================================================
 *                            INTERNAL VARIABLES
 *==========================================================================*/
#ifndef SPM_LITE
/**
 * @brief Volatile variable which will be used to read back SPM register 
 *        being written to. This is to ensure that write value actually got 
 *        propagated to HW.
 */
volatile uint32 spm_hal_read_back_val;
#endif

/*==========================================================================
 *                             INTERNAL MACROS
 *=========================================================================*/

/**
 * @brief Size of each command sequence register in byte.
 */
#define SPM_HAL_CMD_SEQ_REG_SIZE  4

/**
 * @brief Size of each command in bytes.
 */
#define SPM_HAL_CMD_SIZE  1

/**
 * @brief Number of commands per register
 */
#define SPM_HAL_CMDS_PER_REG  (SPM_HAL_CMD_SEQ_REG_SIZE/SPM_HAL_CMD_SIZE)

/**
 * @brief Macros to create bit mask, set and clear bit in a mask
 */
#define MAKE_MASK32(bit_pos)    ((uint32)1 << (bit_pos % 32))
#define BIT_SET32(val, bit_pos) (val | (MAKE_MASK32(bit_pos)))
#define BIT_CLR32(val, bit_pos) (val & ~(MAKE_MASK32(bit_pos)))

/**
 * @brief Macro to readback an SPM register.
 */
#define SPM_HAL_READBACK_REG(base, reg) \
  (spm_hal_read_back_val = SPM_HWIO_IN(base, reg))

/*===========================================================================
 *                            EXTERNAL FUNCTIONS
 *==========================================================================*/

/*
 * spm_hal_enable
 */
void spm_hal_enable(uint8 *spm_base, uint8 enable)
{
  enable = (0 != enable) ? 1 : 0;
  SPM_HWIO_OUTF(spm_base, SPM_CTL, SPM_EN, enable);
}

/*
 * spm_hal_config_clk_div
 */
void spm_hal_config_clk_div(uint8* spm_base, uint8 clk_div)
{
  SPM_HWIO_OUTF(spm_base, CFG, CLK_DIV, clk_div);
}

/*
 * spm_hal_config_wakeup
 */
void spm_hal_config_wakeup(uint8* spm_base, uint8 wakeup_config)
{
  SPM_HWIO_OUTF(spm_base, SPM_CTL, WAKEUP_CONFIG, wakeup_config);
}

/*
 * spm_hal_config_delays
 */
void spm_hal_config_delays(uint8   *spm_base,
                           uint16  delay1,
                           uint16  delay2, 
                           uint16  delay3)
{
  uint32 mask = SPM_HWIO_FMSK(SPM_DLY, DLY1) |
                SPM_HWIO_FMSK(SPM_DLY, DLY2) |
                SPM_HWIO_FMSK(SPM_DLY, DLY3);

  uint32 val = SPM_HWIO_FVAL(SPM_DLY, DLY1, delay1) |
               SPM_HWIO_FVAL(SPM_DLY, DLY2, delay2) |
               SPM_HWIO_FVAL(SPM_DLY, DLY3, delay3);

  SPM_HWIO_OUTM(spm_base, SPM_DLY, mask, val);
}

/*
 * spm_hal_config_lpm_ctl
 */
void spm_hal_config_lpm_ctl(uint8* spm_base, uint32 ctl_val)
{
  /* Mask of mode specific fields */
  uint32 mask = ((SPM_HWIO_FMSK(SPM_CTL, ISAR)) | 
                 (SPM_HWIO_FMSK(SPM_CTL, SPM_START_ADR)) |
                 (SPM_HWIO_FMSK(SPM_CTL, SPM_SYS_PC_MODE)) | 
                 (SPM_HWIO_FMSK(SPM_CTL, SPM_SYS_RET_MODE))|
                 (SPM_HWIO_FMSK(SPM_CTL, EVENT_SYNC)));

  SPM_HWIO_OUTM(spm_base, SPM_CTL, mask, ctl_val);
}

/*
 * spm_hal_invalidate_cmd_seqs
 */
void spm_hal_invalidate_cmd_seqs(uint8* spm_base)
{
  const uint32  val       = 0x0F0F0F0F; /* End of sequence commands */
  uint32        i;
  uint32        reg_count = spm_hal_get_num_cmd_seq_reg(spm_base);

  for(i = 0; i < reg_count; i++)
    SPM_HWIO_OUTI(spm_base, SPM_SLP_SEQ_ENTRY_n, i, val);
}

/*
 * spm_hal_copy_cmd_seq
 */
uint16 spm_hal_copy_cmd_seq(uint8   *spm_base,
                            uint16  start_adr,
                            uint8*  cmds,
                            uint16  size)
{
  uint32 mask         = 0;
  uint32 val          = 0;
  uint32 cmd_mask     = 0;
  uint32 cmd_shift    = 0;
  uint16 cmds_copied  = 0;
  uint16 i            = 0;
  uint16 addr         = start_adr;
  uint16 max_cmds     = SPM_HWIO_INF(spm_base, ID, NUM_SPM_ENTRY) * SPM_HAL_CMDS_PER_REG;

  if((start_adr >= max_cmds) || ((start_adr + size) > max_cmds))
  {
    return cmds_copied;
  }

  for(i = 0; i < size; i++, addr++)
  {
    switch(addr % SPM_HAL_CMDS_PER_REG)
    {
      case 0:
        if(0 != cmds_copied)
        {
          /* We hit register boundary - perform actual write if we processed
           * any command . */
          SPM_HWIO_OUTMI(spm_base, SPM_SLP_SEQ_ENTRY_n, 
                          ((addr-1)/SPM_HAL_CMDS_PER_REG), mask, val);
          mask = val = 0;
        }
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD0);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD0);
        break;

      case 1:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD1);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD1);
        break;

      case 2:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD2);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD2);
        break;

      case 3:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD3);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD3);
        break;
    }

    mask |= cmd_mask;
    val |= (cmds[i] << cmd_shift);
    cmds_copied++;
  }
  
  SPM_HWIO_OUTMI(spm_base, SPM_SLP_SEQ_ENTRY_n, 
                  ((addr-1)/SPM_HAL_CMDS_PER_REG), mask, val);

  return cmds_copied;
}

/*
 * spm_hal_get_num_cmd_seq_reg
 */
uint16 spm_hal_get_num_cmd_seq_reg(uint8* spm_base)
{
  return (SPM_HWIO_INF(spm_base, ID, NUM_SPM_ENTRY));
}

/*=======================================================================
 *       GLOBAL FUNCTIONS NEEDED FOR DYNAMIC SEQUENCE UPDATING
 *======================================================================*/
#ifdef SPM_DYNAMIC_SEQ
/*
 * spm_hal_config_cmd_at_idx
 */
void spm_hal_config_cmd_at_idx(uint8  *spm_base,
                               uint16 cmd_index,
                               uint8  cmd)
{
  uint8  cmd_offset;
  uint16 reg_index = cmd_index / SPM_HAL_CMDS_PER_REG;

  if( reg_index >= spm_hal_get_num_cmd_seq_reg(spm_base) )
    return;

  cmd_offset = cmd_index % SPM_HAL_CMDS_PER_REG;

  switch(cmd_offset)
  {
    case 0:
      SPM_HWIO_OUTFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD0, cmd);
      break;
    case 1:
      SPM_HWIO_OUTFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD1, cmd);
      break;
    case 2:
      SPM_HWIO_OUTFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD2, cmd);
      break;
    case 3:
      SPM_HWIO_OUTFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD3, cmd);
      break;
    default:
      //May want to error here if >4 commands per register are supported
      break;
  }
}
#endif

/*=======================================================================
 *              GLOBAL FUNCTIONS NOT NEEDED IN LITE VERSION
 *======================================================================*/
#ifndef SPM_LITE
/*
 * spm_hal_reset
 */
void spm_hal_reset(uint8* spm_base)
{
  SPM_HWIO_OUT(spm_base, RST, 0x1);
}

/*
 * spm_hal_get_saw_id
 */
uint32 spm_hal_get_saw_id(uint8* spm_base)
{
  return (SPM_HWIO_IN(spm_base, ID));
}

/*
 * spm_hal_get_status
 */
uint32 spm_hal_get_status(uint8* spm_base)
{
  return (SPM_HWIO_IN(spm_base, SPM_STS));
}

/*
 * spm_hal_config_index_delay
 */
void spm_hal_config_index_delay(uint8   *spm_base,
                                uint8   delay_index,
                                uint16  delay)
{
  switch(delay_index)
  {
    case 1:
      SPM_HWIO_OUTF(spm_base, SPM_DLY, DLY1, delay);
      break;
    case 2:
      SPM_HWIO_OUTF(spm_base, SPM_DLY, DLY2, delay);
      break;
    case 3:
      SPM_HWIO_OUTF(spm_base, SPM_DLY, DLY3, delay);
      break;
    default:
      /* May be error fatal but need a proper macro that works in all
       * environment without losing context. */
      break;
  }
}

/*
 * spm_hal_get_last_cmd_addr
 */
uint16 spm_hal_get_last_cmd_addr(uint8* spm_base)
{
  return (SPM_HWIO_INF(spm_base, SPM_STS, SPM_CMD_ADDR));
}

/*
 * spm_hal_config_cmd_seq
 */
void spm_hal_config_cmd_seq(uint8 *spm_base, uint8 reg_index, uint32 val)
{
  if( reg_index >= spm_hal_get_num_cmd_seq_reg(spm_base) )
    return;

  SPM_HWIO_OUTI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, val);
}

/*
 * spm_hal_get_num_cmds_in_reg
 */
uint8 spm_hal_get_num_cmds_in_reg(void)
{
  return SPM_HAL_CMDS_PER_REG;
}

/*
 * spm_hal_get_num_regs_required
 */
uint16 spm_hal_get_num_regs_required(uint32 total_cmds)
{
  uint32 reg_req = (total_cmds + SPM_HAL_CMDS_PER_REG - 1) / 
                   SPM_HAL_CMDS_PER_REG;

  return reg_req;
}

/*
 * spm_hal_config_event
 */
void spm_hal_config_event(uint8* spm_base, uint8 sync, uint8 event_num)
{
  uint32 sync_val = SPM_HWIO_INF(spm_base, SPM_CTL, EVENT_SYNC);
  sync_val = sync ? 
             BIT_SET32(sync_val, event_num) : BIT_CLR32(sync_val, event_num);

  SPM_HWIO_OUTF(spm_base, SPM_CTL, EVENT_SYNC, sync_val);
}

/*
 * spm_hal_config_seq_start_addr
 */
void spm_hal_config_seq_start_addr(uint8 *spm_base, uint16 start_addr)
{
  SPM_HWIO_OUTF(spm_base, SPM_CTL, SPM_START_ADR, start_addr);
}

/*
 * spm_hal_config_isar
 */
void spm_hal_config_isar(uint8* spm_base, uint8 isar)
{
  isar = (0 != isar) ? 1 : 0;
  SPM_HWIO_OUTF(spm_base, SPM_CTL, ISAR, isar);
}

#endif /* SPM_LITE */

/*===========================================================================
 *                           TARGET PMIC SUPPORTED
 *==========================================================================*/
/*
 * spm_hal_get_vctl
 */
uint32 spm_hal_get_vctl(uint8* spm_base)
{
#ifdef SPM_TARGET_PMIC_SUPPORTED
  return (SPM_HWIO_INF(spm_base, VCTL, PMIC_DATA));
#else
  return 0;
#endif
}

/*
 * spm_hal_config_pmic
 */
void spm_hal_config_pmic(uint8  *spm_base,
                         uint8  index,
                         uint8  addr_index,
                         uint16 data,
                         uint8  size,
                         uint8  delay)
{
#ifdef SPM_TARGET_PMIC_SUPPORTED
  uint32 mask, val;

  if(index >= SPM_HWIO_INF(spm_base, ID, NUM_PMIC_DATA))
    return;

  mask = ((SPM_HWIO_FMSK(SPM_PMIC_DATA_n, ADR_IDX)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, DATA)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, SIZE)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, DLY)));

  val = ((SPM_HWIO_FVAL(SPM_PMIC_DATA_n, ADR_IDX, addr_index)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, DATA, data)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, SIZE, size)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, DLY, delay)));
  
  SPM_HWIO_OUTMI(spm_base, SPM_PMIC_DATA_n, index, mask, val);
#endif
}

