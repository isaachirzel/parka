#ifndef WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP

// local headers
#include <warbler/ast/expression/comparison_expression.hpp>

namespace warbler
{
	enum EqualityType
	{
		EQUALITY_EQUALS,
		EQUALITY_NOT_EQUALS
	};

	struct EqualityRhs
	{
		ComparisonExpression expr;
		EqualityType type;
	};

	class EqualityExpression
	{
	private:

		ComparisonExpression _lhs;
		Array<EqualityRhs> _rhs;

	public:

		EqualityExpression(ComparisonExpression&& lhs, Array<EqualityRhs>&& rhs);

		static Result<EqualityExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}
#endif
