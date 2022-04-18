/*==================================================================
 *
 * FILE:        ddi_firehose.c
 *
 * DESCRIPTION:
 *
 *
 *        Copyright © 2008-2016 Qualcomm Technologies Incorporated.
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
 * 2015-02-18   wek     Zero initalize different set of buffers.
 * 2015-01-20   wek     Avoid NULL dereference.
 * 2014-12-02   wek     8996/XBL Compilation.
 * 2014-10-02   ah      Major code clean up
 * 2014-03-03   dks     Added MMC FFU Support
 * 2013-06-03   ah      Added legal header
 * 2013-05-31   ab      Initial checkin
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "crc.h"
#include "stringl/stringl.h"
#include "ddi_firehose.h"
#include "ddr_drivers.h"
#include "ddi_initialize.h"

#include "usb_wrapper.h"
#include "boot_sahara.h"
#include "ClockBoot.h"
#include "busywait.h"
#include "fs_hotplug.h"
#include "fs_hotplug_config.h"

#define MAX_TAG_NAME_LENGTH 30
#define MAX_TAG_ATTR_LENGTH 80

#define XML_HEADER_LENGTH 40    // 40 does NOT include null
#define XML_TAIL_LENGTH 9       // 9 DOES include null

/* Buffers that are allocated in On chip memory. */
byte lite_main_channel_buffer_A[FIREHOSE_LITE_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.LITE_CHANNEL_BUFFER_A_SECTION"))) __attribute__((__aligned__(16))) = {0};
byte lite_main_channel_buffer_B[FIREHOSE_LITE_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.LITE_CHANNEL_BUFFER_B_SECTION"))) __attribute__((__aligned__(16))) = {0};
byte transmit_buffer[FIREHOSE_TX_BUFFER_SIZE]  __attribute__ ((section (".bss.TRANSMIT_BUFFER_SECTION"))) = {0};
byte* packet;
char temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE];
firehose_protocol_t fh __attribute__ ((section (".bss.FIREHOSE_PROTOCOL_STRUCT")));

#ifdef USE_FIRMWARE_BUFFER
#define BIG_FW_BUFFER_SIZE (1024*512)
byte BigFWBuffer[BIG_FW_BUFFER_SIZE] __attribute__ ((section (".bss.DDR_CHANNEL_BUFFER_A_SECTION"))) = {0};
SIZE_T BigFWBufferCount = 0, BigFWBufferExpected = 0;
#endif

SIZE_T ConfigureCommandNotReceivedYet = 1;  // allow VERBOSE until user turns it off
static const char xml_header[XML_HEADER_LENGTH] = "<\?xml version=\"1.0\" encoding=\"UTF-8\" \?>\n";

char NewTagName[MAX_TAG_NAME_LENGTH+1];
char CurrentTagName[MAX_TAG_NAME_LENGTH+1];
char ParseAttributes = 1; // this changes from 0 to 1 during the program
SIZE_T glen = 0 ;

struct Error_Struct
{
    unsigned int ErrorNum;
    char *pErrorMessage;
};

struct Error_Struct AllErrorsStruct[] =
{
    { FAILURE_CHIP_SERIAL_NUMBER,       "FAILURE_CHIP_SERIAL_NUMBER"},
    { AUTHENTICATE_IMAGE_FAILURE,       "AUTHENTICATE_IMAGE_FAILURE"},
    { UFS_COMMIT_EXTRAS_FAILURE,        "UFS_COMMIT_EXTRAS_FAILURE"},
    { SET_BOOTABLE_PARTITION_FAILURE,   "SET_BOOTABLE_PARTITION_FAILURE"},
    { STORAGE_READ_FAILURE,             "STORAGE_READ_FAILURE"},
    { STORAGE_WRITE_FAILURE,            "STORAGE_WRITE_FAILURE"},
    { STORAGE_DEVICE_ERASE_FAILURE,     "STORAGE_DEVICE_ERASE_FAILURE"},
    { EMMC_COMMIT_EXTRAS_FAILURE,       "EMMC_COMMIT_EXTRAS_FAILURE"},
    { EMMC_FW_UPDATE_FAILURE,           "EMMC_FW_UPDATE_FAILURE"},
    { USB_READ_FAILURE,                 "USB_READ_FAILURE"},
    { USB_WRITE_FAILURE,                "USB_WRITE_FAILURE"},
    { DIGITAL_SIGNATURE_DID_NOT_PASS,   "DIGITAL_SIGNATURE_DID_NOT_PASS"},
    { PACKET_HASH_MISMATCH,             "PACKET_HASH_MISMATCH"},
    { HANDLE_CONFIGURE_FAILURE,         "HANDLE_CONFIGURE_FAILURE"},
    { HANDLE_STORAGE_INFO_FAILURE,      "HANDLE_STORAGE_INFO_FAILURE"},
    { HANDLE_PEEK_FAILURE,              "HANDLE_PEEK_FAILURE"},
    { HANDLE_POKE_FAILURE,              "HANDLE_POKE_FAILURE"},
    { HANDLE_ERASE_FAILURE,             "HANDLE_ERASE_FAILURE"},
    { HANDLE_FIRMWARE_PROGRAM_FAILURE,  "HANDLE_FIRMWARE_PROGRAM_FAILURE"},
    { HANDLE_PATCH_FAILURE,             "HANDLE_PATCH_FAILURE"},
    { HANDLE_GET_DIGEST_FAILURE,        "HANDLE_GET_DIGEST_FAILURE"},
    { HANDLE_PROGRAM_FAILURE,           "HANDLE_PROGRAM_FAILURE"},
    { XML_PACKET_TOO_LARGE,             "XML_PACKET_TOO_LARGE"},
    { SERIAL_NUM_OF_DEVICE_INCORRECT,   "SERIAL_NUM_OF_DEVICE_INCORRECT"},
};

uint32 patternDataBuf[256]   __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
char NewAttrValue[3072] __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
uint32 write_in_pattern[256];
uint16 patternElemCnt;
char str[BUFFER_LENGTH] = {0};
static DDR_STRUCT *DDI_share_data = (DDR_STRUCT *)DDR_GLOBAL_STRUCT_DATARAM_ADDR;
boolean quitDDI = FALSE;
uint32 dataBuffer[256]  =
{
    0xDEADBEEF, 0x5A5A5A5A, 0xA5A5A5A5, 0xFEEDFACE, 0xCAFEBABE, 0xA5A5A5A5, 0x5A5A5A5A, 0x0BADF00D,
    0xDEADBEEF, 0x5A5A5A5A, 0xA5A5A5A5, 0xFEEDFACE, 0xCAFEBABE, 0xA5A5A5A5, 0x5A5A5A5A, 0x0BADF00D,
    0x22222222, 0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0x0f0f0f0f, 0xf0f0f0f0, 0x00000000, 0xffffffff,
    0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0x0f0f0f0f, 0xf0f0f0f0, 0x00000000, 0xffffffff,
    0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x66666666, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000,
    0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000, 0xfcfcfcfc, 0x00000000,
    0x55555555, 0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
    0x5a5a5a5a, 0xa5a5a5a5, 0x5a5a5a5a, 0xa5a5a5a5, 0xf0f0f0f0, 0x0f0f0f0f, 0xffffffff, 0x00000000,
    0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808,
    0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808, 0xf7f7f7f7, 0x08080808,
    0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B,
    0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B,
    0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A,
    0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A, 0x5B5B5B5B, 0x5A5A5A5A,

    0x3789D91E, 0x19E69FC4, 0x484E3BE0, 0xCD6014C4, 0x77D1D4B1, 0xAB30DF90, 0xCB1F041D, 0xFA3D26AB,
    0x63E23084, 0x03DD0851, 0x18577023, 0x913FB1B5, 0xE81D6955, 0xCF7163D4, 0x2A452F75 ,0x01E6629F,
    0x797B2280, 0x9ACE7CD7, 0xA06B1A1D, 0xBE79D5DB, 0xEBBFF686, 0x6EBB85FF, 0xBF31749A, 0x29F2E6C7,
    0x8C91AAFC, 0xAB1AAB75, 0xAC48D44E, 0x504C17D0, 0xB1C5B12A, 0xAC329613, 0xBA5D149B ,0x592054F1,
    0x753B266D, 0x20944DEB, 0x3220F4C2, 0xDFDF25CD, 0x80D363CB, 0x63EEBF1B, 0x4C1A820C, 0x1E54639A,
    0x127F2554, 0xEB3C2935, 0xCDAAFAEF, 0xC84B4320, 0x2A0B9168, 0xA4CC98BF, 0xF3609880 ,0xD79CAE43,
    0x713BB864, 0x72FA35F8, 0x6DED7DF2, 0x23A354E0, 0xCB34F01A, 0xB035D5A0, 0x86C06BD6, 0xEFAB7C43,
    0x74DFBE03, 0xC1E91236, 0x09CAD86F, 0x1C0D78EC, 0xDA6B8136, 0xA18EA81C, 0xEA4D7192 ,0x8B331A3B,
    0x81810414, 0xA4555EFD, 0x31722982, 0xFC0E7445, 0x883A76E5, 0x4A9718FF, 0x9577C0A3, 0x49F2D41B,
    0x5D8D9AC4, 0xB48E6E84, 0x4451DBED, 0x0C03D7D7, 0x398540DD, 0xBDC56DB1, 0x29555DDF ,0x47B64FF0,
    0x3DF87F32, 0x4697A951, 0x78FFBEF0, 0xA71F8CBD, 0xC449842F, 0x036EDD7C, 0x4E020585, 0xFB39FB64,
    0x4FF1CEC2, 0x7D3A52FB, 0xF8A2D60B, 0x1FD68B15, 0x092A6BD6, 0x2386376D, 0xCCFC9C10 ,0xB8257024,
    0xC1A1FDED, 0x186DD915, 0xA0AC5EFE, 0x5363D067, 0x2507A9F2, 0xADD4BC69, 0xFC266ABB, 0x835F251B,
    0x9FA61759, 0x071198C9, 0x1000275A, 0xC7883CC7, 0xF3C7AB76, 0x20E052FD, 0xE3AA85F3 ,0x042B74AA
};

const char ddi_firehose_type_name[DDI_FIREHOSE_ARRAY_UINT32+1][DDI_FIREHOSE_SIZE_TYPELEN]=
{
    "",
    "int8",
    "uint8",
    "int16",
    "uint16",
    "int32",
    "uint32",
    "string",
    "bool",
    "array_uint32"
};

const char ddi_firehose_bool_name[2][DDI_FIREHOSE_SIZE_BOOLLEN]=
{
    "false",
    "true"
};

ddi_firehose_item_p current_item = NULL;
ddi_firehose_params_p current_item_params = NULL;
ddi_firehose_rspons_p current_item_rspons = NULL;
ddi_firehose_item_set_p ddi_firehose_package = NULL;

tag_handler_t CurrentHandlerFunction;   // this will always point to latest TAG function, i.e. handleConfigure()

firehose_tag_data_t firehose_tag_data[] =
{
    {"ddinfo",                  handleDDIInfo},
    {"Reset",                   handleReset},
    {"nop",                     handleNop}            // Use this with Verbose="1", i.e. <NOP value="ping" Verbose="1" /> to turn on verbose logging for debug
};

extern uint8 gSupportedClockLevel ;
extern uint32 bimc_clk_plan[MAX_CLOCK_FREQ];

void InitBufferWithXMLHeader(byte *MyBuffer, SIZE_T Length);
void CloseTXBuffer(void);
void AppendToBuffer(byte *MyBuffer, char *buf, SIZE_T MaxBufferSize);
char * RemoveBannedChars(char *p);


/* Temporary bringup function to clear the USB Buffers. */
void deviceprogrammer_zi_buffers (void)
{

    memset (&fh, 0, sizeof(fh));
    //memset (&storage_extras, 0, sizeof(storage_extras));

    memset (lite_main_channel_buffer_A, 0, sizeof(lite_main_channel_buffer_A));
    memset (lite_main_channel_buffer_B, 0, sizeof(lite_main_channel_buffer_B));
}

static void firehoseResetValidationVariables()
{
    fh.num_packets_received = 0;

    fh.validation_hash_buffer_num_hashes = 0;
    fh.validation_hash_buffer_capacity = sizeof(fh.validation_hash_buffer) /
                                         sizeof(fh.validation_hash_value);
    fh.validation_hash_buffer_new_capacity = fh.validation_hash_buffer_capacity;

    fh.validation_hash_buffer_index = 0;
    fh.validation_table_count = 0;
    fh.validation_signed_hash_received = FALSE;
}

void initFirehoseProtocol()
{
    byte *channelA;
    byte *channelB;
    uint32 channel_size;

    /* Set the default values for the buffers as Lite buffers. */
    channelA = lite_main_channel_buffer_A;
    channelB = lite_main_channel_buffer_B;
    channel_size = FIREHOSE_LITE_CHANNEL_BUFFER_SIZE;
    fh.nak_all_packets = 0;

    fh.tx_buffer = transmit_buffer;
    // Channel variables
    fh.channel_error_code = 0;
    fh.channel_bytes_read = 0;
    fh.channel_read_completed = FALSE;
    //fh.channel_total_bytes_read = 0;
    fh.channel_write_completed = FALSE;
    //fh.channel_bytes_written = 0;
    //fh.channel_total_bytes_written = 0;

    fh.channel_buffer[0] = channelA;
    fh.channel_buffer[1] = channelB;
    fh.channel_buffer_capacity = channel_size;
    //fh.channel_num_errors = 0;
    fh.channel_buffer_queued = FALSE;
    fh.channel_buffer_to_use = 0;

    fh.debug_log_position = 0;


    //xmlInitReader(&(fh.xml_reader), NULL, 0);
    //xmlInitWriter(&(fh.xml_writer),
    //             fh.tx_buffer,
    //             FIREHOSE_TX_BUFFER_SIZE);
    //storage_device_init_struct(&fh.store_dev);

    //fh.skip_storage_writes = FALSE;
    //fh.hash_in_non_secure = FALSE;
    //fh.verbose = FALSE;
    //fh.ack_raw_data_every = 0;

    firehoseResetValidationVariables();
}

void debugMessage(const char* format, ...)
{
    char *temp_log_buffer = (char *) fh.debug_log_buffer[fh.debug_log_position];
    SIZE_T buffer_space = FIREHOSE_DEBUG_LOG_MESSAGE_SIZE;

    va_list args;
    va_start (args, format);

    vsnprintf(temp_log_buffer,
              buffer_space,
              format,
              args);
    va_end (args);
    fh.debug_log_position = (fh.debug_log_position + 1) % FIREHOSE_NUM_DEBUG_LOG_MESSAGES;
}

void shutDownUSB()
{
    qusb_al_bulk_shutdown();
    busywait(3000000);
}

static void packet_handle_input_buf (uint32 bytes_read, uint32 err_code)
{
    debugMessage("cback bytes_read=%u err_code=%u", bytes_read, err_code);
    fh.channel_error_code = err_code;
    if (err_code != BULK_SUCCESS)
    {
        fh.channel_bytes_read = 0;
        //fh.channel_num_errors += 1;
        //usb_al_bulk_cancel_rx();
    }
    else
    {
        fh.channel_bytes_read = bytes_read;
        fh.num_packets_received += 1;
    }
    //fh.channel_total_bytes_read += bytes_read;
    fh.channel_read_completed = TRUE;
    return;
}

firehose_error_t readChannel(byte** packet_ptr, SIZE_T bytes_to_read, SIZE_T *bytes_read, boolean queue_only)
{
    // Since the 'channel' variables are directly manipulated here, they must not be used by clients such
    // as handleProgram directly. Only the copies made by this function (packet_ptr, bytes_read) must
    // be used by those client functions

    if (fh.channel_buffer_queued == FALSE)
    {
        uint32 frame_size = usb_al_bulk_get_max_packet_size ();
        uint32 usb_pad;
        debugMessage("In readChannel queue %lld", bytes_to_read);

        fh.channel_read_completed = FALSE;
        fh.channel_bytes_read = 0;
        fh.channel_buffer_queued = TRUE;

        // Check if the number of bytes is a multiple of the USB frame size.
        // The frame size depends if it is USB3.0 (Super Seed) or USB2.0
        // (High Speed) and it has to be a multiple of the frame size for the
        // usb_al_bulk_receive to return success.
        usb_pad = bytes_to_read % frame_size;
        if (usb_pad != 0)
        {
            // round up to the USB PAD boundary.
            bytes_to_read += frame_size - usb_pad;
        }

        if (bytes_to_read > fh.channel_buffer_capacity)
        {
            logMessage("readChannel bytes to read larger than buffer capacity %d>%d", bytes_to_read, fh.channel_buffer_capacity);
            return FIREHOSE_ERROR;
        }

        usb_al_bulk_receive(fh.channel_buffer[fh.channel_buffer_to_use], bytes_to_read, packet_handle_input_buf, &fh.channel_error_code);

        if (fh.channel_error_code != BULK_SUCCESS)
        {
            logMessage("USB read failed - usb_al_bulk_receive() gave channel error code %u",fh.channel_error_code);
            MyErrorMessage(USB_READ_FAILURE);
            return FIREHOSE_TRANSPORT_ERROR;
        }
    }

    if (queue_only == TRUE)
        return FIREHOSE_SUCCESS;

    while (fh.channel_read_completed == FALSE)
    {
        usb_al_bulk_poll();
    }

    if (fh.channel_bytes_read > fh.channel_buffer_capacity)
    {
        debugMessage("read fh.channel_bytes_read=%i fh.channel_buffer_capacity=%i", fh.channel_bytes_read, fh.channel_buffer_capacity);
        return FIREHOSE_TRANSPORT_ERROR;
    }

    *bytes_read = fh.channel_bytes_read;
    *packet_ptr = fh.channel_buffer[fh.channel_buffer_to_use];
    fh.channel_buffer_queued = FALSE;
    fh.channel_buffer_to_use = 1 - fh.channel_buffer_to_use;

    debugMessage("Leaving readChannel bytes_read %lld", fh.channel_bytes_read);

    if (fh.channel_error_code != BULK_SUCCESS)
    {
        logMessage("USB read failed - usb_al_bulk_receive() gave channel error code %u",fh.channel_error_code);
        MyErrorMessage(USB_READ_FAILURE);
        return FIREHOSE_TRANSPORT_ERROR;
    }

    return FIREHOSE_SUCCESS;
}

static void packet_handle_outgoing_buf(uint32 bytes_written, uint32 err_code)
{
    //fh.channel_bytes_written = bytes_written;
    //fh.channel_total_bytes_written += bytes_written;
    fh.channel_error_code = err_code;
    fh.channel_write_completed = TRUE;
    return;
}

static firehose_error_t writeChannel(byte* buffer, SIZE_T length)
{
    fh.channel_write_completed = FALSE;

    debugMessage("bulk_tx() buffer at 0x%X", buffer);
    debugMessage("bulk_tx() length %lld", length);

    usb_al_bulk_transmit(buffer, length, packet_handle_outgoing_buf, &fh.channel_error_code);

    if (fh.channel_error_code != BULK_SUCCESS)
    {
        MyErrorMessage(USB_WRITE_FAILURE);
        return FIREHOSE_TRANSPORT_ERROR;
    }

    while (fh.channel_write_completed == FALSE)
    {
        usb_al_bulk_poll();
    }

    return FIREHOSE_SUCCESS;
}

static firehose_error_t sendTransmitBuffer()
{
    debugMessage("sendTransmitBuffer() fh.tx_buffer at 0x%X", fh.tx_buffer);
    firehose_error_t retval = writeChannel(fh.tx_buffer, strlen((const char *)fh.tx_buffer));
    return retval;
}
// format: C string that contains a format string that follows the same specifications as format in printf

#ifdef _MSC_VER
#define dbg(log_level, fmt, ...) MyLog(log_level, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#else
#define dbg(log_level, fmt ...) logMessage(fmt)
#endif


void logMessage(const char* format, ...)
{
    int retval;
    int written;
    char temp_log_buffer[FIREHOSE_LOG_BUFFER_SIZE] = {0};  // no single message > 256 bytes
    SIZE_T buffer_space = sizeof(temp_log_buffer);

    va_list args;
    va_start (args, format);

    retval = vsnprintf(temp_log_buffer,
                       buffer_space,
                       format,
                       args);
    va_end (args);
    written = MIN(retval, buffer_space - 1); // vsnprintf retval doesn't include null char


    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<log value=\"", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,temp_log_buffer, FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"\"/>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"</data>", FIREHOSE_TX_BUFFER_SIZE);
    sendTransmitBuffer();

}

void ErrorMessage(unsigned int LineNumber, firehose_error_code_t ErrorCode)
{
    unsigned int i = 0, found = 0;

    for(i=0; i<FH_ERR_MAX; i++)
    {
        if(ErrorCode == AllErrorsStruct[i].ErrorNum)
        {
            found = 1;
            break;
        }
    }

    if(found)
        logMessage("ERROR %d: Line %d: %s", ErrorCode, LineNumber, AllErrorsStruct[i].pErrorMessage );
    else
        logMessage("ERROR %d: Line %d: Unknown error is *not* in AllErrorsStruct", ErrorCode, LineNumber);

}

firehose_error_t sendResponse(response_t response)
{
    if (fh.nak_all_packets != 0)
    {
        logMessage("ERROR: DDR Test failed, pease file a CR for this. Fall back to Lite version while this gets fixed.");
    }

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    if(response==ACK && fh.nak_all_packets == 0)
    {
        AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
    }
    else
    {
        AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
    }

    sendTransmitBuffer();

    if(response==ACK)
        return FIREHOSE_SUCCESS;
    else
        return FIREHOSE_ERROR;
}


void ddi_firehose_print_debug(const char* format, ...)
{
    char *temp_log_buffer = (char *) fh.debug_log_buffer[fh.debug_log_position];
    SIZE_T buffer_space = FIREHOSE_DEBUG_LOG_MESSAGE_SIZE;

    va_list args;
    va_start (args, format);

    vsnprintf(temp_log_buffer,
              buffer_space,
              format,
              args);
    va_end (args);
    boot_log_message(temp_log_buffer);
}


firehose_error_t ddi_firehose_print_log(const char* format, ...)
{
    int retval;
    int written;
    char temp_log_buffer[FIREHOSE_LOG_BUFFER_SIZE] = {0};  // no single message > 256 bytes
    SIZE_T buffer_space = sizeof(temp_log_buffer);

    va_list args;
    va_start (args, format);

    retval = vsnprintf(temp_log_buffer,
                       buffer_space,
                       format,
                       args);
    va_end (args);
    written = MIN(retval, buffer_space - 1); // vsnprintf retval doesn't include null char

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<log value=\"", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,temp_log_buffer, FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"\"/>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"</data>", FIREHOSE_TX_BUFFER_SIZE);
    sendTransmitBuffer();

    busywait(10000);

    return FIREHOSE_SUCCESS;
}


firehose_error_t ddi_firehose_print_response(const char* item_name, const char* rsp_name, const char* rsp_val)
{
    char temp_buffer[FIREHOSE_TEMP_ATTRIBUTE_BUFFER_SIZE] = {0};
    char* responseTag = "response";

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<", FIREHOSE_TX_BUFFER_SIZE);
    snprintf(temp_buffer, BUFFER_LENGTH,"%s%s", responseTag, item_name);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(temp_buffer, BUFFER_LENGTH," %s=\"%s\"/>\n</data> ", rsp_name, rsp_val);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE );
    sendTransmitBuffer();
    sendResponse(ACK);

    return FIREHOSE_SUCCESS;
}

