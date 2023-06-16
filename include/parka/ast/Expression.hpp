#ifndef PARKA_AST_EXPRESSION_HPP
#define PARKA_AST_EXPRESSION_HPP

#include "parka/parser/Token.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ir/Expression.hpp"

namespace parka::ast
{
	struct ExpressionAst
	{
		virtual ~ExpressionAst() {}
		virtual ExpressionType expressionType() const = 0;
		virtual const Snippet& snippet() const = 0;
		virtual ir::ExpressionIr *validate(SymbolTable& symbolTable) = 0;
		
		static ExpressionAst *parse(Token& token);
		static ExpressionAst *parseLiteral(Token& token);
		static ExpressionAst *parsePostfixExpression(Token& token);
		static ExpressionAst *parsePrimaryExpression(Token& token);
	};
}

#endif
