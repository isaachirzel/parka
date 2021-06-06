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


node_t *parse_label(const token_t **tok)
{
	const token_t *t = *tok;
	node_t *out = parse_identifier(&t);
	if (!out) return NULL;
	parse_terminal(t, TOK_COLON, "':'", {
		node_destroy(out);
		return NULL;
	});
	*tok = t;
	return out;
}


node_t *parse_parameter(const token_t **tok)
{
	const token_t *t = *tok;

	node_t *out = node_create(NODE_PARAMETER);

	// getting identifier
	out->val = t;
	parse_terminal(t, TOK_IDENTIFIER, "identifier", goto failure);

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


node_t *parse_member_access(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	
	node_t *out = node_create(NODE_MEMBER_ACCESS);
	parse_terminal(t, TOK_DOT, "member-access operator", goto failure);
	out->val = t;
	parse_terminal(t, TOK_IDENTIFIER, "identifier", goto failure);

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_function_call(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_FUNCTION_CALL);
	out->val = t;
	parse_terminal(t, TOK_LPAREN, "function-call", goto failure);

	// getting arguments
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
			parse_non_terminal(out, t, expression, goto failure);
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


node_t *parse_index(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_INDEX);
	out->val = t;
	parse_terminal(t, TOK_LBRACK, "index-operation", goto failure);
	parse_non_terminal(out, t, expression, goto failure);
	parse_terminal(t, TOK_RBRACK, "']'", goto failure);

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_factor(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_FACTOR);

	const token_t *t = *tok;

	switch (t->type)
	{
	case TOK_INT_LITERAL:
	case TOK_STR_LITERAL:
	case TOK_FLOAT_LITERAL:
	case TOK_TRUE:
	case TOK_FALSE:
	case TOK_IDENTIFIER:
		out->val = t++;
		*tok = t;
		break;

	case TOK_LPAREN:
		out->val = t++;
		parse_non_terminal(out, t, expression, break);
		parse_terminal(t, TOK_RPAREN, "')'", goto failure);
		*tok = t;
		break;;

	default:
		syntax_error(t, "factor");
		goto failure;
	}

	// parsing suffix expressions
	while (true)
	{
		node_t *arg;
		switch (t->type)
		{
		case TOK_INCREMENT:
			arg = node_create(NODE_INCREMENT);
			break;

		case TOK_DECREMENT:
			arg = node_create(NODE_DECREMENT);
			break;

		// member access
		case TOK_DOT:
			arg = parse_member_access(&t);
			break;

		// indexing
		case TOK_LBRACK:
			arg = parse_index(&t);
			break;

		// function call
		case TOK_LPAREN:
			arg = parse_function_call(&t);
			break;

		default:
			*tok = t;
			return out;
		}

		// adding suffix to factor
		if (!arg) return NULL;
		node_push_arg(out, arg);
	}

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_prefix_expression(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;

	switch (t->type)
	{
	case TOK_INCREMENT:
	case TOK_DECREMENT:
	case TOK_PLUS:
	case TOK_MINUS:
	case TOK_EXCLAMATION:
	case TOK_ASTERISK:
	case TOK_AMPERSAND:
		break;

	default:
		return parse_factor(tok);
	}

	node_t *out = node_create(NODE_PREFIX_EXPR);
	out->val = t++;

	// getting further prefixes
	parse_non_terminal(out, t, prefix_expression, goto failure);
	
	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
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

	node_t *left = (!precedence) ?
		parse_prefix_expression(&t) :
		parse_binary_recurse(&t, precedence - 1);
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
	node_t *right = (!precedence) ?
		parse_prefix_expression(&t) :
		parse_binary_recurse(&t, precedence - 1);
	if (!right) goto failure;
	node_push_arg(out, left);
	node_push_arg(out, right);

	// while there is still a chain of same-type expressions
	while (type->condition(t))
	{
		// storing out as lehing
		// creating tree
		out = node_create(type->id);
		out->val = t;
		t += 1;
		// getting right side leaf
		right = (!precedence) ?
			parse_prefix_expression(&t) :
			parse_binary_recurse(&t, precedence - 1);
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


node_t *parse_assignment(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;

	node_t *left = parse_binary_expression(&t);

	switch (t->type)
	{
	case TOK_ASSIGN:
	case TOK_ADD_ASSIGN:
	case TOK_SUB_ASSIGN:
	case TOK_MUL_ASSIGN:
	case TOK_DIV_ASSIGN:
	case TOK_MOD_ASSIGN:
		break;
	default:
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
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_IF_STMT);
	out->val = t;
	parse_terminal(t, TOK_IF, "if-statement", goto failure);
	parse_non_terminal(out, t, expression, goto failure);
	parse_non_terminal(out, t, statement, goto failure);

	if (t->type == TOK_ELSE)
	{
		t += 1;
		parse_non_terminal(out, t, statement, goto failure);
	}

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_switch_statement(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_IF_STMT);
	out->val = t;
	parse_terminal(t, TOK_SWITCH, "switch-statement", goto failure);


	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_loop_statement(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_IF_STMT);
	out->val = t;
	parse_terminal(t, TOK_LOOP, "loop-statement", goto failure);
	parse_non_terminal(out, t, statement, goto failure);
	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_while_statement(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_WHILE_STMT);
	out->val = t;
	parse_terminal(t, TOK_WHILE, "while-statement", goto failure);
	parse_non_terminal(out, t, expression, goto failure);
	parse_non_terminal(out, t, statement, goto failure);

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_for_statement(const token_t **tok)
{

	log_errorf((*tok)->line, (*tok)->col, "%s is not yet implemented\n", __func__);
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


node_t *parse_compound_statement(const token_t **tok)
{
	print_parse();
	node_t *out = node_create(NODE_COMPOUND_STMT);

	const token_t *t = *tok;
	out->val = t;
	// skip over opening brace
	parse_terminal(t, TOK_LBRACE, "compound-statement", goto failure);

	while (t->type != TOK_RBRACE)
	{
		parse_non_terminal(out, t, statement, goto failure);
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


// node_t *parse_(const token_t **tok)
// {
// 	print_parse();
// 	const token_t *t = *tok;
// 	node_t *out = node_create(NODE_COMPONENT);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }

node_t *parse_union(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_UNION);
	out->val = t;

	parse_terminal(t, TOK_UNION, "union", goto failure);
	parse_terminal(t, TOK_LBRACE, "union-definition", goto failure);
	while (t->type != TOK_RBRACE)
	{
		parse_non_terminal(out, t, parameter, goto failure);
	}
	t += 1;

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}

node_t *parse_enum(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_ENUM);
	out->val = t;

	parse_terminal(t, TOK_ENUM, "enum", goto failure);
	parse_terminal(t, TOK_LBRACE, "enum-definition", goto failure);
	if (t->type == TOK_RBRACE)
	{
		t += 1;
	}
	else
	{
		while (true)
		{
			parse_non_terminal(out, t, identifier, goto failure);
			if (t->type != TOK_COMMA) break;
			t += 1;
		}

		parse_terminal(t, TOK_RBRACE, "'}'", goto failure);
	}

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_struct(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_STRUCT);
	out->val = t;

	parse_terminal(t, TOK_STRUCT, "struct", goto failure);
	parse_terminal(t, TOK_LBRACE, "struct-definition", goto failure);
	while (t->type != TOK_RBRACE)
	{
		parse_non_terminal(out, t, parameter, goto failure);
	}
	t += 1;

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_type(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_TYPE);
	out->val = t;

	parse_terminal(t, TOK_TYPE, "type-definition", goto failure);
	parse_non_terminal(out, t, label, goto failure);

	switch (t->type)
	{
	case TOK_STRUCT:
		parse_non_terminal(out, t, struct, goto failure);
		break;

	case TOK_ENUM:
		parse_non_terminal(out, t, enum, goto failure);
		break;

	case TOK_UNION:
		parse_non_terminal(out, t, union, goto failure);
		break;

	default:
		parse_non_terminal(out, t, typename, goto failure);
		break;
	}

	
	parse_semicolon(t, goto failure);

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_import(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_COMPONENT);

	out->val = t;
	parse_terminal(t, TOK_IMPORT, "import-statement", goto failure);
	parse_non_terminal(out, t, identifier, goto failure);
	parse_semicolon(t, goto failure);

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse_module(const token_t **tok)
{
	print_parse();
	const token_t *t = *tok;
	node_t *out = node_create(NODE_MODULE);

	while (t->type != TOK_EOF)
	{
		switch (t->type)
		{
		// function definition
		case TOK_FUNC:
			parse_non_terminal(out, t, function, goto failure);
			break;

		// import statement
		case TOK_IMPORT:
			parse_non_terminal(out, t, import, goto failure);
			break;

		// type definition
		case TOK_TYPE:
			parse_non_terminal(out, t, type, goto failure);
			break;
		}
	}

	*tok = t;
	return out;

failure:
	node_destroy(out);
	return NULL;
}


node_t *parse(toklist_t *toks)
{
	return parse_module((const token_t **)&toks->data);
}
