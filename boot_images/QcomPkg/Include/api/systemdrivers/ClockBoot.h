#ifndef __CLOCKBOOT_H__
#define __CLOCKBOOT_H__

/** @file ClockBoot.h

  This file contains the external interface definitions for the clock regime device driver.
  This driver is support for the Krait Second Primary Boot Loader.

  Copyright (c) 2010-2016, Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/22/16    vg     Removed null entry in ClockQUPI2CType 
 06/03/15   vph     Add support for BLSP2 I2C clocks
 04/17/15   vph     Add API for support VSense clocks
 11/07/14   jcuddihy  Added query API Clock_GetClockFrequency().
 08/08/11   vtw     Added support for SDC clocks.
 04/11/11   vtw     Created from 8960 clock driver project.

=============================================================================*/

/*=========================================================================
      Includes
==========================================================================*/

#include "com_dtypes.h"
#include "railway.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Macro to force an enumeration to be a full 32 bits wide.
 */
#define CLOCK_ENUM_32BITS(name) CLOCK_##name##_32BITS = 0x7FFFFFFF

/**
@brief List of boot speeds that the clock driver supports.

MIN - XO frequency perf level.
NOMINAL - Highest frequency at nominal voltage level.
MAX - Max frequency support by the frequency plan.
DEFAULT - Same as NOMINAL.

*/
typedef enum
{
  CLOCK_BOOT_PERF_NONE,
  CLOCK_BOOT_PERF_MIN,
  CLOCK_BOOT_PERF_NOMINAL,
  CLOCK_BOOT_PERF_MAX,
  CLOCK_BOOT_PERF_DEFAULT,
  CLOCK_BOOT_PERF_NUM,
  CLOCK_ENUM_32BITS(BOOT_PERF)
} ClockBootPerfLevelType;

/**
@brief List of SDC clocks that the clock driver supports.
*/
typedef enum
{
   CLK_SDC0,
   CLK_SDC1,
   CLK_SDC2,
   CLK_SDC3,
   CLK_SDC4,
   CLK_SDC5,
   CLK_SDC_NUM_CLKS,
   CLK_SDC_NONE = CLK_SDC_NUM_CLKS,
} ClockSDCType;

/**
@brief List of SDC clocks that the clock driver supports.
*/
typedef enum
{
   CLK_BLSP_UART_NONE,
   CLK_BLSP0_UART0_APPS,
   CLK_BLSP0_UART1_APPS,
   CLK_BLSP0_UART2_APPS,
   CLK_BLSP0_UART3_APPS,
   CLK_BLSP1_UART1_APPS,
   CLK_BLSP1_UART2_APPS,
   CLK_BLSP1_UART3_APPS,
   CLK_BLSP1_UART4_APPS,
   CLK_BLSP1_UART5_APPS,
   CLK_BLSP1_UART6_APPS,
   CLK_BLSP2_UART1_APPS,
   CLK_BLSP2_UART2_APPS,
   CLK_BLSP2_UART3_APPS,
   CLK_BLSP2_UART4_APPS,
   CLK_BLSP2_UART5_APPS,
   CLK_BLSP2_UART6_APPS,
   CLK_BLSP_UART_NUM_CLKS
} ClockUARTType;


/**
@brief List of QUP_I2C clocks that the clock driver supports.
*/
typedef enum
{
   CLK_BLSP1_QUP0_I2C_NONE,
   CLK_BLSP1_QUP1_I2C_APPS,
   CLK_BLSP1_QUP2_I2C_APPS,
   CLK_BLSP1_QUP3_I2C_APPS,
   CLK_BLSP1_QUP4_I2C_APPS,
   CLK_BLSP1_QUP5_I2C_APPS,
   CLK_BLSP1_QUP6_I2C_APPS,
   CLK_BLSP2_QUP1_I2C_APPS,
   CLK_BLSP2_QUP2_I2C_APPS,
   CLK_BLSP2_QUP3_I2C_APPS,
   CLK_BLSP2_QUP4_I2C_APPS,
   CLK_BLSP2_QUP5_I2C_APPS,
   CLK_BLSP2_QUP6_I2C_APPS,
   CLK_BLSP_QUP_I2C_NUM_CLKS
} ClockQUPI2CType;

