#ifndef PARKA_SYNTAX_EXPRESSION_IDENTIFIER_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_IDENTIFIER_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/Token.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class IdentifierExpressionContext : public ExpressionContext
	{
		EntityContext& _entity;

	public:

		IdentifierExpressionContext(EntityContext& entity);
		IdentifierExpressionContext(IdentifierExpressionContext&&) = default;
		IdentifierExpressionContext(const IdentifierExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Identifier; }
		const ValueType& valueType() const;
	};

	class IdentifierExpressionSyntax : public ExpressionSyntax
	{
		QualifiedIdentifier _identifier;

	public:

		IdentifierExpressionSyntax(QualifiedIdentifier&& identifier) :
		_identifier(std::move(identifier))
		{}
		IdentifierExpressionSyntax(IdentifierExpressionSyntax&&) = default;
		IdentifierExpressionSyntax(const IdentifierExpressionSyntax&) = delete;

		static IdentifierExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Identifier; }
		const Snippet& snippet() const { return _identifier.snippet(); }

		const auto& identifier() const { return _identifier; }
	};
}

#endif
