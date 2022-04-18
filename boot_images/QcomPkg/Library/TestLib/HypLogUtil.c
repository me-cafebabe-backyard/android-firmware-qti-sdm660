/* HypLogUtil.c
*  implement logging from hypversor and tz
*
* Copyright (c)  2015-2016 by Qualcomm Technologies, Inc. All Rights Reserved.
* 
*
**********************************************************************/

#include "DALSys.h" // used for MALLOC
#include <Uefi.h>
#include <Library/UefiLib.h>
//#include "msmhwiobase.h"  // SYSTEM_IMEM_BASE=0x14680000

// ==================PRIVATE DATA FOR 8996 ==========

// ================IMEM LOG INFO =====================================
#define SYSTEM_IMEM_BASE					0x14680000
#define IMEM_BASE_OFFSET                   	0x0003F000
#define IMEM_BASE							(SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET)
  
#define IMEM_HYP_OFFSET             0x00000B20
#define IMEM_HYP_LOG_ADDR           (IMEM_BASE + IMEM_HYP_OFFSET + 0x10)
#define IMEM_HYP_LOG_SIZE           (IMEM_BASE + IMEM_HYP_OFFSET + 0x14)

#define IMEM_TZ_DIAG_OFFSET         0x00000720
#define IMEM_TZ_DIAG_ADDR           (IMEM_BASE + IMEM_TZ_DIAG_OFFSET)

#define HYP_LOG_SIZE 8*1024

#define NUMCPUS 4 // NUMBER OF CORES OF MSM8998

// ==================================TZ MACRO========================

#define TZBSP_DIAG_NUM_OF_VMID 16
#define TZBSP_DIAG_INT_NUM  64
#define TZBSP_CPU_COUNT 8
#define TZBSP_DIAG_MAJOR_VERSION_LEGACY 2
#define TZ_LOG_BUFFER_SIZE 0x2000 // 0x2000
#define TZBSP_DIAG_VMID_DESC_LEN 7
#define TZBSP_MAX_INT_DESC 16
#define QSEE_LOG_BUF_SIZE 0x8000

//========================= LOGGING STRUCTURE ==============================

typedef struct hyp_log_pos_s
{
  /* Ring buffer wrap-around ctr */
  UINT16 wrap;
  
  /* Ring buffer current position */
  UINT16 offset;
} hyp_log_pos_t;


/* Boot Info Table */
typedef struct hyp_diag_boot_info_s
{
  /* Warmboot entry CPU Counter */
  uint32 warm_entry_cnt;

  /* Warmboot exit CPU Counter */
  uint32 warm_exit_cnt;

   /* Warmboot marker */
  uint32 warmboot_marker;
  
} hyp_diag_boot_info_t;


// TODO: replace 4 with dynamic CPU variables
typedef struct hyp_diag_log_s
{
  /* Magic Number */
  uint32                  magic_num;

  /* Number of CPU's */
  uint32                  cpu_count;

  /* Ring Buffer Offset */
  uint32                  ring_off;

  /* Ring buffer position mgmt */
  hyp_log_pos_t   log_pos;
  uint32          log_len;
  
  /* S2 fault numbers */
  uint32                  s2_fault_counter;

  /* Boot Info */
  hyp_diag_boot_info_t    boot_info[NUMCPUS];
    
  /* Ring buffer pointer */
  char                    *log_buf_p;
} hyp_diag_log_t;



// TZ LOG ===============================================================



typedef struct tzbsp_log_pos_s
{
  /* Ring buffer wrap-around ctr */
  uint16 wrap;
  
  /* Ring buffer current position */
  uint16 offset;
} tzbsp_log_pos_t;

typedef struct tzbsp_diag_int_s
{
  /* Type of Interrupt/exception */
  uint16 int_info;

  /* Availability of the slot */
  uint8 avail;

  /* Reserved for future use. */
  uint8 spare;

  /* Interrupt Number for IRQ and FIQ interrupts */
  uint32 int_num;

  /* ASCII text describing type of interrupt e.g. Secure Timer, EBI XPU. This
   * string is always null terminated, supporting at most \c TZBSP_MAX_INT_DESC
   * characters. Any additional characters are truncated. */
  uint8 int_desc[TZBSP_MAX_INT_DESC];

  /* Number of this interrupt seen per CPU. */
  uint32 int_count[TZBSP_CPU_COUNT];
} tzbsp_diag_int_t;


