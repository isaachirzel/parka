#ifndef PARKA_AST_LITERAL_HPP
#define PARKA_AST_LITERAL_HPP

#include "parka/ast/expression.hpp"

struct Literal : public Expression
{
	virtual ~Literal() {}

	static Optional<ExpressionId> parse(Token& token);
};

#endif
