#ifndef WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_EQUALITY_EXPRESSION_HPP

// local headers
#include <warbler/ast/expression/relational_expression.hpp>

namespace warbler::ast
{
	enum EqualityType
	{
		EQUALITY_EQUALS,
		EQUALITY_NOT_EQUALS
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

		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const Location& location() const;
	};
}
#endif
