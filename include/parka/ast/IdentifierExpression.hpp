#ifndef PARKA_AST_EXPRESSION_IDENTIFIER_HPP
#define PARKA_AST_EXPRESSION_IDENTIFIER_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"

namespace parka::ast
{
	class IdentifierExpressionAst: public ExpressionAst
	{
		QualifiedIdentifier _identifier;

	public:

		IdentifierExpressionAst(QualifiedIdentifier&& identifier):
		ExpressionAst(ExpressionType::Identifier),
		_identifier(std::move(identifier))
		{}
		IdentifierExpressionAst(IdentifierExpressionAst&&) = default;
		IdentifierExpressionAst(const IdentifierExpressionAst&) = delete;

		const Snippet& snippet() const { return _identifier.snippet(); }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
