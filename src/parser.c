// header
#include <grackle/parser.h>

// local includes
#include <grackle/log.h>
#include <grackle/assert.h>

// standard library
#include <stdio.h>


// TODO
/*
	Program:
		- change to module
		- make it parse "components" instead of functions
		- allow for struct / enum / union / submodule definitions
	
	Expression:
		- handle unary expressions and post expression operators
		- ternary, match, if else, and switch expressions
			- all of these will require the else block / default case 
				as it is important to keep with the "no uninitialized data" paradaigm
		
*/



// macros
#define print_parse() printf("%s: ", __func__); string_put(&tok[0]->str)
#define parse_terminal(tok, expected_type, expected_tok, error_action) if (tok->type != expected_type) { syntax_error(tok, expected_tok); error_action; } tok += 1
#define parse_non_terminal(out, tok, function, error_action) { node_t *arg = parse_##function(&tok); if (!arg) error_action; node_push_arg(out, arg); }
#define parse_semicolon(tok, error_action) parse_terminal(tok, TOK_SEMICOLON, "';'", error_action)

/**
 * @brief Prints syntax error
 * 
 * @param	tok			current token 
 * @param	expected	the type of node expected
 */
void syntax_error(const token_t *tok, const char *expected)
{
	log_error_prompt(tok->line, tok->col);
	fprintf(stderr, "expected %s before '", expected);
	string_fputs(&tok->str, stderr);
	fputs("'\n", stderr);
}


// forward declarations of functions
node_t *parse_statement(const token_t **tok);
node_t *parse_expression(const token_t **tok);
node_t *parse_binary_expression(const token_t **tok);


node_t *parse_identifier(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	if (t->type != TOK_IDENTIFIER)
	{
		printf("Type: %u\n", t->type);
		syntax_error(t, "identifier");
		return NULL;
	}
	node_t *out = node_create(NODE_IDENTIFIER);
	out->val = t;
	t += 1;
	*tok = t;
	return out;
}


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
		syntax_error(t, "typename");
		node_destroy(out);
		return NULL;
	}
}




node_t *parse_parameter(const token_t **tok)
{
	const token_t *t = *tok;

	node_t *out = node_create(NODE_PARAMETER);

	// getting identifier
	parse_non_terminal(out, t, identifier, goto failure);

	// checking for type annotation
	parse_terminal(t, TOK_COLON, "type-annotation", goto failure);

	// getting typename
	parse_non_terminal(out, t, typename, goto failure);

	// moving iterator forwards
	*tok = t;

	return out;

failure:

	node_destroy(out);
	return NULL;
}


node_t *parse_parameter_list(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_PARAM_LIST);

	const token_t *t = *tok;

	parse_terminal(t, TOK_LPAREN, "argument-list", goto failure);

	// empty list
	if (t->type == TOK_RPAREN)
	{
		t += 1;
	}
	// list of parameters
	else
	{
		// parse parameters as long as there is a comma
		while (true)
		{
			parse_non_terminal(out, t, parameter, goto failure);
			if (t->type != TOK_COMMA) break;
			t += 1;
		}
		parse_terminal(t, TOK_RPAREN, ")", goto failure);
	}

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
		syntax_error(t, "compound-statement");
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

	// check for var keyword
	parse_terminal(t, TOK_VAR, "declaration", goto failure);
	// setting token value to var keyword (used in printing)
	out->val = t - 1;


	// get identifier
	parse_non_terminal(out, t, identifier, goto failure);

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
		node_push_arg(out, node_create(NODE_TYPENAME));
	}
	
	// checking for equals sign
	if (t->type != TOK_ASSIGN)
	{
		log_error(t->line, t->col, "declaration of uninitialized variables is not allowed");
		goto failure;
	}
	t += 1;

	// get assignment expression
	parse_non_terminal(out, t, expression, goto failure);

	// semicolon
	parse_terminal(t, TOK_SEMICOLON, "';'", goto failure);

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
		syntax_error(t, "term");
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


node_t *parse_if_statement(const token_t **tok)
{
	return NULL;
}


node_t *parse_switch_statement(const token_t **tok)
{
	return NULL;
}


node_t *parse_loop_statement(const token_t **tok)
{
	return NULL;
}


node_t *parse_while_statement(const token_t **tok)
{
	return NULL;
}


node_t *parse_for_statement(const token_t **tok)
{
	return NULL;
}


node_t *parse_jump_statement(const token_t **tok)
{
	const token_t *t = *tok;
	node_t *out = node_create(NODE_NO_TYPE);
	out->val = t;

	switch (t->type)
	{
	case TOK_CONTINUE:
		out->type = NODE_CONTINUE_STMT;
		break;

	case TOK_BREAK:
		out->type = NODE_BREAK_STMT;
		break;
	}

	t += 1;

	parse_semicolon(t,
	{
		node_destroy(out);
		return NULL;
	});

	*tok = t;
	return out;
}


node_t *parse_return_statement(const token_t **tok)
{
	const token_t *t = *tok;
	parse_terminal(t, TOK_RETURN, "return-statement", return NULL);
	node_t *out = node_create(NODE_RETURN_STMT);
	out->val = t - 1;
	// if returning a value
	if (t->type != TOK_SEMICOLON)
	{
		parse_non_terminal(out, t, expression, goto failure);
		parse_terminal(t, TOK_SEMICOLON, "';'", goto failure);
	}
	else
	{
		t += 1;
	}

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
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

	case TOK_IF:
		return parse_if_statement(tok);

	case TOK_WHILE:
		return parse_while_statement(tok);

	case TOK_LOOP:
		return parse_loop_statement(tok);

	case TOK_FOR:
		return parse_for_statement(tok);

	case TOK_SWITCH:
		return parse_switch_statement(tok);

	case TOK_BREAK:
	case TOK_CONTINUE:
		return parse_jump_statement(tok);

	case TOK_RETURN:
		return parse_return_statement(tok);

	// no-op
	case TOK_SEMICOLON:;
		node_t *noop = node_create(NODE_NOOP_STMT);
		noop->val = *tok;
		return noop;

	// expression statement
	default:;
		node_t *expr = parse_expression(tok);
		if (!expr) return NULL;
		const token_t *t = *tok;
		if (t->type != TOK_SEMICOLON)
		{
			syntax_error(t, "';'");
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
	parse_terminal(t, TOK_FUNC, "function", goto failure);
	out->val = t - 1;

	// getting identifier
	parse_non_terminal(out, t, identifier, goto failure);

	// getting arg list
	parse_non_terminal(out, t, parameter_list, goto failure);

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
		node_push_arg(out, node_create(NODE_TYPENAME));
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
			syntax_error(t, "';'");
			goto failure;
		}
		t += 1;
		break;
	
	// error
	default:
		syntax_error(t, "function-body");
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
