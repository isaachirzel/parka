#ifndef PARKA_AST_STATMENT_EXPRESSION_HPP
#define PARKA_AST_STATMENT_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/parser/Token.hpp"

namespace parka::ast
{
	class ExpressionStatementAst : public StatementAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;

	public:

		ExpressionStatementAst(const Snippet& snippet, ExpressionAst& expression) :
		StatementAst(StatementType::Expression),
		_snippet(snippet),
		_expression(expression)
		{}
		ExpressionStatementAst(ExpressionStatementAst&&) = default;
		ExpressionStatementAst(const ExpressionStatementAst&) = delete;

		static StatementAst *parse(Token& token);
		ir::StatementIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
	};
}

#endif
