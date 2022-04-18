#ifndef CLOCKBSP_H
#define CLOCKBSP_H
/**
==============================================================================

  @file ClockBSP.h

  Internal header file for the BSP data structures.

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

#include "ClockBoot.h"
#include "ClockCommon.h"
#include "railway.h"

#define PRE_SIL
#define DEVICE_ID_SDM660      0x6
#define DEVICE_ID_SDM630      0x7
#define PART_NUM_SDM636       0x0cc
#define PART_NUM_SDA636       0x0cd

/*=========================================================================
      References
==========================================================================*/

/*=========================================================================
      Definitions
==========================================================================*/

/* For use with APCS_ALIAS0_CMD_RCGR */
typedef enum {
  APCS_SOURCE_CXO        = 0x0, // refRoot_Clk
  APCS_SOURCE_GPLL4_MAIN = 0x1, // SYS_apcsAux_Clk_2
  APCS_SOURCE_APLL0_MAIN = 0x2, // APLL0_main
  APCS_SOURCE_AG_MAIN    = 0x3, // Agera PLL main
  APCS_SOURCE_GPLL0_MAIN = 0x4, // SYS_apcsAux_Clk_3
  APCS_SOURCE_AG_EARLY   = 0x5, // Agera PLL early
  APCS_SOURCE_QSB        = 0x6, // SYS_apcsQsb_Clk
} ClockAPCSSourceSelectType;

/* For use with APCS_COMMON_CCI_CMD_RCGR */
typedef enum {
  CCI_SOURCE_CXO        = 0x0, // refRoot_Clk
  CCI_SOURCE_GPLL4_MAIN = 0x3, // Agera PLL main
  CCI_SOURCE_GPLL0_MAIN = 0x4, // SYS_apcsAux_Clk_3
  CCI_SOURCE_QSB        = 0x6, // SYS_apcsQsb_Clk
} ClockCCISourceSelectType;

#define SPARK_CONFIG_CTL 0x4001055B
#define AGERA_CONFIG_CTL 0x00000006200D4828



#define DIV2X(d) ((int)(2*(d)))
/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * ClockConfigApcsCfgType
 *
 * Parameters used for configuring APCS PLLs.
 *
 */
typedef struct sbl_clock_apcs_pll_cfg
{
  ClockConfigPLLType PLL_Cfg;
  uintnt                    nCPUCMDRCGRAddr;
  ClockAPCSSourceSelectType eCPUSource;
  uint32                    nCPUDiv2x;
  ClockCCISourceSelectType  eCCISource;
  uint32                    nCCIDiv2x;
  uint32 nFrequency;
} ClockConfigApcsCfgType;

/*
 * ClockConfigCPUL2Type
 *
 * Parameters used for configuring a standard clock multiplexer.
 *
 *  nSourceHF   - The HF mux source to use.
 *  nSourceLF   - The LF mux source to use. 
 *  nL          - The L value of the HFPLL, 0 indicates not a PLL 
 */
typedef struct sbl_clock_l2cpu_cfg
{
  uint32 nSourceHF;
  uint32 nSourceLF;
  uint32 nGFMDiv;
  uint32 nL;
  uint32 nPLLPostDiv;
  uint32 nFrequency;
} ClockConfigCPUL2Type;

/* Data structure for configuration data */
typedef struct
{
  /* PLL configurations */
  ClockConfigPLLType PLL0_Cfg;
  ClockConfigPLLType PLL1_Cfg;
  ClockConfigPLLType PLL2_Cfg;
  ClockConfigPLLType PLL3_Cfg;
  ClockConfigPLLType PLL4_Cfg;
  ClockConfigPLLType PLL5_Cfg;

  /* PLL Configurations for SDM660 APCS */
  ClockConfigApcsCfgType CPU_Cfg[CLOCK_BOOT_PERF_NUM];

  /* PLL Configurations for SDM630 APCS */
  ClockConfigApcsCfgType CPU_Cfg_SDM630[CLOCK_BOOT_PERF_NUM];

  /* Configurations for RPM */
  ClockConfigMuxType RPM_Cfg[CLOCK_BOOT_PERF_NUM];

  /* System NOC config data */
  ClockConfigMuxType SNOC_Cfg[CLOCK_BOOT_PERF_NUM];

  /* PIMEM config data */
  ClockConfigMuxType PIMEM_Cfg[CLOCK_BOOT_PERF_NUM];

  /* HS System NOC config data */
  ClockConfigMuxType HS_SNOC_Cfg[CLOCK_BOOT_PERF_NUM];

  /* Config NOC config data */
  ClockConfigMuxType CNOC_Cfg[CLOCK_BOOT_PERF_NUM];

  /* Config-peripheral NOC config data */
  ClockConfigMuxType CNOC_Periph_Cfg[CLOCK_BOOT_PERF_NUM];

  /* SDC table (for backwards compatibility) */
  uint32 SDC_Cfg[CLOCK_BOOT_PERF_NUM];

  /* SDC extended configurations */
  ClockFreqMuxCfgType SDC1_Ext_Cfg[7];
  
  ClockFreqMuxCfgType SDC2_Ext_Cfg[6];

  /* Crypto clock config */
  ClockConfigMuxType CE_Cfg;

  /* USB clock config */
  ClockConfigMuxType USB_Cfg;

  /* UART clock config */
  ClockConfigMuxType UART_Cfg[CLOCK_BOOT_PERF_NUM];

  /* Krait AHB config data */
  ClockConfigMuxType HMSS_AHB_Cfg;

  /* I2C clock config */
  ClockConfigMuxType I2C_Cfg[CLOCK_BOOT_PERF_NUM];

  /* SPI configurations */
  ClockFreqMuxCfgType SPI_Cfg[3];

  /* SPI Serial configurations */
  ClockFreqMuxCfgType QSPISer_Cfg[5];

  /* UFS clock config */
  ClockConfigMuxType UFS_Cfg[CLOCK_BOOT_PERF_NUM];

  /* UFS ICE CORE clock config */
  ClockConfigMuxType UFS_Ice_Cfg[CLOCK_BOOT_PERF_NUM];

} Clock_ConfigType;

/* Data structure for Railway data */
typedef struct
{
  char*             CxRail;
  int               nCxRailId;
  railway_voter_t   CxVoter;
  char*             EBIRail;
  int               nEBIRailId;
  railway_voter_t   EBIVoter;
}Clock_RailwayType;

extern Clock_ConfigType *Clock_Config( void );
extern Clock_RailwayType *Clock_RailwayConfig( void );
extern boolean Clock_EnableSource( ClockSourceType eSource );
extern boolean Clock_DisableSource( ClockSourceType eSource );
extern boolean Clock_ConfigureSource( ClockSourceType eSource );

boolean Clock_SourceMapToMux
(
  const ClockConfigMuxType *pConfig,
  uint32 *nMuxValue
);

#endif /* !CLOCKBSP_H */

