#include "rpm_hwio.h"
#include "HALhwio.h"
#include "CoreVerify.h"
#include "swevent.h"
#include "gcc_reset_hwio.h"

extern uint32 rpm_in_core_dump_ctx;

void time_service_init(void)
{
  //allow read/write access to timer registers
  //TODO: make this write more obvious/indicative of whats going on
#ifndef QCS405_IMAGE_LAYOUT  
  HWIO_OUTI(RPM_QTMR_AC_CNTACRn_FG0, 0, 33);
#else
  HWIO_OUTI(RPM_QTMR_AC_CNTACR_n, 0, 33);
#endif	
  //enable RPM QTMR
  HWIO_OUTF(RPM_F0_QTMR_V1_CNTP_CTL, EN, 1);
}

static void qtimer_zero(void)
{
  if (rpm_in_core_dump_ctx ==1)
	  return;
  else
	  CORE_VERIFY(0);
}

uint64_t time_service_now(void)
{
    uint32_t first_hi, second_hi, lo;

    INTLOCK();

    do
    {
        first_hi = HWIO_IN(RPM_F0_QTMR_V1_CNTPCT_HI);
        __schedule_barrier();

        lo = HWIO_IN(RPM_F0_QTMR_V1_CNTPCT_LO);
        __schedule_barrier();

        second_hi = HWIO_IN(RPM_F0_QTMR_V1_CNTPCT_HI);
        __schedule_barrier();
    } while(first_hi != second_hi);

    INTFREE();
    if((!second_hi) && (!lo))
    {
      qtimer_zero();
    }
    return (((uint64_t)second_hi) << 32) | lo;
}


