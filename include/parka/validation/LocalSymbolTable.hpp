#ifndef PARKA_VALIDATION_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_VALIDATION_LOCAL_SYMBOL_TABLE_HPP

#include "parka/validation/SymbolTable.hpp"

namespace parka::validation
{
	class FunctionSymbolTable;

	struct LocalSymbolTable: public SymbolTable
	{
		LocalSymbolTable(SymbolTableType symbolTableType):
			SymbolTable(symbolTableType)
		{}
		virtual ~LocalSymbolTable() {}

		virtual bool isInLoop() const = 0;
		virtual FunctionSymbolTable& functionSymbolTable() = 0;
		virtual const ir::TypeIr& returnType() const = 0;
	};
}

#endif
