#include <warbler/parser.h>

#include <warbler/util/memory.h>
#include <warbler/util/print.h>
#include <warbler/directory.h>
#include <assert.h>

bool parseAdditiveExpression(ExpressionSyntax *out, Token *token)
{
	AdditiveExpressionSyntax syntax = { 0 };

	if (!parseMultiplicativeExpression(&syntax.lhs, token))
		goto error;

	while (true)
	{
		AdditiveType type;

		if (token->type == TOKEN_PLUS)
		{
			type = ADDITIVE_ADD;
		}
		else if (token->type == TOKEN_MINUS)
		{
			type = ADDITIVE_ADD;
		}
		else
		{
			break;
		}

		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseMultiplicativeExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = (AdditiveRhsSyntax)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->additive = allocate(sizeof(*out->additive));
	out->type = EXPRESSION_MULTIPLICATIVE;
	*out->additive = syntax;
	
	return true;

error:

	freeAdditiveExpressionSyntax(&syntax);

	return false;
}

bool parseBitwiseAndExpression(ExpressionSyntax *out, Token *token)
{
	BitwiseAndExpressionSyntax syntax = { 0 };

	if (!parseEqualityExpression(&syntax.lhs, token))
		goto error;

	while (token->type == TOKEN_AMPERSAND)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseEqualityExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = expression;
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_AND;
	out->bitwiseAnd = new(BitwiseAndExpressionSyntax);
	*out->bitwiseAnd = syntax;

	return true;

error:

	freeBitwiseAndExpressionSyntax(&syntax);
	return false;
}

bool parseBitwiseOrExpression(ExpressionSyntax *out, Token *token)
{
	BitwiseOrExpressionSyntax syntax = { 0 };

	if (!parseBitwiseXorExpression(&syntax.lhs, token))
		goto error;

	while (token->type == TOKEN_PIPE)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseBitwiseXorExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = expression;
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_OR;
	*makeNew(out->bitwiseOr) = syntax;

	return true;
	
error:

	freeBitwiseOrExpressionSyntax(&syntax);
	return false;
}

bool parseBitwiseXorExpression(ExpressionSyntax *out, Token *token)
{
	BitwiseXorExpressionSyntax syntax = { 0 };

	if (!parseBitwiseAndExpression(&syntax.lhs, token))
		goto error;

	while (token->type == TOKEN_CARROT)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseBitwiseAndExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = expression;
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_XOR;
	*makeNew(out->bitwiseXor) = syntax;

	return true;
	
error:

	freeBitwiseXorExpressionSyntax(&syntax);
	return false;
}

bool parseBooleanAndExpression(ExpressionSyntax *out, Token *token)
{
	BooleanAndExpressionSyntax syntax = { 0 };

	if (!parseBitwiseOrExpression(&syntax.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_AND)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseBitwiseOrExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = expression;
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_AND;
	out->booleanAnd = new(BooleanAndExpressionSyntax);
	*out->booleanAnd = syntax;

	return true;
	
error:

	freeBooleanAndExpressionSyntax(&syntax);
	return false;
}

bool parseBooleanOrExpression(ExpressionSyntax *out, Token *token)
{
	BooleanOrExpressionSyntax syntax = { 0 };

	if (!parseBooleanAndExpression(&syntax.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_OR)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseBooleanAndExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = expression;
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_OR;
	*makeNew(out->booleanOr) = syntax;

	return true;
	
error:

	freeBooleanOrExpressionSyntax(&syntax);
	return false;
}

bool parseConditionalExpression(ExpressionSyntax *out, Token *token)
{
	ConditionalExpressionSyntax syntax = { 0 };

	if (!parseBooleanOrExpression(&syntax.expression, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_THEN)
	{
		*out = syntax.expression;
		return true;
	}

	incrementToken(token);

	syntax.hasRhs = true;

	if (!parseBooleanOrExpression(&syntax.rhs.trueCase, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_ELSE)
	{
		printParseError(token, "'else' or false case", NULL);
		goto error;
	}

	incrementToken(token);

	ExpressionSyntax falseCase;

	if (!parseBooleanOrExpression(&syntax.rhs.falseCase, token))
		goto error;

	out->type = EXPRESSION_CONDITIONAL;
	*makeNew(out->conditional) = syntax;

	return true;
	
error:

	freeConditionalExpressionSyntax(&syntax);
	return false;
}

bool parseEqualityExpression(ExpressionSyntax *out, Token *token)
{
	EqualityExpressionSyntax syntax = { 0 };

	if (!parseRelationalExpression(&syntax.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		EqualityType type;
		switch (token->type)
		{
			case TOKEN_EQUALS:
				type = EQUALITY_EQUALS;
				break;

			case TOKEN_NOT_EQUALS:
				type = EQUALITY_NOT_EQUALS;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseRelationalExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = (EqualityRhsSyntax)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_EQUALITY;
	*makeNew(out->equality) = syntax;

	return true;
	
error:

	freeEqualityExpressionSyntax(&syntax);
	return false;
}


bool parseMultiplicativeExpression(ExpressionSyntax *out, Token *token)
{
	MultiplicativeExpressionSyntax syntax = { 0 };

	if (!parsePrefixExpression(&syntax.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		MultiplicativeType type;
		switch (token->type)
		{
			case TOKEN_MODULUS:
				type = MULTIPLICATIVE_MODULUS;
				break;

			case TOKEN_ASTERISK:
				type = MULTIPLICATIVE_MULTIPLY;
				break;

			case TOKEN_SLASH:
				type = MULTIPLICATIVE_DIVIDE;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		ExpressionSyntax expression;

		if (!parsePrefixExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = (MultiplicativeRhsSyntax)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
		return true;
	}

	out->type = EXPRESSION_MULTIPLICATIVE;
	*makeNew(out->multiplicative) = syntax;

	return true;
	
error:

	freeMultiplicativeExpressionSyntax(&syntax);
	return false;
}

bool parseArgumentList(ArgumentListSyntax* out, Token *token)
{
	assert(token->type == TOKEN_LEFT_PARENTHESIS);
	incrementToken(token);

	ArgumentListSyntax syntax = { 0 };

parseArgument:

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseExpression(&expression, token))
			goto error;
		
		syntax.expressions = resizeArray(syntax.expressions, ++syntax.count);
		syntax.expressions[syntax.count - 1] = expression;

		if (token->type == TOKEN_COMMA)
		{
			incrementToken(token);
			goto parseArgument;
		}

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "')' after function arguments", NULL);
			return false;
		}
	}

	incrementToken(token);

	*out = syntax;

	// return arguments
	return true;
	
error:

	freeArgumentListSyntax(&syntax);
	return false;
}

bool parsePostfixExpression(ExpressionSyntax *out, Token *token)
{
	PostfixExpressionSyntax syntax = { 0 };

	if (!parsePrimaryExpression(&syntax.expression, token))
		goto error;

parsePostfix:

	switch (token->type)
	{
		case TOKEN_LEFT_BRACKET: // Index
			incrementToken(token);

			ExpressionSyntax index;

			if (!parseExpression(&index, token))
				goto error;

			syntax.type = POSTFIX_INDEX;
			syntax.index = index;

			if (token->type != TOKEN_RIGHT_BRACKET)
			{
				printParseError(token, "']' after index operation", NULL);
				goto error;
			}

			incrementToken(token);
			break;

		case TOKEN_LEFT_PARENTHESIS: // Function call
			incrementToken(token);

			ArgumentListSyntax arguments;

			if (!parseArgumentList(&arguments, token))
				goto error;

			syntax.type = POSTFIX_FUNCTION_CALL;
			syntax.arguments = arguments;

			if (token->type != TOKEN_RIGHT_PARENTHESIS)
			{
				printParseError(token, "')' after function call", NULL);
				goto error;
			}

			incrementToken(token);
			break;

		case TOKEN_DOT: // Member
			incrementToken(token);
		
			if (token->type != TOKEN_IDENTIFIER)
			{
				printParseError(token, "member, method, or property name", NULL);
				goto error;
			}

			Token name = *token;

			incrementToken(token);
			
			syntax.type = POSTFIX_MEMBER;
			syntax.member = name;
			break;
		
		default:
			goto finish;
	}

	ExpressionSyntax inner =
	{
		.type = EXPRESSION_POSTFIX,
		.postfix = new(PostfixExpressionSyntax)
	};

	*inner.postfix = syntax;

	syntax = (PostfixExpressionSyntax)
	{
		.expression = inner
	};

	goto parsePostfix;

finish:

	*out = syntax.expression;

	return true;
	
error:

	freePostfixExpressionSyntax(&syntax);
	return false;
}

bool parsePrefixExpression(ExpressionSyntax *out, Token *token)
{
	PrefixExpressionSyntax syntax = { 0 };

	switch (token->type)
	{
		case TOKEN_AMPERSAND:
			syntax.type = PREFIX_REFERENCE;
			break;

		case TOKEN_ASTERISK:
			syntax.type = PREFIX_DEREFERENCE;
			break;

		case TOKEN_PLUS:
			syntax.type = PREFIX_POSITIVE;
			break;

		case TOKEN_MINUS:
			syntax.type = PREFIX_NEGATIVE;
			break;

		case TOKEN_BITWISE_NOT:
			syntax.type = PREFIX_BITWISE_NOT;
			break;

		case TOKEN_BOOLEAN_NOT:
			syntax.type = PREFIX_BOOLEAN_NOT;
			break;

		default:
			return parsePostfixExpression(out, token);
	}

	syntax.token = *token;

	incrementToken(token);

	if (!parsePrefixExpression(&syntax.expression, token))
		goto error;

	return true;
	
error:

	freePrefixExpressionSyntax(&syntax);
	return false;
}

bool parsePrimaryExpression(ExpressionSyntax *out, Token *token)
{
	ExpressionSyntax syntax = { 0 };

	if (token->type == TOKEN_IDENTIFIER)
	{		
		if (!parseSymbol(&syntax, token))
			goto error;
	}
	else if (token->type == TOKEN_LEFT_PARENTHESIS)
	{
		incrementToken(token);

		if (!parseExpression(&syntax, token))
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
		if (!parseConstant(&syntax, token))
			goto error;
	}

	*out = syntax;

	return true;

error:

	freeExpressionSyntax(&syntax);
	return false;
}

bool parseRelationalExpression(ExpressionSyntax *out, Token *token)
{
	RelationalExpressionSyntax syntax = { 0 };

	if (!parseBitShiftExpression(&syntax.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		RelationalType type;
		switch (token->type)
		{
			case TOKEN_GREATER_THAN:
				type = RELATIONAL_GREATER_THAN;
				break;

			case TOKEN_LESS_THAN:
				type = RELATIONAL_LESS_THAN;
				break;

			case TOKEN_GREATER_THAN_OR_EQUAL_TO:
				type = RELATIONAL_GREATER_THAN_OR_EQUAL_TO;
				break;

			case TOKEN_LESS_THAN_OR_EQUAL_TO:
				type = RELATIONAL_LESS_THAN_OR_EQUAL_TO;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseBitShiftExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = (RelationalRhsSyntax)
		{
			.expr = expression,
			.type = type
		};
	}

	if (!syntax.rhs)
	{
		*out = syntax.lhs;
	}
	else
	{
		out->type = EXPRESSION_RELATIONAL;
		out->relational = new(RelationalExpressionSyntax);
		*out->relational = syntax;
	}

	return true;
	
error:

	freeRelationalExpressionSyntax(&syntax);
	return false;
}

bool parseBitShiftExpression(ExpressionSyntax *out, Token *token)
{
	BitShiftExpressionSyntax syntax = { 0 };

	if (!parseAdditiveExpression(&syntax.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;
		BitShiftType type;

		switch (token->type)
		{
			case TOKEN_LEFT_BIT_SHIFT:
				type = BIT_SHIFT_LEFT;
				break;

			case TOKEN_RIGHT_BIT_SHIFT:
				type = BIT_SHIFT_RIGHT;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;
		
		incrementToken(token);

		ExpressionSyntax expression;

		if (!parseAdditiveExpression(&expression, token))
			goto error;

		syntax.rhs = resizeArray(syntax.rhs, ++syntax.rhsCount);
		syntax.rhs[syntax.rhsCount - 1] = (BitShiftRhsSyntax)
		{
			.type = type,
			.expr = expression
		};
	}
	
	if (!syntax.rhs)
	{
		*out = syntax.lhs;
	}
	else
	{
		out->type = EXPRESSION_SHIFT;
		*makeNew(out->shift) = syntax;
	}

	return true;
	
error:

	freeBitShiftExpressionSyntax(&syntax);
	return false;
}

bool parseAssignment(ExpressionSyntax *out, Token *token)
{
	AssignmentSyntax syntax = { 0 };

	if (!parseConditionalExpression(&syntax.lhs, token))
		goto error;

	AssignmentType type;
	switch (token->type)
	{
		case TOKEN_ASSIGN:
			type = ASSIGNMENT_BECOME;
			break;

		case TOKEN_MULTIPLY_ASSIGN:
			type = ASSIGNMENT_MULTIPLY;
			break;

		case TOKEN_DIVIDE_ASSIGN:
			type = ASSIGNMENT_DIVIDE;
			break;

		case TOKEN_MODULUS_ASSIGN:
			type = ASSIGNMENT_MODULUS;
			break;

		case TOKEN_ADD_ASSIGN:
			type = ASSIGNMENT_ADD;
			break;

		case TOKEN_SUBTRACT_ASSIGN:
			type = ASSIGNMENT_SUBTRACT;
			break;

		case TOKEN_LEFT_BIT_SHIFT_ASSIGN:
			type = ASSIGNMENT_LEFT_BIT_SHIFT;
			break;

		case TOKEN_RIGHT_BIT_SHIFT_ASSIGN:
			type = ASSIGNMENT_RIGHT_BIT_SHIFT;
			break;

		case TOKEN_BITWISE_AND_ASSIGN:
			type = ASSIGNMENT_BITWISE_AND;
			break;

		case TOKEN_BITWISE_OR_ASSIGN:
			type = ASSIGNMENT_BITWISE_OR;
			break;

		case TOKEN_BITWISE_XOR_ASSIGN:
			type = ASSIGNMENT_BITWISE_XOR;
			break;
		
		default:
			*out = syntax.lhs;
			return true;
	}

	syntax.type = type;

	incrementToken(token);

	if (!parseConditionalExpression(&syntax.rhs, token))
		goto error;

	return true;
	
error:

	freeAssignmentSyntax(&syntax);
	return false;
}

bool parseExpression(ExpressionSyntax *out, Token *token)
{
	if (token->type == TOKEN_LEFT_BRACE)
		return parseBlock(out, token);

	return parseAssignment(out, token);
}

static bool parseCharacterConstant(ExpressionSyntax *out, Token *token)
{
	if (token->length != 3)
	{
		printTokenError(token, "character literals may only contain 1 character", NULL);
		return false;
	}

	out->type = EXPRESSION_CONSTANT;
	*makeNew(out->constant) = (ConstantSyntax)
	{
		.token = *token,
		.character = tokenGetChar(token, 1),
		.type = CONSTANT_CHARACTER
	};

	incrementToken(token);

	return true;
}

static bool parseFloatConstant(ExpressionSyntax *out, Token *token)
{
	// TODO: account for multiple decimals when parsing float

	f64 value = 0.0;
	for (usize i = 0; i < token->length; ++i)
	{
		if (tokenGetChar(token, i) != '.')
		{
			value = value * 10.0 + (tokenGetChar(token, i) - '0');
		}
		else
		{
			i += 1;

			f64 decimal = 0.0;
			f64 place = 1.0;

			while (i < token->length)
			{
				decimal = decimal * 10.0 + (tokenGetChar(token, i) - '0');
				place *= 10.0;
				++i;
			}
			
			value += (decimal / place);
			break;
		}
	}
	
	out->type = EXPRESSION_CONSTANT;
	*makeNew(out->constant) = (ConstantSyntax)
	{
		.token = *token,
		.type = CONSTANT_FLOAT,
		.floating = value
	};

	incrementToken(token);

	return true;
}

static bool parseStringConstant(ExpressionSyntax *out, Token *token)
{
	out->type = EXPRESSION_CONSTANT;
	*makeNew(out->constant) = (ConstantSyntax)
	{
		.token = *token,
		.string = tokenGetText(token),
		.type = CONSTANT_STRING
	};

	incrementToken(token);

	return true;
}

static bool parseIntegerConstant(ExpressionSyntax *out, Token *token)
{
	// TODO: Calculate required size for integers
	// TODO: Confirm will fit in required size

	u64 value = 0;

	for (usize i = 0; i < token->length; ++i)
		value = value * 10 + (tokenGetChar(token, i) - '0');

	out->type = EXPRESSION_CONSTANT;
	*makeNew(out->constant) = (ConstantSyntax)
	{
		.token = *token,
		.integer = value,
		.type = CONSTANT_INTEGER
	};

	incrementToken(token);
	
	return true;
}

bool parseBooleanConstant(ExpressionSyntax *out, Token *token)
{
	out->type = EXPRESSION_CONSTANT;
	*makeNew(out->constant) = (ConstantSyntax)
	{
		.type = CONSTANT_BOOLEAN,
		.token = *token,
		.boolean = token->type == TOKEN_KEYWORD_TRUE
	};

	incrementToken(token);

	return true;
}

bool parseConstant(ExpressionSyntax *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_CHARACTER_LITERAL:
			return parseCharacterConstant(out, token);

		case TOKEN_STRING_LITERAL:
			return parseStringConstant(out, token);

		case TOKEN_INTEGER_LITERAL:
			return parseIntegerConstant(out, token);

		case TOKEN_FLOAT_LITERAL:
			return parseFloatConstant(out, token);

		case TOKEN_KEYWORD_TRUE:
		case TOKEN_KEYWORD_FALSE:
			return parseBooleanConstant(out, token);

		default:
			printParseError(token, "constant", NULL);
			return false;
	}
}

bool parseSymbol(ExpressionSyntax *out, Token *token)
{
	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "symbol", NULL);
		return false;
	}

	SymbolSyntax *symbol = new(SymbolSyntax);

	*symbol = (SymbolSyntax) { *token };

	incrementToken(token);

	*out = (ExpressionSyntax)
	{
		.type = EXPRESSION_SYMBOL,
		.symbol = symbol
	};

	return true;
}

bool parseFunction(FunctionSyntax *out, Token *token)
{
	assert(token->type == TOKEN_KEYWORD_FUNCTION);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "function name", NULL);
		return false;
	}

	FunctionSyntax syntax =
	{
		.name = *token,
	};

	incrementToken(token);

	if (!parseFunctionSignature(&syntax.signature, token))
		goto error;

	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' after function signature", NULL);
		goto error;
	}

	if (!parseBlock(&syntax.body, token))
		goto error;

	*out = syntax;

	return true;

error:

	freeFunctionSyntax(&syntax);
	return false;
}

bool parseParameter(ParameterSyntax *out, Token *token)
{
	ParameterSyntax syntax = { 0 };

	if (token->type == TOKEN_KEYWORD_MUT)
	{
		syntax.isMutable = true;
		incrementToken(token);
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "parameter name", NULL);
		goto error;
	}

	syntax.name = *token;

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, ":", "parameters require a valid type");
		return false;
	}

	incrementToken(token);

	if (!parseType(&syntax.type, token))
		goto error;

	*out = syntax;
	return true;

error:

	freeParameterSyntax(&syntax);
	return false;
}

bool parseParameterList(ParameterListSyntax *out, Token *token)
{
	if (token->type != TOKEN_LEFT_PARENTHESIS)
	{
		printParseError(token, "'(' after function name", NULL);
		return false;
	}

	ParameterListSyntax syntax = { 0 };

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		while (true)
		{
			ParameterSyntax parameter = { 0 };

			if (!parseParameter(&parameter, token))
				goto error;

			syntax.data = resizeArray(syntax.data, ++syntax.count);
			syntax.data[syntax.count - 1] = parameter;

			if (token->type != TOKEN_COMMA)
				break;

			incrementToken(token);
		}

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "')'", "Invalid tokens in parameter list");
			goto error;
		}
	}

	incrementToken(token);

	*out = syntax;
	return true;

