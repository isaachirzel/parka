#include "parka/file/FilePosition.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const FilePosition& position)
	{
		out << position._line << ':' << position._col << ':';

		return out;
	}
}
