#include "warbler/ast/struct.h"
#include "warbler/util/memory.h"

void structFree(Struct *node)
{
	memberListFree(&node->members);

	deallocate(node->symbol);
}
