// header
#include <grackle/analyzer.h>

// local includes
#include <grackle/container/symtbl.h>

// standard library
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
	Todo for error handling:
		Type mismatch
		Undeclared / out-of-scope symbols
		Multiple declaration of symbols in same scope
		Actual and formal parameter mismatch
*/

string_t global_namespace_str = { "grac_", 5 };
symbol_t namespaces[128] = { { &global_namespace_str, SYM_GLOBAL } };

// TYPE TABLE


#define analyze_func(func) bool analyze_##func(node_t *node, unsigned char depth, symtbl_t *syms)


void duplicate_symbol_error(symbol_t *sym)
{
	char *symbol_name = string_duplicate(sym->str);
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

	printf("\033[91merror:\033[0m %s '%s' previously declared\n", type, symbol_name);
	free(symbol_name);
}


analyze_func(statement)
{
	switch (node->type)
	{
	case NODE_VAR_DECLARATION:;
		puts("BINGO");
		// handling identifier
		symbol_t sym = { &node->args[0]->val->str, SYM_VARIABLE };
		if (symtbl_containsn(syms, sym.str->ptr, sym.str->len)) duplicate_symbol_error(&sym);
		symtbl_setnref(syms, sym.str->ptr, sym.str->len, &sym);

		// handling type

		// handling value

		break;
	}
}


analyze_func(compound_statement)
{
	
}


analyze_func(function)
{
	puts(__func__);

	// handling identifier
	puts("A");
	// creating symbol
	symbol_t sym = { &node->args[0]->val->str, SYM_FUNCTION };
	puts("A");
	// error if symbol already exists in current scope
	if (symtbl_containsn(syms, sym.str->ptr, sym.str->len)) duplicate_symbol_error(&sym);
	puts("A");
	// adding symbol to list
	symtbl_setnref(syms, sym.str->ptr, sym.str->len, &sym);
	puts("A");
	namespaces[++depth] = sym;
puts("A");
	// handling type
	if (node->args[2]->val->type == TOK_IDENTIFIER)
	{
		// TODO: check if type exists
		// puts("IT's an IDENTIFIER");
	}
puts("A");
	// handling body. This is done by analyzing each statement of compound body
	// as analyze_compound_statement changes the scope
	puts("G");
	symtbl_t *func_syms = symtbl_create();
	puts("B");
	if (node->args[3]->type == NODE_COMPOUND_STMT)
	{
		puts("B");
		for (size_t i = 0; i < node->args[3]->argc; ++i)
		{
			analyze_statement(node->args[3]->args[i], depth, func_syms);
			puts("C");
		}
	}
	else
	{
		// single statement functions
		analyze_statement(node->args[3], depth, func_syms);
	}
	symtbl_destroy(func_syms);
}


analyze_func(program)
{
	puts(__func__);
	syms = symtbl_create();
	for (unsigned i = 0; i < node->argc; ++i)
	{
		analyze_function(node->args[i], depth, syms);
	}
	symtbl_destroy(syms);
}

void analyze(node_t *node)
{
	puts("\n\n");
	analyze_program(node, 0, NULL);
}

/*
global 				: grackle_
namespace and class	: <name>_
variables in funcs	: var_<name>
member variables	: m_<name>
functions			: func_<name>

ex:
int gackle_val = 3;

module mod
{
	export do_thing;


	export func do_thing() -> i32
	{

	}
}

void grackle_func_greet()
{
	puts("Hello");
}

int main()
{

}

*/

