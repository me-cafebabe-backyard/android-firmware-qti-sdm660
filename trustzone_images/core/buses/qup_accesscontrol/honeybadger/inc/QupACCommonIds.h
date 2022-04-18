#ifndef QUPAC_COMMONIDS_H
#define QUPAC_COMMONIDS_H

/*===========================================================================
         Copyright (c) 2015-2016,2017 by QUALCOMM Technologies, Incorporated.  
              All Rights Reserved.
            QUALCOMM Confidential & Proprietary
===========================================================================*/

/*===========================================================================

  EDIT HISTORY FOR FILE


  when       who     what, where, why
  --------   ---     ------------------------------------------------------------
  02/08/17   dpk     Addressed KW issues.
  01/09/17   dpk     Changed the name to LPASS to access sensor blsp peripherals.
  08/05/16   dpk     Upgraded the driver. 
  2/03/15   sk      Created
  =============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>

#define MAX_PERIPH_QUPS 12   /* QUPS in both Peripheral BLSP 1 & 2 */
#define MAX_PERIPH_UARTS 12  /* UARTS in both Peripheral BLSP 1 & 2 */
#define MAX_SENSOR_QUPS 6    /* QUPS in Sensor BLSP */
#define MAX_SENSOR_UARTS 6   /* UARTS in Sensor BLSP */

#define BLSP_QUP1_DEV_ACCESS "/dev/buses/qup/blsp_qup1"
#define BLSP_QUP2_DEV_ACCESS "/dev/buses/qup/blsp_qup2"
#define BLSP_QUP3_DEV_ACCESS "/dev/buses/qup/blsp_qup3"
#define BLSP_QUP4_DEV_ACCESS "/dev/buses/qup/blsp_qup4"
#define BLSP_QUP5_DEV_ACCESS "/dev/buses/qup/blsp_qup5"
#define BLSP_QUP6_DEV_ACCESS "/dev/buses/qup/blsp_qup6"
#define BLSP_QUP7_DEV_ACCESS "/dev/buses/qup/blsp_qup7"
#define BLSP_QUP8_DEV_ACCESS "/dev/buses/qup/blsp_qup8"
#define BLSP_QUP9_DEV_ACCESS "/dev/buses/qup/blsp_qup9"
#define BLSP_QUP10_DEV_ACCESS "/dev/buses/qup/blsp_qup10"
#define BLSP_QUP11_DEV_ACCESS "/dev/buses/qup/blsp_qup11"
#define BLSP_QUP12_DEV_ACCESS "/dev/buses/qup/blsp_qup12"
#define SENSOR_QUP1_DEV_ACCESS  "/dev/buses/qup/sensor_qup1"
#define SENSOR_QUP2_DEV_ACCESS  "/dev/buses/qup/sensor_qup2"
#define SENSOR_QUP3_DEV_ACCESS  "/dev/buses/qup/sensor_qup3"
#define SENSOR_QUP4_DEV_ACCESS  "/dev/buses/qup/sensor_qup4"
#define SENSOR_QUP5_DEV_ACCESS  "/dev/buses/qup/sensor_qup5"
#define SENSOR_QUP6_DEV_ACCESS  "/dev/buses/qup/sensor_qup6"

