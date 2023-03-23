#include "parka/ast/package.hpp"
#include "parka/ast/module.hpp"
#include "parka/scope.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/file.hpp"

usize getModuleCount(const Directory *directory)
{
	usize count = 0;

	for (usize i = 0; i < directory->entryCount; ++i)
	{
		// TODO: Check if has correct extension
		if (!directory->entries[i].isDirectory)
			count += 1;
	}

	return count;
}

bool parsePackage(const Directory *directory, Scope& scope, const String& name)
{
	auto success = true;
	auto index = symbolTable.addPackage();
	auto node = symbolTableGetPackage(index);
	auto symbol = scopeCreateSymbol(scope, name);

	scope.push(name);

	node->symbol = symbol;

	usize moduleCount = getModuleCount(directory);

	arrayInit(&node->modules, moduleCount);

	for (usize i = 0; i < directory->entryCount; ++i)
	{
		const DirectoryEntry *entry = &directory->entries[i];

		if (entry->isDirectory)
		{
			if (!parsePackage(entry->directory, scope, entry->directory->name))
				success = false;

			continue;
		}

		switch (entry->file.type)
		{
			case FILE_SOURCE:
			{
				Module module = { 0 };

				if (!parseModule(&module, &entry->file, node->symbol))
					success = false;

				arrayPush(&node->modules, &module);
				break;
			}

			default:
				break;
		}
	}

	scopePop(scope);

	return success;
}

bool declarePackage(usize index)
{
	bool success = symbolTableDeclareGlobal(EntityType::Package, index);
	Package *package = symbolTableGetPackage(index);

	for (usize i = 0; i < package->modules.length; ++i)
	{
		if (!declareModule(&package->modules.data[i]))
			success = false;
	}

	return success;
}

bool validatePackage(usize index)
{
	bool success = true;
	Package *package = symbolTableGetPackage(index);
	Scope scope = scopeFromKey(package->symbol);

	for (usize i = 0; i < package->modules.length; ++i)
	{
		if (!validateModule(&package->modules.data[i], &scope))
			success = false;
	}

	scopeDestroy(&scope);

	return success;
}
