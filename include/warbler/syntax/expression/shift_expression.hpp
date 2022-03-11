#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_SHIFT_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_SHIFT_HPP

// local headers
#include <warbler/syntax/expression/additive_expression.hpp>

namespace warbler::syntax
{
	enum class ShiftType
	{
		Left,
		Right
	};

	struct ShiftRhs
	{
		Expression expr;
		ShiftType type;
	};

	class ShiftExpression
	{
	private:

		Expression _lhs;
		Array<ShiftRhs> _rhs;

	public:

		ShiftExpression(Expression&& lhs, Array<ShiftRhs>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}

#endif
