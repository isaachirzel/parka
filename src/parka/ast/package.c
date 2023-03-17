#include "parka/ast/package.h"
#include "parka/ast/module.h"
#include "parka/scope.h"
#include "parka/symbol_table.h"
#include "parka/util/directory.h"
#include "parka/util/file.h"

static usize getModuleCount(const Directory *directory)
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

bool parsePackage(const Directory *directory, Scope *scope, const char *name)
{
	bool success = true;

	usize index = symbolTableAddPackage();
	Package *node = symbolTableGetPackage(index);
	char *symbol = scopeCreateSymbol(scope, name);

	scopePush(scope, name);

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
	bool success = symbolTableDeclareGlobal(SYMBOL_PACKAGE, index);
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

void packageFree(Package *node)
{
	for (usize i = 0; i < node->modules.length; ++i)
		moduleFree(&node->modules.data[i]);

	arrayDestroy(&node->modules, (ElementDestructor)moduleFree);
	deallocate(node->symbol);
}
