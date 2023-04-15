#ifndef PARKA_UTIL_FILE_POSITION_HPP
#define PARKA_UTIL_FILE_POSITION_HPP

#include "parka/file/File.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class File;

	class FilePosition
	{
		const File& _file;
		usize _index;
		usize _line;
		usize _col;

	public:

		FilePosition(const File& file, usize index);

		const auto& file() const { return _file; }
		const auto& index() const { return _index; }
		const auto& line() const { return _line; }
		const auto& col() const { return _col; }
		const auto* ptr() const { return &_file[_index]; }

		friend std::ostream& operator<<(std::ostream& out, const FilePosition& position);
	};
}

#endif
