#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	struct SymbolTable
	{
		virtual ~SymbolTable() {}
		virtual const EntityContext *resolve(const Identifier& identifier) = 0;
		virtual const EntityContext *resolve(const QualifiedIdentifier& identifier) = 0;
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
