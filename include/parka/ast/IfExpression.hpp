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

		IfExpressionAst(const Snippet& snippet) :
		ExpressionAst(ExpressionType::If),
		_snippet(snippet)
		{}

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
