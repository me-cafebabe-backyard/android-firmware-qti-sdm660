/*=========================================================================
                       QDSS e-fuse check

GENERAL DESCRIPTION 
   The interface to check efuses associated with the QDSS for accessing its 
   trace functionality is implemented. The fuses that are checked include 
   DBGEN, SPIDEN, NIDEN and SPNIDEN. The functionality controlled by the fuses 
   are as follows. DBGEN controls non-secure invasive debugging, SPIDEN controls
   secured invasive debugging, NIDEN controls non-secure non-invasive debugging 
   and SPNIDEN controls secure non-invasive debugging.

   According to the ARM Coresight architecture, in all cases, the fuse 
   setting for invasive debugging overrides settings for non-invasive debugging.
    
 
EXTERNALIZED FUNCTIONS
   qdss_fuse_trace_access
 
 
INITIALIZATION AND SEQUENCING REQUIREMENTS
   Requires System FPB clock to access the efuse registers.
   

      Copyright (c) 2012 by Qualcomm Technologies, Inc.  All Rights Reserved.
==========================================================================*/

/*========================================================================== 
 $Header: //components/rel/rpm.bf/1.8/core/debugtrace/common/src/qdss_fuse_check.c#1 $
==========================================================================*/  

#include "Chipinfo.h"

#include "qdss_fuse_check.h"

#define TRUE  1
#define FALSE 0

/*
Input: None
   Fuse check functions that clock drivers uses. 
   This always returns TRUE. There is no harm in turnig clocks on 
   even if fuse is blown. Before QDSS initialiazation STM AUTHSTATUS register 
   is used to determine the actual fuse state.

Description:

Return:
   0 - Trace access not possible
   1 - Trace access is possible
*/


unsigned int qdss_fuse_trace_access(void)
{
   return TRUE;
}
