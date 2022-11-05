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
		break;

	default:
		exitWithErrorFmt("Invalid ExpressionType: %d", self->type);
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
			exitWithErrorFmt("Invalid ExpressionType: %d", self->type);
	}
}

void freeStatementSyntax(StatementSyntax *self)
{
	if (self->isDeclaration)
	{
		freeDeclarationSyntax(self->declaration);
		deallocate(self->declaration);
	}
	else
	{
		freeExpressionSyntax(self->expression);
		deallocate(self->expression);
	}
}

void freeIfStatementSyntax(IfStatementSyntax *self)
{
	freeExpressionSyntax(&self->condition);

	if (self->type == IF_THEN_ELSE)
	{
		freeBlockSyntax(&self->elseBody);
	}
	else if (self->type == IF_THEN_ELSE)
	{
		freeIfStatementSyntax(self->elseIf);
		deallocate(self->elseIf);
	}
}

void freePackageSyntax(PackageSyntax *syntax)
{
	for (usize i = 0; i < syntax->moduleCount; ++i)
		freeModuleSyntax(&syntax->modules[i]);

	deallocate(syntax->name);
	deallocate(syntax->modules);
}

void freeProgramSyntax(ProgramSyntax *self)
{
	for (usize i = 0; i < self->packageCount; ++i)
		freePackageSyntax(&self->packages[i]);

	deallocate(self->packages);
}

void freeAdditiveExpressionSyntax(AdditiveExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(&syntax->rhs[i].expr);

	deallocate(syntax->rhs);
}

void freeBitwiseAndExpressionSyntax(BitwiseAndExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(syntax-> rhs + i);

	deallocate(syntax->rhs);
}

void freeBitwiseOrExpressionSyntax(BitwiseOrExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(syntax-> rhs + i);

	deallocate(syntax->rhs);
}

void freeBitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(syntax-> rhs + i);

	deallocate(syntax->rhs);
}

void freeBooleanAndExpressionSyntax(BooleanAndExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(syntax-> rhs + i);

	deallocate(syntax->rhs);
}

void freeBooleanOrExpressionSyntax(BooleanOrExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(syntax-> rhs + i);

	deallocate(syntax->rhs);
}

void freeConditionalRhsSyntax(ConditionalRhsSyntax *syntax)
{
	freeExpressionSyntax(&syntax->trueCase);
	freeExpressionSyntax(&syntax->falseCase);
}

void freeConditionalExpressionSyntax(ConditionalExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->expression);

	if (syntax->hasRhs)
		freeConditionalRhsSyntax(&syntax->rhs);
}

void freeEqualityExpressionSyntax(EqualityExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(&syntax->rhs[i].expr);

	deallocate(syntax->rhs);
}

void freeMultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(&syntax->rhs[i].expr);

	deallocate(syntax->rhs);
}

void freeRelationalExpressionSyntax(RelationalExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(&syntax->rhs[i].expr);

	deallocate(syntax->rhs);
}

void freeBitShiftExpressionSyntax(BitShiftExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);

	for (usize i = 0; i < syntax->rhsCount; ++i)
		freeExpressionSyntax(&syntax->rhs[i].expr);

	deallocate(syntax->rhs);
}

void freePrefixExpressionSyntax(PrefixExpressionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->expression);
}

void freeParameterSyntax(ParameterSyntax *syntax)
{
	freeTypeSyntax(&syntax->type);
}

void freeParameterListSyntax(ParameterListSyntax *syntax)
{
	for (usize i = 0; i < syntax->count; ++i)
		freeParameterSyntax(syntax->data + i);
		
	deallocate(syntax->data);
}

void freeFunctionSyntax(FunctionSyntax *syntax)
{
	freeExpressionSyntax(&syntax->body);
	freeParameterListSyntax(&syntax->parameters);

	if (syntax->hasReturnType)
		freeTypeSyntax(&syntax->returnType);
}

void freeBlockSyntax(BlockSyntax *syntax)
{
	for (usize i = 0; i< syntax->count; ++i)
		freeStatementSyntax(&syntax->statements[i]);
}

void freeDeclarationSyntax(DeclarationSyntax *syntax)
{
	freeVariableSyntax(&syntax->variable);
	freeExpressionSyntax(&syntax->value);
}

void freeVariableSyntax(VariableSyntax *syntax)
{
	freeTypeSyntax(&syntax->type);
}

void freeAssignmentSyntax(AssignmentSyntax *syntax)
{
	freeExpressionSyntax(&syntax->lhs);
	freeExpressionSyntax(&syntax->rhs);
}

void freeStructSyntax(StructSyntax *syntax)
{
	for (usize i = 0; i < syntax->memberCount; ++i)
		freeMemberSyntax(&syntax->members[i]);
}

void freeMemberSyntax(MemberSyntax *syntax)
{
	freeTypeSyntax(&syntax->type);
}

void freeTypeSyntax(TypeSyntax *syntax)
{
	deallocate(syntax->ptrs);
}

void freeModuleSyntax(ModuleSyntax *syntax)
{
	for (usize i = 0; i < syntax->functionCount; ++i)
		freeFunctionSyntax(&syntax->functions[i]);

	for (usize i = 0; i < syntax->structCount; ++i)
		freeStructSyntax(&syntax->structs[i]);

	deallocate(syntax->functions);
	deallocate(syntax->structs);
}
