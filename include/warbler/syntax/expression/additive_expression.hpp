#ifndef WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_ARITHMETIC_EXPRESSION_HPP

// local headers
#include <warbler/syntax/expression/multiplicative_expression.hpp>

namespace warbler::syntax
{
	enum class AdditiveType
	{
		Add,
		Subtract
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

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}

#endif
