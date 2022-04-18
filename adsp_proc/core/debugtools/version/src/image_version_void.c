/** vi: tw=128 ts=3 sw=3 et
@file image_version_void.c
@brief This file contains the API for the IMAGE VERSION, API 1.0.1
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/version/src/image_version_void.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

#include "comdef.h"
#include "smem.h"
#include "string.h"
#include "image_version.h"

/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/

/*===========================================================================

**  Function :  image_version_populate_version

** ==========================================================================
*/
/*!
*
* @brief
*   This function populates the image_version in image_versoin_table in smem
*   based on image index/allocated-entry.
*
* @param[in] image_index index in the smem_image_version_table
*
* @par Dependencies
*   smem must have been initialized.
*
* @retval
*   returns status: 0 value represents no error, for other errors review
*   image_version_error_type
*
* @par Side Effects
*   None
*
*/
uint32 image_version_populate_version(image_index_type image_index)
{
   return IMG_VER_ERROR_NONE;
}

/*===========================================================================

**  Function :  image_version_initialize_version_table

** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes the image_version_table in smem with spaces.
*
* @param
*   None
*
* @par Dependencies
*   smem must have been initialized and smem element for image_version_table
*   allocated.
*
* @retval
*   returns status: 0 value represents no error, for other errors review
*   image_version_error_type
*
* @par Side Effects
*   Initializes whole SMEM_IMAGE_VERSION_TABLE with spaces
*   This API should only be called once right after smem_boot_init by the image
*   doing smem_boot_init.
*
*/
uint32 image_version_initialize_version_table(void)
{
   return IMG_VER_ERROR_NONE;
}
