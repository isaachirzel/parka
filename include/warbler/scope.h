#ifndef WARBLER_SCOPE_H
#define WARBLER_SCOPE_H

#include <warbler/util/primitives.h>
#include <warbler/util/string.h>

typedef struct Scope
{
    StringBuilder *names;
    usize count;
    usize capacity;
} Scope;

bool scopeContains(const Scope *scope, const char *name);
void scopePush(Scope *scope, const char *name);
void scopePop(Scope *scope);
void scopeDestroy(Scope *scope);
void scopeClear(Scope *scope);

char *scopeCreateSymbol(const Scope *scope, const char *identifier);
char *scopeCreateSymbolN(const Scope *scope, const char *identifier, usize n);

#endif
