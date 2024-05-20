#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/symbol/SymbolTable.hpp"

namespace parka
{
	class FunctionSymbolTable;

	struct LocalSymbolTable: public SymbolTable
	{
		LocalSymbolTable(SymbolTableType symbolTableType):
			SymbolTable(symbolTableType)
		{}
		virtual ~LocalSymbolTable() {}

		virtual FunctionSymbolTable& functionSymbolTable() = 0;
		virtual const ir::TypeIr& returnType() const = 0;
	};
}

#endif
