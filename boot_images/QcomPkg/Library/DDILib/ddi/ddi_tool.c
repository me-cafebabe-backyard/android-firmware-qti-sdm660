/*===========================================================================

                    BOOT_DDI_TOOL

DESCRIPTION
  This file contains the code for Boot DDR Debug Image tool.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2017 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/09/17   zhz     Add DQ Vref CDC shmoo test
03/06/17   zhz     Read the correct CA Vref value from ca_vref.range_vref
01/09/17   zhz     move the target related function to ddi_target.c
09/09/16   jh       Ported various bugfixes from 8996
07/27/16   qbz     Cleaned files included
05/06/15   sng     Initial Release
=============================================================================*/
#include "ddi_target.h"
#include "ddi_tool.h"
#include "ddi_firehose.h"
#include "ddi_initialize.h"
#include "boot_visual_indication.h"
#include "boot_extern_ddr_interface.h"
#include "boot_cache_mmu.h"
#include "boothw_target.h"
#include "ClockBoot.h"
#include "pm_rgb.h"
#include "ddrss.h"
#include "ddrss_training.h"
#include "bimc.h"
#include "boot_target.h"
#include "ddr_common_params.h"
//#include "boot_msm.h"
#include "HALhwio.h"

#define BIT_ERROR_STATISTICS

extern uint32 dataBuffer[DDR_PATTERN_LENGTH];
extern uint16 patternElemCnt;
extern char str[BUFFER_LENGTH];

uint8 xAxisTitle[X_AXIS_TITLE_LENGTH]  __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
uint8 yAxisTitle[Y_AXIS_TITLE_LENGTH]  __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
uint32 read_back_pattern[DDR_PATTERN_LENGTH]  __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
char ddiTrainingBuffer[TRAINING_BUFFER_LENGTH] __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
char srcBuffer[BUFFER_LENGTH] __attribute__ ((section (".bss.DDITRAINING_BUFFER_SECTION"))) = {0};
uint64 gBase = 0;
uint32 gSize = 0;

#ifdef BIT_ERROR_STATISTICS
uint32 error_statistics =0;
#endif

char str_log[BUFFER_LENGTH] = {0};

DDR_STRUCT *share_data = (DDR_STRUCT *)DDR_GLOBAL_STRUCT_DATARAM_ADDR;
uint8 gSupportedClockLevel ;
uint32 bimc_clk_plan[MAX_CLOCK_FREQ];

DDI_MR_Struct_t MRParams[NUM_ECDT_FREQ_SWITCH_STRUCTS];
uint32 boot_ddr_freq = 200000;
boolean rdcdc_scan = FALSE;
uint32 failures[4];
DDR_TEST_PATTERN PATTERN;
uint8 current_clock_idx = 0;
uint8 current_coarse_cdc = 0;
uint8 current_fine_cdc = 0;
uint8 current_vref = 0;
uint8 which_ch = 0;
uint8 which_cs = 0;
boolean retrain_status = FALSE;
uint32 PRFS_BAND_THRESHOLD[NUM_PRFS_BANDS] = {F_RANGE_0, F_RANGE_1, F_RANGE_2, F_RANGE_3, F_RANGE_4, F_RANGE_5, F_RANGE_6, F_RANGE_7};

#define PRFS_BAND_THRESHOLD_NUMBER  (sizeof(PRFS_BAND_THRESHOLD) / sizeof(PRFS_BAND_THRESHOLD[0]))

char pattern_name[][20] =
{
    {"Training pattern"},
    {"Bit Flip"},
    {"Checkerboard"},
    {"Bit Spread"},
    {"Solid bits"},
    {"Walking ones"},
    {"Walking zeros"},
    {"Seq incr"},
    {"Customer"},
};

void resetDDI()
{
    boot_hw_reset(BOOT_WARM_RESET_TYPE);
}

void InitDDITransport()
{
    deviceprogrammer_zi_buffers ();
    initFirehoseProtocol(); // initializes default values for fh structure
    ddi_init_hw();
    initMRStruct();
}

void deInitTransport()
{
    shutDownUSB();
}

void initDDIBuffer()
{
    uint32 cookie1 = share_data->ddi_buf[0];
    uint32 cookie2 = share_data->ddi_buf[1];
    memset(share_data->ddi_buf, 0x0, sizeof(share_data->ddi_buf));
    share_data->ddi_buf[0] = cookie1;
    share_data->ddi_buf[1] = cookie2;
}

void clearDDIBuff()
{
    memset(&share_data->ddi_buf, 0x0, sizeof(share_data->ddi_buf));
    share_data->ddi_buf[0] = DDI_MAGIC_IS_RETRAINED;
}

void clearFlashParams()
{
    memset(&share_data->flash_params, 0x0, sizeof(struct ddr_params_partition));
}

DDR_TYPE getDDRType(void)
{
    return share_data->detected_ddr_device[0].device_type;
}

