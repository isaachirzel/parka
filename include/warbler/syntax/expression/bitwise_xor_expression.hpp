#ifndef WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BITWISE_XOR_HPP

// local headers
#include <warbler/syntax/expression/bitwise_and_expression.hpp>

namespace warbler::syntax
{
	class BitwiseXorExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BitwiseXorExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		Type *get_type();
		const lexicon::Token& token() const;
		void print_tree(u32 depth = 0) const;
	};
}
#endif
