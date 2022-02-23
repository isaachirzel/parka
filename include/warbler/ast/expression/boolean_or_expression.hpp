#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_OR_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_OR_HPP

// local headers
#include <warbler/ast/expression/boolean_and_expression.hpp>

namespace warbler::ast
{
	class BooleanOrExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BooleanOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const Location& location() const;
	};
}
#endif