firehose_error_t sendDDIResponseFields(const char *tag_name, int n_args, ...)
{
    va_list args;
    int i;

    char format;
    int int_arg;
    int32 uint_arg;
    SIZE_T size_arg;
    char char_arg;
    char* string_arg;
    char *attribute_name;
    char temp_attribute_buffer[FIREHOSE_TEMP_ATTRIBUTE_BUFFER_SIZE] = {0};
    int written;

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    snprintf(str, BUFFER_LENGTH,"<%s",tag_name);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );

    va_start (args, n_args);
    for (i = 0; i < n_args; i++)
    {
        attribute_name = va_arg(args, char *);
        format = (char) va_arg(args, int);
        switch(format)
        {
            case 's':
                string_arg = va_arg(args, char *);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   "%s",
                                   string_arg);
                break;
            case 'd':
                int_arg = va_arg(args, int);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   "%d",
                                   int_arg);
                break;
            case 'u':
                uint_arg = va_arg(args, uint32);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   "%u",
                                   uint_arg);
                break;
            case 't':
                size_arg = va_arg(args, SIZE_T);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   SIZE_T_FORMAT,
                                   size_arg);
                break;
            case 'l':
                size_arg = va_arg(args, long long int);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   "%lld",
                                   size_arg);
                break;
            case 'c':
                char_arg = (char) va_arg(args, int);
                written = snprintf(temp_attribute_buffer,
                                   sizeof(temp_attribute_buffer),
                                   "%c",
                                   char_arg);
                break;
            default:
                va_end (args);
                return FIREHOSE_ERROR;
        }

        if (written >= sizeof(temp_attribute_buffer))
        {
            va_end (args);
            return FIREHOSE_ERROR;
        }

        snprintf(str, BUFFER_LENGTH," %s=\"%s\"", attribute_name, temp_attribute_buffer);
        AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );

    }

    va_end (args);

    AppendToBuffer(fh.tx_buffer," />\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"</data>\r\n", FIREHOSE_TX_BUFFER_SIZE );
    sendTransmitBuffer();
    busywait(10000);
    return FIREHOSE_SUCCESS;
}

