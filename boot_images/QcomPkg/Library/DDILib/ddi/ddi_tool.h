#ifndef _BOOT_DDI_TOOL_H
#define _BOOT_DDI_TOOL_H
/*===========================================================================

                    BOOT EXTERN QUSB DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external QUSB drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2016 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
09/09/16   zhz        remove the target related function
07/27/2016  qbz      Cleaned file included
05/07/2015  Singh   Support for DDI
===========================================================================*/

/*

DDI BUFF Structure. Available DWORDS : 100, Used : 44

DDI BUFF STRUCTURE.....
|__________________|DWORD 0-> cookie 1
|__________________|DWORD 1-> cookie 2
|__________________|DWORD 2-> DQ_LO 0 PRFS values
|__________________|DWORD 3-> DQ_LO 1 PRFS values
|__________________|DWORD 4-> DQ_LO 2 PRFS values
|__________________|DWORD 5-> DQ_LO 3 PRFS values
|__________________|DWORD 6-> DQ_LO 4 PRFS values
|__________________|DWORD 7-> DQ_LO 5 PRFS values
|__________________|DWORD 8-> DQ_LO 6 PRFS values
|__________________|DWORD 9-> DQ_LO 7 PRFS values
|__________________|DWORD 10-> DQ_HI 0 PRFS values
|__________________|DWORD 11-> DQ_HI 1 PRFS values
|__________________|DWORD 12-> DQ_HI 2 PRFS values
|__________________|DWORD 13-> DQ_HI 3 PRFS values
|__________________|DWORD 14-> DQ_HI 4 PRFS values
|__________________|DWORD 15-> DQ_HI 5 PRFS values
|__________________|DWORD 16-> DQ_HI 6 PRFS values
|__________________|DWORD 17-> DQ_HI 7 PRFS values
|__________________|DWORD 18-> CA_LO 0 PRFS values
|__________________|DWORD 19-> CA_LO 1 PRFS values
|__________________|DWORD 20-> CA_LO 2 PRFS values
|__________________|DWORD 21-> CA_LO 3 PRFS values
|__________________|DWORD 22-> CA_LO 4 PRFS values
|__________________|DWORD 23-> CA_LO 5 PRFS values
|__________________|DWORD 24-> CA_LO 6 PRFS values
|__________________|DWORD 25-> CA_LO 7 PRFS values
|__________________|DWORD 26-> CA_HI 0 PRFS values
|__________________|DWORD 27-> CA_HI 1 PRFS values
|__________________|DWORD 28-> CA_HI 2 PRFS values
|__________________|DWORD 29-> CA_HI 3 PRFS values
|__________________|DWORD 30-> CA_HI 4 PRFS values
|__________________|DWORD 31-> CA_HI 5 PRFS values
|__________________|DWORD 32-> CA_HI 6 PRFS values
|__________________|DWORD 33-> CA_HI 7 PRFS values
|__________________|DWORD 34-> 32 bits for possible frequencies for which MR registers are changed.
|__________________|DWORD 35-> 32 bits for Print Mask. This will enable the data that will be displayed for training
|__________________|DWORD 36->
_______________________________________________________________________________________________________________________
|8 bits for MR3 for freq 4  |   8 bits for MR3 for freq 3   |   8 bits for MR3 for freq 2   |8 bits for MR3 for freq 1|
-----------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 37->
_____________________________________________________________________________________________________________________
|8 bits for MR3 for freq 8  |   8 bits for MR3 for freq 7   |   8 bits for MR3 for freq 6| 8 bits for MR3 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 38->
_____________________________________________________________________________________________________________________
|8 bits for MR11 for freq 4 |   8 bits for MR11 for freq 3  |   8 bits for MR11 for freq 2| 8 bits for MR11 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 39->
_____________________________________________________________________________________________________________________
|8 bits for MR11 for freq 8 |   8 bits for MR11 for freq 7  |   8 bits for MR11 for freq 6| 8 bits for MR11 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 40->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS0 for freq 4 |8 bits for MR22_CS0 for freq 3|8 bits for MR22_CS0 for freq 2| 8 bits for MR22_CS0 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 41->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS0 for freq 8 |8 bits for MR22_CS0 for freq 7|8 bits for MR22_CS0 for freq 6| 8 bits for MR22_CS0 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 42->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS1 for freq 4 |8 bits for MR22_CS1 for freq 3|8 bits for MR22_CS1 for freq 2| 8 bits for MR22_CS1 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 43->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS1 for freq 8 |8 bits for MR22_CS1 for freq 7|8 bits for MR22_CS1 for freq 6| 8 bits for MR22_CS1 for freq 5|
---------------------------------------------------------------------------------------------------------------------
|__________________|DWORD 44->     Training Data Display or not
*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

/*

DDI BUFF Structure. Available DWORDS : 100, Used : 44

DDI BUFF STRUCTURE.....
|__________________|DWORD 0-> cookie 1
|__________________|DWORD 1-> cookie 2
|__________________|DWORD 2-> DQ_LO 0 PRFS values
|__________________|DWORD 3-> DQ_LO 1 PRFS values
|__________________|DWORD 4-> DQ_LO 2 PRFS values
|__________________|DWORD 5-> DQ_LO 3 PRFS values
|__________________|DWORD 6-> DQ_LO 4 PRFS values
|__________________|DWORD 7-> DQ_LO 5 PRFS values
|__________________|DWORD 8-> DQ_LO 6 PRFS values
|__________________|DWORD 9-> DQ_LO 7 PRFS values
|__________________|DWORD 10-> DQ_HI 0 PRFS values
|__________________|DWORD 11-> DQ_HI 1 PRFS values
|__________________|DWORD 12-> DQ_HI 2 PRFS values
|__________________|DWORD 13-> DQ_HI 3 PRFS values
|__________________|DWORD 14-> DQ_HI 4 PRFS values
|__________________|DWORD 15-> DQ_HI 5 PRFS values
|__________________|DWORD 16-> DQ_HI 6 PRFS values
|__________________|DWORD 17-> DQ_HI 7 PRFS values
|__________________|DWORD 18-> CA_LO 0 PRFS values
|__________________|DWORD 19-> CA_LO 1 PRFS values
|__________________|DWORD 20-> CA_LO 2 PRFS values
|__________________|DWORD 21-> CA_LO 3 PRFS values
|__________________|DWORD 22-> CA_LO 4 PRFS values
|__________________|DWORD 23-> CA_LO 5 PRFS values
|__________________|DWORD 24-> CA_LO 6 PRFS values
|__________________|DWORD 25-> CA_LO 7 PRFS values
|__________________|DWORD 26-> CA_HI 0 PRFS values
|__________________|DWORD 27-> CA_HI 1 PRFS values
|__________________|DWORD 28-> CA_HI 2 PRFS values
|__________________|DWORD 29-> CA_HI 3 PRFS values
|__________________|DWORD 30-> CA_HI 4 PRFS values
|__________________|DWORD 31-> CA_HI 5 PRFS values
|__________________|DWORD 32-> CA_HI 6 PRFS values
|__________________|DWORD 33-> CA_HI 7 PRFS values
|__________________|DWORD 34-> 32 bits for possible frequencies for which MR registers are changed.
|__________________|DWORD 35-> 32 bits for Print Mask. This will enable the data that will be displayed for training
|__________________|DWORD 36->
_______________________________________________________________________________________________________________________
|8 bits for MR3 for freq 4  |   8 bits for MR3 for freq 3   |   8 bits for MR3 for freq 2   |8 bits for MR3 for freq 1|
-----------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 37->
_____________________________________________________________________________________________________________________
|8 bits for MR3 for freq 8  |   8 bits for MR3 for freq 7   |   8 bits for MR3 for freq 6| 8 bits for MR3 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 38->
_____________________________________________________________________________________________________________________
|8 bits for MR11 for freq 4 |   8 bits for MR11 for freq 3  |   8 bits for MR11 for freq 2| 8 bits for MR11 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 39->
_____________________________________________________________________________________________________________________
|8 bits for MR11 for freq 8 |   8 bits for MR11 for freq 7  |   8 bits for MR11 for freq 6| 8 bits for MR11 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 40->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS0 for freq 4 |8 bits for MR22_CS0 for freq 3|8 bits for MR22_CS0 for freq 2| 8 bits for MR22_CS0 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 41->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS0 for freq 8 |8 bits for MR22_CS0 for freq 7|8 bits for MR22_CS0 for freq 6| 8 bits for MR22_CS0 for freq 5|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 42->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS1 for freq 4 |8 bits for MR22_CS1 for freq 3|8 bits for MR22_CS1 for freq 2| 8 bits for MR22_CS1 for freq 1|
---------------------------------------------------------------------------------------------------------------------

|__________________|DWORD 43->
_____________________________________________________________________________________________________________________
|8 bits for MR22_CS1 for freq 8 |8 bits for MR22_CS1 for freq 7|8 bits for MR22_CS1 for freq 6| 8 bits for MR22_CS1 for freq 5|
---------------------------------------------------------------------------------------------------------------------
|__________________|DWORD 44->     Training Data Display or not
*/

