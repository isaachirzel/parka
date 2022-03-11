#ifndef WARBLER_SYNTAX_EXPRESSION_BOOLEAN_OR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BOOLEAN_OR_HPP

// local headers
#include <warbler/syntax/expression/boolean_and_expression.hpp>

namespace warbler::syntax
{
	class BooleanOrExpression
	{
	private:

		Expression _lhs;
		Array<Expression> _rhs;

	public:

		BooleanOrExpression(Expression&& lhs, Array<Expression>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
