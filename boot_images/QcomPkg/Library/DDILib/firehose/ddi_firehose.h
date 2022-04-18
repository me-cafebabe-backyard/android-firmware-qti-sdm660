/*==================================================================
 *
 * FILE:        ddi_firehose.h
 *
 * DESCRIPTION:
 *
 *
 *        Copyright © 2016 Qualcomm Technologies Incorporated.
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
 * 2016-12-15   zhz     DDI framwork re-architecture
 * 2015-04-15   bn      Added GetStorageInfo support
 * 2015-03-26   wek     Test DDR if fails use Lite buffers to communicate.
 * 2014-10-02   ah      Major code clean up
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */


#ifndef DDI_FIREHOSE_H
#define DDI_FIREHOSE_H

#include "ddi_utils.h"
//#include "ddi_storage.h"
#include "ddi_bsp.h"
#include "ddi_tool.h"
#include "HAL_SNS_DDR.h"

#define FIREHOSE_XML_BUFFER_SIZE 4096
#define FIREHOSE_LOG_BUFFER_SIZE 4096
#define FIREHOSE_TEMP_LOG_BUFFER_SIZE 256
#define FIREHOSE_TEMP_ATTRIBUTE_BUFFER_SIZE 256
#define FIREHOSE_DEBUG_LOG_MESSAGE_SIZE 128
#define FIREHOSE_NUM_DEBUG_LOG_MESSAGES 32
#define FIREHOSE_SIGNED_HASH_PACKET_SIZE 8192   // Needs to be at least 8KB for DigSig
#define FIREHOSE_NUM_HASHES_IN_HASH_TABLE (FIREHOSE_SIGNED_HASH_PACKET_SIZE/32)

#define ATTR_INVALID_VAL ((SIZE_T) -1L)   // default invalid attribute value

#define MyErrorMessage(Y) ErrorMessage(__LINE__,Y)


typedef enum firehose_error_t
{
    FIREHOSE_SUCCESS,
    FIREHOSE_ERROR,
    FIREHOSE_TRANSPORT_ERROR,
    FIREHOSE_STORAGE_ERROR,
    FIREHOSE_VALIDATION_ERROR
} firehose_error_t;

#define MAX_STRING_SIZE 64

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
typedef struct
{
    SIZE_T MaxPayloadSizeToTargetInBytes;   // numeric attributes
    SIZE_T MaxPayloadSizeToTargetInBytesSupported;  // DDR version would typically have this set to 1MB
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

    SIZE_T ZlpAwareHost;        // bool attributes but made SIZE_T.
    SIZE_T SkipWrite;           // otherwise the generic function that assigns values
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

    //hotplug_dev_type storage_type;  // attribute MemoryName={"eMMC" or "ufs"}
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
    SIZE_T validation_hash_buffer_index;            // index at which hashes were loaded into the table
    SIZE_T validation_hash_buffer_capacity;         // fixed number based on above validation_hash_buffer size
    SIZE_T validation_hash_buffer_new_capacity;
    SIZE_T validation_table_count;  // table currently being used, i.e. 0,1,2 etc
    uint8 validation_hash_value[32];

    // On target debug log buffer
    byte debug_log_buffer[FIREHOSE_NUM_DEBUG_LOG_MESSAGES][FIREHOSE_DEBUG_LOG_MESSAGE_SIZE];
    SIZE_T debug_log_position;

    // Storage medium
    //storage_device_t store_dev;

    // Performance measurement
    //boolean skip_storage_writes;
    //boolean hash_in_non_secure;
    //boolean verbose;
    //SIZE_T ack_raw_data_every;
    //SIZE_T  start_time;
    //SIZE_T  end_time;

    firehose_attrs_t attrs;
} firehose_protocol_t;


#define MAX_PARAM_TYPE_NAME_SIZE 16
#define MAX_CMD_NAME_SIZE 32
#define MAX_RSP_NAME_SIZE 32
#define MAX_PARAM_NAME_SIZE 32
#define MAX_INFO_SIZE 64

#define DDR_TYPE_MASK(type) ((type >= 32) ? 0 : 1 << type)

#define DDI_FIREHOSE_SIZE_NAME        (64)
#define DDI_FIREHOSE_SIZE_INFOVAL     (256)
#define DDI_FIREHOSE_SIZE_TYPELEN     (16)
#define DDI_FIREHOSE_SIZE_BOOLLEN     (8)
#define DDI_FIREHOSE_SIZE_MAXPAR      (32)
#define DDI_FIREHOSE_SIZE_STR_INT32   (12)
#define DDI_FIREHOSE_SIZE_INFO_MAX    (8) //max number of ddi infomation supported