/**
@brief List of QUP_SPI clocks that the clock driver supports.
*/
typedef enum
{
   CLK_BLSP0_QUP0_SPI_APPS,
   CLK_BLSP0_QUP1_SPI_APPS,
   CLK_BLSP1_QUP1_SPI_APPS,
   CLK_BLSP1_QUP2_SPI_APPS,
   CLK_BLSP1_QUP3_SPI_APPS,
   CLK_BLSP1_QUP4_SPI_APPS,
   CLK_BLSP1_QUP5_SPI_APPS,
   CLK_BLSP1_QUP6_SPI_APPS,
   CLK_BLSP2_QUP1_SPI_APPS,
   CLK_BLSP2_QUP2_SPI_APPS,
   CLK_BLSP2_QUP3_SPI_APPS,
   CLK_BLSP2_QUP4_SPI_APPS,
   CLK_BLSP2_QUP5_SPI_APPS,
   CLK_BLSP2_QUP6_SPI_APPS,
   CLK_BLSP3_QUP0_SPI_APPS,
   CLK_BLSP3_QUP1_SPI_APPS,
   CLK_BLSP_QUP_SPI_NUM_CLKS
} ClockQUPSPIType;

typedef enum
{
  /* No request / Invalid request  */
  CLOCK_RESOURCE_QUERY_INVALID         = 0,

  /*
  Clock driver query ID for the number of supported performance levels.
  This query returns the number of supported performance levels for
  the clock resource in question.
 */
  CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS,

  /*
  CLock driver query for the minimum supported frequency in kHz for a clock resource.
  This query returns the minimum supported frequency for the resource
  based on the target.
 */
  CLOCK_RESOURCE_QUERY_MIN_FREQ_KHZ,

  /*
  CLock driver for all supported frequencies in kHz for a clock resource.
  This query returns the array of supported frequency for the resource
  based on the target and the voltage levels.
 */
  CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ,
} ClockQueryType;

/*
 * ClockVRegLevelType
 *
 * List of voltage levels that match to a certain clock frequency.  Note that the
 * enumeration values map to pmic.
 *
 *  OFF          - Turn off non-CX rail
 *  LOW          - Lowest voltage level, or "do not care"
 *  NOMINAL      - Nominal voltage level
 *  NOMINAL_PLUS - Intermediate leve between Nominal and high (Turbo)
 *  HIGH         - Elevated, or "Super Turbo" voltage level.
 */
//typedef enum
//{
//  CLOCK_VREG_LEVEL_OFF          = RAILWAY_NO_REQUEST,
//  CLOCK_VREG_LEVEL_RETENTION    = RAILWAY_RETENTION,
//  CLOCK_VREG_LEVEL_LOW_MIN      = RAILWAY_SVS_MIN,
//  CLOCK_VREG_LEVEL_LOW_MINUS    = RAILWAY_SVS_LOW,
//  CLOCK_VREG_LEVEL_LOW          = RAILWAY_SVS,
//  CLOCK_VREG_LEVEL_LOW_PLUS     = RAILWAY_SVS_HIGH,
//  CLOCK_VREG_LEVEL_NOMINAL      = RAILWAY_NOMINAL,
//  CLOCK_VREG_LEVEL_NOMINAL_PLUS = RAILWAY_TURBO,
//  //CLOCK_VREG_LEVEL_HIGH_MINUS   = ???
//  CLOCK_VREG_LEVEL_HIGH         = RAILWAY_SUPER_TURBO,
//  CLOCK_VREG_LEVEL_HIGH_NO_CPR  = RAILWAY_SUPER_TURBO_NO_CPR,
//  CLOCK_VREG_NUM_LEVELS,
//} ClockVRegLevelType;

/*
 * Clock
 *
 * Struct of clock plan that has frequency that associates with voltage levels
 */

typedef enum
{
  CLOCK_DDR_MODE_GCC,
  CLOCK_DDR_MODE_DDRCC,
  CLOCK_DDR_MODE_FORCE32BIT = 0x7FFFFFFF
} ClockDDRMode;

/*
 * ClockUSB30PipeClkSrcType
 *
 * Select USB30 PIPE Clk Source Type
 */
