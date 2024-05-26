#include "parka/util/ThreadPool.hpp"

#include <thread>

namespace parka
{
	usize ThreadPool::getThreadCount()
	{
		return std::thread::hardware_concurrency();
	}
}
