/*
 * HALclkInitASM.S
 * This file contains the implementation for setting up PLL, Q6 clock of LPASS
 *                   Edit History

   $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/HALclkInitASM.S#1 $

     #when       who                  what, where, why
    --------   -------------       ----------------------------------------------
    11/03/16   shantonu            Added SSC PLL setup & configured AON & CORE bus
                                   domains to 99.837542 MHz.
    10/04/16   shantonu            First version for SDM660.
 *
 */

#include "HALclkHWIOASM.h"


/////////////////////////////////////////////////////////////////////////////////
//
//       Additional definitions and bit masks not defined in HWIO inc files.
// 
/////////////////////////////////////////////////////////////////////////////////

#define LPAAUDIO_PLL_MODE_ACTIVE HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK


// Q6SS Core clock configuration values.

#define Q6CORE_RCG_SRC_SEL                    0x1
#define Q6CORE_RCG_SRC_DIV                    0x1
#define Q6SS_GFMUX_SRC_SEL                    0x0

#define HALCLK_WAIT_1_US                      0x14
#define HALCLK_WAIT_5_US                      0x60
#define HALCLK_WAIT_10_US                     0xC0
#define HALCLK_WAIT_50_US                     0x3C0

#define LPAAUDIO_PLL_CONFIG_CTL_VAL           0x00004289
#define LPASS_LPAAUDIO_PLL_BIAS_COUNT_VAL     0x6
#define LPAAUDIO_DIG_PLL_CONFIG_CTL_VAL       0x4001055B
#define LPASS_QDSP6SS_PLL_CONFIG_CTL_VAL      0x4001055B
#define LPASS_SCC_PLL_CONFIG_CTL_VAL          0x88488CE3

#define LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_VAL 0x0
#define LPASS_LPAAUDIO_DIG_PLL_BIAS_COUNT_VAL      0x6
#define LPASS_LPAAUDIO_PLL_USER_CTL_VAL       0x0000000F // HSR gives 0xF. POR is 0x1.
#define LPASS_LPAAUDIO_PLL_USER_CTL_U_VAL     0x00000000
#define LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VAL   0x0022810B // HSR gives 0x100001. POR is 0x228109. Should be 0x22810B.
#define LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_VAL 0x00000004
#define LPASS_QDSP6SS_PLL_USER_CTL_VAL        0x00200001
#define LPASS_QDSP6SS_PLL_USER_CTL_U_VAL      0x00270004 // Calibration_L should be 0x27(For Auto-Calibration at 748.8Mhz)
#define LPASS_SCC_PLL_USER_CTL_VAL            0x00000011 // HSR gives 0x11. POR is 0x1.
#define LPASS_SCC_PLL_USER_CTL_U_VAL          0x00000B14 // HSR gives 0xB14. POR is 0x404.

#define LPASS_LPAAUDIO_PLL_TEST_CTL_VAL       0x08000000 // HSR gives 0x8000000. POR is 0x0.
#define LPASS_LPAAUDIO_PLL_TEST_CTL_U_VAL     0x00000000
#define LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_VAL   0x00000000 // HSR & POR both 0x0. Can remove.
#define LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_VAL 0x00000000
#define LPASS_QDSP6SS_PLL_TEST_CTL_VAL        0x00000000 // HSR & POR both 0x0. Can remove.
#define LPASS_QDSP6SS_PLL_TEST_CTL_U_VAL      0x00000000
#define LPASS_SCC_PLL_TEST_CTL_VAL            0x08000000 // HSR gives 0x8000000. POR is 0x0. Should be 0x0.
#define LPASS_SCC_PLL_TEST_CTL_U_VAL          0x200000E0 // HSR gives 0x200000E0. POR is 0x0. Should be 0x0.

// SCC PLL data definitions

#define SCC_PLL_L_VAL                         0x1DC1
#define SCC_PLL_OPMODE_RUN                    0x1
#define SCC_PLL_LOCK_DELAY_TIMEOUT_VAL        0x7F

#define LPASS_CORE_CFG_RCG_SRC_DIV_VAL          0x4
#define LPASS_CORE_CFG_RCG_SRC_SEL_VAL          0x3

