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

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
