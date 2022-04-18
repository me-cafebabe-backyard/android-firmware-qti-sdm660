#ifndef __LOWI_CONST_H__
#define __LOWI_CONST_H__

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

        LOWI Const Interface Header file

GENERAL DESCRIPTION
  This file contains the structure definitions and function prototypes for
  LOWIConst

Copyright (c) 2015-2016 Qualcomm Technologies, Inc. All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.

Copyright (c) 2012 Qualcomm Atheros, Inc.
  All Rights Reserved.
  Qualcomm Atheros Confidential and Proprietary.

Export of this technology or software is regulated by the U.S. Government.
Diversion contrary to U.S. law prohibited.
=============================================================================*/
#if APSS
#include <ctype.h>
#include <inttypes.h>
#include <time.h>
#include <new>
#include <stdint.h>
#include <base_util/vector.h>
#include <inc/lowi_defines.h>
#endif
namespace qc_loc_fw
{

#define BSSID_LEN 6
#define SSID_LEN 32
/** SSID Length for AP List. Need only first few bytes */
#define SSID_LEN_AP_LIST 10


#if APSS
#define MAX_CHAN_INFO_SIZE 16
#else
#define MAX_CHAN_INFO_SIZE 20
#endif

#define CLIENT_NAME_LEN 128
#define CELL_POWER_NOT_FOUND 0x7F

const char* const LOWI_CLIENT_SUFFIX = "-LOWIClient";
const char* const SERVER_NAME = "LOWI-SERVER";
const char* const NOT_AVAILABLE = "NA";
const int ASYNC_DISCOVERY_REQ_VALIDITY_PERIOD_SEC_MAX = 3600;

/** Defines if simulation mode in LOWI is enabled or not */
#define LOWI_SIMULATION_ENABLED 0

/** Defines the buffer threshold (percentile) for AP list batching buffer */
#define LOWI_AP_LIST_DEFAULT_THRESHOLD 90

/** MAX age of APs in the AP List */
#define LOWI_MAX_AP_AGE_IN_SEC_IN_AP_LIST 360

/** Max APs that can be batched in the AP List*/
#define LOWI_MAX_APS_IN_AP_LIST 1000

/** Max APs that can be in the cache */
#define LOWI_MAX_APS_IN_CACHE 200

/** Statistics logging enabled */
#define LOWI_STATISTICS_LOGGING_ENABLED 1

/** Default logging level - INFO */
#define LOWI_DEFAULT_LOG_LEVEL 3

/** Threshold for discovery scan in NORMAL mode */
#define LOWI_NORMAL_MODE_SCAN_THRESHOLD_MSEC 500

/** Max BGScan buffer size in bytes */
#define LOWI_BGSCAN_MAX_BUFFER_SIZE 1024*100

/** BGScan Max APs cached per scan */
#define LOWI_BGSCAN_MAX_AP_CACHE_PER_SCAN 32

/** Max measurements stored in BGScan buffer */
#define LOWI_BGSCAN_MAX_MEASUREMENTS 20000

/** BGScan Max reporting threshold */
#define LOWI_BGSCAN_MAX_REPORTING_THRESHOLD \
  ((0.9 * LOWI_BGSCAN_MAX_MEASUREMENTS)/LOWI_BGSCAN_MAX_AP_CACHE_PER_SCAN)

/** Max APs that can be in the BGScan buffer */
#define LOWI_BGSCAN_MAX_APS_IN_CACHE 1000

/** Max QMI message size
 * This could be ideally as big as 65535 bytes but we
 * want to restrict it to around 4K or less for BGSCAN*/
#define LOWI_MAX_QMI_MSG_SIZE_BGSCAN 3500

/*=================================================
 * MACRO: LOWI_MACADDR_FMT, LOWI_MACADDR
 * These two macros are just mapping of Mac Address
 * content from unsigned char[6] to string format
 ==================================================*/
#define LOWI_MACADDR_FMT \
  "%02x:%02x:%02x:%02x:%02x:%02x"
#define LOWI_MACADDR(mac_addr) \
  mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]

/** Country code length*/
#define LOWI_COUNTRY_CODE_LEN 3
/** LOWI Cache keeps the SSID truncated to this size */
#define LOWI_CACHE_SSID_SIZE  18
/** Number of measurements (RSSI / meas age) to be cached per AP */
#define LOWI_CACHE_NUM_AP_MEASUREMENTS 1
/** Cache full SSID for BGScan buffer */
#define LOWI_BGSCAN_SSID_SIZE  32

#define WIFI_CHANNEL_SPACING 5      // Channels are 5 MHz apart
#define BAND_2G_FREQ_BASE     2407  //Base frequency of 2G band (MHz)
#define BAND_2G_CHAN_BEGIN    1     //First channel for 2G band
#define BAND_2G_CHAN_END      14    //Last channel for 2G band
#define BAND_2G_FREQ_LAST     2484  //Last frequency for 2G band (MHz)
#define BAND_5G_FREQ_BASE     5000  //Base frequency of 5G band (MHz)
#define BAND_5G_CHAN_BEGIN    34    //First channel for 5G band
#define BAND_5G_CHAN_END      196   //Last channel for 5G band
#define BAND_60G_FREQ_BASE    56160 //Base frequency for 60G band (MHz)
#define BAND_60G_CHAN_BEGIN   1     //First channel for 60G band
#define BAND_60G_CHAN_END     4     //Last channel for 60G band
#define BAND_60G_CHAN_SPACING 2160  //Channel spacing for 60G band (MHz)

#if !APSS
/**
 * Service versions.
 * List of versions that the service can support at any given time
 * this list helps implement backward compatibility for previous versions.
 */
enum eSupportedServiceVersion
{
  VER_01 = 1
};

/**
 * Supported service version for the client
 * Every time the client side support changes, this version should
 * be updated.
 */
const eSupportedServiceVersion CLIENT_SUPPORTS_SERVICE_VERSION = VER_01;
#endif

} // namespace qc_loc_fw
#endif //#ifndef __LOWI_CONST_H__
