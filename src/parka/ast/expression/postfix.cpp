#include "parka/ast/expression/postfix.hpp"
#include "parka/ast/expression/call.hpp"

#include "parka/ast/expression/expression.hpp"
#include "parka/util/print.hpp"

Optional<Box<Expression>> PostfixExpression::parse(Token& token)
{
	PostfixExpression node = { 0 };

	if (!parsePrimaryExpression(&node.expression, token))
		goto error;

parsePostfix:

	switch (token.type())
	{
		case TokenType::LeftBracket: // Index
			token.increment();

			Expression index;

			if (!parseExpression(&index, token))
				goto error;

			node.type = POSTFIX_INDEX;
			node.index = index;

			if (token.type() != TokenType::RightBracket)
			{
				printParseError(token, "']' after index operation", NULL);
				goto error;
			}

			token.increment();
			break;

		case TokenType::LeftParenthesis: // Function call
		{
			CallExpression arguments;

			if (!parseCallExpression(&arguments, token))
				goto error;

			node.type = POSTFIX_FUNCTION_CALL;
			node.call = arguments;
			break;
		}

		case TokenType::Dot: // Member
			token.increment();
		
			if (token.type() != TokenType::Identifier)
			{
				printParseError(token, "member, method, or property name", NULL);
				goto error;
			}

			Token name = *token;

			token.increment();
			
			node.type = POSTFIX_MEMBER;
			node.member = name;
			break;
		
		default:
			goto finish;
	}

	Expression inner =
	{
		.type = EXPRESSION_POSTFIX,
		.postfix = new(Postfix)
	};

	*inner.postfix = node;

	node = (Postfix)
	{
		.expression = inner
	};

	goto parsePostfix;

finish:

	*out = node.expression;

	return true;
	
error:

	return false;
}
