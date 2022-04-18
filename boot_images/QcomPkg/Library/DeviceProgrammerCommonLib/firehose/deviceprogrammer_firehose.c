/*==================================================================
 *
 * FILE:        deviceprogrammer_firehose.c
 *
 * DESCRIPTION:
 *
 *
 *        Copyright (c) 2008-2018 Qualcomm Technologies Incorporated.
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
 * 2018-02-09   svl     corrected boundary check
 * 2018-02-01   svl     fix BL CR 2121212
 * 2017-07-08   svl     parse NUM_DISK_SECTORS when erasing data chunks.
 * 2017-02-28   sb      Align buffers to 64byte for crypto BAM.
 * 2016-03-08   wek     Fix bug when attribute is empty string.
 * 2016-02-10   wek     Add option to format whole dev or erase a portion.
 * 2015-11-10   wek     Add slot argument to storage APIs, but no effect.
 * 2015-11-09   wek     Remove structure coupling between fh and storage.
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
#include "deviceprogrammer_firehose.h"

#include "usb_wrapper.h"
#include "boot_sahara.h"
#include "ClockBoot.h"

//#include "CeTL_sha2_sw.h"
//void InitTXBufferWithXMLHeader(void);
void InitBufferWithXMLHeader(byte *MyBuffer, SIZE_T Length);
void CloseTXBuffer(void);
//void AppendToTXBuffer(char *buf);
void AppendToBuffer(byte *MyBuffer, char *buf, SIZE_T MaxBufferSize);
//char * CleanStringForPC(char *p, SIZE_T  Length);
char * RemoveBannedChars(char *p);

#define MAX_TAG_NAME_LENGTH 30
#define MAX_TAG_ATTR_LENGTH 80

char NewTagName[MAX_TAG_NAME_LENGTH+1];
char CurrentTagName[MAX_TAG_NAME_LENGTH+1];
char ParseAttributes = 1; // this changes from 0 to 1 during the program


typedef enum response_t {
    NAK,
    ACK
} response_t;



// These buffers are being allocated separately so as to make them easy to relocate
// because these are currently accessed directly by the hardware

/* Buffers that are allocated in DDR */
byte ddr_main_channel_buffer_A[FIREHOSE_DDR_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.DDR_CHANNEL_BUFFER_A_SECTION"))) __attribute__((__aligned__(64))) = {0};
byte ddr_main_channel_buffer_B[FIREHOSE_DDR_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.DDR_CHANNEL_BUFFER_B_SECTION"))) __attribute__((__aligned__(64))) = {0};

/* Buffers that are allocated in On chip memory. */
byte lite_main_channel_buffer_A[FIREHOSE_LITE_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.LITE_CHANNEL_BUFFER_A_SECTION"))) __attribute__((__aligned__(16))) = {0};
byte lite_main_channel_buffer_B[FIREHOSE_LITE_CHANNEL_BUFFER_SIZE]  __attribute__ ((section (".bss.LITE_CHANNEL_BUFFER_B_SECTION"))) __attribute__((__aligned__(16)))= {0};


byte transmit_buffer[FIREHOSE_TX_BUFFER_SIZE]  __attribute__ ((section (".bss.TRANSMIT_BUFFER_SECTION"))) = {0};
byte* packet;


char temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE];

static byte storage_raw_data_buff[STORAGE_DEVICE_INFO_BUFFER_SIZE];

//firehose_protocol_t fh;	// this can be a big structure
firehose_protocol_t fh __attribute__ ((section (".bss.FIREHOSE_PROTOCOL_STRUCT")));

#ifdef FEATURE_DEVICEPROGRAMMER_DDR
/* Uncomment the following line to enable Firware Update. */
//#define USE_FIRMWARE_BUFFER
#endif

#ifdef USE_FIRMWARE_BUFFER
#define BIG_FW_BUFFER_SIZE (1024*1024)
byte BigFWBuffer[BIG_FW_BUFFER_SIZE] __attribute__ ((section (".bss.DDR_CHANNEL_BUFFER_A_SECTION"))) = {0};
SIZE_T BigFWBufferCount = 0, BigFWBufferExpected = 0;
#endif


SIZE_T ConfigureCommandNotReceivedYet = 1;  // allow VERBOSE until user turns it off

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

#define MAX_ATTR_NAME_SIZE 32
#define MAX_ATTR_RAW_SIZE 64

struct Attributes_Struct
{
        char    Name[MAX_ATTR_NAME_SIZE];				// i.e. "MaxPayloadSizeToTargetInBytes"
        char    Raw[MAX_ATTR_RAW_SIZE];   // i.e. "8192" 
        void   *pValue;
        SIZE_T  Min;
        SIZE_T  Max;
        SIZE_T  MultipleOf;
	SIZE_T  SizeOfpStr;
        char    *pStr;
        char    Type;           // i.e. "i" for integer, "s" for string, "x" for special, "t" for SIZE_T
        char    Assigned;       // i.e. Flag indicating if it was just assigned
};


// Declare the variables we care about
storage_device_extras_t storage_extras;

struct UFS_LUN_Var
{
    SIZE_T LUNum;
    SIZE_T bLUEnable;
    SIZE_T bBootLunID;
    SIZE_T bLUWriteProtect;
    SIZE_T bMemoryType;
    SIZE_T size_in_KB;
    SIZE_T bDataReliability;
    SIZE_T bLogicalBlockSize;
    SIZE_T bProvisioningType;
    SIZE_T wContextCapabilities;
};

struct UFS_LUN_Var UFS_LUN_Var_Struct;


static struct Attributes_Struct AllAttributes[] = {
        {"Verbose",                             "", (SIZE_T *)&fh.attrs.Verbose,                       0,0,1,0, NULL, 'i', 0 },
        {"MaxPayloadSizeToTargetInBytes",       "", (SIZE_T *)&fh.attrs.MaxPayloadSizeToTargetInBytes, 0,0,512,0, NULL, 'i', 0 },
        {"MaxDigestTableSizeInBytes",           "", (SIZE_T *)&fh.attrs.MaxDigestTableSizeInBytes,     0,0,512,0, NULL, 'i', 0 },
        {"AckRawDataEveryNumPackets",           "", (SIZE_T *)&fh.attrs.AckRawDataEveryNumPackets,     0,0,1,0, NULL, 'i', 0 },
        {"delayinseconds",                      "", (SIZE_T *)&fh.attrs.delayinseconds,                0,0,1,0, NULL, 'i', 0 },
        {"address64",                           "", (SIZE_T *)&fh.attrs.address64,                     0,0,1,0, NULL, 'i', 0 },
        {"value64",                             "", (SIZE_T *)&fh.attrs.value64,                       0,0,1,0, NULL, 'i', 0 },
        //{"storagedrive",                        "", (SIZE_T *)&fh.attrs.storagedrive,                  0,0,1,0, NULL, 'i', 0 },
        {"storagedrive",                        "", (SIZE_T *)&fh.attrs.physical_partition_number,     0,0,1,0, NULL, 'i', 0 },
        {"SECTOR_SIZE_IN_BYTES",                "", (SIZE_T *)&fh.attrs.SECTOR_SIZE_IN_BYTES,          0,0,512,0, NULL, 'i', 0 },
        {"byte_offset",                         "", (SIZE_T *)&fh.attrs.byte_offset,                   0,0,1,0, NULL, 'i', 0 },
        {"physical_partition_number",           "", (SIZE_T *)&fh.attrs.physical_partition_number,     0,0,1,0, NULL, 'i', 0 },
        {"size_in_bytes",                       "", (SIZE_T *)&fh.attrs.size_in_bytes,                 0,0,1,0, NULL, 'i', 0 },
        {"trials",                              "", (SIZE_T *)&fh.attrs.trials,                        0,0,1,0, NULL, 'i', 0 },
        {"file_sector_offset",                  "", (SIZE_T *)&fh.attrs.file_sector_offset,            0,0,1,0, NULL, 'i', 0 },   // 13

        {"ZlpAwareHost",                        "", (SIZE_T *)&fh.attrs.ZlpAwareHost,                  0,0,1,0, NULL, 'i', 0 },
        {"SkipWrite",                           "", (SIZE_T *)&fh.attrs.SkipWrite,                     0,0,1,0, NULL, 'i', 0 },
        {"BufferWrites",                        "", (SIZE_T *)&fh.attrs.BufferWrites,                     0,0,1,0, NULL, 'i', 0 },
        //{"AckRawData",                          "", (SIZE_T *)&fh.attrs.AckRawData,                    0,0,1,0, NULL, 'i', 0 },
        {"AlwaysValidate",                      "", (SIZE_T *)&fh.attrs.AlwaysValidate,                0,0,1,0, NULL, 'i', 0 },
        {"commit",                              "", NULL,                                       0,0,1,sizeof(fh.attrs.Commit), (char *)fh.attrs.Commit, 'x', 0 }, // string convert to fh.attrs.commit
        //{"display",                             "", (SIZE_T *)&fh.attrs.display,                       0,0,1,0, NULL, 'i', 0 },
        //{"read_back_verify",                    "", (SIZE_T *)&fh.attrs.read_back_verify,              0,0,1,0, NULL, 'i', 0 },
        {"TestWritePerformance",                "", (SIZE_T *)&fh.attrs.TestWritePerformance,          0,0,1,0, NULL, 'i', 0 },
        {"TestReadPerformance",                 "", (SIZE_T *)&fh.attrs.TestReadPerformance,           0,0,1,0, NULL, 'i', 0 },
        {"TestDigestPerformance",               "", (SIZE_T *)&fh.attrs.TestDigestPerformance,         0,0,1,0, NULL, 'i', 0 },   // 20
        {"TestDDRValidity",                     "", (SIZE_T *)&fh.attrs.TestDDRValidity,          0,0,1,0, NULL, 'i', 0 },
        {"SkipStorageInit",                     "", (SIZE_T *)&fh.attrs.SkipStorageInit,               0,0,1,0, NULL, 'i', 0 },	// <configure SkipStorageInit="1"
        {"SkipSettingMinClocks",                "", (SIZE_T *)&fh.attrs.SkipSettingMinClocks,          0,0,1,0, NULL, 'i', 0 },	// <configure SkipSettingMinClocks="1"
        {"SkipSettingMaxClocks",                "", (SIZE_T *)&fh.attrs.SkipSettingMaxClocks,          0,0,1,0, NULL, 'i', 0 },	// <configure SkipSettingMaxClocks="1"
        {"actual_size_in_bytes",                "", (SIZE_T *)&fh.attrs.actual_size_in_bytes,          0,0,1,0, NULL, 'i', 0 },	// <configure actual_size_in_bytes="1234"


        // eMMC GPP creation
        {"DRIVE4_SIZE_IN_KB",                   "", (SIZE_T *)&storage_extras.emmc_extras.GPP_size[0], 	0,0,512,0, NULL, 'w', 0 },    // 24
        {"DRIVE5_SIZE_IN_KB",                   "", (SIZE_T *)&storage_extras.emmc_extras.GPP_size[1], 	0,0,512,0, NULL, 'w', 0 },
        {"DRIVE6_SIZE_IN_KB",                   "", (SIZE_T *)&storage_extras.emmc_extras.GPP_size[2], 	0,0,512,0, NULL, 'w', 0 },
        {"DRIVE7_SIZE_IN_KB",                   "", (SIZE_T *)&storage_extras.emmc_extras.GPP_size[3], 	0,0,512,0, NULL, 'w', 0 },
        {"ENH_SIZE",                            "", (SIZE_T *)&storage_extras.emmc_extras.ENH_size,    	0,0,1,0,   NULL, 'w', 0 },
        {"ENH_START_ADDR",                      "", (SIZE_T *)&storage_extras.emmc_extras.ENH_start_addr, 0,0,1,0,   NULL, 'w', 0 },
        {"GPP_ENH_FLAG",                        "", (SIZE_T *)&storage_extras.emmc_extras.GPP_enh_flag, 	0,0,1,0,   NULL, 'b', 0 },    // 30

        // UFS LUN creation
        {"bNumberLU",                   		"", (byte *)&storage_extras.ufs_extras.bNumberLU, 	    0,0,1,0,   NULL, 'b', 0 },
        {"bBootEnable",                   		"", (byte *)&storage_extras.ufs_extras.bBootEnable,	    0,0,1,0,   NULL, 'b', 0 },
        {"bDescrAccessEn",                 		"", (byte *)&storage_extras.ufs_extras.bDescrAccessEn,  0,0,1,0,   NULL, 'b', 0 },
        {"bInitPowerMode",                 		"", (byte *)&storage_extras.ufs_extras.bInitPowerMode,  0,0,1,0,   NULL, 'b', 0 },
        {"bHighPriorityLUN",               		"", (byte *)&storage_extras.ufs_extras.bHighPriorityLUN,	0,0,1,0,   NULL, 'b', 0 },
        {"bSecureRemovalType",             		"", (byte *)&storage_extras.ufs_extras.bSecureRemovalType, 	0,0,1,0,   NULL, 'b', 0 },
        {"bInitActiveICCLevel",            		"", (byte *)&storage_extras.ufs_extras.bInitActiveICCLevel, 0,0,1,0,   NULL, 'b', 0 },
        {"wPeriodicRTCUpdate",            		"", (short *)&storage_extras.ufs_extras.wPeriodicRTCUpdate, 	0,0,1,0,   NULL, 'n', 0 },
        {"bConfigDescrLock",            		"", (byte *)&storage_extras.ufs_extras.bConfigDescrLock, 	0,0,1,0,   NULL, 'b', 0 },
        {"qVendorConfigCode",            		"", (SIZE_T *)&storage_extras.ufs_extras.qVendorConfigCode, 	0,0,1,0,   NULL, 'w', 0 },
        {"LUNtoGrow",                                   "", (byte *)&storage_extras.lun_to_grow,                     0,0,1,0, NULL, 'i', 0 },

        // These vars are handled in ParseComplicatedAttributes when (CurrentHandlerFunction==handleStorageExtras)
        {"LUNum",            					"", (byte *)&UFS_LUN_Var_Struct.LUNum, 					0,7,1,0,   NULL, 'i', 0 },
        {"bLUEnable",            				"", (byte *)&UFS_LUN_Var_Struct.bLUEnable, 				0,0,1,0,   NULL, 'b', 0 },
        {"bBootLunID",            				"", (byte *)&UFS_LUN_Var_Struct.bBootLunID, 			0,0,1,0,   NULL, 'b', 0 },
        {"bLUWriteProtect",            			"", (byte *)&UFS_LUN_Var_Struct.bLUWriteProtect, 		0,0,1,0,   NULL, 'b', 0 },
        {"bMemoryType",            				"", (byte *)&UFS_LUN_Var_Struct.bMemoryType, 			0,0,1,0,   NULL, 'b', 0 },
        {"size_in_KB",            				"", (SIZE_T *)&UFS_LUN_Var_Struct.size_in_KB, 			0,0,1,0,   NULL, 'i', 0 },
        {"bDataReliability",           			"", (byte *)&UFS_LUN_Var_Struct.bDataReliability, 		0,0,1,0,   NULL, 'b', 0 },
        {"bLogicalBlockSize",            		"", (byte *)&UFS_LUN_Var_Struct.bLogicalBlockSize, 		0,0,1,0,   NULL, 'b', 0 },
        {"bProvisioningType",            		"", (byte *)&UFS_LUN_Var_Struct.bProvisioningType, 		0,0,1,0,   NULL, 'b', 0 },
        {"wContextCapabilities",            	"", (short *)&UFS_LUN_Var_Struct.wContextCapabilities, 	0,0,1,0,   NULL, 'n', 0 },

        {"MemoryName",                          "", NULL,                                       0,0,1,sizeof(fh.attrs.MemoryName), (char *)fh.attrs.MemoryName, 's', 0 },
        {"TargetName",                          "", NULL,                                       0,0,1,sizeof(fh.attrs.TargetName), (char *)fh.attrs.TargetName, 's', 0 },
        {"filename",                            "", NULL,                                       0,0,1,sizeof(fh.attrs.filename), (char *)fh.attrs.filename,   's', 0 },
        {"value",                               "", NULL,                                       0,0,1,sizeof(fh.attrs.value), (char *)fh.attrs.value,      's', 0 },   // 53

        // x means it needs special processing later, as in start_sector="NUM_DISK_SECTORS-33."
        {"start_sector",                        "", (SIZE_T *)&fh.attrs.start_sector,                  0,0,1,0, NULL, 'x', 0 },   // 54
        {"num_partition_sectors",               "", (SIZE_T *)&fh.attrs.num_partition_sectors,         0,0,1,0, NULL, 'x', 0 },
};




//#define XML_HEADER_LENGTH 47  // 47 does NOT include null
#define XML_HEADER_LENGTH 40    // 40 does NOT include null
#define XML_TAIL_LENGTH 9               // 9 DOES include null

static const char xml_header[XML_HEADER_LENGTH] = "<\?xml version=\"1.0\" encoding=\"UTF-8\" \?>\n";

extern uint32 Image$$SBL1_DEVICEPROGRAMMER_USB_ZI$$Base[];
extern uint32 Image$$SBL1_DEVICEPROGRAMMER_USB_ZI$$ZI$$Length;

extern uint32 Image$$SBL1_DEVICEPROG_FH_ZI$$Base[];
extern uint32 Image$$SBL1_DEVICEPROG_FH_ZI$$ZI$$Length;

/* Temporary bringup function to clear the USB Buffers. */
void deviceprogrammer_zi_buffers (void) {

  memset (&fh, 0, sizeof(fh));
  memset (&storage_extras, 0, sizeof(storage_extras));

#ifdef FEATURE_DEVICEPROGRAMMER_DDR
//  memset (ddr_main_channel_buffer_A, 0, sizeof(ddr_main_channel_buffer_A));
//  memset (ddr_main_channel_buffer_B, 0, sizeof(ddr_main_channel_buffer_B));
  memset (Image$$SBL1_DEVICEPROGRAMMER_USB_ZI$$Base, 0, (size_t)&Image$$SBL1_DEVICEPROGRAMMER_USB_ZI$$ZI$$Length);
#endif

//  memset (lite_main_channel_buffer_A, 0, sizeof(lite_main_channel_buffer_A));
//  memset (lite_main_channel_buffer_B, 0, sizeof(lite_main_channel_buffer_B));
  
  memset (Image$$SBL1_DEVICEPROG_FH_ZI$$Base, 0, (size_t)&Image$$SBL1_DEVICEPROG_FH_ZI$$ZI$$Length);
}

static void firehoseResetValidationVariables() {
    fh.num_packets_received = 0;

    fh.validation_hash_buffer_num_hashes = 0;
    fh.validation_hash_buffer_capacity = sizeof(fh.validation_hash_buffer) /
                        sizeof(fh.validation_hash_value);
    fh.validation_hash_buffer_new_capacity = fh.validation_hash_buffer_capacity;

    fh.validation_hash_buffer_index = 0;
    fh.validation_table_count = 0;
    fh.validation_signed_hash_received = FALSE;
}

int memset_verify (byte *buffer, byte val, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (buffer[i] != val)
      return -1;
  }
  return 0;
}

int ddr_set_and_test (byte val)
{
  byte *channelA;
  byte *channelB;
  uint32 channel_size;
  int result;

  channelA = ddr_main_channel_buffer_A;
  channelB = ddr_main_channel_buffer_B;
  /* It takes a long time to memset the whole buffers, do just half to save time. */
  channel_size = FIREHOSE_DDR_CHANNEL_BUFFER_SIZE / 2;

  memset (channelA, val, channel_size);
  memset (channelB, val, channel_size);

  result = memset_verify (channelA, val, channel_size);
  if (result != 0)
    return -1;
  result = memset_verify (channelB, val, channel_size);
  if (result != 0)
    return -1;

  return 0;
}

int ddr_fill_and_check_test (void)
{
  byte *channelA;
  byte *channelB;
  uint32 channel_size;
  int i;
  byte val;

  // Rename the variables for easy typing.
  channelA = ddr_main_channel_buffer_A;
  channelB = ddr_main_channel_buffer_B;
  /* It takes a long time to memset the whole buffers, do just half to save time. */
  channel_size = FIREHOSE_DDR_CHANNEL_BUFFER_SIZE / 2;

  val = 0;
  // Fill the buffers with some pattern.
  for (i = 0; i < channel_size; i++)
  {
    channelA[i] = val;
    channelB[i] = val;
    val++;
    // Make the counter wrap around at an odd value. This causes that same
    // value won't fall in the same "column" in memory. If we use a multiple
    // of 2, then the same value will fall in the same colum every time.
    if (val >= 253)
      val = 0;
  }
  val = 0;
  // Verify the pattern that we just filled.
  for (i = 0; i < channel_size; i++)
  {
    /* The buffers should be filled with an specific pattern. Verify that pattern. */
    if (channelA[i] != val || channelB[i] != val)
      return -1;

    val++;
    if (val >= 253)
      val = 0;
  }

  return 0;
}


/* This feature will run some tests on DDR. If the test fail it will fall back
 * and use the Lite buffers and return a NAK for any command sent. */
#ifdef FEATURE_DEVICEPROGRAMMER_INIT_DDR_TEST
static int basic_test_ddr(void)
{
  int result;

  /* Set DDR to some values and read back the pattern to make sure it is there. */
  result = ddr_set_and_test (0x55);
  if (result != 0)
    return -1;
  result = ddr_set_and_test (0xAA);
  if (result != 0)
    return -1;

  /* Fill the buffers with a non repetitive pattern and verify it */
  result = ddr_fill_and_check_test ();
  if (result != 0)
    return -1;

  /* Last do the test filling the memory to zero, esentially initializing it. */
  result = ddr_set_and_test (0x00);
  if (result != 0)
    return -1;

  return 0;
}
#else
static int basic_test_ddr(void)
{
  return 0;
}
#endif


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

  /* If the DDR Buffers are defined, verify DDR is good.*/
  if (FIREHOSE_LITE_CHANNEL_BUFFER_SIZE <= FIREHOSE_DDR_CHANNEL_BUFFER_SIZE)
  {
    int result;
    result = basic_test_ddr ();
    if (result == 0)
    {
      // DDR Is good. Use the DDR Buffers instead.
      channelA = ddr_main_channel_buffer_A;
      channelB = ddr_main_channel_buffer_B;
      channel_size = FIREHOSE_DDR_CHANNEL_BUFFER_SIZE;
    }
    else
    {
      fh.nak_all_packets = 1;
    }
  }

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
    fh.store_dev = storage_device_init_struct();

    //fh.skip_storage_writes = FALSE;
    //fh.hash_in_non_secure = FALSE;
    //fh.verbose = FALSE;
    //fh.ack_raw_data_every = 0;

    firehoseResetValidationVariables();
}

