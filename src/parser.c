// header
#include <grackle/parser.h>

// local includes
#include <grackle/log.h>
#include <grackle/assert.h>

// standard library
#include <stdio.h>


// convenience defines for easier function definition
#define parse_terminal(term_type) if (toklist_getref(toks, index + out.offs)->type != term_type) goto exit_failure; out.offs += 1
#define is_terminal(term_type) (toklist_getref(toks, index + out.offs)->type == term_type)
#define handle_non_terminal(func, action)\
{\
	result_t res = parse_##func(toks, index + out.offs);\
	out.offs += res.offs;\
	if (!res.ok) { node_destroy(out.node); out.ok = false; out.err = res.err; return out; }\
	action;\
}
#define push_non_terminal(func) handle_non_terminal(func, node_push_arg(out.node, res.node))
#define swap_non_terminal(func, arg_pos) handle_non_terminal(func,\
{\
	node_t *expr = out.node;\
	out.node = res.node;\
	out.node->args[arg_pos] = expr;\
})

#define parse_failure(expected) exit_failure: node_destroy(out.node); out.ok = false; out.err = expected; return out;
#define result_init(type) (result_t){ true, node_create(type), 0 }; printf("%s: ", __func__); string_put(&toklist_getref(toks, index)->str)
#define parse_func(func) result_t parse_##func(toklist_t *toks, size_t index)


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


#define ERROR_PROMPT "\033[31merror:\033[0m"


void parse_error(token_t *tok, const char *expected)
{
	fprintf(stderr, "%u:%u:  " ERROR_PROMPT " expected %s before '",
		tok->line, tok->col, expected);

	for (unsigned i = 0; i < tok->str.len; ++i)
	{
		putc(tok->str.ptr[i], stderr);
	}
	fputs("'\n", stderr);
}	


// forward declarations of functions
parse_func(statement);
parse_func(expression);


parse_func(identifier)
{
	result_t out = result_init(NODE_IDENTIFIER);
	out.node->val = toklist_getref(toks, index);
	if (out.node->val->type == TOK_IDENTIFIER)
	{
		out.offs += 1;
		return out;
	}
	parse_failure("identifier");
}


parse_func(typename)
{
	result_t out = result_init(NODE_TYPENAME);
	out.node->val = toklist_getref(toks, index);
	switch (out.node->val->type)
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
		out.offs += 1;
		return out;
	}
	parse_failure("typename");
}


parse_func(arglist)
{
	result_t out = result_init(NODE_ARGLIST);

	parse_terminal(TOK_LPAREN);
	parse_terminal(TOK_RPAREN);

	return out;

	parse_failure("argument-list");
}


parse_func(compound_statement)
{
	result_t out = result_init(NODE_COMPOUND_STMT);
	
	// skip over opening brace
	parse_terminal(TOK_LBRACE);

	while (!is_terminal(TOK_RBRACE))
	{
		push_non_terminal(statement);
	}

	// skip over closing brace
	out.offs += 1;

	return out;

	parse_failure("compound-statement");
}


parse_func(declaration)
{
	result_t out = result_init(NODE_DECL_STMT);

	// check for 'var'
	parse_terminal(TOK_VAR);

	// get identifier
	push_non_terminal(identifier);

	// checking for type annotation
	if (is_terminal(TOK_COLON))
	{
		out.offs += 1;
		push_non_terminal(typename);
	}
	else
	{
		// push empty type if no type is annotated
		node_push_arg(out.node, node_create(NODE_EMPTY_TYPE));
	}

	// checking for equals sign
	parse_terminal(TOK_ASSIGN);

	// get assignment expression
	push_non_terminal(expression);

	// semicolon
	parse_terminal(TOK_SEMICOLON);

	return out;

	parse_failure("declaration");
}


parse_func(binary_expression)
{
	result_t out = result_init(NODE_NO_TYPE);

	// making space for arg
	node_push_arg(out.node, NULL);

	switch (toklist_getref(toks, index)->type)
	{
	// additive expression
	case TOK_PLUS:
	case TOK_MINUS:
		out.node->type = NODE_ADD_EXPR;
		break;

	// multiplicitive expression
	case TOK_MODULUS:
	case TOK_ASTERISK:
	case TOK_SLASH:
		out.node->type = NODE_MUL_EXPR;
		break;
	}
	out.offs = 1;

	push_non_terminal(expression);

	return out;

	parse_failure("binary-expression");
}


parse_func(expression)
{
	result_t out = result_init(NODE_NO_TYPE);

	token_t *t = toklist_getref(toks, index);

	// checking first token type
	switch (t->type)
	{
	// straight expressions
	case TOK_INT_LITERAL:
	case TOK_FLOAT_LITERAL:
	case TOK_STR_LITERAL:
	case TOK_IDENTIFIER:
		// gotta check for binary expressions
		out.node->val = t;
		out.offs = 1;

		break;

	// parenthesis expressions
	case TOK_LPAREN:
		break;

	// unary operators before expression
	case TOK_AMPERSAND:
	case TOK_ASTERISK:
	case TOK_MINUS:
	case TOK_EXCLAMATION:
	case TOK_INCREMENT:
	case TOK_DECREMENT:
		// add following expression
		//push_non_terminal(expression);
		break;

	}

	// if binary expression
	// this should be put in a while loop for expressions like (a ** 2 + b ** 2) ** .5
	switch (toklist_getref(toks, index + out.offs)->type)
	{
	// any of these are binary expressions
	case TOK_PLUS:
	case TOK_MINUS:
	case TOK_MODULUS:
	case TOK_ASTERISK:
	case TOK_SLASH:
		swap_non_terminal(binary_expression, 0);
		break;
	}

	return out;

	parse_failure("expression");
}


parse_func(statement)
{
	switch (toklist_getref(toks, index)->type)
	{
	// compound statement
	case TOK_LBRACE:
		return parse_compound_statement(toks, index);

	// declaration
	case TOK_VAR:
		return parse_declaration(toks, index);
	
	// expression statement
	default:
		return parse_expression(toks, index);
	}

	result_t out;
	out.ok = false;
	out.err = "statement";
	out.offs = 0;
	return out;
}


parse_func(function)
{
	result_t out = result_init(NODE_FUNCTION);
	
	// getting func token
	parse_terminal(TOK_FUNC);

	// getting identifier
	push_non_terminal(identifier);

	// getting arg list
	push_non_terminal(arglist);

	// checking for return type
	if (is_terminal(TOK_SINGLE_ARROW))
	{
		out.offs += 1;
		// getting return type
		push_non_terminal(typename);
	}
	else
	{
		// push empty type if no type is annotated
		node_push_arg(out.node, node_create(NODE_EMPTY_TYPE));
	}

	// getting statement
	push_non_terminal(statement);

	return out;

	parse_failure("function");
}


parse_func(program)
{
	result_t out = result_init(NODE_PROGRAM);

	// parse functions until end of file is reached
	while (toklist_getref(toks, index + out.offs)->type != TOK_EOF)
	{
		push_non_terminal(function);
	}

	return out;

	parse_failure("program");
}


node_t *parse(toklist_t *toks)
{
	result_t res = parse_program(toks, 0);
	if (!res.ok)
	{
		parse_error(toklist_getref(toks, res.offs), res.err);
		return NULL;
	}
	return res.node;
}
