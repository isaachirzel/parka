#ifndef PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP

#include "parka/enum/RelationalType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class RelationalExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;
		RelationalType _type;

		RelationalExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs, RelationalType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}

	public:

		RelationalExpressionSyntax(RelationalExpressionSyntax&&) = default;
		RelationalExpressionSyntax(const RelationalExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Relational; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