error:

	freeParameterListSyntax(&syntax);
	return false;
}

bool parseFunctionSignature(FunctionSignatureSyntax *out, Token *token)
{
	FunctionSignatureSyntax syntax = { 0 };

	if (!parseParameterList(&syntax.parameters, token))
		goto error;

	if (token->type != TOKEN_COLON)
		return true;

	incrementToken(token);

	if (!parseType(&syntax.returnType, token))
		goto error;

	syntax.hasReturnType = true;

	*out = syntax;
	return true;

error:

	freeFunctionSignatureSyntax(&syntax);
	return false;
}

bool parseBlock(ExpressionSyntax *out, Token *token)
{
	assert(token->type == TOKEN_LEFT_BRACE);

	incrementToken(token);

	BlockSyntax syntax = { 0 };

	while (true)
	{
		if (token->type == TOKEN_RIGHT_BRACE)
			break;

		if (token->type == TOKEN_END_OF_FILE)
		{
			printParseError(token, "'}'", NULL);
			return false;
		}

		StatementSyntax statement = { 0 };

		if (!parseStatement(&statement, token))
			goto error;

		syntax.statements = resizeArray(syntax.statements, ++syntax.count);
		syntax.statements[syntax.count - 1] = statement;
	}

	incrementToken(token);

	*makeNew(out->block) = syntax;
	out->type = EXPRESSION_BLOCK;

	return true;

error:

	freeBlockSyntax(&syntax);
	return false;
}

