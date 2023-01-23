#include "warbler/ast.h"
#include "warbler/util/memory.h"
#include <stdlib.h>

void moduleFree(Module *node)
{
	arrayDestroy(&node->functionIds, NULL);
	arrayDestroy(&node->structIds, NULL);

	deallocate(node->symbol);
}

void packageFree(Package *node)
{
	for (usize i = 0; i < node->modules.length; ++i)
		moduleFree(&node->modules.data[i]);

	arrayDestroy(&node->modules, (ElementDestructor)moduleFree);
	deallocate(node->symbol);
}
