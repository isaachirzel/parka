#ifndef PARKA_AST_EXPRESSION_PREFIX_HPP
#define PARKA_AST_EXPRESSION_PREFIX_HPP

#include "parka/enum/PrefixType.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/parser/Token.hpp"

namespace parka::ast
{
	class PrefixExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;
		PrefixType _type;

	public:

		PrefixExpressionAst(const Snippet& snippet, PrefixType type, ExpressionAst& expression) :
		ExpressionAst(ExpressionType::Prefix),
		_snippet(snippet),
		_expression(expression),
		_type(type)
		{}
		PrefixExpressionAst(PrefixExpressionAst&&) = default;
		PrefixExpressionAst(const PrefixExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