bool parseDeclaration(DeclarationSyntax *out, Token *token)
{
	DeclarationSyntax syntax = { 0 };

	if (!parseVariable(&syntax.variable, token))
		goto error;

	if (token->type != TOKEN_ASSIGN)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	if (!parseExpression(&syntax.value, token))
		goto error;


	if (token->type != TOKEN_SEMICOLON)
	{
		printParseError(token, "expected ';' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	*out = syntax;
	return true;

error:

	freeDeclarationSyntax(&syntax);
	return false;
}

bool parseStatement(StatementSyntax *out, Token *token)
{
	if (token->type == TOKEN_KEYWORD_VAR)
	{
		DeclarationSyntax declaration;

		if (!parseDeclaration(&declaration, token))
			return false;

		*makeNew(out->declaration) = declaration;
		out->isDeclaration = true;

		return true;
	}

	ExpressionSyntax expression;

	if (!parseExpression(&expression, token))
		return false;

	if (token->type != TOKEN_SEMICOLON)
	{
		printParseError(token, "';' after expression statement", NULL);
		freeExpressionSyntax(&expression);
		return false;
	}

	incrementToken(token);

	*makeNew(out->expression) = expression;
	out->isDeclaration = false;

	return true;
}

bool parseMember(MemberSyntax *out, Token *token)
{
	MemberSyntax syntax = { 0 };

	if (token->type == TOKEN_KEYWORD_PUBLIC)
	{
		syntax.isPublic = true;
		incrementToken(token);
	}
	else if (token->type == TOKEN_KEYWORD_PRIVATE)
	{
		incrementToken(token);
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "member name", NULL);
		printNote("Trailing commas are not allowed.");
		goto error;
	}

	syntax.name = *token;

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, "':' after member name", NULL);
		goto error;
	}
	
	incrementToken(token);

	if (!parseType(&syntax.type, token))
		goto error;

	*out = syntax;
	return true;

