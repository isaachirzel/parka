#ifndef PARKA_AST_EXPRESSION_IF_HPP
#define PARKA_AST_EXPRESSION_IF_HPP

#include "parka/ast/expression/expression.hpp"
#include "parka/entity/statement_id.hpp"
#include "parka/util/box.hpp"

// TODO: Consider merging this with conditional expression

enum class IfType
{
	Then,
	ThenElse,
	ThenElseIf
};

class IfExpression //: public Expression
{
	ExpressionId _condition;
	StatementId _thenCase;

	union
	{
		StatementId _elseCase;
		ExpressionId _elseIf;
	};

	IfType _type;
};

#endif
