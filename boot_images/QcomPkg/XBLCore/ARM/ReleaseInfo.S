//------------------------------------------------------------------------------ 
//
// Copyright (c) 2012-2014,2016, Qualcomm Technologies Inc. All rights reserved.
//
//------------------------------------------------------------------------------

//=============================================================================
//                              EDIT HISTORY
//
//
// when       who     what, where, why
// --------   ---     ---------------------------------------------------------
// 11/29/16   aus     Added support for 32 bit LLVM compilation
//
//============================================================================
  
#include <ReleaseInfo.h>
#define LINE_FEED  0x0A

#define REL_INF_STRING  REL_LABEL_FIELD, REL_LABEL, " ",    \
                        REL_DATE_FIELD, REL_DATE, " ",      \
                        BUILD_VER_FIELD, BUILD_VER1, " ",   \
                        BUILD_DATE_FIELD,  BUILD_DATE, " ", \
                        BUILD_TIME_FIELD,  BUILD_TIME, " " 

.text
.align 2

.global _ReleaseInfo
.global _UefiInfoBlockPtr
.global _UefiRelInfoString
        
.extern _ModuleEntryPoint

_ReleaseInfo:
  b _ModuleEntryPoint

.data
.align 2
_UefiInfoBlockPtr:
.long 0

.align 2
_UefiRelInfoString:
 .ascii REL_INF_STRING

.align 2
.long 0
  
