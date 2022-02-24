#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP

// local headers
#include <warbler/syntax//expression/bitwise_and_expression.hpp>

namespace warbler::syntax
{
	class BitwiseXorExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BitwiseXorExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		Type *get_type();
		const source::Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}
#endif
