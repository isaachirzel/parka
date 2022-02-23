#ifndef WARBLER_UTIL_FILE_HPP
#define WARBLER_UTIL_FILE_HPP

#include <warbler/util/string.hpp>
#include <warbler/util/result.hpp>

namespace warbler
{
	Result<String> read_file(const String& filepath);
}

#endif
