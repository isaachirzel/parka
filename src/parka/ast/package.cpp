#include "parka/ast/package.hpp"
#include "parka/ast/module.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/file.hpp"
#include "parka/util/print.hpp"

Optional<Package> Package::parse(const Array<File>& files, String&& symbol)
{
	// TODO: Add multithreading
	auto success = true;
	auto modules = Array<Module>();

	for (const auto& file : files)
	{
		auto mod = Module::parse(file, symbol);

		if (!mod)
		{
			success = false;
			continue;
		}

		modules.push(mod.unwrap());
	}

	if (!success)
		return {};

	auto package = Package(std::move(symbol), std::move(modules));

	return package;
}

bool Package::declare(Table<String, EntityId>& globalSymbols)
{
	auto success = true;

	for (auto& mod : _modules)
	{
		if (!mod.declare(globalSymbols))
			success = false;
	}

	return success;
}

bool Package::validate(Table<String, EntityId>& globalSymbols)
{
	auto success = true;

	for (auto& mod : _modules)
	{
		if (!mod.validate(globalSymbols, _symbol))
			success = false;
	}

	return success;
}
