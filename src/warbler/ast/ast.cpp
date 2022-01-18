#include <warbler/ast/ast.hpp>

namespace warbler
{
	Ast::Ast(Program&& program) :
	_program(program)
	{}

	Result<Ast> Ast::parse(const std::vector<Token>& tokens)
	{
		auto iter = tokens.begin();
		auto res = Program::parse(iter);

		if (res.has_error())
			return res.error();

		return Ast(res.unwrap());
	}

	void Ast::print_tree(u32 depth) const
	{
		_program.print_tree(depth);
	}
}