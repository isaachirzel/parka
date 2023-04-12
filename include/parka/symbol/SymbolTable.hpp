#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct SymbolTable
	{
		virtual ~SymbolTable() {}

		virtual bool declare(const Identifier& identifier) = 0;
		virtual Optional<EntitySyntaxId> resolve(const Identifier& identifier) const = 0;
		virtual Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const = 0;
	};
}

#endif
