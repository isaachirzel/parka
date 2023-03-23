#ifndef PARKA_AST_MODULE_HPP
#define PARKA_AST_MODULE_HPP

#include "parka/scope.hpp"
#include "parka/util/array.hpp"
#include "parka/util/file.hpp"
#include "parka/util/optional.hpp"

class Module
{
	String _symbol;
	Array<usize> _functionIds;
	Array<usize> _structIds;

	Module(String&& symbol, Array<usize>&& functionIds, Array<usize>&& structIds) :
	_symbol(std::move(symbol)),
	_functionIds(std::move(functionIds)),
	_structIds(std::move(structIds))
	{}

public:

	Module(Module&&) = default;
	Module(const Module&) = delete;
	~Module() = default;

	static Optional<Module> parse(const File& file, const String& package);

	bool declare();
	bool validate(const Scope& packageScope);

	const auto& symbol() const { return _symbol; }
	const auto& functionIds() const { return _functionIds; }
	const auto& structIds() const { return _structIds; }
};

#endif