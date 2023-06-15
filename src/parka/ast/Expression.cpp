#include "parka/ast/Expression.hpp"
#include "parka/ast/AssignmentExpression.hpp"
#include "parka/ast/BlockExpression.hpp"

namespace parka
{
	ExpressionSyntax *ExpressionSyntax::parse(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return BlockExpressionSyntax::parse(token);

		return AssignmentExpressionSyntax::parse(token);
	}
}
