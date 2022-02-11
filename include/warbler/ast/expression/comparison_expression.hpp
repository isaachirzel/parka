#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_HPP

// local headers
#include <warbler/ast/expression/shift_expression.hpp>

namespace warbler::ast
{
	enum ComparisonType
	{
		COMPARISON_GREATER,
		COMPARISON_LESS,
		COMPARISON_GREATER_EQUAL,
		COMPARISON_LESS_EQUAL
	};

	struct ComparisonRhs
	{
		ShiftExpression expr;
		ComparisonType type;
	};

	class ComparisonExpression
	{
	private:

		ShiftExpression _lhs;
		std::vector<ComparisonRhs> _rhs;

	public:

		ComparisonExpression(ShiftExpression&& lhs, std::vector<ComparisonRhs>&& rhs);

		static Result<ComparisonExpression> parse(TokenIterator& iter);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};

}

#endif