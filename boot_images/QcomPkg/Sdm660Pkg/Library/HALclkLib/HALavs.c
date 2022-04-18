/*
============================================================================

                A D A P T I V E   V O L T A G E   S C A L I N G
              H A R D W A R E   A B S T R A C T I O N   L A Y E R

FILE:         HALavs.c

DESCRIPTION:
              This file contains hardware abstraction APIs for the AVS
              subsystem.

============================================================================

                             Edit History


when       who     what, where, why
--------   ---     ---------------------------------------------------------
10/29/14   jb      Created NULL lib for 8996
03/15/11   dcf     Restructured for new clock driver and directory structure.
11/03/10   dcf     Increase retry count for voltage verification  from 5 to
                   200 to ensure enough time is given.  This value should be
                   much greater than what is actually needed, but 5 is too
                   low.
05/12/10   dcf     Created.

============================================================================
            Copyright (c) 2011-2014 QUALCOMM Technologies Incorporated.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
============================================================================
*/

/*==========================================================================
                             INCLUDE FILES FOR MODULE
==========================================================================*/

#include <HALcomdef.h>
#include <HALhwio.h>
#include "HALavsHWIOSAW4.h"
#include "Library/HALclkSharedLib/HALavs.h"
#include "DDIChipInfo.h"


/*==========================================================================
                     DEFINES AND STRUCTURES FOR THIS MODULE
==========================================================================*/

/*
 * Generic register read/write macros.
 */

