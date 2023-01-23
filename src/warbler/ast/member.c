#include "warbler/ast/member.h"
#include "warbler/util/memory.h"

void memberFree(Member *node)
{
	typeAnnotationFree(&node->annotation);
}

void memberListFree(MemberList *node)
{
	for (usize i = 0; i < node->count; ++i)
		memberFree(&node->data[i]);

	deallocate(node->data);
}
