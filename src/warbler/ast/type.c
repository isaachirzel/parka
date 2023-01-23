#include "warbler/ast/type.h"
#include "warbler/ast.h"
#include "warbler/ast/function.h"
#include "warbler/ast/literal.h"
#include "warbler/ast/statement.h"
#include "warbler/symbol_table.h"
#include "warbler/util/print.h"

const Type voidType =
{
	.index = INDEX_VOID,
	.type = SYMBOL_PRIMITIVE
};

void typeFree(Type *type)
{
	assert(type);
	// TODO: pointers
}

void typeAnnotationFree(TypeAnnotation *node)
{
	typeFree(&node->type);
}

char *typeGetName(const Type *type)
{
	Symbol *symbol = symbolTableGetSymbol(type->index);
	char *name = stringDuplicate(symbol->key);

	return name;
}

bool typeCanConvert(const Type *to, const Type *from)
{
	bool canConvert = to->type == from->type
		&& to->index == from->index;

	return canConvert;
}

Type typeDuplicate(const Type *type)
{
	return *type;
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
			Variable *variable = symbolTableGetVariable(node->index);

			return typeDuplicate(&variable->annotation.type);
		}
		
		case SYMBOL_PARAMETER:
		{
			Parameter *parameter = symbolTableGetParameter(node->index);

			return typeDuplicate(&parameter->annotation.type);
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
			return literalGetType(expression->literal, expectedType);

		case EXPRESSION_IDENTIFIER:
			return typeFromIdentifier(&expression->identifier);

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Type for Expression of type: %d", expression->type);
}
