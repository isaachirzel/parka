#include "warbler/util/string.h"
#include <warbler/ast.h>
#include <warbler/type.h>
#include <warbler/symbol_table.h>
#include <warbler/util/memory.h>
#include <warbler/util/print.h>

enum PrimitiveIndex
{
	INDEX_VOID,
	INDEX_U8,
	INDEX_16,
	INDEX_U32,
	INDEX_U64,
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

const SymbolId voidSymbolId = { SYMBOL_PRIMITIVE, INDEX_VOID };
const SymbolId u8SymbolId = { SYMBOL_PRIMITIVE, INDEX_U8 };
const SymbolId u16SymbolId = { SYMBOL_PRIMITIVE, INDEX_16 };
const SymbolId u32SymbolId = { SYMBOL_PRIMITIVE, INDEX_U32 };
const SymbolId u64SymbolId = { SYMBOL_PRIMITIVE, INDEX_U64 };
const SymbolId i8SymbolId = { SYMBOL_PRIMITIVE, INDEX_I8 };
const SymbolId i16SymbolId = { SYMBOL_PRIMITIVE, INDEX_I16 };
const SymbolId i32SymbolId = { SYMBOL_PRIMITIVE, INDEX_I32 };
const SymbolId i64SymbolId = { SYMBOL_PRIMITIVE, INDEX_I64 };
const SymbolId f32SymbolId = { SYMBOL_PRIMITIVE, INDEX_F32 };
const SymbolId f64SymbolId = { SYMBOL_PRIMITIVE, INDEX_F64 };
const SymbolId boolSymbolId = { SYMBOL_PRIMITIVE, INDEX_BOOL };
const SymbolId charSymbolId = { SYMBOL_PRIMITIVE, INDEX_CHAR };
const SymbolId stringSymbolId = { SYMBOL_PRIMITIVE, INDEX_STRING };

const Type voidType = { .id = { SYMBOL_PRIMITIVE, INDEX_VOID } };

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
	{ "char", PRIMITIVE_CHARACTER, 1 },
	{ "string", PRIMITIVE_STRING, 0 }
};

const usize primitiveCount = sizeof(primitives) / sizeof(*primitives);

void stringLiteralFree(StringLiteral *node)
{
	deallocate(node->text);
}

void literalFree(Literal *node)
{
	if (node->type == LITERAL_STRING)
		stringLiteralFree(&node->string);
}

