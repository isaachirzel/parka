#include <warbler/parser.h>

#include <warbler/util/memory.h>
#include <warbler/util/print.h>
#include <warbler/util/directory.h>
#include <warbler/symbol_table.h>
#include <string.h>
#include <assert.h>

char *createSymbol(const char *package, const Token *name)
{
	const char *iter = tokenGetIterator(name);
	StringBuilder builder = sbCreate(128);
	
	if (*package)
	{
		sbPushString(&builder, package);
		sbPushString(&builder, "::");
	}

	sbPushStringN(&builder, iter, name->length);

	return builder.data;
}

bool parseType(TypeAnnotation *out, Token *token)
{
	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "type", NULL);
		return false;
	}
	
	out->token = *token;

	incrementToken(token);

	return true;
}

bool parseSymbol(Expression *out, Token *token)
{
	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "symbol", NULL);
		return false;
	}

	Symbol symbol =
	{
		.token = *token
	};

	incrementToken(token);

	*out = (Expression)
	{
		.type = EXPRESSION_SYMBOL,
		.symbol = symbol
	};

	return true;
}

static bool parseCharacterLiteral(Expression *out, Token *token)
{
	if (token->length != 3)
	{
		printTokenError(token, "character literals may only contain 1 character", NULL);
		return false;
	}

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.character = tokenGetChar(token, 1),
		.type = LITERAL_CHARACTER
	};

	incrementToken(token);

	return true;
}

static bool parseFloatLiteral(Expression *out, Token *token)
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
	
	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.token = *token,
		.type = LITERAL_FLOAT,
		.floating = value
	};

	incrementToken(token);

	return true;
}

static bool parseStringLiteral(Expression *out, Token *token)
{
	Literal literal =
	{
		.token = *token,
		.string = { tokenGetText(token), token->length },
		.type = LITERAL_STRING
	};

	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = literal;

	incrementToken(token);

	return true;
}

static bool parseIntegerLiteral(Expression *out, Token *token)
{
	// TODO: Calculate required size for integers
	// TODO: Confirm will fit in required size

	u64 value = 0;

	for (usize i = 0; i < token->length; ++i)
		value = value * 10 + (tokenGetChar(token, i) - '0');

	

	out->type = EXPRESSION_LITERAL;
	out->literal = new(Literal);
	*out->literal = (Literal)
	{
		*token,
		{ value },
		LITERAL_INTEGER
	};

	incrementToken(token);
	
	return true;
}

bool parseBooleanLiteral(Expression *out, Token *token)
{
	out->type = EXPRESSION_LITERAL;
	*makeNew(out->literal) = (Literal)
	{
		.type = LITERAL_BOOLEAN,
		.token = *token,
		.boolean = token->type == TOKEN_KEYWORD_TRUE
	};

	incrementToken(token);

	return true;
}

bool parseLiteral(Expression *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_CHARACTER_LITERAL:
			return parseCharacterLiteral(out, token);

		case TOKEN_STRING_LITERAL:
			return parseStringLiteral(out, token);

		case TOKEN_INTEGER_LITERAL:
			return parseIntegerLiteral(out, token);

		case TOKEN_FLOAT_LITERAL:
			return parseFloatLiteral(out, token);

		case TOKEN_KEYWORD_TRUE:
		case TOKEN_KEYWORD_FALSE:
			return parseBooleanLiteral(out, token);

		default:
			printParseError(token, "literal", NULL);
			return false;
	}
}

