#ifndef PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/syntax/SyntaxTree.hpp"

namespace parka
{
	class GlobalSymbolTable : public SymbolTable
	{
		Table<String, SymbolTableEntry> _symbols;
		// TODO: External symbols that have been imported

		void declare(const EntitySyntaxId& entityId);

	public:

		GlobalSymbolTable(const SyntaxTree& syntaxTree);
		GlobalSymbolTable(GlobalSymbolTable&&) = delete;
		GlobalSymbolTable(const GlobalSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;

		const SymbolTable *getParent() const { return nullptr; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Global; }

		friend std::ostream& operator<<(std::ostream& out, const GlobalSymbolTable& globalSymbols);
	};
}

#endif
