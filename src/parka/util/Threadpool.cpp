#include "parka/util/Threadpool.hpp"

#include <thread>

namespace parka
{
	usize Threadpool::getThreadCount()
	{
		return std::thread::hardware_concurrency();
	}
}
