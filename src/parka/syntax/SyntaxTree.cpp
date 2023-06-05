#include "parka/log/Log.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"

#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const MemberSyntax *getRecursiveMember(const Array<MemberSyntax>&, EntitySyntaxId /*parentId*/)
	{
		log::notImplemented(here());
		// for (const auto& member : members)
		// {
		// 	// TODO: Check if types are referencing the base type or an indirection to it
		// 	const auto& type = member.annotation().type();
		// 	auto& entity = SyntaxRepository::get(type.entityId());

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

	bool validateStructRecursion(EntitySyntaxId structId)
	{
		auto& strct = structId.getStruct();

		const MemberSyntax *recursiveMember = getRecursiveMember(strct.members(), structId);

		if (recursiveMember)
		{
			log::error(recursiveMember->name(), "DeclarationStatementSyntax of member creates recursive type.");
			return false;
		}

		return true;
	}

	SyntaxTree SyntaxTree::parse(const Project& project)
	{
		const auto& directory = project.srcDirectory();
		auto modules = Array<ModuleSyntax>(directory.files().length());
		auto packageIds = Array<EntitySyntaxId>(directory.subdirectories().length());

		for (const auto& file : directory.files())
			modules.push(ModuleSyntax::parse(file));

		for (const auto& subdirectory : directory.subdirectories())
			packageIds.push(PackageSyntax::parse(subdirectory, subdirectory.name()));
		
		// TODO: Parse external projects

		auto result = SyntaxTree(std::move(modules), std::move(packageIds));

		return result;
	}

	// bool SyntaxTree::validate()
	// {
	// 	auto success = true;
	// 	auto& globalPackage = SyntaxRepository::getPackage(_globalPackageId);

	// 	// if (!globalPackage.declare())
	// 	// 	success = false;
		
	// 	if (!globalPackage.validate())
	// 		success = false;

	// 	// TODO: Validate struct recursion

	// 	return success;
	// }
}
