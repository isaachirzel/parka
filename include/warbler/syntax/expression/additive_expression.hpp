#ifndef WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_ADDITIVE_HPP
#define WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_ADDITIVE_HPP

// local headers
#include <warbler/syntax/expression/multiplicative_expression.hpp>

namespace warbler::syntax
{
	enum AdditiveType
	{
		ADDITIVE_ADD,
		ADDITIVE_SUBTRACT
	};

	struct AdditiveRhs
	{
		Ptr<Expression> expr;
		AdditiveType type;
	};

	class AdditiveExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<AdditiveRhs> _rhs;
	
	public:

		AdditiveExpression(Ptr<Expression>&& lhs, Array<AdditiveRhs>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const source::Location& location() const;
	};
}

#endif
