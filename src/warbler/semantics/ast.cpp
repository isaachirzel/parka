#include <warbler/semantics/ast.hpp>

namespace warbler::semantics
{
	Ast::Ast(Module&& mod) :
	_module(std::move(mod))
	{}

	Result<Ast> Ast::validate(const syntax::Ast& syntax)
	{
		auto res = Module::validate(syntax.mod());

		if (!res)
			return {};

		return Ast { res.unwrap() };
	}
}
