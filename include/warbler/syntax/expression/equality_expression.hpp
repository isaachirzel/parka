#ifndef WARBLER_SYNTAX_EXPRESSION_EQUALITY_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_EQUALITY_EXPRESSION_HPP

// local headers
#include <warbler/syntax/expression/relational_expression.hpp>

namespace warbler::syntax
{
	enum class EqualityType
	{
		Equals,
		NotEquals
	};

	struct EqualityRhs
	{
		Ptr<Expression> expr;
		EqualityType type;
	};

	class EqualityExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<EqualityRhs> _rhs;

	public:

		EqualityExpression(Ptr<Expression>&& lhs, Array<EqualityRhs>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const source::Location& location() const;
	};
}
#endif
