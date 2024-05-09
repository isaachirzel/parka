#ifndef PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP
#define PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class CharLiteralAst: public ExpressionAst
	{
		Snippet _snippet;

	public:

		CharLiteralAst(const Snippet& snippet):
		ExpressionAst(ExpressionType::CharLiteral),
		_snippet(snippet)
		{}
		CharLiteralAst(CharLiteralAst&&) = default;
		CharLiteralAst(const CharLiteralAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
