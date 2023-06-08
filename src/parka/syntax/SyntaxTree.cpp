#include "parka/log/Log.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const MemberSyntax *getRecursiveMember(const Array<MemberSyntax>&, StructSyntax& /*parent*/)
	{
		log::notImplemented(here());
		// for (const auto& member : members)
		// {
		// 	// TODO: Check if types are referencing the base type or an indirection to it
		// 	const auto& type = member.annotation().type();
		// 	auto& entity = SyntaxRepository::get(type.entity());

		// 	if (entity.type() != EntityType::StructSyntax)
		// 		continue;

		// 	auto& strct = (StructSyntax&)entity;

		// 	if (parentSymbol == strct.identifier())
		// 		return &member;

		// 	auto recursiveMember = getRecursiveMember(strct.members(), parentSymbol);

		// 	if (recursiveMember)
		// 		return recursiveMember;
		// }
		
		// return nullptr;
	}

	bool validateStructRecursion(const StructSyntax& strct)
	{
		log::notImplemented(here());
		// const MemberSyntax *recursiveMember = getRecursiveMember(strct.members(), strct);

		// if (recursiveMember)
		// {
		// 	log::error(recursiveMember->name(), "DeclarationStatementSyntax of member creates recursive type.");
		// 	return false;
		// }

		// return true;
	}

	SyntaxTree SyntaxTree::parse(const Project& project)
	{
		// TODO: Parse external projects
		const auto *package = PackageSyntax::parse(project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = SyntaxTree(*package);

		return result;
	}

	// bool SyntaxTree::validate()
	// {
	// 	auto success = true;
	// 	auto& globalPackage = SyntaxRepository::getPackage(_globalPackage);

	// 	// if (!globalPackage.declare())
	// 	// 	success = false;
		
	// 	if (!globalPackage.validate())
	// 		success = false;

	// 	// TODO: Validate struct recursion

	// 	return success;
	// }
}
