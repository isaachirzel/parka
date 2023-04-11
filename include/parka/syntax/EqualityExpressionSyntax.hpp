#ifndef PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	enum class EqualityType
	{
		Equals,
		NotEquals
	};

	class EqualityExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;
		EqualityType _type;

		EqualityExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs, EqualityType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		EqualityExpressionSyntax(EqualityExpressionSyntax&&) = default;
		EqualityExpressionSyntax(const EqualityExpressionSyntax&) = delete;
		~EqualityExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
