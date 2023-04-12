#ifndef PARKA_SYNTAX_EXPRESSION_IDENTIFIER_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_IDENTIFIER_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/Token.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class IdentifierExpressionSyntax : public ExpressionSyntax
	{
		QualifiedIdentifier _identifier;
		Optional<EntitySyntaxId> _entityId;

		IdentifierExpressionSyntax(QualifiedIdentifier&& identifier) :
		_identifier(std::move(identifier)),
		_entityId()
		{}

	public:

		IdentifierExpressionSyntax(IdentifierExpressionSyntax&&) = default;
		IdentifierExpressionSyntax(const IdentifierExpressionSyntax&) = delete;
		~IdentifierExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& identifier() const { return _identifier; }
	};
}

#endif