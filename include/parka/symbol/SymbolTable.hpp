#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	// TODO: Implement getting symbols for entity
	struct SymbolTable
	{	
		virtual ~SymbolTable() {}
		virtual SymbolTableType symbolTableType() const = 0;
		virtual bool declare(EntitySyntax& entity) = 0;
		virtual EntityEntry *resolve(const Identifier& identifier) = 0;
		virtual EntityEntry *resolve(const QualifiedIdentifier& identifier) = 0;
	};
}

#endif
