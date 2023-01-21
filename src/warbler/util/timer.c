#include <bits/time.h>
#include <warbler/util/print.h>
#include <warbler/util/timer.h>

#include <warbler/util/print.h>
#include <time.h>

// TODO: Make OS agnostic

typedef struct CpuTimer
{
	bool isRunning;
	struct timespec startTime;
} CpuTimer;

typedef struct ClockTimer
{
	bool isRunning;
	struct timespec startTime;
} ClockTimer;

static CpuTimer cpuTimers[16];
static ClockTimer clockTimers[16];
static usize cpuTimerCount = sizeof(cpuTimers) / sizeof(*cpuTimers);
static usize clockTimerCount = sizeof(clockTimers) / sizeof(*clockTimers);

static struct timespec getClockTime()
{
	struct timespec time;

	if (clock_gettime(CLOCK_MONOTONIC, &time))
			exitWithError("The system does not support a clock timer.");
			
	return time;
}

static struct timespec getCpuTime()
{
	struct timespec time;

	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time))
			exitWithError("The system does not support a CPU timer.");
			
	return time;
}

CpuTimerId cpuTimerStart(void)
{
	for (usize i = 0; i < cpuTimerCount; ++i)
	{
		CpuTimerId id = &cpuTimers[i];

		if (id->isRunning)
			continue;

		id->isRunning = true;
		id->startTime = getCpuTime();

		return id;
	}

	exitWithErrorFmt("Unable to create a CPU timer as all %zu CPU timers are currently running.", cpuTimerCount);
}

f64 cpuTimerStop(CpuTimerId id)
{
	struct timespec currentTime = getCpuTime();

	f64 elapsedSeconds = (f64) (currentTime.tv_sec - id->startTime.tv_sec)
		+ (f64) (currentTime.tv_nsec - id->startTime.tv_nsec) / 1.0e+9;

	id->isRunning = false;

	return elapsedSeconds;
}

ClockTimerId clockTimerStart(void)
{
	for (usize i = 0; i < clockTimerCount; ++i)
	{
		ClockTimerId id = &clockTimers[i];

		if (id->isRunning)
			continue;

		id->isRunning = true;
		id->startTime = getClockTime();

		return id;
	}

	exitWithErrorFmt("Unable to create a clock timer as all %zu clock timers are currently running.", clockTimerCount);
}

f64 clockTimerStop(ClockTimerId id)
{
	struct timespec currentTime = getClockTime();

	f64 elapsedSeconds = (f64) (currentTime.tv_sec - id->startTime.tv_sec)
		+ (f64) (currentTime.tv_nsec - id->startTime.tv_nsec) / 1.0e+9;

	id->isRunning = false;

	return elapsedSeconds;
}

