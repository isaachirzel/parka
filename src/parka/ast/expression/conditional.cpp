#include "parka/ast/expression/conditional.hpp"
#include "parka/ast/expression/boolean_or.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> ConditionalExpression::parse(Token& token)
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

	auto expression = ConditionalExpression(condition.unwrap(), trueCase.unwrap(), falseCase.unwrap());
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool ConditionalExpression::validate(SymbolTable& symbols)
{
	exitNotImplemented(here());
}

Optional<Type> ConditionalExpression::getType(const SymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented(here());
}
