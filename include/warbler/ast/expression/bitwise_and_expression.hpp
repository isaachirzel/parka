#ifndef WARBLER_AST_EXPRESSION_BITWISE_AND_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_AND_HPP

// local headers
#include <warbler/ast/expression/equality_expression.hpp>

namespace warbler::ast
{
	class BitwiseAndExpression
	{
	private:

		EqualityExpression _lhs;
		Array<EqualityExpression> _rhs;

	public:

		BitwiseAndExpression(EqualityExpression&& lhs, Array<EqualityExpression>&& rhs);

		static Result<BitwiseAndExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& context);
		void print_tree(u32 depth = 0) const;
	};
}
#endif
