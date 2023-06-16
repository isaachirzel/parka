#ifndef PARKA_SYMBOL_TABLE_ENTRY_TYPE_HPP
#define PARKA_SYMBOL_TABLE_ENTRY_TYPE_HPP

#include <ostream>
namespace parka
{
	enum class SymbolTableEntryType
	{
		Package,
		Struct,
		Primitive,
		Function,
		Variable,
		Parameter,
		Member
	};

	std::ostream& operator<<(std::ostream& out, const SymbolTableEntryType& type);
}

#endif