/* Reset Infor Table */
typedef struct tzbsp_diag_reset_info_s
{
  /* Reset Reason - Security Violation */
  uint32 reset_type;

  /* Number of resets that occured for above CPU */
  uint32 reset_cnt;
} tzbsp_diag_reset_info_t;

/* warm boot reason for cores */
typedef struct tzbsp_diag_wakeup_info_s
{
  /* Wake source info : APCS_GICC_HPPIR */
  uint32 HPPIR;
  /* Wake source info : APCS_GICC_AHPPIR */
  uint32 AHPPIR;

} tzbsp_diag_wakeup_info_t;



typedef struct tzbsp_diag_log_s
{
  /* Ring buffer position mgmt */
  tzbsp_log_pos_t   log_pos;
  
  /* open ended array to the end of the 4K IMEM buffer */
  uint8             log_buf[1];
} tzbsp_diag_log_t;

typedef PACKED struct tzbsp_diag_vmid_s
{
  /* Virtual Machine Identifier */
  uint8 vmid;

  /* ASCII Text */
  uint8 desc[TZBSP_DIAG_VMID_DESC_LEN];
} tzbsp_diag_vmid_t;


/* Boot Info Table */
typedef struct tzbsp_diag_boot_info_s
{
  /* Warmboot entry CPU Counter */
  uint32 warm_entry_cnt;

  /* Warmboot exit CPU Counter */
  uint32 warm_exit_cnt;

  /* Power collapse termination entry counter. */
  uint32 term_entry_cnt;

  /* Power collapse termination exit counter. The number of times CPU fell
   * through the WFI without entering power collapse. */
  uint32 term_exit_cnt;

  /* Warmboot entry CPU Counter */
  uint32 psci_entry_cnt;

  /* Warmboot exit CPU Counter */
  uint32 psci_exit_cnt;

  /* Last Warmboot Jump Address */
  UINTN warm_jmp_addr;

  /* Last Warmboot Jump Address Instruction */
  uint32 warm_jmp_instr;

} tzbsp_diag_boot_info_t;

/* Diagnostic Table */
typedef struct tzbsp_diag_s
{
  /* Magic Number */
  uint32 magic_num;

  /* Major.Minor version */
  uint32 version;

  /* Number of CPU's */
  uint32 cpu_count;

  /* Offset of VMID Table */
  uint32 vmid_info_off;

  /* Offset of Boot Table */
  uint32 boot_info_off;

  /* Offset of Reset Table */
  uint32 reset_info_off;

  /* Offset of Interrupt Table */
  uint32 int_info_off;

  /* Ring Buffer Offset */
  uint32 ring_off;

  /* Ring Buffer Len */
  uint32 ring_len;

  /* Offset for Wakeup info */
  uint32 wakeup_info_off;

  /* VMID to EE Mapping. */
  tzbsp_diag_vmid_t vmid[TZBSP_DIAG_NUM_OF_VMID];

  /* Boot Info */
  tzbsp_diag_boot_info_t  boot_info[TZBSP_CPU_COUNT];

  /* Reset Info */
  tzbsp_diag_reset_info_t reset_info[TZBSP_CPU_COUNT];

  /* Length of the interrupt table */
  uint32 num_interrupts;
  tzbsp_diag_int_t  int_info[TZBSP_DIAG_INT_NUM];
  
  /* Wake up info */
  tzbsp_diag_wakeup_info_t  wakeup_info[TZBSP_CPU_COUNT];

  /* We need at least 2K for the ring buffer */
  /* TZ Ring Buffer */
  tzbsp_diag_log_t log;
} tzbsp_diag_t;