void getBaseSize(uint8 ch, uint8 cs)
{
    uint64 address[2][2] = {{0}};

    address[0][0] = (share_data->ddr_size_info.ddr0_cs0_remapped_addr) + TRAINING_BASE_ADDRESS_OFFSET;

    address[0][1] = (share_data->ddr_size_info.ddr0_cs1_remapped_addr) + TRAINING_BASE_ADDRESS_OFFSET;

    address[1][0] = share_data->ddr_size_info.ddr1_cs0_remapped_addr + TRAINING_BASE_ADDRESS_OFFSET + \
                    ((share_data->detected_ddr_device[0].interleave_en & DDR_CS0_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0);

    address[1][1] = share_data->ddr_size_info.ddr1_cs1_remapped_addr + TRAINING_BASE_ADDRESS_OFFSET + \
                    ((share_data->detected_ddr_device[0].interleave_en & DDR_CS1_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0);

    gBase = address[ch][cs];

    switch (ch)
    {
        case 0:
            switch (cs)
            {
                case 0:
                    gSize = (uint32)(share_data->ddr_size_info.ddr0_cs0_mb);
                    gSize = gSize << 20;
                    gSize = gSize - TRAINING_BASE_ADDRESS_OFFSET;
                    boot_log_message("CH0 CS0");
                    break;
                case 1:
                    gSize = (uint32)(share_data->ddr_size_info.ddr0_cs1_mb);
                    gSize = gSize << 20;
                    gSize = gSize - TRAINING_BASE_ADDRESS_OFFSET;
                    boot_log_message("CH0 CS1");
                    break;
                default:
                    break;
            }

            break;

        case 1:
            switch (cs)
            {
                case 0:
                    gSize = (uint32)(share_data->ddr_size_info.ddr1_cs0_mb);
                    gSize = gSize << 20;
                    gSize = gSize - (TRAINING_BASE_ADDRESS_OFFSET + ((share_data->detected_ddr_device[0].interleave_en & DDR_CS0_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0));
                    boot_log_message("CH1 CS0");
                    break;

                case 1:
                    gSize = (uint32)(share_data->ddr_size_info.ddr1_cs1_mb);
                    gSize = gSize << 20;
                    gSize = gSize - (TRAINING_BASE_ADDRESS_OFFSET + ((share_data->detected_ddr_device[0].interleave_en & DDR_CS1_INTERLEAVE) ? TRAINING_INTERLEAVE_ADDRESS_OFFSET : 0));
                    boot_log_message("CH1 CS1");
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

}

void update_ddr_clock_table()
{
    uint32 i=0;
    gSupportedClockLevel = share_data->misc.ddr_num_clock_levels;
    if(gSupportedClockLevel <= MAX_CLOCK_FREQ)
    {
        for(i = 0; i < gSupportedClockLevel; i++)
        {
            bimc_clk_plan[i] =  share_data->misc.clock_plan[i].clk_freq_in_khz;
        }
    }
}

boolean ddi_writeMRReg(uint8 ch, uint8 cs, uint8 reg, uint8 regVal)
{
    ch++;
    cs++;
    BIMC_MR_Write(ch,cs,reg,regVal);
    return TRUE;
}

boolean ddi_readMRReg(uint8 ch, uint8 cs, uint8 reg)
{
    uint32 mrVal = 0;

    ch++;
    cs++;
    mrVal = BIMC_MR_Read(ch, cs, reg);
    ddi_firehose_print_log("MR REG Value: %d", mrVal);
    return TRUE;
}

boolean ddi_ChangeBIMCClock(uint8 Ix)
{
    if(Clock_SetBIMCSpeed(bimc_clk_plan[Ix]) == TRUE)
        return TRUE;

    return FALSE;
}

uint32 ddi_ReadVoltage(uint8 pmic_chip, uint8 smps_peripheral_index)
{
    uint32 voltage = 0;
    pm_smps_volt_level_status(pmic_chip, smps_peripheral_index, &voltage);
    return voltage;
}

uint16 ddi_WriteVoltage(uint8 pmic_chip, uint8 smps_peripheral_index, uint32 voltage)
{
    return pm_smps_volt_level(pmic_chip, smps_peripheral_index, voltage);
}

void initMRStruct()
{
    uint8 level = sizeof(MRParams)/sizeof(MRParams[0]);

    for (int i  = 0; i < level; i++)
    {
        MRParams[i].mr11Val = -1;
        MRParams[i].mr3Val = -1;

        if (getDDRType() == DDR_TYPE_LPDDR4X)
            MRParams[i].freq_switch_range_in_kHz = bimc_freq_switch_params_struct_lp4x[i].freq_switch_range_in_kHz;
        else
            MRParams[i].freq_switch_range_in_kHz = bimc_freq_switch_params_struct[i].freq_switch_range_in_kHz;
    }
}

void ddi_setMR3(uint32 index, uint8 value)
{
    bimc_freq_switch_params_struct[index].MR3 = value;
    bimc_freq_switch_params_struct_lp4x[index].MR3 = value;
}

void ddi_setMR11(uint32 index, uint8 value)
{
    bimc_freq_switch_params_struct[index].MR11 = value;
    bimc_freq_switch_params_struct_lp4x[index].MR11 = value;
}


void ApplyMR(uint8 JEDEC_NUM, uint8 Value)
{
    BIMC_MR_Write(DDR_CH0, DDR_CS0, JEDEC_NUM, Value );
    BIMC_MR_Write(DDR_CH0, DDR_CS1, JEDEC_NUM, Value );
    BIMC_MR_Write(DDR_CH1, DDR_CS0, JEDEC_NUM, Value );
    BIMC_MR_Write(DDR_CH1, DDR_CS1, JEDEC_NUM, Value );
}

void applyMRVal()
{
    uint8 level = sizeof(MRParams)/sizeof(MRParams[0]);
    uint8 j = 0;

    for (int i = 0; i < level; i++)
    {
        if ( (share_data->ddi_buf[(j + 1) + 36]&0xFF) != 0xFF && (share_data->ddi_buf[(j + 1) + 36]&0xFF) != 0 )
        {
            MRParams[i].mr3Val = share_data->ddi_buf[(j + 1) + 36] & 0xFF;
        }
        else
        {
            MRParams[i].mr3Val = -1;
        }

        if ( ((share_data->ddi_buf[(j + 1) + 36]&0xFF00)>>8) != 0xFF && ((share_data->ddi_buf[(j + 1) + 36]&0xFF00)>>8) != 0)
        {
            MRParams[i].mr11Val = (share_data->ddi_buf[(j + 1) + 36] & 0xFF00)>>8;
        }
        else
        {
            MRParams[i].mr11Val = -1;
        }

        j = j+2;

    }

    // set the MR values
    for (int i = 0; i < level; i++)
    {
        if (MRParams[i].mr3Val != -1)
        {
            ddi_setMR3(i, (uint8)MRParams[i].mr3Val);
        }
        if (MRParams[i].mr11Val != -1)
        {
            ddi_setMR11(i, (uint8)MRParams[i].mr11Val);
        }
    }
}

void UpdateFSP(uint8 ix)
{
    uint8 temp = 0;
    temp = (ix << 7) | (ix << 6) | (0 << 5) | (0 << 3) | (0 << 2) | (0 << 0);

    ApplyMR(JEDEC_MR_13, temp);
}

void UpdateMR(uint8 ix)
{
    uint8 temp = 0;
    uint32 MASK = 0xFF << (ix*8);

    if (ix<=3)
    {
        if(((share_data->ddi_buf[34]) & (1<<ix)) != 0)
        {
            // Get MR3 value for this freq..
            temp = ((share_data->ddi_buf[36] & MASK)>>(ix*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_3, temp);
            }

            // Get MR11 value for this freq..
            temp = ((share_data->ddi_buf[38] & MASK)>>(ix*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_11, temp);
            }

            // Get MR22 value for this freq..for cs0
            temp = ((share_data->ddi_buf[40] & MASK)>>(ix*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_22, temp);
            }
        }

    }
    else
    {
        if(((share_data->ddi_buf[34]) & (1<<ix)) != 0)
        {
            // Get MR3 value for this freq..
            temp = ((share_data->ddi_buf[37] & MASK)>>((ix-4)*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_3, temp);
            }

            // Get MR11 value for this freq..
            temp = ((share_data->ddi_buf[39] & MASK)>>((ix-4)*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_11, temp);
            }
            // Get MR22 value for this freq..for cs0
            temp = ((share_data->ddi_buf[41] & MASK)>>((ix-4)*8));
            if(temp != 0)
            {
                ApplyMR(JEDEC_MR_22, temp);
            }
        }
    }

}

void changeDRAMSettings(uint32 clk_in_khz)
{
    uint8 new_clk_idx = 0;
    uint8 new_params_idx =0;

    for (new_clk_idx = 0; new_clk_idx < share_data->misc.ddr_num_clock_levels; new_clk_idx++)
    {
        if (clk_in_khz <= share_data->misc.clock_plan[new_clk_idx].clk_freq_in_khz)
            break;
    }

    new_params_idx = BIMC_Freq_Switch_Params_Index (share_data, clk_in_khz);

    if (MRParams[new_params_idx].mr3Val != -1 && MRParams[new_params_idx].mr3Val != 0xFF)
    {
        ddi_setMR3(new_params_idx, (uint8)MRParams[new_params_idx].mr3Val);
    }
    if (MRParams[new_params_idx].mr11Val != -1 && MRParams[new_params_idx].mr11Val != 0xFF)
    {
        ddi_setMR11(new_params_idx, (uint8)MRParams[new_params_idx].mr11Val);
    }

}

boolean ddi_ChangeMR11(uint8 freq, uint8 mr11Val )
{
    uint8 i = 0;
    uint8 level = sizeof(MRParams)/sizeof(MRParams[0]);

    for ( i = 0; i < level; i++)
    {
        if (bimc_clk_plan[freq] <= MRParams[i].freq_switch_range_in_kHz)
        {
            MRParams[i].mr11Val = mr11Val;
            return TRUE;
        }
    }

    return FALSE;
}

boolean ddi_ChangeMR3(uint8 freq, uint8 mr3Val )
{
    uint8 i = 0;
    uint8 level = sizeof(MRParams)/sizeof(MRParams[0]);

    for (i = 0; i < level; i++)
    {
        if (bimc_clk_plan[freq] <= MRParams[i].freq_switch_range_in_kHz)
        {
            MRParams[i].mr3Val = mr3Val;
            return TRUE;
        }
    }
    return FALSE;
}

void ddi_mem_copy(uint32 * source, uint32 * destination, uint32 size, uint32 burst)
{
    uint32 i;

    if(burst)
    {
        /* perform a burst write */
#ifndef CDVI_SVTB
        __blocksCopy(source, destination, size);
#endif
    }
    else
    {
        for(i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }

}

char *ddi_strcpy(char *restrict dest, const char *restrict src)
{
#if 1
    __stpcpy(dest, src);
    return dest;
#else
    const unsigned char *s = src;
    unsigned char *d = dest;
    while ((*d++ = *s++));
    return dest;
#endif
}

char *ddi_strcat(char *restrict dest, const char *restrict src)
{
    ddi_strcpy(dest + strlen(dest), src);
    return dest;
}

void temperature_read_helper()
{
    TsensResultType tsensResult;
    int32 nDegC;
    uint32 tsens_index=0;
    uint32 numSensors = 0;
    if(Tsens_GetNumSensors(&numSensors) == TSENS_SUCCESS)
    {
        ddi_firehose_print_log("Num of sensors found on system: %d",numSensors);
        while(tsens_index<numSensors)
        {
            tsensResult = Tsens_GetTemp(tsens_index,&nDegC);
            if (tsensResult == TSENS_SUCCESS)
            {
                ddi_firehose_print_log("TSENS %d value %d deci degC",tsens_index,nDegC);
            }
            else
                ddi_firehose_print_log("Temperature Sensor read failure");

            tsens_index=tsens_index+1;
        }
    }
    else
        ddi_firehose_print_log("Could not get Number of sensors on system");

}

boolean ddi_readPowerSetting()
{
    uint32 VDD1 = 0;
    uint32 VDD2 = 0;
//   uint32 VDDQ = 0;  //For sdm660 platform, there is a buck to control the vddq voltage, can be read out the voltage value

    VDD1 = ddi_ReadVDD1();
    if (VDD1 != 0)
    {
        VDD1 = VDD1/1000;
        ddi_firehose_print_log("VDD1 Value(mV): %d", VDD1);

    }

    VDD2 = ddi_ReadVDD2();
    if (VDD2 != 0)
    {
        VDD2 = VDD2/1000;
        ddi_firehose_print_log("VDD2 Value(mV): %d", VDD2);

    }

//
#if 0
    VDDQ = ddi_ReadVDDQ();
    if (VDDQ != 0)
    {
        VDDQ = VDDQ/1000;
        ddi_firehose_print_log("VDDQ Value(mV): %d", VDDQ);

    }
#endif
    return TRUE;
}

boolean ddi_readTemperature()
{
    temperature_read_helper();
    return TRUE;
}


boolean ddi_ChangeVDDQ(uint32 vddVal)
{
    uint16 retErrFlag = 0;
    uint32 mx=vddVal*1000;

    retErrFlag = ddi_WriteVDDQ(mx);
    if(retErrFlag !=0)
    {
        ddi_firehose_print_log("Failed to set VDDQ!");
        return FALSE;
    }

    mx = ddi_ReadVDDQ();
    ddi_firehose_print_log("PX1/VDDQ set to: %d(mv)", mx / 1000);
    return TRUE;
}

boolean ddi_ChangeVDD1(uint32 vddVal)
{
    uint16 retErrFlag = 0;
    uint32 px3=vddVal*1000;

    retErrFlag = ddi_WriteVDD1(px3);
    if(retErrFlag !=0)
    {
        ddi_firehose_print_log("Failed to set VDD1!");
        return FALSE;
    }

    px3 = ddi_ReadVDD1();
    ddi_firehose_print_log("PX3/VDD1 set to: %d(mv)", px3 / 1000);
    return TRUE;
}

boolean ddi_ChangeVDD2(uint32 vddVal)
{
    uint16 retErrFlag = 0;
    uint32 vdd=vddVal*1000;

    retErrFlag = ddi_WriteVDD2(vdd);
    if(retErrFlag !=0)
    {
        ddi_firehose_print_log("Failed to set VDD2!");
        return FALSE;
    }

    vdd = ddi_ReadVDD2();
    ddi_firehose_print_log("VDD2 set to: %d(mv)", vdd / 1000);
    return TRUE;
}

void sendTrainingRsp()
{
    ddi_firehose_print_response("Retrain", "Pass", "true");
}

void print_training_data(void *buffer, ddr_training_args* targs, training_params_t *training_params_ptr)
{
    training_data *training_data_ptr;

    training_data_ptr = (training_data *)(&share_data->flash_params.training_data);
    uint8 ch = targs->currentChannel;
    uint8 cs = targs->currentChipSelect;
    uint8 ddr_freq_index = targs->currentFreqIndex;
    uint8 training_type= targs->trainingType;
    uint32 FreqInKhz = targs->FreqInKhz;
    uint8 best_coarse_cdc, best_fine_cdc, best_vref;

    ddrss_rdwr_dqdqs_local_vars *local_vars_DQ;
    ddrss_ca_vref_local_vars *local_vars_CACK;
    uint8 MaxNumPhy_CA = NUM_CA_PCH;
    uint8 MaxNumPhy_DQ = NUM_DQ_PCH;
    int coarse_vref;
    int coarse_cdc ;
    uint8 num_phy;

    uint8 ix = 0;
    uint8 iy = 0;

    if(training_type == DDR_TRAINING_CACK)
    {
        local_vars_CACK = (ddrss_ca_vref_local_vars *)buffer;
    }
    else
    {
        local_vars_DQ = (ddrss_rdwr_dqdqs_local_vars *)buffer;
    }

    if(share_data->ddi_buf[0] == DDI_MAGIC_RETRAIN_REQUIRED_A &&
       share_data->ddi_buf[1] == DDI_MAGIC_RETRAIN_REQUIRED_B)
    {
        if (training_type == DDR_TRAINING_CACK)
        {
            for(num_phy =0; num_phy < MaxNumPhy_CA; num_phy ++)
            {
                memset(xAxisTitle, 0, X_AXIS_TITLE_LENGTH);
                memset(yAxisTitle, 0, Y_AXIS_TITLE_LENGTH);
                memset(srcBuffer, 0, Y_AXIS_TITLE_LENGTH);
                memset(ddiTrainingBuffer, 0, TRAINING_BUFFER_LENGTH);

                ddi_firehose_print_log("FRAME_START");
                ddi_firehose_print_log("paramFreq: %d",targs->FreqInKhz);
                ddi_firehose_print_log("paramChannel: %d",targs->currentChannel);
                ddi_firehose_print_log("paramChipSelect: %d",targs->currentChipSelect);
                ddi_firehose_print_log("paramTrainingType: %d",targs->trainingType);
                ddi_firehose_print_log("paramByteNum: %d", num_phy);

                ddi_strcpy((char*)ddiTrainingBuffer,"bandcoarsepasscounttable:");
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"{");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);

                iy = 0;
                for( coarse_vref = 0; coarse_vref <training_params_ptr->ca_vref.coarse_vref_max_value+1; coarse_vref += training_params_ptr->ca_vref.coarse_vref_step)
                {
                    ix = 0;
                    yAxisTitle[iy++] = coarse_vref;
                    for(coarse_cdc =training_params_ptr->ca_vref.coarse_cdc_start_value; coarse_cdc < training_params_ptr->ca_vref.coarse_cdc_max_value + 1 ; coarse_cdc += training_params_ptr->ca_vref.coarse_cdc_step)
                    {
                        xAxisTitle[ix++] = coarse_cdc;
                        snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", local_vars_CACK->vref_fail_count_table[num_phy][coarse_vref]);
                        ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                    }

                    snprintf((char*)srcBuffer,sizeof(srcBuffer),"LF");
                    ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);

                }

                snprintf((char*)srcBuffer,sizeof(srcBuffer),"}");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);

                // Send X- axis and Y-axis data..
                ddi_strcpy((char*)ddiTrainingBuffer,"xAxis_title_CDC:{" );
                for (int i = 0; i < ix ; i++)
                {
                    snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", xAxisTitle[i]);
                    ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                }
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"},");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);
                memset(xAxisTitle,0, X_AXIS_TITLE_LENGTH);

                ddi_strcpy((char*)ddiTrainingBuffer,"yAxis_title_VREF:{" );
                for (int i = 0; i < iy ; i++)
                {
                    snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", yAxisTitle[i]);
                    ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                }
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"},");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);
                memset(yAxisTitle,0, Y_AXIS_TITLE_LENGTH);

                best_coarse_cdc = (uint8) training_data_ptr->results.ca_vref.coarse_cdc[ddr_freq_index][ch][cs][num_phy];
                best_fine_cdc = (uint8) training_data_ptr->results.ca_vref.fine_cdc[ddr_freq_index][ch][cs][num_phy];
                best_vref = (uint8) training_data_ptr->results.ca_vref.range_vref[ddr_freq_index][ch][cs][num_phy];

                ddi_firehose_print_log("resultbestcoarsecdc: %d", best_coarse_cdc);
                ddi_firehose_print_log("resultbestfinecdc: %d", best_fine_cdc);
                ddi_firehose_print_log("resultbestvref: %d", best_vref);
                ddi_firehose_print_log("FRAME_END");
            }
        }

        else
        {
            for(num_phy =0; num_phy < MaxNumPhy_DQ  ; num_phy ++)
            {
                memset(xAxisTitle,0, X_AXIS_TITLE_LENGTH);
                memset(yAxisTitle,0, Y_AXIS_TITLE_LENGTH);
                memset(srcBuffer, 0, Y_AXIS_TITLE_LENGTH);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);

                ddi_firehose_print_log("FRAME_START");
                ddi_firehose_print_log("paramFreq: %d",targs->FreqInKhz);
                ddi_firehose_print_log("paramChannel: %d",targs->currentChannel);
                ddi_firehose_print_log("paramChipSelect: %d",targs->currentChipSelect);
                ddi_firehose_print_log("paramTrainingType: %d",targs->trainingType);
                ddi_firehose_print_log("paramByteNum: %d", num_phy);

                ddi_strcat((char*)ddiTrainingBuffer,"bandcoarsepassband:");
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"{");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);

                if (training_type == DDR_TRAINING_READ)
                {
                    iy = 0;

                    for(coarse_vref = 0; coarse_vref < training_params_ptr->rd_dqdqs.coarse_vref_max_value + 1; coarse_vref += training_params_ptr->rd_dqdqs.coarse_vref_step)
                    {
                        ix = 0;
                        yAxisTitle[iy++] = coarse_vref;
                        for(coarse_cdc =training_params_ptr->rd_dqdqs.coarse_cdc_start_value; coarse_cdc < training_params_ptr->rd_dqdqs.coarse_cdc_max_value + 1 ; coarse_cdc += training_params_ptr->rd_dqdqs.coarse_cdc_step)
                        {
                            xAxisTitle[ix++] = coarse_cdc;
                            snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", local_vars_DQ->coarse_schmoo.coarse_dq_passband_info[num_phy][coarse_vref][coarse_cdc]);
                            ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                        }

                        snprintf((char*)srcBuffer,sizeof(srcBuffer),"LF");
                        ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                    }
                }

                if (training_type == DDR_TRAINING_WRITE)
                {
                    iy = 0;
                    for( coarse_vref = 0; coarse_vref < training_params_ptr->wr_dqdqs.coarse_vref_max_value + 1; coarse_vref += training_params_ptr->wr_dqdqs.coarse_vref_step)
                    {
                        yAxisTitle[iy++] = coarse_vref;
                        ix = 0;
                        for(coarse_cdc =training_params_ptr->wr_dqdqs.coarse_cdc_start_value; coarse_cdc < training_params_ptr->wr_dqdqs.coarse_cdc_max_value + 1 ; coarse_cdc += training_params_ptr->wr_dqdqs.coarse_cdc_step)
                        {
                            xAxisTitle[ix++] = coarse_cdc;
                            snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", local_vars_DQ->coarse_schmoo.coarse_dq_passband_info[num_phy][coarse_vref][coarse_cdc]);
                            ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                        }

                        snprintf((char*)srcBuffer,sizeof(srcBuffer),"LF");
                        ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                    }
                }

                snprintf((char*)srcBuffer,sizeof(srcBuffer),"}");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);

                // Send X- axis and Y-axis data..
                ddi_strcpy((char*)ddiTrainingBuffer,"xAxis_title_CDC:{" );
                for (int i = 0; i < ix ; i++)
                {
                    snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", xAxisTitle[i]);
                    ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                }
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"},");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);
                memset(xAxisTitle,0, X_AXIS_TITLE_LENGTH);

                ddi_strcpy((char*)ddiTrainingBuffer,"yAxis_title_VREF:{" );
                for (int i = 0; i < iy ; i++)
                {
                    snprintf((char*)srcBuffer,sizeof(srcBuffer),"%d,", yAxisTitle[i]);
                    ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                }
                snprintf((char*)srcBuffer,sizeof(srcBuffer),"},");
                ddi_strcat((char*)ddiTrainingBuffer, (char*)srcBuffer);
                ddi_firehose_print_log(ddiTrainingBuffer);
                memset(ddiTrainingBuffer,0, TRAINING_BUFFER_LENGTH);
                memset(yAxisTitle,0, Y_AXIS_TITLE_LENGTH);

                if(training_type == DDR_TRAINING_READ)
                {
                    best_coarse_cdc = training_data_ptr->results.rd_dqdqs.coarse_cdc [ddr_freq_index][ch][cs][num_phy];
                    best_fine_cdc = training_data_ptr->results.rd_dqdqs.fine_cdc [ddr_freq_index][ch][cs][num_phy];

                    if(FreqInKhz <= HIGHEST_MPVREF_PRFS_FREQ)
                    {
                        best_vref = training_data_ptr->results.rd_dqdqs.coarse_vref[MPVREF][ch][cs][num_phy];
                    }
                    else
                    {
                        best_vref = training_data_ptr->results.rd_dqdqs.coarse_vref[HPVREF][ch][cs][num_phy];
                    }

                    ddi_firehose_print_log("resultbestcoarsecdc: %d", best_coarse_cdc);
                    ddi_firehose_print_log("resultbestfinecdc: %d", best_fine_cdc);
                    ddi_firehose_print_log("resultbestvref: %d", best_vref);
                }
                else if (training_type == DDR_TRAINING_WRITE)
                {
                    best_coarse_cdc = training_data_ptr->results.wr_dqdqs.coarse_cdc [ddr_freq_index][ch][cs][num_phy];
                    best_fine_cdc = training_data_ptr->results.wr_dqdqs.fine_cdc [ddr_freq_index][ch][cs][num_phy];
                    best_vref = training_data_ptr->results.wr_dqdqs.coarse_vref[ddr_freq_index][ch][cs][num_phy];

                    ddi_firehose_print_log("resultbestcoarsecdc: %d", best_coarse_cdc);
                    ddi_firehose_print_log("resultbestfinecdc: %d", best_fine_cdc);
                    ddi_firehose_print_log("resultbestvref: %d", best_vref);
                }

                ddi_firehose_print_log("FRAME_END");
            }
        }
    }

}