#define LPASS_AON_CFG_RCG_SRC_DIV_VAL          0x4
#define LPASS_AON_CFG_RCG_SRC_SEL_VAL          0x3

#define TCSR_SOC_VERSION_MAJOR_V1_VAL         0x100


/////////////////////////////////////////////////////////////////////////////////
//
//                        Data declarations start here.
// 
/////////////////////////////////////////////////////////////////////////////////

   //PLL L, and ALPHA VAL REG values
   .equ Q6_PLL_CALIB_L_VAL,                    0x27  //  39 for 748.8 MHz
   .equ Q6_PLL_L_VAL,                          0x27  //  39 for 748.8 MHz


/////////////////////////////////////////////////////////////////////////////////
//
//                 Macros Start Here.
// 
/////////////////////////////////////////////////////////////////////////////////


    //
    // MACRO:  WRITE_REGISTER
    //
    // DESCRIPTION:
    //   This macro writes an unmasked value to a register.  Any contents will
    //   be overwritten in the proccess.  r6 and r7 may be clobbered.
    //

    .macro write_register  val
        {
            r6 = \val
            r7 = r0
        }
        memw(r0) = r6
        barrier
    .endm


    //
    // MACRO:  CLEAR_BITS
    //
    // DESCRIPTION:
    //   This macro clears one ore more bits in a register.  r4, r5, r6, and r7
    //   may be clobbered when running this macro.
    //

    .macro clear_bits val_mask
        {
            r7 = r0
            r5.h = #hi(\val_mask)
        }
        {
            r5.l = #lo(\val_mask)
        }
        {
            r4 = memw(r0)
            r5 = not(r5)
        }
        r4 = and(r4, r5)    // clear the mask bits
        {
            memw(r0) = r4  //write the reg value
        }
        barrier
    .endm


    //
    // MACRO:  SET_BITS
    //
    // DESCRIPTION:
    //   This macro sets one or more bits in a register.  r4, r5 and r7 will be 
    //   clobbered when using this macro.
    //

    .macro set_bits val_mask
        {
            r7 = r0
            r5.h = #hi(\val_mask)
        }
        {
            r5.l = #lo(\val_mask)
            dcinva(r7)
        }
        {
            r4 = memw(r0)
            r6 = not(r5)
        }
        r4 = and(r4, r6)    // clear the fields
        r4 = or(r4,r5)      // set the value

        {
            memw(r0) = r4  //write the reg value
        }
        barrier
    .endm

    .macro __busywait_init
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(0)
        memw(r0) = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTNSAR_FG0_RMSK
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(1)
        memw(r0) = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTNSAR_FG0_RMSK
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(2)
        memw(r0) = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTNSAR_FG0_RMSK
        barrier
    .endm

    .macro __busywait_deinit
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(0)
        memw(r0) = ##0x0
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(1)
        memw(r0) = ##0x0
        r0 = ##HWIO_LPASS_QDSP6SS_QTMR_AC_CNTACRn_FG0_ADDR(2)
        memw(r0) = ##0x0
        barrier
    .endm


/////////////////////////////////////////////////////////////////////////////////
//
//         Executable code starts here.
// 
/////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------
// FUNCTION: __HEXAGON_BSP_INIT
//
// DESCRIPTION:
//   This is the main API for this file.  This function will check the status of the
//   main LPASS PLL and configure it if it is not running.  Otherwise, it will just
//   add a HW vote on behalf of the LPASS processor.
//
//   The QDSP6 clock will then be initialized if not already set up.  The 
//   purpose of this is to ensure the QDSP6 clock is running at maximum
//   frequency under SVS voltage.
//
// ASSUMPTIONS:
//   There is no stack available when this is called, so only device registers can be
//   accessed.
//----------------------------------------------------------------------------------
#if defined(SIM)
  // No initialization.
#else
   .section .start,"ax",@progbits
   .falign
   .global __hexagon_bsp_init
   .type  __hexagon_bsp_init, @function

__hexagon_bsp_init:

   __busywait_init

  jump start_prog

__busywait:
  {
    r8 = r1
    r9 = r2
    r10 = r3
  }
  r2 = r0             // delay_count
  r0 = ##HWIO_LPASS_QDSP6SS_QTMR_V1_CNTPCT_LO_1_ADDR
  r1 = memw(r0)       // start count

