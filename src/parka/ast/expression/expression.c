
#include "parka/ast/expression/expression.h"
#include "parka/ast/expression/additive.h"
#include "parka/ast/expression/assignment.h"
#include "parka/ast/expression/bitwise_and.h"
#include "parka/ast/expression/bitwise_or.h"
#include "parka/ast/expression/bitwise_xor.h"
#include "parka/ast/expression/block.h"
#include "parka/ast/expression/boolean_and.h"
#include "parka/ast/expression/boolean_or.h"
#include "parka/ast/expression/conditional.h"
#include "parka/ast/expression/equality.h"
#include "parka/ast/expression/identifier.h"
#include "parka/ast/expression/multiplicative.h"
#include "parka/ast/expression/postfix.h"
#include "parka/ast/expression/prefix.h"
#include "parka/ast/expression/relational.h"
#include "parka/ast/expression/shift.h"
#include "parka/ast/expression/literal.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseExpression(Expression *out, Token *token)
{
	if (token->type == TOKEN_LEFT_BRACE)
		return parseBlock(out, token);

	return parseAssignment(out, token);
}

bool parsePrimaryExpression(Expression *out, Token *token)
{
	Expression node = { 0 };

	if (token->type == TOKEN_IDENTIFIER)
	{		
		if (!parseIdentifier(&node, token))
			goto error;
	}
	else if (token->type == TOKEN_LEFT_PARENTHESIS)
	{
		incrementToken(token);

		if (!parseExpression(&node, token))
			goto error;

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "expected ')' after primary sub-expression", NULL);
			goto error;
		}

		incrementToken(token);
	}
	else
	{
		if (!parseLiteral(&node, token))
			goto error;
	}

	*out = node;

	return true;

error:

	expressionFree(&node);
	return false;
}

bool validateExpression(Expression *node, LocalSymbolTable *localTable)
{
	switch (node->type)
	{
		case EXPRESSION_BLOCK:
			return validateBlock(node->block, localTable);

		case EXPRESSION_ASSIGNMENT:
			return validateAssignment(node->assignment, localTable);

		case EXPRESSION_CONDITIONAL:
			// evaluate types of both branch, confirm are the same and return that
			break;

		case EXPRESSION_BOOLEAN_OR:
			// confirm both types have bool operator
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
			return validateAdditiveExpression(node->additive, localTable);

		case EXPRESSION_MULTIPLICATIVE:
			return validateMultiplicativeExpression(node->multiplicative, localTable);

		case EXPRESSION_POSTFIX:
			return validatePostfix(node->postfix, localTable);

		case EXPRESSION_PREFIX:
			return validatePrefix(node->prefix, localTable);
		
		case EXPRESSION_LITERAL:
			return validateLiteral(node->literal);

		case EXPRESSION_IDENTIFIER:
			return validateIdentifier(node->identifier, localTable);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Expression with type: %d.", node->type);
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
		prefixFree(node->prefix);
		deallocate(node->prefix);
		break;
	case EXPRESSION_PREFIX:
		postfixFree(node->postfix);
		deallocate(node->postfix);
		break;
	case EXPRESSION_LITERAL:
		literalFree(node->literal);
		deallocate(node->literal);
		break;
	case EXPRESSION_IDENTIFIER:
		deallocate(node->identifier);
		break;

	default:
		exitWithErrorFmt("Invalid ExpressionType: %d", node->type);
	}
}

bool expressionGetType(Type *out, Expression *node, const Type *expected)
{
	switch (node->type)
	{
		case EXPRESSION_BLOCK:
			return blockGetType(out, node->block, expected);

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
			return additiveExpressionGetType(out, node->additive, expected);

		case EXPRESSION_MULTIPLICATIVE:
			break;

		case EXPRESSION_POSTFIX:
			break;
			
		case EXPRESSION_PREFIX:
			break;

		case EXPRESSION_LITERAL:
			return literalGetType(out, node->literal, expected);

		case EXPRESSION_IDENTIFIER:
			return identifierGetType(out, node->identifier, expected);

		default:
			break;
	}

	exitWithErrorFmt("Unable to get Type for Expression of type: %d", node->type);
}

Token expressionGetToken(const Expression *node)
{
	switch (node->type)
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
			return node->literal->token;
			
		case EXPRESSION_IDENTIFIER:
			return node->identifier->token;
	}

	exitWithErrorFmt("Unable to get Token for Expression of type: %d", node->type);
}
