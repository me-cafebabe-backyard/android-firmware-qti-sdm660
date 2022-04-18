#ifndef PLATFORMINFO_H
#define PLATFORMINFO_H

/**
  @file PlatformInfo.c

  Public header file for the PlatformInfo driver.
*/
/*
  ====================================================================

  Copyright (c) 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/rpm.bf/1.8/core/api/systemdrivers/PlatformInfo.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Generates a platform version number.
 *
 * This macro generates the platform version number from the specified
 * major and minor numbers. For example, version 1.2 is represented by
 * @code PLATORMINFO_VERSION(1,2) @endcode
 *
*/
#define PLATFORMINFO_VERSION(major, minor)  (((major) << 16) | (minor))


/**
  Target type of the device on which the platform is running.
 */
typedef enum
{
  PLATFORMINFO_TYPE_UNKNOWN      = 0x00,  /**< Unknown target device. */
  PLATFORMINFO_TYPE_SURF         = 0x01,  /**< Target is a SURF device. */
  PLATFORMINFO_TYPE_FFA          = 0x02,  /**< Target is an FFA device. */
  PLATFORMINFO_TYPE_FLUID        = 0x03,  /**< Target is a FLUID device. */
  PLATFORMINFO_TYPE_FUSION       = 0x04,  /**< Target is a FUSION device. */
  PLATFORMINFO_TYPE_OEM          = 0x05,  /**< Target is an OEM device. */
  PLATFORMINFO_TYPE_QT           = 0x06,  /**< Target is a QT device. */
  PLATFORMINFO_TYPE_CDP          = PLATFORMINFO_TYPE_SURF,
                                             /**< Target is a CDP (aka SURF) device. */
  PLATFORMINFO_TYPE_MTP_MDM      = 0x07,  /**< Target is a MDM MTP device. */
  PLATFORMINFO_TYPE_MTP_MSM      = 0x08,  /**< Target is a MSM MTP device. */
  PLATFORMINFO_TYPE_LIQUID       = 0x09,  /**< Target is a LiQUID device. */
  PLATFORMINFO_TYPE_DRAGONBOARD  = 0x0A,  /**< Target is a DragonBoard device. */
  PLATFORMINFO_TYPE_QRD          = 0x0B,  /**< Target is a QRD device. */
  PLATFORMINFO_TYPE_EVB          = 0x0C,  /**< Target is an EVB device. */
  PLATFORMINFO_TYPE_HRD          = 0x0D,  /**< Target is a HRD device. */
  PLATFORMINFO_TYPE_DTV          = 0x0E,  /**< Target is a DTV device. */
  PLATFORMINFO_TYPE_RUMI         = 0x0F,  /**< Target is on RUMI. */
  PLATFORMINFO_TYPE_VIRTIO       = 0x10,  /**< Target is on VIRTIO. */
  PLATFORMINFO_TYPE_GOBI         = 0x11,  /**< Target is a GOBI device. */
  PLATFORMINFO_TYPE_CBH          = 0x12,  /**< Target is a CBH device. */
  PLATFORMINFO_TYPE_BTS          = 0x13,  /**< Target is a BTS device. */
  PLATFORMINFO_TYPE_XPM          = 0x14,  /**< Target is a XPM device. */
  PLATFORMINFO_TYPE_RCM          = 0x15,  /**< Target is a RCM device. */
  PLATFORMINFO_TYPE_DMA          = 0x16,  /**< Target is a DMA device. */

  PLATFORMINFO_NUM_TYPES         = 0x17,  /**< Number of known targets
                                               (including unknown). */
  /** @cond */
  PLATFORMINFO_TYPE_32BITS       = 0x7FFFFFFF
  /** @endcond */
} PlatformInfoPlatformType;


/**
 * Sub-type of the platform.
 */
typedef enum
{
  PLATFORMINFO_SUBTYPE_UNKNOWN = 0x00, /**< Unknown sub-type. */
  PLATFORMINFO_SUBTYPE_CSFB    = 0x01, /**< Platform is of sub-type CSFB. */
  PLATFORMINFO_SUBTYPE_SVLTE1  = 0x02, /**< Platform is of sub-type SVLTE1. */
  PLATFORMINFO_SUBTYPE_SVLTE2A = 0x03, /**< Platform is of sub-type SVLTE2A. */
  PLATFORMINFO_SUBTYPE_SVLTE2B = 0x04, /**< Platform is of sub-type SVLTE2B. */
  PLATFORMINFO_SUBTYPE_SVLTE2C = 0x05, /**< Platform is of sub-type SVLTE2C. */
  PLATFORMINFO_SUBTYPE_SGLTE   = 0x06, /**< Platform is of sub-type SGLTE. */
  PLATFORMINFO_SUBTYPE_DSDA    = 0x07, /**< Platform is of sub-type DSDA. */

  PLATFORMINFO_NUM_SUBTYPES    = 0x08, /**< Number of known sub-types (
                                             (including unknown). */
  /** @cond */
  PLATFORMINFO_SUBTYPE_32BITS  = 0x7FFFFFFF
  /** @endcond */
} PlatformInfoPlatformSubtype;


/**
 * Keys to get data out of the CDT.
 */
typedef enum
{
  PLATFORMINFO_KEY_UNKNOWN       = 0x00,
  PLATFORMINFO_KEY_DDR_FREQ      = 0x01,
  PLATFORMINFO_KEY_GFX_FREQ      = 0x02,
  PLATFORMINFO_KEY_CAMERA_FREQ   = 0x03,

  PLATFORMINFO_NUM_KEYS          = 0x04,

  /** @cond */
  PLATFORMINFO_KEY_32BITS  = 0x7FFFFFFF
  /** @endcond */
} PlatformInfoKeyType;


/**
  @brief Stores the target platform, the platform version, and the
  platform subtype.
 */
typedef struct
{
  PlatformInfoPlatformType     ePlatform;   /**< Type of the current target. */
  uint32                       nVersion;    /**< Version of the platform in use. */
  PlatformInfoPlatformSubtype  eSubtype;    /**< Sub-type of the platform. */
  boolean                      bFusion;     /**< TRUE if Fusion; FALSE otherwise. */
} PlatformInfoPlatformInfoType;


/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : PlatformInfo_GetPlatform
** =========================================================================*/
/**
  Returns the current platform.
*/
PlatformInfoPlatformType PlatformInfo_GetPlatform (void);


/* =========================================================================
**  Function : PlatformInfo_GetPlatformInfo
** =========================================================================*/
/**
  Returns information on the current platform.

  @return
    TRUE -- Success.
    FALSE -- The pInfo parameter is NULL.
*/
boolean PlatformInfo_GetPlatformInfo
(
  PlatformInfoPlatformInfoType *pInfo
);


/* =========================================================================
**  Function : PlatformInfo_GetKeyValue
** =========================================================================*/
/**
  Returns a value for a given key.

  @return
    TRUE -- Key was found in the CDT.
    FALSE -- Key wasn't found in the CDT.
*/
boolean PlatformInfo_GetKeyValue
(
  PlatformInfoKeyType eKey,
  uint32              *nValue
);


/* =========================================================================
**  Function : PlatformInfo_Init
** =========================================================================*/
/**
  Initializes the PlatformInfo driver.
*/
void PlatformInfo_Init (void);

#endif

