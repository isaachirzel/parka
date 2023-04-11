#ifndef PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	enum class MultiplicativeType
	{
		Multiply,
		Divide,
		Modulus
	};

	class MultiplicativeExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;
		MultiplicativeType _type;

		MultiplicativeExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs, MultiplicativeType type):
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		MultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax&&) = default;
		MultiplicativeExpressionSyntax(const MultiplicativeExpressionSyntax&) = delete;
		~MultiplicativeExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
