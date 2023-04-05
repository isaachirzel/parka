#include "parka/ast/function/variable.hpp"
#include "parka/ast/identifier.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EntityId> Variable::parse(Token& token)
{
	// TODO: Variable mutability
	auto keyword = Keyword::parseVar(token);

	if (!keyword)
		return {};	
	
	auto identifier = Identifier::parse(token);

	if (!identifier)
		return {};

	Optional<TypeAnnotation> annotation;

	if (token.type() == TokenType::Colon)
	{
		token.increment();

		annotation = TypeAnnotation::parse(token);

		if (!annotation)
			return {};
	}

	auto variable = Variable(identifier.unwrap(), false, std::move(annotation));
	auto id = NodeBank::add(std::move(variable));

	return id;
}

bool Variable::validate(const EntityId& functionId)
{
	_isValidated = true;

	if (_annotation)
 	{
		if (!_annotation->validate(functionId))
			return false;

		auto type = _annotation->getType();

		_type = type;
	}

	return true;
}

Optional<Type> Variable::getType() const
{
	if (!_type)
		return {};

	return *_type;
}
