#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> ConditionalExpressionSyntax::parse(Token& token)
	{
		auto condition = BooleanOrExpressionSyntax::parse(token);
		auto keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = ConditionalExpressionSyntax::parse(token);

		if (!trueCase)
			return {};

		keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Else)
		{
			printError(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = ConditionalExpressionSyntax::parse(token);

		if (!falseCase)
			return {};

		auto expression = ConditionalExpressionSyntax(*condition, *trueCase, *falseCase);
		auto id = Storage::add(std::move(expression));

		return id;
	}
}