#define HAL_AVS_WRITE(coreaddr, reg, field, value) \
  outpdw((coreaddr), (inpdw((coreaddr)) & ~(HWIO_##reg##_##field##_BMSK)) |\
  ((HWIO_##reg##_##field##_BMSK) & ((value) << HWIO_##reg##_##field##_SHFT)))


#define HAL_AVS_READ(coreaddr, reg, field) \
  ((inpdw((coreaddr)) & (HWIO_##reg##_##field##_BMSK)) >> \
  (HWIO_##reg##_##field##_SHFT))


#define HAL_AVS_ABS(v1, v2) ((v1)>(v2)?((v1)-(v2)):((v2)-(v1)))


/* Reference select for PMIC_DATA. */
#define HAL_AVS_PM8058_VDD_REF_SEL 0xE0
#define HAL_AVS_PMIC_VDD_BAND2_SEL 0x80

#define HAL_AVS_SAW4_PMIC_WRITE_RETRY_COUNT 200

#if 0
/* PMIC MODE_CTL Register Values */
#define HAL_AVS_POWER_MODE_PWM_FIELD_VAL  0x80
#define HAL_AVS_POWER_MODE_AUTO_FIELD_VAL 0x40
#endif

#define HAL_AVS_SAW4_VCTL_REG_VCTL_ADR_IDX 0x0
#define HAL_AVS_SAW4_VCTL_REG_PHASE_ADR_IDX 0x1
#define HAL_AVS_SAW4_VCTL_REG_MODE_ADR_IDX 0x2

/*
 * AVS register type.  Each core will have it's own offset to access
 * AVS registers.
 */
typedef struct
{
  size_t nVddCtl;       /* Voltage nControl register (SAW4_VCTL) */
  size_t nPMICStatus;   /* PMIC status register (SAW4_PMIC_STS) */
  size_t nAVSStatus;    /* AVS status register (SAW4_AVS_STS) */
  size_t nConfig;       /* AVS nConfiguration register (SAW4_CFG) */
  size_t nControl;      /* AVS Control register (SAW4_AVS_CTL) */
  size_t nLimit;        /* Limit register for AVS VLVL (SAW4_AVS_LIMIT) */
  size_t nDelay;        /* Delay programming for AVS (SAW4_AVS_DLY) */

}HAL_avs_RegAddrType;

/* Default PMIC configuration values */
#define HAL_AVS_PMSdm660_VOLTAGE_STEP_SIZE  1000    // in uV
#define HAL_AVS_PMSdm660_VOLTAGE_OFFSET     768000   // in uV



/*==========================================================================
                     DECLARATIONS USED IN THIS MODULE
==========================================================================*/

static HAL_avs_RegAddrType asAVSRegs[HAL_AVS_NUM_CORES];

static HAL_avs_CoreDataType ganCoreData[HAL_AVS_NUM_CORES];

static HAL_avs_ContextType gHALAVSContext =
{
  /* .BusyWait             = */ NULL,
  /* .pCoreData            = */ ganCoreData,
  /* .nCurrVoltageVal      = */ 0,
  /* .nCurrPhaseVal        = */ 0,
  /* .nPmicVoltageStepSize = */ 0xDEADDEAD,
  /* .nPmicVoltageOffset   = */ 0xDEADDEAD,
  /* .nChipId              = */ 0,
  /* .nChipVersion         = */ 0
};




/*============================================================================
                     FUNCTION DEFINITIONS FOR THIS MODULE
============================================================================*/


/* ===========================================================================
**  HAL_avs_GetVddSettleTimeUS
**
**  Description:  Returns the amount of time to delay based on the voltage
**                delta passed in.
** ======================================================================== */

uint32 HAL_avs_GetVddSettleTimeUS(HAL_avs_CoreType eCore, uint32 nDeltaUS)
{
  uint32 nDelayTimeUS = 0;
  if( nDeltaUS != 0)
  {
    switch( gHALAVSContext.pCoreData[eCore].ePMIC )
    {
      case HAL_AVS_PMSdm660_SUPPORT:
        /*
         * Formula: us = uV * 10 us / 25000 uV
         *
         * NOTE: We always compute a delay that is a multiple of 10 us.
         *
         * NOTE: We add 25000 uV in the beginning because we
         *       divide out the remainder in the final step.
         */

        /* Use formula 25000uV/10us. */
        nDelayTimeUS = nDeltaUS + 25000;
        nDelayTimeUS *= 10;
        nDelayTimeUS /= 25000;

        /* Now divide down to nearest multiple of 10 */
        nDelayTimeUS /= 10;
        nDelayTimeUS *= 10;

        return nDelayTimeUS ;

      default:
        return 0;
    }
  }
  return 0;

} /* END HAL_avs_GetVddSettleTimeUS */


/* ===========================================================================
**  HAL_avs_GetVoltage
**
**  Description:  Returns PMIC voltage that corresponds to PMIC data.
** ======================================================================== */

uint32 HAL_avs_GetVoltage(HAL_avs_CoreType eCore, uint32 nPMICData)
{
  switch( gHALAVSContext.pCoreData[eCore].ePMIC )
  {
    case HAL_AVS_PMSdm660_SUPPORT:
      return gHALAVSContext.nPmicVoltageStepSize *
             nPMICData + gHALAVSContext.nPmicVoltageOffset;
    default:
      return 0;
  }

} /* HAL_avs_GetVoltage */


/* ===========================================================================
**  HAL_avs_GetPMICFormat
**
**  Description:  Returns the PMIC format to be used with the SAW_VCTL reg.
** ======================================================================== */

uint32 HAL_avs_GetPMICFormat(HAL_avs_CoreType eCore, uint32 nVoltage)
{
  switch( gHALAVSContext.pCoreData[eCore].ePMIC )
  {
    case HAL_AVS_PMSdm660_SUPPORT:
      if (nVoltage < gHALAVSContext.nPmicVoltageOffset || gHALAVSContext.nPmicVoltageStepSize == 0)
      {
        return 0;
      }
      return (nVoltage - gHALAVSContext.nPmicVoltageOffset) / gHALAVSContext.nPmicVoltageStepSize;

    default:
      return (uint32)-1;
  }

} /* HAL_avs_GetPMICFormat */


/* ===========================================================================
**  HAL_avs_FormatPMICData
**
**  Description:  Converts a voltage in uV into PMIC_DATA format for supported
**  PMICs.
** ======================================================================== */

uint32 HAL_avs_FormatPMICData(HAL_avs_CoreType eCore, uint32 nVoltage)
{
  switch( gHALAVSContext.pCoreData[eCore].ePMIC )
  {
    case HAL_AVS_PMSdm660_SUPPORT:
        return HAL_avs_GetPMICFormat(eCore, nVoltage);

    default:
      return (uint32)-1;
  }

}/* END HAL_avs_FormatPMICData */


/* ===========================================================================
**  HAL_avs_FormatPhaseCount
**
**  Description:  Converts a phase count into PMIC format.
** ======================================================================== */

static uint32 HAL_avs_FormatPhaseCount (HAL_avs_CoreType eCore, uint32 nPhases)
{
  switch (gHALAVSContext.pCoreData[eCore].ePMIC)
  {
    case HAL_AVS_PMSdm660_SUPPORT:
      switch (nPhases)
      {
        case 0:
        case 1: return 0;
        case 2: return 1;
        case 3:
        case 4:
        default:
          return 3;
      }

    default:
      return 0;
  }

} /* END HAL_avs_FormatPhaseCount */


/* ===========================================================================
**  HAL_avs_GetPhaseCount
**
**  Description:  Converts PMIC data value into the number of phases.
** ======================================================================== */

static uint32 HAL_avs_GetPhaseCount (HAL_avs_CoreType eCore, uint32 nPMICData)
{
  switch (gHALAVSContext.pCoreData[eCore].ePMIC)
  {
    case HAL_AVS_PMSdm660_SUPPORT:
      switch (nPMICData)
      {
        case 0: return 1;
        case 1: return 2;
        case 2:
        case 3:
        default:
          return 4;
      }

    default:
      return 0;
  }

} /* END HAL_avs_GetPhaseCount */


/* ===========================================================================
**  HAL_avs_BusyWait
** ======================================================================== */

void HAL_avs_BusyWait
(
  uint32 uSec
)
{
  if (gHALAVSContext.BusyWait != NULL)
  {
     gHALAVSContext.BusyWait(uSec);
  }
  /*
   * If the BusyWait API has not been initialized, there is nothing to do.
   */

} /* END HAL_avs_BusyWait */


/* ===========================================================================
**  HAL_avs_Init
** ======================================================================== */

void HAL_avs_Init( HAL_avs_ContextType* pCtxt )
{
  uint32 nIdx;
  size_t nBaseAddr = 0;

  gHALAVSContext.BusyWait = pCtxt->BusyWait;
  gHALAVSContext.nChipId = pCtxt->nChipId;
  gHALAVSContext.nChipVersion = pCtxt->nChipVersion;


  if (gHALAVSContext.nPmicVoltageStepSize == 0xDEADDEAD)
    {
      gHALAVSContext.nPmicVoltageStepSize = HAL_AVS_PMSdm660_VOLTAGE_STEP_SIZE;
    }

    if (gHALAVSContext.nPmicVoltageOffset == 0xDEADDEAD)
    {
      gHALAVSContext.nPmicVoltageOffset = HAL_AVS_PMSdm660_VOLTAGE_OFFSET;
    }


  /* Set registers  */
  for( nIdx = 0; nIdx < HAL_AVS_NUM_CORES; ++nIdx )
  {
    if( pCtxt->pCoreData[nIdx].nBaseAddr != 0 )
    {
      gHALAVSContext.pCoreData[nIdx].nBaseAddr = pCtxt->pCoreData[nIdx].nBaseAddr;
      gHALAVSContext.pCoreData[nIdx].ePMIC = pCtxt->pCoreData[nIdx].ePMIC;
      nBaseAddr = gHALAVSContext.pCoreData[nIdx].nBaseAddr;

      /* Initialize the supported register addresses */
      asAVSRegs[nIdx].nVddCtl = HWIO_SAW4_VCTL_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nPMICStatus = HWIO_SAW4_PMIC_STS_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nAVSStatus = HWIO_SAW4_AVS_STS_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nConfig = HWIO_SAW4_CFG_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nControl = HWIO_SAW4_AVS_CTL_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nLimit = HWIO_SAW4_AVS_LIMIT_ADDR(nBaseAddr);
      asAVSRegs[nIdx].nDelay = HWIO_SAW4_AVS_DLY_ADDR(nBaseAddr);
    }
  }

} /* END HAL_avs_Init */


/* ===========================================================================
**  HAL_avs_Reset
** ======================================================================== */

void HAL_avs_Reset( void ) { /* Not implemented */ }


/* ===========================================================================
**  HAL_avs_Save
** ======================================================================== */

void HAL_avs_Save( void ) { /* Not implemented */ }


/* ===========================================================================
**  HAL_avs_Restore
** ======================================================================== */

void HAL_avs_Restore( void ) { /* Not implemented */ }


/* ===========================================================================
**  HAL_avs_SetCurrentVoltage
** ======================================================================== */

boolean HAL_avs_SetCurrentVoltage( HAL_avs_CoreType eCore, uint32 nVoltage )
{
  uint32  nRetryCount = HAL_AVS_SAW4_PMIC_WRITE_RETRY_COUNT;
  boolean bSuccess = FALSE;
  uint32  nCurrPMICData = 0;
  uint32  nPrevVoltage = 0;
  uint32  nVddDelta = 0;
  static  boolean bIsInit = TRUE;
  uint32  nSAW4VctlRegVal = 0;
  uint32  nPMICDataValue = HAL_avs_FormatPMICData(eCore, nVoltage);

  if ((HAL_avs_IsCoreSupported(eCore) == TRUE) && (nPMICDataValue != (uint32)-1))
  {
    nCurrPMICData = HAL_AVS_READ(asAVSRegs[eCore].nVddCtl, SAW4_VCTL, PMIC_DATA);
    nPrevVoltage = HAL_avs_GetVoltage(eCore, nCurrPMICData);
    nVddDelta = HAL_AVS_ABS(nVoltage, nPrevVoltage);

    /* Mask in the adr_idx field */
    nSAW4VctlRegVal |=
      HWIO_FMSK(SAW4_VCTL, ADR_IDX) &
      (HAL_AVS_SAW4_VCTL_REG_VCTL_ADR_IDX << HWIO_SHFT(SAW4_VCTL, ADR_IDX));

    /* Mask in the pmic_data field */
    nSAW4VctlRegVal |=
      HWIO_FMSK(SAW4_VCTL, PMIC_DATA) &
      (nPMICDataValue << HWIO_SHFT(SAW4_VCTL, PMIC_DATA));

    /* For now assume the voltage is in PMIC-readable format.  Send PMIC voltage. */
    outpdw(asAVSRegs[eCore].nVddCtl, nSAW4VctlRegVal);

    while (nRetryCount-- > 0)
    {
      /*
       * If the PMIC state is done and if the current PMIC data matches
       * the expected value, then we suceeded.
       */
      if( (0 == HAL_AVS_READ(asAVSRegs[eCore].nPMICStatus, SAW4_PMIC_STS, PMIC_STATE)) &&
               (HAL_AVS_READ(asAVSRegs[eCore].nPMICStatus, SAW4_PMIC_STS, CURR_PMIC_DATA) ==
                             nPMICDataValue) )
      {
        bSuccess = TRUE;
        break;
      }
      HAL_avs_BusyWait(2);
    }

    /*
     * Wait for voltage to settle. The initial voltage writing does not
     * need settling time since it is just used to initialize the SAW with
     * the current voltage (from driver initialization).
     */
    if( (FALSE == bIsInit) && (nPrevVoltage < nVoltage) )
    {
      HAL_avs_BusyWait(HAL_avs_GetVddSettleTimeUS(eCore, nVddDelta));
    }
  }

  bIsInit = FALSE;

  return bSuccess;

} /* END HAL_avs_SetCurrentVoltage */


/* ===========================================================================
**  HAL_avs_SetMaxVoltage
** ======================================================================== */

void HAL_avs_SetMaxVoltage( HAL_avs_CoreType eCore, uint32 nMaxVdd )
{
  uint32 nMaxVddCfg = 0;

  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    nMaxVddCfg =
      HAL_avs_GetPMICFormat(eCore, nMaxVdd);

    /* Set the maximum allowable value the voltage can be increased to. */
    HAL_AVS_WRITE(asAVSRegs[eCore].nLimit, SAW4_AVS_LIMIT, MAX_VLVL, nMaxVddCfg);
  }

}/* END HAL_avs_SetMaxVoltage */


/* ===========================================================================
**  HAL_avs_SetMinVoltage
** ======================================================================== */

void HAL_avs_SetMinVoltage( HAL_avs_CoreType eCore, uint32 nMinVdd )
{
  uint32 nMinVddCfg = 0;

  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    nMinVddCfg = HAL_avs_GetPMICFormat(eCore, nMinVdd);

    /* Set the minimum allowable value the voltage can be decreased to. */
    HAL_AVS_WRITE(asAVSRegs[eCore].nLimit, SAW4_AVS_LIMIT, MIN_VLVL, nMinVddCfg);
  }

} /* END HAL_avs_SetMinVoltage */


/* ===========================================================================
**  HAL_avs_SetDelay
** ======================================================================== */

void HAL_avs_SetDelay( HAL_avs_CoreType eCore, uint32 nDelay )
{
  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    HAL_AVS_WRITE(asAVSRegs[eCore].nDelay, SAW4_AVS_DLY, AVS_DELAY, nDelay);
  }

} /* END HAL_avs_SetDelay */


/* ===========================================================================
**  HAL_avs_SetClockDivider
** ======================================================================== */

void HAL_avs_SetClockDivider( HAL_avs_CoreType eCore, uint32 nDivider )
{
  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    /*HAL_AVS_WRITE(asAVSRegs[eCore].nConfig, SAW4_CFG, CLK_DIV, nDivider);
    This value is being programmed by TZ as 0x14 and hence we don't want to overwrite this in HLOS*/
	HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, TMR_CLK_DIV, nDivider);
  }
  //Need to set the tmr_clk_div in nControl as well as this is a new clock feature added in saw4.

} /* END HAL_avs_SetClockDivider */


/* ===========================================================================
**  HAL_avs_SetVoltageStepSize
** ======================================================================== */

void HAL_avs_SetVoltageStepSize( HAL_avs_CoreType eCore, HAL_avs_StepSizeType nStep )
{
  uint32 nValue = 0;

  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    switch( nStep )
    {
      case HAL_AVS_STEP_SIZE_25MV:
        nValue = 1;
        break;

      default:
        /* Leave value to no change. */
        nValue = 0;
        break;
    }

    HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, VLVL_STEP_DN, nValue);
	HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, VLVL_STEP_UP, nValue);
  }

} /* END HAL_avs_SetVoltageStepSize */


/* ===========================================================================
**  HAL_avs_EnableInterrupt
** ======================================================================== */

void HAL_avs_EnableInterrupt( HAL_avs_CoreType eCore,
                              HAL_avs_IntRequestType eRequest,
                              boolean bEnable )
{
  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    switch(eRequest)
    {
      case HAL_AVS_INT_REQUEST_SW_DONE:
        if( FALSE == bEnable )
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, SW_DONE_INT_EN, 0x0);
        }
        else
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, SW_DONE_INT_EN, 0x1);
        }
        break;

      case HAL_AVS_INT_REQUEST_MAX_LVL_EXCEEDED:
        if( FALSE == bEnable )
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, MAX_INT_EN, 0x0);
        }
        else
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, MAX_INT_EN, 0x1);
        }
        break;

      case HAL_AVS_INT_REQUEST_MIN_LVL_EXCEEDED:
        if( FALSE == bEnable )
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, MIN_INT_EN, 0x0);
        }
        else
        {
          HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, MIN_INT_EN, 0x1);
        }
        break;
    }
  }
} /* END HAL_avs_EnableInterrupt */


