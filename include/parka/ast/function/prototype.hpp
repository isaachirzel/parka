#ifndef PARKA_AST_FUNCTION_PROTOTYPE_HPP
#define PARKA_AST_FUNCTION_PROTOTYPE_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/type/type_annotation.hpp"

class Prototype
{
	Keyword _keyword;
	Identifier _identifier;
	Array<EntityId> _parameterIds;
	Optional<TypeAnnotation> _returnType;

	Prototype(Keyword&& keyword, Identifier&& identifier, Array<EntityId>&& parameterIds, Optional<TypeAnnotation>&& returnType) :
	_keyword(std::move(keyword)),
	_identifier(std::move(identifier)),
	_parameterIds(std::move(parameterIds)),
	_returnType(std::move(returnType))
	{}

public:

	Prototype(Prototype&&) = default;
	Prototype(const Prototype&) = delete;
	~Prototype() = default;

	static Optional<Prototype> parse(Token& token);

	bool validate(const EntityId& functionId);

	const auto& identifier() const { return _identifier; }
	const auto& parameters() const { return _parameterIds; }
	const auto& returnType() const { return _returnType; }
};

#endif
