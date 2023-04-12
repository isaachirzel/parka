#include "parka/syntax/PrototypeSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<Array<EntitySyntaxId>> parseParameterList(Token& token)
	{
		if (token.type() != TokenType::LeftParenthesis)
		{
			printParseError(token, "'(' after function name");
			return {};
		}

		token.increment();

		auto parameters = Array<EntitySyntaxId>();

		if (token.type() == TokenType::RightParenthesis)
		{
			token.increment();

			return parameters;
		}
		
		while (true)
		{
			auto parameterId = ParameterSyntax::parse(token);

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

	Optional<TypeAnnotationSyntax> parseReturnType(Token& token)
	{
		if (token.type() != TokenType::SingleArrow)
			return {};

		token.increment();
		
		auto returnType = TypeAnnotationSyntax::parse(token);

		return returnType;
	}

	Optional<PrototypeSyntax> PrototypeSyntax::parse(Token& token)
	{
		auto keyword = KeywordSyntax::parseFunction(token);

		if (!keyword)
			return {};

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		auto parameters = parseParameterList(token);
		
		if (!parameters)
			return {};

		auto returnType = parseReturnType(token);
		auto prototype = PrototypeSyntax(*keyword, *identifier, *parameters, std::move(returnType));

		return prototype;
	}

	// bool PrototypeSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto success = true;
	// 	auto& function = SyntaxRepository::getFunction(functionId);

	// 	for (auto parameterId : _parameterIds)
	// 	{
	// 		auto& parameter = SyntaxRepository::getParameter(parameterId);

	// 		if (!parameter.validate(functionId))
	// 			success = false;

	// 		if (!function.declare(parameterId))
	// 			success = false;
	// 	}

	// 	if (_returnType && !_returnType->validate(functionId))
	// 		success = false;

	// 	return success;
	// }
}
