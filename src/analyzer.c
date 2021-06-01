// header
#include <grackle/analyzer.h>

// local includes
#include <grackle/container/symtbl.h>

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


typedef struct scope
{
	symbol_t *sym;
	symtbl_t *sym_table;
} scope_t;

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

	printf(ERROR_PROMPT " %s '", type);
	string_put(sym->str);
	puts("' was previously declared");
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
		if (symtbl_containsn(scopes[depth - 1].sym_table, label->ptr, label->len))
		{
			return duplicate_symbol_error(&var_sym);
		}

		symtbl_setnref(scopes[depth - 1].sym_table, label->ptr, label->len, &var_sym);

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
	
	// error if symbol already exists in current scope
	if (symtbl_containsn(scopes[depth - 1].sym_table, label->ptr, label->len))
	{
		duplicate_symbol_error(&symbol);
	}

	// adding symbol to list
	symtbl_setnref(syms, label->ptr, label->len, &symbol);

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