#define BLSP_UART1_DEV_ACCESS "/dev/buses/uart/blsp_uart1"
#define BLSP_UART2_DEV_ACCESS "/dev/buses/uart/blsp_uart2"
#define BLSP_UART3_DEV_ACCESS "/dev/buses/uart/blsp_uart3"
#define BLSP_UART4_DEV_ACCESS "/dev/buses/uart/blsp_uart4"
#define BLSP_UART5_DEV_ACCESS "/dev/buses/uart/blsp_uart5"
#define BLSP_UART6_DEV_ACCESS "/dev/buses/uart/blsp_uart6"
#define BLSP_UART7_DEV_ACCESS "/dev/buses/uart/blsp_uart7"
#define BLSP_UART8_DEV_ACCESS "/dev/buses/uart/blsp_uart8"
#define BLSP_UART9_DEV_ACCESS "/dev/buses/uart/blsp_uart9"
#define BLSP_UART10_DEV_ACCESS "/dev/buses/uart/blsp_uart10"
#define BLSP_UART11_DEV_ACCESS "/dev/buses/uart/blsp_uart11"
#define BLSP_UART12_DEV_ACCESS "/dev/buses/uart/blsp_uart12"
#define SENSOR_UART1_DEV_ACCESS  "/dev/buses/uart/sensor_uart1"
#define SENSOR_UART2_DEV_ACCESS  "/dev/buses/uart/sensor_uart2"
#define SENSOR_UART3_DEV_ACCESS  "/dev/buses/uart/sensor_uart3"
#define SENSOR_UART4_DEV_ACCESS  "/dev/buses/uart/sensor_uart4"
#define SENSOR_UART5_DEV_ACCESS  "/dev/buses/uart/sensor_uart5"
#define SENSOR_UART6_DEV_ACCESS  "/dev/buses/uart/sensor_uart6"


#define BLSP_QUP1_DEV_CONFIG "/dev/buses/qup/blsp_qup1_cfg"
#define BLSP_QUP2_DEV_CONFIG "/dev/buses/qup/blsp_qup2_cfg"
#define BLSP_QUP3_DEV_CONFIG "/dev/buses/qup/blsp_qup3_cfg"
#define BLSP_QUP4_DEV_CONFIG "/dev/buses/qup/blsp_qup4_cfg"
#define BLSP_QUP5_DEV_CONFIG "/dev/buses/qup/blsp_qup5_cfg"
#define BLSP_QUP6_DEV_CONFIG "/dev/buses/qup/blsp_qup6_cfg"
#define BLSP_QUP7_DEV_CONFIG "/dev/buses/qup/blsp_qup7_cfg"
#define BLSP_QUP8_DEV_CONFIG "/dev/buses/qup/blsp_qup8_cfg"
#define BLSP_QUP9_DEV_CONFIG "/dev/buses/qup/blsp_qup9_cfg"
#define BLSP_QUP10_DEV_CONFIG "/dev/buses/qup/blsp_qup10_cfg"
#define BLSP_QUP11_DEV_CONFIG "/dev/buses/qup/blsp_qup11_cfg"
#define BLSP_QUP12_DEV_CONFIG "/dev/buses/qup/blsp_qup12_cfg"
#define SENSOR_QUP1_DEV_CONFIG "/dev/buses/qup/sensor_qup1_cfg"
#define SENSOR_QUP2_DEV_CONFIG "/dev/buses/qup/sensor_qup2_cfg"
#define SENSOR_QUP3_DEV_CONFIG "/dev/buses/qup/sensor_qup3_cfg"
#define SENSOR_QUP4_DEV_CONFIG "/dev/buses/qup/sensor_qup4_cfg"
#define SENSOR_QUP5_DEV_CONFIG "/dev/buses/qup/sensor_qup5_cfg"
#define SENSOR_QUP6_DEV_CONFIG "/dev/buses/qup/sensor_qup6_cfg"

