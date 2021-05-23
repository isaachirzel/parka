// header
#include <grackle/parser.h>

// local includes
#include <grackle/log.h>

// standard library
#include <stdio.h>

// ideas:
/*
	have a get statemnt function where it will go forward and grab
	ids until it has found a semi colon.
	It will then parse this statement and memoize it.

*/

typedef struct parse_result
{
	bool ok;
	union
	{
		node_t *node;
		const char* err;
	};
} result_t;

typedef result_t(*parse_func)(toklist_t*, size_t*);

bool get_res(result_t *out, toklist_t* toks, size_t *index, parse_func func)
{
	result_t res = func(toks, index);

	if (!res.ok)
	{
		node_destroy(out->node);
		*out = res;
		return false;
	}
	
	node_push_arg(out->node, res.node);
	return true;
}

result_t parse_identifier(toklist_t *toks, size_t *index)
{
	node_t *identifier = node_create(NODE_IDENTIFIER);
	result_t out = { true, NULL };
	out.node = identifier;

	token_t *t = toklist_get_ref(toks, *index);
	if (t->type != TOK_IDENTIFIER)
	{
		out.ok = false;
		out.err = "expected identifier";
		return out;
	}
	identifier->val = t;
	*index += 1;
	return out;
}


result_t parse_arglist(toklist_t *toks, size_t *index)
{
	result_t out = { true, node_create(NODE_ARGLIST) };
	token_t *t = toklist_get_ref(toks, *index);

	if (t->type != TOK_LPAREN)
	{
		out.err = "error: expected '(' for arglist";
		goto exit_failure;
	}

	*index += 1;
	t = toklist_get_ref(toks, *index);
	if (t->type != TOK_RPAREN)
	{
		out.err = "error: expected ')' for arglist";
		goto exit_failure;
	}

	*index += 1;

	return out;

exit_failure:

	node_destroy(out.node);
	out.ok = false;
	return out;
}


result_t parse_expression(toklist_t *toks, size_t *index)
{
	result_t out = { true, node_create(NODE_EXPRESSION) };
	return out;
}


result_t parse_statement(toklist_t *toks, size_t *index)
{
	result_t out = { true, node_create(NODE_NO_TYPE) };
	size_t i = *index;
	token_t *t = toklist_get_ref(toks, i++);
	const char *error = NULL;
	switch (t->type)
	{
	case TOK_LBRACE:
		out.node->type = NODE_COMPOUND_STMT;
		t = toklist_get_ref(toks, i++);
		while (t->type != TOK_RBRACE)
		{
			if (t->type == TOK_EOF)
			{
				error = "expected '}' at end of statement block";
				goto exit_failure;
			}

			if (!get_res(&out, toks, &i, parse_statement)) return out;
		}
		break;

	// declaration
	case TOK_VAR:
		out.node->type = NODE_VAR_DECLARATION;
		if (!get_res(&out, toks, &i, parse_identifier)) return out;
		// type specifier
		puts("Colon");
		t = toklist_get_ref(toks, i);
		if (t->type == TOK_COLON)
		{
			i += 1;
			if (!get_res(&out, toks, &i, parse_identifier)) return out;
		}
		puts("assign");
		// peek for initialization
		t = toklist_get_ref(toks, i);

		break;

	default:
		goto exit_failure;
	}

	*index = i;

	return out;

exit_failure:
	node_destroy(out.node);
	out.ok = false;
	out.err = error;
	return out;
}


result_t parse_function(toklist_t *toks, size_t *index)
{
	size_t i = *index;
	token_t *t = toklist_get_ref(toks, i++);
	const char *error = NULL;
	if (t->type != TOK_FUNC)
	{
		error = "expected 'func' at function definition";
		goto exit_failure;
	}

	result_t out = { true, node_create(NODE_FUNCTION) };

	if (!get_res(&out, toks, &i, parse_identifier)) return out;

	if (!get_res(&out, toks, &i, parse_arglist)) return out;

	t = toklist_get_ref(toks, i);
	if (t->type == TOK_SINGLE_ARROW)
	{
		i += 1;
		if (!get_res(&out, toks, &i, parse_identifier)) return out;
	}

	if (!get_res(&out, toks, &i, parse_statement)) return out;

	*index = i;
	return out;
	
exit_failure:

	node_destroy(out.node);
	out.ok = false;
	out.err = error;
	return out;
}


result_t parse_program(toklist_t *toks, size_t *index)
{
	result_t out = { true, node_create(NODE_PROGRAM) };
	size_t i = *index;

	get_res(&out, toks, &i, parse_function);

	*index = i;
	return out;
}


node_t *parse(toklist_t *toks)
{
	size_t index = 0;
	result_t res = parse_program(toks, &index);
	if (!res.ok)
	{
		log_error(toklist_get_ref(toks, index), res.err);
		return NULL;
	}
	return res.node;
}
