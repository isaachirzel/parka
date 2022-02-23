#ifndef WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP

// local headers
#include <warbler/ast/expression/prefix_expression.hpp>

namespace warbler::ast
{
	enum MultiplicativeType
	{
		MULTIPLICATIVE_MULTIPLY,
		MULTIPLICATIVE_DIVIDE,
		MULTIPLICATIVE_MODULUS
	};

	struct MultiplicativeRhs
	{
		Ptr<Expression> expr;
		MultiplicativeType type;
	};

	class MultiplicativeExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<MultiplicativeRhs> _rhs;
	
	public:

		MultiplicativeExpression(Ptr<Expression>&& lhs, Array<MultiplicativeRhs>&& rhs);

		static Result<MultiplicativeExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
	};
}

#endif
