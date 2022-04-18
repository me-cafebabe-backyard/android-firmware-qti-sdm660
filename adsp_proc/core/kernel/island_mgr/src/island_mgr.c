/*======================================================================
                        island_mgr.c 

GENERAL DESCRIPTION
  Island Manager functions

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none

 Copyright (c) 2014  by Qualcomm Technologies, Inc.  All Rights Reserved.
 ======================================================================*/
#include <qurt.h>
#include <island_mgr.h>
#include "qdss.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "DALSys.h"
#include "DDIHWIO.h"

#define ISLAND_MGR_MAX_ATTRS 30 /* maximum number of attributes */

extern qurt_island_t g_island_spec_id;
extern int g_island_mgr_inited;

qurt_island_attr_resource_t g_uImageIslandData[19] = 
{
    /* Interrupt elements */
    {QURT_ISLAND_ATTR_INT, {{0}}   }, /* PMI */
    {QURT_ISLAND_ATTR_INT, {{2}}   }, /* q6ss_qtmr_irq[0] */
    {QURT_ISLAND_ATTR_INT, {{32}}   }, /* HW DOG Bark interrupt */
    {QURT_ISLAND_ATTR_INT, {{194}}  }, /* Island exit q6ss_spm_trig_done_irq_1 */
    {QURT_ISLAND_ATTR_INT, {{156}}  }, /* Island entry */
    {QURT_ISLAND_ATTR_INT, {{205}}  }, /* qTimer frame 3 pmu_lpi_sw_slp_tmr_int*/
    {QURT_ISLAND_ATTR_INT, {{206}}  }, /* core_bi_px_gpio_67 */
    {QURT_ISLAND_ATTR_INT, {{207}}  }, /* core_bi_px_gpio_68 */
    {QURT_ISLAND_ATTR_INT, {{208}}  }, /* core_bi_px_gpio_69 */
    {QURT_ISLAND_ATTR_INT, {{209}}  }, /* core_bi_px_gpio_70 */
    {QURT_ISLAND_ATTR_INT, {{210}} }, /* core_bi_px_gpio_71 */
    {QURT_ISLAND_ATTR_INT, {{211}} }, /* core_bi_px_gpio_72*/
    {QURT_ISLAND_ATTR_INT, {{212}} }, /* core_bi_px_gpio_73 */
    {QURT_ISLAND_ATTR_INT, {{213}} }, /* core_bi_px_gpio_74 */
    {QURT_ISLAND_ATTR_INT, {{214}} }, /* core_bi_px_gpio_75 */
    {QURT_ISLAND_ATTR_INT, {{215}} }, /* core_bi_px_gpio_76 */

    /* Memory range elements */
    {QURT_ISLAND_ATTR_MEMORY, 
     {{0x15780000, 4}} }, /* HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDRetc*/

    {QURT_ISLAND_ATTR_MEMORY, 
    {{0x15D90000, 4}} }, /* HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDRetc*/
 
    /* Indicate end of list */
    {QURT_ISLAND_ATTR_END_OF_LIST, {{0}} }
};

#if 0

If there are any physical addresses that need to be converted to virtual for an attr,
use the following code:

DalDeviceHandle *handle;
DALResult result;
uint8 *base_ptr;

      result = DAL_DeviceAttach(DALDEVICEID_HWIO, handle);
      if ( (DAL_SUCCESS != result) || (NULL == handle) ) {
         XXX ERROR XXX
      }
       if ( DAL_SUCCESS !=
             DalHWIO_MapRegion(handle,
                               “RPM_SS_MSG_RAM_START_ADDRESS_BASE”,
                               &base_ptr) ) {
         XXX ERROR XXX
      }
   }


#endif

int island_mgr_init(void)
{
    int qurt_rc;
    qurt_island_attr_t *island_attr;
    DalDeviceHandle *handle;
    DALResult dal_result;
    unsigned int rpm_ss_msg_ram_base_ptr;
    unsigned int clk_ctl_base_ptr;
    unsigned int lpass_base_ptr;
   // unsigned int periph_ss_base_ptr;

    dal_result = DAL_DeviceAttach(DALDEVICEID_HWIO, &handle);
    if((DAL_SUCCESS != dal_result) || (NULL == handle))
    {
	return ISLAND_MGR_EFAILED;
    }
    if(DAL_SUCCESS != DalHWIO_MapRegion(handle,"RPM_SS_MSG_RAM_START_ADDRESS",(uint8 **)&rpm_ss_msg_ram_base_ptr))
    {
	return ISLAND_MGR_EFAILED;
    }
    if(DAL_SUCCESS != DalHWIO_MapRegion(handle,"CLK_CTL",(uint8 **)&clk_ctl_base_ptr))
    {
	return ISLAND_MGR_EFAILED;
    }
    if(DAL_SUCCESS != DalHWIO_MapRegion(handle,"LPASS",(uint8 **)&lpass_base_ptr))
    {
	return ISLAND_MGR_EFAILED;
    }
    
    qurt_rc = qurt_island_attr_create(&island_attr, ISLAND_MGR_MAX_ATTRS);
    if (qurt_rc != QURT_EOK)
    {
        return ISLAND_MGR_EFAILED;
    }

    qurt_rc = qurt_island_attr_add(island_attr, g_uImageIslandData);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }

    qurt_rc = qurt_island_attr_add_mem(island_attr, rpm_ss_msg_ram_base_ptr, 0x00007000);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }
    qurt_rc = qurt_island_attr_add_mem(island_attr, clk_ctl_base_ptr, 0x000c0000);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }
    qurt_rc = qurt_island_attr_add_mem(island_attr, lpass_base_ptr, 0x00c00000);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }

    unsigned int stm_sns_ptr;
    unsigned int stm_adsp_ptr;
    QDSSGetSTMBaseAddrSensor((uint32 *)&stm_sns_ptr); 
    QDSSGetSTMBaseAddrADSP((uint32 *)&stm_adsp_ptr);
    qurt_rc = qurt_island_attr_add_mem(island_attr, stm_sns_ptr, 4);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }
    qurt_rc = qurt_island_attr_add_mem(island_attr, stm_adsp_ptr, 4);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }

    qurt_rc = qurt_island_spec_create(&g_island_spec_id, island_attr);
    if (qurt_rc != QURT_EOK)
    {
	qurt_island_attr_delete(island_attr);
	return ISLAND_MGR_EFAILED;
    }
    qurt_island_attr_delete(island_attr);

    g_island_mgr_inited=1;

    return ISLAND_MGR_EOK;
}