__buswait_loop:
  r3 = memw(r0)
  r3 = sub(r3, r1)
  {
    p0 = cmp.gtu(r3, r2)
    if (!p0.new) jump:t __buswait_loop
  }
  {
    r1 = r8
    r2 = r9
    r3 = r10
  }
  jumpr r13

start_prog:
  //*******************************************************************
  // Program the PLL_CONFIG_CTL values based on recommendations.
  //*******************************************************************

   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR
   memw(r0) = ##LPAAUDIO_PLL_CONFIG_CTL_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR
   memw(r0) = ##LPAAUDIO_DIG_PLL_CONFIG_CTL_VAL

   r0 = ##HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR
   memw(r0) = ##LPASS_QDSP6SS_PLL_CONFIG_CTL_VAL

   r0 = ##HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR
   memw(r0) = ##LPASS_SCC_PLL_CONFIG_CTL_VAL

   barrier
   
   //*******************************************************************
  // Program LPASS DIGITAL PLL Source
  //*******************************************************************

   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_VAL
   
   barrier
   
  //*******************************************************************
  // Program the USER_CTL and USER_CTL_U values based on recommendations.
  //*******************************************************************

   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_PLL_USER_CTL_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_PLL_USER_CTL_U_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_VAL

   r0 = ##HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR
   memw(r0) = ##LPASS_QDSP6SS_PLL_USER_CTL_VAL

   r0 = ##HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR
   memw(r0) = ##LPASS_QDSP6SS_PLL_USER_CTL_U_VAL

   r0 = ##HWIO_LPASS_SCC_PLL_USER_CTL_ADDR
   memw(r0) = ##LPASS_SCC_PLL_USER_CTL_VAL

   r0 = ##HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR
   memw(r0) = ##LPASS_SCC_PLL_USER_CTL_U_VAL

   barrier

  //*******************************************************************
  // Program the PLL_MODE , TEST_CTL and TEST_CTL_U values based on recommendations.
  //*******************************************************************
   
   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR
   
   clear_bits HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK
   r1 = memw(r0)
   // Add the new values.
   {
     r2 = ##(LPASS_LPAAUDIO_PLL_BIAS_COUNT_VAL << HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT)
   }
   r1 = or(r1, r2)
   memw(r0) = r1
   
   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_PLL_TEST_CTL_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_PLL_TEST_CTL_U_VAL
   
   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR
   
   
   clear_bits HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_BMSK
   r1 = memw(r0)
   // Add the new values.
   {
     r2 = ##(LPASS_LPAAUDIO_DIG_PLL_BIAS_COUNT_VAL << HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_SHFT)
   }
   r1 = or(r1, r2)
   memw(r0) = r1
   
   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_VAL

   r0 = ##HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR
   memw(r0) = ##LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_VAL

   r0 = ##HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR
   memw(r0) = ##LPASS_QDSP6SS_PLL_TEST_CTL_VAL

   r0 = ##HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR
   memw(r0) = ##LPASS_QDSP6SS_PLL_TEST_CTL_U_VAL

   r0 = ##HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR
   memw(r0) = ##LPASS_SCC_PLL_TEST_CTL_VAL

   r0 = ##HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR
   memw(r0) = ##LPASS_SCC_PLL_TEST_CTL_U_VAL

   barrier

  //*******************************************************************
  //
  // Begin main PLL programming sequence here.
  //
  //*******************************************************************

