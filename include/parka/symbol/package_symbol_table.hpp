#ifndef PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSymbolTable
	{
		EntityId _packageId;
		Table<String, EntityId> _symbols;
		Array<PackageSymbolTable> _packages;
		PackageSymbolTable *_parent;

		PackageSymbolTable(const EntityId& entityId, Table<String, EntityId>&& symbols) :
		_packageId(entityId),
		_symbols(std::move(symbols)),
		_parent(nullptr)
		{}

		PackageSymbolTable(const EntityId& entityId, Table<String, EntityId>&& symbols, PackageSymbolTable& parent) :
		_packageId(entityId),
		_symbols(std::move(symbols)),
		_parent(&parent)
		{}

		static Optional<PackageSymbolTable> declare(const EntityId& packageId, PackageSymbolTable *parent);

		PackageSymbolTable& getGlobalPackageSymbolTable();
		Optional<EntityId> resolve(const QualifiedIdentifier& identifier, usize index);

	public:

		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;
		~PackageSymbolTable() = default;

		static Optional<PackageSymbolTable> declare(const EntityId& packageId);

		Optional<EntityId> find(const Identifier& identifier) const;
		Optional<EntityId> findGlobal(const Identifier& identifier) const;
		Optional<EntityId> resolve(const QualifiedIdentifier& identifier) const;
	};
}

#endif