/* ===========================================================================
**  HAL_avs_SetVoltageWidth
** ======================================================================== */

void HAL_avs_SetVoltageWidth( HAL_avs_CoreType eCore, HAL_avs_PmicType ePMIC )
{
  uint32 nWidth = 0;

  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    switch( ePMIC )
    {
      case HAL_AVS_PMSdm660_SUPPORT:
        nWidth = 1;
        break;

      default:
        return;
    }
    HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, VLVL_WIDTH, nWidth);
  }

} /* END HAL_avs_SetVoltageWidth */


/* ===========================================================================
**  HAL_avs_Enable
** ======================================================================== */

void HAL_avs_Enable( HAL_avs_CoreType eCore, boolean bEnable )
{
  if( HAL_avs_IsCoreSupported(eCore) == TRUE )
  {
    if( FALSE == bEnable )
    {
      /* Disable HW from adjusting the Vdd. level. */
      HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, EN, 0x0);
      HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, CTL_SEL, 0x0);
    }
    else
    {
      /* Set HW to adjust the Vdd. level. */
      HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, EN, 0x1);
      HAL_AVS_WRITE(asAVSRegs[eCore].nControl, SAW4_AVS_CTL, CTL_SEL, 0x1);
    }
  }

} /* END HAL_avs_Enable */


