#ifndef WARBLER_AST_EXPRESSION_PRIMARY_EXPRESSION
#define WARBLER_AST_EXPRESSION_PRIMARY_EXPRESSION

#include <warbler/token.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	struct PrimaryExpression
	{
		static Result<Ptr<Expression>> parse(TokenIterator& iter);
	};
}

#endif
