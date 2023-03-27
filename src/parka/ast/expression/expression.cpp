
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/expression/assignment.hpp"
#include "parka/ast/expression/block.hpp"

Optional<ExpressionId> Expression::parse(Token& token)
{
	if (token.type() == TokenType::LeftBrace)
		return Block::parse(token);

	return Assignment::parse(token);
}
