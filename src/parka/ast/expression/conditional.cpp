#include "parka/ast/expression/conditional.hpp"
#include "parka/ast/expression/boolean_or.hpp"

#include "parka/ast/expression/expression.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<Box<Expression>> ConditionalExpression::parse(Token& token)
{
	auto condition = BooleanOrExpression::parse(token);

	if (token.type() != TokenType::KeywordThen)
		return condition;

	token.increment();

	auto trueCase = ConditionalExpression::parse(token);

	if (!trueCase)
		return {};

	if (token.type() != TokenType::KeywordElse)
	{
		printTokenError(token, "else case for conditional expression");
		return {};
	}

	token.increment();

	auto falseCase = ConditionalExpression::parse(token);

	if (!falseCase)
		return {};

	auto expression = new ConditionalExpression(condition.unwrap(), trueCase.unwrap(), falseCase.unwrap());
	auto box = Box<Expression>(expression);

	return box;
}