void displayData(void * buffer, uint32 size, void* tArgs, void *training_params_ptr)
{
    print_training_data(buffer,(ddr_training_args*)tArgs, training_params_ptr);
    sendResponse(ACK);
}

boolean ddi_DDRAddressLinesTest(uint8 ch , uint8 cs, char* tag)
{
    uint32 addr_line;
    uint32 data[32] = {0};
    uint32 i;
    uint64* base_addr = NULL;
    uint32 limit = 0;

    boot_log_message("ddi_DDRAddressLinesTest, Start");

    getBaseSize(ch, cs);
    base_addr = (uint64 *)gBase;
    limit = (uint32)gSize;

    snprintf(str_log, 100, "Test Address : 0x%x  Size : 0x%X", base_addr, limit) ;
    boot_log_message(str_log);

    limit = limit - 1;
    limit >>= 3;

    /* write negation of address to each word at (0x1 << n) */
    for (addr_line = 0x1, i = 1; addr_line <= limit; addr_line <<= 1, i++)
    {
        /* save the address prior to overwriting it */
        data[i] = base_addr[addr_line];
        base_addr[addr_line] = ~addr_line;
    }

    /*
    save content at base */
    data[0] = base_addr[0x0];

    /* write negation of address to word at 0x0 */
    base_addr[0x0] = ~0x0;

    /* check if same value is read back from each word */
    for (addr_line = 0x1, i = 1; addr_line <= limit; addr_line <<= 1, i++)
    {
        if (base_addr[addr_line] != ~addr_line)
        {
            boot_log_message("ddi_DDRAddressLinesTest, END");
            return FALSE;
        }
        else
        {
            /* restore the address line's original content */
            base_addr[addr_line] = data[i];
        }
    }

    /* restore base content */
    base_addr[0x0] = data[0];
    boot_log_message("ddi_DDRAddressLinesTest, END");
    return TRUE;

}

