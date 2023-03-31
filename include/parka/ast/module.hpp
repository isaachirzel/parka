#ifndef PARKA_AST_MODULE_HPP
#define PARKA_AST_MODULE_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/global_symbol_table.hpp"
#include "parka/util/array.hpp"
#include "parka/util/file.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/table.hpp"

class Module
{
	String _symbol; // TODO: Change to filename?
	Array<EntityId> _functionIds;
	Array<EntityId> _structIds;

	Module(String&& symbol, Array<EntityId>&& functionIds, Array<EntityId>&& structIds) :
	_symbol(std::move(symbol)),
	_functionIds(std::move(functionIds)),
	_structIds(std::move(structIds))
	{}

public:

	Module(Module&&) = default;
	Module(const Module&) = delete;
	~Module() = default;

	static Optional<Module> parse(const File& file, const String& packageSymbol);

	bool declare(GlobalSymbolTable& globalSymbols);
	bool validate(GlobalSymbolTable& globalSymbols, const String& packageSymbol);

	const auto& symbol() const { return _symbol; }
	const auto& functionIds() const { return _functionIds; }
	const auto& structIds() const { return _structIds; }
};

#endif