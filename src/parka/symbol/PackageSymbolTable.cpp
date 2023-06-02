#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	bool PackageSymbolTable::declare(const EntitySyntaxId& entityId)
	{
		// TODO: Invalidate symbol on failure, better error
		auto entry = SymbolTableEntry(entityId, *this);
		const auto& identifier = entityId->identifier();
		auto result = _symbols.insert(identifier, std::move(entry));

		if (!result)
			printError("Name `$` is already declared in this package.", identifier);

		return result;
	}

	const SymbolTableEntry *PackageSymbolTable::findEntry(const QualifiedIdentifier& identifier, usize index) const
	{
		auto& part = identifier[index];
		auto result = resolve(part);

		if (!result)
		{
			if (_parent)
				result = _parent->resolve(part);

			if (!result)
			{
				auto& package = *_packageId;
				// TODO: Output package symbol, entity type and reference highlight
				printError("Unable to find `$` in package `$`.", part.text(), package.identifier());
				return {};
			}
		}

		return nullptr;
	}

	PackageSymbolTable::PackageSymbolTable(const EntitySyntaxId& packageId, const PackageSymbolTable *parent) :
	_packageId(packageId),
	// TODO: pre-reserve symbol count _symbols(###),
	_parent(parent)
	{
		auto& package = packageId.getPackage();

		if (parent == nullptr)
		{
			for (usize i = 0; i < Primitive::primitiveCount; ++i)
			{
				const auto& primitive = Primitive::primitives[i];
				auto id = EntitySyntaxId::getFor(primitive);

				_symbols.insert(primitive.identifier(), SymbolTableEntry(id, *this));
			}
		}

		for (const auto& mod : package.modules())
		{
			for (const auto& structId : mod.structIds())
				declare(structId);

			for (const auto& functionId : mod.functionIds())
				declare(functionId);
		}

		for (const auto& packageId : package.packageIds())
			declare(packageId);
	}

	const PackageSymbolTable& PackageSymbolTable::getGlobalPackageSymbolTable() const
	{
		const auto *table = this;

		while (table->_parent)
			table = table->_parent;

		return *table;
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolveGlobal(const Identifier& identifier) const
	{
		auto& globalSymbols = getGlobalPackageSymbolTable(); 
		auto global = globalSymbols.resolve(identifier);

		return global;
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const Identifier& identifier) const
	{
		// TODO: Confirm this makes sense. I'm not sure if resolving single identifiers should always do
		// this or if it should seek upwards at times
		const auto *result = _symbols.find(identifier.text());

		if (!result)
			return {};
			
		return result->entityId();
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		const auto *entry = findEntry(identifier, 0);

		if (!entry)
			return {};

		return entry->entityId();
	}
}