typedef enum
{
  CLOCK_USB30_SRC_USB3_PHY = 0,
  CLOCK_USB30_SRC_CORE_BI_PLL_TEST_SE,
  CLOCK_USB30_SRC_CXO,
  CLOCK_USB30_SRC_TCK,
  CLOCK_USB30_SRC_INVALID
} ClockUSB30PipeClkSrcType;

/*
 * BootLogClockType
 *
 * List of clocks whose frequency can be queried via external interface.
 */
typedef enum
{
   CLK_BOOT_LOG_APPS_CLUSTER_0,
   CLK_BOOT_LOG_DDR,
   CLK_BOOT_LOG_NUM_CLOCKS,
   CLOCK_ENUM_32BITS(CLK_BOOT_LOG_TYPE)
} ClockBootLogQueryType;


typedef struct
{
  uint32 pll_dec_start;
  uint32 pll_div_frac_start3;
  uint32 pll_plllock_cmp1;
  uint32 pll_plllock_cmp2;
  uint32 pll_vco_count1;
  uint32 pll_vco_count2;
  uint32 pll_pll_lpf2_postdiv;
  uint32 pll_kvco_code;
} ClockDSFConfigType;


/*
 * ClockPlanType
 *
 * Struct of clock plan that has frequency that associates with voltage levels
 */
typedef struct
{
  uint32             nFreqKHz;
  railway_corner     eVRegLevel;
  ClockDDRMode       eMode;
}ClockPlanType;

/* ========================================================================
**  Function : Clock_PreDDRInit
** ======================================================================*/
/*
    Description: Configure all clocks needed for DDR configuration.
*/
boolean Clock_PreDDRInit( uint32 ddr_type );


/* ========================================================================
**  Function : Clock_PreDDRInit
** ======================================================================*/
/*
    Description: Configure all clocks needed for DDR configuration.
*/
boolean Clock_PreDDRInitEx( uint32 ddr_type );

/* ============================================================================
**  Function : Clock_Init
** ============================================================================
*/
/*!

    This function turns on the required clocks and configures
    Fabric and Krait speeds depending on the System Fabric and
    CPU boot performance level.

    @param eSysPerfLevel   -  [in] Fabric and DDR performance level to initialize.
    @param eCPUPerfLevel   -  [in] Scropion CPU performance level to initialize.

    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

   @dependencies
    None.

*/

boolean Clock_Init(ClockBootPerfLevelType eSysPerfLevel,
                    ClockBootPerfLevelType eCPUPerfLevel);

/* ============================================================================
**  Function : Clock_SetSysPerfLevel
** ============================================================================
*/
/**
  Configure System and Application Fabric to a perf level.

  @param eSysPerfLevel [in]  -  Fabric and DDR performance level to configure.

  @return
  TRUE -- Fabric was configured to perf level successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/

boolean Clock_SetSysPerfLevel(ClockBootPerfLevelType eSysPerfLevel);

/* ============================================================================
**  Function : Clock_SetCPUPerfLevel
** ============================================================================
*/
/**
  Configure Krait CPU to a specific perf level.

  @param eCPUPerfLevel [in] - CPU performance level.

  @return
  TRUE -- CPU was configured to perf level successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/

boolean Clock_SetCPUPerfLevel(ClockBootPerfLevelType eCPUPerfLevel);

/* ============================================================================
**  Function : Clock_EnableL2
** ============================================================================
*/
/*!
    Configure L2 cache to a specific perf level.

    @param eL2PerfLevel   -  [IN] CPU performance level

    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetL2PerfLevel(ClockBootPerfLevelType eL2PerfLevel);

/* ============================================================================
**  Function : Clock_SetSDCClockFrequency
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
           eClock            -  [IN] SDC clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetSDCClockFrequency(ClockBootPerfLevelType ePerfLevel,
                                    ClockSDCType eClock);


/* ============================================================================
**  Function : Clock_SetSDCClockFrequencyExt
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param nFreqKHz          -  [IN] Frequency in KHz
           eClock            -  [IN] SDC clock to configure
    @return
        freq - Returns the frequency which may be rounded up if the
          requested frequency was not in the clock plan.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetSDCClockFrequencyExt( uint32 nFreqKHz, ClockSDCType eClock);

/* ============================================================================
**  Function : Clock_SetUARTClockFrequency
** ============================================================================
*/
/*!
    Configure UART clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
                     eClock            -  [IN] UART clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetUARTClockFrequency(ClockBootPerfLevelType ePerfLevel,
                                    ClockUARTType eClock);


/* ============================================================================
**  Function : Clock_SetQSPIFrequency
** ============================================================================
*/
/*!
    Set QSPI clock frequency.  Clocks will turn off if request frequency is zero

    @param nFreqKHz - Clock frequency in KHz

    @return - Frequency that clock has been match and set to.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetQSPIFrequency( uint32 nFreqKHz );

/* ============================================================================
**	Function : Clock_DisableUARTClock
** ============================================================================
*/
/*!
	Disable  specific UART clock.

	@param    eClock	-	[IN] UART clock to Disable
	@return
	TRUE -- Clock disable was successful.
	FALSE -- Clock disable failed.

	@dependencies
	None.

	@sa None
*/
boolean Clock_DisableUARTClock(ClockUARTType eClock);



