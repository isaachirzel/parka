#include <warbler/syntax/identifier.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Identifier::Identifier(const lexicon::Token& token) :
	_token(token)
	{}

	Result<Identifier> Identifier::parse(lexicon::Token& token)
	{
		if (token.type() != lexicon::TokenType::Identifier)
			return {};

		auto identifier = token;

		token.next();

		return Identifier { identifier };
	}

	void Identifier::print_tree(u32 depth) const
	{
		print_branch(depth, _token.text());
	}
}