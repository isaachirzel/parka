#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_HPP
#define WARBLER_AST_EXPRESSION_CONDITIONAL_HPP

// local headers
#include <warbler/ast/expression/boolean_or_expression.hpp>

namespace warbler
{
	struct ConditionalRhs;

	class ConditionalExpression
	{
	private: // members

		BooleanOrExpression _lhs;
		ConditionalRhs *_rhs;

	public: // methods

		ConditionalExpression(BooleanOrExpression&& lhs);
		ConditionalExpression(BooleanOrExpression&& lhs, ConditionalRhs&& rhs);
		ConditionalExpression(ConditionalExpression&& other);
		ConditionalExpression(const ConditionalExpression& other);
		~ConditionalExpression();

		static Result<ConditionalExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		ConditionalExpression& operator=(ConditionalExpression&& other);
		ConditionalExpression& operator=(const ConditionalExpression& other);
	};

	struct ConditionalRhs
	{
		BooleanOrExpression true_case;
		ConditionalExpression false_case;

		ConditionalRhs(BooleanOrExpression&& true_case, ConditionalExpression&& false_case);
	};
}

#endif
