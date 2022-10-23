#include <warbler/syntax.h>

#include <warbler/util/memory.h>
#include <warbler/util/print.h>

void freeConstantSyntax(ConstantSyntax *self)
{
	if (self->type == CONSTANT_STRING)
		deallocate(&self->string);
}

void freeExpressionSyntax(ExpressionSyntax *self)
{
	switch (self->type)
	{
	case EXPRESSION_ASSIGNMENT:
		freeAssignmentSyntax(self->assignment);
		break;
	case EXPRESSION_CONDITIONAL:
		freeConditionalExpressionSyntax(self->conditional);
		break;
	case EXPRESSION_BOOLEAN_OR:
		freeBooleanOrExpressionSyntax(self->booleanOr);
		break;
	case EXPRESSION_BOOLEAN_AND:
		freeBooleanAndExpressionSyntax(self->booleanAnd);
		break;
	case EXPRESSION_BITWISE_OR:
		freeBitwiseOrExpressionSyntax(self->bitwiseOr);
		break;
	case EXPRESSION_BITWISE_XOR:
		freeBitwiseXorExpressionSyntax(self->bitwiseXor);
		break;
	case EXPRESSION_BITWISE_AND:
		freeBitwiseAndExpressionSyntax(self->bitwiseAnd);
		break;
	case EXPRESSION_EQUALITY:
		freeEqualityExpressionSyntax(self->equality);
		break;
	case EXPRESSION_RELATIONAL:
		freeRelationalExpressionSyntax(self->relational);
		break;
	case EXPRESSION_SHIFT:
		freeBitShiftExpressionSyntax(self->shift);
		break;
	case EXPRESSION_ADDITIVE:
		freeAdditiveExpressionSyntax(self->additive);
		break;
	case EXPRESSION_MULTIPLICATIVE:
		freeMultiplicativeExpressionSyntax(self->multiplicative);
		break;
	case EXPRESSION_POSTFIX:
		freePrefixExpressionSyntax(self->prefix);
		break;
	case EXPRESSION_PREFIX:
		freePostfixExpressionSyntax(self->postfix);
		break;
	case EXPRESSION_CONSTANT:
		freeConstantSyntax(self->constant);
		break;
	case EXPRESSION_SYMBOL:
		freeSymbolSyntax(self->symbol);
		break;

	default:
		exitWithError("Invalid ExpressionType: %d", self->type);
	}
}

void freeArgumentListSyntax(ArgumentListSyntax *self)
{
	for (usize i = 0; i < self->count; ++i)
	{
		freeExpressionSyntax(self->expressions + i);
	}

	deallocate(self->expressions);
}

void freePostfixExpressionSyntax(PostfixExpressionSyntax *self)
{
	freeExpressionSyntax(&self->expression);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			freeExpressionSyntax(&self->index);
			break;

		case POSTFIX_FUNCTION_CALL:
			freeArgumentListSyntax(&self->arguments);
			break;

		case POSTFIX_MEMBER:
			break;

		default:
			exitWithError("Invalid ExpressionType: %d", self->type);
	}
}

void freeStatementSyntax(StatementSyntax *self)
{
	switch (self->type)
	{
		case STATEMENT_EXPRESSION:
			freeExpressionSyntax(self->expression);
			deallocate(self->block);
			break;
			
		case STATEMENT_BLOCK:
			freeBlockStatementSyntax(self->block);
			deallocate(self->block);
			break;
			
		case STATEMENT_DECLARATION:
			freeDeclarationSyntax(self->declaration);
			deallocate(self->declaration);
			break;
		
		default:
			exitWithError("Invalid StatementType: %d", self->type);
	}

	deallocate(self->expression); // Deallocate pointer of union
}

void freeIfStatementSyntax(IfStatementSyntax *self)
{
	freeExpressionSyntax(&self->condition);

	if (self->type == IF_THEN_ELSE)
	{
		freeBlockStatementSyntax(&self->elseBody);
	}
	else if (self->type == IF_THEN_ELSE)
	{
		freeIfStatementSyntax(self->elseIf);
		deallocate(self->elseIf);
	}
}

void freePackageSyntax(PackageSyntax *self)
{
	deallocate(self->name);

	for (usize i = 0; i < self->functionCount; ++i)
	{
		freeFunctionSyntax(self->functions + i);
	}

	for (usize i = 0; i < self->structCount; ++i)
	{
		freeStructSyntax(self->structs + i);
	}

	deallocate(self->functions);
	deallocate(self->structs);
}

void freeProgramSyntax(ProgramSyntax *self)
{
	for (usize i = 0; i < self->packageCount; ++i)
	{
		freePackageSyntax(self->packages + i);
	}

	deallocate(self->packages);
}
