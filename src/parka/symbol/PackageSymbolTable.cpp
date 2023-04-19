#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"

#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	PackageEntry::PackageEntry(const EntitySyntaxId& entityId, const PackageSymbolTable& parent) :
	_entityId(entityId)
	{
		auto *symbolTable = (SymbolTables*)_symbols;

		switch (_entityId.type())
		{
			case EntityType::Package:
				new (&symbolTable->package) PackageSymbolTable(entityId, parent);
				break;

			case EntityType::Function:
				new (&symbolTable->function) FunctionSymbolTable(entityId, parent);
				break;

			default:
				break;
		}
	}

	PackageEntry::~PackageEntry()
	{
		auto *symbolTable = (SymbolTables*)_symbols;

		switch (_entityId.type())
		{
			case EntityType::Package:
				symbolTable->package.~PackageSymbolTable();
				break;

			// case EntityType::Struct:
				// break;
			case EntityType::Function:
				symbolTable->function.~FunctionSymbolTable();
				break;

			default:
				break;
		}
	}

	// bool declareEntities(Table<String, EntitySyntaxId>& symbols, const Array<EntitySyntaxId>& entityIds)
	// {
	// 	// TODO: Invalidate symbol on failure, better error
	// 	auto success = true;

	// 	for (const auto& entityId : entityIds)
	// 	{
	// 		auto& entity = SyntaxRepository::get(entityId);
	// 		const auto& identifier = entity.identifier();
	// 		auto result = symbols.insert(identifier, entityId);

	// 		if (!result)
	// 		{
	// 			printError("Name `$` is already declared in this package.", identifier);
	// 			success = false;
	// 		}
	// 	}

	// 	return success;
	// }

	bool PackageSymbolTable::declare(const EntitySyntaxId& entityId)
	{
		auto& entity = *entityId;
		auto entry = PackageEntry(entityId, _packageId);
		auto result = _symbols.insert(entity.identifier(), std::move(entry));

		return result;
	}

	const PackageEntry *PackageSymbolTable::findPackageEntry(const QualifiedIdentifier& identifier, usize index) const
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

	PackageSymbolTable PackageSymbolTable::from(const EntitySyntaxId& packageId, const PackageSymbolTable *parent)
	{
		// TODO: pre-reserve symbol count
		auto success = true;
		auto& package = packageId.getPackage();
		auto symbols = Table<String, PackageEntry>();

		if (parent == nullptr)
		{
			usize index = 0;

			for (const auto& primitive: Primitive::primitives)
			{
				symbols.insert(primitive.identifier(), EntitySyntaxId::getFor(primitive));
				
				index += 1;
			}
		}

		for (const auto& mod : package.modules())
		{
			if (!declareEntities(symbols, mod.structIds()))
				success = false;

			if (!declareEntities(symbols, mod.functionIds()))
				success = false;
		}

		for (const auto& packageId : package.packageIds())
		{
			auto& package = packageId.getPackage();

			symbols.insert(package.identifier(), packageId);

			
		}

		if (!success)
			return {};

		return PackageSymbolTable(packageId, std::move(symbols), parent);
	}

	Optional<PackageSymbolTable> PackageSymbolTable::from(const EntitySyntaxId& packageId)
	{
		return from(packageId, nullptr);
	}

	Optional<PackageSymbolTable> PackageSymbolTable::from(const EntitySyntaxId& packageId, const PackageSymbolTable& parent)
	{
		return from(packageId, &parent);
	}

	bool PackageSymbolTable::declare(const Identifier&)
	{
		exitNotImplemented(here());
	}

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const Identifier& identifier) const
	{
		return _symbols.find(identifier.text());
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

	Optional<EntitySyntaxId> PackageSymbolTable::resolve(const QualifiedIdentifier& identifier) const
	{
		const auto *entry = findPackageEntry(identifier, 0);

		if (!entry)
			return {};

		return entry->entityId;
	}
}
