#ifndef WARBLER_SYNTAX_EXPRESSION_BOOLEAN_AND_HPP
#define WARBLER_SYNTAX_EXPRESSION_BOOLEAN_AND_HPP

// local headers
#include <warbler/syntax/expression/bitwise_or_expression.hpp>

namespace warbler::syntax
{
	class BooleanAndExpression
	{
	private:

		Expression _lhs;
		Array<Expression> _rhs;

	public:

		BooleanAndExpression(Expression&& lhs, Array<Expression>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}

#endif
