
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> ExpressionSyntax::parse(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return BlockSyntax::parse(token);

		return AssignmentExpressionSyntax::parse(token);
	}
}
