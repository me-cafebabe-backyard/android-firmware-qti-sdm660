/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  SDM660 LPASS system.

*/
/*
===============================================================================

                             Edit History


when       who     what, where, why
--------   ---     ------------------------------------------------------------
08/02/16   SA      Branched from 8998 and updated for SDM660

===============================================================================
                   Copyright (c) 2016 QUALCOMM Technologies Inc.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/
#include "bamtgtcfg.h"
/** Configs supported for
    BLSP1
    BLSP2
    SLIMBUS_AUD
    SLIMBUS_QCA
    BLSP_SENSOR
    CE1
    BAM_TGT_CFG_LAST
 */

bam_sec_config_type bam_tgt_slimbus_aud_secconfig =
{
    /*.ee*/         {
                       /*[0]*/          {
                       /*.pipe_mask*/       0x0001FF87,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                        },
                       /*[1]*/          {
                       /*.pipe_mask*/       0x007E0078,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                        },
                       /*[2]*/          {
                       /*.pipe_mask*/       0x00000000,
                       /*.vmid*/            0x0,
                       /*.pipe_mask_ac*/    0x0,
                       /*.vmid_ac*/         0x0
                                         },
                       /*[3]*/          {
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

bam_sec_config_type bam_tgt_slimbus_qca_secconfig =
{
    /*.ee*/           {
                         /*[0]*/            {
                         /*.pipe_mask*/         0x00000787, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            },
                         /*[1]*/            {
                         /*.pipe_mask*/         0x00001878, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            },
                         /*[2]*/            {
                         /*.pipe_mask*/         0x00000000, 
                         /*.vmid*/              0x0, 
                         /*.pipe_mask_ac*/      0x0, 
                         /*.vmid_ac*/           0x0
                                            },
                         /*[3]*/            {
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
     /* .bam_pa     */   0xC144000,
     /* .options    */   BAM_TGT_CFG_NO_INIT,    
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,                             
     /* .ee         */   1,                                             
     /* .sec_config */   NULL, 
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // BLSP2_BAM 
     /* .bam_pa     */   0xC184000,
     /* .options    */   BAM_TGT_CFG_NO_INIT,    
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,                             
     /* .ee         */   1,                                             
     /* .sec_config */   NULL, 
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // SLIMBUS_AUD_BAM
     /* .bam_pa     */   0x15184000,
     /* .options    */   BAM_TGT_CFG_INIT,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   0,
     /* .sec_config */   &bam_tgt_slimbus_aud_secconfig,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // SLIMBUS_QCA_BAM
     /* .bam_pa     */   0x15204000, 
     /* .options    */   BAM_TGT_CFG_INIT,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   0,
     /* .sec_config */   &bam_tgt_slimbus_qca_secconfig,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // BLSP_SENSOR_BAM
     /* .bam_pa     */   0x15404000, 
     /* .options    */   BAM_TGT_CFG_NO_INIT,
     /* .cfg_bits   */   BAM_CNFG_BITS_VAL,   
     /* .ee         */   0,
     /* .sec_config */   NULL,
     /* .size       */   BAM_MAX_MMAP
    },
    {                    // Crypto_BAM
     /* .bam_pa     */   0x1DC4000,
     /* .options    */   BAM_TGT_CFG_NO_INIT,
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




