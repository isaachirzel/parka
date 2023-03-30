#include "parka/ast/function/parameter.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Parameter::parse(Token& token)
{
	auto isMutable = false;

	if (token.type() == TokenType::KeywordMut)
	{
		isMutable = true;
		token.increment();
	}

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "parameter name");
		return {};
	}

	auto name = token;

	token.increment();

	if (token.type() != TokenType::Colon)
	{
		printParseError(token, "':'", "Parameters require a type annotation.");
		return {};
	}

	token.increment();

	auto annotation = TypeAnnotation::parse(token);

	if (!annotation)
		return {};
	
	auto parameter = Parameter(name, name.text(), annotation.unwrap(), isMutable);
	auto id = NodeBank::add(std::move(parameter));
	
	return id;
}

bool Parameter::validate(SymbolTable& symbols)
{
	auto success = true;

	if (!_annotation.validate(symbols))
		success = false;

	return success;
}
