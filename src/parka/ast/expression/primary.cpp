#include "parka/ast/expression/primary.hpp"

Optional<Box<Expression>> PrimaryExpression::parse(Token& token)
{
	Expression node = { 0 };

	if (token.type() == TokenType::Identifier)
	{		
		if (!parseIdentifier(&node, token))
			goto error;
	}
	else if (token.type() == TokenType::LeftParenthesis)
	{
		token.increment();

		if (!parseExpression(&node, token))
			goto error;

		if (token.type() != TokenType::RightParenthesis)
		{
			printParseError(token, "expected ')' after primary sub-expression", NULL);
			goto error;
		}

		token.increment();
	}
	else
	{
		if (!parseLiteral(&node, token))
			goto error;
	}

	*out = node;

	return true;

error:

	return false;
}
