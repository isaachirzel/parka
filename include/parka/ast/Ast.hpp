#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/ast/PackageAst.hpp"

namespace parka::ast
{
	class Ast
	{
		String _name;
		PackageAst& _globalPackage;
		// TODO: Project metadata
		// TODO: External package ids
		
	public:

		Ast(const String& name, PackageAst& globalPackage):
			_name(std::move(name)),
			_globalPackage(globalPackage)
		{}
		Ast(Ast&&) = default;
		Ast(const Ast&) = delete;

		const auto& name() const { return _name; }
		const auto& globalPackage() const { return _globalPackage; }
	};
}

#endif
