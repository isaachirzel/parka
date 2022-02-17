#ifndef WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP

// local headers
#include <warbler/ast/expression/comparison_expression.hpp>

namespace warbler::ast
{
	enum EqualityType
	{
		EQUALITY_EQUALS,
		EQUALITY_NOT_EQUALS
	};

	struct EqualityRhs
	{
		ComparisonExpression expr;
		EqualityType type;
	};

	class EqualityExpression
	{
	private:

		ComparisonExpression _lhs;
		Array<EqualityRhs> _rhs;

	public:

		EqualityExpression(ComparisonExpression&& lhs, Array<EqualityRhs>&& rhs);

		static Result<EqualityExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}
#endif
