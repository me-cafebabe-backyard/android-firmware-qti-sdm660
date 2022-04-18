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
#include "ddr_cc_mccc_config.h"
#include "HALhwio.h"
#include "ddr_cc_mccc_seq_hwiobase.h"
#include "ddr_cc_mccc_seq_hwioreg.h"
#include "ddr_cc_mccc.h"



/*==============================================================================
                                  DATA
==============================================================================*/
uint32 ddr_cc_mccc_regs_config[][2] =
{
  //{HWIO_ADDRX((SEQ_DDR_CC_MCCC_DDRCC_MCCC_OFFSET), DDR_CC_MCCC_DDRCC_MCCC_TOP_CFG), 0xF8336618},
  {0x0, 0x0}
};

uint32 ddr_cc_mccc_ch_regs_config[][2] =
{
  {0x0, 0x0}
};

uint32 ddr_cc_mccc_ch_regs_ch_diff[][2] =
{
  {0x0, 0x0}
};



/* The shared ddr_cc_mccc regs exist only once, so do not differ between channels */
uint32 ddr_cc_mccc_regs_ch_diff[][2] =
{
  {0x0, 0x0}
};

/* ddr_cc_mccc config differences compared to MSM V1 */
uint32 ddr_cc_mccc_regs_config_diff[][2] =
{
  {0x0, 0x0}
};

uint32 ddr_cc_mccc_ch_regs_config_diff[][2] =
{
  {0x0, 0x0}
};


/* ddr_cc_mccc base config */
uint32 (*ddr_cc_mccc_regs_config_base)[2]               = ddr_cc_mccc_regs_config;
uint32 (*ddr_cc_mccc_ch_regs_config_base)[2]          = ddr_cc_mccc_ch_regs_config;

/* ddr_cc_mccc config for diff settings across channels*/
uint32 (*ddr_cc_mccc_regs_config_ch_delta)[2]              = ddr_cc_mccc_regs_ch_diff;
uint32 (*ddr_cc_mccc_ch_regs_config_ch_delta)[2]         = ddr_cc_mccc_ch_regs_ch_diff;

/* ddr_cc_mccc delta config compared to base */
uint32 (*ddr_cc_mccc_regs_config_delta)[2]              = ddr_cc_mccc_regs_config_diff;
uint32 (*ddr_cc_mccc_ch_regs_config_delta)[2]         = ddr_cc_mccc_ch_regs_config_diff;


/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void ddr_cc_mccc_set_config
(
  DDR_STRUCT *ddr,
  uint32 offset,
  uint32 (*ddr_cc_mccc_config_base)[2], uint32 (*ddr_cc_mccc_config_ch_delta)[2], uint32 (*ddr_cc_mccc_config_delta)[2]
)
{
  uint32 reg = 0;
  uint8  ch = 0;
  uint32 ch_offset = offset;

  /* Populate base config */
  if (ddr_cc_mccc_config_base != NULL)
  {
     if (ddr_cc_mccc_config_base != ddr_cc_mccc_regs_config)
     {
        for (ch=0; ch < 2; ch++)
        {
           ch_offset += DDR_CC_MCCC_CH_OFFSET*ch;

           for (reg = 0; ddr_cc_mccc_config_base[reg][0] != 0; reg++)
           {
             out_dword(ddr_cc_mccc_config_base[reg][0] + ch_offset, ddr_cc_mccc_config_base[reg][1]);
           }
        }
        ch_offset = offset;
     }
     else 
     {
        for (reg = 0; ddr_cc_mccc_config_base[reg][0] != 0; reg++)
        {
          out_dword(ddr_cc_mccc_config_base[reg][0] + offset, ddr_cc_mccc_config_base[reg][1]);
        }
     }
  }

  /* Populate channel delta config */
  if (ddr_cc_mccc_config_ch_delta != NULL)
  {
    for (reg = 0; ddr_cc_mccc_config_ch_delta[reg][0] != 0; reg++)
    {
      out_dword(ddr_cc_mccc_config_ch_delta[reg][0] + offset, ddr_cc_mccc_config_ch_delta[reg][1]);
    }
  }


  /* Populate version delta config */
    if (((ddr->misc.platform_id == (DDR_SOC_MSM8997_V1 >> 16)) && (ddr->misc.chip_version >= 0x0200))
       || ((ddr->misc.platform_id == (DDR_SOC_MSM8998_V1 >> 16)) && (ddr->misc.chip_version >= 0x0200)))
    {
        if (ddr_cc_mccc_config_delta != ddr_cc_mccc_regs_config_delta)
        {
            for (ch=0; ch < 2; ch++)
            {
                ch_offset += DDR_CC_MCCC_CH_OFFSET*ch;

                for (reg = 0; ddr_cc_mccc_config_delta[reg][0] != 0; reg++)
                {
                    out_dword(ddr_cc_mccc_config_delta[reg][0] + ch_offset, ddr_cc_mccc_config_delta[reg][1]);
                }
            }
            ch_offset = offset;
        }
        else 
        {
            for (reg = 0; ddr_cc_mccc_config_delta[reg][0] != 0; reg++)
            {
                out_dword(ddr_cc_mccc_config_delta[reg][0] + offset, ddr_cc_mccc_config_delta[reg][1]);
            }
        }
    }


}
