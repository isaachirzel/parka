#include <warbler/scope.h>

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