/* ===========================================================================
**  HAL_avs_IsCoreSupported
** ======================================================================== */

boolean HAL_avs_IsCoreSupported( HAL_avs_CoreType eCore )
{
  if( gHALAVSContext.pCoreData[eCore].nBaseAddr )
  {
    return TRUE;
  }
  return FALSE;

} /* END HAL_avs_IsCoreSupported */


/*============================================================================
**  HAL_avs_UpdatePmicVoltageStepSize
** ======================================================================== */

void HAL_avs_UpdatePmicVoltageStepSize(uint32 nPmicVoltageStepSize)
{
  gHALAVSContext.nPmicVoltageStepSize = nPmicVoltageStepSize;

} /* END HAL_avs_UpdatePmicVoltageStepSize */


/*============================================================================
**  HAL_avs_UpdatePmicVoltageOffset
** ======================================================================== */

void HAL_avs_UpdatePmicVoltageOffset(uint32 nPmicVoltageOffset)
{
  gHALAVSContext.nPmicVoltageOffset = nPmicVoltageOffset;

} /* END HAL_avs_UpdatePmicVoltageOffset */


/*============================================================================
**  HAL_avs_ReturnPmicVoltageStepSize
** ======================================================================== */

uint32 HAL_avs_ReturnPmicVoltageStepSize(void)
{
  return gHALAVSContext.nPmicVoltageStepSize;

} /* END HAL_avs_ReturnPmicVoltageStepSize */


