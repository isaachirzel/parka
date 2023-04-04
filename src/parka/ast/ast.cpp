#include "parka/ast/ast.hpp"
#include "parka/ast/struct/member.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/struct/struct.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/array.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

const Member *getRecursiveMember(const Array<Member>&, EntityId /*parentId*/)
{
	exitNotImplemented(here());
	// for (const auto& member : members)
	// {
	// 	// TODO: Check if types are referencing the base type or an indirection to it
	// 	const auto& type = member.annotation().type();
	// 	auto& entity = NodeBank::get(type.entityId());

	// 	if (entity.type() != EntityType::Struct)
	// 		continue;

	// 	auto& strct = (Struct&)entity;

	// 	if (parentSymbol == strct.identifier())
	// 		return &member;

	// 	auto recursiveMember = getRecursiveMember(strct.members(), parentSymbol);

	// 	if (recursiveMember)
	// 		return recursiveMember;
	// }
	
	// return nullptr;
}

bool validateStructRecursion(EntityId structId)
{
	auto& strct = NodeBank::getStruct(structId);

	const Member *recursiveMember = getRecursiveMember(strct.members(), structId);

	if (recursiveMember)
	{
		printError(recursiveMember->name(), "Declaration of member creates recursive type.");
		return false;
	}

	return true;
}

Optional<Ast> Ast::parse(const Project& project)
{
	auto globalPackageId = Package::parse(project);
	
	if (!globalPackageId)
		return {};

	auto ast = Ast(globalPackageId.unwrap());

	return ast;
}

bool Ast::validate()
{
	auto success = true;
	auto& globalPackage = NodeBank::getPackage(_globalPackageId);

	if (!globalPackage.declare())
		success = false;
	
	if (!globalPackage.validate())
		success = false;

	// TODO: Validate struct recursion

	return success;
}
