#ifndef WARBLER_SYNTAX_EXPRESSION_CONDITIONAL_HPP
#define WARBLER_SYNTAX_EXPRESSION_CONDITIONAL_HPP

// local headers
#include <warbler/syntax/expression/boolean_or_expression.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/util/optional.hpp>

namespace warbler::syntax
{
	struct ConditionalRhs
	{
		Expression _true_case;
		Expression _false_case;

		ConditionalRhs(Expression&& true_case, Expression&& false_case);
	};

	class ConditionalExpression
	{
	private: // members

		Expression _lhs;
		Optional<ConditionalRhs> _rhs;

	public: // methods

		ConditionalExpression(Expression&& lhs);
		ConditionalExpression(Expression&& lhs, Expression&& true_case, Expression&& false_case);
		ConditionalExpression(ConditionalExpression&&) = default;
		ConditionalExpression(const ConditionalExpression&) = delete;

		static Result<Expression> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const lexicon::Token& token() const;

		ConditionalExpression& operator=(ConditionalExpression&&) = default;
		ConditionalExpression& operator=(const ConditionalExpression&) = delete;
	};
}

#endif
