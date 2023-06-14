#ifndef PARKA_SYMBOL_TABLE_TYPE_HPP
#define PARKA_SYMBOL_TABLE_TYPE_HPP

#include <ostream>

namespace parka
{
	enum class SymbolTableType
	{
		Global,
		Package,
		Function,
		Struct,
		Block
	};

	std::ostream& operator<<(std::ostream& out, const SymbolTableType& type);
}

#endif