#include <string.h>
#include "ddr_drivers.h"
#include "ddr_common.h"
#include "boot_logger.h"
#include "ddr_external.h"
#include "pm_smps.h"
#include "TsensLib.h"
#include "HAL_SNS_DDR.h"
#include "target_config_rpm.h"
#include "ddrss_training.h"

#define BUFFER_LENGTH 1024
#define TRAINING_BUFFER_LENGTH 3072
#define DDR_PATTERN_LENGTH 256
#define X_AXIS_TITLE_LENGTH 50
#define Y_AXIS_TITLE_LENGTH 100

#define DDI_MAGIC_IS_RETRAINED          0xE12A3456
#define DDI_MAGIC_RETRAIN_REQUIRED_A    0xDD3DEB06
#define DDI_MAGIC_RETRAIN_REQUIRED_B    0xb5b5b5b5
#define MAX_CLOCK_FREQ 15
#define DDR_TEST_OFFSET 0x7000000
#define MAX_PRFS_LEVELS 8

typedef enum
{
    DEFAULT_PATTERN,
    BITFLIP_PATTERN,
    CHECK_BOARD_PATTERN,
    BITSPREAD_PATTERN,
    SOLID_BITS_PATTERN,
    WORKING_ONE_PATTERN,
    WORKING_ZERO_PATTERN,
    SEQ_INR_PARTTERN,
    CUSTOMER_PARTTERN,
    INVALID_PARTTERN
} DDR_TEST_PATTERN;


