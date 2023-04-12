#ifndef PARKA_UTIL_TIMER_HPP
#define PARKA_UTIL_TIMER_HPP

#include "parka/util/Common.hpp"

#include <chrono>

namespace parka
{
	class Timer
	{
		using Clock = std::chrono::high_resolution_clock;
		
		std::chrono::time_point<Clock> _startTime;
		std::chrono::time_point<Clock> _splitTime;

	public:

		Timer() :
		_startTime(Clock::now()),
		_splitTime(Clock::now())
		{}

		f64 split();
		f64 stop();
	};
}

#endif
