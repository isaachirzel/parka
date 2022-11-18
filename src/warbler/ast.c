#include <warbler/ast.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

enum PrimitiveIndex
{
	INDEX_VOID,
	INDEX_UINT,
	INDEX_U8,
	INDEX_16,
	INDEX_U32,
	INDEX_U64,
	INDEX_INT,
	INDEX_I8,
	INDEX_I16,
	INDEX_I32,
	INDEX_I64,
	INDEX_F32,
	INDEX_F64,
	INDEX_BOOL,
	INDEX_CHAR,
	INDEX_STRING,
};

SymbolId voidSymbolId = { SYMBOL_PRIMITIVE, INDEX_VOID };
SymbolId uintSymbolId = { SYMBOL_PRIMITIVE, INDEX_UINT };
SymbolId u8SymbolId = { SYMBOL_PRIMITIVE, INDEX_U8 };
SymbolId u16SymbolId = { SYMBOL_PRIMITIVE, INDEX_16 };
SymbolId u32SymbolId = { SYMBOL_PRIMITIVE, INDEX_U32 };
SymbolId u64SymbolId = { SYMBOL_PRIMITIVE, INDEX_U64 };
SymbolId intSymbolId = { SYMBOL_PRIMITIVE, INDEX_INT };
SymbolId i8SymbolId = { SYMBOL_PRIMITIVE, INDEX_I8 };
SymbolId i16SymbolId = { SYMBOL_PRIMITIVE, INDEX_I16 };
SymbolId i32SymbolId = { SYMBOL_PRIMITIVE, INDEX_I32 };
SymbolId i64SymbolId = { SYMBOL_PRIMITIVE, INDEX_I64 };
SymbolId f32SymbolId = { SYMBOL_PRIMITIVE, INDEX_F32 };
SymbolId f64SymbolId = { SYMBOL_PRIMITIVE, INDEX_F64 };
SymbolId boolSymbolId = { SYMBOL_PRIMITIVE, INDEX_BOOL };
SymbolId charSymbolId = { SYMBOL_PRIMITIVE, INDEX_CHAR };
SymbolId stringSymbolId = { SYMBOL_PRIMITIVE, INDEX_STRING };

const Primitive primitives[] =
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

void freeSymbolIdList(SymbolIdList *list)
{
	deallocate(list->indeces);
}

void freeStringLiteral(StringLiteral *node)
{
	deallocate(node->text);
}

void freeLiteral(Literal *node)
{
	if (node->type == LITERAL_STRING)
		freeStringLiteral(&node->string);
}

