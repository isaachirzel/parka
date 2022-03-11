#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP

// local headers
#include <warbler/syntax/expression/bitwise_and_expression.hpp>

namespace warbler::syntax
{
	class BitwiseXorExpression
	{
	private:

		Expression _lhs;
		Array<Expression> _rhs;

	public:

		BitwiseXorExpression(Expression&& lhs, Array<Expression>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		Type *get_type();
		const lexicon::Token& token() const;
		void print_tree(u32 depth = 0) const;
	};
}
#endif
