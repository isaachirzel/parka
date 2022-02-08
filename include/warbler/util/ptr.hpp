#ifndef WARBLER_UTIL_PTR_HPP
#define WARBLER_UTIL_PTR_HPP

#include <memory>

namespace warbler
{
	template<typename T>
	using Ptr = std::unique_ptr<T>;
}

#endif
