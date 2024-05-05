#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	struct ExpressionAst
	{
		const ExpressionType expressionType;

	public:

		ExpressionAst(ExpressionType expressionType):
		expressionType(expressionType)
		{}
		virtual ~ExpressionAst() {}
		
		virtual const Snippet& snippet() const = 0;
	};
}

#endif
