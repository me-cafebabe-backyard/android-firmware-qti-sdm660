#ifndef __HALCLKTARGET_H__
#define __HALCLKTARGET_H__
/*
==============================================================================

FILE:         HALclkTarget.h

DESCRIPTION:  Target specific HAL definitions

==============================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/inc/HALclkTarget.h#3 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
07/18/11   bc      Separated out the target specfici HAL definitions for BIMC into
                   this separate file to differentiate MSM8998 and SDM660
==============================================================================
            Copyright (c) 2016-2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/


/*
 * BIMC accessors used for repurposed mux config bit-fields.
 * Utilized to fit independent RCG clock dividers for all BIMC clients into
 * a single mux config, to provide HAL compatibility.
 */
#define debug_marker(var,value) var = value
#define HAL_CLK_BIMC_DIV2X_VAL(ddrcc_mode, ddr_gpll0_sel, ddr_div2x, cdsp_gpll0_sel, cdsp_div2x) \
  ((((ddrcc_mode) & 0x1) << 15) | (((ddr_gpll0_sel) & 0x3) << 13) | (((ddr_div2x) & 0x1F) << 8) | (((cdsp_gpll0_sel) & 0x7) << 5) | ((cdsp_div2x) & 0x1F))
 
#define HAL_CLK_BIMC_DIV2X_DDRCC_MODE_EN(div2x) (((div2x) & 0x8000) >> 15)
#define HAL_CLK_BIMC_DIV2X_DDR_GPLL0_SEL(div2x) (((div2x) & 0x6000) >> 13)
#define HAL_CLK_BIMC_DIV2X_DDR_DIV2X(div2x)     (((div2x) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_DIV2X_CDSP_GPLL0_SEL(div2x)(((div2x) & 0xE0) >> 5)
#define HAL_CLK_BIMC_DIV2X_CDSP_DIV2X(div2x)    ((div2x) & 0x1F)



#define HAL_CLK_BIMC_M_VAL(bimc_gpll0_sel, bimc_div2x, hmss_gpll0_sel, hmss_div2x) \
  ((((bimc_gpll0_sel) & 0x7) << 13) | (((bimc_div2x) & 0x1F) << 8) | (((hmss_gpll0_sel) & 0x7) << 5) | ((hmss_div2x) & 0x1F))

#define HAL_CLK_BIMC_M_BIMC_GPLL0_SEL(m)    (((m) & 0xE000) >> 13)
#define HAL_CLK_BIMC_M_BIMC_DIV2X(m)        (((m) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_M_HMSS_GPLL0_SEL(m)    (((m) & 0xE0) >> 5)
#define HAL_CLK_BIMC_M_HMSS_DIV2X(m)        ((m) & 0x1F)



#define HAL_CLK_BIMC_N_VAL(gfx_gpll0_sel, gfx_div2x, mpss_gpll0_sel, mpss_div2x) \
  ((((gfx_gpll0_sel) & 0x7) << 13) | (((gfx_div2x) & 0x1F) << 8) | (((mpss_gpll0_sel) & 0x7) << 5) | ((mpss_div2x) & 0x1F))

#define HAL_CLK_BIMC_N_GFX_GPLL0_SEL(n)     (((n) & 0xE000) >> 13)
#define HAL_CLK_BIMC_N_GFX_DIV2X(n)         (((n) & 0x1F00) >> 8)
#define HAL_CLK_BIMC_N_MPSS_GPLL0_SEL(n)    (((n) & 0xE0) >> 5)
#define HAL_CLK_BIMC_N_MPSS_DIV2X(n)        ((n) & 0x1F)



#define HAL_CLK_BIMC_N2D_VAL(gpll23_idx, VDDA_EBI_vote) \
  ((((gpll23_idx) & 0xF) << 12) | ((VDDA_EBI_vote) & 0xFFF))

#define HAL_CLK_BIMC_N2D_GPLL23_IDX(n2d)                (((n2d) & 0xF000) >> 12)
#define HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(n2d)             ((n2d) & 0xFFF)



enum GPLLx_BIMC_DDR_RCG_ID{
  GPLL23_GPLL0_BIMC_DDR_RCG_PLL_ID,
  GPLL0_ASYNC_CLK_PLL_ID,
  GPLL1_ASYNC_CLK_PLL_ID,
  GPLL4_ASYNC_CLK_PLL_ID,
  GPLL5_ASYNC_CLK_PLL_ID,
  NUM_GPLLx_ASYNC_CLK_PLL_ID
};
#endif /* !HALCLKTARGET_H */
