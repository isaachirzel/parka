#include <warbler/scope.h>
#include <warbler/util/string.h>
#include <warbler/util/memory.h>
#include <string.h>
#include <assert.h>

bool scopeContains(const Scope *scope, const char *name)
{
	for (usize i = 0; i < scope->count; ++i)
	{
		if (!strcmp(scope->names[i].data, name))
			return true;
	}

	return false;
}

void scopePush(Scope *scope, const char *name)
{
	assert(scope);
	assert(scope->capacity >= scope->count); // Count should never be higher than capacity

	if (scope->count == scope->capacity)
	{
		usize newCapacity = scope->count + 8;
		StringBuilder *names = reallocate(scope->names, newCapacity * sizeof(StringBuilder));

		for (usize i = scope->count; i < newCapacity; ++i)
			names[i] = (StringBuilder) { 0 };

		scope->names = names;
		scope->capacity = newCapacity;
	}

	usize index = scope->count;

	StringBuilder *sb = &scope->names[index];

	sbClear(sb);
	sbPushString(sb, name);

	scope->count += 1;
}

void scopePop(Scope *scope)
{
	assert(scope->count > 0);
	
	scope->count -= 1;
}

void scopeDestroy(Scope *scope)
{
	for (usize i = 0; i < scope->count; ++i)
		sbDestroy(&scope->names[i]);

	deallocate(scope->names);
}

void scopeClear(Scope *scope)
{
	scope->count = 0;
}

char *scopeCreateSymbolN(const Scope *scope, const char *identifier, usize n)
{
	assert(n <= scope->count);
	StringBuilder symbol = { 0 };

	sbReserve(&symbol, 128);

	for (usize i = 0; i < n; ++i)
	{
		sbConcat(&symbol, &scope->names[i]);
		sbPushString(&symbol, "::");
	}

	sbPushString(&symbol, identifier);

	return symbol.data;
}

char *scopeCreateSymbol(const Scope *scope, const char *identifier)
{
	return scopeCreateSymbolN(scope, identifier, scope->count);
}
