#ifndef PARKA_SYMBOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/enum/SymbolTableEntryType.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	struct SymbolTableEntry
	{
		const SymbolTableEntryType symbolTableEntryType;

	public:

		SymbolTableEntry(SymbolTableEntryType symbolTableEntryType) :
		symbolTableEntryType(symbolTableEntryType)
		{}
		virtual ~SymbolTableEntry() {}

		virtual const String& name() const = 0; // TODO: Convert this to symbol
		// virtual ir::EntityIr *context() = 0;

		friend std::ostream& operator<<(std::ostream& out, const SymbolTableEntry &entry);
	};
}

#endif
