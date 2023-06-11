#ifndef PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP

#include "parka/enum/RelationalType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class RelationalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		RelationalType _type;

	public:

		RelationalExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, RelationalType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		RelationalExpressionSyntax(RelationalExpressionSyntax&&) = default;
		RelationalExpressionSyntax(const RelationalExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Relational; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
