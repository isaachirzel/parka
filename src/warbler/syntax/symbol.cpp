#include <warbler/syntax/expression/symbol.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Symbol::Symbol(const lexicon::Token& token) :
	_token(token)
	{}

	Result<Symbol> Symbol::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::Identifier)
		{
			print_parse_error(token, "symbol");
			return {};
		}

		auto symbol = token;

		token.next();

		return Symbol { symbol };
	}

	// bool Symbol::validate(semantics::Context& context)
	// {
	// 	#pragma message("Implement symbol checking for functions on validation")

	// 	auto *declaration = func_ctx.get_declaration(_text);

	// 	if (declaration == nullptr)
	// 	{
	// 		print_error(_token, "symbol '" + _text + "' is not declared in scope");
	// 		return false;
	// 	}

	// 	_type = &declaration->type();

	// 	return true;
	// }

	void Symbol::print_tree(u32 depth) const
	{
		print_branch(depth, _token.text());
	}
}