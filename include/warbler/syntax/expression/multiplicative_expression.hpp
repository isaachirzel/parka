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

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const source::Location& location() const;
	};
}

#endif
