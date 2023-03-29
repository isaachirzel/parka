#include "parka/util/file_position.hpp"

std::ostream& operator<<(std::ostream& out, const FilePosition& position)
{
	out << position._line << ':' << position._col << ':';
}
