/*===========================================================================

            GLink RPM transport 9x55 APSS Configuration Structures

=============================================================================

  @file
    xport_rpm_devcfg_<msm_id>_<proc>.c

    Contains structures to be used in Glink RPM trasnport configuration.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies, Inc. Confidential and Proprietary.
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE


when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/13/15   db      Initial version
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "DALStdDef.h"
#include "xport_rpm_config.h"
#include "msmhwiobase.h"
#include "smem_type.h"

/*===========================================================================
                           MACRO DEFINITIONS
===========================================================================*/

#define XPORT_RPM_MSG_RAM_BASE        RPM_SS_MSG_RAM_START_ADDRESS_BASE
#define XPORT_RPM_MSG_RAM_SIZE        RPM_SS_MSG_RAM_START_ADDRESS_BASE_SIZE

/** Base and size of Glink RPM transport ToC in MSG RAM */
#define XPORT_RPM_MSG_TOC_SIZE        0x100
#define XPORT_RPM_MSG_TOC_BASE        (XPORT_RPM_MSG_RAM_BASE + \
                                       XPORT_RPM_MSG_RAM_SIZE - \
                                       XPORT_RPM_MSG_TOC_SIZE)

/*===========================================================================
                        DATA DECLARATIONS
===========================================================================*/
/** Local processor details */
const xport_rpm_config_proc_type xport_rpm_devcfg_proc_info = 
{
  "dsps",                           /* Local processor name     */
  SMEM_SSC,                         /* Local processor host id  */
  (uint8*)XPORT_RPM_MSG_RAM_BASE,   /* Message RAM base address */
  XPORT_RPM_MSG_RAM_SIZE,           /* Message RAM size         */
  (uint32*)XPORT_RPM_MSG_TOC_BASE,  /* TOC base address         */
  XPORT_RPM_MSG_TOC_SIZE            /* TOC size                 */
};

/** Remote processors details */
const xport_rpm_config_type xport_rpm_devcfg_remote_procs[] =
{
  /* SLPI->Rpm */
  {
    "rpm",                /* Remote host name        */
    XPORT_RPM_SC2R_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_R2SC_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_RPM,
      DALIPCINT_GP_0
    },
    74                    /* Incoming interrupt      */
  },
  
  /* END */
  {
    NULL,                  /* Remote host name        */
    0,                     /* Tx FIFO ID in RPM ToC   */
    0,                     /* Rx FIFO ID in RPM ToC   */
    {                      /* Outgoing interrupt      */
      DALIPCINT_PROC_32BITS,
      DALIPCINT_INT_32BITS
    },
    0                      /* Incoming interrupt      */
  }
};


