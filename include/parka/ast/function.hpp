#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/prototype.hpp"
#include "parka/ast/identifier.hpp"
#include "parka/ast/qualified_identifier.hpp"
#include "parka/node/entity.hpp"
#include "parka/node/entity_id.hpp"
#include "parka/type/type.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/type_annotation.hpp"

#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/string.hpp"

class Function : public Entity
{
	Prototype _prototype;
	ExpressionId _body;
	// Validation
	Optional<EntityId> _packageId;
	Array<EntityId> _localSymbols;
	Array<usize> _blocks;

	Function(Prototype&& prototype, ExpressionId&& body) :
	_prototype(std::move(prototype)),
	_body(std::move(body))
	{}

public:

	Function(Function&&) = default;
	Function(const Function&) = delete;
	~Function() = default;

	static Optional<EntityId> parse(Token& token);

	bool declare(const EntityId& entityId);
	bool validate(const EntityId& packageId);

	void pushBlock();
	void popBlock();

	Optional<EntityId> resolve(const Identifier& identifier);
	Optional<EntityId> resolve(const QualifiedIdentifier& identifier);
	
	const String& identifier() const { return _prototype.identifier().text(); }
	EntityType type() const { return EntityType::Function; }
	const auto& body() const { return _body; }
	Type getReturnType() const;
};

#endif
