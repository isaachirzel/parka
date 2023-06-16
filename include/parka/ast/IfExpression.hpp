#ifndef PARKA_AST_IF_EXPRESSION_HPP
#define PARKA_AST_IF_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"

// TODO: Consider merging this with conditional expression

namespace parka::ast
{
	class IfExpressionAst : public ExpressionAst
	{
		Snippet _snippet;

	public:

		static ExpressionAst	*parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::If; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
