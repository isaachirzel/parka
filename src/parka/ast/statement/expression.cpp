#include "parka/ast/statement/expression.hpp"
#include "parka/symbol/expression_id.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<StatementId> ExpressionStatement::parse(Token& token)
{
	auto expression = Expression::parse(token);

	if (!expression)
		return {};

	if (token.type() != TokenType::Semicolon)
	{
		printParseError(token, "';' after expression statement", NULL);
		return {};
	}

	token.increment();

	auto statement = ExpressionStatement(expression.unwrap());
	auto id = NodeBank::add(std::move(statement));

	return id;
}

bool ExpressionStatement::validate(LocalSymbolTable& symbols)
{
	exitNotImplemented(here());
}
