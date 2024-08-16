#ifndef PARKA_AST_EXPRESSION_LITERAL_STRING_HPP
#define PARKA_AST_EXPRESSION_LITERAL_STRING_HPP

#include "parka/ast/ExpressionAst.hpp"

namespace parka::ast
{
	class StringLiteralAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;
		String _text;

	public:

		StringLiteralAst(const fs::FileSnippet& snippet, String&& text):
			ExpressionAst(ExpressionType::StringLiteral),
			_snippet(snippet),
			_text(std::move(text))
		{}
		StringLiteralAst(StringLiteralAst&&) = default;
		StringLiteralAst(const StringLiteralAst&) = delete;
		
		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& text() const { return _text; }
	};
}

#endif
