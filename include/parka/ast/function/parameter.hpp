#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/type/type_annotation.hpp"
#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/symbol/entity.hpp"



class Parameter : public Entity
{
	Token _name;
	String _symbol;
	TypeAnnotation _annotation;
	bool _isMutable;

	Parameter(const Token& name, String&& symbol, TypeAnnotation&& annotation, bool isMutable) :
	_name(name),
	_symbol(std::move(symbol)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

public:

	Parameter(Parameter&&) = default;
	Parameter(const Parameter&) = delete;
	~Parameter() = default;

	static Optional<EntityId> parse(Token& token);

	bool validate(SymbolTable& symbols);

	Token token() const { return _name; }
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Parameter; }

	const auto& name() const { return _name; }
	const auto& annotation() const { return _annotation; }
	const auto& isMutable() const { return _isMutable; }
};

#endif