boolean ddi_DDRDataLinesTest(uint8 ch , uint8 cs, char* tag)
{
    uint32 pattern;
    uint32 data0, data1;
    uint64* base_addr = NULL;
    uint32 limit = 0;
    boot_log_message("ddi_DDRDataLinesTest, Start");

    getBaseSize(ch, cs);
    base_addr = (uint64 *)gBase;
    limit = (uint32)gSize;

    snprintf(str_log, 100, "Test Address : 0x%x  Size : 0x%X", base_addr, limit) ;
    boot_log_message(str_log);

    limit = limit - 1;
    limit >>= 3;

    /* save the data before writing to it for ram dump case */
    data0 = base_addr[0];
    data1 = base_addr[limit];

    /* test data lines by walking-ones */
    for (pattern = 0x1; pattern != 0x0; pattern <<= 1)
    {
        /* write (0x1 << n) to first word */
        base_addr[0] = pattern;

        /* write ~(0x1 << n) to last word to clear data lines */
        base_addr[limit] = ~pattern;

        /* check if same value is read back */
        if (base_addr[0] != pattern)
        {
            boot_log_message("ddi_DDRDataLinesTest, END");

            return FALSE;
        }

    }

    /* restore the data for ram dump*/
    base_addr[0] = data0;
    base_addr[limit]= data1;

    boot_log_message("ddi_DDRDataLinesTest, END");

    return TRUE;

}

boolean ddi_DDRTestOwnAddr(uint8 ch , uint8 cs, char* tag)
{

    uint32 offset;
    uint64* base_addr = NULL;
    uint32 limit = 0;

    boot_log_message("ddi_DDRTestOwnAddr, Start");

    getBaseSize(ch, cs);
    base_addr = (uint64 *)gBase;
    limit = (uint32)gSize;

    snprintf(str_log, 100, "Test Address : 0x%x  Size : 0x%X", base_addr, limit) ;
    boot_log_message(str_log);

    limit = limit - 1;
    limit >>= 3;

    /* write each word with its own address */
    for (offset = 0; offset <= limit; offset++)
    {
        *(base_addr+offset) = offset;
    }

    /* check if same value is read back from each word */
    for (offset = 0; offset <= limit; offset++)
    {

        if (*(base_addr+offset) != offset)
        {
            boot_log_message("ddi_DDRDataLinesTest, END");
            return FALSE;
        }
    }

    /* write each word with negation of address */
    for (offset = 0; offset <= limit; offset++)
    {
        *(base_addr+offset) = ~offset;
    }

    /* check if same value is read back from each word */
    for (offset = 0; offset <= limit; offset++)
    {
        if (*(base_addr+offset) != ~offset)
        {
            boot_log_message("ddi_DDRDataLinesTest, END");
            return FALSE;
        }
    }

    boot_log_message("ddi_DDRTestOwnAddr, End");
    return TRUE;
}

boolean ddi_ReadTest(uint8 ch, uint8 cs, uint32 loopcnt)
{
    uint32 dataBufferSize = 0;
    uint32* base_addr = NULL;
    uint32 cnt = 0;
    boot_log_message("ddi_ReadTest, Start");

    getBaseSize(ch, cs);
    base_addr = (uint32 *)gBase;

    snprintf(str_log, 100, "Test Address : 0x%x", base_addr) ;
    boot_log_message(str_log);

    snprintf(str_log, 100, "param:%d, %d, %d", ch, cs, loopcnt) ;
    boot_log_message(str_log);

    dataBufferSize = sizeof(dataBuffer)/sizeof(uint32);

    ddi_mem_copy(dataBuffer, base_addr,dataBufferSize, 1);

    while (cnt < loopcnt)
    {
        ddi_mem_copy (base_addr, read_back_pattern, dataBufferSize, 1);
        cnt++;
    }
    boot_log_message("ddi_ReadTest, loop complete");
    boot_log_message("ddi_ReadTest, END");

    return 1;
}

