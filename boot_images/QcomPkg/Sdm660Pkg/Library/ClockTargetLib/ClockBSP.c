/**
==============================================================================

  @file ClockBSP.c

  Definitions of the support clock perf level.

==============================================================================

                             Edit History


when      who           what, where, why
--------  ------------  ------------------------------------------------------
08/11/15  jcuddihy      Initial SDM660 revision, branched from MSM8996.

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "ClockCommon.h"
#include "ClockHWIO.h"

/*=========================================================================
      Prototypes
==========================================================================*/
boolean Clock_SourceMapToGCC(ClockSourceType eSource, uint32 *nMuxValue);
boolean Clock_SourceMapToMMSS(ClockSourceType eSource, uint32 *nMuxValue);
boolean Clock_SourceMapToQSPI(ClockSourceType eSource, uint32 *nMuxValue);
boolean Clock_SourceMapToSDCC2(ClockSourceType eSource, uint32 *nMuxValue);



/*=========================================================================
      Data
==========================================================================*/
static Clock_RailwayType ClockRailway =
{
  "vddcx",
  0,
  0,
  "vddmx",
  0,
  0
};

static Clock_ConfigType Clock_ConfigData =
{
  /* GPLL0 @ 600 MHz (general purpose PLL). */
  .PLL0_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL0_MODE),
    .nVoteAddr     =  HWIO_ADDR(GCC_APCS_GPLL_ENA_VOTE),
    .nVoteMask     =  HWIO_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL0),
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  31,
    .nM            =  0, // unused
    .nN            =  0, // unused
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x4000000000
  },
 
  /* GPLL1 @ 802 MHz. */
  .PLL1_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL1_MODE),
    .nVoteAddr     =  HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE),
    .nVoteMask     =  HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL1),
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  41, 
    .nM            =  0, // unused
    .nN            =  0, // unused
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0xC555000000
  },

  /* GPLL2 @ 825.6 MHz (dynmaic config--dedicated to BIMC). */
  .PLL2_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL2_MODE),
    .nVoteAddr     =  HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE),
    .nVoteMask     =  HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL2),
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1, 
    .nL            =  43, 
    .nM            =  0, // unused
    .nN            =  0, // unused
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x0
  },

  /* GPLL3 @ 825.6 MHz (dynmaic config--dedicated to BIMC). */
  .PLL3_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL3_MODE), 
    .nVoteAddr     =  HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE), 
    .nVoteMask     =  HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL3),
    .nVCO          =  2, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  43,
    .nM            =  0,
    .nN            =  0,
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x0
  },

  /* GPLL4 @ 1536 MHz */
  .PLL4_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL4_MODE), 
    .nVoteAddr     =  HWIO_ADDR(GCC_APCS_GPLL_ENA_VOTE),
    .nVoteMask     =  HWIO_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL4),
    .nVCO          =  0, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  80, 
    .nM            =  0,
    .nN            =  0,
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x0
  },

  /* GPLL5 @ 1708.8 MHz */
  .PLL5_Cfg =
  {
    .nPLLModeAddr  =  HWIO_ADDR(GCC_GPLL5_MODE), 
    .nVoteAddr     =  HWIO_ADDR(GCC_RPM_GPLL_ENA_VOTE),
    .nVoteMask     =  HWIO_FMSK(GCC_RPM_GPLL_ENA_VOTE, GPLL5),
    .nVCO          =  0, 
    .nPreDiv       =  1,
    .nPostDiv      =  1,
    .nL            =  89,
    .nM            =  0,
    .nN            =  0,
    .nConfigCtl    =  SPARK_CONFIG_CTL,
    .nAlpha        =  0x0
  },

  .CPU_Cfg =
  {
    /* {ClockConfigPLLType, nFrequency} */
    {{0}, 0,0,0,0,0 },
    {{0}, HWIO_ADDR(APCS_ALIAS0_CMD_RCGR), APCS_SOURCE_CXO,        DIV2X(1), 0, 0,  19200}, /*Min*/
    //{{0}, HWIO_ADDR(APCS_ALIAS0_CMD_RCGR), APCS_SOURCE_GPLL0_MAIN, DIV2X(1), 0, 0, 600000}, /*Nom*/
    //{{0}, HWIO_ADDR(APCS_ALIAS0_CMD_RCGR), APCS_SOURCE_GPLL0_MAIN, DIV2X(1), 0, 0, 600000}, /*Max*/
    { {HWIO_ADDR(APCS_C0_PLL_MODE), 0, 0, 0, 1, 1, 72, 0, 0, AGERA_CONFIG_CTL, 0, 0}, 
         HWIO_ADDR(APCS_ALIAS0_CMD_RCGR), APCS_SOURCE_AG_EARLY,  DIV2X(1), 0, 0, 1382400000}, /*Nom*/
    { {HWIO_ADDR(APCS_C0_PLL_MODE), 0, 0, 0, 1, 1, 72, 0, 0, AGERA_CONFIG_CTL, 0, 0}, 
         HWIO_ADDR(APCS_ALIAS0_CMD_RCGR), APCS_SOURCE_AG_EARLY,  DIV2X(1), 0, 0, 1382400000}, /*Max*/		 
  },

  .CPU_Cfg_SDM630 =
  {
    /* {ClockConfigPLLType, nFrequency} */
    {{0}, 0,0,0,0,0 },
    {{0}, HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_CXO,        DIV2X(1), 0, 0,  19200}, /*Min*/
  //  {{0}, HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_GPLL0_MAIN, DIV2X(1), 0, 0, 600000}, /*Nom*/
  //  {{0}, HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_GPLL0_MAIN, DIV2X(1), 0, 0, 600000}, /*Max*/
    { {HWIO_ADDR(APCS_C1_PLL_MODE), 0, 0, 0, 1, 1, 87, 0, 0, AGERA_CONFIG_CTL, 0, 0}, 
          HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_AG_EARLY,  DIV2X(1), 0, 0, 1670400000}, /*Nom*/		 		  
    { {HWIO_ADDR(APCS_C1_PLL_MODE), 0, 0, 0, 1, 1, 87, 0, 0, AGERA_CONFIG_CTL, 0, 0}, 
          HWIO_ADDR(APCS_ALIAS1_CMD_RCGR), APCS_SOURCE_AG_EARLY,  DIV2X(1), 0, 0, 1670400000}, /*Max*/		 
  },

  .RPM_Cfg = 
  {
    {HWIO_ADDR(GCC_RPM_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0},  /* PERF NONE */
    {HWIO_ADDR(GCC_RPM_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0},  /* MIN - 19.2 MHz               */
    {HWIO_ADDR(GCC_RPM_CMD_RCGR), MUX_GCC, SRC_GPLL1,  4, 0, 0, 0},  /* NOM - 401 MHz (SVS)          */
    {HWIO_ADDR(GCC_RPM_CMD_RCGR), MUX_GCC, SRC_GPLL0,  1, 0, 0, 0},  /* MAX - 600 MHz (NOMINAL)      */
    {HWIO_ADDR(GCC_RPM_CMD_RCGR), MUX_GCC, SRC_GPLL0,  1, 0, 0, 0}   /* DEFAULT - 600 MHz (Max Nom)  */
  },

  .SNOC_Cfg = 
  {
    {HWIO_ADDR(GCC_SYSTEM_NOC_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0},  /* PERF NONE */
    {HWIO_ADDR(GCC_SYSTEM_NOC_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0},  /* MIN - 19.2 MHz               */
    {HWIO_ADDR(GCC_SYSTEM_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0, 10, 0, 0, 0},  /* NOM - 120 MHz (SVS)          */
    {HWIO_ADDR(GCC_SYSTEM_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0,  6, 0, 0, 0},  /* MAX - 200 MHz (NOMINAL)      */
    {HWIO_ADDR(GCC_SYSTEM_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0,  6, 0, 0, 0}   /* DEFAULT - 200 MHz (Max Nom)  */
  },

  .PIMEM_Cfg = 
  {
    {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0},  /* PERF NONE */
    {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0},  /* MIN - 19.2 MHz               */
    {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  8, 0, 0, 0},  /* NOM - 150 MHz (SVS)          */
    {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  4, 0, 0, 0},  /* MAX - 300 MHz (NOMINAL)      */
    {HWIO_ADDR(GCC_PIMEM_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  4, 0, 0, 0}   /* DEFAULT - 300 MHz (Max Nom)  */
  },

  .HS_SNOC_Cfg = 
  {
    {HWIO_ADDR(GCC_SYS_NOC_HS_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0},  /* PERF NONE */
    {HWIO_ADDR(GCC_SYS_NOC_HS_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0},  /* MIN - 19.2 MHz               */
    {HWIO_ADDR(GCC_SYS_NOC_HS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  8, 0, 0, 0},  /* NOM - 150 MHz (SVS)          */
    {HWIO_ADDR(GCC_SYS_NOC_HS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  5, 0, 0, 0},  /* MAX - 240 MHz (NOMINAL)      */
    {HWIO_ADDR(GCC_SYS_NOC_HS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0,  5, 0, 0, 0}   /* DEFAULT - 240 MHz (Max Nom)  */
  },

  .CNOC_Cfg = 
  {
    {HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0},  /* PERF NONE                  */
    {HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0},  /* MIN - 19.2 MHz             */
    {HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0, 32, 0, 0, 0},  /* NOM - 37.5 MHz (SVS)       */
    {HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0, 16, 0, 0, 0},  /* MAX - 75 MHz    (NOMINAL)  */
    {HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR), MUX_GCC, SRC_GPLL0, 16, 0, 0, 0}   /* DEFAULT - 75 MHz (Max Nom) */
  },

  .CNOC_Periph_Cfg =
  {
    {HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0}, /* PERF NONE                    */
    {HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0}, /* MIN - 19.2 MHz               */
    {HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR), MUX_GCC, SRC_GPLL0, 24, 0, 0, 0}, /* NOM - 50 MHz (SVS)           */
    {HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR), MUX_GCC, SRC_GPLL0, 12, 0, 0, 0}, /* MAX - 100 MHz    (NOMINAL)   */
    {HWIO_ADDR(GCC_CNOC_PERIPH_CMD_RCGR), MUX_GCC, SRC_GPLL0, 12, 0, 0, 0}  /* DEFAULT - 100 MHz (Max Nom)  */
  },

  /* SDC configuration : for backwards compatiblity to the old API */
  .SDC_Cfg =
  {
    0,       /* PERF NONE                 */
    400,     /* MIN - 400KHz              */
    25000,   /* NOMINAL - 25MHz           */
    50000,   /* MAX - 50MHz               */
    25000    /* DEFAULT - SAME AS NOMINAL */
  },

  /*  SDC extended configurations */
  .SDC1_Ext_Cfg =
  {
    {   400,  {0, MUX_GCC, SRC_CXO,   24, 1, 4, 4}},
    { 25000,  {0, MUX_GCC, SRC_GPLL0_DIV2, 12, 1, 2, 2}},
    { 50000,  {0, MUX_GCC, SRC_GPLL0_DIV2, 12, 0, 0, 0}},
    {100000,  {0, MUX_GCC, SRC_GPLL0, 12, 0, 0, 0}},
    {192000,  {0, MUX_GCC, SRC_GPLL4, 16, 0, 0, 0}},
    {384000,  {0, MUX_GCC, SRC_GPLL4,  8, 0, 0, 0}},
    {0}
  },
  
  /*  SDC extended configurations */
  .SDC2_Ext_Cfg =
  {
    {   400,  {0, MUX_SDCC2, SRC_CXO,        24, 1, 4, 4}},
    { 25000,  {0, MUX_SDCC2, SRC_GPLL0_DIV2, 12, 1, 2, 2}},
    { 50000,  {0, MUX_SDCC2, SRC_GPLL0_DIV2, 12, 0, 0, 0}},
    {100000,  {0, MUX_SDCC2, SRC_GPLL0,      12, 0, 0, 0}},
    {192000,  {0, MUX_SDCC2, SRC_GPLL4,      16, 0, 0, 0}},
    {0}
  },

  /* Crypto */
  .CE_Cfg =
  {
    HWIO_ADDR(GCC_CE1_CMD_RCGR), MUX_GCC, SRC_GPLL0, 7, 0, 0, 0   /* 171.43 MHz */
  },

  /* USB */
  .USB_Cfg =
  {
    HWIO_ADDR(GCC_USB30_MASTER_CMD_RCGR), MUX_GCC, SRC_GPLL0, 6, 0, 0, 0   /* 200 MHz */
  },

  /*UART */
  .UART_Cfg = 
  {
    {HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR), MUX_GCC, SRC_CXO,   0,  0,     0,     0}, /* PERF-NONE */
    {HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 1, 96, 15625, 15625}, /*MIN - 3.6864 MHz */
    {HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 1, 96, 15625, 15625}, /* NOMINAL - 3.6864 MHz MHz */
    {HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 1, 96, 15625, 15625}, /* MAX - 3.6864 MHz MHz */
    {HWIO_ADDR(GCC_BLSP1_UART1_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 1, 96, 15625, 15625}, /* DEFAULT - SAME AS NOMINAL */	  
  },

  /* HMSS AHB configuration */
  .HMSS_AHB_Cfg =
  {
    HWIO_ADDR(GCC_HMSS_AHB_CMD_RCGR), MUX_GCC, SRC_CXO, 1, 0, 0, 0 /* 19.2 MHZ */   
  },

  /* I2C */
 .I2C_Cfg = 
  {
    {HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR), MUX_GCC, SRC_CXO,    0, 0, 0, 0}, /* PERF-NONE */
    {HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0}, /* MIN - 19.2 MHz */
    {HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 24, 0, 0, 0}, /* NOMINAL - 50 MHz */
    {HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR), MUX_GCC, SRC_GPLL0, 24, 0, 0, 0}, /* MAX - 50 MHz */
    {HWIO_ADDR(GCC_BLSP1_QUP1_I2C_APPS_CMD_RCGR), MUX_GCC, SRC_CXO,    1, 0, 0, 0}, /* DEFAULT - 19.2 MHz */
  },

  /* BLSP*_QUP*_SPI configurations */
  .SPI_Cfg =
  {
    { 19200, {0, MUX_GCC, SRC_CXO,    1, 0, 0, 0}},
    { 50000, {0, MUX_GCC, SRC_GPLL0, 24, 0, 0, 0}},
    {0}
  },

  .QSPISer_Cfg =
  {
    { 80200, {HWIO_ADDR(GCC_QSPI_SER_CMD_RCGR), MUX_QSPI, SRC_GPLL1_DIV2, 10, 0, 0, 0}},
    {160400, {HWIO_ADDR(GCC_QSPI_SER_CMD_RCGR), MUX_QSPI, SRC_GPLL1, 10, 0, 0, 0}},
    {267300, {HWIO_ADDR(GCC_QSPI_SER_CMD_RCGR), MUX_QSPI, SRC_GPLL1,  6, 0, 0, 0}},
    {320800, {HWIO_ADDR(GCC_QSPI_SER_CMD_RCGR), MUX_QSPI, SRC_GPLL1,  5, 0, 0, 0}},
    {0}
  },
  /* UFS */
  .UFS_Cfg = 
  {
    {HWIO_ADDR(GCC_UFS_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,   1,  0, 0, 0}, /* OFF */
    {HWIO_ADDR(GCC_UFS_AXI_CMD_RCGR), MUX_GCC, SRC_CXO,   1,  0, 0, 0}, /* MIN - 19.2 MHz */
    {HWIO_ADDR(GCC_UFS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0, 6,  0, 0, 0}, /* NOMINAL - 200 MHz */
    {HWIO_ADDR(GCC_UFS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0, 6,  0, 0, 0}, /* MAX - 200 MHz */
    {HWIO_ADDR(GCC_UFS_AXI_CMD_RCGR), MUX_GCC, SRC_GPLL0, 6,  0, 0, 0}, /* DEFAULT - SAME AS NOMINAL */
  },
  
  /* UFS ICE CORE */
  .UFS_Ice_Cfg = 
  {
    {HWIO_ADDR(GCC_UFS_ICE_CORE_CMD_RCGR), MUX_GCC, SRC_CXO,   1,  0, 0, 0}, /* OFF */
    {HWIO_ADDR(GCC_UFS_ICE_CORE_CMD_RCGR), MUX_GCC, SRC_CXO,   1,  0, 0, 0}, /* MIN - 19.2 MHz */
    {HWIO_ADDR(GCC_UFS_ICE_CORE_CMD_RCGR), MUX_GCC, SRC_GPLL0, 4,  0, 0, 0}, /* NOMINAL - 300 MHz */
    {HWIO_ADDR(GCC_UFS_ICE_CORE_CMD_RCGR), MUX_GCC, SRC_GPLL0, 4,  0, 0, 0}, /* MAX - 300 MHz */
    {HWIO_ADDR(GCC_UFS_ICE_CORE_CMD_RCGR), MUX_GCC, SRC_GPLL0, 4,  0, 0, 0}, /* DEFAULT - SAME AS NOMINAL */
  },
};


boolean (*Clock_MuxMap[NUM_MUX_TYPES])(ClockSourceType, uint32 *) =
{
  Clock_SourceMapToGCC, 
  Clock_SourceMapToMMSS,
  Clock_SourceMapToSDCC2,
  Clock_SourceMapToQSPI,
};

/*=========================================================================
      Functions
==========================================================================*/

/* ============================================================================
**  Function : Clock_RailwayCfg
** ============================================================================
*/
/*!
    Return a pointer to the Railway configuration data.

   @param  None

   @retval a pointer to the Railway configuration data

*/
Clock_RailwayType *Clock_RailwayConfig( void )
{
  return &ClockRailway;
}

/* ============================================================================
**  Function : Clock_Config
** ============================================================================
*/
/*!
    Return a pointer to the configuration data.

   @param  None

   @retval a pointer to the configuration data

*/
Clock_ConfigType *Clock_Config( void )
{
  return &Clock_ConfigData;
}

/* ============================================================================
**  Function : Clock_SourceMapToMux
** ============================================================================
*/
boolean Clock_SourceMapToMux
(
  const ClockConfigMuxType *pConfig,
  uint32 *nMuxValue
)
{
  if( (pConfig == NULL) ||
      (nMuxValue == NULL) ||
      pConfig->eMux >= NUM_MUX_TYPES )
  {
    return FALSE;
  }

  return Clock_MuxMap[pConfig->eMux](pConfig->eSource, nMuxValue);
}


/* ============================================================================
**  Function : Clock_SourceMapToGCC
** ============================================================================
*/
/*!
   Map the source enumeration to a physical mux setting for GCC.

   @param  eSource : The source enumeration to map.
   @param  nMuxValue : output parameter.

   @retval a pointer to the configuration data

*/
boolean Clock_SourceMapToGCC(ClockSourceType eSource, uint32 *nMuxValue)
{
  switch( eSource )
  {
    case SRC_CXO:
      *nMuxValue = 0;
      break;
    case SRC_GPLL0:
    case SRC_EXT1:
      *nMuxValue = 1;
      break;
    case SRC_GPLL1:
      *nMuxValue = 4;
      break;
    case SRC_GPLL2:
    case SRC_EXT2:
      *nMuxValue = 2;
      break;
    case SRC_GPLL3:
      *nMuxValue = 3;
      break;
    case SRC_GPLL4:
    case SRC_GPLL5:
      *nMuxValue = 5;
      break;      
    case SRC_GPLL0_DIV2:
      *nMuxValue = 6;
      break;
    default:
      return FALSE;
  }
  return TRUE;
}


/* ============================================================================
**  Function : Clock_SourceMapToSDCC2
** ============================================================================
*/
/*!
   Map the source enumeration to a physical mux setting for GCC.

   @param  eSource : The source enumeration to map.
   @param  nMuxValue : output parameter.

   @retval a pointer to the configuration data

*/
boolean Clock_SourceMapToSDCC2(ClockSourceType eSource, uint32 *nMuxValue)
{
  switch( eSource )
  {
    case SRC_CXO:
      *nMuxValue = 0;
      break;
    case SRC_GPLL0:
      *nMuxValue = 1;
      break;
    case SRC_GPLL4:
      *nMuxValue = 5;
      break;      
    case SRC_GPLL0_DIV2:
      *nMuxValue = 2;
      break;
    default:
      return FALSE;
  }
  return TRUE;
}


/* ============================================================================
**  Function : Clock_SourceMapToQSPI
** ============================================================================
*/
/*!
   Map the source enumeration to a physical mux setting for GCC.

   @param  eSource : The source enumeration to map.
   @param  nMuxValue : output parameter.

   @retval a pointer to the configuration data

*/
boolean Clock_SourceMapToQSPI(ClockSourceType eSource, uint32 *nMuxValue)
{
  switch( eSource )
  {
    case SRC_CXO:
      *nMuxValue = 0;
      break;
    case SRC_GPLL0:
      *nMuxValue = 1;
      break;
    case SRC_GPLL1:
      *nMuxValue = 4;
      break;
    case SRC_GPLL4:
      *nMuxValue = 5;
      break;      
    case SRC_GPLL0_DIV2:
      *nMuxValue = 3;
      break;
   case SRC_GPLL1_DIV2:
     *nMuxValue = 6;
     break;
    default:
      return FALSE;
  }
  return TRUE;
}



/* ============================================================================
**  Function : Clock_SourceMapToMMSS
** ============================================================================
*/
/*!
   Map a ClockSourceType into a physical mux setting for the MMSS muxes.

   @param  None

   @retval a pointer to the configuration data

*/
boolean Clock_SourceMapToMMSS(ClockSourceType eSource, uint32 *nMuxValue)
{
  switch( eSource )
  {
    case SRC_CXO:
      *nMuxValue = 0;
      break;
    case SRC_MMPLL0:
    case SRC_EXT1:
      *nMuxValue = 1;
      break;
    case SRC_MMPLL5:
    case SRC_EXT2:
      *nMuxValue = 2;
      break;
    case SRC_GPLL0:
      *nMuxValue = 5;
      break;
    case SRC_GPLL0_DIV2:
      *nMuxValue = 6;
      break;
    default:
      return FALSE;
  }
  return TRUE;
}

/* ============================================================================
**  Function : Clock_EnableSource
** ============================================================================
*/

boolean Clock_EnableSource( ClockSourceType eSource )
{
  boolean rtrn = FALSE;

  switch( eSource )
  {
    case SRC_CXO:
      rtrn = TRUE;
      break;

    case SRC_GPLL0:
    case SRC_GPLL0_DIV2:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL0_Cfg);
      HWIO_OUTF(GCC_GPLL0_USER_CTL, PLLOUT_LV_EARLY, 1);
      break;

    case SRC_GPLL1:
    case SRC_GPLL1_DIV2:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL1_Cfg);
      HWIO_OUTF(GCC_GPLL1_USER_CTL, PLLOUT_LV_EARLY, 1);
      break;

    case SRC_GPLL2:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL2_Cfg);
      break;

    case SRC_GPLL3:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL3_Cfg);
      break;

    case SRC_GPLL4:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL4_Cfg);
      break;

    case SRC_GPLL5:
      rtrn = Clock_EnablePLL(&Clock_ConfigData.PLL5_Cfg);
      break;

    default:
      break;
  }
  return rtrn;
}

/* ============================================================================
**  Function : Clock_DisableSource
** ============================================================================
*/
boolean Clock_DisableSource( ClockSourceType eSource )
{
  boolean rtrn = FALSE;

  switch( eSource )
  {
    case SRC_CXO:
      rtrn = TRUE;
      break;

    case SRC_GPLL0:
    case SRC_GPLL0_DIV2:
      /* There is currently no use case to disable GPLL0 in XBL Loader. */
      break;

    case SRC_GPLL1:
    case SRC_GPLL1_DIV2:
      rtrn = Clock_DisablePLL(&Clock_ConfigData.PLL1_Cfg);
      break;

    case SRC_GPLL2:
      rtrn = Clock_DisablePLL(&Clock_ConfigData.PLL2_Cfg);
      break;

    case SRC_GPLL3:
      rtrn = Clock_DisablePLL(&Clock_ConfigData.PLL3_Cfg);
      break;

    case SRC_GPLL4:
      rtrn = Clock_DisablePLL(&Clock_ConfigData.PLL4_Cfg);
      break;

    case SRC_GPLL5:
      rtrn = Clock_DisablePLL(&Clock_ConfigData.PLL5_Cfg);
      break;

    default:
      break;
  }
  return rtrn;
}

/* ============================================================================
**  Function : Clock_ConfigureSource
** ============================================================================
*/
boolean Clock_ConfigureSource( ClockSourceType eSource )
{
  boolean rtrn = FALSE;

  switch( eSource )
  {
    case SRC_CXO:
      rtrn = TRUE;
      break;

    case SRC_GPLL0:
    case SRC_GPLL0_DIV2:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL0_Cfg);
      HWIO_OUTF(GCC_GPLL0_USER_CTL, PLLOUT_LV_EARLY, 1);
      break;

    case SRC_GPLL1:
    case SRC_GPLL1_DIV2:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL1_Cfg);
      HWIO_OUTF(GCC_GPLL1_USER_CTL, PLLOUT_LV_EARLY, 1);
      break;

    case SRC_GPLL2:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL2_Cfg);
      break;

    case SRC_GPLL3:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL3_Cfg);
      break;

    case SRC_GPLL4:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL4_Cfg);
      break;

    case SRC_GPLL5:
      rtrn = Clock_ConfigurePLL(&Clock_ConfigData.PLL5_Cfg);
      break;

    default:
      break;
  }
  return rtrn;
}
