#include <warbler/syntax/ast.hpp>

#include <warbler/syntax/function.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Ast::Ast(Module&& module) :
	_module(std::move(module))
	{}

	Result<Ast> Ast::parse(const source::File& file)
	{
		auto token = lexicon::Token::get_initial(file);
		auto res = Module::parse(token);

		if (!res)
			return {};

		if (token.type() != lexicon::TokenType::EndOfFile)
		{
			print_error(token, "stray token in source file");
			return {};
		}

		return Ast(res.unwrap());
	}

	void Ast::print_tree(u32 depth) const
	{
		_module.print_tree(depth);
	}

	// bool Ast::validate()
	// {
	// 	#pragma message "actually implement passing scope to module"
	// 	return _module.validate({ "TEST_MODULE" });
	// }
}
