#include "parka/validation/Resolvable.hpp"

namespace parka::validation
{
	std::ostream& operator<<(std::ostream& out, const Resolvable& entry)
	{
		out << entry.name() << ": " << entry.resolvableType;

		return out;
	}
}
