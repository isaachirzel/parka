#include "parka/validation/ContextEntry.hpp"

namespace parka::validation
{
	std::ostream& operator<<(std::ostream& out, const ContextEntry& entry)
	{
		out << entry.name() << ": " << entry.resolvableType;

		return out;
	}
}
