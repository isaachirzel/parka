#ifndef PARKA_AST_FUNCTION_PROTOTYPE_HPP
#define PARKA_AST_FUNCTION_PROTOTYPE_HPP

#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/local_symbol_table.hpp"

class Prototype
{
	Token _name;
	Array<EntityId> _parameterIds;
	Optional<TypeAnnotation> _returnType;

	Prototype(const Token& name, Array<EntityId>&& parameterIds, Optional<TypeAnnotation>&& returnType = {}) :
	_name(name),
	_parameterIds(std::move(parameterIds)),
	_returnType(std::move(returnType))
	{}

public:

	Prototype(Prototype&&) = default;
	Prototype(const Prototype&) = delete;
	~Prototype() = default;

	static Optional<Prototype> parse(Token& token);

	bool validate(LocalSymbolTable& symbols);

	const auto& name() const { return _name; }
	const auto& parameters() const { return _parameterIds; }
	const auto& returnType() const { return _returnType; }
};

#endif
