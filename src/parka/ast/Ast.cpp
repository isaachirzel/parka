#include "parka/ast/Ast.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
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
