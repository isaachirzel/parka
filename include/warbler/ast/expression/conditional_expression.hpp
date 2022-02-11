#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_HPP
#define WARBLER_AST_EXPRESSION_CONDITIONAL_HPP

// local headers
#include <warbler/ast/expression/boolean_or_expression.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	struct ConditionalRhs;

	class ConditionalExpression : public Expression
	{
	private: // members

		BooleanOrExpression _lhs;
		Ptr<ConditionalRhs> _rhs;

	public: // methods

		ConditionalExpression(BooleanOrExpression&& lhs);
		ConditionalExpression(BooleanOrExpression&& lhs, ConditionalRhs&& rhs);
		ConditionalExpression(ConditionalExpression&&) = default;
		ConditionalExpression(const ConditionalExpression&) = delete;

		static Result<ConditionalExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		ConditionalExpression& operator=(ConditionalExpression&&) = default;
		ConditionalExpression& operator=(const ConditionalExpression&) = delete;
	};

	struct ConditionalRhs
	{
		BooleanOrExpression true_case;
		ConditionalExpression false_case;

		ConditionalRhs(BooleanOrExpression&& true_case, ConditionalExpression&& false_case);
	};
}

#endif
