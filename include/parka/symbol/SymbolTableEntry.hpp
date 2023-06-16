#ifndef PARKA_SYMBOL_SYMBOL_TABLE_ENTRY_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_ENTRY_HPP

#include "parka/ir/Entity.hpp"

namespace parka
{
	struct SymbolTableEntry
	{
		virtual EntityType entityType() const = 0;
		virtual const String& name() const = 0;
		virtual ir::EntityIr *context() = 0;

		friend std::ostream& operator<<(std::ostream& out, const SymbolTableEntry &entry);
	};
}

#endif
