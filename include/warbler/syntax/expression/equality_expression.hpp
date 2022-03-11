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
		Expression expr;
		EqualityType type;
	};

	class EqualityExpression
	{
	private:

		Expression _lhs;
		Array<EqualityRhs> _rhs;

	public:

		EqualityExpression(Expression&& lhs, Array<EqualityRhs>&& rhs);

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
