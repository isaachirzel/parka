#ifndef PARKA_AST_EXPRESSION_IDENTIFIER_HPP
#define PARKA_AST_EXPRESSION_IDENTIFIER_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"

namespace parka::ast
{
	class IdentifierExpressionAst: public ExpressionAst
	{
		QualifiedIdentifierAst _identifier;

	public:

		IdentifierExpressionAst(QualifiedIdentifierAst&& identifier):
		ExpressionAst(ExpressionType::Identifier),
		_identifier(std::move(identifier))
		{}
		IdentifierExpressionAst(IdentifierExpressionAst&&) = default;
		IdentifierExpressionAst(const IdentifierExpressionAst&) = delete;

		const fs::FileSnippet& snippet() const { return _identifier.snippet(); }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
