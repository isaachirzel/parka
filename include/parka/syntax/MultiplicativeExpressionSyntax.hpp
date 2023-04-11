#ifndef PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP

#include "parka/enum/MultiplicativeType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	class MultiplicativeExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;
		MultiplicativeType _type;

		MultiplicativeExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs, MultiplicativeType type):
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		MultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax&&) = default;
		MultiplicativeExpressionSyntax(const MultiplicativeExpressionSyntax&) = delete;
		~MultiplicativeExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
