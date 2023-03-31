#include "parka/ast/ast.hpp"
#include "parka/ast/struct/member.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/struct/struct.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/global_symbol_table.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/array.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

String getSymbolFromPath(const String& pathText)
{
	auto path = path::toAbsolute(pathText);
	print("Path: $", path);
	exitNotImplemented(here());
}

const Member *getRecursiveMember(const Array<Member>& members, const String& parentSymbol)
{
	for (const auto& member : members)
	{
		// TODO: Check if types are referencing the base type or an indirection to it
		const auto& type = member.annotation().type();
		auto& entity = NodeBank::get(type.entityId());

		if (entity.type() != EntityType::Struct)
			continue;

		auto& strct = (Struct&)entity;

		if (parentSymbol == strct.symbol())
			return &member;

		auto recursiveMember = getRecursiveMember(strct.members(), parentSymbol);

		if (recursiveMember)
			return recursiveMember;
	}
	
	return nullptr;
}

bool validateStructRecursion(EntityId structId)
{
	auto& strct = NodeBank::getStruct(structId);

	const Member *recursiveMember = getRecursiveMember(strct.members(), strct.symbol());

	if (recursiveMember)
	{
		printError(recursiveMember->name(), "Declaration of member creates recursive type.");
		return false;
	}

	return true;
}

Optional<Array<EntityId>> parseDirectory(const Directory& directory, String&& symbol)
{
	auto success = true;
	auto packageIds = Array<EntityId>();

	for (const auto& subdirectory : directory.subdirectories())
	{
		auto subdirectorySymbol = symbol + "::" + subdirectory.name();
		auto subPackageIds = parseDirectory(subdirectory, std::move(subdirectorySymbol));

		if (!subPackageIds)
		{
			success = false;
			continue;
		}

		auto value = subPackageIds.unwrap();

		packageIds.concat(value);
	}

	auto package = Package::parse(directory.files(), std::move(symbol));

	if (!package || !success)
		return {};

	auto id = NodeBank::add(package.unwrap());

	packageIds.push(std::move(id));

	return packageIds;
}

Optional<Ast> Ast::parse(const Project& project)
{
	auto packageIds = parseDirectory(project.srcDirectory(), String(project.name()));
	
	if (!packageIds)
		return {};

	auto ast = Ast(packageIds.unwrap());

	return ast;
}

bool Ast::validate()
{
	auto success = true;
	auto globalSymbols = GlobalSymbolTable();

	// Declare packages
	for (auto packageId : _packageIds)
	{
		globalSymbols.declare(packageId);

		auto& package = NodeBank::getPackage(packageId);

		if (!package.declare(globalSymbols))
			success = false;
	}

	// Validate packages
	for (const auto& packageId : _packageIds)
	{
		auto& package = NodeBank::getPackage(packageId);

		if (!package.validate(globalSymbols))
			success = false;
	}

	// TODO: Validate struct recursion

	return success;
}