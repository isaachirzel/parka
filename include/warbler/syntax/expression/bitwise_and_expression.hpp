#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_AND_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_AND_HPP

// local headers
#include <warbler/syntax/expression/equality_expression.hpp>

namespace warbler::syntax
{
	class BitwiseAndExpression
	{
	private:

		Expression _lhs;
		Array<Expression> _rhs;

	public:

		BitwiseAndExpression(Expression&& lhs, Array<Expression>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
