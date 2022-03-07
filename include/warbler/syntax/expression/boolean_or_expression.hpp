#ifndef WARBLER_SYNTAX_EXPRESSION_BOOLEAN_OR_HPP
#define WARBLER_SYNTAX_EXPRESSION_BOOLEAN_OR_HPP

// local headers
#include <warbler/syntax/expression/boolean_and_expression.hpp>

namespace warbler::syntax
{
	class BooleanOrExpression : public Expression
	{
	private:

		Ptr<Expression> _lhs;
		Array<Ptr<Expression>> _rhs;

	public:

		BooleanOrExpression(Ptr<Expression>&& lhs, Array<Ptr<Expression>>&& rhs);

		static Result<Ptr<Expression>> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;
	};
}
#endif
