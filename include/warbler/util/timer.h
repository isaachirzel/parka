#ifndef WARBLER_UTIL_TIMER_H
#define WARBLER_UTIL_TIMER_H

#include <warbler/util/primitives.h>

typedef struct CpuTimer *CpuTimerId;
typedef struct ClockTimer *ClockTimerId;

CpuTimerId cpuTtimerStart(void);
f64 cpuTimerStop(CpuTimerId id);

ClockTimerId clockTimerStart(void);
f64 clockTimerStop(ClockTimerId id);

#endif
