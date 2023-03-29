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
	auto name = prototype->name().text();
	auto symbol = package + "::" + name;
	auto body = parseBody(token);

	if (!body)
		return {};

	auto function = Function(std::move(symbol), prototype.unwrap(), body.unwrap());
	auto id = NodeBank::add(std::move(function));

	return id;
}

bool Function::validate(SymbolTable& symbols)
{
	auto success = true;

	if (!_prototype.validate(symbols))
		success = false;

	auto& expression = NodeBank::get(_body);

	if (!expression.validate(symbols))
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