error:

	freeMemberSyntax(&syntax);
	return false;
}

bool parseStruct(StructSyntax *out, Token *token)
{
	assert(token->type == TOKEN_KEYWORD_STRUCT);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "struct name", NULL);
		return false;
	}

	StructSyntax syntax = { 0 };

	syntax.name = *token;

	incrementToken(token);

	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' before struct body", NULL);
		goto error;
	}

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_BRACE)
	{
		while (true)
		{
			MemberSyntax member = { 0 };

			if (!parseMember(&member, token))
				goto error;

			resizeArray(syntax.members, ++syntax.memberCount);
			syntax.members[syntax.memberCount - 1] = member;

			if (token->type != TOKEN_COMMA)
				break;

			incrementToken(token);
		}

		if (token->type != TOKEN_RIGHT_BRACE)
		{
			printParseError(token, "'}' after struct body", NULL);
			return false;
		}
	}

	incrementToken(token);

	*out = syntax;
	return true;

error:

	freeStructSyntax(&syntax);
	return false;
}

bool parseType(TypeSyntax *out, Token *token)
{
	TypeSyntax syntax = { 0 };

	while (token->type == TOKEN_ASTERISK)
	{
		incrementToken(token);

		resizeArray(syntax.ptrs, ++syntax.ptrCount);

		if (token->type == TOKEN_KEYWORD_MUT)
		{
			syntax.ptrs[syntax.ptrCount - 1] = (PtrSyntax)
			{
				.token = *token,
				.isMutable = true
			};
			
			incrementToken(token);
		}
		else
		{
			syntax.ptrs[syntax.ptrCount - 1] = (PtrSyntax)
			{
				.token = *token,
				.isMutable = false
			};
		}
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "type", NULL);
		return false;
	}
	
	syntax.name = *token;

	incrementToken(token);

	*out = syntax;
	return true;

