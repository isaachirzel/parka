#include <warbler/parser.h>

// local includes
#include <warbler/ast.h>

// standard
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define print_parse() printf("%s: ", __func__); string_put(&tok[0]->str)
#define parse_terminal(tok, expected_type, expected_tok, error_action) if (tok->type != expected_type) { syntax_error(tok, expected_tok); error_action; } tok += 1
#define parse_non_terminal(out, tok, function, error_action) { node_t *arg = parse_##function(&tok); if (!arg) error_action; node_push_arg(out, arg); }
#define parse_semicolon(tok, error_action) parse_terminal(tok, TOKEN_SEMICOLON, "';'", error_action)

void syntax_error(const Token *token, const char *expected)
{
	// log_error_prompt(tok->line, tok->col);
	// fprintf(stderr, "expected %s before '", expected);
	// string_fputs(&tok->str, stderr);
	// fputs("'\n", stderr);
}

// node_t *parse_identifier(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	if (t->type != TOKEN_IDENTIFIER)
// 	{
// 		printf("Type: %u\n", t->type);
// 		syntax_error(t, "identifier");
// 		return NULL;
// 	}
// 	node_t *out = node_create(NODE_IDENTIFIER);
// 	out->val = t;
// 	t += 1;
// 	*tok = t;
// 	return out;
// }

Error parse_program(Program **out, const Token *tokens[])
{
	assert(out != NULL);
	assert(tokens != NULL);

	return not_implemented_error();
}

