#include "warbler/util/primitives.h"
#include "warbler/util/string.h"
#include "warbler/ast.h"
#include "warbler/type.h"
#include "warbler/symbol_table.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

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

const usize voidSymbolId = INDEX_VOID;
const usize u8SymbolId = INDEX_U8;
const usize u16SymbolId = INDEX_16;
const usize u32SymbolId = INDEX_U32;
const usize u64SymbolId = INDEX_U64;
const usize i8SymbolId = INDEX_I8;
const usize i16SymbolId = INDEX_I16;
const usize i32SymbolId = INDEX_I32;
const usize i64SymbolId = INDEX_I64;
const usize f32SymbolId = INDEX_F32;
const usize f64SymbolId = INDEX_F64;
const usize boolSymbolId = INDEX_BOOL;
const usize charSymbolId = INDEX_CHAR;
const usize stringSymbolId = INDEX_STRING;

const Type voidType =
{
	.index = INDEX_VOID,
	.type = SYMBOL_PRIMITIVE
};

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
	case EXPRESSION_IDENTIFIER:
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
	typeAnnotationFree(&node->annotation);
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
	typeAnnotationFree(&node->annotation);
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

typedef usize (*LiteralValidationFunction)(const Primitive *);

usize getFloatLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_FLOATING_POINT)
		return NOT_FOUND;

	return INDEX_F64;
}

usize getIntegerLiteralSymbolId(const Primitive *primitive)
{
	if (primitive)
	{
		switch (primitive->type)
		{
			// TODO: Add boolean and char
			case PRIMITIVE_UNSIGNED_INTEGER:
			case PRIMITIVE_SIGNED_INTEGER:
			case PRIMITIVE_FLOATING_POINT:
				return NOT_FOUND;

			default:
				break;
		}
	}

	return INDEX_I32;
}

usize getBooleanLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_BOOLEAN)
		return NOT_FOUND;

	return INDEX_BOOL;
}

usize getCharacterLiteralSymbolId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_CHARACTER)
		return NOT_FOUND;

	return INDEX_CHAR;
}

usize getStringLiteralSymboId(const Primitive *primitive)
{
	if (primitive && primitive->type == PRIMITIVE_STRING)
		return NOT_FOUND;

	return INDEX_STRING;
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
	if (type == NULL || type->type != SYMBOL_PRIMITIVE)
		return NULL;

	const Primitive *primitive = symbolTableGetPrimitive(type->index);

	return primitive;
}

usize getLiteralSymbolId(Literal *literal, const Type *expectedType)
{
	assert(literal != NULL);

	LiteralValidationFunction check = getLiteralValidationFunction(literal);
	const Primitive *primitive = getTypePrimitive(expectedType);
	usize index = check(primitive);

	if (index == NOT_FOUND)
		index = expectedType->index;

	return index;
}

Type getLiteralType(Literal *literal, const Type *expectedType)
{
	// TODO: Make this not always a primitive, because there are literal structs

	Type type =
	{
		.index = getLiteralSymbolId(literal, expectedType),
		.type = SYMBOL_PRIMITIVE
	};

	return type;
}

Type typeFromBlock(Block *block)
{
	Type type = block->hasReturnType
		? typeDuplicate(&block->returnType)
		: typeDuplicate(&voidType);

	return type;
}

Type typeFromIdentifier(Identifier *node)
{
	switch (node->type)
	{
		// case SYMBOL_FUNCTION: // TODO: Add function primitive
		case SYMBOL_VARIABLE:
		{
			Local *local = symbolTableGetVariable(node->index);

			return typeDuplicate(&local->annotation.type);
		}
		
		case SYMBOL_PARAMETER:
		{
			Local *local = symbolTableGetParameter(node->index);

			return typeDuplicate(&local->annotation.type);
		}

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Type for Identifier with SymbolType: %d.", node->type);
}

Type typeFromExpression(Expression *expression, const Type *expectedType)
{
	switch (expression->type)
	{
		case EXPRESSION_BLOCK:
			return typeFromBlock(expression->block);

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

		case EXPRESSION_IDENTIFIER:
			return typeFromIdentifier(&expression->identifier);

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Type for Expression of type: %d", expression->type);
}

Type typeDuplicate(const Type *type)
{
	return *type;
}

bool typeCanConvert(const Type *to, const Type *from)
{
	bool canConvert = to->type == from->type
		&& to->index == from->index;

	return canConvert;
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
			
		case EXPRESSION_IDENTIFIER:
			return expression->identifier.token;
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
	Symbol *symbol = symbolTableGetSymbol(type->index);
	char *name = stringDuplicate(symbol->key);

	return name;
}

Operators createOperators()
{
	exitNotImplemented();
}
