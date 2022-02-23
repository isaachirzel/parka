#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_RELATIONAL_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_RELATIONAL_HPP

// local headers
#include <warbler/ast/expression/shift_expression.hpp>

namespace warbler::ast
{
	enum RelationalType
	{
		RELATIONAL_GREATER,
		RELATIONAL_LESS,
		RELATIONAL_GREATER_EQUAL,
		RELATIONAL_LESS_EQUAL
	};

	struct RelationalRhs
	{
		ShiftExpression expr;
		RelationalType type;
	};

	class RelationalExpression : public Expression
	{
	private:

		ShiftExpression _lhs;
		std::vector<RelationalRhs> _rhs;

	public:

		RelationalExpression(ShiftExpression&& lhs, std::vector<RelationalRhs>&& rhs);

		static Result<RelationalExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
	};

}

#endif