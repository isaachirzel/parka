#ifndef PARKA_AST_EXPRESSION_IF_HPP
#define PARKA_AST_EXPRESSION_IF_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/util/box.hpp"

class Statement;

// TODO: Consider merging this with conditional expression

enum IfType
{
	IF_THEN,
	IF_THEN_ELSE,
	IF_THEN_ELSE_IF
};

typedef struct IfExpression : public Expression
{
	Box<Expression> condition;
	Box<Statement> thenCase;

	union
	{
		struct Statement *elseCase;
		struct IfExpression *elseIf;
	};

	IfType type;
} IfExpression;

#endif
