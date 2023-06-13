#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	DeclarationStatementSyntax::DeclarationStatementSyntax(VariableSyntax& variable, ExpressionSyntax& value) :
	_variable(variable),
	_value(value)
	{}

	StatementSyntax *DeclarationStatementSyntax::parse(Token& token)
	{
		auto *variable = VariableSyntax::parse(token);

		if (!variable)
			return {};

		if (token.type() != TokenType::Assign)
		{
			log::parseError(token, "expected '=' after declaration");
			return {};
		}

		token.increment();

		auto value = ExpressionSyntax::parse(token);

		if (!value)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';'", "DeclarationStatementSyntax statements need to be ended with a ';'.");
			return {};
		}

		token.increment();

		auto *syntax = new DeclarationStatementSyntax(*variable, *value);

		return syntax;
	}

	StatementContext *DeclarationStatementSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
