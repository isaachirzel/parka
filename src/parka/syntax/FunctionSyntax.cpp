#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> parseBody(Token& token)
	{
		if (token.type() == TokenType::DoubleArrow)
		{
			token.increment();

			auto body = ExpressionSyntax::parse(token);

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
			return BlockSyntax::parse(token);
		
		printParseError(token, "function body", "Functions require a body.");

		return {};
	}

	Optional<EntityId> FunctionSyntax::parse(Token& token)
	{
		auto prototype = PrototypeSyntax::parse(token);

		if (!prototype)
			return {};

		auto body = parseBody(token);

		if (!body)
			return {};

		auto function = FunctionSyntax(*prototype, *body);
		auto id = Storage::add(std::move(function));

		return id;
	}

	// bool FunctionSyntax::declare(const EntityId& entityId)
	// {
	// 	// TODO: Implement LocalEntity to get common functionality
		
	// 	auto& entity = Storage::get(entityId);
	// 	const auto& identifier = entity.identifier();

	// 	print("Declaring $ $", entityId.type(), identifier);

	// 	auto blockIndex = _blocks.length() > 0
	// 		? _blocks.back()
	// 		: 0;

	// 	for (auto i = blockIndex; i < _localSymbols.length(); ++i)
	// 	{
	// 		auto previousId = _localSymbols[i];
	// 		auto& previous = Storage::get(previousId);

	// 		if (entity.identifier() == previous.identifier())
	// 		{
	// 			// TODO: Show previous declaration
	// 			// TODO: Token highlights
	// 			printError("`$` is already declared in this block.", identifier);

	// 			return false;
	// 		}
	// 	}

	// 	_localSymbols.push(EntityId(entityId));

	// 	return true;
	// }

	// bool FunctionSyntax::validate(const EntityId& packageId)
	// {
	// 	auto success = true;
	// 	auto functionId = Storage::getId(*this);
		
	// 	_packageId = packageId;

	// 	if (!_prototype.validate(functionId))
	// 		success = false;

	// 	auto& expression = Storage::get(_body);

	// 	if (!expression.validate(functionId))
	// 		success = false;

	// 	// TODO: Validate return type

	// 	return success;
	// }

	// Type FunctionSyntax::getReturnType() const
	// {
	// 	exitNotImplemented(here());
	// 	// auto returnType = _returnType
	// 	// 	? _returnType->type()
	// 	// 	: voidType;

	// 	// return returnType;
	// }
	// Optional<EntityId> FunctionSyntax::resolve(const Identifier& identifier)
	// {
	// 	auto i = _localSymbols.length();

	// 	while (i > 0)
	// 	{
	// 		i -= 1;

	// 		auto id = _localSymbols[i];
	// 		auto& entity = Storage::get(id);

	// 		if (entity.identifier() == identifier.text())
	// 			return id;
	// 	}

	// 	auto& package = Storage::getPackage(*_packageId);
	// 	auto result = package.findGlobal(identifier);

	// 	if (!result)
	// 		printError(identifier.token(), "Unable to find $ in this scope.", identifier);

	// 	return result;
	// }

	// Optional<EntityId> FunctionSyntax::resolve(const QualifiedIdentifier& identifier)
	// {
	// 	if (identifier.isAbsolute() || identifier.length() > 1)
	// 	{
	// 		auto& package = Storage::getPackage(*_packageId);
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
