#ifndef WARBLER_SEMANTICS_AST_HPP
#define WARBLER_SEMANTICS_AST_HPP

#include <warbler/syntax/ast.hpp>
#include <warbler/semantics/module.hpp>

namespace warbler::semantics
{
	class Svt
	{
	private:

		Module _module;

	public:

		static Result<Svt> validate(const syntax::Ast& ast);
	};
}

#endif