typedef struct
{
    int32   mr3Val;
    int32   mr11Val;
    uint32  freq_switch_range_in_kHz;
} DDI_MR_Struct_t;

/**
 * @brief function defect test
 *        name function test name
 *        fp   test function pointer
 */
typedef struct
{
    char *name;
    boolean (*fp)(const uint64 base, const uint32 size);
} funcDefectTest_s;

boolean ddi_DDRTestOwnAddr(uint8 ch , uint8 cs, char* tag);
boolean ddi_DDRDataLinesTest(uint8 ch , uint8 cs, char* tag);
boolean ddi_DDRAddressLinesTest(uint8 ch , uint8 cs, char* tag);
void retrainDDR(void);
void displayData(void * buffer, uint32 size,void* tArgs, void *training_params_ptr);
void clearFlashParams();
void clearDDIBuff();
void InitDDITransport();
void getBaseSize(uint8 ch, uint8 cs);
void resetDDI();
void changeDRAMSettings(uint32 clk_in_khz);
void sendTrainingRsp();
char *ddi_strcpy(char *restrict dest, const char *restrict src);
void deInitTransport();
boolean ddi_ChangeMR11(uint8 freq, uint8 mr11Val);
boolean ddi_ChangeMR3(uint8 freq, uint8 mr3Val );
void update_ddr_clock_table();
boolean ddi_ChangeBIMCClock(uint8 Ix);
boolean ddi_readPowerSetting();
boolean ddi_readTemperature();
uint32 ddi_ReadVoltage(uint8 pmic_chip, uint8 smps_peripheral_index);
uint16 ddi_WriteVoltage(uint8 pmic_chip, uint8 smps_peripheral_index, uint32 voltage);
boolean ddi_ChangeVDDQ(uint32 vddVal);
boolean ddi_ChangeVDD1(uint32 vddVal);
boolean ddi_ChangeVDD2(uint32 vddVal);
boolean ddi_ReadWriteTest(uint8 ch, uint8 cs, uint32 loopcnt);
boolean ddi_WriteTest(uint8 ch, uint8 cs, uint32 loopcnt);
boolean ddi_ReadTest(uint8 ch, uint8 cs, uint32 loopcnt);
boolean ddi_readMRReg(uint8 ch, uint8 cs, uint8 reg);
boolean ddi_writeMRReg(uint8 ch, uint8 cs, uint8 reg, uint8 regVal);
boolean ddi_DQ_Read_Vref_CDC_Shmoo(uint8 ch, uint8 cs, uint8 clock_idx, uint8 start_vref, uint8 end_vref, uint8 vref_step, uint8 start_coarse_cdc, uint8 end_coarse_cdc);
boolean ddi_DQ_Write_Vref_CDC_Shmoo(uint8 ch, uint8 cs, uint8 clock_idx, uint8 start_vref, uint8 end_vref, uint8 vref_step, uint8 start_coarse_cdc, uint8 end_coarse_cdc);
void initMRStruct();
void applyMRVal();
void initDDIBuffer();
DDR_TYPE getDDRType(void);
#endif /* _BOOT_DDI_TOOL_H */
