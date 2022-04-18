/** vi: tw=128 ts=3 sw=3 et
@file udog_hal_sdm660_cdsp.c
@brief This file contains the API details for the Dog Services, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2016-17 by Qualcomm Technologies Incorporated.  All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.qdsp6/1.0.c2/debugtools/dog/src/udog_hal_sdm660_cdsp.c#1 $
$DateTime: 2020/02/10 01:57:30 $
$Change: 22511909 $
$Author: pwbldsvc $
===============================================================================*/

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

FUNCTIONS
  HAL_dogKick
  HAL_dogRegisterBark
  HAL_dogForceBite
  HAL_dogForceNMI
  HAL_dogBarkISR

Wrapper FUNCTIONS
  dog_force_bite
  dog_force_kick

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

#include "comdef.h"             /* Definitions for byte, word, etc.     */
#include "HALhwio.h"
#include "dog_hal.h"
#include "dog_hal_sdm660_cdsp.h"
#include "msmhwiobase.h"
#include "err.h"
#include "qurt.h"

#define DOG_BITE_ENABLE_TIMEOUT_NOW_SLCK    0x0001          // BITE "NOW" 

volatile boolean dog_intentional_timeout_flag = FALSE;
#if defined(FEATURE_DISABLE_HW_WATCHDOG)
volatile boolean dog_hal_disable_for_bringup = TRUE;
#else
volatile boolean dog_hal_disable_for_bringup = FALSE;
#endif

/** =====================================================================
 * Function:
 *     HAL_dogBarkISR
 *
 * Description:
 *     This function is called when the watchdog bark interrupt occurs
 *
 * Parameters:
 *     callback_param : not used
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogBarkISR(unsigned int callback_param)
{
   if (qurt_island_get_status() == TRUE)
   {
      // When bark timeout occurs, hw dog is kicked only when in Island mode. 
      // This was done because there are no deferrable utimers available in island mode
      // to kick the hw dog and avoid unnecessary wakeup of Q6 in automatic power collapse and 
      // full power collapse.
      HAL_dogKick();
   }
   else
   {
      ERR_FATAL("DOG BARK Starvation %d %d %d",
                HWIO_TURING_QDSP6SS_WDOG_BITE_TIME_IN, // supply BITE timer value
                HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_IN, // supply BARK timer value
                HWIO_TURING_QDSP6SS_WDOG_NMI_TIME_IN   // supply NMI/UNMASKED timer value
               );
   }
}

/** =====================================================================
 * Function:
 *     HAL_dogKick
 *
 * Description:
 *     This function kicks the hardware dog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogKick(void)
{
   if (!dog_intentional_timeout_flag)
   {
      HWIO_TURING_QDSP6SS_WDOG_RESET_OUT(1 << HWIO_TURING_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT);
   }
}

/** =====================================================================
* Function:
*     HAL_dogForceBite
*
* Description:
*       Force the watchdog to bite
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void HAL_dogForceBite(void)
{
   if(dog_hal_disable_for_bringup != TRUE)
   {
      // KICK DOG
      HWIO_TURING_QDSP6SS_WDOG_RESET_OUT(1 << HWIO_TURING_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT);
      
      // SET BARK TIMEOUT AS MAX
      HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_OUTM(HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK, HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK);
     
      // DISABLE NMI
      HWIO_TURING_QDSP6SS_WDOG_CTL_OUTM(HWIO_TURING_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK, 0 << HWIO_TURING_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT);

      // SET MINIMUM TIMEOUT
      HWIO_TURING_QDSP6SS_WDOG_BITE_TIME_OUTM(HWIO_TURING_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK, DOG_BITE_ENABLE_TIMEOUT_NOW_SLCK);

      // ENABLE BITE
      HWIO_TURING_QDSP6SS_WDOG_CTL_OUTM(HWIO_TURING_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 1 << HWIO_TURING_QDSP6SS_WDOG_CTL_ENABLE_SHFT);

      // KICK DOG
      HWIO_TURING_QDSP6SS_WDOG_RESET_OUT(1 << HWIO_TURING_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT);

      dog_intentional_timeout_flag = TRUE;                                          //Flag to block kicks
   }
}

/** =====================================================================
* Function:
*     HAL_dogDisableBark_NMI
*
* Description:
*     Disable the watchdog Bark and NMI
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void HAL_dogDisableBark_NMI(void)
{
   if(dog_hal_disable_for_bringup != TRUE)
   {
      // SET BARK TIMEOUT AS MAX
      HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_OUTM(HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK, HWIO_TURING_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK);
    
      // DISABLE NMI
      HWIO_TURING_QDSP6SS_WDOG_CTL_OUTM(HWIO_TURING_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK, 0 << HWIO_TURING_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT);
   }
}

/** =====================================================================
* Function: Wrapper function
*     dog_disable_bark_nmi
*
* Description:
*     Disable the watchdog to Bark and NMI
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void dog_disable_bark_nmi(void)
{
   HAL_dogDisableBark_NMI();
}

/** =====================================================================
* Function: Wrapper function
*     dog_force_bite
*
* Description:
*       Force the watchdog to bite
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void dog_force_bite(void)
{
   HAL_dogForceBite();
}

/** =====================================================================
 * Function: Wrapper function
 *     dog_force_kick
 *
 * Description:
 *     This function kicks the hardware dog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void dog_force_kick(void)
{
   HAL_dogKick();
}
