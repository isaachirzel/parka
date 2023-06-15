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

	private:

		IntegerLiteralContext(u64 value, ValueType&& valueType);

	public:

		IntegerLiteralContext(IntegerLiteralContext&&) = default;
		IntegerLiteralContext(const IntegerLiteralContext&) = delete;
		
		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		// TODO: Actually check size of literal
		const ValueType& valueType() const { return ValueType::i32Type; }

		friend class IntegerLiteralSyntax;
	};

	class IntegerLiteralSyntax : public ExpressionSyntax
	{
		Token _token;

	public:

		IntegerLiteralSyntax(const Token& token);
		IntegerLiteralSyntax(IntegerLiteralSyntax&&) = default;
		IntegerLiteralSyntax(const IntegerLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		const auto& token() const { return _token; }
	};
}

#endif