bool parsePrimaryExpression(Expression *out, Token *token)
{
	Expression node = { 0 };

	if (token->type == TOKEN_IDENTIFIER)
	{		
		if (!parseSymbol(&node, token))
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

	freeExpression(&node);
	return false;
}

bool parseArgumentList(ArgumentList* out, Token *token)
{
	assert(token->type == TOKEN_LEFT_PARENTHESIS);
	incrementToken(token);

	ArgumentList node = { 0 };

parseArgument:

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		incrementToken(token);

		Expression expression;

		if (!parseExpression(&expression, token))
			goto error;
		
		resizeArray(node.expressions, ++node.count);
		node.expressions[node.count - 1] = expression;

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

	*out = node;

	// return arguments
	return true;
	
error:

	freeArgumentList(&node);
	return false;
}

bool parsePostfix(Expression *out, Token *token)
{
	Postfix node = { 0 };

	if (!parsePrimaryExpression(&node.expression, token))
		goto error;

parsePostfix:

	switch (token->type)
	{
		case TOKEN_LEFT_BRACKET: // Index
			incrementToken(token);

			Expression index;

			if (!parseExpression(&index, token))
				goto error;

			node.type = POSTFIX_INDEX;
			node.index = index;

			if (token->type != TOKEN_RIGHT_BRACKET)
			{
				printParseError(token, "']' after index operation", NULL);
				goto error;
			}

			incrementToken(token);
			break;

		case TOKEN_LEFT_PARENTHESIS: // Function call
		{
			ArgumentList arguments;

			if (!parseArgumentList(&arguments, token))
				goto error;

			node.type = POSTFIX_FUNCTION_CALL;
			node.arguments = arguments;
			break;
		}

		case TOKEN_DOT: // Member
			incrementToken(token);
		
			if (token->type != TOKEN_IDENTIFIER)
			{
				printParseError(token, "member, method, or property name", NULL);
				goto error;
			}

			Token name = *token;

			incrementToken(token);
			
			node.type = POSTFIX_MEMBER;
			node.member = name;
			break;
		
		default:
			goto finish;
	}

	Expression inner =
	{
		.type = EXPRESSION_POSTFIX,
		.postfix = new(Postfix)
	};

	*inner.postfix = node;

	node = (Postfix)
	{
		.expression = inner
	};

	goto parsePostfix;

finish:

	*out = node.expression;

	return true;
	
error:

	freePostfixExpression(&node);
	return false;
}

bool parsePrefix(Expression *out, Token *token)
{
	Prefix node = { 0 };

	switch (token->type)
	{
		case TOKEN_AMPERSAND:
			node.type = PREFIX_REFERENCE;
			break;

		case TOKEN_ASTERISK:
			node.type = PREFIX_DEREFERENCE;
			break;

		case TOKEN_PLUS:
			node.type = PREFIX_POSITIVE;
			break;

		case TOKEN_MINUS:
			node.type = PREFIX_NEGATIVE;
			break;

		case TOKEN_BITWISE_NOT:
			node.type = PREFIX_BITWISE_NOT;
			break;

		case TOKEN_BOOLEAN_NOT:
			node.type = PREFIX_BOOLEAN_NOT;
			break;

		default:
			return parsePostfix(out, token);
	}

	node.token = *token;

	incrementToken(token);

	if (!parsePrefix(&node.expression, token))
		goto error;

	*makeNew(out->prefix) = node;
	out->type = EXPRESSION_PREFIX;

	return true;
	
error:

	freePrefixExpression(&node);
	return false;
}

bool parseMultiplicativeExpression(Expression *out, Token *token)
{
	MultiplicativeExpression node = { 0 };

	if (!parsePrefix(&node.lhs, token))
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

		Expression expression;

		if (!parsePrefix(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (MultiplicativeRhs)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_MULTIPLICATIVE;
	*makeNew(out->multiplicative) = node;

	return true;
	
error:

	freeMultiplicativeExpression(&node);
	return false;
}

bool parseAdditiveExpression(Expression *out, Token *token)
{
	AdditiveExpression node = { 0 };

	if (!parseMultiplicativeExpression(&node.lhs, token))
		return false;

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

		Expression expression;

		if (!parseMultiplicativeExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);

		node.rhs[node.rhsCount - 1] = (AdditiveRhs)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->additive = allocate(sizeof(*out->additive));
	out->type = EXPRESSION_ADDITIVE;
	*out->additive = node;
	
	return true;

error:

	freeAdditiveExpression(&node);

	return false;
}

bool parseBitShiftExpression(Expression *out, Token *token)
{
	BitShiftExpression node = { 0 };

	if (!parseAdditiveExpression(&node.lhs, token))
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

		Expression expression;

		if (!parseAdditiveExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (BitShiftRhs)
		{
			.type = type,
			.expr = expression
		};
	}
	
	if (!node.rhs)
	{
		*out = node.lhs;
	}
	else
	{
		out->type = EXPRESSION_SHIFT;
		*makeNew(out->shift) = node;
	}

	return true;
	
error:

	freeBitShiftExpression(&node);
	return false;
}

bool parseRelationalExpression(Expression *out, Token *token)
{
	RelationalExpression node = { 0 };

	if (!parseBitShiftExpression(&node.lhs, token))
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

		Expression expression;

		if (!parseBitShiftExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (RelationalRhs)
		{
			.expr = expression,
			.type = type
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
	}
	else
	{
		out->type = EXPRESSION_RELATIONAL;
		out->relational = new(RelationalExpression);
		*out->relational = node;
	}

	return true;
	
error:

	freeRelationalExpression(&node);
	return false;
}

bool parseEqualityExpression(Expression *out, Token *token)
{
	EqualityExpression node = { 0 };

	if (!parseRelationalExpression(&node.lhs, token))
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

		Expression expression;

		if (!parseRelationalExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (EqualityRhs)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_EQUALITY;
	*makeNew(out->equality) = node;

	return true;
	
error:

	freeEqualityExpression(&node);
	return false;
}

bool parseBitwiseAndExpression(Expression *out, Token *token)
{
	BitwiseAndExpression node = { 0 };

	if (!parseEqualityExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_AMPERSAND)
	{
		incrementToken(token);

		Expression expression;

		if (!parseEqualityExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_AND;
	out->bitwiseAnd = new(BitwiseAndExpression);
	*out->bitwiseAnd = node;

	return true;

error:

	freeBitwiseAndExpression(&node);
	return false;
}

bool parseBitwiseXorExpression(Expression *out, Token *token)
{
	BitwiseXorExpression node = { 0 };

	if (!parseBitwiseAndExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_CARROT)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseAndExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_XOR;
	*makeNew(out->bitwiseXor) = node;

	return true;
	
error:

	freeBitwiseXorExpression(&node);
	return false;
}

bool parseBitwiseOrExpression(Expression *out, Token *token)
{
	BitwiseOrExpression node = { 0 };

	if (!parseBitwiseXorExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_PIPE)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseXorExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_OR;
	*makeNew(out->bitwiseOr) = node;

	return true;
	
error:

	freeBitwiseOrExpression(&node);
	return false;
}

bool parseBooleanAndExpression(Expression *out, Token *token)
{
	BooleanAndExpression node = { 0 };

	if (!parseBitwiseOrExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_AND)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseOrExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_AND;
	out->booleanAnd = new(BooleanAndExpression);
	*out->booleanAnd = node;

	return true;
	
error:

	freeBooleanAndExpression(&node);
	return false;
}

bool parseBooleanOrExpression(Expression *out, Token *token)
{
	BooleanOrExpression node = { 0 };

	if (!parseBooleanAndExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_OR)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBooleanAndExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_OR;
	*makeNew(out->booleanOr) = node;

	return true;
	
error:

	freeBooleanOrExpression(&node);
	return false;
}

bool parseConditionalExpression(Expression *out, Token *token)
{
	ConditionalExpression node = { 0 };

	if (!parseBooleanOrExpression(&node.expression, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_THEN)
	{
		*out = node.expression;
		return true;
	}

	incrementToken(token);

	node.hasRhs = true;

	if (!parseBooleanOrExpression(&node.rhs.trueCase, token))
		goto error;

	if (token->type != TOKEN_KEYWORD_ELSE)
	{
		printParseError(token, "'else' or false case", NULL);
		goto error;
	}

	incrementToken(token);

	if (!parseBooleanOrExpression(&node.rhs.falseCase, token))
		goto error;

	out->type = EXPRESSION_CONDITIONAL;
	*makeNew(out->conditional) = node;

	return true;
	
error:

	freeConditionalExpression(&node);
	return false;
}

bool parseAssignment(Expression *out, Token *token)
{
	Assignment node = { 0 };

	if (!parseConditionalExpression(&node.lhs, token))
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
			*out = node.lhs;
			return true;
	}

	node.type = type;

	incrementToken(token);

	if (!parseConditionalExpression(&node.rhs, token))
		goto error;

	return true;
	
error:

	freeAssignment(&node);
	return false;
}

bool parseBlock(Expression *out, Token *token)
{
	assert(token->type == TOKEN_LEFT_BRACE);

	incrementToken(token);

	Block node = { 0 };

	while (true)
	{
		if (token->type == TOKEN_RIGHT_BRACE)
			break;

		if (token->type == TOKEN_END_OF_FILE)
		{
			printParseError(token, "'}'", NULL);
			return false;
		}

		Statement statement = { 0 };

		if (!parseStatement(&statement, token))
			goto error;

		resizeArray(node.statements, ++node.count);
		node.statements[node.count - 1] = statement;
	}

	incrementToken(token);

	*makeNew(out->block) = node;
	out->type = EXPRESSION_BLOCK;

	return true;

error:

	freeBlock(&node);
	return false;
}

bool parseExpression(Expression *out, Token *token)
{
	if (token->type == TOKEN_LEFT_BRACE)
		return parseBlock(out, token);

	return parseAssignment(out, token);
}

bool parseParameter(Parameter *out, Token *token)
{
	*out = (Parameter) { 0 };

	if (token->type == TOKEN_KEYWORD_MUT)
	{
		out->isMutable = true;
		incrementToken(token);
	}

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "parameter name", NULL);
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, ":", "parameters require a valid type");
		return false;
	}

	incrementToken(token);

	if (!parseType(&out->type, token))
		return false;
	
	return true;
}

bool parseParameterList(SymbolIdList *out, Token *token)
{
	if (token->type != TOKEN_LEFT_PARENTHESIS)
	{
		printParseError(token, "'(' after function name", NULL);
		return false;
	}

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_PARENTHESIS)
	{
		while (true)
		{
			SymbolId id = symbolTableAddParameter();
			Parameter *parameter = symbolTableGetParameter(&id);

			if (!parseParameter(parameter, token))
				return false;

			symbolIdListPush(out, &id);

			if (token->type != TOKEN_COMMA)
				break;

			incrementToken(token);
		}

		if (token->type != TOKEN_RIGHT_PARENTHESIS)
		{
			printParseError(token, "')'", "Invalid tokens in parameter list");
			return false;
		}
	}

	incrementToken(token);

	return true;
}

bool parseFunction(SymbolId *out, Token *token, const char *package)
{
	assert(token->type == TOKEN_KEYWORD_FUNCTION);

	SymbolId id = symbolTableAddFunction();
	Function *node = symbolTableGetFunction(&id);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "function name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbol(package, token);

	incrementToken(token);

	if (!parseParameterList(&node->parameterIds, token))
		return false;

	if (token->type == TOKEN_COLON)
	{
		incrementToken(token);

		if (!parseType(&node->returnType, token))
			return false;

		node->hasReturnType = true;
	}

	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' after function signature", NULL);
		return false;
	}

	if (!parseBlock(&node->body, token))
		return false;

	*out = id;

	return true;
}

bool parseVariable(Variable *out, Token *token)
{
	assert(token->type == TOKEN_KEYWORD_VAR);

	Variable node = { 0 };

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "variable name", NULL);
		return false;
	}

	node.name = *token;
	node.symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		*out = node;
		return true;
	}
	
	incrementToken(token);

	node.isExplicitlyTyped = true;

	if (!parseType(&node.type, token))
		goto error;

	*out = node;
	return true;

