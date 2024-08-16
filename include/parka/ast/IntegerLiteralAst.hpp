#ifndef PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP
#define PARKA_AST_EXPRESSION_LITERAL_INTEGER_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/util/Common.hpp"

namespace parka::ast
{
	class IntegerLiteralAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;

	public:

		IntegerLiteralAst(const fs::FileSnippet& snippet):
		ExpressionAst(ExpressionType::IntegerLiteral),
		_snippet(snippet)
		{}
		IntegerLiteralAst(IntegerLiteralAst&&) = default;
		IntegerLiteralAst(const IntegerLiteralAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
	};
}

#endif
