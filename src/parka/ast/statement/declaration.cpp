#include "parka/ast/expression/expression.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/function/variable.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<StatementId> Declaration::parse(Token& token)
{
	auto variableId = Variable::parse(token);

	if (!variableId)
		return {};

	if (token.type() != TokenType::Assign)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return {};
	}

	token.increment();

	auto value = Expression::parse(token);

	if (!value)
		return {};

	if (token.type() != TokenType::Semicolon)
	{
		printParseError(token, "';'", "Declaration statements need to be ended with a ';'.");
		return {};
	}

	token.increment();

	auto declaration = Declaration(variableId.unwrap(), value.unwrap());
	auto id = NodeBank::add(std::move(declaration));

	return id;
}

bool Declaration::validate(SymbolTable& symbols)
{
	exitNotImplemented();
	// bool success = true;

	// if (!symbolTableDeclareLocal(symbols, EntityType::Variable, node->variableId))
	// 	success = false;

	// Variable *variable = symbolTableGetVariable(node->variableId);
	
	// if (!validateVariable(variable, symbols))
	// 	success = false;

	// if (!validateExpression(&node->value, symbols))
	// 	success = false;
	
	// if (!success)
	// 	return false;

	// Type *variableType = variable->isExplicitlyTyped
	// 	? &variable->annotation.type
	// 	: NULL;

	// Type expressionType;
	// if (!expressionGetType(&expressionType, &node->value, variableType))
	// 	return false;

	// if (variable->isExplicitlyTyped)
	// {
	// 	Type& variableType = &variable->annotation.type;

	// 	if (!typeCanConvert(variableType, &expressionType))
	// 	{
	// 		auto toTypeName = expressionType.getName();
	// 		auto fromTypeName = variableTypegetName();

	// 		// TODO: Make error highlight entire statement
	// 		printTokenError(&variable->name, "Variable of type `%s` cannot be initialized with value of type `%s`.", toTypeName, fromTypeName);
	// 		deallocate(toTypeName);
	// 		deallocate(fromTypeName);

	// 		return false;
	// 	}
	// }
	// else
	// {
	// 	variable->annotation.type = expressionType;
	// }

	// return true;
}
