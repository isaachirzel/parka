// header
#include <grackle/parser.h>

// local includes
#include <grackle/log.h>
#include <grackle/assert.h>

// standard library
#include <stdio.h>


// function type
#define parse_func(func) node_t *parse_##func(const token_t **tok)


#define print_parse() printf("%s: ", __func__); string_put(&tok[0]->str)

void parse_error(const token_t *tok, const char *expected)
{
	log_error_prompt(tok->line, tok->col);
	fprintf(stderr, "expected %s before '", expected);
	string_fputs(&tok->str, stderr);
	fputs("'\n", stderr);
}


// forward declarations of functions
parse_func(statement);
parse_func(expression);


node_t *parse_typename(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_TYPENAME);

	const token_t *t = *tok;

	switch (t->type)
	{
	case TOK_IDENTIFIER:
	case TOK_TYPE_I8:
	case TOK_TYPE_I16:
	case TOK_TYPE_I32:
	case TOK_TYPE_I64:
	case TOK_TYPE_U8:
	case TOK_TYPE_U16:
	case TOK_TYPE_U32:
	case TOK_TYPE_U64:
	case TOK_TYPE_F32:
	case TOK_TYPE_F64:
	case TOK_TYPE_STR:
		out->val = t;
		*tok = t + 1;
		return out;

	default:
		parse_error(t, "typename");
		node_destroy(out);
		return NULL;
	}
}


node_t *parse_arglist(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_ARGLIST);

	const token_t *t = *tok;

	if (t->type != TOK_LPAREN)
	{
		node_destroy(out);
		parse_error(t, "argument-list");
		return NULL;
	}
	t += 1;

	if (t->type != TOK_RPAREN)
	{
		node_destroy(out);
		return NULL;
	}
	t += 1;

	*tok = t;
	return out;

failure:

	node_destroy(out);
	return NULL;
}


node_t *parse_compound_statement(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_COMPOUND_STMT);

	const token_t *t = *tok;

	// skip over opening brace
	if (t->type != TOK_LBRACE)
	{
		parse_error(t, "compound-statement");
		return 0;
	}
	t += 1;

	while (t->type != TOK_RBRACE)
	{
		node_t *stmt = parse_statement(&t);
		if (!stmt) goto failure;
		node_push_arg(out, stmt);
	}
	t += 1;

	*tok = t;
	return out;

failure:

	node_destroy(out);
	return NULL;
}


node_t *parse_declaration(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_DECL_STMT);

	const token_t *t = *tok;

	// check for 'var'
	if (t->type != TOK_VAR)
	{
		parse_error(t, "declaration");
		goto failure;
	}
	t += 1;

	// get identifier
	if (t->type != TOK_IDENTIFIER)
	{
		parse_error(t, "identifier");
		goto failure;
	}
	out->val = t;
	t += 1;

	// checking for type annotation
	if (t->type == TOK_COLON)
	{
		t += 1;
		node_t *type = parse_typename(&t);
		if (!type) goto failure;
		node_push_arg(out, type);
	}
	else
	{
		
		// push empty type if no type is annotated
		node_push_arg(out, node_create(NODE_EMPTY_TYPE));
	}
	
	// checking for equals sign
	if (t->type != TOK_ASSIGN)
	{
		log_error(t->line, t->col, "declaration without initialization is not allowed");
		goto failure;
	}
	t += 1;

	// get assignment expression
	node_t *expr = parse_expression(&t);
	if (!expr) goto failure;
	node_push_arg(out, expr);

	// semicolon
	if (t->type != TOK_SEMICOLON)
	{
		parse_error(t, "';'");
		goto failure;
	}
	t += 1;

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_term(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_TERM);

	const token_t *t = *tok;

	switch (t->type)
	{
	case TOK_INT_LITERAL:
	case TOK_STR_LITERAL:
	case TOK_FLOAT_LITERAL:
	case TOK_IDENTIFIER:
		out->val = t++;
		*tok = t;
		return out;

	default:
		parse_error(t, "term");
		node_destroy(out);
		return NULL;
	}
}


