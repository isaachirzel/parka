#include "parka/ast/function/variable.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Variable::parse(Token& token)
{
	// TODO: Variable mutability
	if (token.type() != TokenType::KeywordVar)
	{
		printParseError(token, "`var` keyword");
		return {};
	}

	token.increment();

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "variable name");
		return {};
	}

	auto name = token;

	token.increment();

	Optional<TypeAnnotation> annotation;

	if (token.type() == TokenType::Colon)
	{
		token.increment();

		annotation = TypeAnnotation::parse(token);

		if (!annotation)
			return {};
	}

	auto variable = Variable(name, false, std::move(annotation));
	auto id = NodeBank::add(std::move(variable));

	return id;
}

bool Variable::validate(LocalSymbolTable& symbols)
{
	auto success = true;
	if (_annotation && !_annotation->validate(symbols))
		success = false;

	return success;
}
