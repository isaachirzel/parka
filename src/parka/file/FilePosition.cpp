#include "parka/file/FilePosition.hpp"
#include "parka/file/File.hpp"
#include "parka/log/Color.hpp"

namespace parka
{
 	FilePosition::FilePosition(const File& file, usize index):
	_file(file),
	_index(index),
	_line(1),
	_col(1)
	{
		assert(index <= file.text().length());
		
		usize filePos = 0;

		for (auto length : file.lineLengths())
		{
			if (filePos + length > index)
				break;

			filePos += length + 1;
			_line += 1;
		}

		_col = index - filePos + 1;
	}

	std::ostream& operator<<(std::ostream& out, const FilePosition& position)
	{		
		out << Color::Yellow << position.file().path() << ':' << position.line() << ':' << position.col() << Color::Reset;

		return out;
	}
}
