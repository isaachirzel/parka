#ifndef PARKA_UTIL_TIMER_HPP
#define PARKA_UTIL_TIMER_HPP

#include "parka/util/primitives.hpp"

#include <chrono>

class Timer
{
	using Clock = std::chrono::high_resolution_clock;
	
	std::chrono::time_point<Clock> _startTime;
	std::chrono::time_point<Clock> _stopTime;

public:

	void start() { _startTime = Clock::now(); }
	void stop() { _stopTime = Clock::now(); }

	const auto& startTime() const { return _startTime; }
	const auto& stopTime() const { return _stopTime; }

	f64 elapsedSeconds() const
	{
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(_stopTime - _startTime).count();
		auto elapsedSeconds = (f64)nanoseconds / 1'000'000'000.0;

		return elapsedSeconds;
	}
};

#endif
