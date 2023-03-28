#include "parka/ast/function/function.hpp"
#include "parka/ast/expression/block.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> parseBody(Token& token)
{
	if (token.type() == TokenType::DoubleArrow)
	{
		token.increment();

		auto body = Expression::parse(token);

		if (!body)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			printParseError(token, "';'", "Inline function bodies need to be ended with ';'.");
			return {};
		}

		token.increment();

		return body;
	}

	if (token.type() == TokenType::LeftBrace)
		return Block::parse(token);
	
	printParseError(token, "function body", "Functions require a body.");

	return {};
}

Optional<EntityId> Function::parse(Token& token, const String& package)
{
	auto prototype = Prototype::parse(token);

	if (!prototype)
		return {};

	auto symbol = package + "::" + prototype.value().name().text();
	auto body = parseBody(token);

	if (!body)
		return {};

	auto function = Function(std::move(symbol), prototype.unwrap(), body.unwrap());
	auto id = NodeBank::add(std::move(function));

	return id;
}

bool Function::validate(SymbolTable& symbols)
{
	exitNotImplemented(here());
	// bool success = true;

	// for (auto parameterId : _parameterIds)
	// {
	// 	auto& parameter = (Parameter&)symbols.getEntity({ EntityType::Parameter, parameterId });

	// 	if (!parameter.validate(symbols))
	// 		success = false;
	// }

	// if (_returnType)
	// {
	// 	_returnType.value().validate(const Scope &packageScope)
	// }

	// if (node->hasReturnType
	// 		&& !validateTypeAnnotation(&node->returnType, symbols->packageScope))
	// 	success = false;

	// if (!validateExpression(&node->body, symbols))
	// 	success = false;

	// if (success)
	// {
	// 	const Type *returnType = functionGetReturnType(node);
	// 	Type bodyType;
		
	// 	if (!expressionGetType(&bodyType, &node->body, returnType))
	// 		return false;

	// 	if (!typeCanConvert(returnType, &bodyType))
	// 	{
	// 		auto returnTypeName = typeGetName(returnType);
	// 		auto bodyTypeName = typeGetName(&bodyType);
	// 		// TODO: handle token like so: Token token = tokenFromExpression(&node->body);

	// 		printError("Expected `$`, got `$`.", returnTypeName, bodyTypeName);
	// 		printTokenNote(&node->returnType.token, "Function return type here.");

	// 		success = false;
	// 	}
	// }	

	// return success;
}

Type Function::getReturnType() const
{
	exitNotImplemented(here());
	// auto returnType = _returnType
	// 	? _returnType.value().type()
	// 	: voidType;

	// return returnType;
}
