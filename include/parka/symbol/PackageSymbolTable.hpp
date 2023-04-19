#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageEntry;

	class PackageSymbolTable : public SymbolTable
	{
		EntitySyntaxId _packageId;
		Table<String, PackageEntry> _symbols;
		const PackageSymbolTable *_parent;

	private:

		PackageSymbolTable(const EntitySyntaxId& entityId, const PackageSymbolTable *parent) :
		_packageId(entityId),
		_parent(parent)
		{}

		bool declare(const EntitySyntaxId& entity);
		const PackageSymbolTable& getGlobalPackageSymbolTable() const;
		const PackageEntry *findPackageEntry(const QualifiedIdentifier& identifier, usize index) const;

	public:

		
		PackageSymbolTable(const EntitySyntaxId& entityId, const PackageSymbolTable& parent) :
		_packageId(entityId),
		_parent(&parent)
		{}
		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolveGlobal(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
	};

	union SymbolTables
	{
		PackageSymbolTable package;
		FunctionSymbolTable function;

		SymbolTables() = delete;
	};

	class PackageEntry
	{
		EntitySyntaxId _entityId;
		alignas (SymbolTables) byte _symbols[sizeof(SymbolTables)];

	public:

		PackageEntry(const EntitySyntaxId& entityId, const PackageSymbolTable& packageId);
		PackageEntry(PackageEntry&&) = default;
		PackageEntry(const PackageEntry&) = default;
		~PackageEntry();

		friend class PackageSymbolTable;
	};
}

#endif
