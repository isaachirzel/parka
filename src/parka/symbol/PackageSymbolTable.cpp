#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	// void PackageSymbolTable::declarePackage(const EntitySyntaxId& packageId)
	// {
	// 	auto& package = Storage::getPackage(packageId);

	// 	_symbols.insert({ package.identifier(), packageId });

	// 	package._parentPackageId = packageId;
	// }

	// bool PackageSymbolTable::declareEntity(const EntitySyntaxId& entityId)
	// {
	// 	auto& entity = Storage::get(entityId);
	// 	const auto& identifier = entity.identifier();

	// 	print("Declaring $ `$`", entityId.type(), identifier);

	// 	auto result = _symbols.insert({ identifier, entityId });

	// 	if (!result.second)
	// 	{
	// 		// TODO: get previous entity
	// 		// auto previousId = result.first->second;
	// 		// auto& previous = Storage::get(previousId);
	// 		//TODO: invalidate entity previous.invalidate();

	// 		printError("`$` is already declared in this package.", identifier);
	// 	}

	// 	return result.second;
	// }

	bool declareEntities(Table<String, EntitySyntaxId>& symbols, const Array<EntitySyntaxId>& entityIds)
	{
		// TODO: Invalidate symbol on failure, better error
		auto success = true;

		for (const auto& entityId : entityIds)
		{
			auto& entity = Storage::get(entityId);
			const auto& identifier = entity.identifier();
			auto result = symbols.insert({ identifier, entityId });

			if (!result.second)
			{
				printError("Name `$` is already declared in this package.", identifier);
				success = false;
			}
		}

		return success;
	}

	Optional<PackageSymbolTable> PackageSymbolTable::declare(const EntitySyntaxId& packageId, PackageSymbolTable *parent)
	{
		// TODO: pre-reserve symbol count
		auto success = true;
		auto& package = Storage::getPackage(packageId);
		auto symbols = Table<String, EntitySyntaxId>();

		if (parent == nullptr)
			Storage::declarePrimitives(symbols);

		for (const auto& mod : package.modules())
		{
			if (!declareEntities(symbols, mod.structIds()))
				success = false;

			if (!declareEntities(symbols, mod.functionIds()))
				success = false;
		}

		for (const auto& packageId : package.packageIds())
		{
			auto& package = Storage::getPackage(packageId);

			symbols.insert({ package.identifier(), packageId });

			// if (!package.declare())
			// 	success = false;
		}

		if (!success)
			return {};

		return PackageSymbolTable(packageId, std::move(symbols));
	}

	Optional<PackageSymbolTable> PackageSymbolTable::declare(const EntitySyntaxId& packageId)
	{
		return declare(packageId, nullptr);
	}

	Optional<EntitySyntaxId> PackageSymbolTable::find(const Identifier& identifier) const
	{
		auto iter = _symbols.find(identifier.text());

		if (iter == _symbols.end())
			return {};

		return iter->second;
	}

	const PackageSymbolTable& PackageSymbolTable::getGlobalPackageSymbolTable() const
	{
		auto *table = this;

		while (table->_parent)
			table = table->_parent;

		return *table;
	}

	Optional<EntitySyntaxId> PackageSymbolTable::findGlobal(const Identifier& identifier) const
	{
		auto& globalSymbols = getGlobalPackageSymbolTable(); 
		auto global = globalSymbols.find(identifier);

		return global;
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const QualifiedIdentifier& identifier, usize index) const
	{
		auto& part = identifier[index];
		auto result = find(part);

		if (!result)
		{
			if (_parent)
				result = _parent->find(part);

			if (!result)
			{
				auto& package = Storage::get(_packageId);
				// TODO: Output package symbol, entity type and reference highlight
				printError("Unable to find `$` in package `$`.", part.text(), package.identifier());
				return {};
			}
		}
		
		// FIXME: Reimplement

		// auto isLast = index == identifier.length() - 1;

		// if (isLast)
		// 	return result;

		// auto& entity = Storage::get(*result);

		// // TODO: Update for static features of other entities
		// switch (entity.type())
		// {
		// 	case EntityType::PackageSyntax:
		// 	{
		// 		auto& package = (PackageSyntax&)entity;

		// 		return package.resolve(identifier, index);
		// 	}

		// 	default:
		// 		break;
		// }
		
		// printError("Unable able to get static member `$` of `$`.", entity.identifier());

		return {};
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		return resolve(identifier, 0);
	}
}
