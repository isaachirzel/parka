#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/typed_entity.hpp"
#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/symbol/entity.hpp"



class Parameter : public TypedEntity
{
	Identifier _identifier;
	TypeAnnotation _annotation;
	bool _isMutable;
	Optional<Type> _type;

	Parameter(Identifier&& identifier, TypeAnnotation&& annotation, bool isMutable) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

public:

	Parameter(Parameter&&) = default;
	Parameter(const Parameter&) = delete;
	~Parameter() = default;

	static Optional<EntityId> parse(Token& token);

	bool validate(const EntityId& functionId);

	Optional<Type> getType() const;
	const String& identifier() const { return _identifier.text(); }
	EntityType type() const { return EntityType::Parameter; }

	const auto& annotation() const { return _annotation; }
	const auto& isMutable() const { return _isMutable; }
};

#endif
