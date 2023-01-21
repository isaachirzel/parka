#ifndef WARBLER_SYMBOL_ID_H
#define WARBLER_SYMBOL_ID_H

#include "warbler/type.h"
#include "warbler/util/primitives.h"

typedef struct IdList
{
	usize *ids;
	usize count;
} IdList;

typedef bool (*IdAction)(usize index);

usize idListGet(const IdList *ids, usize index);
void symbolIdListPush(IdList *ids, usize index);
void symbolIdListFree(IdList *ids);
bool symbolIdListForEach(const IdList *list, IdAction action);

#endif