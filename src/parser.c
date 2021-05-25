// header
#include <grackle/parser.h>

// local includes
#include <grackle/log.h>
#include <grackle/assert.h>

// standard library
#include <stdio.h>


// convenience defines for easier function definition
#define parse_terminal(term_type) if (toklist_get_ref(toks, index + out.offs)->type != term_type) goto exit_failure; out.offs += 1
#define is_terminal(term_type) (toklist_get_ref(toks, index + out.offs)->type == term_type)
#define parse_non_terminal(func)\
{\
	result_t res = parse_##func(toks, index + out.offs);\
	out.offs += res.offs;\
	if (!res.ok) { node_destroy(out.node); out.ok = false; out.err = res.err; return out; }\
	node_push_arg(out.node, res.node);\
}

#define parse_failure(expected) exit_failure: node_destroy(out.node); out.ok = false; out.err = expected; return out;
#define result_init(type) (result_t){ true, node_create(type), 0 }; printf("%s: ", __func__); string_put(toklist_get_ref(toks, index)->str)
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




// forward declarations of functions
parse_func(statement);
parse_func(expression);


parse_func(identifier)
{
	result_t out = result_init(NODE_IDENTIFIER);
	out.node->val = toklist_get_ref(toks, index + out.offs);
	if (out.node->val->type == TOK_IDENTIFIER)
	{
		out.offs += 1;
		return out;
	}
	parse_failure("identifier");
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
		parse_non_terminal(statement);
	}

	// skip over closing brace
	out.offs += 1;

	return out;

	parse_failure("compound-statement");
}


parse_func(declaration)
{
	result_t out = result_init(NODE_VAR_DECLARATION);

	// check for 'var'
	parse_terminal(TOK_VAR);

	// get identifier
	parse_non_terminal(identifier);

	// checking for type annotation
	if (is_terminal(TOK_COLON))
	{
		out.offs += 1;
		parse_non_terminal(identifier);
	}

	// checking for equals sign
	parse_terminal(TOK_ASSIGN);

	// get assignment expression
	parse_non_terminal(expression);

	// semicolon
	parse_terminal(TOK_SEMICOLON);

	return out;

	parse_failure("declaration");
}

parse_func(statement)
{
	switch (toklist_get_ref(toks, index)->type)
	{
	// compound statement
	case TOK_LBRACE:
		return parse_compound_statement(toks, index);

	// declaration
	case TOK_VAR:
		return parse_declaration(toks, index);
	}

	result_t out;
	out.ok = false;
	out.err = "statement";
	out.offs = 0;
	return out;
}


parse_func(expression)
{
	result_t out = result_init(NODE_EXPRESSION);

	token_t *t = toklist_get_ref(toks, index);

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
		return out;

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
		parse_non_terminal(expression);
		break;

	}

check_for_binary_expr:
	t = toklist_get_ref(toks, index + out.offs);
	switch (t->type)
	{
	case TOK_AMPERSAND:
	case TOK_PLUS:
	case TOK_MINUS:
	case TOK_SLASH:
		break;
	}

	return out;

	parse_failure("expression");
}


parse_func(function)
{
	result_t out = result_init(NODE_FUNCTION);
	
	// getting func token
	parse_terminal(TOK_FUNC);

	// getting identifier
	parse_non_terminal(identifier);

	// getting arg list
	parse_non_terminal(arglist);

	// checking for return type
	if (is_terminal(TOK_SINGLE_ARROW))
	{
		out.offs += 1;
		// getting return type
		parse_non_terminal(identifier);
	}

	// getting statement
	parse_non_terminal(statement);

	return out;

	parse_failure("function");
}


parse_func(program)
{
	result_t out = result_init(NODE_PROGRAM);

	parse_non_terminal(function);
	// this is how it will work, but we are only doing one for now
	// while (toklist_get_ref(toks, index + out.offs)->type != TOK_EOF)
	// {
	// }

	return out;

	parse_failure("program");
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