void debugMessage(const char* format, ...) {
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

static void packet_handle_incoming_buf (uint32 bytes_read, uint32 err_code) {
    debugMessage("cback bytes_read=%u err_code=%u", bytes_read, err_code);
    fh.channel_error_code = err_code;
    if (err_code != BULK_SUCCESS) {
        fh.channel_bytes_read = 0;
        //fh.channel_num_errors += 1;
        //usb_al_bulk_cancel_rx();
    }
    else {
        fh.channel_bytes_read = bytes_read;
        fh.num_packets_received += 1;
    }
    //fh.channel_total_bytes_read += bytes_read;
    fh.channel_read_completed = TRUE;
    return;
}

static firehose_error_t readChannel(byte** packet_ptr, SIZE_T bytes_to_read, SIZE_T *bytes_read, boolean queue_only) {
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

        usb_al_bulk_receive(fh.channel_buffer[fh.channel_buffer_to_use], bytes_to_read, packet_handle_incoming_buf, &fh.channel_error_code);

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

static void packet_handle_outgoing_buf(uint32 bytes_written, uint32 err_code) {
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
      // We should not call log message inside the write channel,
      // because writeChannel will call writeChannel causing a possible
      // infinite recursion.
//        logMessage("USB write failed - usb_al_bulk_transmit() gave channel error code %u",fh.channel_error_code);
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

#define dbg(log_level, fmt ...) logMessage(fmt)

void logMessage(const char* format, ...) {
    char temp_log_buffer[FIREHOSE_TEMP_LOG_BUFFER_SIZE] = {0};  // no single message > 512 bytes
    SIZE_T buffer_space = sizeof(temp_log_buffer);

    va_list args;
    va_start (args, format);

    vsnprintf(temp_log_buffer,
              buffer_space,
              format,
              args);
    va_end (args);

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

    for(i=0;i<FH_ERR_MAX;i++)
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

static firehose_error_t sendResponse(response_t response)
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


    //return sendResponseFields(response, 0);
}


static void logDigest(char* prefix, byte* digest, SIZE_T length) {
    int i = 0;
    int written;
    char log_string[FIREHOSE_TEMP_BUFFER_SIZE] = { 0 };

    if (sizeof(log_string) < ((length * 2) + strlen(prefix) + 1)) {
        return;
    }

    written = snprintf(log_string,
                       sizeof(log_string),
                       "%s",
                       prefix);
    while (written < sizeof(log_string) && i < length) {
        written += snprintf(log_string + written,
                            sizeof(log_string) - written,
                            "%02X",
                            digest[i]);
        i++;
    }

    logMessage(log_string);
}


static void firehoseResetValidation() {
    firehoseResetValidationVariables();
    logMessage("Reset validation state. Expecting Digital signature");
}


static firehose_error_t recvNextPacket(byte** packet_ptr, SIZE_T bytes_to_read,SIZE_T *bytes_read, boolean queue_only)
{
    boolean packet_validated = FALSE;
    byte* hash_location;
    SIZE_T signed_payload_size;
    SIZE_T len_copied;
    firehose_error_t read_retval = FIREHOSE_SUCCESS;



    if(fh.validation_enabled == TRUE)
    {

        // This code section handles Validated programming
        // if a failure occurs call the function to reset
        // all validation related variables to their initial
        // states

            while(packet_validated == FALSE)
            {
               if (fh.validation_signed_hash_received == FALSE)
               {
                  // To be here means we are recieving the FIRST SIGNED HASH TABLE
                  // It will be in channel A, i.e. fh.channel_buffer[0], or fh.channel_buffer[ fh.channel_buffer_to_use ]

                  logMessage("VIP - Validated Image Programming is enabled - Validation is enabled.");

                  
                  // Signed Digest Table will be in main_channel_buffer_A
                  debugMessage("VIP - FIREHOSE_SIGNED_HASH_PACKET_SIZE=%lld", FIREHOSE_SIGNED_HASH_PACKET_SIZE);
                  debugMessage("VIP - queue_only=%i", queue_only);
                  read_retval = readChannel(packet_ptr, FIREHOSE_SIGNED_HASH_PACKET_SIZE, bytes_read, queue_only);
                  if (read_retval != FIREHOSE_SUCCESS)
                  {
                    firehoseResetValidation();
                    return read_retval;
                  }
				  debugMessage("VIP - bytes_read=%lld", *bytes_read);

                  if (queue_only == TRUE)
                    return FIREHOSE_SUCCESS;

                // Verify the data in the receive buffer, then copy the data
                // into validation_hash_buffer
                if (authenticateSignedHash(*packet_ptr, *bytes_read, &hash_location, &signed_payload_size) == FALSE)
                {
                    logMessage("Failed to authenticate Digital Signature, resetting validation state");
                    MyErrorMessage(DIGITAL_SIGNATURE_DID_NOT_PASS);
                    sendResponse(NAK);

                    firehoseResetValidation();
                    return FIREHOSE_VALIDATION_ERROR;
                }

                  // To be this far means the SIGNED DIGEST TABLE passed
                  fh.validation_signed_hash_received = TRUE;

                  // Resetting num_pacets to 0, we don't count the first signed digest table
                  fh.num_packets_received = 0;

                  fh.validation_hash_buffer_num_hashes = signed_payload_size / sizeof(fh.validation_hash_value);  // if this is > 54, can't be true assert(validation_hash_buffer_num_hashes>54)

				  debugMessage("VIP - num_hashes=%lld", fh.validation_hash_buffer_num_hashes);
				  
                  if (fh.validation_hash_buffer_num_hashes>54)
                  {
                      logMessage("It appears your First Hash Table has more than 54 hashes, which should be impossible.");
					  logMessage("signed_payload_size = %ld",signed_payload_size);
					  logMessage("sizeof(fh.validation_hash_value) = %i",sizeof(fh.validation_hash_value));
                      logMessage("Your first hash table has %d hashes. Is it DIGITALLY SIGNED??",fh.validation_hash_buffer_num_hashes);
                      sendResponse(NAK);
                      firehoseResetValidation();
                      return FIREHOSE_VALIDATION_ERROR;
                  }
				  
				  logMessage("VIP - validation_hash_buffer_num_hashes=%lld", fh.validation_hash_buffer_num_hashes);
				  logMessage("VIP - validation_hash_buffer_capacity=%lld", fh.validation_hash_buffer_capacity);

                  // Ex. Our hash_buffer can hold 256 hashes. Therefore assuming we got 54 hashes in the first signed table,
                  // we want to load them as the LAST 54 hashes in our table, meaning starting at location 202
                  memscpy( &fh.validation_hash_buffer[fh.validation_hash_buffer_capacity - fh.validation_hash_buffer_num_hashes],
                           sizeof(fh.validation_hash_buffer),
                           hash_location,
                           signed_payload_size);

                  fh.validation_hash_buffer_index = fh.validation_hash_buffer_capacity - fh.validation_hash_buffer_num_hashes;
                  sendResponse(ACK);  // set breakpoint here to inspect validation_hash_buffer
                  continue;
           }
           else
           {
				//fh.validation_signed_hash_received == TRUE here, meaning we have the Signed Table
				// to be here means we have a packet
               //if (fh.validation_hash_buffer_index == fh.validation_hash_buffer_capacity - 1 && fh.validation_hash_buffer_num_hashes == fh.validation_hash_buffer_capacity)
			   if (fh.validation_hash_buffer_index == fh.validation_hash_buffer_capacity - 1)
               {
				   // expecting a new digest table here
				   //debugMessage("hash_buffer_index==hash_buffer_capacity-1");
				   //debugMessage("validation_hash_buffer_num_hashes=%lld",fh.validation_hash_buffer_num_hashes);
				   //debugMessage("validation_hash_buffer_capacity=%lld",fh.validation_hash_buffer_capacity);
                   read_retval = readChannel(packet_ptr, fh.validation_hash_buffer_new_capacity * sizeof(fh.validation_hash_value), bytes_read, queue_only);
               }
               else
               {
                    // This is the *real* XML read now. Since above we discovered we had to read the digest table
					debugMessage("real XML");
                    read_retval = readChannel(packet_ptr, bytes_to_read, bytes_read, queue_only);
               }

               if (read_retval != FIREHOSE_SUCCESS)
               {
                   firehoseResetValidation();
                   return read_retval;
               }

               if (queue_only == TRUE)
                   return FIREHOSE_SUCCESS;

               if (fh.validation_hash_buffer_num_hashes == 0)
               {
                   logMessage("No more hashes to validate against, resetting validation state.");
                   sendResponse(NAK);

                   firehoseResetValidation();
                   return FIREHOSE_VALIDATION_ERROR;
               }

               PerformSHA256(*packet_ptr, *bytes_read, fh.validation_hash_value);

                if ( memcmp( fh.validation_hash_value, fh.validation_hash_buffer[fh.validation_hash_buffer_index], sizeof(fh.validation_hash_value)) != 0)
                {
                    logMessage("Hash of packet of size %lld bytes that target sent does not match hash in table. Rejecting this packet. See log",*bytes_read);

                    // this is what was rejected - fh.channel_buffer[ fh.channel_buffer_to_use ]); //main_channel_buffer_B
                    logDigest("Expected:      ", fh.validation_hash_buffer[fh.validation_hash_buffer_index], sizeof(fh.validation_hash_value));
                    logDigest("Found instead: ", fh.validation_hash_value, sizeof(fh.validation_hash_value));
                    logMessage("(P%04d) (H%04d) Using Table %lld", (int)fh.num_packets_received - 1, (int)fh.validation_hash_buffer_index, fh.validation_table_count);
                    logMessage("Make sure that you are sending the same command used when generating the hash with --createdigests");
                    logMessage("Resetting validation state.");


                    MyErrorMessage(PACKET_HASH_MISMATCH);
                    sendResponse(NAK);

                    firehoseResetValidation();
                    return FIREHOSE_VALIDATION_ERROR;
                }
                
                if(fh.attrs.Verbose == TRUE || ConfigureCommandNotReceivedYet)
                {
                    logMessage("(P%04d) (H%04d) Using Table %lld", (int)fh.num_packets_received - 1, (int)fh.validation_hash_buffer_index, fh.validation_table_count);
                    logMessage("VIP - HASH of packet ACCEPTED");
                }
                
               fh.validation_hash_buffer_num_hashes--;

               if (fh.validation_hash_buffer_index == fh.validation_hash_buffer_capacity - 1)
               {
                   // we're at the end of current hash buffer; this packet is the new one, so store it
                   len_copied = MIN( sizeof(fh.validation_hash_buffer), *bytes_read);

                   memscpy(fh.validation_hash_buffer, sizeof(fh.validation_hash_buffer), *packet_ptr, len_copied);

                   fh.validation_hash_buffer_index       = 0;
                   fh.validation_hash_buffer_num_hashes  = len_copied / sizeof(fh.validation_hash_value);

                   if (fh.validation_hash_buffer_capacity != fh.validation_hash_buffer_new_capacity)
                   {
                       fh.validation_hash_buffer_capacity = fh.validation_hash_buffer_new_capacity;
                   }

                   if (fh.validation_hash_buffer_num_hashes < 2)
                   {
                       debugMessage("read hashes %lld", fh.validation_hash_buffer_num_hashes);
                   }

                   fh.validation_table_count++;
                   sendResponse(ACK);  // set breakpoint here to inspect validation_hash_buffer

                   continue;
               }
               else
               {
                   fh.validation_hash_buffer_index++;
                   packet_validated = TRUE;
               } // end if (fh.validation_hash_buffer_index == fh.validation_hash_buffer_capacity - 1)
           } // end if (fh.validation_signed_hash_received == FALSE)
        } // end while(packet_validated == FALSE)
    }
    else
    {
        read_retval = readChannel(packet_ptr, bytes_to_read, bytes_read, queue_only);
        if (read_retval != FIREHOSE_SUCCESS)
        {
            return read_retval;
        }

        if (queue_only == TRUE)
            return FIREHOSE_SUCCESS;

        if (fh.attrs.AlwaysValidate == TRUE)    // hash in non secure mode to see speed impact
        {
          PerformSHA256(*packet_ptr, *bytes_read, fh.validation_hash_value);
        }
    } // end if (fh.validation_enabled == TRUE)
    return FIREHOSE_SUCCESS;
}

static firehose_error_t queueNextPacket(SIZE_T bytes_to_read) {
    return recvNextPacket(NULL, bytes_to_read, NULL, TRUE);
}

static firehose_error_t getNextPacket(byte** packet_ptr, SIZE_T bytes_to_read, SIZE_T *bytes_read) {
    return recvNextPacket(packet_ptr, bytes_to_read, bytes_read, FALSE);
}

// Parse a string sector value in valueArray and store in parsedValue.
// attrName is name of XML attribute with this value, used in error message.
//
// Returns:
//      FALSE if sector value is non-numerical, if it exceeds the number of
//      sectors in specified partition, or if partition is invalid
//      TRUE if sector value is valid
static boolean parseSectorValue(char* valueArray,
                          SIZE_T value_array_size,
                          SIZE_T *parsedValue,
                          SIZE_T partition,
                          char *attrName) {
    //byte temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE] = {0};
    boolean num_conversion;
    uint64 num_partition_sectors = 0;

    memset(temp_buffer,0,sizeof(temp_buffer));	// clear this out
	
    if (fh.attrs.SkipStorageInit == FALSE)
    {

      if (FALSE == storage_device_get_num_partition_sectors(fh.store_dev, 0, partition, &num_partition_sectors))
	  {
	    logMessage("storage_device_get_num_partition_sectors FAILED!");    // conversion to number failed
            return FALSE;
	  }

    }

    simpleStrReplace(valueArray,
                         ".",
                         "");

    if (strstr(valueArray, "NUM_DISK_SECTORS") != NULL) {
        snprintf((char *)temp_buffer, sizeof(temp_buffer), SIZE_T_FORMAT, num_partition_sectors);
        simpleStrReplace(valueArray,
                         "NUM_DISK_SECTORS",
                         (const char *) temp_buffer);
        //num_conversion = parseExpression(valueArray, parsedValue);
	num_conversion = MyParseExpression(valueArray, strlen(valueArray), parsedValue);
    }
    else
    {
        //num_conversion = parseExpression(valueArray, parsedValue);
	num_conversion = MyParseExpression(valueArray, strlen(valueArray), parsedValue);
    }
    if (FALSE == num_conversion)
    {
        logMessage("Can't convert attribute '%s'='%s' to number", attrName, valueArray);    // conversion to number failed
        return FALSE;
    }

    if (fh.attrs.SkipStorageInit == FALSE)
    {

       if (*parsedValue > num_partition_sectors)
       {
           logMessage("XML attribute '%s'=%lld exceeds total size of partition %lld in sectors: %lld", attrName, *parsedValue, partition, num_partition_sectors);
           return FALSE;
       }
    }
    return TRUE;
}

static firehose_error_t handleConfigure()
{
    response_t response = ACK;
    char *memory_name;

    //char temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE] = {0};

	memset(temp_buffer,0,sizeof(temp_buffer));	// clear this out

    // Let's first clear the variables that the <configure> can
    // set, by assigning default values
    //fh.skip_storage_writes = FALSE;
    //fh.ack_raw_data_every = 0;
    //fh.hash_in_non_secure = FALSE;
    //fh.verbose = FALSE;

    ConfigureCommandNotReceivedYet = 0; // we have gotten it now
    
    // set defaults if not provided
    if (fh.attrs.MaxPayloadSizeToTargetInBytes == 0)
    {
        logMessage("Host's payload to target size not provided or 0; using %lld", (SIZE_T)fh.channel_buffer_capacity);
        fh.attrs.MaxPayloadSizeToTargetInBytes = fh.channel_buffer_capacity;
    }

    if (fh.attrs.MaxDigestTableSizeInBytes == 0)
    {
        logMessage("Host's hash buffer size not provided or 0; using %lld", (SIZE_T)sizeof(fh.validation_hash_buffer));
        fh.attrs.MaxDigestTableSizeInBytes = sizeof(fh.validation_hash_buffer);
    }

    if (fh.attrs.MaxPayloadSizeToTargetInBytes > fh.channel_buffer_capacity)
    {
        logMessage("fh.attrs.MaxPayloadSizeToTargetInBytes of %lld > fh.channel_buffer_capacity of %lld",fh.attrs.MaxPayloadSizeToTargetInBytes,fh.channel_buffer_capacity);
        fh.attrs.MaxPayloadSizeToTargetInBytes = fh.channel_buffer_capacity; // correct this
        response = NAK;
    }
    else
    {
        fh.channel_buffer_capacity = fh.attrs.MaxPayloadSizeToTargetInBytes;
    }

    if (fh.attrs.MaxDigestTableSizeInBytes > sizeof(fh.validation_hash_buffer))
    {
        logMessage("Attribute '%s'=%lld cannot exceed %lld", "MaxDigestTableSizeInBytes", fh.attrs.MaxDigestTableSizeInBytes, (SIZE_T)sizeof(fh.validation_hash_buffer));
        MyErrorMessage(HANDLE_CONFIGURE_FAILURE);
        fh.attrs.MaxDigestTableSizeInBytes = sizeof(fh.validation_hash_buffer);
        response = NAK;
    }
    else {
        // TODO: MAYBE: there might be a more elegant way to handle
        // this but at the moment this is the simplest, i.e. keep a
        // separate variable and when the time comes to fetch a new
        // hash table, grab this size instead of the original size
        fh.validation_hash_buffer_new_capacity = fh.attrs.MaxDigestTableSizeInBytes / sizeof(fh.validation_hash_value);
    }

    if(fh.attrs.SkipStorageInit == TRUE) 		{        logMessage("skipping storage init requested by user");    }
    if(fh.attrs.SkipWrite == TRUE) 				{        logMessage("skipping write requested by user");    }
#ifdef USE_FIRMWARE_BUFFER    
    if(fh.attrs.BufferWrites == TRUE) 		    {        logMessage("BufferWrites in the BigFWBuffer enabled");    }
#endif    
    //if(fh.attrs.AckRawData == TRUE) 			{        fh.ack_raw_data_every = 1;											    }
    //if(fh.attrs.AckRawDataEveryNumPackets > 0) 	{        fh.ack_raw_data_every = fh.attrs.AckRawDataEveryNumPackets;		    }
    //if(fh.attrs.AlwaysValidate == TRUE) 		{        fh.hash_in_non_secure = TRUE;										    }
    //if(fh.attrs.Verbose == TRUE) 				{        fh.verbose = TRUE;													    }

	//logMessage("In handleConfigure() and fh.attrs.ZlpAwareHost=%ld",fh.attrs.ZlpAwareHost);

    if(fh.attrs.ZlpAwareHost == FALSE)
    {
        //if(fh.attrs.Verbose == TRUE)
            logMessage("Calling usb_al_bulk_set_zlp_mode(FALSE) since ZlpAwareHost='0'");

        usb_al_bulk_set_zlp_mode(FALSE);
    }
	else
	{
        logMessage("Calling usb_al_bulk_set_zlp_mode(TRUE) since ZlpAwareHost='1'");
        usb_al_bulk_set_zlp_mode(TRUE);
	}

	//logMessage("In handleConfigure() and fh.attrs.ZlpAwareHost=%ld",fh.attrs.ZlpAwareHost);



/*
#ifndef FEATURE_FIREHOSE_SKIP_CLOCK

    // Lowering clock frequencies because otherwise eMMC card initialization sometimes fails
    // if the clock '' is set too high
    if (fh.attrs.SkipSettingMinClocks == 0)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling Clock_Init(CLOCK_BOOT_PERF_MIN, CLOCK_BOOT_PERF_MIN) - If this hangs use SkipSettingMinClocks='1' for configure");

        if (FALSE == Clock_Init(CLOCK_BOOT_PERF_MIN, CLOCK_BOOT_PERF_MIN)) {
            logMessage("FAILED Clock_Init(CLOCK_BOOT_PERF_MIN, CLOCK_BOOT_PERF_MIN) returned FALSE");
            sendResponse(NAK);

            return FIREHOSE_ERROR;
        }
    }
    else if(fh.attrs.Verbose == TRUE)
            logMessage("SKIPPING Clock_Init(CLOCK_BOOT_PERF_MIN, CLOCK_BOOT_PERF_MIN) at users request");

#endif
*/
    fh.storage_type = fh.attrs.storage_type;
    if(fh.attrs.SkipStorageInit == FALSE)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling storage_device_open(0x%X) - If this hangs use SkipStorageInit='1' for configure",fh.attrs.storage_type);

        if(storage_device_open(fh.store_dev, fh.attrs.storage_type) == FALSE)
        {
            logMessage("storage_device_open() returned FALSE");
            MyErrorMessage(HANDLE_CONFIGURE_FAILURE);
            sendResponse(NAK);
            return FIREHOSE_ERROR;
        }
    }
    else
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("SkipStorageInit is TRUE, Therefore assigning fh.storage_type=0x%X",fh.attrs.storage_type);

        // set anyway so we can do storage extras
        storage_device_set_type (fh.store_dev, fh.attrs.storage_type);
    } // end of if(fh.attrs.SkipStorageInit == FALSE)


/*
    if(fh.storage_type == STORAGE_DEVICE_TYPE_UFS )
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("In handleConfigure() Calling init_ufs_params() since fh.storage_type=STORAGE_DEVICE_TYPE_UFS");

        if(init_ufs_params(fh.store_dev)==FALSE)
        {
            if(fh.attrs.Verbose == TRUE)
                logMessage("In handleConfigure() init_ufs_params() returned FALSE");
        } // end if(
    }  // end if(fh.storage_type == STORAGE_DEVICE_TYPE_UFS )
*/

/*
#ifndef FEATURE_FIREHOSE_SKIP_CLOCK
    // This calls the Clock API to bump up clocks.
    // Before doing this, we need support for it in the Clock SCons
    // env.AddLibsToImage(['CLOCK_BOOT_DRIVER', 'EMMCBLD_IMAGE'],
    // ClockChipsetSBL_lib)
    // in file core\systemdrivers\clock\hw\msm8974\build\clock_sbl.scons

    if (fh.attrs.SkipSettingMaxClocks == 0)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX) - If this hangs use SkipSettingMaxClocks='1' for configure");

        if (FALSE == Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX))
        {
            logMessage("FAILED - Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX) returned FALSE");
            sendResponse(NAK);
            return FIREHOSE_ERROR;
        }
    }
    else if(fh.attrs.Verbose == TRUE)
        logMessage("SKIPPING Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX) at users request");

#endif
*/

    switch (fh.storage_type)
    {
        case STORAGE_DEVICE_TYPE_MMC:
            memory_name = "eMMC";
            break;
        case STORAGE_DEVICE_TYPE_UFS:
            memory_name = "UFS";
            break;
        case STORAGE_DEVICE_TYPE_SPI_NOR:
            memory_name = "spinor";
            break;
        default:
            memory_name = "none";
    }

    if(fh.attrs.Verbose == TRUE)
        logMessage("memory_name set to '%s' and fh.sector_size = %lld", memory_name,(SIZE_T)fh.sector_size);


    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only

    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    if(response==ACK)
        AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" ", FIREHOSE_TX_BUFFER_SIZE);
    else
        AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" ", FIREHOSE_TX_BUFFER_SIZE);

    AppendToBuffer(fh.tx_buffer,"MinVersionSupported=\"1\" ", FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"MemoryName=\"%s\" ", memory_name);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"MaxPayloadSizeFromTargetInBytes=\"%d\" ", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"MaxPayloadSizeToTargetInBytes=\"%llu\" ", fh.channel_buffer_capacity);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"MaxPayloadSizeToTargetInBytesSupported=\"%lld\" ", fh.channel_buffer_capacity);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"MaxXMLSizeInBytes=\"%lu\" ", sizeof(fh.xml_buffer));
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"Version=\"%d\" ", 1);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    snprintf(temp_buffer,sizeof(temp_buffer),"TargetName=\"%s\" ", DEVICEPROGRAMMER_TARGET_NAME);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

