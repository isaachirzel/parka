#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class DeclarationStatementSyntax : public StatementSyntax
	{
		VariableSyntax& _variable;
		ExpressionSyntax& _value;

	public:

		DeclarationStatementSyntax(VariableSyntax& variable, ExpressionSyntax& value);
		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Declaration; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
