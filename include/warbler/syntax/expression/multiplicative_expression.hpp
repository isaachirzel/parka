#ifndef WARBLER_SYNTAX_EXPRESSION_MULTIPLICATIVE_HPP
#define WARBLER_SYNTAX_EXPRESSION_MULTIPLICATIVE_HPP

// local headers
#include <warbler/syntax/expression/prefix_expression.hpp>

namespace warbler::syntax
{
	enum class MultiplicativeType
	{
		Multiply,
		Divide,
		Modulus
	};

	struct MultiplicativeRhs
	{
		Expression expr;
		MultiplicativeType type;
	};

	class MultiplicativeExpression
	{
	private:

		Expression _lhs;
		Array<MultiplicativeRhs> _rhs;
	
	public:

		MultiplicativeExpression(Expression&& lhs, Array<MultiplicativeRhs>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}

#endif
