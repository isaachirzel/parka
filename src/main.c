// local includes

// standard library
#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[])
{
	validate_cli_args(argc, argv);

	std::string src = read_file(argv[1]);
	preprocesor(src);

// 	// preprocessing src
// 	preprocess(src);

// 	// printing src
// 	// puts(src);

// 	// lexing src
// 	lex_init();
// 	toklist_t *toks = lex(src);
// 	if (!toks) return 1;
// 	// pritning toks
// 	// print_toks(toks);

// 	// parsing src
// 	node_t *ast = parse(toks);
// 	if (!ast) goto cleanup;
	
// 	puts("\nAbstract Syntax Tree:");
// 	node_print(ast);

// 	puts("\n");
// 	// semantic analysis
// 	//if (!analyze(ast)) goto cleanup;

// 	// code generation
// 	// strlist_t *gen = generate(ast);
// 	// generate_print(gen);


// cleanup:
// 	// memory cleanup
// 	node_destroy(ast);
// 	toklist_destroy(toks);
// 	lex_cleanup();
// 	free(src);
	return 0;
}
