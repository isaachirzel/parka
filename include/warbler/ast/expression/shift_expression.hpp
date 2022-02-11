#ifndef WARBLER_AST_EXPRESSION_BITWISE_SHIFT_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_SHIFT_HPP

// local headers
#include <warbler/ast/expression/additive_expression.hpp>

namespace warbler::ast
{
	enum ShiftType
	{
		SHIFT_LEFT,
		SHIFT_RIGHT
	};

	struct ShiftRhs
	{
		AdditiveExpression expr;
		ShiftType type;
	};

	class ShiftExpression
	{
	private:

		AdditiveExpression _lhs;
		std::vector<ShiftRhs> _rhs;

	public:

		ShiftExpression(AdditiveExpression&& lhs, std::vector<ShiftRhs>&& rhs);

		bool validate(semantics::ModuleContext& context);
		static Result<ShiftExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
