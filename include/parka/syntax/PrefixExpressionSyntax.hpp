#ifndef PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/Token.hpp"

namespace parka
{
	enum class PrefixExpressionSyntaxType
	{
		Reference,
		Dereference,
		Positive,
		Negative,
		BitwiseNot,
		BooleanNot
	};

	class PrefixExpressionSyntax : public ExpressionSyntax
	{
		Token _token;
		ExpressionId _expression;
		PrefixExpressionSyntaxType _type;

		PrefixExpressionSyntax(PrefixExpressionSyntaxType type, ExpressionId&& expression, const Token& token) :
		_token(token),
		_expression(std::move(expression)),
		_type(type)
		{}

	public:

		PrefixExpressionSyntax(PrefixExpressionSyntax&&) = default;
		PrefixExpressionSyntax(const PrefixExpressionSyntax&) = delete;
		~PrefixExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);
		
		bool validate(const EntityId& functionId);
		Optional<Type> getType() const;

		const auto& token() const { return _token; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