int getfirehose_tag_data_num()
{
    return (int)(sizeof(firehose_tag_data)/sizeof(firehose_tag_data_t));

}

firehose_error_t handleNop()
{
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}
firehose_error_t handleReset()
{
    resetDDI();
    return FIREHOSE_SUCCESS;
}

firehose_error_t handleDDIInfo()
{
    //ddi_firehose_info_p tmpInfo = NULL;
    ddi_firehose_item_p tmpItems = NULL;
    ddi_firehose_params_p tmpItemParams = NULL;
    ddi_firehose_rspons_p tmpItemRspons = NULL;
    //ddi_firehose_info_p info_arr = NULL;

    int itemNum = 0;
    int itemParamNum = 0;
    int itemRsponNum = 0;

    if(NULL == ddi_firehose_package)
    {
        ddi_firehose_print_debug("DDI item package not defined!");
        return FIREHOSE_ERROR;
    }

    if(NULL == ddi_firehose_package->item_arr)
    {
        ddi_firehose_print_debug("No valid item in DDI package, NULL array!");
        return FIREHOSE_ERROR;
    }

    itemNum = 0;
    tmpItems = ddi_firehose_package->item_arr;
    while(0 != strlen(tmpItems->item_name))
    {
        if(cmdIsCompatible(tmpItems))
            itemNum++;
        tmpItems++;
    }
    if(0 == itemNum)
    {
        ddi_firehose_print_debug("No valid item in DDI package, 0 item!");
        return FIREHOSE_ERROR;
    }

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<ddidefinition ", FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," Version=\"%d\"", ddi_firehose_package->version);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," Platform=\"%s\"", ddi_firehose_package->platform);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," BuildDate=\"%s\"",__DATE__);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," BuildTime=\"%s\"",__TIME__);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," DSFVersion=\"%d.%d\"",((DDI_share_data->version) >> 16),((DDI_share_data->version) & 0x0000FFFF));
	AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," DSFRPMversion=\"%d.%d\"",((DDI_share_data->rpm_version) >> 16),((DDI_share_data->rpm_version) & 0x0000FFFF));
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );
    snprintf(str, BUFFER_LENGTH," ClkPlan=\"\r\n");
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE);

    for (int i = 0; i < gSupportedClockLevel ; i++)
    {
        snprintf(str, BUFFER_LENGTH,"%d - %d,\r\n", i, bimc_clk_plan[i]);
        AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE);
    }
    AppendToBuffer(fh.tx_buffer,"\r\n\"", FIREHOSE_TX_BUFFER_SIZE);

