#ifndef _SPM_HAL_H_
#define _SPM_HAL_H_
/*==============================================================================
  FILE:         spm_hal.h

  OVERVIEW:     This file provides Hardware layer (HAL) APIs for SPM driver. 
                SPM driver should use these APIs to perform actual IO on SPM
                HW block.

  DEPENDENCIES: This interface is specific to SAW/SPM version.
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/v3/inc/spm_hal.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"
#include "spm_hwio.h"

/*========================================================================
 *                           HAL SPECIFIC MACROS
 *========================================================================*/

/**
 * @brief Macros to indicate invalid indices for different purposes.
 */
#define SPM_HAL_INVALID_INDEX           (uint16)(-1)
#define SPM_HAL_INVALID_MODE_INDEX      SPM_HAL_INVALID_INDEX
#define SPM_HAL_INVALID_SEQ_START_ADR   SPM_HAL_INVALID_INDEX

/**
 * @brief Macro that returns mask representing Inhibit Start Address Reset 
 *        (ISAR) field. 
 *
 * This is used by target files for the modes that should not reset 
 * start address.
 */
#define SPM_HAL_ISAR_SET (1 << (SPM_HWIO_SHFT(SPM_CTL, ISAR)))

/**
 * @brief Macro to create mask having SPM_SYS_PC|RET_MODE set. 
 *
 * This is used by target files for the modes that requires above bit set.
 */
#define SPM_HAL_SYS_PC_MODE_SET \
        (1 << (SPM_HWIO_SHFT(SPM_CTL, SPM_SYS_PC_MODE)))

#define SPM_HAL_SYS_RET_MODE_SET \
        (1 << (SPM_HWIO_SHFT(SPM_CTL, SPM_SYS_RET_MODE)))
/**
 * @brief Macro to create mask that has SPM_START_ADR field set to input 
 *        value.
 */
#define SPM_HAL_START_ADR_SET(addr) \
        (((addr) << SPM_HWIO_SHFT(SPM_CTL, SPM_START_ADR)) & \
        (SPM_HWIO_FMSK(SPM_CTL, SPM_START_ADR)))

/**
 * @brief Macros to generate different commands in SPM sequence.
 *
 * The macros are defined as per encoding specified in SAW SWI for
 * this version.
 *
 *   SPM_HAL_SEQ_PWR_CTL_CMD - Toggle power control if number of power control
 *                             toggles handled by SPM is <= 16.
 *
 *   SPM_HAL_SEQ_PWR_CTLX_CMD - Toggle power control if number of power control
 *                              toggles handled by SPM is > 16 (extended).
 *
 *   SPM_HAL_SEQ_PMIC_CMD - PMIC operation.
 *   
 *   SPM_HAL_SEQ_EVENT_CMD - Wait for event.
 *
 *   SPM_HAL_SEQ_DLY_CMD - SPM delay command.
 *
 *   SPM_HAL_SEQ_SLEEP_CMD - Sleep with or without RPM handshake.
 *
 *   SPM_HAL_SEQ_END_CMD - End of SPM command sequence.
 */
#define SPM_HAL_SEQ_PWR_CTL_CMD(pwr_ctl, delay)   ((((pwr_ctl) & 0xF) << 4) | (((delay) & 0x7) << 1))
 
#define SPM_HAL_SEQ_PWR_CTLX_CMD(pwr_ctl, delay)  ((((pwr_ctl) & 0xF) << 4) | (((pwr_ctl) & 0x10) >> 1) | \
                                                     (((delay) & 0x3) << 1))

#define SPM_HAL_SEQ_PMIC_CMD(pmic_val)            ((((pmic_val) & 0x7) << 4) | 0x1)

#define SPM_HAL_SEQ_EVENT_CMD(event)              ((((event) & 0xF) << 4) | 0xB)

#define SPM_HAL_SEQ_DLY_CMD(delay_index)          ((((delay_index) & 0x7) << 4) | 0xF)

#define SPM_HAL_SEQ_SLEEP_CMD(rpm_hs)             ((rpm_hs) ? (0x7) : (0x3))

#define SPM_HAL_SEQ_END_CMD (0xF)

