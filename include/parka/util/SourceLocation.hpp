#ifndef PARKA_UTIL_SOURCE_LOCATION_HPP
#define PARKA_UTIL_SOURCE_LOCATION_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class SourceLocation
	{
		const char *_file;
		usize _line;
		const char *_function;

	public:

		SourceLocation(const char *file, usize line, const char *function) :
		_file(file),
		_line(line),
		_function(function)
		{}

		const auto* file() const { return _file; }
		const auto& line() const { return _line; }
		const auto* function() const { return _function; }

		friend std::ostream& operator<<(std::ostream& out, const SourceLocation& location);
	};
}

#define here() (SourceLocation(__FILE__, __LINE__, __func__))

#endif
