#include <grackle/parser.h>
#include <stdio.h>

// ideas:
/*
	have a get statemnt function where it will go forward and grab
	ids until it has found a semi colon.
	It will then parse this statement and memoize it.

*/

node_t *parse_typename(toklist_t *toks, size_t *index)
{
	size_t i = *index;
	token_t *t = toklist_get_ref(toks, i);

	if (!t) return NULL;

	switch (t->type)
	{
	case TOK_I32_TYPE:
		break;

	default:
		return NULL;
	}

	node_t *out = node_create(NODE_TYPENAME);
	out->val = t;
	return out;
}


node_t *parse_identifier(toklist_t *toks, size_t *index)
{
	token_t *t = toklist_get_ref(toks, *index);
	if (t->type != TOK_IDENTIFIER) return NULL;
	node_t *identifier = node_create(NODE_IDENTIFIER);
	identifier->val = t;
	*index += 1;
	return identifier;
}


node_t *parse_arglist(toklist_t *toks, size_t *index)
{
	token_t *t = toklist_get_ref(toks, *index);
	if (t->type != TOK_LPAREN)
	{
		puts("error: expected '(' for arglist");
		return NULL;
	}
	*index += 1;
	t = toklist_get_ref(toks, *index);
	if (t->type != TOK_RPAREN)
	{
		puts("error: expected ')' for arglist");
		return NULL;
	}
	*index += 1;
	node_t *arglist = node_create(NODE_ARGLIST);
	return arglist;
}


node_t *parse_expression(toklist_t *toks, size_t *index)
{
	node_t *expression = node_create(NODE_EXPRESSION);
	return expression;
}


#define fail(err) { error = err; goto exit_failure; }

node_t *parse_statement(toklist_t *toks, size_t *index)
{
	node_t *statement = NULL;
	size_t i = *index;
	token_t *t = toklist_get_ref(toks, i++);
	
	const char *error = NULL;

	switch (t->type)
	{
	case TOK_LBRACE:
		statement = node_create(NODE_COMPOUND_STMT);
		t = toklist_get_ref(toks, i++);
		while (t->type != TOK_RBRACE)
		{
			if (t->type == TOK_EOF) fail("expected '}' at end of statement block");
			node_t *n = parse_statement(toks, index);
			if (!n) goto exit_failure;
			node_push_arg(statement, n);
		}
		break;

	// declaration
	case TOK_VAR:
		statement = node_create(NODE_VAR_DECLARATION);
		node_t *n = parse_identifier(toks, &i);
		if (!n) goto exit_failure;
		node_push_arg(statment, n);
		// type specifier
		t = toklist_get_ref(toks, i++);
		if (t->type == TOK_COLON)
		{
			statement->type = NODE_TYPE_DECLARATION;
			n = 
		}

		break;

	default:
		goto exit_failure;
	}

	*index = i;
	return statement;

exit_failure:
	if (!error) error = "failed to parse statement";
	fprintf(stderr, "error: %s\n", error);
	node_destroy(statement);
	return NULL;
}


node_t *parse_function(toklist_t *toks, size_t *index)
{
	node_t *function = node_create(NODE_FUNCTION);

	node_t *n = parse_identifier(toks, index);
	if (!n)
	{
		puts("Failed to parse function return type");
		goto exit_failure;
	}
	node_push_arg(function, n);

	printf("%s", "Parsed return type: ");
	string_put(n->val->str);

	n = parse_identifier(toks, index);
	if (!n)
	{
		puts("Failed to parse func symbol");
		goto exit_failure;
	}
	node_push_arg(function, n);

	printf("%s", "Parsed symbol name: ");
	string_put(n->val->str);

	n = parse_arglist(toks, index);
	if (!n) goto exit_failure;
	node_push_arg(function, n);
	puts("Parsed arglist '()'");

	n = parse_statement(toks, index);
	if (!n) goto exit_failure;
	node_push_arg(function, n);
	puts("Parsed statement: '{}'");

	return function;

exit_failure:
	node_destroy(function);
	return NULL;
}


node_t *parse_program(toklist_t *toks, size_t *index)
{
	node_t *program = node_create(NODE_PROGRAM);
	

	node_t *func = parse_function(toks, index);
	if (!func)
	{
		puts("Failed to parse function");
	}
	node_push_arg(program, func);
	
	return program;

exit_failure:
	node_destroy(program);
	return NULL;
}


node_t *parse(toklist_t *toks)
{
	size_t index = 0;
	return parse_program(toks, &index);
}
