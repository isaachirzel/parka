#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/ast/PackageAst.hpp"

namespace parka::ast
{
	class Ast
	{
		PackageAst& _globalPackage;
		// TODO: Project metadata
		// TODO: External package ids
		
	public:

		Ast(PackageAst& globalPackage):
			_globalPackage(globalPackage)
		{}
		Ast(Ast&&) = default;
		Ast(const Ast&) = delete;

		const auto& globalPackage() const { return _globalPackage; }
	};
}

#endif