void expressionFree(Expression *node)
{
	switch (node->type)
	{
	case EXPRESSION_BLOCK:
		blockFree(node->block);
		deallocate(node->block);
		break;
	case EXPRESSION_ASSIGNMENT:
		assignmentFree(node->assignment);
		deallocate(node->assignment);
		break;
	case EXPRESSION_CONDITIONAL:
		conditionalExpressionFree(node->conditional);
		deallocate(node->conditional);
		break;
	case EXPRESSION_BOOLEAN_OR:
		booleanOrExpressionFree(node->booleanOr);
		deallocate(node->booleanOr);
		break;
	case EXPRESSION_BOOLEAN_AND:
		booleanAndExpressionFree(node->booleanAnd);
		deallocate(node->booleanAnd);
		break;
	case EXPRESSION_BITWISE_OR:
		bitwiseOrExpressionFree(node->bitwiseOr);
		deallocate(node->bitwiseOr);
		break;
	case EXPRESSION_BITWISE_XOR:
		bitwiseXorExpressionFree(node->bitwiseXor);
		deallocate(node->bitwiseXor);
		break;
	case EXPRESSION_BITWISE_AND:
		bitwiseAndExpressionFree(node->bitwiseAnd);
		deallocate(node->bitwiseAnd);
		break;
	case EXPRESSION_EQUALITY:
		equalityExpressionFree(node->equality);
		deallocate(node->equality);
		break;
	case EXPRESSION_RELATIONAL:
		relationalExpressionFree(node->relational);
		deallocate(node->relational);
		break;
	case EXPRESSION_SHIFT:
		bitShiftExpressionFree(node->shift);
		deallocate(node->shift);
		break;
	case EXPRESSION_ADDITIVE:
		additiveExpressionFree(node->additive);
		deallocate(node->additive);
		break;
	case EXPRESSION_MULTIPLICATIVE:
		multiplicativeExpressionFree(node->multiplicative);
		deallocate(node->multiplicative);
		break;
	case EXPRESSION_POSTFIX:
		prefixExpressionFree(node->prefix);
		deallocate(node->prefix);
		break;
	case EXPRESSION_PREFIX:
		postfixExpressionFree(node->postfix);
		deallocate(node->postfix);
		break;
	case EXPRESSION_LITERAL:
		literalFree(node->literal);
		deallocate(node->literal);
		break;
	case EXPRESSION_SYMBOL:
		break;

	default:
		exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}

void argumentListFree(ArgumentList *node)
{
	for (usize i = 0; i < node->count; ++i)
	{
		expressionFree(node->expressions + i);
	}

	deallocate(node->expressions);
}

void postfixExpressionFree(Postfix *node)
{
	expressionFree(&node->expression);

	switch (node->type)
	{
		case POSTFIX_INDEX:
			expressionFree(&node->index);
			break;

		case POSTFIX_FUNCTION_CALL:
			argumentListFree(&node->arguments);
			break;

		case POSTFIX_MEMBER:
			break;

		default:
			exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}

void jumpStatementFree(JumpStatement *node)
{
	if (node->hasValue)
		expressionFree(&node->value);
}

void statementFree(Statement *node)
{
	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			expressionFree(node->expression);
			deallocate(node->expression);
			break;

		case STATEMENT_DECLARATION:
			declarationFree(node->declaration);
			deallocate(node->declaration);
			break;

		case STATEMENT_JUMP:
			jumpStatementFree(node->jump);
			deallocate(node->jump);
			break;

		default:
			exitWithErrorFmt("Unable to free Statement with StatementType: %d", node->type);
	}
}

void ifExpressionFree(IfStatement *node)
{
	expressionFree(&node->condition);
	statementFree(&node->thenCase);

	if (node->type == IF_THEN_ELSE)
	{
		statementFree(&node->elseCase);
	}
	else if (node->type == IF_THEN_ELSE)
	{
		ifExpressionFree(node->elseIf);
		deallocate(node->elseIf);
	}
}

void packageFree(Package *node)
{
	for (usize i = 0; i < node->moduleCount; ++i)
		moduleFree(&node->modules[i]);

	deallocate(node->symbol);
}

void additiveExpressionFree(AdditiveExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void bitwiseAndExpressionFree(BitwiseAndExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}

void bitwiseOrExpressionFree(BitwiseOrExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}

void bitwiseXorExpressionFree(BitwiseXorExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}

void booleanAndExpressionFree(BooleanAndExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}

void booleanOrExpressionFree(BooleanOrExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}

void freeConditionalRhs(ConditionalRhs *node)
{
	expressionFree(&node->trueCase);
	expressionFree(&node->falseCase);
}

void conditionalExpressionFree(ConditionalExpression *node)
{
	expressionFree(&node->expression);

	if (node->hasRhs)
		freeConditionalRhs(&node->rhs);
}

void equalityExpressionFree(EqualityExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void multiplicativeExpressionFree(MultiplicativeExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void relationalExpressionFree(RelationalExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void bitShiftExpressionFree(BitShiftExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

void prefixExpressionFree(Prefix *node)
{
	expressionFree(&node->expression);
}

void parameterFree(Local *node)
{
	typeAnnotationFree(&node->type);
	deallocate(node->symbol);
}

void functionFree(Function *node)
{
	expressionFree(&node->body);
	symbolIdListFree(&node->parameterIds);

	if (node->hasReturnType)
		typeAnnotationFree(&node->returnType);

	deallocate(node->symbol);
}

void blockFree(Block *node)
{
	for (usize i = 0; i< node->count; ++i)
		statementFree(&node->statements[i]);
}

void declarationFree(Declaration *node)
{
	expressionFree(&node->value);
}

void variableFree(Local *node)
{
	typeAnnotationFree(&node->type);
	deallocate(node->symbol);
}

void assignmentFree(Assignment *node)
{
	expressionFree(&node->lhs);
	expressionFree(&node->rhs);
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

void freeType(Type *type)
{
	assert(type);
	// TODO: pointers
}

void typeAnnotationFree(TypeAnnotation *node)
{
	freeType(&node->type);
}

void moduleFree(Module *node)
{
	symbolIdListFree(&node->functionIds);
	symbolIdListFree(&node->structIds);

	deallocate(node->symbol);
}

typedef const SymbolId *(*LiteralValidationFunction)(const Primitive *);

const SymbolId *getFloatLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_FLOATING_POINT)
		return NULL;

	return &f64SymbolId;
}

const SymbolId *getIntegerLiteralSymbolId(const Primitive *primitive)
{
	if (primitive)
	{
		switch (primitive->type)
		{
			// TODO: Add boolean and char
			case PRIMITIVE_UNSIGNED_INTEGER:
			case PRIMITIVE_SIGNED_INTEGER:
			case PRIMITIVE_FLOATING_POINT:
				return NULL;

			default:
				break;
		}
	}

	return &i32SymbolId;
}

const SymbolId *getBooleanLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_BOOLEAN)
		return NULL;

	return &boolSymbolId;
}

const SymbolId *getCharacterLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_CHARACTER)
		return NULL;

	return &charSymbolId;
}

const SymbolId *getStringLiteralSymboId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_STRING)
		return NULL;

	return &stringSymbolId;
}