boolean ddi_WriteTest(uint8 ch, uint8 cs, uint32 loopcnt)
{
    uint32 dataBufferSize = 0;
    uint32* base_addr = NULL;
    uint32 cnt = 0;
    boot_log_message("ddi_WriteTest, Start");

    getBaseSize(ch, cs);
    base_addr = (uint32 *)gBase;

    snprintf(str_log, 100, "Test Address : 0x%x", base_addr) ;
    boot_log_message(str_log);

    snprintf(str_log, 100, "param:%d, %d, %d", ch, cs, loopcnt) ;
    boot_log_message(str_log);

    dataBufferSize = sizeof(dataBuffer)/sizeof(uint32);

    while (cnt < loopcnt)
    {
        ddi_mem_copy(dataBuffer, base_addr,dataBufferSize, 1);
        cnt++;
    }
    boot_log_message("ddi_WriteTest, loop complete");

    boot_log_message("ddi_WriteTest, END");

    return TRUE;
}

boolean ddi_ReadWriteTest(uint8 ch, uint8 cs, uint32 loopcnt)
{
    uint32 dataBufferSize = 0;
    uint32* base_addr = NULL;
    uint32 cnt = 0;
    boot_log_message("ddi_ReadWriteTest, Start");

    getBaseSize(ch, cs);
    base_addr = (uint32*)gBase;

    snprintf(str_log, 100, "Test Address : 0x%x", base_addr) ;
    boot_log_message(str_log);

    snprintf(str_log, 100, "param:%d, %d, %d", ch, cs, loopcnt) ;
    boot_log_message(str_log);

    dataBufferSize = sizeof(dataBuffer)/sizeof(uint32);

    while (cnt < loopcnt)
    {
        /* convert base address and limit for accessing memory by word */
        base_addr = (uint32 *)gBase;
        ddi_mem_copy(dataBuffer, base_addr,dataBufferSize, 1);
        ddi_mem_copy (base_addr, read_back_pattern, dataBufferSize, 1);
        cnt++;
    }

    boot_log_message("ddi_ReadWriteTest, loop complete");
    boot_log_message("ddi_ReadWriteTest, END");

    return TRUE;
}


void  ddr_write_pattern(const uint64 base, uint32 test_size, uint32 val)
{
    volatile uint64 * base_addr = (uint64 *)base;
    uint32 i = 0;
    uint32 value;
    value = val;

    if (rdcdc_scan == TRUE)
        Clock_SetBIMCSpeed(boot_ddr_freq);
    else
        Clock_SetBIMCSpeed(bimc_clk_plan[current_clock_idx]);

    // Enable refresh so that memory contents are retained after write
    BIMC_Auto_Refresh_Ctrl (DDR_CH_BOTH, DDR_CS_BOTH, FEATURE_ENABLE);

    switch(PATTERN)
    {
        case BITFLIP_PATTERN:
        case CHECK_BOARD_PATTERN:
        case BITSPREAD_PATTERN:
        case SOLID_BITS_PATTERN:
            for (i = 0; i <= test_size; i++)
            {
                base_addr[i] = (i % 2) == 0 ? value : ~value;
            }
            break;

        case WORKING_ONE_PATTERN:
        case WORKING_ZERO_PATTERN:
            for (i = 0; i <= test_size; i++)
            {
                base_addr[i] = value;
            }
            break;

        case SEQ_INR_PARTTERN:
            for (i = 0; i <= test_size; ++i)
            {
                base_addr[i] = value;
                ++value;
            }
            break;

        case DEFAULT_PATTERN:
            ddr_mem_copy(dataBuffer, (uint32 *)(size_t)base_addr, DDR_PATTERN_LENGTH, 1);
            break;

        case CUSTOMER_PARTTERN:
        case INVALID_PARTTERN:
            break;
    }

}