error:

	freeTypeSyntax(&syntax);
	return false;
}

bool parseVariable(VariableSyntax *out, Token *token)
{
	assert(token->type == TOKEN_KEYWORD_VAR);

	VariableSyntax syntax = { 0 };

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "variable name", NULL);
		return false;
	}

	syntax.name = *token;

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		*out = syntax;
		return true;
	}
	
	incrementToken(token);

	syntax.isExplicitlyTyped = true;

	if (!parseType(&syntax.type, token))
		goto error;

	*out = syntax;
	return true;

error:

	freeVariableSyntax(&syntax);
	return false;
}

bool parseModule(ModuleSyntax *out, Token *token)
{
	ModuleSyntax syntax = { 0 };

parse:

	switch (token->type)
	{
		case TOKEN_KEYWORD_FUNCTION:
		{
			FunctionSyntax function = { 0 };

			if (!parseFunction(&function, token))
				goto error;

			resizeArray(syntax.functions, ++syntax.functionCount);
			syntax.functions[syntax.functionCount - 1] = function;
			goto parse;
		}
		case TOKEN_KEYWORD_STRUCT:
		{
			StructSyntax strct = { 0 };

			if (!parseStruct(&strct, token))
				goto error;

			resizeArray(syntax.structs, ++syntax.structCount);
			syntax.structs[syntax.structCount - 1] = strct;
			goto parse;
		}

		case TOKEN_END_OF_FILE:
			break;

		default:
			printParseError(token, "type or function definition", NULL);
			goto error;
	}

	*out = syntax;
	return true;

error:

	freeModuleSyntax(&syntax);
	return true;
}

