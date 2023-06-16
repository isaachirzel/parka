#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Entity.hpp"

namespace parka
{
	// TODO: Implement getting symbols for entity
	struct SymbolTable
	{	
		virtual ~SymbolTable() {}
		virtual SymbolTableType symbolTableType() const = 0;
		virtual bool declare(ast::EntityAst& entity) = 0;
		virtual SymbolTableEntry *find(const ast::Identifier& identifier) = 0;
		virtual ir::EntityIr *resolve(const ast::QualifiedIdentifier& identifier) = 0;
	};
}

#endif