start_pll:

  //*******************************************************************
  // Check the HW version for the PLL_L_VAL programming.
  //*******************************************************************
  // Letting this fwk to detect the version # remain in case SL
  //       other versions come for SL.

   r0 = ##HWIO_TCSR_SOC_HW_VERSION_ADDR
   r1 = memw(r0)
   r2 = and(r1, ##TCSR_SOC_VERSION_MAJOR_V1_VAL)
   {
     p0 = cmp.eq(r2, ##TCSR_SOC_VERSION_MAJOR_V1_VAL)
     if (p0.new) jump:t v1_pll_configs
   }

v1_pll_configs:

   r14 = ##Q6_PLL_L_VAL
   r15 = ##Q6_PLL_CALIB_L_VAL
   r16 = ##Q6CORE_RCG_SRC_DIV
   jump program_q6ss_pll

program_q6ss_pll:

  //*******************************************************************
  // Set up the PLL L value.
  //*******************************************************************

  {
    r0 = ##HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR
    r1 = r14
  }
  memw(r0) = r1
  barrier

  //*******************************************************************
  // Put the PLL in standby and then run mode.
  //*******************************************************************

  r0 = ##HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR
  set_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_BMSK
  r0 = ##HALCLK_WAIT_5_US
  r13 = add(PC, #0x8)
  jump __busywait

  r0 = ##HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR
  set_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK
  r0 = ##HALCLK_WAIT_50_US
  r13 = add(PC, #0x8)
  jump __busywait

  //*******************************************************************
  // Poll on the lock detect value until it transitions to '1'
  //*******************************************************************

  r4 = ##HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR
  r2 = ##HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK

q6_lock_det_loop:

  r0 = ##HALCLK_WAIT_10_US
  r13 = add(PC, #0x8)
  jump __busywait

  r1 = memw(r4)
  r3 = and(r1, r2)
  {
    p0 = cmp.eq(r2, r3)
    if (!p0.new) jump:t q6_lock_det_loop
  }

  //*******************************************************************
  // Enable PLL outputs
  //*******************************************************************
 
  r0 = ##HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR
  set_bits HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK

  r0 = ##HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR
  set_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK

  // ...End QDSP6SS PLL Setup...

  //*******************************************************************
  // Switch the Q6 to run on the QDSP6SS_PLL.
  //*******************************************************************

   
   // Program the Strap ACC value.
   r0 = ##HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR

   r1 = ##0x0
   memw(r0) = r1
   barrier
   
   // Set up the QDSP6 now.
check_qdsp6:

   r0 = ##HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR
   r1 = memw(r0)

   // Clear out the source selection and divider values.
   {
     r2 = ##HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK
     r3 = ##HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK
   }
   r2 = or(r2, r3)
   r2 = not(r2)
   r1 = and(r1, r2)

   // Add the new values.
   {
     r2 = ##Q6CORE_RCG_SRC_SEL << HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT
     r3 = asl(r16, #HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT)
   }
   r2 = or(r2, r3)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   // Ensure Q6 is on.
   r0 = ##HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR
   r1 = memw(r0)
   
   // Trigger the update
   r2 = ##HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

q6_cmd_update:

   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r3, r2)
     if (p0.new) jump:t q6_cmd_update
   }

   // Program the GFMUX config register.
   r0 = ##HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR
   r1 = memw(r0)

   r2 = ##HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK
   r2 = not(r2)
   r1 = and(r1, r2)
   r2 = ##(Q6SS_GFMUX_SRC_SEL << HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT)
   {
     r3 = ##HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK
     r4 = ##HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK
   }
   r3 = or(r3, r4)
   r2 = or(r2, r3)
   r1 = or(r1, r2)

   memw(r0) = r1
   barrier
   
   //*******************************************************************
   // Set up the Peel PLL lock detect delay timeout timer.
   //*******************************************************************

   r0 = ##HWIO_LPASS_PMU_SM_CSR1_ADDR
   r1 = memw(r0)
   set_bits HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_TMR_EN_BMSK
   {
      r2 = ##(SCC_PLL_LOCK_DELAY_TIMEOUT_VAL << HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_SHFT)
      r3 = ##(0x1 << HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_WR_SHFT)
   }
   r2 = or(r2, r3)
   r1 = or(r1, r2)
   memw(r0) = r1

   //*******************************************************************
   // Set the desired L-value.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_L_VAL_ADDR
   r1 = ##SCC_PLL_L_VAL
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Duplicate the L-value to the CALIB_L register.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR
   r1 = ##SCC_PLL_L_VAL
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Turn off the PLL outputs.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_MODE_ADDR
   r1 = memw(r0)
   clear_bits HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_BMSK

   //*******************************************************************
   // For when transitioning to RUN and skipping calibration, scale down
   // the CPU by 12%.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR
   r1 = memw(r0)
   clear_bits (HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_BMSK)
   r2 = ##(0x2 << HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_SHFT)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Set the number of reference cycles taken per calibration step to 4
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR
   r1 = memw(r0)
   clear_bits HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_BMSK
   r2 = ##(0x2 << HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_SHFT)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   //*******************************************************************
   // To stabilize the PEEL PLL, set the fine lock detect threshold to
   // 0x6. 0x4 was the default.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR
   r1 = memw(r0)
   clear_bits HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK
   r2 = ##(0x6 << HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier  

   //*******************************************************************
   // Put the PLL into standby mode.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_OPMODE_ADDR
   clear_bits HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_BMSK

   //*******************************************************************
   // Bring PLL out of reset.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_MODE_ADDR
   set_bits HWIO_LPASS_SCC_PLL_MODE_PLL_RESET_N_BMSK

   //*******************************************************************
   // Put the PLL into run mode.
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_OPMODE_ADDR
   r1 = memw(r0)
   r2 = ##(SCC_PLL_OPMODE_RUN << HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_SHFT)
   r1 = or(r1,r2)
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Poll on the lock detect value until it transitions to '1'
   //*******************************************************************

   r4 = ##HWIO_LPASS_SCC_PLL_MODE_ADDR
   r2 = ##HWIO_LPASS_SCC_PLL_MODE_PLL_LOCK_DET_BMSK

peel_lock_det_loop:
   r0 = ##HALCLK_WAIT_1_US
   r13 = add(PC, #0x8)
   jump __busywait

   r1 = memw(r4)
   r3 = and(r1, r2)
   {
      p0 = cmp.eq(r2,r3)
      if (!p0.new) jump:t peel_lock_det_loop
   }

   //*******************************************************************
   // Enable PLL outputs
   //*******************************************************************

   r0 = ##HWIO_LPASS_SCC_PLL_USER_CTL_ADDR
   set_bits HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK

   r0 = ##HWIO_LPASS_SCC_PLL_MODE_ADDR
   set_bits HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_BMSK

   // End of Peel PLL setup

   //****************************************************************************
   //
   //            SET UP THE BUS DOMAINS TO RUN ON THE PEEL PLL
   //
   //****************************************************************************

   //*******************************************************************
   // Program the divider and source selection to the Peel PLL.
   //*******************************************************************

   r0 = ##HWIO_LPASS_CORE_CFG_RCGR_ADDR
   r1 = memw(r0)

   {
      r2 = ##(LPASS_CORE_CFG_RCG_SRC_DIV_VAL << HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_SHFT)
      r3 = ##(LPASS_CORE_CFG_RCG_SRC_SEL_VAL << HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_SHFT)
   }

   r2 = or(r2, r3)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Trigger the state update and poll on completion.
   //*******************************************************************

   r0 = ##HWIO_LPASS_CORE_CMD_RCGR_ADDR
   set_bits HWIO_LPASS_CORE_CMD_RCGR_UPDATE_BMSK

   r1 = ##HWIO_LPASS_CORE_CMD_RCGR_UPDATE_BMSK

bus_rcgr_update:
   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r3, r2)
     if (p0.new) jump:t bus_rcgr_update
   }
   
   //*******************************************************************
   // Program the divider and source selection to the Peel PLL.
   //*******************************************************************

   r0 = ##HWIO_LPASS_AON_CFG_RCGR_ADDR
   r1 = memw(r0)

   {
      r2 = ##(LPASS_AON_CFG_RCG_SRC_DIV_VAL << HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_SHFT)
      r3 = ##(LPASS_AON_CFG_RCG_SRC_SEL_VAL << HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_SHFT)
   }

   r2 = or(r2, r3)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   //*******************************************************************
   // Trigger the state update and poll on completion.
   //*******************************************************************

   r0 = ##HWIO_LPASS_AON_CMD_RCGR_ADDR
   set_bits HWIO_LPASS_AON_CMD_RCGR_UPDATE_BMSK

   r1 = ##HWIO_LPASS_AON_CMD_RCGR_UPDATE_BMSK

aon_rcgr_update:
   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r3, r2)
     if (p0.new) jump:t aon_rcgr_update
   }

  // End AON & CORE bus clock config setup
  
  
   __busywait_deinit

end_init:
   Jumpr r31

.size __hexagon_bsp_init, .-__hexagon_bsp_init
#endif // SIM