// Helper function to copy data from IMEM to display buffer
static int _copyDataToBuffer (char *src, char *dest, uint32 len);
static int _disp_tz_log_stats (void);
static int _disp_tz_log_stats_legacy(void);
static int _disp_tz_boot_stats (void);
static tzbsp_diag_t *getTzLogStruct (void);
static hyp_diag_log_t * getHypLogStruct (void) ;
static int _dumpBuffer(char *buff, uint32 len);

static UINT16 latest_tz_log_pos;
static UINT16 latest_hyp_log_pos;

void coretest_hyp_log_init(void)
{
	hyp_diag_log_t* g_pHyp_log = getHypLogStruct();
	latest_hyp_log_pos = (g_pHyp_log->log_pos).offset;
	//AsciiPrint("coretest_hyp_log_init: latest_hyp_log_pos = %x\n",latest_hyp_log_pos);
	return;
}

void coretest_tz_log_init(void)
{
	tzbsp_diag_t* tz_log = getTzLogStruct();
	latest_tz_log_pos = (tz_log->log).log_pos.offset;
	//AsciiPrint("coretest_tz_log_init: latest_tz_log_pos = %x\n",latest_tz_log_pos);
	return;
}

// TODO: add some error checking to avoid crash
/*
#define IMEM_BASE_OFFSET                   	0x0003F000
#define IMEM_BASE							(SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET)
  
#define IMEM_HYP_OFFSET             0x00000B20
#define IMEM_HYP_LOG_ADDR           (IMEM_BASE + IMEM_HYP_OFFSET + 0x10)
*/
hyp_diag_log_t * getHypLogStruct (void) 
{

	// get the address of the hyp log structure
	UINTN hyp_log_base_address = (*((UINTN *) IMEM_HYP_LOG_ADDR)) & 0xFFFFFFFF;
	
	//AsciiPrint("getHypLogStruct: hyp_log_base_address = %x\n",hyp_log_base_address);
	return (hyp_diag_log_t *)(UINTN)(hyp_log_base_address);

}



void printHypLog(void) 
{
	hyp_diag_log_t* g_pHyp_log;
 	char buffArr [HYP_LOG_SIZE] = {0}; // temp array 
 	g_pHyp_log = getHypLogStruct ();

	// dump the log 
	// only dump from valid offset to the end..
 	uint32 len = g_pHyp_log->log_len - latest_hyp_log_pos + 1;
 	int res = _copyDataToBuffer((char *) g_pHyp_log + g_pHyp_log->ring_off + latest_hyp_log_pos, buffArr, len);
 	if (res == 0){
 		_dumpBuffer(buffArr,len);
		latest_hyp_log_pos = (g_pHyp_log->log_pos).offset;
 	}
 	else
 		AsciiPrint("HYP LOG DATA IS INVALID OR EMPTY");
}


tzbsp_diag_t *getTzLogStruct (void) 
{
	UINTN tz_log_base_address = (*((UINTN *) IMEM_TZ_DIAG_ADDR)) & 0xFFFFFFFF;

	//AsciiPrint("getTzLogStruct: tz_log_base_address = %x\n",tz_log_base_address);
	return (tzbsp_diag_t*)(UINTN)(tz_log_base_address);
}


/**
	Display TZ debugging log...
*/
void printTzBspLog(void) 
{
	tzbsp_diag_t* tz_log = getTzLogStruct();

	// verify TZ version to pick the correct function
	if (TZBSP_DIAG_MAJOR_VERSION_LEGACY <(tz_log->version >> 16)) {
		_disp_tz_log_stats();
	} else {
		_disp_tz_log_stats_legacy();
	}
	latest_tz_log_pos = (tz_log->log).log_pos.offset;
	//AsciiPrint("coretest_tz_log_init: latest_tz_log_pos = %x\n",latest_tz_log_pos);
}

/** DISPLAY TZ BOOT STATS */
void printTzBootStats(void){

	_disp_tz_boot_stats();
}

