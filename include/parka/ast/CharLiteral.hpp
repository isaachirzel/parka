#ifndef PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP
#define PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP

#include "parka/ast/Expression.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class CharLiteralAst : public ExpressionAst
	{
		Snippet _snippet;
		char _value;
		// TODO: UTF-8

	public:

		CharLiteralAst(const Snippet& snippet, char value) :
		ExpressionAst(ExpressionType::CharLiteral),
		_snippet(snippet),
		_value(value)
		{}
		CharLiteralAst(CharLiteralAst&&) = default;
		CharLiteralAst(const CharLiteralAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
