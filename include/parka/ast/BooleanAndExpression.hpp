#ifndef PARKA_AST_EXPRESSION_BOOLEAN_AND_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_BOOLEAN_AND_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class BooleanAndExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;

	public:

		BooleanAndExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs) :
		ExpressionAst(ExpressionType::BooleanAnd),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BooleanAndExpressionAst(BooleanAndExpressionAst&&) = default;
		BooleanAndExpressionAst(const BooleanAndExpressionAst&) = delete;
		
		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
