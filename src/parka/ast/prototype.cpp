#include "parka/ast/prototype.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/parameter.hpp"
#include "parka/ast/identifier.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/type_annotation.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/type/type.hpp"
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

		parameters.push(*parameterId);

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

Optional<TypeAnnotation> parseReturnType(Token& token)
{
	if (token.type() != TokenType::SingleArrow)
		return {};

	token.increment();
	
	auto returnType = TypeAnnotation::parse(token);

	return returnType;
}

Optional<Prototype> Prototype::parse(Token& token)
{
	auto keyword = Keyword::parseFunction(token);

	if (!keyword)
		return {};

	auto identifier = Identifier::parse(token);

	if (!identifier)
		return {};

	auto parameters = parseParameterList(token);
	
	if (!parameters)
		return {};

	auto returnType = parseReturnType(token);
	auto prototype = Prototype(*keyword, *identifier, *parameters, std::move(returnType));

	return prototype;
}

bool Prototype::validate(const EntityId& functionId)
{
	auto success = true;
	auto& function = NodeBank::getFunction(functionId);

	for (auto parameterId : _parameterIds)
	{
		auto& parameter = NodeBank::getParameter(parameterId);

		if (!parameter.validate(functionId))
			success = false;

		if (!function.declare(parameterId))
			success = false;
	}

	if (_returnType && !_returnType->validate(functionId))
		success = false;

	return success;
}
