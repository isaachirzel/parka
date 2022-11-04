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

void freeConstantContext(ConstantContext *context)
{
	if (context->type == CONSTANT_STRING)
		deallocate(context->string);
}

void freeTypeContext(TypeContext *context)
{
	if (context->type == ANNOTATION_CONSTANT)
		freeConstantContext(&context->constant);
}

void freeMemberContext(MemberContext *context)
{
	freeTypeContext(&context->type);
	deallocate(context->name);
}

void freeFunctionSignatureContext(FunctionSignatureContext *context)
{
	freeParameterListContext(&context->parameters);
	freeTypeContext(&context->returnType);
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
	if (!context)
		return;
	
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
	if (!context)
		return;
		
	freeExpressionContext(&context->value);
}

void freeStatementContext(StatementContext *context)
{
	if (context->isDeclaration)
	{
		freeDeclarationContext(context->declaration);
	}
	else
	{
		freeExpressionContext(context->expression);
	}
}

void freeBlockContext(BlockContext* context)
{
	for (usize i = 0; i < context->count; ++i)
		freeStatementContext(context->statements + i);

	deallocate(context->statements);
}

void freeParameterListContext(ParameterListContext *context)
{
	// Freeing individual parameters not necessary as it is a list of indeces
	deallocate(context->data);
}

void freePackageContext(PackageContext *context)
{
	deallocate(context->name);
}

void freeStructContext(StructContext *context)
{
	for (usize i = 0; i < context->memberCount; ++i)
		freeMemberContext(context->members + i);

	deallocate(context->members);
	deallocate(context->symbol);
}

void freeProgramContext(ProgramContext *context)
{
	// Structs
	for (usize i = 0; i < context->structCount; ++i)
		freeStructContext(context->structs + i);
	
	deallocate(context->structs);

	// Functions
	for (usize i = 0; i < context->functionCount; ++i)
		freeFunctionContext(context->functions + i);

	deallocate(context->functions);

	// Variables
	for (usize i = 0; i < context->variableCount; ++i)
		freeVariableContext(context->variables + i);

	deallocate(context->variables);

	// Parameters
	for (usize i = 0; i < context->parameterCount; ++i)
		freeParameterContext(context->parameters + i);

	deallocate(context->parameters);

	// Packages
	for (usize i = 0; i < context->packageCount; ++i)
		freePackageContext(context->packages + i);

	deallocate(context->packages);
}
