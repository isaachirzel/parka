#include "parka/log/Log.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const StatementSyntax *DeclarationStatementSyntax::parse(Token& token)
	{
		auto variable = VariableSyntax::parse(token);

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

		auto statement = DeclarationStatementSyntax(*variable, *value);
		auto& id = StatementSyntax::create(std::move(statement));

		return &id;
	}

	// bool DeclarationStatementSyntax::validate(const EntitySyntax& function)
	// {
	// 	auto success = true;
	// 	auto& function = SyntaxRepository::getFunction(function);
	// 	auto& variable = SyntaxRepository::getVariable(_variable);
	// 	auto& value = SyntaxRepository::get(_value);
		
	// 	if (!value.validate(function))
	// 		success = false;

	// 	if (!variable.validate(function))
	// 		success = false;

	// 	// The declaration comes after expression validation so it can't access the declaration
	// 	if (!function.declare(_variable))
	// 		success = false;

	// 	if (!success)
	// 		return false;

	// 	auto valueType = value.getType();

	// 	if (!valueType)
	// 		return false;

	// 	auto variableType = variable.getType();

	// 	if (variableType)
	// 	{
	// 		if (!valueType->canConvertTo(*variableType))
	// 		{
	// 			log::error("Unable to initialize $ with $", *variableType, *valueType);
	// 			return false;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		variable.setType(*valueType);
	// 	}

	// 	return true;
	// }
}