#ifdef DEVICEPROGRAMMER_BUILD_ID
    snprintf(temp_buffer,sizeof(temp_buffer),"BuildId=\"%s\" ",DEVICEPROGRAMMER_BUILD_ID);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);
#endif
    snprintf(temp_buffer,sizeof(temp_buffer),"DateTime=\"%s\" ",__DATE__ " - " __TIME__);
    AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);

    AppendToBuffer(fh.tx_buffer,"/>\n</data>", FIREHOSE_TX_BUFFER_SIZE);
    sendTransmitBuffer();

    return FIREHOSE_SUCCESS;

} // end of handleConfigure

static firehose_error_t handleGetStorageInfo() {
    uint32 i = 0;
    uint32 j = 0;
    uint32 buffer_len = 0;
    boolean result = FALSE;
    struct ufs_info_type *ufs_info = NULL;
    char buf[30];

    /* This GetInfo goes common layer to get a few typical storage info data */
    if (FALSE == storage_device_get_info(fh.store_dev, 0, fh.attrs.physical_partition_number))
    {
        logMessage("GetStorageInfo Failed - storage_device_get_info() returned FALSE");
        MyErrorMessage(HANDLE_STORAGE_INFO_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    /* Get omplete storage device info. */
    buffer_len = sizeof (storage_raw_data_buff);

    result = storage_device_get_info_raw(fh.store_dev, &storage_raw_data_buff[0], &buffer_len);
    if (FALSE == result)
    {
        logMessage("GetStorageInfo Raw Data failed in storage_device_get_info_raw() ");
        MyErrorMessage(HANDLE_STORAGE_INFO_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if (buffer_len > STORAGE_DEVICE_INFO_BUFFER_SIZE)
    {
        logMessage("GetStorageInfo Buffer is overwritten. buffer_len = %d", buffer_len);
        MyErrorMessage(HANDLE_STORAGE_INFO_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if (STORAGE_DEVICE_TYPE_MMC  == fh.storage_type)
    {

        logMessage("eMMC Extended CSD Revision: 0x%x", (uint8_t)storage_raw_data_buff[192]);
        logMessage("eMMC Firmware Version: 0x%x", (uint64_t)storage_raw_data_buff[254]);

        /* Note: temp_buffer needs to be at least (STORAGE_DEVICE_INFO_BUFFER_SIZE + 1) */
        /* The reason is for every element of the array storage_raw_data_buff[], */
        /* we send 2 bytes in the hex format */
        /* There is a NULL character added at the end to indicate the end of the string */
        memset (temp_buffer, 0, sizeof(temp_buffer));

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<data>\n",FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<log value=\"eMMC_RAW_DATA [0:265]",FIREHOSE_TX_BUFFER_SIZE);

        /* We have a small TX_BUFFER_SIZE 1K and small temp_buffer */
        /* Break the transfer of 532 bytes eMMC raw data into 2 transactions */
        for(i=0; i<STORAGE_DEVICE_INFO_BUFFER_SIZE/2; i++)
        {
            snprintf(&temp_buffer[i*2], sizeof (temp_buffer), "%02X", (byte)(storage_raw_data_buff[i]&0xFF));
        }
        /* Add a NULL to indicate the end of the string */
        temp_buffer[i*2] = '\0';

        AppendToBuffer(fh.tx_buffer, temp_buffer, FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"\" />\n</data>",FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<data>\n",FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<log value=\"eMMC_RAW_DATA [266:531]",FIREHOSE_TX_BUFFER_SIZE);

        memset (temp_buffer, 0, sizeof(temp_buffer));

        for(i=0; i<STORAGE_DEVICE_INFO_BUFFER_SIZE/2; i++)
        {
            snprintf(&temp_buffer[i*2], sizeof (temp_buffer), "%0.2X", (byte)(storage_raw_data_buff[i+STORAGE_DEVICE_INFO_BUFFER_SIZE/2]&0xFF));
        }
        /* Add a NULL to indicate the end of the string */
        temp_buffer[i*2] = '\0';

        AppendToBuffer(fh.tx_buffer,temp_buffer, FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"\" />\n</data>",FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();
    }
    else if (STORAGE_DEVICE_TYPE_UFS == fh.storage_type)
    {
        ufs_info = (struct ufs_info_type*) storage_raw_data_buff;
        logMessage("UFS fInitialized: 0x%x", (uint8_t)ufs_info->fInitialized);
        logMessage("UFS Current LUN Number: = 0x%x", (uint8_t)ufs_info->bLUN);
        logMessage("UFS Total Active LU: 0x%x", (uint8_t)ufs_info->bNumberLu);
        logMessage("UFS wManufacturerID: 0x%x", (uint16_t)ufs_info->wManufacturerID);
        logMessage("UFS Boot Partition Enabled: 0x%x", (uint8_t)ufs_info->bBootEnable);
        logMessage("UFS Raw Device Capacity: = 0x%x", (uint64_t)ufs_info->qTotalRawDeviceCapacity);
        logMessage("UFS Min Block Size: 0x%x", (uint8_t)ufs_info->bMinAddrBlockSize);
        logMessage("UFS Erase Block Size: 0x%x", (uint32_t)ufs_info->dSegmentSize);
        logMessage("UFS Allocation Unit Size: 0x%x", (uint8_t)ufs_info->bAllocationUnitSize);
        logMessage("UFS RPMB ReadWrite Size: = 0x%x", (uint32_t)ufs_info->bRPMB_ReadWriteSize);
        logMessage("UFS Number of Allocation Uint for This LU: 0x%x", (uint32_t)ufs_info->dNumAllocUnits);
        logMessage("UFS Logical Block Size: 0x%x", (uint8_t)ufs_info->bLogicalBlockSize);
        logMessage("UFS Provisioning Type: 0x%x", (uint8_t)ufs_info->bProvisioningType);
        logMessage("UFS LU Write Protect: 0x%x", (uint8_t)ufs_info->bLUWriteProtect);
        logMessage("UFS Boot LUN ID: = 0x%x", (uint8_t)ufs_info->bBootLunID);
        logMessage("UFS Memory Type: 0x%x", (uint8_t)ufs_info->bMemoryType);
        logMessage("UFS LU Total Blocks: 0x%x", (uint32_t)ufs_info->dLuTotalBlocks);
        logMessage("UFS Supported Memory Types: 0x%x", (uint16_t)ufs_info->wSupportedMemoryTypes);
        logMessage("UFS dEnhanced1MaxNAllocU: 0x%x", (uint32_t)ufs_info->dEnhanced1MaxNAllocU);
        logMessage("UFS wEnhanced1CapAdjFac: 0x%x", (uint16_t)ufs_info->wEnhanced1CapAdjFac);
        logMessage("UFS dEnhanced2MaxNAllocU: = 0x%x", (uint32_t)ufs_info->dEnhanced2MaxNAllocU);
        logMessage("UFS wEnhanced2CapAdjFac: 0x%x", (uint16_t)ufs_info->wEnhanced2CapAdjFac);
        logMessage("UFS dEnhanced3MaxNAllocU: 0x%x", (uint32_t)ufs_info->dEnhanced3MaxNAllocU);
        logMessage("UFS wEnhanced3CapAdjFac: 0x%x", (uint16_t)ufs_info->wEnhanced3CapAdjFac);
        logMessage("UFS dEnhanced4MaxNAllocU: 0x%x", (uint32_t)ufs_info->dEnhanced4MaxNAllocU);
        logMessage("UFS wEnhanced4CapAdjFac: 0x%x", (uint16_t)ufs_info->wEnhanced4CapAdjFac);
        logMessage("UFS LUN Enable Bitmask: 0x%x", (uint32_t)ufs_info->dLunEnabled);
        logMessage("UFS Logical Block Count: 0x%x", (uint64_t)ufs_info->qLogicalBlockCount);
        logMessage("UFS bConfigDescrLock: 0x%x", (uint8_t)ufs_info->bConfigDescrLock);
        logMessage("UFS iManufacturerName String Index: 0x%x", (uint8_t)ufs_info->iManufacturerName);
        logMessage("UFS iProductName String Index: 0x%x", (uint8_t)ufs_info->iProductName);
        logMessage("UFS iSerialNumber String Index: 0x%x", (uint8_t)ufs_info->iSerialNumber);
        logMessage("UFS iOemID String Index: 0x%x", (uint8_t)ufs_info->iOemID);

        /* Send Inquiry String */
        for (j=0;j<28;j++) 
        {
           buf[j] = ufs_info->inquiry_str[j] != 0 ? ufs_info->inquiry_str[j] : ' ';
        }
        buf[28] = 0;
        buf[29] = 0;
        logMessage("UFS Inquiry Command Output: %s ", buf);
    }
    sendResponse(ACK);

    return FIREHOSE_SUCCESS;
}

static firehose_error_t handlePower() 
{
    SIZE_T  delay_time = 0;
    typedef enum {POWER_NONE, POWER_RESET, POWER_OFF, POWER_RESET_TO_EDL} power_action_t;
    power_action_t power_action = POWER_NONE;

    debugMessage("Inside handlePower()");

    if (strncasecmp((char *)fh.attrs.value, "reset_to_edl", strlen("reset_to_edl")) == 0) 
    {
        power_action = POWER_RESET_TO_EDL;
        logMessage("Inside handlePower() - Requested POWER_RESET_TO_EDL - Will set PBL cookies before reset");
    }
    else if (strncasecmp((char *)fh.attrs.value, "reset", strlen("reset")) == 0) 
    {
        power_action = POWER_RESET;
        logMessage("Inside handlePower() - Requested POWER_RESET");
    }
    else if (strncasecmp((char *)fh.attrs.value, "off", strlen("off")) == 0) 
    {
        power_action = POWER_OFF;
        logMessage("Inside handlePower() - Requested POWER_OFF");
    }

    //if(fh.attrs.Verbose == TRUE) // ALWAYS SHOW THIS. Cause if Watchdog is not enable, target will appear hung
    

    delay_time = fh.attrs.delayinseconds;
    if (delay_time < 1) {
        delay_time = 1; // At least 1 second to give time for USB messages to be sent back to PC
    }

    if (power_action == POWER_RESET) 
    {
        logMessage("Issuing bsp_target_reset() after %ld seconds, if this hangs, do you have WATCHDOG enabled?",delay_time);
        sendResponse(ACK);
        delaySeconds(delay_time);
        debugMessage("bsp_target_reset();");
        bsp_target_reset();
        while(1);
    }
    else if (power_action == POWER_OFF) 
    {
        logMessage("Issuing bsp_target_poweroff() after %ld seconds, if this hangs, do you have WATCHDOG enabled?",delay_time);
        sendResponse(ACK);
        delaySeconds(delay_time);
        debugMessage("bsp_target_poweroff()");
        bsp_target_poweroff();
        while(1);
    } else if (power_action == POWER_RESET_TO_EDL) 
    {
        logMessage("Issuing bsp_target_reset_edl() after %ld seconds, if this hangs, do you have WATCHDOG enabled?",delay_time);
        sendResponse(ACK);
        delaySeconds(delay_time);
        debugMessage("bsp_target_reset_edl()");
        bsp_target_reset_edl();
        while(1);
    }

    logMessage("To be here means power_action was not understood with power tag. Target is *not* being reset or powered off");


    sendResponse(NAK);
    return FIREHOSE_ERROR;
}

static firehose_error_t handlePeek() 
{
    //byte temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE] = {0};
    byte another_temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE] = {0};
    byte* address = (byte *) (uintptr_t) fh.attrs.address64;
    SIZE_T i,
   // Each byte will take 5 characters [0 x 0 0 space]
   bytes_per_log_message = FIREHOSE_TEMP_LOG_BUFFER_SIZE / 5;

   if (isSecureBootEnabled() == TRUE)
   {
     logMessage("Peek not allowed when secure boot is enabled.");
     sendResponse(NAK);
     return FIREHOSE_ERROR;
   }

   memset(temp_buffer,0,sizeof(temp_buffer));	// clear this out
   
    if (NULL == address || 0 == fh.attrs.size_in_bytes)
    {
        if (NULL == address)
            logMessage("Attribute '%s' can't equal %lld", "address", fh.attrs.address64);
        else
            logMessage("Attribute '%s' can't equal %lld", "size_in_bytes", fh.attrs.size_in_bytes);

        MyErrorMessage(HANDLE_PEEK_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
    logMessage("Using address %p", address);
    for (i = 0; i < fh.attrs.size_in_bytes; ++i)
    {
        snprintf((char *) temp_buffer, sizeof(temp_buffer), "0x%02X ", *(address + i));
        strlcat((char *) another_temp_buffer, (const char *) temp_buffer, sizeof(another_temp_buffer));
        if ((i + 1) % bytes_per_log_message == 0 || i == fh.attrs.size_in_bytes - 1) {
            logMessage("%s", another_temp_buffer);
            another_temp_buffer[0] = '\0';
        }
    }
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}

static firehose_error_t handlePoke() {
    byte* address = (byte *) (uintptr_t) fh.attrs.address64;
    SIZE_T i;

    if (isSecureBootEnabled() == TRUE)
    {
      logMessage("Poke not allowed when secure boot is enabled.");
      sendResponse(NAK);
      return FIREHOSE_ERROR;
    }

    if (NULL == address || 0 == fh.attrs.size_in_bytes)
    {
        if (NULL == address)
            logMessage("Attribute '%s' can't equal %lld", "address", fh.attrs.address64);
        else
            logMessage("Attribute '%s' can't equal %lld", "size_in_bytes", fh.attrs.size_in_bytes);

        MyErrorMessage(HANDLE_POKE_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
    if (fh.attrs.size_in_bytes > sizeof(fh.attrs.value64))
    {
        logMessage("Attribute '%s'=%lld cannot exceed %lld", "size_in_bytes", fh.attrs.size_in_bytes, sizeof(fh.attrs.value64));
        MyErrorMessage(HANDLE_POKE_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
    logMessage("Using address %p", address);
    for (i = 0; i < fh.attrs.size_in_bytes; ++i)
    {
        *address = fh.attrs.value64 & 0xFF;
        address++;
        fh.attrs.value64 = fh.attrs.value64 >> 8;
    }
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}

int ReturnNumAttributes(void)
{
	return (int)(sizeof(AllAttributes)/sizeof(struct Attributes_Struct));
}

int ReturnAttributeLocation(char *NewAttrName)
{
    volatile SIZE_T i;
	SIZE_T StringLength1=0,StringLength2=0;

	StringLength1 = strlen((const char *)NewAttrName);

    for(i=0;i<(SIZE_T)ReturnNumAttributes();i++)
    {
		StringLength2 = strlen((const char *)AllAttributes[i].Name);

		if(StringLength1<StringLength2)
			StringLength1 = StringLength2;	// want the biggest number

        if ( strncasecmp(AllAttributes[i].Name, NewAttrName, StringLength1) == 0)
        {
			return i;
		}
	}

	return -1;
}

static int was_attribute_assigned(char* attribute)
{
  int offset;
  offset = ReturnAttributeLocation (attribute);
  if (offset == -1)
    return 0;

  if(AllAttributes[offset].Assigned == 0)
    return 0;

  return 1;
}

static firehose_error_t handleErase()
{
  uint64 start_sector = 0;
  uint64 num_sectors = 0;
    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling storage_device_erase(%d)",fh.attrs.physical_partition_number);

    logMessage("In handleErase Calling storage_device_erase()");

    if(was_attribute_assigned("start_sector"))
    {
      start_sector = fh.attrs.start_sector;
      if(was_attribute_assigned("num_partition_sectors"))
        num_sectors = fh.attrs.num_partition_sectors;
    }

    if(num_sectors == 0)
    {
      if(fh.attrs.Verbose == TRUE)
        logMessage("Did not specify start/size, format whole device");
      if(storage_device_format(fh.store_dev, 0, fh.attrs.physical_partition_number) == FALSE)
      {
        logMessage("storage_device_format returned FALSE");
        MyErrorMessage(HANDLE_ERASE_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_STORAGE_ERROR;
      }
    }
    else
    {
      if(fh.attrs.Verbose == TRUE)
        logMessage("Specified start%d and size %d to erase", start_sector,
          num_sectors);
      if(storage_device_erase(fh.store_dev, 0, fh.attrs.physical_partition_number, start_sector, num_sectors) == FALSE)
      {
        logMessage("storage_device_erase returned FALSE");
        MyErrorMessage(HANDLE_ERASE_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_STORAGE_ERROR;
      }
    }

    logMessage("storage_device_erase() reported SUCCESS");
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}

static firehose_error_t handleNop()
{
    logMessage("Binary build date: %s @ %s\n", __DATE__, __TIME__);
    
    //fh.attrs.Verbose ^= 1;
    logMessage("fh.attrs.Verbose is set to %i", fh.attrs.Verbose);

    sendAndAuthSerialNum();
    sendSupportedFunctions();
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}

static firehose_error_t handleSetBootableStorageDrive()
{
    boolean num_conversion;

    // Declare the variables we care about
    SIZE_T bootable_drive = stringToNumber((const char *) fh.attrs.value, &num_conversion); // fh.attrs.value parsed as string
    if (FALSE == num_conversion)
    {
        logMessage("Can't convert attribute '%s'='%s' to number", "value", fh.attrs.value); // conversion to number failed
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if(fh.attrs.Verbose == TRUE)
    {
      logMessage("Calling storage_device_set_bootable_partition(%d) of size",bootable_drive);
    }

    if (storage_device_set_bootable_partition(fh.store_dev, 0, bootable_drive) == TRUE)
    {
        sendResponse(ACK);
        return FIREHOSE_SUCCESS;
    }
    else
    {
        sendResponse(NAK);
        return FIREHOSE_STORAGE_ERROR;
    }
}


void Display_storage_extras_UFS(void)
{
	int i;
	// test if attribute was set here
	i = ReturnAttributeLocation("bNumberLU");
	if(i==-1) { return; }

	if(AllAttributes[i].Assigned == 1)
	{
		InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE); 
		AppendToBuffer(fh.tx_buffer,"<data>\n",FIREHOSE_TX_BUFFER_SIZE);
		AppendToBuffer(fh.tx_buffer,"<log value=\"",FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bNumberLU=%i ",storage_extras.ufs_extras.bNumberLU);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bBootEnable=%i ",storage_extras.ufs_extras.bBootEnable);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bDescrAccessEn=%i ",storage_extras.ufs_extras.bDescrAccessEn);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bInitPowerMode=%i ",storage_extras.ufs_extras.bInitPowerMode);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bHighPriorityLUN=%i ",storage_extras.ufs_extras.bHighPriorityLUN);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bSecureRemovalType=%i ",storage_extras.ufs_extras.bSecureRemovalType);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bInitActiveICCLevel=%i ",storage_extras.ufs_extras.bInitActiveICCLevel);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"wPeriodicRTCUpdate=%i ",storage_extras.ufs_extras.wPeriodicRTCUpdate);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bConfigDescrLock=%i ",storage_extras.ufs_extras.bConfigDescrLock);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		AppendToBuffer(fh.tx_buffer,"\" />\n</data>",FIREHOSE_TX_BUFFER_SIZE);
		sendTransmitBuffer();
	}		
	
	i = ReturnAttributeLocation("LUNum");
	if(i==-1) { return; }

	if(AllAttributes[i].Assigned == 1)
	{
		// show variables now. NOTE, can't use    i = UFS_LUN_Var_Struct.LUNum    since I memset this struct
			 if(AllAttributes[i].Raw[0] == '1') { i = 1; }
		else if(AllAttributes[i].Raw[0] == '2') { i = 2; }
		else if(AllAttributes[i].Raw[0] == '3') { i = 3; }
		else if(AllAttributes[i].Raw[0] == '4') { i = 4; }
		else if(AllAttributes[i].Raw[0] == '5') { i = 5; }
		else if(AllAttributes[i].Raw[0] == '6') { i = 6; }
		else if(AllAttributes[i].Raw[0] == '7') { i = 7; }
		else 							        { i = 0; }
		
		InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE); 
		AppendToBuffer(fh.tx_buffer,"<data>\n",FIREHOSE_TX_BUFFER_SIZE);
		AppendToBuffer(fh.tx_buffer,"<log value=\"",FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"LUNum=%i ",i);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bLUEnable=%i ",storage_extras.ufs_extras.unit[i].bLUEnable);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bBootLunID=%i ",storage_extras.ufs_extras.unit[i].bBootLunID);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bLUWriteProtect=%i ",storage_extras.ufs_extras.unit[i].bLUWriteProtect);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bMemoryType=%i ",storage_extras.ufs_extras.unit[i].bMemoryType);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"size_in_KB=%i ",storage_extras.ufs_extras.unit[i].dNumAllocUnits);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bDataReliability=%i ",storage_extras.ufs_extras.unit[i].bDataReliability);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bLogicalBlockSize=%i ",storage_extras.ufs_extras.unit[i].bLogicalBlockSize);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"bProvisioningType=%i ",storage_extras.ufs_extras.unit[i].bProvisioningType);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		snprintf(temp_buffer,sizeof(temp_buffer),"wContextCapabilities=%i ",storage_extras.ufs_extras.unit[i].wContextCapabilities);
		AppendToBuffer(fh.tx_buffer,temp_buffer,FIREHOSE_TX_BUFFER_SIZE);
		AppendToBuffer(fh.tx_buffer,"\" />\n</data>",FIREHOSE_TX_BUFFER_SIZE);
		sendTransmitBuffer();
	}

}



static firehose_error_t handleStorageExtras()
{
#ifndef FEATURE_FIREHOSE_ENABLE_STORAGE_EXTRAS
    logMessage("handleStorageExtras() is not supported in this image");
    return sendResponse(NAK);
#endif

    if (fh.attrs.commit == FALSE)
    {
		if(fh.storage_type == STORAGE_DEVICE_TYPE_UFS)
			Display_storage_extras_UFS();
		
        //logMessage("In handleStorageExtras() but doing nothing since commit==FALSE");
        return sendResponse(ACK);
    }

    // To be this far means we're going through with committing these changes

    if (FALSE == storage_device_commit_extras(fh.store_dev, &storage_extras))
    {
        logMessage("Failed to set storage extra parameters - storage_device_commit_extras() returned FALSE");  // Failed to set storage extra parameters
        return sendResponse(NAK);
    }


    logMessage("Set storage parameters successfully");

    // Clear these for next run
    fh.attrs.commit = 0;
    memset(&storage_extras.emmc_extras,0,sizeof(sdcc_emmc_gpp_enh_desc_type));	// clear this out for next run
    memset(&storage_extras.ufs_extras, 0,sizeof(struct ufs_config_descr));		// clear this out for next run

    return sendResponse(ACK);
}

static firehose_error_t handleFirmwareProgram() {
    SIZE_T bytes_to_read = 0;
    response_t response = ACK;

    if (fh.attrs.num_partition_sectors == ATTR_INVALID_VAL)
    {
        logMessage("Attribute '%s' not provided (or -1)", "num_partition_sectors");   // not provided or invalid
        MyErrorMessage(HANDLE_FIRMWARE_PROGRAM_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    logMessage ("firmwarewrite cmd: Sector size %lld", fh.attrs.SECTOR_SIZE_IN_BYTES);
    logMessage ("firmwarewrite cmd: Number of Sectors %lld", fh.attrs.num_partition_sectors);

    bytes_to_read = fh.attrs.SECTOR_SIZE_IN_BYTES * fh.attrs.num_partition_sectors;

    if(fh.attrs.actual_size_in_bytes>0)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("fh.attrs.actual_size_in_bytes found");

        bytes_to_read = fh.attrs.actual_size_in_bytes;
    }


    fh.attrs.actual_size_in_bytes = 0;  // always reset him here

    if(fh.attrs.Verbose == TRUE)
        logMessage("Bytes to read from channel: %lld", bytes_to_read);

    if (bytes_to_read == 0)
    {
        // Firmware Binary must be non-zero in size (size_in_bytes == 0). Check binary
        logMessage("Firmware Binary must be non-zero in size (size_in_bytes == 0). Check binary");
        MyErrorMessage(HANDLE_FIRMWARE_PROGRAM_FAILURE);

        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

#ifdef USE_FIRMWARE_BUFFER    
    if (bytes_to_read > BIG_FW_BUFFER_SIZE)
    {
        logMessage("%s must be less than %lld bytes (currently %lld)", "(SECTOR_SIZE_IN_BYTES * num_partition_sectors)", BIG_FW_BUFFER_SIZE, bytes_to_read);
        MyErrorMessage(HANDLE_FIRMWARE_PROGRAM_FAILURE);

        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
#else
    if (bytes_to_read > fh.channel_buffer_capacity)
    {
        logMessage("%s must be less than %lld bytes (currently %lld)", "(SECTOR_SIZE_IN_BYTES * num_partition_sectors)", fh.channel_buffer_capacity, bytes_to_read);
        MyErrorMessage(HANDLE_FIRMWARE_PROGRAM_FAILURE);

        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
#endif
    
    
    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"true\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
    sendTransmitBuffer();

#ifdef USE_FIRMWARE_BUFFER
    BigFWBufferCount    = 0;
    BigFWBufferExpected = (SIZE_T) bytes_to_read;

    SIZE_T bytes_read_in_layer;

    while(BigFWBufferExpected>0)
    {
        byte * raw_data_buffer;
        firehose_error_t channel_read_retval  = FIREHOSE_SUCCESS;
        raw_data_buffer = fh.channel_buffer[1 - fh.channel_buffer_to_use];

        bytes_read_in_layer = (SIZE_T) MIN(BigFWBufferExpected, fh.attrs.MaxPayloadSizeToTargetInBytes);

        channel_read_retval = getNextPacket(&raw_data_buffer, bytes_read_in_layer, &bytes_read_in_layer);
        if (channel_read_retval != FIREHOSE_SUCCESS)
        {
            response = NAK;
            goto end;
        }

        // Now store it in BigFWBuffer
        memscpy ( &BigFWBuffer[BigFWBufferCount], BIG_FW_BUFFER_SIZE, raw_data_buffer, bytes_read_in_layer );
        BigFWBufferExpected -= bytes_read_in_layer;
        BigFWBufferCount    += bytes_read_in_layer;
    }

    // to be this far I should have all the FW data in BigFWBufferCount

    if (response == ACK) 
    {
        logMessage("Channel read %lld bytes", bytes_read_in_layer);
    }

    BigFWBufferExpected = BigFWBufferCount;

    
    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling storage_device_fw_update(NumSectors=%d)",BigFWBufferExpected);

    //response = ACK;
    //ghoto end;

    //if (FALSE == storage_device_fw_update(fh.store_dev, raw_data_buffer, fh.attrs.num_partition_sectors))
    if (FALSE == storage_device_fw_update(fh.store_dev, BigFWBuffer, BigFWBufferExpected))
    {
        response = NAK;
        goto end;
    }

    response = ACK;

end:

#endif

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
        AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
        if(response==ACK)
                AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        else
                AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();

    if (response == NAK)
        return FIREHOSE_ERROR;

    return FIREHOSE_SUCCESS;
}

static firehose_error_t handlePatch() 
{
    boolean num_conversion;

    // Let's declare the variables we care about
    //byte temp_buffer[FIREHOSE_TEMP_BUFFER_SIZE] = {0};
    SIZE_T patch_result = 0;
    byte * raw_data_buffer;
    uint64 num_partition_sectors = 0;

    // Declare vars used in the CRC patch value parsing
    SIZE_T crc_start_sector, crc_over_num_bytes;
    char *comma_pos;
    char *end_crc_pos;
    SIZE_T patch_value_len, StringLength;

	memset(temp_buffer,0,sizeof(temp_buffer));	// clear this out
	
    if (fh.attrs.start_sector == ATTR_INVALID_VAL)
    {
        logMessage("Attribute '%s' not provided (or -1)", "start_sector", ATTR_INVALID_VAL);    // not provided or invalid
        MyErrorMessage(HANDLE_PATCH_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if (FALSE == storage_device_get_num_partition_sectors(fh.store_dev, 0, fh.attrs.physical_partition_number, &num_partition_sectors)) {
        return FIREHOSE_ERROR;
    }

    if (fh.attrs.byte_offset >= fh.channel_buffer_capacity) {
        return FIREHOSE_ERROR;
    }
    if (strncasecmp("DISK", fh.attrs.filename, sizeof(fh.attrs.filename)) != 0) {
        // Nothing to be done if it is not a DISK patch
        return FIREHOSE_SUCCESS;
    }
    if (fh.sector_size != fh.attrs.SECTOR_SIZE_IN_BYTES)
    {
        logMessage("Attribute 'SECTOR_SIZE_IN_BYTES'=%lld must be equal to disk sector size %lld", fh.attrs.SECTOR_SIZE_IN_BYTES, fh.sector_size);
        MyErrorMessage(HANDLE_PATCH_FAILURE);

        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    // TODO: Clean this up. This functionality should not know so much
    // about the buffers available
    raw_data_buffer = fh.channel_buffer[0];

    snprintf((char *)temp_buffer, sizeof(temp_buffer), SIZE_T_FORMAT, num_partition_sectors);
    simpleStrReplace((char *)fh.attrs.value,
                     "NUM_DISK_SECTORS",
                     (const char *) temp_buffer);
    simpleStrReplace((char *)fh.attrs.value,
                     ".",
                     "");

    if (strstr((char *)fh.attrs.value, "CRC32")) {
        simpleStrReplace((char *)fh.attrs.value,
                         "CRC32",
                         "");

        patch_value_len = strlen((char *)fh.attrs.value);
        comma_pos = strchr((char *)fh.attrs.value, ',');
        end_crc_pos = strrchr((char *)fh.attrs.value, ')');
        if (NULL == comma_pos || NULL == end_crc_pos)
        {
            logMessage("Invalid CRC patch value");
            MyErrorMessage(HANDLE_PATCH_FAILURE);
            return FIREHOSE_ERROR;
        }
        if (end_crc_pos < comma_pos) {
            return FIREHOSE_ERROR;
        }
        memscpy(temp_buffer,
                    sizeof(temp_buffer),
                    comma_pos + 1,
                    end_crc_pos - (comma_pos + 1));
        temp_buffer[end_crc_pos - (comma_pos + 1)] = '\0';
        //crc_start_sector
        crc_over_num_bytes = stringToNumber((const char *) temp_buffer, &num_conversion);
        if (FALSE == num_conversion)
        {
            logMessage("Failed to get crc_over_num_bytes");
            MyErrorMessage(HANDLE_PATCH_FAILURE);
            sendResponse(NAK);
            return FIREHOSE_ERROR;
        }
        memsmove(comma_pos, sizeof(temp_buffer),
                end_crc_pos,
                1 + fh.attrs.value + patch_value_len - (byte *)end_crc_pos);
        //parseExpression((char *)fh.attrs.value, &crc_start_sector);
	StringLength = sizeof(fh.attrs.value);
	MyParseExpression((char *)fh.attrs.value, StringLength, &crc_start_sector);
        logMessage("crc start sector %lld, over bytes %lld", crc_start_sector, crc_over_num_bytes);

        storage_device_read(
            fh.store_dev,
            0,
            fh.attrs.physical_partition_number,
            raw_data_buffer,
            crc_start_sector,
            (crc_over_num_bytes / fh.sector_size)
            + ((crc_over_num_bytes % fh.sector_size == 0) ? 0 : 1));
        patch_result = calc_crc32(raw_data_buffer, crc_over_num_bytes);
    }
    else {
        //parseExpression((char *)fh.attrs.value, &patch_result);
	StringLength = sizeof(fh.attrs.value);
	MyParseExpression((char *)fh.attrs.value, StringLength, &patch_result);
    }

    storage_device_read(fh.store_dev,
                        0,
                        fh.attrs.physical_partition_number,
                        raw_data_buffer,
                        fh.attrs.start_sector,
                        1);

    // TODO: clean this up a bit
    if (4 == fh.attrs.size_in_bytes)
        patch_result &= 0xFFFFFFFF;
    memscpy(raw_data_buffer + fh.attrs.byte_offset,
                fh.channel_buffer_capacity-fh.attrs.byte_offset,
                &patch_result,
                sizeof(SIZE_T));
    /*
    if (sizeof(patch_result) < fh.attrs.size_in_bytes)
    {
        if ((fh.attrs.byte_offset + fh.attrs.size_in_bytes) < sizeof(temp_buffer)) {
            memset(temp_buffer + fh.attrs.byte_offset + sizeof(patch_result),
                   0,
                   fh.attrs.size_in_bytes - sizeof(patch_result));
        }
    }
    */
    storage_device_write(fh.store_dev,
                       0,
                       fh.attrs.physical_partition_number,
                       raw_data_buffer,
                       fh.attrs.start_sector,
                       1);

    logMessage("Patched sector %lld with %08X", fh.attrs.start_sector, patch_result);

    return sendResponse(ACK);
}

static firehose_error_t handleGetDigest(void)
{
    // Variables to deal with raw data
    boolean retval = FALSE;
    SIZE_T sectors_to_send,
           bytes_to_send_to_layer;
    byte* raw_data_buffer;
    SIZE_T raw_data_buffer_sector_capacity;
    //int errno;
    struct __sechsh_ctx_s   context;
    //SHA256_CTX sha2_ctx;
    uint8 data_digest[32] = {0};
    // The log string size is currently based on
    // sizeof(data_digest) * 2 + strlen("SHA256 ") + 1
    // and some extra space
    char log_string[72] = {0};
    int written;
    int i = 0;
    SIZE_T sectors_done = 0;
    SIZE_T log_msg_every_sectors = 2048;
    SIZE_T log_start_sector, log_num_sectors;


    if (fh.attrs.start_sector == ATTR_INVALID_VAL || fh.attrs.num_partition_sectors == ATTR_INVALID_VAL)
    {
        if (fh.attrs.start_sector == ATTR_INVALID_VAL)
            logMessage("Attribute '%s' not provided (or -1)", "start_sector", ATTR_INVALID_VAL);    // not provided or invalid
        else
            logMessage("Attribute '%s' not provided (or -1)", "num_partition_sectors", ATTR_INVALID_VAL);   // not provided or invalid

        MyErrorMessage(HANDLE_GET_DIGEST_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if (fh.sector_size != fh.attrs.SECTOR_SIZE_IN_BYTES)
    {
        logMessage("Attribute 'SECTOR_SIZE_IN_BYTES'=%lld must be equal to disk sector size %lld", fh.attrs.SECTOR_SIZE_IN_BYTES, fh.sector_size);
        MyErrorMessage(HANDLE_GET_DIGEST_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    raw_data_buffer_sector_capacity = fh.channel_buffer_capacity / fh.attrs.SECTOR_SIZE_IN_BYTES;

    sechsharm_sha256_init (&context);

    //SHA256_Init(&sha2_ctx );


    // TODO: Clean this up. Read functionality should not know so much
    // about the buffers available
    raw_data_buffer = fh.channel_buffer[1 - fh.channel_buffer_to_use];

    log_start_sector = fh.attrs.start_sector;
    log_num_sectors = fh.attrs.num_partition_sectors;

    logMessage("Beginning HASHING disk data. This can take a while!!");

    while (fh.attrs.num_partition_sectors > 0) {
        sectors_to_send = MIN(fh.attrs.num_partition_sectors, raw_data_buffer_sector_capacity);
        bytes_to_send_to_layer = sectors_to_send * fh.attrs.SECTOR_SIZE_IN_BYTES;

        retval = storage_device_read(fh.store_dev,
                              0,
                              fh.attrs.physical_partition_number,
                              raw_data_buffer,
                              fh.attrs.start_sector,
                              sectors_to_send);

        if (retval == FALSE) {
            break;
        }
        else {
            fh.attrs.start_sector += sectors_to_send;
        }

        sechsharm_sha256_update(&context,
                        context.leftover,
                        &(context.leftover_size),
                        raw_data_buffer,
                        bytes_to_send_to_layer);
        //SHA256_Update(&sha2_ctx, raw_data_buffer, bytes_to_send_to_layer);


        fh.attrs.num_partition_sectors -= sectors_to_send;

        sectors_done += sectors_to_send;
        if (sectors_done >= log_msg_every_sectors) {
            sectors_done = 0;
            if (fh.attrs.num_partition_sectors > 0)
                logMessage("%lld sectors more to hash", fh.attrs.num_partition_sectors);
        }
    }
    if (retval == TRUE)
    {
        sechsharm_sha256_final (&context,
                        context.leftover,
                        &(context.leftover_size),
                        data_digest);
        //SHA256_Final(data_digest, &sha2_ctx);

        written = snprintf(log_string,
                       sizeof(log_string),
                       "%s",
                       "Digest ");

        while (written < sizeof(log_string) && i < sizeof(data_digest))
        {
            written += snprintf(log_string + written,
                                sizeof(log_string) - written,
                                "%02X",
                                data_digest[i]);
            i++;
        }

        logMessage("Hash start sector %lld num sectors %lld", log_start_sector, log_num_sectors);
        logMessage(log_string);
    }
    sendResponse(ACK);
    return FIREHOSE_SUCCESS;
}

static firehose_error_t handleGetDigestSHA256() {
    return handleGetDigest();
}


static firehose_error_t handleRead() {

#ifndef FEATURE_FIREHOSE_ENABLE_READ
    logMessage("Read operation not allowed");
    // ACK-ing here since Read is (usually) not
    // a critical operation
    return sendResponse(ACK);
#else

    // Let's declare the variables we care about
    SIZE_T read_fail_sector = 0,TotalSectorsToRead;

    // Variables to deal with raw data
    boolean retval = FALSE;
    response_t raw_data_status;
    SIZE_T sectors_to_send,
           bytes_to_send_to_layer;
    byte* raw_data_buffer;
    SIZE_T raw_data_buffer_sector_capacity;
    //int errno;
    SIZE_T original_start_sector = fh.attrs.start_sector;

    if (fh.attrs.start_sector == ATTR_INVALID_VAL || fh.attrs.num_partition_sectors == ATTR_INVALID_VAL)
    {
        if (fh.attrs.start_sector == ATTR_INVALID_VAL)
            logMessage("Attribute '%s' not provided (or -1)", "start_sector", ATTR_INVALID_VAL);    // not provided or invalid
        else
            logMessage("Attribute '%s' not provided (or -1)", "num_partition_sectors", ATTR_INVALID_VAL);   // not provided or invalid

        MyErrorMessage(STORAGE_READ_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    if (fh.sector_size != fh.attrs.SECTOR_SIZE_IN_BYTES)
    {
        logMessage("Attribute 'SECTOR_SIZE_IN_BYTES'=%lld must be equal to disk sector size %lld", fh.attrs.SECTOR_SIZE_IN_BYTES, fh.sector_size);
        MyErrorMessage(STORAGE_READ_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }
    raw_data_buffer_sector_capacity = fh.channel_buffer_capacity / fh.attrs.SECTOR_SIZE_IN_BYTES;

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
        AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"true\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();
/*
    sendResponseFields(
           ACK,
           1,
           "rawmode" ,'s', "true");
*/
    raw_data_status = ACK;
	
	TotalSectorsToRead = fh.attrs.num_partition_sectors;

    while (fh.attrs.num_partition_sectors > 0) {
        sectors_to_send = MIN(fh.attrs.num_partition_sectors, raw_data_buffer_sector_capacity);
        bytes_to_send_to_layer = sectors_to_send * fh.attrs.SECTOR_SIZE_IN_BYTES;

        // TODO: Clean this up. Read functionality should not know so much
        // about the buffers available
        raw_data_buffer = fh.channel_buffer[1 - fh.channel_buffer_to_use];

        if (raw_data_status == ACK) {
            retval = storage_device_read(fh.store_dev,
                              0,
                              fh.attrs.physical_partition_number,
                              raw_data_buffer,
                              fh.attrs.start_sector,
                              sectors_to_send);

            if (retval == FALSE) {
                raw_data_status = NAK;

                // We cannot send out a log message in the middle of Read
                // raw data mode because the host will interpret it as raw
                // data and that would throw off its calculation of the number
                // of bytes to expect, so we save the failed sector (since that
                // is the only point of failure), and send it out later
                read_fail_sector = fh.attrs.start_sector;
            }
            else {
                fh.attrs.start_sector += sectors_to_send;
            }
        }

        writeChannel(raw_data_buffer, bytes_to_send_to_layer);
        fh.attrs.num_partition_sectors -= sectors_to_send;

        /*
        if (fh.ack_raw_data == TRUE) {
            getNextPacket(&raw_data_buffer,
                          sizeof(fh.xml_buffer),
                          &bytes_read_in_layer);
        }
        */
    }


    if (NAK == raw_data_status)
    {
        logMessage("Read failed at sector %lld", read_fail_sector);
        MyErrorMessage(STORAGE_READ_FAILURE);
    }
	
    logMessage("Finished reading from sector address %lld to %lld", original_start_sector,(original_start_sector+TotalSectorsToRead));

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
        AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
        if(raw_data_status==ACK)
                AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        else
                AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();

/*
    sendResponseFields(
           raw_data_status,
           1,
           "rawmode" ,'s', "false");
*/
    return (raw_data_status == ACK) ? FIREHOSE_SUCCESS : FIREHOSE_ERROR;

#endif

}

static firehose_error_t handleProgram()
{
    // Variables to deal with raw data
    boolean retval                        = FALSE;
    firehose_error_t channel_read_retval  = FIREHOSE_SUCCESS;
    SIZE_T rx_length_sectors,TotalSectorsToProgram;
    response_t raw_data_status;
    SIZE_T sectors_to_read,
           bytes_to_read_from_layer,
           bytes_read_in_layer;
    byte* raw_data_buffer;
    SIZE_T raw_data_buffer_sector_capacity;
    SIZE_T  ack_every_counter = 0;
    volatile SIZE_T  i=0,j=0;
    volatile SIZE_T  WereDone = 0;

    if (fh.sector_size != fh.attrs.SECTOR_SIZE_IN_BYTES)
    {
        i = j; // for breakpoint
        logMessage("Attribute 'SECTOR_SIZE_IN_BYTES'=%lld must be equal to disk sector size %lld", fh.attrs.SECTOR_SIZE_IN_BYTES, fh.sector_size);
        MyErrorMessage(HANDLE_PROGRAM_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    i = j; // for breakpoint

    if (fh.attrs.SECTOR_SIZE_IN_BYTES == 0)
    {
        i = j; // for breakpoint
        logMessage("SECTOR_SIZE_IN_BYTES is 0");
        MyErrorMessage(HANDLE_PROGRAM_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

    i = j; // for breakpoint

    raw_data_buffer_sector_capacity = fh.channel_buffer_capacity / fh.attrs.SECTOR_SIZE_IN_BYTES;

    i = j; // for breakpoint

    if (fh.attrs.start_sector == ATTR_INVALID_VAL || fh.attrs.num_partition_sectors == ATTR_INVALID_VAL)
    {
        if (fh.attrs.start_sector == ATTR_INVALID_VAL)
            logMessage("Attribute '%s' not provided (or -1)", "start_sector", ATTR_INVALID_VAL);    // not provided or invalid
        else
            logMessage("Attribute '%s' not provided (or -1)", "num_partition_sectors", ATTR_INVALID_VAL);   // not provided or invalid

        MyErrorMessage(HANDLE_PROGRAM_FAILURE);
        sendResponse(NAK);
        return FIREHOSE_ERROR;
    }

	TotalSectorsToProgram = fh.attrs.num_partition_sectors;
    logMessage("start %lld, num %lld", fh.attrs.start_sector, TotalSectorsToProgram);

    InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
    AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
    AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"true\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
    sendTransmitBuffer();

    raw_data_status = ACK; // Init to ACK. If storage_device_write returns FALSE, then this becomes NAK

    while (fh.attrs.num_partition_sectors > 0)
    {
        debugMessage("TOP OF LOOP %lld to go",fh.attrs.num_partition_sectors);
        sectors_to_read          = MIN(fh.attrs.num_partition_sectors, raw_data_buffer_sector_capacity);

        bytes_to_read_from_layer = sectors_to_read * fh.attrs.SECTOR_SIZE_IN_BYTES;

        debugMessage("bytes_to_read_from_layer=%lld", bytes_to_read_from_layer);
        debugMessage("calling getNextPacket");
        channel_read_retval = getNextPacket(&raw_data_buffer, bytes_to_read_from_layer, &bytes_read_in_layer);
        //debugMessage("back from getNextPacket");
        debugMessage("toread bytes_to_read_from_layer=%lld bytes_read_in_layer=%lld", bytes_to_read_from_layer, bytes_read_in_layer);

        if (channel_read_retval != FIREHOSE_SUCCESS)
        {
            MyErrorMessage(HANDLE_PROGRAM_FAILURE);

            if (fh.validation_enabled == TRUE)
            {
                logMessage("Encountered RAW data transport error in validation mode.");
            }
            else
            {
                delaySeconds(10);

                InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
                AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
                AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" rawmode=\"false\" AttemptRetry=\"1\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
                sendTransmitBuffer();
            }
            return channel_read_retval;
        }

		if(bytes_read_in_layer==0)
		{
			logMessage("USB read has failed. Returned 0 bytes.");
			logMessage("Did you remember to set ZlpAwareHost='1' for Windows in your configure tag");
			logMessage("Did you remember to set ZlpAwareHost='0' for Linux in your configure tag");
			MyErrorMessage(HANDLE_PROGRAM_FAILURE);
			sendResponse(NAK);
			return FIREHOSE_ERROR;
		}

		// To be this we have read data from the channel
		
        if (bytes_read_in_layer > bytes_to_read_from_layer || bytes_read_in_layer % fh.attrs.SECTOR_SIZE_IN_BYTES != 0)
        {
            continue;
        }

        rx_length_sectors = bytes_read_in_layer / fh.attrs.SECTOR_SIZE_IN_BYTES;
		debugMessage("bytes_read_in_layer=%lld fh.attrs.SECTOR_SIZE_IN_BYTES=%lld", bytes_read_in_layer, fh.attrs.SECTOR_SIZE_IN_BYTES);
        debugMessage("rx_length_sectors=%lld fh.attrs.start_sector=%lld", rx_length_sectors, fh.attrs.start_sector);
		

        // We've got a packet, but before writing it QUEUE next packet if we need to

        if (fh.attrs.num_partition_sectors - rx_length_sectors > 0)
        {
           // To be here means we know we will need another packet, since we have fh.attrs.num_partition_sectors left
           // If fh.attrs.num_partition_sectors - rx_length_sectors is < 0, then our previously queued packet will take care of it

           // Below we queue for raw_data_buffer_sector_capacity 99% of the time.
           // except when (fh.attrs.num_partition_sectors - rx_length_sectors) is smaller than this (last request)
            debugMessage("calling queueNextPacket");
            queueNextPacket( MIN(fh.attrs.num_partition_sectors - rx_length_sectors, raw_data_buffer_sector_capacity) * fh.attrs.SECTOR_SIZE_IN_BYTES);
        }
        else
        {
           debugMessage("We are Done");
           WereDone = 1; // no need to queue anymore
        }


        // We've got a packet we can write, BUT, if any of the previous writes failed, just skip writing anything else
        // Remember we can't bail on this, since FIREHOSE protocol means the target will be blasting data at us the entire time

        if (raw_data_status == ACK)
        {
            // logMessage("Writing to address %d",
            //           fh.raw_data_address);
            retval = TRUE;

            if(!fh.attrs.SkipWrite)  //if (fh.skip_storage_writes == TRUE)
            {

#ifdef USE_FIRMWARE_BUFFER
                if(fh.attrs.BufferWrites == TRUE)
                {
                    SIZE_T Big_rx_length_sectors;
                    memscpy ( &BigFWBuffer[BigFWBufferCount], BIG_FW_BUFFER_SIZE, raw_data_buffer, bytes_read_in_layer );
                    BigFWBufferCount    += bytes_read_in_layer;

                    if(BigFWBufferCount>=BIG_FW_BUFFER_SIZE || WereDone)
                    {
                        // we have a full buffer
                        Big_rx_length_sectors = BigFWBufferCount/fh.attrs.SECTOR_SIZE_IN_BYTES;
                        retval = storage_device_write(fh.store_dev, 0, fh.attrs.physical_partition_number, BigFWBuffer, fh.attrs.start_sector, Big_rx_length_sectors);
                        fh.attrs.start_sector += Big_rx_length_sectors;
                        BigFWBufferCount = 0;   // reset to beginning
                    } // end of big buffer full
                }
                else
                {
                    retval = storage_device_write(fh.store_dev, 0, fh.attrs.physical_partition_number, raw_data_buffer, fh.attrs.start_sector, rx_length_sectors);
                    fh.attrs.start_sector += rx_length_sectors;
                } // end of if(fh.attrs.BufferWrites == TRUE)
#else
    //logMessage("fh.attrs.start_sector = %lld",fh.attrs.start_sector);
    //logMessage("rx_length_sectors = %lld",rx_length_sectors);
    retval = storage_device_write(fh.store_dev, 0, fh.attrs.physical_partition_number, raw_data_buffer, fh.attrs.start_sector, rx_length_sectors); // is rx_length_sectors==0?
    //logMessage("retval = 0x%X",retval);
    fh.attrs.start_sector += rx_length_sectors;
#endif
            } // end of if(!fh.attrs.SkipWrite)  //if (fh.skip_storage_writes == TRUE)

            if (retval == FALSE)
               raw_data_status = NAK;


        } // end if (raw_data_status == ACK)

        fh.attrs.num_partition_sectors -= rx_length_sectors;

        if(fh.attrs.AckRawDataEveryNumPackets > 0)
        {
            ack_every_counter++;
            if (ack_every_counter >= fh.attrs.AckRawDataEveryNumPackets)
            {
                logMessage("%lld sectors to go", fh.attrs.num_partition_sectors);
                sendResponse(raw_data_status);
                ack_every_counter = 0;
            }
        } // end if (fh.attrs.AckRawDataEveryNumPackets > 0)

        i = j; // for breakpoint

    } // end while (fh.attrs.num_partition_sectors > 0)

	// Note that start_sector gets incremented while programming, so below we subtract to indicate where we started from
    logMessage("Finished programming start_sector %lld and TotalSectorsToProgram %lld", (fh.attrs.start_sector),TotalSectorsToProgram);

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
        AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
        if(raw_data_status==ACK)
                AppendToBuffer(fh.tx_buffer,"<response value=\"ACK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        else
                AppendToBuffer(fh.tx_buffer,"<response value=\"NAK\" rawmode=\"false\" />\n</data>", FIREHOSE_TX_BUFFER_SIZE);
        sendTransmitBuffer();
/*
    sendResponseFields(
           raw_data_status,
           1,
           "rawmode" ,'s', "false");
*/
    return (raw_data_status == ACK) ? FIREHOSE_SUCCESS : FIREHOSE_ERROR;
}

static firehose_error_t handleBenchmark()
{
    SIZE_T i, j, trials = 1000;
    SIZE_T  start_time, end_time, average_time;
    uint8 temp_hash_value[32] = {0};
    byte* buffer = fh.channel_buffer[0];
    byte* buffer2= fh.channel_buffer[1];
    SIZE_T sector_size = fh.sector_size;
    SIZE_T buffer_size = fh.channel_buffer_capacity;

    // TODO: Do not reference channel_buffer[0] directly. This func should not have any knowledge
    // of how many buffers are in use

    if (fh.attrs.TestWritePerformance == TRUE)
    {
        logMessage("Going to test writes for lengths %lld to %lld for %lld trials. This can take a while.", sector_size, buffer_size, trials);

        storage_device_read(fh.store_dev, 0, 0, buffer, 0, buffer_size / sector_size);

        for (i = sector_size; i <= buffer_size; i = i * 2)
        {
            average_time = 0;

            start_time = get_time();
            for (j = 0; j < trials; j++)
            {
              storage_device_write(fh.store_dev, 0, 0, buffer, 0, i/sector_size);
            }
            end_time = get_time();
            average_time += (end_time - start_time);

            average_time = average_time / j;
            logMessage("Writing %lld bytes %ld us", i, average_time);
        }
    }

    if (fh.attrs.TestReadPerformance == TRUE)
    {
        logMessage("Going to test reads for lengths %lld to %lld for %lld trials. This can take a while.", sector_size, buffer_size, trials);
        for (i = sector_size; i <= buffer_size; i = i * 2)
        {
            average_time = 0;

            start_time = get_time();
            for (j = 0; j < trials; j++)
            {
              storage_device_read(fh.store_dev, 0, 0, buffer, 0, i/sector_size);
            }
            end_time = get_time();
            average_time += (end_time - start_time);

            average_time = average_time / j;
            logMessage("Reading %lld bytes %d us", i, average_time);
        }
    }

    if (fh.attrs.TestDigestPerformance == TRUE)
    {
        for (i = sector_size; i <= buffer_size; i = i * 2)
        {
            average_time = 0;
            for (j = 0; j < trials; j++)
            {
                start_time = get_time();
                PerformSHA256(buffer, i, temp_hash_value);
                end_time = get_time();
                average_time += (end_time - start_time);
            }
            average_time = average_time / j;
            logMessage("Hashing %lld bytes %lld times took %ld us on average", i, trials, average_time);
        }
    }

    if (fh.attrs.TestDDRValidity == TRUE)
    {
        for (j = 0; j <fh.attrs.trials; j++)
        {
            for(i=0;i<buffer_size;i++)
        	buffer[i] = ((i+j)&0xFF);

            writeChannel(buffer, buffer_size);	

            for(i=0;i<buffer_size;i++)
        	buffer2[i] = ((i+j)&0xFF);

            writeChannel(buffer2, buffer_size);	
        }
	
        logMessage("Done TestDDRValidity, pattern was simply i=0;i<%lld;i++ with buffer[i] = (i&0xFF); and trials=%lld",buffer_size,fh.attrs.trials);
    }

	fh.attrs.TestWritePerformance  = FALSE;
	fh.attrs.TestReadPerformance   = FALSE;
	fh.attrs.TestDigestPerformance = FALSE;
	fh.attrs.TestDDRValidity       = FALSE;

    return sendResponse(ACK);
}

firehose_tag_data_t firehose_tag_data[] = {
    {"program", handleProgram},
    {"configure", handleConfigure},
    {"nop", handleNop},				// Use this with Verbose="1", i.e. <NOP value="ping" Verbose="1" /> to turn on verbose logging for debug
#ifndef DEVICEPROGRAMMER_TINY
    {"firmwarewrite", handleFirmwareProgram},
    {"patch", handlePatch},
    {"setbootablestoragedrive", handleSetBootableStorageDrive},
    {"ufs", handleStorageExtras},
    {"emmc", handleStorageExtras},
    {"power", handlePower},
    {"benchmark", handleBenchmark},
    {"read", handleRead},
    {"getstorageinfo", handleGetStorageInfo},
    {"getsha256digest", handleGetDigestSHA256},
    {"erase", handleErase},
#ifdef FEATURE_DEVICEPROGRAMMER_PEEK_POKE
    {"peek", handlePeek},
    {"poke", handlePoke}
#endif
#endif
};

// This reads the next packet sent over USB and initializes the XML
// reader fh.xml_reader with it.
//
// Returns: FIREHOSE_SUCCESS if valid XML was received
//          FIREHOSE_ERROR on read error, invalid XML, or XML too large
//
// NOTE: How 'we' choose to validate the XML right now is not very generic.
// Hence this should not be put under the xml parser code
static firehose_error_t getXMLPacket() {
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

    memscpy(fh.xml_buffer, sizeof(fh.xml_buffer), packet, bytes_read);
    //xmlInitReader(&fh.xml_reader, fh.xml_buffer, bytes_read);

    i = 4; // for breakpoint

    return FIREHOSE_SUCCESS;
}

void initFirehoseTransport()
{
    usb_al_bulk_init();
}

// Send all the functions in the function table in separate log messages.
//
// This gives the user information as well as partially serving to identify the
// Firehose version.
void sendSupportedFunctions(void)
{
    int i;

        InitBufferWithXMLHeader(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE);            // adds XML header only
        AppendToBuffer(fh.tx_buffer,"<data>\n", FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"<log value=\"Supported Functions: ", FIREHOSE_TX_BUFFER_SIZE);


    for (i = 0; i < sizeof(firehose_tag_data) / sizeof(firehose_tag_data[0]); i++)
    {
        //logMessage("supported function: '%s'", firehose_tag_data[i].tag_name);
        AppendToBuffer(fh.tx_buffer,firehose_tag_data[i].tag_name, FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer," ", FIREHOSE_TX_BUFFER_SIZE);

    }

        AppendToBuffer(fh.tx_buffer,"\"/>\n", FIREHOSE_TX_BUFFER_SIZE);
        AppendToBuffer(fh.tx_buffer,"</data>", FIREHOSE_TX_BUFFER_SIZE);

        sendTransmitBuffer();

} // end void sendSupportedFunctions()

// Send the chip's serial number. This gives the user information as well as
// serving as a signal that USB is initialized and Firehose is ready to
// receive commands.
//
// Also, if DEVICEPROGRAMMER_SERIAL_NUM is specified in build, Firehose will
// halt if actual serial num does not match.
void sendAndAuthSerialNum(void)
{
    uint32 chip_serial_num = getChipSerialNum();

#ifdef DEVICEPROGRAMMER_SERIAL_NUM
    if (chip_serial_num != DEVICEPROGRAMMER_SERIAL_NUM)
    {
        for (;;)
        {
            logMessage("Serial number specified in build does not match actual serial number: %u (0x%x).", chip_serial_num, chip_serial_num);
            logMessage("Build serial num: %u (0x%x)", DEVICEPROGRAMMER_SERIAL_NUM, DEVICEPROGRAMMER_SERIAL_NUM);
            MyErrorMessage(SERIAL_NUM_OF_DEVICE_INCORRECT);
            delaySeconds(2);
        }
    }
#endif

    logMessage("Chip serial num: %u (0x%x)", chip_serial_num, chip_serial_num);
}


char OPENING_DATA_TAG[] = "<data>";
char CLOSING_DATA_TAG[] = "</data>";
char OPENING_PATCHES_TAG[] = "<patches>";
char CLOSING_PATCHES_TAG[] = "</patches>";

tag_handler_t CurrentHandlerFunction;   // this will always point to latest TAG function, i.e. handleConfigure()

static SIZE_T CopyString(char *Dest, char *Source, SIZE_T  Dstart, SIZE_T  Sstart, SIZE_T  length, SIZE_T DestSize, SIZE_T SourceSize)
{
        SIZE_T  i = 0;
        char Temp;

	if(Dest==NULL)				 { return 0; }	// Dest is null
	if(Source==NULL)			 { return 0; }	// Source is null
	if(Dstart+length>DestSize-1) { return 0; }	// string to copy over is too big for destination
	if(Sstart+length>SourceSize) { return 0; }	// range to copy is beyond source string
	if(length==0)				 { return 0; }	// nothing to copy

	//logMessage("CopyString(0x%X, 0x%X, %ld, %ld, %ld, %ld, %ld)",Dest,Source,Dstart,Sstart,length,DestSize,SourceSize);
		
        for(i=0;i<length;i++)
        {
           Temp = *(Source+Sstart+i);

            *(Dest+Dstart+i) = Temp;
        } // end i

        *(Dest+Dstart+i) = '\0';    // NULL

		return length;
}

void ResetAllAttributeAssignFlags(void)
{
        SIZE_T  i;

		for(i=0;i<(SIZE_T)ReturnNumAttributes();i++)
			AllAttributes[i].Assigned = 0;
}


int AssignAttribute(char *NewAttrName, char *NewAttrValue, SIZE_T NewAttrValueLen)
{
        volatile SIZE_T  i,j=0,Matched=0;
        SIZE_T TempValue;
        unsigned int uTempValue;
        int nTempValue;
        char cTempValue;
        //printf("\n\nIn AssignAttribute(%s,%s)\n",NewAttrName,NewAttrValue);
	
        //logMessage("In AssignAttribute(%s,%s) and fh.attrs.Verbose=0x%X",NewAttrName,NewAttrValue,fh.attrs.Verbose);

        for(i=0;i<sizeof(AllAttributes)/sizeof(struct Attributes_Struct);i++)
        {
                if (strncasecmp(NewAttrName, AllAttributes[i].Name, strlen((const char *)AllAttributes[i].Name)) == 0)
                {
                        Matched = 1;
                        
                        if(fh.attrs.Verbose == TRUE)
                            logMessage("Recognized Attribute Number %lld ('%s') with value '%s' type is '%c'",i,NewAttrName,NewAttrValue,AllAttributes[i].Type);

                        //printf("MATCHED - '%s'\n",AllAttributes[i].Name);
			if( CopyString(AllAttributes[i].Raw, NewAttrValue, 0, 0, strlen(NewAttrValue), sizeof(AllAttributes[i].Raw), NewAttrValueLen) == 0)
			{
				dbg(LOG_ERROR, "1 Failed to copy string '%s' of length %ld bytes into AllAttributes[%ld].Raw of size %ld bytes for '%s'",NewAttrValue,strlen(NewAttrValue),i,sizeof(AllAttributes[i].Raw),NewAttrName);
				return 1;
			}
                        //strncpy( AllAttributes[i].Raw, NewAttrValue,sizeof(AllAttributes[i].Raw) );
                        j = i; // for breakpoint
                        if( AllAttributes[i].Type == 'i' || AllAttributes[i].Type == 'w' || AllAttributes[i].Type == 'n' || AllAttributes[i].Type == 'b')
                        {
                            boolean num_conversion;

                            TempValue = stringToNumber((const char *) AllAttributes[i].Raw, &num_conversion);
                            if (FALSE == num_conversion)
                            {
                                dbg(LOG_INFO,"Call to stringToNumber failed on attribute '%s' with value '%s'",NewAttrName,AllAttributes[i].Raw);
                                return 1;	// error
                            }

                            //if(fh.attrs.Verbose == TRUE)
                            //    logMessage("Converted to TempValue = %lld",TempValue);

                            if(CurrentHandlerFunction!=handleFirmwareProgram && CurrentHandlerFunction!=handleRead)
                            {
                                // When it's handleFirmwareProgram we allow SECTOR_SIZE_IN_BYTES=1
                                // handleRead can allow page size to be a non multiple of 512
                                if((TempValue % AllAttributes[i].MultipleOf == 0))
                                {
                                   // AllIsWell = 1;
                                }
                                else
                                {
                                   dbg(LOG_INFO,"Attribute '%s' is not a multiple of %i",NewAttrName,AllAttributes[i].MultipleOf);
                                   return 1;	// error
                                }
                            }

                            if( AllAttributes[i].Max != 0 )
                            {
                               // Need to check against max value
                               if( TempValue <= AllAttributes[i].Max )
                               {
                                  //AllIsWell = 1;
                               }
                               else
                               {
                                  dbg(LOG_INFO,"Attribute '%s' is larger than %i",NewAttrName,AllAttributes[i].Max);
                                  return 1;	// error
                               }
                            }

                            if(AllAttributes[i].Type == 'w')
                            {
                                //if(fh.attrs.Verbose == TRUE)
                                //    logMessage("Assigning Var %d ('%s') as UNSIGNED INT %lld",i,NewAttrName,TempValue);
                                uTempValue = (unsigned int)TempValue;

                                *((unsigned int *)AllAttributes[i].pValue) = (unsigned int)uTempValue;
                            }
                            else if(AllAttributes[i].Type == 'n')
                            {
                                //if(fh.attrs.Verbose == TRUE)
                                //    logMessage("Assigning Var %lld ('%s') as BYTE as %lld",i,NewAttrName,TempValue);
                                nTempValue = (short)TempValue;
                                *((short *)AllAttributes[i].pValue) = (short)nTempValue;
                            }
                            else if(AllAttributes[i].Type == 'b')
                            {
                                //if(fh.attrs.Verbose == TRUE)
                                //    logMessage("Assigning Var %lld ('%s') as BYTE as %lld",i,NewAttrName,TempValue);
                                cTempValue = (char)TempValue;
                                *((char *)AllAttributes[i].pValue) = (byte)cTempValue;
                            }
                            else
                            {
                                //if(fh.attrs.Verbose == TRUE)
                                //    logMessage("Assigning Var %lld ('%s') as SIZE_T as %lld",i,NewAttrName,TempValue);
                                *((SIZE_T *)AllAttributes[i].pValue) = (SIZE_T)TempValue;
                            }

                        }
                        else if( AllAttributes[i].Type == 's' )
                        {
                           j = i; // for breakpoint
                           //AllIsWell = 1;

			if( CopyString(AllAttributes[i].pStr, NewAttrValue, 0, 0, strlen(NewAttrValue), AllAttributes[i].SizeOfpStr, NewAttrValueLen)  == 0)
			{
				dbg(LOG_ERROR, "2 Failed to copy string '%s' into AllAttributes[%ld].pStr",NewAttrValue,i);
				return 1;
			}

                           //strncpy( AllAttributes[i].pStr,NewAttrValue,sizeof(AllAttributes[i].Raw) );
                           j = i; // for breakpoint
                        }
                        // else we have the special 'x' case, handled later if Assigned has been set
                        j = i; // for breakpoint
                        AllAttributes[i].Assigned = 1;

                        break;
                }       // end of comparing attribute names
        } // end of looping through all attributes

        if(Matched==0)
        {
            if(fh.attrs.Verbose == TRUE)
                dbg(LOG_INFO,"IGNORING UNRECOGNIZED Attribute '%s' with value '%s'",NewAttrName,NewAttrValue);

            j = i;	// for breakpoint
        }

        return 0;
}


SIZE_T IsEmptySpace(char c)
{
	if( c == 0xA ) { return 1; }
	if( c == 0xD ) { return 1; }
	if( c == 0x9 ) { return 1; }
	if( c == 0x20) { return 1; }

	return 0;
}


char * RemoveEverythingButTags(char *Packet, SIZE_T  CurrentPacketLoc, SIZE_T MaxPacketSize)
{
	SIZE_T  PacketLength,PacketLoc=0,i;
	char *pch;
	long FoundRightBrace=-1,FoundForwardSlash=-1,Found=0;

	if(CurrentPacketLoc>=MaxPacketSize)
		return Packet; // nothing to do

    PacketLength= strlen((const char *)Packet);

	if((!PacketLength) || (PacketLength>=MaxPacketSize))
		return Packet; // should be impossible

	for(i=0;i<PacketLength;i++)
	{
		if(Found==0)
		{
			if(i+3<PacketLength)
			{
				if(Packet[i]=='<' && Packet[i+1]=='!' && Packet[i+2]=='-' && Packet[i+3]=='-')	// protected by if(i+3<PacketLength) above
				{
					Found = 1;
					Packet[i] = ' '; Packet[i+1] = ' '; Packet[i+2] = ' '; Packet[i+3] = ' '; 
					i+=3;
				}
			}
		} // end of if(Found==0)
		else
		{
			// we are inside of a comment
			if(i+2<PacketLength)
			{
				if(Packet[i]=='-' && Packet[i+1]=='-' && Packet[i+2]=='>')	// protected by if(i+2<PacketLength) above
				{
					Found = 0;
					Packet[i] = ' '; Packet[i+1] = ' '; Packet[i+2] = ' '; 
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
		if(pch==NULL) { break; }

		// to be this far we found "xml version"
		// Now look slightly beyond that

		pch = strstr(pch, ">");				// is now pointing to the beginning of the file
		if(pch!=NULL) //'\0')					// pch = "<configuration> <options> DOWNLOAD_PROTOCOL       = FIREHOSE etc etc
		{
			memset(Packet,0x20,pch-&Packet[PacketLoc]+1);	// this removes <?xml version="1.0" ?>
		}

		// We could have more than 1 XML file here
		pch = strstr(Packet, "xml version");
		if((pch!=NULL) && (pch > Packet))
		{
			PacketLength = pch-Packet; // now length updated to start of next XML
		}


		// find last tag name
		// find last tag name
		for(i=PacketLength-1;i>0;i--)
		{
			if( Packet[i] == '>' ) { FoundRightBrace = i; }

			if(FoundRightBrace>0)
				if( Packet[i] == '/' ) { FoundForwardSlash = i; }

			if(FoundRightBrace>0 && FoundForwardSlash>0)
			{
				if( Packet[i] == '<' )
				{
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
		//strncpy(CurrentTagName,&Packet[FoundForwardSlash],FoundRightBrace-FoundForwardSlash+1);	// CurrentTagName = "/data>" OR "/configuration>" etc etc

		//CurrentTagName[FoundRightBrace-FoundForwardSlash+1] = '\0';

		memset(&Packet[FoundForwardSlash-1],0x20,strlen(CurrentTagName)+1);	// this takes out </configuration> OR </data> at the end of the file

		CurrentTagName[0] = '<';							// CurrentTagName = "<data>" OR "<configuration>" etc etc

		pch = strstr(Packet, CurrentTagName);				// is now pointing to the beginning of the file
		if(pch!=NULL) //'\0')					// pch = "<configuration> <options> DOWNLOAD_PROTOCOL       = FIREHOSE etc etc
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

	}while(1); // end of looking for "xml version"

	return Packet;
}

SIZE_T  DetermineTag(char *Packet, SIZE_T  CurrentPacketLoc, SIZE_T MaxPacketSize)
{
    volatile SIZE_T  i=0;
	SIZE_T  PacketLength;
    int CurrentTag = -1;
    char *pch;
	long FoundRightBrace=-1;

	if(CurrentPacketLoc>=MaxPacketSize)
		return 0;	// out of packet

	Packet = RemoveEverythingButTags(Packet,CurrentPacketLoc, MaxPacketSize);
    // Step 1. String away header
    // Step 2. Strip away <data> tags
    // step 3. Get tag_name
    // step 4. Get attributes
    PacketLength= strlen((const char *)Packet);

	if(PacketLength>=MaxPacketSize)
		return 0;	// should be impossible

		
	ResetAllAttributeAssignFlags();
	
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
        return 0;	// not formed correctly
    }

    CurrentPacketLoc++;    // move past the above opening <

	// Could be one solid tag like <options>, test by looking for spaces *before* seeing a '>'
	FoundRightBrace = -1;
	for(i=CurrentPacketLoc;i<PacketLength;i++)
	{
		if( Packet[i] == '>' ) { FoundRightBrace = i; break;}
		if( Packet[i] == ' ' ) { break;}
	}

	if(FoundRightBrace>0)
	{
		// this is something like <options> some text </options>
		ParseAttributes = 0;	// need to parse the strings

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
			return 0;	// not formed correctly
		}

		if( pch-&Packet[CurrentPacketLoc] > MAX_TAG_NAME_LENGTH )
		{
			logMessage("ERROR: The XML TAG is too long (%d chars) only %d chars allowed",(pch-&Packet[CurrentPacketLoc]),MAX_TAG_NAME_LENGTH);
			return 0;	// not formed correctly
		}


		CopyString(NewTagName, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewTagName), MaxPacketSize );   // NewTagName has the TAG now
		RemoveBannedChars(NewTagName); // chars like " < > are replaced by _

		CurrentPacketLoc += strlen((const char *)NewTagName);
		CurrentPacketLoc++;    // move past the above opening space we confirmed exists above

	}

	for (i = 0; i < sizeof(firehose_tag_data) / sizeof(firehose_tag_data_t); i++)
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
    char NewAttrValue[MAX_TAG_ATTR_LENGTH];
    char *pch;

	if(CurrentPacketLoc>=MaxPacketSize)
		return 0;	// ran out of packet

    // step 4. Get attributes
    PacketLength    = strlen((const char *)Packet); 
    // Packet[CurrentPacketLoc] should be at the first letter of the attribute now
    // They all look like this attribute1="value1" attribute2="value2"
    // Meaning only spaces seperate them 

	if(PacketLength>=MaxPacketSize)
		return 0;	// should be impossible

    AttributesFound = 0;

	while(CurrentPacketLoc < PacketLength)
    {
        pch = strstr(&Packet[CurrentPacketLoc], "=");          // Find an equals sign
        if(pch==NULL) //'\0')   // if null, we didn't find it
        {
            dbg(LOG_ERROR,"XML not formed correctly. Could not find '=' character");
            return 0;	// not formed correctly
        }

        if( pch-&Packet[CurrentPacketLoc] > MAX_TAG_ATTR_LENGTH )
        {
            dbg(LOG_ERROR,"The value for XML attribute is too long (%d chars) only %d chars allowed",(pch-&Packet[CurrentPacketLoc]),MAX_TAG_ATTR_LENGTH);
            return 0;	// not formed correctly
        }

        CopyString(NewAttrName, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewAttrName), MaxPacketSize );  // NewAttrName has the ATTR now

        RemoveBannedChars(NewAttrName); // chars like " < > are replaced by _

        CurrentPacketLoc += strlen((const char *)NewAttrName);
        CurrentPacketLoc++;    // move past the = sign

        if(Packet[CurrentPacketLoc]!='"')
        {
            dbg(LOG_ERROR,"XML not formed correctly. Expected one &quot; character at loc %d",CurrentPacketLoc);
            return 0;	// not formed correctly
        }

        CurrentPacketLoc++;    // Before "value" and now we move past the " sign, all that is left now is the actual value"

        pch = strstr(&Packet[CurrentPacketLoc], "\"");         // Find closing "

        if(pch==NULL) //'\0')   // if null, we didn't find it
        {
            dbg(LOG_ERROR,"XML not formed correctly. Expected one &quot; character at loc %d",CurrentPacketLoc);
            return 0;	// not formed correctly
        }

        if( pch-&Packet[CurrentPacketLoc] > MAX_TAG_ATTR_LENGTH )
        {
            dbg(LOG_ERROR,"The value for XML attribute '%s' is too long (%d chars) only %d chars allowed",NewAttrName,(pch-&Packet[CurrentPacketLoc]),MAX_TAG_ATTR_LENGTH);
            return 0;	// not formed correctly
        }

        /* If the length of the string is zero, the attribute is not assigned. */
        if(pch-&Packet[CurrentPacketLoc] > 0)
        {
          CopyString(NewAttrValue, Packet, 0, CurrentPacketLoc,   pch-&Packet[CurrentPacketLoc], sizeof(NewAttrValue), MaxPacketSize ); // NewAttrValue has the ATTR value now
          RemoveBannedChars(NewAttrValue); // chars like " < > are replaced by _

          AttributesFound++;

          // FIGURE OUT WHICH ATTRIBUTE AND ASSIGN VALUE

          if( AssignAttribute(NewAttrName, NewAttrValue, sizeof(NewAttrValue)) != 0 )
          {
            dbg(LOG_ERROR,"AssignAttribute failed");
            return 0;	// not formed correctly
          }

          CurrentPacketLoc += strlen((const char *)NewAttrValue);
        }
        CurrentPacketLoc++;    // move past the closing quote " sign

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

#define BYTES_PER_KB 1024

static SIZE_T  ParseComplicatedAttributes(void)
{
        volatile SIZE_T  i,j;

		for(i=0;i<(SIZE_T)ReturnNumAttributes();i++)
		{
            j = i;    // for breakpoint

            if(AllAttributes[i].Assigned==0)
                continue;	// variable wasn't even assigned, so no point checking


            if(CurrentHandlerFunction==handleStorageExtras)
            {
                // This is a special case, where the <ufs> or <emmc> tags are used and variables are sent
                // over multiple packets. In this case the struct UFS_LUN_Var is used as for temporary holding
                // and these values need to be moved to storage_extras.ufs_extras.unit[ 0 ].bLUEnable
                j = i; // for breakpoint
            }
            else if(AllAttributes[i].Type == 'i' && AllAttributes[i].Type == 'b' && AllAttributes[i].Type == 'w')
                continue;	// integer attributes are not complicated, Only want 'x' or 's'


            j = i+1;    // for breakpoint

            if (strncasecmp(AllAttributes[i].Name, "start_sector",strlen("start_sector")) == 0)
            {
                //printf("MATCHED - '%s'\n",AllAttributes[i].Name);

                j = i;    // for breakpoint

                if (parseSectorValue(AllAttributes[i].Raw, sizeof(AllAttributes[i].Raw), &fh.attrs.start_sector, fh.attrs.physical_partition_number, "start_sector") == FALSE)
                {
                    logMessage("parseSectorValue could not handle start_sector value");
                    return FIREHOSE_ERROR;
                }

                j = i;    // for breakpoint

            }  // end of looking for start_sector

            if (strncasecmp(AllAttributes[i].Name, "num_partition_sectors",strlen("num_partition_sectors")) == 0)
            {
                //printf("MATCHED - '%s'\n",AllAttributes[i].Name);

                j = i;    // for breakpoint

                if (parseSectorValue(AllAttributes[i].Raw, sizeof(AllAttributes[i].Raw), &fh.attrs.num_partition_sectors, fh.attrs.physical_partition_number, "num_partition_sectors") == FALSE)
                {
                    logMessage("parseSectorValue could not handle num_partition_sectors value");
                    return FIREHOSE_ERROR;
                }

                j = i;    // for breakpoint

            }  // end of looking for num_partition_sectors
// =================================================================

            if (strncasecmp(AllAttributes[i].Name, "MemoryName", strlen("MemoryName")) == 0)
            {
                //printf("MATCHED - '%s'\n",AllAttributes[i].Name);

                j = i;    // for breakpoint


               // convert memory name to enum value
               if (strncasecmp( AllAttributes[i].Raw, "emmc", strlen("emmc") ) == 0)
               {
                   fh.attrs.storage_type = STORAGE_DEVICE_TYPE_MMC;
                   fh.sector_size = 512; // for eMMC

                   i = j;
               }
               else if (strncasecmp( AllAttributes[i].Raw, "ufs", strlen("ufs") ) == 0)
               {
                   fh.attrs.storage_type = STORAGE_DEVICE_TYPE_UFS;
                   fh.sector_size = 4096; // for UFS
                   i = j;
               }
               else if (strncasecmp( AllAttributes[i].Raw, "spinor", strlen("spinor") ) == 0)
               {
                   fh.attrs.storage_type = STORAGE_DEVICE_TYPE_SPI_NOR;
                   fh.sector_size = 4096;
                   i = j;
               }
               else
               {
                   logMessage("Invalid storage type: %s", (char *)AllAttributes[i].Raw);
                   return FIREHOSE_ERROR;
               }

                j = i;    // for breakpoint
            }  // end of looking for MemoryName
// ==================================================================
            if (strncasecmp(AllAttributes[i].Name, "LUNum",strlen("LUNum")) == 0)
            {
                volatile SIZE_T  Temp1 = 0;
                volatile SIZE_T  Temp2 = 0;

                if(CurrentHandlerFunction!=handleStorageExtras) { continue; }

                j = i;    // for breakpoint

                Temp1 = UFS_LUN_Var_Struct.LUNum;

                // All attributes for this LUN would have also been assigned
                Temp2 = UFS_LUN_Var_Struct.bLUEnable;				storage_extras.ufs_extras.unit[ Temp1 ].bLUEnable           = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bBootLunID;				storage_extras.ufs_extras.unit[ Temp1 ].bBootLunID          = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bLUWriteProtect;			storage_extras.ufs_extras.unit[ Temp1 ].bLUWriteProtect     = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bMemoryType;				storage_extras.ufs_extras.unit[ Temp1 ].bMemoryType         = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bDataReliability;		storage_extras.ufs_extras.unit[ Temp1 ].bDataReliability    = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bLogicalBlockSize;		storage_extras.ufs_extras.unit[ Temp1 ].bLogicalBlockSize   = Temp2;
                Temp2 = UFS_LUN_Var_Struct.bProvisioningType;		storage_extras.ufs_extras.unit[ Temp1 ].bProvisioningType   = Temp2;
                Temp2 = UFS_LUN_Var_Struct.wContextCapabilities;	storage_extras.ufs_extras.unit[ Temp1 ].wContextCapabilities= Temp2;

                // We allow user to enter size_in_KB but the real attribute is dNumAllocUnits
                Temp2 = UFS_LUN_Var_Struct.size_in_KB;

                storage_extras.ufs_extras.unit[ Temp1 ].dNumAllocUnits = Temp2;	// for now, dNumAllocUnits *is* size_in_KB until we call ufs_commit_extras()

                memset(&UFS_LUN_Var_Struct,0,sizeof(UFS_LUN_Var_Struct));	// clear this out for next run

                j = i;    // for breakpoint

            }  // end of looking for start_sector
// =================================================================
// ==================================================================

            if (strncasecmp(AllAttributes[i].Name, "commit",strlen("commit")) == 0)
            {
                //printf("MATCHED - '%s'\n",AllAttributes[i].Name);

                // Need to update this value

                j = i;    // for breakpoint

                if (strncasecmp(AllAttributes[i].Raw, "true",strlen("true")) == 0)
                    fh.attrs.commit = 1;
                else if (strncasecmp(AllAttributes[i].Raw, "1",strlen("1")) == 0)
                    fh.attrs.commit = 1;
                else
                    fh.attrs.commit = 0;

                j = i;    // for breakpoint

            }  // end of looking for start_sector
// =================================================================

        } // end for i

        return FIREHOSE_SUCCESS;

} // end SIZE_T  ParseComplicatedAttributes(void)

void handleResettingAttributesBasedOnTag(void)
{
    if(CurrentHandlerFunction == handleConfigure)
    {
        //fh.skip_storage_writes  = FALSE;
        //fh.ack_raw_data_every   = 0;
        //fh.hash_in_non_secure   = FALSE;


        fh.attrs.SkipWrite                  = FALSE;
        fh.attrs.BufferWrites               = FALSE;
        //fh.attrs.AckRawData                 = FALSE;
        fh.attrs.AckRawDataEveryNumPackets  = 0;
        fh.attrs.AlwaysValidate             = FALSE;    // fh.hash_in_non_secure
        //fh.attrs.Verbose                    = FALSE;
        //fh.attrs.read_back_verify           = FALSE;
        fh.attrs.SkipStorageInit            = FALSE;
        fh.attrs.SkipSettingMinClocks       = FALSE;
        fh.attrs.SkipSettingMaxClocks       = FALSE;
        fh.attrs.actual_size_in_bytes       = 0;
    }
	else if(CurrentHandlerFunction == handleStorageExtras)
	{
		fh.attrs.commit = 0;	// user sent <ufs or <emmc, so need to ensure they set the commit themselves
	}
    //else if(CurrentHandlerFunction == handleNop)
    //{
    //    etc etc
    //}



} // end of void handleResettingAttributesBasedOnTag(void);

/*
 * The main entry point after initialization in deviceprogrammer_initialize.c.
 * It is called by deviceprogrammer_entry().
 *
 * To add a new command to Firehose, define it above and add it to the function
 * table: firehose_tag_data.
 */
 
//#include "CeTL_Comdef.h"
//#include "CeML.h"
//#include "CeTL_Hash.h"
//#include "CeTL_Env.h"

static void InitAttributes(void)
{
	fh.attrs.MaxPayloadSizeToTargetInBytes 			= 131072; //ONE_MEGABYTE;
	fh.attrs.MaxPayloadSizeToTargetInBytesSupported = 32768; //ONE_MEGABYTE;
	fh.attrs.MaxPayloadSizeFromTargetInBytes		= 8192; //ONE_MEGABYTE;
	fh.attrs.Verbose								= 0;
	fh.attrs.MaxDigestTableSizeInBytes				= 8192;
	fh.attrs.AckRawDataEveryNumPackets				= 0;
	fh.attrs.delayinseconds							= 1;
	fh.attrs.address64								= 0;
	fh.attrs.value64								= 0;
	fh.attrs.storagedrive							= 0;
	fh.attrs.physical_partition_number				= 0;
	fh.attrs.SECTOR_SIZE_IN_BYTES					= 512;
	fh.attrs.byte_offset							= 0;
	fh.attrs.physical_partition_number				= 0;
	fh.attrs.size_in_bytes							= 0;
	fh.attrs.num_partition_sectors					= 0;
	fh.attrs.file_sector_offset						= 0;

	fh.attrs.ZlpAwareHost							= 1;
	fh.attrs.SkipWrite								= 0;
	fh.attrs.BufferWrites							= 0;
	//fh.attrs.AckRawData								= 0;
	fh.attrs.AlwaysValidate							= 0;
									 
	//fh.attrs.display								= 0;
	//fh.attrs.read_back_verify						= 0;
	fh.attrs.TestWritePerformance					= 0;
	fh.attrs.TestReadPerformance					= 0;
	fh.attrs.TestDigestPerformance					= 0;
	fh.attrs.TestDDRValidity                        = 0;
	fh.attrs.SkipStorageInit						= 0;
	fh.attrs.SkipSettingMinClocks					= 0;
	fh.attrs.SkipSettingMaxClocks					= 0;
	fh.attrs.actual_size_in_bytes					= 0;

	fh.attrs.start_sector							= 0;
	
	if( CopyString(fh.attrs.MemoryName, "eMMC", 0, 0, sizeof("eMMC"),sizeof(fh.attrs.MemoryName),sizeof("eMMC")) == 0)
	{
		dbg(LOG_ERROR, "Failed to copy '%s' of length %"SIZE_T_FORMAT" bytes into fh.attrs.MemoryName","eMMC",strlen("eMMC"));
		//ExitAndShowLog(1);
	}
	
}

void main_firehose(void)
{
    volatile SIZE_T  PacketLoc = 0, BreakPoint = 0;

    dbg(LOG_INFO,"Binary build date: %s @ %s", __DATE__, __TIME__);

	InitAttributes();
	
//    
//    CeTLHashTests();
//    
    sendAndAuthSerialNum();     // sent again in handleNop
    sendSupportedFunctions();   // sent again in handleNop

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
		
        PacketLoc = DetermineTag((char *)fh.xml_buffer, PacketLoc, FIREHOSE_XML_BUFFER_SIZE);		// This sets CurrentHandlerFunction()

        // PacketLoc should be past the xml and data tags, pointing at the 1st attribute
        // So if PacketLoc is still it 0, something went wrong

        if(PacketLoc==0) {  sendResponse(NAK);          continue;        }


        // Based on the TAG above, some variables need to be reset
        handleResettingAttributesBasedOnTag();


       // To be this far fh.xml_buffer[PacketLoc] is pointing to the first char of the first attribute
        PacketLoc = DetermineAttributes((char *)fh.xml_buffer, PacketLoc, FIREHOSE_XML_BUFFER_SIZE);

        // PacketLoc should now be past all attributes and pointing at the />
        // So if PacketLoc is still it 0, something went wrong

        if(PacketLoc==0) {  sendResponse(NAK);          continue;        }

        // At this point some attributes will need additional processing before
        // we call the Tag Handler function
        if(ParseComplicatedAttributes()==FIREHOSE_ERROR)    // i.e. start_sector="NUM_DISKSECTORS-33."
        {  sendResponse(NAK);          continue;        }

        BreakPoint = 2;

        // Below is the function pointer, i.e. tag_handler_t CurrentHandlerFunction;
        CurrentHandlerFunction();
    }
}

void AppendToBuffer(byte *MyBuffer, char *buf, SIZE_T MaxBufferSize)
{
   size_t SpaceLeft, CharsToAdd = 0;
   size_t Length;

   Length       = strlen((const char *)MyBuffer);
   CharsToAdd   = strlen((const char *)buf);    // size of string to append

   //SpaceLeft = FIREHOSE_TX_BUFFER_SIZE - Length - XML_TAIL_LENGTH;      // tx_buffer is transmit_buffer of size FIREHOSE_TX_BUFFER_SIZE
   SpaceLeft = MaxBufferSize - Length - XML_TAIL_LENGTH;      // tx_buffer is transmit_buffer of size FIREHOSE_TX_BUFFER_SIZE
   

   if(CharsToAdd > SpaceLeft) { return; } // too big to add this

   // NOTE: If you're *not* seeing your messages, increase the size of transmit_buffer[FIREHOSE_TX_BUFFER_SIZE]
   //       or break up your logging

   memscpy((MyBuffer+Length), MaxBufferSize, buf, CharsToAdd);
   MyBuffer[Length+CharsToAdd] = '\0';

} // end void AppendToBuffer(byte *MyBuffer, char *buf)


/*
void InitTXBufferWithXMLHeader(void)
{
   memset(fh.tx_buffer, 0x0, FIREHOSE_TX_BUFFER_SIZE);
   memscpy(fh.tx_buffer, FIREHOSE_TX_BUFFER_SIZE, xml_header, XML_HEADER_LENGTH);
} // end void InitTXBufferWithXMLHeader(void)
*/
void InitBufferWithXMLHeader(byte *MyBuffer, SIZE_T Length)
{
   memset(MyBuffer, 0x0, Length);
   memscpy(MyBuffer, Length, xml_header, XML_HEADER_LENGTH);
   //MyBuffer[XML_HEADER_LENGTH] = '\0';
} // end void InitBufferWithXMLHeader(void)

/*
void AppendToTXBuffer(char *buf)
{
   size_t SpaceLeft, CharsToAdd = 0;
   size_t Length;

   Length       = strlen((const char *)fh.tx_buffer);
   CharsToAdd   = strlen((const char *)buf);    // size of string to append

   SpaceLeft = FIREHOSE_TX_BUFFER_SIZE - Length - XML_TAIL_LENGTH;      // fh.tx_buffer is transmit_buffer of size FIREHOSE_TX_BUFFER_SIZE

   if(CharsToAdd > SpaceLeft) { return; } // too big to add this

   // NOTE: If you're *not* seeing your messages, increase the size of transmit_buffer[FIREHOSE_TX_BUFFER_SIZE]
   //       or break up your logging

   memscpy((fh.tx_buffer+Length), SpaceLeft, buf, CharsToAdd);

} // end void AppendToTXBuffer(char *buf)
*/

char * RemoveBannedChars(char *p)
{
    char *pOrig = p;

    while(*p!='\0')
    {
        if( *p=='"' || *p=='<' || *p=='>')
            *p = '_';

         p++;
    }

    return pOrig;
}

