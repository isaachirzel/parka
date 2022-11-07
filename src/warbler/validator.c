#include <warbler/validator.h>
#include <warbler/util/print.h>
#include <warbler/scope.h>
#include <string.h>

const char *annotationTypeName(AnnotationType type)
{
	switch (type)
	{
		case ANNOTATION_STRUCT:
			return "struct";

		case ANNOTATION_PRIMITIVE:
			return "primitive";

		default:
			return "type";
	}
}

bool validateType(TypeContext *out, const TypeSyntax *syntax)
{
	// TODO: Optimize name
	char *name = tokenGetText(&syntax->name);
	SymbolId *id = symbolTableResolve(name);

	if (!id)
	{
		printTokenError(&syntax->name, "The type '%s' does not exist this scope.", name);
		return false;
	}

	// TODO: Figure out how to handle invalid symbols
	// if (!data->isValid)
	// 	return false;

	AnnotationType annotationType;

	switch (id->type)
	{
		case SYMBOL_STRUCT:
			annotationType = ANNOTATION_STRUCT;
			break;

		case SYMBOL_PRIMITIVE:
			annotationType = ANNOTATION_PRIMITIVE;
			break;

		default:
		{
			const char *typeName = symbolTypeGetName(id->type);
			printTokenError(&syntax->name, "Expected type name, found %s '%s'.", typeName, name);
			return false;
		}
	}

	TypeContext type =
	{
		.type = annotationType,
		.id = *id
	};

	*out = type;
	return true;
}

bool validateStructMember(MemberContext *out, const MemberSyntax *syntax)
{
	out->name = tokenGetText(&syntax->name);
	out->isPublic = syntax->isPublic;

	if (!validateType(&out->type, &syntax->type))
		return false;

	return true;
}

bool validateStructDeclaration(const StructSyntax *syntax)
{
	return !!symbolTableDeclareStruct(syntax);
}

bool validateStructDefinition(const SymbolId *id, const StructSyntax *syntax)
{
	bool success = true;

	// TODO: Validate recursive types

	StructContext *context = symbolTableStructAt(id->index);

	context->memberCount = syntax->memberCount;
	makeArray(context->members, context->memberCount);

	for (usize i = 0; i < context->memberCount; ++i)
	{
		const MemberSyntax *memberSyntax = &syntax->members[i];

		for (usize j = 0; j < i; ++j)
		{
			if (tokenIsSame(&memberSyntax->name, &syntax->members[j].name))
			{
				success = false;
				// TODO: Stack based string
				char *name = tokenGetText(&memberSyntax->name);
				printTokenError(&syntax->name, "A member with name '%s' is already declared in struct '%s'.", name, context->symbol);
				// TODO: Show previous declaration
				deallocate(name);
				// Break to avoid showing duplicate, incorrect errors
				break;
			}
		}

		success = success && validateStructMember(&context->members[i], memberSyntax);
	}

	return success;
}

bool validateConstant(ExpressionContext *out, const ConstantSyntax *syntax)
{
	ConstantContext context =
	{
		.type = syntax->type
	};

	switch (syntax->type)
	{
		case CONSTANT_CHARACTER:
			context.character = syntax->character;
			break;

		case CONSTANT_STRING:
			context.string = duplicateString(syntax->string);
			break;

		case CONSTANT_INTEGER:
			context.integer = syntax->integer;
			break;

		case CONSTANT_FLOAT:
			context.floating = syntax->floating;
			break;

		case CONSTANT_BOOLEAN:
			context.boolean = syntax->boolean;
			break;

		default:
			exitWithErrorFmt("Invalid constant type: %d.", syntax->type);
	}

	return true;
}

bool validateSymbol(ExpressionContext *out, const SymbolSyntax *syntax)
{
	bool success = true;
	char *symbol = tokenGetText(&syntax->token);
	SymbolId *id = symbolTableFind(symbol);

	success = success && id;

	if (!id)
	{
		printTokenError(&syntax->token, "The symbol '%s' could not be found in this scope.", symbol);
	}
	else
	{
		*makeNew(out->symbolId) = *id;
		out->type = EXPRESSION_SYMBOL;
	}

	deallocate(symbol);
	
	return success;
}

