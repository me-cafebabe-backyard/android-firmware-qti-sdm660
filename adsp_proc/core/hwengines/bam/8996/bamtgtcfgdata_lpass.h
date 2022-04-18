/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  8996 LPASS system.

*/
/*
===============================================================================

                             Edit History

 $Header: //components/rel/core.qdsp6/1.0.c2/hwengines/bam/8996/bamtgtcfgdata_lpass.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/01/15   ss      Added Crypto BAM support
03/10/15   ss      Modified for slimbus bam init in tz
08/11/14    rl     branched from 8994 and updated for 8996

===============================================================================
                   Copyright (c) 2013-2015 QUALCOMM Technologies Inc.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "bamtgtcfg.h"
/** Configs supported for
    BLSP1,2
    SLIMBUS
    SLIMBUS1
    CE1
    BAM_TGT_CFG_LAST
 */
bam_sec_config_type bam_tgt_slimbus_aud_secconfig_8996 =
{
    /*.ee*/         {
                       /*[0]*/          {
                       /*.pipe_mask*/       0x1fffffE7,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                        },
                       /*[1]*/          {
                       /*.pipe_mask*/       0x60000018,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                        },
                       /*[2]*/          {
                       /*.pipe_mask*/       0x00000000,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                         }
                    },
    /*.sg*/         {{0x0}},
    /*.ctrl_vmid*/  0x0,
    /*.bam_irq_ee*/ 0x0
};

bam_sec_config_type bam_tgt_slimbus_qca_secconfig_8996 =
{
    /*.ee*/           {
                         /*[0]*/            {
                         /*.pipe_mask*/         0x0007ffE7, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            },
                         /*[1]*/            {
                         /*.pipe_mask*/         0x00000018, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            },
                         /*[2]*/            {
                         /*.pipe_mask*/         0x00000000, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            }
                      },
    /*.sg*/           {{0x0}},
    /*.ctrl_vmid*/    0x0,
    /*.bam_irq_ee*/   0x0
};

#define BAM_CNFG_BITS_VAL 0xFFFFF004


const bam_target_config_type  bam_tgt_config[] = {
    {                    // BLSP1_BAM 
     /* .bam_pa     */   0x7544000,
     /* .options    */   (BAM_TGT_CFG_NO_INIT),    
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,                             
     /* .ee         */   1,                                             
     /* .sec_config */   NULL, 
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // BLSP2_BAM 
     /* .bam_pa     */   0x7584000,
     /* .options    */   (BAM_TGT_CFG_NO_INIT),    
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,                             
     /* .ee         */   1,                                             
     /* .sec_config */   NULL, 
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // SLIMBUS_AUD_BAM
     /* .bam_pa     */   0x9184000,
     /* .options    */   0x0,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   0,
     /* .sec_config */   &bam_tgt_slimbus_aud_secconfig_8996,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // SLIMBUS_QCA_BAM
     /* .bam_pa     */   0x9204000,
     /* .options    */   0x0,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   0,
     /* .sec_config */   &bam_tgt_slimbus_qca_secconfig_8996,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // Crypto_BAM
     /* .bam_pa     */   0x644000,
     /* .options    */   0x0,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   1,
     /* .sec_config */   NULL,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    //dummy config
     /* .bam_pa     */   BAM_TGT_CFG_LAST,
     /* .options    */   0,
     /* .cfg_bits   */   0,
     /* .ee         */   0,
     /* .sec_config */   NULL,
     /* .size       */   0
    },
};