Error parse_identifier(Identifier **out, const Token *tokens[])
{
	assert(out != NULL);
	assert(tokens != NULL);
	
	if (tokens[0]->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	Identifier *identifier;
	try_allocate(identifier);

	identifier->text = &tokens[0]->string;

	*tokens += 1;
	*out = identifier;

	return ERROR_NONE;
}

Error parse_typename(Typename **out, const Token *tokens[])
{
	const Token *iterator = *tokens;
	if (iterator[0].type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	Typename *typename;
	try_alloate(typename);		

	typename->text = &tokens[0]->string;

	*out = typename;
	*tokens += 1;

	return ERROR_NONE;
}

Error parse_label(Label **out, const Token *tokens[])
{
	const Token *tokens = *iterator;
	if (tokens[0].type != TOKEN_IDENTIFIER || tokens[1]->type != TOKEN_COLON)
		return ERROR_ARGUMENT;

	Label *label;
	try_allocate(label);

	label->text = &tokens[0]->string;

	*out = label;
	*tokens += 2;

	return ERROR_NONE;
}

Parameter *parse_parameter(const Token **tokens)
{
	const Token
	if (tokens[0]->type 
	const Token *t = *tok;

	node_t *out = node_create(NODE_PARAMETER);

	// getting identifier
	out->val = t;
	parse_terminal(t, TOKEN_IDENTIFIER, "identifier", goto failure);

	// checking for type annotation
	parse_terminal(t, TOKEN_COLON, "type-annotation", goto failure);

	// getting typename
	parse_non_terminal(out, t, typename, goto failure);

	// moving iterator forwards
	*tok = t;

	return out;

failure:

	node_destroy(out);
	return NULL;
}


// node_t *parse_parameter_list(const Token **tokens)
// {
// 	print_parse();
// 	node_t *out = node_create(NODE_PARAM_LIST);

// 	const Token *t = *tok;

// 	parse_terminal(t, TOKEN_LPAREN, "argument-list", goto failure);

// 	// empty list
// 	if (t->type == TOKEN_RPAREN)
// 	{
// 		t += 1;
// 	}
// 	// list of parameters
// 	else
// 	{
// 		// parse parameters as long as there is a comma
// 		while (true)
// 		{
// 			parse_non_terminal(out, t, parameter, goto failure);
// 			if (t->type != TOKEN_COMMA) break;
// 			t += 1;
// 		}
// 		parse_terminal(t, TOKEN_RPAREN, ")", goto failure);
// 	}

// 	*tok = t;

// 	return out;

// failure:

// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_member_access(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
	
// 	node_t *out = node_create(NODE_MEMBER_ACCESS);
// 	parse_terminal(t, TOKEN_DOT, "member-access operator", goto failure);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_IDENTIFIER, "identifier", goto failure);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_function_call(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_FUNCTION_CALL);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_LPAREN, "function-call", goto failure);

// 	// getting arguments
// 	// empty list
// 	if (t->type == TOKEN_RPAREN)
// 	{
// 		t += 1;
// 	}
// 	// list of parameters
// 	else
// 	{
// 		// parse parameters as long as there is a comma
// 		while (true)
// 		{
// 			parse_non_terminal(out, t, expression, goto failure);
// 			if (t->type != TOKEN_COMMA) break;
// 			t += 1;
// 		}
// 		parse_terminal(t, TOKEN_RPAREN, ")", goto failure);
// 	}


// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_index(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_INDEX);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_LBRACK, "index-operation", goto failure);
// 	parse_non_terminal(out, t, expression, goto failure);
// 	parse_terminal(t, TOKEN_RBRACK, "']'", goto failure);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_factor(const Token **tokens)
// {
// 	print_parse();
// 	node_t *out = node_create(NODE_FACTOR);

// 	const Token *t = *tok;

// 	switch (t->type)
// 	{
// 	case TOKEN_INT_LITERAL:
// 	case TOKEN_STR_LITERAL:
// 	case TOKEN_FLOAT_LITERAL:
// 	case TOKEN_TRUE:
// 	case TOKEN_FALSE:
// 	case TOKEN_IDENTIFIER:
// 		out->val = t++;
// 		*tok = t;
// 		break;

// 	case TOKEN_LPAREN:
// 		out->val = t++;
// 		parse_non_terminal(out, t, expression, break);
// 		parse_terminal(t, TOKEN_RPAREN, "')'", goto failure);
// 		*tok = t;
// 		break;;

// 	default:
// 		syntax_error(t, "factor");
// 		goto failure;
// 	}

// 	// parsing suffix expressions
// 	while (true)
// 	{
// 		node_t *arg;
// 		switch (t->type)
// 		{
// 		case TOKEN_INCREMENT:
// 			arg = node_create(NODE_INCREMENT);
// 			break;

// 		case TOKEN_DECREMENT:
// 			arg = node_create(NODE_DECREMENT);
// 			break;

// 		// member access
// 		case TOKEN_DOT:
// 			arg = parse_member_access(&t);
// 			break;

// 		// indexing
// 		case TOKEN_LBRACK:
// 			arg = parse_index(&t);
// 			break;

// 		// function call
// 		case TOKEN_LPAREN:
// 			arg = parse_function_call(&t);
// 			break;

// 		default:
// 			*tok = t;
// 			return out;
// 		}

// 		// adding suffix to factor
// 		if (!arg) return NULL;
// 		node_push_arg(out, arg);
// 	}

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_prefix_expression(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;

// 	switch (t->type)
// 	{
// 	case TOKEN_INCREMENT:
// 	case TOKEN_DECREMENT:
// 	case TOKEN_PLUS:
// 	case TOKEN_MINUS:
// 	case TOKEN_EXCLAMATION:
// 	case TOKEN_ASTERISK:
// 	case TOKEN_AMPERSAND:
// 		break;

// 	default:
// 		return parse_factor(tok);
// 	}

// 	node_t *out = node_create(NODE_PREFIX_EXPR);
// 	out->val = t++;

// 	// getting further prefixes
// 	parse_non_terminal(out, t, prefix_expression, goto failure);
	
// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// bool is_mul_expr(const Token *tok)
// {
// 	switch (tok->type)
// 	{
// 	case TOKEN_ASTERISK:
// 	case TOKEN_SLASH:
// 	case TOKEN_MODULUS:
// 		return true;

// 	default:
// 		return false;
// 	}
// }


// bool is_add_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_PLUS || tok->type == TOKEN_MINUS;
// }


// bool is_shift_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_LSHIFT || tok->type == TOKEN_RSHIFT;
// }


// bool is_comp_expr(const Token *tok)
// {
// 	switch (tok->type)
// 	{
// 	case TOKEN_LANGBRACK:
// 	case TOKEN_RANGBRACK:
// 	case TOKEN_LTOET:
// 	case TOKEN_GTOET:
// 		return true;

// 	default:
// 		return false;
// 	}
// }


// bool is_equal_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_EQUALS || tok->type == TOKEN_NEQUALS;
// }


// bool is_bitand_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_AMPERSAND;
// }


// bool is_bitxor_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_CARROT;
// }


// bool is_bitor_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_PIPELINE;
// }

// bool is_and_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_AND;
// }


// bool is_or_expr(const Token *tok)
// {
// 	return tok->type == TOKEN_OR;
// }



// typedef bool (*condition_func)(const Token *);

// typedef struct binexpr
// {
// 	condition_func condition;
// 	short id;
// } binexpr_t;

// binexpr_t binexprs[] =
// {
// 	{ is_mul_expr, NODE_MUL_EXPR },
// 	{ is_add_expr, NODE_ADD_EXPR },
// 	{ is_shift_expr, NODE_SHIFT_EXPR },
// 	{ is_comp_expr, NODE_COMP_EXPR },
// 	{ is_equal_expr, NODE_EQ_EXPR },
// 	{ is_bitand_expr, NODE_BITAND_EXPR },
// 	{ is_bitxor_expr, NODE_BITXOR_EXPR },
// 	{ is_bitor_expr, NODE_BITOR_EXPR },
// 	{ is_and_expr, NODE_AND_EXPR },
// 	{ is_or_expr, NODE_OR_EXPR },
// };


// node_t *parse_binary_recurse(const Token **tokens, const unsigned precedence)
// {
// 	printf("%s(%u): ", __func__, precedence);
// 	string_put(&(*tok)->str);

// 	const Token *t = *tok;
// 	binexpr_t *type = binexprs + precedence;

// 	node_t *left = (!precedence) ?
// 		parse_prefix_expression(&t) :
// 		parse_binary_recurse(&t, precedence - 1);
// 	if (!left) return NULL;

// 	// if not binary, just return first term
// 	if (!type->condition(t))
// 	{
// 		*tok = t;
// 		return left;
// 	}
// 	t += 1;

// 	// make binary node
// 	node_t *out = node_create(type->id);
// 	out->val = t - 1;
// 	node_t *right = (!precedence) ?
// 		parse_prefix_expression(&t) :
// 		parse_binary_recurse(&t, precedence - 1);
// 	if (!right) goto failure;
// 	node_push_arg(out, left);
// 	node_push_arg(out, right);

// 	// while there is still a chain of same-type expressions
// 	while (type->condition(t))
// 	{
// 		// storing out as lehing
// 		// creating tree
// 		out = node_create(type->id);
// 		out->val = t;
// 		t += 1;
// 		// getting right side leaf
// 		right = (!precedence) ?
// 			parse_prefix_expression(&t) :
// 			parse_binary_recurse(&t, precedence - 1);
// 		if (!right) goto failure;
// 		// adding args to tree
// 		node_push_arg(out, left);
// 		node_push_arg(out, right);
// 	}

// 	*tok = t;
// 	return out;

// failure:

// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_binary_expression(const Token **tokens)
// {
// 	return parse_binary_recurse(tok, sizeof(binexprs) / sizeof(binexpr_t) - 1);
// }


// node_t *parse_assignment(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;

// 	node_t *left = parse_binary_expression(&t);

// 	switch (t->type)
// 	{
// 	case TOKEN_ASSIGN:
// 	case TOKEN_ADD_ASSIGN:
// 	case TOKEN_SUB_ASSIGN:
// 	case TOKEN_MUL_ASSIGN:
// 	case TOKEN_DIV_ASSIGN:
// 	case TOKEN_MOD_ASSIGN:
// 		break;
// 	default:
// 		puts("Not an assignment");
// 		*tok = t;
// 		return left;
// 	}

// 	node_t *out = node_create(NODE_ASSIGN_EXPR);
// 	out->val = t;
// 	t += 1;
// 	node_push_arg(out, left);

// 	node_t *right = parse_assignment(&t);
// 	node_push_arg(out, right);

// 	*tok = t;
// 	return out;
// }


Error parse_expression(Expression **out, const Token *tokens[])
{
	Expression *expression;
	try_allocate(expression);
	
	try_cleanup(parse_assignment_expression(&expression->assignment, tokens), {
		free(expression);
	});

	*out = expression;
	return ERROR_NONE;
}

bool is_assignment_token(const Token* token)
{
	return token->type == TOKEN_ASSIGN;
	// switch (token->type)
	// {
	// 	case TOKEN_ASSIGN:
	// 	case TOKEN_BECOME_ASSIGN:
	// 	case TOKEN_ADD_ASSIGN:
	// 	case TOKEN_SUBTRACT_ASSIGN:
	// 	case TOKEN_MULTIPLY_ASSIGN:
	// 	case TOKEN_DIVIDE_ASSIGN:
	// 	case TOKEN_MODULUS_ASSIGN:
	// 	case TOKEN_LSHIFT_ASSIGN:
	// 	case TOKEN_RSHIFT_ASSIGN:
	// 		return true;
	// 	default:
	// 		return false;
	// }
}

Error parse_assignment_expression(AssignmentExpression **out, const Token *tokens[])
{
	AssignmentExpression *assignment;
	try_allocate(assignment);

	try_cleanup(parse_unary_expression(&assignment->left, iterator), {
		free(assignment);
	});

	const Token *tokens = *iterator;

	if (is_assignment_token(tokens))
	{

	}

	*out = assignment;
	return ERROR_NONE;
}

// node_t *parse_if_statement(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_IF_STMT);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_IF, "if-statement", goto failure);
// 	parse_non_terminal(out, t, expression, goto failure);
// 	parse_non_terminal(out, t, statement, goto failure);

// 	if (t->type == TOKEN_ELSE)
// 	{
// 		t += 1;
// 		parse_non_terminal(out, t, statement, goto failure);
// 	}

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_switch_statement(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_IF_STMT);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_SWITCH, "switch-statement", goto failure);


// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_loop_statement(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_IF_STMT);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_LOOP, "loop-statement", goto failure);
// 	parse_non_terminal(out, t, statement, goto failure);
// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_while_statement(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_WHILE_STMT);
// 	out->val = t;
// 	parse_terminal(t, TOKEN_WHILE, "while-statement", goto failure);
// 	parse_non_terminal(out, t, expression, goto failure);
// 	parse_non_terminal(out, t, statement, goto failure);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_for_statement(const Token **tokens)
// {

// 	log_errorf((*tok)->line, (*tok)->col, "%s is not yet implemented\n", __func__);
// 	return NULL;
// }


// node_t *parse_jump_statement(const Token **tokens)
// {
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_NO_TYPE);
// 	out->val = t;

// 	switch (t->type)
// 	{
// 	case TOKEN_CONTINUE:
// 		out->type = NODE_CONTINUE_STMT;
// 		break;

// 	case TOKEN_BREAK:
// 		out->type = NODE_BREAK_STMT;
// 		break;
// 	}

// 	t += 1;

// 	parse_semicolon(t,
// 	{
// 		node_destroy(out);
// 		return NULL;
// 	});

// 	*tok = t;
// 	return out;
// }


// node_t *parse_return_statement(const Token **tokens)
// {
// 	const Token *t = *tok;
// 	parse_terminal(t, TOKEN_RETURN, "return-statement", return NULL);
// 	node_t *out = node_create(NODE_RETURN_STMT);
// 	out->val = t - 1;
// 	// if returning a value
// 	if (t->type != TOKEN_SEMICOLON)
// 	{
// 		parse_non_terminal(out, t, expression, goto failure);
// 		parse_terminal(t, TOKEN_SEMICOLON, "';'", goto failure);
// 	}
// 	else
// 	{
// 		t += 1;
// 	}

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_compound_statement(const Token **tokens)
// {
// 	print_parse();
// 	node_t *out = node_create(NODE_COMPOUND_STMT);

// 	const Token *t = *tok;
// 	out->val = t;
// 	// skip over opening brace
// 	parse_terminal(t, TOKEN_LBRACE, "compound-statement", goto failure);

// 	while (t->type != TOKEN_RBRACE)
// 	{
// 		parse_non_terminal(out, t, statement, goto failure);
// 	}
// 	t += 1;

// 	*tok = t;
// 	return out;

// failure:

// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_declaration(const Token **tokens)
// {
// 	print_parse();
// 	node_t *out = node_create(NODE_DECL_STMT);

// 	const Token *t = *tok;

// 	// check for var keyword
// 	parse_terminal(t, TOKEN_VAR, "declaration", goto failure);
// 	// setting token value to var keyword (used in printing)
// 	out->val = t - 1;


// 	// get identifier
// 	parse_non_terminal(out, t, identifier, goto failure);

// 	// checking for type annotation
// 	if (t->type == TOKEN_COLON)
// 	{
// 		t += 1;
// 		node_t *type = parse_typename(&t);
// 		if (!type) goto failure;
// 		node_push_arg(out, type);
// 	}
// 	else
// 	{
		
// 		// push empty type if no type is annotated
// 		node_push_arg(out, node_create(NODE_TYPENAME));
// 	}
	
// 	// checking for equals sign
// 	if (t->type != TOKEN_ASSIGN)
// 	{
// 		log_error(t->line, t->col, "declaration of uninitialized variables is not allowed");
// 		goto failure;
// 	}
// 	t += 1;

// 	// get assignment expression
// 	parse_non_terminal(out, t, expression, goto failure);

// 	// semicolon
// 	parse_terminal(t, TOKEN_SEMICOLON, "';'", goto failure);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_statement(const Token **tokens)
// {
// 	print_parse();
// 	switch ((*tok)->type)
// 	{
// 	// compound statement
// 	case TOKEN_LBRACE:
// 		return parse_compound_statement(tok);

// 	// declaration
// 	case TOKEN_VAR:
// 		return parse_declaration(tok);

// 	case TOKEN_IF:
// 		return parse_if_statement(tok);

// 	case TOKEN_WHILE:
// 		return parse_while_statement(tok);

// 	case TOKEN_LOOP:
// 		return parse_loop_statement(tok);

// 	case TOKEN_FOR:
// 		return parse_for_statement(tok);

// 	case TOKEN_SWITCH:
// 		return parse_switch_statement(tok);

// 	case TOKEN_BREAK:
// 	case TOKEN_CONTINUE:
// 		return parse_jump_statement(tok);

// 	case TOKEN_RETURN:
// 		return parse_return_statement(tok);

// 	// no-op
// 	case TOKEN_SEMICOLON:;
// 		node_t *noop = node_create(NODE_NOOP_STMT);
// 		noop->val = *tok;
// 		return noop;

// 	// expression statement
// 	default:;
// 		node_t *expr = parse_expression(tok);
// 		if (!expr) return NULL;
// 		const Token *t = *tok;
// 		if (t->type != TOKEN_SEMICOLON)
// 		{
// 			syntax_error(t, "';'");
// 			return NULL;
// 		}
// 		*tok = t + 1;
// 		return expr;
// 	}
// }


// node_t *parse_function(const Token **tokens)
// {
// 	print_parse();
// 	node_t *out = node_create(NODE_FUNCTION);
	
// 	const Token *t = *tok;

// 	// getting func token
// 	parse_terminal(t, TOKEN_FUNC, "function", goto failure);
// 	out->val = t - 1;

// 	// getting identifier
// 	parse_non_terminal(out, t, identifier, goto failure);

// 	// getting arg list
// 	parse_non_terminal(out, t, parameter_list, goto failure);

// 	// checking for return type
// 	if (t->type == TOKEN_SINGLE_ARROW)
// 	{
// 		t += 1;
// 		// getting return type
// 		node_t *type = parse_typename(&t);
// 		if (!type) goto failure;
// 		node_push_arg(out, type);
// 	}
// 	else
// 	{
// 		// push empty type if no type is annotated
// 		node_push_arg(out, node_create(NODE_TYPENAME));
// 	}

// 	// getting statement
// 	switch (t->type)
// 	{
// 	// compound statement
// 	case TOKEN_LBRACE:;
// 		node_t *compound = parse_compound_statement(&t);
// 		if (!compound) goto failure;
// 		node_push_arg(out, compound);
// 		break;

// 	// expression
// 	case TOKEN_DOUBLE_ARROW:;
// 		t += 1;
// 		parse_non_terminal(out, t, expression, goto failure);
// 		parse_semicolon(t, goto failure);
// 		break;
	
// 	// error
// 	default:
// 		syntax_error(t, "function-body");
// 		goto failure;
// 	}

// 	*tok = t;
// 	return out;


// failure:

// 	node_destroy(out);
// 	return NULL;
// }


// // node_t *parse_(const Token **tokens)
// // {
// // 	print_parse();
// // 	const Token *t = *tok;
// // 	node_t *out = node_create(NODE_COMPONENT);

// // 	*tok = t;
// // 	return out;

// // failure:
// // 	node_destroy(out);
// // 	return NULL;
// // }

// node_t *parse_union(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_UNION);
// 	out->val = t;

// 	parse_terminal(t, TOKEN_UNION, "union", goto failure);
// 	parse_terminal(t, TOKEN_LBRACE, "union-definition", goto failure);
// 	while (t->type != TOKEN_RBRACE)
// 	{
// 		parse_non_terminal(out, t, parameter, goto failure);
// 	}
// 	t += 1;

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }

// node_t *parse_enum(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_ENUM);
// 	out->val = t;

// 	parse_terminal(t, TOKEN_ENUM, "enum", goto failure);
// 	parse_terminal(t, TOKEN_LBRACE, "enum-definition", goto failure);
// 	if (t->type == TOKEN_RBRACE)
// 	{
// 		t += 1;
// 	}
// 	else
// 	{
// 		while (true)
// 		{
// 			parse_non_terminal(out, t, identifier, goto failure);
// 			if (t->type != TOKEN_COMMA) break;
// 			t += 1;
// 		}

// 		parse_terminal(t, TOKEN_RBRACE, "'}'", goto failure);
// 	}

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_struct(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_STRUCT);
// 	out->val = t;

// 	parse_terminal(t, TOKEN_STRUCT, "struct", goto failure);
// 	parse_terminal(t, TOKEN_LBRACE, "struct-definition", goto failure);
// 	while (t->type != TOKEN_RBRACE)
// 	{
// 		parse_non_terminal(out, t, parameter, goto failure);
// 	}
// 	t += 1;

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_type(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_TYPE);
// 	out->val = t;

// 	parse_terminal(t, TOKEN_TYPE, "type-definition", goto failure);
// 	parse_non_terminal(out, t, label, goto failure);

// 	switch (t->type)
// 	{
// 	case TOKEN_STRUCT:
// 		parse_non_terminal(out, t, struct, goto failure);
// 		break;

// 	case TOKEN_ENUM:
// 		parse_non_terminal(out, t, enum, goto failure);
// 		break;

// 	case TOKEN_UNION:
// 		parse_non_terminal(out, t, union, goto failure);
// 		break;

// 	default:
// 		parse_non_terminal(out, t, typename, goto failure);
// 		parse_semicolon(t, goto failure);
// 		break;
// 	}

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_import(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_COMPONENT);

// 	out->val = t;
// 	parse_terminal(t, TOKEN_IMPORT, "import-statement", goto failure);
// 	parse_non_terminal(out, t, identifier, goto failure);
// 	parse_semicolon(t, goto failure);

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse_module(const Token **tokens)
// {
// 	print_parse();
// 	const Token *t = *tok;
// 	node_t *out = node_create(NODE_MODULE);

// 	while (t->type != TOKEN_EOF)
// 	{
// 		switch (t->type)
// 		{
// 		// function definition
// 		case TOKEN_FUNC:
// 			parse_non_terminal(out, t, function, goto failure);
// 			break;

// 		// import statement
// 		case TOKEN_IMPORT:
// 			parse_non_terminal(out, t, import, goto failure);
// 			break;

// 		// type definition
// 		case TOKEN_TYPE:
// 			parse_non_terminal(out, t, type, goto failure);
// 			break;

// 		default:
// 			syntax_error(t, "module-component");
// 			goto failure;
// 		}
// 	}

// 	*tok = t;
// 	return out;

// failure:
// 	node_destroy(out);
// 	return NULL;
// }


// node_t *parse(toklist_t *toks)
// {
// 	return parse_module((const Token **)&toks->data);
// }