bool validateAssignment(ExpressionContext *out, const AssignmentSyntax *syntax)
{
	AssignmentContext context =
	{
		.type = syntax->type
	};

	bool success = true;

	success = success && validateExpression(&context.lhs, &syntax->lhs);
	success = success && validateExpression(&context.rhs, &syntax->rhs);

	// TODO: validate type of assignment

	if (!success)
	{
		freeAssignmentContext(&context);
		return false;
	}

	*makeNew(out->assignment) = context;
	out->type = EXPRESSION_ASSIGNMENT;

	return true;
}

bool validateBlock(ExpressionContext *out, const BlockSyntax *syntax)
{
	bool success = true;
	BlockContext context =
	{
		.count = syntax->count
	};

	makeArray(context.statements, syntax->count);

	for (usize i = 0; i < syntax->count; ++i)
		success = success && validateStatement(&context.statements[i], &syntax->statements[i]);

	if (!success)
		goto error;

	*makeNew(out->block) = context;
	out->type = EXPRESSION_BLOCK;

	return true;

error:

	freeBlockContext(&context);
	return false;
}

bool validatePrefix(ExpressionContext *out, const PrefixSyntax *syntax)
{
	exitNotImplemented();
}

bool validateArgumentList(ArgumentListContext *out, const ArgumentListSyntax *syntax)
{
	exitNotImplemented();
}

bool validatePostfix(ExpressionContext *out, const PostfixSyntax *syntax)
{
	PostfixContext context = { 0 };

	if (!validateExpression(&context.expression, &syntax->expression))
		goto error;
	
	switch (syntax->type)
	{
		case POSTFIX_INDEX:
			exitWithError("Postfix indexing not implemented");
			break;

		case POSTFIX_FUNCTION_CALL:
			exitWithError("Postfix function call not implemented");
			break;

		case POSTFIX_MEMBER:
			exitWithError("Postfix member validation not implemented");
			break;
	}

	*makeNew(out->postfix) = context;
	out->type = EXPRESSION_POSTFIX;
	return true;

error:

	freePostfixContext(&context);
	return false;
}

bool validateExpression(ExpressionContext *out, const ExpressionSyntax *syntax)
{
	switch (syntax->type)
	{
		case EXPRESSION_BLOCK:
			return validateBlock(out, syntax->block);

		case EXPRESSION_CONSTANT:
			return validateConstant(out, syntax->constant);

		case EXPRESSION_SYMBOL:
			return validateSymbol(out, syntax->symbol);

		case EXPRESSION_ASSIGNMENT:
			return validateAssignment(out, syntax->assignment);

		case EXPRESSION_PREFIX:
			return validatePrefix(out, syntax->prefix);

		case EXPRESSION_POSTFIX:
			return validatePostfix(out, syntax->postfix);

		default:
			exitWithErrorFmt("Invalid expression type: %d.", syntax->type);
	}
}

static bool validateStructConversion(const Token *token, const TypeContext *to, const TypeContext *from)
{
	exitNotImplemented();

	// assert(to->type == ANNOTATION_STRUCT);
	// assert(from->type == ANNOTATION_STRUCT);
}

static bool validateConstantToPrimitiveConversion(const TypeContext *to, const TypeContext *from)
{
	exitNotImplemented();
}

static const char *getConstantTypeName(ConstantType type)
{
	switch (type)
	{
		case CONSTANT_CHARACTER:
			return "char";

		case CONSTANT_STRING:
			return "string literal";
			
		case CONSTANT_INTEGER:
			return "integer";

		case CONSTANT_FLOAT:
			return "float";

		case CONSTANT_BOOLEAN:
			return "bool";

		default:
			exitWithErrorFmt("Invalid constant type: %d.", type);
	}
}

static TypeContext getExpressionType(const ExpressionContext *expression)
{
	exitNotImplemented();
}

static bool validateExpressionConversion(TypeContext *out, const ExpressionContext *from, const TypeContext *to)
{
	exitNotImplemented();
}

bool validateVariable(const VariableSyntax *syntax, const ExpressionContext *value)
{
	bool success = true;

	SymbolId *id = symbolTableDeclareVariable(syntax);

	success = success && id;

	VariableContext *context = symbolTableVariableAt(id->index);

	context->isExplicitlyTyped = syntax->isExplicitlyTyped;
	context->isMutable = syntax->isMutable;

	if (syntax->isExplicitlyTyped)
	{
		success = success && validateType(&context->type, &syntax->type);
	}
	else
	{
		context->type = getExpressionType(value);
	}

	return success;
}

