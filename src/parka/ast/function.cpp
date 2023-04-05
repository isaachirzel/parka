#include "parka/ast/function.hpp"
#include "parka/ast/block.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/type_annotation.hpp"
#include "parka/node/entity_id.hpp"
#include "parka/node/node_bank.hpp"
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

Optional<EntityId> Function::parse(Token& token)
{
	auto prototype = Prototype::parse(token);

	if (!prototype)
		return {};

	auto body = parseBody(token);

	if (!body)
		return {};

	auto function = Function(*prototype, *body);
	auto id = NodeBank::add(std::move(function));

	return id;
}

bool Function::declare(const EntityId& entityId)
{
	// TODO: Implement LocalEntity to get common functionality
	
	auto& entity = NodeBank::get(entityId);
	const auto& identifier = entity.identifier();

	print("Declaring $ $", entityId.type(), identifier);

	auto blockIndex = _blocks.length() > 0
		? _blocks.back()
		: 0;

	for (auto i = blockIndex; i < _localSymbols.length(); ++i)
	{
		auto previousId = _localSymbols[i];
		auto& previous = NodeBank::get(previousId);

		if (entity.identifier() == previous.identifier())
		{
			// TODO: Show previous declaration
			// TODO: Token highlights
			printError("`$` is already declared in this block.", identifier);

			return false;
		}
	}

	_localSymbols.push(EntityId(entityId));

	return true;
}

bool Function::validate(const EntityId& packageId)
{
	auto success = true;
	auto functionId = NodeBank::getId(*this);
	
	_packageId = packageId;

	if (!_prototype.validate(functionId))
		success = false;

	auto& expression = NodeBank::get(_body);

	if (!expression.validate(functionId))
		success = false;

	// TODO: Validate return type

	return success;
}

Type Function::getReturnType() const
{
	exitNotImplemented(here());
	// auto returnType = _returnType
	// 	? _returnType->type()
	// 	: voidType;

	// return returnType;
}
Optional<EntityId> Function::resolve(const Identifier& identifier)
{
	auto i = _localSymbols.length();

	while (i > 0)
	{
		i -= 1;

		auto id = _localSymbols[i];
		auto& entity = NodeBank::get(id);

		if (entity.identifier() == identifier.text())
			return id;
	}

	auto& package = NodeBank::getPackage(*_packageId);
	auto result = package.findGlobal(identifier);

	if (!result)
		printError(identifier.token(), "Unable to find $ in this scope.", identifier);

	return result;
}

Optional<EntityId> Function::resolve(const QualifiedIdentifier& identifier)
{
	if (identifier.isAbsolute() || identifier.length() > 1)
	{
		auto& package = NodeBank::getPackage(*_packageId);
		auto result = package.resolve(identifier);
	}

	auto result = resolve(identifier[0]);

	return result;
}

void Function::pushBlock()
{
	auto offset = _localSymbols.length();

	_blocks.push(offset);
}

void Function::popBlock()
{
	_localSymbols.reserve(_blocks.back());
	_blocks.pop();
}
