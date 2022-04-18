#ifndef TMS_UTILS_MSG_H
#define TMS_UTILS_MSG_H
/**
@file tms_utils_internal.h
@brief This file contains the Macro definitions for TMS utils
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2016 QUALCOMM Technologies Incorporated.
All rights reserved.
QUALCOMM Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/api/tms_utils_msg.h#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#ifdef TMS_PERIPHERAL_MPSS
#define TMS_PERIPHERAL "MPSS:"
#elif TMS_PERIPHERAL_ADSP
#define TMS_PERIPHERAL "ADSP:"
#elif TMS_PERIPHERAL_SLPI
#define TMS_PERIPHERAL "SLPI:"
#elif TMS_PERIPHERAL_CDSP
#define TMS_PERIPHERAL "CDSP:"
#endif 

#define TMS_DIAG_F3_MESSAGE_ALLOW

#ifdef TMS_DIAG_F3_MESSAGE_ALLOW
#include "msg.h"
#define TMS_MSG_LOW( str)    \
        MSG( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str)
#define TMS_MSG_LOW_1( str, a)    \
        MSG_1( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a)
#define TMS_MSG_LOW_2( str, a, b)    \
        MSG_2  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_LOW_3( str, a, b, c )    \
        MSG_3  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a, b, c )

#define TMS_MSG_MED( str)    \
        MSG( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str)
#define TMS_MSG_MED_1( str, a)    \
        MSG_1( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a)
#define TMS_MSG_MED_2( str, a, b)    \
        MSG_2  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_MED_3( str, a, b, c )    \
        MSG_3  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a, b, c )

#define TMS_MSG_HIGH( str)    \
        MSG( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str)
#define TMS_MSG_HIGH_1( str, a)    \
        MSG_1( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a)
#define TMS_MSG_HIGH_2( str, a, b)    \
        MSG_2  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_HIGH_3( str, a, b, c )    \
        MSG_3  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a, b, c )

#define TMS_MSG_ERROR( str)    \
        MSG( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str)
#define TMS_MSG_ERROR_1( str, a)    \
        MSG_1( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a)
#define TMS_MSG_ERROR_2( str, a, b)    \
        MSG_2  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_ERROR_3( str, a, b, c )    \
        MSG_3  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a, b, c )

#define TMS_MSG_FATAL( str)    \
        MSG( MSG_SSID_TMS, MSG_LEGACY_FATAL , TMS_PERIPHERAL str)
#define TMS_MSG_FATAL_1( str, a)    \
        MSG_1( MSG_SSID_TMS, MSG_LEGACY_FATAL , TMS_PERIPHERAL str, a)
#define TMS_MSG_FATAL_2( str, a, b)    \
        MSG_2  ( MSG_SSID_TMS, MSG_LEGACY_FATAL , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_FATAL_3( str, a, b, c )    \
        MSG_3  ( MSG_SSID_TMS, MSG_LEGACY_FATAL , TMS_PERIPHERAL str, a, b, c )

#define TMS_MSG_SPRINTF_LOW( str)    \
        MSG_SPRINTF( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str)
#define TMS_MSG_SPRINTF_LOW_1( str, a)    \
        MSG_SPRINTF_1( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a)
#define TMS_MSG_SPRINTF_LOW_2( str, a, b)    \
        MSG_SPRINTF_2  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_SPRINTF_LOW_3( str, a, b, c )    \
        MSG_SPRINTF_3  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a, b, c )
#define TMS_MSG_SPRINTF_LOW_4( str, a, b, c, d )    \
        MSG_SPRINTF_4  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a, b, c, d )
#define TMS_MSG_SPRINTF_LOW_5( str, a, b, c, d, e )    \
        MSG_SPRINTF_5  ( MSG_SSID_TMS, MSG_LEGACY_LOW , TMS_PERIPHERAL str, a, b, c, d, e )

#define TMS_MSG_SPRINTF_MED( str)    \
        MSG_SPRINTF( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str)
#define TMS_MSG_SPRINTF_MED_1( str, a)    \
        MSG_SPRINTF_1( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a)
#define TMS_MSG_SPRINTF_MED_2( str, a, b)    \
        MSG_SPRINTF_2  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_SPRINTF_MED_3( str, a, b, c )    \
        MSG_SPRINTF_3  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a, b, c )
#define TMS_MSG_SPRINTF_MED_4( str, a, b, c, d )    \
        MSG_SPRINTF_4  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a, b, c, d )
#define TMS_MSG_SPRINTF_MED_5( str, a, b, c, d, e )    \
        MSG_SPRINTF_5  ( MSG_SSID_TMS, MSG_LEGACY_MED , TMS_PERIPHERAL str, a, b, c, d, e )


#define TMS_MSG_SPRINTF_HIGH( str)    \
        MSG_SPRINTF( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str)
#define TMS_MSG_SPRINTF_HIGH_1( str, a)    \
        MSG_SPRINTF_1( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a)
#define TMS_MSG_SPRINTF_HIGH_2( str, a, b)    \
        MSG_SPRINTF_2  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_SPRINTF_HIGH_3( str, a, b, c )    \
        MSG_SPRINTF_3  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a, b, c )
#define TMS_MSG_SPRINTF_HIGH_4( str, a, b, c, d )    \
        MSG_SPRINTF_4  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a, b, c, d )
#define TMS_MSG_SPRINTF_HIGH_5( str, a, b, c, d, e )    \
        MSG_SPRINTF_5  ( MSG_SSID_TMS, MSG_LEGACY_HIGH , TMS_PERIPHERAL str, a, b, c, d, e )


#define TMS_MSG_SPRINTF_ERROR( str)    \
        MSG_SPRINTF( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str)
#define TMS_MSG_SPRINTF_ERROR_1( str, a)    \
        MSG_SPRINTF_1( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a)
#define TMS_MSG_SPRINTF_ERROR_2( str, a, b)    \
        MSG_SPRINTF_2  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a,b )
#define TMS_MSG_SPRINTF_ERROR_3( str, a, b, c )    \
        MSG_SPRINTF_3  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a, b, c )
#define TMS_MSG_SPRINTF_ERROR_4( str, a, b, c, d )    \
        MSG_SPRINTF_4  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a, b, c, d )
#define TMS_MSG_SPRINTF_ERROR_5( str, a, b, c, d, e )    \
        MSG_SPRINTF_5  ( MSG_SSID_TMS, MSG_LEGACY_ERROR , TMS_PERIPHERAL str, a, b, c, d, e )

#else  /* TMS_DIAG_F3_MESSAGE_ALLOW */

