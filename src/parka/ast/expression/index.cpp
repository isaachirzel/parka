#include "parka/ast/expression/index.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> IndexExpression::parse(Token& token, ExpressionId primary)
{
	if (token.type() != TokenType::LeftBracket)
	{
		printParseError(token, "'['");
		return {};
	}

	token.increment();

	auto index = Expression::parse(token);

	if (!index)
		return {};

	auto expression = IndexExpression(std::move(primary), index.unwrap());
	auto id = NodeBank::add(std::move(expression));

	if (token.type() != TokenType::RightBracket)
	{
		printParseError(token, "']' after subscript");
		return {};
	}

	token.increment();

	return id;
}

bool IndexExpression::validate(SymbolTable& symbols)
{
	exitNotImplemented();
}

Optional<Type> IndexExpression::getType(const SymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented();
}
