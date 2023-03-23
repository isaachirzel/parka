#ifndef PARKA_LOCAL_ENTITY_TABLE_HPP
#define PARKA_LOCAL_ENTITY_TABLE_HPP

#include "parka/scope.hpp"
#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/ref.hpp"

class Function;

struct BlockInfo
{
	struct Block *node;
	usize offset;
};

class LocalEntityTable
{
	Array<EntityContext> _entities;
	Array<BlockInfo> _blocks;
	Scope _packageScope;
	// const Function *_function; Why does it need this?

public:

	LocalEntityTable() :
	_packageScope(10)
	{}
	LocalEntityTable(LocalEntityTable&&) = default;
	LocalEntityTable(const LocalEntityTable&) = delete;
	~LocalEntityTable() = default;

	// Maybe just pass the function symbol? or the package symbol and it will construct the scope?
	void setFunction(const Function& function); // This will reset the table

	Ref<EntityContext> resolve(const Token& token);
	Ref<EntityContext> resolve(const String& identifier);
	void pushBlock(Block& block);
	void popBlock();
	Block& getCurrentBlock();
	bool declare(EntityId id);

	const auto& symbols() const { return _entities; }
	const auto& blocks() const { return _blocks; }
	// const auto& function() const { return _function; }
	// const auto& packageScope() const { return _packageScope; }
};

#endif
