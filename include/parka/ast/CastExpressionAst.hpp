#ifndef PARKA_AST_CAST_EXPRESSION_AST_HPP
#define PARKA_AST_CAST_EXPRESSION_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"

namespace parka::ast
{
	class CastExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _expression;
		TypeAnnotationAst _typeAnnotation;

	public:

		CastExpressionAst(const Snippet& snippet, ExpressionAst& expression, TypeAnnotationAst&& typeAnnotation):
			ExpressionAst(ExpressionType::Cast),
			_snippet(snippet),
			_expression(expression),
			_typeAnnotation(std::move(typeAnnotation))
		{}
		CastExpressionAst(CastExpressionAst&&) = default;
		CastExpressionAst(const CastExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
		const auto& typeAnnotation() const { return _typeAnnotation; }
	};
}

#endif
