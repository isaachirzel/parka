#ifndef WARBLER_SYNTAX_EXPRESSION_BOOLEAN_AND_HPP
#define WARBLER_SYNTAX_EXPRESSION_BOOLEAN_AND_HPP

// local headers
#include <warbler/syntax//expression/bitwise_or_expression.hpp>

namespace warbler::syntax
{
	class BooleanAndExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BooleanAndExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const Location& location() const;
	};
}

#endif