#if 0
    info_arr = ddi_firehose_package->info_arr;
    while(0 != strlen(info_arr->info_key))
    {
        snprintf(str, BUFFER_LENGTH," %s=\"%s\"", info_arr->info_key, info_arr->info_val);
        AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE);
        info_arr++;
    }
    AppendToBuffer(fh.tx_buffer,"\r\n\"", FIREHOSE_TX_BUFFER_SIZE);
#endif

    snprintf(str, BUFFER_LENGTH," CommandNum=\"%d\r\n\"", itemNum);
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE );

    snprintf(str, BUFFER_LENGTH," TrainingType=\"\r\n");
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"0 - READ,\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"1 - WRITE,\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"2 - CA\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"\r\n\"", FIREHOSE_TX_BUFFER_SIZE);

    snprintf(str, BUFFER_LENGTH," Testline=\"\r\n");
    AppendToBuffer(fh.tx_buffer,str, FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"0 - DQ,\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"1 - DQS,\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"2 - CA,\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"3 - CK\r\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"\r\n\"", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer," />\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"</data>\r\n", FIREHOSE_TX_BUFFER_SIZE );
    sendTransmitBuffer();

    busywait(10000);

    tmpItems = ddi_firehose_package->item_arr;

    while(0 != strlen(tmpItems->item_name))
    {
        if(cmdIsCompatible(tmpItems))
        {
            // loop for param num
            itemParamNum = 0;
            if(NULL != tmpItems->item_params_arr)
            {
                tmpItemParams = tmpItems->item_params_arr;
                while(0 != strlen(tmpItemParams->param_name))
                {
                    itemParamNum++;
                    tmpItemParams++;
                }
            }

            // loop for response num
            itemRsponNum = 0;
            if(NULL != tmpItems->item_rspons_arr)
            {
                tmpItemRspons = tmpItems->item_rspons_arr;
                while(0 != strlen(tmpItemRspons->rspons_name))
                {
                    itemRsponNum++;
                    tmpItemRspons++;
                }
            }

            // send command defination
            sendDDIResponseFields(
                "commandefinition",
                4,
                "name",          's', tmpItems->item_name,
                "version",       'u', tmpItems->item_ver,
                "parameternum",  'u', itemParamNum,
                "responsenum",   'u', itemRsponNum
            );

            // send parameter defination
            if(NULL != tmpItems->item_params_arr)
            {
                tmpItemParams = tmpItems->item_params_arr;
                while(0 != strlen(tmpItemParams->param_name))
                {
                    if(DDI_FIREHOSE_UINT8 == tmpItemParams->param_type ||
                       DDI_FIREHOSE_UINT16 == tmpItemParams->param_type ||
                       DDI_FIREHOSE_UINT32 == tmpItemParams->param_type)
                    {
                        sendDDIResponseFields(
                            "parameterdefiniton",
                            5,
                            "name",          's', tmpItemParams->param_name,
                            "type",          's', ddi_firehose_type_name[tmpItemParams->param_type],
                            "min",           't', tmpItemParams->param_min,
                            "max",           't', tmpItemParams->param_max,
                            "default",       't', tmpItemParams->param_default
                        );
                    }
                    else if(DDI_FIREHOSE_INT8 == tmpItemParams->param_type ||
                            DDI_FIREHOSE_INT16 == tmpItemParams->param_type ||
                            DDI_FIREHOSE_INT32 == tmpItemParams->param_type)
                    {
                        sendDDIResponseFields(
                            "parameterdefiniton",
                            5,
                            "name",          's', tmpItemParams->param_name,
                            "type",          's', ddi_firehose_type_name[tmpItemParams->param_type],
                            "min",           'd', (int)tmpItemParams->param_min,
                            "max",           'd', (int)tmpItemParams->param_max,
                            "default",       'd', (int)tmpItemParams->param_default
                        );
                    }
                    else
                    {

                    }
                    tmpItemParams++;
                }
            }

            // send response defination
            if(NULL != tmpItems->item_rspons_arr)
            {
                tmpItemRspons = tmpItems->item_rspons_arr;
                while(0 != strlen(tmpItemRspons->rspons_name))
                {
                    sendDDIResponseFields(
                        "responsedefinition",
                        2,
                        "name",          's', tmpItemRspons->rspons_name,
                        "type",          's', ddi_firehose_type_name[tmpItemRspons->rspons_type]
                    );
                    tmpItemRspons++;
                }
            }
        }
        tmpItems++;
    }

    sendResponse(ACK);// acknowledge that we are done !!

    return FIREHOSE_SUCCESS;

}


static void logDigest(char* prefix, byte* digest, SIZE_T length)
{
    int i = 0;
    int written;
    char log_string[FIREHOSE_TEMP_BUFFER_SIZE] = { 0 };

    if (sizeof(log_string) < ((length * 2) + strlen(prefix) + 1))
    {
        return;
    }

    written = snprintf(log_string,
                       sizeof(log_string),
                       "%s",
                       prefix);
    while (written < sizeof(log_string) && i < length)
    {
        written += snprintf(log_string + written,
                            sizeof(log_string) - written,
                            "%02X",
                            digest[i]);
        i++;
    }

    logMessage(log_string);
}

static void firehoseResetValidation()
{
    firehoseResetValidationVariables();
    logMessage("Reset validation state. Expecting Digital signature");
}

static firehose_error_t recvNextPacket(byte** packet_ptr, SIZE_T bytes_to_read,SIZE_T *bytes_read, boolean queue_only)
{

    firehose_error_t read_retval = FIREHOSE_SUCCESS;
    read_retval = readChannel(packet_ptr, bytes_to_read, bytes_read, queue_only);
    if (read_retval != FIREHOSE_SUCCESS)
    {
        return read_retval;
    }

    if (queue_only == TRUE)
        return FIREHOSE_SUCCESS;

    return FIREHOSE_SUCCESS;
}

static firehose_error_t queueNextPacket(SIZE_T bytes_to_read)
{
    return recvNextPacket(NULL, bytes_to_read, NULL, TRUE);
}

static firehose_error_t getNextPacket(byte** packet_ptr, SIZE_T bytes_to_read, SIZE_T *bytes_read)
{
    return recvNextPacket(packet_ptr, bytes_to_read, bytes_read, FALSE);
}

// This reads the next packet sent over USB and initializes the XML
// reader fh.xml_reader with it.
//
// Returns: FIREHOSE_SUCCESS if valid XML was received
//          FIREHOSE_ERROR on read error, invalid XML, or XML too large
//
// NOTE: How 'we' choose to validate the XML right now is not very generic.
// Hence this should not be put under the xml parser code
firehose_error_t getXMLPacket()
{
    SIZE_T bytes_read = 0;
    firehose_error_t read_retval;
    volatile int i = 0;

    while (bytes_read == 0)
        read_retval = getNextPacket(&packet, MIN(sizeof(fh.xml_buffer), fh.channel_buffer_capacity), &bytes_read);


    i = 1; // for breakpoint

    if (FIREHOSE_SUCCESS != read_retval)
        return read_retval;

    i = 2; // for breakpoint

    if (sizeof(fh.xml_buffer) < bytes_read)
    {
        i = bytes_read; // for breakpoint

        logMessage("XML (%lld bytes) is too big for buffer (max %lld bytes)", bytes_read, sizeof(fh.xml_buffer));
        MyErrorMessage(XML_PACKET_TOO_LARGE);
        return FIREHOSE_ERROR;
    }

    i = 3; // for breakpoint
//#define memscpy(dest,destsize,src,srcsize) memcpy(dest,src,srcsize)
    //memscpy(fh.xml_buffer, sizeof(fh.xml_buffer), packet, bytes_read);
    memset(fh.xml_buffer, 0, sizeof(fh.xml_buffer));
    memscpy(fh.xml_buffer, sizeof(fh.xml_buffer), packet, bytes_read);
    //xmlInitReader(&fh.xml_reader, fh.xml_buffer, bytes_read);

    i = 4; // for breakpoint

    return FIREHOSE_SUCCESS;
}

