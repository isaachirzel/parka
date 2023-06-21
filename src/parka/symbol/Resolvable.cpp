#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const Resolvable& entry)
	{
		out << entry.name() << ": " << entry.resolvableType;

		return out;
	}
}