node_t *make_binary(node_t *a, node_t *b)
{
	node_t * bin = node_create(NODE_BINARY_EXPR);
	node_push_arg(bin, a);
	node_push_arg(bin, b);
	return bin;
}


node_t *parse_add_expr(const token_t **tok)
{
	print_parse();

	const token_t *t = *tok;

	node_t *term = parse_term(&t);
	if (!term) return NULL;

	// if not binary, just return first term
	if (t->type != TOK_PLUS && t->type != TOK_MINUS)
	{
		*tok = t;
		return term;
	}
	t += 1;

	// make binary node
	node_t *out = node_create(NODE_BINARY_EXPR);
	node_push_arg(out, term);
	out->val = t - 1;

	do
	{
		// push
		term = parse_term(&t);
		if (!term) goto failure;
		node_push_arg(out, term);
	}
	while (t->type == TOK_PLUS || t->type == TOK_MINUS);

	*tok = t;
	return out;

failure:

	node_destroy(out);
	return NULL;
}


node_t *parse_expression(const token_t **tok)
{
	print_parse();
	return parse_add_expr(tok);
}


node_t *parse_statement(const token_t **tok)
{
	print_parse();
	switch ((*tok)->type)
	{
	// compound statement
	case TOK_LBRACE:
		return parse_compound_statement(tok);

	// declaration
	case TOK_VAR:
		return parse_declaration(tok);
	
	// expression statement
	default:;
		node_t *expr = parse_expression(tok);
		if (!expr) return NULL;
		const token_t *t = *tok;
		if (t->type != TOK_SEMICOLON)
		{
			parse_error(t, "';'");
			return NULL;
		}
		*tok = t + 1;
		return expr;
	}
}


node_t *parse_function(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_FUNCTION);
	
	const token_t *t = *tok;

	// getting func token
	if (t->type != TOK_FUNC)
	{
		parse_error(t, "function");
		goto failure;
	}
	t += 1;

	// getting identifier
	if (t->type != TOK_IDENTIFIER)
	{
		parse_error(t, "identifier");
		goto failure;
	}
	out->val = t;
	t += 1;

	// getting arg list
	node_t *arglist = parse_arglist(&t);
	if (!arglist) goto failure;
	node_push_arg(out, arglist);

	// checking for return type
	if (t->type == TOK_SINGLE_ARROW)
	{
		t += 1;
		// getting return type
		node_t *type = parse_typename(&t);
		if (!type) goto failure;
		node_push_arg(out, type);
	}
	else
	{
		// push empty type if no type is annotated
		node_push_arg(out, node_create(NODE_EMPTY_TYPE));
	}

	// getting statement
	switch (t->type)
	{
	// compound statement
	case TOK_LBRACE:;
		node_t *compound = parse_compound_statement(&t);
		if (!compound) goto failure;
		node_push_arg(out, compound);
		break;

	// expression
	case TOK_DOUBLE_ARROW:;
		node_t *expr = parse_expression(&t);
		if (!expr) goto failure;
		node_push_arg(out, expr);

		if (t->type != TOK_SEMICOLON)
		{
			parse_error(t, "';'");
			goto failure;
		}
		t += 1;
		break;
	
	// error
	default:
		parse_error(t, "function-body");
		goto failure;
	}

	*tok = t;
	return out;


failure:

	node_destroy(out);
	return NULL;
}


node_t *parse(toklist_t *toks)
{
	node_t *out = node_create(NODE_PROGRAM);

	// parse functions until end of file is reached
	const token_t *t = toks->data;
	while (t->type != TOK_EOF)
	{
		node_t *func = parse_function(&t);
		// failed to parse function
		if (!func)
		{
			// destroy node
			node_destroy(out);
			return NULL;
		}
		node_push_arg(out, func);
	}

	return out;
}
