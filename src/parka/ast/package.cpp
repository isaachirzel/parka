#include "parka/ast/package.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/struct.hpp"
#include "parka/node/entity_id.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/array.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/file.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Package::parse(const Directory& directory, const String& name)
{
	// TODO: Add multithreading
	print("Package `$` has $ subpackages and $ modules", name, directory.subdirectories().length(), directory.files().length());
	auto success = true;
	auto modules = Array<Module>();
	auto packageIds = Array<EntityId>(directory.subdirectories().length());

	for (const auto& file : directory.files())
	{
		auto mod = Module::parse(file);

		if (!mod)
		{
			success = false;
			continue;
		}

		modules.push(*mod);
	}

	for (const auto& subdirectory : directory.subdirectories())
	{
		auto packageId = Package::parse(subdirectory, subdirectory.name());

		if (!packageId)
		{
			success = false;
			continue;
		}

		packageIds.push(*packageId);
	}

	if (!success)
		return {};

	auto package = Package(String(name), std::move(modules), std::move(packageIds));
	auto id = NodeBank::add(std::move(package));

	return id;
}

Optional<EntityId> Package::parse(const Project& project)
{
	return Package::parse(project.srcDirectory(), "");
}

void Package::declarePackage(const EntityId& packageId)
{
	auto& package = NodeBank::getPackage(packageId);

	_symbols.insert({ package.identifier(), packageId });

	package._parentPackageId = packageId;
}

bool Package::declareEntity(const EntityId& entityId)
{
	auto& entity = NodeBank::get(entityId);
	const auto& identifier = entity.identifier();

	print("Declaring $ `$`", entityId.type(), identifier);

	auto result = _symbols.insert({ identifier, entityId });

	if (!result.second)
	{
		// TODO: get previous entity
		// auto previousId = result.first->second;
		// auto& previous = NodeBank::get(previousId);
		//TODO: invalidate entity previous.invalidate();

		printError("`$` is already declared in this package.", identifier);
	}

	return result.second;
}

bool Package::declareEntities(const Array<EntityId>& entityIds)
{
	auto success = true;

	for (const auto& entityId : entityIds)
	{
		if (!declareEntity(entityId))
			success = false;
	}

	return success;
}

bool Package::declareModule(const Module& mod)
{
	print("Declaring module `$` with $ struct and $ functions", mod.filename(), mod.structIds().length(), mod.functionIds().length());
	auto success = true;

	if (!declareEntities(mod.structIds()))
		success = false;

	if (!declareEntities(mod.functionIds()))
		success = false;

	return success;
}

bool Package::declare()
{
	print("Declaring Package: `$`", _identifier);

	auto success = true;
	auto isGlobalPackage = _identifier.length() == 0;

	if (isGlobalPackage) 
		NodeBank::declarePrimitives(_symbols);

	for (const auto& mod : _modules)
	{
		if (!declareModule(mod))
			success = false;
	}

	for (const auto& packageId : _packageIds)
	{
		auto& package = NodeBank::getPackage(packageId);

		_symbols.insert({ package.identifier(), packageId });

		if (!package.declare())
			success = false;
	}

	return success;
}

bool Package::validate()
{
	auto success = true;
	auto id = NodeBank::getId(*this);

	for (auto& mod : _modules)
	{
		if (!mod.validate(id))
			success = false;
	}

	for (const auto& packageId : _packageIds)
	{
		auto& package = NodeBank::getPackage(packageId);

		if (!package.validate(id))
			success = false;
	}

	return success;
}

bool Package::validate(const EntityId& parentPackageId)
{
	// TODO: Multithreading
	auto success = true;
	auto id = NodeBank::getId(*this);

	_parentPackageId = parentPackageId;

	for (auto& mod : _modules)
	{
		if (!mod.validate(id))
			success = false;
	}

	for (const auto& packageId : _packageIds)
	{
		auto& package = NodeBank::getPackage(packageId);

		if (!package.validate(id))
			success = false;
	}

	return success;
}

Optional<EntityId> Package::find(const Identifier& identifier)
{
	auto iter = _symbols.find(identifier.text());

	if (iter == _symbols.end())
		return {};

	return iter->second;
}

Package& Package::getGlobalPackage()
{
	auto *table = this;

	while (table->_parentPackageId)
	{
		auto& package = NodeBank::getPackage(*table->_parentPackageId);

		table = &package;
	}

	return *table;
}

Optional<EntityId> Package::findGlobal(const Identifier& identifier)
{
	auto& globalSymbols = getGlobalPackage(); 
	auto global = globalSymbols.find(identifier);

	return global;
}

Optional<EntityId> Package::resolve(const QualifiedIdentifier& identifier, usize index)
{
	auto& part = identifier[index];
	auto result = find(part);

	if (!result)
	{
		if (_parentPackageId)
		{
			auto& parentPackage = NodeBank::getPackage(*_parentPackageId);

			result = parentPackage.find(part);
		}

		if (!result)
		{
			// TODO: Output package symbol, entity type and reference highlight
			printError("Unable to find `$` in package `$`.", part.text(), _identifier);
			return {};
		}
	}

	auto isLast = index == identifier.length() - 1;

	if (isLast)
		return result;

	auto& entity = NodeBank::get(*result);

	// TODO: Update for static features of other entities
	switch (entity.type())
	{
		case EntityType::Package:
		{
			auto& package = (Package&)entity;

			return package.resolve(identifier, index);
		}

		default:
			break;
	}
	
	printError("Unable able to get static member `$` of `$`.", entity.identifier());

	return {};
}

Optional<EntityId> Package::resolve(const QualifiedIdentifier& identifier)
{
	return resolve(identifier, 0);
	
}