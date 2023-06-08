#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class DeclarationStatementSyntax : public StatementSyntax
	{
		const EntitySyntax& _variable;
		const ExpressionSyntax& _value;

		DeclarationStatementSyntax(const EntitySyntax& variable, const ExpressionSyntax& value) :
		_variable(variable),
		_value(value)
		{}

	public:

		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;

		static const StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Declaration; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
