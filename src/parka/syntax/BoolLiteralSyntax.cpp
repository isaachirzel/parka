#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/KeywordSyntax.hpp"

namespace parka
{
	static Optional<bool> parseBool(Token& token)
	{
		auto type = KeywordSyntax::getKeywordType(token);

		switch (type)
		{
			case KeywordType::True:
				return true;

			case KeywordType::False:
				return false;

			default:
				break;
		}

		log::parseError(token, "`true` or `false`");
		
		return {};
	}

	ExpressionSyntax *BoolLiteralSyntax::parse(Token& token)
	{
		auto value = parseBool(token);

		if (!value)
			return {};

		auto *syntax = new BoolLiteralSyntax(token, *value);

		token.increment();

		return syntax;
	}
}
