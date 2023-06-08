#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *parseBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = ExpressionSyntax::parse(token);

			if (!body)
				return {};

			if (token.type() != TokenType::Semicolon)
			{
				log::parseError(token, "';'", "Inline function bodies need to be ended with ';'.");
				return {};
			}

			token.increment();

			return body;
		}

		if (token.type() == TokenType::LeftBrace)
			return BlockSyntax::parse(token);
		
		log::parseError(token, "function body", "Functions require a body.");

		return {};
	}

	const FunctionSyntax *FunctionSyntax::parse(Token& token)
	{
		auto prototype = PrototypeSyntax::parse(token);

		if (!prototype)
			return {};

		auto body = parseBody(token);

		if (!body)
			return {};

		auto function = FunctionSyntax(*prototype, *body);
		auto& syntax = EntitySyntax::create(std::move(function));

		return (const FunctionSyntax*)&syntax;
	}

	// ValueType FunctionSyntax::getReturnType() const
	// {
	// 	log::notImplemented(here());
	// 	// auto returnType = _returnType
	// 	// 	? _returnType->type()
	// 	// 	: voidType;

	// 	// return returnType;
	// }
	// EntitySyntax *FunctionSyntax::resolve(const Identifier& identifier)
	// {
	// 	auto i = _localSymbols.length();

	// 	while (i > 0)
	// 	{
	// 		i -= 1;

	// 		auto id = _localSymbols[i];
	// 		auto& entity = SyntaxRepository::get(id);

	// 		if (entity.identifier() == identifier.text())
	// 			return id;
	// 	}

	// 	auto& package = SyntaxRepository::getPackage(*_package);
	// 	auto result = package.findGlobal(identifier);

	// 	if (!result)
	// 		log::erroridentifier.token(), "Unable to find $ in this scope.", identifier);

	// 	return result;
	// }

	// EntitySyntax *FunctionSyntax::resolve(const QualifiedIdentifier& identifier)
	// {
	// 	if (identifier.isAbsolute() || identifier.length() > 1)
	// 	{
	// 		auto& package = SyntaxRepository::getPackage(*_package);
	// 		auto result = package.resolve(identifier);
	// 	}

	// 	auto result = resolve(identifier[0]);

	// 	return result;
	// }

	// void FunctionSyntax::pushBlock()
	// {
	// 	auto offset = _localSymbols.length();

	// 	_blocks.push(offset);
	// }

	// void FunctionSyntax::popBlock()
	// {
	// 	_localSymbols.reserve(_blocks.back());
	// 	_blocks.pop();
	// }
}
