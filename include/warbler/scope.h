#ifndef WARBLER_SCOPE_H
#define WARBLER_SCOPE_H

#include <warbler/util/primitives.h>

typedef struct Scope
{
    char **names;
    usize count;
    usize capacity;
} Scope;

bool scopeContains(const Scope *scope, const char *name);
void scopePush(Scope *scope, const char *name);
void scopePop(Scope *scope);
void scopeDestroy(Scope *scope);

#endif
