#ifndef PARKA_AST_EXPRESSION_BITWISE_AND_HPP
#define PARKA_AST_EXPRESSION_BITWISE_AND_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class BitwiseAndExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;

	public:

		BitwiseAndExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs) :
		ExpressionAst(ExpressionType::BitwiseAnd),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BitwiseAndExpressionAst(BitwiseAndExpressionAst&&) = default;
		BitwiseAndExpressionAst(const BitwiseAndExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
