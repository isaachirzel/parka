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
		Ptr<Expression> expr;
		RelationalType type;
	};

	class RelationalExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		std::vector<RelationalRhs> _rhs;

	public:

		RelationalExpression(Ptr<Expression>&& lhs, std::vector<RelationalRhs>&& rhs);

		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const Location& location() const;
	};

}

#endif