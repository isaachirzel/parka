#include "parka/ast/function/parameter.hpp"
#include "parka/ast/identifier.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Parameter::parse(Token& token)
{
	auto mutKeyword = Keyword::parseMut(token);
	auto isMutable = !!mutKeyword;

	auto identifier = Identifier::parse(token);

	if (!identifier)
		return {};

	if (token.type() != TokenType::Colon)
	{
		printParseError(token, "':'", "Parameters require a type annotation.");
		return {};
	}

	token.increment();

	auto annotation = TypeAnnotation::parse(token);

	if (!annotation)
		return {};
	
	auto parameter = Parameter(identifier.unwrap(), annotation.unwrap(), isMutable);
	auto id = NodeBank::add(std::move(parameter));
	
	return id;
}

bool Parameter::validate(const EntityId& functionId)
{
	auto success = true;

	if (!_annotation.validate(functionId))
		success = false;

	return success;
}
