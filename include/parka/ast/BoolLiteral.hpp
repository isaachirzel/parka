#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_BOOL_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class BoolLiteralContext : public ExpressionContext
	{
		bool _value;

	public:

		BoolLiteralContext(bool value) :
		_value(value)
		{}
		BoolLiteralContext(BoolLiteralContext&&) = default;
		BoolLiteralContext(const BoolLiteralContext&) = delete;

		const ValueType& valueType() const { return ValueType::boolType; }
		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const auto& value() const { return _value; }
	};

	class BoolLiteralSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		bool _value;

	public:

		BoolLiteralSyntax(const Snippet& snippet, bool value) :
		_snippet(snippet),
		_value(value)
		{}
		BoolLiteralSyntax(BoolLiteralSyntax&&) = default;
		BoolLiteralSyntax(const BoolLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BoolLiteral; }
		const Snippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