void freeExpression(Expression *node)
{
	switch (node->type)
	{
	case EXPRESSION_BLOCK:
		freeBlock(node->block);
		deallocate(node->block);
		break;
	case EXPRESSION_ASSIGNMENT:
		freeAssignment(node->assignment);
		deallocate(node->assignment);
		break;
	case EXPRESSION_CONDITIONAL:
		freeConditionalExpression(node->conditional);
		deallocate(node->conditional);
		break;
	case EXPRESSION_BOOLEAN_OR:
		freeBooleanOrExpression(node->booleanOr);
		deallocate(node->booleanOr);
		break;
	case EXPRESSION_BOOLEAN_AND:
		freeBooleanAndExpression(node->booleanAnd);
		deallocate(node->booleanAnd);
		break;
	case EXPRESSION_BITWISE_OR:
		freeBitwiseOrExpression(node->bitwiseOr);
		deallocate(node->bitwiseOr);
		break;
	case EXPRESSION_BITWISE_XOR:
		freeBitwiseXorExpression(node->bitwiseXor);
		deallocate(node->bitwiseXor);
		break;
	case EXPRESSION_BITWISE_AND:
		freeBitwiseAndExpression(node->bitwiseAnd);
		deallocate(node->bitwiseAnd);
		break;
	case EXPRESSION_EQUALITY:
		freeEqualityExpression(node->equality);
		deallocate(node->equality);
		break;
	case EXPRESSION_RELATIONAL:
		freeRelationalExpression(node->relational);
		deallocate(node->relational);
		break;
	case EXPRESSION_SHIFT:
		freeBitShiftExpression(node->shift);
		deallocate(node->shift);
		break;
	case EXPRESSION_ADDITIVE:
		freeAdditiveExpression(node->additive);
		deallocate(node->additive);
		break;
	case EXPRESSION_MULTIPLICATIVE:
		freeMultiplicativeExpression(node->multiplicative);
		deallocate(node->multiplicative);
		break;
	case EXPRESSION_POSTFIX:
		freePrefixExpression(node->prefix);
		deallocate(node->prefix);
		break;
	case EXPRESSION_PREFIX:
		freePostfixExpression(node->postfix);
		deallocate(node->postfix);
		break;
	case EXPRESSION_LITERAL:
		freeLiteral(node->literal);
		deallocate(node->literal);
		break;
	case EXPRESSION_SYMBOL:
		break;

	default:
		exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}

void freeArgumentList(ArgumentList *node)
{
	for (usize i = 0; i < node->count; ++i)
	{
		freeExpression(node->expressions + i);
	}

	deallocate(node->expressions);
}

void freePostfixExpression(Postfix *node)
{
	freeExpression(&node->expression);

	switch (node->type)
	{
		case POSTFIX_INDEX:
			freeExpression(&node->index);
			break;

		case POSTFIX_FUNCTION_CALL:
			freeArgumentList(&node->arguments);
			break;

		case POSTFIX_MEMBER:
			break;

		default:
			exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}

void freeStatement(Statement *node)
{
	if (node->isDeclaration)
	{
		freeDeclaration(node->declaration);
		deallocate(node->declaration);
	}
	else
	{
		freeExpression(node->expression);
		deallocate(node->expression);
	}
}

void freeIfStatement(IfStatement *node)
{
	freeExpression(&node->condition);

	if (node->type == IF_THEN_ELSE)
	{
		freeBlock(&node->elseBody);
	}
	else if (node->type == IF_THEN_ELSE)
	{
		freeIfStatement(node->elseIf);
		deallocate(node->elseIf);
	}
}

void freePackage(Package *node)
{
	for (usize i = 0; i < node->moduleCount; ++i)
		freeModule(&node->modules[i]);

	deallocate(node->symbol);
}

void freeAdditiveExpression(AdditiveExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void freeBitwiseAndExpression(BitwiseAndExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(node-> rhs + i);

	deallocate(node->rhs);
}

void freeBitwiseOrExpression(BitwiseOrExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(node-> rhs + i);

	deallocate(node->rhs);
}

void freeBitwiseXorExpression(BitwiseXorExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(node-> rhs + i);

	deallocate(node->rhs);
}

void freeBooleanAndExpression(BooleanAndExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(node-> rhs + i);

	deallocate(node->rhs);
}

void freeBooleanOrExpression(BooleanOrExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(node-> rhs + i);

	deallocate(node->rhs);
}

void freeConditionalRhs(ConditionalRhs *node)
{
	freeExpression(&node->trueCase);
	freeExpression(&node->falseCase);
}

void freeConditionalExpression(ConditionalExpression *node)
{
	freeExpression(&node->expression);

	if (node->hasRhs)
		freeConditionalRhs(&node->rhs);
}

void freeEqualityExpression(EqualityExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void freeMultiplicativeExpression(MultiplicativeExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void freeRelationalExpression(RelationalExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void freeBitShiftExpression(BitShiftExpression *node)
{
	freeExpression(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		freeExpression(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void freePrefixExpression(Prefix *node)
{
	freeExpression(&node->expression);
}

void freeParameter(Parameter *node)
{
	freeType(&node->type);
	deallocate(node->symbol);
}

void freeFunction(Function *node)
{
	freeExpression(&node->body);
	freeSymbolIdList(&node->parameterIds);

	if (node->hasReturnType)
		freeType(&node->returnType);

	deallocate(node->symbol);
}

void freeBlock(Block *node)
{
	for (usize i = 0; i< node->count; ++i)
		freeStatement(&node->statements[i]);
}

void freeDeclaration(Declaration *node)
{
	freeExpression(&node->value);
}

void freeVariable(Variable *node)
{
	freeType(&node->type);
	deallocate(node->symbol);
}

void freeAssignment(Assignment *node)
{
	freeExpression(&node->lhs);
	freeExpression(&node->rhs);
}

void freeStruct(Struct *node)
{
	for (usize i = 0; i < node->memberCount; ++i)
		freeMember(&node->members[i]);

	deallocate(node->symbol);
}

void freeMember(Member *node)
{
	freeType(&node->type);
}

void freeType(TypeAnnotation *node)
{
	// No-op
}

void freeModule(Module *node)
{
	symbolIdListFree(&node->functionIds);
	symbolIdListFree(&node->structIds);

	deallocate(node->symbol);
}
