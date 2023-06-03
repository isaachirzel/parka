#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct SymbolTable
	{
		virtual ~SymbolTable() {}

		virtual Optional<EntitySyntaxId> resolve(const Identifier& identifier) const = 0;
		virtual Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const = 0;
		virtual const SymbolTable *parent() const = 0;
		virtual SymbolTableType symbolTableType() const = 0;

		const SymbolTable& getGlobalSymbolTable() const
		{
			const auto *table = this;
			const auto *parentTable = table->parent();

			while (parentTable)
			{
				table = parentTable;
				parentTable = table->parent();
			}

			assert(table->symbolTableType() == SymbolTableType::Global);

			return *table;
		}
	};
}

#endif