void initFirehoseTransport()
{
    usb_al_bulk_init();
}

int AssignAttribute(char *NewAttrName, char *NewAttrValue, SIZE_T NewAttrValueLen)
{
    volatile SIZE_T Matched=0;
    ddi_firehose_params_p InputParams = NULL;

    //printf("\n\nIn AssignAttribute(%s,%s)\n",NewAttrName,NewAttrValue);

    //logMessage("In AssignAttribute(%s,%s) and fh.attrs.Verbose=0x%X",NewAttrName,NewAttrValue,fh.attrs.Verbose);

    if(NULL != current_item_params && NULL != current_item && (0 != strlen(current_item->item_name)))
    {
        InputParams = current_item_params;
        while(0 != strlen(InputParams->param_name))
        {
            if (strncasecmp(NewTagName, current_item->item_name, strlen((const char *)current_item->item_name)) == 0)
            {
                if (strncasecmp(NewAttrName, InputParams->param_name, strlen((const char *)InputParams->param_name)) == 0)
                {
                    Matched = 1;
                    if( CopyString(InputParams->param_entity, NewAttrValue, 0, 0, strlen(NewAttrValue), sizeof(InputParams->param_entity), NewAttrValueLen) == 0)
                    {
                        dbg(LOG_ERROR, "Failed to copy string");
                        return 1;
                    }
                }
            }

            InputParams ++;
        }
    }
    if(Matched==0)
    {
        if(fh.attrs.Verbose == TRUE)
            dbg(LOG_INFO,"IGNORING UNRECOGNIZED Attribute '%s' with value '%s'",NewAttrName,NewAttrValue);
    }

    return 0;
}


SIZE_T IsEmptySpace(char c)
{
    if( c == 0xA )
    {
        return 1;
    }
    if( c == 0xD )
    {
        return 1;
    }
    if( c == 0x9 )
    {
        return 1;
    }
    if( c == 0x20)
    {
        return 1;
    }

    return 0;
}

char * RemoveEverythingButTags(char *Packet, SIZE_T  CurrentPacketLoc, SIZE_T MaxPacketSize)
{
    SIZE_T  PacketLength,PacketLoc=0,i;
    char *pch;
    long FoundLeftBrace=-1,FoundRightBrace=-1,FoundForwardSlash=-1,Found=0;

    if(CurrentPacketLoc>=MaxPacketSize)
        return Packet; // nothing to do

    PacketLength= strlen((const char *)Packet);

    if((!PacketLength) || (PacketLength>=MaxPacketSize))
        return Packet; // should be impossible

    for(i=0; i<PacketLength; i++)
    {
        if(Found==0)
        {
            if(i+3<PacketLength)
            {
                if(Packet[i]=='<' && Packet[i+1]=='!' && Packet[i+2]=='-' && Packet[i+3]=='-')  // protected by if(i+3<PacketLength) above
                {
                    Found = 1;
                    Packet[i] = ' ';
                    Packet[i+1] = ' ';
                    Packet[i+2] = ' ';
                    Packet[i+3] = ' ';
                    i+=3;
                }
            }
        } // end of if(Found==0)
        else
        {
            // we are inside of a comment
            if(i+2<PacketLength)
            {
                if(Packet[i]=='-' && Packet[i+1]=='-' && Packet[i+2]=='>')  // protected by if(i+2<PacketLength) above
                {
                    Found = 0;
                    Packet[i] = ' ';
                    Packet[i+1] = ' ';
                    Packet[i+2] = ' ';
                    i+=2;
                    continue;
                }
            } // end if(i+2<PacketLength)
            Packet[i] = ' '; // remove since this is a comment
        }

    }

    // At this point, XML file has all <!-- comments --> replaced by spaces


    // Now nuke the first <?xml version="1.0" ?>

    do
    {
        pch = strstr(Packet, "xml version");
        if(pch==NULL)
        {
            break;
        }

        // to be this far we found "xml version"
        // Now look slightly beyond that

        pch = strstr(pch, ">");             // is now pointing to the beginning of the file
        if(pch!=NULL) //'\0')                   // pch = "<configuration> <options> DOWNLOAD_PROTOCOL       = FIREHOSE etc etc
        {
            memset(Packet,0x20,pch-&Packet[PacketLoc]+1);   // this removes <?xml version="1.0" ?>
        }

        // We could have more than 1 XML file here
        pch = strstr(Packet, "xml version");
        if((pch!=NULL) && (pch > Packet))
        {
            PacketLength = pch-Packet; // now length updated to start of next XML
        }


        // find last tag name
        // find last tag name
        for(i=PacketLength-1; i>0; i--)
        {
            if( Packet[i] == '>' )
            {
                FoundRightBrace = i;
            }

            if(FoundRightBrace>0)
                if( Packet[i] == '/' )
                {
                    FoundForwardSlash = i;
                }

            if(FoundRightBrace>0 && FoundForwardSlash>0)
            {
                if( Packet[i] == '<' )
                {
                    FoundLeftBrace = i;
                    break;
                }
            } // end if(FoundRightBrace>0)
        } // end for

        if( (FoundRightBrace <= 0) || (FoundForwardSlash <= 0) ||
            (FoundRightBrace-FoundForwardSlash+2) > MaxPacketSize-1 )
        {
            logMessage("Either closing tag is bigger than %d bytes, or the XML file is not formed correctly",MaxPacketSize);
            return Packet; // something is wrong
        }

        memset(CurrentTagName,0,sizeof(CurrentTagName));

        if( CopyString(CurrentTagName, Packet, 0, FoundForwardSlash, FoundRightBrace-FoundForwardSlash+1, sizeof(CurrentTagName), MaxPacketSize)  == 0)
        {
            logMessage("3 Failed to copy string of length %ld bytes into CurrentTagName",FoundRightBrace-FoundForwardSlash+1);
            return Packet; // something is wrong
        }
        //strncpy(CurrentTagName,&Packet[FoundForwardSlash],FoundRightBrace-FoundForwardSlash+1);   // CurrentTagName = "/data>" OR "/configuration>" etc etc

        //CurrentTagName[FoundRightBrace-FoundForwardSlash+1] = '\0';

        memset(&Packet[FoundForwardSlash-1],0x20,strlen(CurrentTagName)+1); // this takes out </configuration> OR </data> at the end of the file

        CurrentTagName[0] = '<';                            // CurrentTagName = "<data>" OR "<configuration>" etc etc

        pch = strstr(Packet, CurrentTagName);               // is now pointing to the beginning of the file
        if(pch!=NULL) //'\0')                   // pch = "<configuration> <options> DOWNLOAD_PROTOCOL       = FIREHOSE etc etc
        {
            memset(Packet,0x20,strlen(CurrentTagName)+(pch-Packet)); // nukes everything up to <data>
        }
        else
        {
            logMessage("ERROR: Either closing tag is bigger than %d bytes, or the XML file is not formed correctly",MaxPacketSize);
            logMessage("ERROR: Could not find '%s' tag",CurrentTagName);
            return Packet; // something is wrong
        }

        break; // breaking the do loop

    }
    while(1);  // end of looking for "xml version"

    return Packet;
}