#define TMS_MSG_LOW( str)
#define TMS_MSG_LOW_1( str, a)
#define TMS_MSG_LOW_2( str, a, b)
#define TMS_MSG_LOW_3( str, a, b, c )

#define TMS_MSG_MED( str)
#define TMS_MSG_MED_1( str, a)
#define TMS_MSG_MED_2( str, a, b)
#define TMS_MSG_MED_3( str, a, b, c )

#define TMS_MSG_HIGH( str)
#define TMS_MSG_HIGH_1( str, a)
#define TMS_MSG_HIGH_2( str, a, b)
#define TMS_MSG_HIGH_3( str, a, b, c )

#define TMS_MSG_ERROR( str)
#define TMS_MSG_ERROR_1( str, a)
#define TMS_MSG_ERROR_2( str, a, b)
#define TMS_MSG_ERROR_3( str, a, b, c )

#define TMS_MSG_FATAL( str)    
#define TMS_MSG_FATAL_1( str, a)    
#define TMS_MSG_FATAL_2( str, a, b)    
#define TMS_MSG_FATAL_3( str, a, b, c )    

#define TMS_MSG_SPRINTF_LOW( str)   
#define TMS_MSG_SPRINTF_LOW_1( str, a) 
#define TMS_MSG_SPRINTF_LOW_2( str, a, b)   
#define TMS_MSG_SPRINTF_LOW_3( str, a, b, c )   
#define TMS_MSG_SPRINTF_LOW_4( str, a, b, c, d ) 
#define TMS_MSG_SPRINTF_LOW_5( str, a, b, c, d, e )

#define TMS_MSG_SPRINTF_MED( str)   
#define TMS_MSG_SPRINTF_MED_1( str, a)    
#define TMS_MSG_SPRINTF_MED_2( str, a, b)   
#define TMS_MSG_SPRINTF_MED_3( str, a, b, c )   
#define TMS_MSG_SPRINTF_MED_4( str, a, b, c, d ) 
#define TMS_MSG_SPRINTF_MED_5( str, a, b, c, d, e )

#define TMS_MSG_SPRINTF_HIGH( str)    
#define TMS_MSG_SPRINTF_HIGH_1( str, a)    
#define TMS_MSG_SPRINTF_HIGH_2( str, a, b)    
#define TMS_MSG_SPRINTF_HIGH_3( str, a, b, c )  
#define TMS_MSG_SPRINTF_HIGH_4( str, a, b, c, d ) 
#define TMS_MSG_SPRINTF_HIGH_5( str, a, b, c, d, e )

#define TMS_MSG_SPRINTF_ERROR( str)   
#define TMS_MSG_SPRINTF_ERROR_1( str, a)   
#define TMS_MSG_SPRINTF_ERROR_2( str, a, b)   
#define TMS_MSG_SPRINTF_ERROR_3( str, a, b, c )   
#define TMS_MSG_SPRINTF_ERROR_4( str, a, b, c, d ) 
#define TMS_MSG_SPRINTF_ERROR_5( str, a, b, c, d, e )


#endif /* TMS_DIAG_F3_MESSAGE_ALLOW */

#endif /* TMS_UTILS_MSG_H */
