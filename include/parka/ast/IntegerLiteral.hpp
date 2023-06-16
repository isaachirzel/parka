#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class IntegerLiteralContext : public ExpressionContext
	{
		u64 _value;
		ValueType _valueType;

	public:

		IntegerLiteralContext(u64 value, ValueType&& valueType) :
		_value(value),
		_valueType(std::move(valueType))
		{}
		IntegerLiteralContext(IntegerLiteralContext&&) = default;
		IntegerLiteralContext(const IntegerLiteralContext&) = delete;
		
		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		// TODO: Actually check size of literal
		const ValueType& valueType() const { return ValueType::i32Type; }

		friend class IntegerLiteralSyntax;
	};

	class IntegerLiteralSyntax : public ExpressionSyntax
	{
		Snippet _snippet;

	public:

		IntegerLiteralSyntax(const Snippet& snippet) :
		_snippet(snippet)
		{}
		IntegerLiteralSyntax(IntegerLiteralSyntax&&) = default;
		IntegerLiteralSyntax(const IntegerLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
