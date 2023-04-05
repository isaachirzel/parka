#ifndef PARKA_AST_MODULE_HPP
#define PARKA_AST_MODULE_HPP

#include "parka/node/entity_id.hpp"
#include "parka/util/array.hpp"
#include "parka/util/file.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/table.hpp"

class Module
{
	String _filepath;
	Array<EntityId> _functionIds;
	Array<EntityId> _structIds;

	Module(String&& filepath, Array<EntityId>&& functionIds, Array<EntityId>&& structIds) :
	_filepath(std::move(filepath)),
	_functionIds(std::move(functionIds)),
	_structIds(std::move(structIds))
	{}

public:

	Module(Module&&) = default;
	Module(const Module&) = delete;
	~Module() = default;

	static Optional<Module> parse(const File& file);

	bool validate(const EntityId& packageId);

	const auto& filename() const { return _filepath; }
	const auto& functionIds() const { return _functionIds; }
	const auto& structIds() const { return _structIds; }
};

#endif