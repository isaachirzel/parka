#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
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

		printParseError(token, "`true` or `false`");
		
		return {};
	}

	Optional<ExpressionSyntaxId> BoolLiteralSyntax::parse(Token& token)
	{
		auto value = parseBool(token);

		if (!value)
			return {};

		auto literal = BoolLiteralSyntax(token, *value);
		auto id = SyntaxRepository::add(std::move(literal));

		token.increment();

		return id;
	}
}