/* ============================================================================
**  Function : Clock_InitForDownloadMode
** ============================================================================
*/
/*!
    This will initialize clocks for the RAMs in the system that are to be saved
    during crash dump procedures in the downloader.

    @param
      None
    @return
      None

    @dependencies
    None.

    @sa None
*/
/* ============================================================================
**  Function : Clock_SetI2CClockFrequency
** ============================================================================
*/
/*!
    Configure an I2C clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
                     eClock  -  [IN] I2C clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetI2CClockFrequency
(
  ClockBootPerfLevelType ePerfLevel,
  ClockQUPI2CType eClock
);


/* ============================================================================
**	Function : Clock_DisableI2CClock
** ============================================================================
*/
/*!
	Disable a specific I2C clock.

	@param    eClock	-	[IN] I2C clock to Disable
	@return
	TRUE -- Clock disable was successful.
	FALSE -- Clock disable failed.

	@dependencies
	None.

	@sa None
*/
boolean Clock_DisableI2CClock(ClockQUPI2CType eClock);


/* ============================================================================
**  Function : Clock_SetSPIClockFrequency
** ============================================================================
*/
/*!
    Configure the SPI clock to a specified Frquency, rounding up.

    @param nFreqKHz          -  [IN] Frequency in KHz
           eClock            -  [IN] SPI clock to configure
    @return
        freq - Returns the frequency which may be rounded up if the
          requested frequency was not in the clock plan.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_SetSPIClockFrequency(ClockQUPSPIType eClock,  uint32 nFreqKHz);


/* ============================================================================
**  Function : Clock_InitForDownloadMode
** ============================================================================
*/
/*!
    This will initialize clocks for the RAMs in the system that are to be saved
    during crash dump procedures in the downloader.

    @param
      None
    @return
      None

    @dependencies
    None.

    @sa None
*/

void Clock_InitForDownloadMode(void);

/* ============================================================================
**  Function : Clock_InitUSB
** ============================================================================
*/
/*!
    Configure USB clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_InitUSB(void);


/* ============================================================================
**  Function : Clock_InitUSB30
** ============================================================================
*/
/*!
    Configure USB3.0 clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_InitUSB30(void);


/* ============================================================================
**  Function : Clock_Usb30EnableSWCollapse
** ============================================================================
*/
/*!
    Enable SW Collapse for USB30

    @param Enable/Disable.
    @return
    TRUE always

    @dependencies
    None.

    @sa None
   */
boolean Clock_Usb30EnableSWCollapse(boolean enable);

/* ============================================================================
**  Function : Clock_Usb30GetSWCollapse
** ============================================================================
*/
/*!
    Returns the status of SW Collapse for USB30

    @param None
    @return
    TRUE if enabled
    FALSE if disabled

    @dependencies
    None.

    @sa None
*/
boolean Clock_Usb30GetSWCollapse(void);

