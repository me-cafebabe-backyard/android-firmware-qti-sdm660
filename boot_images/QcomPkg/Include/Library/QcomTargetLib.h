/** @file QcomTargetLib.h
   
  Contains Qualcomm target specific library functions.

  Copyright (c) 2012,2015, Qualcomm Technologies, Inc. All rights reserved. 

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/17/15   jb      Add define for debug mode
 03/13/12   jz      Created
=============================================================================*/
#ifndef __QCOMTARGETLIB_H__
#define __QCOMTARGETLIB_H__

#include <Base.h>

/* Macro used to determine if production mode is enabled or disabled */
#ifdef PRODMODE
#define PRODMODE_ENABLED TRUE
#define PRODMODE_DISABLED FALSE
#else
#define PRODMODE_ENABLED FALSE
#define PRODMODE_DISABLED TRUE
#endif

#ifdef MDEPKG_NDEBUG
#define DEBUGMODE_ENABLED FALSE
#define DEBUGMODE_DISABLED TRUE
#else
#define DEBUGMODE_ENABLED TRUE
#define DEBUGMODE_DISABLED FALSE
#endif


#endif /* __QCOMTARGETLIB_H__ */

