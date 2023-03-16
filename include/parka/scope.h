#ifndef PARKA_SCOPE_H
#define PARKA_SCOPE_H

#include "parka/util/primitives.h"
#include "parka/util/string.h"

typedef struct Scope
{
    StringBuilder *names;
    usize count;
    usize capacity;
} Scope;

Scope scopeCreate(usize capacity);
Scope scopeFromKey(const char *key);
bool scopeContains(const Scope *scope, const char *name);
void scopePush(Scope *scope, const char *name);
void scopePop(Scope *scope);
void scopeDestroy(Scope *scope);
void scopeClear(Scope *scope);

char *scopeCreateSymbol(const Scope *scope, const char *identifier);
char *scopeCreateSymbolN(const Scope *scope, const char *identifier, usize n);

#endif
