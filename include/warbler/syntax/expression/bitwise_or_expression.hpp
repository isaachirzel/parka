#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_OR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_OR_HPP

// local headers
#include <warbler/syntax/expression/bitwise_xor_expression.hpp>

namespace warbler::syntax
{
	class BitwiseOrExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;	

	public:

		BitwiseOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		Type *get_type();
		const lexicon::Token& token() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
