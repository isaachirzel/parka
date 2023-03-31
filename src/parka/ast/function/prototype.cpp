#include "parka/ast/function/prototype.hpp"
#include "parka/ast/function/parameter.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/array.hpp"
#include "parka/util/print.hpp"

Optional<Array<EntityId>> parseParameterList(Token& token)
{
	if (token.type() != TokenType::LeftParenthesis)
	{
		printParseError(token, "'(' after function name");
		return {};
	}

	token.increment();

	auto parameters = Array<EntityId>();

	if (token.type() == TokenType::RightParenthesis)
	{
		token.increment();

		return parameters;
	}
	
	while (true)
	{
		auto parameterId = Parameter::parse(token);

		if (!parameterId) // TODO: Attempt to fast forward to parameter
			return {};

		parameters.push(parameterId.unwrap());

		if (token.type() == TokenType::Comma)
		{
			token.increment();
			continue;
		}

		break;
	}

	if (token.type() != TokenType::RightParenthesis)
	{
		printParseError(token, "')'", "Invalid tokens in parameter list");
		return {};
	}

	token.increment();

	return parameters;
}

Optional<Prototype> Prototype::parse(Token& token)
{
	if (token.type() != TokenType::KeywordFunction)
	{
		printParseError(token, "`function` keyword");
		return {};
	}

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "function name");
		return {};
	}

	auto name = token;

	token.increment();

	auto parameters = parseParameterList(token);
	
	if (!parameters)
		return {};

	if (token.type() != TokenType::SingleArrow)
	{
		auto prototype = Prototype(name, parameters.unwrap());

		return prototype;
	}
	
	token.increment();

	auto returnType = TypeAnnotation::parse(token);

	if (!returnType)
		return {};

	auto prototype = Prototype(name, parameters.unwrap(), std::move(returnType));

	return prototype;
}

bool Prototype::validate(LocalSymbolTable& symbols)
{
	auto success = true;

	for (auto parameterId : _parameterIds)
	{
		auto& parameter = NodeBank::getParameter(parameterId);

		if (!parameter.validate(symbols))
			success = false;

		if (!symbols.declare(parameterId))
			success = false;
	}

	if (_returnType && !_returnType->validate(symbols))
		success = false;

	return success;
}
