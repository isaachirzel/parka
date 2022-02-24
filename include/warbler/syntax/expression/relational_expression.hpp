#ifndef WARBLER_SYNTAX_EXPRESSION_BOOLEAN_RELATIONAL_HPP
#define WARBLER_SYNTAX_EXPRESSION_BOOLEAN_RELATIONAL_HPP

// local headers
#include <warbler/syntax//expression/shift_expression.hpp>

namespace warbler::syntax
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
		Array<RelationalRhs> _rhs;

	public:

		RelationalExpression(Ptr<Expression>&& lhs, Array<RelationalRhs>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const source::Location& location() const;
	};

}

#endif