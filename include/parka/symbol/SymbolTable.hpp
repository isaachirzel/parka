#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/Resolution.hpp"

namespace parka
{
	// TODO: Implement getting symbols for entity
	struct SymbolTable
	{
		const SymbolTableType symbolTableType;

	public:

		SymbolTable(SymbolTableType symbolTableType):
		symbolTableType(symbolTableType)
		{}
		virtual ~SymbolTable() {}

		virtual bool declare(const Declarable& entity) = 0;
		virtual Resolvable *find(const ast::Identifier& identifier) = 0;
		virtual Resolution *resolve(const ast::QualifiedIdentifier& identifier) = 0;
	};
}

#endif
