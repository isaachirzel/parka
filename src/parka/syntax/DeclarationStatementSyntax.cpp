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
			return nullptr;

		if (token.type() != TokenType::Assign)
		{
			log::parseError(token, "expected '=' after declaration");
			return nullptr;
		}

		token.increment();

		auto value = ExpressionSyntax::parse(token);

		if (!value)
			return nullptr;

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';'", "DeclarationStatementSyntax statements need to be ended with a ';'.");
			return nullptr;
		}

		token.increment();

		auto *syntax = new DeclarationStatementSyntax(*variable, *value);

		return syntax;
	}

	StatementContext *DeclarationStatementSyntax::validate(SymbolTable& symbolTable)
	{
		auto *value = _value.validate(symbolTable);
		auto *variable = _variable.validate(symbolTable, value);

		if (!variable || !value)
			return nullptr;

		log::notImplemented(here());
	}
}