/*============================================================================
**  HAL_avs_ReturnPmicVoltageOffset
** ======================================================================== */

uint32 HAL_avs_ReturnPmicVoltageOffset(void)
{
  return gHALAVSContext.nPmicVoltageOffset;

} /* END HAL_avs_ReturnPmicVoltageOffset */


/* ===========================================================================
**  HAL_avs_SetPhaseCount
** ======================================================================== */

boolean HAL_avs_SetPhaseCount( HAL_avs_CoreType eCore, uint32 nPhases )
{
  uint32 nRetryCount = HAL_AVS_SAW4_PMIC_WRITE_RETRY_COUNT;
  uint32 nVCtlVal, nPhaseValue, nPrevPhases;
  boolean bSuccess = FALSE;

  if(HAL_avs_IsCoreSupported(eCore) != TRUE)
  {
    return FALSE;
  }

  nPrevPhases = HAL_avs_GetPhaseCount(eCore, gHALAVSContext.nCurrPhaseVal);
  nPhaseValue = HAL_avs_FormatPhaseCount(eCore, nPhases);

  /*
   * Select the PHASE_CNT index and program the phase count.
   */
  nVCtlVal = 0;
  nVCtlVal |= HWIO_FVAL(SAW4_VCTL, ADR_IDX, HAL_AVS_SAW4_VCTL_REG_PHASE_ADR_IDX);
  nVCtlVal |= HWIO_FVAL(SAW4_VCTL, PMIC_DATA, nPhaseValue);
  outpdw(asAVSRegs[eCore].nVddCtl, nVCtlVal);

  while (nRetryCount-- > 0)
  {
    /*
     * Only check for the PMIC_STATE, because CURR_PMIC_DATA doesn't update
     * properly for the phase index.
     */
    if (0 == HAL_AVS_READ(asAVSRegs[eCore].nPMICStatus, SAW4_PMIC_STS, PMIC_STATE))
    {
      gHALAVSContext.nCurrPhaseVal = nPhaseValue;
      bSuccess = TRUE;
      break;
    }

    HAL_avs_BusyWait(2);
  }

  /*
   * Wait for the phases to warm up.
   */
  if (nPhases > nPrevPhases)
  {
    HAL_avs_BusyWait(50);
  }

  return bSuccess;

} /* END HAL_avs_SetPhaseCount */


