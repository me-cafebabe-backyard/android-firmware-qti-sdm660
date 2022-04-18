#ifndef PNGLIBCONF_H
#define PNGLIBCONF_H

/*===========================================================================
   Copyright (c) 2013 Qualcomm Technologies, Inc.       
   All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.7.1/securemsm/sse/qsee/SecureDisplay/libpng/include/pnglibconf.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
07/02/13   ts       Initial version.

===========================================================================*/
#define PNG_IDAT_READ_SIZE PNG_ZBUF_SIZE

#ifndef PNG_INFLATE_BUF_SIZE
    //#error Inflate Buffer size must be stated
    #define PNG_INFLATE_BUF_SIZE 1024
#endif

#ifndef PNG_ZBUF_SIZE
    //#error Zbuf size must be stated
    #define PNG_ZBUF_SIZE 8192
#endif

#endif

