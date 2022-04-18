/*==================================================================
 *
 * FILE:        deviceprogrammer_firehose.h
 *
 * DESCRIPTION:
 *   
 *
 *        Copyright (c) 2008-2015,2017 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2017-04-24   sb      Increase signed hash packet size for 4K signing
 * 2015-11-09   wek     Remove structure coupling between fh and storage.
 * 2015-04-15   bn      Added GetStorageInfo support
 * 2015-03-26   wek     Test DDR if fails use Lite buffers to communicate.
 * 2014-10-02   ah      Major code clean up
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */

 
#ifndef DEVICEPROGRAMMER_FIREHOSE_H
#define DEVICEPROGRAMMER_FIREHOSE_H

#include "deviceprogrammer_utils.h"
#include "deviceprogrammer_storage.h"
#include "deviceprogrammer_security.h"
#include "deviceprogrammer_bsp.h"
#include "devprg_log.h"


#define FIREHOSE_XML_BUFFER_SIZE 4096
#define FIREHOSE_LOG_BUFFER_SIZE 4096
#define FIREHOSE_TEMP_LOG_BUFFER_SIZE 512
#define FIREHOSE_TEMP_ATTRIBUTE_BUFFER_SIZE 256
#define FIREHOSE_DEBUG_LOG_MESSAGE_SIZE 64
#define FIREHOSE_NUM_DEBUG_LOG_MESSAGES 32
#ifdef FEATURE_DEVICEPROGRAMMER_DDR
#define FIREHOSE_SIGNED_HASH_PACKET_SIZE 12288   // Needs to be at least 8KB for DigSig
#else
#define FIREHOSE_SIGNED_HASH_PACKET_SIZE 8192   // Needs to be at least 8KB for DigSig
#endif
#define FIREHOSE_NUM_HASHES_IN_HASH_TABLE (FIREHOSE_SIGNED_HASH_PACKET_SIZE/32)


void sendSupportedFunctions(void);
void sendAndAuthSerialNum(void) ;

#define ATTR_INVALID_VAL ((SIZE_T) -1L)   // default invalid attribute value

#define MyErrorMessage(Y) ErrorMessage(__LINE__,Y)


typedef enum firehose_error_t {
    FIREHOSE_SUCCESS,
    FIREHOSE_ERROR,
    FIREHOSE_TRANSPORT_ERROR,
    FIREHOSE_STORAGE_ERROR,
    FIREHOSE_VALIDATION_ERROR
} firehose_error_t;

#define MAX_STRING_SIZE	64

/* Currently the maximum memory info raw data is the eMMC's: */
/* Extended CSD, CID, and CSD 512+4+16 = 532 bytes */
#define STORAGE_DEVICE_INFO_BUFFER_SIZE 532

/* temp_buffer is used to transmit eMMC's device info. */
/* Make sure the temp_buffer is large enough to hold the */
/* eMMC raw data and a NULL at the end */
#define FIREHOSE_TEMP_BUFFER_SIZE STORAGE_DEVICE_INFO_BUFFER_SIZE + 1



// When adding new attribute, add to:
// 1) this struct
// 2) NUM_ATTRS or BOOL_ATTRS if needed. Make sure to put it with the other
//    SIZE_T or boolean attributes so they are parsed correctly.
// 3) setDefaultAttributes() to set default value.
// 4) preParseAttributes() to handle parsing if not using NUM_ATTRS/BOOL_ATTRS
typedef struct {
    SIZE_T MaxPayloadSizeToTargetInBytes;   // numeric attributes
    SIZE_T MaxPayloadSizeToTargetInBytesSupported;	// DDR version would typically have this set to 1MB
    SIZE_T MaxPayloadSizeFromTargetInBytes;
    SIZE_T MaxDigestTableSizeInBytes;
    SIZE_T AckRawDataEveryNumPackets;
    SIZE_T delayinseconds;
    SIZE_T address64;
    SIZE_T value64;
    SIZE_T storagedrive;
    SIZE_T SECTOR_SIZE_IN_BYTES;
    SIZE_T byte_offset;
    SIZE_T physical_partition_number;
    SIZE_T size_in_bytes;
    SIZE_T file_sector_offset;

    SIZE_T ZlpAwareHost;       	// bool attributes but made SIZE_T.
    SIZE_T SkipWrite;			// otherwise the generic function that assigns values
    SIZE_T BufferWrites;			
    SIZE_T AlwaysValidate;      // will possibly overwrite the next address in memory
    SIZE_T Verbose;
    SIZE_T commit;
    //SIZE_T display;
    SIZE_T TestWritePerformance;
    SIZE_T TestReadPerformance;
    SIZE_T TestDigestPerformance;
    SIZE_T TestDDRValidity;
    SIZE_T trials;
    //SIZE_T read_back_verify;
    SIZE_T SkipStorageInit;
    SIZE_T SkipSettingMinClocks;
    SIZE_T SkipSettingMaxClocks;
    SIZE_T actual_size_in_bytes;

    SIZE_T start_sector;    // special attributes
    SIZE_T num_partition_sectors;
    char filename[MAX_STRING_SIZE];
    byte value[FIREHOSE_TEMP_BUFFER_SIZE];

    char MemoryName[MAX_STRING_SIZE];
    char TargetName[MAX_STRING_SIZE];
    char Commit[MAX_STRING_SIZE];       // We have some commit='true', which eventually goes to set fh.attrs.commit=1

    // these are stored into first in preParseAttributes(), then
    // parseAttributes() fills in start_sector and num_partition_sectors
    //char start_sector_value[64];
    //char num_partition_sectors_value[64];

    enum storage_device_type storage_type;  // attribute MemoryName={"eMMC" or "ufs"}
} firehose_attrs_t;


