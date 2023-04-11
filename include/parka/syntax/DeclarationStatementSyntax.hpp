#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/util/Primitives.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class DeclarationStatementSyntax : public StatementSyntax
	{
		EntityId _variableId;
		ExpressionId _value;

		DeclarationStatementSyntax(EntityId variableId, ExpressionId value) :
		_variableId(variableId),
		_value(value)
		{}

	public:

		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;
		~DeclarationStatementSyntax() = default;

		static Optional<StatementId> parse(Token& token);

		const auto& variableId() const { return _variableId; }
		const auto& value() const { return _value; }
	};
}

#endif
