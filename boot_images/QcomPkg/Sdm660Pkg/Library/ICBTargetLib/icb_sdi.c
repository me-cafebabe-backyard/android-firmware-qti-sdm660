/**

@file   icb_sdi.c

@brief  ICB support for SDI. Save/restore BRIC segment/remap
        
===========================================================================

                             Edit History


when         who     what, where, why
----------   ---     --------------------------------------------------------
2015/08/24   sds     Created 

===========================================================================
           Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                       All Rights Reserved.
                       QUALCOMM Proprietary
===========================================================================
*/

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../Include/msmhwiobase.h"
#include "../../../Library/ICBLib/HALbimcHwio.h"
#include "../../../Library/ICBLib/HALbimcHwioGeneric.h"

/* -----------------------------------------------------------------------
** Definitions
** ----------------------------------------------------------------------- */
#define BIMC_BASE        (DDR_SS_BASE      + 0x00003000)

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */
typedef struct
{
  uint32_t addr_hi;
  uint32_t addr_low;
  uint32_t mask_hi;
  uint32_t mask_low;
} icb_sdi_segment_t;

typedef struct
{
  uint32_t addr_hi;
  uint32_t addr_low;
  uint32_t mask_hi;
  uint32_t mask_low;
  uint32_t op0;
  uint32_t op1;
} icb_sdi_remap_t;

/* -----------------------------------------------------------------------
** Data
** ----------------------------------------------------------------------- */
static bool valid = false;
static icb_sdi_segment_t segments[2][4];
static icb_sdi_remap_t   remaps[4];

/* -----------------------------------------------------------------------
** Functions
** ----------------------------------------------------------------------- */

//*============================================================================*/
/**
@brief 
      Save BRIC SEGMENT and REMAP registers for SDI.
*/ 
/*============================================================================*/
void icb_sdi_save( void )
{
  uint32_t ch, seg;

  /* Save segment decode registers. */
  for( ch = 0; ch < 2; ch ++ )
  {
    for( seg = 0; seg < 4; seg ++ )
    {
      segments[ch][seg].addr_hi  = BIMC_INI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_UPPER, ch, seg);
      segments[ch][seg].addr_low = BIMC_INI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_LOWER, ch, seg);
      segments[ch][seg].mask_hi  = BIMC_INI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_UPPER, ch, seg);
      segments[ch][seg].mask_low = BIMC_INI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_LOWER, ch, seg);
    }
  }

  /* Save remap registers. */
  for( seg = 0; seg < 4; seg ++ )
  {
    remaps[seg].addr_hi  = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_ADDR_BASE_UPPER, seg);
    remaps[seg].addr_low = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_ADDR_BASE_LOWER, seg);
    remaps[seg].mask_hi  = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_ADDR_MASK_UPPER, seg);
    remaps[seg].mask_low = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_ADDR_MASK_LOWER, seg);
    remaps[seg].op0      = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_OP0, seg);
    remaps[seg].op1      = BIMC_INI((uint8_t *)BIMC_BASE, REMAPn_OP1, seg);
  }

  valid = true;
}

//*============================================================================*/
/**
@brief 
      Restore BRIC SEGMENT and REMAP registers for SDI.
 
@dependencies
      icb_sdi_save() must have been called first.
 
@return    
      true if successful
      false if no valid data to restore
*/ 
/*============================================================================*/
bool icb_sdi_restore( void )
{
  uint32_t ch, seg;

  if( false == valid )
  {
    return false;
  }

  /* First, disable all decode segments. */
  for( ch = 0; ch < 2; ch ++ )
  {
    for( seg = 0; seg < 4; seg ++ )
    {
      BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_LOWER, ch, seg, 0);
    }
  }

  /* Restore segment decode registers.
   * First, restore any subtractive mappings.
   * Then restore any additive mappings.
   * We need to avoid any accidental mappings over hardware. */
  for( ch = 0; ch < 2; ch ++ )
  {
    for( seg = 0; seg < 4; seg ++ )
    {
      /* Only apply subtractive. */
      if( 0 != (segments[ch][seg].addr_low & BIMC_FMSK(SEGMENTn_ADDR_BASEm_LOWER, TYPE)) )
      {
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_UPPER, ch, seg, segments[ch][seg].mask_hi);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_LOWER, ch, seg, segments[ch][seg].mask_low);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_UPPER, ch, seg, segments[ch][seg].addr_hi);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_LOWER, ch, seg, segments[ch][seg].addr_low);
      }
    }
    for( seg = 0; seg < 4; seg ++ )
    {
      /* Only apply additive. */
      if( 0 == (segments[ch][seg].addr_low & BIMC_FMSK(SEGMENTn_ADDR_BASEm_LOWER, TYPE)) )
      {
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_UPPER, ch, seg, segments[ch][seg].mask_hi);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_MASKm_LOWER, ch, seg, segments[ch][seg].mask_low);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_UPPER, ch, seg, segments[ch][seg].addr_hi);
        BIMC_OUTI2((uint8_t *)BIMC_BASE, SEGMENTn_ADDR_BASEm_LOWER, ch, seg, segments[ch][seg].addr_low);
      }
    }
  }

  /* Restore remap registers. */
  for( seg = 0; seg < 4; seg ++ )
  {
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_OP0, seg, remaps[seg].op0);
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_OP1, seg, remaps[seg].op1);
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_ADDR_MASK_UPPER, seg, remaps[seg].mask_hi);
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_ADDR_MASK_LOWER, seg, remaps[seg].mask_low);
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_ADDR_BASE_UPPER, seg, remaps[seg].addr_hi);
    BIMC_OUTI((uint8_t *)BIMC_BASE, REMAPn_ADDR_BASE_LOWER, seg, remaps[seg].addr_low);
  }

  return true;
}

