#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSymbolTable
	{
		EntitySyntaxId _packageId;
		Table<String, EntitySyntaxId> _symbols;
		Array<PackageSymbolTable> _packages;
		const PackageSymbolTable *_parent;

		PackageSymbolTable(const EntitySyntaxId& entityId, Table<String, EntitySyntaxId>&& symbols) :
		_packageId(entityId),
		_symbols(std::move(symbols)),
		_parent(nullptr)
		{}

		PackageSymbolTable(const EntitySyntaxId& entityId, Table<String, EntitySyntaxId>&& symbols, const PackageSymbolTable& parent) :
		_packageId(entityId),
		_symbols(std::move(symbols)),
		_parent(&parent)
		{}

		void declarePackage(const EntitySyntaxId& packageId);
		static Optional<PackageSymbolTable> declare(const EntitySyntaxId& packageId, PackageSymbolTable *parent);

		const PackageSymbolTable& getGlobalPackageSymbolTable() const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier, usize index) const;

	public:

		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;
		~PackageSymbolTable() = default;

		static Optional<PackageSymbolTable> declare(const EntitySyntaxId& packageId);

		Optional<EntitySyntaxId> find(const Identifier& identifier) const;
		Optional<EntitySyntaxId> findGlobal(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
	};
}

#endif