/*========================================================================
 *                             GLOBAL FUNCTIONS
 *========================================================================*/
/**
 * @brief Enables or disables SPM.
 *
 * @param spm_base: SPM's base address.
 * @param enable: Value to indicate if SPM needs to be enabled or 
 *                disabled (0 Disable, 1 Enable)
 */
void spm_hal_enable(uint8 *spm_base, uint8 enable);

/**
 * @brief Resets the SPM instance.
 *
 * @param spm_base: SPM's base address.
 */
void spm_hal_reset(uint8 *spm_base);

/**
 * @brief This function programs the clock divider ratio for the SPM 
 *        reference clock.
 *
 * @param spm_base: SPM instance's base address.
 * @param clk_div: Clock divider ration to be progammed.
 */
void spm_hal_config_clk_div(uint8* spm_base, uint8 clk_div);

/**
 * @brief Returns the content of SAW_ID register for a given SPM instance. 
 *        It can be used to support same functionality differently across
 *        SPM version.
 *
 * @param spm_base: SPM instance's base address.
 * 
 * @return SAW_ID register value.
 */
uint32 spm_hal_get_saw_id(uint8* spm_base);

/**
 * @brief Returns the voltage level currently programmed by AVS. This may be
 *        useful to config restore voltage level.
 * 
 * @param spm_base: SPM instance's base address.
 * 
 * @return Currently programmed voltage level.
 */
uint32 spm_hal_get_vctl(uint8* spm_base);

/**
 * @brief Returns the content of SPM_STS register
 *
 * @param spm_base: SPM instance's base address.
 *
 * @return SAW_STS register.
 */
uint32 spm_hal_get_status(uint8* spm_base);

/**
 * @brief Returns the address of last executed command in sequence.
 *
 * @param spm_base: SPM instance's base address.
 *
 * @return Address of last executed in sequence.
 */
uint16 spm_hal_get_last_cmd_addr(uint8* spm_base);

/**
 * @brief Returns the number of command sequence registers available on 
 *        the given SPM instance.
 *
 * @param spm_base: SPM instance's base address.
 *
 * @return Number of command sequence registers.
 */
uint16 spm_hal_get_num_cmd_seq_reg(uint8* spm_base);

/**
 * @brief Returns max number of commands that can fit in to a command
 *        sequence register.
 *
 * @return max number of commands that can fit in to a command sequence
 *         register.
 */
uint8 spm_hal_get_num_cmds_in_reg(void);

/**
 * @brief Returns the number of command sequence register necessary to
 *        program input number of commands.
 *
 * @param total_cmds: Number of commands we want to program in SPM.
 *
 * @return Number of command sequence registers required for that.
 */
uint16 spm_hal_get_num_regs_required(uint32 total_cmds);

/**
 * @brief Configures SPM command sequence register with a given value.
 *
 * @param spm_base: SPM instance's base address.
 * @param reg_index: Index of command sequence register to be configured.
 * @param val: Value to be written to command sequence register. 
 */
void spm_hal_config_cmd_seq(uint8 *spm_base, uint8 reg_index, uint32 val);

/**
 * @brief Configures/updates the command at a paritcular index in a given 
 *        command sequence register.
 *
 * @param spm_base: SPM instance's base address.
 * @param cmd_index: Index of the command in the sequence that is being changed.
 * @param cmd: New command value.
 */
void spm_hal_config_cmd_at_idx(uint8  *spm_base,
                               uint16 cmd_index,
                               uint8  cmd);

/**
 * @brief Copies input commands sequence in to SPM HW block.
 *
 * @param spm_base: SPM instance's base address.
 * @param start_adr: Address (command index) to start copying at.
 * @param cmds: Array containing commands to be programmed.
 * @param size: Size of above array.
 *
 * @return Number of commands copied to actual SPM HW (In successful call
 *         it must be equal to size).
 */
uint16 spm_hal_copy_cmd_seq
(
  uint8 *spm_base, 
  uint16 start_adr, 
  uint8* cmds, 
  uint16 size
);