SIZE_T  DetermineTag(char *Packet, SIZE_T  CurrentPacketLoc, SIZE_T MaxPacketSize)
{
    volatile SIZE_T  i=0;
    SIZE_T  PacketLength;
    int CurrentTag = -1;
    char *pch;
    long FoundRightBrace=-1;
    ddi_firehose_item_p tmpItems = NULL;

    if(CurrentPacketLoc>=MaxPacketSize)
        return 0;   // out of packet

    Packet = RemoveEverythingButTags(Packet,CurrentPacketLoc, MaxPacketSize);
    // Step 1. String away header
    // Step 2. Strip away <data> tags
    // step 3. Get tag_name
    // step 4. Get attributes
    PacketLength= strlen((const char *)Packet);

    if(PacketLength>=MaxPacketSize)
        return 0;   // should be impossible


    //ResetAllAttributeAssignFlags();

    // This chomps up empty space till we hit a tag
    while( IsEmptySpace( Packet[CurrentPacketLoc] ) )
    {
        CurrentPacketLoc++;

        if(CurrentPacketLoc>=PacketLength)
        {
            logMessage("ERROR: XML packet not formed correctly. Ran out of room looking for TAG");

            return 0;
        }
    }

    if(Packet[CurrentPacketLoc]!='<')
    {
        logMessage("ERROR: XML not formed correctly. Expected a &lt; character at loc %d",CurrentPacketLoc);
        return 0;   // not formed correctly
    }

    CurrentPacketLoc++;    // move past the above opening <

    // Could be one solid tag like <options>, test by looking for spaces *before* seeing a '>'
    FoundRightBrace = -1;
    for(i=CurrentPacketLoc; i<PacketLength; i++)
    {
        if( Packet[i] == '>' )
        {
            FoundRightBrace = i;
            break;
        }
        if( Packet[i] == ' ' )
        {
            break;
        }
    }

    if(FoundRightBrace>0)
    {
        // this is something like <options> some text </options>
        ParseAttributes = 0;    // need to parse the strings

        CopyString(NewTagName, Packet, 0, CurrentPacketLoc,   FoundRightBrace-CurrentPacketLoc, sizeof(NewTagName), MaxPacketSize );   // NewTagName has the TAG now
        RemoveBannedChars(NewTagName); // chars like " < > are replaced by _

        CurrentPacketLoc = FoundRightBrace + 1; // The +1 to get past the >

    }
    else
    {
        // or could be tag with attributes like <program filename
        ParseAttributes = 1;

        pch = strstr(&Packet[CurrentPacketLoc], " ");          // Find a space after the TAG name

        if(pch==NULL) //'\0')   // if null, XML is not formed correctly
        {
            logMessage("ERROR: XML not formed correctly. Expected one SPACE character at loc %d",CurrentPacketLoc);
            return 0;   // not formed correctly
        }

        if( pch-&Packet[CurrentPacketLoc] > MAX_TAG_NAME_LENGTH )
        {
            logMessage("ERROR: The XML TAG is too long (%d chars) only %d chars allowed",(pch-&Packet[CurrentPacketLoc]),MAX_TAG_NAME_LENGTH);
            return 0;   // not formed correctly
        }


        CopyString(NewTagName, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewTagName), MaxPacketSize );   // NewTagName has the TAG now
        RemoveBannedChars(NewTagName); // chars like " < > are replaced by _

        CurrentPacketLoc += strlen((const char *)NewTagName);
        CurrentPacketLoc++;    // move past the above opening space we confirmed exists above

    }

    // to match item
    tmpItems = ddi_firehose_package->item_arr;
    while(0 != strlen(tmpItems->item_name))
    {
        if(strncasecmp(tmpItems->item_name, NewTagName,strlen((const char *)NewTagName)) == 0)
        {
            current_item = tmpItems;
            if(tmpItems->item_params_arr != NULL)
                current_item_params = tmpItems->item_params_arr;
            if(tmpItems->item_rspons_arr != NULL)
                current_item_rspons = tmpItems->item_rspons_arr;

            CurrentTag = i;
            break;
        }
        tmpItems++;
    }

    //For these cmd have no attribute expect Retrain
    for (i = 0; i < getfirehose_tag_data_num(); i++)
    {
        if (strncasecmp(firehose_tag_data[i].tag_name, NewTagName,strlen((const char *)NewTagName)) == 0)
        {
            CurrentTag             = i;
            CurrentHandlerFunction = firehose_tag_data[i].handler;
            break;
        }
    } // end i

    if(CurrentTag==-1)
    {
        logMessage("**WARNING Ignoring Unrecognized tag '%s'", NewTagName);
        return 0;
    }

    // The above got the <TAG>, accessible like this firehose_tag_data[CurrentTag].handler and firehose_tag_data[CurrentTag].tag_name

    return CurrentPacketLoc;

} // end DetermineTag(char *Packet, SIZE_T  PacketLoc)


SIZE_T  DetermineAttributes(char *Packet, SIZE_T  CurrentPacketLoc, SIZE_T MaxPacketSize)
{
    SIZE_T  AttributesFound=0;
    SIZE_T  PacketLength;

    char NewAttrName[MAX_TAG_ATTR_LENGTH];

    char *pch;

    if(CurrentPacketLoc>=MaxPacketSize)
        return 0;   // ran out of packet

    // step 4. Get attributes
    PacketLength    = strlen((const char *)Packet);
    // Packet[CurrentPacketLoc] should be at the first letter of the attribute now
    // They all look like this attribute1="value1" attribute2="value2"
    // Meaning only spaces seperate them

    if(PacketLength>=MaxPacketSize)
        return 0;   // should be impossible

    AttributesFound = 0;

    while(CurrentPacketLoc < PacketLength)
    {
        pch = strstr(&Packet[CurrentPacketLoc], "=");          // Find an equals sign
        if(pch==NULL) //'\0')   // if null, we didn't find it
        {
            dbg(LOG_ERROR,"XML not formed correctly. Could not find '=' character");
            return 0;   // not formed correctly
        }

        if( pch-&Packet[CurrentPacketLoc] > 3072 )
        {
            dbg(LOG_ERROR,"The value for XML attribute is too long (%d chars) only %d chars allowed",(pch-&Packet[CurrentPacketLoc]),MAX_TAG_ATTR_LENGTH);
            return 0;   // not formed correctly
        }

        CopyString(NewAttrName, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewAttrName), MaxPacketSize );  // NewAttrName has the ATTR now

        RemoveBannedChars(NewAttrName); // chars like " < > are replaced by _

        CurrentPacketLoc += strlen((const char *)NewAttrName);
        CurrentPacketLoc++;    // move past the = sign

        if(Packet[CurrentPacketLoc]!='"')
        {
            dbg(LOG_ERROR,"XML not formed correctly. Expected one &quot; character at loc %d",CurrentPacketLoc);
            return 0;   // not formed correctly
        }

        CurrentPacketLoc++;    // Before "value" and now we move past the " sign, all that is left now is the actual value"

        pch = strstr(&Packet[CurrentPacketLoc], "\"");         // Find closing "

        if(pch==NULL) //'\0')   // if null, we didn't find it
        {
            dbg(LOG_ERROR,"XML not formed correctly. Expected one &quot; character at loc %d",CurrentPacketLoc);
            return 0;   // not formed correctly
        }

        if( pch-&Packet[CurrentPacketLoc] > 3072 )
        {
            dbg(LOG_ERROR,"The value for XML attribute '%s' is too long (%d chars) only %d chars allowed",NewAttrName,(pch-&Packet[CurrentPacketLoc]),MAX_TAG_ATTR_LENGTH);
            return 0;   // not formed correctly
        }

        CopyString(NewAttrValue, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewAttrValue), MaxPacketSize ); // NewAttrValue has the ATTR value now
        RemoveBannedChars(NewAttrValue); // chars like " < > are replaced by _

        AttributesFound++;

        // FIGURE OUT WHICH ATTRIBUTE AND ASSIGN VALUE



        if (strncasecmp(NewAttrName, "Pattern", strlen((const char *)NewAttrName)) == 0)
        {
            int patternCount = 0;
            uint32 dataBufferSize = sizeof(dataBuffer)/sizeof(uint32);
            uint16 count = 0;
            uint16 patternIx = 0;



            patternElemCnt = 0;
            // tokenize the pattern string
            // get intvalue..
            //save to pattern container

            if (NewAttrValue[0] == '-' && NewAttrValue[1] == '1')
            {
                glen = strlen((const char *)NewAttrValue);
                // use default pattern..
                for (int i = 0 ; i < 256 ; i++) // potential bug...we dont have size of write_in_buffer so we use hard coded data here.TO DO
                {
                    patternDataBuf[i] = write_in_pattern[i];
                    patternElemCnt++;
                }

                if(patternElemCnt%16!=0)
                {
                    return 0;
                }
                else
                {
                    while(patternCount < (dataBufferSize/patternElemCnt))
                    {

                        while(count < patternElemCnt)
                        {
                            dataBuffer[patternIx + count] = patternDataBuf[count];
                            count = count+1;
                        }

                        patternIx = patternIx + count;
                        count = 0;
                        patternCount = patternCount+1;
                    }
                }


            }
            else // assuminng we are getting c style array!!
            {
                glen = getlength(NewAttrValue);
                char *strIx;
                strIx = ddi_strtok(NewAttrValue, "{,}");
                while (strIx != NULL)
                {

                    patternDataBuf[patternElemCnt] = convertStrtoUint(strIx);
                    //sscanf(strIx, "%x", &patternDataBuf[patternElemCnt]);
                    patternElemCnt++;
                    if (patternElemCnt == dataBufferSize)
                    {
                        break;
                    }
                    strIx = ddi_strtok(NULL, "{,}");
                }

                if(patternElemCnt%16!=0)
                {
                    return 0;
                }
                else
                {
                    while(patternCount < (dataBufferSize/patternElemCnt))
                    {

                        while(count < patternElemCnt)
                        {


                            dataBuffer[patternIx + count] = patternDataBuf[count];
                            count = count+1;


                        }

                        patternIx = patternIx + count;
                        count = 0;
                        patternCount = patternCount+1;

                    }
                }

            }

            CurrentPacketLoc += glen;
            CurrentPacketLoc++;    // move past the closing quote " sign

        }
        else
        {
            if( AssignAttribute(NewAttrName, NewAttrValue, sizeof(NewAttrValue)) != 0 )
            {
                dbg(LOG_ERROR,"AssignAttribute failed");
                return 0;   // not formed correctly
            }
            CurrentPacketLoc += strlen((const char *)NewAttrValue);
            CurrentPacketLoc++;    // move past the closing quote " sign
        }

        while( IsEmptySpace( Packet[CurrentPacketLoc] ) )
        {
            CurrentPacketLoc++;

            if(CurrentPacketLoc>=PacketLength)
            {
                dbg(LOG_ERROR,"XML packet not formed correctly. Ran out of room looking for ATTRIBUTES");
                return 0;
            }
        }

        if(Packet[CurrentPacketLoc]=='/')
        {
            // This is the END of the packet
            return CurrentPacketLoc+2; // +2 gets us past the />
        }
    } // end of while(CurrentPacketLoc < PacketLength)

    return 0;       // to be here means we ran out of packet

} // end DetermineAttributes(char *Packet, SIZE_T CurrentPacketLoc)


