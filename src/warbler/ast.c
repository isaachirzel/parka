#include "warbler/ast.h"
#include "warbler/ast/expression.h"
#include "warbler/util/memory.h"

void argumentListFree(ArgumentList *node)
{
	for (usize i = 0; i < node->count; ++i)
	{
		expressionFree(node->expressions + i);
	}

	deallocate(node->expressions);
}

void packageFree(Package *node)
{
	for (usize i = 0; i < node->moduleCount; ++i)
		moduleFree(&node->modules[i]);

	deallocate(node->symbol);
}

void memberListFree(MemberList *node)
{
	for (usize i = 0; i < node->count; ++i)
		memberFree(&node->data[i]);

	deallocate(node->data);
}

void structFree(Struct *node)
{
	memberListFree(&node->members);

	deallocate(node->symbol);
}

void memberFree(Member *node)
{
	typeAnnotationFree(&node->annotation);
}

void moduleFree(Module *node)
{
	symbolIdListFree(&node->functionIds);
	symbolIdListFree(&node->structIds);

	deallocate(node->symbol);
}
