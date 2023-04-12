#ifndef PARKA_UTIL_FILE_POSITION_HPP
#define PARKA_UTIL_FILE_POSITION_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class FilePosition
	{
		usize _line;
		usize _col;

	public:

		FilePosition(usize line, usize col) :
		_line(line),
		_col(col)
		{}

		const auto& line() const { return _line; }
		const auto& col() const { return _col; }

		friend std::ostream& operator<<(std::ostream& out, const FilePosition& position);
	};
}

#endif
