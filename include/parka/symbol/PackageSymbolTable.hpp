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
		const PackageSymbolTable *_parent;

	private:
		
		PackageSymbolTable(const EntitySyntaxId& packageId, const PackageSymbolTable *parent);

		bool declare(const EntitySyntaxId& entity);
		const PackageSymbolTable& getGlobalPackageSymbolTable() const;
		const SymbolTableEntry *findEntry(const QualifiedIdentifier& identifier, usize index) const;

	public:

		PackageSymbolTable(const EntitySyntaxId& packageId) :
		PackageSymbolTable(packageId, nullptr)
		{}
		
		PackageSymbolTable(const EntitySyntaxId& packageId, const PackageSymbolTable& parent) :
		PackageSymbolTable(packageId, &parent)
		{}

		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolveGlobal(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }
	};
}

#endif
