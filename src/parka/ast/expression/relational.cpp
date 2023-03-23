#include "parka/ast/expression/relational.hpp"
#include "parka/ast/expression/shift.hpp"


Optional<Box<Expression>> RelationalExpression::parse(Token& token)
{
	RelationalExpression node = { 0 };

	if (!parseBitShiftExpression(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		RelationalType type;
		switch (token.type())
		{
			case TokenType::GreaterThan:
				type = RELATIONAL_GREATER_THAN;
				break;

			case TokenType::LessThan:
				type = RELATIONAL_LESS_THAN;
				break;

			case TokenType::GreaterThanOrEqualTo:
				type = RELATIONAL_GREATER_THAN_OR_EQUAL_TO;
				break;

			case TokenType::LessThanOrEqualTo:
				type = RELATIONAL_LESS_THAN_OR_EQUAL_TO;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		token.increment();

		Expression expression;

		if (!parseBitShiftExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (RelationalRhs)
		{
			.expr = expression,
			.type = type
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
	}
	else
	{
		out->type = EXPRESSION_RELATIONAL;
		out->relational = new(RelationalExpression);
		*out->relational = node;
	}

	return true;
	
error:

	return false;
}
