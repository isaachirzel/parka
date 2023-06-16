#ifndef PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP
#define PARKA_AST_EXPRESSION_LITERAL_FLOAT_HPP

#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class FloatLiteralAst : public ExpressionAst
	{
		Snippet _snippet;

	public:

		FloatLiteralAst(const Snippet& snippet) :
		_snippet(snippet)
		{}
		FloatLiteralAst(FloatLiteralAst&&) = default;
		FloatLiteralAst(const FloatLiteralAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		// TODO: Actually determine size of float
		ExpressionType expressionType() const { return ExpressionType::FloatLiteral; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
