#include "parka/syntax/PrototypeSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/type/ValueType.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<Array<const ParameterSyntax*>> parseParameterList(Token& token)
	{
		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' after function name");
			return {};
		}

		token.increment();

		auto parameters = Array<const ParameterSyntax*>();

		if (token.type() == TokenType::RightParenthesis)
		{
			token.increment();

			return parameters;
		}
		
		while (true)
		{
			auto parameter = ParameterSyntax::parse(token);

			if (!parameter) // TODO: Attempt to fast forward to parameter
				return {};

			parameters.push(parameter);

			if (token.type() == TokenType::Comma)
			{
				token.increment();
				continue;
			}

			break;
		}

		if (token.type() != TokenType::RightParenthesis)
		{
			log::parseError(token, "')'", "Invalid tokens in parameter list");
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

	// bool PrototypeSyntax::validate(const EntitySyntax& function)
	// {
	// 	auto success = true;
	// 	auto& function = SyntaxRepository::getFunction(function);

	// 	for (auto parameter : _parameters)
	// 	{
	// 		auto& parameter = SyntaxRepository::getParameter(parameter);

	// 		if (!parameter.validate(function))
	// 			success = false;

	// 		if (!function.declare(parameter))
	// 			success = false;
	// 	}

	// 	if (_returnType && !_returnType->validate(function))
	// 		success = false;

	// 	return success;
	// }
}
