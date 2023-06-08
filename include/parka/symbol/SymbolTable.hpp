#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct SymbolTable
	{
		virtual ~SymbolTable() {}

		virtual const EntitySyntax *resolve(const Identifier& identifier) const = 0;
		virtual const EntitySyntax *resolve(const QualifiedIdentifier& identifier) const = 0;
		virtual const SymbolTable *getParent() const = 0;		
		virtual SymbolTableType symbolTableType() const = 0;

		const SymbolTable& getGlobalSymbolTable() const
		{
			const auto *table = this;
			const auto *parentTable = table->getParent();

			while (parentTable)
			{
				table = parentTable;
				parentTable = table->getParent();
			}

			assert(table->symbolTableType() == SymbolTableType::Package);

			return *table;
		}
	};
}

#endif
