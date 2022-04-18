
/*===========================================================================
Copyright (c) 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
============================================================================*/

#include "teetest.h"
#include "teetest_mmu.h"

extern l1_tt_t  *l1;
extern l2_tt_t   l2[NUM_L2_TTS];

static int       cur_num_l2_tts = 0;

extern void clean_and_inval_dcache_region(uint32 vaddr, uint32 len);

static uint32 get_num_ttes(uint32 level, uint32 v_addr, uint32 size_kb) {
  if (0 == size_kb || level > 2)
    return 0;

  switch (level) {
  case 1:
    return KB2NUML1TTES(B2KB(v_addr) + size_kb - 1) - B2NUML1TTES(v_addr) + 1;
  case 2:
    return KB2NUML2TTES(B2KB(v_addr) + size_kb - 1) - B2NUML2TTES(v_addr) + 1;
  }
  return 0;
}

static l2_tt_t* l1_walk(sd_tte_t l1_tte) {
  return (l2_tt_t *) (uint32)(l1_tte & 0xFFFFFC00);
}

/*
   Checks the L1 entries at the given address to see how many already
   point to allocated level two translation tables and how many need
   new allocations

   retval number of level two translation tables needed for the given
          virtual address and number of 1 MB sections
*/
static int get_num_l2tts_needed(
  const uint32 v_addr, 
  const uint32 num_l1ttes) {
  uint32    l1tte_ii, tt_ii;
  int       num_l2tts_needed = 0;
  sd_tte_t *l1_tt_ptr        = &l1->tt[0];

  for (l1tte_ii = 0; l1tte_ii < num_l1ttes; l1tte_ii++) {
    tt_ii = B2L1TTE(v_addr) + l1tte_ii;

    /* Does this L1 TTE already point to an allocated L2 TTE? */
    if ((*(l1_tt_ptr + tt_ii) & 0x3) != L1_SECONDARY_TTE_DESCRIPTOR) {
      num_l2tts_needed++;
    }
  }
  return num_l2tts_needed;
}

static int num_l2tts_available(void)
{
  return (NUM_L2_TTS - cur_num_l2_tts);
}

static l2_tt_t* l2tt_iter_start(l2tt_iter_t* iter) {
  *iter = 0;
  return &l2[0];
}

static l2_tt_t* l2tt_iter_next(l2tt_iter_t* iter) {
  (*iter)++;

  if (*iter < ARRAY_SIZE(l2)) {
    return &l2[*iter];
  } else {
    return NULL;
  }
}

static boolean is_l2tt_used(l2_tt_t* tt_ptr) {
  /* Not currently using large L2 pages, so this is our "free" indication */
  return (((uint32) tt_ptr->tt[0] & 0x3) != L2_LARGE_PAGE_DESCRIPTOR);
}

static int alloc_l2tt(l2_tt_t** l2tt_ptr_ptr) {
  l2_tt_t*    tt_ptr = 0;
  l2tt_iter_t iter;

  /* Any available memory for L2 pages? */
  if (num_l2tts_available() == 0) {
    /* Unrecoverable error */
    tee_panic();
  }

  /* Loop through first page entry in each L2 remap area and look for
   * the first available remap area */
  for (tt_ptr = l2tt_iter_start(&iter); tt_ptr != NULL; tt_ptr = l2tt_iter_next(&iter)) {
    if (!is_l2tt_used(tt_ptr)) {
      /* Found an open slot */
      *l2tt_ptr_ptr = tt_ptr;
      cur_num_l2_tts++;
      return E_SUCCESS;
    }
  }

  /* Unrecoverable error */
  tee_panic();

  /* Shouldn't get here */
  return E_FAILURE;
}

/**
   For a given virtual address, this function will retrieve the level
   two translation table address, if the level one translation table
   was programmed to point to one, or it will return a newly allocated
   level two translation table and return the L1 translation table
   configuration, translated to L2 format and the old physical address
   mapping of the L1 translation table.

   @retval E_SUCCESS Level one and two translation tables populated
                     successfully

   @pre l1 must be allocated
   @pre l2 must be allocated
*/
static void get_or_make_l2tt (uint32    v_addr,    l2_tt_t** l2_tt_ptr_ptr,
                              uint32*   l1_p_addr, boolean*  newl2tt) {
  uint32    tt_ii     =  B2L1TTE(v_addr);
  sd_tte_t *l1_tt_ptr = &l1->tt[0];

  if ((*(l1_tt_ptr + tt_ii) & 0x3) == L1_SECONDARY_TTE_DESCRIPTOR) {
    *l2_tt_ptr_ptr = l1_walk(*(l1_tt_ptr + tt_ii));
    *l1_p_addr     = 0;
    *newl2tt       = FALSE;
  } else {
    if (alloc_l2tt(l2_tt_ptr_ptr) != E_SUCCESS) {
      /* Error scenario */
      tee_panic();
    }
    *newl2tt       = TRUE;
    *l1_p_addr     = (*(l1_tt_ptr + tt_ii) & 0xFFF00000);
  }
}

