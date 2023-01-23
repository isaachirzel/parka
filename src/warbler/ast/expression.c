#include "warbler/ast.h"
#include "warbler/ast/expression.h"
#include "warbler/ast/literal.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"
#include "warbler/ast/statement.h"

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

void ifExpressionFree(IfStatement *node)
{
	expressionFree(&node->condition);
	statementFree(node->thenCase);

	if (node->type == IF_THEN_ELSE)
	{
		statementFree(node->elseCase);
	}
	else if (node->type == IF_THEN_ELSE)
	{
		ifExpressionFree(node->elseIf);
		deallocate(node->elseIf);
	}
}

void blockFree(Block *node)
{
	for (usize i = 0; i< node->count; ++i)
		statementFree(&node->statements[i]);
}

void assignmentFree(Assignment *node)
{
	expressionFree(&node->lhs);
	expressionFree(&node->rhs);
}