/* ============================================================================
**  Function : Clock_InitCrypto
** ============================================================================
*/
/*!
    Configure Crypto clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_InitCrypto(void);

/* ============================================================================
**  Function : Clock_ExitBoot
** ============================================================================
*/
/*!

    This function turns off clocks that were used during boot, but are not
    needed after boot.  This should be called at the end of boot.

    @return
    TRUE -- Clean up was successful.
    FALSE -- Clean up failed.

   @dependencies
    Call this last in the boot sequence.

*/
boolean Clock_ExitBoot(void);

/* ============================================================================
**  Function : Clock_DebugInit
** ============================================================================
*/
/*!

    This function is called very early in boot.  It is used for work-arounds that
    need to be done before JTAG attaches at the SBL "hold focus button" spin loop.

    @return
    TRUE -- Clean up was successful.
    FALSE -- Clean up failed.

   @dependencies
    You cannot use busywait in this function.

*/
boolean Clock_DebugInit(void);

/* ============================================================================
**  Function : Clock_DisableUSB
** ============================================================================
*/
/*!
    Disable USB clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_DisableUSB(void);

/* ============================================================================
**  Function : Clock_USB30_PipeClkSrcSel
** ============================================================================
*/
/*!
    Select USB3 PIPE clock source.

    @param eSrc -  [IN] Clock source choice for the USB3.0 PHY
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.
    @dependencies  None.
    @sa None
*/
boolean Clock_USB30_PipeClkSrcSel(ClockUSB30PipeClkSrcType eSrc);

/* ============================================================================
**  Function : Clock_DDRSpeed
** ============================================================================
*/
/*!
    Return the DDR clock rate in kilohertz.  This clock rate is the bus speed.
    It is not the controller clock (2X) clock for targets that use Legacy mode.

    @param None.
    @return
      The speed configured in Clock_PreDDRInit() of the BIMC/DDR clock.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_DDRSpeed(void);

/* ============================================================================
**  Function : Clock_GetClockFrequency
** ============================================================================
*/
/*!
    Get the requested clock frequency in hertz.

    @param None.
    @return
      True iff the requested clock frequency is placed in pnFrequencyHz.

    @dependencies
    None.

    @sa None
*/
boolean Clock_GetClockFrequency(ClockBootLogQueryType eBootLogClock,
                                uint32 *pnFrequencyHz);

/* ========================================================================
**  Function : Clock_I2CInit
** ======================================================================*/
/*
    Description: Configure all clocks needed for EEPROM to be used Pre DDR.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_I2CInit(void);

/* ========================================================================
**  Function : Clock_EnableQPICForDownloadMode
** ======================================================================*/
/*
    Description: Enable QPIC clocks.
                 The function is used in Download Mode where QPIC clocks are
                 not enabeld by PBL.

    @param None
    @return TRUE on success.

    @dependencies
    None.

    @sa None
*/
boolean Clock_EnableQPICForDownloadMode( void );

/* ========================================================================
**  Function : Clock_BIMCQuery
** ======================================================================*/

void Clock_BIMCQuery(ClockQueryType nQuery,void* pResource);

/* ========================================================================
**  Function : Clock_SetDDRMinMax
** ======================================================================*/
/*
    Description: API for cap DDR at min/max levels

    @param nDDRMin - Min index.
           nDDRMax - Max index.

    @return TRUE on success.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetDDRMinMax( uint8 nDDRMin, uint8 nDDRMax );

/* ========================================================================
**  Function : Clock_GetDDRMinMax
** ======================================================================*/
/*
    Description: API for getting current setting DDR min/max levels

    @param pDDRMin - Min level
           pDDRMax - Max level

    @return TRUE on success.

    @dependencies
    None.

    @sa None
*/
void Clock_GetDDRMinMax( uint8 *pDDRMin, uint8 *pDDRMax );

/* ========================================================================
**  Function : Clock_UFSInit
** ======================================================================*/
/*
    Description: Enable UFS clocks, and set it to certain performance levels

    @param ePerfLevel
    @return TRUE on success.

    @dependencies
    None.

    @sa None
*/
boolean Clock_UFSInit( ClockBootPerfLevelType ePerfLevel );


/* ============================================================================
**  Function : Clock_InitRPM
** ============================================================================
*/
/*!

    This function does any initialization before RPM launches.  SMEM is now
    usable.

    @return
    TRUE -- Success
    FALSE -- Failure

   @dependencies
    Requires SMEM

*/
boolean Clock_InitRPM( void );


