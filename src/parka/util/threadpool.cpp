#include "parka/util/threadpool.hpp"

// TODO: Make OS agnostic
#include <unistd.h>

usize getProcessorCount(void)
{
	long processorCount = sysconf(_SC_NPROCESSORS_ONLN);

	return processorCount;
}
