#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<StatementId> DeclarationStatementSyntax::parse(Token& token)
	{
		auto variableId = VariableSyntax::parse(token);

		if (!variableId)
			return {};

		if (token.type() != TokenType::Assign)
		{
			printParseError(token, "expected '=' after declaration", NULL);
			return {};
		}

		token.increment();

		auto value = ExpressionSyntax::parse(token);

		if (!value)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			printParseError(token, "';'", "DeclarationStatementSyntax statements need to be ended with a ';'.");
			return {};
		}

		token.increment();

		auto declaration = DeclarationStatementSyntax(*variableId, *value);
		auto id = Storage::add(std::move(declaration));

		return id;
	}

	// bool DeclarationStatementSyntax::validate(const EntityId& functionId)
	// {
	// 	auto success = true;
	// 	auto& function = Storage::getFunction(functionId);
	// 	auto& variable = Storage::getVariable(_variableId);
	// 	auto& value = Storage::get(_value);
		
	// 	if (!value.validate(functionId))
	// 		success = false;

	// 	if (!variable.validate(functionId))
	// 		success = false;

	// 	// The declaration comes after expression validation so it can't access the declaration
	// 	if (!function.declare(_variableId))
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
	// 			printError("Unable to initialize $ with $", *variableType, *valueType);
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