void InitAttributes(void)
{
    fh.attrs.MaxPayloadSizeToTargetInBytes          = 131072; //ONE_MEGABYTE;
    fh.attrs.MaxPayloadSizeToTargetInBytesSupported = 32768; //ONE_MEGABYTE;
    fh.attrs.MaxPayloadSizeFromTargetInBytes        = 8192; //ONE_MEGABYTE;
    fh.attrs.Verbose                                = 0;
    fh.attrs.MaxDigestTableSizeInBytes              = 8192;
    fh.attrs.AckRawDataEveryNumPackets              = 0;
    fh.attrs.delayinseconds                         = 1;
    fh.attrs.address64                              = 0;
    fh.attrs.value64                                = 0;
    fh.attrs.storagedrive                           = 0;
    fh.attrs.physical_partition_number              = 0;
    fh.attrs.SECTOR_SIZE_IN_BYTES                   = 512;
    fh.attrs.byte_offset                            = 0;
    fh.attrs.physical_partition_number              = 0;
    fh.attrs.size_in_bytes                          = 0;
    fh.attrs.num_partition_sectors                  = 0;
    fh.attrs.file_sector_offset                     = 0;

    fh.attrs.ZlpAwareHost                           = 1;
    fh.attrs.SkipWrite                              = 0;
    fh.attrs.BufferWrites                           = 0;
    //fh.attrs.AckRawData                               = 0;
    fh.attrs.AlwaysValidate                         = 0;

    //fh.attrs.display                              = 0;
    //fh.attrs.read_back_verify                     = 0;
    fh.attrs.TestWritePerformance                   = 0;
    fh.attrs.TestReadPerformance                    = 0;
    fh.attrs.TestDigestPerformance                  = 0;
    fh.attrs.TestDDRValidity                        = 0;
    fh.attrs.SkipStorageInit                        = 0;
    fh.attrs.SkipSettingMinClocks                   = 0;
    fh.attrs.SkipSettingMaxClocks                   = 0;
    fh.attrs.actual_size_in_bytes                   = 0;

    fh.attrs.start_sector                           = 0;

    if( CopyString(fh.attrs.MemoryName, "eMMC", 0, 0, sizeof("eMMC"),sizeof(fh.attrs.MemoryName),sizeof("eMMC")) == 0)
    {
        dbg(LOG_ERROR, "Failed to copy '%s' of length %"SIZE_T_FORMAT" bytes into fh.attrs.MemoryName","eMMC",strlen("eMMC"));
        //ExitAndShowLog(1);
    }

}


boolean ddi_firehose_add_ddi_infomation(ddi_firehose_info_p modInfo, const char *key, const char type, void *val)
{
    int infoCnt = 0;
    ddi_firehose_info_p tmpDDInfo;

    if(NULL == modInfo) return FALSE;

    infoCnt = 0;
    tmpDDInfo = modInfo;
    while(0 != strlen(tmpDDInfo->info_key))
    {
        if(infoCnt >= DDI_FIREHOSE_SIZE_INFO_MAX) //protect
        {
            CopyString(tmpDDInfo->info_key, "", 0, 0, sizeof(""), sizeof(tmpDDInfo->info_key), sizeof(""));
            CopyString(tmpDDInfo->info_val, "", 0, 0, sizeof(""), sizeof(tmpDDInfo->info_val), sizeof(""));
            return FALSE;
        }
        tmpDDInfo++;
        infoCnt++;
    }

    snprintf(tmpDDInfo->info_key,
             DDI_FIREHOSE_SIZE_NAME,
             "%s",
             key);

    switch(type)
    {
        case 'u':
            snprintf(tmpDDInfo->info_val,
                     DDI_FIREHOSE_SIZE_STR_INT32,
                     "%u",
                     *(uint32*)val);
            break;
        case 'd':
            snprintf(tmpDDInfo->info_val,
                     DDI_FIREHOSE_SIZE_STR_INT32,
                     "%d",
                     *(int32*)val);
            break;
        case 's':
            snprintf(tmpDDInfo->info_val,
                     strlen((const char*)val) + 1,
                     "%s",
                     (const char*)val);
            break;
        case 'x':
            snprintf(tmpDDInfo->info_val,
                     DDI_FIREHOSE_SIZE_STR_INT32,
                     "0x%llx",
                     *(uint64*)val);
            break;
        default:
            CopyString(tmpDDInfo->info_key, "", 0, 0, sizeof(""), sizeof(tmpDDInfo->info_key), sizeof(""));
            CopyString(tmpDDInfo->info_val, "", 0, 0, sizeof(""), sizeof(tmpDDInfo->info_val), sizeof(""));
            return FALSE;
    }

    return TRUE;
}


ddi_firehose_item_p ddi_firehose_get_current_item()
{
    return current_item;
}

boolean ddi_firehose_fetch_parameters(char* str, ddi_firehose_item_p item, void *value)
{
    ddi_firehose_params_p tmpItemParams = NULL;
    uint32 tmpCvntUint = 0;
    int32 tmpCvntInt = 0;

    if (NULL == item)
    {
        ddi_firehose_print_debug("No valid item in DDI package!");
        return FALSE;
    }

    tmpItemParams = item->item_params_arr;
    if(NULL != tmpItemParams)
    {
        while(strlen(tmpItemParams->param_name) != 0)
        {
            if (strncasecmp(str, tmpItemParams->param_name, strlen((const char *)tmpItemParams->param_name)) == 0)
            {
                if(DDI_FIREHOSE_INT8 == tmpItemParams->param_type ||
                   DDI_FIREHOSE_INT16 == tmpItemParams->param_type ||
                   DDI_FIREHOSE_INT32 == tmpItemParams->param_type)
                {
                    tmpCvntInt = convertStrtoInt(tmpItemParams->param_entity);
                    if(0xDEAD == tmpCvntInt)
                    {
                        ddi_firehose_print_debug("Convert type(%s=%s) failed!", ddi_firehose_type_name[tmpItemParams->param_type], tmpItemParams->param_entity);
                        return FALSE;
                    }

                    switch(tmpItemParams->param_type)
                    {

                        case DDI_FIREHOSE_INT8:
                            *(int8 *)value = (int8)tmpCvntInt;
                            break;

                        case DDI_FIREHOSE_INT16:
                            *(int16 *)value = (int16)tmpCvntInt;
                            break;

                        case DDI_FIREHOSE_INT32:
                            *(int32 *)value = (int32)tmpCvntInt;
                            break;

                        default:
                            break;
                    }

                    return TRUE;
                }

                if(DDI_FIREHOSE_UINT8 == tmpItemParams->param_type ||
                   DDI_FIREHOSE_UINT16 == tmpItemParams->param_type ||
                   DDI_FIREHOSE_UINT32 == tmpItemParams->param_type)
                {
                    tmpCvntUint = convertStrtoUint(tmpItemParams->param_entity);
                    if(0xDEAD == tmpCvntUint)
                    {
                        ddi_firehose_print_debug("Convert type(%s=%s) failed!", ddi_firehose_type_name[tmpItemParams->param_type], tmpItemParams->param_entity);
                        return FALSE;
                    }

                    switch(tmpItemParams->param_type)
                    {
                        case DDI_FIREHOSE_UINT8:
                            *(uint8 *)value = (uint8)tmpCvntUint;
                            break;

                        case DDI_FIREHOSE_UINT16:
                            *(uint16 *)value = (uint16)tmpCvntUint;
                            break;

                        case DDI_FIREHOSE_UINT32:
                            *(uint32 *)value = (uint32)tmpCvntUint;
                            break;

                        default:
                            break;
                    }

                    return TRUE;
                }
            }

            tmpItemParams ++;
        }
    }
    ddi_firehose_print_debug("There is no related %s paramater found!", str);
    return FALSE;
}


void AppendToBuffer(byte *MyBuffer, char *buf, SIZE_T MaxBufferSize)
{
    size_t SpaceLeft, CharsToAdd = 0;
    size_t Length;

    Length       = strlen((const char *)MyBuffer);
    CharsToAdd   = strlen((const char *)buf);    // size of string to append

    //SpaceLeft = FIREHOSE_TX_BUFFER_SIZE - Length - XML_TAIL_LENGTH;      // tx_buffer is transmit_buffer of size FIREHOSE_TX_BUFFER_SIZE
    SpaceLeft = MaxBufferSize - Length - XML_TAIL_LENGTH;      // tx_buffer is transmit_buffer of size FIREHOSE_TX_BUFFER_SIZE


    if(CharsToAdd > SpaceLeft)
    {
        return;    // too big to add this
    }

    // NOTE: If you're *not* seeing your messages, increase the size of transmit_buffer[FIREHOSE_TX_BUFFER_SIZE]
    //       or break up your logging

    memscpy((MyBuffer+Length), MaxBufferSize, buf, CharsToAdd);
    MyBuffer[Length+CharsToAdd] = '\0';

} // end void AppendToBuffer(byte *MyBuffer, char *buf)

