#include "parka/ast/expression/call.hpp"
#include "parka/symbol_table.hpp"

#include "parka/util/print.hpp"

Optional<Box<Expression>> CallExpression::parse(Token& token)
{
	if (token.type() == TokenType::LeftParenthesis)
	{
		printParseError(token, "'(' before argument list");
		
		return {};
	}

	token.increment();

	// TODO: Add initial capacity
	auto arguments = Array<Box<Expression>>();

	if (token.type() == TokenType::RightParenthesis)
	{
		do
		{
			token.increment();

			auto argument = Expression::parse(token);

			if (!argument)
				return {}; // TODO: Continue to next argument

			arguments.emplace_back(argument.unwrap());
		}
		while (token.type() == TokenType::Comma);

		if (token.type() != TokenType::RightParenthesis)
		{
			printParseError(token, "')' after argument list");

			return {};
		}
	}

	token.increment();

	auto *call = new CallExpression(std::move(arguments));
	auto box = Box<Expression>(call);

	return box;
}

bool CallExpression::validate(SymbolTable& symbols)
{
	exitNotImplemented();
}
