/******************************************************************************
* File: dsp_cache.S
*
* Copyright (c) 2016 Qualcomm Technologies, Inc.
* All Rights Reserved
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*
******************************************************************************/

.global cache_invalidate
.type   cache_invalidate, @function
   cache_invalidate:
   r3 = lsr(r1,#5)
   loop0(1f,r3)
   .falign
1:
   {
      dcinva(r0)
      r0 = add(r0,#32)
   }:endloop0
   jumpr r31
.size cache_invalidate, .-cache_invalidate


.global cache_clean
.type   cache_clean, @function
   cache_clean:
   {
      p0 = cmp.eq(r1,#0)
      if (p0.new) jump:nt 2f
      r3 = lsr(r1,#5)
   }
   loop0(1f,r3)
   .falign
1:
   {
      dccleana(r0)
      r0 = add(r0,#32)
   }:endloop0
2:
   syncht
   jumpr r31
.size cache_clean, .-cache_clean
