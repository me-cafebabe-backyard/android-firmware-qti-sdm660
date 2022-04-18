#ifndef __DDR_CORES_H__
#define __DDR_CORES_H__

/*=============================================================================

                                DDR CORES
                                Header File
GENERAL DESCRIPTION
 This file defines the DDR controller and DDR PHY core data structures


Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DSFTargetLib/rpm/sns_api/ddr_cores.h#4 $
$DateTime: 2016/10/12 00:05:04 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
12/01/13   dp      Initial version.
==============================================================================*/
/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALcomdef.h"

/*==============================================================================
                                  TYPES
==============================================================================*/

/**********************/
/*** DDR Controller ***/
/**********************/

struct ddr_ctlr
{
  struct
  {
    uint32 arch;
    uint32 major;
    uint32 minor;
  } version;
};

/**********************/
/*** DDR PHY  ***/
/**********************/

struct ddr_phy
{
    struct
    {
      uint32 major;
      uint32 minor;
    } version;
};

#endif /* __DDR_CORES_H__ */
