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
	size_t offs;
} result_t;


typedef result_t(*parse_func)(toklist_t*, size_t);


result_t result_init(char type)
{
	return (result_t){ true, node_create(type), 0 };
}


bool get_res(result_t *out, toklist_t* toks, parse_func func)
{
	result_t res = func(toks, out->offs);
	out->offs += res.offs;

	if (!res.ok)
	{
		node_destroy(out->node);
		out->ok = false;
		out->err = res.err;
		return false;
	}

	node_push_arg(out->node, res.node);
	return true;
}


result_t parse_identifier(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = result_init(NODE_IDENTIFIER);

	token_t *t = toklist_get_ref(toks, index + out.offs);
	if (t->type != TOK_IDENTIFIER)
	{
		out.ok = false;
		out.err = "identifier";
		return out;
	}
	out.node->val = t;
	out.offs += 1;
	return out;

exit_failure:
	node_destroy(out.node);
	out.ok = false;
	out.err = "identifier";
	return out;
}


result_t parse_arglist(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = { true, node_create(NODE_ARGLIST), 0 };
	token_t *t = toklist_get_ref(toks, index + out.offs);

	if (t->type != TOK_LPAREN)
	{
		out.err = "error: expected '(' for arglist";
		goto exit_failure;
	}

	out.offs += 1;
	t = toklist_get_ref(toks, index + out.offs);
	if (t->type != TOK_RPAREN)
	{
		out.err = "error: expected ')' for arglist";
		goto exit_failure;
	}

	out.offs += 1;

	return out;

exit_failure:

	node_destroy(out.node);
	out.ok = false;
	return out;
}


result_t parse_expression(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = { true, node_create(NODE_EXPRESSION) };
	return out;
}


result_t parse_compound_statement(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = result_init(NODE_COMPOUND_STMT);
	
	return out;
}


result_t parse_declaration(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = result_init(NODE_VAR_DECLARATION);

	return out;
}


result_t parse_statement(toklist_t *toks, size_t index)
{
	puts(__func__);
	token_t *t = toklist_get_ref(toks, index);

	switch (t->type)
	{
	// compound statement
	case TOK_LBRACE:
		return parse_compound_statement(toks, index);

	// declaration
	case TOK_VAR:
		return parse_declaration(toks, index);

	default:;
		result_t out;
		out.ok = false;
		out.err = "statement";
		out.offs = 0;
		return out;
	}
}


result_t parse_function(toklist_t *toks, size_t index)
{
	puts(__func__);
	result_t out = result_init(NODE_FUNCTION);
	
	// getting func token
	token_t *t = toklist_get_ref(toks, index + out.offs);
	if (t->type != TOK_FUNC) goto exit_failure;
	out.offs += 1;

	// getting identifier
	if (!get_res(&out, toks, parse_identifier)) return out;

	// getting arg list
	if (!get_res(&out, toks, parse_arglist)) return out;

	// checking for return type
	t = toklist_get_ref(toks, index + out.offs);
	if (t->type == TOK_SINGLE_ARROW)
	{
		out.offs += 1;
		// getting return type
		if (!get_res(&out, toks, parse_identifier)) return out;
	}

	// getting statement
	if (!get_res(&out, toks, parse_statement)) return out;

	return out;
	
exit_failure:
	node_destroy(out.node);
	out.ok = false;
	out.err = "function";
	return out;
}


result_t parse_program(toklist_t *toks, size_t index)
{
	result_t out = result_init(NODE_PROGRAM);

	if (!get_res(&out, toks, parse_function)) return out;

	return out;

exit_failure:
	node_destroy(out.node);
	out.ok = false;
	out.err = "program";
	return out;
}


node_t *parse(toklist_t *toks)
{
	result_t res = parse_program(toks, 0);
	if (!res.ok)
	{
		log_parse_error(toklist_get_ref(toks, res.offs), res.err);
		return NULL;
	}
	return res.node;
}
