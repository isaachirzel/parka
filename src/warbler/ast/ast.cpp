#include <warbler/ast/ast.hpp>

#include <warbler/ast/function.hpp>

namespace warbler::ast
{
	Ast::Ast(Module&& module) :
	_module(std::move(module))
	{}

	Result<Ast> Ast::parse(const std::vector<Token>& tokens)
	{
		auto iter = tokens.begin();
		auto res = Module::parse(iter);

		if (!res)
			return {};

		return Ast(res.unwrap());
	}

	void Ast::print_tree(u32 depth) const
	{
		_module.print_tree(depth);
	}

	bool Ast::validate()
	{
		#pragma message("actually implement passing scope to module")
		return _module.validate({ "TEST_MODULE" });
	}
}
