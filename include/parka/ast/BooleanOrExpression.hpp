#ifndef PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_OR_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class BooleanOrExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;

	public:

		BooleanOrExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs) :
		ExpressionAst(ExpressionType::BooleanOr),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BooleanOrExpressionAst(BooleanOrExpressionAst&&) = default;
		BooleanOrExpressionAst(const BooleanOrExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