extern const char ddi_firehose_bool_name[2][DDI_FIREHOSE_SIZE_BOOLLEN];

typedef enum
{
    DDI_FIREHOSE_NULL = 0,
    DDI_FIREHOSE_INT8,
    DDI_FIREHOSE_UINT8,
    DDI_FIREHOSE_INT16,
    DDI_FIREHOSE_UINT16,
    DDI_FIREHOSE_INT32,
    DDI_FIREHOSE_UINT32,
    DDI_FIREHOSE_STRING,
    DDI_FIREHOSE_BOOLEAN,
    DDI_FIREHOSE_ARRAY_UINT32,
} ddi_firehose_type;


typedef firehose_error_t (*tag_handler_t)();

typedef struct
{
    char tag_name[32];      // configure
    tag_handler_t handler;  // handleConfigure()
} firehose_tag_data_t;

typedef enum response_t
{
    NAK,
    ACK
} response_t;

typedef struct
{
    char info_key[MAX_INFO_SIZE];
    char info_val[MAX_INFO_SIZE];
} ddi_firehose_info, *ddi_firehose_info_p;

typedef struct
{
    const char param_name[MAX_PARAM_NAME_SIZE];
    ddi_firehose_type param_type;
    int param_min;
    int param_max;
    int param_default;
    char param_entity[MAX_INFO_SIZE];
} ddi_firehose_params, *ddi_firehose_params_p;

typedef struct
{
    const char rspons_name[MAX_RSP_NAME_SIZE];
    ddi_firehose_type rspons_type;
} ddi_firehose_rspons, *ddi_firehose_rspons_p;

typedef struct
{
    const char item_name[MAX_CMD_NAME_SIZE];

    int item_ver;

    int ddrTypeCompatibility;
    // item parameters array
    ddi_firehose_params_p item_params_arr;

    // item responses array
    ddi_firehose_rspons_p item_rspons_arr;

    boolean (*item_exec_init)(void *this_p); //input: list from QDUTT(strictly same order as defined), output: pretest args

    // executors
    boolean (*item_exec_pretest)(void *this_p); //input: list from QDUTT(strictly same order as defined), output: pretest args
    boolean (*item_exec_dotest)(void *this_p); //input pretest output args, output test done args
    boolean (*item_exec_postest)(void *this_p); //input done test args
} ddi_firehose_item, *ddi_firehose_item_p;

typedef struct
{
    char platform[256];
    int version;

    // ddi extra infomation array
    ddi_firehose_info_p info_arr;

    // ddi items array
    ddi_firehose_item_p item_arr;

    // for ddi framework to hadle
    boolean (*worker_exec_pre)(void *this_p);
    boolean (*worker_exec_post)(void *this_p);
} ddi_firehose_item_set, *ddi_firehose_item_set_p;

void initFirehoseProtocol(void);
boolean initFirehoseStorage(void);
void initFirehoseTransport(void);
void deviceprogrammer_zi_buffers (void);
firehose_error_t getXMLPacket();
void AppendToBuffer(byte *MyBuffer, char *buf, SIZE_T MaxBufferSize);
void logMessage(const char* format, ...);
void ErrorMessage(unsigned int LineNumber, firehose_error_code_t ErrorCode);
firehose_error_t sendResponse(response_t response);
void ddi_firehose_print_debug(const char* format, ...);
firehose_error_t ddi_firehose_print_log(const char* format, ...);
firehose_error_t ddi_firehose_print_response(const char* item_name, const char* rsp_name, const char* rsp_val);
firehose_error_t sendDDIResponseFields(const char *tag_name, int n_args, ...);
void shutDownUSB();
firehose_error_t handleDDIInfo();
boolean check_especial_cmd_attribute(void);
boolean check_normal_cmd_attribute(void);
boolean ddi_firehose_add_ddi_infomation(ddi_firehose_info_p modInfo, const char *key, const char type, void *val);
ddi_firehose_item_p ddi_firehose_get_current_item();
boolean ddi_firehose_fetch_parameters(char* str, ddi_firehose_item_p item, void *value);
void ddi_firehose_update_item_set(ddi_firehose_item_set_p ddiItemSet);
boolean cmdIsCompatible(ddi_firehose_item_p item);
int getfirehose_tag_data_num(void);
firehose_error_t handleReset();
firehose_error_t handleNop();
boolean main_firehose(void);
#endif
