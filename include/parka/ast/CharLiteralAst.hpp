#ifndef PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP
#define PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class CharLiteralAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;

	public:

		CharLiteralAst(const fs::FileSnippet& snippet):
		ExpressionAst(ExpressionType::CharLiteral),
		_snippet(snippet)
		{}
		CharLiteralAst(CharLiteralAst&&) = default;
		CharLiteralAst(const CharLiteralAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
	};
}

#endif
