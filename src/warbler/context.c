#include <warbler/context.h>
#include <warbler/util/print.h>
#include <warbler/symbol_table.h>

const PrimitiveContext primitives[] =
{
	{ "void", PRIMITIVE_VOID, 0 },
	{ "u8", PRIMITIVE_UNSIGNED_INTEGER, 1 },
	{ "u16", PRIMITIVE_UNSIGNED_INTEGER, 2 },
	{ "u32", PRIMITIVE_UNSIGNED_INTEGER, 4 },
	{ "u64", PRIMITIVE_UNSIGNED_INTEGER, 8 },
	{ "i8", PRIMITIVE_SIGNED_INTEGER, 1 },
	{ "i16", PRIMITIVE_SIGNED_INTEGER, 2 },
	{ "i32", PRIMITIVE_SIGNED_INTEGER, 4 },
	{ "i64", PRIMITIVE_SIGNED_INTEGER, 8 },
	{ "f32", PRIMITIVE_FLOATING_POINT, 4 },
	{ "f64", PRIMITIVE_FLOATING_POINT, 8 },
	{ "bool", PRIMITIVE_BOOLEAN, 1 },
	{ "char", PRIMITIVE_CHARACTER, 1 }
};

const usize primitiveCount = sizeof(primitives) / sizeof(*primitives);

const PrimitiveContext *primitiveAt(usize index)
{
	assert(index < primitiveCount);

	return primitives + index;
}

const char *typeAnnotationSymbol(const TypeContext *type, const ProgramContext *program)
{
	switch (type->type)
	{
		case ANNOTATION_STRUCT:
		{
			const StructContext *context = structAt(program, type->index);

			return context->symbol;
		}

		case ANNOTATION_PRIMITIVE:
		{
			const PrimitiveContext *context = primitiveAt(type->index);

			return context->symbol;
		}

		case ANNOTATION_CONSTANT:
		default:
			exitWithError("Invalid TypeAnnotationType: %d", type->type);
	}
}

void freeMemberContext(MemberContext *member)
{
	deallocate(member->name);
}

void freeConstantContext(ConstantContext *context)
{
	if (context->type == CONSTANT_STRING)
		deallocate(context->string);
}

void freeTypeContext(TypeContext *context)
{
	
	switch (context->type)
	{
		case ANNOTATION_STRUCT:
		case ANNOTATION_PRIMITIVE:
			break;

		case ANNOTATION_CONSTANT:
			freeConstantContext(&context->constant);
			break;
	}
}

void freeFunctionSignatureContext(FunctionSignatureContext *context)
{
	freeParameterListContext(&context->parameters);
	freeTypeContext(&context->returnType);
}

void freeParameterListContext(ParameterListContext *context)
{
	deallocate(context->data);
}

void freeAssignmentContext(AssignmentContext *context)
{
	freeExpressionContext(&context->lhs);
	freeExpressionContext(&context->rhs);
}

void freeParameterContext(ParameterContext *context)
{
	deallocate(context->name);
	freeTypeContext(&context->type);
}

void freeFunctionContext(FunctionContext *context)
{
	deallocate(context->symbol);
	freeExpressionContext(&context->body);
	freeFunctionSignatureContext(&context->signature);

	for (usize i = 0; i < context->parameterCount; ++i)
		freeParameterContext(context->parameters + i);

	for (usize i = 0; i < context->variableCount; ++i)
		freeVariableContext(context->variables + i);

	deallocate(context->parameters);
	deallocate(context->variables);
}

void freeExpressionContext(ExpressionContext *context)
{
	switch (context->type)
	{
		case EXPRESSION_ASSIGNMENT:
			return freeAssignmentContext(context->assignment);
		// case EXPRESSION_CONDITIONAL:
		// 	return free(context->);
		// case EXPRESSION_BOOLEAN_OR:
		// 	return free(context->);
		// case EXPRESSION_BOOLEAN_AND:
		// 	return free(context->);
		// case EXPRESSION_BITWISE_OR:
		// 	return free(context->);
		// case EXPRESSION_BITWISE_XOR:
		// 	return free(context->);
		// case EXPRESSION_BITWISE_AND:
		// 	return free(context->);
		// case EXPRESSION_EQUALITY:
		// 	return free(context->);
		// case EXPRESSION_RELATIONAL:
		// 	return free(context->);
		// case EXPRESSION_SHIFT:
		// 	return free(context->);
		// case EXPRESSION_ADDITIVE:
		// 	return free(context->);
		// case EXPRESSION_MULTIPLICATIVE:
		// 	return free(context->);
		// case EXPRESSION_POSTFIX:
		// 	return free(context->);
		// case EXPRESSION_PREFIX:
		// 	return free(context->);
		case EXPRESSION_CONSTANT:
			return freeConstantContext(context->constant);
		case EXPRESSION_SYMBOL:
			return;
	}
}

void freeVariableContext(VariableContext *context)
{
	deallocate(context->name);
	freeTypeContext(&context->type);
}

void freeDeclarationContext(DeclarationContext *context)
{
	freeExpressionContext(&context->value);
}

void freeStatementContext(StatementContext *context)
{
	if (context->isDeclaration)
		return freeDeclarationContext(context->declaration);

	freeExpressionContext(context->expression);
}

void freeBlockContext(BlockContext* context)
{
	for (usize i = 0; i < context->count; ++i)
		freeStatementContext(context->statements + i);

	deallocate(context->statements);
}
