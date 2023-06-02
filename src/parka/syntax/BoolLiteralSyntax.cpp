#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/KeywordSyntax.hpp"

#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<bool> parseBool(Token& token)
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

		Log::parseError(token, "`true` or `false`");
		
		return {};
	}

	Optional<ExpressionSyntaxId> BoolLiteralSyntax::parse(Token& token)
	{
		auto value = parseBool(token);

		if (!value)
			return {};

		auto literal = BoolLiteralSyntax(token, *value);
		auto id = ExpressionSyntaxId::create(std::move(literal));

		token.increment();

		return id;
	}
}
