#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_INTEGER_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/syntax/LiteralSyntax.hpp"

namespace parka
{
	class IntegerLiteralSyntax : public ExpressionSyntax
	{
		Token _token;
		u64 _value;
		u32 _bytes;

	public:

		IntegerLiteralSyntax(const Token& token, u64 value, u32 bytes);
		IntegerLiteralSyntax(IntegerLiteralSyntax&&) = default;
		IntegerLiteralSyntax(const IntegerLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		const auto& token() const { return _token; }
		const auto& value() const { return _value; }
		const auto& bytes() const { return _bytes; }
	};
}

#endif
