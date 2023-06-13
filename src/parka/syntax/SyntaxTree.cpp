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
	SyntaxTree::SyntaxTree(PackageSyntax& globalPackage) :
	_globalPackage(globalPackage)
	{}
	
	SyntaxTree SyntaxTree::parse(const Project& project)
	{
		// TODO: Parse external projects
		auto *package = PackageSyntax::parse(project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = SyntaxTree(*package);

		return result;
	}

	void SyntaxTree::declare()
	{
		return _globalPackage.declare(nullptr);
	}

	Optional<ContextTree> SyntaxTree::validate()
	{
		auto *package = _globalPackage.validate();

		if (!package)
			return {};

		auto context = ContextTree(*package);

		return context;
	}
}