LiteralValidationFunction getLiteralValidationFunction(Literal *literal)
{
	switch (literal->type)
	{
		case LITERAL_CHARACTER:
			return getCharacterLiteralSymbolId;

		case LITERAL_STRING:
			return getStringLiteralSymboId;

		case LITERAL_INTEGER:
			return getIntegerLiteralSymbolId;

		case LITERAL_FLOAT:
			return getFloatLiteralSymbolId;

		case LITERAL_BOOLEAN:
			return getBooleanLiteralSymbolId;

		default:
			break;
	}

	exitWithErrorFmt("Unable to get SymbolId for Literal of type: %d", literal->type);
}

static const Primitive *getTypePrimitive(const Type *type)
{
	if (!type)
		return NULL;

	const SymbolId *id = &type->id;

	if (id->type != SYMBOL_PRIMITIVE)
		return NULL;

	const Primitive *primitive = symbolTableGetPrimitive(id);

	return primitive;
}

SymbolId getLiteralSymbolId(Literal *literal, const Type *expectedType)
{
	assert(literal != NULL);

	LiteralValidationFunction check = getLiteralValidationFunction(literal);
	const Primitive *primitive = getTypePrimitive(expectedType);
	const SymbolId *id = check(primitive);

	if (!id)
		id = &expectedType->id;

	return *id;
}

Type getLiteralType(Literal *literal, const Type *expectedType)
{
	Type type =
	{
		.id = getLiteralSymbolId(literal, expectedType)
	};

	return type;
}

Type typeFromExpression(Expression *expression, const Type *expectedType)
{
	switch (expression->type)
	{
		case EXPRESSION_BLOCK:
			break;
		case EXPRESSION_ASSIGNMENT:
			break;
		case EXPRESSION_CONDITIONAL:
			break;
		case EXPRESSION_BOOLEAN_OR:
			break;
		case EXPRESSION_BOOLEAN_AND:
			break;
		case EXPRESSION_BITWISE_OR:
			break;
		case EXPRESSION_BITWISE_XOR:
			break;
		case EXPRESSION_BITWISE_AND:
			break;
		case EXPRESSION_EQUALITY:
			break;
		case EXPRESSION_RELATIONAL:
			break;
		case EXPRESSION_SHIFT:
			break;
		case EXPRESSION_ADDITIVE:
			break;
		case EXPRESSION_MULTIPLICATIVE:
			break;
		case EXPRESSION_POSTFIX:
			break;
		case EXPRESSION_PREFIX:
			break;
		case EXPRESSION_LITERAL:
			return getLiteralType(expression->literal, expectedType);
		case EXPRESSION_SYMBOL:
			break;
	}

	exitWithErrorFmt("Unable to get type for expression of type: %d", expression->type);
}

Type typeDuplicate(const Type *type)
{
	return *type;
}

bool typeCanConvert(const Type *to, const Type *from)
{
	const SymbolId *toId = &to->id;
	const SymbolId *fromId = &from->id;

	bool success = symbolIdEquals(toId, fromId);

	return success;
}

Token tokenFromExpression(Expression *expression)
{
	switch( expression->type)
	{
		case EXPRESSION_BLOCK:
			break;

		case EXPRESSION_ASSIGNMENT:
			break;

		case EXPRESSION_CONDITIONAL:
			break;

		case EXPRESSION_BOOLEAN_OR:
			break;

		case EXPRESSION_BOOLEAN_AND:
			break;

		case EXPRESSION_BITWISE_OR:
			break;

		case EXPRESSION_BITWISE_XOR:
			break;

		case EXPRESSION_BITWISE_AND:
			break;

		case EXPRESSION_EQUALITY:
			break;

		case EXPRESSION_RELATIONAL:
			break;

		case EXPRESSION_SHIFT:
			break;

		case EXPRESSION_ADDITIVE:
			break;

		case EXPRESSION_MULTIPLICATIVE:
			break;

		case EXPRESSION_POSTFIX:
			break;

		case EXPRESSION_PREFIX:
			break;

		case EXPRESSION_LITERAL:
			return expression->literal->token;
			
		case EXPRESSION_SYMBOL:
			return expression->symbol.token;
	}

	exitWithErrorFmt("Unable to get Token for Expression of type: %d", expression->type);
}

const Type *functionGetReturnType(const Function *function)
{
	const Type *returnType = function->hasReturnType
		? &function->returnType.type
		: &voidType;

	return returnType;
}

char *typeGetName(const Type *type)
{
	const char *symbol = symbolTableGetSymbol(&type->id);
	
	char *name = stringDuplicate(symbol);

	return name;
}