/**
 * @brief Invalidates given SPM's command sequence register bank with end of 
 *        sequence command.
 *
 * This function is intended to use at init time before programming any 
 * command sequences. It is to prevent invalid commands beyond programmed
 * sequences.
 *
 * @param spm_base: SPM instance's base address.
 */
void spm_hal_invalidate_cmd_seqs(uint8 *spm_base);

/**
 * @brief Configures the start address from which SPM will start executing 
 *        command sequence.
 *
 * @param spm_base: SPM instance's base address.
 * @param start_addr: Address to start executing (usually start of a low 
 *                    power mode command sequence).
 */
void spm_hal_config_seq_start_addr(uint8 *spm_base, uint16 start_addr);

/**
 * @brief Configures ISAR (Inhibit Start Address Reset) field for the SPM.
 *        If set, SPM start address will not be reset to 0 upon completion
 *        of a command sequence.
 *
 * @param spm_base: SPM instace's base address.
 * @param isar: Value to indicate if start address reset should be 
 *              inhibited (1 - inhibit, 0 - don't inhibit)
 */
void spm_hal_config_isar(uint8* spm_base, uint8 isar);

/**
 * @brief Performs SPM wakeup configuration.
 *
 * @param spm_base: SPM instace's base address.
 * @param wakeup_config: Value indicating wakeup configuration.
 */
void spm_hal_config_wakeup(uint8* spm_base, uint8 wakeup_config);

/**
 * @brief Sets up low power mode specific fields of SPM_CTL register like
 *        ISAR, SYS_PC/RET_MODE and START_ADR.
 *
 * This function is exepcted to be called while configuring SPM for a low
 * power mode.
 *
 * @param spm_base: SPM instace's base address.
 * @param ctl_val: Bitwise OR'd value of low power mode specific fields
 */
void spm_hal_config_lpm_ctl(uint8* spm_base, uint32 ctl_val);

/**
 * @brief Configures different delay fields to control timing between spm
 *        commands.
 *
 * @param spm_base: SPM instance's base address.
 * @param delay_index: Which delay to configure (1 to 3)
 * @param delay: Actual delay value.
 */
void spm_hal_config_index_delay
(
  uint8* spm_base, 
  uint8 delay_index, 
  uint16 delay
);

/**
 * @brief Configures all SPM delay fields. They are used to introduced 
 *        additional delay between SPM commands.
 *
 * @param spm_base: SPM instance's base address.
 * @param delay1: Value to set for DLY1.
 * @param delay2: Value to set for DLY2.
 * @param delay3: Value to set for DLY3.
 */
void spm_hal_config_delays
(
  uint8 *spm_base, 
  uint16 delay1, 
  uint16 delay2, 
  uint16 delay3
);

/**
 * @brief Configures SPM to peform or skip RPM handshake during low power
 *        mode sequences.
 *
 * @param spm_base: SPM instance's base address.
 * @param rpm_hs: Value to indicate if SPM should perfrom RPM handshake or 
 *                not (1 - Perform RPM handshake, 0 - skip it).
 */
void spm_hal_config_rpm_handshake(uint8 *spm_base, uint8 rpm_hs);

/**
 * @brief Configures PMIC arbiter address index, delay and data.
 *
 * @param spm_base: SPM instance's base address.
 * @param index: PMIC register index to program.
 * @param addr_index: PMIC address index bus.
 * @param data: PMIC data to send to arbiter.
 * @param size: Number of bytes per request (0 - 1 byte, 1 - 2 byte).
 * @param delay: Delay between sending PMIC data and next command in the 
 *               sequence.
 */
void spm_hal_config_pmic
(
  uint8* spm_base,
  uint8 index,
  uint8 addr_index,
  uint16 data,
  uint8 size,
  uint8 delay
);

/**
 * @brief This function configures an event as synchronous or asynchronous.
 *
 * @param spm_base: SPM's base address.
 * @param sync: Value to indicate if event is synchronous or asynchronous.
 *              (1 - synchronous, 0 - asynchronous)
 * @param event_num: which event.
 */
void spm_hal_config_event(uint8* spm_base, uint8 sync, uint8 event_num);

#ifdef __cplusplus
}
#endif

#endif 
