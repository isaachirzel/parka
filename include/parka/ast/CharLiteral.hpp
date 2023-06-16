#ifndef PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP
#define PARKA_AST_EXPRESSION_LITERAL_CHAR_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class CharLiteralAst : public ExpressionAst
	{
		Snippet _snippet;
		char _value;
		// TODO: UTF-8

	public:

		CharLiteralAst(const Snippet& snippet, char value) :
		_snippet(snippet),
		_value(value)
		{}
		CharLiteralAst(CharLiteralAst&&) = default;
		CharLiteralAst(const CharLiteralAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::CharLiteral; }
		const Snippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
