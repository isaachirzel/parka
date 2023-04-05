
#include "parka/ast/expression_statement.hpp"
#include "parka/ast/assignment_expression.hpp"
#include "parka/ast/block.hpp"

Optional<ExpressionId> Expression::parse(Token& token)
{
	if (token.type() == TokenType::LeftBrace)
		return Block::parse(token);

	return Assignment::parse(token);
}
