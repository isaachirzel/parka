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
node_t *parse_binary_expression(const token_t **tok);


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
	out->val = t;
	// skip over opening brace
	if (t->type != TOK_LBRACE)
	{
		parse_error(t, "compound-statement");
		goto failure;
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
		log_error(t->line, t->col, "declaration of uninitialized variables is not allowed");
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


bool is_mul_expr(const token_t *tok)
{
	switch (tok->type)
	{
	case TOK_ASTERISK:
	case TOK_SLASH:
	case TOK_MODULUS:
		return true;

	default:
		return false;
	}
}


bool is_add_expr(const token_t *tok)
{
	return tok->type == TOK_PLUS || tok->type == TOK_MINUS;
}


bool is_shift_expr(const token_t *tok)
{
	return tok->type == TOK_LSHIFT || tok->type == TOK_RSHIFT;
}


bool is_comp_expr(const token_t *tok)
{
	switch (tok->type)
	{
	case TOK_LANGBRACK:
	case TOK_RANGBRACK:
	case TOK_LTOET:
	case TOK_GTOET:
		return true;

	default:
		return false;
	}
}


bool is_equal_expr(const token_t *tok)
{
	return tok->type == TOK_EQUALS || tok->type == TOK_NEQUALS;
}


bool is_bitand_expr(const token_t *tok)
{
	return tok->type == TOK_AMPERSAND;
}


bool is_bitxor_expr(const token_t *tok)
{
	return tok->type == TOK_CARROT;
}


bool is_bitor_expr(const token_t *tok)
{
	return tok->type == TOK_PIPELINE;
}

bool is_and_expr(const token_t *tok)
{
	return tok->type == TOK_AND;
}


bool is_or_expr(const token_t *tok)
{
	return tok->type == TOK_OR;
}



typedef bool (*condition_func)(const token_t *);

typedef struct binexpr
{
	condition_func condition;
	short id;
} binexpr_t;

binexpr_t binexprs[] =
{
	{ is_mul_expr, NODE_MUL_EXPR },
	{ is_add_expr, NODE_ADD_EXPR },
	{ is_shift_expr, NODE_SHIFT_EXPR },
	{ is_comp_expr, NODE_COMP_EXPR },
	{ is_equal_expr, NODE_EQ_EXPR },
	{ is_bitand_expr, NODE_BITAND_EXPR },
	{ is_bitxor_expr, NODE_BITXOR_EXPR },
	{ is_bitor_expr, NODE_BITOR_EXPR },
	{ is_and_expr, NODE_AND_EXPR },
	{ is_or_expr, NODE_OR_EXPR },
};


node_t *parse_binary_recurse(const token_t **tok, const unsigned precedence)
{
	printf("%s(%u): ", __func__, precedence);
	string_put(&(*tok)->str);

	const token_t *t = *tok;
	binexpr_t *type = binexprs + precedence;

	node_t *left = (!precedence) ? parse_term(&t) : parse_binary_recurse(&t, precedence - 1);
	if (!left) return NULL;

	// if not binary, just return first term
	if (!type->condition(t))
	{
		*tok = t;
		return left;
	}
	t += 1;

	// make binary node
	node_t *out = node_create(type->id);
	out->val = t - 1;
	node_t *right = (!precedence) ? parse_term(&t) : parse_binary_recurse(&t, precedence - 1);
	if (!right) goto failure;
	node_push_arg(out, left);
	node_push_arg(out, right);

	// while there is still a chain of same-type expressions
	while (type->condition(t))
	{
		// storing out as leaf
		left = out;
		// creating tree
		out = node_create(type->id);
		out->val = t;
		t += 1;
		// getting right side leaf
		right = (!precedence) ? parse_term(&t) : parse_binary_recurse(&t, precedence - 1);
		if (!right) goto failure;
		// adding args to tree
		node_push_arg(out, left);
		node_push_arg(out, right);
	}

	*tok = t;
	return out;

failure:

	node_destroy(out);
	return NULL;
}

node_t *parse_binary_expression(const token_t **tok)
{
	return parse_binary_recurse(tok, sizeof(binexprs) / sizeof(binexpr_t) - 1);
}


bool is_assignment(const token_t *tok)
{
	switch (tok->type)
	{
	case TOK_ASSIGN:
	case TOK_ADD_ASSIGN:
	case TOK_MIN_ASSIGN:
	case TOK_MUL_ASSIGN:
	case TOK_DIV_ASSIGN:
	case TOK_MOD_ASSIGN:
		return true;

	default:
		return false;
	}
}

node_t *parse_assignment(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;

	node_t *left = parse_binary_expression(&t);
	if (!is_assignment(t))
	{
		puts("Not an assignment");
		*tok = t;
		return left;
	}

	node_t *out = node_create(NODE_ASSIGN_EXPR);
	out->val = t;
	t += 1;
	node_push_arg(out, left);

	node_t *right = parse_assignment(&t);
	node_push_arg(out, right);

	*tok = t;
	return out;
}


node_t *parse_expression(const token_t **tok)
{
	node_t *out =  parse_assignment(tok);
	puts("\nExpression tree:");
	node_print(out);
	return out;
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
