#ifndef PARKA_AST_LITERAL_HPP
#define PARKA_AST_LITERAL_HPP

#include "parka/ast/expression/expression.hpp"

struct Literal : public Expression
{
	virtual ~Literal() {}
};

#endif
