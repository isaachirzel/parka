#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_HPP
#define WARBLER_AST_EXPRESSION_CONDITIONAL_HPP

// local headers
#include <warbler/ast/expression/boolean_or_expression.hpp>

namespace warbler
{
	struct Expression;

	enum ConditionalType
	{
		CONDITIONAL_NONE,
		CONDITIONAL_TERNARY
	};

	class ConditionalExpression
	{
	private:

		BooleanOrExpression _lhs;
		ConditionalType _type;

	public:

		ConditionalExpression(BooleanOrExpression&& lhs);

		static Result<ConditionalExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0);
	};
}

#endif
