/*! \file 
*  \n
*  \brief pm_comm_spmi_lite.c ---- 
*  \n
* *  \n &copy; Copyright 2014 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/comm/spmi_lite/src/pm_comm_spmi_lite.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/04/14   aks   created  
========================================================================== */

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include "pm_comm.h"  
#include "SpmiBus.h"
#include "CoreVerify.h"


static boolean spmi_initialized = FALSE;

__attribute__((section("pm_dram_reclaim_pool")))
pm_err_flag_type pm_comm_channel_init_internal(void)
{
    Spmi_Result spmi_result = SPMI_SUCCESS;
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    
    // initialize the SPMI BUS
    spmi_result = SpmiBus_Init();

    if(SPMI_SUCCESS  == spmi_result )
    {
        spmi_initialized = TRUE;
    }
    else
    {
        CORE_VERIFY(0); //if spmi_bus init fails err_fatal
    }
    
    return err;
}

pm_err_flag_type pm_comm_read_byte(uint32 slave_id, uint16 addr, uint8* data, uint8 priority)
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result spmi_result = SPMI_SUCCESS;
    /* Read the data from the SPMI */
    uint32               dataReadLength = 0;
    
    if(TRUE == spmi_initialized)
    {
       spmi_result = SpmiBus_ReadLong( slave_id, (Spmi_AccessPriority)priority, addr, data, 1, &dataReadLength);

       if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG__SPMI_OPT_ERR; }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR;
    }

    return err;
}

pm_err_flag_type pm_comm_read_byte_mask(uint32 slave_id, uint16 addr, uint8 mask, uint8* data, uint8 priority)
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS;

    err = pm_comm_read_byte(slave_id,addr,data,priority);
    if ( err != PM_ERR_FLAG__SUCCESS ) 
    { 
        err = PM_ERR_FLAG__SPMI_OPT_ERR; 
    }
    else 
    { 
        *data = *data & mask; 
    }

    
    return err;
}



pm_err_flag_type pm_comm_write_byte(uint32 slave_id, uint16 addr, uint8 data, uint8 priority)
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result spmi_result = SPMI_SUCCESS;
    
    if(TRUE == spmi_initialized)
    {
        spmi_result = SpmiBus_WriteLong(slave_id, (Spmi_AccessPriority)priority, addr, &data, 1);

        if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG__SPMI_OPT_ERR; }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR;
    }

    return err;
}

pm_err_flag_type pm_comm_write_byte_mask(uint32 slave_id, uint16 addr, uint8 mask, uint8 value, uint8 priority)
{
    pm_err_flag_type         err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result       spmi_result = SPMI_SUCCESS;
    uint32                   dataReadLength = 1;
    uint8                    data = 0 ;

    if(TRUE == spmi_initialized)
    {
        /* Read the data from the SPMI and leave all the bits other than the mask to the previous state */
        spmi_result = SpmiBus_ReadLong(slave_id, (Spmi_AccessPriority)priority, addr, &data, 1, &dataReadLength);

        if ( spmi_result == SPMI_SUCCESS )
        {
            data &= (~mask); 
            data |= (value & mask);

            spmi_result = SpmiBus_WriteLong(slave_id, (Spmi_AccessPriority)priority, addr, &data, 1);

            if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG__SPMI_OPT_ERR; }
        }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR;
    }

    return err;
}


pm_err_flag_type pm_comm_write_byte_array(uint32 slave_id, uint16 addr, uint32 num_bytes, uint8* data, uint8 priority) 
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result spmi_result = SPMI_SUCCESS;

    if(TRUE == spmi_initialized)
    {
        spmi_result = SpmiBus_WriteLong(slave_id, (Spmi_AccessPriority)priority, addr, data, num_bytes);

        if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG__SPMI_OPT_ERR ; }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR ;
    }

    return err ;
}

pm_err_flag_type pm_comm_read_byte_array (uint32 slave_id, uint16 addr, uint32 num_bytes, uint8* data, uint8 priority) 
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result spmi_result = SPMI_SUCCESS;
    /* Read the data from the SPMI */
    uint32               dataReadLength = 0;

    if(TRUE == spmi_initialized)
    {
        spmi_result = SpmiBus_ReadLong(slave_id, (Spmi_AccessPriority)priority, addr, data, num_bytes, &dataReadLength);

        if ( spmi_result != SPMI_SUCCESS ) { err = PM_ERR_FLAG__SPMI_OPT_ERR; }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR;
    }

    return err;
}

pm_err_flag_type  pm_comm_register_isr(uint32 slave_id, uint16 addr, uint8 irq_mask, void* isr_ptr, uint32 isr_ctx) 
{
    pm_err_flag_type err = PM_ERR_FLAG__SUCCESS ;
    Spmi_Result spmi_result = SPMI_SUCCESS;
    SpmiToken pm_token;
    uint8 periph_id = 0;

   
    if(TRUE == spmi_initialized)
    {
        periph_id = (uint8)(addr>>8);

        spmi_result = SpmiBus_RegisterIsr(slave_id, periph_id, irq_mask, (SpmiIsr)isr_ptr, (void*)isr_ctx, &pm_token);

        if(spmi_result != SPMI_SUCCESS) 
        { 
            err = PM_ERR_FLAG__SPMI_OPT_ERR; 
        }
    }
    else
    {
        err = PM_ERR_FLAG__SPMI_OPT_ERR;
    }

    return err;
}