boolean Clock_SetBIMCSpeed(uint32 nFreqKHz );

/* ============================================================================
**  Function : Clock_InitVSense
** ============================================================================
*/
/*!
    This function enables the Voltage Sensor clocks, and configure them run
    at max frequency level at NOMINAL voltage.

    @return
      TRUE -- Initialization was successful.
      FALSE -- Initialization failed.

   @dependencies
     None.

*/
boolean Clock_InitVSense( void );

/* ============================================================================
**  Function : Clock_ShutdownVSense
** ============================================================================
*/
/*!
    This function disables the voltage sensor clocks.

    @return
      TRUE -- Initialization was successful.
      FALSE -- Initialization failed.

   @dependencies
      None.

*/
boolean Clock_ShutdownVSense( void );

/* ============================================================================
**  Function : Clock_DDRQuery
** ============================================================================
*/
/*!
    Retrieve parameters about the DDR clock plan.  The caller is responsible for allocating
      the space for the response.  The request can be either:
    CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS : pResource should point to a uint32 (4 bytes).
      The number of clock rates is stored in *pResource.
    CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ :  pResource should point to sizeof(ClockPlanType)*num_perf_levels.

    @param nQuery - The request.
    @param pResource - (output) A pointer to enough space to hold the response.

    @return TRUE on success.

    @dependencies


*/
void Clock_DDRQuery(ClockQueryType nQuery, void* pResource);

/* ============================================================================
**  Function : Clock_DDRPrepareChange
** ============================================================================
*/
/*!
    This function prepares for a DDR clock switch.  It increases voltage and locks
    the unused PLL to prepare for the switch.

    @param nMDDRChannel - Choose a channel (0-5) to prepare the clock switch.
    @param nFreqKHz - A frequency from the clock plan (as retrieved from Clock_DDRQuery())

    @return TRUE on success.

   @dependencies
      None.

*/
boolean Clock_DDRPrepareChange
(
  uint32 nMDDRChannel,
  uint32 nFreqKHz
);

/* ============================================================================
**  Function : Clock_DDRApplyChange
** ============================================================================
*/
/*!
    This function actually switches the clock switch that was started by
      Clock_DDRPrepareChange().

    @param nMDDRChannel - Choose a channel (0-5) to apply the clock switch.

    @return TRUE on success.

   @dependencies
      None.

*/
boolean Clock_DDRApplyChange
(
 uint32 nMDDRChannel
);

/* ============================================================================
**  Function : Clock_DDRCleanUpChange
** ============================================================================
*/
/*!
    This function completes the clock switch.  It applies a drop in voltage if
    needed and turns off the unused PLL.

    @param nMDDRChannel - Choose a channel (0-5) to apply the clock switch.

    @return TRUE on success.

   @dependencies
      None.

*/
boolean Clock_DDRCleanUpChange
(
 uint32 nMDDRChannel
);

/* ============================================================================
**  Function : Clock_LMhInit
** ============================================================================
*/
/*  Initialize for the current limiter calibration.
 *  Power on A57 at Turbo Voltage(A57 operation and stability is not a requirement)
    L2 headswitch needs to be closed as well.

    @param nA57uV  -  [IN] requested voltage in microvolts
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean Clock_LMhInit
(
  uint32 nA57uV
);

/* ============================================================================
**  Function : Clock_LMhPreCalibration
** ============================================================================
*/
/*  Set the A57 cores at the maximum clock rate.

    @param  nFreqKHz : The frequency to set in KHz
    @return : rounded freqeuncy that was set, or 0 on failure in kHz.

    @dependencies
    None.

    @sa None
*/
uint32 Clock_LMhPreCalibration
(
  uint32 nFreqKHz
);

/* ============================================================================
**  Function : Clock_LMhDeInit
** ============================================================================
*/
/*  Disable the PLL, turn of the L2 head switch, power off the rail.

    @param  None.
    @return
    TRUE -- Success.
    FALSE -- Reserved, not used.

    @dependencies
    None.

    @sa None
*/
boolean Clock_LMhDeInit
(
  void
);

#endif  /* __CLOCKBOOT_H__ */
