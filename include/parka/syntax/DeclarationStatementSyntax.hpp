#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class DeclarationStatementSyntax : public StatementSyntax
	{
		EntitySyntaxId _variableId;
		ExpressionSyntaxId _value;

		DeclarationStatementSyntax(EntitySyntaxId variableId, ExpressionSyntaxId value) :
		_variableId(variableId),
		_value(value)
		{}

	public:

		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;

		static Optional<StatementSyntaxId> parse(Token& token);

		StatementType statementType() const { return StatementType::Declaration; }

		const auto& variableId() const { return _variableId; }
		const auto& value() const { return _value; }
	};
}

#endif
