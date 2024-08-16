#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/fs/FileSnippet.hpp"

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
		
		virtual const fs::FileSnippet& snippet() const = 0;
	};
}

#endif
