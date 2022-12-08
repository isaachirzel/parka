#include <warbler/symbol_id.h>
#include <warbler/util/memory.h>
#include <assert.h>

bool symbolIdEquals(const SymbolId *a, const SymbolId *b)
{
    assert(a);
    assert(b);
    return a->type == b->type && a->index == b->index;
}

void symbolIdListPush(SymbolIdList *ids, const SymbolId *id)
{
    assert(ids->type == id->type);
    resizeArray(ids->indeces, ++ids->count);

    ids->indeces[ids->count - 1] = id->index;
}

void symbolIdListFree(SymbolIdList *ids)
{
    deallocate(ids->indeces);
}

bool symbolIdListForEach(const SymbolIdList *list, SymbolIdAction action)
{
    bool success = true;

    for (usize i = 0; i < list->count; ++i)
    {
        SymbolId id = { list->type, i };

        if (!action(&id))
            success = false;
    }

    return success;
}
