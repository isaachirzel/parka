#ifndef PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP
#define PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP

#include "parka/ast/Expression.hpp"
#include "parka/util/Common.hpp"

namespace parka::ast
{
	class IntegerLiteralAst: public ExpressionAst
	{
		Snippet _snippet;

	public:

		IntegerLiteralAst(const Snippet& snippet):
		ExpressionAst(ExpressionType::IntegerLiteral),
		_snippet(snippet)
		{}
		IntegerLiteralAst(IntegerLiteralAst&&) = default;
		IntegerLiteralAst(const IntegerLiteralAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
