#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_AND_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_AND_HPP

// local headers
#include <warbler/syntax/expression/equality_expression.hpp>

namespace warbler::syntax
{
	class BitwiseAndExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BitwiseAndExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
