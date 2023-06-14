#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	// TODO: Implement getting symbols for entity
	struct SymbolTable
	{
		virtual ~SymbolTable() {}
		virtual bool declare(EntitySyntax& entity) = 0;
		virtual EntitySyntax *resolve(const Identifier& identifier) = 0;
		virtual EntitySyntax *resolve(const QualifiedIdentifier& identifier) = 0;
		virtual SymbolTable *parent() = 0;		
		virtual SymbolTableType symbolTableType() const = 0;

		SymbolTable& getGlobalSymbolTable()
		{
			auto *table = this;
			auto *parentTable = table->parent();

			while (parentTable)
			{
				table = parentTable;
				parentTable = table->parent();
			}

			assert(table->symbolTableType() == SymbolTableType::Package);

			return *table;
		}
	};
}

#endif
