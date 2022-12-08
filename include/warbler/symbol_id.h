#ifndef WARBLER_SYMBOL_ID_H
#define WARBLER_SYMBOL_ID_H

#include <warbler/type.h>
#include <warbler/util/primitives.h>

typedef struct SymbolId
{
	SymbolType type;
	usize index;
} SymbolId;

typedef struct SymbolIdList
{
	SymbolType type;
	usize *indeces;
	usize count;
} SymbolIdList;

typedef bool (*SymbolIdAction)(const SymbolId *id);

bool symbolIdEquals(const SymbolId *a, const SymbolId *b);
void symbolIdListPush(SymbolIdList *ids, const SymbolId *id);
void symbolIdListFree(SymbolIdList *ids);
bool symbolIdListForEach(const SymbolIdList *list, SymbolIdAction action);

#endif