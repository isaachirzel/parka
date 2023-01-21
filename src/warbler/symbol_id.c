#include "warbler/symbol_id.h"
#include "warbler/util/memory.h"

#include <assert.h>

usize idListGet(const IdList *ids, usize index)
{
    assert(index < ids->count);

    return ids->ids[index];
}

void symbolIdListPush(IdList *ids, usize index)
{
    resizeArray(ids->ids, ++ids->count);

    ids->ids[ids->count - 1] = index;
}

void symbolIdListFree(IdList *ids)
{
    deallocate(ids->ids);
}

bool symbolIdListForEach(const IdList *list, IdAction action)
{
    bool success = true;

    for (usize i = 0; i < list->count; ++i)
    {
        if (!action(i))
            success = false;
    }

    return success;
}
