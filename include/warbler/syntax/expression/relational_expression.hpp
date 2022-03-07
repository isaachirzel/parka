#ifndef WARBLER_SYNTAX_EXPRESSION_RELATIONAL_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_RELATIONAL_EXPRESSION_HPP

// local headers
#include <warbler/syntax/expression/shift_expression.hpp>

namespace warbler::syntax
{
	enum class RelationalType
	{
		GreaterThan,
		LessThan,
		GreaterThanOrEqualTo,
		LessThanOrEqualTo
	};

	struct RelationalRhs
	{
		Ptr<Expression> expr;
		RelationalType type;
	};

	class RelationalExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<RelationalRhs> _rhs;

	public:

		RelationalExpression(Ptr<Expression>&& lhs, Array<RelationalRhs>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		//const lexicon::Token& token() const;
	};

}

#endif