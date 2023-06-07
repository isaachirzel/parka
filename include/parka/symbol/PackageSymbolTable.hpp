#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

// TODO: Move constructor

namespace parka
{
	class SymbolTableEntry;

	class PackageSymbolTable : public SymbolTable
	{
		EntitySyntaxId _packageId;
		Table<String, SymbolTableEntry> _symbols;
		const SymbolTable *_parent;

	private:
		
		bool declare(const EntitySyntaxId& entityId);
		const SymbolTableEntry *findEntry(const QualifiedIdentifier& identifier, usize index) const;

	public:

		PackageSymbolTable(const EntitySyntaxId& packageId, const SymbolTable *parent);
		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;

		const auto& packageId() const { return _packageId; }
		const auto& symbols() const { return _symbols; }
		auto& symbols() { return _symbols; }
		const SymbolTable *getParent() const { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& symbols);

		friend class SymbolTableEntry;
	};
}

#endif