#define BLSP_UART1_DEV_CONFIG "/dev/buses/uart/blsp_uart1_cfg"
#define BLSP_UART2_DEV_CONFIG "/dev/buses/uart/blsp_uart2_cfg"
#define BLSP_UART3_DEV_CONFIG "/dev/buses/uart/blsp_uart3_cfg"
#define BLSP_UART4_DEV_CONFIG "/dev/buses/uart/blsp_uart4_cfg"
#define BLSP_UART5_DEV_CONFIG "/dev/buses/uart/blsp_uart5_cfg"
#define BLSP_UART6_DEV_CONFIG "/dev/buses/uart/blsp_uart6_cfg"
#define BLSP_UART7_DEV_CONFIG "/dev/buses/uart/blsp_uart7_cfg"
#define BLSP_UART8_DEV_CONFIG "/dev/buses/uart/blsp_uart8_cfg"
#define BLSP_UART9_DEV_CONFIG "/dev/buses/uart/blsp_uart9_cfg"
#define BLSP_UART10_DEV_CONFIG "/dev/buses/uart/blsp_uart10_cfg"
#define BLSP_UART11_DEV_CONFIG "/dev/buses/uart/blsp_uart11_cfg"
#define BLSP_UART12_DEV_CONFIG "/dev/buses/uart/blsp_uart12_cfg"
#define SENSOR_UART1_DEV_CONFIG "/dev/buses/uart/sensor_uart1_cfg"
#define SENSOR_UART2_DEV_CONFIG "/dev/buses/uart/sensor_uart2_cfg"
#define SENSOR_UART3_DEV_CONFIG "/dev/buses/uart/sensor_uart3_cfg"
#define SENSOR_UART4_DEV_CONFIG "/dev/buses/uart/sensor_uart4_cfg"
#define SENSOR_UART5_DEV_CONFIG "/dev/buses/uart/sensor_uart5_cfg"
#define SENSOR_UART6_DEV_CONFIG "/dev/buses/uart/sensor_uart6_cfg"


/* TODO: If AccessControl.h is visible to both TZ and Hyp, we may be able to use the enum defines from there directly.
 * Though, DAL properties cannot be enum value if its an array type
 */
#define AC_NONE  0
#define AC_TZ  1
#define AC_RPM  2
#define AC_HLOS  3
#define AC_HYP  4
#define AC_SSC_Q6_ELF 5
#define AC_ADSP_Q6_ELF 6 // Single 
#define AC_SSC_HLOS 7   // ??, may be we combine this with other SSC one //
#define AC_CP_TOUCH 8
#define AC_CP_BITSTREAM 9
#define AC_CP_PIXEL 10
#define AC_CP_NON_PIXEL 11
#define AC_VIDEO_FW 12
#define AC_CP_CAMERA 13
#define AC_HLOS_UNMAPPED 14
#define AC_MSS_MSA 15
#define AC_MSS_NONMSA 16
#define AC_UNMAPPED 17
#define AC_LPASS 22
#define BLSP_AC_LAST 19 // This indicates the number of AC owners defined
#define AC_DEFAULT 0xFF// Default as in retain whatever in SMMU static config table

//TODO: Check if below enum list is still needed 
typedef enum {
   PERIPH_ENUM_MIN = 0,
   BLSP_QUPID_START = PERIPH_ENUM_MIN,
   BLSP_QUP1 = BLSP_QUPID_START,
   BLSP_QUP2,
   BLSP_QUP3,
   BLSP_QUP4,
   BLSP_QUP5,
   BLSP_QUP6,
   BLSP_QUP7,
   BLSP_QUP8,
   BLSP_QUP9,
   BLSP_QUP10,
   BLSP_QUP11,
   BLSP_QUP12,
   SENSOR_QUPID_START,
   SENSOR_QUP1 = SENSOR_QUPID_START,
   SENSOR_QUP2,
   SENSOR_QUP3,
   SENSOR_QUP4,
   SENSOR_QUP5,
   SENSOR_QUP6,
   BLSP_UARTID_START,
   BLSP_UART1 = BLSP_UARTID_START,
   BLSP_UART2,
   BLSP_UART3,
   BLSP_UART4,
   BLSP_UART5,
   BLSP_UART6,
   BLSP_UART7,
   BLSP_UART8,
   BLSP_UART9,
   BLSP_UART10,
   BLSP_UART11,
   BLSP_UART12,
   SENSOR_UARTID_START,
   SENSOR_UART1 = SENSOR_UARTID_START,
   SENSOR_UART2,
   SENSOR_UART3,
   SENSOR_UART4,
   SENSOR_UART5,
   SENSOR_UART6,
   PERIPH_MAX_ID
} BLSP_PERIPHID;

typedef enum {
   PERIPH_BLSP1 = 1, 
   PERIPH_BLSP2 = 2, 
   SENSOR_BLSP = 3 
}QUPAC_BLSPID;


#endif

