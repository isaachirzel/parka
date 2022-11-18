#include <warbler/symbol_id.h>
#include <warbler/util/memory.h>
#include <assert.h>

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
