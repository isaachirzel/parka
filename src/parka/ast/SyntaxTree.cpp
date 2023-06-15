#include "parka/log/Log.hpp"
#include "parka/ast/AssignmentExpression.hpp"
#include "parka/ast/Member.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Package.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/ast/SyntaxTree.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	SyntaxTree::SyntaxTree(PackageSyntax& globalPackage) :
	_globalPackage(globalPackage)
	{}

	ContextTree::ContextTree(PackageContext& globalPackage) :
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

	bool SyntaxTree::declare(EntitySyntax& entity)
	{
		return _globalPackage.declare(entity);
	}

	bool SyntaxTree::declareSelf()
	{
		return _globalPackage.declareSelf(nullptr);
	}

	EntityEntry *SyntaxTree::resolve(const Identifier& identifier)
	{
		return _globalPackage.resolve(identifier);
	}

	EntityEntry *SyntaxTree::resolve(const QualifiedIdentifier& identifier)
	{
		return _globalPackage.resolve(identifier);
	}

	Optional<ContextTree> SyntaxTree::validate()
	{
		auto *package = _globalPackage.validate();

		if (!package)
			return {};

		auto context = ContextTree(*package);

		return context;
	}

	std::ostream& operator<<(std::ostream& out, const SyntaxTree& syntax)
	{
		out << syntax._globalPackage;

		return out;
	}
}
