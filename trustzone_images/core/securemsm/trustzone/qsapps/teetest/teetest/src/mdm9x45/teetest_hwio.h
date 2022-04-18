
/*===========================================================================
Copyright (c) 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
============================================================================*/

#ifndef __TEETEST_HWIO_H

/******************************************************************************
* MODULE: APCS_QGICDR_QGICDR_GICD
******************************************************************************/
#define APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS     (0x0B000000) //(HMSS_BASE_PHYS + 0x003c0000) //(0x0B000000)

#define HWIO_APCS_QGICDR_GICD_IPRIORITYRn_ADDR(n) (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000400 + 0x4 * (n))
#define HWIO_APCS_QGICDR_GICD_ICENABLERn_ADDR(n)  (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000180 + 0x4 * (n))
#define HWIO_APCS_QGICDR_GICD_ISPENDRn_ADDR(n)    (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000200 + 0x4 * (n))
#define HWIO_APCS_QGICDR_GICD_ISENABLERn_ADDR(n)  (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000100 + 0x4 * (n))
#define HWIO_APCS_QGICDR_GICD_ITARGETSRn_ADDR(n)  (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000800 + 0x4 * (n))
#define HWIO_APCS_QGICDR_GICD_ISPENDRn_ADDR(n)    (APCS_QGICDR_QGICDR_GICD_REG_BASE_PHYS + 0x00000200 + 0x4 * (n))

#endif  /* __TEETEST_HWIO_H */
