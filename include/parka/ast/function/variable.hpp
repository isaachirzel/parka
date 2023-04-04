#ifndef PARKA_AST_VARIABLE_HPP
#define PARKA_AST_VARIABLE_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/entity_id.hpp"

class Variable : public Entity
{
	Identifier _identifier;
	Optional<TypeAnnotation> _annotation;
	bool _isMutable;

	Variable(Identifier&& identifier, bool isMutable, Optional<TypeAnnotation> annotation) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

public:

	static Optional<EntityId> parse(Token& token);

	bool validate(const EntityId& functionId);

	const String& identifier() const { return _identifier.text(); }
	EntityType type() const { return EntityType::Variable; }
	bool isExplicitlyTyped() const { return _annotation.hasValue(); }
	const auto& annotation() const { return *_annotation; }
	const auto& isMutable() const { return _isMutable; }
};

#endif