error:

	freeVariable(&node);
	return false;
}

bool parseDeclaration(Declaration *node, Token *token)
{
	SymbolId id = symbolTableAddVariable();
	Variable *variable = symbolTableGetVariable(&id);

	node->variableId = id;

	if (!parseVariable(variable, token))
		return false;

	if (token->type != TOKEN_ASSIGN)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	if (!parseExpression(&node->value, token))
		return false;

	if (token->type != TOKEN_SEMICOLON)
	{
		printFmt("TOKEN: %zu, %s", token->length, tokenGetText(token));

		printParseError(token, "';' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	return true;
}

bool parseStatement(Statement *out, Token *token)
{
	if (token->type == TOKEN_KEYWORD_VAR)
	{
		Declaration declaration;

		if (!parseDeclaration(&declaration, token))
			return false;

		*makeNew(out->declaration) = declaration;
		out->isDeclaration = true;

		return true;
	}

	Expression expression;

	if (!parseExpression(&expression, token))
		return false;

	if (token->type != TOKEN_SEMICOLON)
	{
		printParseError(token, "';' after expression statement", NULL);
		freeExpression(&expression);
		return false;
	}

	incrementToken(token);

	*makeNew(out->expression) = expression;
	out->isDeclaration = false;

	return true;
}

bool parseMember(Member *out, Token *token)
{
	if (token->type == TOKEN_KEYWORD_PUBLIC)
	{
		out->isPublic = true;
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
		return false;
	}

	out->name = *token;
	out->symbol = tokenGetText(token);

	incrementToken(token);

	if (token->type != TOKEN_COLON)
	{
		printParseError(token, "':' after member name", NULL);
		return false;
	}
	
	incrementToken(token);

	if (!parseType(&out->annotation, token))
		return false;

	return true;
}

bool parseMemberList(MemberList *out, Token *token)
{
	if (token->type != TOKEN_LEFT_BRACE)
	{
		printParseError(token, "'{' before member list", NULL);
		return false;
	}

	incrementToken(token);

	if (token->type != TOKEN_RIGHT_BRACE)
	{
		while (true)
		{
			usize index = out->count;

			resizeArray(out->data, ++out->count);

			out->data[index] = (Member) { 0 };

			if (!parseMember(&out->data[index], token))
				return false;

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

	return true;
}

bool parseStruct(SymbolId *out, Token *token, const char *package)
{
	assert(token->type == TOKEN_KEYWORD_STRUCT);

	SymbolId id = symbolTableAddStruct();
	Struct *node = symbolTableGetStruct(&id);

	incrementToken(token);

	if (token->type != TOKEN_IDENTIFIER)
	{
		printParseError(token, "struct name", NULL);
		return false;
	}

	node->name = *token;
	node->symbol = createSymbol(package, token);

	incrementToken(token);

	if (!parseMemberList(&node->members, token))
		return false;

	*out = id;
	return true;
}

bool parseModule(Module *node, const File *file, const char *package)
{
	// TODO: parse error recovery
	bool success = true;
	Token token = getInitialToken(file);

	node->structIds.type = SYMBOL_STRUCT;
	node->functionIds.type = SYMBOL_FUNCTION;

parse:

	switch (token.type)
	{
		case TOKEN_KEYWORD_FUNCTION:
		{
			SymbolId id;

			if (!parseFunction(&id, &token, package))
			{
				success = false;
				break;
			}

			symbolIdListPush(&node->functionIds, &id);
			goto parse;
		}

		case TOKEN_KEYWORD_STRUCT:
		{
			SymbolId id;

			if (!parseStruct(&id, &token, package))
			{
				success = false;
				break;
			}

			symbolIdListPush(&node->structIds, &id);
			goto parse;
		}

		case TOKEN_END_OF_FILE:
			break;

		default:
			printParseError(&token, "type or function definition", NULL);
			success = false;
			break;
	}

	return success;
}

usize getPackageStringLength(const char *path)
{
	usize length = 0;

	for (const char *iter = path; *iter; ++iter)
	{
		if (*iter == '/')
			length += 1;

		length += 1;
	}

	return length;
}

char *getPackageFromDirectory(const Directory *directory, usize pathOffset)
{
	const char *path = directory->path + pathOffset;

	usize length = getPackageStringLength(path);

	// printFmt("P: %s, len: %zu", path, length);

	StringBuilder symbol = sbCreate(length);

	for (const char *iter = path; *iter; ++iter)
	{
		if (*iter == '/')
		{
			sbPushString(&symbol, "::");
		}
		else
		{
			sbPushChar(&symbol, *iter);
		}
	}

	return symbol.data;
}

static usize getModuleCount(const Directory *directory)
{
	usize count = 0;

	for (usize i = 0; i < directory->entryCount; ++i)
	{
		// TODO: Check if has correct extension
		if (!directory->entries[i].isDirectory)
			count += 1;
	}

	return count;
}

bool parsePackage(const Directory *directory, Scope *package, const char *name)
{
	bool success = true;

	SymbolId id = symbolTableAddPackage();
	Package *node = symbolTableGetPackage(&id);
	char *symbol = scopeCreateSymbol(package, name);

	scopePush(package, name);

	node->symbol = symbol,
	node->moduleCount = getModuleCount(directory);

	makeArray(node->modules, node->moduleCount);

	usize fileIndex = 0;

	for (usize i = 0; i < directory->entryCount; ++i)
	{
		const Entry *entry = &directory->entries[i];

		if (entry->isDirectory)
		{
			if (!parsePackage(entry->directory, package, entry->directory->name))
				success = false;

			continue;
		}

		if (!parseModule(&node->modules[fileIndex], &entry->file, node->symbol))
			success = false;

		++fileIndex;
	}

	scopePop(package);

	return success;
}

bool parse(const Project *project)
{
	// TODO: Only allow qulified ids for symbols and unqualified ids for declarations
	Scope package = { 0 };

	bool success = parsePackage(&project->srcDir, &package, project->name);

	scopeDestroy(&package);

	return success;
}
