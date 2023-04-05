#ifndef PARKA_AST_VARIABLE_HPP
#define PARKA_AST_VARIABLE_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/type_annotation.hpp"
#include "parka/node/entity.hpp"
#include "parka/node/entity_id.hpp"
#include "parka/node/expression_id.hpp"
#include "parka/node/typed_entity.hpp"
#include "parka/util/ref.hpp"

class Variable : public TypedEntity
{
	Identifier _identifier;
	Optional<TypeAnnotation> _annotation;
	bool _isMutable;
	// Validation
	Optional<Type> _type;
	bool _isValidated;

	Variable(Identifier&& identifier, bool isMutable, Optional<TypeAnnotation> annotation) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

public:

	static Optional<EntityId> parse(Token& token);

	bool validate(const EntityId& functionId);
	void setType(const Type& type) { _type = type; }
	Optional<Type> getType() const;

	const String& identifier() const { return _identifier.text(); }
	EntityType type() const { return EntityType::Variable; }
	const auto& isExplicitlyTyped() const { return _annotation.hasValue(); }
	const auto& annotation() const { return *_annotation; }
	const auto& isMutable() const { return _isMutable; }
};

#endif
