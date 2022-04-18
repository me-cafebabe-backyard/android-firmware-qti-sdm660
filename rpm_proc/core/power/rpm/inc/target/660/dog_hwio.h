#ifndef __DOG_HWIO_H__
#define __DOG_HWIO_H__
/*
===========================================================================
*/
/**
  @file dog_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPM_DEC

  'Include' filters applied: WDOG[RPM_DEC]
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/power/rpm/inc/target/660/dog_hwio.h#1 $
  $DateTime: 2018/03/19 05:24:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"
#include "HALhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: RPM_DEC
 *--------------------------------------------------------------------------*/

#define RPM_DEC_REG_BASE                                                 (RPM_BASE      + 0x00080000)

#define HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR                                 (RPM_DEC_REG_BASE      + 0x00000008)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_RMSK                                        0x1
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_IN          \
        in_dword_masked(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR, HWIO_RPM_TIMERS_CLK_OFF_CTL_RMSK)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR, m)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_OUT(v)      \
        out_dword(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR,v)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR,m,v,HWIO_RPM_TIMERS_CLK_OFF_CTL_IN)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_BMSK                     0x1
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_SHFT                     0x0

#define HWIO_RPM_WDOG_RESET_ADDR                                         (RPM_DEC_REG_BASE      + 0x00000040)
#define HWIO_RPM_WDOG_RESET_RMSK                                                0x3
#define HWIO_RPM_WDOG_RESET_IN          \
        in_dword_masked(HWIO_RPM_WDOG_RESET_ADDR, HWIO_RPM_WDOG_RESET_RMSK)
#define HWIO_RPM_WDOG_RESET_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_RESET_ADDR, m)
#define HWIO_RPM_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_RESET_ADDR,v)
#define HWIO_RPM_WDOG_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_RESET_ADDR,m,v,HWIO_RPM_WDOG_RESET_IN)
#define HWIO_RPM_WDOG_RESET_SYNC_STATUS_BMSK                                    0x2
#define HWIO_RPM_WDOG_RESET_SYNC_STATUS_SHFT                                    0x1
#define HWIO_RPM_WDOG_RESET_WDOG_RESET_BMSK                                     0x1
#define HWIO_RPM_WDOG_RESET_WDOG_RESET_SHFT                                     0x0

#define HWIO_RPM_WDOG_CTRL_ADDR                                          (RPM_DEC_REG_BASE      + 0x00000044)
#define HWIO_RPM_WDOG_CTRL_RMSK                                                 0x3
#define HWIO_RPM_WDOG_CTRL_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_CTRL_ADDR,v)
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_BMSK                              0x2
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_SHFT                              0x1
#define HWIO_RPM_WDOG_CTRL_ENABLE_BMSK                                          0x1
#define HWIO_RPM_WDOG_CTRL_ENABLE_SHFT                                          0x0

#define HWIO_RPM_WDOG_BARK_TIME_ADDR                                     (RPM_DEC_REG_BASE      + 0x0000004c)
#define HWIO_RPM_WDOG_BARK_TIME_RMSK                                       0x1fffff
#define HWIO_RPM_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_RPM_WDOG_BARK_TIME_ADDR, HWIO_RPM_WDOG_BARK_TIME_RMSK)
#define HWIO_RPM_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_BARK_TIME_ADDR, m)
#define HWIO_RPM_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_BARK_TIME_ADDR,v)
#define HWIO_RPM_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_BARK_TIME_ADDR,m,v,HWIO_RPM_WDOG_BARK_TIME_IN)
#define HWIO_RPM_WDOG_BARK_TIME_SYNC_STATUS_BMSK                           0x100000
#define HWIO_RPM_WDOG_BARK_TIME_SYNC_STATUS_SHFT                               0x14
#define HWIO_RPM_WDOG_BARK_TIME_WDOG_BARK_VAL_BMSK                          0xfffff
#define HWIO_RPM_WDOG_BARK_TIME_WDOG_BARK_VAL_SHFT                              0x0

#define HWIO_RPM_WDOG_BITE_TIME_ADDR                                     (RPM_DEC_REG_BASE      + 0x00000050)
#define HWIO_RPM_WDOG_BITE_TIME_RMSK                                       0x1fffff
#define HWIO_RPM_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_RPM_WDOG_BITE_TIME_ADDR, HWIO_RPM_WDOG_BITE_TIME_RMSK)
#define HWIO_RPM_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_BITE_TIME_ADDR, m)
#define HWIO_RPM_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_BITE_TIME_ADDR,v)
#define HWIO_RPM_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_BITE_TIME_ADDR,m,v,HWIO_RPM_WDOG_BITE_TIME_IN)
#define HWIO_RPM_WDOG_BITE_TIME_SYNC_STATUS_BMSK                           0x100000
#define HWIO_RPM_WDOG_BITE_TIME_SYNC_STATUS_SHFT                               0x14
#define HWIO_RPM_WDOG_BITE_TIME_WDOG_BITE_VAL_BMSK                          0xfffff
#define HWIO_RPM_WDOG_BITE_TIME_WDOG_BITE_VAL_SHFT                              0x0

#endif /* __DOG_HWIO_H__ */
