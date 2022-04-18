/*===========================================================================

                GLink RPM transport Configuration

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
07/26/16   rv      Initial version
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
/** Base and size of RPM MSG RAM */
#define XPORT_RPM_MSG_RAM_BASE        (RPM_MSG_RAM_BASE)
#define XPORT_RPM_MSG_RAM_SIZE        (RPM_MSG_RAM_BASE_SIZE)

/** Base and size of Glink RPM transport ToC in MSG RAM */
#define XPORT_RPM_MSG_TOC_SIZE        (0x100)
#define XPORT_RPM_MSG_TOC_BASE        (XPORT_RPM_MSG_RAM_BASE + \
                                       XPORT_RPM_MSG_RAM_SIZE - \
                                       XPORT_RPM_MSG_TOC_SIZE)

/*===========================================================================
                        DATA DECLARATIONS
===========================================================================*/
/** Local processor details */
const xport_rpm_config_proc_type xport_rpm_devcfg_proc_info = 
{
  "rpm",                              /* Local processor name     */
  SMEM_RPM ,                          /* Local processor host id  */
  (uint8*)XPORT_RPM_MSG_RAM_BASE,             /* Message RAM base address */
  XPORT_RPM_MSG_RAM_SIZE,             /* Message RAM size         */
  (uint32*)XPORT_RPM_MSG_TOC_BASE,    /* TOC base address         */
  XPORT_RPM_MSG_TOC_SIZE              /* TOC size                 */
};

/** Remote processors details */
const xport_rpm_config_type xport_rpm_devcfg_remote_procs[] =
{
  /* Rpm->Apps */
  {
    "apss",               /* Remote host name        */
    XPORT_RPM_R2AP_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_AP2R_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_ACPU,
      DALIPCINT_GP_2,      
    },
    8                     /* Incoming interrupt      */
  },

  /* Rpm->Mpss */
  {
    "mpss",               /* Remote host name        */
    XPORT_RPM_R2MP_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_MP2R_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_MCPU,
      DALIPCINT_GP_2,
    },
    46                    /* Incoming interrupt      */
  },
  
  /* Rpm->Adsp */
  {
    "lpass",              /* Remote host name        */
    XPORT_RPM_R2AD_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_AD2R_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_ADSP,
      DALIPCINT_GP_2,      
    },
    20                    /* Incoming interrupt      */
  },

  /* Rpm->cdsp */
  {
    "cdsp",               /* Remote host name        */
    XPORT_RPM_R2CD_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_CD2R_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_CDSP,
      DALIPCINT_GP_2,      
    },
    36                    /* Incoming interrupt      */
  },

  /* Rpm->TZ */
  {
    "tz",                 /* Remote host name        */
    XPORT_RPM_R2TZ_ID,    /* Tx FIFO ID in RPM ToC   */
    XPORT_RPM_TZ2R_ID,    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_TZ,
      DALIPCINT_GP_HIGH,      
    },
    11                    /* Incoming interrupt      */
  },
  
  /* END */
  {
    NULL,                 /* Remote host name        */
    0,                    /* Tx FIFO ID in RPM ToC   */
    0,                    /* Rx FIFO ID in RPM ToC   */
    {                     /* Outgoing interrupt      */
      DALIPCINT_PROC_32BITS,
      DALIPCINT_INT_32BITS,      
    },
    0                     /* Incoming interrupt      */
  }
};

/** TOC details */
const xport_rpm_config_toc_type xport_rpm_devcfg_toc[] = 
{
  /* Apps-Rpm */
  {
    XPORT_RPM_AP2R_ID,
    SMEM_APPS,
    0x6f8
  },
  /* Rpm-Apps */
  {
    XPORT_RPM_R2AP_ID,
    SMEM_APPS,
    0x6f8
  },
  /* Mpss-Rpm */
  {
    XPORT_RPM_MP2R_ID,
    SMEM_MODEM,
    0x6f8
  },
  /* Rpm-Mpss */
  {
    XPORT_RPM_R2MP_ID,
    SMEM_MODEM,
    0x6f8
  },
  /* Adsp-Rpm */
  {
    XPORT_RPM_AD2R_ID,
    SMEM_ADSP,
    0x6f8
  },
  /* Rpm-Adsp */
  {
    XPORT_RPM_R2AD_ID,
    SMEM_ADSP,
    0x6f8
  },
  /* cdsp-Rpm */
  {
    XPORT_RPM_CD2R_ID,
    SMEM_CDSP,
    0x6f8
  },
  /* Rpm-cdsp */
  {
    XPORT_RPM_R2CD_ID,
    SMEM_CDSP,
    0x6f8
  },
  /* TZ-Rpm */
  {
    XPORT_RPM_TZ2R_ID,
    SMEM_TZ,
    0x6f8
  },
  /* Rpm-TZ */
  {
    XPORT_RPM_R2TZ_ID,
    SMEM_TZ,
    0x6f8
  },
  
  /* END */
  {
    0,
    SMEM_INVALID_HOST,
    0
  }
};