/* ===========================================================================
**  HAL_avs_SetPowerMode
** ======================================================================== */

boolean HAL_avs_SetPowerMode
(
  HAL_avs_CoreType  eCore,
  HAL_avs_PowerMode eMode
)
{
#if 0
  uint32 nRetryCount = HAL_AVS_SAW4_PMIC_WRITE_RETRY_COUNT;
  uint32 nModeCtlRegVal = 0, nModeCtl;
  boolean bSuccess = FALSE;

  /*
   * Validate that the core is supported.
   */
  if (HAL_avs_IsCoreSupported(eCore) != TRUE)
  {
    return FALSE;
  }

  /*
   * Validate that the power mode is supported.
   */
  if (eMode == HAL_AVS_POWER_MODE_PWM)
  {
    nModeCtl = HAL_AVS_POWER_MODE_PWM_FIELD_VAL;
  }
  else if (eMode == HAL_AVS_POWER_MODE_AUTO)
  {
    nModeCtl = HAL_AVS_POWER_MODE_AUTO_FIELD_VAL;
  }
  else
  {
    return FALSE;
  }

  /* Mask in the adr_idx field */
  nModeCtlRegVal |=
    HWIO_FMSK(SAW4_VCTL, ADR_IDX) &
    (HAL_AVS_SAW4_VCTL_REG_MODE_ADR_IDX << HWIO_SHFT(SAW4_VCTL, ADR_IDX));

  /* Mask in the pmic_data field */
  nModeCtlRegVal |=
    HWIO_FMSK(SAW4_VCTL, PMIC_DATA) &
    (nModeCtl << HWIO_SHFT(SAW4_VCTL, PMIC_DATA));

  /* Send PMIC power mode. */
  outpdw(asAVSRegs[eCore].nVddCtl, nModeCtlRegVal);

  while (nRetryCount-- > 0)
  {
    /*
     * If the PMIC state is done and if the current PMIC data matches
     * the expected value, then we succeeded.
     */
    if (HAL_AVS_READ(asAVSRegs[eCore].nPMICStatus, SAW4_PMIC_STS, PMIC_STATE) == 0)
    {
      bSuccess = TRUE;
      break;
    }

    HAL_avs_BusyWait(2);
  }

  return bSuccess;
#endif
  return TRUE;

} /* END HAL_avs_SetPowerMode */
