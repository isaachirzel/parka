#include <warbler/syntax/label.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Label::Label(const lexicon::Token& token) :
	_token(token)
	{}

	Result<Label> Label::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::Identifier)
		{
			print_parse_error(token, "label identifer");
			return {};
		}

		auto label = token;

		if (token.next().type() != lexicon::TokenType::Colon)
		{
			print_parse_error(token, "':' after label");
			return {};
		}

		token.next();

		return Label(label);
	}

	void Label::print_tree(u32 depth) const
	{
		print_branch(depth, _token.text());
	}
}
