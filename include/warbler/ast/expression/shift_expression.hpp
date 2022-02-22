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

	class ShiftExpression : public Expression
	{
	private:

		AdditiveExpression _lhs;
		std::vector<ShiftRhs> _rhs;

	public:

		ShiftExpression(AdditiveExpression&& lhs, std::vector<ShiftRhs>&& rhs);

		static Result<ShiftExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Typename *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
	};
}

#endif
