#include "parka/util/SourceLocation.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const SourceLocation& location)
	{
		out << location._file << ':' << location._line << ':' << location._function << "()";

		return out;
	}
}