void InitBufferWithXMLHeader(byte *MyBuffer, SIZE_T Length)
{
    memset(MyBuffer, 0x0, Length);
    memscpy(MyBuffer, Length, xml_header, XML_HEADER_LENGTH);
    //MyBuffer[XML_HEADER_LENGTH] = '\0';
} // end void InitBufferWithXMLHeader(void)

char * RemoveBannedChars(char *p)
{
    char *pOrig = p;

    while(*p!='\0')
    {
        if(*p=='"' || *p=='<' || *p=='>')
            *p = '_';
        p++;
    }
    return pOrig;
}


boolean cmdIsCompatible(ddi_firehose_item_p item)
{
    int ddr_type_mask = DDR_TYPE_MASK(getDDRType());
    int item_ddr_compatibility = item->ddrTypeCompatibility;
    return ddr_type_mask & item_ddr_compatibility;
}

boolean check_especial_cmd_attribute(void)
{
    if((strncasecmp("nop", NewTagName,strlen((const char *)NewTagName))) == 0  ||
       (strncasecmp("ddinfo", NewTagName,strlen((const char *)NewTagName))) == 0 ||
       (strncasecmp("Reset", NewTagName,strlen((const char *)NewTagName))) == 0)
    {
        return TRUE;
    }

    return FALSE;
}

boolean check_normal_cmd_attribute(void)
{
    if (NULL != current_item)
    {
        if(strlen(current_item->item_name) != 0)
        {
            if (strncasecmp(current_item->item_name, NewTagName,strlen((const char *)NewTagName)) == 0)
            {
                if (current_item->item_params_arr == NULL)
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
    }

    return FALSE;
}


boolean parse_item_params(void)
{
    uint32 tmpCvntUint = 0;
    int32 tmpCvntInt = 0;
    ddi_firehose_params_p tmpItemParams = NULL;

    tmpItemParams = current_item_params;
    if(NULL == tmpItemParams)
        return FALSE;

    while(0 != strlen(tmpItemParams->param_name))
    {
        if(DDI_FIREHOSE_UINT8 == tmpItemParams->param_type ||
           DDI_FIREHOSE_UINT16 == tmpItemParams->param_type ||
           DDI_FIREHOSE_UINT32 == tmpItemParams->param_type)
        {

            tmpCvntUint = convertStrtoUint((char *)tmpItemParams->param_entity);
            if(0xDEAD == tmpCvntUint) // convert not OK
            {
                ddi_firehose_print_debug("Convert type(%s=%s) failed!",
                                         ddi_firehose_type_name[tmpItemParams->param_type],
                                         tmpItemParams->param_entity
                                        );
                return FALSE;
            }

            if(tmpCvntUint < tmpItemParams->param_min || tmpCvntUint > tmpItemParams->param_max)
            {
                ddi_firehose_print_debug("<%s> out of range(%d~%d)",
                                         tmpItemParams->param_name,
                                         tmpItemParams->param_min,
                                         tmpItemParams->param_max
                                        );
                return FALSE;
            }

        }
        else if(DDI_FIREHOSE_INT8 == tmpItemParams->param_type ||
                DDI_FIREHOSE_INT16 == tmpItemParams->param_type ||
                DDI_FIREHOSE_INT32 == tmpItemParams->param_type)
        {
            //check int
            tmpCvntInt = convertStrtoInt((char *)tmpItemParams->param_entity);
            if(0xDEAD == tmpCvntInt)
            {
                ddi_firehose_print_debug("Convert type(%s=%s) failed!",
                                         ddi_firehose_type_name[tmpItemParams->param_type],
                                         tmpItemParams->param_entity
                                        );
                return FALSE;
            }

            if(tmpCvntInt < (int)tmpItemParams->param_min || tmpCvntInt > (int)tmpItemParams->param_max)
            {
                ddi_firehose_print_debug("<%s> out of range(%d~%d)",
                                         tmpItemParams->param_name,
                                         (int)tmpItemParams->param_min,
                                         (int)tmpItemParams->param_max
                                        );
                return FALSE;
            }

        }
        else if(DDI_FIREHOSE_STRING == tmpItemParams->param_type)
        {

        }
        else if(DDI_FIREHOSE_BOOLEAN == tmpItemParams->param_type)
        {

        }
        else if(DDI_FIREHOSE_ARRAY_UINT32 == tmpItemParams->param_type)
        {

        }
        else
        {
            ddi_firehose_print_debug("Type(%d) not supported!", tmpItemParams->param_type);
            return FALSE;
        }

        tmpItemParams ++;
    }

    return TRUE;
}


void ddi_firehose_update_item_set(ddi_firehose_item_set_p ddiItemSet)
{
    if(NULL != ddiItemSet) ddi_firehose_package = ddiItemSet;
}

boolean main_firehose(void)
{
    volatile SIZE_T  PacketLoc = 0;// BreakPoint = 0;
    ddi_firehose_item_p tmpItems;

    hotplug_init_no_poll();
    deviceprogrammer_zi_buffers ();
    initFirehoseProtocol(); // initializes default values for fh structure
    InitAttributes();

    if(NULL == ddi_firehose_package)
    {
        ddi_firehose_print_log("Not found DDI command/item package defination!");
        return FALSE;
    }

    tmpItems = ddi_firehose_package->item_arr;

    if(NULL == tmpItems)
    {
        ddi_firehose_print_debug("No valid item in DDI package!");
        return FALSE;
    }

    if(NULL != ddi_firehose_package->worker_exec_pre)
    {
        if(TRUE != (*ddi_firehose_package->worker_exec_pre)((void *)ddi_firehose_package))
        {
            ddi_firehose_print_log("Failed to run DDI prework!");
            return FALSE;
        }
    }

    while(0 != strlen(tmpItems->item_name))
    {
        if(NULL != tmpItems->item_exec_init)
        {
            if(FALSE == (*tmpItems->item_exec_init)((void *)tmpItems))
            {
                ddi_firehose_print_log("Init item(%s) failed!", tmpItems->item_name);
                return FALSE;
            }
        }
        tmpItems++;
    }

    ddi_firehose_print_debug("Start DDI using firehose");

    for (;;)
    {
        PacketLoc = 0;

        // Get XML packet over USB and initialize XML reader.
        if (getXMLPacket() != FIREHOSE_SUCCESS)
        {
            // on any errors send NAK and get next packet, getXMLPacket() would have sent the error
            sendResponse(NAK);
            continue;
        }

        // To be this far fh.xml_buffer has the data
        PacketLoc = DetermineTag((char *)fh.xml_buffer, PacketLoc, FIREHOSE_XML_BUFFER_SIZE);       // This sets CurrentHandlerFunction()

        // PacketLoc should be past the xml and data tags, pointing at the 1st attribute
        // So if PacketLoc is still it 0, something went wrong
        if(PacketLoc==0)
        {
            sendResponse(NAK);
            continue;
        }

        // Singh TO DO: determine Attributes should not be executed for operations like ddiinfo and nop
        if (FALSE == check_especial_cmd_attribute())
        {
            if (FALSE == check_normal_cmd_attribute())
            {

                // To be this far fh.xml_buffer[PacketLoc] is pointing to the first char of the first attribute
                PacketLoc = DetermineAttributes((char *)fh.xml_buffer, PacketLoc, FIREHOSE_XML_BUFFER_SIZE);

                // PacketLoc should now be past all attributes and pointing at the />
                // So if PacketLoc is still it 0, something went wrong
                if(PacketLoc==0)
                {
                    sendResponse(NAK);
                    continue;
                }
                //Check the input parameters
                if (FALSE == parse_item_params())
                    continue;
            }

            if(NULL != current_item->item_exec_pretest)
            {
                if(FALSE == (*current_item->item_exec_pretest)((void *)current_item))
                {
                    ddi_firehose_print_debug("Run pre-test failed!");
                    continue;
                }
            }

            if(NULL != current_item->item_exec_dotest)
            {
                if(FALSE == (*current_item->item_exec_dotest)((void *)current_item))
                {
                    ddi_firehose_print_debug("Run testing failed!");
                    continue;
                }
            }

            if(NULL != current_item->item_exec_postest)
            {
                if(FALSE == (*current_item->item_exec_postest)((void *)current_item))
                {
                    ddi_firehose_print_debug("Run post-test failed!");
                    continue;
                }
            }

        }
        else   //handle the especial cmd
        {
            CurrentHandlerFunction();
        }

        if(TRUE == quitDDI)
            break;
    }

    if(NULL != ddi_firehose_package->worker_exec_post)
    {
        if(TRUE  != (*ddi_firehose_package->worker_exec_post)((void *)ddi_firehose_package))
        {
            ddi_firehose_print_log("Failed to run DDI postwork!");
            return FALSE;
        }
    }

    return TRUE;

}
