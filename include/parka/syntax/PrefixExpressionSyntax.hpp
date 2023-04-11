#ifndef PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP

#include "parka/enum/PrefixType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/Token.hpp"

namespace parka
{
	class PrefixExpressionSyntax : public ExpressionSyntax
	{
		Token _token;
		ExpressionSyntaxId _expression;
		PrefixType _type;

		PrefixExpressionSyntax(PrefixType type, ExpressionSyntaxId&& expression, const Token& token) :
		_token(token),
		_expression(std::move(expression)),
		_type(type)
		{}

	public:

		PrefixExpressionSyntax(PrefixExpressionSyntax&&) = default;
		PrefixExpressionSyntax(const PrefixExpressionSyntax&) = delete;
		~PrefixExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);
		
		bool validate(const EntitySyntaxId& functionId);
		Optional<Type> getType() const;

		const auto& token() const { return _token; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
