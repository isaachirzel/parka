#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_HPP
#define WARBLER_AST_EXPRESSION_CONDITIONAL_HPP

// local headers
#include <warbler/ast/expression/boolean_or_expression.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
{
	class ConditionalExpression : public Expression
	{
	private: // members

		Ptr<Expression> _lhs;
		Ptr<Expression> _true_case;
		Ptr<Expression> _false_case;

	public: // methods

		ConditionalExpression(Ptr<Expression>&& lhs);
		ConditionalExpression(Ptr<Expression>&& lhs, Ptr<Expression>&& true_case, Ptr<Expression>&& false_case);
		ConditionalExpression(ConditionalExpression&&) = default;
		ConditionalExpression(const ConditionalExpression&) = delete;

		static Result<Ptr<Expression>> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type();
		const Location& location() const;

		ConditionalExpression& operator=(ConditionalExpression&&) = default;
		ConditionalExpression& operator=(const ConditionalExpression&) = delete;
	};
}

#endif
