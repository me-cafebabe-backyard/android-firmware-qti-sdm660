#ifndef _SPM_HWIO_H_
#define _SPM_HWIO_H_
/*==============================================================================
  FILE:         spm_hwio.h

  OVERVIEW:     This file contains the generic HWIO wrapper macros for SPM.

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/hwio/inc/spm_hwio.h#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "HALhwio.h"
#include "spm_hal_hwio.h"

/* Ensure prefix is defined at build level */
#ifndef SPM_HWIO_PREFIX
#error "SPM_HWIO_PREFIX is undefined"
#endif

/*==========================================================================
 *                                MACROS
 *=========================================================================*/
/* These macros are used to defer register name - build script can provide
 * the necessary parameters to construct actual register name.
 *
 * @Note
 * This list does not cover all HWIO macros. Only those macros used by 
 * SPM HAL layer are defined here. If required, new wrapper macros can
 * be added here. */
#define _SPM_HWIO_CONCAT_NAME(prefix, name)                prefix##_##name
#define _SPM_HWIO_CONCAT_BMSK(prefix, reg, field)          HWIO_##prefix##_##reg##_##field##_BMSK
#define SPM_HWIO_CONCAT_NAME(prefix, name)                 _SPM_HWIO_CONCAT_NAME(prefix, name)
#define SPM_HWIO_CONCAT_BMSK(prefix, reg, field)           _SPM_HWIO_CONCAT_BMSK(prefix, reg, field)
#define SPM_HWIO_EXPAND_NAME(name)                         SPM_HWIO_CONCAT_NAME(SPM_HWIO_PREFIX, name)
#define SPM_HWIO_EXPAND_BMSK(reg, field)                   SPM_HWIO_CONCAT_BMSK(SPM_HWIO_PREFIX, reg, field)

#define SPM_HWIO_RMSK(name)                                HWIO_RMSK(SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_RMSKI(name, index)                        HWIO_RMSKI(SPM_HWIO_EXPAND_NAME(name), index)
#define SPM_HWIO_SHFT(name, field)                         HWIO_SHFT(SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_FMSK(name, field)                         HWIO_FMSK(SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_VAL(name, field, val)                     HWIO_VAL(SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_FVAL(name, field, val)                    HWIO_FVAL(SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_FVALV(name, field, val)                   HWIO_FVALV(SPM_HWIO_EXPAND_NAME(name), field, val)

#ifdef SPM_EXPLICIT_HWIO_BASE_ADDR
/* Macros for targets that require specific base addressing */

#define SPM_HWIO_ADDR(base, name)                         HWIO_ADDRX(base, SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_ADDRI(base, name, index)                 HWIO_ADDRXI(base, SPM_HWIO_EXPAND_NAME(name), index)

#define SPM_HWIO_IN(base, name)                           HWIO_INX(base, SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_INI(base, name, index)                   HWIO_INXI(base, SPM_HWIO_EXPAND_NAME(name), index)
#define SPM_HWIO_INM(base, name, mask)                    HWIO_INXM(base, SPM_HWIO_EXPAND_NAME(name), mask)
#define SPM_HWIO_INMI(base, name, index, mask)            HWIO_INXMI(base, SPM_HWIO_EXPAND_NAME(name), index, mask)
#define SPM_HWIO_INF(base, name, field)                   HWIO_INXF(base, SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_INFI(base, name, field, index)           HWIO_INXFI(base, SPM_HWIO_EXPAND_NAME(name), field, index)

#define SPM_HWIO_OUT(base, name, val)                     HWIO_OUTX(base, SPM_HWIO_EXPAND_NAME(name), val)
#define SPM_HWIO_OUTI(base, name, index, val)             HWIO_OUTXI(base, SPM_HWIO_EXPAND_NAME(name), index, val)
#define SPM_HWIO_OUTM(base, name, mask, val)              HWIO_OUTXM(base, SPM_HWIO_EXPAND_NAME(name), mask, val)
#define SPM_HWIO_OUTMI(base, name, index, mask, val)      HWIO_OUTXMI(base, SPM_HWIO_EXPAND_NAME(name), index, mask, val)
#define SPM_HWIO_OUTF(base, name, field, val)             HWIO_OUTXF(base, SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_OUTFI(base, name, index, field, val)     HWIO_OUTXFI(base, SPM_HWIO_EXPAND_NAME(name), index, field, val)

#else
/* Macros for targets that do not require specific base addressing
 * (i.e. only targets with a single SPM and/or have base addressing as 
 *  part of the HWIO macros themselves) */ 
#define SPM_HWIO_ADDR(base, name)                         HWIO_ADDR(SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_ADDRI(base, name, index)                 HWIO_ADDRI(SPM_HWIO_EXPAND_NAME(name), index)

#define SPM_HWIO_IN(base, name)                           HWIO_IN(SPM_HWIO_EXPAND_NAME(name))
#define SPM_HWIO_INI(base, name, index)                   HWIO_INI(SPM_HWIO_EXPAND_NAME(name), index)
#define SPM_HWIO_INM(base, name, mask)                    HWIO_INM(SPM_HWIO_EXPAND_NAME(name), mask)
#define SPM_HWIO_INMI(base, name, index, mask)            HWIO_INMI(SPM_HWIO_EXPAND_NAME(name), index, mask)
#define SPM_HWIO_INF(base, name, field)                   HWIO_INF(SPM_HWIO_EXPAND_NAME(name), field)
#define SPM_HWIO_INFI(base, name, field, index)           HWIO_INFI(SPM_HWIO_EXPAND_NAME(name), field, index)

#define SPM_HWIO_OUT(base, name, val)                     HWIO_OUT(SPM_HWIO_EXPAND_NAME(name), val)
#define SPM_HWIO_OUTI(base, name, index, val)             HWIO_OUTI(SPM_HWIO_EXPAND_NAME(name), index, val)
#define SPM_HWIO_OUTM(base, name, mask, val)              HWIO_OUTM(SPM_HWIO_EXPAND_NAME(name), mask, val)
#define SPM_HWIO_OUTMI(base, name, index, mask, val)      HWIO_OUTMI(SPM_HWIO_EXPAND_NAME(name), index, mask, val)
#define SPM_HWIO_OUTF(base, name, field, val)             HWIO_OUTF(SPM_HWIO_EXPAND_NAME(name), field, val)
#define SPM_HWIO_OUTFI(base, name, index, field, val)     HWIO_OUTFI(SPM_HWIO_EXPAND_NAME(name), index, field, val)

#endif /* SPM_EXPLICIT_HWIO_BASE_ADDR */

/* Enable spm PMIC support based on target */
#if (0 != SPM_HWIO_RMSK(PMIC_DATA_n))
#define SPM_TARGET_PMIC_SUPPORTED
#endif

#ifdef __cplusplus
}
#endif

#endif /* _SPM_HWIO_H_ */

