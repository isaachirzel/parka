#include "warbler/ast/function.h"
#include "warbler/ast.h"
#include "warbler/util/array.h"
#include "warbler/util/memory.h"

void parameterFree(Parameter *node)
{
	typeAnnotationFree(&node->annotation);
	deallocate(node->symbol);
}

void functionFree(Function *node)
{
	expressionFree(&node->body);
	arrayDestroy(&node->parameterIds, NULL);

	if (node->hasReturnType)
		typeAnnotationFree(&node->returnType);

	deallocate(node->symbol);
}

const Type *functionGetReturnType(const Function *function)
{
	const Type *returnType = function->hasReturnType
		? &function->returnType.type
		: &voidType;

	return returnType;
}