typedef enum
{
    FAILURE_CHIP_SERIAL_NUMBER          = 0,
    AUTHENTICATE_IMAGE_FAILURE          = 1,
    UFS_COMMIT_EXTRAS_FAILURE           = 2,
    SET_BOOTABLE_PARTITION_FAILURE      = 3,
    STORAGE_READ_FAILURE                = 4,
    STORAGE_WRITE_FAILURE               = 5,
    STORAGE_DEVICE_ERASE_FAILURE        = 6,
    EMMC_COMMIT_EXTRAS_FAILURE          = 7,
    EMMC_FW_UPDATE_FAILURE              = 8,
    USB_READ_FAILURE                    = 9,
    USB_WRITE_FAILURE                   = 10,
    DIGITAL_SIGNATURE_DID_NOT_PASS      = 11,
    PACKET_HASH_MISMATCH                = 12,
    HANDLE_CONFIGURE_FAILURE            = 13,
    HANDLE_STORAGE_INFO_FAILURE         = 14,
    HANDLE_PEEK_FAILURE                 = 15,
    HANDLE_POKE_FAILURE                 = 16,
    HANDLE_ERASE_FAILURE                = 17,
    HANDLE_FIRMWARE_PROGRAM_FAILURE     = 18,
    HANDLE_PATCH_FAILURE                = 19,
    HANDLE_GET_DIGEST_FAILURE           = 20,
    HANDLE_PROGRAM_FAILURE              = 21,
    XML_PACKET_TOO_LARGE                = 22,
    SERIAL_NUM_OF_DEVICE_INCORRECT      = 23,

    FH_ERR_MAX
} firehose_error_code_t;

typedef struct
{
    // Buffer which is passed to USB
    // Using a constant value instead of a #define since that would
    // give the impression that this value is flexible. It is currently not.
    byte* channel_buffer[2];

    // Main buffer which holds the XML file to be parsed
    byte xml_buffer[FIREHOSE_XML_BUFFER_SIZE];

    // Transmit buffer for any outgoing XML or data
    byte* tx_buffer;

    // XML reader
    //xml_reader_t xml_reader;

    // XML writer
    //xml_writer_t xml_writer;

    char nak_all_packets; // If set to 1 all packets will be NAKed, killing communication.

    // Channel variables
    uint32 channel_error_code;
    SIZE_T channel_bytes_read;
    boolean channel_read_completed;
    boolean channel_write_completed;
    //SIZE_T channel_bytes_written;
    //SIZE_T channel_total_bytes_written;
    //SIZE_T channel_total_bytes_read;
    SIZE_T channel_buffer_capacity;
    //SIZE_T channel_num_errors;
    SIZE_T num_packets_received;
    boolean channel_buffer_queued;
    int channel_buffer_to_use;

    // Variables for validation mode
    boolean validation_enabled;
    boolean validation_signed_hash_received;
    byte validation_hash_buffer[FIREHOSE_NUM_HASHES_IN_HASH_TABLE][32];
    SIZE_T validation_hash_buffer_num_hashes;
    SIZE_T validation_hash_buffer_index;			// index at which hashes were loaded into the table
    SIZE_T validation_hash_buffer_capacity;			// fixed number based on above validation_hash_buffer size
    SIZE_T validation_hash_buffer_new_capacity;
    SIZE_T validation_table_count;	// table currently being used, i.e. 0,1,2 etc
    uint8 validation_hash_value[32];

    // On target debug log buffer
    byte debug_log_buffer[FIREHOSE_NUM_DEBUG_LOG_MESSAGES][FIREHOSE_DEBUG_LOG_MESSAGE_SIZE];
    SIZE_T debug_log_position;

    uint32 sector_size;//Size of a sector, 512 for eMMC, 4096 UFS.
    enum storage_device_type storage_type;

    // Storage medium
    storage_device_t *store_dev;

    // Performance measurement
    //boolean skip_storage_writes;
    //boolean hash_in_non_secure;
    //boolean verbose;
    //SIZE_T ack_raw_data_every;
    //SIZE_T  start_time;
    //SIZE_T  end_time;

    firehose_attrs_t attrs;
} firehose_protocol_t;




//typedef firehose_error_t (*attr_postproc_func_t)(firehose_attrs_t *attrs);

typedef firehose_error_t (*tag_handler_t)();

typedef struct
{
    char tag_name[32];      // configure
    tag_handler_t handler;  // handleConfigure()
} firehose_tag_data_t;



void initFirehoseProtocol(void);
boolean initFirehoseStorage(void);
//boolean isValidationMode(void);
void initFirehoseTransport(void);
void main_firehose(void) __attribute__((noreturn));
void ErrorMessage(unsigned int LineNumber, firehose_error_code_t ErrorCode);

void deviceprogrammer_zi_buffers (void);

#endif

