#ifndef PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP
#define PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP

#include "parka/ast/ExpressionAst.hpp"

// TODO: Determine size of float

namespace parka::ast
{
	class FloatLiteralAst: public ExpressionAst
	{
		Snippet _snippet;

	public:

		FloatLiteralAst(const Snippet& snippet):
		ExpressionAst(ExpressionType::FloatLiteral),
		_snippet(snippet)
		{}
		FloatLiteralAst(FloatLiteralAst&&) = default;
		FloatLiteralAst(const FloatLiteralAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
