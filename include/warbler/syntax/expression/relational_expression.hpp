#ifndef WARBLER_SYNTAX_EXPRESSION_RELATIONAL_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_RELATIONAL_EXPRESSION_HPP

// local headers
#include <warbler/syntax/expression/shift_expression.hpp>

namespace warbler::syntax
{
	enum class RelationalType
	{
		GreaterThan,
		LessThan,
		GreaterThanOrEqualTo,
		LessThanOrEqualTo
	};

	struct RelationalRhs
	{
		Expression expr;
		RelationalType type;
	};

	class RelationalExpression
	{
	private:

		Expression _lhs;
		Array<RelationalRhs> _rhs;

	public:

		RelationalExpression(Expression&& lhs, Array<RelationalRhs>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
	};

}

#endif