usize getPathSize(const char *path)
{
	usize size = 0;

	for (const char *iter = path; *iter; ++iter)
	{
		if (*iter == '/' || *iter == '\\')
			size += 1;

		size += 1;
	}
}

char *getPackageFromDirectory(const Directory *directory)
{
	String symbol = { 0 };
	usize capacity = getPathSize(directory->path);

	stringReserve(&symbol, capacity);

	const char *path = directory->path;

	for (const char *iter = path; *iter; ++iter)
	{
		if (*iter == '/')
		{
			stringPushCString(&symbol, "::");
			continue;
		}

		stringPushChar(&symbol, *iter);
	}

	return symbol.data;
}

bool parsePackage(PackageSyntax *out, const Directory *directory)
{
	PackageSyntax syntax =
	{
		.name = getPackageFromDirectory(directory)
	};

	for (usize i = 0; i < directory->fileCount; ++i)
	{
		ModuleSyntax module = { 0 };

		Token token = getInitialToken(directory->files + i);

		if (!parseModule(&module, &token))
			goto error;

		usize newFunctionCount = syntax.functionCount + module.functionCount;

		resizeArray(syntax.functions, newFunctionCount);

		for (usize j = 0; j < module.functionCount; ++j)
			syntax.functions[syntax.functionCount + j] = module.functions[j];

		syntax.functionCount = newFunctionCount;

		usize newStructCount = syntax.structCount + module.structCount;

		resizeArray(syntax.structs, newStructCount);

		for (usize j = 0; j < module.structCount; ++j)
			syntax.structs[syntax.structCount + j] = module.structs[j];

		syntax.structCount = newStructCount;
	}

	*out = syntax;
	return true;

error:

	freePackageSyntax(&syntax);
	return false;
}

bool parse(ProgramSyntax *out, const Directory *directories, usize directoryCount)
{
	if (directoryCount == 0)
	{
		printError("No directories to compile.");
		return false;
	}

	ProgramSyntax syntax = { 0 };
	usize fileCount = 0;

	for (usize i = 0; i < directoryCount; ++i)
	{
		const Directory *directory = directories + i;

		fileCount += directory->fileCount;

		PackageSyntax package;

		if (!parsePackage(&package, directory))
			goto error;

		resizeArray(syntax.packages, ++syntax.packageCount);
		syntax.packages[syntax.packageCount - 1] = package;
	}

	if (fileCount == 0)
	{
		printError("No source files passed to compiler.");
		return false;
	}

	*out = syntax;

	return true;

error:

	print("A");
	freeProgramSyntax(&syntax);
	return false;
}
