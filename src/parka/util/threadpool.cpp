#include "parka/util/threadpool.hpp"

#include <thread>

usize Threadpool::getThreadCount()
{
	return std::thread::hardware_concurrency();
}
