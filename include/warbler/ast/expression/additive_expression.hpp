#ifndef WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_HPP
#define WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_HPP

// local headers
#include <warbler/ast/expression/multiplicative_expression.hpp>

namespace warbler::ast
{
	enum AdditiveType
	{
		ADDITIVE_ADD,
		ADDITIVE_SUBTRACT
	};

	struct AdditiveRhs
	{
		MultiplicativeExpression expr;
		AdditiveType type;
	};

	class AdditiveExpression
	{
	private:

		MultiplicativeExpression _lhs;
		Array<AdditiveRhs> _rhs;
	
	public:

		AdditiveExpression(MultiplicativeExpression&& lhs, Array<AdditiveRhs>&& rhs);

		static Result<AdditiveExpression> parse(TokenIterator& iter);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