bool validateDeclaration(DeclarationContext *out, const DeclarationSyntax *syntax)
{
	DeclarationContext context = { 0 };
	
	if (!validateExpression(&context.value, &syntax->value))
		goto error;

	if (!validateVariable(&syntax->variable, &context.value))
		goto error;

	*out = context;
	return true;

error:

	freeDeclarationContext(&context);
	return false;
}

bool validateStatement(StatementContext *out, const StatementSyntax *syntax)
{
	if (syntax->isDeclaration)
	{
		DeclarationContext declaration;
		
		if (!validateDeclaration(&declaration, syntax->declaration))
			return false;

		*makeNew(out->declaration) = declaration;
	}
	else
	{
		ExpressionContext expression;

		if (!validateExpression(&expression, syntax->expression))
			return false;

		*makeNew(out->expression) = expression;
	}

	out->isDeclaration = syntax->isDeclaration;

	return true;
}

bool validateParameter(SymbolId *out, const ParameterSyntax *syntax)
{	
	SymbolId *id = symbolTableDeclareParameter(syntax);

	if (!id)
		return false;

	ParameterContext *context = symbolTableParameterAt(id->index);

	context->isMutable = syntax->isMutable;

	if (!validateType(&context->type, &syntax->type))
		return false;

	*out = *id;

	return true;
}

bool validateParameterList(SymbolIdList *out, const ParameterListSyntax *syntax)
{
	bool success = true;
	SymbolIdList ids =
	{
		.type = SYMBOL_PARAMETER,
		.count = syntax->count
	};

	makeArray(ids.indeces, ids.count);

	for (usize i = 0; i < syntax->count; ++i)
	{
		SymbolId parameterId;

		success = success && validateParameter(&parameterId, &syntax->data[i]);

		// Ok to do whether or not failure
		ids.indeces[i] = parameterId.index;
	}

	if (success)
	{
		*out = ids;
	}
	else
	{
		freeSymbolIdList(&ids);
	}

	return success;
}

bool validateFunctionDeclaration(const FunctionSyntax *syntax)
{
	bool success = true;

	SymbolId *id = symbolTableDeclareFunction(syntax);

	success = success && id;

	if (!id)
		return false;

	FunctionContext *context = symbolTableFunctionAt(id->index);

	success = success && validateParameterList(&context->parameters, &syntax->parameters);

	if (syntax->hasReturnType)
	{
		success = success && validateType(&context->returnType, &syntax->returnType);
	}
	else
	{
		context->returnType = (TypeContext)
		{
			.type = ANNOTATION_PRIMITIVE,
			.id = {
				.type = SYMBOL_PRIMITIVE,
				.index = VOID_INDEX
			}
		};
	}

	return success;
}

bool validateFunctionDefinition(const SymbolId *id, const FunctionSyntax *syntax)
{
	bool success = true;

	FunctionContext *context = symbolTableFunctionAt(id->index);

	success = success && validateExpression(&context->body, &syntax->body);

	return success;
}

bool validateModuleDeclarations(const ModuleSyntax *syntax)
{
	bool success = true;

	for (usize i = 0; i < syntax->functionCount; ++i)
		success = success && validateFunctionDeclaration(&syntax->functions[i]);

	for (usize i = 0; i < syntax->structCount; ++i)
		success = success && validateStructDeclaration(&syntax->structs[i]);

	return success;
}

bool validatePackageDeclarations(const PackageSyntax *syntax)
{
	bool success = true;

	symbolTableDeclarePackage(syntax->name);

	for (usize i = 0; i < syntax->moduleCount; ++i)
		success = success && validateModuleDeclarations(&syntax->modules[i]);

	return success;
}

bool validate(ProgramContext *out, const ProgramSyntax *syntax)
{
	bool success = true;

	symbolTableInitialize();

	for (usize i = 0; i < syntax->packageCount; ++i)
		success = success && validatePackageDeclarations(&syntax->packages[i]);

	usize count = symbolTableGetValidationCount();

	for (usize i = 0; i < count; ++i)
	{
		const Validation *validation = symbolTableValidationAt(i);

		switch (validation->id.type)
		{
			case SYMBOL_STRUCT:
				validateStructDefinition(&validation->id, validation->structSyntax);
				break;

			case SYMBOL_FUNCTION:
				validateFunctionDefinition(&validation->id, validation->functionSyntax);
				break;

			default:
				exitWithErrorFmt("Invalid validation symbol type: %d", validation->id.type);
		}
	}

	if (success)
	{
		*out = symbolTableExport();
	}
	else
	{
		symbolTableDestroy();
	}

	return success;
}
