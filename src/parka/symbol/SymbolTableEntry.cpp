#include "parka/symbol/SymbolTableEntry.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const SymbolTableEntry& entry)
	{
		out << entry.name() << ": " << entry.symbolTableEntryType;

		return out;
	}
}
