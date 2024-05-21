#ifndef PARKA_AST_CAST_EXPRESSION_AST_HPP
#define PARKA_AST_CAST_EXPRESSION_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"

namespace parka::ast
{
	class CastExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;
		QualifiedIdentifierAst _typeIdentifier;

	public:

		CastExpressionAst(const Snippet& snippet, ExpressionAst& expression, QualifiedIdentifierAst&& typeIdentifier):
			ExpressionAst(ExpressionType::Cast),
			_snippet(snippet),
			_expression(expression),
			_typeIdentifier(std::move(typeIdentifier))
		{}
		CastExpressionAst(CastExpressionAst&&) = default;
		CastExpressionAst(const CastExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
		const auto& typeIdentifier() const { return _typeIdentifier; }
	};
}

#endif
