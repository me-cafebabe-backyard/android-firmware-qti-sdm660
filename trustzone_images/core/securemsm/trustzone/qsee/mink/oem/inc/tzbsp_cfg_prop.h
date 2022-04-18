#ifndef TZBSP_CFG_PROP_H
#define TZBSP_CFG_PROP_H

/**
 * Copyright 2015 QUALCOMM Technologies, Inc. 
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 */

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

  when       who      what, where, why
  --------   ---      ------------------------------------
  02/02/15   cz       Initial version

===========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>
#include "DALSys.h"
#include "DALSysTypes.h"

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef enum
{
    TZBSP_CFG_SUCCESS                   = 0x00,
    TZBSP_CFG_INVALID_INPUT             = 0x01,
    TZBSP_CFG_BUFFER_TOO_SMALL          = 0x02,
    TZBSP_CFG_ERROR_GET_PROP_HDLSTR     = 0x03,
    TZBSP_CFG_ERROR_GET_PROP_VALUE      = 0x04,
    TZBSP_CFG_ERROR_MEMSCPY             = 0x05,
    TZBSP_CFG_UNKNOWN_TYPE              = 0x06,
    
    TZBSP_CFG_MAX_ERROR_CODE          = 0x7FFFFFFF
} tzbsp_cfg_error;

typedef struct
{
    uint32 dwType;
    uint32 dwLen;  /* in bytes */
    uint8  val[1]; /* If dwLen > 1, the left variables followed by val[0] */
}  tzbsp_cfg_propvar_t;

typedef struct
{
    uint32 wQseeFatalErrFlag;
    uint32 wOemFatalErrFlag;
}  tzbsp_reset_reason_pair_t;

typedef struct
{
    uint32 dwCount;
    tzbsp_reset_reason_pair_t *rst_reason;
}  tzbsp_cfg_oem_reset_reason_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
 
/**
 * @brief the configuration value is fetched from TZ kernel via SYS CALL
 *
 * @param[in]    PropName     point to Property Name (a string)
 * @param[in]    PropNameLen  The length of the PropName size. It does not include '\0'. It should be less than 64.
 * @param[in]    PropID       Property ID
 * @param[out]   pPropBuf     output buffer that populates DAL configuration value
 *                            the populated buffer need to cast to the qsee_cfg_propvar_t type
 * @param[in]    PropBufSz    the output buffer size in bytes
 * @param[out]   PropBufSzRet the actual populated buffer size in bytes
 *
 * @return zero on success, non-zero on failure
*/
tzbsp_cfg_error tzbsp_cfg_getpropval
(
    const char             *PropName,
    uint32                  PropNameLen,
    uint32                  PropId,
    tzbsp_cfg_propvar_t    *pPropBuf,
    uint32                  PropBufSz,
    uint32                 *PropBufSzRet
);

#endif //TZBSP_CFG_PROP_H
