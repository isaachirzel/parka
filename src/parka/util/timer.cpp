#include "parka/util/timer.hpp"

f64 Timer::split()
{
	auto now = Clock::now();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - _splitTime).count();
	auto elapsedSeconds = (f64)nanoseconds / 1'000'000'000.0;
	
	_splitTime = now;

	return elapsedSeconds;
}

f64 Timer::stop()
{
	auto now = Clock::now();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - _startTime).count();
	auto elapsedSeconds = (f64)nanoseconds / 1'000'000'000.0;

	return elapsedSeconds;
}
