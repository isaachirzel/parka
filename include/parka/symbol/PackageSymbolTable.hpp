#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSymbolTable : public SymbolTable
	{
		EntitySyntaxId _packageId;
		Table<String, EntitySyntaxId> _symbols;
		Array<PackageSymbolTable> _packages;
		const PackageSymbolTable *_parent;

		PackageSymbolTable(const EntitySyntaxId& entityId, Table<String, EntitySyntaxId>&& symbols, const PackageSymbolTable *parent) :
		_packageId(entityId),
		_symbols(std::move(symbols)),
		_parent(parent)
		{}

		void declarePackage(const EntitySyntaxId& packageId);
		static Optional<PackageSymbolTable> declare(const EntitySyntaxId& packageId, PackageSymbolTable *parent);

		const PackageSymbolTable& getGlobalPackageSymbolTable() const;
		Optional<EntitySyntaxId> resolveOffset(const QualifiedIdentifier& identifier, usize index) const;
		static Optional<PackageSymbolTable> from(const EntitySyntaxId& packageId, const PackageSymbolTable *parent);

	public:

		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;
		~PackageSymbolTable() = default;

		static Optional<PackageSymbolTable> from(const EntitySyntaxId& packageId);
		static Optional<PackageSymbolTable> from(const EntitySyntaxId& packageId, const PackageSymbolTable& parent);

		bool declare(const Identifier& identifier);
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		Optional<EntitySyntaxId> resolveGlobal(const Identifier& identifier) const;
	};
}

#endif
