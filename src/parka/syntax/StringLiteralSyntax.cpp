#include "parka/syntax/StringLiteralSyntax.hpp"

#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *StringLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			log::parseError(token, "string");
			return {};
		}

		auto literal = StringLiteralSyntax(token, token.text());
		auto& syntax = ExpressionSyntax::create(std::move(literal));

		token.increment();

		return &syntax;
	}
}
