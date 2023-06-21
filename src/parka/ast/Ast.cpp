#include "parka/log/Log.hpp"
#include "parka/ast/AssignmentExpression.hpp"
#include "parka/ast/Member.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Package.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/ast/Ast.hpp"
#include "parka/symbol/Resolution.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	Ast Ast::parse(const Project& project)
	{
		// TODO: Parse external projects
		auto *package = PackageAst::parse(project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = Ast(*package);

		return result;
	}

	bool Ast::declare(Declarable& declarable)
	{
		return _globalPackage.declare(declarable);
	}

	bool Ast::declareSelf()
	{
		return _globalPackage.declareSelf(nullptr);
	}

	Resolvable *Ast::find(const Identifier& identifier)
	{
		return _globalPackage.find(identifier);
	}

	Resolution *Ast::resolve(const QualifiedIdentifier& identifier)
	{
		return _globalPackage.resolve(identifier);
	}

	// Optional<ir::Ir> Ast::validate()
	// {
	// 	auto *package = _globalPackage.validate();

	// 	if (!package)
	// 		return {};

	// 	auto context = ir::Ir(*package);

	// 	return context;
	// }

	std::ostream& operator<<(std::ostream& out, const Ast& syntax)
	{
		out << syntax._globalPackage;

		return out;
	}
}
