#include "parka/util/source_location.hpp"

std::ostream& operator<<(std::ostream& out, const SourceLocation& location)
{
	out << location._file << ':' << location._line << ": ";

	return out;
}
