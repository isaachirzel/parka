#ifndef PARKA_AST_EXPRESSION_LITERAL_STRING_HPP
#define PARKA_AST_EXPRESSION_LITERAL_STRING_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class StringLiteralAst: public ExpressionAst
	{
		Snippet _snippet;

	public:

		StringLiteralAst(const Snippet& snippet):
		ExpressionAst(ExpressionType::StringLiteral),
		_snippet(snippet)
		{}
		StringLiteralAst(StringLiteralAst&&) = default;
		StringLiteralAst(const StringLiteralAst&) = delete;
		
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