/** DISPLAY TZ RESET STATS */
void printTzResetStats (void) {
	int i = 0;
	tzbsp_diag_reset_info_t *ptr; 
	tzbsp_diag_t* tz_log = getTzLogStruct();

	// get the reset stat info
	ptr = (tzbsp_diag_reset_info_t *) ((char *)tz_log + tz_log->reset_info_off);

	// now dump the info
	for (i = 0; i < TZBSP_CPU_COUNT; i++) {
		AsciiPrint ("  CPU #: %d\n"
					"     Reset Type (reason)       : 0x%x\n"
					"     Reset counter             : 0x%x\n", ptr->reset_type, ptr->reset_cnt);
	}

}


// ============================ HELPER PRIVATE FUNCTION ======================================

static int _disp_tz_log_stats (void) {
	
	//AsciiPrint("TZ BSP DEBUG LOG\n");
	
	int res = 1;
	tzbsp_diag_t *tz_log = getTzLogStruct();


	if (tz_log != NULL){

		char *ptr;

		char buffArr [TZ_LOG_BUFFER_SIZE] = {0};

		uint32 len  = 0;
		
		ptr = (char *)tz_log + tz_log->ring_off + latest_tz_log_pos;
		//AsciiPrint("print from address 0x%x\n", (UINT32)ptr);

		len = tz_log->ring_len - latest_tz_log_pos + 1;

		res = _copyDataToBuffer(ptr, buffArr, len);
		
		if (res == 0  )
		{
				//AsciiPrint("TZ BSP DEBUG LOG:  \n");
				_dumpBuffer(buffArr,len);

		} else {

				//AsciiPrint("TZ BSP  DEBUG LOG --- EMPTY");

		}
	}

	return res;

}


static int _disp_tz_boot_stats (void) {

	tzbsp_diag_t *tz_log = getTzLogStruct();

	tzbsp_diag_boot_info_t *ptr;

	int i;

	ptr = (tzbsp_diag_boot_info_t *)((unsigned char *)tz_log +
					tz_log->boot_info_off);

	for (i = 0; i < TZBSP_CPU_COUNT; i++) {
		AsciiPrint(
					"  CPU #: %d\n"
					"     Warmboot jump address     : 0x%x\n"
					"     Warmboot entry CPU counter: 0x%x\n"
					"     Warmboot exit CPU counter : 0x%x\n"
					"     Power Collapse entry CPU counter: 0x%x\n"
					"     Power Collapse exit CPU counter : 0x%x\n"
					"=================================================\n",
				i, ptr->warm_jmp_addr, ptr->warm_entry_cnt,
				ptr->warm_exit_cnt, ptr->term_entry_cnt,
				ptr->term_exit_cnt);

		ptr++;
	}

	return 0;
}


static int _disp_tz_log_stats_legacy (void) {
	
	tzbsp_diag_t *tz_log = getTzLogStruct();

	AsciiPrint("TZ BSP LEGACY DEBUG LOG\n");
	
	if (tz_log != NULL){

		char *ptr;

		//char buffArr [TZ_LOG_BUFFER_SIZE] = {0};

		ptr = (char *)tz_log + tz_log->ring_off;
		
		if (ptr != NULL )
		{
				AsciiPrint("TZ BSP LEGACY DEBUG LOG:  %a \n", ptr);

				return 0;

		} else {

				AsciiPrint("TZ BSP LEGACY DEBUG LOG --- EMPTY");

		}
	}

	return 1;

}



static int _copyDataToBuffer (char *src, char *dest, uint32 len) {

	uint32 i = 0;

	// quick error checks
	if (len == 0)
		return 1;

	if (src == NULL || dest == NULL)
		return 1;

	// let's copy byte by byte
	while ((0 != (*dest++ = *src++)) && (i <= len)) {
		i++;
	}
	//AsciiPrint("Done Copy for %d bytes\n",i);
	return 0;
}


//dump buffer char by char ...
static int _dumpBuffer(char *buff, uint32 len) {

	uint32 i;
	if (buff == NULL ){
		AsciiPrint("NULL BUFFER CANNOT BE DUMP\n");
		return 1;
	}

	for (i = 0; i < len; i++){
		if (buff[i] != 0)
			AsciiPrint("%c",buff[i]);
	}

	return 0;
}
