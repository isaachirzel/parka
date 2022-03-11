#ifndef WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_EXPRESSION_HPP

// local headers
#include <warbler/syntax/expression/multiplicative_expression.hpp>

namespace warbler::syntax
{
	enum class AdditiveType
	{
		Add,
		Subtract
	};

	struct AdditiveRhs
	{
		Expression expr;
		AdditiveType type;
	};

	class AdditiveExpression
	{
	private:

		Expression _lhs;
		Array<AdditiveRhs> _rhs;
	
	public:

		AdditiveExpression(Expression&& lhs, Array<AdditiveRhs>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		
	};
}

#endif