boolean ddr_read_pattern(const uint64 base, uint32 test_size, uint32 val)
{
    volatile uint64 * base_addr = (uint64 *)base;
    uint32 i = 0;
    uint32 value;
    uint32 temp_value = 0;
    uint32 expect_value = 0;
    uint32 idx = 0;
    uint32 result = 0;

    value = val;

    if (rdcdc_scan == TRUE)
        Clock_SetBIMCSpeed((bimc_clk_plan[current_clock_idx]));
    else
        Clock_SetBIMCSpeed(boot_ddr_freq);

    // Enable refresh so that memory contents are retained after write
    BIMC_Auto_Refresh_Ctrl (DDR_CH_BOTH, DDR_CS_BOTH, FEATURE_ENABLE);

    switch(PATTERN)
    {
        case BITFLIP_PATTERN:
        case CHECK_BOARD_PATTERN:
        case BITSPREAD_PATTERN:
        case SOLID_BITS_PATTERN:
            for (i = 0; i <= test_size; i++)
            {
                if ((~(((uint64)&base_addr[i] >> ADDRESS_DECODE_RANK_BIT_LOCATION & ADDRESS_DECODE_RANK_BIT_WIDTH) ^ ((uint64)which_cs))) && (~(((uint64)&base_addr[i] >> ADDRESS_DECODE_CHANNEL_BIT_LOCATION & ADDRESS_DECODE_CHANNEL_BIT_WIDTH) ^ ((uint64)which_ch))))
            {
                temp_value = base_addr[i];
                expect_value = (i % 2) == 0 ? value : ~value;
                if (temp_value != expect_value)
                {
                    memset(str_log, 0, BUFFER_LENGTH);

                    result = temp_value ^ expect_value;

#ifdef BIT_ERROR_STATISTICS
                    error_statistics |= result;
                    if(rdcdc_scan == TRUE)
                        snprintf(str_log, BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
                    else
                        snprintf(str_log, BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
#else

                    if(rdcdc_scan == TRUE)
                        snprintf(str_log, BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error data:0x%08x, expect data:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), temp_value, expect_value);
                    else
                        snprintf(str_log, BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error data:0x%08x, expect data:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), temp_value, expect_value);
#endif
                    for (idx = 0; idx < 4; idx++)
                    {
                        if ( result & (0xFF << (idx*8)) )
                        {
                            failures[idx]++;
                        }
                    }

#ifdef BIT_ERROR_STATISTICS
                    if(failures[0] && failures[1] && failures[2] && failures[3]) // All bytes are found read/write data error, exit the verify loop.
                        return FALSE;
#else
                    return FALSE;   //Any byte is found read/write data error, exit the verify loop.
#endif
                }
            }
            }
            break;

        case WORKING_ONE_PATTERN:
        case WORKING_ZERO_PATTERN:
            /* verify */
            for (i = 0; i <= test_size; i++)
            {
                if ((~(((uint64)&base_addr[i] >> ADDRESS_DECODE_RANK_BIT_LOCATION & ADDRESS_DECODE_RANK_BIT_WIDTH) ^ ((uint64)which_cs))) && (~(((uint64)&base_addr[i] >> ADDRESS_DECODE_CHANNEL_BIT_LOCATION & ADDRESS_DECODE_CHANNEL_BIT_WIDTH) ^ ((uint64)which_ch))))
            {
                temp_value = base_addr[i];
                if (temp_value != value)
                {
                    memset(str_log, 0, BUFFER_LENGTH);
                    result = temp_value ^ value;

#ifdef BIT_ERROR_STATISTICS
                    error_statistics |= result;
                    if(rdcdc_scan == TRUE)
                        snprintf(str_log, BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
                    else
                        snprintf(str_log, BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
#else

                    if(rdcdc_scan == TRUE)
                        snprintf(str_log,BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN],base_addr + i, temp_value, ((i % 2) == 0 ? value : ~value));
                    else
                        snprintf(str_log,BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN],base_addr + i, temp_value, ((i % 2) == 0 ? value : ~value));
#endif

                    for (idx = 0; idx < 4; idx++)
                    {
                        if ( result & (0xFF << (idx*8)) )
                        {
                            failures[idx]++;
                        }
                    }

#ifdef BIT_ERROR_STATISTICS
                    if(failures[0] && failures[1] && failures[2] && failures[3])
                        return FALSE; // All bytes are found read/write data error, exit the verify loop.
#else
                    return FALSE; //Any byte is found read/write data error, exit the verify loop.
#endif
                }
            }
            }
            break;

        case SEQ_INR_PARTTERN:
            for (i = 0; i <= test_size; ++i)
            {
                if ((~(((uint64)&base_addr[i] >> ADDRESS_DECODE_RANK_BIT_LOCATION & ADDRESS_DECODE_RANK_BIT_WIDTH) ^ ((uint64)which_cs))) && (~(((uint64)&base_addr[i] >> ADDRESS_DECODE_CHANNEL_BIT_LOCATION & ADDRESS_DECODE_CHANNEL_BIT_WIDTH) ^ ((uint64)which_ch))))
            {
                temp_value = base_addr[i];
                if (temp_value != value)
                {
                    memset(str_log, 0, BUFFER_LENGTH);
                    result = temp_value ^ value;

#ifdef BIT_ERROR_STATISTICS
                    error_statistics |= result;
                    if(rdcdc_scan == TRUE)
                        snprintf(str_log, BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
                    else
                        snprintf(str_log, BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], (base_addr+i), error_statistics, 0x0);
#else

                    if(rdcdc_scan == TRUE)
                        snprintf(str_log,BUFFER_LENGTH, "[%s]read failed at address:address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN], base_addr + i, temp_value, value);
                    else
                        snprintf(str_log,BUFFER_LENGTH, "[%s]write failed at address:address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN],  base_addr + i, temp_value, value);
#endif

                    for (idx = 0; idx < 4; idx++)
                    {
                        if ( result & (0xFF << (idx*8)) )
                        {
                            failures[idx]++;
                        }
                    }

#ifdef BIT_ERROR_STATISTICS
                    if(failures[0] && failures[1] && failures[2] && failures[3])
                        return FALSE; // All bytes are found read/write data error, exit the verify loop.
#else
                    return FALSE; //Any byte is found read/write data error, exit the verify loop.
#endif
                }
                }

                ++value;
            }
            break;

        case DEFAULT_PATTERN:
            ddr_mem_copy ((uint32 *)(size_t)base_addr, read_back_pattern, DDR_PATTERN_LENGTH, 1);
            for (i = 0; i < DDR_PATTERN_LENGTH; i ++)
            {

                if ((~(((uint64)&base_addr[i] >> ADDRESS_DECODE_RANK_BIT_LOCATION & ADDRESS_DECODE_RANK_BIT_WIDTH) ^ ((uint64)which_cs))) && (~(((uint64)&base_addr[i] >> ADDRESS_DECODE_CHANNEL_BIT_LOCATION & ADDRESS_DECODE_CHANNEL_BIT_WIDTH) ^ ((uint64)which_ch))))
                {
                temp_value = read_back_pattern[i];

                if(temp_value != dataBuffer[i])
                {
                    memset(str_log, 0, BUFFER_LENGTH);

                    result |= dataBuffer[i] ^ temp_value;

#ifdef BIT_ERROR_STATISTICS
                    error_statistics |= result;
                    if(rdcdc_scan == TRUE)
                        snprintf(str_log, BUFFER_LENGTH, "[%s]read failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], ((uint32 *)base_addr+i), error_statistics, 0x0);
                    else
                        snprintf(str_log, BUFFER_LENGTH, "[%s]write failed at address:0x%llx, error result:0x%08x, expect result:0x%08x",
                                 pattern_name[PATTERN], ((uint32 *)base_addr+i), error_statistics, 0x0);
#else

                    if(rdcdc_scan == TRUE)
                        snprintf(str_log,BUFFER_LENGTH, "[%s]read failed at address:address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN], ((uint32 *)base_addr + i), temp_value, value);
                    else
                        snprintf(str_log,BUFFER_LENGTH, "[%s]write failed at address:address:0x%llx, error data:0x%08x, expect data:0x%08x\r\n",
                                 pattern_name[PATTERN],  ((uint32 *)base_addr + i), temp_value, value);
#endif

                    for (idx = 0; idx < 4; idx++)
                    {
                        if ( result & (0xFF << (idx*8)) )
                        {
                            failures[idx]++;
                        }
                    }

#ifdef BIT_ERROR_STATISTICS
                    if(failures[0] && failures[1] && failures[2] && failures[3])
                        return FALSE; // All bytes are found read/write data error, exit the verify loop.
#else
                    return FALSE; //Any byte is found read/write data error, exit the verify loop.
#endif
                }
                }
            }

            break;

        case CUSTOMER_PARTTERN:
        case INVALID_PARTTERN:
            break;
    }

    if(failures[0]||failures[1]||failures[2]||failures[3])
        return FALSE;

    return TRUE;
}

boolean ddr_test_default(const uint64 base, const uint32 size)
{
    uint32 val = 0;
    const uint8 LOOP_CYCLES = 64;
    uint32 i = 0;

    PATTERN = DEFAULT_PATTERN;

    for (i = 0; i < LOOP_CYCLES; ++i)
    {
        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)== FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_test_solid_bits(const uint64 base, const uint32 size)
{
    uint32 val = 0;
    const uint32 UINT32_ZERO = 0x0;
    const uint8 LOOP_CYCLES = 64;
    uint32 i = 0;

    PATTERN = SOLID_BITS_PATTERN;

    for (i = 0; i < LOOP_CYCLES; ++i)
    {
        val = (i % 2) == 0 ? (~UINT32_ZERO) : UINT32_ZERO;

        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)== FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_test_check_board(const uint64 base, const uint32 size)
{
    const uint32 CHECK_BOARD = 0x55555555;
    const uint8 LOOP_CYCLES = 64;
    uint32 i = 0;
    uint32 val = CHECK_BOARD;

    PATTERN = CHECK_BOARD_PATTERN;

    for (i = 0; i < LOOP_CYCLES; ++i)
    {
        val = (i % 2) == 0 ? (~CHECK_BOARD) : CHECK_BOARD;

        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)== FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_test_bit_spread(const uint64 base, const uint32 size)
{
    const uint8 UINT32_LEN = 32;
    const uint32 ONE = 0x1;
    uint8  j = 0;
    uint32 val = 0;

    PATTERN = BITSPREAD_PATTERN;

    for (j = 0; j < UINT32_LEN * 2; ++j)
    {
        val = (ONE << j) | (ONE << (j + 2));

        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)== FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_test_bit_flip(const uint64 base, const uint32 size)
{
    const uint8 UINT32_LEN = 32;
    const uint32 ONE = 0x1;
    uint8 j = 0;
    uint32 val = ONE;

    PATTERN = BITFLIP_PATTERN;

    for (j = 0; j < UINT32_LEN; ++j)
    {
        val = ONE << j;

        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)==FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_test_walking_one(const uint64 base, const uint32 size)
{
    const uint8 UINT32_LEN = 32;
    const uint32 ONE = 0x1;
    uint8  j = 0;
    uint32 val = 0;

    PATTERN = WORKING_ONE_PATTERN;

    for (j = 0; j < UINT32_LEN * 2; ++j)
    {
        if (j < UINT32_LEN)
            val = (ONE << j) ;
        else
            val = (ONE << (UINT32_LEN * 2 - 1 - j));

        ddr_write_pattern(base, size, val);


        /* verify */
        if(ddr_read_pattern(base, size, val) == FALSE)
            return FALSE;
    }


    return TRUE;
}

boolean ddr_test_walking_zero(const uint64 base, const uint32 size)
{
    const uint8 UINT32_LEN = 32;
    const uint32 ONE = 0x1;
    uint8  j = 0;
    uint32 val = 0;

    PATTERN = WORKING_ZERO_PATTERN;

    for (j = 0; j < UINT32_LEN * 2; ++j)
    {
        if (j < UINT32_LEN)
            val = ~(ONE << j) ;
        else
            val = ~(ONE << (UINT32_LEN * 2 - 1 - j));
        ddr_write_pattern(base, size, val);

        /* verify */
        if(ddr_read_pattern(base, size, val)==FALSE)
            return FALSE;
    }

    return TRUE;
}

boolean ddr_function_defect_test(const uint64 ddr_base, const uint32 size)
{
    static funcDefectTest_s function_defect_test[] =
    {
        {"Training pattern", ddr_test_default},
        {"Solid bits", ddr_test_solid_bits},
        {"Checkerboard", ddr_test_check_board},
        {"Bit Spread", ddr_test_bit_spread},
        {"Bit Flip", ddr_test_bit_flip},
        {"Walking ones", ddr_test_walking_one},
        {"Walking zeros", ddr_test_walking_zero}
    };

    uint8 ddr_function_defect_test_num = sizeof(function_defect_test) / sizeof(*function_defect_test);
    uint8 i= 0;

    for(i=0; i < ddr_function_defect_test_num; i++)
    {
        if(function_defect_test[i].name && function_defect_test[i].fp)
        {
            if(!(function_defect_test[i].fp(ddr_base, size)))
            {
                return  FALSE;
            }
        }
    }

    return TRUE;
}

void ddi_Stress_Test(uint8 ch, uint8 cs, uint32 loopcnt)
{
    uint64 base_addr = 0;
    uint32 test_size = 0;
    uint8 i = 0;

    getBaseSize(ch, cs);
    base_addr = (uint64)gBase;
    test_size = (uint32)0x100000;

    //snprintf(str_log, 100, "Test Address : 0x%llx  Size : 0x%x\n", base_addr, test_size) ;
    //boot_log_message(str_log);

    for( i = 0; i < loopcnt; i++)
    {
        ddr_function_defect_test(base_addr, (test_size -1) >> 3);
    }
}

void ddr_tuning_log_out(uint32 failures[4])
{
    memset(str,0,BUFFER_LENGTH);
    if( failures[0] == 0 && failures[1] == 0 && failures[2] == 0 && failures[3] == 0)
    {
        snprintf(str, BUFFER_LENGTH, "%4u, %4u, %4u,"
                 "%3u,%3u,%3u,%3u.[log]%s\r\n",
                 current_vref, current_coarse_cdc, current_fine_cdc,
                 failures[0], failures[1], failures[2], failures[3],"[stress test]PASS");
    }
    else
    {
        snprintf(str, BUFFER_LENGTH, "%4u, %4u, %4u,"
                 "%3u,%3u,%3u,%3u.[log]%s\r\n",
                 current_vref, current_coarse_cdc, current_fine_cdc,
                 failures[0], failures[1], failures[2], failures[3], str_log);
    }
    ddi_firehose_print_log(str);
    memset(str_log, 0, BUFFER_LENGTH);
}

boolean ddi_DDR_training_restore(DDR_STRUCT *ddr, DDR_CHANNEL channel, DDR_CHIPSELECT chip_select)
{
    DDR_CHIPSELECT qualified_cs = DDR_CS_BOTH;

    DDRSS_training_restore_lpddr4 (ddr, channel, chip_select);

    qualified_cs = (DDR_CHIPSELECT)(chip_select & ddr->detected_ddr_device[0].populated_chipselect);

    // Refresh rate control through TUF bit override
    BIMC_Refresh_Rate_Ctrl (channel, qualified_cs);
    // Enables DownTime requests
    BIMC_Downtime_Request_Ctrl ( channel, 1);

    // Add Power Collapse Save mode after training is done.
    ddr_printf(DDR_NORMAL, "DDR PHY Power Collapse SAVE\n\n");

    // 200MHz is ok to use, since this parameter does not matter for SAVE mode.
    ddr_external_set_clk_speed (200000);
    DDR_PHY_rtn_pcc_pre_collapse (ddr, PHY_POWER_CLPS_SAVE, 200000);
    DDR_PHY_rtn_pcc_post_collapse(ddr, PHY_POWER_CLPS_SAVE, 200000);

    return TRUE;
}

boolean ddi_DQ_Read_Vref_CDC_Shmoo(uint8 ch, uint8 cs, uint8 clock_idx, uint8 start_vref, uint8 end_vref,  uint8 vref_step, uint8 start_coarse_cdc, uint8 end_coarse_cdc)
{
    uint8 vref = 0;
    uint8 coarse_cdc = 0;
    uint8 fine_cdc = 0;
    uint8 byte_lane = 0;
    uint8 max_fine = 16;
    uint8 prfs_idx= 0;
    uint8 current_prfs_idx = 0;
    //uint32 reg_offset_shke = 0;
    boolean result = TRUE;
    training_data *training_data_ptr;
    training_params_t training_params;

    uint8 coarse_cdc_ori  [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];
    uint8 fine_cdc_ori    [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];
    uint8 coarse_vref_ori [VREF_MP_HP][NUM_CH][NUM_CS][NUM_DQ_PCH];
    current_vref = 0;
    current_coarse_cdc = 0;
    current_fine_cdc = 0;
    current_clock_idx = clock_idx;

    for(prfs_idx = PRFS_BAND_THRESHOLD_NUMBER - 1; prfs_idx > 0; prfs_idx--)
    {
        if (bimc_clk_plan[clock_idx] >= PRFS_BAND_THRESHOLD[prfs_idx])
            break;
    }

    if(prfs_idx == PRFS_BAND_THRESHOLD_NUMBER - 1)
        current_prfs_idx = prfs_idx;
    else
        current_prfs_idx = prfs_idx + 1;

    snprintf(str_log, 100, "current_prfs_idx:%d   clock threshold:0x%d", current_prfs_idx, PRFS_BAND_THRESHOLD[current_prfs_idx]);
    boot_log_message(str_log);

    DDRSS_set_training_params((training_params_t *)&training_params);

    if(FALSE == retrain_status)  //only do DDR training only once
    {
        DDRSS_boot_training_lpddr4(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
        retrain_status = TRUE;
    }

    training_data_ptr = (training_data *)(&share_data->flash_params.training_data);
    share_data->flash_params.version = TARGET_DDR_SYSTEM_FIRMWARE_VERSION;

    memset(coarse_cdc_ori, 0, sizeof(coarse_cdc_ori));
    memset(fine_cdc_ori, 0, sizeof(fine_cdc_ori));
    memset(coarse_vref_ori, 0, sizeof(coarse_vref_ori));
    memcpy(coarse_cdc_ori, training_data_ptr->results.rd_dqdqs.coarse_cdc, sizeof(coarse_cdc_ori));
    memcpy(fine_cdc_ori, training_data_ptr->results.rd_dqdqs.fine_cdc, sizeof(fine_cdc_ori));
    memcpy(coarse_vref_ori, training_data_ptr->results.rd_dqdqs.coarse_vref, sizeof(coarse_vref_ori));
    max_fine = COARSE_STEP_IN_PS / FINE_STEP_IN_PS;

    if (end_coarse_cdc >= ((CONVERT_CYC_TO_PS / bimc_clk_plan[current_clock_idx]) / COARSE_STEP_IN_PS))
        end_coarse_cdc = ((CONVERT_CYC_TO_PS / bimc_clk_plan[current_clock_idx]) / COARSE_STEP_IN_PS);
    // Set the Vref scan range based on the frequency
    if(bimc_clk_plan[current_clock_idx] <= HIGHEST_MPVREF_PRFS_FREQ)  // <= 800Mhz, Vref scan range min 15, max 45.
    {
        if(start_vref < training_params.rd_dqdqs.coarse_vref_start_mprx)
            start_vref = training_params.rd_dqdqs.coarse_vref_start_mprx;

        if(start_vref > (training_params.rd_dqdqs.coarse_vref_start_mprx + training_params.rd_dqdqs.coarse_vref_max_mprx))
            start_vref = training_params.rd_dqdqs.coarse_vref_start_mprx + training_params.rd_dqdqs.coarse_vref_max_mprx;

        if(end_vref > (training_params.rd_dqdqs.coarse_vref_start_mprx + training_params.rd_dqdqs.coarse_vref_max_mprx))
            end_vref = training_params.rd_dqdqs.coarse_vref_start_mprx + training_params.rd_dqdqs.coarse_vref_max_mprx;

        if(end_vref < start_vref)
            end_vref = start_vref;
    }
    else  // >800Mhz  Vref scan range min 2, max 11
    {
        if(start_vref < 2)
            start_vref = 2;

        if(start_vref > 11)
            start_vref = 11;

        if(end_vref > 11)
            end_vref = 11;

        if(end_vref < start_vref)
            end_vref = start_vref;
    }

    memset(str_log, 0, BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$CH(%4u, 0, %4u)\n", ch, ch);
    ddi_firehose_print_log(str_log);

    memset(str_log, 0, BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$CS(%4u, 0, %4u)\n", cs, cs);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$Clock(%4u, 0, %4u)\n", bimc_clk_plan[current_clock_idx], bimc_clk_plan[current_clock_idx]);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$Vref(%4u, %4u, %4u)\n", start_vref, vref_step, end_vref);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$coarsecdc(%4u, %4u, %4u)\n", start_coarse_cdc, 1, end_coarse_cdc);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$finecdc(%4u, %4u, %4u)\n", 0, 1, max_fine);
    ddi_firehose_print_log(str_log);


    which_ch = ch;
    which_cs = cs;

    ddi_firehose_print_log("Vref, coarse CDC, fine CDC, byte0, byte1, byte2, byte3.[log]test result");

    for(vref = start_vref; vref <= end_vref; vref = vref + vref_step)
    {
        for(coarse_cdc = start_coarse_cdc; coarse_cdc <= end_coarse_cdc; coarse_cdc ++)
        {
            for(fine_cdc = 0; fine_cdc <= max_fine; fine_cdc ++)
            {
                for(int ch_idx = 0; ch_idx < NUM_CH; ch_idx ++)
                {
                    for(int cs_idx = 0; cs_idx < NUM_CS; cs_idx ++)
                    {
                        for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane++)
                        {
                            if(bimc_clk_plan[current_clock_idx] <= HIGHEST_MPVREF_PRFS_FREQ)
                                training_data_ptr->results.rd_dqdqs.coarse_vref[MPVREF][ch_idx][cs_idx][byte_lane] = vref;
                            else
                                training_data_ptr->results.rd_dqdqs.coarse_vref[HPVREF][ch_idx][cs_idx][byte_lane] = vref;

                            training_data_ptr->results.rd_dqdqs.coarse_cdc[current_prfs_idx][ch_idx][cs_idx][byte_lane] = coarse_cdc;
                            training_data_ptr->results.rd_dqdqs.fine_cdc[current_prfs_idx][ch_idx][cs_idx][byte_lane] = fine_cdc;
                        }
                    }
                }

                rdcdc_scan = TRUE;
                current_vref = vref;
                current_coarse_cdc = coarse_cdc;
                current_fine_cdc = fine_cdc;

                failures[0] = failures[1] = failures[2] = failures[3] = 0;
                error_statistics = 0;

                Clock_SetBIMCSpeed(boot_ddr_freq);
                //HAL_DDR_Boot_Training_Restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
                ddi_DDR_training_restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
                ddi_Stress_Test(ch, cs, 1);
                Clock_SetBIMCSpeed(boot_ddr_freq);
                ddr_tuning_log_out(failures);
            }
        }
    }
    memcpy(training_data_ptr->results.rd_dqdqs.coarse_cdc, coarse_cdc_ori, sizeof(coarse_cdc_ori));
    memcpy(training_data_ptr->results.rd_dqdqs.fine_cdc, fine_cdc_ori, sizeof(fine_cdc_ori));
    memcpy(training_data_ptr->results.rd_dqdqs.coarse_vref, coarse_vref_ori, sizeof(coarse_vref_ori));
    HAL_DDR_Boot_Training_Restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);

    return result;
}

boolean ddi_DQ_Write_Vref_CDC_Shmoo(uint8 ch, uint8 cs, uint8 clock_idx, uint8 start_vref, uint8 end_vref, uint8 vref_step, uint8 start_coarse_cdc, uint8 end_coarse_cdc)
{
    uint8 vref = 0;
    uint8 coarse_cdc = 0;
    uint8 fine_cdc = 0;
    uint8 byte_lane = 0;
    uint8 max_fine = 16;
    uint8 prfs_idx= 0;
    uint8 current_prfs_idx = 0;
    uint8  training_ddr_freq_indx = 0;
    uint8  max_prfs_index = 0;
    //uint32 reg_offset_shke = 0;

    boolean result = TRUE;
    training_data *training_data_ptr;

    uint8 coarse_cdc_ori [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];
    uint8 fine_cdc_ori   [NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_DQ_PCH];
    uint8 coarse_best_eye_vref_value_ori[NUM_PRFS_BANDS][NUM_CH][NUM_CS][NUM_CA_PCH];
    current_vref = 0;
    current_coarse_cdc = 0;
    current_fine_cdc = 0;
    current_clock_idx = clock_idx;

    for(prfs_idx = PRFS_BAND_THRESHOLD_NUMBER -1; prfs_idx > 0; prfs_idx--)
    {
        if (bimc_clk_plan[clock_idx] >= PRFS_BAND_THRESHOLD[prfs_idx])
            break;
    }

    if(prfs_idx == PRFS_BAND_THRESHOLD_NUMBER - 1)
        current_prfs_idx = prfs_idx;
    else
        current_prfs_idx = prfs_idx + 1;

    snprintf(str_log, 100, "current_prfs_idx:%d", current_prfs_idx) ;
    boot_log_message(str_log);

    //search through frequency table to automatically identify training frequency
    for (training_ddr_freq_indx = 0; training_ddr_freq_indx < share_data->misc.ddr_num_clock_levels; training_ddr_freq_indx++)
    {
        if ((share_data->misc.clock_plan[training_ddr_freq_indx].clk_freq_in_khz) > PRFS_BAND_THRESHOLD[max_prfs_index])
        {
            max_prfs_index++;
        }
    }

    if(FALSE == retrain_status)  //only do DDR training only once
    {
        DDRSS_boot_training_lpddr4(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
        retrain_status = TRUE;
    }

    training_data_ptr = (training_data *)(&share_data->flash_params.training_data);
    memset(coarse_cdc_ori, 0, sizeof(coarse_cdc_ori));
    memset(fine_cdc_ori, 0, sizeof(fine_cdc_ori));
    memset(coarse_best_eye_vref_value_ori, 0, sizeof(coarse_best_eye_vref_value_ori));
    memcpy(coarse_cdc_ori, training_data_ptr->results.wr_dqdqs.coarse_cdc, sizeof(coarse_cdc_ori));
    memcpy(fine_cdc_ori, training_data_ptr->results.wr_dqdqs.fine_cdc, sizeof(fine_cdc_ori));
    memcpy(coarse_best_eye_vref_value_ori, training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value, sizeof(coarse_best_eye_vref_value_ori));
    share_data->flash_params.version = TARGET_DDR_SYSTEM_FIRMWARE_VERSION;

    max_fine = COARSE_STEP_IN_PS / FINE_STEP_IN_PS;
    if (end_coarse_cdc >= ((CONVERT_CYC_TO_PS / bimc_clk_plan[current_clock_idx]) / COARSE_STEP_IN_PS))
        end_coarse_cdc = ((CONVERT_CYC_TO_PS / bimc_clk_plan[current_clock_idx]) / COARSE_STEP_IN_PS);

    memset(str_log, 0, BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$CH(%4u, 0, %4u)\n", ch, ch);
    ddi_firehose_print_log(str_log);

    memset(str_log, 0, BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$CS(%4u, 0, %4u)\n", cs, cs);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$Clock(%4u, 0, %4u)\n", bimc_clk_plan[current_clock_idx], bimc_clk_plan[current_clock_idx]);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$Vref(%4u, %4u, %4u)\n", start_vref, vref_step, end_vref);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$coarsecdc(%4u, %4u, %4u)\n", start_coarse_cdc, 1, end_coarse_cdc);
    ddi_firehose_print_log(str_log);

    memset(str_log,0,BUFFER_LENGTH);
    snprintf(str_log, BUFFER_LENGTH, "$finecdc(%4u, %4u, %4u)\n", 0, 1, max_fine);
    ddi_firehose_print_log(str_log);

    ddi_firehose_print_log("Vref, coarse CDC, fine CDC, byte0, byte1, byte2, byte3.[log]test result");

    which_ch = ch;
    which_cs = cs;
    for(vref = start_vref; vref <= end_vref; vref = vref + vref_step)
    {
        for(coarse_cdc = start_coarse_cdc; coarse_cdc <= end_coarse_cdc; coarse_cdc ++)
        {
            for(fine_cdc = 0; fine_cdc <= max_fine; fine_cdc ++)
            {
                //for(int ch_idx = 0; ch_idx < NUM_CH; ch_idx ++)
                {
                    //for(int cs_idx = 0; cs_idx < NUM_CS; cs_idx ++)
                    {
                        int ch_idx = ch;
                        int cs_idx = cs;
                        for(byte_lane = 0; byte_lane < NUM_DQ_PCH; byte_lane ++)
                        {
                            //Update the trained data Vref for max FSP0 freq(768MHz) and FSP1 freq(1804MHz)
                            if(bimc_clk_plan[current_clock_idx] <= HIGHEST_MPVREF_PRFS_FREQ)
                            {
                                training_data_ptr->results.wr_dqdqs.coarse_vref[FSP_THRESHOLD_PRFS_BAND][ch_idx][cs_idx][byte_lane] = vref;
                            }
                            else
                                training_data_ptr->results.wr_dqdqs.coarse_vref[max_prfs_index][ch_idx][cs_idx][byte_lane] = vref;

                            training_data_ptr->results.wr_dqdqs.coarse_cdc[current_prfs_idx][ch_idx][cs_idx][byte_lane] = coarse_cdc;
                            training_data_ptr->results.wr_dqdqs.fine_cdc[current_prfs_idx][ch_idx][cs_idx][byte_lane] = fine_cdc;
                        }
                    }
                }

                rdcdc_scan = FALSE;
                current_vref = vref;
                current_coarse_cdc = coarse_cdc;
                current_fine_cdc = fine_cdc;
                failures[0] = failures[1] = failures[2] = failures[3] = 0;
                error_statistics = 0;

                Clock_SetBIMCSpeed(boot_ddr_freq);
                //HAL_DDR_Boot_Training_Restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
                ddi_DDR_training_restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
                ddi_Stress_Test(ch, cs, 1);
                Clock_SetBIMCSpeed(boot_ddr_freq);
                ddr_tuning_log_out(failures);
            }
        }
    }

    memcpy(training_data_ptr->results.wr_dqdqs.coarse_cdc, coarse_cdc_ori, sizeof(coarse_cdc_ori));
    memcpy(training_data_ptr->results.wr_dqdqs.fine_cdc, fine_cdc_ori, sizeof(fine_cdc_ori));
    memcpy(training_data_ptr->results.wr_dqdqs.coarse_best_eye_vref_value, coarse_best_eye_vref_value_ori, sizeof(coarse_best_eye_vref_value_ori));
    HAL_DDR_Boot_Training_Restore(share_data, DDR_CH_BOTH, DDR_CS_BOTH);
    return result;
}

void retrainDDR()
{
    uint8 level = sizeof(MRParams)/sizeof(MRParams[0]);
    uint8 j = 0;

    for (int  i  = 0; i < level; i++)
    {
        share_data->ddi_buf[j+36] = MRParams[i].freq_switch_range_in_kHz;
        if (MRParams[i].mr3Val != -1 && MRParams[i].mr3Val != 0xFFFFFFFF )
        {
            share_data->ddi_buf[(j + 1) + 36] = MRParams[i].mr3Val & 0xFF;
        }
        else
        {
            share_data->ddi_buf[(j + 1) + 36] = 0xFF;
        }

        if (MRParams[i].mr11Val != -1 && MRParams[i].mr11Val != 0xFFFFFFFF)
        {
            share_data->ddi_buf[(j+1)+36] = share_data->ddi_buf[(j+1)+36] | ((MRParams[i].mr11Val & 0xFF)<<8);
        }
        else
        {
            share_data->ddi_buf[(j+1)+36] = share_data->ddi_buf[(j+1)+36] | (0xFF<<8);
        }
        j = j+2;
    }

    share_data->ddi_buf[0] = DDI_MAGIC_RETRAIN_REQUIRED_A;
    share_data->ddi_buf[1] = DDI_MAGIC_RETRAIN_REQUIRED_B;

    // flush the region containing the share data sctructure
    dcache_flush_region((void *)share_data, sizeof(*share_data));

    //busywait(10000);
    deInitTransport();
    //busywait(10000);
    boot_hw_reset(BOOT_WARM_RESET_TYPE);
    //boot_enable_led(DDR_TRAINING_LED, TRUE);
    //boot_ddr_do_ddr_training();
    //boot_enable_led(DDR_TRAINING_LED, FALSE);
}

