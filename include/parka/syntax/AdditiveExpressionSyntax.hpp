#ifndef PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	enum class AdditiveType
	{
		Add,
		Subtract
	};

	class AdditiveExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;
		AdditiveType _type;

		AdditiveExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs, AdditiveType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}
		
	public:

		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(const AdditiveExpressionSyntax&) = delete;
		~AdditiveExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