/* For simplicity, map everything with 4KB pages */
void tee_mmu_map(
  unsigned int v_addr,
  unsigned int p_addr,
  unsigned int len,
  unsigned int cfg) {

  const uint32 num_l1ttes    = get_num_ttes(1, v_addr, len);
  const uint32 num_l2ttes    = get_num_ttes(2, v_addr, len);
  const uint32 num_l2tts_req = get_num_l2tts_needed(v_addr, num_l1ttes);

  if (num_l2tts_req > num_l2tts_available()) {
    /* Error condition */
    tee_panic();
  }

  sd_tte_t *l1_tt_ptr = &l1->tt[0];
  l2_tt_t  *l2_tt_ptr;
  uint32    l1_p_addr;
  uint32    tt_offset;
  uint32    tt_base;
  uint32    tt_limit;
  uint32    tt_ii;
  boolean   newl2tt;
  
  tt_base  = B2L1TTE(v_addr);
  tt_limit = tt_base + num_l1ttes;

  /* First initialize the first level descriptor for each 1 MB High 22
     bits provide the physical base address of the level 2 translation
     table */

  /* L1 TTE for Page Diagram
      _______________________________________________________________________
     |                                                  | |        | |   |   |
     |31----------------------------------------------10|9|8------5|4|3 2|1 0|
     |         level 2 PT Address base                  |0| DOMAIN |0|0 0|0 1|
     |__________________________________________________|_|________|_|___|___|
  */

  /* We'll have to do each step for every l1 translation table entry
     that gets replaced with a pointer to a l2 translation table
   */
  for (uint32 l1tt_ii = 0; l1tt_ii < num_l1ttes; l1tt_ii++) {
    get_or_make_l2tt( v_addr + L1TTE2B(l1tt_ii), &l2_tt_ptr, 
                     &l1_p_addr,                 &newl2tt);

    /* The given mapping may not begin at the 1 MB boundary for the
       first L2 TTE of the given memory block.  Calculate the l2
       translation table index for the start of the given mapping. */
    tt_offset = (l1tt_ii == 0) ? B2L2TTE(v_addr) : 0;

    /* If there are multiple L2 TTs needed, all L2 TTs will iterate to
       the end except the last one */
    tt_limit = (l1tt_ii == (num_l1ttes - 1)) ?
      B2L2TTE(v_addr) + num_l2ttes - NUM_L2_TTES_PER_L1_TTE * l1tt_ii :
      NUM_L2_TTES_PER_L1_TTE;

    /* Now we need to program the L2 translation table */
    /* Page Diagram
        _____________________________________________________________________
       |                               |  |  |     |     |       |  |  |  |  |
       |31---------------------------12|11|10|--9--|8---6|5-----4|-3|-2|-1|-0|
       |     Phys Address base         |nG| S|AP[2]| TEX |AP[1:0]| C| B| 1|XN|
       |_______________________________|__|__|_____|_____|_______|__|__|__|__|
    */

    /* Iterate through all the 4KB pages in the 1MB section */
    for (tt_ii = 0; tt_ii < NUM_L2_TTES_PER_L1_TTE; tt_ii++) {
      /* If the index lies between the base index and the limit, then
         this is the given section we need to map */
      if ((tt_offset <= tt_ii) && (tt_ii < tt_limit)) {
        l2_tt_ptr->tt[tt_ii] = (((v_addr & L1_ADDR_MSK) +
                                 L2TTE2B(tt_ii) + L1TTE2B(l1tt_ii)) | cfg);

        /* Invalidate TLB for each entry as it's updated */
        asm ("dsb sy \n mcr p15,0,%0,c8,c3,1" :: "r"
             ((uint64) ((v_addr & L1_ADDR_MSK) + L2TTE2B(tt_ii) +
                        L1TTE2B(l1tt_ii)) >> 12));
      }
      /* If this is a newly mapped L2 TT, TLB invalidation is done below
         when the L1 is changed to a L2 pointer. */
      else if (newl2tt) {
        l2_tt_ptr->tt[tt_ii] = 0;
      }
    }

    /* Enter the L2 base address and mark the descriptor for L2
     * translation table and default L1 TTE for L2 TTE info.
     */
    if (newl2tt) {
      uint32 tt_ii_local = B2L1TTE(v_addr + L1TTE2B(l1tt_ii));

      /* Write entire new L2TT to DDR */
      clean_and_inval_dcache_region((v_addr_t) l2_tt_ptr, sizeof(*l2_tt_ptr));

      *(l1_tt_ptr + tt_ii_local) =
        ((uint32) l2_tt_ptr | L1_DEFAULT_DOMAIN | L1_SECONDARY_TTE_DESCRIPTOR);
      asm ("dsb sy \n mcr p15,0,%0,c8,c3,1" :: "r"
           ((uint64) (L1TTE2B(tt_ii_local) >> 12)));
      clean_and_inval_dcache_region((v_addr_t) &*(l1_tt_ptr + tt_ii_local),
                                    sizeof(*(l1_tt_ptr + tt_ii)));
    } else {
      /* Write only changes out to DDR */
      clean_and_inval_dcache_region((v_addr_t) &l2_tt_ptr->tt[tt_offset],
                                    (tt_limit - tt_offset) *
                                    sizeof(l2_tt_ptr->tt[tt_offset]));
    }
  }

  asm ("dsb sy \n isb"::);
}

/* Set up any structures and variables required */
void tee_mmu_init(void) {
  /* Set up the L2 tables */
  for (uint32 i = 0;i < NUM_L2_TTS;i++) {
    for (uint32 j = 0;j < NUM_L2_TTES_PER_L1_TTE;j++) {
      /* Not currently using large L2 pages, so this is our "free" indication */
      l2[i].tt[j] = L2_LARGE_PAGE_DESCRIPTOR;
    }
  }
}

