/**
 * @file ddr_sdi_wrapper.c
 * @brief
 * Target specific DDR drivers.
 */
/*==============================================================================
                                EDIT HISTORY

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/DDRTargetLib/ddr_sdi_wrapper.c#4 $
$DateTime: 2017/03/02 23:04:43 $
$Author: pwbldsvc $
================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
02/17/17   din     Updated DDR dload cookie
07/20/15   tw      updated sanity ddr test to check across interleave
02/20/15   tw      Initial version.
================================================================================
                   Copyright 2015 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddrss_init_sdi.h"
#include <stdbool.h>
#include "DALSys.h"
#include "ddr_hwio.h"

/*==============================================================================
                                  MACROS
==============================================================================*/

/*==============================================================================
                                  DATA
==============================================================================*/
DDR_STRUCT *ddrsns_share_data_sdi = (DDR_STRUCT *)DDR_GLOBAL_STRUCT_DATARAM_ADDR;
static boolean ddr_init_status = FALSE;

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/

boolean Clock_ConfigureDDR( void );
void icb_sdi_save( void );
bool icb_sdi_restore( void );

static boolean ddr_test_read_write
(
  uint64 base,
  uint32 limit
)
{
  volatile uint32 *base_addr;
  uint32 data[limit];
  uint32 offset;
  base_addr = (uint32 *)base;
  limit >>= 2;
  for (offset = 0; offset <= limit; offset++)
  {
	data[offset] = base_addr[offset];
	base_addr[offset] = ~(~data[offset]);
  }
  for (offset = 0; offset <= limit; offset++)
  {
    if (base_addr[offset] != data[offset])
    {
      return FALSE;
    }
  }
  return TRUE;
}
/* ============================================================================
**  Function : ddr_sdi_init
** ============================================================================
*/
/*!
*   @brief
*   This function is called to reinitialize ddr in SDI context. 
*
*   @details
*   This function is called to reinitialize ddr in SDI context. 
*   lite library for both clock and bus will be called first to
*   prepare for data access on the ddr, then sdi version of ddr driver
*   will be called to take ddr out from self refresh.
*
*   @param
*   None
*
*   @par Dependencies
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/

void ddr_sdi_init(void)
{
  int *p = (int *)(0x146BF650);

  /* initialize clock for ddr */
  Clock_ConfigureDDR();
  
  /* initialize bus driver */
  icb_sdi_restore();
  
	*p = 0xCACEC00C;
  if (ddrsns_share_data_sdi->misc.chip_version  == 0x100 )
  {
    HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS_BOTH, 200000);
    ddr_init_status = TRUE;
  }
  /* reinitialize ddr driver */
  if (ddr_init_status == FALSE)
  {
	if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_mb) && 
		(ddrsns_share_data_sdi->ddr_size_info.ddr1_cs0_mb))
	{
		if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_mb) &&
		(ddrsns_share_data_sdi->ddr_size_info.ddr1_cs1_mb))
		{
			HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS_BOTH, 200000);
		}
		else
		{
			HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS0, 200000);
		}
	}
	
	else if (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_mb)
	{
		if (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_mb)
		{
			HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH0, DDR_CS_BOTH, 200000);
		}
		else
		{
			HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH0, DDR_CS0, 200000);
		}
	}		
	
//	HAL_DDR_Init_sdi(ddrsns_share_data_sdi,DDR_CH0, DDR_CS0, 8000);
  }

  *p = 0xDEADD00D;

  if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_mb) && 
     (ddrsns_share_data_sdi->ddr_size_info.ddr1_cs0_mb))
  {
    if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_mb) &&
       (ddrsns_share_data_sdi->ddr_size_info.ddr1_cs1_mb))
    {
      if ((ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_remapped_addr, 128)) &&
          (ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_remapped_addr+0x400, 128)) &&
          (ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_remapped_addr, 128)) &&
          (ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_remapped_addr+0x400, 128)))
      {
        *p = 0xCAFEBABE;
      }
    }
    else
    {
      if ((ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_remapped_addr, 128)) &&
          (ddr_test_read_write (ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_remapped_addr+0x400, 128)))
      {
        *p = 0xCAFEBABE;
      }
    }
  }
  if(*p != 0xCAFEBABE)
  {
    *p = 0xBADDB055;
  }
  ddr_init_status = TRUE;             
}

void ddr_sdi_exit(void)
{
  
  if (ddrsns_share_data_sdi->misc.chip_version  == 0x100 )
  {
    BIMC_Enter_Self_Refresh_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS_BOTH);
  }
  else if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs0_mb != 0) && 
     (ddrsns_share_data_sdi->ddr_size_info.ddr1_cs0_mb))
  {
    if((ddrsns_share_data_sdi->ddr_size_info.ddr0_cs1_mb) &&
    (ddrsns_share_data_sdi->ddr_size_info.ddr1_cs1_mb))
    {
      BIMC_Enter_Self_Refresh_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS_BOTH);
    }
    else
    {
      BIMC_Enter_Self_Refresh_sdi(ddrsns_share_data_sdi,DDR_CH_BOTH, DDR_CS0);
    }
  } 
  /* enable mpm freeze io */
  HWIO_OUTF(MPM2_MPM_DDR_PHY_FREEZEIO_EBI1, DDR_PHY_FREEZEIO_EBI1, 0x1 );
}

/*===========================================================================
FUNCTION
    ddr_mpm_config_ebi1_freeze_io_sdi
DESCRIPTION
    Freeze/unfreeze the IO to the DDR devices.  This implementation is required by the DSF drivers 
    (in file ddr_external.h) to allow Power Collapse or other operating modes where the output 
    to the DDR is disabled.
===========================================================================*/

void ddr_mpm_config_ebi1_freeze_io_sdi(boolean flag)
{
   HWIO_OUTF(MPM2_MPM_LOW_POWER_CFG, SW_EBI1_CTL_VALUE, (flag ? 1:0));
   HWIO_OUTF(MPM2_MPM_LOW_POWER_CFG, SW_EBI1_CTL_ENABLE, 0x1);

   // Freeze/unfreeze IO as requested by flag
   HWIO_OUTF(MPM2_MPM_DDR_PHY_FREEZEIO_EBI1, DDR_PHY_FREEZEIO_EBI1, (flag ? 1:0) );
}
