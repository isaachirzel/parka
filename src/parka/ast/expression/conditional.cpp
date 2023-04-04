#include "parka/ast/expression/conditional.hpp"
#include "parka/ast/expression/boolean_or.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> ConditionalExpression::parse(Token& token)
{
	auto condition = BooleanOrExpression::parse(token);
	auto keyword = Keyword::getKeywordType(token);

	if (keyword != KeywordType::Then)
		return condition;

	token.increment();

	auto trueCase = ConditionalExpression::parse(token);

	if (!trueCase)
		return {};

	keyword = Keyword::getKeywordType(token);

	if (keyword != KeywordType::Else)
	{
		printError(token, "else case for conditional expression");
		return {};
	}

	token.increment();

	auto falseCase = ConditionalExpression::parse(token);

	if (!falseCase)
		return {};

	auto expression = ConditionalExpression(condition.unwrap(), trueCase.unwrap(), falseCase.unwrap());
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool ConditionalExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> ConditionalExpression::getType(Ref<Type>) const
{
	exitNotImplemented(here());
}
