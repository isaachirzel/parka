#ifndef PARKA_AST_VARIABLE_HPP
#define PARKA_AST_VARIABLE_HPP

#include "parka/ast/type_annotation.hpp"
#include "parka/symbol_table.hpp"

class Variable : public Entity
{
	Token _name;
	String _symbol;
	Optional<TypeAnnotation> _annotation;
	bool _isMutable;

public:

	static Variable parse(Token& token);

	bool validate(SymbolTable& localTable);

	Token token() const { return _name; }
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Variable; }

	const auto& name() const { return _name; }
	bool isExplicitlyTyped() const { return _annotation.hasValue(); }
	const auto& annotation() const { return _annotation.value(); }
	const auto& isMutable() const { return _isMutable; }
};

#endif
