#include "ClockBoot.h"
//#include "Drivers/ClockDxe/ClockDriver.h"
#include "DALSys.h"
#include "DDIChipInfo.h"
#include "Library/HALclkSharedLib/HALavs.h"
#ifdef CLOCK_ULOG_STUB
  #include "ClockULogStub.h"
#else
  #include "ULogFront.h"
#endif
#include "ClockDefs.h"
//#include "drivers/ClockDxe/ClockBSP.h"
#include "HALclk.h"

#ifdef CLOCK_NPA_STUB
#include "ClockNPAStub.h"
#else
  #include "npa.h"
  #include "npa_resource.h"
#endif

/* =========================================================================
**  Function : Clock_SetBIMCSpeed
** =========================================================================*/
/*!
    Switch DDR and the related BIMC roots to the requested frequency

    @param -  nFreqHz [in] Frequency to search for in the table
    @return - FALSE on fail, TRUE on success

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetBIMCSpeed(uint32 nFreqKHz )
{
  return TRUE;
}