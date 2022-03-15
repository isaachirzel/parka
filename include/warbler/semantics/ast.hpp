#ifndef WARBLER_SEMANTICS_AST_HPP
#define WARBLER_SEMANTICS_AST_HPP

#include <warbler/syntax/ast.hpp>
#include <warbler/semantics/module.hpp>

namespace warbler::semantics
{
	class Ast
	{
		Module _module;

		Ast(Module&& mod);

	public:

		static Result<Ast> validate(const syntax::Ast& syntax);
	};
}

#endif
