// header
#include <grackle/analyzer.h>

// local includes
#include <grackle/log.h>
#include <grackle/data/scope.h>

// standard library
#include <string.h>
#include <stdlib.h>
#include <assert.h>


/*
	Done:
		- Multiple declaration of symbols in same scope
	Todo:
		- Type mismatch
		- Undeclared / out-of-scope symbols
			this will be done in expressions when symbols are used
		- Actual and formal parameter mismatch
			this is something that will happen in 
*/


// TYPE TABLE

// Macro definitions
#define analyze_func(func) bool analyze_##func(node_t *node, scope_t *scopes, const short depth)
#define call(func, node, depth) if (!analyze_##func(node, scopes, depth)) goto exit_failure
#define failure(call) exit_failure: { call } return false

#define COLOR_RED		"\033[31m"
#define COLOR_RESET		"\033[0m"
#define ERROR_PROMPT	COLOR_RED "error:" COLOR_RESET 

#define CREATE_SYMTBL(name)\
symtbl_t *name = symtbl_create();\
if (!name)\
{\
	puts(ERROR_PROMPT "failed to allocate symbol table");\
	return false;\
}

//
//	Error functions
//

bool duplicate_symbol_error(symbol_t *sym)
{
	const char *type = NULL;

	switch (sym->type)
	{
	case SYM_FUNCTION:
		type = "function";
		break;

	case SYM_VARIABLE:
		type = "variable";
		break;

	default:
		type = "symbol";
		break;
	}

	log_error_prompt(0, 0);
	fprintf(stderr, "%s '", type);
	string_fputs(sym->str, stderr);
	fputs("' was previously declared", stderr);
	return false;
}


//
//	Analyze functions
//

analyze_func(statement)
{
	switch (node->type)
	{
	case NODE_DECL_STMT:;
		puts("analyze var declaration");

		// handling identifier
		const string_t *label = &node->args[0]->val->str;
		symbol_t var_sym = { label, SYM_VARIABLE };

		// copying string_t into char buffer
		char id_buffer[129];
		strncpy(id_buffer, label->ptr, label->len);
		id_buffer[label->len] = 0;

		if (symtbl_contains(scopes[depth - 1].sym_table, id_buffer))
		{
			return duplicate_symbol_error(&var_sym);
		}

		symtbl_setref(scopes[depth - 1].sym_table, id_buffer, &var_sym);

		// handling type

		// handling value

		break;
	}
	return true;

	failure();
}


analyze_func(compound_statement)
{
	return false;
}


analyze_func(function)
{
	puts(__func__);

	// getting function name
	const string_t *label = &node->args[0]->val->str;
	// handling identifier
	CREATE_SYMTBL(syms);

	// creating symbol
	symbol_t symbol = { label, SYM_FUNCTION };
	scopes[depth] = (scope_t){ &symbol, syms };
	
	char id_buffer[129];
	strncpy(id_buffer, label->ptr, label->len);
	id_buffer[label->len] = 0;

	// error if symbol already exists in current scope
	if (symtbl_contains(scopes[depth - 1].sym_table, id_buffer))
	{
		duplicate_symbol_error(&symbol);
	}

	// adding symbol to list
	symtbl_setref(syms, id_buffer, &symbol);

	// handling type
	if (node->args[2]->val->type == TOK_IDENTIFIER)
	{
		// TODO: check if type exists
		// puts("IT's an IDENTIFIER");
	}

	// handling body. This is done by analyzing each statement of compound body
	// as analyze_compound_statement changes the scope
	
	if (node->args[3]->type == NODE_COMPOUND_STMT)
	{
		for (size_t i = 0; i < node->args[3]->argc; ++i)
		{
			call(statement, node->args[3]->args[i], depth + 1);
		}
	}
	else
	{
		// single statement functions
		call(statement, node->args[3], depth);
	}

	
	symtbl_destroy(syms);
	return true;

	failure(symtbl_destroy(syms););
}


bool analyze(node_t *node)
{
	string_t global_prefix = { "grac_", 5 };
	symbol_t global_symbol = { &global_prefix, SYM_GLOBAL };
	CREATE_SYMTBL(syms);
	scope_t scopes[64];
	scopes[0] = (scope_t){ &global_symbol, syms };

	for (unsigned i = 0; i < node->argc; ++i)
	{
		call(function, node->args[i], 1);
	}

	symtbl_destroy(syms);
	return true;

	failure(symtbl_destroy(syms););
}
