/*==============================================================================
                      Warning: This file is auto-generated
================================================================================
                   Copyright 2016 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "mccc_config.h"
#include "HALhwio.h"
#include "mccc_seq_hwiobase.h"
#include "mccc_seq_hwioreg.h"
#include "mccc.h"



/*==============================================================================
                                  DATA
==============================================================================*/
uint32 mccc_regs_config[][2] =
{
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND0_CFG0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND0_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND0_UPPER_FREQ_THRESHOLD), 0x0000CB70},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND1_CFG0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND1_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND1_UPPER_FREQ_THRESHOLD), 0x00000724},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND2_CFG0), 0x00001111},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND2_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND2_UPPER_FREQ_THRESHOLD), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND3_CFG0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND3_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND3_UPPER_FREQ_THRESHOLD), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND4_CFG0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND4_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND4_UPPER_FREQ_THRESHOLD), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND5_CFG0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_BAND5_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_CLK_PERIOD), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_CLOCK_GATE_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_DEBUG_BUS_SELECT), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FREQ_SWITCH_DISABLE), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FREQ_SWITCH_FSM_CFG), 0x0000000F},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FREQ_SWITCH_STATE_EXIT_COND), 0x3000FFFE},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FREQ_SWITCH_UPDATE), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FSC_STATE_APPEND_TIMER_SEL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FSC_STATE_PREPEND_TIMER_SEL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_FSC_STATE_TIMER_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_MISC_FEATURE_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK0_RX_ENABLE_CFG), 0x40000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK1_RX_CLKON_CFG), 0x40000011},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK2_GFCM_SWITCH_CFG), 0x70000088},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK3_SSP_CFG), 0x70000020},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK4_RX_DISABLE_CFG), 0x70000033},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK_DEP_VEC_CFG0), 0x08040100},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK_DEP_VEC_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK_DEP_VEC_CFG2), 0x00000008},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK_MASK_CFG0), 0x00010117},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TASK_MASK_CFG1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_MCCC_REGS_OFFSET), MCCC_REGS_TEST_CLOCK_SELECT), 0x00000000},
  {0x0, 0x0}
};

uint32 mccc_ch_regs_config[][2] =
{
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_CLK_CBCR), 0x80000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_CLK_RST_CTL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_CONFIG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_GCC_SRC0_BYP_CLK_CGCR), 0x80000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_GCC_SRC1_BYP_CLK_CGCR), 0x80000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_MC_CLK_CBCR), 0x80004220},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER0_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER1_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER2_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER3_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_FSC_TIMER_ENABLE), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_PDM_STM_CFG), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX0_CONFIG_CTL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX0_TEST_CTL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX0_USER_CTL), 0x0000001A},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX1_CONFIG_CTL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX1_TEST_CTL), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_RX1_USER_CTL), 0x0000001A},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SPARE0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SPARE1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_CTL0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_CTL1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_OVERRIDE0), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_OVERRIDE1), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_OVERRIDE2), 0x00000000},
  {HWIO_ADDRX((SEQ_MCCC_MCCC_CH0_MCCC_CH_REGS_OFFSET), MCCC_CH_REGS_SW_OVERRIDE_UPDATE), 0x00000000},
  {0x0, 0x0}
};

uint32 mccc_ch_regs_ch_diff[][2] =
{
  {0x0, 0x0}
};



/* The shared MCCC regs exist only once, so do not differ between channels */
uint32 mccc_regs_ch_diff[][2] =
{
  {0x0, 0x0}
};

/* MCCC config differences compared to MSM V1 */
uint32 mccc_regs_config_diff[][2] =
{
  {0x0, 0x0}
};

uint32 mccc_ch_regs_config_diff[][2] =
{
  {0x0, 0x0}
};


/* MCCC base config */
uint32 (*mccc_regs_config_base)[2]               = mccc_regs_config;
uint32 (*mccc_ch_regs_config_base)[2]          = mccc_ch_regs_config;

/* MCCC config for diff settings across channels*/
uint32 (*mccc_regs_config_ch_delta)[2]              = mccc_regs_ch_diff;
uint32 (*mccc_ch_regs_config_ch_delta)[2]         = mccc_ch_regs_ch_diff;

/* MCCC delta config compared to base */
uint32 (*mccc_regs_config_delta)[2]              = mccc_regs_config_diff;
uint32 (*mccc_ch_regs_config_delta)[2]         = mccc_ch_regs_config_diff;


/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void mccc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*mccc_config_base)[2], uint32 (*mccc_config_ch_delta)[2], uint32 (*mccc_config_delta)[2]
)
{
  uint32 reg = 0;
  uint8  ch = 0;
  uint32 ch_offset = offset;

  /* Populate base config */
  if (mccc_config_base != NULL)
  {
     if (mccc_config_base != mccc_regs_config)
     {
        for (ch=0; ch < 2; ch++)
        {
           ch_offset += MCCC_CH_OFFSET*ch;

           for (reg = 0; mccc_config_base[reg][0] != 0; reg++)
           {
             out_dword(mccc_config_base[reg][0] + ch_offset, mccc_config_base[reg][1]);
           }
        }
        ch_offset = offset;
     }
     else 
     {
        for (reg = 0; mccc_config_base[reg][0] != 0; reg++)
        {
          out_dword(mccc_config_base[reg][0] + offset, mccc_config_base[reg][1]);
        }
     }
  }

  /* Populate channel delta config */
  if (mccc_config_ch_delta != NULL)
  {
    for (reg = 0; mccc_config_ch_delta[reg][0] != 0; reg++)
    {
      out_dword(mccc_config_ch_delta[reg][0] + offset, mccc_config_ch_delta[reg][1]);
    }
  }


  /* Populate version delta config */
    if (((ddr->misc.platform_id == (DDR_SOC_MSM8997_V1 >> 16)) && (ddr->misc.chip_version >= 0x0200))
       || ((ddr->misc.platform_id == (DDR_SOC_MSM8998_V1 >> 16)) && (ddr->misc.chip_version >= 0x0200)))
    {
        if (mccc_config_delta != mccc_regs_config_delta)
        {
            for (ch=0; ch < 2; ch++)
            {
                ch_offset += MCCC_CH_OFFSET*ch;

                for (reg = 0; mccc_config_delta[reg][0] != 0; reg++)
                {
                    out_dword(mccc_config_delta[reg][0] + ch_offset, mccc_config_delta[reg][1]);
                }
            }
            ch_offset = offset;
        }
        else 
        {
            for (reg = 0; mccc_config_delta[reg][0] != 0; reg++)
            {
                out_dword(mccc_config_delta[reg][0] + offset, mccc_config_delta[reg][1]);
            }
        }
    }


}
