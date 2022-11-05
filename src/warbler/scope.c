#include <warbler/scope.h>
#include <warbler/util/string.h>
#include <warbler/util/memory.h>
#include <string.h>
#include <assert.h>

bool scopeContains(const Scope *scope, const char *name)
{
	for (usize i = 0; i < scope->count; ++i)
	{
		if (!strcmp(scope->names[i], name))
			return true;
	}

	return false;
}

void scopePush(Scope *scope, const char *name)
{
	usize index = scope->count;

	incrementArray(scope->names, &scope->count, &scope->capacity);

	scope->names[index] = duplicateString(name);
}

void scopePop(Scope *scope)
{
	assert(scope->count > 0);
	
	scope->count -= 1;

	deallocate(scope->names + scope->count);
}

void scopeDestroy(Scope *scope)
{
	for (usize i = 0; i < scope->count; ++i)
		deallocate(scope->names[i]);

	deallocate(scope->names);
}

void scopeClear(Scope *scope)
{
	for (usize i = 0; i < scope->count; ++i)
		deallocate(scope->names[i]);

	scope->count = 0;
}

char *scopeCreateSymbolN(const Scope *scope, const char *identifier, usize n)
{
	String symbol = { 0 };

	stringReserve(&symbol, 128);

	for (usize i = 0; i < n; ++i)
	{
		const char *package = scope->names[i];

		stringPush(&symbol, package);
		stringPush(&symbol, "::");
	}

	stringPush(&symbol, identifier);

	return symbol.data;
}

char *scopeCreateSymbol(const Scope *scope, const char *identifier)
{
	return scopeCreateSymbolN(scope, identifier, scope->count);
}
