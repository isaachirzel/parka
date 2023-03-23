#ifndef PARKA_GLOBAL_ENTITY_TABLE_HPP
#define PARKA_GLOBAL_ENTITY_TABLE_HPP

#include "parka/entity_context.hpp"
#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/pool.hpp"
#include "parka/util/ref.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"
#include "parka/util/primitives.hpp"
#include "parka/scope.hpp"

#include <cassert>

class Function;
class Package;
class Parameter;
class Primitive;
class Variable;
class Struct;

class GlobalEntityTable
{
	Table<EntityContext> _entities;
	// Pool<Package> _packages;
	// Pool<Struct> _structs;
	// Pool<Function> _functions;
	// Pool<Variable> _variables;
	// Pool<Parameter> _parameters;

public:

	GlobalEntityTable();
	GlobalEntityTable(GlobalEntityTable&&) = default;
	GlobalEntityTable(const GlobalEntityTable&) = delete;
	~GlobalEntityTable() = default;

	EntityId addEntity(Entity& entity);
	bool declare(EntityId id);
	void setScopeFromSymbol(const String& symbol);
	const String& getSymbolKey(EntityType type, usize index) const;
	Ref<EntityContext> resolve(const Scope& scope, const Token& token);
	EntityContext& getEntityContext(usize index);
	Entity& getEntity(EntityId id);
	// Package& getPackage(usize index) { assert(index < _packages.count()); return _packages[index]; }
	// Variable& getVariable(usize index) { assert(index < _variables.count()); return _variables[index]; }
	// Parameter& getParameter(usize index) { assert(index < _parameters.count()); return _parameters[index]; }
	// Function& getFunction(usize index) { assert(index < _functions.count()); return _functions[index]; }
	// Struct& getStruct(usize index) { assert(index < _structs.count()); return _structs[index]; }
	// Primitive& getPrimitive(usize index) { assert(index < primitives.size()); return primitives[index]; }

	// View<Package> packages() { return _packages.items(); }
	// View<Struct> structs() { return _structs.items(); }
	// View<Function> functions() { return _functions.items(); }
	// View<Parameter> parameters() { return _parameters.items(); }
	// View<Variable> variables() { return _variables.items(); }
};

#endif
