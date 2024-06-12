#ifndef PARKA_AST_EXPRESSION_LITERAL_STRING_HPP
#define PARKA_AST_EXPRESSION_LITERAL_STRING_HPP

#include "parka/ast/ExpressionAst.hpp"

namespace parka::ast
{
	class StringLiteralAst: public ExpressionAst
	{
		Snippet _snippet;
		String _text;

	public:

		StringLiteralAst(const Snippet& snippet, String&& text):
			ExpressionAst(ExpressionType::StringLiteral),
			_snippet(snippet),
			_text(std::move(text))
		{}
		StringLiteralAst(StringLiteralAst&&) = default;
		StringLiteralAst(const StringLiteralAst&) = delete;
		
		const Snippet& snippet() const { return _snippet; }
		const auto& text() const { return _text; }
	};
}

#endif
