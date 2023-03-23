#ifndef PARKA_UTIL_TIMER_HPP
#define PARKA_UTIL_TIMER_HPP

#include "parka/util/primitives.hpp"

typedef struct CpuTimer *CpuTimerId;
typedef struct ClockTimer *ClockTimerId;

CpuTimerId cpuTtimerStart(void);
f64 cpuTimerStop(CpuTimerId id);

ClockTimerId clockTimerStart(void);
f64 clockTimerStop(ClockTimerId id);

#endif
