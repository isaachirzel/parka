#ifndef PARKA_AST_IF_EXPRESSION_HPP
#define PARKA_AST_IF_EXPRESSION_HPP

#include "parka/ast/ExpressionAst.hpp"

// TODO: Consider merging this with conditional expression

namespace parka::ast
{
	class IfExpressionAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;

	public:

		IfExpressionAst(const fs::FileSnippet& snippet):
		ExpressionAst(ExpressionType::If),
		_snippet(snippet)
		{}

		const fs::FileSnippet& snippet() const { return _snippet; }
	};
}

#endif
